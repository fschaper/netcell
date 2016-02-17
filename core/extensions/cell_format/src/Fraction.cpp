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

#include "Fraction.hpp"

#include <cmath>
#include <valarray>

namespace cell_format
{

    // create a chain fraction approaching the value
    // result is returned in vec which has length n+1 and is terminated by -1
    static void get_c_fraction( std::valarray<int>& vec, double x, int n )
    {
        //n: max number of factors
        //x: real number

        int k, a;
        double y;
        double error = 0.000001;

        vec.resize( n + 1 );

        for ( k = 0; k < n; k++ ) {
            a = ( int )floor( x );
            vec[k] = a;
            y = x - a;
            if ( y < error ) {
                vec[k+1] = -1;
                return;
            }
            x = 1 / y;
        }

        vec[n] = -1;

        return;
    }

    void Fraction::calculate( double value, int max_denominator, int& numerator, int& denominator )
    {
        int i;
        int x_0 = 1, x_1 = 0, x_2;
        std::valarray<int> vec;
        int n = 10;

        get_c_fraction( vec, value, n );
        i = n + 1;
        while ( vec[--i] != -1 );
        n = --i; // n is the actual length of vec

        for ( ;; ) {
            x_1 = 0;
            x_2 = 1;

            for ( i = n; i >= 0; i-- ) {
                x_0 = x_1;
                x_1 = x_2;
                x_2 = vec[i] * x_1 + x_0;
            }

            if ( abs( x_1 ) >= max_denominator ) {
                n--;
                continue;
            } else {
                break;
            }
        }

        numerator = x_2;
        denominator = x_1;

        return;
    }

}
