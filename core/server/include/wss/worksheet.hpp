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

#include <wss/define.hpp>
#include <wss/type.hpp>
#include <wss/identifiable_object.hpp>
#include <wss/used_range.hpp>
#include <wss/copy_format_from.hpp>
#include <wss/shift_direction.hpp>
#include <wss/style_manager.hpp>
#include <wss/format_manager.hpp>
#include <wss/attribute_manager.hpp>
#include <wss/locked_cell_manager.hpp>

#if defined( WIN32 )
# pragma warning ( disable : 4251 4275 ) // disable "needs to have dll-interface" warning
#endif // WIN32

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <string>
# include <boost/enable_shared_from_this.hpp>
# include <boost/noncopyable.hpp>
# include <boost/scoped_ptr.hpp>
# include <boost/uuid/uuid.hpp>
# include <boost/uuid/nil_generator.hpp>
# include <boost/make_shared.hpp>
#endif

class range;
class cell_manager;
class layout_coord;
class variable_map;
class border_manager;
class formula_kernel;
class selection_state;
class session_sheet_map;
class function_parameter;
class interpreter_variant;
class merged_cell_manager;
class sheet_layout_manager;
class unmerge_cells_command;
class i_named_formula_manager;
class get_server_query_command;
class worksheet_element_storage;
class get_cell_lock_list_command;
class conditional_format_manager;

namespace spreadsheetml
{
    class CT_extended_data;
}

namespace policy
{
    /*!
     * \brief
     * stub for object creation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class, class, class>
    struct has_parent;
}

/*!
 * \brief
 * Worksheet representation.
 *
 * \see
 * server | application | workbook
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE worksheet
    : boost::noncopyable
    , public boost::enable_shared_from_this<worksheet>
    , public identifiable_object
{
    friend class cell;
    friend class range;
    friend class range_lock;
    friend class cell_manager;
    friend class formula_kernel;
    template<bool t>
    friend class opcode_rewriterT;
    friend class range_reference;
    friend class opcode_generator;
    friend class dependency_manager;
    friend class formula_calculation;
    friend class merge_cells_command;
    friend class named_formula_kernel;
    friend class unmerge_cells_command;
    friend class get_server_query_command;
    friend class named_formula_calculation;
    friend class get_cell_lock_list_command;
    friend class layout_coord;
    template< class T, class A1, class A2, class A3 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const& );
    friend interpreter_variant function_offset( function_parameter& parameters );
public:
    /*!
     * \brief
     * will be called by every worksheet before upon destruction.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static boost::signal<void( const worksheet& )> on_global_before_delete;

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~worksheet();

    /*!
     * \brief
     * retrieves the associated workbook object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_workbook_type parent() const;

    /*!
     * \brief
     * retreive a weak pointer of the object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    weak_worksheet_type weak_pointer() const;

    /*!
     * \brief
     * returns a range covering the passed sheet_range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::range range( const sheet_range& r );

    /*!
     * \brief
     * returns a range covering the passed sheet_range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const ::range range( const sheet_range& r ) const;

    /*!
     * \brief
     * retrieve the covered range on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    optional_sheet_range_type used_range( int query = ::used_range::all, bool include_fulls = true   ) const;

    /*!
     * \brief
     * select the worksheet as the currently active sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void select( selection_state& s );

    /*!
     * \brief
     * insert 'row_count' rows starting from 'row'.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void insert_row( session& s, unsigned int row, unsigned int row_count, const copy_format_from::type copy_from = copy_format_from::left_or_above  );

    /*!
     * \brief
     * insert 'column_count' columns starting from column.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void insert_column( session& s, unsigned int column, unsigned int column_count, const copy_format_from::type copy_from = copy_format_from::left_or_above  );

    /*!
     * \brief
     * delete 'row_count' rows starting from 'row'
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void delete_row( session& s, unsigned int row, unsigned int row_count );

    /*!
     * \brief
     * delete 'column_count' columns starting from column.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void delete_column( session& s, unsigned int column, unsigned int column_count );

    /*!
     * \brief
     * insert cells at the sheet_range rect
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void insert_cells(  session& s, const sheet_range& rect, const insert_shift_direction::type shift_direction = insert_shift_direction::horizontally, copy_format_from::type format_from = copy_format_from::left_or_above );

    /*!
     * \brief
     * delete cells
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void delete_cells( session& s, const sheet_range& rect, const insert_shift_direction::type shift_direction = insert_shift_direction::horizontally );

    /*!
     * \brief
     * TODO
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    shared_worksheet_type copy( session& s, shared_workbook_type target_wb, const uuid_type& next_ws_uuid = boost::uuids::nil_uuid() ) const;

    /*!
     * \brief
     * TODO
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    const bool hidden();

    /*!
     * \brief
     * retrieve the list of merged ranges.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    rectangle_list_type merged_range_list() const;

    // region Persistence

    /*!
     * \brief
     * deserialize from xml persistence.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void deserialize( session& s, const spreadsheetml::CT_extended_data& data );

    /*!
     * \brief
     * serialize to xml persistence.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void serialize( session& s, spreadsheetml::CT_extended_data& data ) const;

    // endregion Persistence

    // region Managers
    /*!
     * \brief
     * TODO
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    worksheet_element_storage& elements();

    /*!
     * \brief
     * TODO
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    const worksheet_element_storage& elements() const;

    /*!
     * \brief
     * TODO
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    conditional_format_manager& conditional_formats();

    /*!
     * \brief
     * TODO
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    const conditional_format_manager& conditional_formats() const;

    /*!
     * \brief
     * TODO
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    border_manager& borders();

    /*!
     * \brief
     * TODO
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    const border_manager& borders() const;

    /*!
    * \brief
    * retrieve the format manager.
    *
    * \author
    * Vali Nitu <vali@yalos-solutions.com>
    */
    format_manager_type& format();

