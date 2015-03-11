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

#include <wss/conditional_format_manager.hpp>
#include "conditional_format_storage.hpp"
#include <wss/style_set.hpp>
#include "conditional_format_rule.hpp"
#include <wss/worksheet.hpp>
#include <wss/workbook.hpp>
#include "conditional_format_locked_storage.hpp"
#include "border_utility.hpp"
#include "border.hpp"

conditional_format_manager::conditional_format_manager( worksheet& ws )
    : m_mutex()
    , m_storage()
    , m_parent_ws( ws )
{
    m_storage.reset( new cf::conditional_format_storage( *this ) );
}

conditional_format_manager::~conditional_format_manager()
{}

void conditional_format_manager::add( session& s, const set_conditional_format& cf_format, bool relative/* = true*/ )
{
    lock_type lock( m_mutex );

    m_storage->insert( s, cf_format, parent( lock ).parent()->get_next_cf_id(), m_parent_ws.shared_from_this(), cf_format.position(), relative );
}

void conditional_format_manager::update( session& s, const conditional_format_lookup_id_type id, const set_conditional_format& cf_format )
{
    lock_type lock( m_mutex );
    m_storage->update( s, id, cf_format, m_parent_ws.shared_from_this(), cf_format.position() );
}

void conditional_format_manager::erase( session& s, const sheet_range::rectangles_type& ranges, const id_list_type& ids )
{
    lock_type lock( m_mutex );
    m_storage->external_remove( s, ranges, ids );
}

void conditional_format_manager::erase( session& s, const sheet_range& range )
{
    lock_type lock( m_mutex );
    sheet_range::rectangles_type ranges;
    ranges.push_back( range );
    m_storage->remove( s, ranges );
}

worksheet& conditional_format_manager::parent()
{
    lock_type lock( m_mutex );
    return parent( lock );
}

worksheet& conditional_format_manager::parent( lock_type& )
{
    return m_parent_ws;
}

cf::cf_vec_type conditional_format_manager::match( session& s, const sheet_range& range, const conditional_format_query_type query_type /* = query_conditional_format_all */ ) const
{
    lock_type lock( m_mutex );
    return m_storage->match( s, range, query_type );
}

get_conditionalformat_list_type conditional_format_manager::get( session& s, const sheet_range::rectangles_type& ranges ) const
{
    lock_type lock( m_mutex );
    return m_storage->get( s, ranges );
}

void conditional_format_manager::get( get_conditionalformat_list_type& return_val, session& s, const bool solve_formulas /* = false */ ) const
{
    lock_type lock( m_mutex );
    m_storage->get( return_val, s, solve_formulas );
}

void conditional_format_manager::move( session& s, const sheet_range& source, const sheet_point& target, const shared_worksheet_type& target_ws )
{
    lock_type lock( m_mutex );
    if ( target_ws && ( *target_ws != parent( lock ) ) ) {
        m_storage->move( s, source, target, target_ws );
    } else {
        if ( source.upper_left() == target ) {
            return;
        }
        m_storage->move( s, source, target );
    }
}

void conditional_format_manager::copy( session& s, const sheet_range& source, const sheet_range& target, const shared_worksheet_type& target_ws, const bool use_copy_move /* = false */ )
{
    lock_type lock( m_mutex );
    if ( target_ws && ( *target_ws != parent( lock ) ) ) {
        m_storage->copy( s, source, target, parent( lock ).parent(), target_ws, use_copy_move );
    } else {
        if ( source == target ) {
            return;
        }
        m_storage->copy( s, source, target, parent( lock ).parent(), shared_worksheet_type(), use_copy_move );
    }
}

cf::conditional_format_storage& conditional_format_manager::get_store( lock_type& )
{
    return *m_storage;
}

void conditional_format_manager::move_up( session& s, const conditional_format_lookup_id_type id, const sheet_range::rectangles_type& selected_region )
{
    lock_type lock( m_mutex );
    m_storage->move_up( s, id, selected_region );
}

void conditional_format_manager::move_down( session& s, const conditional_format_lookup_id_type id, const sheet_range::rectangles_type& selected_region )
{
    lock_type lock( m_mutex );
    m_storage->move_down( s, id, selected_region );
}

optional_sheet_range_type conditional_format_manager::used_range() const
{
    lock_type lock( m_mutex );
    return m_storage->used_range();
}
