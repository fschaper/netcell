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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/define.hpp>
#include <wss/base_command.hpp>
#include <wss/type.hpp>
#include <wss/i_named_formula_manager.hpp>
#include <wss/session.hpp>
#include <wss/worksheet.hpp>

class variant;

/*!
 * \brief
 * add a named formula
 *
 * \param s sessioncontext
 *
 * \param name of the named formula
 *
 * \param formula
 *
 * \param scope_ws string with the name of the ws if scope is ws and "Workbook" if scope is workbook
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class WSS_MODULE create_named_formula_command
    : public base_command<i_command>
{
public:
    typedef i_named_formula_manager::key_val_vec_type result_type;
    typedef std::map< std::string, std::string > key_val_map_type;

    create_named_formula_command( session& s, const std::string& name, const variant& formula, const sheet_point& position = sheet_point( 0, 0 ), const std::string& comment = "" );

    create_named_formula_command( session& s, const std::string& name, const variant& formula, const uuid_type& sheet_id, const sheet_point& position = sheet_point( 0, 0 ), const std::string& comment = "" );

    //this constructor should take care of moving from core2 to core3
    create_named_formula_command( session& s, const key_val_map_type& k_v_map, const sheet_point& position /* = sheet_point */ );

    /*!
     * \brief
     * execute the command functionality.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual void execute();

    result_type value() const;

    DECLARE_CLONEABLE( create_named_formula_command );

private:

    std::string m_name;
    variant m_formula;
    named_formula_scope::type m_scope;
    weak_worksheet_type m_ws;
    std::string m_comment;
    const sheet_point m_position;
};

