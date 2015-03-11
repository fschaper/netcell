/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
*  \Author
*  Florian Schaper <florian.schaper@jedox.com>
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/

#pragma once

#include <string>
#include <utility> //pair
#include <map>
#include <set>

#include "textmetric_impl.hpp"

#include <wss/ci_string.hpp>
#include <wss/style_set.hpp>

/*!
* text_metric_intf
* class to calculate the space a given text with a given style will occupy
*
* \todo maybe cache fonts or styles somehow to speed things up!
*
* \author Frieder Hofmann <frieder.hofmann@jedox.com>
*/

namespace textmetric_internal
{

    class text_metric_intf
    {
    private:
        template< typename S >
        class known_keys
        {
        public:
            typedef typename std::set<  S > key_type;

            known_keys() {
                keys.insert( "font-weight" );
                keys.insert( "font-style" );
                keys.insert( "font-size" );
                keys.insert( "font-family" );
                keys.insert( "text-decoration" );
                m_end = this->keys.end();
            }

            bool find( const S& key ) const {
                return ( m_end != this->keys.find( key ) );
            }

        private:
            key_type keys;
            typename key_type::const_iterator m_end;
        };

        class is_known_val
        {
        public:
            bool operator()( std::pair< const std::string, const std::string> t ) const;
        };

        template< class S >
        inline S strip_units_copy( const S& str ) {
            if ( str.substr( str.size() - 2, 2 ) == "pt" ) {
                return str.substr( 0, str.size() - 2 );
            }
            if ( str.substr( str.size() - 2, 2 ) == "em" ) {
                return str.substr( 0, str.size() - 2 );
            }
            return str.substr( 0 );
        }

    public:
        //bounding box type
        typedef size_t height_type, width_type;
        typedef std::pair< width_type, height_type > bounding_box_type;

    public:

        /*!
        * \brief text_metric_intf
        *
        * \param default_style
        * The default style of the application, will be used if no
        * value is given in style
        *
        * \param style
        * The style to use, \note style directives given here will override
        * values in default_style

        * \param text
        * The text we want to calculate the size for
        *
        * \param old_style
        * optional, this can be compared to style and if nothing significant
        * has changed no recalculation is necessary
        *
        */
        text_metric_intf( const style_set_type& default_style, const style_set_type& style, const std::string& text, const unsigned int xdpi, const unsigned int ydpi );

        /*!
        * \brief get the bounding box of the text
        *
        * \note parse() has to be called before
        *
        * \returns
        * bounding box of the text using the style passed to the constructor
        * format is <width, height>
        *
        * \note if an empty string is passed to the constructor, the
        * bounding box is calculated for a blank " " with the style information,
        * to get the right height.
        *
        * \see text_metric_intf::parse
        */
        void parse();

        /*!
        * \brief get the width of the bounding box of the text
        *
        * \returns
        * width bounding box of the text using the style passed to the constructor
        */
        const int get_width() const;

        /*!
        * \brief get the height of the bounding box of the text
        *
        * \returns
        * height bounding box of the text using the style passed to the constructor
        */
        const int get_height() const;

        /*!
        * \brief check if the style passed to the constructors changed if
        * compared to old_style (passed to the constructor too)
        *
        */
        const bool style_changed() const;


    private:
        //the style used
        const style_set_type&               m_style;
        //the default style used in the application
        const style_set_type&               m_default_style;
        //resolution
        const unsigned int                  m_xdpi;
        const unsigned int                  m_ydpi;
        //the text
        std::string                         m_text;
        //bounding box of the text, this is calculated when parse() is  called.
        textmetric_internal::bounding_box   m_bbox;
    };

}; // namespace textmetric_internal
