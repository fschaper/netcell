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
#include "wss/set_attribute_command.hpp"
#include "wss/range.hpp"
#include "wss/worksheet.hpp"
#include "wss/session.hpp"
#include "wss/invalid_worksheet_exception.hpp"

set_attribute_command::set_attribute_command( session& s, const sheet_range& area, const std::string& json )
    : abstract_undoable_command( s )
    , m_area( area )
    , m_new_attributes( json )
{}

void set_attribute_command::execute()
{
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    range r( ws->range( m_area ) );
#ifdef CORE_DO_UNDO_SUPPORT
    if ( supports_do_undo::check( ws ) ) {
        m_old_attributes = r.attribute_undo_list();
    }
#endif
    r.attribute( m_session, attribute_set_type::unserialize( m_new_attributes ) );
}

void set_attribute_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    assert( "un_execute called on a command that is on a temporary wb or on a cloned sheet!" && supports_do_undo::check( ws ) );
    range r( ws->range( m_area ) );
    r.attribute_undo_list( m_old_attributes );
#endif
}

DEFINE_CLONEABLE( set_attribute_command );


