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

#include "xlsx_import_filter.hpp"
#include <boost/algorithm/string/regex.hpp>
#include <boost/regex.hpp>
#include <wss/ci_string.hpp>
#include <wss/style_set.hpp>
#include <wss/worksheet.hpp>
#include <wss/workbook.hpp>
#include <wss/application.hpp>
#include <wss/range.hpp>
#include <wss/worksheet_element.hpp>
#include <wss/invalid_formula_exception.hpp>
#include <wss/can_not_change_part_of_an_array_exception.hpp>
#include <wss/import_exception.hpp>

#ifdef _DEBUG
# include <wss/logger.hpp>
# include <wss/a1conversion.hpp>
#endif // _DEBUG

#include "oxml_utils.hpp"
#include "persistent_drawing.hpp"
#include "persistent_conditional_formats.hpp"
#include "hyperlink_adapter.hpp"
#include "relations.hpp"

#include "xercesc/dom/DOM.hpp"
XERCES_CPP_NAMESPACE_USE

namespace xlsx
{
    extern boost::regex match_export_var_regex;
    boost::regex match_export_var_regex( "(?<![a-zA-Z0-9])(__wss_exported_variable_)(?=\\w)" );
    extern std::string atChr_str;
    std::string atChr_str( "@" );

    inline const utf8_ci_string internal_get_wb_name( const std::string  filename, const std::string file_extension, const bool remove_node_number )
    {
        const size_t size_of_file_extension = file_extension.size();
        const size_t min_size_expected = 2 + size_of_file_extension;
        if ( filename.size() > min_size_expected ) {
            if ( filename.compare( filename.size() - size_of_file_extension, size_of_file_extension, file_extension )  == 0 ) {
                const std::string::size_type start = remove_node_number ? filename.find_first_of( '-' ) + 1 : 0;
                if ( start < ( filename.size() - size_of_file_extension ) ) {
                    return convert_utf8_ci( filename.substr( start, filename.size() - size_of_file_extension - start ) );
                }
            }
        }
        //fallback to filename
        return convert_utf8_ci( filename );
    }


    const utf8_ci_string get_wb_name( const std::string  filename, const bool native_format )
    {
        if ( native_format ) {
            return internal_get_wb_name( filename, ".wss", true );
        } else { //xlsx file format
            return convert_utf8_ci( filename );
            //return internal_get_wb_name( filename, ".xlsx", false );
        }
    }

    class scoped_set_session_to_importing
    {
    public:
        scoped_set_session_to_importing( session& s )
            : m_session( s ), m_import_successfull( false ) {
            m_session.is_loading( true );
        }

        void import_successfull() {
            shared_workbook_type wb = m_session.selected().workbook().lock();
            if ( wb ) {
                m_session.is_loading( false );
                m_import_successfull = true;
                typedef workbook::iterator_pair::const_iterator wb_const_iterator_type;
                const workbook::iterator_pair it_pair = wb->locking_iterator();
                for ( wb_const_iterator_type it = it_pair.begin(), end_it = it_pair.end(); it != end_it; ++it ) {
                    ( *it )->compute_view_independent( m_session );
                }
            }
        }
        ~scoped_set_session_to_importing() {
            if ( !m_import_successfull ) {
                m_session.is_loading( false );
            }
        }
    private:
        session& m_session;
        bool m_import_successfull;
    };

    shared_workbook_type xlsx_import_filter::do_import( session& s, application& a, const boost::filesystem::path& in_file, const bool is_native )
    {
        XMLPlatformUtils::Initialize() ;
        shared_workbook_type return_value;
        m_is_native = is_native;
        try {
            package::izpackage izpackage( in_file.string() );
            return_value = internal_import( s, a, izpackage, in_file );
        } catch ( std::exception& e ) {
            throw import_exception( e.what() );
        } catch ( ... ) {
            throw import_exception();
        }
        return return_value;
    }

    bool xlsx_import_filter::extended_data_import( session& s, application& a, const boost::filesystem::path& in_file )
    {
        try {
            package::izpackage izpackage( in_file.string() );
            return( internal_extended_data_import( s, a, izpackage, in_file ) );
        } catch ( std::exception& e ) {
            throw import_exception( e.what() );
        } catch ( ... ) {
            throw import_exception();
        }
    }

    std::vector<std::string> xlsx_import_filter::get_progress_list()
    {

        std::vector<std::string> ret = locked_import_progress_list::access( m_import_progress_list ).get();
        locked_import_progress_list::access( m_import_progress_list ).get().clear();
        return ret;

    }


