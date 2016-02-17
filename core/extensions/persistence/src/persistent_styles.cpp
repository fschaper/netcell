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
#include "persistent_styles.hpp"
#include "persistent_theme.hpp"
#include "css_utils.hpp"
#include "string_utils.hpp"
#include <wss/border_manager.hpp>

namespace xlsx
{

    namespace sml = spreadsheetml;

    persistent_styles::persistent_styles()
    {
        clear();
    }

    int persistent_styles::register_dxf( const std::string& style_string, bool flip_fg_bg )
    {
        persistent_dxf dxf;
        ssmap font_rules;
        ssmap align_rules;
        ssmap protection_rules;
        ssmap border_rules;
        ssmap fill_rules;
        ssmap format_rules;
        ssmap qoute_rules;

        std::map< std::string, int >::iterator it = m_dxf_map.find( style_string );
        if ( it != m_dxf_map.end() ) {
            return it->second;
        }

        if ( !separate_styles( style_string, align_rules, font_rules, border_rules, fill_rules, protection_rules, format_rules, qoute_rules ) ) {
            return -1;
        }

        std::string format;

        if ( !fill_rules.empty() ) {
            persistent_fills::key_type key = persistent_fills::get_key( fill_rules );
            persistent_fill pf( key.second, key.first );
            if ( flip_fg_bg ) {
                pf.flip_fg_bg = true;
            }
            dxf.fill = pf;
        }

        if ( !align_rules.empty() ) {
            dxf.alignment = persistent_alignment( align_rules );
        }
        if ( !protection_rules.empty() ) {
            dxf.protection = persistent_protection( protection_rules );
        }
        if ( !border_rules.empty() ) {
            dxf.border = persistent_border( border_rules );
        }
        if ( !font_rules.empty() ) {
            dxf.font = persistent_font( font_rules );
        }

        if ( !format_rules.empty() ) {
            int format_id;
            if ( m_nfmts.register_format( format_rules, format_id ) ) {
                dxf.num_fmt.getset().m_id = format_id;
                dxf.num_fmt.getset().m_format_code = persistent_nfmts::read_format( format_rules );
            }
        }

        m_dxfs.push_back( dxf );
        int res = static_cast< int >( m_dxfs.size() ) - 1;
        m_dxf_map[ style_string ] = res;
        return res;
    }

    int persistent_styles::register_style( const std::string& style_string )
    {
        persistent_style style;
        bool valid = false;
        ssmap font_rules;
        ssmap align_rules;
        ssmap protection_rules;
        ssmap border_rules;
        ssmap fill_rules;
        ssmap format_rules;
        ssmap quote_rules;

        if ( style_string.empty() ) {
            return -1;
        }

        if ( m_last_registered_string == style_string ) {
            return m_last_registered_idx;
        }

        std::map<std::string, int>::iterator it = m_style_map.find( style_string );
        if ( m_style_map.end() != it ) {
            m_last_registered_string = style_string;
            m_last_registered_idx = it->second;
            return m_last_registered_idx;
        }

        if ( !separate_styles( style_string, align_rules, font_rules, border_rules, fill_rules, protection_rules, format_rules, quote_rules ) ) {
            return -1;
        }

        if ( !font_rules.empty() ) {
            valid = true;
            style.font_id = m_fonts.register_font( font_rules );
        }

        if ( !align_rules.empty() ) {
            valid = true;
            style.align_id = m_alignments.register_alignment( align_rules );
        }

        if ( !border_rules.empty() ) {
            valid = true;
            style.border_id = m_borders.register_border( border_rules );
        }

        if ( !protection_rules.empty() ) {
            valid = true;
            persistent_protection prot( protection_rules );
            style.locked = prot.locked;
            style.hidden = prot.hidden;
        }

        if ( !quote_rules.empty() ) {
            valid = true;
            style.quote_prefix = true;
        }

        if ( !fill_rules.empty() ) {
            int fill_id;
            bool is_empty_fill = true;
            for ( ssmap::const_iterator i = fill_rules.begin(), e = fill_rules.end(); i != e; ++i ) {
                if ( !i->second.empty() && !( i->second == "none" ) ) {
                    is_empty_fill = false;
                    break;
                }
            }
            if ( is_empty_fill ) {
                valid = true;
                style.fill_id = 0; //this is the empty fill
            } else if ( m_fills.register_fill( fill_rules, fill_id ) ) {
                valid = true;
                style.fill_id = fill_id;
            }
        }

        if ( !format_rules.empty() ) {
            int format_id;
            if ( m_nfmts.register_format( format_rules, format_id ) ) {
                valid = true;
                style.nfmt_id = format_id;
            }
        }

        if ( !valid ) {
            return -1;
        }

        //insert style
        int i = static_cast<int>( m_styles.size() );
        m_styles.push_back( style );
        m_style_map[style_string] = i;

        m_last_registered_string = style_string;
        m_last_registered_idx = i;

        return i;
    }

