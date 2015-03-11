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

#include "wss/value_manager.hpp"
#include "wss/not_implemented_exception.hpp"
#include "wss/r_tree.hpp"
#include "wss/locked_object.hpp"
#include <boost/static_assert.hpp>
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
    typedef std::pair<sheet_range, index_type> pair_type;
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
 * private implementation file as a compiler firewall.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class value_T, class undo_traits_T>
struct value_manager<value_T, undo_traits_T>::value_manager_impl {
    // mapping of values to indexes
    typedef value_T value_type;
    typedef reference_counted_indexed_mapping<value_type> value_mapping_type;
    typedef typename value_mapping_type::index_type index_type;
    // r-tree which holds the coverage information for a value
    typedef typename r::tree<index_type> lookup_container_type;

    value_type from_mapping( index_type value ) {
        return m_value_map[ value ];
    }

    static void release_memory( bool purge ) {
        lookup_container_type::release_memory( purge );
    }

    // (fschaper) the order of initialization (better destruction) is important for
    // the value_mapping_type and the lookup_container.get since the lookup_container
    // holds handles to the key_map it needs to be destroyed first.
    value_mapping_type m_value_map;
    lookup_container_type m_lookup_container;
};

template<class value_T, class undo_traits_T>
value_manager<value_T, undo_traits_T>::value_manager()
    : m_mutex()
    , m_impl( new value_manager_impl() )
{}

template<class value_T, class undo_traits_T>
value_manager<value_T, undo_traits_T>::~value_manager()
{
    lock_type lock( m_mutex );
    m_impl.reset();
}

template<class value_T, class undo_traits_T>
void value_manager<value_T, undo_traits_T>::set( const sheet_range& area, const value_type& value )
{
    lock_type lock( m_mutex );

    // erase all nodes in that area.
    erase( area );
    //if value is empty don't do anything
    if ( !value.empty() ) {
        m_impl->m_lookup_container.insert( area, m_impl->m_value_map.set( value ) );
    }
}

template<class value_T, class undo_traits_T>
typename value_manager<value_T, undo_traits_T>::optional_value_type value_manager<value_T, undo_traits_T>::get( const sheet_point& p ) const
{
    typedef typename value_manager_impl::index_type index_type;
    typename node_lookup_callback<index_type>::node_list_type node_list;

    node_lookup_callback<index_type> query_callback( node_list );
    {
        lock_type lock( m_mutex );
        m_impl->m_lookup_container.query( geometry::rectangle_type( p ), query_callback );
    }

    // re-create the value set by adding each separate node value back to
    // the return value.
    optional_value_type return_value;
    foreach( const typename node_lookup_callback<index_type>::pair_type & v, node_list ) {
        return_value = m_impl->from_mapping( v.second );
    }
    return return_value;
}

template<class value_T, class undo_traits_T>
void value_manager<value_T, undo_traits_T>::copy( const sheet_range& source_range, const sheet_range& target_range, self_type& target, insert_shift_direction::type shift /*= insert_shift_direction::automatic */ )
{
    typedef typename value_manager_impl::index_type index_type;
    typename node_lookup_callback<index_type>::node_list_type node_list;
    const sheet_range local_target = target_range.enclose( source_range.checked_offset( source_range.distance( target_range ) ) );

    node_lookup_callback<index_type> query_node_callback( node_list );
    {
        lock_type lock( m_mutex );

        // the lookup callback will create a copy of all nodes in the source_range region
        m_impl->m_lookup_container.query( source_range, query_node_callback );
        // since we already have a copy of all nodes in the source range (the node_list)
        // we can simply erase the complete target range.
        target.erase( local_target );

        // loop through all nodes that intersect with the source area
        copy_fill_iterator it( source_range, local_target );
        foreach( const typename node_lookup_callback<index_type>::pair_type & current_node, node_list ) {
            it.reset();
            // for every node that intersects with the source area determine the covered (selected) area
            // by intersection (the area covered by the node and the selection).
            const geometry::rectangle_type affected_range( current_node.first.intersection( source_range ) );
            // set the new value in the target area.
            // the selected area (the area where the node coverage intersects with the users selection) is moved to the
            // upper left point of the target range. then we apply a offset to determine the sector that is currently
            // filled in case the target range is a multiple of the source range (current_row_multiplier/current_column_multiplier).
            // then we add a last offset to maintain the distance the intersecting region has from the upper left of the source range.
            const value_type set_type =  m_impl->from_mapping( current_node.second );
            const std::list<sheet_range> target_list( it.whole_target_area( affected_range ) );
            for ( std::list<sheet_range>::const_iterator current_target_it = target_list.begin(), end_it = target_list.end(); current_target_it != end_it; ++current_target_it ) {
                target.set( *current_target_it , set_type );
            }
        }
    }
}

