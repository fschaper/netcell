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
#include "wss/translation_table.hpp"
#include "wss/invalid_translation_table_exception.hpp"

const shared_translation_map_type& translation_table::operator[]( const ::locale& l ) const
{
    // (fschaper) try to find an exact match for the requested locale.
    language_map_type::const_iterator it( m_entry_map.find( l ) );
    language_map_type::const_iterator end( m_entry_map.end() );
    if ( it == end ) {
        // (fschaper) we could not find an exact match for the locale, maybe we have
        // a fall back entry (de-CH requested but only de-* present).
        it = m_entry_map.upper_bound( l );
        if ( it == end || it->first != l ) {
            // (fschaper) no exact match and no fall back either. abort.
            throw invalid_translation_table_exception();
        }
    }
    return it->second;
}

bool translation_table::has( const ::locale& l ) const
{
    // (fschaper) try to find an exact match for the requested locale.
    language_map_type::const_iterator it( m_entry_map.find( l ) );
    if ( it == m_entry_map.end() ) {
        // (fschaper) an exact match could not be found. try to find a fall back.
        it = m_entry_map.upper_bound( l );
        return it != m_entry_map.end() && it->first == l;
    } else {
        return true;
    }
}

void translation_table::add( const shared_translation_map_type& map )
{
    m_entry_map.insert( language_map_type::value_type( map->locale(), map ) );
}

translation_table::translation_table()
{}

