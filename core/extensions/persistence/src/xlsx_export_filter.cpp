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

#include "xlsx_export_filter.hpp"
#include "oxml_utils.hpp"
#include "hyperlink_adapter.hpp"
#include <wss/used_range.hpp>
#include <wss/conditional_format_manager.hpp>
#include "persistent_conditional_formats.hpp"
#include <oxml/sml-workbook.hpp>
#include <oxml/custom_data.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/regex.hpp>
#include <oxml/dml-spreadsheetDrawing_serializer.hpp>
#include "wss/get_conditional_format.hpp"
#include "persistent_drawing.hpp"
#include <wss/a1conversion.hpp>
#define foreach BOOST_FOREACH
#include "wss/worksheet.hpp"
#include "wss/worksheet_element_storage.hpp"
#include "wss/i_named_formula_manager.hpp"
#include "wss/workbook.hpp"
#include "wss/worksheet_element.hpp"
#include "wss/export_exception.hpp"

#include "xercesc/dom/DOM.hpp"
XERCES_CPP_NAMESPACE_USE

void trim_hyperlink( std::string& value )
{
    size_t start = value.find( '>' );
    if ( std::string::npos == start ) {
        return;
    }
    size_t stop = value.find( '<', start );
    if ( std::string::npos == stop ) {
        return;
    }
    value = value.substr( start + 1, stop - start - 1 );
}

namespace xlsx
{
    static boost::regex match_atChr_regex( "(?<![a-zA-Z0-9])@(?=\\w)" );
    static std::string wss_var_export_prefix( "__wss_exported_variable_" );

    void xlsx_export_filter::do_export( session& s, workbook& wb, const boost::filesystem::path& out_file, const bool as_snapshoot/* = false*/, const bool is_native )
    {
        XMLPlatformUtils::Initialize();
        m_is_native = is_native;
        try {
            package::ozpackage ozpackage( out_file.string() );
            this->m_export_file = out_file;
            internal_export( s, wb, ozpackage, as_snapshoot );
        } catch ( std::exception& e ) {
            throw export_exception( e.what() );
        } catch ( ... ) {
            throw export_exception();
        }
    }

    void xlsx_export_filter::clear()
    {
        m_defined_names.clear();
        m_shared_strings.clear();
        m_styles.clear();
        m_doc_rels.clear();
        m_doc_ctypes.clear();
        m_wb_rels.clear();
        m_pic_id = 1;
    }

    void xlsx_export_filter::set_dummy_styles()
    {
        m_styles.set_dummies();
    }

    void xlsx_export_filter::store_core_properties( std::ostream& os )
    {
        os << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
        os << "<cp:coreProperties xmlns:cp=\"http://schemas.openxmlformats.org/package/2006/metadata/core-properties\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:dcmitype=\"http://purl.org/dc/dcmitype/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">";
        os << "</cp:coreProperties>";
    }

    void xlsx_export_filter::store_extended_properties( std::ostream& os )
    {
        os << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
        os << "<Properties xmlns=\"http://schemas.openxmlformats.org/officeDocument/2006/extended-properties\" xmlns:vt=\"http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes\">";
        os << "</Properties>";
    }

