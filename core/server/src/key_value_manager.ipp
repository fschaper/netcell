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

#include "wss/key_value_manager.hpp"
#include "wss/key_value_set.hpp"
#include "wss/not_implemented_exception.hpp"
#include "wss/reference_counted_indexed_mapping.hpp"
#include "wss/r_tree.hpp"
#include "wss/locked_object.hpp"
#include "copy_fill_iterator.hpp"

/*!
 * \brief
 * callback class to receive value information from
 * the rectangle_container.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class index_T>
class node_lookup_callback
{
public:
    typedef index_T index_type;
    typedef std::pair<geometry::rectangle_type, index_type> pair_type;
    typedef std::list<pair_type> node_list_type;
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    node_lookup_callback( node_list_type& s )
        : m_node_list( s ) {}

    /*!
     * \brief
     * for every matching node, collect coverage and index value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator()( const r::r_tree_rectangle_type& r, const index_type& i ) {
        m_node_list.push_back( std::make_pair( r, i ) );
        return true;
    }

private:
    node_list_type& m_node_list;
};

/*!
 * \brief
 * callback class to receive value information from
 * the rectangle_container.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class index_T>
class node_lookup_by_key_callback
{
public:
    typedef index_T index_type;
    typedef std::set<typename index_type::first_type> key_set_type;
    typedef std::pair<geometry::rectangle_type, index_type> pair_type;
    typedef std::list<pair_type> node_list_type;
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    node_lookup_by_key_callback( const key_set_type& keys, node_list_type& s )
        : m_node_list( s )
        , m_keys_to_find( keys ) {}

    /*!
     * \brief
     * for every node whose key matches one of the search keys collect
     * the node information.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator()( const r::r_tree_rectangle_type& r, const index_type& i ) {
        if ( m_keys_to_find.find( i.first ) != m_keys_to_find.end() ) {
            m_node_list.push_back( std::make_pair( r, i ) );
        }
        return true;
    }

private:
    node_list_type& m_node_list;
    const key_set_type& m_keys_to_find;
};

/*!
 * \brief
 * erase callback.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class index_T>
struct erase_all_callback {
    typedef index_T index_type;
    bool operator()( const r::r_tree_rectangle_type& r, const index_type& ) const {
        return true;
    }
};

/*!
 * \brief
 * erase by key callback.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class index_T>
class erase_by_key_callback
{
public:
    typedef index_T index_type;
    typedef std::set<typename index_type::first_type> key_set_type;

    erase_by_key_callback( const key_set_type& keys_to_erase )
        : m_keys_to_erase( keys_to_erase ) {}

    bool operator()( const r::r_tree_rectangle_type& r, const index_type& i ) const {
        return m_keys_to_erase.find( i.first ) != m_keys_to_erase.end();
    }

private:
    const key_set_type& m_keys_to_erase;
};

/*!
 * \brief
 * private implementation file as a compiler firewall.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class value_T>
struct key_value_manager<value_T>::key_value_manager_impl {
    // mapping of keys to indexes (f.ex. background-color, color, border, ...)
    typedef reference_counted_indexed_mapping<typename value_T::key_type> key_mapping_type;
    // mapping of values to indexes (f.ex. blue, #00ff00, solid 1px black, ...)
    typedef reference_counted_indexed_mapping<typename value_T::value_type> value_mapping_type;
    // combination of key and value indexes
    typedef std::pair<typename key_mapping_type::index_type, typename value_mapping_type::index_type> index_pair_type;
    // r-tree which holds the coverage information for a key/value pair
    typedef r::tree<index_pair_type> lookup_container_type;

    // (fschaper) the order of initialization (better destruction) is important for
    // the key_map, m_value_map and the lookup_container.get since the lookup_container
    // holds handles to the key_map and m_value_map it needs to be destroyed first.
    key_mapping_type m_key_map;
    value_mapping_type m_value_map;
    lookup_container_type m_lookup_container;
};

template<class value_T>
key_value_manager<value_T>::key_value_manager()
    : m_mutex()
    , m_impl( new key_value_manager_impl() )
{}

template<class value_T>
key_value_manager<value_T>::~key_value_manager()
{}

template<class value_T>
void key_value_manager<value_T>::set( const sheet_range& area, const value_type& value )
{
    lock_type lock( m_mutex );

    typedef typename key_value_manager_impl::index_pair_type index_pair_type;
    typedef typename erase_by_key_callback<index_pair_type>::key_set_type erase_key_set_type;

    // collect all keys we are about to set in the passed area in the erase_key_set
    erase_key_set_type erase_key_set;
    {
        foreach( const typename value_T::pair_type & p, value ) {
            erase_key_set.insert( m_impl->m_key_map.set( p.first ) );
        }
    }

    // erase all nodes that match the collected keys from the area.
    // we will reinsert them with their intersection with 'area' removed.
    {
        typedef typename node_lookup_by_key_callback<index_pair_type>::node_list_type node_list_type;
        node_list_type node_list;
        node_lookup_by_key_callback<index_pair_type> query_callback( erase_key_set, node_list );

        // query all nodes and values that intersect with the area to be deleted and
        // contain matching keys
        m_impl->m_lookup_container.query( area, query_callback );

        // erase the nodes with the matching keys from the lookup container
        erase_by_key_callback<index_pair_type> erase_callback( erase_key_set );
        m_impl->m_lookup_container.remove( area, erase_callback );

        // insert all nodes back into tree with their intersection removed.
        foreach( const typename node_list_type::value_type & current_node, node_list ) {
            foreach( const sheet_range & insert_rect, current_node.first.cut( area ) ) {
                m_impl->m_lookup_container.insert( insert_rect, current_node.second );
            }
        }
    }

    // insert the new information
    {
        foreach( const typename value_type::pair_type & p, value ) {
            m_impl->m_lookup_container.insert( area, std::make_pair( m_impl->m_key_map.set( p.first ), m_impl->m_value_map.set( p.second ) ), true );
        }
    }

}

template<class value_T>
typename key_value_manager<value_T>::value_type key_value_manager<value_T>::get( const sheet_point& p ) const
{
    typedef typename key_value_manager_impl::index_pair_type index_pair_type;
    typename node_lookup_callback<index_pair_type>::node_list_type node_list;

    node_lookup_callback<index_pair_type> query_callback( node_list );
    {
        lock_type lock( m_mutex );
        m_impl->m_lookup_container.query( geometry::rectangle_type( p ), query_callback );
    }

    // re-create the key_value set by adding each separate node value back to
    // the return value.
    value_T return_value;
    foreach( const typename node_lookup_callback<index_pair_type>::pair_type & v, node_list ) {
        return_value.add( m_impl->m_key_map[ v.second.first ], m_impl->m_value_map[ v.second.second ] );
    }
    return return_value;
}

template<class value_T>
void key_value_manager<value_T>::copy( const sheet_range& source_range, const sheet_range& target_range, self_type& target, insert_shift_direction::type shift /*= insert_shift_direction::automatic */ )
{
    typedef typename key_value_manager_impl::index_pair_type index_pair_type;
    typename node_lookup_callback<index_pair_type>::node_list_type node_list;
    const sheet_range local_target = target_range.enclose( source_range.checked_offset( source_range.distance( target_range ) ) );

    node_lookup_callback<index_pair_type> query_node_callback( node_list );
    {
        lock_type lock( m_mutex );

        // the lookup callback will create a copy of all nodes in the source_range region
        m_impl->m_lookup_container.query( source_range, query_node_callback );
        // since we already have a copy of all nodes in the source range (the node_list)
        // we can simply erase the complete target range.
        target.erase( local_target );

        copy_fill_iterator it( source_range, local_target );
        // loop through all nodes that intersect with the source area
        foreach( const typename node_lookup_callback<index_pair_type>::pair_type & current_node, node_list ) {
            it.reset();
            // for every node that intersects with the source area determine the covered (selected) area
            // by intersection (the area covered by the node and the selection).
            const sheet_range affected_range( current_node.first.intersection( source_range ) );
            // set the new value in the target area.
            // the selected area (the area where the node coverage intersects with the users selection) is moved to the
            // upper left point of the target range. then we apply a offset to determine the sector that is currently
            // filled in case the target range is a multiple of the source range (current_row_multiplier/current_column_multiplier).
            // then we add a last offset to maintain the distance the intersecting region has from the upper left of the source range.
            value_T set_type;
            set_type.add( m_impl->m_key_map[ current_node.second.first ], m_impl->m_value_map[ current_node.second.second ] );
            const std::list<sheet_range> target_list( it.whole_target_area( affected_range ) );
            for ( std::list<sheet_range>::const_iterator current_target_it = target_list.begin(), end_it = target_list.end(); current_target_it != end_it; ++current_target_it ) {
                target.set( *current_target_it , set_type );
            }
        }
    }
}

