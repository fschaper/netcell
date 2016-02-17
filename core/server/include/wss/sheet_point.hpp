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

#include <wss/position_out_of_range_exception.hpp>
#include <wss/sheet_dimension.hpp>
#include <wss/reference.hpp>
#include <wss/define.hpp>
#include <wss/point.hpp>





/*!
 * \brief
 * point that ensures it is within a worksheets bounds.
 *
 * \see
 * point_base | cyclic_point
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class sheet_point
    : public geometry::generic_point<sheet_point>
{
    typedef geometry::generic_point<sheet_point> base_type;
    friend class geometry::generic_point<sheet_point>;
public:
    typedef boost::uint_fast32_t unsigned_integer_type;

    /*!
     * \brief
     * sheet_point
     *
     * \throws
     * will throw an position_out_of_range_exception exception in case the
     * coordinates are not within the sheet boundaries.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sheet_point( unsigned_integer_type row, unsigned_integer_type column, reference::type reference_type = reference::relative )
        : base_type( row, column )
        , m_reference_type( reference_type ) {
        if ( this->row() > static_cast<int>( sheet_dimension::max_row ) || this->column() > static_cast<int>( sheet_dimension::max_column ) ) {
            throw position_out_of_range_exception();
        }
    }

    /*!
     * \brief
     * sheet_point
     *
     * \throws
     * will throw an position_out_of_range_exception exception in case the
     * coordinates are not within the sheet boundaries.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sheet_point( const geometry::point& p, reference::type reference_type = reference::relative )
        : base_type( p )
        , m_reference_type( reference_type ) {
        if ( this->row() > static_cast<int>( sheet_dimension::max_row ) || this->column() > static_cast<int>( sheet_dimension::max_column )
                || this->row() < 0 || this->column() < 0 ) {
            throw position_out_of_range_exception();
        }
    }

    /*!
     * \brief
     * copy constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sheet_point( const sheet_point& other )
        : base_type( other )
        , m_reference_type( other.m_reference_type ) {}

    /*!
     * \brief
     * to determine if the point is of absolute or relative type.
     *
     * \return reference::type
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    reference::type type() const {
        return m_reference_type;
    }

    /*!
     * \brief
     * comparison
     *
     * \return bool
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline bool operator ==( const sheet_point& rhs ) const {
        return base_type::operator ==( rhs ) && ( type() == rhs.type() );
    }

    /*!
     * \brief
     * less than
     *
     * \return bool
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    inline bool operator <( const sheet_point& rhs ) const {
        if ( is_at_same_row( rhs ) && is_at_same_column( rhs ) ) {
            return type() < rhs.type();
        }
        return base_type::operator <( rhs );
    }

    /*!
     * \brief
     * unique index of the point on the sheet.
     *
     * \return reference::type
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline unsigned_integer_type key() const {
        return geometry::calculate_key::key( row(), column() );
    }

    /*!
     * \brief
     * create sheet_point from key index
     *
     * \return sheet_point
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static sheet_point from_key( unsigned_integer_type key ) {
        return sheet_point( row_from_key( key ), column_from_key( key ) );
    }

    /*!
     * \brief
     * returns row/column from key
     *
     * \return row and column
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    static void from_key( const unsigned_integer_type key, integer_type& row, integer_type& col  ) {
        row = row_from_key( key );
        col = column_from_key( key );
    }

    /*!
     * \brief
     * given a key, calculate the column
     * this is an optimization used when calculating the used range for cells
     *
     * \return column
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static integer_type column_from_key( const unsigned_integer_type key ) {
        return key % ( sheet_dimension::max_column + 1 );
    }

    /*!
     * \brief
     * given a key, calculate the row
     * this is an optimization used when calculating the used range for cells
     *
     * \return row
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static integer_type row_from_key( const unsigned_integer_type key ) {
        return key / ( sheet_dimension::max_column + 1 );
    }

private:
    reference::type m_reference_type;
};

namespace geometry
{
    /*!
     * \brief
     * offset
     *
     * \param int row
     * \param int column
     *
     * \return sheet_point
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<>
    template<class other_row_T, class other_col_T>
    inline sheet_point generic_point<sheet_point>::offset( const other_row_T row, const other_col_T column ) const
    {
        return sheet_point(
                   ( static_cast<const sheet_point&>( *this ).m_reference_type & reference::absolute_row ? this->row() : this->row() + row )
                   , ( static_cast<const sheet_point&>( *this ).m_reference_type & reference::absolute_column ? this->column() : this->column() + column )
                   , static_cast<const sheet_point&>( *this ).m_reference_type );
    }

    /*!
    * \brief
    * offset
    *
    * \param int row
    * \param int column
    *
    * \return sheet_point (move absolute references too!)
    *
    * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    template<>
    template<class other_row_T, class other_col_T>
    inline sheet_point generic_point<sheet_point>::offset_move_absolute_references( const other_row_T row, const other_col_T column ) const
    {
        return sheet_point(
                   ( this->row() + row )
                   , ( this->column() + column )
                   , static_cast<const sheet_point&>( *this ).m_reference_type );
    }
    /*!
    * \brief
    * cyclic_offset
    *
    * \param row
    * \param column
    *
    * \return sheet_point that is within the boundaries of the sheet, even if row/column aren't.
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    namespace sheet_point_internal
    {
        template<class other_T>
        inline sheet_point::integer_type calculate_offset(
            const sheet_point::integer_type own_value,
            const other_T other_value
            , const int max_value )
        {
            return ( ( ( ( own_value + other_value ) % max_value ) + max_value  ) % max_value );

        }

        template<class other_T>
        inline sheet_point::integer_type calculate_offset_if_not_absolute(
            const bool is_absolute,
            const sheet_point::integer_type own_value,
            const other_T other_value, const int max_value )
        {
            if ( is_absolute ) {
                return own_value;
            }
            return calculate_offset( own_value, other_value, max_value );
        }


    } //namespace sheet_point_internal

    template<>
    template<bool move_absolute_references, class sheet_dimensionT, class other_row_T, class other_col_T>
    inline sheet_point generic_point<sheet_point>::cyclic_offset( const other_row_T row,  const other_col_T column ) const
    {
        const int max_row_num = sheet_dimensionT::max_row + 1;
        const int max_col_num = sheet_dimensionT::max_column + 1;
        if ( move_absolute_references ) {

            return sheet_point(
                       sheet_point_internal::calculate_offset( this->row(), row, max_row_num )
                       , sheet_point_internal::calculate_offset( this->column(), column, max_col_num )
                       , static_cast<const sheet_point&>( *this ).m_reference_type );
        } else {
            return sheet_point(
                       sheet_point_internal::calculate_offset_if_not_absolute(
                           static_cast<const sheet_point&>( *this ).m_reference_type & reference::absolute_row
                           , this->row(), row, max_row_num )
                       , sheet_point_internal::calculate_offset_if_not_absolute(
                           static_cast<const sheet_point&>( *this ).m_reference_type & reference::absolute_column
                           , this->column(), column, max_col_num )
                       , static_cast<const sheet_point&>( *this ).m_reference_type );
        }
    }


    /*!
    * \brief
    * checked_offset
    *
    * \param row
    * \param column
    *
    * \return sheet_point that is within the boundaries of the sheet, even if row/column aren't.
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    template<>
    template<class other_row_T, class other_col_T>
    inline sheet_point generic_point<sheet_point>::checked_offset( const other_row_T row,  const other_col_T column ) const
    {
        return sheet_point(
                   static_cast<const sheet_point&>( *this ).m_reference_type & reference::absolute_row ?
                   // absolute, just return the value, nothing to do
                   this->row()
                   :
                   // relative row, we have to adjust
                   ( static_cast<integer_type>( std::max<other_row_T>( 0, std::min<other_row_T>( this->row() + row, sheet_dimension::max_row ) ) ) )
                   ,
                   static_cast<const sheet_point&>( *this ).m_reference_type & reference::absolute_column ?
                   // absolute, just return the value, nothing to do
                   this->column()
                   :
                   // relative column, we have to adjust
                   ( static_cast<integer_type>( std::max<other_row_T>( 0,  std::min<other_col_T>( this->column() + column, sheet_dimension::max_column ) ) ) )
                   , static_cast<const sheet_point&>( *this ).m_reference_type );
    }
}

/*!
 * \brief
 * supports output with formatting specific settings.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
WSS_MODULE std::ostream& operator <<( std::ostream& os, const sheet_point& p );
