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

#include "precompiled_header.hpp"
#include "array_manager.hpp"


#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

bool array_manager::add( const sheet_range& coverage )
{
    if ( is_partially_intersecting( coverage ) ) {
        return false;
    }
    m_container.push_back( coverage );
    return true;
}

bool array_manager::remove( const sheet_range& to_remove )
{
    typedef std::vector<geometry::rectangle_type> delete_list_type;
    delete_list_type delete_list;
    for( rectangle_list_type::const_iterator existing = m_container.begin(), end_it = m_container.end(); existing != end_it; ++existing ) {
        if ( existing->does_intersect( to_remove ) ) {
            if ( to_remove.covers( *existing ) ) {
                delete_list.push_back( *existing );
            } else {
                return false;
            }
        }
    }

    for( delete_list_type::const_iterator existing = delete_list.begin(), end_it = delete_list.end(); existing != end_it; ++existing ) {
        m_container.remove( *existing );
    }
    return true;
}

bool array_manager::contains_array( const sheet_range& coverage ) const
{
    for( rectangle_list_type::const_iterator existing = m_container.begin(), end_it = m_container.end(); existing != end_it; ++existing ) {
        if ( existing->does_intersect( coverage ) && coverage.covers( *existing ) ) {
            return true;
        }
    }
    return false;
}

bool array_manager::is_partially_intersecting( const sheet_range& coverage ) const
{
    for( rectangle_list_type::const_iterator existing = m_container.begin(), end_it = m_container.end(); existing != end_it; ++existing ) {
        if ( existing->does_intersect( coverage ) && !coverage.covers(  *existing ) ) {
            return true;
        }
    }
    return false;
}

bool array_manager::array_move_okay( const sheet_range& source, const sheet_range& target ) const
{
    for( rectangle_list_type::const_iterator existing = m_container.begin(), end_it = m_container.end(); existing != end_it; ++existing ) {
        if ( existing->does_intersect( source ) ) {
            if( source.covers( *existing ) ) {
                //thats okay, we will move the whole array!
            } else {
                //we try to move part of the array!
                return false;
            }
        } else if( existing->does_intersect( target ) ) {
            if( target.covers(  *existing ) ) {
                //thats okay, we just overwrite the whole array
            } else {
                //we would overwrite part of an array
                return false;
            }
        }
    }
    return true;
}

rectangle_list_type array_manager::list() const
{
    return m_container;
}

