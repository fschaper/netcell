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
 * TODO
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 *
 * \returns
 * TODO
 *
 * \details
 * TODO
 *
 * \see
 * internal::Sum | internal::SumSq | internal::Counter | function_stdeva | function_stdevp | function_stdevpa | function_dstdev | function_dstdevp
 *
 * \author
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
class sum_alg : public error_handling_alg
{
private:
    size_t      m_count;
    double      s;
public:
    sum_alg() {
        m_count = 0;
        s = 0;
    }

    void operator()( const variant& arg ) {
        m_count++;
        s += arg.as_double();
    }

    operator variant() {
        //         if ( 0 == m_count ) {
        //             return variant( variant::error_n_a );
        //         }

        return ( variant( s ) );
    }
};

interpreter_variant function_sum( function_parameter& parameters )
{
    sum_alg alg;
    return interpreter_variant( traverse( parameters, alg ) );
}
