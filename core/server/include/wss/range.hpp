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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/type.hpp>
#include <wss/session.hpp>
#include <wss/variant.hpp>
#include <wss/style_set.hpp>
#include <wss/sheet_range.hpp>
#include <wss/content_type.hpp>
#include <wss/attribute_set.hpp>
#include <wss/style_manager.hpp>
#include <wss/format_manager.hpp>
#include <wss/shift_direction.hpp>
#include <wss/dependency_info.hpp>
#include <wss/copy_format_from.hpp>
#include <wss/attribute_manager.hpp>
#include <wss/locked_cell_manager.hpp>
#include <wss/sheet_layout_trait.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <cstdlib> // std::size_t
#   include <set>
#endif

class worksheet;
class calculation_context;
class cell_manager;

/*!
 * \brief
 * range class.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE range
{
    friend class worksheet;
    friend class cell;
public:
    /*!
     * \brief
     * a set of ranges type definition.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    typedef std::set<range> range_set_type;

    /*!
     * \brief
     * copy-construct a range from another.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range( const range& other );

    /*!
     * \brief
     * give range in A1 notation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    std::string address() const;

    /*!
     * \brief
     * return the corresponding worksheet that this
     * range was created from.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    weak_worksheet_type worksheet() const;

    /*!
     * \brief
     * coverage of the range on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline const sheet_range& coverage() const {
        return m_referenced_rect;
    }

    /*!
     * \brief
     * return a range with
     * {row, range_column_upper_left}x(row, range_column_lower_right}
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range row( unsigned int row ) const;

    /*!
     * \brief
     * return a range with
     * {range_upper_left_row, column }x(range_lower_right_row, column}
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range column( unsigned int column ) const;

    /*!
     * \brief
     * return the number of covered cells on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    std::size_t count() const;

    /*!
     * \brief
     * calculate the distance between two ranges on a sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    geometry::point distance( const range& other ) const;

    /*!
     * \brief
     * set all cells that are covered by the range to the passed value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void value( session& s, const variant& v, const bool trim_hyperlink = false );

    /*!
     * \brief
     * retrieve the value of all cells covered by the range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant value( session& s ) const;

    /*!
     * \brief
     * retrieve the value of all cells covered by the range
     * the calculation_context will ensure that volatile cells
     * etc. will be of the same value during calculation runs.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant value( calculation_context& cc );

    /*!
     * \brief
     * retrieve the formula of all cells covered by the range.
     *
     * if supress_value is left to FALSE will return values for
     * cells that do not contain a formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant formula( session& s, bool supress_value = false ) const;

    /*!
     * \brief
     * retrieve the formulas of all cells covered by the range
     * the calculation_context will ensure that volatile cells
     * etc. will be of the same value during calculation runs.
     *
     * if supress_value is left to FALSE will return values for
     * cells that do not contain a formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant formula( calculation_context& cc, bool supress_value = false ) const;

    /*!
     * \brief
     * will return a boolean value for each cell indicating
     * if it contains a formula or not.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant has_formula() const;

    /*!
     * \brief
     * create an array formula that covers the range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void array_formula( session& s, const variant& v );

    /*!
     * \brief
     * unset array formula
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void unset_array_formula( session& s );

    /*!
     * \brief
     * set the style for the covered range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void style( session& s, const style_set_type& style_set, const bool dont_invalidate = false );

    /*!
     * \brief
     * retrieve the styles for the covered range.
     * borders and style set by conditional formatting
     * will be returned too
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    css_style_vec_type style( session& s, const bool saving = false, const cf::cf_vec_type& cf_vec = cf::cf_vec_type(), const bool use_cf_vec = false ) const;

    /*!
    * \brief
    * retrieve the styles for the covered range
    * (no borders and conditional formats)
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    // css_style_vec_type style() const;

    /*!
    * \brief
    * retrieve the styles for the covered range
    * (no conditional formats)
    *
    * \author
    * Radu Ialovoi <ialovoi@yalos-solutions.com>
    */
    css_style_vec_type style( const bool skip_empties = true ) const;

    /*!
    * \brief
    * retrieve style information for undo operations
    * (no borders and conditional formats)
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    style_manager_type::undo_list_type style_undo_list() const;

    /*!
    * \brief
    * apply style information for undo operations
    * (no borders and conditional formats)
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void style_undo_list( const style_manager_type::undo_list_type& l );

    /*!
    * \brief
    * retrieve format information for undo operations
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    format_manager_type::undo_list_type format_undo_list() const;

    /*!
    * \brief
    * apply format information for undo operations
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    void format_undo_list( const format_manager_type::undo_list_type& l );

    /*!
     * \brief
     * set the attribute for the covered range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void attribute( session& s, const attribute_set_type& attribute_set );

    /*!
     * \brief
     * retrieve the attributes for the covered range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant attribute() const;

    /*!
     * \brief
     * retrieve one single attribute by key.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    variant attribute( utf8_ci_string& key ) const;

    /*!
    * \brief
    * retrieve attribute information for undo operations
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    attribute_manager::undo_list_type attribute_undo_list() const;

    /*!
    * \brief
    * apply attribute information for undo operations
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void attribute_undo_list( const attribute_manager::undo_list_type& l );

    /*!
     * \brief
     * get unlock information for cells in this area
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    unlocked_cells_vec_type un_locked( session& s, const cf::cf_vec_type& cf_vec = cf::cf_vec_type(), const bool use_cf_vec = false ) const;

    /*!
     * \brief
     * set un_locked state of cells in this area
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void un_locked( session& s, const bool unlocked );

    /*!
    * \brief
    * retrieve lock information for undo operations
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    locked_cell_manager_type::undo_list_type un_locked_undo_list_type() const;

    /*!
    * \brief
    * apply lock information for undo operations
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void un_locked_undo_list_type( const locked_cell_manager_type::undo_list_type& l );

    /*!
     * \brief
     * set format
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void format( session& s, const std::string& format_string, const bool dont_invalidate = false );

    /*!
     * \brief
     * get format
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    variant format( session& s, const cf::cf_vec_type& cf_vec = cf::cf_vec_type(), const bool use_cf_vec = false ) const;

    /*!
     * \brief
     * get formated value(s)
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    variant formatted_value( session& s, const cf::cf_vec_type& cf_vec = cf::cf_vec_type(), const bool use_cf_vec = false ) const;

    /*!
     * \brief
     * returns the number of volatile dependencies.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant volatile_count() const;

    /*!
     * \brief
     * get a set of ranges with all the precedents for
     * the current selected cells.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range_set_type precedents();

    /*!
     * \brief
     * get a set of ranges with all the dependents for
     * the current selected cells.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range_set_type dependents();

    /*!
     * \brief
     * get brief info about dependents of
     * the current selected cells.
     *
     * \author
     * radu ialovoi <ialovoi@yalos-solutions.com>
     */
    template<bool adjust_position_for_ui>
    const variant dependents( session& s );

    /*!
     * \brief
     * clear content of the cells.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void clear( session& s, const int type_of_content = content_type::all, bool is_delete_column_row_operation = false );

    /*!
     * \brief
     * copy the current range upon the target range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void copy( session& s, range& target, const bool whole_column_or_row = false, const insert_shift_direction::type shift_direction = insert_shift_direction::automatic, const int type_of_content = content_type::all_plus_cf ) const;

    /*!
     * \brief
     * copy-move the current range upon the target range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void copy_move( session& s, range& target, const insert_shift_direction::type shift_direction = insert_shift_direction::automatic, const int type_of_content = content_type::all_plus_cf ) const;

    /*!
     * \brief
     * move the current range upon the target range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void move( session& s, range& target, const bool whole_column_or_row = false, const copy_format_from::type format_from = copy_format_from::left_or_above, insert_shift_direction::type shift_direction = insert_shift_direction::automatic, const int type_of_content = content_type::all_plus_cf ) const;

    /*!
     * \brief
     * compare if one range is < that the other.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator <( const range& rhs ) const;

    /*!
     * \brief
     * create a merged cell out of this range
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void merge( session& s );

    /*!
     * \brief
     * un-merge this range
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void un_merge( session& s );

    /*!
     * \brief
     * auto-fill
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void copy_fill( session& s, range& target );

    /*!
    * \brief
    * copy range attributes
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    void copy_styles_formats_attributes ( session& s, const shared_worksheet_type& source_sheet, sheet_range& source, sheet_range& target, const shared_worksheet_type& target_sheet );

    /*!
     * \brief
     * width
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    const sheet_layout_trait::integer_type width( session& s ) const;

    /*!
    * \brief
    * height
    *
    * \author
    * Vali Nitu <vali@yalos-solutions.com>
    */
    const sheet_layout_trait::integer_type height( session& s ) const;

    /*!
    * \brief
    * validate that a string is a valid formula and returns a value
    *
    * \author
    * Radu Ialovoi <ialovoi@yalos-solutions.com>
    */
    bool validate_formula( session& s, std::string& formula );

    /*!
    * \brief
    * clears attributes for this range
    *
    * \author
    * Radu Ialovoi <ialovoi@yalos-solutions.com>
    */
    void clear_attributes();
private:
    range( weak_worksheet_type ws, const sheet_range& rr );
private:
    weak_worksheet_type m_worksheet;
    sheet_range m_referenced_rect;
};
