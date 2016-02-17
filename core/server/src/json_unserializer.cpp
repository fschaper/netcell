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
#include "wss/define.hpp"
#include "wss/json_unserializer.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/spirit/include/phoenix1.hpp>
#   include <boost/spirit/include/classic_core.hpp>
#   include <boost/spirit/include/classic_actor.hpp>
#   include <boost/spirit/include/classic_utility.hpp>
#endif

ci_key_value_map_type json_unserializer::unserialize( const std::string& j )
{
    ci_key_value_map_type return_value;
    std::pair<utf8_ci_string, std::string> entry;

    // -- section migrated from c2. originally written in 2008 by Dragan Simic <dragan.simic@jedox.com>
    using namespace boost::spirit::classic;
    rule<> json_value;
    rule<> json_ddigit  = range_p( '0', '9' );
    rule<> json_hdigit  = json_ddigit | range_p( 'a', 'f' ) | range_p( 'A', 'F' );
    rule<> json_hnumber = ch_p( 'u' ) >> json_hdigit >> json_hdigit >> json_hdigit >> json_hdigit;
    rule<> json_escape  = ch_p( '\\' ) >> ( ch_p( '"' ) | '\\' | '/' | 'b' | 'f' | 'n' | 'r' | 't' | json_hnumber );
    rule<> json_char    = ~ch_p( '"' ) & ~ch_p( '\\' );
    rule<> json_string  = ch_p( '"' ) >> !( *( json_char | json_escape ) ) >> '"';
    rule<> json_number  = !ch_p( '-' ) >> ( '0' | ( range_p( '1', '9' ) >> *( json_ddigit ) ) ) >> !( '.' >> *( json_ddigit ) ) >> !( as_lower_d["e"] >> !sign_p >> *( json_ddigit ) );
    rule<> json_array   = ch_p( '[' ) >> !( json_value >> *( ',' >> json_value ) ) >> ']';
    rule<> json_item    = json_string >> ':' >> json_value;
    rule<> json_object  = ch_p( '{' ) >> !( json_item >> *( ',' >> json_item ) ) >> '}';
    json_value   = json_string | json_number | json_object | json_array | str_p( "true" ) | "false" | "null";

    rule<> json_item_entry  = ( ( json_string )[assign_a( entry.first )] >> ':' >> ( json_value )[assign_a( entry.second )] )[insert_at_a( return_value, entry.first, entry.second )];
    rule<> json_object_entry = ch_p( '{' ) >> !( json_item_entry >> *( ',' >> json_item_entry ) ) >> '}';

    parse( j.c_str(), json_object_entry, space_p );
    // -- //

    return return_value;
}
