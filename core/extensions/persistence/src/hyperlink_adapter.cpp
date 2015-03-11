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

#include "hyperlink_adapter.hpp"
#include <oxml/relationships_parser.hpp>
#include <wss/worksheet.hpp>
#include <wss/range.hpp>
#include <wss/a1conversion.hpp>

namespace xlsx
{

    bool hyperlink_adapter::load_relations( package::izpackage& package, const size_t idx, export_helpers::relations& relations )
    {
        std::stringstream rel_name;
        rel_name << "xl/worksheets/_rels/sheet" << idx << ".xml.rels";

        rels_ns::relationships relsDoc;
        ::xio::xml::binding::parser relParser;
        relParser.parse_doc( package.get( rel_name.str() ), relsDoc );
        if ( !relsDoc.Relationships.present() ) {
            return false;    //malformed archive
        }

        relations.deserialize( relsDoc.Relationships.get() );

        return true;
    }

    void hyperlink_adapter::make_url( session& s, shared_worksheet_type& ws, const sheet_point& cell, const std::string& url, const std::string& tip )
    {
        ::range crt = ws->range( cell );
        const std::string& text = crt.value( s ).as_string( s.locale() );
        const std::string link = "\"link\":{\"type\":\"obj\",\"cnt\":\"_new\",\"value\":{\"type\":\"url\",\"target\":\"" + url + "\"}}";
        const std::string display = "\"text\":{\"type\":\"string\",\"value\":\"" + text + "\"}";
        const std::string tooltip = "\"tip\":{\"type\":\"string\",\"value\":\"" + tip + "\"}";
        const std::string span = "<span class=\"hl\" onmouseover=\"Jedox.wss.hl.toolTip(event, true);\" onmouseout=\"Jedox.wss.hl.toolTip(event, false);\">" + text + "</span>";

        attribute_set_type  crt_attributes;
        crt_attributes.add( std::string( "\"mousedown\"" ), std::string( "[\"hl\",{\"dyn\":false" ) + "," + link + "," + display + "," + tooltip + ",\"trans\":[]}]" );

        crt.attribute( s, crt_attributes );

        crt.value( s, span );
    }

    void hyperlink_adapter::make_sheet( session& s, shared_worksheet_type& ws, const sheet_point& cell, const std::string& location, const std::string& tip )
    {
        std::string::size_type exclamation = location.find( '!' );
        if ( exclamation == std::string::npos ) {
            return;
        }
        ::range crt = ws->range( cell );
        const std::string& text = crt.value( s ).as_string( s.locale() );
        const std::string link = "\"link\":{\"type\":\"obj\",\"value\":{\"type\":\"local\",\"target\":{\"path\":\"SELF\",\"sheet\":\"" + location.substr( 0, exclamation ) + "\",\"range\":\"" + location.substr( exclamation + 1, location.size() ) + "\",\"ghnt\":null}}}";
        const std::string display = "\"text\":{\"type\":\"string\",\"value\":\"" + text + "\"}";
        const std::string tooltip = "\"tip\":{\"type\":\"string\",\"value\":\"" + tip + "\"}";
        const std::string span = "<span class=\"hl\" onmouseover=\"Jedox.wss.hl.toolTip(event, true);\" onmouseout=\"Jedox.wss.hl.toolTip(event, false);\">" + text + "</span>";

        attribute_set_type  crt_attributes;
        crt_attributes.add( std::string( "\"mousedown\"" ), std::string( "[\"hl\",{\"dyn\":false" ) + "," + link + "," + display + "," + tooltip + ",\"trans\":[]}]" );

        crt.attribute( s, crt_attributes );

        crt.value( s, span );
    }

    void hyperlink_adapter::from_tags( session& s, const size_t idx, shared_worksheet_type& ws, package::izpackage& package, const sml::CT_Worksheet& in_sheet )
    {
        if ( !in_sheet.hyperlinks.present() ) {
            return;
        }

        const std::vector< sml::CT_Hyperlink > hl = in_sheet.hyperlinks.get().hyperlink;


        for ( std::vector< sml::CT_Hyperlink >::const_iterator i = hl.begin(); i != hl.end(); ++i ) {
            const sheet_point cell = a1conversion::from_a1::cell( i->ref.get() );

            std::string tip( "" );
            if ( i->tooltip.present() ) {
                tip = i->tooltip.get().get();
            }

            if ( i->id.present() ) {
                std::string url( "" );
                export_helpers::relations relations;
                if ( load_relations( package, idx, relations ) ) {
                    url = relations.get( i->id.get() );
                }
                if ( !url.empty() ) {
                    make_url( s, ws, cell, url, tip );
                }
            } else if ( i->location.present() ) {
                make_sheet( s, ws, cell, i->location.get(), tip );
            }
        }
    }

