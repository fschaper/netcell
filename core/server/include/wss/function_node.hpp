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

#include <wss/function_entry.hpp>
#include <wss/function_registry.hpp>
#include <wss/opcode.hpp>

#include <wss/base_node.hpp>


/*!
 * \brief
 * function node
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE function_node
    : public base_node
{
    friend class memory::pooled_creator<function_node>;
public:
    typedef opcode::opcode_string_type string_type;

    DESTROY_CLONE_VISIT( function_node );

    static auto_type create( const std::string& f );

    bool is_valid() const;

    bool is_volatile() const;

    bool is_view_independent() const;

    bool executes_on_set() const;

    const string_type& function_name() const;

    virtual bool lazy_evaluation() const;

    ::function_entry& function_entry();

private:
    function_node( const std::string& function_name );

private:
    string_type m_function_name;
    bool m_lazy_evaluation;
    bool m_view_independent;
    bool m_execute_on_set;
    boost::optional< ::function_entry& > m_function_entry;
};
