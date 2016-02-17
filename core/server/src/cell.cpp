/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as published
 *  by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 *  Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  You may obtain a copy of the License at
 *
 *  <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *    http://www.jedox.com/license_palo_bi_suite.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 *
 *  \author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "cell.hpp"

#include "wss/formula.hpp"
#include "wss/session.hpp"
#include "wss/object_not_found_exception.hpp"
#include "wss/can_not_change_part_of_an_array_exception.hpp"
#include "wss/calculation_context.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/i_dependency_reference.hpp"
#include "wss/worksheet.hpp"
#include "cell_manager.hpp"
#include "wss/range_reference.hpp"
#include "wss/named_formula_reference.hpp"
#include "wss/reference_operation.hpp"
#include "wss/syntax.hpp"
#include "wss/allocation.hpp"
#include "wss/ast_formula.hpp"
#include "wss/sheet_layout_manager.hpp"
#include "stack_calculation.hpp"
#include "formula_kernel.hpp"
#ifdef _DEBUG
#   include "wss/a1conversion.hpp"
#endif // _DEBUG

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
# include <boost/bind.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0
#include "wss/insert_from_temporary.hpp"
#include "wss/calculation_setting.hpp"
#include "wss/cyclic_dependency_set.hpp"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class scoped_named_formula_initiator_reset
{
public:
    scoped_named_formula_initiator_reset( interpreter_context& ic )
        : m_is_inside_named_formula( ic.is_inside_named_formula() )
        , m_ic( ic ) {
        m_ic.is_inside_named_formula( false );
    }

    ~scoped_named_formula_initiator_reset() {
        m_ic.is_inside_named_formula( m_is_inside_named_formula );
    }
private:
    const bool m_is_inside_named_formula;
    interpreter_context& m_ic;
};

