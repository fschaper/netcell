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

#ifndef CELL_FORMAT_DATA_WRITERS_HPP
#define CELL_FORMAT_DATA_WRITERS_HPP

#include "cell_format_data.hpp"
#include "cell_format_data_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace cfd
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class CT_Month_writer;
        class CT_MonthList_writer;
        class CT_DayOfWeek_writer;
        class CT_DaysOfWeek_writer;
        class Char_writer;
        class CT_FormatCodes_writer;
        class CT_Color_writer;
        class CT_Colors_writer;
        class CT_Boolean_writer;
        class CT_Locale_writer;
        class CT_FormatCodesOverlay_writer;
        class CT_LocaleDiversion_writer;
        class CT_Locales_writer;
        class CT_Format_writer;
        class CT_DefaultFormat_writer;
        class CT_Formats_writer;
        class CT_ReverseFormat_writer;
        class CT_ReverseFormats_writer;
        class CT_Root_writer;
        class cell_format_data_writer;

        class CT_Month_writer : public type_writer
        {
            CT_Month* t() {
                return static_cast<CT_Month*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_MonthList_writer : public type_writer
        {
            auto_type_writer< CT_Month_writer > _Month_writer;
            CT_MonthList* t() {
                return static_cast<CT_MonthList*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_DayOfWeek_writer : public type_writer
        {
            CT_DayOfWeek* t() {
                return static_cast<CT_DayOfWeek*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_DaysOfWeek_writer : public type_writer
        {
            auto_type_writer< CT_DayOfWeek_writer > _DayOfWeek_writer;
            CT_DaysOfWeek* t() {
                return static_cast<CT_DaysOfWeek*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class Char_writer : public type_writer
        {
            Char* t() {
                return static_cast<Char*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_FormatCodes_writer : public type_writer
        {
            CT_FormatCodes* t() {
                return static_cast<CT_FormatCodes*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_Color_writer : public type_writer
        {
            CT_Color* t() {
                return static_cast<CT_Color*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_Colors_writer : public type_writer
        {
            auto_type_writer< CT_Color_writer > _Red_writer;
            auto_type_writer< CT_Color_writer > _Black_writer;
            auto_type_writer< CT_Color_writer > _Cyan_writer;
            auto_type_writer< CT_Color_writer > _Magenta_writer;
            auto_type_writer< CT_Color_writer > _White_writer;
            auto_type_writer< CT_Color_writer > _Blue_writer;
            auto_type_writer< CT_Color_writer > _Green_writer;
            auto_type_writer< CT_Color_writer > _Yellow_writer;
            CT_Colors* t() {
                return static_cast<CT_Colors*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_Boolean_writer : public type_writer
        {
            CT_Boolean* t() {
                return static_cast<CT_Boolean*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_Locale_writer : public type_writer
        {
            auto_type_writer< CT_MonthList_writer > _Months_writer;
            auto_type_writer< CT_DaysOfWeek_writer > _DaysOfWeek_writer;
            auto_type_writer< CT_FormatCodes_writer > _FormatCodes_writer;
            auto_type_writer< CT_Colors_writer > _Colors_writer;
            auto_type_writer< CT_Boolean_writer > _Boolean_writer;
            CT_Locale* t() {
                return static_cast<CT_Locale*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_FormatCodesOverlay_writer : public type_writer
        {
            CT_FormatCodesOverlay* t() {
                return static_cast<CT_FormatCodesOverlay*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_LocaleDiversion_writer : public type_writer
        {
            auto_type_writer< CT_MonthList_writer > _Months_writer;
            auto_type_writer< CT_DaysOfWeek_writer > _DaysOfWeek_writer;
            auto_type_writer< CT_FormatCodesOverlay_writer > _FormatCodesOverlay_writer;
            auto_type_writer< CT_Colors_writer > _Colors_writer;
            CT_LocaleDiversion* t() {
                return static_cast<CT_LocaleDiversion*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_Locales_writer : public type_writer
        {
            auto_type_writer< CT_Locale_writer > _LocaleTemplate_writer;
            auto_type_writer< CT_LocaleDiversion_writer > _LocaleDiversion_writer;
            CT_Locales* t() {
                return static_cast<CT_Locales*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_Format_writer : public type_writer
        {
            CT_Format* t() {
                return static_cast<CT_Format*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_DefaultFormat_writer : public type_writer
        {
            auto_type_writer< CT_Format_writer > _Format_writer;
            CT_DefaultFormat* t() {
                return static_cast<CT_DefaultFormat*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_Formats_writer : public type_writer
        {
            auto_type_writer< CT_DefaultFormat_writer > _DefaultFormat_writer;
            CT_Formats* t() {
                return static_cast<CT_Formats*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_ReverseFormat_writer : public type_writer
        {
            CT_ReverseFormat* t() {
                return static_cast<CT_ReverseFormat*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_ReverseFormats_writer : public type_writer
        {
            auto_type_writer< CT_ReverseFormat_writer > _ReverseFormat_writer;
            CT_ReverseFormats* t() {
                return static_cast<CT_ReverseFormats*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_Root_writer : public type_writer
        {
            auto_type_writer< CT_Locales_writer > _Locales_writer;
            auto_type_writer< CT_Formats_writer > _Formats_writer;
            auto_type_writer< CT_ReverseFormats_writer > _ReverseFormats_writer;
            CT_Root* t() {
                return static_cast<CT_Root*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class cell_format_data_writer : public type_writer
        {
            auto_type_writer< CT_Root_writer > _Root_writer;
            cell_format_data* t() {
                return static_cast<cell_format_data*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

    }
}
#endif