template<class value_T, class undo_traits_T>
void value_manager<value_T, undo_traits_T>::move( const sheet_range& source_range, const sheet_range& target_range, self_type& target, copy_format_from::type format_from /* = copy_format_from::left_or_above */, insert_shift_direction::type shift /* = insert_shift_direction::automatic */ )
{
    copy( source_range, source_range.coverage().checked_offset( target_range.upper_left() ), target, shift );
    // remove all regions from the source range that do not overlap with the target range
    if ( reinterpret_cast<value_manager<value_T, undo_traits_T>* >( &target ) != this ) {
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

template<class value_T, class undo_traits_T>
void value_manager<value_T, undo_traits_T>::erase( const sheet_range& area, erase_shift_direction::type shift /*= erase_shift_direction::automatic */ )
{
    lock_type lock( m_mutex );
    typedef typename value_manager_impl::index_type index_type;
    typename node_lookup_callback<index_type>::node_list_type node_list;
    node_lookup_callback<index_type> query_callback( node_list );
    // query all nodes and values that intersect with the area to be deleted
    m_impl->m_lookup_container.query( area, query_callback );
    // remove all nodes that intersect with the area
    m_impl->m_lookup_container.remove( area, erase_all_callback<index_type>() );
    // insert all nodes back into tree with their intersection removed.
    foreach( const typename node_lookup_callback<index_type>::pair_type & current_node, node_list ) {
        foreach( const sheet_range & insert_rect, current_node.first.cut( area ) ) {
            m_impl->m_lookup_container.insert( insert_rect, current_node.second );
        }
    }
}

template<class value_T, class undo_traits_T>
optional_sheet_range_type value_manager<value_T, undo_traits_T>::used_range() const
{
    typename value_manager_impl::lookup_container_type::optional_rectangle_type used_range;
    {
        lock_type lock( m_mutex );
        used_range = m_impl->m_lookup_container.used_range();
    }
    return used_range ? optional_sheet_range_type( *used_range ) : optional_sheet_range_type();
}

template<class value_T, typename undo_traits_T>
typename undo_traits_T::undo_list_type value_manager<value_T, undo_traits_T>::get_list_for_undo( const sheet_range& target_range ) const
{
    const optional_sheet_range_type used_range = this->used_range();
    if ( used_range ) {
        if ( used_range->does_intersect( target_range ) ) {
            typename undo_traits_T::kv_pair_list_type undo_list;
            node_lookup_callback< typename value_manager<value_T, undo_traits_T>::index_type > query_callback( undo_list );
            m_impl->m_lookup_container.query( target_range, query_callback );
            return undo_list;
        }
    }
    return typename undo_traits_T::kv_pair_list_type();
}

template<class value_T, class undo_traits_T>
void value_manager<value_T, undo_traits_T>::apply_list_for_undo( const sheet_range& target_range, const undo_list_type& undo_list )
{
    erase( target_range );
    foreach( const typename undo_traits_T::kv_pair_type & value, undo_list ) {
        m_impl->m_lookup_container.insert( target_range, value.second, true );
    }
}

template < class value_T, class undo_traits_T >
void value_manager<value_T, undo_traits_T>::release_memory( bool purge )
{
    value_manager_impl::lookup_container_type::release_memory( purge );
}
