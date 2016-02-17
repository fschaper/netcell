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
#include <wss/base_command.hpp>
#include <wss/define.hpp>

/*!
 * \brief
 * transaction command for rollback support.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE transaction_command
    : public base_command<i_undoable_command>
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    transaction_command( session& s );

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~transaction_command();

    /*!
     * \brief
     * add a command to the transactional command
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_undoable_command_type execute( i_command& cmd );

    /*!
     * \brief
     * execute all transactional commands
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void execute();

    /*!
     * \brief
     * unexecute all transactional commands
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void un_execute();

    /*!
     * \brief
     * clone method.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual auto_type clone() const;

private:
    struct transaction_command_impl;
    typedef boost::scoped_ptr<transaction_command_impl> transaction_command_impl_type;
    transaction_command_impl_type m_impl;
};