    void xlsx_export_filter::init_relations()
    {
        m_doc_rels.add( "docProps/core.xml", "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties" );
        m_doc_rels.add( "docProps/app.xml", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties" );
        m_doc_rels.add( "xl/workbook.xml", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument" );

        m_doc_ctypes.add( "/docProps/core.xml", "application/vnd.openxmlformats-package.core-properties+xml" );
        m_doc_ctypes.add( "/docProps/app.xml", "application/vnd.openxmlformats-officedocument.extended-properties+xml" );
        m_doc_ctypes.add( "/xl/workbook.xml", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml" );
    }

    void xlsx_export_filter::write_globals( package::opackage& package )
    {
        //store shared strings
        m_wb_rels.add( "sharedStrings.xml", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/sharedStrings" );
        m_doc_ctypes.add( "/xl/sharedStrings.xml", "application/vnd.openxmlformats-officedocument.spreadsheetml.sharedStrings+xml" );
        m_shared_strings.store( package.get( "xl/sharedStrings.xml" ) );

        //store styles
        m_wb_rels.add( "styles.xml", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles" );
        m_doc_ctypes.add( "/xl/styles.xml", "application/vnd.openxmlformats-officedocument.spreadsheetml.styles+xml" );
        m_styles.store( package.get( "xl/styles.xml" ) );

        //store content types
        m_doc_ctypes.serialize( package.get( "[Content_Types].xml" ) );

        //store core.xml and app.xml
        store_core_properties( package.get( "docProps/core.xml" ) );
        store_extended_properties( package.get( "docProps/app.xml" ) );

        //store workbook relationships
        m_wb_rels.serialize( package.get( "xl/_rels/workbook.xml.rels" ) );

        //store document relationships
        m_doc_rels.serialize( package.get( "_rels/.rels" ) );
    }

    void xlsx_export_filter::stamp_default_height( const shared_worksheet_type& ws, sml::CT_SheetFormatPr& out_sfpr )
    {
        out_sfpr.defaultRowHeight =  oxml_utils::px2pt( ws->layout().default_row_height() );
        out_sfpr.customHeight = true;
    }

    typedef std::pair< shared_worksheet_element_type, double > img_elt;

    bool img_elt_smaller_pred( const img_elt& left, const img_elt& right )
    {
        return left.second < right.second;
    }

    void xlsx_export_filter::translate_worksheetelements( session& s, sml::CT_Worksheet& out_ws, int sheet_id, const shared_worksheet_type& ws, package::opackage& package, export_helpers::relations& sheet_rels )
    {

        std::vector< img_elt >      images;
        sml::CT_Drawing             drawing;

        foreach( const shared_worksheet_element_type & wse, ws->elements().list_all_elements( ) ) {
            worksheet_element::key_value_type    crt = wse->property( s, "e_type" );
            if ( variant( "img" ) == crt.second ) {
                try {
                    crt = wse->property( s, "zindex" );
                    images.push_back( img_elt( wse, static_cast<unsigned int>( crt.second.as_double() ) ) );
                } catch ( worksheet_element_exception& ) {
                    //default to something here
                    images.push_back( img_elt( wse, 51 ) );
                }
            }
        }


        if ( images.empty() ) {
            return;
        }

        std::sort( images.begin(), images.end(), img_elt_smaller_pred );


        drawing.id = sheet_rels.add(
                         "../drawings/drawing" + boost::lexical_cast< std::string >( sheet_id ) + ".xml",
                         "http://schemas.openxmlformats.org/officeDocument/2006/relationships/drawing" );
        out_ws.drawing = drawing;

        dml::dml_spreadsheetDrawing     drawings_doc;
        dml::CT_Drawings                drawings;

        export_helpers::relations       drawing_rels;

        foreach( const img_elt & wse, images ) {
            dml::CT_TwoCellAnchor   out_image;
            persistent_drawing      drawing( out_image, drawing_rels, m_pic_id++ );
            drawing.serialize( s, package, *( wse.first ), ws->layout() );
            drawing.save( out_image );
            drawings.twoCellAnchor.push_back( out_image );
            m_doc_ctypes.register_img_extension( drawing.media_type() );
        }

        drawings_doc.wsDr = drawings;

        serialize_doc( package.get( "xl/drawings/drawing" + boost::lexical_cast< std::string >( sheet_id ) + ".xml" ), drawings_doc );

        std::stringstream drawing_rel_name;
        drawing_rel_name << "xl/drawings/_rels/drawing" << sheet_id << ".xml.rels";
        drawing_rels.serialize( package.get( drawing_rel_name.str() ) );
        m_doc_ctypes.add( "/xl/drawings/drawing" + boost::lexical_cast< std::string > ( sheet_id ) + ".xml", "application/vnd.openxmlformats-officedocument.drawing+xml" );
    }

    void xlsx_export_filter::do_one_worksheet( session& s, sml::CT_Sheets& sheets, int sheet_id, const shared_worksheet_type& ws, package::opackage& package, const bool as_snapshoot/* = false*/ )
    {

        std::stringstream               sheetNames;
        std::string                     sheetName;
        std::string                     ws_rid;
        sml::CT_Sheet                   out_sheet;
        export_helpers::relations       extended_data;
        sml::custom_data                ed_doc;
        sml::CT_extended_data&          out_ed = ed_doc.extended_data.getset();

        m_hyperlink_cells.clear();

        sheetNames << "sheet" << sheet_id;

        sheetName = sheetNames.str();

        ws_rid = m_wb_rels.add(
                     "worksheets/" + sheetName + ".xml",
                     "http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet" );

        m_doc_ctypes.add( "/xl/worksheets/" + sheetName + ".xml", "application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml" );

        out_sheet.name = convert_utf8_ci( ws->name() );
        out_sheet.sheetId = sheet_id;
        out_sheet.id = ws_rid;


        sml::sml_sheet sheetDoc;
        sml::CT_Worksheet& out_ws = sheetDoc.worksheet.getset();
        sml::CT_SheetData& out_sd = out_ws.sheetData;

        //prepare array formula master cells
        array_formula_master_cells.clear();
        rectangle_list_type array_region_list = ws->array_region_list();

        for ( rectangle_list_type::const_iterator  i = array_region_list.begin(); i != array_region_list.end(); i++ ) {
            unsigned int c1 = i->upper_left().column();
            unsigned int r1 = i->upper_left().row() + 1;
            unsigned int c2 = i->lower_right().column();
            unsigned int r2 = i->lower_right().row() + 1;

            std::string cref = oxml_utils::cell_reference( c1, r1 );
            std::string rref = oxml_utils::range2string( c1, r1, c2, r2 );

            //for single cell array formula ref is cell ref, not range ref
            array_formula_master_cells[cref] = ( c1 < c2 || r1 < r2 ) ? rref : cref;
        }

        optional_sheet_range_type used_range = ws->used_range( used_range::cell | used_range::style | used_range::lock, false );

        sheet_point::integer_type   row_start = -1;
        sheet_point::integer_type   row_stop = -1;

        sheet_point::integer_type   col_start = -1;
        sheet_point::integer_type   col_stop = -1;


        //TODO: write a better alg as we will have more time to spare. for the time being we only have 256 columns;
        //prefere simplicity right now
        sml::CT_Cols out_cols;
        sheet_layout_manager& layout = ws->layout();
        style_manager_type& style = ws->style();
        m_full_cols.clear();
        const unsigned int default_col_width = layout.default_column_width();
        for ( unsigned int i = 0; i <= sheet_dimension::max_column; i++ ) {
            unsigned int        width = layout.column_width( i );
            const bool has_width = width != default_col_width;

            const bool has_style = ( size_t ) - 1  != style.get_col_background_key( i );

            if ( has_style ) {
                m_full_cols.push_back( i );
            }

            if ( has_width || has_style ) {
                sml::CT_Col         out_col;

                if ( 0 == width ) {
                    out_col.hidden = true;
                    width = layout.hidden_column_width( i );
                }

                double              chars = ( int )( width * 256.0 / oxml_utils::default_char_max_width ) / 256.0; //stupid sml formula


                out_col.min = i + 1;
                out_col.max = i + 1;
                out_col.width = chars;

                if ( has_style  ) {
                    const style_set_type& def_style =  ws->style().get_col_background( i );

                    if ( def_style.empty() ) {
                        out_col.style =  m_styles.get_empty_style();
                    } else {
                        out_col.style = m_styles.register_style( def_style.serialize( false ) );
                    }
                }
                out_col.customWidth = has_width;
                out_cols.col.push_back( out_col );
            }
        }

        if ( !out_cols.col.empty() ) {
            out_ws.cols.push_back( out_cols );
        }


        if ( used_range ) {
            const sheet_point&                                  ul = used_range->upper_left();
            const sheet_point&                                  lr = used_range->lower_right();
            row_start = ul.row();
            col_start = ul.column();
            row_stop = lr.row();
            col_stop = lr.column();

            optional_sheet_range_type used_vals = ws->used_range( used_range::cell, false );
            if ( used_vals ) {
                m_min_val_col = used_vals->upper_left().column();
                m_max_val_col = used_vals->lower_right().column();
            } else {
                m_min_val_col = m_max_val_col = -1;
            }

            optional_sheet_range_type used_styles = ws->used_range( used_range::style | used_range::lock, false );
            if ( used_styles ) {
                m_min_style_col = used_styles->upper_left().column();
                m_max_style_col = used_styles->lower_right().column();
            } else {
                m_min_style_col = m_max_style_col = -1;
            }

            const sheet_point::integer_type layout_row_start = ws->style().min_row();
            const sheet_point::integer_type layout_row_stop = ws->style().max_row();

            if ( row_start > layout_row_start ) {
                row_start = layout_row_start;
            }

            if ( row_stop < layout_row_stop ) {
                row_stop = layout_row_stop;
            }

            std::map<sheet_point, bool> all_val_cells_map;
            {
                const worksheet::existing_cell_list_type& all_cells_vec = ws->existing_cells();
                for ( worksheet::existing_cell_list_type::const_iterator it = all_cells_vec.begin(); it != all_cells_vec.end(); ++it ) {
                    all_val_cells_map.insert( std::pair<sheet_point, bool>( *it, true ) );
                }
            }
            for ( sheet_point::integer_type row = row_start; row <= row_stop; row++ ) {
                sml::CT_Row             out_row;
                if ( add_row( s, out_row, ws, row, ul.column(), lr.column(), all_val_cells_map, as_snapshoot ) ) {
                    out_sd.row.push_back( out_row );
                }
            }

            process_merged_cells( ws, out_ws );

        }

        process_conditional_formats( s, ws, out_ws );

        const sheet_layout_manager::sparse_indexed_container_type&  rows = ws->layout().rows();
        if ( 0 != rows.size() ) {

            for ( sheet_layout_manager::sparse_indexed_container_type::const_iterator i = rows.begin(); i != rows.end(); i++ ) {
                if ( ( sheet_point::integer_type )i->first >= row_start && ( sheet_point::integer_type )i->first <= row_stop ) {
                    continue;
                }
                sml::CT_Row             out_row;

                out_row.r = i->first + 1;

                out_row.ht              = oxml_utils::px2pt( i->second );
                out_row.customHeight    = true;
                out_sd.row.push_back( out_row );
            }
        }

        translate_worksheetelements( s, out_ws, sheet_id, ws, package, extended_data );

        if ( !m_hyperlink_cells.empty() ) {
            hyperlink_adapter::to_tags( s, sheet_id, m_hyperlink_cells, ws, package, out_ws, extended_data );
        }

        m_defined_names.register_names( ws->parent()->named_formulas().get_all( s, ws->uuid() ), sheet_id - 1, s.locale() );

        stamp_default_height( ws, out_ws.sheetFormatPr.getset() );

        extended_data.add( "../embeddings/embeddedObject" + sheetName + ".xml", "http://../oleObject" );
        if ( 1 == sheet_id ) {
            //introduce the relation for workbook extended data
            extended_data.add( "../embeddings/embeddedObjectWorkbook.xml", "http://../oleObject" );
        }
        extended_data.serialize( package.get( "xl/worksheets/_rels/" + sheetName + ".xml.rels" ) );

        ws->serialize( s, out_ed );
        serialize_doc( package.get( "xl/embeddings/embeddedObject" + sheetName + ".xml" ), ed_doc );

        sheets.sheet.push_back( out_sheet );

        serialize_doc( package.get( "xl/worksheets/" + sheetName + ".xml" ), sheetDoc );
    }

    void xlsx_export_filter::process_merged_cells( const shared_worksheet_type& ws, sml::CT_Worksheet& out_ws )
    {
        rectangle_list_type                all_mc      = ws->merged_range_list();

        if ( all_mc.empty() ) {
            return;
        }

        sml::CT_MergeCells out_mcells = out_ws.mergeCells.getset();
        out_mcells.count = ( int )all_mc.size();

        foreach( const sheet_range & range, all_mc ) {
            sml::CT_MergeCell out_mcell;

            int c1 = range.upper_left().column();
            int r1 = range.upper_left().row() + 1;
            int c2 = range.lower_right().column();
            int r2 = range.lower_right().row() + 1;
            std::string cref = oxml_utils::cell_reference( c1, r1 );
            out_mcell.ref = oxml_utils::range2string( c1, r1, c2, r2 );
            out_mcells.mergeCell.push_back( out_mcell );
        }

        out_ws.mergeCells = out_mcells;
    }

    void xlsx_export_filter::process_conditional_formats( session& s, const shared_worksheet_type& ws, sml::CT_Worksheet& out_ws )
    {
        persistent_conditional_formats      cf_map;
        get_conditionalformat_list_type     all_cf;
        conditional_format_manager&         cf_manager = ws->conditional_formats();

        cf_manager.get( all_cf, s, true );

        foreach( const get_conditional_format & cond_fmt, all_cf ) {
            persistent_conditional_format   crt_format;
            std::vector< std::string >      ranges;
            std::string                     style_string;

            if ( crt_format.parse_rule( cond_fmt.rule ) ) {
                style_string = persistent_conditional_format::get_style_string( cond_fmt.style, cond_fmt.format );
                if ( style_string == ";" ) {
                    style_string = "";
                }
                if ( cond_fmt.lock_cells ) {
                    if (  *cond_fmt.lock_cells ) {
                        style_string.append( "page-break-before:never;" );
                    } else {
                        style_string.append( "page-break-before:always;" );
                    }
                }
                for ( get_conditional_format::border_map_type::const_iterator i = cond_fmt.borders.begin(), e = cond_fmt.borders.end(); i != e; ++i ) {
                    switch ( i->first ) {
                        case border_types::bottom:
                            style_string += ( std::string( "border-bottom:" )  + i->second + ";" );
                            break;
                        case border_types::left:
                            style_string += ( std::string( "border-left:" )  + i->second + ";" );
                            break;
                        case border_types::top:
                            style_string += ( std::string( "border-top:" )  + i->second + ";" );
                            break;
                        case border_types::right:
                            style_string += ( std::string( "border-right:" )  + i->second + ";" );
                            break;
                        default:
                            break;
                    }
                }

                crt_format.dxf_id = m_styles.register_dxf( style_string, true );
                foreach( const std::string & v, cond_fmt.operands ) {
                    if ( !m_is_native ) {
                        crt_format.operands.push_back( string_utils::trim_start( boost::replace_all_regex_copy( v, match_atChr_regex, wss_var_export_prefix ), '=' ) );
                    }
                    crt_format.operands.push_back( string_utils::trim_start( v, '=' ) );
                }
            }

            oxml_utils::split_ranges( cond_fmt.applies_to, ranges );
            foreach( const std::string & range, ranges ) {
                cf_map.register_cf( range, crt_format );
            }
        }
        cf_map.store( out_ws.conditionalFormatting );
    }

    bool xlsx_export_filter::add_row( session& s, sml::CT_Row& out_row, const shared_worksheet_type& ws, const sheet_point::integer_type row, const sheet_point::integer_type min_col, const sheet_point::integer_type max_col, const std::map<sheet_point, bool>& all_used_cells, const bool as_snapshoot/* = false*/ )
    {
        bool                    result = false;
        out_row.r = row + 1;


        unsigned int height = ws->layout().row_height( row );

        if ( height != ws->layout().default_row_height() ) {
            if ( 0 == height ) {
                out_row.hidden = true;
                out_row.ht              = oxml_utils::px2pt( ws->layout().hidden_row_height( row ) );
                out_row.customHeight    = true;
            } else {
                out_row.ht              = oxml_utils::px2pt( height );
                out_row.customHeight    = true;
            }
            result                  = true;
        }

        int default_style = -1;
        if (  ( size_t ) - 1 != ws->style().get_row_background_key( row ) ) {
            const style_set_type& def_style =  ws->style().get_row_background( row );

            if ( def_style.empty() ) {
                default_style = m_styles.get_empty_style();
            } else {
                default_style = m_styles.register_style( def_style.serialize( false ) );
            }
            out_row.customFormat = true;
            out_row.s = default_style;
            result = true;
        }


        range                                       row_range = ws->range( sheet_range( sheet_point( row, m_min_style_col ), sheet_point( row, m_max_style_col ) ) );
        sparse_vector<variant>                      row_style;
        sparse_vector<variant>::const_iterator      cell_style;
        unlocked_cells_vec_type                     row_lock;
        unlocked_cells_vec_type::const_iterator     cell_lock;
        //        style_manager_type::undo_list_type          row_styles_idx;

        if ( -1 != m_min_style_col ) {
            //            row_styles_idx = row_range.style_keys();
            row_style = row_range.style( false );
            cell_style = row_style.begin();
            cf::cf_vec_type dummy;
            row_lock = row_range.un_locked( s, dummy, true );
            cell_lock = row_lock.begin();
        }

        for ( sheet_point::integer_type col = min_col; col <= max_col; col++ ) {
            bool                inner_result = false;
            range               crt         = ws->range( sheet_range( sheet_point( row, col ) ) );
            sml::CT_Cell        out_c;
            std::string         out_ref;

            out_ref.clear();

            if ( col >= m_min_style_col && col <= m_max_style_col && m_min_style_col >= 0 ) {

                if ( *cell_lock ) {
                    const std::string style_string = "page-break-before:always;" + cell_style->as_string( s.locale() );
                    int si = -1;
                    if ( style_string.empty() ) {
                        if ( -1 != default_style ) {
                            si = m_styles.get_empty_style();
                        } else if ( m_full_cols.end() != std::find( m_full_cols.begin(), m_full_cols.end(), col ) ) {
                            si = m_styles.get_empty_style();
                        }
                    } else {
                        si = m_styles.register_style( style_string );
                    }
                    if ( -1 != si ) {
                        if ( default_style !=  si  ) {
                            out_c.s = si;
                            inner_result = true;
                        }
                    }
                } else {
                    const std::string& style_string = cell_style->as_string( s.locale() );
                    int si = -1;
                    if ( style_string.empty() ) {
                        if ( -1 != default_style ) {
                            si = m_styles.get_empty_style();
                        } else if ( m_full_cols.end() != std::find( m_full_cols.begin(), m_full_cols.end(), col ) ) {
                            si = m_styles.get_empty_style();
                        }
                    } else {
                        si = m_styles.register_style( style_string );
                    }
                    if ( -1 != si ) {
                        if ( default_style !=  si  ) {
                            out_c.s = si;
                            inner_result = true;
                        }
                    }

                }
                cell_style++;
                cell_lock++;
            }

            if ( col >= m_min_val_col && col <= m_max_val_col && ( all_used_cells.end() != all_used_cells.find( sheet_point( row, col ) ) ) ) {
                if ( variant( true ) == crt.has_formula() ) {
                    const std::string formula = crt.formula( s ).as_string( s.locale() );
                    if ( formula[0] != '\'' ) {
                        if ( as_snapshoot ) {
                            if ( !formula.empty() ) {
                                std::string formula_name = formula.substr( 0, formula.find( '(' ) );
                                std::transform( formula_name.begin(), formula_name.end(), formula_name.begin(), ::tolower );
                                if ( formula_name == "=hyperlink" ) {
                                    inner_result = true;
                                    std::string svalue = crt.value( s ).as_string( s.locale() );
                                    trim_hyperlink( svalue );
                                    out_c.t = sml::ST_CellType::s_literal;
                                    out_c.v = oxml_utils::int2string( m_shared_strings.register_string( svalue ) );

                                } else if ( formula_name == "=showpict" ) {
                                    out_c.t = sml::ST_CellType::s_literal;
                                    out_c.v = oxml_utils::int2string( m_shared_strings.register_string( "showpict" ) );
                                    inner_result = true;
                                } else if ( formula_name.substr( 0, 6 ) == "=spark" ) {
                                    out_c.t = sml::ST_CellType::s_literal;
                                    out_c.v = oxml_utils::int2string( m_shared_strings.register_string( "microchart" ) );
                                    inner_result = true;
                                } else {
                                    variant value = crt.value( s );
                                    inner_result = true;
                                    switch ( value.type() ) {
                                        case variant::type_string:
                                            out_c.t = sml::ST_CellType::s_literal;
                                            out_c.v = oxml_utils::int2string( m_shared_strings.register_string( value.string() ) );
                                            break;
                                        case variant::type_bool:
                                            out_c.t = sml::ST_CellType::b_literal;
                                            out_c.v =  std::string( ( value.as_double() == 0 ) ? "0" : "1" );
                                            break;
                                        case variant::type_double:
                                            out_c.v = value.as_string( s.locale() );
                                            break;
                                        default:
                                            break;
                                    }
                                }
                            }
                        } else {
                            if ( !formula.empty() ) {
                                inner_result = true;
                                if ( formula[0] == '{' && formula[formula.length()-1] == '}' ) {
                                    out_ref = a1conversion::to_a1::from_point( sheet_point( row, col ) );
                                    std::map<std::string, std::string>::iterator afit = array_formula_master_cells.find( out_ref );
                                    if ( formula.length() >= 3  && afit != array_formula_master_cells.end() ) {
                                        //array formula master cell
                                        std::string ref = afit->second;
                                        std::string local_formula = formula.substr( 2, formula.length() - 3 );
                                        if ( !m_is_native ) {
                                            local_formula = boost::replace_all_regex_copy( local_formula, match_atChr_regex, wss_var_export_prefix );
                                        }
                                        out_c.f = local_formula;
                                        out_c.f.get().t = sml::ST_CellFormulaType::array_literal;
                                        out_c.f.get().ref = ref;
                                    }
                                } else {
                                    // fixup hyperlink function
                                    typedef const boost::iterator_range<std::string::const_iterator> string_range;
                                    const std::string func ( "hyperlink" );
                                    std::string local_formula = formula.substr( 1 );
                                    if ( !m_is_native && boost::ifind_first( string_range( formula.begin(), formula.end() ), string_range( func.begin(), func.end() ) ) ) {
                                        if ( std::count( local_formula.begin(), local_formula.end(), ',' ) > 1 ) {
                                            size_t first_comma = formula.find( "," ) + 1;
                                            local_formula = local_formula.substr( 0, formula.find( ",", first_comma ) - 1 );
                                        }
                                        local_formula = boost::ireplace_all_copy( local_formula, "[self]", "#" ) + ")";
                                    }

                                    if ( !m_is_native ) {
                                        local_formula = boost::replace_all_regex_copy( local_formula, match_atChr_regex, wss_var_export_prefix );
                                    }

                                    out_c.f = local_formula;
                                }
                            }
                        }
                    } else {
                        variant value = crt.value( s );
                        if ( !value.is_empty() ) {
                            inner_result = true;
                            std::string cell_value( "" );
                            out_c.t = sml::ST_CellType::s_literal;
                            cell_value = value.string();
                            if ( cell_value.substr( 0, 11 ) == "<span class" && !m_is_native ) {
                                m_hyperlink_cells.push_back( crt );
                                trim_hyperlink( cell_value );
                            }
                            out_c.v = oxml_utils::int2string( m_shared_strings.register_string( cell_value ) );
                        }
                    }
                } else {

                    //skip calculation on save
                    variant             value       = crt.value( s );
                    if ( !value.is_empty() ) {
                        inner_result = true;
                        std::string cell_value( "" );
                        switch ( value.type() ) {
                            case variant::type_string:
                                out_c.t = sml::ST_CellType::s_literal;
                                cell_value = value.string();
                                if ( cell_value.substr( 0, 11 ) == "<span class" && !m_is_native ) {
                                    m_hyperlink_cells.push_back( crt );
                                    trim_hyperlink( cell_value );
                                }
                                out_c.v = oxml_utils::int2string( m_shared_strings.register_string( cell_value ) );
                                break;
                            case variant::type_bool:
                                out_c.t = sml::ST_CellType::b_literal;
                                out_c.v =  std::string( ( value.as_double() == 0 ) ? "0" : "1" );
                                break;
                            case variant::type_double:
                                out_c.v = value.as_string( s.locale() );
                                break;
                            default:
                                break;
                        }
                    }
                }
            }


            if ( inner_result ) {
                if ( out_ref.empty() ) {
                    out_c.r = a1conversion::to_a1::from_point( sheet_point( row, col ) );
                } else {
                    out_c.r = out_ref;
                }
                out_row.c.push_back( out_c );
                result = inner_result;
            }
        }

        return result;
    }


    void xlsx_export_filter::internal_export( session& s, workbook& wb, package::opackage& package, const bool as_snapshoot/* = false*/ )
    {
        clear();
        set_dummy_styles();
        init_relations();

        sml::sml_workbook           wbDoc;
        sml::CT_Workbook&           out_wb = wbDoc.workbook.getset();
        int                         sheetId = 0;
        sml::CT_Sheets&             out_sheets = out_wb.sheets;

        workbook::iterator_pair     wb_it = wb.locking_iterator();

        foreach( const shared_worksheet_type & ws, wb_it ) {

            ++sheetId;

            if ( s.session_sheets().check_original_uuid( ws->uuid() ) && !m_is_native ) {
                const shared_worksheet_type sws = s.session_sheets().session_sheet_by_original_uuid( ws->uuid() );
                do_one_worksheet( s, out_sheets, sheetId, sws, package, as_snapshoot );
            } else {
                do_one_worksheet( s, out_sheets, sheetId, ws, package, as_snapshoot );
            }
        }

        m_defined_names.register_names( wb.named_formulas().get_all( s ), optional<int>(), s.locale() );
        m_defined_names.store( out_wb.definedNames.getset() );

        serialize_doc( package.get( "xl/workbook.xml" ), wbDoc );

        sml::custom_data                ed_doc;
        sml::CT_extended_data&          out_ed = ed_doc.extended_data.getset();
        out_ed.version.major = VERSION_HI;
        out_ed.version.minor = VERSION_LO;


        variable_mapping_list_type::const_iterator it( s.variable().list().begin() );
        variable_mapping_list_type::const_iterator end_it( s.variable().list().end() );
        for ( ; it != end_it; ++it ) {
            sml::CT_variable v;
            sml::CT_vt_value crt_output;
            it->second.serialize( crt_output );
            v.key = it->first;
            v.value = crt_output;
            out_ed.variables.variable.push_back( v );
        }


        wb.serialize( s, out_ed );

        serialize_doc( package.get( "xl/embeddings/embeddedObjectWorkbook.xml" ), ed_doc );

        write_globals( package );

        package.close_current();

    }

}
