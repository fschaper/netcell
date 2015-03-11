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
 *  \author
 *  Marek Pikulski <marek.pikulski@jedox.com>
 */

#pragma once

// stl
#include <string>
#include <vector>

// wss
#include "Color.hpp"

namespace cell_format
{
    /*! \brief Result of a cell formatting.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    struct FormattedCell {
        FormattedCell()
        {}

        FormattedCell( const std::string& s )
            : value( s )
        {}

        /*! The actual cell value. */
        std::string value;

        /*! The color to be applied to the font. */
        Color color;

        struct MeasuredSpaceInfo {
            inline MeasuredSpaceInfo()
                : idx( static_cast<size_t>( -1 ) )
            {}

            bool operator==( const MeasuredSpaceInfo& other ) const {
                return idx == other.idx && width == other.width;
            }

            bool operator!=( const MeasuredSpaceInfo& other ) const {
                return !operator==( other );
            }

            size_t idx;
            char width; //! character whose width shall be used
        };

        /*! List of indices which spaces that should have a special width determined by the specified character. */
        typedef std::vector<MeasuredSpaceInfo> MeasuredSpaces;

        MeasuredSpaces spacing;

        /*! Character to fill space on before index index value, default is no fill (padding). */
        struct Padding {
            inline Padding() : idx( static_cast<size_t>( -1 ) )
            {}

            size_t idx; //! -1 if no fill
            char value;

            bool operator==( const Padding& other ) const {
                return idx == other.idx
                       && ( idx == static_cast<size_t>( -1 ) ? true : value == other.value );
            }

            bool operator!=( const Padding& other ) const {
                return !operator==( other );
            }
        } padding;

        inline operator std::string&() {
            return value;
        }

        inline operator const std::string&() const {
            return value;
        }

        inline bool operator!=( const FormattedCell& other ) const {
            return value != other.value ? true
                   : ( color != other.color ? true
                       : ( spacing != other.spacing ? true
                           : ( padding != other.padding ? true
                               : false ) ) );
        }

        inline bool operator==( const FormattedCell& other ) const {
            return !operator!=( other );
        }
    };
}
