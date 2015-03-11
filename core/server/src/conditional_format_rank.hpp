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

#include "wss/conditional_format_manager.hpp"
#include "conditional_format_types.hpp"

namespace cf
{
    class conditional_format_rank
        : public boost::noncopyable
    {
        typedef internal_id_list_type::const_iterator const_iterator;
        typedef internal_id_list_type::iterator iterator;
        typedef internal_id_list_type::const_reverse_iterator const_reverse_iterator;
        typedef internal_id_list_type::reverse_iterator reverse_iterator;

    public:


        inline void move_up( const internal_id_set_type& ids, const internal_id_set_type& ids_to_check ) {
            typedef internal_id_set_type::const_iterator id_set_it_type;
            for ( id_set_it_type id_it = ids.begin(), id_it_end = ids.end(); id_it != id_it_end; ++id_it ) {

                // this isn't very effective, but this list shouldn't be that big,
                // and moving up or down shouldn't occur very often!

                const_iterator end_it( m_sorted_ids.end() );
                iterator it( std::find( m_sorted_ids.begin(), m_sorted_ids.end(), *id_it ) );

                assert( "something is messed up, all ids should have a rank!" && it != end_it );

                iterator this_item = it;
                ++it;

                internal_id_set_type::const_iterator ids_to_check_end( ids_to_check.end() );

                while ( it != end_it && ids_to_check.find( *it ) == ids_to_check_end ) {
                    //move up until we find an element that we want to compare against
                    ++it;
                }

                if ( it != end_it ) {
                    std::iter_swap( this_item, it );
                }
            }
        }

        inline void move_down( const internal_id_set_type& ids, const internal_id_set_type& ids_to_check ) {
            typedef internal_id_set_type::const_iterator id_set_it_type;
            for ( id_set_it_type id_it = ids.begin(), id_it_end = ids.end(); id_it != id_it_end; ++id_it ) {
                // this isn't very effective, but this list shouldn't be that big,
                // and moving up or down shouldn't occur very often!
                const_reverse_iterator end_it( m_sorted_ids.rend() );
                reverse_iterator it( std::find( m_sorted_ids.rbegin(), m_sorted_ids.rend(), *id_it ) );

                assert( "something is messed up, all ids should have a rank!" && it != end_it );

                reverse_iterator this_item = it;
                ++it;

                internal_id_set_type::const_iterator ids_to_check_end( ids_to_check.end() );

                while ( it != end_it && ids_to_check.find( *it ) == ids_to_check_end ) {
                    //move up until we find an element that we want to compare against
                    ++it;
                }

                if ( it != end_it ) {
                    std::iter_swap( this_item, it );
                }
            }
        }

        inline void add( const internal_lookup_id_type id ) {
            m_sorted_ids.push_back( id );
        }

        inline void remove( const internal_lookup_id_type id ) {
            iterator it( std::find( m_sorted_ids.begin() , m_sorted_ids.end(), id ) );
            if ( it != m_sorted_ids.end() ) {
                m_sorted_ids.erase( it );
            }
        }

        inline internal_id_list_type sort( const internal_id_set_type& ids ) const {
            internal_id_list_type return_val;
            const_reverse_iterator it( m_sorted_ids.rbegin() ), end_it( m_sorted_ids.rend() );
            internal_id_set_type::const_iterator ids_end( ids.end() );
            while ( it != end_it ) {
                if ( ids.find( *it ) != ids_end ) {
                    return_val.push_back( *it );
                }
                ++it;
            }
            return return_val;
        }

    private:
        internal_id_list_type m_sorted_ids;
    };
}
