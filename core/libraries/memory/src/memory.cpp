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

#include <wss/memory.hpp>
#include <exception>
#include <memory>
#include <new>

memory_callback_type g_allocation_callback = NULL;
memory_callback_type g_deallocation_callback = NULL;

/*!
 * \brief
 * memory header block
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct memory_header {
    int magic;
    std::size_t block_size;
    std::size_t payload_size;
};

/*!
 * \brief
 * operator new - throw
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void* operator new( std::size_t size ) throw( std::bad_alloc )
{
    allocation_payload payload;
    if ( g_allocation_callback ) {
        ( *g_allocation_callback )( size, payload );
    }

    void* ptr = malloc( size + sizeof( memory_header ) + payload.size );
    if ( ! ptr ) {
        if ( payload.size ) {
            free( payload.payload );
        }
        throw std::bad_alloc();
    }

    static_cast<memory_header*>( ptr )->magic = 0xc0de;
    static_cast<memory_header*>( ptr )->block_size = size;
    static_cast<memory_header*>( ptr )->payload_size = payload.size;
    ptr = static_cast<char*>( ptr ) + sizeof( memory_header );
    if ( payload.size ) {
        // copy the allocation payload to the end of the allocated block
        memcpy( static_cast<void*>( static_cast<char*>( ptr ) + size ), payload.payload, payload.size );
        free( payload.payload );
    }
    return ptr;
}

/*!
 * \brief
 * operator new - nothrow
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void* operator new( std::size_t size, const std::nothrow_t& ) throw()
{
    try {
        return ::operator new ( size );
    } catch ( const std::bad_alloc& ) {
    }
    return NULL;
}

/*!
 * \brief
 * operator array new
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void* operator new[]( std::size_t size ) throw( std::bad_alloc )
{
    return ::operator new( size );
}

/*!
 * \brief
 * operator array new - nothrow
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void* operator new[]( std::size_t size, const std::nothrow_t& ) throw()
{
    try {
        return ::operator new ( size );
    } catch ( const std::bad_alloc& ) {
    }
    return NULL;
}

/*!
 * \brief
 * operator delete
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void operator delete( void* ptr ) throw()
{
    if ( ptr != NULL ) {
        void* ptr_block = static_cast<char*>( ptr ) - sizeof( memory_header );
        if ( static_cast<memory_header*>( ptr_block )->magic == 0xc0de ) {
            if ( g_deallocation_callback ) {
                allocation_payload payload;
                payload.size = static_cast<memory_header*>( ptr_block )->payload_size;
                if ( static_cast<memory_header*>( ptr_block )->payload_size ) {
                    payload.payload = static_cast<char*>( ptr ) + static_cast<memory_header*>( ptr_block )->block_size;
                }
                ( *g_deallocation_callback )( static_cast<memory_header*>( ptr_block )->block_size, payload );
            }
            free( ptr_block );
        } else {
            // the memory has been allocated from some
            // place else.
            free( ptr );
        }
    }
}

/*!
 * \brief
 * operator delete
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void operator delete( void* p, std::size_t size ) throw()
{
    if ( p != NULL ) {
        ::operator delete( p );
    }
}

/*!
 * \brief
 * operator delete array
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void operator delete[]( void* p ) throw()
{
    if ( p != NULL ) {
        ::operator delete( p );
    }
}

/*!
 * \brief
 * operator delete array
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void operator delete[]( void* p, std::size_t size ) throw()
{
    if ( p != NULL ) {
        ::operator delete( p );
    }
}

void allocation_callback( memory_callback_type cb )
{
    g_allocation_callback = cb;
}

void deallocation_callback( memory_callback_type cb )
{
    g_deallocation_callback = cb;
}
