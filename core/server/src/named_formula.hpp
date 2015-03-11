/**
 *  \file
 *  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 *
 *  \author
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include "wss/type.hpp"
#include "wss/i_dependency.hpp"
#include "wss/identifiable_object.hpp"
#include "wss/named_formula_scope.hpp"
#include "abstract_dependency.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/thread/recursive_mutex.hpp>
#   include <boost/enable_shared_from_this.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

class sheet_point;
class named_formula;
typedef boost::shared_ptr<named_formula> shared_named_formula_type;

struct positioned_op_codes;

/*!
 * \brief
 * named formula class
 *
 * \details
 * TODO
 *
 * \see
 * i_named_formula_manager | named_formula_manager | basic_dependency | identifiable_object
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class named_formula
    : public identifiable_object
    , public abstract_dependency
    , boost::noncopyable
{
    typedef std::map<weak_dependency_type, shared_dependency_type> dependency_wrapper_map_type;
    //use a recursive mutex here for now, this is because raise_volatile value will call get_proxy
    typedef locked_object < dependency_wrapper_map_type/*, boost::recursive_mutex*/ > locked_dependency_wrapper_map_type;

    typedef locked_object < shared_named_formula_kernel_type/*, boost::recursive_mutex*/ > locked_kernel_type;
    typedef locked_object<weak_workbook_type> locked_workbool_type;
    typedef locked_object<weak_worksheet_type> locked_worksheet_type;
    typedef locked_object<weak_workbook_type> locked_workbook_type;
    typedef locked_object<sheet_point> locked_position_type;
    typedef locked_object<bool> locked_bool_type;
    typedef locked_object<std::string> locked_string_type;
    typedef locked_object<variant> locked_variant_type;

    typedef boost::uint_fast32_t move_count_type;
    typedef locked_object<move_count_type> locked_uint_type;

    template< class T, class A1, class A2, class A3, class A4 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const& );
    friend class named_formula_kernel;
    friend class named_formula_dependency_wrapper;
    template<bool t>
    friend class opcode_interpreterT;
#ifdef _DEBUG
    friend class debug_logging_helper;
    struct named_formula_debug_helper;