template<class value_T>
void key_value_manager<value_T>::move( const sheet_range& source_range, const sheet_range& target_range, self_type& target, copy_format_from::type format_from /* = copy_format_from::left_or_above */, insert_shift_direction::type shift /* = insert_shift_direction::automatic */ )
{
    copy( source_range, source_range.coverage().checked_offset( target_range.upper_left() ), target, shift );
    // remove all regions from the source range that do not overlap with the target range
    if ( &target != this ) {
        // in case the target of the move operation is on another sheet
        // we have to remove the whole source region.
        erase( source_range );
    } else {
        // the target and the source are on the same sheet. we only delete the areas
        // of the source range that do not overlap with the moved area.
        foreach( const sheet_range & remove_rect, source_range.cut( source_range.coverage().checked_offset( target_range.upper_left() ) ) ) {
            erase( remove_rect );
        }
    }
}

template<class value_T>
void key_value_manager<value_T>::erase( const sheet_range& area, erase_shift_direction::type shift /*= erase_shift_direction::automatic */ )
{
    lock_type lock( m_mutex );
    typedef typename key_value_manager_impl::index_pair_type index_pair_type;
    typename node_lookup_callback<index_pair_type>::node_list_type node_list;
    node_lookup_callback<index_pair_type> query_callback( node_list );
    // query all nodes and values that intersect with the area to be deleted
    m_impl->m_lookup_container.query( area, query_callback );
    // remove all nodes that intersect with the area
    m_impl->m_lookup_container.remove( area, erase_all_callback<index_pair_type>() );
    // insert all nodes back into tree with their intersection removed.
    foreach( const typename node_lookup_callback<index_pair_type>::pair_type & current_node, node_list ) {
        foreach( const sheet_range & insert_rect, current_node.first.cut( area ) ) {
            m_impl->m_lookup_container.insert( insert_rect, current_node.second );
        }
    }
}

