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
#include <wss/variant.hpp>
#include <wss/type.hpp>

/*!
 * \brief
 * perform different queries against the server based on flags
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE get_server_query_command
    : public base_command<i_command>
{
public:
    typedef const variant& result_type;

    enum query_type {
        query_value = 1,
        query_formula = 2,
        query_style = 4,
        query_formula_where_exists = 8,
        query_attribute = 16,
        query_dimensions = 32,
        query_formatted_value = 64,
        query_format = 128,
        query_merge = 256,
        // this will return the formula inside the named formula
        query_formula_with_named_ranges = 512,
        query_lock = 1024,
        query_all = ( query_value | query_formula_where_exists | query_style | query_attribute | query_formatted_value | query_format | query_merge | query_formula_with_named_ranges )
    };

    get_server_query_command( session& s, const sheet_range& area, int query_flags );

    /*!
     * \brief
     * execute the command functionality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void execute();

    result_type value() const;

    DECLARE_CLONEABLE( get_server_query_command );

private:
    sheet_range m_area;
    int m_flags;
    variant m_result;
};

