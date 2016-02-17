/**
 *  \file
 *  implementation of generic cell
 *
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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

struct subset_helper;
struct dimension_element_info_simple_helper;
struct consolidation_element_info_helper;

template<class T>
struct get_types_and_static_data : non_instantiable {
    typedef void helper_type;
    static const size_t get( const T& ) {
        BOOST_STATIC_ASSERT( sizeof( T ) == 0 );
        return 0;
    }
};

template<>
struct get_types_and_static_data<SubsetResults> {
    typedef subset_helper helper_type;
    enum { max_entries = 3};
};

template<>
struct get_types_and_static_data<ConsolidationElementInfoArray> {
    typedef consolidation_element_info_helper helper_type;
    enum { max_entries = 4};
};

template<>
struct get_types_and_static_data<DimensionElementInfoSimpleArray> {
    typedef dimension_element_info_simple_helper helper_type;
    enum { max_entries = 3};
};

struct idx_iterator : boost::noncopyable {
    inline idx_iterator( const size_t max_size ) : max_size( max_size ), current_idx( 0 ), current_offset( 0 ) {}

    inline void operator++() {
        ++current_idx;
        current_offset = 0;
    }

    inline size_t next() const {
        const size_t return_val = max_size * current_offset + current_idx;
        ++current_offset;
        return return_val;
    }

    inline bool is_valid() const {
        return current_idx < max_size;
    }
private:
    const size_t max_size;
    size_t current_idx;
    mutable size_t current_offset;
};

template<class T>
std::string use_adapter_cell_to_cast_to_string( palo_cell_adapter& adapter_cell, const T& t )
{
    return adapter_cell.create()->set( t );
}

template<class helper_type>
class palo_cell_adapter_helper : non_instantiable
{
    typedef typename helper_type::entries_type entries_type;
    typedef typename helper_type::entry_type entry_type;

public:
    static inline void handle_entries( palo_cell_adapter& adapter_cell, const entries_type& es, const bool is_retval, const size_t cols, const size_t rows, variant& return_value, const bool is_inside_nf ) {
        return_value = variant( variant::type_array );
        variant::variant_array_type& array = return_value.array();

        const size_t max_entries = get_types_and_static_data<entries_type>::max_entries;
        const bool is_vertical = !( cols > max_entries && cols >= rows ); // return as column

        size_t num_entries = max_entries; // return everything
        if ( is_retval ) {
            if ( is_vertical ) {
                num_entries = cols;
            } else {
                num_entries = rows;
            }

            if ( num_entries > max_entries || num_entries == 0 ) {
                num_entries = max_entries;
            }
        }

        const size_t max_size = is_vertical ? rows : cols;

        handle_entries( adapter_cell, es, is_vertical, num_entries, max_size, array, is_inside_nf );

        if ( is_retval && !is_vertical ) {
            const size_t cols_to_use = is_vertical ? num_entries : es.size();
            const size_t cols_to_set = std::min<size_t>( cols_to_use, cols );
            if ( cols_to_set != 0 ) {
                return_value.column_width( ( unsigned int ) cols_to_set );
            } else {
                return_value.column_width( 3 );
            }
        } else {
            return_value.column_width( ( unsigned int ) num_entries );
        }
    }

private:
    static inline void handle_entries( palo_cell_adapter& adapter_cell, const entries_type& es, const bool is_vertical, const size_t num_entries, size_t max_size, variant::variant_array_type& array, const bool is_inside_nf ) {
        if ( max_size == 0 ) {
            max_size = es.size();
        }

        static const size_t MAX_PALO_REQUEST_RETURN_SIZE = 20000;

        if ( max_size > MAX_PALO_REQUEST_RETURN_SIZE ) {
            max_size = MAX_PALO_REQUEST_RETURN_SIZE;
        }

        if ( !is_vertical ) {
            handle_horizontal_entries( adapter_cell, es, max_size, num_entries, array );
        } else {
            handle_entries( adapter_cell, es, max_size, num_entries, array, is_inside_nf );
        }
    }

    static inline void handle_horizontal_entries( palo_cell_adapter& adapter_cell, const entries_type& es, const size_t max_size, const size_t num_entries, variant::variant_array_type& array ) {
        array.resize(  num_entries * max_size );
        switch ( num_entries ) {
            case 1:
                handle_horizontal_entries<1>( adapter_cell, max_size, es, array );
                break;
            case 2:
                handle_horizontal_entries<2>( adapter_cell, max_size, es, array );
                break;
            default:
                handle_horizontal_entries<3>( adapter_cell, max_size, es, array );
        }
    }

    static inline void handle_entries( palo_cell_adapter& adapter_cell, const entries_type& es, const size_t max_size, const size_t num_entries, variant::variant_array_type& array, const bool is_inside_nf ) {
        switch ( num_entries ) {
            case 1:
                handle_entries<1>( adapter_cell, max_size, es, array );
                break;
            case 2:
                handle_entries<2>( adapter_cell, max_size, es, array );
                break;
            default:
                if ( is_inside_nf ) {
                    handle_entries_inside_nf( max_size, es, array );
                } else {
                    handle_entries<3>( adapter_cell, max_size, es, array );
                }
        }
    }

    template<int num_entries>
    static inline void handle_horizontal_entries( palo_cell_adapter& adapter_cell, const size_t max_size, const entries_type& es, variant::variant_array_type& array ) {
        idx_iterator it( max_size );
        foreach( const entry_type & e, es ) {
            if ( !it.is_valid() ) {
                return;
            }
            helper_type::template handle_horizontal_entry<num_entries>( adapter_cell, it, e, array );
            ++it;
        }
    }

    template<int num_entries>
    static inline void handle_entries( palo_cell_adapter& adapter_cell, const size_t max_size, const entries_type& es, variant::variant_array_type& array ) {
        if ( max_size != 0 ) {
            size_t counter = max_size;

            foreach( const entry_type & e, es ) {
                if ( counter == 0 ) {
                    return;
                }
                helper_type::template handle_entry<num_entries>( adapter_cell, e, array );
                --counter;
            }
        } else {
            foreach( const entry_type & e, es ) {
                helper_type::template handle_entry<num_entries>( adapter_cell, e, array );
            }
        }
    }

    static inline void handle_entries_inside_nf( const size_t max_size, const entries_type& es, variant::variant_array_type& array ) {
        foreach( const entry_type & e, es ) {
            helper_type::handle_entry_inside_nf( e, array );
        }
    }


};

struct subset_helper  {

    typedef SubsetResults entries_type;
    typedef SubsetResult entry_type;

    template<int num_entries>
    static inline void handle_horizontal_entry( palo_cell_adapter& /*adapter_cell*/, const idx_iterator& it, const entry_type& e, variant::variant_array_type& array ) {
        if ( num_entries > 2 ) {
            array.set( it.next(), static_cast<double>( e.idx ) );
        }
        array.set( it.next(), e.name );
        if ( num_entries > 1 ) {
            array.set( it.next(), e.alias );
        }
    }

    template<int num_entries>
    static inline void handle_entry( palo_cell_adapter& /*adapter_cell*/, const entry_type& e, variant::variant_array_type& array ) {
        if ( num_entries > 2 ) {
            array.push_back( static_cast<double>( e.idx ) );
        }
        array.push_back( e.name );
        if ( num_entries > 1 ) {
            array.push_back( e.alias );
        }
    }

    static inline void handle_entry_inside_nf( const entry_type& e, variant::variant_array_type& array ) {
        array.push_back( e.name );
        array.push_back( e.alias );
        array.push_back( static_cast<double>( e.idx ) );
    }
};

