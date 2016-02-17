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

#pragma once

#include <wss/i_command.hpp>
#include <wss/define.hpp>

#include <boost/scoped_ptr.hpp>

class session;
class workbook;

/*!
 * \brief
 * transaction handling with rollback support.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE transaction_wrapper
    : boost::noncopyable
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    transaction_wrapper();

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~transaction_wrapper();

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    transaction_wrapper( session& s );

    /*!
     * \brief
     * starts a new transaction.
     *
     * \remarks
     * in case you start a new transaction you will automatically conclude
     * an existing one not formerly closed.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void start_transaction();

    /*!
     * \brief
     * end a transaction
     *
     * a transaction also automatically ends in case
     * start_transaction is called again.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void end_transaction();

    /*!
     * \brief
     * undo all operations that have been performed for the
     * current transaction
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void rollback();

    /*!
     * \brief
     * execute command and add it to the undo chain if applicable.
     *
     * \remarks
     * the transaction manager relies on the select_worksheet_command
     * and select_workbook_command as being un_executable for
     * switching sheets/workbooks.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void execute( i_command& cmd );

    /*!
     * \brief
     * can perform undo for the selected sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool can_undo();

    /*!
     * \brief
     * can perform redo on the selected sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool can_redo();

    /*!
     * \brief
     * perform undo.
     *
     * \throw
     * will throw an 'undo_chain_exception' in case the operation
     * could not be performed (there is no undo).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void undo();

    /*!
     * \brief
     * perform redo.
     *
     * \throw
     * will throw an 'undo_chain_exception' in case the operation
     * could not be performed (there is no redo).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void redo();

    /*!
     * \brief
     * remove all undo/redo information for the workbook
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void remove_workbook_undo_redo_list( const workbook& wb );

private:
    class transaction_wrapper_impl;
    boost::scoped_ptr<transaction_wrapper_impl> m_impl;
};


