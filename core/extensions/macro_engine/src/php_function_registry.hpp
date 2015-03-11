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

#include "i_php_function_wrapper.hpp"

#include <wss/singleton.hpp>
#include <wss/friend.hpp>
#include <wss/locked_object.hpp>


/*!
 * \brief
 * registry of all php spreadsheet functions
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class php_function_registry
    : public singleton<php_function_registry>
{
    FRIEND_CLASS singleton<php_function_registry>;
public:
    ~php_function_registry();

    /*!
     * \brief
     * register an php function with worksheetserver
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void register_function( const std::string& spreadsheet_function_name, const boost::filesystem::path& filename, const std::string& php_function_name, bool is_volatile = false, bool view_independent_calculation = false );

    /*!
     * \brief
     * register an php function with worksheetserver
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void register_function( const std::string& spreadsheet_function_name, const std::string& php_function_name, bool is_volatile = false, bool view_independent_calculation = false );

    /*!
     * \brief
     * returns true to the caller when the spreadsheet function is known.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool has_handler( const std::string& spreadsheet_function_name ) const;

private:
    friend class php_function_redirection_registry;
    /*!
     * \brief
     * registers a handler with the worksheetserver
     *
     * \throw
     * duplicate_handler_exception - if a handler by that name is already registered.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void register_handler( const std::string& spreadsheet_function_name, bool is_volatile, bool view_independent_calculation, const shared_function_handler_type& handler );

private:
    php_function_registry();

private:
    typedef std::map<std::string, shared_function_handler_type> container_type;
    typedef locked_object<container_type, trait::boost_lock_trait<> > locked_container_type;
    locked_container_type m_container;
};

