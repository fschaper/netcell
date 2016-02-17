/*!
 *  \file
 *  Copyright (C) 2006-2008 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
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
 *  Dragan Simic <dragan.simic@jedox.com>
 */

#ifndef _TASKS
# define _TASKS

//stl
#include <list>

// wss
#include <wss/define.hpp>
#include <wss/interpreter_variant.hpp>

// php_macro_engine
#include "i_task.hpp"

/*!
 * \brief
 * run custom php script from disk and calls back into php with two parameters
 *
 * wrapper which allows execution of a php script file on the disk followed by an
 * callback into the php code. the result of the function call is stored and
 * can be retrieved by "get_result".
 */
class php_eval_file_task_callback: public i_task
{
public:
    typedef std::list<interpreter_variant> task_arguments_list_type;

public:
    /*!
     * \brief
     * Constructor
     *
     * \param php_file_name
     * path to the php script file to be executed
     *
     * \param php_callback_function
     * name of the function in php that will be called
     *
     * \param parameter1
     * first parameter passed to the php function
     *
     * \param parameter2
     * second parameter passed to the php function
     */
    php_eval_file_task_callback( const std::string& php_file_name,
                                 const std::string& php_callback_function,
                                 const task_arguments_list_type& php_function_arguments );

    /*!
     * \brief
     * executes the php command.
     *
     * Parses the specified php file and executes it. After initial
     * execution the specified php callback function is called with
     * the parameters passed in the constructor. The result of the
     * callback is stored and can be retrieved with an call to
     * php_eval_file_task_callback::get_result()
     * repeated calls to operator()() will overwrite the previous result.
     *
     * \remarks
     * should only be called by PHPBridge::excecute_task()
     *
     * \see
     * PHPBridge::excecute_task | php_eval_file_task_callback::get_result
     */
    virtual void operator()() const;

    /*!
     * \brief
     * returns the result of an call to php_eval_file_task_callback::operator()()
     *
     * \returns
     * value returned by an call to the specified php callback function
     *
     * \remarks
     * repeated calls to operator()() will overwrite the previous result.
     *
     * \see
     * php_eval_file_task_callback::operator()
     */
    const interpreter_variant& get_result() const;

private:
    const std::string m_php_file_name;
    const std::string m_php_callback_function;
    const task_arguments_list_type m_arguments;
    mutable variant m_return_value;
};

#endif // _TASKS
