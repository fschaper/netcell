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

/*!
 * \brief
 * private implementation file as a compiler firewall.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<>
struct value_manager<bool, boolean_undo_type_trait>::value_manager_impl {
    typedef r::tree<bool> lookup_container_type;
    typedef boolean_undo_type_trait::index_type index_type;

    bool from_mapping( index_type value ) {
        return value;
    }

    lookup_container_type m_lookup_container;
};

template<>
inline void value_manager<bool, boolean_undo_type_trait>::set( const sheet_range& area, const value_type& value )
{
    lock_type lock( m_mutex );

    // erase all nodes in that area.
    erase( area );
    m_impl->m_lookup_container.insert( area, value );
}

template<>
inline value_manager<bool, boolean_undo_type_trait>::list_all_list_type value_manager<bool, boolean_undo_type_trait>::list_all() const
{
    list_all_list_type return_list;
    const optional_sheet_range_type used_locked_range( used_range() );
    if ( used_locked_range ) {
        //TODO we need a range query method that should be used here instead of the undo functionality!
        foreach( const kv_pair_type & kv, get_list_for_undo( *used_locked_range ) ) {
            if ( kv.second ) {
                return_list.push_back( kv.first );
            }
        }
    }
    return return_list;
}

