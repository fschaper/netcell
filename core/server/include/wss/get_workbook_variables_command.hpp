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

#include <wss/define.hpp>
#include <wss/base_command.hpp>
#include <wss/type.hpp>

/*!
 * \brief
 * get workbook variables
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class WSS_MODULE get_workbook_variables_command
    : public base_command<i_command>
{
public:
    typedef const variable_name_list_type& result_type;

    get_workbook_variables_command( session& s, const boost::filesystem::path& file_path  );

    /*!
     * \brief
     * execute the command functionality.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual void execute();

    /*!
     * \brief
     * get the result
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    result_type value() const;

    DECLARE_CLONEABLE( get_workbook_variables_command );

private:
    boost::filesystem::path m_file_path;
    variable_name_list_type m_value;
};