    void xlsx_import_filter::process_worksheet( session& s, shared_worksheet_type& ws, const sml::CT_Worksheet& in_sheet, const sml::CT_Workbook& in_book )
    {
        std::set< std::string > blocked_cells; //used for master array formulas

        if ( in_sheet.sheetFormatPr.present() ) {
            //set default row height
            ws->layout().default_row_height( oxml_utils::pt2px( in_sheet.sheetFormatPr.get().defaultRowHeight ) );

            if ( in_sheet.sheetFormatPr.get().defaultColWidth.present() ) {
                double chars = in_sheet.sheetFormatPr.get().defaultColWidth.get();
                int width = ( int )( chars * oxml_utils::default_char_max_width + 0.4999 );
                if ( width > 0 ) {
                    ws->layout().default_column_width( width );
                }
            }
        }

        bool discarded_cols = false;

        //sheet layout
        for ( std::vector<sml::CT_Cols>::const_iterator colsIt = in_sheet.cols.begin(); colsIt != in_sheet.cols.end(); colsIt++ ) {
            for ( std::vector<sml::CT_Col>::const_iterator colIt = colsIt->col.begin(); colIt != colsIt->col.end(); colIt++ ) {
                if ( colIt->width.present() ) {
                    double chars = colIt->width.get();
                    int width = ( int )( chars * oxml_utils::default_char_max_width + 0.4999 );
                    if ( width >= 0 ) {
                        if ( colIt->min > sheet_dimension::max_column || colIt->max > sheet_dimension::max_column ) {
                            discarded_cols = true;
                            continue;
                        }
                        for ( unsigned int col = colIt->min; col <= colIt->max; col++ ) {
                            if ( 0 == width ) {
                                //fallback for old style hide
                                ws->layout().hide_column( col - 1 );
                            } else {
                                ws->layout().column_width( col - 1, width );
                            }
                            if ( colIt->hidden ) {
                                ws->layout().hide_column( col - 1 );
                            }
                        }
                    }
                }

                if ( colIt->style > 0 ) {
                    if ( colIt->min > sheet_dimension::max_column || colIt->max > sheet_dimension::max_column ) {
                        discarded_cols = true;
                        continue;
                    }

                    range crt = ws->range( sheet_range( sheet_point( 0, colIt->min - 1 ), sheet_point( sheet_dimension::max_row, colIt->max - 1 ) ) );

                    const style_set_type& cell_style = m_styles.cs_xf_at( colIt->style );

                    if ( !cell_style.empty() ) {
                        crt.style( s, cell_style, true );
                    }

                    for ( unsigned int c = colIt->min; c <= colIt->max; c ++ ) {
                        for ( unsigned int r = 0; r < sheet_dimension::max_row; r++ ) {
                            m_styles.apply_border_at( ws->borders(), colIt->style, r, c, !m_is_native );
                        }
                    }
                    if ( m_styles.protected_at( colIt->style ) ) {
                        //TODO: how do we support hide? Not supported in 2.0
                        crt.un_locked( s, true );
                    }

                    const std::string& cell_format = m_styles.nf_at( colIt->style );

                    if ( !cell_format.empty() ) {
                        crt.format( s, cell_format, true );
                    }
                }

            }
        }

        if ( discarded_cols ) {
            locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Warning: Columns outside the supported range were discarded." );
        }

        std::list<geometry::rectangle_type> array_cell_ranges;

        m_paste_view_adapter.reset( new paste_view_adapter( m_shared_strings, in_book, ws->name() ) );

        //process sheet rows
        for ( std::vector<sml::CT_Row>::const_iterator rowIt = in_sheet.sheetData.row.begin(); rowIt != in_sheet.sheetData.row.end(); rowIt++ ) {
            do_one_row( s, ws, *rowIt, array_cell_ranges );
        }

        merge_cells( s, ws, in_sheet );

        if ( m_paste_view_adapter->active() ) {
            if ( m_paste_view_adapter->validate() ) {
                //add paste view
                shared_worksheet_element_type palo = worksheet_element::create( ws );
                worksheet_element::key_value_vector_type properties_list;

                properties_list.push_back( std::make_pair( "e_type", variant( "palo_pv" )  ) );
                properties_list.push_back( std::make_pair( "pv_id", variant( "pv_abcdefabcdefa" )  ) );
                properties_list.push_back( std::make_pair( "n_location", variant( m_paste_view_adapter->location() )  ) );
                properties_list.push_back( std::make_pair( "payload", m_paste_view_adapter->encoded_payload() ) );

                palo->properties( s, properties_list );

                range pivot = ws->range( m_paste_view_adapter->pivot() );

                attribute_set_type attrs;

                attrs.add( std::string( "\"dblclick\"" ) , std::string( "[\"hnd_dblCpvOpen\",\"pv_abcdefabcdefa\"," + boost::lexical_cast<std::string>( pivot.coverage().upper_left().column() ) + "," + boost::lexical_cast<std::string>( pivot.coverage().upper_left().row() ) + "]" ) );
                pivot.attribute( s, attrs );

                attribute_set_type enames_attr;
                enames_attr.add( std::string( "\"elaborate_later\"" ) , std::string( "[\"elaborate later\"]" ) );
                const std::vector< sheet_point > enames = m_paste_view_adapter->enames();
                for ( std::vector< sheet_point >::const_iterator i = enames.begin(); i != enames.end(); ++i ) {
                    range ename_range = ws->range( *i );
                    ename_range.attribute( s, enames_attr );
                }
            }
        }

        do_cf( s, ws, in_sheet );
    }