template<class value_T>
optional_sheet_range_type key_value_manager<value_T>::used_range() const
{
    typename key_value_manager_impl::lookup_container_type::optional_rectangle_type used_range;
    {
        lock_type lock( m_mutex );
        used_range = m_impl->m_lookup_container.used_range();
    }
    return used_range ? optional_sheet_range_type( *used_range ) : optional_sheet_range_type();
}

template<class value_T>
typename key_value_manager<value_T>::undo_list_type key_value_manager<value_T>::get_list_for_undo( const sheet_range& target_range ) const
{
    const optional_sheet_range_type used_range = this->used_range();
    if ( used_range ) {
        if ( used_range->does_intersect( target_range ) ) {
            undo_list_type node_list;
            node_lookup_callback<index_type> query_node_callback( node_list );
            m_impl->m_lookup_container.query( target_range, query_node_callback );
            return node_list;
        }
    }
    return undo_list_type();
}

template<class value_T>
void key_value_manager<value_T>::apply_list_for_undo( const sheet_range& target_range, const undo_list_type& undo_list )
{
    erase( target_range );
    foreach( const typename key_value_manager<value_T>::kv_pair_type & value, undo_list ) {
        m_impl->m_lookup_container.insert( target_range, value.second, true );
    }
}

template<class value_T>
void key_value_manager<value_T>::release_memory( bool purge )
{
    key_value_manager<value_T>::key_value_manager_impl::lookup_container_type::release_memory( purge );
}


