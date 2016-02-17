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
#include "wss/paste_range_command.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/worksheet.hpp"
#include "wss/range.hpp"

paste_range_command::paste_range_command( session& s, const sheet_range& target, clipboard::clipboard_id_type id, int paste_type /* = content_type::all_plus_cf */ )
    : abstract_undoable_command( s )
    , m_target( target )
    , m_clipboard_id( id )
    , m_paste_type( paste_type )
{
    if ( m_paste_type & content_type::style ) {
        m_paste_type |= content_type::border;
    }
}

void paste_range_command::execute()
{
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();

    clipboard& cb = m_session.clipboard();

    m_saved_clip_entry = cb.get( m_clipboard_id );
    if ( ( *m_saved_clip_entry ).type() != clipboard_entry::entry::range ) {
        return;
    }

    range source = boost::any_cast<range>( ( *m_saved_clip_entry ).get() );
    range target = ws->range( m_target );
#ifdef CORE_DO_UNDO_SUPPORT
    if ( supports_do_undo::check( ws ) ) {
        m_old_value_target = target.value( m_session );
    }
#endif
    switch ( ( *m_saved_clip_entry ).method() ) {
        case clipboard_entry::method::copy:
            source.copy( m_session, target, false, insert_shift_direction::automatic, m_paste_type );
            break;

        case clipboard_entry::method::cut:
            source.move( m_session, target, false, copy_format_from::left_or_above, insert_shift_direction::automatic, m_paste_type  );
            break;

        case clipboard_entry::method::copy_fill:
            source.copy_fill( m_session, target ); //TODO: m_paste_type
            break;

        case clipboard_entry::method::copy_move:
            source.copy_move( m_session, target, insert_shift_direction::automatic, m_paste_type  );
            break;

        default:
            assert( !"unknown clipboard command issued" );
    }
}

void paste_range_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    assert( "un_execute called on a command that is on a temporary wb or on a cloned sheet!" && supports_do_undo::check( ws ) );
    range target = ws->range( m_target );
    target.value( m_session, m_old_value_target );
    if ( m_saved_clip_entry ) {
        m_session.clipboard().add( *m_saved_clip_entry );
    }
#endif
}

DEFINE_CLONEABLE( paste_range_command );
