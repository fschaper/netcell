/**
 *  \file
 *  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
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

#include <wss/locked_object.hpp>
#include <wss/type.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/any.hpp>
# include <map>
#endif

class server;

/*!
 * \brief
 * registry of all objects derived from identifiable_object.
 *
 * (fschaper) would have liked to implement registration
 * and de-registration of the objects directly in identifiable-
 * object but then we might erroneously try to access an object during
 * destruction.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE object_registry
    : public boost::noncopyable
{
    friend class server;
public:
    /*!
     * \brief
     * return the object with the passed uuid.
     *
     * if the object can no longer be found in the registry
     * will return an empty object instead so you have to check
     * for this condition (nil).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    boost::any get( const uuid_type& id );

    /*!
     * \brief
     * register an object with the global registry.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class object_T>
    void set( object_T& obj ) {
        ( *m_container.lock() )[ obj->uuid() ] = boost::weak_ptr< typename object_T::element_type >( obj );
    }

    /*!
     * \brief
     * unregister an object from the global registry.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class object_T>
    void unset( object_T& obj ) {
        ( *m_container.lock() ).erase( obj.uuid() );
    }

    /*!
     * \brief
     * this value will be returned in case an object can not
     * be retrieved from the registry.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static const boost::any nil;

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    object_registry() {}

private:
    typedef locked_object<std::map<uuid_type, boost::any>, trait::boost_lock_trait<> > object_container_map_type;
    object_container_map_type m_container;
};
