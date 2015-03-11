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
#include <wss/worksheet_element.hpp>

/*!
 * \brief
 * get worksheet elements
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class WSS_MODULE get_worksheet_elements_command
    : public base_command<i_command>
{
public:
    typedef worksheet_element::key_vec_type key_vec_type;
    typedef key_vec_type id_vec_type;
    typedef worksheet_element::key_value_vector_vector_type key_value_vector_vector_type;
    typedef worksheet_element::key_value_vector_type key_value_vector_type;
    typedef const worksheet_element::key_value_vector_vector_type& result_type;

    get_worksheet_elements_command( session& s, const std::string& ws_id, const id_vec_type& ws_elem_ids, const key_vec_type& keys, const key_value_vector_type& vals, const bool wb_scope = false );

    /*!
     * \brief
     * execute the command functionality.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual void execute();

    result_type value() const;

    DECLARE_CLONEABLE( get_worksheet_elements_command );
private:

    weak_worksheet_type m_ws;
    weak_workbook_type m_wb;
    id_vec_type m_ids;
    key_vec_type m_keys;
    key_value_vector_type m_vals;
    worksheet_element::key_value_vector_vector_type m_cached_value;
    bool m_wb_scope;
};

