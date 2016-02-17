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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/variant.hpp>
#include <wss/type.hpp>
#include <wss/cyclic_dependency_set.hpp>

#include <boost/noncopyable.hpp>
#include <map>
#include "i_dependency.hpp"

class i_dependency;
class free_formula;

struct precedents_cache {
    precedents_cache() : is_cyclic( false ) {}
    precedents_cache( const precedents_cache& other )
        : calculation_order( other.calculation_order ), is_cyclic( other.is_cyclic ) {
        //being copied, check if this is necessary!
    }

    typedef std::stack<shared_dependency_type> precedents_stack_type;
    precedents_stack_type calculation_order;
    bool is_cyclic;
};

/*!
 * \brief
 * caches volatile values during one calculation cycle.
 *
 * \remarks
 * this class is not protected by any mutex. care must be taken
 * that every cache is used only by one thread at once!
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class calculation_cache
    : private boost::noncopyable
{
    typedef map_to_use<const i_dependency*, variant>::type volatile_cache_type;
    typedef map_to_use<const i_dependency*, unsigned int >::type cyclic_counter_type;
    typedef map_to_use<const i_dependency*, precedents_cache>::type precedents_cache_type;
    typedef map_to_use<const free_formula*, variant>::type free_formula_cache_type;
public:
    /*!
     * \brief
     * stores the volatile value in the cache.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline void store( const i_dependency& d, const variant& v ) {
        store( d, v, select_volatile_cache( d ) );
    }

    inline void remove( const i_dependency& d ) {
        remove( d, select_volatile_cache( d ) );
    }


    inline void store_cyclic( const i_dependency& d, const variant& v ) {
        store_cyclic( d, v, select_volatile_cache( d ) );
    }


    inline void store( const i_dependency& d, const variant& v, volatile_cache_type& cache ) {
        //         assert( "value has already been added to volatile cache!"
        //                 && cache.find( &d ) == cache.end() );
        //assert( "value is not volatile but still wants to be stored here!" && d.is_volatile() );
        cache.insert( volatile_cache_type::value_type( &d, v ) );
    }

    inline void store_cyclic( const i_dependency& d, const variant& v, volatile_cache_type& cache ) {
        cache[&d] = v;
    }
    /*!
     * \brief
     * retrieves a volatile value from the cache.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    optional_variant_type retrieve( const i_dependency& d ) const {
        return retrieve( d, select_volatile_cache( d ) );
    }

    /*!
     * \brief
     * clear the cache
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void clear( const bool dont_clear_caches ) {
        if ( !dont_clear_caches ) {
            // (fschaper) we don't use volatile_cache_type().swap( m_volatile_cache ); here since
            // we will need the previous amount of memory again anyway.
            // raise the calculation token. external caches need also be reset at this point.
            m_volatile_nf_cache.clear();
            m_cyclic_counters.clear();
        }
        m_volatile_cell_cache.clear();
        m_cyclic_dependencies.clear();
        m_view_independents_done = false;
        ++m_calculation_token;
    }

    bool increment_iteration_count( const i_dependency& d, const variant& current_value ) {
        volatile_cache_type::iterator it( m_cyclic_cache.find( &d ) );
        if ( m_cyclic_cache.end() == it ) {
            m_cyclic_cache.insert( std::make_pair( &d, current_value ) );
            ++m_cyclic_counters[&d];
            return true;
        }
        if ( current_value == it->second ) {
            return false;
        }
        ++m_cyclic_counters[&d];
        m_cyclic_cache[&d] = current_value;
        return true;
    }

    bool iteration_count_still_valid( const i_dependency& d, const unsigned int maximum_iterations ) const {
        cyclic_counter_type::const_iterator it( m_cyclic_counters.find( &d ) );
        return it == m_cyclic_counters.end() || it->second < maximum_iterations;
    }

    void set_iteration_count_to_max( const i_dependency& d, const unsigned int maximum_iterations ) {
        m_cyclic_counters[&d] = maximum_iterations;
    }

    bool increment_and_check_iteration_count( const i_dependency& d, const variant& current_value, const unsigned int maximum_iterations ) {
        if ( ++m_cyclic_counters[&d] < maximum_iterations ) {
            m_cyclic_cache[&d] = current_value;
            return true;
        }
        return false;
    }

    bool increment_and_check_iteration_count( const i_dependency& d, const unsigned int maximum_iterations ) {
        return ++m_cyclic_counters[&d] < maximum_iterations;
    }

    const variant& retrieve_cyclic_value( const i_dependency& d ) {
        return m_cyclic_cache[&d];
    }

    /*!
     * \brief
     * return the current calculation token for the object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    unsigned long calculation_token() const {
        return m_calculation_token;
    }

    cyclic_dependency_set& cyclic_dependencies() {
        return m_cyclic_dependencies;
    }

    inline const bool view_independents_done() const {
        return m_view_independents_done;
    }
    inline void view_independents_done( const bool val ) {
        m_view_independents_done = val;
    }

private:
    inline volatile_cache_type& select_volatile_cache( const i_dependency& d ) {
        if ( d.put_in_general_cache() ) {
            return m_volatile_cell_cache;
        }
        return m_volatile_nf_cache;
    }

    inline const volatile_cache_type& select_volatile_cache( const i_dependency& d ) const {
        if ( d.put_in_general_cache() ) {
            return m_volatile_cell_cache;
        }
        return m_volatile_nf_cache;
    }

    inline optional_variant_type retrieve( const i_dependency& d, const volatile_cache_type& cache ) const {
        //assert( "value is not volatile but still wants to get its volatile cached value!" && d.is_volatile() );
        volatile_cache_type::const_iterator it( cache.find( &d ) );
        return it != cache.end() ? optional_variant_type( it->second ) : optional_variant_type();
    }

    inline void remove( const i_dependency& d, volatile_cache_type& cache ) {
        cache.erase( &d );
    }

private:
    volatile_cache_type m_volatile_cell_cache;
    volatile_cache_type m_volatile_nf_cache;
    cyclic_counter_type m_cyclic_counters;
    volatile_cache_type m_cyclic_cache;
    unsigned long m_calculation_token;
    cyclic_dependency_set m_cyclic_dependencies;
    bool m_view_independents_done;
};
