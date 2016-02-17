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
#include <wss/define.hpp>

#include <wss/friend.hpp>
#include <wss/border_types.hpp>
#include <wss/shift_direction.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/scoped_ptr.hpp>
#   include <boost/thread/mutex.hpp>
#endif
#include <wss/copy_format_from.hpp>

#ifdef _DEBUG
//# define DEBUG_BORDER_MANAGER
#endif


class border_storage;
class border_locked_storage;
class worksheet;
class range;
class set_border_command;

class WSS_MODULE border_manager
{
    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;

    typedef border_storage storage_type;

    FRIEND_CLASS border_locked_storage;
    FRIEND_CLASS range;
    FRIEND_CLASS worksheet;
    FRIEND_CLASS set_border_command;
    FRIEND_CLASS border_storage;

    typedef std::pair<sheet_range, ::border> kv_pair_type;

public:
    void border( const sheet_range& rect, const long border_type, const std::string& border_style, const bool overwrite_only_if_darker = false );

    void border( const sheet_range& rect, const long border_type, const border_style_flyweight_type& border_style, const bool overwrite_only_if_darker = false );

    void border( const sheet_range& rect, const ::border& b, const bool overwrite_only_if_darker = false );

    const border_vec_type border( const sheet_range& rect, const cf::cf_vec_type& cf_vec, bool add_surrounding_borders = false, bool simple_mode = false, bool add_inside_borders = true ) const;

    optional_sheet_range_type used_range() const;

    virtual ~border_manager();

private:

    border_manager();

    void erase( const sheet_range& source_range, erase_shift_direction::type shift = erase_shift_direction::automatic );

    void copy( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, insert_shift_direction::type shift = insert_shift_direction::automatic );

    void copy_fill( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet );

    void move( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, copy_format_from::type format_from = copy_format_from::left_or_above, insert_shift_direction::type shift = insert_shift_direction::automatic );

    typedef border_types::type key_type;
    typedef std::pair<key_type, border_style_flyweight_type> border_index_type;
    typedef std::list< std::pair< geometry::rectangle_type, border_index_type> > undo_list_type;

    /*!
     * \brief
     * get information for undo functionality
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    undo_list_type get_list_for_undo( const sheet_range& r ) const;

    /*!
     * \brief
     * apply information for undo functionality
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void apply_list_for_undo( const sheet_range& r, const undo_list_type& undo_list );

public:
#ifdef _DEBUG
    void dump() const;
#endif // _DEBUG

private:
    border_storage& get_store( lock_type& );

private:
    mutable mutex_type m_mutex;
    boost::scoped_ptr<border_storage> m_storage;
};
