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

#include "precompiled_header.hpp"
#include "traverse2.hpp"





class pearson_alg
{
private:
    size_t      m_count;
    double sumx; // the sum of the data of array1.
    double sumy; // the sum of the data of array2.
    double sumxy; // the sum of the products of corresponding data of array1 and array2.
    double sumx2; //the sum of the squares of the data of array1
    double sumy2; //the sum of the squares of the data of array2
public:
    pearson_alg() {
        m_count = 0;
        sumx = 0.0;
        sumx2 = 0.0;
        sumy = 0.0;
        sumy2 = 0.0;
        sumxy = 0.0;

    }

    void operator()( const variant& arg1, const variant& arg2 ) {
        m_count++;
        sumx += arg1.numeric();
        sumx2 += arg1.numeric() * arg1.numeric();
        sumy += arg2.numeric();
        sumy2 += arg2.numeric() * arg2.numeric();
        sumxy += arg1.numeric() * arg2.numeric();
    }

    operator variant() {
        if ( 0 == m_count ) {
            return variant( variant::error_div_null );
        }

        double sx = sumx2 - sumx * sumx / m_count;
        double sy = sumy2 - sumy * sumy / m_count;
        // If any standard deviation equals zero, RSQ returns the #DIV/0! error value.
        if ( sx <= 0.0 || sy <= 0.0 ) {
            return  variant( variant::error_div_null );
        }

        double result = sumxy - sumx * sumy / m_count;
        result = result * result / sx / sy;
        return variant( sqrt( result ) );

    }

};

interpreter_variant function_pearson( function_parameter& parameters )
{
    pearson_alg alg;
    return interpreter_variant( traverse2( parameters, alg ) );
}
