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
#include "wss/variable_store.hpp"
#include "wss/session.hpp"
#include "wss/worksheet.hpp"

void variable_store::variable( session& s, const std::string& key, const variant& value )
{
    {
        lock_type lock( m_mutex );
        m_list[ key ] = value;
    }
    s.clear_cache();
    if ( shared_worksheet_type ws = s.selected().worksheet().lock() ) {
        ws->compute_view_independent( s );
    }
}

variant variable_store::variable( const std::string& key )
{
    lock_type lock( m_mutex );
    variable_mapping_list_type::const_iterator it( m_list.find( key ) );
    return ( it != m_list.end() ) ? it->second : variant( variant::error_value );
}

const variable_mapping_list_type& variable_store::list() const
{
    lock_type lock( m_mutex );
    return m_list;
}

void variable_store::clear()
{
    lock_type lock( m_mutex );
    m_list.clear();
}

