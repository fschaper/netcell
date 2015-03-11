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

#include <wss/define.hpp>
#include <wss/type.hpp>
#include <wss/sheet_range.hpp>
#include <wss/generic_rectangle.hpp>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include "conditional_format_utils.hpp"


namespace cf
{
    class conditional_format_affected_range_list
    {
        typedef rectangle_list_type::iterator iterator;
        typedef rectangle_list_type::const_iterator const_iterator;
    public:

        conditional_format_affected_range_list( const rectangle_list_type& r_list ) {
            foreach( const sheet_range & r, r_list ) {
                add( r );
            }
        }

        std::string to_a1( const locale& l ) const {
            return conditional_format_utils::range_list_to_a1( l, m_list );
        }

    private:
        void add( const sheet_range& r ) {
            rectangle_list_type list_to_add( 1, r );
            split_list_to_avoid_intersections( list_to_add );
            foreach( sheet_range & new_r, list_to_add ) {
                internal_add( new_r );
            }
        }

        void split_list_to_avoid_intersections( rectangle_list_type& r_list ) {
            for ( iterator current_old_r = m_list.begin(), old_r_end = m_list.end(); current_old_r != old_r_end ; ++current_old_r ) {
                iterator r = r_list.begin();
                while ( r != r_list.end() ) {
                    if ( r->does_intersect( *current_old_r ) ) {
                        insert_from_temporary( r_list, r->cut( *current_old_r ) );
                        r = r_list.erase( r );
                    } else {
                        ++r;
                    }
                }
                if ( r_list.empty() ) {
                    break;
                }

            }
        }

        void internal_add( sheet_range& r ) {
            bool changed = false;
            geometry::generic_rectangle<geometry::point> search_r = r.grow( 1, 1 );
            do {
                changed = false;
                rectangle_list_type::iterator it( m_list.begin() );
                while ( it != m_list.end() ) {
                    if ( search_r.does_intersect( *it ) && r.border_contact_type( *it ) != geometry::contact_none ) {
                        r.enclose_into_self( *it );
                        search_r = r.grow( 1, 1 );
                        it = m_list.erase( it );
                        changed = true;
                    } else {
                        ++it;
                    }
                }
            } while ( changed );
            m_list.push_back( r );
            m_list.sort();
        }
        rectangle_list_type m_list;
    };

}
