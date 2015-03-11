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

/*!
 * \brief
 * execute the command and return the result of the operation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 *
 * \see
 * execute_fetch
 */
template < class command_T, class result_T = typename command_T::result_type >
struct execute_command
{
    typedef result_T result_type;

    result_type operator()( command_T& cmd ) {
        cmd.execute();
        return cmd.value();
    }
};

/*!
 * \brief
 * overload for commands that do not have a result value.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 *
 * \see
 * execute_fetch
 */
template<class command_T>
struct execute_command<command_T, void> {
    typedef void result_type;

    void operator()( command_T& cmd ) {
        cmd.execute();
    }
};

/*!
 * \brief
 * execute command and return the result value (if any)
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class command_T>
typename command_T::result_type execute_fetch( command_T& cmd )
{
    execute_command<command_T> ex;
    return ex( cmd );
}


