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

#pragma once

#include <wss/non_instantiable.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <cassert>
# include <boost/pool/singleton_pool.hpp>
# if defined(WIN32)
#   include <boost/detail/interlocked.hpp>
# else
#   define BOOST_INTERLOCKED_INCREMENT( x )
#   define BOOST_INTERLOCKED_DECREMENT( x )
# endif
#endif

#define USE_POOLED_MEMORY 0

namespace memory
{
    typedef boost::default_user_allocator_malloc_free default_user_allocator_type;

    /*!
     * \brief
     * default allocation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template
    <
    class object_T
    >
    struct default_allocator
            : non_instantiable
    {
        typedef std::allocator<object_T> type;
    };

#ifdef _DEBUG
    /*!
     * \brief
     * memory allocation debugging.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class allocator_T>
    class allocator_debugging
    {
    public:
        allocator_debugging()
            : m_allocation_count( 0 ) {}


#if defined(_WSS_UNIT_TESTS)

        ~allocator_debugging();
#else
        ~allocator_debugging() {
            assert( "memory leaks detected!" && m_allocation_count == 0 );
        }
#endif
        inline void operator ++() {
            BOOST_INTERLOCKED_INCREMENT( &m_allocation_count );
        }

        inline void operator --() {
            BOOST_INTERLOCKED_DECREMENT( &m_allocation_count );
        }

        inline long count() const {
            return m_allocation_count;
        }

    private:
        volatile long m_allocation_count;
    };

#else
    /*!
     * \brief
     * dummy class for release builds.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class allocator_T>
    class allocator_debugging
    {
    public:
        allocator_debugging() {}

        ~allocator_debugging() {}

        void operator ++() {}

        void operator --() {}

        long count() const {
            return 0;
        }
    };
#endif // _DEBUG

    struct no_delete {};

    /*!
     * \brief
     * pooling object allocation class.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template
    <
    class object_T
    , size_t chunk_size = 500
    , class allocator_T = default_user_allocator_type
    >
    class pooled_creator
    {
    public:
        typedef allocator_T allocator_type;
        typedef boost::singleton_pool<object_T, chunk_size, allocator_type > pool_type;
        typedef object_T* pointer_type;
        typedef object_T& reference_type;

    public:
        static pointer_type create() {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T();
            return obj;
        }

        template<typename arg1_T>
        static pointer_type create( arg1_T& parameter ) {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T( parameter );
            return obj;
        }

        template<typename arg1_T, typename arg2_T>
        static pointer_type create( arg1_T& parameter1, arg2_T& parameter2 ) {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T( parameter1, parameter2 );
            return obj;
        }

        template<typename arg1_T, typename arg2_T, typename arg3_T>
        static pointer_type create( arg1_T& parameter1, arg2_T& parameter2, arg3_T& parameter3 ) {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T( parameter1, parameter2, parameter3 );
            return obj;
        }

        template<typename arg1_T, typename arg2_T, typename arg3_T, typename arg4_T>
        static pointer_type create( arg1_T& parameter1, arg2_T& parameter2, arg3_T& parameter3, arg4_T& parameter4 ) {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T( parameter1, parameter2, parameter3, parameter4 );
            return obj;
        }

        template<typename arg1_T, typename arg2_T, typename arg3_T, typename arg4_T, typename arg5_T>
        static pointer_type create( arg1_T& parameter1, arg2_T& parameter2, arg3_T& parameter3, arg4_T& parameter4, arg5_T& parameter5 ) {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T( parameter1, parameter2, parameter3, parameter4, parameter5 );
            return obj;
        }

        template<typename arg1_T, typename arg2_T, typename arg3_T, typename arg4_T, typename arg5_T, typename arg6_T>
        static pointer_type create( arg1_T& parameter1, arg2_T& parameter2, arg3_T& parameter3, arg4_T& parameter4, arg5_T& parameter5, arg6_T& parameter6 ) {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T( parameter1, parameter2, parameter3, parameter4, parameter5, parameter6 );
            return obj;
        }

        template<typename arg1_T, typename arg2_T, typename arg3_T, typename arg4_T, typename arg5_T, typename arg6_T, typename arg7_T>
        static pointer_type create( arg1_T& parameter1, arg2_T& parameter2, arg3_T& parameter3, arg4_T& parameter4, arg5_T& parameter5, arg6_T& parameter6, arg7_T& parameter7 ) {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T( parameter1, parameter2, parameter3, parameter4, parameter5, parameter6, parameter7 );
            return obj;
        }

        template<typename arg1_T, typename arg2_T, typename arg3_T, typename arg4_T, typename arg5_T, typename arg6_T, typename arg7_T, typename arg8_T>
        static pointer_type create( arg1_T& parameter1, arg2_T& parameter2, arg3_T& parameter3, arg4_T& parameter4, arg5_T& parameter5, arg6_T& parameter6, arg7_T& parameter7, arg8_T& parameter8 ) {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T( parameter1, parameter2, parameter3, parameter4, parameter5, parameter6, parameter7 );
            return obj;
        }

        static pointer_type clone( const pointer_type to_clone ) {
            ++m_allocation_count;
            void* ptr = pool_type::ordered_malloc();
            object_T* obj = new ( ptr ) object_T( *to_clone );
            return obj;
        }

        static void destroy( pointer_type ptr ) {
            if ( ptr ) {
                --m_allocation_count;
                ptr->~object_T();
                pool_type::free( reinterpret_cast<void*>( ptr ) );
            }
        }

        static void destroy( pointer_type ptr, no_delete ) {
            if ( ptr ) {
                --m_allocation_count;
                pool_type::free( reinterpret_cast<void*>( ptr ) );
            }
        }

        static void release_memory( bool purge = false ) {
            if ( !purge ) {
                pool_type::release_memory();
            } else {
                pool_type::purge_memory();
            }
        }

    private:
        static allocator_debugging<object_T> m_allocation_count;
    };

    /*!
     * \brief
     * boost ptr_* allocator policy for pool-created objects.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct pooled_heap_clone_allocator {
        template<class U>
        static U* allocate_clone( const U& r ) {
            return U::clone( &r );
        }

        template<class U>
        static void deallocate_clone( const U* r ) {
            const_cast<U*>( r )->destroy();
        }
    };
}

#include "allocation.ipp"