    void xlsx_import_filter::merge_cells( session& s, shared_worksheet_type& ws, const sml::CT_Worksheet& in_sheet  )
    {
        if ( !in_sheet.mergeCells.present() ) {
            return;
        }

        for ( std::vector<sml::CT_MergeCell>::const_iterator it = in_sheet.mergeCells.get().mergeCell.begin(); it != in_sheet.mergeCells.get().mergeCell.end(); it++ ) {
            std::string range_str = it->ref;
            int r1, c1, r2, c2;
            if ( oxml_utils::parse_range( range_str, c1, r1, c2, r2 ) ) {
                range crt = ws->range( sheet_range( sheet_point( r1 - 1, c1 ), sheet_point( r2 - 1, c2 ) ) );

                crt.merge( s );
            }
        }
    }

    void xlsx_import_filter::do_cf( session& s, shared_worksheet_type& ws, const sml::CT_Worksheet& in_sheet  )
    {
        conditional_format_manager&  cf_manager = ws->conditional_formats();
        for ( std::vector<sml::CT_ConditionalFormatting>::const_iterator cfit = in_sheet.conditionalFormatting.begin(); cfit != in_sheet.conditionalFormatting.end(); cfit++ ) {
            std::vector< std::string >    ranges;
            rectangle_list_type                range;
            if ( cfit->sqref.present() )
                for ( sml::ST_Sqref::const_iterator rangeIt = cfit->sqref.get().begin(); rangeIt != cfit->sqref.get().end(); rangeIt++ ) {
                    ranges.push_back( *rangeIt );
                    int r1, c1, r2, c2;
                    if ( oxml_utils::parse_range( *rangeIt, c1, r1, c2, r2 ) ) {
                        range.push_back( sheet_range( sheet_point( r1 - 1, c1 ), sheet_point( r2 - 1, c2 ) ) );
                    } else if ( oxml_utils::parse_reference( *rangeIt , c1, r1 ) ) {
                        range.push_back( sheet_range( sheet_point( r1 - 1, c1 ), sheet_point( r1 - 1, c1 ) ) );
                    }
                }
            if ( cfit->extLst.present()  && !cfit->extLst.get().ext.empty() && cfit->extLst.get().ext[0].uri.present() ) {
                persistent_conditional_formats::load_rule( cfit->cfRule, m_theme, cf_manager, s, range, m_styles, m_version_info.is_core3(), cfit->extLst.get().ext[0].uri.get()  );
            } else {
                persistent_conditional_formats::load_rule( cfit->cfRule, m_theme, cf_manager, s, range, m_styles, m_version_info.is_core3() );
            }
        }
    }

