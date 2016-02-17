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

#include "date_extractor.hpp"

#include <boost/tokenizer.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace cell_format
{

    double date_extractor::total_days()
    {
        boost::gregorian::date  greg_date;

        greg_date = boost::gregorian::date( m_year, m_month, m_day );

        boost::gregorian::date  day_0( 1900, 1, 1 );

        boost::gregorian::date_duration lapsed_days = greg_date - day_0;

        int excelBugg = 1;
        if ( lapsed_days.days() > 58 ) {
            excelBugg++;
        }

        lapsed_days += boost::gregorian::date_duration( excelBugg );
        return ( double ) lapsed_days.days();
    }

    unsigned short date_extractor::month( const std::string& input )
    {
        unsigned short result;
        //1. given as text
        for ( unsigned short i = 0; i < 12; i++ ) {
            if ( m_control_tokens.months[i] == input ) {
                return i + 1;
            }
        }

        //given as number
        result = boost::lexical_cast< unsigned short >( input );
        if ( result < 1 || result > 12 ) {
            throw std::logic_error( "Invalid month" );
        }

        return result;
    }

    unsigned short date_extractor::day( const std::string& input )
    {
        return boost::lexical_cast< unsigned short >( input );
    }

    unsigned short date_extractor::year( const std::string& input )
    {
        unsigned short result;
        result = boost::lexical_cast< short >( input );

        if ( result <= 29 ) {
            result += 2000;
        } else if ( result <= 99 ) {
            result += 1900;
        } else if ( result < 1900 ) {
            throw std::logic_error( "Invalid year" );
        }

        return result;
    }

    date_extractor::operator variant()
    {
        typedef boost::char_separator<char> separator;
        typedef boost::tokenizer< boost::char_separator< char > > tokenizer;

        tokenizer tokens( m_formatted_value, separator( m_control_tokens.format_codes.date_separators.c_str() ) );

        tokenizer::iterator crt = tokens.begin();
        tokenizer::iterator end = tokens.end();

        for ( size_t i = 0; i < 3; i++ ) {
            ControlTokens::DateOrder::DateOrderPart dop = m_control_tokens.date_order[i];
            switch ( dop ) {
                case ControlTokens::DateOrder::Month:
                    if ( end == crt ) {
                        throw std::logic_error( "Invalid month" );
                    }
                    m_month = month( *crt );
                    crt++;
                    break;
                case ControlTokens::DateOrder::Day:
                    if ( end == crt ) {
                        throw std::logic_error( "Invalid day" );
                    }
                    m_day = day( * crt );
                    crt++;
                    break;

                case ControlTokens::DateOrder::Year:
                    if ( end == crt && i < 2 ) {
                        throw std::logic_error( "Invalid year" );
                    }
                    if ( end != crt ) {
                        m_year = year( *crt );
                        crt++;
                    } else {
                        boost::gregorian::date  today = boost::gregorian::date( boost::gregorian::day_clock::local_day() );
                        m_year =   today.year();
                    }

                    break;

                default:
                    break;

            }

        }

        return variant( total_days() );
    }

}