    /*!
    * \brief
    * retrieve the format manager.
    *
    * \author
    * Vali Nitu <vali@yalos-solutions.com>
    */
    const format_manager_type& format() const;

    /*!
     * \brief
     * retrieve the sheet-layout manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sheet_layout_manager& layout();
    const sheet_layout_manager& layout() const;

    /*!
     * \brief
     * returns a vector containing all the array formula rectangles
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     * Radu Racariu <radu@yalos-solutions.com>
     * Florian Schaper <florian.schaper@jedox.com>
     */
    rectangle_list_type array_region_list();

    /*!
     * \brief
     * retrieve the style manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    style_manager_type& style();

    void register_view_independent( const shared_dependency_type& dep );
    bool is_view_independent( const shared_dependency_type& dep );
    void compute_view_independent(  session& s );

    /*!
     * \brief
     * get a list of existing cells
     *
     * the list exists of unsigned int, if you have an
     * std::vector<sheet_point::unsigned_integer_type>::const_iterator (it) use
     * sheet_point::from_key(*it) to get the position.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    typedef std::vector<sheet_point> existing_cell_list_type;
    existing_cell_list_type existing_cells() const;

    void name( const utf8_ci_string& new_name );

    //not sure why this is needed
    inline const utf8_ci_string& name() const {
        return identifiable_object::name();
    }
private:
    /*!
     * \brief
     * retrieve the cell manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    cell_manager& cells();

    /*!
     * \brief
     * retrieve the cell manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const cell_manager& cells() const;

    /*!
     * \brief
     * retrieve the style manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const style_manager_type& style() const;

    /*!
     * \brief
     * retrieve the attribute manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    attribute_manager& attribute();

    /*!
     * \brief
     * retrieve the attribute manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const attribute_manager& attribute() const;

    /*!
     * \brief
     * retrieve the worksheet variable manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variable_map& variable();

    /*!
     * \brief
    * retrieve the merged cell manager.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    merged_cell_manager& merge();

    /*!
     * \brief
     * retrieve the merged cell manager.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    const merged_cell_manager& merge() const;

    /*!
     * \brief
     * locked cell manager
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_cell_manager_type& lock();

    /*!
     * \brief
     * locked cell manager
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const locked_cell_manager_type& lock() const;

    // endregion Managers

private:
    template<class, class, class>
    friend struct policy::has_parent;
    /*!
     * \brief
     * factory method.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_worksheet_type create( const shared_workbook_type& wb, const utf8_ci_string& name, const bool hidden = false );

    FRIEND_CLASS session_sheet_map;
    static shared_worksheet_type create_session_sheet( session& s, const shared_worksheet_type& source_ws );

    friend class workbook;
    template<class, class, template<class, class, class> class, class >
    friend class object_container;

    /*!
     * \brief
     * unload the worksheet from memory.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unload();

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    worksheet( const shared_workbook_type& wb, const utf8_ci_string& name, const bool hidden = false );

    /*!
     * \brief
     * TODO
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void copy_everything_into_target_sheet( session& s, const shared_worksheet_type& target_sheet ) const;
    void fill_session_sheet( session& s, const shared_worksheet_type& session_sheet ) const;

private:
    struct worksheet_impl;
    boost::scoped_ptr<worksheet_impl> m_impl;
    shared_workbook_type m_parent;
    weak_worksheet_type m_weak_worksheet;
};