    void xlsx_import_filter::do_one_row( session& s, shared_worksheet_type& ws, const sml::CT_Row& row, std::list<geometry::rectangle_type>& array_cell_ranges )
    {
        int r = row.r.get();

        m_row_agregator.clear();



        if ( row.ht.present() ) {
            double height = row.ht.get();
            if ( 0 == height ) {
                ws->layout().hide_row( r - 1 );
            } else {
                ws->layout().row_height( r - 1, oxml_utils::pt2px( height ) );
            }
        }

        if ( row.hidden ) {
            ws->layout().hide_row( r - 1 );
        }

        if ( row.customFormat ) {
            range crt = ws->range( sheet_range( sheet_point( r - 1, 0 ), sheet_point( r - 1, sheet_dimension::max_column ) ) );

            const style_set_type& cell_style = m_styles.cs_xf_at( row.s );

            crt.style( s, cell_style, true );

            for ( unsigned int c = 0; c < sheet_dimension::max_column; c++ ) {
                m_styles.apply_border_at( ws->borders(), row.s, r - 1, c, !m_is_native );
            }
            if ( m_styles.protected_at( row.s ) ) {
                //TODO: how do we support hide? Not supported in 2.0
                crt.un_locked( s, true );
            }

            const std::string& cell_format = m_styles.nf_at( row.s );

            if ( !cell_format.empty() ) {
                crt.format( s, cell_format, true );
            }
        }

        m_row_agregator.clear();

        //process row cells
        for ( std::vector< sml::CT_Cell >::const_iterator cIt = row.c.begin(); cIt != row.c.end(); cIt++ ) {
            if ( !cIt->r.present() ) {
                continue;
            }

            //early reject something like this:
            //<c r="G93"/>
            if ( !cIt->f.present() && ( !cIt->v.present() && ( cIt->t != sml::ST_CellType::inlineStr_literal && cIt->t != sml::ST_CellType::b_literal ) ) && cIt->s == 0 ) {
                continue;
            }
            do_one_cell( s, ws, *cIt, array_cell_ranges );
        }


        for ( row_agregator::row_data_vector::const_iterator i = m_row_agregator.begin(), e = m_row_agregator.end(); i != e; i++ ) {
            range crt = ws->range( sheet_range( sheet_point( r - 1, i->min ), sheet_point( r - 1, i->max ) ) );
            const int id = i->style_id;

            const std::string& cell_format = m_styles.nf_at( id );

            if ( !cell_format.empty() ) {
                crt.format( s, cell_format, true );
            }

            const style_set_type& crt_style = m_styles.cs_xf_at( id );
            if ( persistent_styles::is_empty_style( crt_style ) ) {
                static const style_set_type empty;
                crt.style( s, empty, true );
            } else {
                crt.style( s, crt_style, true );
            }

            if ( m_styles.protected_at( id ) ) {
                //TODO: how do we support hide? Not supported in 2.0
                crt.un_locked( s, true );
            }
        }
    }

    inline bool already_done_by_array_cell( const sheet_point& current, std::list<geometry::rectangle_type>& array_cell_ranges )
    {
        if ( !array_cell_ranges.empty() ) {
            for ( std::list<geometry::rectangle_type>::const_iterator it = array_cell_ranges.begin(), end_it = array_cell_ranges.end(); it != end_it; ++it ) {
                if ( it->covers( current ) ) {
                    return true;
                }
            }
        }
        return false;
    }

