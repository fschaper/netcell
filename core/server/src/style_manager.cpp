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
#include <wss/style_set.hpp>

//#include "key_value_manager.ipp"
//template class key_value_manager<style_set_type>;

#include "generic_container.ipp"
#include "wss/style_set.hpp"

template<>
const size_t simple_allocator< style_set_type >::NOTHING = ( size_t ) - 1;

template<>
void generic_container< style_set_type >::set( const sheet_range& area, const value_type& value )
{
    bool full_row = sheet_dimension::max_column == ( unsigned int ) area.lower_right().column() && 0 == ( unsigned int ) area.upper_left().column();
    bool full_col = sheet_dimension::max_row == ( unsigned int ) area.lower_right().row() && 0 == ( unsigned int ) area.upper_left().row();
    size_t simple_value = allocator().register_value( value );

    if ( full_col ) {
        for ( int col = area.upper_left().column(); col <= area.lower_right().column(); col++ ) {
            size_t there = m_columns.get( col );
            if ( there != simple_allocator<style_set_type>::NOTHING ) {
                style_set_type merge = allocator().at( there );
                merge += value;
                m_columns.set( col, allocator().register_value( merge ) );
            } else {
                m_columns.set( col, simple_value );
            }

            for ( rows_data_type::iterator i = m_rows.begin(), e = m_rows.end(); i != e; ++i  ) {
                size_t there = i->second.get( col );
                if ( i->second.last_result() ) {
                    style_set_type merge = allocator().at( there );
                    merge += value;
                    i->second.set( col, allocator().register_value( merge ) );
                }
            }
        }
        return;
    }

    if ( full_row ) {

        for ( int row_idx = area.upper_left().row(); row_idx <= area.lower_right().row(); row_idx++ ) {
            rows_data_type::iterator crt = get_row( row_idx );
            size_t there = crt->second.background();
            if ( there != simple_allocator<style_set_type>::NOTHING ) {
                style_set_type merge = allocator().at( there );
                merge += value;
                crt->second.background( allocator().register_value( merge ) );
            } else {
                crt->second.background( simple_value );
            }
            if ( crt->second.empty() ) {
                continue;
            }
            for ( size_t col_idx = crt->second.min(), max = crt->second.max(); col_idx <= max; ++col_idx ) {
                there = crt->second.get( col_idx );
                if ( there != simple_allocator<style_set_type>::NOTHING && there != crt->second.background() ) {
                    style_set_type merge = allocator().at( there );
                    merge += value;
                    crt->second.set( col_idx, allocator().register_value( merge ) );
                }
            }
        }

        return;
    }

    //TODO: do I win th & bunny? (RIA)
    for ( int row = area.upper_left().row(); row <= area.lower_right().row(); row++ ) {
        for ( int col = area.upper_left().column(); col <= area.lower_right().column(); col++ ) {
            sheet_point pos( row, col );
            style_set_type there = get( pos );
            if ( there.empty() ) {
                set( pos, simple_value );
            } else {
                there += value;
                set( pos, allocator().register_value( there ) );
            }
        }
    }
}

template<>
bool simple_allocator<style_set_type>::is_empty( style_set_type val )
{
    if ( val.empty() ) {
        return true;
    }
    if ( 1 <= val.size() ) {
        if ( val.begin()->first == "background-color" ) {
            std::string value = val.begin()->second;
            if ( value.empty() ) {
                return true;
            }

            if ( value == "none" ) {
                return true;
            }

            return false;
        }
    }
    return true;
}

template<>
std::vector< size_t > simple_allocator<style_set_type>::empty_keys()
{

    std::vector< size_t > result;

    // todo:
    // until we can get boost 1.44 we'll only use write_lock for VS10
    // https://svn.boost.org/trac/boost/ticket/2501 is fixed for 1.44
    // there is also a patch available https://svn.boost.org/trac/boost/attachment/ticket/2501/2501.patch
#if defined(USING_VS_2010)
    write_lock   lock( m_mutex );
#else
    read_write_lock   lock( m_mutex );
#endif
    for ( map_type::const_iterator i = m_values.begin(), e = m_values.end(); i != e; i++ ) {
        if ( is_empty( i->second ) ) {
            result.push_back( i->first );
        }
    }

#if !defined(USING_VS_2010)
    upgrade_lock    write( lock );
#endif
    result.push_back( NOTHING );
    return result;
}

template<>
optional_sheet_range_type generic_container< style_set_type >::used_range( const bool include_fulls ) const
{
    if ( m_rows.empty() && m_columns.empty() ) {
        return optional_sheet_range_type();
    }

    std::vector< size_t > empties = const_cast< generic_container< style_set_type >* >( this )->allocator().empty_keys();

    size_t min_row = sheet_dimension::max_row + 1;
    size_t max_row = 0;
    size_t min_col = sheet_dimension::max_column + 1;
    size_t max_col = 0;

    for ( rows_data_type::const_iterator i = m_rows.begin(), e = m_rows.end(); i != e; ++i ) {

        const size_t row_background = i->second.background() ;
        simple_allocator<style_set_type>& alloc = const_cast< generic_container< style_set_type >* >( this )->allocator();

        if ( include_fulls && simple_allocator<style_set_type>::NOTHING != row_background ) {
            if ( !alloc.is_empty( alloc.at( row_background ) ) ) {
                min_col = 0;
                max_col = sheet_dimension::max_column;
            }
        }

        if ( i->second.empty() ) {
            continue;
        }

        {
            const size_t crt_eval = include_fulls ?  i->second.min_not_of( empties ) : i->second.min();

            if ( crt_eval != simple_allocator<style_set_type>::NOTHING  && crt_eval < min_col ) {
                min_col = crt_eval;
            }
        }


        {
            const size_t crt_eval = include_fulls ? i->second.max_not_of( empties ) : i->second.max();
            if ( crt_eval != simple_allocator<style_set_type>::NOTHING  && crt_eval > max_col ) {
                max_col = crt_eval;
            }
        }

        const size_t row = i->first;

        if ( row < min_row ) {
            min_row = row;
        }
        if ( row > max_row ) {
            max_row = row;
        }
    }


    if ( include_fulls && !m_columns.empty()
            && simple_allocator<style_set_type>::NOTHING != m_columns.min_not_of( empties )
            && simple_allocator<style_set_type>::NOTHING != m_columns.max_not_of( empties ) ) {
        min_row = 0;
        max_row = sheet_dimension::max_row;

        {
            const size_t crt_eval = m_columns.min_not_of( empties );
            if ( crt_eval != simple_allocator<style_set_type>::NOTHING && min_col > crt_eval ) {
                min_col = crt_eval;;
            }
        }


        {
            const size_t crt_eval = m_columns.max_not_of( empties );
            if ( crt_eval != simple_allocator<style_set_type>::NOTHING  && max_col < crt_eval ) {
                max_col = crt_eval;
            }
        }
    }

    if ( sheet_dimension::max_row + 1 == min_row ) {
        min_row = 0;
    }

    if ( sheet_dimension::max_column + 1 == min_col ) {
        min_col = 0;
    }

    return optional_sheet_range_type( sheet_range( sheet_point( min_row, min_col ), sheet_point( max_row, max_col ) ) );
}

#ifdef _WIN32
template class WSS_MODULE generic_container< style_set_type >;
#else
template class generic_container< style_set_type >;
#endif
