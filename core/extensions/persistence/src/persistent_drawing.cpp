/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 *  Vali Nitu <vali@yalos-solutions.com>
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "persistent_drawing.hpp"
#include <boost/filesystem/path.hpp>
#include <wss/session.hpp>
#include <wss/worksheet_element.hpp>
#include <wss/a1conversion.hpp>
#include <wss/json_unserializer.hpp>
#include <wss/variant_conversion_exception.hpp>
#include <xio/xercesc/istream.hpp>

#ifdef _MSC_VER
//inflate/deflate algorithms introduced through minizip
#ifdef _DEBUG
#define BOOST_ZLIB_BINARY "libminizip_d.lib"
#else
#define BOOST_ZLIB_BINARY "libminizip.lib"
#endif
#endif

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/detail/config/zlib.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/tokenizer.hpp>
#include <boost/math/special_functions/round.hpp>

namespace xlsx
{

    void persistent_drawing::persistent_two_cell_anchor::persistent_picture::deserialize( package::izpackage& package, export_helpers::relations& rels, key_value_vector_type& vals )
    {
        worksheet_element::key_value_type           crt_val;

        crt_val.first       = "img_type";

        boost::filesystem::path picture_file = boost::filesystem::path( "xl/drawings/" ) / boost::filesystem::path( rels.get( relID ) );
        picture_file.normalize();
        if ( ".jpg"  == picture_file.extension() || ".jpeg"  == picture_file.extension() ) {
            crt_val.second      = variant( "image/jpeg" );
            vals.push_back( crt_val );
        } else if ( ".png"  == picture_file.extension() ) {
            crt_val.second      = variant( "image/png" );
            vals.push_back( crt_val );
        } else if ( ".gif"  == picture_file.extension() ) {
            crt_val.second      = variant( "image/gif" );
            vals.push_back( crt_val );
        } else {
            return;
        }

        std::istream& img_file = package.get( picture_file.string() );
        std::streambuf& raw = package.get_buf( img_file );

        using namespace boost::iostreams;
        using namespace boost::archive::iterators;

        filtering_streambuf< input > binary_input;
        binary_input.push( zlib_compressor() );
        binary_input.push( raw );

        std::stringstream compressed_output;
        copy( binary_input, compressed_output );

        std::string payload = compressed_output.str();

        typedef
        base64_from_binary  <
        transform_width <    std::string::iterator, 6, sizeof( char ) * 8  >
        >   base64_t;

        switch ( payload.length() % 3 ) {
            case 1:
                payload += char ( 0 );
            case 2:
                payload += char ( 0 );
            default:
                break;
        }


        crt_val.first = "payload";
        crt_val.second = variant( std::string( base64_t( payload.begin() ), base64_t( payload.end() ) ) );
        vals.push_back( crt_val );
    }

