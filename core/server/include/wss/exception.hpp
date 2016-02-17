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

// list worksheetserver runtime exceptions
#include <wss/wss_runtime_exception.hpp>
#include <wss/invalid_name_exception.hpp>
#include <wss/invalid_locale_exception.hpp>
#include <wss/object_not_found_exception.hpp>
#include <wss/position_out_of_range_exception.hpp>
#include <wss/invalid_worksheet_exception.hpp>
#include <wss/invalid_function_exception.hpp>
#include <wss/invalid_workbook_exception.hpp>
#include <wss/invalid_formula_exception.hpp>
#include <wss/can_not_change_part_of_an_array_exception.hpp>
#include <wss/lock_timeout_exception.hpp>
#include <wss/invalid_session_exception.hpp>
#include <wss/invalid_clipboard_entry_exception.hpp>
#include <wss/object_unloading_exception.hpp>
#include <wss/invalid_application_exception.hpp>
#include <wss/creation_exception.hpp>
#include <wss/not_implemented_exception.hpp>
#include <wss/can_not_change_merged_cell_exception.hpp>
#include <wss/extension_module_load_exception.hpp>
#include <wss/extension_function_call_failed_exception.hpp>
#include <wss/named_formula_exception.hpp>
#include <wss/worksheet_element_exception.hpp>
#include <wss/named_formula_not_found_exception.hpp>
#include <wss/invalid_translation_table_exception.hpp>
#include <wss/conditional_format_exception.hpp>
#include <wss/variant_conversion_exception.hpp>
#include <wss/translation_exception.hpp>
#include <wss/filter_exception.hpp>
#include <wss/export_exception.hpp>
#include <wss/import_exception.hpp>
#include <wss/filter_registry_exception.hpp>
#include <wss/vector_io_exception.hpp>
#include <wss/invalid_seek_exception.hpp>
#include <wss/no_buffer_assigned_exception.hpp>
#include <wss/stack_underflow_exception.hpp>
#include <wss/invalid_reference_exception.hpp>
#include <wss/fatal_exception.hpp>
//error codes of 0x003600 to 0x003800 are reserved for cell format
#include <wss/extension_registry_exception.hpp>
#include <wss/missing_text_metrics_exception.hpp>
#include <wss/arbitrary_storage_object_not_found_exception.hpp>
#include <wss/undo_chain_exception.hpp>
#include <wss/uninitialized_session_exception.hpp>
