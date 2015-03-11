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

#include "wss/define.hpp"

class addition_node;
class array_row_node;
class array_node;
class boolean_false_node;
class boolean_true_node;
class brace_node;
class concatenation_node;
class digit_node;
class string_node;
class division_node;
class empty_node;
class equal_node;
class error_node;
class exponent_node;
class function_node;
class greater_equal_node;
class greater_node;
class greater_node;
class less_equal_node;
class less_node;
class multiplication_node;
class named_formula_node;
class negation_node;
class not_equal_node;
class percentage_node;
class range_node;
class root_node;
class subtraction_node;
class variable_node;
class reference_list_node;
class function_call_up_node;
class function_call_down_node;

/*!
 * \brief
 * interface for visitor implementations.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class i_visitor
{
public:
    virtual ~i_visitor() {}

    virtual void visit( addition_node& ) = 0;
    virtual void visit( array_row_node& ) = 0;
    virtual void visit( array_node& ) = 0;
    virtual void visit( boolean_false_node& ) = 0;
    virtual void visit( boolean_true_node& ) = 0;
    virtual void visit( brace_node& ) = 0;
    virtual void visit( concatenation_node& ) = 0;
    virtual void visit( digit_node& ) = 0;
    virtual void visit( string_node& ) = 0;
    virtual void visit( division_node& ) = 0;
    virtual void visit( empty_node& ) = 0;
    virtual void visit( equal_node& ) = 0;
    virtual void visit( error_node& ) = 0;
    virtual void visit( exponent_node& ) = 0;
    virtual void visit( function_node& ) = 0;
    virtual void visit( greater_equal_node& ) = 0;
    virtual void visit( greater_node& ) = 0;
    virtual void visit( less_equal_node& ) = 0;
    virtual void visit( less_node& ) = 0;
    virtual void visit( multiplication_node& ) = 0;
    virtual void visit( named_formula_node& ) = 0;
    virtual void visit( negation_node& ) = 0;
    virtual void visit( not_equal_node& ) = 0;
    virtual void visit( percentage_node& ) = 0;
    virtual void visit( range_node& ) = 0;
    virtual void visit( root_node& ) = 0;
    virtual void visit( subtraction_node& ) = 0;
    virtual void visit( variable_node& ) = 0;
    virtual void visit( reference_list_node& ) = 0;
    virtual void visit( function_call_up_node& ) = 0;
    virtual void visit( function_call_down_node& ) = 0;
};

