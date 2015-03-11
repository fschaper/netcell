/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  Marek Pikulski <marek.pikulski@jedox.com>
 */

#include "i18n.hpp"
#include "ExceptionFactory.hpp"

#include "cell_format_data_parser.hpp"
#include "cell_format_data.hpp"
#include "cell_format_cache.hpp"
#include "reverse_format.hpp"

namespace cell_format
{

    i18n::i18n()
    {
        create_default();
    }

    i18n::~i18n()
    {}

    void i18n::create_default()
    {
        ControlTokens ct;

        ct.colors[ Color::Red ] = "red";
        ct.colors[ Color::Black ] = "black";
        ct.colors[ Color::Cyan ] = "cyan";
        ct.colors[ Color::Magenta ] = "magenta";
        ct.colors[ Color::White ] = "white";
        ct.colors[ Color::Blue ] = "blue";
        ct.colors[ Color::Green ] = "green";
        ct.colors[ Color::Yellow ] = "yellow";

        ct.country_short_name = "en-US";
        ct.date_order = ControlTokens::DateOrder::MDY;

        ct.days_of_week[0] = ControlTokens::DayOfWeek( "sat", "saturday" );
        ct.days_of_week[1] = ControlTokens::DayOfWeek( "sun", "sunday" );
        ct.days_of_week[2] = ControlTokens::DayOfWeek( "mon", "monday" );
        ct.days_of_week[3] = ControlTokens::DayOfWeek( "tue", "tuesday" );
        ct.days_of_week[4] = ControlTokens::DayOfWeek( "wed", "wednesday" );
        ct.days_of_week[5] = ControlTokens::DayOfWeek( "thu", "thursday" );
        ct.days_of_week[6] = ControlTokens::DayOfWeek( "fri", "friday" );

        ct.months[ 0] = ControlTokens::Month( "jan", "january" );
        ct.months[ 1] = ControlTokens::Month( "feb", "february" );
        ct.months[ 2] = ControlTokens::Month( "mar", "march" );
        ct.months[ 3] = ControlTokens::Month( "apr", "april" );
        ct.months[ 4] = ControlTokens::Month( "may", "may" );
        ct.months[ 5] = ControlTokens::Month( "jun", "june" );
        ct.months[ 6] = ControlTokens::Month( "jul", "july" );
        ct.months[ 7] = ControlTokens::Month( "aug", "august" );
        ct.months[ 8] = ControlTokens::Month( "sep", "september" );
        ct.months[ 9] = ControlTokens::Month( "oct", "october" );
        ct.months[10] = ControlTokens::Month( "nov", "november" );
        ct.months[11] = ControlTokens::Month( "dec", "december" );

        ct.format_codes.currency = "$";
        ct.format_codes.date_separators = "/.-";

        ct.format_codes.time_separators = ":";
        ct.format_codes.list_separator = ';';
        ct.format_codes.thousand_separator = ',';
        ct.format_codes.decimal = '.';

        ct.format_codes.month = 'm';
        ct.format_codes.day = 'd';
        ct.format_codes.year = 'y';
        ct.format_codes.hour = 'h';
        ct.format_codes.minute = 'm';
        ct.format_codes.second = 's';

        ct.format_codes.general = "general";

        ct.year_limit = 30;

        ct.booleans.true_name = "true";
        ct.booleans.false_name = "false";

        m_lm[ locale::create( ct.country_short_name ) ] = ct;
    }