    void xlsx_import_filter::do_one_cell( session& s, shared_worksheet_type& ws, const sml::CT_Cell& cell, std::list<geometry::rectangle_type>& array_cell_ranges )
    {

        int r, c;

        oxml_utils::parse_reference( cell.r.get(), c, r );
        const sheet_point current_position( r - 1, c );

        m_row_agregator.register_style( c, cell.s );

#ifdef _DEBUG
        try {
#endif // _DEBUG
            const bool do_formula_and_value = !already_done_by_array_cell( current_position, array_cell_ranges );
            range crt = ws->range( sheet_range( current_position ) );

            if ( m_paste_view_adapter->active() ) {
                m_paste_view_adapter->visit( r - 1, c, cell );
            }

            //            const std::string& cell_format = m_styles.nf_at( cell.s );

            //            if ( !cell_format.empty() ) {
            //                crt.format( s, cell_format, true );
            //            }

            if ( do_formula_and_value ) {
                if ( cell.f.present() ) {
                    //set formula
                    const std::string& t = cell.f.get().t;
                    std::string f;
                    if ( sml::ST_CellFormulaType::shared_literal == t ) {
                        const std::string&      v = cell.f.get();
                        if ( cell.f.get().si.present() ) {
                            int si = cell.f.get().si.get();
                            while ( ( int )m_shared_formulas.size() <= si ) {
                                m_shared_formulas.push_back( shared_formula() );
                            }
                            if ( v.empty() ) {
                                shared_formula& sf = m_shared_formulas[ si ];
                                range masterCellRange = ws->range( sheet_range( sheet_point( sf.r - 1, sf.c ) ) );
                                masterCellRange.copy( s, crt, false, insert_shift_direction::automatic, content_type::formula );
                                //crt.value( s, masterCellRange.value( s ) );
                            } else {
                                m_shared_formulas[si].r = r;
                                m_shared_formulas[si].c = c;
                                f = v;
                            }
                        }
                    } else if ( t == sml::ST_CellFormulaType::normal_literal ) {
                        f = cell.f.get();
                    } else if ( t == sml::ST_CellFormulaType::array_literal ) {
                        std::string f = cell.f.get();
                        if ( cell.f.get().ref.present() ) {
                            int r1, c1, r2, c2;
                            if ( oxml_utils::parse_range( cell.f.get().ref.get(), c1, r1, c2, r2 ) ) {
                                if ( c1 <= c2 && r1 <= r2 ) {
                                    range aRange = ws->range( sheet_range( sheet_point( r1 - 1, c1 ), sheet_point( r2 - 1, c2 ) ) );
                                    try {
                                        aRange.array_formula( s, "=" + boost::replace_all_copy( f, "_xll.", "" ) );
                                    } catch ( const invalid_formula_exception& ) {
                                        aRange.array_formula( s, "UNSUPPORTED FORMULA '=" + boost::replace_all_copy( f, "_xll.", "" ) + "'" );
                                    }
                                    array_cell_ranges.push_back( geometry::rectangle_type( aRange.coverage() ) );
                                    //                             for ( int ac = c1; ac <= c2; ac++ ){
                                    //                                 for ( int ar = r1; ar <= r2; ar++ ) {
                                    //                                     std::string ref = oxml_utils::cell_reference( ac, ar );
                                    //                                     m_blocked_cells.insert( ref );
                                    //                                 }
                                    //                             }
                                }
                            } else {//single cell array formula
                                try {
                                    crt.array_formula( s, "=" + boost::replace_all_copy( f, "_xll.", "" ) );
                                } catch ( const invalid_formula_exception& ) {
                                    crt.array_formula( s, "UNSUPPORTED FORMULA '=" + boost::replace_all_copy( f, "_xll.", "" ) + "'" );
                                }
                            }
                        }
                    }

                    if ( !f.empty() ) {
                        try {

                            // fixup exported variables
                            if ( !m_is_native ) {
                                f = boost::replace_all_regex_copy( f, match_export_var_regex, atChr_str );
                            }

                            // replace refs to datac and datax with data (fhofmann: this should not be needed anymore because we forward it internally
                            //                     f = boost::ireplace_all_copy( f, "palo.datac", "PALO.DATA" );
                            //                     f = boost::ireplace_all_copy( f, "palo.datax", "PALO.DATA" );

                            // replace refs to datac and datax with data (fhofmann: this should not be needed anymore because we forward it internally
                            //                     f = boost::ireplace_all_copy( f, "palo.datac", "PALO.DATA" );
                            //                     f = boost::ireplace_all_copy( f, "palo.datax", "PALO.DATA" );

                            // fixup hyperlink function
                            typedef const boost::iterator_range<std::string::const_iterator> string_range;
                            static const std::string func ( "hyperlink" );
                            static const std::string self_string( "SELF" );
                            static const std::string self_string_ref( "[SELF]" );
                            const static boost::regex self_rx( "(?<![a-zA-Z0-9\\]])(#)(?=\\w)" );
                            const std::string fname = f;
                            if ( boost::ifind_first( string_range( fname.begin(), fname.end() ), string_range( func.begin(), func.end() ) ) ) {
                                size_t comma_count = std::count( fname.begin(), fname.end(), ',' );
                                if ( comma_count == 0 ) {
                                    std::string params = fname.substr( fname.rfind( "(" ), fname.rfind( ")" ) );
                                    f = fname.substr( 0, fname.length() - 1 ) + "," + params.substr( 1, params.length() );
                                    f = f.substr( 0, f.length() - 1 ) + "," + params.substr( 1, params.length() );
                                } else if ( comma_count == 1 ) {
                                    size_t last_idx = fname.rfind( ")" );
                                    std::string params = fname.substr( fname.rfind( "," ), last_idx );
                                    f = fname.substr( 0, last_idx ) + params;
                                }
                                const std::string& wbname = boost::ireplace_all_copy( convert_utf8_ci( ws->parent()->name() ) , "-import.xlsx", "" );
                                f = boost::ireplace_all_copy( f, wbname + ".xlsx", self_string );
                                f = boost::ireplace_all_copy( f, wbname + ".xls", self_string );

                                if ( !m_is_native ) {
                                    f = boost::replace_regex_copy( f, self_rx, self_string_ref );
                                }
                            }
                            crt.value( s, variant( "=" + boost::replace_all_copy( f, "_xll.", "" ) ) );
                        } catch ( const invalid_formula_exception& ) {
                            crt.value( s, variant( "UNSUPPORTED FORMULA '=" + boost::replace_all_copy( f, "_xll.", "" ) + "'" ) );
                        }
                    }
                } else if ( cell.t == sml::ST_CellType::n_literal ) {
                    if ( cell.v.present() ) {
                        crt.value( s, variant( oxml_utils::string2double( cell.v.get() ) ) );
                    }
                } else if ( cell.t == sml::ST_CellType::str_literal ) {
                    if ( cell.v.present() ) {
                        crt.value( s, variant( ( const std::string& ) cell.v.get() ) );
                    }
                } else if ( cell.t == sml::ST_CellType::inlineStr_literal ) {
                    if ( cell.is.present() && cell.is.get().t.present() ) {
                        crt.value( s, variant( ( const std::string& ) cell.is.get().t.get() ) );
                    } else {
                        //ignore formatting info and just concat parts
                        std::stringstream text;
                        for ( std::vector< sml::CT_RElt >::const_iterator r = cell.is.get().r.begin(); r != cell.is.get().r.end(); r++ ) {
                            text << static_cast< const std::string& >( r->t );
                        }
                        m_shared_strings.register_string( text.str() );
                    }
                } else if ( cell.t == sml::ST_CellType::b_literal ) {
                    //set bool value
                    if ( cell.v.present() && ( cell.v.get().get() == "1" || cell.v.get().get() == "true" ) ) {
                        crt.value( s, variant( true ) );
                    } else {
                        crt.value( s, variant( false ) );
                    }
                } else if ( cell.t == sml::ST_CellType::s_literal ) {
                    //set shared string
                    if ( cell.v.present() ) {
                        if ( m_styles.quote_prefix_at( cell.s ) ) {
                            //crt.format( s , "@" );
                            crt.value( s, variant( "'" + m_shared_strings.at( oxml_utils::string2int( cell.v.get() ) ) ) );
                        } else {
                            try {
                                std::string shared_str = m_shared_strings.at( oxml_utils::string2int( cell.v.get() ) );
                                if ( !shared_str.empty() && shared_str[0] == '\'' ) {
                                    style_set_type prefix;
                                    prefix.add( std::string( "quotePrefix" ), "1" );
                                    crt.style( s, prefix );
                                }
                                crt.value( s, variant( shared_str ) );
                            } catch ( invalid_formula_exception& ) {
                                if ( "@" == m_styles.nf_at( cell.s ) ) {
                                    crt.format( s, "@", true );
                                    crt.value( s, variant( m_shared_strings.at( oxml_utils::string2int( cell.v.get() ) ) ) );
                                } else {
                                    throw;
                                }
                            }
                        }
                    }
                } else if ( cell.t == sml::ST_CellType::e_literal ) {
                    //cell error value
                } else {
                    if ( cell.v.present() ) {
                        crt.value( s, ( const std::string& )cell.v.get() );
                    }
                }
            }
            //            const std::string& cell_style = m_styles.cs_xf_at( cell.s );

            //            if ( !cell_style.empty() ) {
            //                crt.style( s, style_set_type::unserialize( cell_style ), true );
            //            }

            m_styles.apply_border_at( ws->borders(), cell.s, r - 1, c, !m_is_native );

            //            if ( m_styles.protected_at( cell.s ) ) {
            //                //TODO: how do we support hide? Not supported in 2.0
            //                crt.un_locked( s, true );
            //            }
#ifdef _DEBUG
        } catch ( const can_not_change_part_of_an_array_exception& ) {
            LOG_ERROR( "can_not_change_part_of_an_array_exception occured in cell: \"" << a1conversion::to_a1::from_point( current_position ) << "\"" );
        }
#endif // _DEBUG
    }

