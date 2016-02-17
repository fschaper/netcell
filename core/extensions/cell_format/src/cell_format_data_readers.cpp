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
#include "cell_format_data_readers.hpp"
#include "cell_format_data_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace cfd
{
    namespace xio
    {
        void CT_Month_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_short_name_literal ) ) {
                driver()->context()->parse( value, t()->short_name );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_long_name_literal ) ) {
                driver()->context()->parse( value, t()->long_name );
                return;
            }
        }
        void CT_MonthList_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Month_literal ) ) {
                t()->Month.resize( t()->Month.size() + 1 );
                driver()->push( localname, _Month_reader.get_reader( &t()->Month.back() ) );
                return;
            }
        }
        void CT_DayOfWeek_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_short_name_literal ) ) {
                driver()->context()->parse( value, t()->short_name );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_long_name_literal ) ) {
                driver()->context()->parse( value, t()->long_name );
                return;
            }
        }
        void CT_DaysOfWeek_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_DayOfWeek_literal ) ) {
                t()->DayOfWeek.resize( t()->DayOfWeek.size() + 1 );
                driver()->push( localname, _DayOfWeek_reader.get_reader( &t()->DayOfWeek.back() ) );
                return;
            }
        }
        void Char_reader::read_value( const xstring& val )
        {{
                driver()->context()->parse( val, *t() );
            }
        }
        void CT_FormatCodes_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_second_literal ) ) {
                driver()->context()->parse( value, t()->second );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_minute_literal ) ) {
                driver()->context()->parse( value, t()->minute );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_hour_literal ) ) {
                driver()->context()->parse( value, t()->hour );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_day_literal ) ) {
                driver()->context()->parse( value, t()->day );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_month_literal ) ) {
                driver()->context()->parse( value, t()->month );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_year_literal ) ) {
                driver()->context()->parse( value, t()->year );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_decimal_sep_literal ) ) {
                driver()->context()->parse( value, t()->decimal_sep );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_thousand_sep_literal ) ) {
                driver()->context()->parse( value, t()->thousand_sep );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_list_sep_literal ) ) {
                driver()->context()->parse( value, t()->list_sep );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_date_sep_literal ) ) {
                driver()->context()->parse( value, t()->date_sep );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_time_sep_literal ) ) {
                driver()->context()->parse( value, t()->time_sep );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_currency_literal ) ) {
                driver()->context()->parse( value, t()->currency );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_general_literal ) ) {
                driver()->context()->parse( value, t()->general );
                return;
            }
        }
        void CT_Color_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_name_literal ) ) {
                driver()->context()->parse( value, t()->name );
                return;
            }
        }
        void CT_Colors_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Red_literal ) ) {
                driver()->push( localname, _Red_reader.get_reader( &t()->Red ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Black_literal ) ) {
                driver()->push( localname, _Black_reader.get_reader( &t()->Black ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Cyan_literal ) ) {
                driver()->push( localname, _Cyan_reader.get_reader( &t()->Cyan ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Magenta_literal ) ) {
                driver()->push( localname, _Magenta_reader.get_reader( &t()->Magenta ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_White_literal ) ) {
                driver()->push( localname, _White_reader.get_reader( &t()->White ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Blue_literal ) ) {
                driver()->push( localname, _Blue_reader.get_reader( &t()->Blue ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Green_literal ) ) {
                driver()->push( localname, _Green_reader.get_reader( &t()->Green ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Yellow_literal ) ) {
                driver()->push( localname, _Yellow_reader.get_reader( &t()->Yellow ) );
                return;
            }
        }
        void CT_Boolean_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_true_name_literal ) ) {
                driver()->context()->parse( value, t()->true_name );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_false_name_literal ) ) {
                driver()->context()->parse( value, t()->false_name );
                return;
            }
        }
        void CT_Locale_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Months_literal ) ) {
                driver()->push( localname, _Months_reader.get_reader( &t()->Months ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_DaysOfWeek_literal ) ) {
                driver()->push( localname, _DaysOfWeek_reader.get_reader( &t()->DaysOfWeek ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_FormatCodes_literal ) ) {
                driver()->push( localname, _FormatCodes_reader.get_reader( &t()->FormatCodes ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Colors_literal ) ) {
                driver()->push( localname, _Colors_reader.get_reader( &t()->Colors ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Boolean_literal ) ) {
                driver()->push( localname, _Boolean_reader.get_reader( &t()->Boolean ) );
                return;
            }
        }
        void CT_Locale_reader::end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_DateOrder_literal ) ) {
                driver()->context()->parse( driver()->get_characters(), t()->DateOrder );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_YearLimit_literal ) ) {
                driver()->context()->parse( driver()->get_characters(), t()->YearLimit );
                return;
            }
        }
        void CT_Locale_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_id_literal ) ) {
                driver()->context()->parse( value, t()->id );
                return;
            }
        }
        void CT_FormatCodesOverlay_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_second_literal ) ) {
                driver()->context()->parse( value, t()->second.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_minute_literal ) ) {
                driver()->context()->parse( value, t()->minute.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_hour_literal ) ) {
                driver()->context()->parse( value, t()->hour.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_day_literal ) ) {
                driver()->context()->parse( value, t()->day.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_month_literal ) ) {
                driver()->context()->parse( value, t()->month.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_year_literal ) ) {
                driver()->context()->parse( value, t()->year.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_decimal_sep_literal ) ) {
                driver()->context()->parse( value, t()->decimal_sep.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_thousand_sep_literal ) ) {
                driver()->context()->parse( value, t()->thousand_sep.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_list_sep_literal ) ) {
                driver()->context()->parse( value, t()->list_sep.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_date_sep_literal ) ) {
                driver()->context()->parse( value, t()->date_sep.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_time_sep_literal ) ) {
                driver()->context()->parse( value, t()->time_sep.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_currency_literal ) ) {
                driver()->context()->parse( value, t()->currency.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_general_literal ) ) {
                driver()->context()->parse( value, t()->general.getset() );
                return;
            }
        }
        void CT_LocaleDiversion_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Months_literal ) ) {
                driver()->push( localname, _Months_reader.get_reader( &t()->Months.getset() ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_DaysOfWeek_literal ) ) {
                driver()->push( localname, _DaysOfWeek_reader.get_reader( &t()->DaysOfWeek.getset() ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_FormatCodesOverlay_literal ) ) {
                driver()->push( localname, _FormatCodesOverlay_reader.get_reader( &t()->FormatCodesOverlay.getset() ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Colors_literal ) ) {
                driver()->push( localname, _Colors_reader.get_reader( &t()->Colors.getset() ) );
                return;
            }
        }
        void CT_LocaleDiversion_reader::end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_year_limit_literal ) ) {
                driver()->context()->parse( driver()->get_characters(), t()->year_limit.getset() );
                return;
            }
        }
        void CT_LocaleDiversion_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_id_literal ) ) {
                driver()->context()->parse( value, t()->id );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_base_id_literal ) ) {
                driver()->context()->parse( value, t()->base_id );
                return;
            }
        }
        void CT_Locales_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_LocaleTemplate_literal ) ) {
                t()->LocaleTemplate.resize( t()->LocaleTemplate.size() + 1 );
                driver()->push( localname, _LocaleTemplate_reader.get_reader( &t()->LocaleTemplate.back() ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_LocaleDiversion_literal ) ) {
                t()->LocaleDiversion.resize( t()->LocaleDiversion.size() + 1 );
                driver()->push( localname, _LocaleDiversion_reader.get_reader( &t()->LocaleDiversion.back() ) );
                return;
            }
        }
        void CT_Format_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_locale_pattern_literal ) ) {
                driver()->context()->parse( value, t()->locale_pattern );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_code_literal ) ) {
                driver()->context()->parse( value, t()->code );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_parse_locale_literal ) ) {
                driver()->context()->parse( value, t()->parse_locale.getset() );
                return;
            }
        }
        void CT_DefaultFormat_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Format_literal ) ) {
                t()->Format.resize( t()->Format.size() + 1 );
                driver()->push( localname, _Format_reader.get_reader( &t()->Format.back() ) );
                return;
            }
        }
        void CT_DefaultFormat_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_id_literal ) ) {
                driver()->context()->parse( value, t()->id );
                return;
            }
        }
        void CT_Formats_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_DefaultFormat_literal ) ) {
                t()->DefaultFormat.resize( t()->DefaultFormat.size() + 1 );
                driver()->push( localname, _DefaultFormat_reader.get_reader( &t()->DefaultFormat.back() ) );
                return;
            }
        }
        void CT_ReverseFormat_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_rule_literal ) ) {
                driver()->context()->parse( value, t()->rule );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_format_literal ) ) {
                driver()->context()->parse( value, t()->format );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_type_literal ) ) {
                driver()->context()->parse( value, t()->type );
                return;
            }
        }
        void CT_ReverseFormats_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_ReverseFormat_literal ) ) {
                t()->ReverseFormat.resize( t()->ReverseFormat.size() + 1 );
                driver()->push( localname, _ReverseFormat_reader.get_reader( &t()->ReverseFormat.back() ) );
                return;
            }
        }
        void CT_Root_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Locales_literal ) ) {
                driver()->push( localname, _Locales_reader.get_reader( &t()->Locales ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Formats_literal ) ) {
                driver()->push( localname, _Formats_reader.get_reader( &t()->Formats ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_ReverseFormats_literal ) ) {
                driver()->push( localname, _ReverseFormats_reader.get_reader( &t()->ReverseFormats ) );
                return;
            }
        }
        void cell_format_data_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, cell_format_data_Root_literal ) ) {
                driver()->push( localname, _Root_reader.get_reader( &t()->Root.getset() ) );
                return;
            }
        }
    }
}
