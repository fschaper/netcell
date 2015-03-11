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
 *  <a href=<wss/http://www.jedox.com/license_palo_bi_suite.txt>>
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
#include "wss/vector_io_device.hpp"
#include "wss/invalid_seek_exception.hpp"
#include "wss/no_buffer_assigned_exception.hpp"

vector_io_device::vector_io_device()
    : m_buffer( NULL )
    , m_read_cursor( 0 )
    , m_write_cursor( 0 )
{}

vector_io_device::vector_io_device( buffer_type* buffer )
    : m_buffer( buffer )
    , m_read_cursor( 0 )
    , m_write_cursor( 0 )
{}

void vector_io_device::open( buffer_type* buffer )
{
    m_buffer = buffer;
    m_read_cursor = 0;
    m_write_cursor = 0;
}

void vector_io_device::close()
{
    m_buffer = NULL;
}

bool vector_io_device::is_open() const
{
    return m_buffer != NULL;
}

bool vector_io_device::eof() const
{
    return m_read_cursor == m_buffer->size();
}

vector_io_device::size_type vector_io_device::write( const char* ptr, size_type size )
{
    if ( ! m_buffer ) {
        throw no_buffer_assigned_exception();
    }

    if ( m_buffer->size() <= m_write_cursor + size ) {
        m_buffer->resize( m_write_cursor + size );
    }

    memcpy( &( *m_buffer )[ m_write_cursor ], ptr, size );
    m_write_cursor += size;
    return size;
}

vector_io_device::size_type vector_io_device::read( char* buffer, size_type size )
{
    if ( ! m_buffer ) {
        throw no_buffer_assigned_exception();
    }

    if ( m_buffer->size() < ( m_read_cursor + size ) ) {
        size = m_buffer->size() - m_read_cursor;
    }
    memcpy( reinterpret_cast<void*>( buffer ), reinterpret_cast<void*>( &( *m_buffer )[ m_read_cursor ] ), size );
    m_read_cursor += size;
    return size;
}

vector_io_device::size_type vector_io_device::size() const
{
    return m_buffer->size();
}

void vector_io_device::clear()
{
    buffer_type().swap( *m_buffer );
}

size_t vector_io_device::tellp() const
{
    return m_write_cursor;
}

void vector_io_device::seekp( int position, seek_type seek )
{
    switch ( seek ) {
        case seek_current:
            if ( position < 0 && ( m_write_cursor + position ) < 0 ) {
                throw invalid_seek_exception();
            }
            m_write_cursor += position;
            break;

        case seek_beginning:
            if ( position < 0 ) {
                throw invalid_seek_exception();
            }
            m_write_cursor = position;
            break;

        case seek_end:
            if ( position < 0 && ( m_buffer->size() + position ) < 0 ) {
                throw invalid_seek_exception();
            }
            m_write_cursor = m_buffer->size() + position;
            break;

        default:
            assert( !"unknown seek type!" );
    }
}

size_t vector_io_device::tellg() const
{
    return m_read_cursor;
}

void vector_io_device::seekg( int position, seek_type seek )
{
    switch ( seek ) {
        case seek_current:
            if ( position < 0 && ( m_read_cursor + position ) < 0 ) {
                throw invalid_seek_exception();
            }
            m_read_cursor += position;
            break;

        case seek_beginning:
            if ( position < 0 ) {
                throw invalid_seek_exception();
            }
            m_read_cursor = position;
            break;

        case seek_end:
            if ( position < 0 && ( m_buffer->size() + position ) < 0 ) {
                throw invalid_seek_exception();
            }
            m_read_cursor = m_buffer->size() + position;
            break;

        default:
            assert( !"unknown seek type!" );
    }
}

