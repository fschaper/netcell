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

#pragma once

#include "wss/type.hpp"
#include "wss/variant.hpp"
#include "wss/sheet_point.hpp"
#include "wss/destroying_auto_pointer.hpp"
#include "wss/locked_object.hpp"
#include "abstract_dependency.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/thread/recursive_mutex.hpp>
#   include <boost/enable_shared_from_this.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

class formula;

/*!
 * \brief
 * cell representation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class cell
    : public abstract_dependency
    , boost::noncopyable
{
    class i_cell_kernel;
    class empty_cell;
    class formula_cell;
    class constant_cell;
    class array_master;
    class array_slave;

    template< class T, class A1, class A2 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const& a1, A2 const& a2 );

    friend class release_pooled_memory;

#ifdef _DEBUG
    friend class debug_logging_helper;
#endif // _DEBUG

    typedef destroying_auto_pointer<i_cell_kernel> scoped_kernel_type;
public:
    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~cell();

    /*!
     * \brief
     * factory method. creates a new cell object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_dependency_type create( const weak_worksheet_type& wws, const sheet_point& sp );

    /*!
     * \brief
     * returns true in case the cell has precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_precedents() const;

    /*!
     * \brief
     * returns the precedents for the current cell
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual referencetable_type precedents() const;

    /*!
     * \brief
     * returns true in case the cell contains a formula
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_formula() const;

    /*!
     * \brief
     * returns a cached volatile value if exists.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual optional_variant_type fetch_cached_volatile( calculation_context& cc ) const;

    /*!
     * \brief
     * returns true in case the cell is marked as dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_dirty() const;

    /*!
     * \brief
     * return true in case the cell is marked as being volatile
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_volatile() const;

    /*!
     * \brief
     * returns true in case the cell is part of a cell array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_array() const;

    /*!
     * \brief
     * returns true in case the cell is the master of a cell array
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_master() const;

    /*!
     * \brief
     * returns true in case the cell is a slave of a cell array
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    bool is_slave() const;

    /*!
     * \brief
     * returns the area covered on the sheet by the cell array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual sheet_range array_coverage() const;

    /*!
     * \brief
     * returns the dependency type (will always be cell_type).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual dependency_type type() const;

    /*!
     * \brief
     * position of the cell on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual const sheet_point& position() const;

    /*!
     * \brief
     * the pretty printed formula of the cell in the users locale.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::string formula( const locale& l ) const;

    /*!
     * \brief
     * sets the value for the cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void value( session& s, const variant& v, const sheet_point&  );

    /*!
     * \brief
     * retreives the value of the cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( interpreter_context& ic ) const;

    /*!
     * \brief
     * retreives the value of the cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( calculation_context& cc ) const;

    /*!
     * \brief
     * calculates the cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void calculate( calculation_context& cc );

    /*!
     * \brief
     * unload the cell. the cell will disconnect from all it's precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unload();

    /*!
     * \brief
     * the current worksheet of the cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    weak_worksheet_type worksheet() const;

    /*!
     * \brief
     * sets the worksheet of the cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void worksheet( const weak_worksheet_type& ws );

    /*!
     * \brief
     * returns the volatile count of the current cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual unsigned long volatile_count() const;

    /*!
    * \brief
    * returns the current volatile count (excluding self)
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    virtual unsigned long volatile_count_without_formula() const;

    /*!
     * \brief
     * initialized a cell array. created the master cell and associates the slaves cells with it.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static void initialize_array( const sheet_range& position, shared_dependency_array_type& cells );

    void copy( cell& target_cell, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range );

    /*!
     * \brief
     * used by the cell_manager::move operation to update the cell with it's new
     * position on the worksheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void update_position( const sheet_point& p );

    /*!
     * \brief
     * flags the cell as dirty
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_flag_dirty();

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
    virtual void internal_raise_volatile_count();

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
    virtual void internal_lower_volatile_count();

    /*!
     * \brief
     * needed to support changing the precedents of a formula from the outside
     * (i.e. if a named formula used in this cell changes its formula)
     *
     * \note use with care!
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void trigger_commit_kernel_change();

    virtual void register_dependent( const shared_dependency_type& sd );
    virtual void unregister_dependent( const shared_dependency_type& sd );
protected:
    /*!
     * \brief
     * will return the cells value as an array.
     *
     * opposed to the regular value method this one will not
     * condense the array to a single result.
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    variant value( calculation_context& cc, bool permit_array_result ) const;

    /*!
     * \brief
     * returns the cells value (optionally as an array)
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant value( interpreter_context& ic, bool permit_array_result ) const;

    /*!
     * \brief
     * returns the value of the cell (called internally)
     *
     * \see
     * abstract_dependency::internal_value
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant internal_value( interpreter_context& );

    /*!
     * \brief
     * calculates the cell (called internally)
     *
     * \see
     * abstract_dependency::internal_calculate
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_calculate( interpreter_context& );

    /*!
     * \brief
     * must return empty values in array expansions instead of N/A.
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    virtual void must_fill_with_empty();

    /*!
     * \brief
     * delegate to array_master::fill_with_empty.
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    bool fill_with_empty();
public:
    const shared_dependency_array_type& get_slave_cells_if_array_master() const;

private:
    typedef locked_object < scoped_kernel_type/*, boost::recursive_mutex*/ > locked_kernel_type;
    typedef locked_object<weak_worksheet_type> locked_worksheet_type;
    typedef locked_object<sheet_point> locked_position_type;

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    cell( weak_worksheet_type wws, const sheet_point& sp );

    /*!
     * \brief
     * set the cells kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void set_kernel( scoped_kernel_type kernel );

    /*!
     * \brief
     * flag the cell as being dirty
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void internal_flag_dirty( locked_kernel_type::access& kernel );

    /*!
     * \brief
     * set the cells kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void set_kernel( locked_kernel_type::access& kernel, scoped_kernel_type new_kernel, bool replace_array = false );

    /*!
     * \brief
     * return the pooled memory to the system
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static void release_cell_memory( bool purge = false );

#ifdef _DEBUG
    std::string get_debug_identifier() const;
#endif // _DEBUG

    locked_kernel_type m_kernel;
    locked_worksheet_type m_worksheet;
    locked_position_type m_position;
};

