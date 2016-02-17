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

#include <wss/base_node.hpp>
#include <wss/named_formula_reference.hpp>
#include <wss/reference_base_node.hpp>
#include <wss/opcode.hpp>

class locale;

/*!
 * \brief
 * node class for named formulas
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class named_formula_node
    : public base_node
    , public reference_base_node
{
    friend class memory::pooled_creator<named_formula_node>;
public:
    typedef opcode::opcode_string_type string_type;

    DESTROY_CLONE_VISIT( named_formula_node );

    static auto_type create( named_formula_scope::type scope, const weak_worksheet_type& ws, const std::string& workbook, const std::string& worksheet, const std::string& name );

    void name( const std::string& name );

    const string_type& name() const;

    const string_type& formula( const locale& l, const sheet_point& position ) const;

    named_formula_scope::type scope() const;

private:
    named_formula_node( named_formula_scope::type scope, const weak_worksheet_type& ws, const std::string& workbook, const std::string& worksheet, const std::string& name );

private:
    string_type m_name;
    named_formula_scope::type m_scope;
};
