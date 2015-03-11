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
 *  Frieder Hofmann <frieder.Hofmann@jedox.com>
 */

#pragma once


#include <wss/type.hpp>
/*!
 * \brief
 * interface for a cached palo connection
 *
 * \author
 * Frieder Hofmann <frieder.Hofmann@jedox.com>
 */

struct i_cached_connection : boost::noncopyable {
    virtual ~i_cached_connection() {}
};

typedef boost::shared_ptr<i_cached_connection> shared_cached_connection_type;

struct connection_cache {
    typedef map_to_use<std::string, shared_cached_connection_type>::type palo_connection_cache_type;
    typedef palo_connection_cache_type::const_iterator const_iterator;
    typedef set_to_use<std::string>::type pinged_type;
    typedef set_to_use<std::string>::type unreachable_connection_type;

    inline void clear_pinged_and_unreachable_cache() {
        m_pinged.clear();
        m_unreachable.clear();
    }

    inline void clear_all() {
        m_cache.clear();
        clear_pinged_and_unreachable_cache();
    }

    inline bool get_pinged( const std::string& key ) const {
        return m_pinged.find( key ) != m_pinged.end();
    }

    inline void set_pinged( const std::string& key ) {
        m_pinged.insert( key );
    }

    inline bool is_unreachable( const std::string& key ) const {
        return m_unreachable.find( key ) != m_unreachable.end();
    }

    inline void set_unreachable( const std::string& key ) {
        m_unreachable.insert( key );
        m_pinged.erase( key );
        m_cache.erase( key );
    }

    inline void cache_connection( const std::string& key, const shared_cached_connection_type& connection ) {
        m_cache.insert( std::make_pair( key, connection ) );
    }

    inline void remove_connection( const std::string& key ) {
        m_cache.erase( key );
        m_pinged.erase( key );
        m_unreachable.erase( key );
    }

    inline const palo_connection_cache_type& internal_access() const {
        return m_cache;
    }

    palo_connection_cache_type m_cache;
    pinged_type m_pinged;
    unreachable_connection_type m_unreachable;
};
