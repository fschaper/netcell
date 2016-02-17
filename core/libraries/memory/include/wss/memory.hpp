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

#include <cstddef>

#ifdef WIN32
#   ifndef DO_EXPORT
#       define EXPORT __declspec( dllexport )
#   else
#       define EXPORT __declspec( dllimport )
#   endif
#else
#   define EXPORT
#endif

/*!
 * \brief
 * data to associate with the allocation
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct allocation_payload {
    allocation_payload()
        : size( 0 )
        , payload( NULL )
    {}

    std::size_t size;
    void* payload;
};

/*!
 * \brief
 * copy object to payload file
 *
 * \remarks
 * the callback functions may not allocate any memory using
 * the new operators. we may use malloc and free and placement
 * new though to create copies to objects/PODs that we may want
 * to associate with the allocation. remember however that the
 * objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class object_T>
bool make_payload( const object_T& obj, allocation_payload& pl )
{
    if ( pl.size != 0 ) {
        return false;
    }

    pl.size = sizeof( object_T );
    pl.payload = malloc( sizeof( object_T ) );
    new ( pl.payload ) object_T( obj );
    return true;
}

/*!
 * \brief
 * callback type for memory registration routines
 *
 * \remarks
 * the callback functions may not allocate any memory using the
 * new operators since that would lead to a recursive call
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef void( *memory_callback_type )( std::size_t, allocation_payload& );


/*!
 * \brief
 * callback for memory allocations
 *
 * \remarks
 * you may _not_ allocate memory via new during the execution
 * of the callback.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
EXPORT void allocation_callback( memory_callback_type cb );

/*!
 * \brief
 * callback for memory de-allocations
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
EXPORT void deallocation_callback( memory_callback_type cb );

