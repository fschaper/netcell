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
#include "border.hpp"
#include "border_utility.hpp"
#include <wss/conditional_format_manager.hpp>

namespace cf
{
    typedef boost::optional<style_set_type> optional_style_set_type;
    typedef boost::optional<bool> optional_bool_type;
    typedef boost::optional<conditional_format_border_type> optional_border_type;
    typedef std::map<border_types::type, std::string> border_map_type;
    /*!
    * \brief struct format_style_border_type
    * return type struct when queries for conditional formats are done
    *
    * \NOTE if format and style needs to be get its best to use one
    * query to get both instead of two separate queries from a performance point of view!
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    struct format_style_unlock_type
            : boost::noncopyable
            , boost::enable_shared_from_this<format_style_unlock_type> {

        inline void combine( const shared_format_style_unlock_type& other ) {
            if ( other->style ) {
                if ( style ) {
                    style->combine( *( other->style ) );
                } else {
                    style.reset( *( other->style ) );
                }
            }
            if ( other->border ) {
                if ( border ) {
                    border->combine( *( other->border ) );
                } else {
                    border.reset( *( other->border ) );
                }
            }

            //theres no way to combine a format, so the first one set wins!
            if ( !format && other->format ) {
                format.reset( *( other->format ) );
            }

            if ( other->unlocked ) {
                if ( !unlocked || !( *unlocked ) ) {
                    unlocked.reset( *( other->unlocked ) );
                }
            }

        }

        inline std::string style_str() const {
            return ( style ? style->serialize() : std::string( "" ) );
        }

        inline border_map_type return_border() const {
            border_map_type return_val;
            if ( border ) {
                const long _border_type_ = border->type();
                if ( border::check_border_type( _border_type_, border_types::top ) ) {
                    return_val.insert( std::make_pair( border_types::top, border->style( border_types::top ) ) );
                }
                if ( border::check_border_type( _border_type_, border_types::bottom ) ) {
                    return_val.insert( std::make_pair( border_types::bottom, border->style( border_types::bottom ) ) );
                }
                if ( border::check_border_type( _border_type_, border_types::left ) ) {
                    return_val.insert( std::make_pair( border_types::left, border->style( border_types::left ) ) );
                }
                if ( border::check_border_type( _border_type_, border_types::right ) ) {
                    return_val.insert( std::make_pair( border_types::right, border->style( border_types::right ) ) );
                }
            }
            return return_val;
        }

        inline std::string format_str() const {
            return format ? format->get() : "";
        }

        inline shared_format_style_unlock_type clone() {
            shared_format_style_unlock_type return_val( boost::make_shared<format_style_unlock_type>() );
            return_val->combine( shared_from_this() );
            return return_val;
        }

        optional_style_set_type style;
        optional_format_type format;
        optional_bool_type unlocked;
        optional_border_type border;
    };

} //namespace cf
