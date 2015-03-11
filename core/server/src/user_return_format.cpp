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
 *  Vali Nitu <vali@yalos-solutions.com>
 */
#include "precompiled_header.hpp"
#include "wss/type.hpp"
#include "wss/user_return_format.hpp"
#include "wss/server.hpp"
#include "wss/formatter.hpp"

user_return_format::user_return_format( const session& session )
    : m_numeric_return_format( "" ) //( "#,##0.00" )
    , m_date_return_format( "" ) //( "DD.MM.YYYY" )
    , m_datetime_return_format( "" ) //( "DD.MM.YYYY hh:mi:ss" )
    , m_unspecified_format( "" )
    , m_loaded( false )
    , m_default_format_map()
    , m_session( session )
{
    m_default_format_map.clear();
    m_default_format_map.add( std::string( "unspecified" ), m_unspecified_format );
    m_default_format_map.add( std::string( "numeric" ), m_numeric_return_format );
    m_default_format_map.add( std::string( "date" ), m_date_return_format );
    m_default_format_map.add( std::string( "date_time" ), m_datetime_return_format );

}

void user_return_format::load_user_format( const locale& l )
{

    formatter::shared_format_engine_type    engine = formatter::instance().engine();
    if ( !engine ) {
        m_numeric_return_format = "#,##0.00";
        m_date_return_format = "DD.MM.YYYY";
        m_datetime_return_format = "DD.MM.YYYY hh:mi:ss";
        m_loaded = true;
    } else {
        try {
            m_numeric_return_format = engine->default_format_string( l, return_type_format::numeric );
        } catch ( wss_runtime_exception& ) {
            m_numeric_return_format = "#,##0.00";
        }
        try {
            m_date_return_format = engine->default_format_string( l, return_type_format::date );
        } catch ( wss_runtime_exception& ) {
            m_date_return_format = "DD.MM.YYYY";
        }
        try {
            m_datetime_return_format = engine->default_format_string( l, return_type_format::date_time );
        } catch ( wss_runtime_exception& ) {
            m_datetime_return_format = "DD.MM.YYYY hh:mi:ss";
        }
        m_loaded = true;
    }
}


const std::string& user_return_format::format( const return_type_format::type rt )
{
    if ( !m_loaded ) {
        load_user_format( m_session.locale() );
    }

    switch ( rt ) {
        case return_type_format::date:
            return m_date_return_format;
            break;

        case return_type_format::date_time:
            return m_datetime_return_format;
            break;


        case return_type_format::numeric:
            return m_numeric_return_format;
            break;

        default:
            return m_unspecified_format;
            break;
    }
}

user_return_format::default_format_set_type& user_return_format::default_format()
{
    return m_default_format_map;
}


void user_return_format::default_format( const default_format_set_type new_format )
{
    m_default_format_map.combine( new_format );

    for ( default_format_set_type::const_iterator i = m_default_format_map.begin(); i != m_default_format_map.end(); i++ ) {
        if ( i->second.length() != 0 ) {
            if ( i->first == "date" )  {
                m_date_return_format = i->second;
            } else if ( i->first == "date_time" ) {
                m_datetime_return_format = i->second;
            } else if ( i->first == "numeric" ) {
                m_numeric_return_format = i->second;
            } else if ( i->first == "unspecified" ) {
                m_unspecified_format = i->second;
            } else {
                m_unspecified_format = i->second;

            }
        }
    }

}



