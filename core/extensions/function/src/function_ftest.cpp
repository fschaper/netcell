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
#include "traverse12.hpp"



class ftest_alg
{
private:
    size_t m_countx;
    size_t m_county;
    double sumx; // the sum of the data of array1.
    double sumy; // the sum of the data of array2.
    double sumx2; //the sum of the squares of the data of array1
    double sumy2; //the sum of the squares of the data of array2
public:
    ftest_alg() {
        m_countx = 0;
        m_county = 0;
        sumx = 0.0;
        sumx2 = 0.0;
        sumy = 0.0;
        sumy2 = 0.0;

    }

    void operator()( const variant& arg1, const variant& arg2 ) {

        if ( arg1.type() == variant::type_double ) {
            m_countx++;
            sumx += arg1.numeric();
            sumx2 += arg1.numeric() * arg1.numeric();
        }

        if ( arg2.type() == variant::type_double ) {
            m_county++;
            sumy += arg2.numeric();
            sumy2 += arg2.numeric() * arg2.numeric();
        }
    }

    operator variant() {
        if ( 0 == m_countx || 0 == m_county ) {
            return variant( variant::error_div_null );
        }

        double var1 = sumx2 - sumx * sumx / m_countx;
        var1 = var1 / ( m_countx - 1 );

        double var2 = sumy2 - sumy * sumy / m_county;
        var2 = var2 / ( m_county - 1 );

        // If the variance of array1 or array2 is zero, FTEST returns the #DIV/0! error value.
        if ( var1 == 0.0 || var2 == 0.0 ) {
            return variant( variant::error_div_null );
        }

        double F;
        double result = 0.0;
        if ( var1 < var2 ) {
            F = var2 / var1;
            boost::math::fisher_f dist( m_county - 1, m_countx - 1 );
            result = cdf( complement( dist, F ) );
        } else {
            F = var1 / var2;
            boost::math::fisher_f dist( m_countx - 1, m_county - 1 );
            result = cdf( complement( dist, F ) );
        }

        return variant( variant( 2.0 * result ) );

    }

};

/*!
 * \brief
 * Returns the one-tailed probability that the variances in array1 and array2 are not significantly different.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the one-tailed probability that the variances in array1 and array2 are not significantly different
 *
 * \details
 *
 * \see
 * function_fdist | function_finv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_ftest( function_parameter& parameters )
{
    ftest_alg alg;
    return interpreter_variant( traverse12( parameters, alg ) );
}





