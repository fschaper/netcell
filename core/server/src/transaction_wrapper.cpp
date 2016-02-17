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
#include "wss/transaction_wrapper.hpp"
#include "wss/transaction_command.hpp"
#include "wss/select_worksheet_command.hpp"
#include "transaction.hpp"
#include "wss/session.hpp"
#include "wss/workbook.hpp"
#include "wss/worksheet.hpp"

/*!
* \brief
* compiler firewall
*
* \author
* Florian Schaper <florian.schaper@jedox.com>
*/
class transaction_wrapper::transaction_wrapper_impl
{
public:
    explicit transaction_wrapper_impl( ::session& s )
        : m_session( s )
    {}

    ::session& session() {
        return m_session;
    }

    transaction m_transact;
    shared_undoable_command_type m_current_transaction;
    ::session& m_session;
    weak_worksheet_type m_transaction_starting_sheet;
};

transaction_wrapper::transaction_wrapper()
{}

transaction_wrapper::~transaction_wrapper()
{}

// (rracariu) session should be used with care,
// as we're called from session's ctor, order of init might change there
transaction_wrapper::transaction_wrapper( session& s )
    : m_impl( new transaction_wrapper_impl( s ) )
{}

void transaction_wrapper::start_transaction()
{
    transaction_command cmd( m_impl->session() );
    m_impl->m_transaction_starting_sheet = m_impl->session().selected().worksheet();
    m_impl->m_current_transaction = m_impl->m_transact.execute( m_impl->session().selected(), cmd );
}

void transaction_wrapper::end_transaction()
{
    if ( m_impl->m_current_transaction ) {
        m_impl->m_current_transaction.reset();
        // if during a transaction we've change the worksheet,
        // add a synthesized command to switch to the new worksheet
        if ( m_impl->session().selected().worksheet().lock() != m_impl->m_transaction_starting_sheet.lock() ) {
            shared_workbook_type wb = m_impl->session().selected().workbook().lock();
            uuid_type current_transaction_sheet = m_impl->session().selected().worksheet().lock()->uuid();
            wb->get( m_impl->session(), m_impl->m_transaction_starting_sheet.lock()->uuid() )->select( m_impl->session().selected() );
            select_worksheet_command swc ( m_impl->session(), current_transaction_sheet );
            execute( swc );
        }
    }
}

void transaction_wrapper::rollback()
{
    if ( m_impl->m_current_transaction ) {
        m_impl->m_transact.undo( m_impl->session().selected() );
        m_impl->m_current_transaction.reset();
    } else if ( m_impl->m_transact.can_undo( m_impl->session().selected() ) ) {
        m_impl->m_transact.undo( m_impl->session().selected() );
    }
}

void transaction_wrapper::execute( i_command& cmd )
{
    if ( m_impl->m_current_transaction ) {
        static_cast<transaction_command&>( *m_impl->m_current_transaction ).execute( cmd );
    } else {
        m_impl->m_transact.execute( m_impl->session().selected(), cmd );
    }
}

bool transaction_wrapper::can_undo()
{
    return m_impl->m_transact.can_undo( m_impl->session().selected() );
}

bool transaction_wrapper::can_redo()
{
    return m_impl->m_transact.can_redo( m_impl->session().selected() );
}

void transaction_wrapper::undo()
{
    return m_impl->m_transact.undo( m_impl->session().selected() );
}

void transaction_wrapper::redo()
{
    return m_impl->m_transact.redo( m_impl->session().selected() );
}

void transaction_wrapper::remove_workbook_undo_redo_list( const workbook& wb )
{
    m_impl->m_transact.remove_workbook_undo_redo_list( wb );
}

