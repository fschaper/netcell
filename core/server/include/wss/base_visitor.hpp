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

#include "i_visitor.hpp"

/*!
 * \brief
 * convenience base class for visitor objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class base_visitor
    : public i_visitor
{
public:
    virtual void visit( addition_node& ) {}
    virtual void visit( array_row_node& ) {}
    virtual void visit( array_node& ) {}
    virtual void visit( boolean_false_node& ) {}
    virtual void visit( boolean_true_node& ) {}
    virtual void visit( brace_node& ) {}
    virtual void visit( concatenation_node& ) {}
    virtual void visit( digit_node& ) {}
    virtual void visit( string_node& ) {}
    virtual void visit( division_node& ) {}
    virtual void visit( empty_node& ) {}
    virtual void visit( equal_node& ) {}
    virtual void visit( error_node& ) {}
    virtual void visit( exponent_node& ) {}
    virtual void visit( function_node& ) {}
    virtual void visit( greater_equal_node& ) {}
    virtual void visit( greater_node& ) {}
    virtual void visit( less_equal_node& ) {}
    virtual void visit( less_node& ) {}
    virtual void visit( multiplication_node& ) {}
    virtual void visit( named_formula_node& ) {}
    virtual void visit( negation_node& ) {}
    virtual void visit( not_equal_node& ) {}
    virtual void visit( percentage_node& ) {}
    virtual void visit( range_node& ) {}
    virtual void visit( root_node& ) {}
    virtual void visit( subtraction_node& ) {}
    virtual void visit( variable_node& ) {}
    virtual void visit( reference_list_node& ) {}
    virtual void visit( function_call_up_node& ) {}
    virtual void visit( function_call_down_node& ) {}

protected:
    base_visitor() {}
};

