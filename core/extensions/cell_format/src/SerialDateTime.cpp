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

#include "SerialDateTime.hpp"

#include <cmath>

namespace cell_format
{

    /* ---- Schaltjahre ----
    4 Jahre: ja
    100 Jahre: nein, jedoch 400 Jahre: ja und 4000 Jahre wieder nicht
    EXCEL-specific: 1900,4000 und 8000 sind Schaltjahre (8000 nicht)
    */

    static int get_serial_date( long int day, long int month, long int year )
    {
        long int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        long int serialdate;
        if ( ( year % 4 == 0 ) && ( ( year % 100 != 0 ) || ( year % 400 == 0 ) ) ) {
            months[1] = 29;
        }
        if ( day == 29 && month == 2 && year == 1900 ) {
            return 60;
        }
        serialdate = ( year - 1 ) * 365 + ( year - 1 ) / 4 + ( year - 1 ) / 400 - ( year - 1 ) / 100;
        for ( month--; month >= 1; month-- ) {
            serialdate += months[month-1];
        }
        serialdate += day;
        serialdate -= 1899 * 365 + 1899 / 4 + 1899 / 400 - 1899 / 100;
        if ( serialdate >= 60 ) {
            serialdate++;
        }
        return serialdate;
    }

    double get_serial_time( double hours, double minutes, double seconds )
    {
        seconds += hours * 3600.0 + minutes * 60.0;
        return seconds / 86400.0;
    }

    double SerialDateTime::convert( const NonSerial& ns )
    {
        return get_serial_date( ns.D, ns.M, ns.Y ) + get_serial_time( ns.h, ns.m, ns.s );
    }

    static void get_dmy_date( long int serialdate, unsigned int* day, unsigned int* month, unsigned int* year )
    {
        unsigned int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        unsigned int d, m, y;

        if ( serialdate == 0 ) {
            *year = 1900;
            *month = 1;
            *day = 0;
            return;
        } else if ( serialdate == 60 ) {
            *year = 1900;
            *month = 2;
            *day = 29;
            return;
        }
        if ( serialdate > 60 ) {
            serialdate--;
        }
        serialdate += ( 1900 - 1 ) * 365 + 1900 / 4 + 1900 / 400 - 1900 / 100 - 1900 / 4000; //date becomes relative to zero

        //year
        /*if(serialdate%(4000*365+4000/4+4000/400-4000/100-4000/4000)>0) {
        y=serialdate/(4000*365+4000/4+4000/400-4000/100-4000/4000)*4000;
        serialdate%=(4000*365+4000/4+4000/400-4000/100-4000/4000);
        } else if(serialdate/(4000*365+4000/4+4000/400-4000/100-4000/4000)>1) {
        y=((serialdate/(4000*365+4000/4+4000/400-4000/100-4000/4000))-1)*4000;
        serialdate=(4000*365+4000/4+4000/400-4000/100-4000/4000);
        }*/
        if ( serialdate % ( 400 * 365 + 400 / 4 + 400 / 400 - 400 / 100 ) > 0 ) {
            y = serialdate / ( 400 * 365 + 400 / 4 + 400 / 400 - 400 / 100 ) * 400;
            serialdate %= ( 400 * 365 + 400 / 4 + 400 / 400 - 400 / 100 );
        } else {
            y = ( ( serialdate / ( 400 * 365 + 400 / 4 + 400 / 400 - 400 / 100 ) ) - 1 ) * 400 + 399;
            serialdate = 366;
            goto next;
        }

        if ( serialdate % ( 100 * 365 + 100 / 4 - 100 / 100 ) > 0 ) {
            y += serialdate / ( 100 * 365 + 100 / 4 - 100 / 100 ) * 100;
            serialdate %= ( 100 * 365 + 100 / 4 - 100 / 100 );
        } else {
            y += ( ( serialdate / ( 100 * 365 + 100 / 4 - 100 / 100 ) ) - 1 ) * 100 + 99;
            serialdate = 365;
            goto next;
        }

        if ( serialdate % ( 4 * 365 + 4 / 4 ) > 0 ) {
            y += serialdate / ( 4 * 365 + 4 / 4 ) * 4;
            serialdate %= ( 4 * 365 + 4 / 4 );
        } else {
            y += ( ( serialdate / ( 4 * 365 + 4 / 4 ) ) - 1 ) * 4 + 3;
            serialdate = 366;
            goto next;
        }

        if ( serialdate % 365 > 0 ) {
            y += serialdate / 365;
            serialdate %= 365;
        } else {
            y += ( serialdate / 365 ) - 1;
            serialdate = 365;
            goto next;
        }

next:
        *year = ++y; // gregorian calendar does not know year 0!

        //month
        if ( ( y % 4 == 0 ) && ( ( y % 100 != 0 ) || y % 400 == 0 ) ) {
            months[1] = 29;
        }
        for ( m = 0; m < 12; m++ ) {
            if ( serialdate - ( signed )months[m] > 0 ) {
                serialdate -= months[m];
            } else {
                break;
            }
        }

        *month = ++m;

        //day
        *day = d = serialdate;
    }

    static void get_hms_time( double fraction, double* hours, double* minutes, double* seconds )
    {
        double h, m, s;

        s = ( 24.0 * 60.0 * 60.0 ) * fraction;
        m = ( ( int )s ) / 60;
        s = fmod( s, 60.0 );
        h = ( ( int )m ) / 60;
        m = fmod( m, 60.0 );
        if ( s > 59 ) {
            m++;
            s = 0;
        }
        if ( m > 59 ) {
            h++;
            m = 0;
        }

        *hours = h;
        *minutes = m;
        *seconds = s;
    }

    SerialDateTime::NonSerial SerialDateTime::convert( double serial )
    {
        NonSerial ns;

        get_dmy_date( ( long int )serial, &ns.D, &ns.M, &ns.Y );
        get_hms_time( serial - ( long int )serial, &ns.h, &ns.m, &ns.s );

        return ns;
    }

    //Saturday=0
    static int get_day_of_week( double serialdatetime )
    {
        int D = ( long int )serialdatetime;
        return D %= 7;
    }

    SerialDateTime::DayOfWeek SerialDateTime::get_day_of_week() const
    {
        return ( SerialDateTime::DayOfWeek )cell_format::get_day_of_week( serial );
    }

}
