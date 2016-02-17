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
#include "wss/interpreter_variant.hpp"
#include "wss/range.hpp"
#include "wss/range_reference.hpp"

interpreter_variant::interpreter_variant( const variant& v )
    : variant( v )
    , m_value_type( type_value )
{}

interpreter_variant::interpreter_variant( const variant& v, const shared_reference_type& cr )
    : variant( v )
    , m_reference( cr )
    , m_value_type( cr->type() ==  i_dependency_reference::named_formula_reference ? type_named_formula
                    : type_range )
{}

interpreter_variant::interpreter_variant( const interpreter_variant& other )
    : variant( other )
    , m_reference( other.m_reference )
    , m_value_type( other.m_value_type )
{}

interpreter_variant::~interpreter_variant()
{}

interpreter_variant::interpreter_variant_type interpreter_variant::i_type() const
{
    return m_value_type;
}

bool interpreter_variant::is_value() const
{
    return type_value == m_value_type;
}

bool interpreter_variant::is_range() const
{
    return type_range == m_value_type;
}

bool interpreter_variant::is_named_formula() const
{
    return type_named_formula == m_value_type;
}

shared_reference_type interpreter_variant::reference() const
{
    return m_reference;
}

