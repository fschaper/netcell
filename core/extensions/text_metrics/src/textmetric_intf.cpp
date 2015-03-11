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


#include "textmetric_intf.hpp"
#include "textmetric_ftmgr.hpp"

//stl
#include <string>


#include <vector>
#include <list>
#include <set>
#include <algorithm>

//boost
#include <boost/lexical_cast.hpp>


namespace textmetric_internal
{

    text_metric_intf::text_metric_intf( const style_set_type& default_style, const style_set_type& style, const std::string& text , const unsigned int xdpi, const unsigned int ydpi )
        : m_style( style )
        , m_default_style( default_style )
        , m_xdpi( xdpi )
        , m_ydpi( ydpi )
    {
        if ( text.empty() ) {
            m_text = " ";
        } else {
            m_text = text;
        }
        m_bbox.width = 0;
        m_bbox.height = 0;
    }

    void text_metric_intf::parse()
    {
        bool has_family = false;
        //bool has_ident = false;
        bool has_style = false;
        bool has_weight = false;
        bool has_decoration = false;
        bool has_size = false;

        //todo: this is silly. let's do some caching
        textmetric_internal::style_map_type sm;

        for ( style_set_type::const_iterator i = m_style.begin(), e = m_style.end(); i != e; i++ ) {
            if ( "text-indent" == i->first ) {
                try {
                    int text_indent;
                    text_indent = boost::lexical_cast< int > ( strip_units_copy< std::string >( i->second ) );
                    sm["text-indent"] = boost::lexical_cast< std::string > ( text_indent );
                } catch  ( boost::bad_lexical_cast& ) {
                    //discard
                }
            }

            if ( "font-family" == i->first ) {
                has_family = true;
                sm["font-family"] = i->second;
                continue;
            }

            if ( "font-style" == i->first ) {
                has_style = true;
                sm["font-style"] = ( "italic" == i->second ? "italic" : "normal" );
                continue;
            }

            if ( "font-weight" == i->first ) {
                has_weight = true;
                sm["font-weight"] = ( "bold" == i->second ? "800" : "normal" );
                continue;
            }

            if ( "text-decoration" == i->first ) {
                has_decoration = true;
                sm["text-decoration"] = ( "underline" == i->second ? "underline" : "normal" );
                continue;
            }

            if ( "font-size" == i->first ) {
                has_size = true;
                try {
                    int size;
                    size = boost::lexical_cast< int > ( strip_units_copy< std::string >( i->second ) );
                    sm["font-size"] = boost::lexical_cast< std::string > ( size );
                } catch  ( boost::bad_lexical_cast& ) {
                    sm["font-size"] = "10";
                }
                continue;
            }
        }

        if ( !has_family || !has_style || !has_weight || !has_decoration || !has_size ) {
            for ( style_set_type::const_iterator i = m_default_style.begin(), e = m_default_style.end(); i != e; i++ ) {
                if ( has_family && has_style && has_weight && has_decoration && has_size ) {
                    break;
                }

                if ( "font-family" == i->first ) {
                    if ( has_family ) {
                        continue;
                    }
                    has_family = true;
                    sm["font-family"] = i->second;
                    continue;
                }

                if ( "font-style" == i->first ) {
                    if ( has_style ) {
                        continue;
                    }
                    has_style = true;
                    sm["font-style"] = ( "italic" == i->second ? "italic" : "normal" );
                    continue;
                }

                if ( "font-weight" == i->first ) {
                    if ( has_weight ) {
                        continue;
                    }
                    has_weight = true;
                    sm["font-weight"] = ( "bold" == i->second ? "800" : "normal" );
                    continue;
                }

                if ( "text-decoration" == i->first ) {
                    if ( has_decoration ) {
                        continue;
                    }
                    has_decoration = true;
                    sm["text-decoration"] = ( "underline" == i->second ? "underline" : "normal" );
                    continue;
                }

                if ( "font-size" == i->first ) {
                    if ( has_size ) {
                        continue;
                    }
                    has_size = true;
                    try {
                        int size;
                        size = boost::lexical_cast< int > ( strip_units_copy< std::string >( i->second ) );
                        sm["font-size"] = boost::lexical_cast< std::string > ( size );
                    } catch  ( boost::bad_lexical_cast& ) {
                        sm["font-size"] = "10";
                    }
                    continue;
                }
            }
        }
        textmetric_internal::text_metric mytm( sm, m_xdpi, m_ydpi );
        m_bbox = mytm.get_bounding_box( m_text );
    }

    const int text_metric_intf::get_width() const
    {
        return m_bbox.width;
    }

    const int text_metric_intf::get_height() const
    {
        return m_bbox.height;
    }

}; // namespace textmetric_internal