    shared_workbook_type xlsx_import_filter::internal_import( session& s, application& a, package::izpackage& package, const boost::filesystem::path& in_file )
    {
        locked_import_progress_list::access( m_import_progress_list ).get().clear();
        std::string file_name = in_file.leaf();
        const utf8_ci_string wb_name = get_wb_name( file_name, m_is_native );
        locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Importing file " +  file_name );
        scoped_set_session_to_importing scoped_set_to_import( s );

        shared_workbook_type workbook = a.add( wb_name );

        a.get( s, workbook->uuid() )->select( s.selected() );

        m_theme.load( package );
        m_styles.load( package, m_theme );
        m_shared_strings.load( package );

        //load workbook
        sml::sml_workbook doc;
        parse_doc( package.get( "xl/workbook.xml" ), doc );

        sml::CT_Workbook& wb = doc.workbook.getset();

        size_t idx = 0;
        std::vector< std::string > sheet_names;

        std::map< std::string, boost::uuids::uuid > worksheet_ids;

        // create all worksheets before first access.
        for ( std::vector<sml::CT_Sheet>::const_iterator i = wb.sheets.sheet.begin(); i != wb.sheets.sheet.end(); i++ ) {
            shared_worksheet_type crt = workbook->add( convert_utf8_ci( i->name ) );
            worksheet_ids[ i->name ] = crt->uuid();
        }

        std::string edata( "embeddings/embeddedObjectWorkbook.xml" );
        //1. check backwards compatibility
        bool has_wb_edata = package.exists( edata );
        if ( !has_wb_edata ) {
            //1. check corect location
            edata = "xl/" + edata;
            has_wb_edata = package.exists( edata );
        }
        sml::custom_data ed_doc;

        if ( has_wb_edata  ) {
            parse_doc( package.get( edata ), ed_doc );
            if ( ed_doc.extended_data.present() ) {
                sml::CT_extended_data&          out_ed = ed_doc.extended_data.get();
                m_version_info = persistent_version_info( out_ed.version.major, out_ed.version.minor );
                workbook->deserialize( s, out_ed );
            }
        }

        locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Workbook Extended data loaded." );

        locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Importing workbook sheets..." );
        for ( std::vector<sml::CT_Sheet>::const_iterator i = wb.sheets.sheet.begin(); i != wb.sheets.sheet.end(); i++ ) {

            std::stringstream wsfn;
            wsfn << "xl/worksheets/sheet" << ++idx << ".xml";

            sml::sml_sheet sheetDoc;
            parse_doc( package.get( wsfn.str() ), sheetDoc );

            if ( !sheetDoc.worksheet.present() ) {
                continue;
            }

            locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Processing " + std::string( i->name ) );
            sml::CT_Worksheet ws = sheetDoc.worksheet.get();

            shared_worksheet_type worksheet = workbook->get( s, worksheet_ids[ i->name ] );

            workbook->get( s, worksheet->uuid() )->select( s.selected() );

            process_worksheet( s, worksheet, ws, wb );

            if ( ws.drawing.present() ) {
                add_worksheet_drawings( s, idx, package, worksheet, ws.drawing.get() );
                locked_import_progress_list::access(  m_import_progress_list ).get().push_back( std::string( i->name ) + " drawing imported." );
            }

            hyperlink_adapter::from_tags( s, idx, worksheet, package, ws );

            sheet_names.push_back( i->name );

            locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Sheet " + std::string( i->name ) + " imported." );

            std::stringstream edata;
            //1st try compatibility mode
            edata << "embeddings/embeddedObjectsheet" <<  idx << ".xml";
            std::string edata_str = edata.str();

            if ( !package.exists( edata_str ) ) {
                //2. upgraded mode with the correct location
                edata_str = "xl/" + edata_str;
                if ( !package.exists(  edata_str ) ) {
                    continue;
                }
            }

            sml::custom_data ed_doc;
            parse_doc( package.get( edata_str ), ed_doc );

            if ( !ed_doc.extended_data.present() ) {
                continue;
            }

            worksheet->deserialize( s, ed_doc.extended_data.get() );
            locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Sheet extended data imported." );
        }

        import_defined_names( s, workbook, wb.definedNames, sheet_names );

        s.selected().worksheet( *( workbook->locking_iterator().begin() ) );
        scoped_set_to_import.import_successfull();
        locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Workbook imported" );
        return workbook;

    }

