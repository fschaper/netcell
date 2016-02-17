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

#pragma once

// stl
#include <string>
#include <cassert>

#include "Color.hpp"

namespace cell_format
{
    /*! Describes keyword (and key-characters).
     *
     *  \author Marek Pikulski <marek.pikulski@jedox.com>
     */
    class ControlTokens
    {
    public:
        ControlTokens()
        {}

        ~ControlTokens()
        {}

        std::string country_short_name;

        bool operator< ( const ControlTokens& right ) const {
            return country_short_name < right.country_short_name;
        }

        struct Month {
            Month()
            {}

            ~Month()
            {}

            Month( const std::string& short_name, const std::string& long_name )
                : short_name( short_name )
                , long_name( long_name )
            {}

            bool operator ==( const std::string& rh ) const {
                return ( short_name == rh ) || ( long_name == rh );
            }

            std::string short_name;
            std::string long_name;
        } months[12];

        struct boolean {
            boolean()
            {}

            ~boolean()
            {}

            boolean( const std::string& true_name, const std::string& false_name )
                : true_name( true_name )
                , false_name( false_name )
            {}

            std::string true_name;
            std::string false_name;
        } booleans;

        /*! Saturday is first. */
        struct DayOfWeek {
            DayOfWeek()
            {}

            ~DayOfWeek()
            {}

            DayOfWeek( const std::string& short_name, const std::string& long_name )
                : short_name( short_name )
                , long_name( long_name )
            {}

            bool operator ==( const std::string& rh ) const {
                return ( short_name == rh ) || ( long_name == rh );
            }

            std::string short_name;
            std::string long_name;
        } days_of_week[7];

        struct FormatCodes {
            char second;
            char minute;
            char hour;
            char day;
            char month;
            char year;
            char decimal;
            char thousand_separator;
            char list_separator;
            std::string date_separators;
            std::string time_separators;
            std::string currency;
            std::string general;
        } format_codes;

        std::string colors[Color::_UNSET_];

        unsigned short year_limit; // 2-digit years later than year_limit
        // will be assumed to be in the last century

        struct DateOrder {
            enum DateOrderPart {
                Year = 0,
                Month = 1,
                Day = 2
            };

            enum DateOrderType {
                DMY, MDY, YMD
            };

            DateOrder& operator=( const DateOrderType& t ) {
                m_type = t;
                return *this;
            }

            DateOrder()
                : m_type( MDY )
            {}

            DateOrderPart operator[]( unsigned char idx ) const {
                assert( idx < 3 );

                if ( m_type == MDY ) {
                    switch ( idx ) {
                        case 0:
                            return Month;
                        case 1:
                            return Day;
                        case 2:
                            return Year;
                    }
                } else if ( m_type == DMY ) {
                    switch ( idx ) {
                        case 0:
                            return Day;
                        case 1:
                            return Month;
                        case 2:
                            return Year;
                    }
                } else if ( m_type == YMD ) {
                    switch ( idx ) {
                        case 0:
                            return Year;
                        case 1:
                            return Month;
                        case 2:
                            return Day;
                    }
                }
                return ( DateOrderPart )( -1 ); // not reached
            };

        private:
            DateOrderType m_type;
        } date_order;

    };
}
