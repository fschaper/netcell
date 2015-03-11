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

#include "time_extractor.hpp"

#include <boost/tokenizer.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace cell_format
{

    double time_extractor::total_seconds()
    {
        double time = m_minute + m_hour * 60;
        time *= 60;
        time += m_second;
        return time / 86400;
    }

    unsigned short time_extractor::hour( const std::string& input )
    {
        unsigned short computed_hour = boost::lexical_cast< unsigned short >( input );
        if ( computed_hour > 23 ) {
            throw std::logic_error( "invalid hour" );
        }
        /*if ( 12 == computed_hour ) {
            computed_hour = 0;
        }*/

        return computed_hour;
    }

    unsigned short time_extractor::minute( const std::string& input )
    {
        unsigned short computed_minute = boost::lexical_cast< unsigned short >( input );
        if ( computed_minute > 59 ) {
            throw std::logic_error( "invalid minute" );
        }
        return computed_minute;
    }

    unsigned short time_extractor::second( const std::string& input )
    {
        unsigned short computed_second = boost::lexical_cast< unsigned short >( input );
        if ( computed_second > 59 ) {
            throw std::logic_error( "invalid second" );
        }
        return computed_second;
    }

    unsigned short time_extractor::adjust_hour( const std::string& input )
    {
        if ( m_hour > 12 ) {
            throw std::logic_error( "invalid format" );
        }
        if ( "pm" == input && m_hour < 12 ) {
            m_hour += 12;
        } else if ( "am" != input && m_hour < 12 ) {
            throw std::logic_error( "invalid format" );
        }

        if ( "am" == input && 12 == m_hour ) {
            m_hour -= 12;
        }

        return m_hour;
    }

    time_extractor::operator variant()
    {
        typedef boost::char_separator<char> separator;
        typedef boost::tokenizer< boost::char_separator< char > > tokenizer;
        std::string ctrl_tokens( m_control_tokens.format_codes.time_separators );
        ctrl_tokens.append( " " );

        tokenizer tokens( m_formatted_value, separator( ctrl_tokens.c_str() ) );

        tokenizer::iterator crt = tokens.begin();
        tokenizer::iterator end = tokens.end();

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
        if ( end != crt ) {
            try {
                m_second = second( *crt );
                crt++;
                if ( end != crt ) {
                    adjust_hour( *crt );
                }
            } catch ( std::bad_cast& ) {
                adjust_hour( *crt );
            }
        }

        return variant( total_seconds() );
    }

}
