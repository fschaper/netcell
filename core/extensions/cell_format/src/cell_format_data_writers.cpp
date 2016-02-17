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
 */


// This file has been auto-generated. Don't change it by hand!

#include "precompiled_header.hpp"
#include "cell_format_data_writers.hpp"
#include "cell_format_data_literals.hpp"

namespace cfd
{
    namespace xio
    {
        void CT_Month_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_short_name_literal, context()->serialize( t()->short_name ) );
            w.attribute( 0, cell_format_data_long_name_literal, context()->serialize( t()->long_name ) );
        }

        void CT_MonthList_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->Month.size(); ++sqi ) {
                w.start_element( 0, cell_format_data_Month_literal );
                _Month_writer.get_writer( context(), &t()->Month[sqi] )->write_target_to( w );
                w.end_element( 0, cell_format_data_Month_literal );
            }
        }

        void CT_DayOfWeek_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_short_name_literal, context()->serialize( t()->short_name ) );
            w.attribute( 0, cell_format_data_long_name_literal, context()->serialize( t()->long_name ) );
        }

        void CT_DaysOfWeek_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->DayOfWeek.size(); ++sqi ) {
                w.start_element( 0, cell_format_data_DayOfWeek_literal );
                _DayOfWeek_writer.get_writer( context(), &t()->DayOfWeek[sqi] )->write_target_to( w );
                w.end_element( 0, cell_format_data_DayOfWeek_literal );
            }
        }

        void Char_writer::write_target_to( xml_writer& w )
        {
            w.write_element_value( context()->serialize( *t() ) );
        }

        void CT_FormatCodes_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_second_literal, context()->serialize( t()->second ) );
            w.attribute( 0, cell_format_data_minute_literal, context()->serialize( t()->minute ) );
            w.attribute( 0, cell_format_data_hour_literal, context()->serialize( t()->hour ) );
            w.attribute( 0, cell_format_data_day_literal, context()->serialize( t()->day ) );
            w.attribute( 0, cell_format_data_month_literal, context()->serialize( t()->month ) );
            w.attribute( 0, cell_format_data_year_literal, context()->serialize( t()->year ) );
            w.attribute( 0, cell_format_data_decimal_sep_literal, context()->serialize( t()->decimal_sep ) );
            w.attribute( 0, cell_format_data_thousand_sep_literal, context()->serialize( t()->thousand_sep ) );
            w.attribute( 0, cell_format_data_list_sep_literal, context()->serialize( t()->list_sep ) );
            w.attribute( 0, cell_format_data_date_sep_literal, context()->serialize( t()->date_sep ) );
            w.attribute( 0, cell_format_data_time_sep_literal, context()->serialize( t()->time_sep ) );
            w.attribute( 0, cell_format_data_currency_literal, context()->serialize( t()->currency ) );
            w.attribute( 0, cell_format_data_general_literal, context()->serialize( t()->general ) );
        }

        void CT_Color_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_name_literal, context()->serialize( t()->name ) );
        }

        void CT_Colors_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, cell_format_data_Red_literal );
            _Red_writer.get_writer( context(), &t()->Red )->write_target_to( w );
            w.end_element( 0, cell_format_data_Red_literal );
            w.start_element( 0, cell_format_data_Black_literal );
            _Black_writer.get_writer( context(), &t()->Black )->write_target_to( w );
            w.end_element( 0, cell_format_data_Black_literal );
            w.start_element( 0, cell_format_data_Cyan_literal );
            _Cyan_writer.get_writer( context(), &t()->Cyan )->write_target_to( w );
            w.end_element( 0, cell_format_data_Cyan_literal );
            w.start_element( 0, cell_format_data_Magenta_literal );
            _Magenta_writer.get_writer( context(), &t()->Magenta )->write_target_to( w );
            w.end_element( 0, cell_format_data_Magenta_literal );
            w.start_element( 0, cell_format_data_White_literal );
            _White_writer.get_writer( context(), &t()->White )->write_target_to( w );
            w.end_element( 0, cell_format_data_White_literal );
            w.start_element( 0, cell_format_data_Blue_literal );
            _Blue_writer.get_writer( context(), &t()->Blue )->write_target_to( w );
            w.end_element( 0, cell_format_data_Blue_literal );
            w.start_element( 0, cell_format_data_Green_literal );
            _Green_writer.get_writer( context(), &t()->Green )->write_target_to( w );
            w.end_element( 0, cell_format_data_Green_literal );
            w.start_element( 0, cell_format_data_Yellow_literal );
            _Yellow_writer.get_writer( context(), &t()->Yellow )->write_target_to( w );
            w.end_element( 0, cell_format_data_Yellow_literal );
        }

        void CT_Boolean_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_true_name_literal, context()->serialize( t()->true_name ) );
            w.attribute( 0, cell_format_data_false_name_literal, context()->serialize( t()->false_name ) );
        }

        void CT_Locale_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_id_literal, context()->serialize( t()->id ) );
            w.start_element( 0, cell_format_data_Months_literal );
            _Months_writer.get_writer( context(), &t()->Months )->write_target_to( w );
            w.end_element( 0, cell_format_data_Months_literal );
            w.start_element( 0, cell_format_data_DaysOfWeek_literal );
            _DaysOfWeek_writer.get_writer( context(), &t()->DaysOfWeek )->write_target_to( w );
            w.end_element( 0, cell_format_data_DaysOfWeek_literal );
            w.start_element( 0, cell_format_data_FormatCodes_literal );
            _FormatCodes_writer.get_writer( context(), &t()->FormatCodes )->write_target_to( w );
            w.end_element( 0, cell_format_data_FormatCodes_literal );
            w.start_element( 0, cell_format_data_Colors_literal );
            _Colors_writer.get_writer( context(), &t()->Colors )->write_target_to( w );
            w.end_element( 0, cell_format_data_Colors_literal );
            w.start_element( 0, cell_format_data_DateOrder_literal );
            w.write_element_value( context()->serialize( t()->DateOrder ) );
            w.end_element( 0, cell_format_data_DateOrder_literal );
            w.start_element( 0, cell_format_data_YearLimit_literal );
            w.write_element_value( context()->serialize( t()->YearLimit ) );
            w.end_element( 0, cell_format_data_YearLimit_literal );
            w.start_element( 0, cell_format_data_Boolean_literal );
            _Boolean_writer.get_writer( context(), &t()->Boolean )->write_target_to( w );
            w.end_element( 0, cell_format_data_Boolean_literal );
        }

        void CT_FormatCodesOverlay_writer::write_target_to( xml_writer& w )
        {
            if ( t()->second.present() ) {
                w.attribute( 0, cell_format_data_second_literal, context()->serialize( t()->second.get() ) );
            }
            if ( t()->minute.present() ) {
                w.attribute( 0, cell_format_data_minute_literal, context()->serialize( t()->minute.get() ) );
            }
            if ( t()->hour.present() ) {
                w.attribute( 0, cell_format_data_hour_literal, context()->serialize( t()->hour.get() ) );
            }
            if ( t()->day.present() ) {
                w.attribute( 0, cell_format_data_day_literal, context()->serialize( t()->day.get() ) );
            }
            if ( t()->month.present() ) {
                w.attribute( 0, cell_format_data_month_literal, context()->serialize( t()->month.get() ) );
            }
            if ( t()->year.present() ) {
                w.attribute( 0, cell_format_data_year_literal, context()->serialize( t()->year.get() ) );
            }
            if ( t()->decimal_sep.present() ) {
                w.attribute( 0, cell_format_data_decimal_sep_literal, context()->serialize( t()->decimal_sep.get() ) );
            }
            if ( t()->thousand_sep.present() ) {
                w.attribute( 0, cell_format_data_thousand_sep_literal, context()->serialize( t()->thousand_sep.get() ) );
            }
            if ( t()->list_sep.present() ) {
                w.attribute( 0, cell_format_data_list_sep_literal, context()->serialize( t()->list_sep.get() ) );
            }
            if ( t()->date_sep.present() ) {
                w.attribute( 0, cell_format_data_date_sep_literal, context()->serialize( t()->date_sep.get() ) );
            }
            if ( t()->time_sep.present() ) {
                w.attribute( 0, cell_format_data_time_sep_literal, context()->serialize( t()->time_sep.get() ) );
            }
            if ( t()->currency.present() ) {
                w.attribute( 0, cell_format_data_currency_literal, context()->serialize( t()->currency.get() ) );
            }
            if ( t()->general.present() ) {
                w.attribute( 0, cell_format_data_general_literal, context()->serialize( t()->general.get() ) );
            }
        }

        void CT_LocaleDiversion_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_id_literal, context()->serialize( t()->id ) );
            w.attribute( 0, cell_format_data_base_id_literal, context()->serialize( t()->base_id ) );
            if ( t()->Months.present() ) {
                w.start_element( 0, cell_format_data_Months_literal );
                _Months_writer.get_writer( context(), &t()->Months.get() )->write_target_to( w );
                w.end_element( 0, cell_format_data_Months_literal );
            }
            if ( t()->DaysOfWeek.present() ) {
                w.start_element( 0, cell_format_data_DaysOfWeek_literal );
                _DaysOfWeek_writer.get_writer( context(), &t()->DaysOfWeek.get() )->write_target_to( w );
                w.end_element( 0, cell_format_data_DaysOfWeek_literal );
            }
            if ( t()->FormatCodesOverlay.present() ) {
                w.start_element( 0, cell_format_data_FormatCodesOverlay_literal );
                _FormatCodesOverlay_writer.get_writer( context(), &t()->FormatCodesOverlay.get() )->write_target_to( w );
                w.end_element( 0, cell_format_data_FormatCodesOverlay_literal );
            }
            if ( t()->Colors.present() ) {
                w.start_element( 0, cell_format_data_Colors_literal );
                _Colors_writer.get_writer( context(), &t()->Colors.get() )->write_target_to( w );
                w.end_element( 0, cell_format_data_Colors_literal );
            }
            if ( t()->year_limit.present() ) {
                w.start_element( 0, cell_format_data_year_limit_literal );
                w.write_element_value( context()->serialize( t()->year_limit.get() ) );
                w.end_element( 0, cell_format_data_year_limit_literal );
            }
        }

        void CT_Locales_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->LocaleTemplate.size(); ++sqi ) {
                w.start_element( 0, cell_format_data_LocaleTemplate_literal );
                _LocaleTemplate_writer.get_writer( context(), &t()->LocaleTemplate[sqi] )->write_target_to( w );
                w.end_element( 0, cell_format_data_LocaleTemplate_literal );
            }
            for ( size_t sqi = 0; sqi < t()->LocaleDiversion.size(); ++sqi ) {
                w.start_element( 0, cell_format_data_LocaleDiversion_literal );
                _LocaleDiversion_writer.get_writer( context(), &t()->LocaleDiversion[sqi] )->write_target_to( w );
                w.end_element( 0, cell_format_data_LocaleDiversion_literal );
            }
        }

        void CT_Format_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_locale_pattern_literal, context()->serialize( t()->locale_pattern ) );
            w.attribute( 0, cell_format_data_code_literal, context()->serialize( t()->code ) );
            if ( t()->parse_locale.present() ) {
                w.attribute( 0, cell_format_data_parse_locale_literal, context()->serialize( t()->parse_locale.get() ) );
            }
        }

        void CT_DefaultFormat_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_id_literal, context()->serialize( t()->id ) );
            for ( size_t sqi = 0; sqi < t()->Format.size(); ++sqi ) {
                w.start_element( 0, cell_format_data_Format_literal );
                _Format_writer.get_writer( context(), &t()->Format[sqi] )->write_target_to( w );
                w.end_element( 0, cell_format_data_Format_literal );
            }
        }

        void CT_Formats_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->DefaultFormat.size(); ++sqi ) {
                w.start_element( 0, cell_format_data_DefaultFormat_literal );
                _DefaultFormat_writer.get_writer( context(), &t()->DefaultFormat[sqi] )->write_target_to( w );
                w.end_element( 0, cell_format_data_DefaultFormat_literal );
            }
        }

        void CT_ReverseFormat_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, cell_format_data_rule_literal, context()->serialize( t()->rule ) );
            w.attribute( 0, cell_format_data_format_literal, context()->serialize( t()->format ) );
            w.attribute( 0, cell_format_data_type_literal, context()->serialize( t()->type ) );
        }

        void CT_ReverseFormats_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->ReverseFormat.size(); ++sqi ) {
                w.start_element( 0, cell_format_data_ReverseFormat_literal );
                _ReverseFormat_writer.get_writer( context(), &t()->ReverseFormat[sqi] )->write_target_to( w );
                w.end_element( 0, cell_format_data_ReverseFormat_literal );
            }
        }

        void CT_Root_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, cell_format_data_Locales_literal );
            _Locales_writer.get_writer( context(), &t()->Locales )->write_target_to( w );
            w.end_element( 0, cell_format_data_Locales_literal );
            w.start_element( 0, cell_format_data_Formats_literal );
            _Formats_writer.get_writer( context(), &t()->Formats )->write_target_to( w );
            w.end_element( 0, cell_format_data_Formats_literal );
            w.start_element( 0, cell_format_data_ReverseFormats_literal );
            _ReverseFormats_writer.get_writer( context(), &t()->ReverseFormats )->write_target_to( w );
            w.end_element( 0, cell_format_data_ReverseFormats_literal );
        }

        void cell_format_data_writer::write_target_to( xml_writer& w )
        {
            if ( t()->Root.present() ) {
                w.start_element( 0, cell_format_data_Root_literal );
                w.attribute( 0, cell_format_data_xmlns_literal, cell_format_data_http_colon__slash__slash_tempuri_dot_org_slash_cell_format_data_dot_xsd_literal );
                w.attribute( cell_format_data_xmlns_literal, cell_format_data_mstns_literal, cell_format_data_http_colon__slash__slash_tempuri_dot_org_slash_cell_format_data_dot_xsd_literal );
                w.attribute( cell_format_data_xmlns_literal, cell_format_data_xs_literal, cell_format_data_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal );
                _Root_writer.get_writer( context(), &t()->Root.get() )->write_target_to( w );
                w.end_element( 0, cell_format_data_Root_literal );
            }
        }

    }
}
