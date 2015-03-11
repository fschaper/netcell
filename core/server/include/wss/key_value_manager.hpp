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

#include <wss/sheet_range.hpp>
#include <wss/i_range_operation.hpp>
#include <wss/used_range.hpp>
#include <wss/reference_counted_indexed_mapping.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/scoped_ptr.hpp>
#   include <boost/thread/recursive_mutex.hpp>
#   include <memory>
#endif

class worksheet;

/*!
 * \brief
 * key_value manager
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class value_T
>
class key_value_manager
{
    friend class release_pooled_memory;
    static void release_memory( bool purge = false );

public:
    typedef value_T value_type;
    typedef key_value_manager<value_T> self_type;

    //needed for undo
    typedef reference_counted_indexed_mapping<typename value_T::key_type> key_mapping_type;
    typedef reference_counted_indexed_mapping<typename value_T::value_type> value_mapping_type;
    typedef std::pair<typename key_mapping_type::index_type, typename value_mapping_type::index_type> index_type;
    typedef std::pair<geometry::rectangle_type, index_type> kv_pair_type;
    typedef std::list<kv_pair_type> kv_pair_list_type;
    typedef kv_pair_list_type undo_list_type ;

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    key_value_manager();

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~key_value_manager();

    /*!
     * \brief
     * sets the value information for an area on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void set( const sheet_range& area, const value_type& value );

    /*!
     * \brief
     * gets value information for a point on the sheet
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    value_type get( const sheet_point& p ) const;

    /*!
     * \brief
     * copy the source range value information to the target range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void copy( const sheet_range& source_range, const sheet_range& target_range, self_type& target, insert_shift_direction::type shift = insert_shift_direction::automatic );

    /*!
     * \brief
     * move the source range value information to the target range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void move( const sheet_range& source_range, const sheet_range& target_range, self_type& target, copy_format_from::type format_from = copy_format_from::left_or_above, insert_shift_direction::type shift = insert_shift_direction::automatic );

    /*!
     * \brief
     * erase the source range value information.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void erase( const sheet_range& area, erase_shift_direction::type shift = erase_shift_direction::automatic );

    /*!
     * \brief
     * used_range
     * return the used range on the worksheet.
     *
     * \return optional_sheet_range_type
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    optional_sheet_range_type used_range() const;

    /*!
    * \brief
    * returns an undo_list for a given range
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    undo_list_type get_list_for_undo( const sheet_range& r ) const;

    /*!
    * \brief
    * applies an undo list to a given range
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void apply_list_for_undo( const sheet_range& r, const undo_list_type& undo_list );

protected:
    struct key_value_manager_impl;
    typedef boost::scoped_ptr<key_value_manager_impl> key_value_manager_impl_type;
    typedef boost::recursive_mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;
    mutable mutex_type m_mutex;
    key_value_manager_impl_type m_impl;
};

