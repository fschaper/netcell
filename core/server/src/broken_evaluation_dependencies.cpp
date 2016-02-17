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
*  and do not license and distribute their source op under the GPL, Jedox provides
*  a flexible OEM Commercial License.
*
*  \author
*  Radu Racariu <Radu@yalos-solutions.com>
*/

#include "precompiled_header.hpp"
#include "wss/i_dependency.hpp"
#include "wss/session.hpp"
#include "wss/broken_evaluation_dependencies.h"
#include "named_formula.hpp"


void broken_evaluation_dependencies::register_name_function( const std::string& function_name, const shared_dependency_type& dependency )
{
    locked_incomplete_dependency_map_type::access map( m_incomplete_dependencies );
    const std::string& function = to_upper_copy_utf8( function_name );
    incomplete_dependency_map_type::iterator it = ( *map ).find( function );
    if ( it == ( *map ).end() ) {
        weak_dependency_set_type set;
        set.insert( dependency );
        ( *map )[function] = set;
    } else {
        it->second.insert( dependency );
    }
}

void broken_evaluation_dependencies::notify( const std::string& function_name )
{
    locked_incomplete_dependency_map_type::access map( m_incomplete_dependencies );
    const std::string& function = to_upper_copy_utf8( function_name );
    incomplete_dependency_map_type::iterator it = ( *map ).find( function );
    if ( it != ( *map ).end() ) {
        foreach( const weak_dependency_type & wd, it->second ) {
            if ( shared_dependency_type sd = wd.lock() ) {
                if ( session* s = session::thread_session() ) {
                    if ( sd->type() == i_dependency::named_formula_type ) {
                        boost::shared_static_cast<named_formula>( sd )->value( *s, boost::shared_static_cast<named_formula>( sd )->formula( s->locale(),  sd->position() ), sd->position(), true );
                    } else {
                        sd->value( *s, sd->formula( s->locale() ), sd->position() );
                    }
                }
            }
        }
        ( *map ).erase( it );
    }
}
void broken_evaluation_dependencies::remove_dependency( const shared_dependency_type& dependency )
{
    locked_incomplete_dependency_map_type::access map( m_incomplete_dependencies );
    foreach( incomplete_dependency_map_type::value_type & val, *map ) {
        weak_dependency_set_type::iterator it = val.second.find( dependency );
        if (  it != val.second.end() ) {
            val.second.erase( it );
            if ( val.second.empty() ) {
                ( *map ).erase( val.first );
            }
        }
    }
}