    void i18n::process_xml( const std::string& filename )
    {
        cell_format_cache&      cache = cell_format_cache::instance();
        std::ifstream   file;

        file.open( filename.c_str() );

        if ( file.fail() ) {
            ExceptionFactory::raise( I18nException::E_XML_FILE_OPEN_FAILED );
        }

        cfd::cell_format_data doc;

        try {
            ::xio::xml::binding::parser parser;
            parser.parse_doc( file, doc );
            if ( !doc.Root.present() ) {
                ExceptionFactory::raise( I18nException::E_XML_FILE_PARSE );
            }
        } catch ( ... ) {
            ExceptionFactory::raise( I18nException::E_XML_FILE_PARSE );
        }

        cfd::CT_Root cfg = doc.Root.get();

        // process locale templates
        for ( std::vector< cfd::CT_Locale >::const_iterator i = cfg.Locales.LocaleTemplate.begin(), e = cfg.Locales.LocaleTemplate.end(); i != e; ++i ) {
            ControlTokens ct;

            ct.colors[Color::Black] = i->Colors.Black.name;
            ct.colors[Color::Blue] = i->Colors.Blue.name;
            ct.colors[Color::Cyan] = i->Colors.Cyan.name;
            ct.colors[Color::Green] = i->Colors.Green.name;
            ct.colors[Color::Magenta] = i->Colors.Magenta.name;
            ct.colors[Color::Red] = i->Colors.Red.name;
            ct.colors[Color::White] = i->Colors.White.name;
            ct.colors[Color::Yellow] = i->Colors.Yellow.name;

            ct.country_short_name = i->id;

            ct.date_order = ( i->DateOrder == cfd::ST_DateOrder::DMY ? ControlTokens::DateOrder::DMY
                              : ( i->DateOrder == cfd::ST_DateOrder::MDY ? ControlTokens::DateOrder::MDY : ControlTokens::DateOrder::YMD ) );

            // days of week
            for ( std::vector< cfd::CT_DayOfWeek >::const_iterator j = i->DaysOfWeek.DayOfWeek.begin(), b = j, f = i->DaysOfWeek.DayOfWeek.end(); j != f; ++j ) {
                ct.days_of_week[ j - b ].short_name = j->short_name;
                ct.days_of_week[ j - b ].long_name = j->long_name;
            }

            ct.format_codes.currency = i->FormatCodes.currency;
            ct.format_codes.date_separators = i->FormatCodes.date_sep;
            ct.format_codes.day = i->FormatCodes.day.get()[0];
            ct.format_codes.decimal = i->FormatCodes.decimal_sep.get()[0];
            ct.format_codes.general = i->FormatCodes.general;
            ct.format_codes.hour = i->FormatCodes.hour.get()[0];
            ct.format_codes.list_separator = i->FormatCodes.list_sep.get()[0];
            ct.format_codes.minute = i->FormatCodes.minute.get()[0];
            ct.format_codes.month = i->FormatCodes.month.get()[0];
            ct.format_codes.second = i->FormatCodes.second.get()[0];
            ct.format_codes.thousand_separator = i->FormatCodes.thousand_sep.get()[0];
            ct.format_codes.time_separators = i->FormatCodes.time_sep;
            ct.format_codes.year = i->FormatCodes.year.get()[0];

            // moths
            for ( std::vector< cfd::CT_Month >::const_iterator j = i->Months.Month.begin(), b = j, f = i->Months.Month.end(); j != f; ++j ) {
                ct.months[ j - b ].short_name = j->short_name;
                ct.months[ j - b ].long_name = j->long_name;
            }

            ct.year_limit = i->YearLimit;

            ct.booleans.true_name = i->Boolean.true_name;
            ct.booleans.false_name = i->Boolean.false_name;

            // replace '-' with '_'
            std::string::size_type t = ct.country_short_name.find( '-' );
            if ( t != std::string::npos ) {
                ct.country_short_name[t] = '_';

                std::string::size_type max = ct.country_short_name.length();
                while ( ++t < max ) {
                    ct.country_short_name[t] = toupper( ct.country_short_name[t] );
                }
            }

            const locale key = locale::create( ct.country_short_name );

            m_lm[ key ] = ct;
            cache.register_locale( key );

        }

        // process locale diversions
        for ( std::vector< cfd::CT_LocaleDiversion >::const_iterator i = cfg.Locales.LocaleDiversion.begin(), e = cfg.Locales.LocaleDiversion.end(); i != e; ++i ) {
            locale_map_type::const_iterator b = m_lm.find( locale::create( i->base_id ) );

            if ( b == m_lm.end() ) {
                ExceptionFactory::raise( I18nException::E_XML_UNKNOWN_BASE_LOCALE );
            }

            ControlTokens ct = b->second;

            ct.country_short_name = i->id;

            // replace '-' with '_' and fix case
            std::string::size_type t = ct.country_short_name.find( '-' );
            if ( t != std::string::npos ) {
                //              ct.country_short_name[t] = '_';

                std::string::size_type max = ct.country_short_name.length();
                while ( ++t < max ) {
                    ct.country_short_name[t] = toupper( ct.country_short_name[t] );
                }
            }

            const locale key = locale::create( ct.country_short_name );

            /*! \todo implement cleanly */
            m_lm[ key ] = ct;
            cache.register_locale( key );
        }

        reverse_format::instance().process_xml( cfg.ReverseFormats );


        // process default formats
        for ( std::vector< cfd::CT_DefaultFormat >::const_iterator i = cfg.Formats.DefaultFormat.begin(), e = cfg.Formats.DefaultFormat.end(); i != e; ++i ) {

            for ( std::vector< cfd::CT_Format >::const_iterator j = i->Format.begin(), f = i->Format.end(); j != f; ++j ) {

                locale key = locale::create( j->locale_pattern );
                default_format_map_type::const_iterator it = m_default_formats.find( key );
                if ( it == m_default_formats.end() ) {
                    default_format_type dft;
                    dft[ i->id ] = j->code;
                    m_default_formats[ key ] = dft;
                } else {
                    default_format_type dft = it->second;
                    dft[ i->id ] = j->code;
                    m_default_formats[ key ] = dft;
                }

            }

        }

    }

    const ControlTokens& i18n::operator[] ( const locale& lang_code )
    {
        locale_map_type::const_iterator i = m_lm.find( lang_code );

        if ( i == m_lm.end() ) {
            if ( "*" == lang_code.language() || "" == lang_code.language() ) {
                ExceptionFactory::raise( I18nException::E_UNKNOWN_LOCALE_REQUESTED );
            } else {
                //try only the major version. lookup the first match in the list
                for ( locale_map_type::const_iterator i = m_lm.begin(); i != m_lm.end(); i++ ) {
                    if ( i->first.language() == lang_code.language() ) {
                        return i->second;
                    }
                }
                ExceptionFactory::raise( I18nException::E_UNKNOWN_LOCALE_REQUESTED );
            }
        }

        return i->second;
    }

    const ControlTokens& i18n::get_english()
    {
        return ( *this )[ locale::create( "en-US" ) ];
    }

    std::string i18n::default_format( const locale& lang_code, unsigned int f_id )
    {



        default_format_map_type::const_iterator i = m_default_formats.find( lang_code );
        if ( i == m_default_formats.end() ) {
            //try to find a generic lang code
            locale non_regioned = locale::create( lang_code.language() );

            i = m_default_formats.find( non_regioned );

            if ( i == m_default_formats.end() ) {

                ExceptionFactory::raise( I18nException::E_UNKNOWN_LOCALE_REQUESTED );
            }
        }

        default_format_type dft = i->second;
        default_format_type::const_iterator ii = dft.find( f_id );
        if ( ii == dft.end() ) {
            ExceptionFactory::raise( I18nException::E_UNKNOWN_FORMAT_ID_REQUESTED );
        } else {
            return ii->second;
        }


        return "";

    }

}
