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

struct function_randbetween_helper : non_instantiable {

    static inline variant generate_random_number_array( const sheet_range array_dimensions, const double min, const double max ) {
        const size_t array_size =  array_dimensions.count();
        variant::variant_array_type return_val;
        for ( size_t i = 0; i < array_size; ++i ) {
            return_val.set( i, ( double )static_cast<int>( ( generate_random_number() * ( max - min ) ) + min ) );
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
 * Returns an integer random number between the min and max parameters
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
 *
 * \see
 * function_rand
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */

interpreter_variant function_randbetween( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    double min = 0.0;
    double max = 0.0;


    if ( parameters[0].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            min = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[0].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        min = static_cast<int>( parameters[0].numeric() );
    }

    if ( parameters[1].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            max = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[1].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        max = static_cast<int>( parameters[1].numeric() );
    }


    if  ( parameters.context().has_array_return_type() ) {
        return interpreter_variant( function_randbetween_helper::generate_random_number_array( parameters.context().caller()->array_coverage(), min, max ) );
    }

    return interpreter_variant( variant( ( double )static_cast<int>( ( function_randbetween_helper::generate_random_number() * ( max - min ) ) + min ) ) );
}
