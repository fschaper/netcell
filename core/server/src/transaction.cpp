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
#include "transaction.hpp"
#include "wss/command.hpp"
#include "wss/undo_chain_exception.hpp"
#include "wss/workbook.hpp"
#include "wss/worksheet.hpp"
#include "wss/supports_do_undo.hpp"

#include <boost/bind.hpp>

transaction::transaction()
{
    workbook_delete_event_connection = workbook::on_global_workbook_delete.connect( boost::bind( &transaction::observe_workbook_deletion, this, _1 ) ) ;
    worksheet_delete_event_connection = worksheet::on_global_before_delete.connect( boost::bind( &transaction::observe_worksheet_deletion, this, _1 ) );
}

transaction::~transaction()
{
    // (rracariu)
    // events should be also disconnected when we're destroyed.
    // i.e. session gets killed prior of workbook/worksheet destruction
    // leading to memory corruption.
    worksheet_delete_event_connection.disconnect();
    workbook_delete_event_connection.disconnect();
}

shared_undoable_command_type transaction::execute( const selection_state& selection, i_command& cmd )
{
    shared_undoable_command_type return_value;

    // execute the command
    cmd.execute();

    if ( !supports_do_undo::check( selection ) ) {
        return return_value;
    }

    // determine if the command to be executed has undo functionality
    i_undoable_command* undoable_command = dynamic_cast<i_undoable_command*>( &cmd );
    if ( undoable_command ) {
        // the command supports undo so
        // we have to add it to the current worksheets undo queue
        return_value = ( * m_locked_command_map.lock() )[selection.workbook()][ selection.worksheet() ].add( undoable_command );
    }
    return return_value;
}

bool transaction::can_undo( const selection_state& selection )
{
    return ( * m_locked_command_map.lock() )[selection.workbook()][ selection.worksheet() ].can_undo();
}

bool transaction::can_redo( const selection_state& selection )
{
    return ( * m_locked_command_map.lock() )[selection.workbook()][ selection.worksheet() ].can_redo();
}

void transaction::undo( const selection_state& selection )
{
    locked_command_map_type::access map( m_locked_command_map );
    worksheet_command_bucket& bucket = ( *map )[selection.workbook()][ selection.worksheet() ];
    if ( ! bucket.can_undo() ) {
        throw undo_chain_exception( "can not perform undo." );
    }
    i_undoable_command& undo_command = bucket.undo();
    undo_command.un_execute();
}

void transaction::redo( const selection_state& selection )
{
    locked_command_map_type::access map( m_locked_command_map );
    worksheet_command_bucket& bucket = ( *map )[selection.workbook()][ selection.worksheet() ];
    if ( ! bucket.can_redo() ) {
        throw undo_chain_exception( "can not perform redo." );
    }
    i_undoable_command& redo_command = bucket.redo();
    redo_command.execute();
}

void transaction::observe_worksheet_deletion( const worksheet& ws )
{
    ( * m_locked_command_map.lock() )[ws.parent()].erase( ws.weak_pointer() );
}

void transaction::observe_workbook_deletion( const workbook& wb )
{
    ( * m_locked_command_map.lock() ).erase( wb.weak_pointer() );
}

void transaction::remove_workbook_undo_redo_list( const workbook& wb )
{
    ( * m_locked_command_map.lock() ).erase( wb.weak_pointer() );
}

transaction::worksheet_command_bucket::worksheet_command_bucket()
{
    clear();
}

transaction::worksheet_command_bucket::worksheet_command_bucket( const worksheet_command_bucket& other )
    : m_commands( other.m_commands )
{
    command_list_type::size_type distance = std::distance( const_cast<command_list_type&>( other.m_commands ).begin(), const_cast<command_list_type::iterator&>( other.m_cursor ) );
    m_cursor = m_commands.begin() + distance;
}

bool transaction::worksheet_command_bucket::can_undo() const
{
    return m_cursor != m_commands.begin();
}

bool transaction::worksheet_command_bucket::can_redo() const
{
    return m_cursor != m_commands.end();
}

shared_undoable_command_type transaction::worksheet_command_bucket::add( const i_undoable_command* const ptr )
{
    // in case we don't point at the end of the undo list
    // we will erase all elements from cursor position
    // to end before adding the new element.
    if ( m_cursor != m_commands.end() ) {
        m_commands.erase( m_cursor, m_commands.end() );
    }
    shared_undoable_command_type cloned_command( static_cast<i_undoable_command*>( ptr->clone().release() ) );
    m_commands.push_back( cloned_command );
    m_cursor = m_commands.end();
    return cloned_command;
}

i_undoable_command& transaction::worksheet_command_bucket::undo()
{
    assert( "tried to move cursor beyond the redo chains beginning" && m_cursor != m_commands.begin() );
    --m_cursor;
    return **m_cursor;
}

i_undoable_command& transaction::worksheet_command_bucket::redo()
{
    assert( "tried to move cursor beyond the redo chains end" && m_cursor != m_commands.end() );
    i_undoable_command& return_value = **m_cursor;
    ++m_cursor;
    return return_value;
}

void transaction::worksheet_command_bucket::clear()
{
    m_commands.clear();
    m_cursor = m_commands.end();
}
