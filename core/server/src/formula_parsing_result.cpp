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

#include "precompiled_header.hpp"
#include "wss/formula_parsing_result.hpp"
#include "wss/syntax.hpp"

formula_parsing_result::formula_parsing_result()
    : m_is_success( false )
    , m_has_volatile( false )
    , m_root( root_node::create() )
    , m_has_view_independent( false )
    , m_execute_on_set( false )
{}

formula_parsing_result::~formula_parsing_result()
{}

const variable_map& formula_parsing_result::variable() const
{
    return m_variable;
}

bool formula_parsing_result::is_success() const
{
    return m_is_success;
}

bool formula_parsing_result::has_volatile() const
{
    return m_has_volatile;
}

bool formula_parsing_result::view_independent() const
{
    return m_has_view_independent;
}

bool formula_parsing_result::executes_on_set() const
{
    return m_execute_on_set;
}

destroying_auto_pointer<base_node> formula_parsing_result::take_ownership() const
{
    return m_root;
}
