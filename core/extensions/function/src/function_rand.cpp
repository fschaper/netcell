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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>

struct function_rand_helper : non_instantiable {

    static inline variant generate_random_number_array( const sheet_range array_dimensions ) {
        const size_t array_size =  array_dimensions.count();
        variant::variant_array_type return_val;
        for ( size_t i = 0; i < array_size; ++i ) {
            return_val.set( i, generate_random_number() );
        }
        return variant( return_val, array_dimensions.column_count() );
    }

    static inline double generate_random_number() {
        static boost::rand48 generator( static_cast<boost::int32_t>( std::time( 0 ) ) );

        return static_cast<double>( generator() ) / ( 1.00000000000001 * boost::rand48::max_value );
    }
};

/*!
 * \brief
 * Returns an evenly distributed random number greater than or equal to 0 and less than 1.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node&
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the random number
 *
 * \details
 * A new random number is returned every time the worksheet is calculated.
 * To generate a random real number between a and b, use: RAND()*(b-a)+a
 *
 * \see
 * function_randbetween
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 * Florian Schaper <florian.schaper@jedox.com>
 */
interpreter_variant function_rand( function_parameter& parameters )
{
    if  ( parameters.context().has_array_return_type() ) {
        return interpreter_variant( function_rand_helper::generate_random_number_array( parameters.context().caller()->array_coverage() ) );
    }

    return interpreter_variant( function_rand_helper::generate_random_number() );
}
