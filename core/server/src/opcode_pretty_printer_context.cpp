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
#include "wss/opcode_pretty_printer_context.hpp"
#include "wss/translation_table.hpp"

opcode_pretty_printer_context::opcode_pretty_printer_context( const positioned_op_codes& c, const shared_dependency_type& current, const ::locale& l, bool resolve_named_formulas /* = false */, const bool always_add_sheet_references /* = true */ )
    : m_code( c )
    , m_current( current )
    , m_active_translation_map( *translation_table::instance()[l] )
    , m_resolve_named_formulas( resolve_named_formulas )
    , m_always_add_sheet_references( always_add_sheet_references )
{}

opcode_pretty_printer_context::opcode_pretty_printer_context( const positioned_op_codes& c, const shared_dependency_type& current, const ::locale& l, const shared_dependency_type& d, bool resolve_named_formulas /* = false */, const bool always_add_sheet_references /* = false */ )
    : m_code( c )
    , m_current( current )
    , m_active_translation_map( *translation_table::instance()[l] )
    , m_initiator( d )
    , m_resolve_named_formulas( resolve_named_formulas )
    , m_always_add_sheet_references( always_add_sheet_references )
{

}
const positioned_op_codes& opcode_pretty_printer_context::code() const
{
    return m_code;
}

const shared_dependency_type& opcode_pretty_printer_context::current() const
{
    return m_current;
}

const ::translation_map& opcode_pretty_printer_context::active_translation() const
{
    return m_active_translation_map;
}

bool opcode_pretty_printer_context::resolve_named_formulas() const
{
    return m_resolve_named_formulas;
}

bool opcode_pretty_printer_context::initiator_given() const
{
    return m_initiator;
}

const shared_dependency_type& opcode_pretty_printer_context::initiator() const
{
    assert( "initiator not given, but now we want to have it.. thats not the way it works!" && m_initiator );
    return m_initiator;
}
