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

#include "date_time_extractor.hpp"

#include <boost/tokenizer.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace cell_format
{

    date_time_extractor::operator variant()
    {
        typedef boost::char_separator<char> separator;
        typedef boost::tokenizer< boost::char_separator< char > > tokenizer;
        std::string ctrl_tokens( date_extractor::m_control_tokens.format_codes.time_separators );
        ctrl_tokens.append( " " );
        ctrl_tokens.append( date_extractor::m_control_tokens.format_codes.date_separators );

        tokenizer tokens( date_extractor::m_formatted_value, separator( ctrl_tokens.c_str() ) );

        tokenizer::iterator crt = tokens.begin();
        tokenizer::iterator end = tokens.end();

        m_year = 0;
        m_month = 0;
        m_second = 0;

        if ( end == crt ) {
            throw std::logic_error( "no hour" );
        }

        m_hour = hour( *crt );

        crt++;
        if ( end == crt ) {
            throw std::logic_error( "no  minute" );
        }

        m_minute = minute( *crt );

        crt++;
        if ( end == crt ) {
            throw std::logic_error( "invalid format" );
        }

        if ( "am" == *crt || "pm" == *crt ) {
            adjust_hour( *crt );
            crt++;
        }

        for ( size_t i = 0; i < 3; i++ ) {
            ControlTokens::DateOrder::DateOrderPart dop = date_extractor::m_control_tokens.date_order[i];
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



        //if ( end == crt ) {
        //          throw std::logic_error( "Invalid month" );
        //      }

        //      m_month = month( *crt );

        //      crt++;
        //      if ( end == crt ) {
        //          throw std::logic_error( "Invalid day" );
        //      }

        //      m_day = day( * crt );

        //      crt++;
        //      if ( end != crt ) {
        //          m_year = year( *crt );
        //      } else {
        //          boost::gregorian::date  today = boost::gregorian::date( boost::gregorian::day_clock::local_day() );
        //          m_year =   today.year();
        //      }

        return variant( total_days() + total_seconds() );
    }

}
