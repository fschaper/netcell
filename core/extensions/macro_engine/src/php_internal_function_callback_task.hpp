/*!
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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

#include "i_task.hpp"

#include <wss/interpreter_variant.hpp>
#include <string>
#include <list>

/*!
 * \brief
 * run internal php function with a variable number of parameters
 *
 * wrapper which allows execution of a php function.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class php_internal_function_callback_task
    : public i_task
{
public:
    typedef std::list<interpreter_variant> parameter_list_type;

public:
    /*!
     * \brief
     * Constructor
     *
     * \param php_callback_function
     * name of the function in php that will be called
     *
     * \param parameter1
     * first parameter passed to the php function
     *
     * \param parameter2
     * second parameter passed to the php function
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    php_internal_function_callback_task( const std::string& function_name
                                         , const parameter_list_type& parameters );

    /*!
     * \brief
     * executes the php function
     *
     * \remarks
     * should only be called by PHPBridge::excecute_task()
     *
     * \see
     * PHPBridge::excecute_task | PHPEvalFileCallbackTask::get_result
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void operator()() const;

    /*!
     * \brief
     * return the cached result
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const variant& result() const;

private:
    const std::string m_function_name;
    const parameter_list_type m_parameters;
    mutable variant m_result;
};