    bool persistent_styles::separate_styles(
        const std::string& style_string,
        ssmap& align_rules,
        ssmap& font_rules,
        ssmap& border_rules,
        ssmap& fill_rules,
        ssmap& protection_rules,
        ssmap& format_rules,
        ssmap& quote_rules )
    {
        std::vector< std::string > rules = css_utils::split_css_name_value( style_string );
        for ( size_t r = 0; r + 1 < rules.size(); r += 2 ) {
            const std::string&  name    = rules[r];
            const std::string&  value   = rules[r+1];

            if ( name == "__number-format" ) {
                format_rules[name] = value;
            } else if ( string_utils::starts_with( name, "background" ) ) {
                fill_rules[name] = value;
            } else if ( name == "font-family" || name == "font-size" || name == "color" || name == "font-weight" || name == "text-decoration" || name == "font-style" ) {
                font_rules[name] = value;
            } else if ( name == "text-align" || name == "vertical-align" || name == "text-indent" ) {
                align_rules[name] = value;
            } else if ( name == "white-space" ) {
                align_rules[name] = value;
            } else if ( string_utils::starts_with( name, "border" ) ) {
                border_rules[name] = value;
            } else if ( name == "page-break-before" && ( value == "always" || value == "never" ) ) {
                protection_rules[name] = value;
            } else if ( ( name == "width" || name == "height" ) && value == "0" ) {
                protection_rules[name] = value;
            } else if ( name == "quotePrefix" ) {
                quote_rules[name] = value;
            }
        }

        return !font_rules.empty() || !align_rules.empty() || !border_rules.empty() || !fill_rules.empty() || !protection_rules.empty() || !format_rules.empty() || !quote_rules.empty();
    }

    void persistent_styles::clear()
    {
        m_fonts.clear();
        m_cell_style_xfs.clear();
        m_fills.clear();
        m_borders.clear();
        m_nfmts.clear();
        m_xfs.clear();
        m_styles.clear();
        m_style_map.clear();
        m_dxfs.clear();
        m_dxf_map.clear();
        m_alignments.clear();
        m_cell_style_xfs.clear();

        m_last_registered_idx = -1;
        m_last_registered_string = "";
        m_empty_style_id = -1;

        m_style_sets.clear();
    }

    void persistent_styles::set_dummies()
    {
        m_fills.set_dummies();
        m_fonts.set_dummies();
        m_borders.set_dummies();
        m_styles.push_back( persistent_style() );
    }

