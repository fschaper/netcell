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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/set_cell_lock_command.hpp"
#include <wss/range.hpp>
#include <wss/worksheet.hpp>

set_cell_lock_command::set_cell_lock_command( session& s, const sheet_range& rect, const bool lock_state ) : abstract_undoable_command( s )
    , m_rect( rect )
    , m_lock_state( !lock_state )
{}

void set_cell_lock_command::execute()
{
    if ( 20000 < m_rect.count() ) {
        throw std::logic_error( std::string( "You are trying to set lock on " + boost::lexical_cast< std::string >( m_rect.count()  ) + " cells. This would allocate too much memory!" ).c_str() );
    }
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    range r = ws->range( m_rect );
#ifdef CORE_DO_UNDO_SUPPORT
    if ( supports_do_undo::check( ws ) ) {
        m_undo_list = r.un_locked_undo_list_type();
    }
#endif
    r.un_locked( m_session, m_lock_state );
}

void set_cell_lock_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    assert( "un_execute called on a command that is on a temporary wb or on a cloned sheet!" && supports_do_undo::check( ws ) );
    range r = ws->range( m_rect );
    r.un_locked_undo_list_type( m_undo_list );
#endif
}

DEFINE_CLONEABLE( set_cell_lock_command );
