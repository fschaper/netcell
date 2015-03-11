/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  \Author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#include <wss/define.hpp>
#include <wss/sheet_point.hpp>

#include <wss/sheet_layout_trait.hpp>
#include <wss/sparse_index_integer_container.hpp>
#include <wss/type.hpp>
#include <wss/session.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <map>
#   include <vector>
#   include <boost/noncopyable.hpp>
#   include <boost/tuple/tuple.hpp>
#   include <boost/optional.hpp>
#   include <boost/cstdint.hpp>
#endif

/*!
 * \brief
 * layout manager.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE sheet_layout_manager
    : public sheet_layout_trait
{
public:
    typedef sparse_indexed_integer_container<integer_type> sparse_indexed_container_type;
private:
    typedef std::pair< integer_type, shared_dependency_type > key_val_type;
    typedef std::vector< key_val_type >  sizes_type;

    sizes_type      m_row_heights;
    sizes_type      m_col_widths;

    typedef integer_type row_index_type;

    void shift_holder( sizes_type& what,  integer_type start, const int count );
    shared_dependency_type get_holder( sizes_type& src,  integer_type pos );
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sheet_layout_manager();

public:
    void  worksheet( weak_worksheet_type ws );
    /*!
     * \brief
     * returns auto_fit information
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    integer_type measure( session& s, sizes_type& what, integer_type pos );
    /*!
     * \brief
     * will attach row/col dependencies to the given cell
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void register_new_cell( shared_dependency_type& sd, const sheet_point& p );
    /*!
     * \brief
     * retrieve the dependency used to calculate row height for the given row
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    shared_dependency_type get_row_height_holder( integer_type row_index );
    /*!
     * \brief
     * retrieve the dependency used to calculate col width for the given col
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    shared_dependency_type get_col_width_holder( integer_type col_index );

    /*!
     * \brief
     * retrieve the row height for the given row index.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    integer_type row_height( integer_type row_index ) const;

    /*!
     * \brief
     * set the column width for the given column index.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    integer_type hidden_row_height( integer_type row_index ) const;

    /*!
     * \brief
     * retrieve the column width for the given column index.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    integer_type column_width( integer_type column_index ) const;

    /*!
     * \brief
     * set the column width for the given column index.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    integer_type hidden_column_width( integer_type column_index ) const;

    /*!
     * \brief
     * set the row height for the given row index
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void row_height( integer_type row_index, integer_type height );

    /*!
     * \brief
     * set the row height for the given range
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void row_height( const line_type& from_to, integer_type height );

    /*!
     * \brief
     * set the column width for the given column index.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void column_width( integer_type column_index, integer_type width );

    /*!
     * \brief
     * set the column width for the given range.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void column_width( const line_type& from_to, integer_type width );
    /*!
     * \brief
     * set the default column width
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void default_column_width( integer_type default_width );

    /*!
     * \brief
     * set the default row height.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void default_row_height( integer_type default_height );

    /*!
     * \brief
     * get the default column width.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    integer_type default_column_width() const;

    /*!
     * \brief
     * get the default row height.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    integer_type default_row_height() const;

    /*!
     * \brief
     * get sparse column information (all values that differ from the default).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_value_range_type sparse_column_range( const line_type& from_to ) const;

    /*!
     * \brief
     * get sparse row information (all values that differ from the default).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_value_range_type sparse_row_range( const line_type& from_to ) const;

    /*!
     * \brief
     * get sparse cell width informations (all values that differ from the default).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_value_range_type sparse_max_cell_width( session& s, const line_type& from_to );

    /*!
     * \brief
     * get sparse cell height informations (all values that differ from the default).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_value_range_type sparse_max_cell_height( session& s, const line_type& from_to );

    void shift_columns( integer_type start_column, const int column_count );
    void shift_rows( integer_type start_row, const int row_count );

    /*!
     * \brief
     * copy every little bit of information to other!
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void copy_everything_to_other( sheet_layout_manager& other ) const;

    /*!
     * \brief
     * retrieve the row/column maps.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    const sparse_indexed_container_type& columns();
    const sparse_indexed_container_type& rows();

    /*!
     * \brief
     * hide row.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void hide_row( integer_type row_index );

    /*!
     * \brief
     * unhide row.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void unhide_row( integer_type row_index );

    /*!
     * \brief
     * hide column.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void hide_column( integer_type column_index );

    /*!
     * \brief
     * unhide column.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void unhide_column( integer_type column_index );

    /*!
     * \brief
     * invalidates a rectangle so that maximum row/col values gets recomputed
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void invalidate_rect( sheet_range& rect );
private:
    sparse_indexed_container_type m_column_map;
    sparse_indexed_container_type m_row_map;
    sparse_indexed_container_type m_hidden_column_map;
    sparse_indexed_container_type m_hidden_row_map;

    weak_worksheet_type m_worksheet;
};