    bool xlsx_import_filter::internal_extended_data_import( session& s, application& a, package::izpackage& package, const boost::filesystem::path& in_file )
    {

        std::string file_name = in_file.leaf();
        const utf8_ci_string filename = convert_utf8_ci( file_name );

        //load workbook
        sml::sml_workbook doc;
        parse_doc( package.get( "xl/workbook.xml" ), doc );

        std::vector< std::string > sheet_names;

        std::string edata( "embeddings/embeddedObjectWorkbook.xml" );
        //1. check backwards compatibility
        bool has_wb_edata = package.exists( edata );
        if ( !has_wb_edata ) {
            //1. check corect location
            edata = "xl/" + edata;
            has_wb_edata = package.exists( edata );
        }


        sml::custom_data ed_doc;

        if ( has_wb_edata ) {

            persistent_version_info version_info;
            parse_doc( package.get( edata ), ed_doc );

            if ( ed_doc.extended_data.present() ) {
                sml::CT_extended_data&          out_ed = ed_doc.extended_data.get();
                m_version_info = persistent_version_info( out_ed.version.major, out_ed.version.minor );
            }

            if ( m_version_info.m_major >= 1 && m_version_info.m_minor >= 7 ) {
                const spreadsheetml::CT_extended_data& data = ed_doc.extended_data.getset();
                const std::vector< sml::CT_variable >&  in_wbvar = data.variables.variable;

                for ( std::vector< sml::CT_variable >::const_iterator i = in_wbvar.begin(), end_it = in_wbvar.end(); i != end_it; ++i ) {
                    if ( i->key.present() ) {
                        variant crt;
                        crt.deserialize( i->value );
                        s.variable().variable( s, i->key.get(), crt );
                    }
                }
                return true;
            }

        }

        return false; //not the good version for extended data import
    }