    void persistent_styles::store( std::ostream& os ) const
    {
        sml::sml_styles ssDoc;
        sml::CT_Stylesheet& out_ss = ssDoc.styleSheet.getset();

        if ( !m_fonts.empty() ) {
            m_fonts.store( out_ss.fonts.getset() );
        }
        if ( !m_fills.empty() ) {
            m_fills.store( out_ss.fills.getset() );
        }
        if ( !m_nfmts.empty() ) {
            m_nfmts.store( out_ss.numFmts.getset() );
        }
        if ( !m_borders.empty() ) {
            m_borders.store( out_ss.borders.getset() );
        }

        if ( !m_styles.empty() ) {
            sml::CT_CellXfs& out_cellXfs = out_ss.cellXfs.getset();
            out_cellXfs.count = ( int )m_styles.size();

            for ( size_t i = 0; i < m_styles.size(); i++ ) {
                sml::CT_Xf out_xf;
                m_styles[i].store( out_xf );

                if ( m_styles[i].align_id.present() ) {
                    out_xf.applyAlignment = true;
                    const persistent_alignment& align = align_at( m_styles[i].align_id.get() );
                    align.store( out_xf.alignment.getset() );
                }

                out_cellXfs.xf.push_back( out_xf );
            }
        }

        sml::CT_CellStyleXfs& out_cellStyleXfs = out_ss.cellStyleXfs.getset();
        out_cellStyleXfs.count = 1;
        sml::CT_Xf out_xf;
        out_xf.fontId = 0;
        out_xf.numFmtId = 0;
        out_xf.fillId = 0;
        out_xf.borderId = 0;
        out_cellStyleXfs.xf.push_back( out_xf );

        sml::CT_CellStyles& out_cellStyles = out_ss.cellStyles.getset();
        out_cellStyles.count = 1;
        sml::CT_CellStyle out_cellStyle;
        out_cellStyle.xfId = 0;
        out_cellStyle.name = sml::ST_Xstring( "Normal" );
        out_cellStyle.builtinId = 0;
        out_cellStyles.cellStyle.push_back( out_cellStyle );

        //dxf
        if ( !m_dxfs.empty() ) {
            sml::CT_Dxfs& out_dxfs = out_ss.dxfs.getset();
            out_dxfs.count = ( int )m_dxfs.size();

            for ( size_t i = 0; i < m_dxfs.size(); i++ ) {
                sml::CT_Dxf out_dxf;
                m_dxfs[i].store( out_dxf );

                out_dxfs.dxf.push_back( out_dxf );
            }
        }

        //serialize
        const_cast< persistent_styles* >( this )->serialize_doc( os, ssDoc );
    }

    void persistent_styles::load_dxfs( const sml::CT_Dxfs& in_dxfs, const persistent_theme& theme )
    {
        m_dxfs.clear();
        m_dxf_map.clear();

        for ( std::vector<sml::CT_Dxf>::const_iterator it = in_dxfs.dxf.begin(); it != in_dxfs.dxf.end(); it++ ) {
            persistent_dxf dxf;

            if ( it->font.present() ) {
                dxf.font = persistent_font( it->font.get(), theme, m_color_table );
            }
            if ( it->border.present() ) {
                dxf.border = persistent_border( it->border.get(), theme, m_color_table );
            }
            if ( it->numFmt.present() ) {
                dxf.num_fmt = persistent_nfmt( it->numFmt.get() );
            }
            if ( it->fill.present() ) {
                if ( it->fill.get().patternFill.present() ) {
                    dxf.fill =  persistent_fill( it->fill.get(), theme, m_color_table );
                    dxf.fill.getset().flip_fg_bg = true;
                }
            }
            if ( it->alignment.present() ) {
                dxf.alignment = persistent_alignment( it->alignment.get() );
            }
            if ( it->protection.present() ) {
                dxf.protection = persistent_protection( it->protection.get() );
            }

            m_dxfs.push_back( dxf );
        }
    }

    void persistent_styles::load( package::ipackage& package, const persistent_theme& theme )
    {
        if ( !package.exists( "xl/styles.xml" ) ) {
            return;
        }

        sml::sml_styles doc;
        parse_doc( package.get( "xl/styles.xml" ), doc );
        if ( !doc.styleSheet.present() ) {
            return;
        }

        clear();

        const sml::CT_Stylesheet& sst = doc.styleSheet.get();

        if ( sst.colors.present() ) {
            m_color_table.load( sst.colors.get() );
        }

        if ( sst.fonts.present() ) {
            m_fonts.load( sst.fonts.get(), theme, m_color_table );
        }
        if ( sst.cellStyleXfs.present() ) {
            m_cell_style_xfs.load( sst.cellStyleXfs.get().xf );
        }
        if ( sst.fills.present() ) {
            m_fills.load( sst.fills.get().fill, theme, m_color_table );
        }
        if ( sst.borders.present() ) {
            m_borders.load( sst.borders.get().border, theme, m_color_table );
        }
        if ( sst.numFmts.present() ) {
            m_nfmts.load( sst.numFmts.get() );
        }
        if ( sst.cellXfs.present() ) {
            m_xfs.load( sst.cellXfs.get().xf );
        }
        if ( sst.dxfs.present() ) {
            load_dxfs( sst.dxfs.get(), theme );
        }

        ss.add( std::string( "font-color" ), "#0000ff" );
        ss.add( std::string( "background_color" ), "#0000ff" );
        ss.add( std::string( "color" ), "#808080" );
        ss.add( std::string( "font-family" ), "Arial" );
        ss.add( std::string( "font-size" ), "10pt" );
        ss.add( std::string( "font-weight" ), "normal" );
        ss.add( std::string( "text-align" ), "center" );
        ss.add( std::string( "vertical-align" ), "center" );
        ss.add( std::string( "white-space" ), "normal" );
    }

