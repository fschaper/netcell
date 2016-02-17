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

#include "precompiled_header.hpp"
#include "lookup_functors.hpp"

bool is_equal( const variant& left, const variant& right )
{

    switch ( left.type() ) {
        case variant::type_double:
            return ( variant::type_double == right.type() )  && ( left.numeric() == right.numeric() );
        case variant::type_bool:
            return ( variant::type_bool == right.type() ) && ( left == right );
        case variant::type_string:
            return ( variant::type_string == right.type() ) && boost::iequals( left.string(), right.string() );
        default:
            return false;
    }
}

bool is_larger( const variant& left, const variant& right )
{

    switch ( left.type() ) {
        case variant::type_double:
            return ( variant::type_double == right.type() ) && ( left.numeric() > right.numeric() );
        case variant::type_bool:
            return ( variant::type_bool != right.type() ) || ( left.numeric() > right.numeric() );
        case variant::type_string:
            if ( left.string().empty() ) {
                return true;
            } else {
                if ( variant::type_bool == right.type() ) {
                    return false;
                } else {
                    //return ( variant::type_double == right.type() ) || !boost::is_iless( right.string(), left.string() );
                    return  ( variant::type_double == right.type() ) || boost::algorithm::lexicographical_compare( right.string(), left.string(), boost::is_iless() );
                }
            }
        default:
            return false;
    }
}

