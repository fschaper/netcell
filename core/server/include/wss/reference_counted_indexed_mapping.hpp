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

#pragma once

#include <wss/indexed_mapping.hpp>
#include <wss/locked_object.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# if defined(BOOST_MSVC)

# pragma warning(push)
# pragma warning(disable:4800; disable:4311; disable:4312; disable:4244)
# endif

#   include <boost/atomic.hpp>

# if defined(BOOST_MSVC)
# pragma warning(pop)
# endif

#endif

template < class value_T >
class reference_counted_indexed_mapping
{
    class handle_index;
    typedef locked_object<indexed_mapping<value_T, handle_index> > locked_indexed_mapping_type;

    class referenced_handle
    {
    public:
        typedef boost::atomic<long> counter_type;

        referenced_handle()
            : m_shared_count( new counter_type( 1 ) )
            , m_mapping( NULL ) {}

        referenced_handle( const referenced_handle& other )
            : m_shared_count( other.m_shared_count )
            , m_mapping( other.m_mapping ) {
            ++( *m_shared_count );
        }

        ~referenced_handle() {
            switch ( ( --( *m_shared_count ) ) ) {
                case 0:
                    // this is the last object referring to the handle.
                    // do the cleanup work
                    delete m_shared_count;
                    m_shared_count = NULL;
                    break;

                case 1:
                    // the container is holding the last
                    // reference to the object.

                    // we may no longer access m_shared_count
                    // because erasing the container element will
                    // invoke case "1".
                    ( *( m_mapping->lock() ) ).erase( *this );
                    m_mapping = NULL;
                    break;

                default:
                    break;
            }
        }

        referenced_handle& operator =( const referenced_handle& rhs ) {
            referenced_handle tmp( rhs );
            swap( tmp );
            return *this;
        }

        void swap( referenced_handle& other ) {
            std::swap( m_shared_count, other.m_shared_count );
            std::swap( m_mapping, other.m_mapping );
        }

        bool operator ==( const referenced_handle& other ) const {
            return m_shared_count == other.m_shared_count;
        }

        bool operator !=( const referenced_handle& other ) const {
            return m_shared_count != other.m_shared_count;
        }

        bool operator <( const referenced_handle& other ) const {
            return m_shared_count < other.m_shared_count;
        }

        void arm( locked_indexed_mapping_type* mapping ) {
            m_mapping = mapping;
        }

    private:
        mutable counter_type* m_shared_count;
        locked_indexed_mapping_type* m_mapping;
    };

    class handle_index
    {
    public:
        typedef referenced_handle index_type;

        index_type create_new_index() {
            return index_type();
        }
    };

public:
    typedef referenced_handle index_type;
    typedef value_T value_type;

    value_type& operator []( const index_type& index ) {
        return ( *m_mapping.lock() )[ index ];
    }

    const value_type& operator []( const index_type& index ) const {
        return ( *m_mapping.lock() )[ index ];
    }

    index_type set( const value_type& v ) {
        index_type return_value = ( *m_mapping.lock() ).set( v );
        return_value.arm( &m_mapping );
        return return_value;
    }

private:
    locked_indexed_mapping_type m_mapping;
};
