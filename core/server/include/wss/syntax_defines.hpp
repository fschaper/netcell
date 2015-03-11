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

#include <wss/define.hpp>
#include <wss/allocation.hpp>
#include <wss/i_visitor.hpp>

#define CREATE_NODE( T ) \
    static auto_type create() { return auto_type( memory::pooled_creator<T>::create() ); }

#define DESTROY_NODE( T ) \
    void destroy() { memory::pooled_creator<T>::destroy( const_cast<T*>( this ) ); }

#define CLONE_NODE( T ) \
    auto_type clone() const { return auto_type( memory::pooled_creator<T>::clone( const_cast<T*>( this ) ) ); }

#define VISITABLE_NODE \
    void accept( i_visitor& v ) { v.visit( *this ); }

#define CREATE_DESTROY_CLONE_VISIT( T ) \
    CREATE_NODE( T ) \
    DESTROY_NODE( T ) \
    CLONE_NODE( T ) \
    VISITABLE_NODE

#define DESTROY_CLONE_VISIT( T ) \
    DESTROY_NODE( T ) \
    CLONE_NODE( T ) \
    VISITABLE_NODE

