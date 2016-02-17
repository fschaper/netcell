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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once

#include <boost/thread/shared_mutex.hpp>

template < class Value_T >
class simple_allocator
{
public:
    static const size_t NOTHING;
private:
    typedef std::map< size_t, Value_T > map_type;

    typedef boost::shared_mutex shared_mutex_type;
    typedef boost::unique_lock< shared_mutex_type > write_lock;
    typedef boost::shared_lock< shared_mutex_type > read_lock;
    typedef boost::upgrade_lock< shared_mutex_type > read_write_lock;
    typedef boost::upgrade_to_unique_lock< shared_mutex_type > upgrade_lock;
public:
    void clear() {
        write_lock   lock( m_mutex );
        m_values.clear();
    }
    const Value_T& at( const size_t idx ) {
        static const Value_T empty;
        read_lock   lock( m_mutex );
        if ( NOTHING == idx ) {
            return empty;
        }
        return m_values.at( idx );
    }
    const size_t register_value( const Value_T& value ) {
        // todo:
        // until we can get boost 1.44 we'll only use write_lock for VS10
        // https://svn.boost.org/trac/boost/ticket/2501 is fixed for 1.44
        // there is also a patch available https://svn.boost.org/trac/boost/attachment/ticket/2501/2501.patch
#if defined(USING_VS_2010)
        write_lock   lock( m_mutex );
#else
        read_write_lock   lock( m_mutex );
#endif
        for ( typename map_type::const_iterator i = m_values.begin(), e = m_values.end(); i != e; i++ ) {
            if ( i->second == value ) {
                return i->first;
            }
        }

        size_t idx = 1;
        if ( !m_values.empty() ) {
            idx =  ( --m_values.end() )->first + 1;
        }

#if !defined(USING_VS_2010)
        upgrade_lock    write( lock );
#endif
        m_values[ idx ] = value;

        return idx;
    }
    const size_t register_value( const Value_T& value, size_t idx ) {
        write_lock   lock( m_mutex );
        m_values[ idx ] = value;
        return idx;
    }

    bool is_empty( Value_T val ) {
        return val.empty();
    }

    std::vector< size_t > empty_keys() {
        return std::vector< size_t >();
    }
private:
    shared_mutex_type m_mutex;
    map_type m_values;
};

