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
#include "wss/css_unserializer.hpp"
#include "wss/define.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/algorithm/string.hpp>
#   include <boost/foreach.hpp>
#   include <vector>
#   include <string>
#endif // HAS_PRECOMPILED_HEADER == 0

ci_key_value_map_type css_unserializer::unserialize( const std::string& css )
{
    typedef std::vector<std::string> css_vector_type;
    css_vector_type css_elements;
    boost::algorithm::split( css_elements, css, boost::is_from_range( ';', ';' ) );

    ci_key_value_map_type return_value;
    foreach( const std::string & v, css_elements ) {
        if ( false == v.empty() ) {
            css_vector_type pair;
            boost::algorithm::split( pair, v, boost::is_from_range( ':', ':' ) );
            if ( pair.size() == 2 ) {
                const std::string trimmed_key( boost::trim_copy( pair[ 0 ] ) );
                const std::string trimmed_value( boost::trim_copy( pair[ 1 ] ) );
                return_value[ convert_utf8_ci( trimmed_key ) ] = trimmed_value;
            }
        }
    }

    return return_value;
}

