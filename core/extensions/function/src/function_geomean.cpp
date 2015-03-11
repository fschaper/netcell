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
#include "traverse.hpp"


/*!
 * \brief
 * Estimates standard deviation based on a sample.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sample standard deviation of the parameters
 *
 * \details
 * The standard deviation is calculated using the unbiased "n-1" method.
 * Arguments that are numbers or logical values or text representations of numbers are not counted.
 * Error values cause errors. Text that cannot be translated into numbers causes the #VALUE! error value.
 * If an argument is an array or reference, only numbers in that array or reference are counted.
 * Empty cells, logical values, or text in the array or reference are ignored.
 *
 * \see
 * internal::Sum | internal::SumSq | internal::Counter | function_stdeva | function_stdevp | function_stdevpa | function_dstdev | function_dstdevp
 *
 * \author
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */



class geomean_alg : public error_handling_alg
{
private:
    size_t      m_count;
    double      p;
    bool        negative_arg;
public:
    geomean_alg() {
        m_count = 0;
        p = 1;
        negative_arg = false;
    }

    void operator()( const variant& arg ) {
        if ( !negative_arg ) {
            if ( arg.as_double() <= 0 ) {
                negative_arg = true;
            } else {
                m_count++;
                p *= arg.as_double();
            }
        }
    }

    operator variant() {
        if ( 0 == m_count ) {
            return variant( variant::error_n_a );
        }
        if ( negative_arg ) {
            return variant ( variant::error_value );
        }

        return ( variant( pow( p, 1.0 / static_cast<double>( m_count ) ) ) );
    }

};

interpreter_variant function_geomean( function_parameter& parameters )
{
    geomean_alg alg;
    return interpreter_variant( traverse( parameters, alg ) );
}
