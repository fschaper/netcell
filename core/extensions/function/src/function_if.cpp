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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include <wss/sparse_range.hpp>
#include <wss/syntax.hpp>
#include <wss/opcode_interpreter.hpp>
#include <boost/foreach.hpp>
#include <wss/logger.hpp>
#include <wss/server.hpp>

#ifndef foreach
#define foreach BOOST_FOREACH
#endif
typedef boost::optional<interpreter_variant> optional_interpreter_variant_type;


struct raise_inside_lazy_function_counter {
    raise_inside_lazy_function_counter( interpreter_context& ic ) : m_ic( ic ) {
        m_ic.raise_inside_lazy_function_count();
    }
    ~raise_inside_lazy_function_counter() {
        m_ic.lower_inside_lazy_function_count();
    }
    interpreter_context& m_ic;
};

variant call_opcode_interpreter( bool inside_nf, const positioned_op_codes& op, interpreter_context& cx )
{
    return inside_nf ? opcode_interpreterT<true>::calculate( op, cx ) : opcode_interpreterT<false>::calculate( op, cx );
}
/*!
 * \brief
 * evaluates the TRUE or FALSE branch of the passed parameters based on CONDITION.
 *
 * IF( [CONDITION] ; [ [TRUE_BRANCH]; [FALSE_BRANCH] ] )
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * one of two value-parameters, depending on the first parameter
 *
 * \details
 * If the first parameter evaluates to TRUE, the second parameter is returned, else the third parameter is returned.
 *
 * \see
 * function_and | function_not | function_or
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
interpreter_variant function_if( function_parameter& parameters )
{
    static const int max_lazy_function_count = session::max_lazy_function_count;
    if ( parameters.context().inside_lazy_function_count() > max_lazy_function_count ) {
        LOG_ERROR( "lazy function count reached more than " << max_lazy_function_count << " stopping further calculation!" );
        return interpreter_variant( variant( variant::error_n_a ) );
    }
    const function_parameter::subtree_vector_type& subtree = parameters.subtree();
    if ( subtree.size() == 0 ) {
        // we need at least "two" parameters for the function
        throw invalid_function_exception( "missing parameters for if" );
    }

    const bool inside_nf = parameters.context().is_inside_named_formula();

    std::auto_ptr<raise_inside_lazy_function_counter> rc( new raise_inside_lazy_function_counter( parameters.context() ) );
    interpreter_variant condition( call_opcode_interpreter( inside_nf, *subtree[0], parameters.context() ) );
    rc.reset();

    if ( variant::type_array == condition.type() ) {
        variant::sparse_array_type  result_array;
        optional_interpreter_variant_type true_condition_result;
        optional_interpreter_variant_type false_condition_result;

        size_t current_index = 0;

        foreach( const variant::sparse_array_type::value_type & v, condition.array() ) {
            if ( v.as_boolean( parameters.context().locale() ) ) {
                if ( subtree.size() > 1 ) {
                    // evaluate the "true" condition when we have one
                    if ( !true_condition_result ) {
                        raise_inside_lazy_function_counter rc( parameters.context() );
                        true_condition_result.reset( interpreter_variant( call_opcode_interpreter( inside_nf, *subtree[1], parameters.context() ) ) );
                    }
                    if ( true_condition_result->is_array() ) {
                        if ( current_index < true_condition_result->array().size() ) {
                            result_array.push_back( true_condition_result->array()[current_index] );
                        } else {
                            result_array.push_back( variant( variant::error_n_a ) );
                        }
                    } else { //not an array
                        result_array.push_back( *true_condition_result );
                    }
                } else {
                    // all other cases return "0.0"
                    result_array.push_back( variant( 0.0 ) );
                }
            } else if ( subtree.size() >= 3 ) {
                // evaluate the "else" branch

                if ( !false_condition_result ) {
                    raise_inside_lazy_function_counter rc( parameters.context() );
                    false_condition_result.reset( interpreter_variant( call_opcode_interpreter( inside_nf, *subtree[2], parameters.context() ) ) );
                }
                if ( false_condition_result->is_array() ) {
                    if ( current_index < false_condition_result->array().size() ) {
                        result_array.push_back( false_condition_result->array()[current_index] );
                    } else {
                        result_array.push_back( variant( variant::error_n_a ) );
                    }
                } else { //not an array
                    result_array.push_back( *false_condition_result );
                }
            } else {
                // condition evaluates to false, return false.
                result_array.push_back( variant( false ) );
            }
            ++current_index;
        }
        return interpreter_variant( variant( result_array, condition.column_width() ) );
    } else if ( !condition.is_error() ) {
        if ( condition.as_boolean( parameters.context().locale() ) ) {
            if ( subtree.size() > 1 ) {
                // evaluate the "true" condition when we have one
                raise_inside_lazy_function_counter rc( parameters.context() );
                return interpreter_variant( call_opcode_interpreter( inside_nf, *subtree[1], parameters.context() ) );
            } else {
                // all other cases return "0.0"
                return interpreter_variant( variant( 0.0 ) );
            }
        } else if ( subtree.size() >= 3 ) {
            // evaluate the "else" branch
            raise_inside_lazy_function_counter rc( parameters.context() );
            return interpreter_variant( call_opcode_interpreter( inside_nf, *subtree[2], parameters.context() ) );
        } else {
            // condition evaluates to false, return false.
            return interpreter_variant( variant( false ) );
        }
    } else {
        return interpreter_variant( condition );
    }
    return interpreter_variant( variant( false ) );
}
