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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/define.hpp>
#include <wss/type.hpp>
#include <wss/non_instantiable.hpp>

#include "border.hpp"
class border_utility : public non_instantiable
{
public:

#ifdef _DEBUG
    template<class border_T>
    static inline std::string short_type_to_css( const border_T& b ) {
        std::string ret_string;
        if ( border_T::check_border_type( b.type(), border_types::top ) ) {
            ret_string += "t";
        }
        if ( border_T::check_border_type( b.type(), border_types::bottom ) ) {
            ret_string += "b";
        }
        if ( border_T::check_border_type( b.type(), border_types::left ) ) {
            ret_string += "l";
        }
        if ( border_T::check_border_type( b.type(), border_types::right ) ) {
            ret_string += "r";
        }
        return ret_string;
    }

    template<class border_T>
    static inline void add_border_string( std::string& ret_string ) {
        ret_string.append( "border-" );
    }
#endif
    template<class border_T>
    static inline std::string type_to_css( const border_T& b ) {
        static border_style_flyweight_type empty_dummy( "" );
        std::string ret_string;
        if ( border_T::check_border_type( b.type(), border_T::border_type::top ) /*&& ! b.style( border_T::border_type::top ) == empty_dummy*/ ) {
            ret_string += "border-top:";
            //here should be bordertypetocss::to_css(border_T)
            ret_string += b.style( border_T::border_type::top );
            ret_string.push_back( ';' );
        }
        if ( border_T::check_border_type( b.type(), border_T::border_type::bottom ) /*&& ! b.style( border_T::border_type::bottom ) == empty_dummy*/ ) {
            ret_string += "border-bottom:";
            ret_string += b.style( border_T::border_type::bottom );
            ret_string.push_back( ';' );
        }
        if ( border_T::check_border_type( b.type(), border_T::border_type::left ) /*&& ! b.style( border_T::border_type::left ) == empty_dummy*/ ) {
            ret_string += "border-left:";
            ret_string += b.style( border_T::border_type::left );
            ret_string.push_back( ';' );
        }
        if ( border_T::check_border_type( b.type(), border_T::border_type::right ) /*&& ! b.style( border_T::border_type::right ) == empty_dummy*/ ) {
            ret_string += "border-right:";
            ret_string += b.style( border_T::border_type::right );
            ret_string.push_back( ';' );
        }
        return /*css_style_type*/( ret_string );
    }
    template<class border_T>
    static inline std::string type_to_css_only_left_and_top( const border_T& b ) {
        std::string ret_string;
        if ( border_T::check_border_type( b.type(), border_T::border_type::top ) /*&& ! b.style( border_T::border_type::top ) == empty_dummy*/ ) {
            ret_string += "border-top:";
            ret_string += b.style( border_T::border_type::top );
            ret_string.push_back( ';' );
        }
        if ( border_T::check_border_type( b.type(), border_T::border_type::left ) /*&& ! b.style( border_T::border_type::left ) == empty_dummy*/ ) {
            ret_string += "border-left:";
            ret_string += b.style( border_T::border_type::left );
            ret_string.push_back( ';' );
        }
        return ret_string;
    }


};
