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

#pragma once

#include <wss/type.hpp>
#include "wss/define.hpp"


#include "wss/rectangle.hpp"
#include "wss/copy_format_from.hpp"
#include "wss/i_range_operation.hpp"
#include "wss/border_manager.hpp"
#include "wss/serialization_defines.hpp"
#include "wss/reference_counted_indexed_mapping.hpp"
#include "wss/key_value_manager.hpp"
#include "wss/border_types.hpp"
#include "wss/r_tree.hpp"
#include "wss/conditional_format_manager.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/scoped_ptr.hpp>
#   include <boost/thread/mutex.hpp>
#endif

#ifdef _DEBUG
//# define DEBUG_border_storage
#endif

class copy_fill_border_callback;
class auto_fill_border_callback;
class worksheet;

class border_storage
{
    friend class release_pooled_memory;
    static void release_memory( bool purge = false );
public:
    typedef border_types::type key_type;
    typedef std::pair<key_type, border_style_flyweight_type> border_index_type;
    typedef std::list< std::pair<geometry::rectangle_type, border_index_type> > get_border_list_type;
    typedef r::tree<border_index_type> container_type;
    typedef border_manager::undo_list_type undo_list_type;

public:
    border_storage();

    ~border_storage();

    void border( const sheet_range& rect, const long border_type, const border_style_flyweight_type& border_style );

    void border( const sheet_range& rect, const ::border& b, const bool overwrite_only_if_darker = false );

    const border_vec_type border( const sheet_range& rect, const cf::cf_vec_type& cf_vec, bool add_surrounding_borders = false, bool simple_mode = false, bool add_inside_borders = true  );

    void copy( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, insert_shift_direction::type /*shift*/ /*= insert_shift_direction::automatic*/ );

    void copy_fill( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet );

    void move( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, copy_format_from::type format_from = copy_format_from::left_or_above, insert_shift_direction::type shift = insert_shift_direction::automatic );

    void erase( const sheet_range& source_range, erase_shift_direction::type /*shift*/ = erase_shift_direction::automatic );

    optional_sheet_range_type used_range() const;

    undo_list_type get_list_for_undo( const sheet_range& r );

    void apply_list_for_undo( const sheet_range& r, const undo_list_type& undo_list );

public:
    void dump() const;

private:
    container_type m_container;
};
