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

#include <wss/command_chain.hpp>

#include <wss/get_server_version_command.hpp>

#include <wss/create_application_command.hpp>
#include <wss/create_workbook_command.hpp>
#include <wss/create_worksheet_command.hpp>
#include <wss/create_empty_workbook_command.hpp>

#include <wss/remove_application_command.hpp>
#include <wss/remove_workbook_command.hpp>
#include <wss/remove_worksheet_command.hpp>

#include <wss/select_application_command.hpp>
#include <wss/select_workbook_command.hpp>
#include <wss/select_worksheet_command.hpp>

#include <wss/rename_application_command.hpp>
#include <wss/rename_workbook_command.hpp>
#include <wss/rename_worksheet_command.hpp>

#include <wss/set_value_command.hpp>
#include <wss/set_array_value_command.hpp>
#include <wss/deactivate_array_formula_command.hpp>
#include <wss/get_value_command.hpp>
#include <wss/get_formula_command.hpp>
#include <wss/get_used_range_command.hpp>
#include <wss/get_precedents_command.hpp>
#include <wss/get_dependents_command.hpp>
#include <wss/get_server_query_command.hpp>
#include <wss/set_default_style_command.hpp>
#include <wss/get_default_style_command.hpp>
#include <wss/set_style_command.hpp>
#include <wss/get_style_command.hpp>
#include <wss/set_border_command.hpp>
#include <wss/set_attribute_command.hpp>

#include <wss/set_conditional_format_command.hpp>
#include <wss/get_conditional_format_command.hpp>
#include <wss/get_all_conditional_formats_command.hpp>
#include <wss/update_conditional_format_command.hpp>
#include <wss/move_conditional_format_rank_command.hpp>
#include <wss/remove_conditional_format_command.hpp>

#include <wss/create_named_formula_command.hpp>
#include <wss/get_named_formula_command.hpp>
#include <wss/get_all_named_formulas_command.hpp>
#include <wss/update_named_formula_command.hpp>
#include <wss/remove_named_formula_command.hpp>

#include <wss/update_worksheet_elements_command.hpp>
#include <wss/create_worksheet_element_command.hpp>
#include <wss/remove_worksheet_element_command.hpp>
#include <wss/get_worksheet_elements_command.hpp>

#include <wss/copy_range_command.hpp>
#include <wss/move_range_command.hpp>
#include <wss/paste_range_command.hpp>

#include <wss/copy_worksheet_command.hpp>
#include <wss/move_worksheet_command.hpp>
#include <wss/clone_worksheet_command.hpp>
#include <wss/remove_clone_worksheet_command.hpp>

#include <wss/get_default_column_width_command.hpp>
#include <wss/get_default_row_height_command.hpp>
#include <wss/get_sparse_column_width_command.hpp>
#include <wss/get_sparse_row_height_command.hpp>
#include <wss/get_default_sheet_dimensions_command.hpp>
#include <wss/set_default_column_width_command.hpp>
#include <wss/set_default_row_height_command.hpp>
#include <wss/get_sparse_max_cell_width_command.hpp>
#include <wss/get_sparse_max_cell_height_command.hpp>
#include <wss/set_column_width_command.hpp>
#include <wss/set_row_height_command.hpp>
#include <wss/save_workbook_command.hpp>
#include <wss/load_workbook_command.hpp>

#include <wss/merge_cells_command.hpp>
#include <wss/unmerge_cells_command.hpp>

#include <wss/insert_column_command.hpp>
#include <wss/delete_column_command.hpp>
#include <wss/insert_row_command.hpp>
#include <wss/delete_row_command.hpp>

#include <wss/get_formatted_value_command.hpp>
#include <wss/set_format_command.hpp>

#include <wss/start_new_calculation_command.hpp>

#include <wss/set_cell_lock_command.hpp>
#include <wss/get_cell_lock_list_command.hpp>
#include <wss/copy_fill_range_command.hpp>
#include <wss/copy_move_range_command.hpp>

#include <wss/clear_cells_command.hpp>
#include <wss/clear_attributes_command.hpp>

#include <wss/set_format_command.hpp>
#include <wss/get_border_command.hpp>
#include <wss/insert_cells_command.hpp>
#include <wss/delete_cells_command.hpp>
#include <wss/get_cell_lock_list_command.hpp>
#include <wss/clear_cells_command.hpp>
#include <wss/clear_attributes_command.hpp>
#include <wss/trigger_extension_module_command.hpp>

#include <wss/measure_text_command.hpp>
#include <wss/transaction_command.hpp>
#include <wss/active_workbook_has_changes_command.hpp>

#include <wss/get_workbook_variables_command.hpp>
#include <wss/get_workbook_version_command.hpp>
#include <wss/get_default_format_command.hpp>
#include <wss/set_default_format_command.hpp>
