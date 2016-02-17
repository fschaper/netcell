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
 *  Marko Stijak <marko.stijak@jedox.com>
 *  Vali Nitu <vali@yalos-solutions.com>
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "persistent_alignment.hpp"
#include <stdio.h>
#include <boost/lexical_cast.hpp>

namespace xlsx
{

    persistent_alignment::persistent_alignment( const ssmap& props )
    {
        indent = 0;
        ssmap::const_iterator   it;
        if ( ( it = props.find( "white-space" ) ) != props.end() ) {
            if ( "pre-wrap" == it->second ) {
                wrap.getset() = true;
            }
        }
        if ( ( it = props.find( "text-align" ) ) != props.end() ) {
            horizontal = it->second;
        }
        if ( ( it = props.find( "vertical-align" ) ) != props.end() ) {
            vertical = it->second;
        }
        if ( ( it = props.find( "text-indent" ) ) != props.end () ) {
            sscanf( it->second.c_str(), "%d", &indent.getset() );  // C4996
            //              indent = 0; //TODO: parse indent ??? pt, px ??? }
        }
    }

    void persistent_alignment::store( sml::CT_CellAlignment& ov )  const
    {
        if ( "left" == horizontal  ) {
            ov.horizontal = sml::ST_HorizontalAlignment::left;
        } else if ( "center" == horizontal ) {
            ov.horizontal = sml::ST_HorizontalAlignment::center;
        } else if ( "right" == horizontal ) {
            ov.horizontal = sml::ST_HorizontalAlignment::right;
        }

        if ( "top" == vertical ) {
            ov.vertical = sml::ST_VerticalAlignment::top;
        } else if ( "middle" == vertical ) {
            ov.vertical = sml::ST_VerticalAlignment::center;
        } else if ( "bottom" == vertical ) {
            ov.vertical = sml::ST_VerticalAlignment::bottom;
        }

        if ( 0 != indent ) {
            ov.indent = indent;
        }
        if ( wrap.present() && wrap.get() ) {
            ov.wrapText = true;
        }
    }

    persistent_alignment::persistent_alignment( const sml::CT_CellAlignment& node )
    {
        if ( node.horizontal.present() ) {

            switch ( node.horizontal.get() ) {
                case sml::ST_HorizontalAlignment::center:
                case sml::ST_HorizontalAlignment::centerContinuous:
                case sml::ST_HorizontalAlignment::distributed:
                case sml::ST_HorizontalAlignment::fill:
                case sml::ST_HorizontalAlignment::justify:
                    horizontal = "center";
                    break;
                case sml::ST_HorizontalAlignment::left:
                    horizontal = "left";
                    break;
                case sml::ST_HorizontalAlignment::right:
                    horizontal = "right";
                    break;
                default:
                    horizontal = "none";
                    break;
            }
        }

        if ( node.vertical.present() ) {
            switch ( node.vertical.get() ) {
                case sml::ST_VerticalAlignment::bottom:
                    vertical = "bottom";
                    break;
                case sml::ST_VerticalAlignment::top:
                    vertical = "top";
                    break;
                case sml::ST_VerticalAlignment::center:
                    vertical = "center";
                    break;
                case sml::ST_VerticalAlignment::justify:
                    vertical = "middle";
                    break;
                case sml::ST_VerticalAlignment::distributed:
                    vertical = "middle";
                    break;
            }
        }
        if ( node.indent.present() ) {
            indent = node.indent.get();
        }

        if ( node.wrapText.present() ) {
            wrap = node.wrapText.get();
        }

        if ( !horizontal.empty() ) {
            style_set.add( std::string( "text-align" ), horizontal );
        }
        if ( !vertical.empty() ) {
            style_set.add( std::string( "vertical-align" ), vertical );
        }
        if ( indent.present() ) {
            style_set.add( std::string( "text-indent" ),  boost::lexical_cast< std::string >( indent.get() ) + "em" );
        }
        if ( wrap.present() ) {
            if ( wrap.get() ) {
                style_set.add( std::string( "white-space" ), "pre-wrap" );
            }
        }

    }

    const std::string persistent_alignment::str() const
    {
        std::string result;
        if ( !horizontal.empty() ) {
            result += ( "text-align:" + horizontal + ";" );
        }
        if ( !vertical.empty() ) {
            result += ( "vertical-align:" + vertical + ";" );
        }
        if ( indent.present() ) {
            std::stringstream ss;
            ss << "text-indent:" << indent.get() << "em;";
            result += ss.str();
        }
        if ( wrap.present() ) {
            if ( wrap.get() ) {
                result +=  ( "white-space:pre-wrap;" );
            }
        }

        return result;
    }

}
