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

#include <wss/point.hpp>
#include <wss/minmax.hpp>
#include <wss/rectangle_iterator.hpp>
#include <wss/position_out_of_range_exception.hpp>


#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <vector>
# define NOMINMAX
# include <algorithm>    // for std::min / std::max
# include <ostream>
# include <boost/optional.hpp>
# ifdef _DEBUG
#  include <iostream>
# endif
#endif // HAS_PRECOMPILED_HEADER == 0

#ifdef _DEBUG
// uncomment the next line to get debug output
//# define _DEBUG_RECTANGLES
#endif
#undef max
#undef min
namespace geometry
{
    /*!
     * \brief
     * type of intersection between two rectangles
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    enum border_type {
        border_none   = 0
        , border_top    = 1
        , border_bottom = 2
        , border_left   = 4
        , border_right  = 8
        , border_all = border_top | border_bottom | border_left | border_right
    };


    /*!
     * \brief
     * type of contact of two rectangles
     *
     * \see generic_rectangle::border_contact_type
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    enum contact_type {
        contact_none = 0
        , contact_top
        , contact_bottom
        , contact_left
        , contact_right
        , contact_all
    };

    /*!
    * \brief
    * type of intersection between two rectangles
    *
    * \see generic_rectangle::intersection_type
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    enum intersect_type {
        intersect_none = 0,
        inside,
        intersects
    };


    /*!
     * \brief
     * definition of an generic_rectangle in two
     * dimensional space.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template
    <
    class point_T
    >
    class generic_rectangle
    {
    public:
        typedef point_T point_type;
        typedef generic_rectangle<point_T> self_type;

        typedef rectangle_iterator iterator;
        typedef rectangle_iterator const_iterator;
        typedef std::vector<self_type> rectangles_type;
        typedef typename point_type::integer_type integer_type;
        typedef boost::optional<self_type> optional_rectangle_type;

        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        generic_rectangle( const point_type& p1, const point_type& p2 )
            : m_upper_left( point_type( std::min( p1.row(), p2.row() ), std::min( p1.column(), p2.column() ) ) )
            , m_lower_right( point_type( std::max( p1.row(), p2.row() ), std::max( p1.column(), p2.column() ) ) ) {}

        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        generic_rectangle( const point_type& p )
            : m_upper_left( p )
            , m_lower_right( p ) {}

        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rect_point_T>
        generic_rectangle( const generic_rectangle<rect_point_T>& other )
            : m_upper_left( other.upper_left() )
            , m_lower_right( other.lower_right() ) {}

        /*!
         * \brief
         * number of rows spanned by the rectangle.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline unsigned int row_count() const {
            return ( m_lower_right.row() - m_upper_left.row() ) + 1;
        }

        /*!
         * \brief
         * number of column spanned by the rectangle.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline unsigned int column_count() const {
            return ( m_lower_right.column() - m_upper_left.column() ) + 1;
        }

        /*!
         * \brief
         * number of 'cells' spanned by the rectangle.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline unsigned int count() const {
            return row_count() * column_count();
        }

        /*!
         * \brief
         * get the upper left position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline const point_type& upper_left() const {
            return m_upper_left;
        }

        /*!
         * \brief
         * get the lower right position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline const point_type& lower_right() const {
            return m_lower_right;
        }

        /*!
         * \brief
         * get the lower left position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline point_type lower_left() const {
            return lower_right().offset( 0, ( column_count() - 1 ) * -1 );
        }

        /*!
         * \brief
         * get the upper right position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline point_type upper_right() const {
            return upper_left().offset( 0, column_count() - 1 );
        }

        /*!
         * \brief
         * grow the rectangle by the passed amount of rows and columns in all directions.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline self_type grow( integer_type rows, integer_type columns ) const {
            return self_type( upper_left().offset( -1 * rows, -1 * columns ), lower_right().offset( 1 * rows, 1 * columns ) );
        }

        /*!
         * \brief
         * return a rectangle of the same size at offset position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rect_point_T>
        inline self_type offset( const rect_point_T& p ) const {
            return self_type( upper_left().offset( p ), lower_right().offset( p ) );
        }

        inline self_type offset( typename point_type::integer_type row, typename point_type::integer_type column ) const {
            return self_type( upper_left().offset( row, column ), lower_right().offset( row, column ) );
        }

        /*!
        * \brief
        * return a rectangle of the same size at offset position, move absolute references too!
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        template<class rect_point_T>
        inline self_type offset_move_absolute_references( const rect_point_T& p ) const {
            return self_type( upper_left().offset_move_absolute_references( p ), lower_right().offset_move_absolute_references( p ) );
        }

        inline self_type offset_move_absolute_references( typename point_type::integer_type row, typename point_type::integer_type column ) const {
            return self_type( upper_left().offset_move_absolute_references( row, column ), lower_right().offset_move_absolute_references( row, column ) );
        }

        /*!
         * \brief
         * checked_offset
         *
         * \param const point& p
         *
         * \return rectangle that is within the boundaries of the sheet.
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        template<class rect_point_T>
        inline self_type checked_offset( const rect_point_T& p ) const {
            return self_type( upper_left().checked_offset( p ), lower_right().checked_offset( p ) );
        }

        /*!
         * \brief
         * cyclic_offset
         *
         * \param const point& p
         *
         * \return rectangle that is within the boundaries of the sheet.
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        template<bool move_absolute_references, class sheet_dimensionT, class rect_point_T>
        inline self_type cyclic_offset( const rect_point_T& p ) const {
            return self_type( upper_left().cyclic_offset<move_absolute_references, sheet_dimensionT>( p ), lower_right().cyclic_offset<move_absolute_references, sheet_dimensionT>( p ) );
        }

        /*!
         * \brief
         * return a rectangle that is the bounding rect of the min. upper left and max. lower right
         * position of both rectangles (the current object and the passed one).
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rect_point_T>
        inline self_type enclose( const generic_rectangle<rect_point_T>& other ) const {
            return self_type( point_type( std::min( other.upper_left().row(), upper_left().row() ) , std::min( other.upper_left().column(), upper_left().column() ) )
                              , point_type( std::max( other.lower_right().row(), lower_right().row() ), std::max( other.lower_right().column(), lower_right().column() ) ) );
        }

        /*!
         * \brief
         * enclose the passed object to form the bounding rect of both areas.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rect_point_T>
        inline void enclose_into_self( const generic_rectangle<rect_point_T>& other ) {
            m_upper_left = point_type( std::min( other.upper_left().row(), upper_left().row() ) , std::min( other.upper_left().column(), upper_left().column() ) );
            m_lower_right = point_type( std::max( other.lower_right().row(), lower_right().row() ), std::max( other.lower_right().column(), lower_right().column() ) );
        }

        inline void intrusive_enclose_into_self( const self_type& other ) {
            m_upper_left.row( std::min( other.upper_left().row(), upper_left().row() ) );
            m_upper_left.column( std::min( other.upper_left().column(), upper_left().column() ) );
            m_lower_right.row( std::max( other.lower_right().row(), lower_right().row() ) );
            m_lower_right.column( std::max( other.lower_right().column(), lower_right().column() ) );
        }

        /*!
         * \brief
         * extend the coverage of the rectangle to also enclose the passed point.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class ppoint_T>
        inline self_type enclose_point( const ppoint_T& other ) const {
            return self_type( point_type( std::min( other.row(), upper_left().row() ) , std::min( other.column(), upper_left().column() ) )
                              , point_type( std::max( other.row(), lower_right().row() ), std::max( other.column(), lower_right().column() ) ) );
        }

        /*!
         * \brief
         * returns true in case the point falls not inside the rect.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class ppoint_T>
        inline bool doesnt_cover( const ppoint_T& p ) const {
            return p.row() < m_upper_left.row() || p.column() < m_upper_left.column()
                   || p.row() > m_lower_right.row() || p.column() > m_lower_right.column();
        }

        /*!
         * \brief
         * returns true in case the point falls into the rect.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class ppoint_T>
        inline bool covers( const ppoint_T& p ) const {
            return doesnt_cover( p ) == false;
        }

        /*!
         * \brief
         * returns true in case the passed rectangle is not 'completely' enclosed by the
         * current object.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rect_point_T>
        inline bool doesnt_cover( const generic_rectangle<rect_point_T>& other ) const {
            return m_upper_left.column() > other.lower_right().column()
                   || m_lower_right.column() < other.upper_left().column()
                   || m_upper_left.row() > other.lower_right().row()
                   || m_lower_right.row() < other.upper_left().row();
        }

        /*!
         * \brief
         * returns true in case the passed rect shares the same boundary or is completely enclosed.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rect_point_T>
        inline bool covers( const generic_rectangle<rect_point_T>& other ) const {
            return other.upper_left().row() >= m_upper_left.row()
                   && other.lower_right().row() <= m_lower_right.row()
                   && other.upper_left().column() >= m_upper_left.column()
                   && other.lower_right().column() <= m_lower_right.column();
        }

        /*!
         * \brief
         * return a rectangle (better a line) that forms the rectangles top border.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline self_type top() const {
            return self_type( m_upper_left, point( m_upper_left.row(), m_lower_right.column() ) );
        }

        /*!
         * \brief
         * return a rectangle (better a line) that forms the rectangles bottom border.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline self_type bottom() const {
            return self_type( point( m_lower_right.row(), m_upper_left.column() ), m_lower_right );
        }

        /*!
         * \brief
         * return a rectangle (better a line) that forms the rectangles left border.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline self_type left() const {
            return self_type( m_upper_left, point_type( m_lower_right.row(), m_upper_left.column() ) );
        }

        /*!
         * \brief
         * return a rectangle (better a line) that forms the rectangles right border.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline self_type right() const {
            return self_type( point_type( m_upper_left.row(), m_lower_right.column() ), m_lower_right );
        }

        /*!
         * \brief
         * returns true in case the passed rectangle is not completely outside the objects bounds.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rect_point_T>
        inline bool does_intersect( const generic_rectangle<rect_point_T>& other ) const {
            return !doesnt_cover( other );
        }

        /*!
        * \brief
        * type of intersection between two rectangles
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        template<class other_T>
        inline intersect_type intersection_type( const other_T& r ) const {
            return covers( r ) ? inside : ( does_intersect( r ) ? intersects : intersect_none );
        }

        /*!
         * \brief
         * returns the 'area' of the current rectangle with a (0,0) upper left offset.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline self_type coverage() const {
            return self_type( point_type( 0, 0 ), point_type( lower_right().row() - upper_left().row(), lower_right().column() - upper_left().column() ) );
        }

        /*!
         * \brief
         * returns the 'area' of the current rectangle with a (0,0) upper left offset.
         *
         * \remarks
         * one of these methods coverage / dimension is obsolete and should be removed.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline self_type dimension() const {
            return self_type( point_type( 0, 0 ), point_type( row_count() - 1, column_count() - 1 ) );
        }

        /*!
         * \brief
         * returns the area of the rectangle.
         *
         * alias for the count function.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        unsigned int area() const {
            return count();
        }

        inline self_type inner() const {
            try {
                return self_type( point_type( m_upper_left.row() + 1, m_upper_left.column() + 1 ), point_type( m_lower_right.row() - 1,  m_lower_right.column() - 1 ) );
            } catch ( const position_out_of_range_exception& ) {
                return self_type( *this );
            }
        }

        /*!
         * \brief
         * retreive a single row from rectangle
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline self_type column( unsigned int c ) const {
            return self_type( point_type( upper_left().row(), c ), point_type( lower_right().row(), c ) );
        }

        /*!
         * \brief
         * retreive a single column from rectangle
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline self_type row( unsigned int r ) const {
            return self_type( point_type( r, upper_left().column() ), point_type( r, lower_right().column() ) );
        }

        /*!
         * \brief
         * determine the distance between the two rectangles.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rect_point_T>
        inline point distance( const generic_rectangle<rect_point_T>& other ) const {
            return upper_left().distance( other.upper_left() );
        }

        /*!
         * \brief
         * determine the distance between the two rectangles.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class ppoint_T>
        inline point distance( const ppoint_T& other ) const {
            return upper_left().distance( other );
        }

        /*!
         * \brief
         * determine if and when in what way the two rectangles borders overlap.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rectangle_T>
        inline border_type border_match_type( const rectangle_T& other ) const {
            if ( other.covers( *this ) ) {
                return border_all;
            } else if ( other.top() == top() ) {
                return border_top;
            } else if ( other.bottom() == bottom() )  {
                return border_bottom;
            } else if ( other.left() == left() ) {
                return border_left;
            } else if ( other.right() == right() ) {
                return border_right;
            }
            return border_none;
        }

        inline self_type shifted_top( int i ) const {
            try {
                return self_type( point_type( static_cast<int>( m_upper_left.row() ) + i, m_upper_left.column() ), point_type( m_upper_left.row() + i, m_lower_right.column() ) );
            } catch ( const position_out_of_range_exception& ) {
                return self_type( point_type( std::max( static_cast<int>( m_upper_left.row() ) + i, 0 ), m_upper_left.column() ), point_type( std::max( static_cast<int> ( m_upper_left.row() ) + i, 0 ), m_lower_right.column() ) );
            }
        }

        inline self_type shifted_bottom( int i ) const {
            try {
                return self_type( point_type( static_cast<int>( m_lower_right.row() ) + i, m_upper_left.column() ),  point_type( m_lower_right.row() + i, m_lower_right.column() ) );
            } catch ( const position_out_of_range_exception& ) {
                return self_type( point_type( std::max( static_cast<int>( m_lower_right.row() ) + i, 0 ), m_upper_left.column() ),  point_type( std::max( static_cast<int>( m_lower_right.row() ) + i, 0 ), m_lower_right.column() ) );
            }
        }

        inline self_type shifted_left( int i ) const {
            try {
                return self_type( point_type( m_upper_left.row(), static_cast<int>( m_upper_left.column() ) + i ), point_type( m_lower_right.row(), m_upper_left.column() + i ) );
            } catch ( const position_out_of_range_exception& ) {
                return self_type( point_type( m_upper_left.row(), std::max( static_cast<int>( m_upper_left.column() ) + i, 0 ) ), point_type( m_lower_right.row(), std::max( static_cast<int>( m_upper_left.column() ) + i, 0 ) ) );
            }
        }

        inline self_type shifted_right( int i ) const {
            try {
                return self_type( point_type( m_upper_left.row(), static_cast<int>( m_lower_right.column() ) + i ),  point_type( m_lower_right.row(), m_lower_right.column() + i ) );
            } catch ( const position_out_of_range_exception& ) {
                return self_type( point_type( m_upper_left.row(), std::max( static_cast<int>( m_lower_right.column() ) + i, 0 ) ),  point_type( m_lower_right.row(), std::max( static_cast<int>( m_lower_right.column() ) + i, 0 ) ) );
            }
        }

        /*!
         * \brief
         * returns the kind of border that is adjacent to the other rectangle
         * like A1:A5 and B1:B5 (no overlapping).
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rectangle_T>
        contact_type border_contact_type( const rectangle_T& other ) const {
            if ( other.covers( *this ) ) {
                return contact_all;
            } else if ( same_columns( other ) ) {
                if ( upper_left().row() == other.lower_right().row() + 1 ) {
                    return contact_top;
                } else if ( lower_right().row() + 1 == other.upper_left().row() ) {
                    return contact_bottom;
                }
            } else if ( same_rows( other ) ) {
                if ( upper_left().column() == other.lower_right().column() + 1 ) {
                    return contact_left;
                } else if ( lower_right().column() + 1 == other.upper_left().column() ) {
                    return contact_right;
                }
            }
            return contact_none;
        }

        /*!
         * \brief
         * determine the intersection of both rectangles.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rectangle_T>
        self_type intersection( const rectangle_T& other ) const {
            if ( false == does_intersect( other ) ) {
                return self_type( point_type( 0, 0 ) );
            }

            if ( other.covers( *this ) ) {
                return *this;
            } else if ( covers( other ) ) {
                return other;
            }

            const int upper_row = std::max<int>( m_upper_left.row(), other.upper_left().row() );
            const int lower_row = std::min<int>( m_lower_right.row(), other.lower_right().row() );
            const int upper_column = std::max<int>( m_upper_left.column(), other.upper_left().column() );
            const int lower_column = std::min<int>( m_lower_right.column(), other.lower_right().column() );

            return self_type( point_type( upper_row, upper_column ), point_type( lower_row, lower_column ) );
        }

        /*!
         * \brief
         * subtract the area of the passed rectangle from the current rectangle.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rectangle_T>
        inline optional_rectangle_type subtract( const rectangle_T& other ) const {
            self_type intersecting_area( intersection( other ) );
            optional_rectangle_type return_value;

            switch ( border_match_type( intersecting_area ) ) {
                case border_top:
                    return_value = self_type( intersecting_area.lower_left().offset( 1, 0 ), lower_right() );
                    break;

                case border_right:
                    return_value = self_type( upper_left(), intersecting_area.lower_left().offset( 0, -1 ) );
                    break;

                case border_bottom:
                    return_value = self_type( upper_left(), intersecting_area.upper_right().offset( -1, 0 ) );
                    break;

                case border_left:
                    return_value = self_type( intersecting_area.upper_right().offset( 0, 1 ), lower_right() );
                    break;

                case border_all:
                    // since the whole area was deleted there is nothing we could return
                    // (the whole point of the return-value being optional).
                    break;

                default:
                    return_value = *this;
            }
            return return_value;
        }

        /*!
         * \brief
         * cut the area of the passed rectangle from the current rectangle.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rectangle_T>
        rectangles_type cut( const rectangle_T& other ) const {
            rectangles_type return_value;
            return_value.reserve( 4 );

            if ( does_intersect( other ) ) {

                self_type cutting_region( intersection( other ) );
                if ( upper_left().column() < cutting_region.upper_left().column() ) {
                    self_type r1(
                        upper_left(),
                        point( lower_right().row(), cutting_region.upper_left().column() - 1 ) );
                    return_value.push_back( r1 );
                }

                if ( upper_left().row() < cutting_region.upper_left().row() ) {
                    self_type r2(
                        point( upper_left().row(), cutting_region.upper_left().column() )
                        , point( cutting_region.upper_left().row() - 1, cutting_region.lower_right().column() ) );
                    return_value.push_back( r2 );
                }

                if ( cutting_region.lower_right().column() < lower_right().column() ) {
                    self_type r3(
                        point( upper_left().row(), cutting_region.lower_right().column() + 1 ),
                        lower_right() );
                    return_value.push_back( r3 );
                }

                if ( cutting_region.lower_right().row() < lower_right().row() ) {
                    self_type r4(
                        point( cutting_region.lower_right().row() + 1, cutting_region.upper_left().column() ),
                        point( lower_right().row(), cutting_region.lower_right().column() ) );
                    return_value.push_back( r4 );
                }

            } else {
                return_value.push_back( *this );
            }
            return return_value;
        }

        template<class rectangle_T>
        inline bool same_columns( const rectangle_T& other ) const {
            return ( other.upper_left().column() == upper_left().column() ) && ( other.lower_right().column() == lower_right().column() );
        }

        template<class rectangle_T>
        inline bool same_rows( const rectangle_T& other ) const {
            return ( other.upper_left().row() == upper_left().row() ) && ( other.lower_right().row() == lower_right().row() );
        }

        /*!
         * \brief
         * calculate the total size of the rectangles margin.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        unsigned int margin() const {
            return 2 * ( ( m_lower_right.column() - m_upper_left.column() + 1 ) + ( m_lower_right.row() - m_upper_left.row() + 1 ) );
        }

        /*!
         * \brief
         * start iterator over the rectangle
         *
         * provides an forward iterator over the rectangle that will provide
         * access to the rectangles individual points.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        iterator begin() {
            return iterator( m_upper_left, 0, column_count() );
        }

        /*!
         * \brief
         * end iterator over the rectangle
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        iterator end() {
            return iterator( m_upper_left, ( row_count() * column_count() ), column_count() );
        }

        /*!
         * \brief
         * start iterator over the rectangle
         *
         * provides an forward iterator over the rectangle that will provide
         * access to the rectangles individual points.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        const_iterator begin() const {
            return iterator( m_upper_left, 0, column_count() );
        }

        /*!
         * \brief
         * end iterator over the rectangle
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        const_iterator end() const {
            return iterator( m_upper_left, ( row_count() * column_count() ), column_count() );
        }

        /*!
         * \brief
         * returns true in case the passed rectangle is more to the right or below
         * the current rectangle.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rectangle_T>
        inline bool operator <( const rectangle_T& rhs ) const {
            if ( upper_left() < rhs.upper_left() ) {
                return true;
            } else if ( upper_left() == rhs.upper_left() ) {
                return lower_right() < rhs.lower_right();
            } else {
                return false;
            }
        }

        /*!
         * \brief
         * returns true in case the passed rectangle is more to the right or below
         * the current rectangle or shares the same position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rectangle_T>
        inline bool operator <=( const rectangle_T& rhs ) const {
            return upper_left() <= rhs.lower_right();
        }

        /*!
         * \brief
         * returns true in case both rectangles share the same position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rectangle_T>
        inline bool operator ==( const rectangle_T& rhs ) const {
            return ( upper_left() == rhs.upper_left() ) && ( lower_right() == rhs.lower_right() );
        }

        /*!
         * \brief
         * returns true in case both rectangles do NOT share the same position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class rectangle_T>
        inline bool operator !=( const rectangle_T& rhs ) const {
            return !( *this == rhs );
        }

#ifdef _DEBUG
        /*!
         * \brief
         * debugging
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void dump( const std::string& msg = "" ) {
            std::cout << msg << " " << ( *this ) << std::endl;
        }
#else
        /*!
         * \brief
         * debugging
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void dump( const std::string& ) {}
#endif // _DEBUG

    private:
        point_type m_upper_left;
        point_type m_lower_right;
    };

    /*!
     * \brief
     * debug information
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class point_T>
    std::ostream& operator <<( std::ostream& os, const generic_rectangle<point_T>& r )
    {
        os << "{" << r.upper_left() << "," << r.lower_right() << "}";
        return os;
    }
}
