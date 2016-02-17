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
#include "wss/transaction_command.hpp"
#include "wss/session.hpp"
#include "transaction.hpp"

/*!
 * \brief
 * compiler firewall
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct transaction_command::transaction_command_impl {
    transaction_command_impl () : shared_transaction( new ::transaction() )
    {}
    typedef boost::shared_ptr<transaction> shared_transaction_type;
    shared_transaction_type shared_transaction;
};

transaction_command::transaction_command( session& s )
    : base_command<i_undoable_command>::base_command( s ), m_impl( new transaction_command_impl() )
{}

transaction_command::~transaction_command()
{}

shared_undoable_command_type transaction_command::execute( i_command& cmd )
{
    return m_impl->shared_transaction->execute( m_session.selected(), cmd );
}

void transaction_command::execute()
{
    selection_state& ss = m_session.selected();
    while ( m_impl->shared_transaction->can_redo( ss ) ) {
        m_impl->shared_transaction->redo( ss );
    }
}

void transaction_command::un_execute()
{
    selection_state& ss = m_session.selected();
    while ( m_impl->shared_transaction->can_undo( ss ) ) {
        m_impl->shared_transaction->undo( ss );
    }
}

transaction_command::auto_type transaction_command::clone() const
{
    return auto_type( new transaction_command( m_session ) );
}