/*!
 * \brief
 * interface class for the different kernel types.
 *
 * the various kernel types implement most of the
 * actual dependency interface.
 * a cell containing a constant value for example
 * will never be dirty and will also always return
 * false for has_formula (opposed to the
 * formula_kernel).
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class cell::i_cell_kernel
{
public:
    /*!
     * \brief
     * all available kernel types are listed here.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct kernel_type {
        enum type {
            formula_kernel     // formula cell
            , empty_kernel       // no value. simply empty.
            , constant_kernel    // cell which contains a constant value (as opposed to an formula)
            , master_kernel      // the upper-left cell of a cell-array. containing the actual formula.
            , slave_kernel       // all the other cells in a cell-array grid. these will refer to their master
            // kernel to fetch values.
        };
    };

    /*!
     * \brief
     * pointer type which will hold the cells kernel type
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    typedef destroying_auto_pointer<i_cell_kernel> auto_type;

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual ~i_cell_kernel() {}

    /*!
     * \brief
     * destroy - called upon destruction of the object.
     *
     * method that the auto pointer holding the object will
     * call to delete the object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void destroy() = 0;

    /*!
     * \brief
     * type of the kernel.
     *
     * like formula_kernel, constant_kernel, ...
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual kernel_type::type type() const = 0;

    /*!
     * \brief
     * used for the formula_kernel to connect the formula
     * with it's precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void commit_kernel_change() = 0;

    /*!
     * \brief
     * returns true in case the kernel contains a formula.
     *
     * basically only the formula_kernel, the master_kernel
     * and the slave_kernel will return true here.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_formula() const = 0;

    /*!
     * \brief
     * returns true in case the kernel contains a formula which
     * contains precedents (other dependencies which must be calculated
     * before this dependency can be calculated).
     *
     * basically only the formula_kernel, the master_kernel
     * and the slave_kernel will return true here.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_precedents() const = 0;

    /*!
     * \brief
     * returns the precedents of a formula.
     *
     * basically only the formula_kernel, the master_kernel
     * and the slave_kernel may return something here.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual referencetable_type precedents() const = 0;

    /*!
     * \brief
     * will be called from within the interpreter.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( interpreter_context&, bool ) const = 0;

    /*!
     * \brief
     * will be called from outside the interpreter and possibly
     * start a calculation in case the state of the object is "dirty".
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( calculation_context&, bool ) const = 0;

    /*!
     * \brief
     * return the locale based pretty printed formula
     * (if any).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::string formula( const locale& ) const = 0;

    /*!
     * \brief
     * will return true in case the object has the dirty flag set or contains
     * a volatile value that has not as of yet been cached.
     *
     * in case this method returns true this will mean that a calculation
     * is in order.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual optional_variant_type fetch_cached_volatile( calculation_context& ) const = 0;

    /*!
     * \brief
     * the object has the dirty flag set.
     *
     * constant kernels f.ex. will never be dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_dirty() const = 0;

    /*!
     * \brief
     * the objects value is volatile
     * (depends on a database query, time function or random value, ...)
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_volatile() const = 0;

    /*!
     * \brief
     * number of precedents (including self) that are of volatile nature.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual unsigned long volatile_count() const = 0;

    /*!
     * \brief
     * number of precedents (excluding self) that are of volatile nature.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual unsigned long volatile_count_without_formula() const = 0;

    /*!
     * \brief
     * raise the volatile count of the dependency
     *
     * does not update the object dependencies but only the
     * object itself
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_raise_volatile_count() = 0;

    /*!
     * \brief
     * lower the volatile count of the dependency
     *
     * does not update the object dependencies but only the
     * object itself
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_lower_volatile_count() = 0;

    /*!
     * \brief
     * will return true in case the object is part of an
     * cell array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_array() const = 0;

    /*!
     * \brief
     * copy operation. relative references need to be rewritten depending on
     * the new location on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual auto_type copy( cell&, const geometry::point&, bool, bool, const sheet_range& ) const = 0;

    /*!
     * \brief
     * in case that the current object is part of a cell array
     * will return the coverage of that cell array on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual sheet_range array_coverage() const = 0;

    /*!
     * \brief
     * will flag the dependency dirty without triggering
     * the dirty flagging of all dependents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_flag_dirty() = 0;

    /*!
     * \brief
     * given a cached volatile value this function
     * will extract the correct value for the current array cell
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual variant handle_cached_volatile( const optional_variant_type& v ) const = 0;

    virtual dependency_set_type slave_dependents() const {
        assert( !"only master cells should be called!" );
        return dependency_set_type();
    }

    virtual bool slaves_have_dependents() const {
        assert( !"only master cells should be called!" );
        return false;
    }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * cell with empty content.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class cell::empty_cell
    : public i_cell_kernel
{
    friend class memory::pooled_creator<empty_cell>;
public:
    /*!
     * \brief
     * factory method
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static auto_type create() {
        return auto_type( memory::pooled_creator<empty_cell>::create() );
    }

    /*!
     * \brief
     * free the allocated memory
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void destroy() {
        memory::pooled_creator<empty_cell>::destroy( this );
    }

    /*!
     * \brief
     * return the kernels type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual kernel_type::type type() const {
        return kernel_type::empty_kernel;
    }

    /*!
     * \brief
     * not needed for kernels of empty type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void commit_kernel_change() {
    }

    /*!
     * \brief
     * empty kernels never have formulas
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_formula() const {
        return false;
    }

    /*!
     * \brief
     * empty kernels never have precedents
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_precedents() const {
        return false;
    }

    /*!
     * \brief
     * empty kernels never have precedents
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual referencetable_type precedents() const {
        static referencetable_type empty;
        return empty;
    }

    /*!
     * \brief
     * empty kernels never have a value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( calculation_context&, bool ) const {
        return variant();
    }

    /*!
     * \brief
     * empty kernels never have a value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( interpreter_context&, bool ) const {
        return variant();
    }

    /*!
     * \brief
     * empty kernels never have a formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::string formula( const locale& ) const {
        return std::string();
    }

    /*!
     * \brief
     * empty kernels never have a volatile value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual optional_variant_type fetch_cached_volatile( calculation_context& ) const {
        return false;
    }

    /*!
     * \brief
     * empty kernels are never dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_dirty() const {
        return false;
    }

    /*!
     * \brief
     * empty kernels are never volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_volatile() const {
        return false;
    }

    /*!
     * \brief
     * empty kernels are never volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual unsigned long volatile_count() const {
        return 0;
    }

    /*!
     * \brief
     * empty kernels are never volatile.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual unsigned long volatile_count_without_formula()  const {
        return 0;
    }

    /*!
     * \brief
     * empty kernels are never volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_raise_volatile_count() {
        assert( false );
    }

    /*!
     * \brief
     * empty kernels are never volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_lower_volatile_count() {
        //assert( false );
    }

    /*!
     * \brief
     * empty kernels can not be arrays.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_array() const {
        return false;
    }

    /*!
     * \brief
     * copy implementation, will create a copy of the current kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual auto_type copy( cell&, const geometry::point&, bool, bool, const sheet_range& ) const {
        return auto_type( empty_cell::create() );
    }

    /*!
     * \brief
     * empty kernels do not have coverage.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual sheet_range array_coverage() const {
        return sheet_range( sheet_point( 0, 0 ) );
    }

    /*!
     * \brief
     * empty kernels are never dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_flag_dirty() {}

    /*!
     * \brief
     * empty kernels can't have a cached volatile value
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual variant handle_cached_volatile( const optional_variant_type& v ) const {
        assert( !"empty kernels can't have a cached volatile value" );
        return variant();
    }

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    empty_cell() {}
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * cell containing a formula.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class cell::formula_cell
    : public i_cell_kernel
{
    friend class memory::pooled_creator<formula_cell>;
public:
    /*!
     * \brief
     * factory method
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static auto_type create( cell& parent, ast_formula& ast, const referencetable_type& references ) {
        return auto_type( memory::pooled_creator<formula_cell>::create( parent, ast, references ) );
    }

    /*!
     * \brief
     * factory method
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static auto_type create( cell& parent, const formula_cell& other, const geometry::point& distance, bool is_rewrite_to_other_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& references ) {
        return auto_type( memory::pooled_creator<formula_cell>::create( parent, other, distance, is_rewrite_to_other_sheet, use_copy_move, source_range, references ) );
    }

    /*!
     * \brief
     * free the allocated memory
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void destroy() {
        memory::pooled_creator<formula_cell>::destroy( this );
    }

    /*!
     * \brief
     * return the type of the current kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual kernel_type::type type() const {
        return kernel_type::formula_kernel;
    }

    /*!
     * \brief
     * a new kernel has been set, connect the kernels precedents to the
     * new containing dependency.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void commit_kernel_change() {
        m_formula_kernel->connect_precedents();
    }

    /*!
     * \brief
     * unload the formula kernel. free all precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unload() {
        m_formula_kernel->unload();
    }

    /*!
     * \brief
     * return true in case the formula contains references to other
     * objects (cells, named formulas).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_precedents() const {
        return m_formula_kernel->has_precedents();
    }

    /*!
     * \brief
     * return the precedents list
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual referencetable_type precedents() const {
        return m_formula_kernel->precedents();
    }

    /*!
     * \brief
     * return the calculated value of the cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( interpreter_context& ic, bool ) const {
        return m_formula_kernel->value();
    }

    /*!
     * \brief
     * return the calculated value of the cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( calculation_context& cc, bool ) const {
        return m_formula_kernel->value();
    }

    /*!
     * \brief
     * return the pretty printed formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::string formula( const locale& l ) const {
        return m_formula_kernel->formula( l );
    }

    /*!
     * \brief
     * start a delayed calculation process.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_calculation delayed_calculation( calculation_context& cc ) {
        return m_formula_kernel->delayed_calculation( cc );
    }

    /*!
     * \brief
     * fetch a cached volatile value from the formula kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual optional_variant_type fetch_cached_volatile( calculation_context& cc ) const {
        return m_formula_kernel->fetch_cached_volatile( cc );
    }

    /*!
     * \brief
     * return true in case the formula is marked as being dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_dirty() const {
        return m_formula_kernel->is_dirty();
    }

    /*!
     * \brief
     * return true in case the formula contains volatile values.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_volatile() const {
        return m_formula_kernel->is_volatile();
    }

    /*!
     * \brief
     * return the volatile count of the formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual unsigned long volatile_count() const {
        return m_formula_kernel->volatile_count();
    }

    /*!
     * \brief
     * return the volatile count of the formula (excluding self)
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual unsigned long volatile_count_without_formula() const {
        return m_formula_kernel->volatile_count_without_formula();
    }

    /*!
     * \brief
     * will always return false.
     *
     * see array_master / array_slave kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_array() const {
        return false;
    }

    /*!
     * \brief
     * will always return an sheet_range with 0,0 dimensions.
     *
     * see array_master / array_slave kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual sheet_range array_coverage() const {
        static const sheet_range empty( sheet_point( 0, 0 ) );
        return empty;
    }

    /*!
     * \brief
     * mark the formula kernel as dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_flag_dirty() {
        m_formula_kernel->flag_dirty();
    }

    /*!
     * \brief
     * raise the volatile count of the kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_raise_volatile_count() {
        m_formula_kernel->internal_raise_volatile_count();
    }

    /*!
     * \brief
     * lower the volatile count.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_lower_volatile_count() {
        m_formula_kernel->internal_lower_volatile_count();
    }

    /*!
     * \brief
     * copy and rewrite the formula to it's target destination.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual auto_type copy( cell& parent, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range ) const {
        return create( parent, *this, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, parent.precedents() );
    }

    /*!
     * \brief
     * will always return true (its a formula_kernel after all).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_formula() const {
        return true;
    }

    /*!
     * \brief
     * formula kernels just pass the value
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual variant handle_cached_volatile( const optional_variant_type& v ) const {
        return *v;
    }

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_cell( cell& parent, ast_formula& ast, const referencetable_type& references )
        : m_formula_kernel( formula_kernel::create( parent.shared_from_this(), ast, references ) ) {}

    /*!
     * \brief
     * copying constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_cell( cell& parent, const formula_cell& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& references )
        : m_formula_kernel( formula_kernel::create( parent.shared_from_this(), *other.m_formula_kernel, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, references ) ) {}

    shared_formula_kernel_type m_formula_kernel;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * constant cell.
 *
 * a cell that does contain a constant value.
 * like strings or doubles.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class cell::constant_cell
    : public i_cell_kernel
{
    friend class memory::pooled_creator<constant_cell>;
public:
    /*!
     * \brief
     * factory method
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static auto_type create( const variant& v ) {
        return auto_type( memory::pooled_creator<constant_cell>::create( v ) );
    }

    /*!
     * \brief
     * free the allocated memory
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void destroy() {
        memory::pooled_creator<constant_cell>::destroy( this );
    }

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~constant_cell() {}

    /*!
     * \brief
     * return the type of the current kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual kernel_type::type type() const {
        return kernel_type::constant_kernel;
    }

    /*!
     * \brief
     * empty stub.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void commit_kernel_change() {
    }

    /*!
     * \brief
     * never has a formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_formula() const {
        return m_shortened_constant_value;
    }

    /*!
     * \brief
     * never has precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_precedents() const {
        return false;
    }

    /*!
     * \brief
     * never has precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual referencetable_type precedents() const {
        static referencetable_type empty;
        return empty;
    }

    /*!
     * \brief
     * return the constant value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( interpreter_context&, bool ) const {
        return m_shortened_constant_value ? *m_shortened_constant_value : m_constant_value;
    }

    /*!
     * \brief
     * return the constant value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( calculation_context&, bool ) const {
        return m_shortened_constant_value ? *m_shortened_constant_value : m_constant_value;
    }

    /*!
     * \brief
     * return an empty string.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::string formula( const locale& ) const {
        return m_shortened_constant_value ? m_constant_value.string() : std::string();
    }

    /*!
     * \brief
     * does not contain volatile data.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual optional_variant_type fetch_cached_volatile( calculation_context& ) const {
        return optional_variant_type();
    }

    /*!
     * \brief
     * can not be dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_dirty() const {
        return false;
    }

    /*!
     * \brief
     * can not be volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_volatile() const {
        return false;
    }

    /*!
     * \brief
     * can not be volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual unsigned long volatile_count() const {
        return 0;
    }


    /*!
     * \brief
     * can not be volatile.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual unsigned long volatile_count_without_formula() const {
        return 0;
    }

    /*!
     * \brief
     * can never be an cell array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_array() const {
        return false;
    }

    /*!
     * \brief
     * copy the cells value to it's target.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual auto_type copy( cell&, const geometry::point&, bool, bool, const sheet_range& ) const {
        return auto_type( constant_cell::create( m_constant_value ) );
    }

    /*!
     * \brief
     * does not have array coverage.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual sheet_range array_coverage() const {
        return sheet_range( sheet_point( 0, 0 ) );
    }

    /*!
     * \brief
     * can never be dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_flag_dirty() {}

    /*!
     * \brief
     * can never be volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_raise_volatile_count() {}

    /*!
     * \brief
     * can never be volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_lower_volatile_count() {}

    /*!
     * \brief
     * constant cells can't be volatile
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual variant handle_cached_volatile( const optional_variant_type& v ) const {
        assert( !"constant cells can't be volatile" );
        return variant();
    }

private:
    optional_variant_type check_if_string_with_inverted_comma( const variant& v ) {
        if ( v.is_string() && !v.string().empty() && v.string()[0] == '\'' ) {
            return optional_variant_type( variant( v.string().substr( 1, v.string().size() - 1 ) ) );
        }
        return optional_variant_type();
    }
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    constant_cell( const variant& v )
        : m_constant_value( v )
        , m_shortened_constant_value( check_if_string_with_inverted_comma( v ) ) {}

private:
    const variant m_constant_value;
    const optional_variant_type m_shortened_constant_value;
};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//helper
inline static variant empty_or_na( bool fill_empty )
{
    return fill_empty ? variant() : variant( variant::error_n_a );
}

/*!
 * \brief
 * array formulas.
 *
 * this is the "master cell" containing the actual formula and calculation
 * logic. all other "slave cells" refer to this one.
 *
 * \see
 * cell::array_slave
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class cell::array_master
    : public cell::i_cell_kernel
{
    friend class memory::pooled_creator<array_master>;
public:
    /*!
     * \brief
     * factory method
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static auto_type create( cell& parent, const geometry::rectangle_type& dimensions, const shared_dependency_array_type& slave_cells ) {
        return auto_type( memory::pooled_creator<array_master>::create( parent, dimensions, slave_cells ) );
    }

    /*!
     * \brief
     * free the allocated memory
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void destroy() {
        memory::pooled_creator<array_master>::destroy( this );
    }

    /*!
     * \brief
     * return the type of the current kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual kernel_type::type type() const {
        return kernel_type::master_kernel;
    }

    /*!
     * \brief
     * a new kernel has been set, connect the kernels precedents to the
     * new containing dependency.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void commit_kernel_change() {
        m_inner_kernel->commit_kernel_change();
    }

    /*!
     * \brief
     * unregister the precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unload() {
        if ( m_inner_kernel->type() == kernel_type::formula_kernel ) {
            static_cast<formula_cell*>( m_inner_kernel.get() )->unload();
        }
    }

    /*!
     * \brief
     * returns bool in case the cell array contains a formula
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_formula() const {
        return m_inner_kernel->has_formula();
    }

    /*!
     * \brief
     * will return true in case the formula has precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_precedents() const {
        return m_inner_kernel->has_precedents();
    }

    /*!
     * \brief
     * return the list of precedents of the current formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual referencetable_type precedents() const {
        return m_inner_kernel->precedents();
    }

    /*!
     * \brief
     * return the correct value from a variant which might be an array
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline variant return_correct_array_value( const variant& v, bool fill_empty, bool permit_array_result = false ) {
        if ( !permit_array_result ) {
            if ( v.is_array() ) {
                if ( v.array().size() > 0 ) {
                    if ( v.array()[ 0 ].is_array() ) {
                        if ( v.array()[ 0 ].array().size() > 0 ) {
                            return v.array()[ 0 ].array()[ 0 ];
                        }
                    }
                    return v.array()[ 0 ];
                } else {
                    return empty_or_na( fill_empty );
                }
            }
        }
        return v;
    }

    /*!
     * \brief
     * return the calculated value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( interpreter_context& ic, bool permit_array_result ) const {
        return return_correct_array_value( m_inner_kernel->value( ic, permit_array_result ), fill_with_empty(), permit_array_result );
    }

    /*!
     * \brief
     * return the calculated value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( calculation_context& cc, bool permit_array_result ) const {
        return return_correct_array_value( m_inner_kernel->value( cc, permit_array_result ), fill_with_empty(), permit_array_result );
    }

    /*!
     * \brief
     * perform a delayed calculation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_calculation delayed_calculation( calculation_context& cc ) {
        return reinterpret_cast<formula_cell&>( ( *m_inner_kernel ) ).delayed_calculation( cc );
    }

    /*!
     * \brief
     * return the pretty printed formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::string formula( const locale& l ) const {
        return std::string( "{" ).append( m_inner_kernel->formula( l ) ).append( "}" );
    }

    /*!
     * \brief
     * return the cached volatile value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual optional_variant_type fetch_cached_volatile( calculation_context& cc ) const {
        return m_inner_kernel->fetch_cached_volatile( cc );
    }

    /*!
     * \brief
     * return true in case the formulas is marked as being dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_dirty() const {
        return m_inner_kernel->is_dirty();
    }

    /*!
     * \brief
     * return true in case the formula is marked as being volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_volatile() const {
        return m_inner_kernel->is_volatile();
    }

    /*!
     * \brief
     * return the formulas volatile count.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual unsigned long volatile_count() const {
        return m_inner_kernel->volatile_count();
    }

    /*!
     * \brief
     * return the formulas volatile count.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual unsigned long volatile_count_without_formula() const {
        return m_inner_kernel->volatile_count_without_formula();
    }


    /*!
     * \brief
     * will always return true.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_array() const {
        return true;
    }

    /*!
     * \brief
     * copy the cell array to another destination
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual auto_type copy( cell& parent, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range ) const {
        return m_inner_kernel->copy( parent, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range );
    }

    /*!
     * \brief
     * return the covered area of the cell array on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual sheet_range array_coverage() const {
        return m_dimensions.offset( m_parent.position() );
    }

    /*!
     * \brief
     * flag the formula as being dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_flag_dirty() {
        m_inner_kernel->internal_flag_dirty();
    }

    /*!
     * \brief
     * raise the formulas volatile count.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_raise_volatile_count() {
        m_inner_kernel->internal_raise_volatile_count();
    }

    /*!
     * \brief
     * lower the formulas volatile count.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_lower_volatile_count() {
        m_inner_kernel->internal_lower_volatile_count();
    }

    /*!
     * \brief
     * set the formula kernel.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void set_kernel( scoped_kernel_type kernel ) {
        m_inner_kernel = kernel;
    }

    /*!
     * \brief
     * must return empty values in array expansions instead of N/A.
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    void must_fill_with_empty() {
        m_fill_with_empty = true;
    }

    /*!
     * \brief
     * test if must return empty values in array expansions instead of N/A
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    bool fill_with_empty() const {
        return m_fill_with_empty;
    }

    /*!
     * \brief
     * return the correct part of the cached volatile value
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual variant handle_cached_volatile( const optional_variant_type& v ) const {
        assert( "empty volatile value passed" && v );
        return return_correct_array_value( *v, fill_with_empty() );
    }

    virtual dependency_set_type slave_dependents() const {
        dependency_set_type return_val;
        for ( shared_dependency_array_type::const_iterator it = m_slave_cells.begin(), end_it = m_slave_cells.end(); it != end_it; ++it ) {
            //foreach( const shared_dependency_type & sd, m_slave_cells ) {
            if ( ( *it )->has_dependents() ) {
                insert_from_temporary( return_val, static_cast<abstract_dependency*>( ( *it ).get() )->abstract_dependency::dependents() );
            }
        }
        //}
        return return_val;
    }

    virtual bool slaves_have_dependents() const {
        for ( shared_dependency_array_type::const_iterator it = m_slave_cells.begin(), end_it = m_slave_cells.end(); it != end_it; ++it ) {
            //foreach( const shared_dependency_type & sd, m_slave_cells ) {
            if ( ( *it )->has_dependents() ) {
                return true;
            }
        }
        return false;
    }

    const shared_dependency_array_type& slave_cells() const {
        return m_slave_cells;
    }

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    array_master( cell& parent, const geometry::rectangle_type& dimensions, const shared_dependency_array_type& slave_cells )
        : m_parent( parent )
        , m_dimensions( dimensions )
        , m_slave_cells( slave_cells )
        , m_inner_kernel( empty_cell::create() )
        , m_fill_with_empty( false )
    {}

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~array_master() {
    }

private:
    cell& m_parent;
    const geometry::rectangle_type m_dimensions;
    shared_dependency_array_type m_slave_cells;
    auto_type m_inner_kernel;
    bool m_fill_with_empty;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * slave cell.
 *
 * maintains a pointer to it's master and forwards all query's to
 * it. it is mostly a place holder.
 *
 * \see
 * cell::array_master
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class cell::array_slave
    : public cell::i_cell_kernel
{
    friend class memory::pooled_creator<array_slave>;
public:
    /*!
     * \brief
     * factory method
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static auto_type create( const shared_dependency_type& master, unsigned int index ) {
        return auto_type( memory::pooled_creator<array_slave>::create( master, index ) );
    }

    /*!
     * \brief
     * free the allocated memory
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void destroy() {
        memory::pooled_creator<array_slave>::destroy( this );
    }

    /*!
     * \brief
     * return the type of the current kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual kernel_type::type type() const {
        return kernel_type::slave_kernel;
    }

    /*!
     * \brief
     * only does something for formula containers.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void commit_kernel_change() {
    }

    /*!
     * \brief
     * will return true in case the master cell contains a formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_formula() const {
        return m_array_master->has_formula();
    }

    /*!
     * \brief
     * will return true in case the master cell contains precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_precedents() const {
        return m_array_master->has_precedents();
    }

    /*!
     * \brief
     * returns the precedents of the master cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual referencetable_type precedents() const {
        return m_array_master->precedents();
    }

    /*!
     * \brief
     * return the correct value from a variant which might be an array
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     * Radu Racariu <radu@yalos-solutions.com>
     */
    static inline variant return_correct_array_value( const variant& master_value, const sheet_point& position, const bool fill_empty ) {
        if ( master_value.is_array() ) {
            if( master_value.array().size() > 0 ) {
                const variant::sparse_array_type& array = master_value.array();
                bool is_structured_array = array[ 0 ].is_array();
                const unsigned int col_count = is_structured_array ? array[ 0 ].array().size() : master_value.column_width();
                const unsigned int row_count = is_structured_array ? array.size() : array.size() / col_count;

                if ( 1 == col_count ) {
                    if ( position.row() >= ( sheet_point::integer_type )( row_count ) ) {
                        return empty_or_na( fill_empty );
                    } else {
                        if ( fill_empty && position.column() >= 1 ) {
                            return variant( "" );
                        }
                        if ( is_structured_array ) {
                            return array[ position.row() ].array()[ 0 ];
                        } else {
                            return array[ position.row() ];
                        }
                    }
                } else if ( 1 == row_count ) {
                    if ( position.column() >= ( sheet_point::integer_type )( col_count ) ) {
                        return empty_or_na( fill_empty );
                    } else {
                        if ( fill_empty && position.row() >= 1 ) {
                            return variant( "" );
                        }

                        if ( is_structured_array ) {
                            return array[0].array()[ position.column() ];
                        } else {
                            return array[ position.column() ];
                        }
                    }
                } else {
                    //bi-dimensional array
                    if ( position.column() >= ( sheet_point::integer_type )( col_count )
                            || position.row() >= ( sheet_point::integer_type )( row_count ) ) {
                        return empty_or_na( fill_empty );
                    } else {
                        if ( is_structured_array ) {
                            if ( array[ position.row() ].is_array() && position.row() < ( sheet_point::integer_type )( array.size() ) ) {
                                if ( position.column() < ( sheet_point::integer_type )( array[ position.row() ].array().size() ) ) {
                                    return array[ position.row() ].array()[ position.column() ];
                                } else {
                                    return empty_or_na( fill_empty );
                                }
                            } else {
                                return empty_or_na( fill_empty );
                            }
                        } else {
                            return array[ position.row() * col_count + position.column() ];
                        }
                    }
                }
            } else {
                return empty_or_na( fill_empty );
            }
        }
        return master_value;
    }

    /*!
     * \brief
     * retrieves the value array from the master cell and returns the cells value by index.
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    variant value( const variant& master_value ) const {

        const sheet_range coverage = array_coverage();

        const sheet_point position = sheet_point( m_index / coverage.column_count(), m_index % coverage.column_count() );

        return return_correct_array_value( master_value, position, fill_with_empty() );

    }

    /*!
     * \brief
     * retrieves the value array from the master cell and returns the cells value by index.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( interpreter_context& ic, bool ) const {
        return  value( boost::shared_static_cast<cell>( m_array_master )->value( ic, true ) );

    }

    /*!
     * \brief
     * retrieves the value array from the master cell and returns the cells value by index.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( calculation_context& cc, bool ) const {
        return value( boost::shared_static_cast<cell>( m_array_master )->value( cc, true ) );
    }

    /*!
     * \brief
     * return the pretty printed formula from the master cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::string formula( const locale& l ) const {
        return m_array_master->formula( l );
    }

    /*!
     * \brief
     * retrieves the cached volatile value array from the master cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual optional_variant_type fetch_cached_volatile( calculation_context& cc ) const {
        return m_array_master->fetch_cached_volatile( cc );
    }

    /*!
     * \brief
     * returns true in case the master cell is flagged as being dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_dirty() const {
        return m_array_master->is_dirty();
    }

    /*!
     * \brief
     * returns true in case the master cell is flagged as being volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_volatile() const {
        return m_array_master->is_volatile();
    }

    /*!
     * \brief
     * will return the volatile count of the master cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual unsigned long volatile_count() const {
        return m_array_master->volatile_count();
    }

    /*!
     * \brief
     * will return the volatile count of the master cell.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual unsigned long volatile_count_without_formula() const {
        return m_array_master->volatile_count_without_formula();
    }

    /*!
     * \brief
     * will always return true as a member of a cell array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_array() const {
        return true;
    }

    /*!
     * \brief
     * copy the cell to a destination.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual auto_type copy( cell& parent, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range ) const {
        boost::shared_static_cast<cell>( m_array_master )->copy( parent, is_rewrite_to_clone_sheet, use_copy_move, source_range );
        return auto_type();
    }

    /*!
     * \brief
     * return the area that is covered on the sheet by this cell array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual sheet_range array_coverage() const {
        return m_array_master->array_coverage();
    }

    /*!
     * \brief
     * flag the master cell as being dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_flag_dirty() {
        //m_array_master->flag_dirty();
    }

    /*!
     * \brief
     * the master cell handles the volatile state.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_raise_volatile_count() {
        // the slave cell does itself has no precedents so
        // it should not be affected by volatile changes!
        assert( false );
    }

    /*!
     * \brief
     * the master cell handles the volatile state.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_lower_volatile_count() {
        // the slave cell does itself has no precedents so
        // it should not be affected by volatile changes!
        assert( false );
    }

    /*!
     * \brief
     * set the master cells kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void set_kernel( scoped_kernel_type kernel ) {
        boost::shared_static_cast<cell>( m_array_master )->set_kernel( kernel );
    }

    /*!
     * \brief
     * return the master cell for this cell array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const shared_dependency_type& master_cell() const {
        return m_array_master;
    }

    bool fill_with_empty() const {
        return boost::shared_static_cast<cell>( m_array_master )->fill_with_empty();
    }

    /*!
     * \brief
     * return the correct part of the cached volatile value
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual variant handle_cached_volatile( const optional_variant_type& v ) const {
        assert( "empty volatile value passed" && v );

        const sheet_range coverage = array_coverage();
        const sheet_point position = sheet_point( m_index / coverage.column_count(), m_index % coverage.column_count() );

        return return_correct_array_value( *v, position, fill_with_empty() );
    }

    void register_at_master( const shared_dependency_type& sd ) {
        static_cast<abstract_dependency*>( m_array_master.get() )->abstract_dependency::register_dependent( sd );
    }
    void unregister_at_master( const shared_dependency_type& sd ) {
        static_cast<abstract_dependency*>( m_array_master.get() )->abstract_dependency::unregister_dependent( sd );
    }

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    array_slave( const shared_dependency_type& master, unsigned int index )
        : m_array_master( master )
        , m_index( index ) {}

private:
    shared_dependency_type m_array_master;
    unsigned int m_index;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

cell::cell( weak_worksheet_type wws, const sheet_point& sp )
    : abstract_dependency()
    , m_kernel( empty_cell::create() )
    , m_worksheet( wws )
    , m_position( sp )
{}

cell::~cell()
{}

shared_dependency_type cell::create( const weak_worksheet_type& wws, const sheet_point& sp )
{
    return boost::make_shared<cell>( wws, sp );
}

i_dependency::dependency_type cell::type() const
{
    return i_dependency::cell_type;
}

bool cell::has_formula() const
{
    return ( *m_kernel.lock() )->has_formula();
}

void cell::value( session& s, const variant& v, const sheet_point& )
{
    if ( s.is_loading() ) {
        if ( is_array() && !s.selected().range().covers( array_coverage() ) ) {
            throw can_not_change_part_of_an_array_exception();
        }
    }

    // (fschaper) steps to be performed to provide for an thread safe set value operation.
    // (1) lock our dependency registry so new depending cells have to wait on us
    // (2) flag all registered dependencies as dirty. once the dirty flag is set
    //     that cell will have to wait for us to execute a calculation request
    // (4) set the new value to this cell
    // (5) release the lock from our cell

    bool is_formula = ( v.is_string() && v.string().length() > 1 && v.string()[0] == '=' );

    if ( is_formula ) {
        format_manager_type& fm = worksheet().lock()->format();
        format_manager_type::optional_value_type format = fm.get( position() );

        if ( format && "@" == *format ) {
            is_formula = false;
        }
    }
    if ( is_formula ) {

        // (fschaper) parse the formula. without having a live lock on the cell.
        weak_worksheet_type current_worksheet( *m_worksheet.lock() );
        ast_formula parsed_formula( s, current_worksheet, v.string() );

#ifdef _DEBUG
        friendly_name( v.string() );
#endif

        const bool executes_on_set        = !s.is_loading() && s.calculation_settings().auto_calculation() && parsed_formula.executes_on_set();
        const bool is_view_independent    = parsed_formula.is_view_independent();

        {
            bool transition_complete = false;
            do {
                {
                    // (fschaper) the lock on the kernel will keep other cells from changing their dirty
                    // state since the value of the kernel can not be accessed now.
                    locked_kernel_type::access kernel( m_kernel );

                    if ( !kernel.get() ) {
                        ( *kernel ) = empty_cell::create();
                    }

                    // (fschaper) since we have a lock on the kernel we flag all dependents dirty
                    // this way all dependents will access the same value once they
                    // update their cached value.
                    transition_complete = flag_dirty();
                    if ( ! transition_complete ) {
                        // if we could not gain a lock on all the cells we release our lock on
                        // the kernel and try the operation again.
                        break;
                    }

                    // set the new kernel that we created. will in turn set the appropriate volatile flag on
                    // all dependencies.
                    // will also connect all precedents.
                    set_kernel( kernel, formula_cell::create( *this, parsed_formula, ( *kernel )->precedents() ), is_array() && has_formula() );
                }
            } while ( !transition_complete );
        }

        if ( executes_on_set ) {
            calculation_context   tmp( s );
            calculate( tmp );
        }

        if ( is_view_independent ) {
            worksheet().lock()->register_view_independent( shared_from_this() );
        }
    } else {
        bool transition_complete = false;
        do {
            {
                locked_kernel_type::access kernel( m_kernel );

                if ( !kernel.get() ) {
                    ( *kernel ) = empty_cell::create();
                }

                // (fschaper) since we have a lock on the kernel we flag all dependents dirty
                // this way all dependents will access the same value once they
                // update their cached value.
                transition_complete = flag_dirty();
                if ( ! transition_complete ) {
                    // if we could not gain a lock on all the cells we release our lock on
                    // the kernel and try the operation again.
                    break;
                }

                if ( v.is_empty() ) {
#ifdef _DEBUG
                    friendly_name( "empty cell" );
#endif
                    set_kernel( kernel, empty_cell::create(), is_array() && has_formula() );
                } else {
#ifdef _DEBUG
                    friendly_name( v.as_string( s.locale() ) );
#endif
                    set_kernel( kernel, constant_cell::create( v ), is_array() && has_formula() );
                }
            }
        } while ( ! transition_complete );
    }
}

variant cell::value( calculation_context& cc ) const
{
    return value( cc, false );
}

variant cell::value( interpreter_context& ic ) const
{
    return value( ic, false );
}

variant cell::value( interpreter_context& ic, bool permit_array_result ) const
{
    if( ic.context().is_calculation_enabled() ) {
        if ( ( *m_kernel.lock() )->is_dirty() && !( ic.context().cache().cyclic_dependencies().check_if_cyclic( const_cast<cell*>( this )->shared_from_this() ) ) ) {
            const_cast<cell*>( this )->internal_calculate( ic );
        } else if ( ic.is_inside_named_formula() ) {
            optional_variant_type cached_volatile = ( *m_kernel.lock() )->fetch_cached_volatile( ic.context() );
            if ( !cached_volatile && ( *m_kernel.lock() )->is_volatile() ) {
                const_cast<cell*>( this )->internal_calculate( ic );
            }
        }
    }

    return ( *m_kernel.lock() )->value( ic, permit_array_result );
}

variant cell::value( calculation_context& cc, bool permit_array_result ) const
{
    optional_variant_type cached_volatile = ( *m_kernel.lock() )->fetch_cached_volatile( cc );
    if ( ( ( !cached_volatile && ( ( *m_kernel.lock() )->is_volatile() ) ) || ( *m_kernel.lock() )->is_dirty() ) && cc.is_calculation_enabled() ) {
        bool do_calculation = true;
        if ( NULL != cc.interpreter_context() ) {
            const ::cell* originator = dynamic_cast<cell*>( cc.interpreter_context()->initiator().get() );
            if ( NULL != originator ) {
                if ( originator->position() == this->position() ) {
                    do_calculation = false;
                }
                if ( do_calculation && originator->is_array() && originator->array_coverage().covers( this->position() ) ) {
                    do_calculation = false;
                }
            }
        }
        if ( do_calculation ) {
            const_cast<cell*>( this )->calculate( cc );
            cached_volatile = ( *m_kernel.lock() )->fetch_cached_volatile( cc );
        }
    }

    if ( cached_volatile ) {
        if ( is_array() ) {
            return ( *m_kernel.lock() )->handle_cached_volatile( cached_volatile );
        }
        return *cached_volatile;
    }

    return ( *m_kernel.lock() )->value( cc, permit_array_result );
}

std::string cell::formula( const locale& l ) const
{
    return ( *m_kernel.lock() )->formula( l );
}

struct formula_calculation_helper : non_instantiable {
    static inline void test_format( calculation_context& cc, cell& current_cell ) {
        format_manager_type& fm = current_cell.worksheet().lock()->format();
        format_manager_type::optional_value_type format = fm.get( current_cell.position() );

        if ( !format ) {
            std::string uf = cc.session().user_format().format( cc.return_type() );
            if ( !uf.empty() ) {
                current_cell.worksheet().lock()->format().set( current_cell.position(), uf );
            }
        }
        cc.return_type( return_type_format::unspecified );
    }
    template<class cell_type>
    static inline void help_cell_calculation( calculation_context& cc, cell::i_cell_kernel& kernel, cell& current_cell ) {
        {
            formula_calculation c = reinterpret_cast<cell_type&>( kernel ).delayed_calculation( cc );
            c();
            test_format( cc, current_cell );
        }
    }

    template<class cell_type>
    static inline void help_cell_calculation( interpreter_context& ic, cell::i_cell_kernel& kernel, cell& current_cell ) {
        calculation_context& cc = ic.context();
        cc.return_type( return_type_format::unspecified );
        if ( ic.initiator().get() == &current_cell ) {
            scoped_named_formula_initiator_reset resetter( ic );
            reinterpret_cast<abstract_calculation&>( ic.alias() )( ic );
        } else {
            formula_calculation c = reinterpret_cast<cell_type&>( kernel ).delayed_calculation( cc );
            scoped_named_formula_initiator_reset resetter( ic );
            reinterpret_cast<abstract_calculation&>( c )( ic );

        }
        //test_format( cc, current_cell );
    }
};

void cell::calculate( calculation_context& cc )
{
    if ( !cc.cache().iteration_count_still_valid( *this, cc.settings().maximum_iterations() ) ) {
        return;
    }
    locked_kernel_type::access kernel( m_kernel );
    if ( ( *kernel )->type() == i_cell_kernel::kernel_type::formula_kernel ) {
        formula_calculation_helper::help_cell_calculation<formula_cell>( cc, **kernel, *this );
    } else if ( is_master() ) {
        formula_calculation_helper::help_cell_calculation<array_master>( cc, **kernel, *this );
    } else if ( is_array() && !is_master() ) {
        reinterpret_cast<array_slave&>( **kernel ).master_cell()->calculate( cc );
        return;
    }
}

const sheet_point& cell::position() const
{
    return *m_position.lock();
}

weak_worksheet_type cell::worksheet() const
{
    return *m_worksheet.lock();
}

void cell::worksheet( const weak_worksheet_type& ws )
{
    *m_worksheet.lock() = ws;
}

void cell::internal_flag_dirty()
{
    locked_kernel_type::access kernel_access( m_kernel );
    internal_flag_dirty( kernel_access );
}

void cell::internal_flag_dirty( locked_kernel_type::access& kernel )
{
    ( *kernel )->internal_flag_dirty();
}

optional_variant_type cell::fetch_cached_volatile( calculation_context& cc ) const
{
    return ( *m_kernel.lock() )->fetch_cached_volatile( cc );
}

bool cell::is_dirty() const
{
    return ( *m_kernel.lock() )->is_dirty();
}

bool cell::is_volatile() const
{
    return ( *m_kernel.lock() )->is_volatile();
}

unsigned long cell::volatile_count() const
{
    return ( *m_kernel.lock() )->volatile_count();
}


unsigned long cell::volatile_count_without_formula() const
{
    return ( *m_kernel.lock() )->volatile_count_without_formula();
}

bool cell::is_array() const
{
    return ( *m_kernel.lock() )->is_array();
}

bool cell::is_master() const
{
    return ( ( *m_kernel.lock() )->type() == i_cell_kernel::kernel_type::master_kernel );
}


bool cell::is_slave() const
{
    return ( ( *m_kernel.lock() )->type() == i_cell_kernel::kernel_type::slave_kernel );
}


sheet_range cell::array_coverage() const
{
    return ( *m_kernel.lock() )->array_coverage();
}

void cell::unload()
{
    flag_dirty( true );
    // (fschaper) we want to explicitly erase the array master formula here
    // so all pointers to the slave cells get eradicated.
    locked_kernel_type::access kernel_access( m_kernel );

    if ( !kernel_access.get() ) {
        return;
    }

    if ( ( *kernel_access )->type() == i_cell_kernel::kernel_type::master_kernel ) {
        static_cast<array_master*>( ( *kernel_access ).get() )->unload();
    } else if ( ( *kernel_access )->type() == i_cell_kernel::kernel_type::formula_kernel ) {
        static_cast<formula_cell*>( ( *kernel_access ).get() )->unload();
    }
    //( *m_dependencies.lock() ).clear();
    set_kernel( kernel_access, empty_cell::create(), true );
#ifdef _DEBUG
    friendly_name( "unloaded" );
#endif
}

void cell::initialize_array( const sheet_range& position, shared_dependency_array_type& cells )
{
    shared_dependency_array_type::iterator it( cells.begin() );
    boost::shared_static_cast<cell>( *it++ )->set_kernel( array_master::create( *boost::shared_static_cast<cell>( cells[ 0 ] ), position.dimension(), shared_dependency_array_type( cells.begin() + 1, cells.end() ) ) );
    for ( unsigned int index = 1; it != cells.end(); ++it, ++index ) {
        boost::shared_static_cast<cell>( *it )->set_kernel( array_slave::create( cells[ 0 ], index ) );
    }
}

void cell::set_kernel( scoped_kernel_type new_kernel )
{
    locked_kernel_type::access kernel( m_kernel );
    set_kernel( kernel, new_kernel );
}

void cell::set_kernel( locked_kernel_type::access& kernel, scoped_kernel_type new_kernel, bool replace_array )
{
    // (fschaper) for cell arrays operations should be triggered by the range object from where a
    // new cell array will be created. the only way to change a cell array is to create a
    // new one in place.
    if ( ! replace_array ) {
        switch ( ( *kernel )->type() ) {
            case i_cell_kernel::kernel_type::master_kernel:
                static_cast<array_master*>( ( *kernel ).get() )->unload();
                static_cast<array_master*>( ( *kernel ).get() )->set_kernel( new_kernel );
                break;

            case i_cell_kernel::kernel_type::formula_kernel:
                // (fschaper) during unload the formula kernel will release all dependencies and
                // un flag all volatile dependencies. in case f.ex. a named formula want's to unregister
                // and un flag the kernel this will be possible since the kernel is still in place
                // while unloading so the lower volatile count method will still be available from
                // the outer cell interface for the same thread (this will only work with recursive
                // mutexes. we will have to use redirecting objects we pass along on the stack in case
                // we want to get rid of those in the future).
                static_cast<formula_cell*>( ( *kernel ).get() )->unload();
                ( *kernel ) = new_kernel;
                break;

            default:
                ( *kernel ) = new_kernel;
                break;
        }
    } else {
        switch ( ( *kernel )->type() ) {
            case i_cell_kernel::kernel_type::master_kernel:
                static_cast<array_master*>( ( *kernel ).get() )->unload();
                static_cast<array_master*>( ( *kernel ).get() )->set_kernel( new_kernel );
                break;
            case i_cell_kernel::kernel_type::formula_kernel:
                // see comment from a few lines above concerning the unload.
                static_cast<formula_cell*>( ( *kernel ).get() )->unload();
                ( *kernel ) = new_kernel;

                break;
            default:
                ( *kernel ) = new_kernel;
                break;
        }
    }

    // (fschaper) connect all precedents to this cell.
    // register dependent has to ensure that no deadlock occurs in case of cyclic references.
    // TODO currently we use a recursive mutex to prevents register_dependent from deadlocking
    // us on "internal_flag_dirty" or "raise_volatile_count". We will introduce a separate object that does the
    // checking on the precedents and set correct flag/volatile count in this method.
    ( *kernel )->commit_kernel_change();
    //this isn't nice, but we have to wait until the kernel is set then raise the volatile count!
    if (  ( *kernel )->is_volatile() ) {
        raise_volatile_count();
    }

    // new guts -> track value_change for this cell position
    //     shared_worksheet_type sw( ( *m_worksheet.lock() ).lock() );
    //     if ( sw ) {
    //         sw->value_change().track( *m_position.lock() );
    //     }
}

bool cell::has_precedents() const
{
    return ( *m_kernel.lock() )->has_precedents();
}

void cell::copy( cell& target_cell, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range )
{
    if ( ( *m_kernel.lock() )->type() == i_cell_kernel::kernel_type::slave_kernel ) {
        // delegate to master cell
        ( *m_kernel.lock() )->copy( target_cell, ( *m_position.lock() ).distance( target_cell.position() ), is_rewrite_to_clone_sheet, use_copy_move, source_range );
    } else {
        target_cell.set_kernel( ( *m_kernel.lock() )->copy( target_cell, ( *m_position.lock() ).distance( target_cell.position() ), is_rewrite_to_clone_sheet, use_copy_move, source_range ) );
#ifdef _DEBUG
        target_cell.friendly_name( friendly_name() );
#endif
    }
    shared_worksheet_type target_ws = target_cell.worksheet().lock();
    if ( target_ws ) {
        if( shared_worksheet_type ws = ( *m_worksheet.lock() ).lock() ) {
            if ( ws->is_view_independent( shared_from_this() ) ) {
                target_ws->register_view_independent( target_cell.shared_from_this() );
            }
        }
        shared_dependency_type s = target_cell.shared_from_this();
        target_ws->layout().register_new_cell( s, target_cell.position() );
    }
    target_cell.flag_dirty();
}

void cell::update_position( const sheet_point& p )
{
    // new position -> update old position
    // inform named formulas about the new position
    const geometry::point distance = ( *m_position.lock() ).distance( p );
    // set cell to new position and mark as dirty
    *m_position.lock() = p;
    bool need_to_connect_precedents_again = false;
    const referencetable_type& rt = precedents();
    for ( referencetable_type::const_iterator it = rt.begin(), end_it = rt.end(); it != end_it; ++it ) {
        if ( ( *it )->type() == i_dependency_reference::named_formula_reference && named_formula_reference_cast( *it ).has_relative_references() ) {
            if ( ! need_to_connect_precedents_again ) {
                reference_operation( shared_from_this(), rt, boost::bind( &i_dependency::unregister_dependent, _1, shared_from_this() ), true );
                need_to_connect_precedents_again = true;
            }
            named_formula_reference_cast( *it ).update_position( distance );
        }
    }
    if ( need_to_connect_precedents_again ) {
        trigger_commit_kernel_change();
    }

    //     const dependency_set_type& dt = dependents();
    //     for ( dependency_set_type::const_iterator it = dt.begin(), end_it = dt.end(); it != end_it; ++it ) {
    //         //foreach( const shared_dependency_type & d, dependents() ) {
    //         if ( ( *it )->type() == i_dependency::named_formula_wrapper_type ) {
    //             ( *it )->flag_moved();
    //         }
    //     }
    internal_flag_dirty();
}

referencetable_type cell::precedents() const
{
    return ( *m_kernel.lock() )->precedents();
}

variant cell::internal_value( interpreter_context& ic )
{
    return ( *m_kernel.lock() )->value( ic, false );
}

void cell::internal_calculate( interpreter_context& ic )
{
    locked_kernel_type::access kernel( m_kernel );
    if ( ( *kernel )->type() == i_cell_kernel::kernel_type::formula_kernel ) {
        formula_calculation_helper::help_cell_calculation<formula_cell>( ic, **kernel, *this );
    } else if ( is_master() ) {
        formula_calculation_helper::help_cell_calculation<array_master>( ic, **kernel, *this );
    } else if ( ( *kernel )->type() == i_cell_kernel::kernel_type::slave_kernel ) {
        shared_dependency_type master = reinterpret_cast<array_slave&>( **kernel ).master_cell();
        master->calculate( ic );
        return;
    }
}

void cell::internal_raise_volatile_count()
{
    ( *m_kernel.lock() )->internal_raise_volatile_count();
}

void cell::internal_lower_volatile_count()
{
    ( *m_kernel.lock() )->internal_lower_volatile_count();
}

void cell::must_fill_with_empty()
{
    locked_kernel_type::access kernel( m_kernel );

    if ( is_master() ) {
        reinterpret_cast<array_master&>( **kernel ).must_fill_with_empty();
    }
}

bool cell::fill_with_empty()
{
    locked_kernel_type::access kernel( m_kernel );

    if ( is_master() ) {
        return reinterpret_cast<array_master&>( **kernel ).fill_with_empty();
    } else {
        return false;
    }
}

void cell::trigger_commit_kernel_change()
{
    ( *m_kernel.lock() )->commit_kernel_change();
}

void cell::register_dependent( const shared_dependency_type& sd )
{
    if ( is_slave() ) {
        static_cast<array_slave*>( ( *m_kernel.lock() ).get() )->register_at_master( sd );
    } else {
        abstract_dependency::register_dependent( sd );
    }
}

void cell::unregister_dependent( const shared_dependency_type& sd )
{
    if ( is_slave() ) {
        static_cast<array_slave*>( ( *m_kernel.lock() ).get() )->unregister_at_master( sd );
    } else {
        abstract_dependency::unregister_dependent( sd );
    }
}

const shared_dependency_array_type& cell::get_slave_cells_if_array_master() const
{
    assert( "this function may only be called on a array master cell!" && is_master() );
    return static_cast<array_master*>( ( *m_kernel.lock() ).get() )->slave_cells();
}

void cell::release_cell_memory( bool purge )
{
    memory::pooled_creator<empty_cell>::release_memory( purge );
    memory::pooled_creator<formula_cell>::release_memory( purge );
    memory::pooled_creator<constant_cell>::release_memory( purge );
    memory::pooled_creator<array_master>::release_memory( purge );
    memory::pooled_creator<array_slave>::release_memory( purge );
}

#ifdef _DEBUG
std::string cell::get_debug_identifier() const
{
    return "[cell " + a1conversion::to_a1::from_point( position() ) + "]";
}
#endif // _DEBUG
