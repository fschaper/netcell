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

namespace cell_format
{
    struct Color {
        Color()
            : m_color( _UNSET_ )
        {}

        ~Color()
        {}

        enum Colors {
            Red,
            Black,
            Cyan,
            Magenta,
            White,
            Blue,
            Green,
            Yellow,
            _UNSET_
        };

        operator Colors() const {
            return m_color;
        }

        Color& operator= ( const Colors& val ) {
            m_color = val;
            return *this;
        }

        std::string to_string() {
            switch ( m_color ) {
                case Red:
                    return std::string( "#FF0000" );
                case Black:
                    return std::string( "#000000" );
                case Cyan:
                    return std::string( "#00FFFF" );
                case Magenta:
                    return std::string( "#FF00FF" );
                case White:
                    return std::string( "#FFFFFF" );
                case Blue:
                    return std::string( "#0000FF" );
                case Green:
                    return std::string( "#00FF00" );
                case Yellow:
                    return std::string( "#FFFF00" );
                default:
                    return std::string( "" );
            }
        }


    protected:
        Colors m_color;
    };
}