    const persistent_alignment& persistent_styles::align_at( const size_t idx ) const
    {
        return m_alignments.at( idx );
    }

    const style_set_type& persistent_styles::cs_xf_at( size_t idx )
    {
        style_set_cache_type::const_iterator match = m_style_sets.find( idx );
        if ( m_style_sets.end() != match ) {
            return match->second;
        }

        style_set_type              style_set;
        const persistent_xf&        xf = m_xfs.at( idx );

        if ( !( xf.apply_fill == false ) && xf.fill_id.present() ) {
            style_set_type fill = m_fills.style_set( xf.fill_id );
            if ( !fill.empty() ) {
                style_set.combine( fill );
            } else {
                fill.add( std::string( "background-color" ), "" );
                style_set.combine( fill );
            }
        }

        if ( !( xf.apply_font == false ) && xf.font_id.present() && xf.font_id.get() > 0 ) {
            const style_set_type& font = m_fonts.style_set( xf.font_id );
            if ( !font.empty() ) {
                style_set.combine( font );
            }
        }

        if ( !( xf.apply_alignment == false ) && xf.alignment.present() ) {
            const style_set_type& alignment = xf.alignment.get().style_set;
            if ( !alignment.empty() ) {
                style_set.combine( alignment );
            }
        }

        if ( xf.quote_prefix ) {
            style_set_type prefix;
            prefix.add( std::string( "quotePrefix" ), "1" );
            style_set.combine( prefix );
        }

        m_style_sets[ idx ] = style_set;

        return m_style_sets[ idx ];
    }

    const std::string persistent_styles::nf_at( const size_t idx ) const
    {
        const persistent_xf& xf = m_xfs.at( idx );

        if ( !( xf.apply_number_format == false ) && xf.num_fmt_id.present() && xf.num_fmt_id.get() > 0 ) {
            return m_nfmts.str( xf.num_fmt_id.get() );
        }

        return "";
    }

    void  persistent_styles::apply_border_at( border_manager& bm, const size_t idx, const size_t row, const size_t col, const bool is_import /* = true */ ) const
    {
        const persistent_xf& xf = m_xfs.at( idx );

        if ( !( xf.apply_border == false ) && xf.border_id.present() && xf.border_id.get() >= 0 ) {
            const persistent_xf& xf = m_xfs.at( idx );
            if ( xf.border_id.present() ) {
                m_borders.apply( bm, xf.border_id.get(), row, col, is_import );
            }
        }
    }

    const bool persistent_styles::protected_at( const size_t idx ) const
    {
        const persistent_xf& xf = m_xfs.at( idx );

        return  !( xf.apply_protection == false ) && xf.protection.present() && xf.protection.get().locked.present();
    }

    const persistent_dxf& persistent_styles::dxf_at( const size_t idx ) const
    {
        return m_dxfs[ idx ];
    }

    const bool persistent_styles::has_dxf( const size_t idx ) const
    {
        return m_dxfs.size() > idx;
    }

    const persistent_color_table& persistent_styles::color_table() const
    {
        return m_color_table;
    }

    int persistent_styles::get_empty_style()
    {
        if ( m_empty_style_id != -1 ) {
            return m_empty_style_id;
        }

        persistent_style style;

        style.nfmt_id = 0;
        style.font_id = 0;
        style.fill_id = 0;
        style.border_id = 0;

        //insert style
        m_empty_style_id = static_cast<int>( m_styles.size() );
        m_styles.push_back( style );
        m_style_map[""] = m_empty_style_id;

        return m_empty_style_id;
    }

    const bool  persistent_styles::quote_prefix_at ( const size_t idx ) const
    {

        return m_xfs.at( idx ).quote_prefix;
    }

}
