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

#include "format_engine.hpp"
#include "cell_format_cache.hpp"
#include "i18n.hpp"
#include "FormattedCell.hpp"
#include "CellFormatProcessor.hpp"
#include "cell_format_exception.hpp"
#include "I18nException.hpp"
#include "reverse_format.hpp"

#include "cell_format_data_parser.hpp"
#include "cell_format_data.hpp"

namespace cell_format
{

    const locale& format_engine::get_english()
    {
        static locale english = locale::create( "en" );
        return english;
    }

    CellValue format_engine::cell_value_converter( const variant& value, const ::locale& l )
    {
        using namespace cell_format;
        switch ( value.type() ) {
            case variant::type_double:
                return CellValue( value.as_double() );

            case variant::type_string:
                return CellValue( value.string() );

            case variant::type_error:
                return CellValue( value.as_string( l ) );

            case variant::type_array:
                // (fschaper) in case of an array we choose the fist "non array" value as
                // the value to be formatted.
                return cell_value_converter( ( value.array().empty() ? variant( "" ) : value.array()[0] ), l );

            case variant::type_bool:
                return CellValue( value.as_string( l ) );

            default:
                break;
        }
        return CellValue();
    }

    std::string format_engine::formatted_value( session& s, const std::string& format, const variant& value )
    {
        if ( variant::type_empty == value.type() ) {
            return "";
        }

        FormattedCell formatted_value;

        try {
            formatted_value =
                cell_format_cache::instance().get( format ) >>
                CellFormatProcessor( i18n::instance()[ s.locale() ] ) <<
                cell_value_converter( value, s.locale() );
        } catch ( cell_format_exception& e ) {
            throw std::logic_error( e.get_message().c_str() );
        } catch ( cell_format::I18nException e ) {
            throw std::logic_error( "unknown locale" );
        }
        return formatted_value.value;
    }

    std::string format_engine::formatted_color( session& s, const std::string& format, const variant& value )
    {
        if ( variant::type_empty == value.type() ) {
            return "";
        }

        FormattedCell formatted_value;

        try {
            formatted_value =
                cell_format_cache::instance().get( format ) >>
                CellFormatProcessor( i18n::instance()[ s.locale() ] ) <<
                cell_value_converter( value, s.locale() );
        } catch ( cell_format_exception& e ) {
            throw std::logic_error( e.get_message().c_str() );
        } catch ( cell_format::I18nException e ) {
            throw std::logic_error( "unknown locale" );
        }
        return formatted_value.color.to_string();
    }

    std::string format_engine::formatted_value_locale( session& s, const std::string& format, const variant& value )
    {
        FormattedCell formatted_value;

        try {
            formatted_value =
                cell_format_cache::instance().get( s.locale(), format ) >>
                CellFormatProcessor( i18n::instance()[ s.locale() ] ) <<
                cell_value_converter( value, s.locale() );
        } catch ( cell_format_exception& e ) {
            throw std::logic_error( e.get_message().c_str() );
        } catch ( cell_format::I18nException e ) {
            throw std::logic_error( "unknown locale" );
        }
        return formatted_value.value;
    }

    std::string format_engine::generic_format_string( session& s, const std::string& format )
    {
        return parsed_cell_format::Allocator::instance().translate( s.locale(), format_engine::get_english(), format );
    }

    bool format_engine::find_format( session& s, const std::string& formatted_value, variant& value, std::string& format )
    {
        bool format_found =  reverse_format::instance().find_format( s.locale(), formatted_value, value, format );

        try {
            std::string fmt_value = format_engine::formatted_value( s, format, value );
        } catch ( std::logic_error& ) {

            return false;
        }

        return format_found;


    }

    std::string format_engine::default_format_string( const locale& l, const unsigned int format_id )
    {
        i18n& crt = i18n::instance();
        try {
            return crt.default_format( l, format_id );
        } catch ( I18nException& ) {
            return crt.default_format( format_engine::get_english(), format_id );
        }

    }


}
