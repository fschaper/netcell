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


// combin helps to calculate function_combin and function_hypgeomdist.
long long combin( long long number, long long number_chosen )
{
    if ( number < 0 || number_chosen < 0 || number < number_chosen ) {
        return 1L;
    }

    double result = 1.0;
    long long minNcDiff = number_chosen < number - number_chosen ? number_chosen : number - number_chosen;
    // Factorize only to the minimum.
    for ( long long i = 0; i < minNcDiff; i++ ) {
        result *= static_cast<double>( number - i ) / static_cast<double>( i + 1 );
    }

    return static_cast<long long>( result + 0.5 );
    // Returns the number of combinations (groups with number_chosen items) for a given number of items (number).
}

