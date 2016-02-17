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
#include <wss/shift_direction.hpp>
#include <wss/copy_format_from.hpp>
#include <wss/type.hpp>
#include <wss/reference_counted_indexed_mapping.hpp>

template<class value_T>
struct default_undo_type_trait {
    //needed for undo
    typedef reference_counted_indexed_mapping<value_T> value_mapping_type;
    typedef typename value_mapping_type::index_type index_type;
    typedef typename std::pair<sheet_range, index_type> kv_pair_type;
    typedef typename std::list<kv_pair_type> kv_pair_list_type;
    typedef kv_pair_list_type undo_list_type;
};

/*!
 * \brief
 * value manager.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template < class value_T, class undo_traits_T = default_undo_type_trait<value_T> >
class value_manager
    : public undo_traits_T
{
    friend class release_pooled_memory;
    static void release_memory( bool purge = false );
public:
    using typename undo_traits_T::value_mapping_type;
    using typename undo_traits_T::index_type;
    using typename undo_traits_T::kv_pair_type;
    using typename undo_traits_T::kv_pair_list_type;
    typedef typename undo_traits_T::kv_pair_list_type undo_list_type;

    typedef value_T value_type;
    typedef boost::optional<value_type> optional_value_type;
    typedef value_manager<value_T, undo_traits_T> self_type;
    typedef std::list<sheet_range> list_all_list_type;

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    value_manager();

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~value_manager();

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
    optional_value_type get( const sheet_point& p ) const;

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
    typename undo_traits_T::undo_list_type get_list_for_undo( const sheet_range& r ) const;

    /*!
    * \brief
    * applies an undo list to a given range
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void apply_list_for_undo( const sheet_range& r, const undo_list_type& undo_list );

    /*!
     * \brief
     * list all - there is an overload for bool that works!
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    inline list_all_list_type list_all() const {
        return list_all_list_type();
    }

protected:
    struct value_manager_impl;
    typedef boost::scoped_ptr<value_manager_impl> value_manager_impl_type;
    typedef boost::recursive_mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;
    mutable mutex_type m_mutex;
    value_manager_impl_type m_impl;
};
