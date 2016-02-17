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
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/named_formula_node.hpp"

named_formula_node::named_formula_node( named_formula_scope::type scope, const weak_worksheet_type& ws, const std::string& workbook, const std::string& worksheet, const std::string& name )
    : reference_base_node( ws, workbook, worksheet )
    ,  m_name( name )
    ,  m_scope( scope )
{}

named_formula_node::auto_type named_formula_node::create( named_formula_scope::type scope, const weak_worksheet_type& ws, const std::string& workbook, const std::string& worksheet, const std::string& name )
{
    return auto_type( memory::pooled_creator<named_formula_node>::create( scope, ws, workbook, worksheet, name ) );
}

void named_formula_node::name( const std::string& name )
{
    m_name = string_type( name );
}

const named_formula_node::string_type& named_formula_node::name() const
{
    return m_name;
}

const named_formula_node::string_type& named_formula_node::formula( const locale& l, const sheet_point& position ) const
{
    return m_name;
}

named_formula_scope::type named_formula_node::scope() const
{
    return m_scope;
}