#endif // _DEBUG
public:
    virtual ~named_formula();

    static shared_named_formula_type create( const bool scope_is_ws, const shared_worksheet_type& ws, const std::string& name, session& s, const variant& formula, const sheet_point& position = sheet_point( 0, 0 ), const bool hidden = false, const bool is_inside_ff = false );

    static shared_named_formula_type create( const shared_dependency_type& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const shared_worksheet_type& ws = shared_worksheet_type() );

    static shared_named_formula_type create( const named_formula& other, bool is_rewrite_to_clone_sheet, const shared_worksheet_type& ws );

    void register_reference( const shared_dependency_type& dependent );

    void unregister_reference( const shared_dependency_type& dependent );

    bool has_formula() const;

    bool has_precedents() const;

    virtual variant value( calculation_context& cc, const sheet_point& position ) const;

    virtual void value( session& s, const variant& v, const sheet_point& position );

    void value( session& s, const variant& v, const sheet_point& position, const bool clear_cache );

    virtual std::string formula( const locale& l, const sheet_point& position ) const;
    std::string formula_without_sheet_references( const locale& l, const sheet_point& position /* = sheet_point */ ) const;

    //functions that are present to support the interface but should never be called
    virtual void calculate( calculation_context& );
    virtual std::string formula( const locale& ) const;
    virtual void internal_calculate( interpreter_context& );
    virtual variant internal_value( interpreter_context& );
    virtual optional_variant_type fetch_cached_volatile( calculation_context& ) const;
    virtual referencetable_type precedents() const;
    virtual referencetable_type precedents( const shared_dependency_type& sd ) const;

    weak_worksheet_type worksheet() const;
    virtual weak_workbook_type workbook() const;
    virtual variant value( calculation_context& ) const;

    virtual bool is_volatile() const;

    virtual unsigned long volatile_count() const;

    /*!
    * \brief
    * returns the current volatile count (excluding self)
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    unsigned long volatile_count_without_formula() const;

    virtual bool is_array() const;

    virtual sheet_range array_coverage() const;

    virtual bool is_dirty() const;

    virtual void internal_raise_volatile_count();

    virtual void internal_lower_volatile_count();

    virtual const sheet_point& position() const;

    void unload();

    void comment( const std::string& comment );

    const std::string& comment() const;

    utf8_ci_string scope_as_string() const;

    const named_formula_scope::type scope() const;

    bool moved( session& s ) const;

    optional_sheet_range_type coverage( const shared_dependency_type& d ) const;

    bool is_relative() const;

    virtual void internal_flag_dirty();

    virtual void flag_moved();

    const shared_dependency_type& get_proxy( const shared_dependency_type& d ) const;

    virtual dependency_type type() const;

    void update_position( const shared_dependency_type& d,  const geometry::point& distance  );

    bool hidden();

    void set_special_caching() {
        m_special_caching = true;
    }

    bool put_in_general_cache() const {
        return !m_special_caching;
    }

    void adjust_legacy_references( const sheet_point& position );

    inline const bool is_inside_ff() const {
        return m_is_inside_ff;
    }

    void trigger_register_dependent();

    void raise_volatile_on_wrappers() const;
    void lower_volatile_on_wrappers() const;
    void register_wrappers_at_cell( const shared_dependency_type& new_cell ) const;
    void unregister_wrappers_at_cell( const shared_dependency_type& new_cell ) const;

protected:
    variant internal_value( interpreter_context& ic, const sheet_point& position );

    void internal_calculate( interpreter_context& ic, const sheet_point& position ) {}

private:
    named_formula( const bool scope_is_ws, const std::string& name, const shared_worksheet_type& ws, const bool is_inside_ff );

    void init_formula( session& s, const std::string& f,  const sheet_point& position = sheet_point( 0, 0 )  );

    inline bool adjust_position( locked_kernel_type::access& kernel, const sheet_point& position );

    inline void internal_register_reference( locked_kernel_type::access& kernel, locked_dependency_wrapper_map_type::access& map, const shared_dependency_type& dependent );
    inline void internal_register_reference( locked_kernel_type::access& kernel, locked_dependency_wrapper_map_type::access& map, const shared_dependency_type& dependent, const shared_dependency_type& dep_wrapper );
    inline void internal_unregister_reference( locked_kernel_type::access& kernel, const shared_dependency_type& dependent, const shared_dependency_type& dep_wrapper );
    inline void clean_up_dependency_wrapper_map( locked_dependency_wrapper_map_type::access& map );
    inline const std::list<shared_dependency_type> internal_access_wrappers() const;
    inline void check_use_count_of_wrappers( const named_formula::dependency_wrapper_map_type& m );
    const positioned_op_codes& get_opcode()const;
    inline void add_to_dependencies_that_use_the_nf( const shared_dependency_type& sd ) const;

#ifdef _DEBUG
    std::string get_debug_identifier() const;
public:
    static size_t m_counter;
#endif // _DEBUG
private:

    locked_kernel_type m_kernel;
    locked_position_type m_position;
    locked_worksheet_type m_worksheet;
    locked_workbook_type m_workbook;
    locked_string_type m_comment;
    const bool m_ws_scope;
    mutable bool m_got_moved;
    locked_dependency_wrapper_map_type m_dependency_wrappers;
    bool m_hidden;
    bool m_special_caching;
    const bool m_is_inside_ff;
    typedef locked_object<weak_dependency_set_type> locked_weak_dependency_set_type;
    locked_weak_dependency_set_type m_dependencies_that_use_the_nf;
#ifdef _DEBUG
    bool m_unload_called;
#endif // _DEBUG
};