    class attribute_deserializer
    {
    private:
        const std::string attribute;
        const size_t attribute_len;

        std::string internal_text;
        std::string internal_tip;
        std::string internal_url;
        std::string internal_path;

        void extract_something( const std::string& what, const size_t len, const std::string& terminator, std::string& where ) {
            size_t start = attribute.find( what );
            if ( std::string::npos != start ) {
                size_t stop = attribute.substr( start + len , attribute_len ).find( terminator );
                if ( std::string::npos != stop ) {
                    where = attribute.substr( start + len, stop );
                }
            }
        }

        void extract_text() {
            static const std::string text_marker( "\"text\":{\"type\":\"string\",\"value\":\"" );
            static const size_t text_marker_size = text_marker.size();

            extract_something( text_marker, text_marker_size, "\"}", internal_text );
        }

        void extract_tip() {
            static const std::string text_marker( "\"tip\":{\"type\":\"string\",\"value\":\"" );
            static const size_t text_marker_size = text_marker.size();

            extract_something( text_marker, text_marker_size, "\"}", internal_tip );
        }

        void extract_url() {
            static const std::string text_marker( "\"value\":{\"type\":\"url\",\"target\":\"" );
            static const size_t text_marker_size = text_marker.size();

            extract_something( text_marker, text_marker_size, "\"}", internal_url );
        }

        void extract_path() {
            static const std::string text_marker( "\"target\":{\"path\":\"SELF\",\"sheet\":\"" );
            static const size_t text_marker_size = text_marker.size();
            static const std::string range_marker( "\",\"range\":\"" );
            static const size_t range_marker_size = range_marker.size();

            extract_something( text_marker, text_marker_size, "\",\"ghnt", internal_path );

            size_t sep_pos = internal_path.find( range_marker );

            if ( sep_pos == std::string::npos ) {
                return;
            }

            internal_path.erase( sep_pos, range_marker_size );
            internal_path.insert( sep_pos, "!" );
        }
    public:
        attribute_deserializer( const std::string& attribute )
            : attribute( attribute )
            , attribute_len( attribute.size() )
            , internal_text( "" )
            , internal_tip( "" )
            , internal_url( "" )
            , internal_path( "" ) {
            extract_text();
            extract_tip();
            extract_url();
            if ( internal_url.empty() ) {
                extract_path();
            }
        }

        std::string& text() {
            return internal_text;
        }

        std::string& tip() {
            return internal_tip;
        }

        std::string& url() {
            return internal_url;
        }

        std::string& path() {
            return internal_path;
        }
    };

    void hyperlink_adapter::to_tags( session& s, const size_t idx, const std::vector< range >& hyperlinks, const shared_worksheet_type& ws, package::opackage& package, sml::CT_Worksheet& out_sheet, export_helpers::relations& sheet_rels )
    {
        for ( std::vector< range >::const_iterator i = hyperlinks.begin(); i != hyperlinks.end(); ++i ) {

            const variant attr = i->attribute();
            if ( !attr.is_array() ) {
                continue;
            }

            const variant::sparse_array_type&   att_array = attr.array();
            if ( att_array.empty() ) {
                continue;
            }

            variant::sparse_array_type::const_iterator att_array_begin = att_array.begin();
            if ( !att_array_begin->is_string() ) {
                continue;
            }

            attribute_deserializer prepared( att_array.begin()->string() );

            sml::CT_Hyperlink hl;

            hl.ref = a1conversion::to_a1::from_point( i->coverage().upper_left() );
            hl.tooltip = prepared.tip();

            if( prepared.url().empty() ) {

                hl.display = prepared.text();
                hl.location = prepared.path();

            } else {
                if ( prepared.url()[0] == 'h' || prepared.url()[0] == 'm' ) {
                    hl.id = sheet_rels.add( prepared.url(), "External", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink" );
                } else {
                    hl.id = sheet_rels.add( "http://" + prepared.url(), "External", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink" );
                }
            }

            out_sheet.hyperlinks.getset().hyperlink.push_back( hl );
        }
    }

}
