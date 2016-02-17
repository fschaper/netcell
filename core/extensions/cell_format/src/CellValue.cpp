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

#include "CellValue.hpp"

#include "ExceptionFactory.hpp"

namespace cell_format
{
    CellValue::CellValue()
        : m_type( CellValue::Empty )
    {}

    CellValue::CellValue( const std::string& s )
        : m_type( CellValue::String )
        , m_string( s )
    {}

    CellValue::CellValue( double d )
        : m_type( CellValue::Number )
        , m_number( d )
    {}

    CellValue::~CellValue()
    {}

    CellValue::Type CellValue::get_type() const
    {
        return m_type;
    }

    bool CellValue::is_empty() const
    {
        return get_type() == CellValue::Empty;
    }

    std::string CellValue::get_string() const
    {
        return m_string;
    }

    double CellValue::get_number() const
    {
        return m_number;
    }

    CellValue::CellValue( const variant& val )
    {
        switch ( val.type() ) {
            case variant::type_empty:
                m_type = CellValue::Empty;
                break;

            case variant::type_string:
                m_type = CellValue::String;
                m_string = val.string();
                break;

            case variant::type_double:
            case variant::type_bool:
                m_type = CellValue::Number;
                m_number = val.as_double();
                break;

            case variant::type_error:
            case variant::type_array:
            default:
                ExceptionFactory::raise( cell_format_exception::E_INVALID_VALUE_TYPE );
        }
    }

    CellValue::operator variant() const
    {
        return get_type() == String ? variant( get_string() )
               : ( get_type() == Number ? variant( get_number() ) : variant() );
    }
}