    void persistent_drawing::persistent_two_cell_anchor::persistent_picture::serialize( session& s, package::opackage& package, export_helpers::relations& rels, worksheet_element& wselt )
    {
        std::string pic_id = boost::lexical_cast< std::string > ( id );
        worksheet_element::key_value_type    crt;

        crt = wselt.property( s, "img_type" );

        typedef boost::char_separator<char> separator;
        typedef boost::tokenizer< boost::char_separator< char > > tokenizer;
        tokenizer tokens( crt.second.string(), separator( "/" ) );

        tokenizer::iterator token_it = tokens.begin();
        token_it++;
        img_type = *token_it;
        name = "Picture " + pic_id;
        description = "image" + pic_id + "." + img_type;

        relID = rels.add(
                    "../media/" + description,
                    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" );

        try {
            crt = wselt.property( s, "hl" );

            if ( !crt.second.is_empty() && crt.second.string() != "" ) {
                const ci_key_value_map_type& img_props = json_unserializer::unserialize( crt.second.string() );

                std::string target = "";

                const ci_key_value_map_type& link_object = json_unserializer::unserialize( img_props.find( "\"link\"" )->second );
                const std::string json_target = json_unserializer::unserialize( link_object.find( "\"value\"" )->second ).find( "\"target\"" )->second;
                const ci_key_value_map_type& target_object = json_unserializer::unserialize( json_target );

                std::string target_mode = json_unserializer::unserialize( link_object.find( "\"value\"" )->second ).find( "\"type\"" )->second;
                target_mode = target_mode.substr( 1, target_mode.length() - 2 );

                if ( target_mode == "url" ) {
                    target_mode = "External";
                    target = json_target.substr( 1, json_target.length() - 2 );
                } else {
                    std::string path = target_object.find( "\"path\"" )->second;
                    target_mode = ( path != "\"SELF\"" ? "External" : "" );

                    path = path.substr( 1, path.length() - 2 );
                    std::string sheet = target_object.find( "\"sheet\"" )->second;
                    sheet = sheet.substr( 1, sheet.length() - 2 );
                    std::string sr = target_object.find( "\"range\"" )->second;
                    sr = sr.substr( 1, sr.length() - 2 );
                    if ( path == "SELF" ) {
                        target = "#" + sheet + "!" + sr;
                    } else {
                        target = path;
                    }

                }
                const std::string& hlink_relID = rels.add( target, target_mode, "http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink" );
                hlinkClick.getset();
                hlinkClick.get().id = hlink_relID;
                std::string tip = json_unserializer::unserialize( img_props.find( "\"tip\"" )->second ).find( "\"value\"" )->second;

                ci_key_value_map_type::const_iterator it = link_object.find( "\"cnt\"" );
                std::string target_frame = "\"_new\"";
                if ( it != link_object.end() ) {
                    target_frame = link_object.find( "\"cnt\"" )->second;
                }
                std::string trans = "{\"target\":" + json_target + ",\"text\":" + img_props.find( "\"text\"" )->second + ",\"tip\":"
                                    + img_props.find( "\"tip\"" )->second + ",\"trans\":" + img_props.find( "\"trans\"" )->second + "}";

                hlinkClick.get().tooltip = tip.substr( 1, tip.length() - 2 );
                hlinkClick.get().tgtFrame = target_frame.substr( 1, target_frame.length() - 2 );
                hlinkClick.get().action = trans;

            }
        } catch ( ... ) {}

        using namespace boost::iostreams;
        using namespace boost::archive::iterators;

        typedef
        transform_width <
        binary_from_base64< std::string::const_iterator>, 8, 6
        > binary_t;

        crt = wselt.property( s, "payload" );
        std::string enc_payload = crt.second.string();

        //TODO: can somebody explain this?
        std::replace( enc_payload.begin(), enc_payload.end(), '=', 'A' );

        std::string comp_payload( binary_t( enc_payload.begin() ), binary_t( enc_payload.end() ) );
        std::stringstream comp_stream( comp_payload );

        filtering_streambuf< input > stream_input;
        stream_input.push( zlib_decompressor() );
        stream_input.push( comp_stream );

        std::stringstream decompressed_payload;
        copy( stream_input, decompressed_payload );

        std::ostream&   img_file = package.get( "xl/media/" + description );

        img_file << decompressed_payload.str();
    }

    void persistent_drawing::persistent_marker::load( const dml::CT_Marker& src )
    {
        row.pos = static_cast<unsigned int>( src.row.get() ) >= UINT_MAX ? 0 : static_cast<unsigned int>( src.row.get() );
        row.offset = src.rowOff;
        col.pos = static_cast<unsigned int>( src.col.get() ) >= UINT_MAX ? 0 : static_cast<unsigned int>( src.col.get() );
        col.offset = src.colOff;
    }

    void persistent_drawing::persistent_marker::save( dml::CT_Marker& dst )
    {
        dst.row = static_cast<unsigned int>( row.pos ) >= UINT_MAX ? 0 : row.pos;
        dst.rowOff = row.offset;
        dst.col = static_cast<unsigned int>( col.pos ) >= UINT_MAX ? 0 : col.pos;
        dst.colOff = col.offset;
    }

    void persistent_drawing::persistent_two_cell_anchor::load( const dml::CT_TwoCellAnchor& src )
    {
        from.load( src.from );
        to.load( src.to );
        if ( src.pic.present() ) {
            dml::CT_NonVisualDrawingProps    props = src.pic.get().nvPicPr.cNvPr;
            persistent_picture               pic;

            pic.id = props.id;
            pic.description = props.descr;
            pic.name = props.name;
            pic.relID = src.pic.get().blipFill.blip.get().embed;
            pic.hlinkClick = props.hlinkClick.present() ? props.hlinkClick.get() : drawingml::CT_Hyperlink();
            picture = pic;
            if ( src.pic.get().nvPicPr.cNvPicPr.picLocks.present() ) {
                nomove = src.pic.get().nvPicPr.cNvPicPr.picLocks.get().noMove;
            } else {
                nomove = false;
            }
        }

    }

    void persistent_drawing::persistent_two_cell_anchor::save( dml::CT_TwoCellAnchor& dst )
    {
        from.save( dst.from );
        to.save( dst.to );
        dst.editAs = dml::ST_EditAs::oneCell;

        if ( picture.present() ) {
            persistent_picture              pic = picture.get();
            dml::CT_Picture                 dst_picture;
            dml::CT_NonVisualDrawingProps   props;

            dml::CT_NonVisualPictureProperties      cNvPicPr;
            dml::CT_PictureNonVisual                nvPicPr;
            dml::CT_PictureLocking                  pickLocks;

            props.id = pic.id;
            props.descr = pic.description;
            props.name = pic.name;

            nvPicPr.cNvPr = props;
            if ( pic.hlinkClick.present() ) {
                nvPicPr.cNvPr.hlinkClick = pic.hlinkClick;
            }
            //nvPicPr.cNvPicPr.picLocks.getset().noChangeAspect = true;
            pickLocks.noChangeAspect = true;
            pickLocks.noMove = nomove;
            cNvPicPr.picLocks = pickLocks;

            nvPicPr.cNvPicPr = cNvPicPr;

            dst_picture.nvPicPr = nvPicPr;

            dml::CT_BlipFillProperties   blipFill;

            dml::CT_Blip blip;
            blip.embed = pic.relID;
            dml::ST_BlipCompression cstate = dml::ST_BlipCompression::print;
            blip.cstate = cstate;

            blipFill.blip = blip;
            dml::CT_RelativeRect fill_rect;
            blipFill.stretch.getset().fillRect = fill_rect;

            dst_picture.blipFill = blipFill;

            dml::CT_ShapeProperties             spPr;
            dml::CT_PresetGeometry2D            prstGeom;
            dml::CT_GeomGuideList               avLst;

            prstGeom.prst = dml::ST_ShapeType::rect;
            prstGeom.avLst = avLst;
            spPr.prstGeom = prstGeom;


            dml::CT_Transform2D                 xfrm;
            dml::CT_Point2D                     off;
            dml::CT_PositiveSize2D              ext;

            off.x = 2371725;
            off.y = 1638300;
            xfrm.off = off;

            ext.cx = 1905000;
            ext.cy = 1435100;
            xfrm.ext = ext;

            spPr.xfrm = xfrm;

            dst_picture.spPr = spPr;

            dst.pic = dst_picture;
        }
    }

    std::string persistent_drawing::persistent_two_cell_anchor::media_type()
    {
        if ( !picture.present() ) {
            return "";
        }
        return picture.get().img_type;
    }

    void persistent_drawing::persistent_two_cell_anchor::deserialize( session& s, package::izpackage& package, export_helpers::relations& rels, worksheet_element& wselt, sheet_layout_manager& layout, unsigned int zorder  )
    {
        worksheet_element::key_value_vector_type    vals;
        worksheet_element::key_value_type           crt_val;

        crt_val.first       = "n_location";
        crt_val.second      = variant( "=" +
                                       a1conversion::to_a1::from_range(
                                           sheet_range(
                                               sheet_point( from.row.pos, from.col.pos, reference::absolute ),
                                               sheet_point( to.row.pos, to.col.pos, reference::absolute ) ) ) );
        vals.push_back( crt_val );

        crt_val.first   = "locked";
        crt_val.second = variant( nomove );

        vals.push_back( crt_val );

        if ( picture.present() ) {
            crt_val.first       = "e_type";
            crt_val.second      = variant( "img" );
            vals.push_back( crt_val );

            crt_val.first       = "pos_offsets";
            //TODO: session should have the DPI for correct offset calculation
            std::string offsets = "[" +
                                  boost::lexical_cast< std::string > ( boost::math::round( ( double ) from.col.offset / 9525 ) ) + "," +
                                  boost::lexical_cast< std::string > ( boost::math::round( ( double ) from.row.offset / 9525 ) ) + "," +
                                  boost::lexical_cast< std::string > ( boost::math::round( ( double ) to.col.offset / 9525 ) ) + "," +
                                  boost::lexical_cast< std::string > ( boost::math::round( ( double ) to.row.offset / 9525 ) ) + "]";
            crt_val.second      = variant( offsets );
            vals.push_back( crt_val );

            crt_val.first       = "size";

            long width = - ( long ) boost::math::round( ( double ) from.col.offset * 91 / 914400 );
            for ( unsigned int i = from.col.pos; i < to.col.pos; i++ ) {
                width += layout.column_width( i );
            }
            width += ( long ) boost::math::round( ( double ) to.col.offset / 9525/* * 91 / 914400*/ ) ;

            long height = - ( long ) boost::math::round( ( double ) from.row.offset / 9525 /** 91 / 914400*/ );
            for ( unsigned int i = from.row.pos; i < to.row.pos; i++ ) {
                height += layout.row_height( i );
            }
            height += ( long ) boost::math::round( ( double ) to.row.offset / 9525 /* * 91 / 914400*/ );

            crt_val.second      = variant( "[" +
                                           boost::lexical_cast< std::string >( width ) + "," +
                                           boost::lexical_cast< std::string >( height ) + "]" );

            vals.push_back( crt_val );

            picture.get().deserialize( package, rels, vals );

            crt_val.first = "zindex";
            crt_val.second = variant( ( double )zorder );
            vals.push_back( crt_val );

            foreach ( export_helpers::relations::relation rel, rels.list() ) {
                if ( rel.type.rfind( "/hyperlink" ) != rel.type.npos
                        && picture.get().hlinkClick.present() && picture.get().hlinkClick.get().id.present()
                        && picture.get().hlinkClick.get().id.get() == rel.id ) {
                    std::string lnk_t = "local";
                    std::string target = "\"" + rel.target + "\"";
                    std::string path = rel.target;

                    const ci_key_value_map_type& json_data = json_unserializer::unserialize( picture.get().hlinkClick.get().action );
                    bool is_native_link = false;
                    if ( json_data.size() == 4 ) {
                        is_native_link = true;
                    }

                    if ( rel.target_mode == "External" ) {
                        if ( path == "" || ( path[0] != ( '/' ) && ( path.find_first_of( "http://" ) != path.npos || path.find_first_of( "https://" ) != path.npos
                                                                     || path.find_first_of( "ftp://" ) != path.npos
                                                                     || path.find_first_of( "mailto:" ) != path.npos || path.find_first_of( "file://" ) != path.npos ) ) ) {
                            lnk_t = "url";
                            boost::replace_all( path, "\\", "/" );
                        }
                    }

                    if ( lnk_t == "local" ) {
                        std::string sheet = "";
                        size_t sheet_start = path.find( "#" );
                        size_t range_start = path.find( "!" );

                        if ( sheet_start != path.npos ) {
                            sheet = std::string( path.begin() + 1, path.begin() + range_start );
                            sheet = "\"" + sheet + "\"";
                        }

                        std::string range = "";
                        std::string ghnt = "null";
                        if ( sheet_start != path.npos && range_start != path.npos ) {
                            range = path.substr( range_start + 1 );
                            range = "\"" + range + "\"";
                        }

                        if ( rel.target_mode == "" && path.at( 0 ) != '/' ) {
                            path = "SELF";
                        } else {
                            if ( is_native_link ) {
                                const ci_key_value_map_type& target_object = json_unserializer::unserialize( json_data.find( "\"target\"" )->second );
                                sheet = target_object.find( "\"sheet\"" )->second;
                                range = target_object.find( "\"range\"" )->second;
                                ghnt = target_object.find( "\"ghnt\"" )->second;
                            } else {
                                sheet =  "null";
                                range = "\"A1\"";
                            }
                        }
                        target = "{\"path\":\"" + path + "\",\"sheet\":" + sheet +
                                 ",\"range\":" + range + ",\"ghnt\":" + ghnt + "}";
                    }

                    crt_val.first = "hl";
                    std::string trans = "[]";
                    if ( is_native_link ) {
                        trans = json_data.find( "\"trans\"" )->second;
                    }

                    std::string target_frame = "_new";
                    if ( picture.get().hlinkClick.get().tgtFrame != "" && picture.get().hlinkClick.get().tgtFrame != target_frame ) {
                        target_frame = picture.get().hlinkClick.get().tgtFrame;
                    }

                    std::string link_text_type = "\"string\"";
                    std::string link_text_value = "\"" + picture.get().name + "\"";
                    std::string link_tip_type = "\"string\"";

                    if ( is_native_link ) {
                        const ci_key_value_map_type& link_text_data = json_unserializer::unserialize( json_data.find( "\"text\"" )->second );
                        const ci_key_value_map_type& link_tip_data = json_unserializer::unserialize( json_data.find( "\"tip\"" )->second );
                        link_text_type = link_text_data.find( "\"type\"" )->second;
                        link_text_value = link_text_data.find( "\"value\"" )->second;
                        link_tip_type = link_tip_data.find( "\"type\"" )->second;
                    }

                    crt_val.second = variant ( "{\"dyn\":false,\"link\":{\"type\":\"obj\",\"cnt\":\""
                                               + target_frame +
                                               "\",\"value\":{\"type\":\""
                                               + lnk_t +
                                               "\",\"target\":" + target +
                                               "}},\"text\":{\"type\":" + link_text_type + ",\"value\":"
                                               +  link_text_value + "},\"tip\":{\"type\":" + link_tip_type + ",\"value\":\""
                                               +  picture.get().hlinkClick.get().tooltip + "\"},\"trans\":" + trans + "}"
                                             );
                    vals.push_back( crt_val );
                    break;
                }
            }

        }

        wselt.properties( s, vals );
    }

    sheet_point persistent_drawing::persistent_two_cell_anchor::compute_geometry(
        sheet_layout_manager& layout,
        const sheet_point& top_left,
        const unsigned int width,
        const unsigned int height,
        unsigned int& bottom_row_offset,
        unsigned int& bottom_col_offset )
    {
        unsigned int col = top_left.column();
        unsigned int row = top_left.row();
        unsigned int current_width = 0;
        unsigned int current_height = 0;

        while ( current_width + layout.column_width( col ) <= width ) {
            current_width += layout.column_width( col );
            col++;
        }

        bottom_col_offset = width - current_width;

        while ( current_height + layout.row_height( row ) <= height ) {
            current_height += layout.row_height( row );
            row++;
        }

        bottom_row_offset = height - current_height;

        return sheet_point( row, col );
    }

    void persistent_drawing::persistent_two_cell_anchor::serialize( session& s, package::opackage& package, export_helpers::relations& rels, worksheet_element& wselt, sheet_layout_manager& layout )
    {
        worksheet_element::key_value_type    crt;

        crt = wselt.property( s, "n_location" );

        typedef boost::char_separator<char> separator;
        typedef boost::tokenizer< boost::char_separator< char > > tokenizer;
        bool has_sheet_name = std::string::npos != crt.second.string().find( '!' );
        std::string separators( "=:" );
        if ( has_sheet_name ) {
            separators += "!";
        }
        tokenizer tokens( crt.second.string(), separator( separators.c_str() ) );


        tokenizer::iterator token_it = tokens.begin();
        if ( tokens.end() == token_it ) {
            throw std::logic_error( "Bad Formula" );
        }

        if ( has_sheet_name ) {
            token_it++;
            if ( tokens.end() == token_it ) {
                throw std::logic_error( "Bad Formula" );
            }
        }

        std::string from_a1 = *token_it;
        std::string from_col;
        std::string from_row;
        for ( std::string::const_iterator i = from_a1.begin(); i != from_a1.end(); i++ ) {
            if ( *i == '$' ) {
                continue;
            }
            if ( std::isdigit( *i ) ) {
                from_row += *i;
            } else {
                from_col += *i;
            }
        }

        from.col.pos = a1conversion::from_a1::column( from_col );
        from.row.pos = boost::lexical_cast< unsigned int >( from_row ) - 1;

        crt = wselt.property( s, "pos_offsets" );

        tokenizer offsets( crt.second.string(), separator( "[,]" ) );

        token_it = offsets.begin();
        unsigned int top_row_offset = 0;
        unsigned int top_col_offset = 0;
        unsigned int bottom_row_offset = 0;
        unsigned int bottom_col_offset = 0;
        unsigned int width = 0;
        unsigned int height = 0;

        //TODO: Session level DPI
        try {
            top_col_offset = boost::lexical_cast< unsigned int >( *token_it++ );
        } catch ( std::bad_cast ) {
            top_col_offset = 0;
        }
        from.col.offset = ( long ) top_col_offset * 9525;
        try {
            top_row_offset = boost::lexical_cast< unsigned int >( *token_it++ );
        } catch ( std::bad_cast ) {
            top_row_offset = 0;
        }
        from.row.offset = ( long ) top_row_offset  * 9525;

        crt = wselt.property( s, "size" );

        tokenizer sizes( crt.second.string(), separator( "[,]" ) );
        token_it = sizes.begin();

        try {
            width = boost::lexical_cast< unsigned int >( *token_it++ );
        } catch ( std::bad_cast ) {
            width = 0;
        }

        try {
            height = boost::lexical_cast< unsigned int >( *token_it++ );
        } catch ( std::bad_cast ) {
            height = 0;
        }

        sheet_point top_left( from.row.pos, from.col.pos );
        sheet_point bottom_right = compute_geometry( layout, top_left, width + top_col_offset, height + top_row_offset, bottom_row_offset, bottom_col_offset );

        to.row.pos = bottom_right.row();
        to.col.pos = bottom_right.column();

        to.row.offset = ( long ) bottom_row_offset  * 9525;
        to.col.offset = ( long ) bottom_col_offset  * 9525;

        crt = wselt.property( s, "locked" );

        try {
            nomove = crt.second == true;
        } catch ( variant_conversion_exception& ) {
            nomove = false;
        }
        persistent_picture tmp_picture;

        tmp_picture.id = id;
        tmp_picture.serialize( s, package, rels, wselt );
        picture = tmp_picture;

    }

    void persistent_drawing::load( const dml::CT_TwoCellAnchor& src )
    {
        two_cell_anchor.load( src );
    }

    void persistent_drawing::save( dml::CT_TwoCellAnchor& dst )
    {
        two_cell_anchor.save( dst );
    }

    persistent_drawing::persistent_drawing( const dml::CT_TwoCellAnchor& src, export_helpers::relations& rels, unsigned int id ) : rels( rels ), id( id )
    {
        two_cell_anchor.id = id;
        load( src );
    }

    void persistent_drawing::deserialize( session& s, package::izpackage& package, worksheet_element& wselt, sheet_layout_manager& layout, unsigned int zorder   )
    {
        two_cell_anchor.deserialize( s, package, rels, wselt, layout, zorder );
    }

    void persistent_drawing::serialize( session& s, package::opackage& package, worksheet_element& wselt, sheet_layout_manager& layout )
    {
        two_cell_anchor.serialize( s, package, rels, wselt, layout );
    }

    std::string persistent_drawing::media_type()
    {
        return two_cell_anchor.media_type();
    }

}
