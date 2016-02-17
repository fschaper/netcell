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

#ifndef CELL_FORMAT_DATA_READERS_HPP
#define CELL_FORMAT_DATA_READERS_HPP

#include "cell_format_data.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace cfd
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class CT_Month_reader;
        class CT_MonthList_reader;
        class CT_DayOfWeek_reader;
        class CT_DaysOfWeek_reader;
        class Char_reader;
        class CT_FormatCodes_reader;
        class CT_Color_reader;
        class CT_Colors_reader;
        class CT_Boolean_reader;
        class CT_Locale_reader;
        class CT_FormatCodesOverlay_reader;
        class CT_LocaleDiversion_reader;
        class CT_Locales_reader;
        class CT_Format_reader;
        class CT_DefaultFormat_reader;
        class CT_Formats_reader;
        class CT_ReverseFormat_reader;
        class CT_ReverseFormats_reader;
        class CT_Root_reader;
        class cell_format_data_reader;

        class CT_Month_reader : public type_reader
        {
        protected:
            CT_Month* t() {
                return static_cast<CT_Month*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_MonthList_reader : public type_reader
        {
            auto_type_reader< CT_Month_reader > _Month_reader;
        protected:
            CT_MonthList* t() {
                return static_cast<CT_MonthList*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_DayOfWeek_reader : public type_reader
        {
        protected:
            CT_DayOfWeek* t() {
                return static_cast<CT_DayOfWeek*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_DaysOfWeek_reader : public type_reader
        {
            auto_type_reader< CT_DayOfWeek_reader > _DayOfWeek_reader;
        protected:
            CT_DaysOfWeek* t() {
                return static_cast<CT_DaysOfWeek*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class Char_reader : public type_reader
        {
        protected:
            Char* t() {
                return static_cast<Char*>( target() );
            }
            void read_value( const xstring& val );
        };

        class CT_FormatCodes_reader : public type_reader
        {
        protected:
            CT_FormatCodes* t() {
                return static_cast<CT_FormatCodes*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_Color_reader : public type_reader
        {
        protected:
            CT_Color* t() {
                return static_cast<CT_Color*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_Colors_reader : public type_reader
        {
            auto_type_reader< CT_Color_reader > _Red_reader;
            auto_type_reader< CT_Color_reader > _Black_reader;
            auto_type_reader< CT_Color_reader > _Cyan_reader;
            auto_type_reader< CT_Color_reader > _Magenta_reader;
            auto_type_reader< CT_Color_reader > _White_reader;
            auto_type_reader< CT_Color_reader > _Blue_reader;
            auto_type_reader< CT_Color_reader > _Green_reader;
            auto_type_reader< CT_Color_reader > _Yellow_reader;
        protected:
            CT_Colors* t() {
                return static_cast<CT_Colors*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_Boolean_reader : public type_reader
        {
        protected:
            CT_Boolean* t() {
                return static_cast<CT_Boolean*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_Locale_reader : public type_reader
        {
            auto_type_reader< CT_MonthList_reader > _Months_reader;
            auto_type_reader< CT_DaysOfWeek_reader > _DaysOfWeek_reader;
            auto_type_reader< CT_FormatCodes_reader > _FormatCodes_reader;
            auto_type_reader< CT_Colors_reader > _Colors_reader;
            auto_type_reader< CT_Boolean_reader > _Boolean_reader;
        protected:
            CT_Locale* t() {
                return static_cast<CT_Locale*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_FormatCodesOverlay_reader : public type_reader
        {
        protected:
            CT_FormatCodesOverlay* t() {
                return static_cast<CT_FormatCodesOverlay*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_LocaleDiversion_reader : public type_reader
        {
            auto_type_reader< CT_MonthList_reader > _Months_reader;
            auto_type_reader< CT_DaysOfWeek_reader > _DaysOfWeek_reader;
            auto_type_reader< CT_FormatCodesOverlay_reader > _FormatCodesOverlay_reader;
            auto_type_reader< CT_Colors_reader > _Colors_reader;
        protected:
            CT_LocaleDiversion* t() {
                return static_cast<CT_LocaleDiversion*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_Locales_reader : public type_reader
        {
            auto_type_reader< CT_Locale_reader > _LocaleTemplate_reader;
            auto_type_reader< CT_LocaleDiversion_reader > _LocaleDiversion_reader;
        protected:
            CT_Locales* t() {
                return static_cast<CT_Locales*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_Format_reader : public type_reader
        {
        protected:
            CT_Format* t() {
                return static_cast<CT_Format*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_DefaultFormat_reader : public type_reader
        {
            auto_type_reader< CT_Format_reader > _Format_reader;
        protected:
            CT_DefaultFormat* t() {
                return static_cast<CT_DefaultFormat*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_Formats_reader : public type_reader
        {
            auto_type_reader< CT_DefaultFormat_reader > _DefaultFormat_reader;
        protected:
            CT_Formats* t() {
                return static_cast<CT_Formats*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_ReverseFormat_reader : public type_reader
        {
        protected:
            CT_ReverseFormat* t() {
                return static_cast<CT_ReverseFormat*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_ReverseFormats_reader : public type_reader
        {
            auto_type_reader< CT_ReverseFormat_reader > _ReverseFormat_reader;
        protected:
            CT_ReverseFormats* t() {
                return static_cast<CT_ReverseFormats*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_Root_reader : public type_reader
        {
            auto_type_reader< CT_Locales_reader > _Locales_reader;
            auto_type_reader< CT_Formats_reader > _Formats_reader;
            auto_type_reader< CT_ReverseFormats_reader > _ReverseFormats_reader;
        protected:
            CT_Root* t() {
                return static_cast<CT_Root*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class cell_format_data_reader : public type_reader
        {
            auto_type_reader< CT_Root_reader > _Root_reader;
        protected:
            cell_format_data* t() {
                return static_cast<cell_format_data*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

    }
}
#endif

