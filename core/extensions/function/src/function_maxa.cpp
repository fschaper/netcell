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
#include "traversea.hpp"
#include "traverse.hpp"



/*!
 * \brief
 * Returns the largest value in a list of arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the largest value of the arguments
 *
 * \details
 * Arguments that are numbers, logical values, or text representations of numbers are counted.
 * Empty parameters are evaluated as 0, empty cells are ignored.
 * Error values cause errors. Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an argument is an array or reference, numbers and logical values in that array or reference are used.
 * Empty cells are ignored. Text is evaluated as 0.
 * If the arguments contain no values, MAXA returns 0.
 *
 * \see
 * function_max | function_dmax
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */



class max_alg : public error_handling_alg
{
private:
    size_t      m_count;
    double      m;
public:
    max_alg() {
        m_count = 0;
        m = 0;
    }

    void operator()( const variant& arg ) {
        m_count++;
        if ( m < arg.as_double() ) {
            m = arg.as_double();
        }
    }

    operator variant() {
        if ( 0 == m_count ) {
            return variant( 0.0 );
        }

        return ( variant( m ) );
    }

};

interpreter_variant function_maxa( function_parameter& parameters )
{
    max_alg alg;
    return interpreter_variant( traversea( parameters, alg ) );
}
