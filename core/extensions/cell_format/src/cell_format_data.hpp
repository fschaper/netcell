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

#ifndef CELL_FORMAT_DATA_HPP
#define CELL_FORMAT_DATA_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace cfd
{
    using namespace ::xio;
    using namespace ::xio::xml::schema;

    class CT_Month;
    class CT_MonthList;
    class CT_DayOfWeek;
    class CT_DaysOfWeek;
    class Char;
    class CT_FormatCodes;
    class CT_Color;
    class CT_Colors;
    class CT_Boolean;
    class CT_Locale;
    class CT_FormatCodesOverlay;
    class CT_LocaleDiversion;
    class CT_Locales;
    class CT_Format;
    class CT_DefaultFormat;
    class CT_Formats;
    class CT_ReverseFormat;
    class CT_ReverseFormats;
    class CT_Root;
    class cell_format_data;

    class CT_Month
    {
    public:
        String short_name;
        String long_name;
    };

    class CT_MonthList
    {
    public:
        std::vector< CT_Month > Month;
    };

    class CT_DayOfWeek
    {
    public:
        String short_name;
        String long_name;
    };

    class CT_DaysOfWeek
    {
    public:
        std::vector< CT_DayOfWeek > DayOfWeek;
    };

    class Char : public simple_type<String>
    {
    public:
        Char() {}
        Char( const String& v ) : simple_type<String>( v ) {}
    };

    class CT_FormatCodes
    {
    public:
        Char second;
        Char minute;
        Char hour;
        Char day;
        Char month;
        Char year;
        Char decimal_sep;
        Char thousand_sep;
        Char list_sep;
        String date_sep;
        String time_sep;
        String currency;
        String general;
    };

    class CT_Color
    {
    public:
        String name;
    };

    class CT_Colors
    {
    public:
        CT_Color Red;
        CT_Color Black;
        CT_Color Cyan;
        CT_Color Magenta;
        CT_Color White;
        CT_Color Blue;
        CT_Color Green;
        CT_Color Yellow;
    };

    class ST_DateOrder
    {
        static String _literals[];
        String _value;
    public:
        enum value { DMY, MDY, YMD };

        static const String DMY_literal;
        static const String MDY_literal;
        static const String YMD_literal;

        ST_DateOrder() : _value( DMY_literal ) {}
        ST_DateOrder( value val ) : _value( convert( val ) ) {}
        ST_DateOrder( const String& str ) : _value( str ) {}

        static value convert( const String& str ) {
            return ( value )::xio::util::binary_search( str, _literals, 3, 0 );
        }
        static String convert( value v ) {
            return _literals[( int )v];
        }

        bool operator == ( const String& str ) const {
            return str == _value;
        }
        bool operator == ( value val ) const {
            return convert( val ) == _value;
        }
        bool operator != ( const String& str ) const {
            return str != _value;
        }
        bool operator != ( value val ) const {
            return convert( val ) != _value;
        }

        const String& operator = ( const String& str ) {
            _value = str;
            return str;
        }
        const value& operator = ( const value& val ) {
            _value = convert( val );
            return val;
        }

        operator const String& () const {
            return _value;
        }
        operator String& () {
            return _value;
        }
        operator value () const {
            return convert( _value );
        }
        String serialize() const {
            return _value;
        }
    };

    class CT_Boolean
    {
    public:
        String true_name;
        String false_name;
    };

    class CT_Locale
    {
    public:
        CT_MonthList Months;
        CT_DaysOfWeek DaysOfWeek;
        CT_FormatCodes FormatCodes;
        CT_Colors Colors;
        ST_DateOrder DateOrder;
        UnsignedShort YearLimit;
        CT_Boolean Boolean;
        Language id;
    };

    class CT_FormatCodesOverlay
    {
    public:
        poptional< Char > second;
        poptional< Char > minute;
        poptional< Char > hour;
        poptional< Char > day;
        poptional< Char > month;
        poptional< Char > year;
        poptional< Char > decimal_sep;
        poptional< Char > thousand_sep;
        poptional< Char > list_sep;
        optional< String > date_sep;
        optional< String > time_sep;
        optional< String > currency;
        optional< String > general;
    };

    class CT_LocaleDiversion
    {
    public:
        poptional< CT_MonthList > Months;
        poptional< CT_DaysOfWeek > DaysOfWeek;
        poptional< CT_FormatCodesOverlay > FormatCodesOverlay;
        poptional< CT_Colors > Colors;
        optional< UnsignedShort > year_limit;
        Language id;
        Language base_id;
    };

    class CT_Locales
    {
    public:
        std::vector< CT_Locale > LocaleTemplate;
        std::vector< CT_LocaleDiversion > LocaleDiversion;
    };

    class CT_Format
    {
    public:
        String locale_pattern;
        String code;
        optional< String > parse_locale;
    };

    class CT_DefaultFormat
    {
    public:
        std::vector< CT_Format > Format;
        UnsignedInt id;
    };

    class CT_Formats
    {
    public:
        std::vector< CT_DefaultFormat > DefaultFormat;
    };

    class ST_FormatClass
    {
        static String _literals[];
        String _value;
    public:
        enum value { _bool_, currency, date, date_time, number, time };

        static const String _bool__literal;
        static const String currency_literal;
        static const String date_literal;
        static const String date_time_literal;
        static const String number_literal;
        static const String time_literal;

        ST_FormatClass() : _value( number_literal ) {}
        ST_FormatClass( value val ) : _value( convert( val ) ) {}
        ST_FormatClass( const String& str ) : _value( str ) {}

        static value convert( const String& str ) {
            return ( value )::xio::util::binary_search( str, _literals, 6, 0 );
        }
        static String convert( value v ) {
            return _literals[( int )v];
        }

        bool operator == ( const String& str ) const {
            return str == _value;
        }
        bool operator == ( value val ) const {
            return convert( val ) == _value;
        }
        bool operator != ( const String& str ) const {
            return str != _value;
        }
        bool operator != ( value val ) const {
            return convert( val ) != _value;
        }

        const String& operator = ( const String& str ) {
            _value = str;
            return str;
        }
        const value& operator = ( const value& val ) {
            _value = convert( val );
            return val;
        }

        operator const String& () const {
            return _value;
        }
        operator String& () {
            return _value;
        }
        operator value () const {
            return convert( _value );
        }
        String serialize() const {
            return _value;
        }
    };

    class CT_ReverseFormat
    {
    public:
        String rule;
        String format;
        ST_FormatClass type;
    };

    class CT_ReverseFormats
    {
    public:
        std::vector< CT_ReverseFormat > ReverseFormat;
    };

    class CT_Root
    {
    public:
        CT_Locales Locales;
        CT_Formats Formats;
        CT_ReverseFormats ReverseFormats;
    };

    class cell_format_data
    {
    public:
        poptional< CT_Root > Root;
    };

}
#endif

