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
 *
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class php_function_redirection_registry
    : public singleton<php_function_redirection_registry>
{
    friend class singleton<php_function_redirection_registry>;
public:
    /*!
     * \brief
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void register_function( const uuid_type& workbook_uuid
                            , const std::string& spreadsheet_function_name
                            , const boost::filesystem::path& filename
                            , const std::string& php_function_name
                            , bool is_volatile = false
                                                 , bool view_independent_calculation = false );

    void unregister_workbook( const uuid_type& uuid );

private:
    php_function_redirection_registry();
    ~php_function_redirection_registry();
private:
    friend class php_redirected_spreadsheet_function;
    const shared_function_handler_type& retreive( const uuid_type& workbook_uuid , const std::string& spreadsheet_function_name );
    void observe_workbook_deletion( const workbook& uuid );
private:
    typedef std::map<std::string, shared_function_handler_type> spreadsheet_function_name_to_handler_map_type;
    typedef std::map<const uuid_type, spreadsheet_function_name_to_handler_map_type> workbook_to_list_map_type;
    typedef locked_object<workbook_to_list_map_type, trait::boost_lock_trait< boost::recursive_mutex > > locked_workbook_to_list_map_type;

    locked_workbook_to_list_map_type m_container;
    boost::signals::connection workbook_delete_event_connection;
};