struct consolidation_element_info_helper  {

    typedef ConsolidationElementInfoArray entries_type;
    typedef ConsolidationElementInfo entry_type;

    template<int num_entries>
    static inline void handle_horizontal_entry( palo_cell_adapter& adapter_cell, const idx_iterator& it, const entry_type& e, variant::variant_array_type& array ) {
        array.set( it.next(), e.name );

        if ( num_entries >= 2 ) {
            array.set( it.next(), e.weight );
        }

        if ( num_entries >= 3 ) {
            array.set( it.next(), use_adapter_cell_to_cast_to_string( adapter_cell, e.type ) );
        }

        if ( num_entries >= 4 ) {
            array.set( it.next(), static_cast<double>( e.identifier ) );
        }
    }

    template<int num_entries>
    static inline void handle_entry( palo_cell_adapter& adapter_cell, const entry_type& e, variant::variant_array_type& array ) {
        array.push_back( e.name );

        if ( num_entries >= 2 ) {
            array.push_back(  e.weight );
        }

        if ( num_entries >= 3 ) {
            array.push_back( use_adapter_cell_to_cast_to_string( adapter_cell, e.type ) );
        }

        if ( num_entries >= 4 ) {
            array.push_back( static_cast<double>( e.identifier ) );
        }
    }

    static inline void handle_entry_inside_nf( const entry_type& e, variant::variant_array_type& array ) {
        assert( !"this should only be called for subsets not for ConsolidationElementInfo" );
    }
};

struct dimension_element_info_simple_helper  {

    typedef DimensionElementInfoSimpleArray entries_type;
    typedef DimensionElementInfoSimple entry_type;

    template<int num_entries>
    static inline void handle_horizontal_entry( palo_cell_adapter& adapter_cell, const idx_iterator& it, const entry_type& e, variant::variant_array_type& array ) {
        array.set( it.next(), e.name );

        if ( num_entries >= 2 ) {
            array.set( it.next(), use_adapter_cell_to_cast_to_string( adapter_cell, e.type ) );
        }

        if ( num_entries >= 3 ) {
            array.set( it.next(), static_cast<double>( e.identifier ) );
        }
    }

    template<int num_entries>
    static inline void handle_entry( palo_cell_adapter& adapter_cell, const entry_type& e, variant::variant_array_type& array ) {
        array.push_back( e.name );

        if ( num_entries >= 2 ) {
            array.push_back( use_adapter_cell_to_cast_to_string( adapter_cell, e.type ) );
        }

        if ( num_entries >= 3 ) {
            array.push_back( static_cast<double>( e.identifier ) );
        }
    }

    static inline void handle_entry_inside_nf( const entry_type& e, variant::variant_array_type& array ) {
        assert( !"this should only be called for subsets not for DimensionElementInfoSimple" );
    }
};



