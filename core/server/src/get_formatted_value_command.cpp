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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"
#include "wss/get_formatted_value_command.hpp"
#include "wss/formatter.hpp"

get_formatted_value_command::get_formatted_value_command( session& s, const std::string& format, const variant& value )
    : base_command<i_command>::base_command( s )
    , m_format( format )
    , m_value( value )
{}

void get_formatted_value_command::execute()
{

    formatter::shared_format_engine_type    engine = formatter::instance().engine();

    if ( !engine ) {
        // TODO (fschaper) throw specialized exception
        throw std::runtime_error( "no format engine" );
    }

    try {
        m_return = engine->formatted_value( m_session, m_format, m_value );
    } catch ( std::exception& e ) {
        //TODO: specialized exceptions here.
        m_return = "";
    }
}

get_formatted_value_command::result_type get_formatted_value_command::value() const
{
    return m_return;
}

DEFINE_CLONEABLE( get_formatted_value_command );