    void xlsx_import_filter::add_worksheet_drawings( session& s, const size_t idx, package::izpackage& package, shared_worksheet_type& ws, const sml::CT_Drawing& in_sheet )
    {
        //load relations
        std::stringstream rel_name;
        rel_name << "xl/worksheets/_rels/sheet" << idx << ".xml.rels";

        rels_ns::relationships relsDoc;
        parse_doc( package.get( rel_name.str() ), relsDoc );
        if ( !relsDoc.Relationships.present() ) {
            return;    //malformed archive
        }

        export_helpers::relations       relations;

        relations.deserialize( relsDoc.Relationships.get() );

        boost::filesystem::path drawing_file = boost::filesystem::path( "xl/worksheets/" ) / boost::filesystem::path( relations.get( in_sheet.id ) );

        drawing_file.normalize();

        dml::dml_spreadsheetDrawing     drawingDoc;

        parse_doc( package.get( drawing_file.string() ), drawingDoc );

        if ( !drawingDoc.wsDr.present() ) {
            return;    //malformed archive
        }

        rels_ns::relationships mediaRelsDoc;

        try {
            parse_doc( package.get( drawing_file.parent_path().string() + "/_rels/" + drawing_file.leaf() + ".rels" ), mediaRelsDoc );
            if ( !mediaRelsDoc.Relationships.present() ) {
                return;    //malformed archive
            }
        } catch ( std::runtime_error& ) {
            return;     //nothing here
        }

        export_helpers::relations   media_relations;

        media_relations.deserialize( mediaRelsDoc.Relationships.get() );
        unsigned int zorder = 50;
        if ( drawingDoc.wsDr.present() ) {
            for ( std::vector< dml::CT_TwoCellAnchor >::iterator i = drawingDoc.wsDr.get().twoCellAnchor.begin(); i != drawingDoc.wsDr.get().twoCellAnchor.end(); i++ ) {
                if ( i->pic.present() ) {
                    persistent_drawing  drawing( *i, media_relations );
                    drawing.deserialize( s, package, *worksheet_element::create( ws ), ws->layout(), zorder++ );
                } else {
                    locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Chart not supported. Skipping chart..." );
                }
            }
        }
    }

    void xlsx_import_filter::import_defined_names( session& s, shared_workbook_type& wb, const xio::poptional< sml::CT_DefinedNames >& in_names, const std::vector< std::string > sheet_names )
    {
        // Don't forget: this should be called with at least one worksheet active otherwise the workbook level named formulas will fail
        // for now the worksbook level named formulas need a worksheet to start from.
        if ( !in_names.present() ) {
            return;
        }

        i_named_formula_manager&   nfm = wb->named_formulas();

        for ( std::vector<sml::CT_DefinedName>::const_iterator it = in_names.get().definedName.begin(); it != in_names.get().definedName.end(); it++ ) {
            sheet_point a1( 0, 0 );
            if ( it->localSheetId.present() && it->localSheetId.get() < sheet_names.size() ) {
                shared_worksheet_type ws = wb->get( s, convert_utf8_ci( sheet_names[ it->localSheetId.get() ] ) );

                named_formula_identifier    nfi( it->name, ws->uuid() );
                if ( nfm.exists( nfi ) ) {
                    nfm.remove( s, nfi );
                }

                try {
                    nfm.create( s, it->name, "=" + boost::replace_all_copy( std::string ( *it ), "_xll.", "" ), named_formula_scope::worksheet_scope, ws, a1, it->hidden );
                    if ( it->comment.present() ) {
                        nfm.comment( it->comment.get(), named_formula_identifier( it->name, ws->uuid() ) );
                    }
                } catch ( ... ) {
                    //Write in the import log
                    locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Defined name import failed: " + std::string( it->name ) );
                }
            } else {
                named_formula_identifier    nfi( it->name );
                if ( nfm.exists( nfi ) ) {
                    nfm.remove( s, nfi );
                }
                try {
                    wb->named_formulas().create( s, it->name, "=" + boost::replace_all_copy( std::string ( *it ), "_xll.", "" ), named_formula_scope::workbook_scope, shared_worksheet_type(), a1, it->hidden );
                    if ( it->comment.present() ) {
                        wb->named_formulas().comment( it->comment.get(), named_formula_identifier( it->name, boost::uuids::nil_uuid() ) );
                    }
                } catch ( ... ) {
                    //Write in the import log
                    locked_import_progress_list::access(  m_import_progress_list ).get().push_back( "Defined name import failed: " + std::string( it->name ) );
                }
            }
        }
    }

}

