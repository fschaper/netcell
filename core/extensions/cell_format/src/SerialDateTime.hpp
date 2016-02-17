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

namespace cell_format
{

    class SerialDateTime
    {
    public:
        struct NonSerial {
            NonSerial( unsigned int D, unsigned int M, unsigned int Y, double h, double m, double s )
                : D( D )
                , M( M )
                , Y( Y )
                , h( h )
                , m( m )
                , s( s )
            {}

            NonSerial()
                : D( 0 )
                , M( 0 )
                , Y( 0 )
                , h( 0 )
                , m( 0 )
                , s( 0 )
            {}

            unsigned int D, M, Y;
            double h, m, s;
        };

        SerialDateTime( unsigned int D, unsigned int M, unsigned int Y, double h, double m, double s )
            : serial( convert( NonSerial( D, M, Y, h, m, s ) ) )
        {}

        SerialDateTime( double serial )
            : serial( serial )
        {}

        ~SerialDateTime()
        {}

        double get_serial() const {
            return serial;
        }

        NonSerial get_non_serial() const {
            return convert( serial );
        }

        enum DayOfWeek {
            Saturday,
            Sunday,
            Monday,
            Tuesday,
            Wednesday,
            Thursday,
            Friday
        };

        DayOfWeek get_day_of_week() const;

    private:
        static double convert( const NonSerial& ns );
        static NonSerial convert( double serial );

        double serial;
    };
}
