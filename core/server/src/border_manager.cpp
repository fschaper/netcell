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
#include "wss/border_manager.hpp"

#include "border_locked_storage.hpp"
#include "border.hpp"

#include "border_storage.hpp"
#include "wss/worksheet.hpp"
#include "wss/rectangle.hpp"
#include "wss/copy_format_from.hpp"
#include "wss/border_types.hpp"
#include "wss/shift_direction.hpp"

border_manager::border_manager()
    : m_mutex()
{
    m_storage.reset( new border_storage() );
}

border_manager::~border_manager()
{}

const border_vec_type border_manager::border( const sheet_range& rect, const cf::cf_vec_type& cf_vec, bool add_surrounding_borders /* = false */, bool simple_mode /* = false */, bool add_inside_borders /* = true */ ) const
{
    lock_type lock( m_mutex );
    return m_storage->border( rect, cf_vec, add_surrounding_borders, simple_mode, add_inside_borders );
}

void border_manager::border( const sheet_range& rect, const ::border& b, const bool overwrite_only_if_darker /* = false */ )
{
    lock_type lock( m_mutex );
    m_storage->border( rect, b, overwrite_only_if_darker );
}

void border_manager::border( const sheet_range& rect, const long border_type, const border_style_flyweight_type& border_style, const bool overwrite_only_if_darker /* = false */ )
{
    border( rect, ::border( border_type, border_style ), overwrite_only_if_darker );
}

void border_manager::border( const sheet_range& rect, const long border_type, const std::string& border_style, const bool overwrite_only_if_darker /* = false */ )
{
    border( rect, border_type, border_style_flyweight_type( border_style ), overwrite_only_if_darker );
}

void border_manager::move( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, copy_format_from::type format_from /*= copy_format_from::left_or_above*/, insert_shift_direction::type shift /*= insert_shift_direction::automatic */ )
{
    lock_type lock( m_mutex );
    m_storage->move( source_range, target_range, target_sheet, format_from, shift );
}

void border_manager::erase( const sheet_range& source_range, erase_shift_direction::type shift /* = erase_shift_direction::automatic */ )
{
    lock_type lock( m_mutex );
    m_storage->erase( source_range, shift );
}

void border_manager::copy( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, insert_shift_direction::type shift /*= insert_shift_direction::automatic */ )
{
    lock_type lock( m_mutex );
    m_storage->copy( source_range, target_range, target_sheet, shift );
}

optional_sheet_range_type border_manager::used_range() const
{
    lock_type lock( m_mutex );
    return m_storage->used_range();
}

void border_manager::copy_fill( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet )
{
    lock_type lock( m_mutex );
    return m_storage->copy_fill( source_range, target_range, target_sheet );
}

#if defined(_DEBUG) && defined(DEBUG_BORDER_MANAGER)
void border_manager::dump() const
{
    lock_type lock( m_mutex );
    m_storage->dump();
}
#endif

border_storage& border_manager::get_store( lock_type& )
{
    return *m_storage;
}

border_manager::undo_list_type border_manager::get_list_for_undo( const sheet_range& r ) const
{
    lock_type lock( m_mutex );
    return m_storage->get_list_for_undo( r );
}

void border_manager::apply_list_for_undo( const sheet_range& r, const undo_list_type& undo_list )
{
    lock_type lock( m_mutex );
    m_storage->apply_list_for_undo( r, undo_list );
}
