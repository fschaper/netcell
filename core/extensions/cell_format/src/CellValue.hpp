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


// wss
#include <wss/variant.hpp>

namespace cell_format
{
    /*! \brief Data m_type representing the cell contents that should be formatted.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class CellValue
    {
    public:
        CellValue();

        CellValue( const std::string& s );

        CellValue( double d );

        CellValue( const variant& val );

        ~CellValue();

        enum Type {
            Number
            , String
            , Empty
        };

        Type get_type() const;

        bool is_empty() const;

        std::string get_string() const;

        double get_number() const;

        bool get_boolean() const;

        operator variant() const;

    private:
        Type m_type;
        std::string m_string;
        double m_number;
        bool m_bool;
    };
}
