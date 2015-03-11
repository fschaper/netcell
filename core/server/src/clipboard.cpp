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
#include "wss/clipboard.hpp"
#include "wss/invalid_clipboard_entry_exception.hpp"
#include "wss/range.hpp"

clipboard_entry::clipboard_entry( const boost::any& e, method::type mt /*= undefined*/, entry::type et /*= undefined */ )
    : m_entry( e )
    , m_method( mt )
    , m_type( et )
{}

const boost::any& clipboard_entry::get() const
{
    return m_entry;
}

boost::any clipboard_entry::get()
{
    return m_entry;
}

clipboard_entry::method::type clipboard_entry::method() const
{
    return m_method;
}

clipboard_entry::entry::type clipboard_entry::type() const
{
    return m_type;
}

//////////////////////////////////////////////////////////////////////////

clipboard::clipboard()
    : m_container( clipboard_ring_size )
    , m_index( 0 )
{}

long clipboard::add( const clipboard_entry& entry )
{
    clipboard_id_type current_index = ( m_index++ % clipboard_ring_size );
    m_container[ current_index ] = entry;
    return current_index;
}

const clipboard_entry& clipboard::get( clipboard_id_type index ) const
{
    if ( index < 0 || index >= m_container.size() ) {
        throw invalid_clipboard_entry_exception();
    }

    return m_container[ index ];
}

void clipboard::clear()
{
    m_container.clear();
    m_container.resize( clipboard_ring_size );
}

bool clipboard::is_empty() const
{
    return m_container.empty();
}



