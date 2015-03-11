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
#include "wss/function_entry.hpp"

function_entry::function_entry( extension_function callback, const utf8_ci_string& name, const std::string& argument_mask, bool is_volatile /*= false*/, bool is_lazy /*= false */, bool need_view_independent_calculation /*= false*/, bool execute_on_set/* = false*/, return_type_format::type return_type  )
    : m_callback( callback )
    , m_name( to_upper_copy_utf8( name ) )
    , m_argument_mask( argument_mask )
    , m_is_volatile( is_volatile )
    , m_is_lazy( is_lazy )
    , m_is_view_independent( need_view_independent_calculation )
    , m_execute_on_set( execute_on_set )
    , m_return_type( return_type )
{}

