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

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <ostream>
# include <boost/cstdint.hpp>
#include <cassert>
#endif // HAS_PRECOMPILED_HEADER == 0
#include "wss/non_instantiable.hpp"
#include "wss/sheet_dimension.hpp"

namespace geometry
{

    //little helper to get a key from row and column (only use this with positive row and column!)
    struct calculate_key : non_instantiable {
        template<class intT>
        static inline boost::uint_fast32_t key( const intT row, const intT column ) {
            if ( !( row >= 0 && column >= 0 ) ) {
                throw std::logic_error( "this function should only be called with positive numbers!" );
            }
            return ( row * ( sheet_dimension::max_column + 1 ) ) + column;
        }
    };

    /*!
     * \brief
     * generic point class
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template
    <
    class derived_T
    >
    class generic_point
    {
    public:
        typedef derived_T derived_type;
        typedef generic_point<derived_T> self_type;
        typedef boost::int_fast32_t integer_type;

        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        generic_point( integer_type row, integer_type column )
            : m_row( row )
            , m_column( column ) {}

        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_T>
        generic_point( const other_T& p )
            : m_row( p.row() )
            , m_column( p.column() ) {}

        /*!
         * \brief
         * copy constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        generic_point( const self_type& other )
            : m_row( other.m_row )
            , m_column( other.m_column ) {}

        /*!
         * \brief
         * return the row part of the point.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        integer_type row() const {
            return m_row;
        }

        /*!
         * \brief
         * return the column part of the point.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        integer_type column() const {
            return m_column;
        }

        /*!
        * \brief
        * set the row part of the point.
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void row( const integer_type r ) {
            m_row = r;
        }

        /*!
         * \brief
         * set the column part of the point.
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        void column( const integer_type c ) {
            m_column = c;
        }

        /*!
         * \brief
         * calculate a offset from the point.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_T>
        inline derived_T offset( const other_T& other ) const;

        /*!
         * \brief
         * calculate a offset from the point.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_row_T, class other_col_T>
        inline derived_T offset( const other_row_T row, const other_col_T column ) const {
            return derived_T( this->row() + row, this->column() + column );
        }
        /*!
                 * \brief
                 * calculate a offset from the point.
                 *
                 * \author
                 * Florian Schaper <florian.schaper@jedox.com>
                 */
        template<class other_T>
        inline derived_T offset_move_absolute_references( const other_T& other ) const;

        /*!
         * \brief
         * calculate a offset from the point.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_row_T, class other_col_T>
        inline derived_T offset_move_absolute_references( const other_row_T row, const other_col_T column ) const {
            return offset( row, column );
        }


        /*!
         * \brief checked_offset
         * offset that is within the boundaries of the sheet
         * (only shift the point until the boundaries are reached!)
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        template<class other_T>
        inline derived_T checked_offset( const other_T& other ) const;

        /*!
         * \brief checked_offset
         * offset that is within the boundaries of the sheet
         * (only shift the point until the boundaries are reached!)
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        template<class other_row_T, class other_col_T>
        inline derived_T checked_offset( const other_row_T row, const other_col_T column ) const {
            return offset( row, column );
        }

        /*!
         * \brief cyclic_offset
         * offset that is within the boundaries of the sheet
         * (shift cyclic)
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        template<bool move_absolute_references, class sheet_dimensionT, class other_T>
        inline derived_T cyclic_offset( const other_T& other ) const;

        /*!
         * \brief cyclic_offset
         * offset that is within the boundaries of the sheet
         * (shift cyclic)
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        template<bool move_absolute_references, class sheet_dimensionT, class other_row_T, class other_col_T>
        inline derived_T cyclic_offset( const other_row_T row, const other_col_T column ) const {
            return offset( row, column );
        }

        /*!
         * \brief
         * calculate the distance between two points.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_T>
        inline derived_T distance( const other_T& other ) const;

        /*!
         * \brief
         * calculate the distance between two points.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        inline derived_T distance( integer_type row, integer_type column ) const {
            return derived_T( ( row - this->row() ), ( column - this->column() ) );
        }

        /*!
         * \brief
         * calculate a negative offset from the point.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_T>
        inline other_T operator -( const other_T& rhs ) const {
            return other_T( this->offset( rhs.row() * -1, rhs.column() * -1 ) );
        }

        /*!
         * \brief
         * calculate a offset from the point.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_T>
        inline other_T operator +( const other_T& rhs ) const {
            return other_T( this->offset( rhs.row(), rhs.column() ) );
        }

        /*!
         * \brief
         * test two points for equality
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_T>
        inline bool operator ==( const other_T& rhs ) const {
            return is_at_same_row( rhs ) && is_at_same_column( rhs );
        }

        /*!
         * \brief
         * test two points for inequality.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_T>
        inline bool operator !=( const other_T& rhs ) const {
            return !( *this == rhs );
        }

        /*!
         * \brief
         * test if a point is above or to the left of another point
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_T>
        inline bool operator <( const other_T& other ) const {
            if ( is_strict_above( other ) ) {
                return true;
            } else if ( is_at_same_row( other ) ) {
                return is_strict_left_of( other );
            } else {
                return false;
            }
        }

        /*!
         * \brief
         * test if a point is above or to the left of another point
         * or shares the same position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_T>
        inline bool operator <=( const other_T& other ) const {
            if ( is_strict_below( other ) ) {
                return true;
            } else if ( is_at_same_row( other ) ) {
                return is_left_of_or_at_same_column( other );
            } else {
                return false;
            }
        }

        /*!
         * \brief
         * little helpers, they do what the name suggests
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        template<class other_T>
        inline bool is_strict_left_of( const other_T& other ) const {
            return column() < other.column();
        }

        template<class other_T>
        inline bool is_strict_right_of( const other_T& other ) const {
            return column() > other.column();
        }

        template<class other_T>
        inline bool is_strict_above( const other_T& other ) const {
            return row() < other.row();
        }

        template<class other_T>
        inline bool is_strict_below( const other_T& other ) const {
            return row() > other.row();
        }

        template<class other_T>
        inline bool is_left_of_or_at_same_column( const other_T& other ) const {
            return column() <= other.column();
        }

        template<class other_T>
        inline bool is_right_of_or_at_same_column( const other_T& other ) const {
            return column() >= other.column();
        }

        template<class other_T>
        inline bool is_above_or_at_same_row( const other_T& other ) const {
            return row() <= other.row();
        }

        template<class other_T>
        inline bool is_below_or_at_same_row( const other_T& other ) const {
            return row() >= other.row();
        }

        template<class other_T>
        inline bool is_at_same_column( const other_T& other ) const {
            return column() == other.column();
        }

        template<class other_T>
        inline bool is_at_same_row( const other_T& other ) const {
            return row() == other.row();
        }

    private:
        integer_type m_row;
        integer_type m_column;
    };

    /*!
     * \brief
     * debug information
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class derived_T>
    std::ostream& operator <<( std::ostream& os, const generic_point<derived_T>& p );

#include "generic_point.ipp"
}

