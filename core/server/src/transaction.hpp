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

#include <wss/i_undoable_command.hpp>
#include <wss/locked_object.hpp>
#include <wss/selection_state.hpp>
#include <wss/type.hpp>

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/signal.hpp>

/*!
 * \brief
 * undo manager
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class transaction
    : boost::noncopyable
{
public:
    /*!
     * \brief
     * constructor
     *
     * will hook into workbook and worksheet deletion events to clean
     * up the undo/redo queue.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    transaction();

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~transaction();

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
    shared_undoable_command_type execute( const selection_state& selection, i_command& cmd );

    /*!
     * \brief
     * can perform undo for the selected sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool can_undo( const selection_state& selection );

    /*!
     * \brief
     * can perform redo on the selected sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool can_redo( const selection_state& selection );

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
    void undo( const selection_state& selection );

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
    void redo( const selection_state& selection );

    /*!
     * \brief
     * remove all undo/redo information for the workbook
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void remove_workbook_undo_redo_list( const workbook& wb );

private:
    /*!
     * \brief
     * observer for worksheet deletions
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void observe_worksheet_deletion( const worksheet& ws );

    /*!
     * \brief
     * observer for workbook deletions.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void observe_workbook_deletion( const workbook& wb );

    /*!
     * \brief
     * class that handles undo/redo on a worksheet level.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class worksheet_command_bucket
    {
        typedef std::vector<shared_undoable_command_type> command_list_type;

    public:
        typedef command_list_type::size_type size_type;

        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        worksheet_command_bucket();

        /*!
         * \brief
         * copy constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        worksheet_command_bucket( const worksheet_command_bucket& other );

        /*!
         * \brief
         * returns true in case there are undo able operations.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool can_undo() const;

        /*!
         * \brief
         * returns true in case there are redo able operations.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool can_redo() const;

        /*!
         * \brief
         * adds a new command to the chain and erases the
         * redo chain from that point on.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        shared_undoable_command_type add( const i_undoable_command* const ptr );

        /*!
         * \brief
         * return the undo command and move the cursor
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        i_undoable_command& undo();

        /*!
         * \brief
         * return the redo command and move the cursor
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        i_undoable_command& redo();

        /*!
         * \brief
         * clear the chain and reset the cursor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void clear();

    private:
        command_list_type m_commands;
        command_list_type::iterator m_cursor;
    };

    typedef std::map<weak_worksheet_type, worksheet_command_bucket > worksheet_command_map_type;
    typedef std::map<weak_workbook_type, worksheet_command_map_type> workbook_command_map_type;
    typedef locked_object<workbook_command_map_type> locked_command_map_type;
    locked_command_map_type m_locked_command_map;

    boost::signals::connection workbook_delete_event_connection;
    boost::signals::connection worksheet_delete_event_connection;
};


