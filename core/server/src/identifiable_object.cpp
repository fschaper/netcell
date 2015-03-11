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

#include "precompiled_header.hpp"
#include "wss/identifiable_object.hpp"
#include <boost/random.hpp>

#if __GNUC__== 4 && __GNUC_MINOR__== 4
uuid_type create_uuid()
#else
inline uuid_type create_uuid()
#endif
{
    static boost::uuids::basic_random_generator<boost::taus88> gen;
    return gen();
}

void identifiable_object::name( const utf8_ci_string& name )
{
    lock_type lock( m_mutex );
    if ( on_before_name_change( boost::ref( *this ), name ) == true ) {
        m_name = name;
    } else {
        throw invalid_name_exception();
    }
}

identifiable_object::identifiable_object( const utf8_ci_string& name )
    : m_name( name )
    , m_uuid( create_uuid() )
{}

bool identifiable_object::operator==( const identifiable_object& other ) const
{
    return this == &other;
}

bool identifiable_object::operator!=( const identifiable_object& other ) const
{
    return !( *this == other );
}

