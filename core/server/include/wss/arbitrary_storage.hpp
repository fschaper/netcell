/**
 *  \brief
 *  PHP/WSS bridge: application object macro wrapper
 *
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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

#include <wss/define.hpp>
#include <wss/locked_object.hpp>
#include <wss/arbitrary_storage_object_not_found_exception.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#   include <boost/thread/mutex.hpp>
#   include <string>
#   include <map>
#   ifndef _DEBUG
#       include <boost/unordered/unordered_map.hpp>
#   endif // _DEBUG
#endif

/*!
 * \brief
 * stores and retrieves session information to/from memory
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE arbitrary_storage
    : boost::noncopyable
{
public:
    typedef std::vector<char> storage_type;

    /*!
     * \brief
     * retrieve an element from the arbitrary storage.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    storage_type retrieve( const std::string& key ) const;

    /*!
     * \brief
     * stores an element in the arbitrary storage.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void store( const std::string& key, const storage_type& value );

    /*!
     * \brief
     * removed an element from storage.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void remove( const std::string& key );

private:
#ifdef _DEBUG
    typedef std::map<std::string, storage_type> storage_map_type;
#else
    typedef boost::unordered_map<std::string, storage_type> storage_map_type;
#endif // _DEBUG
    typedef locked_object<storage_map_type> locked_storage_map_type;
    locked_storage_map_type m_storage_map;
};
