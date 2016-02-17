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

#include "precompiled_header.hpp"
#include "release_pooled_memory.hpp"

#include "wss/syntax.hpp"
#include "wss/allocation.hpp"
#include "wss/style_manager.hpp"
#include "wss/format_manager.hpp"
#include "wss/attribute_manager.hpp"
#include "wss/locked_cell_manager.hpp"

#include "cell.hpp"
#include "border_storage.hpp"
#include "dependency_manager.hpp"
#include "conditional_format_storage.hpp"

void release_pooled_memory::free_node_memory( bool purge )
{
    memory::pooled_creator<addition_node>::release_memory( purge );
    memory::pooled_creator<array_row_node>::release_memory( purge );
    memory::pooled_creator<array_node>::release_memory( purge );
    memory::pooled_creator<boolean_false_node>::release_memory( purge );
    memory::pooled_creator<boolean_true_node>::release_memory( purge );
    memory::pooled_creator<brace_node>::release_memory( purge );
    memory::pooled_creator<concatenation_node>::release_memory( purge );
    memory::pooled_creator<digit_node>::release_memory( purge );
    memory::pooled_creator<division_node>::release_memory( purge );
    memory::pooled_creator<empty_node>::release_memory( purge );
    memory::pooled_creator<equal_node>::release_memory( purge );
    memory::pooled_creator<error_node>::release_memory( purge );
    memory::pooled_creator<exponent_node>::release_memory( purge );
    memory::pooled_creator<function_node>::release_memory( purge );
    memory::pooled_creator<greater_equal_node>::release_memory( purge );
    memory::pooled_creator<greater_node>::release_memory( purge );
    memory::pooled_creator<less_equal_node>::release_memory( purge );
    memory::pooled_creator<less_node>::release_memory( purge );
    memory::pooled_creator<multiplication_node>::release_memory( purge );
    memory::pooled_creator<named_formula_node>::release_memory( purge );
    memory::pooled_creator<negation_node>::release_memory( purge );
    memory::pooled_creator<not_equal_node>::release_memory( purge );
    memory::pooled_creator<percentage_node>::release_memory( purge );
    memory::pooled_creator<range_node>::release_memory( purge );
    memory::pooled_creator<root_node>::release_memory( purge );
    memory::pooled_creator<subtraction_node>::release_memory( purge );
    memory::pooled_creator<variable_node>::release_memory( purge );
    memory::pooled_creator<string_node>::release_memory( purge );
    memory::pooled_creator<reference_list_node>::release_memory( purge );
    memory::pooled_creator<function_call_up_node>::release_memory( purge );
    memory::pooled_creator<function_call_down_node>::release_memory( purge );
}

void release_pooled_memory::free_cell_memory( bool purge )
{
    cell::release_cell_memory( purge );
}

void release_pooled_memory::free_r_tree_memory( bool purge )
{
    style_manager_type::release_memory( purge );
    border_storage::release_memory( purge );
    locked_cell_manager_type::release_memory( purge );
    format_manager_type::release_memory( purge );
    dependency_manager::release_memory( purge );
    attribute_manager::release_memory( purge );
    cf::conditional_format_storage::release_memory( purge );
}

void release_pooled_memory::release_all( bool purge )
{
    free_node_memory( purge );
    free_cell_memory( purge );
    free_r_tree_memory( purge );
}
