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
#include <wss/reference_table_coverage.hpp>
#include <wss/range_reference.hpp>
#include <wss/named_formula_reference.hpp>
#include <wss/i_dependency.hpp>

optional_sheet_range_type reference_table_coverage::coverage( const referencetable_type& table )
{
    optional_sheet_range_type return_range;
    referencetable_type::const_iterator it( table.begin() ), end_it( table.end() );
    for ( ; it != end_it; ++it ) {
        if ( *it ) {
            if ( ( *it )->type() == i_dependency_reference::range_reference ) {
                if ( return_range ) {
                    return_range->enclose_into_self( range_reference_cast( *it ).actualize().position() );
                } else {
                    return_range.reset( range_reference_cast( *it ).actualize().position() );
                }
            } else {
                if ( named_formula_reference_cast( *it ).is_valid() ) {
                    shared_dependency_type sd = named_formula_reference_cast( *it ).precedent();
                    if ( sd ) {
                        if ( return_range ) {
                            const optional_sheet_range_type tmp_coverage = sd->coverage();
                            if ( tmp_coverage ) {
                                return_range->enclose_into_self( *tmp_coverage );
                            }
                        } else {
                            return_range =  sd->coverage();
                        }
                    }
                }
            }
        }
    }
    return return_range;
}

class column_count_set : boost::noncopyable
{
    typedef std::set<unsigned int> single_cell_column_set_type;
    typedef std::pair<unsigned int, unsigned int> column_range_type;
    typedef std::set<column_range_type> multi_cell_column_set_type;
    typedef set_to_use<i_dependency*>::type visited_nfs_set;

public:
    typedef unsigned int counter_type;

    explicit column_count_set( const referencetable_type& table ) : m_count( 0 ) {
        add( table );
    }

    inline const counter_type count() {
        merge_and_clear_covered_singles();
        m_count = single_cell_column_set.size();
        std::for_each( multi_cell_column_set.begin(), multi_cell_column_set.end(), boost::bind( &column_count_set::count_number_of_columns, boost::ref( *this ), _1 ) );
        return m_count;
    }

private:
    inline void add( const referencetable_type& table ) {
        referencetable_type::const_iterator it( table.begin() ), end_it( table.end() );
        for ( ; it != end_it; ++it ) {
            if ( *it ) {
                if ( ( *it )->type() == i_dependency_reference::range_reference ) {
                    range_reference::actual actual_reference = range_reference_cast( *it ).actualize();
                    if ( actual_reference.is_valid() ) {
                        add( actual_reference.position() );
                    }
                } else {
                    if ( named_formula_reference_cast( *it ).is_valid() ) {
                        shared_dependency_type sd = named_formula_reference_cast( *it ).real_nf();
                        if ( sd && visited_nfs.find( sd.get() ) == visited_nfs.end() ) {
                            visited_nfs.insert( sd.get() ); //safe guard against cycles
                            add( sd->precedents() );
                        }
                    }
                }
            }
        }
    }

    inline void count_number_of_columns( const column_range_type& columns ) {
        m_count += columns.second;
        m_count -= columns.first;
        ++m_count;
    }

    inline void add( const sheet_range& current ) {
        if ( current.column_count() == 1 ) {
            single_cell_column_set.insert( current.upper_left().column() );
        } else {
            multi_cell_column_set.insert( std::make_pair( current.upper_left().column(), current.lower_right().column() ) );
        }
    }

    inline void remove_all_inside( const column_range_type& columns ) {
        single_cell_column_set_type::iterator start = single_cell_column_set.lower_bound( columns.first );
        single_cell_column_set_type::iterator end = single_cell_column_set.upper_bound( columns.second );

        if ( start != single_cell_column_set.end() ) {
            single_cell_column_set.erase( start, end );
        }
    }

    inline void merge_and_clear_covered_singles() {
        while ( merge() ) {}

        if ( single_cell_column_set.empty() ) {
            return;
        }
        std::for_each( multi_cell_column_set.begin(), multi_cell_column_set.end(), boost::bind( &column_count_set::remove_all_inside, boost::ref( *this ), _1 ) );
    }

    //if the ranges overlap, we can remove them both and create a bigger one. (1,5) and (3,9) -> (1,9)
    inline bool merge() {
        if ( multi_cell_column_set.size() > 1 ) {
            multi_cell_column_set_type::iterator it = multi_cell_column_set.begin();
            multi_cell_column_set_type::iterator next_it = it;
            ++next_it;

            while ( ( it != multi_cell_column_set.end() ) && ( next_it != multi_cell_column_set.end() ) ) {
                if ( it->second >= next_it->first ) {
                    const column_range_type merged( it->first, next_it->second );
                    ++next_it;
                    multi_cell_column_set.erase( it, next_it );
                    multi_cell_column_set.insert( merged );
                    return true;
                } else {
                    it = next_it;
                    ++next_it;
                }
            }
        }
        return false;
    }


private:
    single_cell_column_set_type single_cell_column_set;
    multi_cell_column_set_type multi_cell_column_set;
    visited_nfs_set visited_nfs;
    counter_type m_count;
};

unsigned int reference_table_coverage::number_of_covered_columns( const referencetable_type& table )
{
    return column_count_set( table ).count();
}
