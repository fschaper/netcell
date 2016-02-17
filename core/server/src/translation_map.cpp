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

#include "precompiled_header.hpp"
#include "wss/translation_map.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/algorithm/string.hpp>
#endif

translation_map::function_translation_entry::function_translation_entry( const std::string& id , const std::string& transl , const std::string& long_desc /*= "" */, const std::string& short_desc /*= "" */ )
    : identifier( to_upper_copy_utf8( id ) )
    , translation( to_upper_copy_utf8( transl ) )
    , description_long( long_desc )
    , description_short( short_desc )
{}

translation_map::translation_map( const ::locale& l, const std::string& parameter_separator, const std::string& column_separator, const std::string& row_separator, bool use_dot, const std::string& t_true, const std::string& t_false )
    : m_locale( l )
    , m_parameter_separator( parameter_separator )
    , m_column_separator( column_separator )
    , m_row_separator( row_separator )
    , m_boolean_true( to_upper_copy_utf8( t_true ) )
    , m_boolean_false( to_upper_copy_utf8( t_false ) )
    , m_use_dot_as_real_separator( use_dot )
    , internal_name_lookup( m_internal_lookup )
    , external_name_lookup( m_external_lookup )
{}

void translation_map::add( const function_translation_entry& entry )
{
    if ( m_internal_lookup.find( convert_utf8_ci( entry.identifier ) ) == m_internal_lookup.end() ) {
        m_entry_map.push_back( entry );
        m_external_lookup.insert( lookup_table_type::value_type( convert_utf8_ci( entry.identifier ), &*m_entry_map.rbegin() ) );
        m_internal_lookup.insert( lookup_table_type::value_type( convert_utf8_ci( entry.translation ), &*m_entry_map.rbegin() ) );
    }
}

const translation_map::error_mapping::type& translation_map::error_translation() const
{
    return m_error_translation_map;
}

void translation_map::error_translation( const error_mapping::type& map )
{
    m_error_translation_map = map;
}

const ::locale& translation_map::locale() const
{
    return m_locale;
}

const std::string& translation_map::parameter_separator() const
{
    return m_parameter_separator;
}

const std::string& translation_map::column_separator() const
{
    return m_column_separator;
}

const std::string& translation_map::row_separator() const
{
    return m_row_separator;
}

const std::string& translation_map::boolean_true() const
{
    return m_boolean_true;
}

const std::string& translation_map::boolean_false() const
{
    return m_boolean_false;
}

shared_translation_map_type translation_map::create( const ::locale& l, const std::string& parameter_separator, const std::string& column_separator, const std::string& row_separator, bool use_dot, const std::string& t_true, const std::string& t_false )
{
    return boost::make_shared<translation_map>( l, parameter_separator, column_separator, row_separator, use_dot, t_true, t_false );
}

bool translation_map::use_dot_as_real_separator() const
{
    return m_use_dot_as_real_separator;
}

