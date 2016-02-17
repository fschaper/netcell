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
*  and do not license and distribute their source op under the GPL, Jedox provides
*  a flexible OEM Commercial License.
*
*  \author
*  Florian Schaper <florian.schaper@jedox.com>
*/

#include "precompiled_header.hpp"
#include "wss/opcode_interpreter.hpp"

#include "wss/variant_conversion_exception.hpp"
#include "wss/token_stream_specialization.hpp"
#include "wss/invalid_function_exception.hpp"
#include "wss/named_formula_reference.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/function_parameters.hpp"
#include "wss/function_registry.hpp"
#include "wss/translation_table.hpp"
#include "wss/vector_io_device.hpp"
#include "wss/range_reference.hpp"
#include "wss/function_entry.hpp"
#include "wss/binary_istream.hpp"
#include "wss/a1conversion.hpp"
#include "wss/i_dependency.hpp"
#include "wss/worksheet.hpp"
#include "wss/workbook.hpp"
#include "wss/opcode.hpp"
#include "wss/token.hpp"
#include "wss/stack.hpp"
#include "wss/range.hpp"

#include "named_formula.hpp"
#include "opcode_stream_helper.hpp"
#include "named_formula_wrapper.hpp"

template<class T>
struct is_error: non_instantiable {
    static bool check( const T& v ) {
        return v.is_error();
    }
};
template<>
struct is_error<double>: non_instantiable {
    static bool check( const double v ) {
        return false;
    }
};

struct opcode_interpreter_helper : non_instantiable {
    template<typename function_T, function_T callback, class lhs_T, class rhs_T>
    static inline interpreter_variant call_function( const lhs_T& lhs, const rhs_T& rhs ) {
        if ( is_error<lhs_T>::check( lhs ) ) {
            return interpreter_variant( lhs );
        } else if ( is_error<rhs_T>::check( rhs ) ) {
            return interpreter_variant( rhs );
        }
        try {
            return interpreter_variant( ( lhs.*callback )( rhs ) );
        } catch ( const variant_conversion_exception& ) {
            return interpreter_variant( variant::error_value );
        }
    }

    template<bool called_from_inside_nf>
    static inline referencetable_type& select_references( const positioned_op_codes& op, interpreter_context& cx ) {
        if ( called_from_inside_nf ) {
            return const_cast<positioned_op_codes*>( &op )->positional_references( cx.caller() ).reference;
        } else {
            return cx.is_inside_named_formula()
                   ? const_cast<positioned_op_codes*>( &op )->positional_references( cx.named_formula_initiator() ).reference
                   : const_cast<positioned_op_codes*>( &op )->original_opcode.location_dependent_reference.reference;
        }
    }
};
/*!
 * \brief
 * opcode interpreter.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<bool called_from_inside_nf>
variant opcode_interpreterT<called_from_inside_nf>::calculate( const positioned_op_codes& op, interpreter_context& cx )
{
    static const variant percent( 100.0 );
    binary_istream<vector_io_device> token_stream;
#ifdef _DEBUG
    size_t stack_size;
    stack_size = cx.stack().size();
#endif // _DEBUG
    token_stream.open( const_cast<opcode::sequence_type*>( &op.original_opcode.code ) );
    token::type current_token;
    referencetable_type& references = opcode_interpreter_helper::select_references<called_from_inside_nf>( op, cx );
    while ( ! token_stream.eof() ) {
        token_stream >> current_token;
        switch ( current_token ) {
            case token::dec_fct_count:
                cx.lower_inside_function_count();
                break;
            case token::inc_fct_count:
                cx.raise_inside_function_count();
                break;
            case token::addition:
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::add >( cx.stack().pop(), cx.stack().pop() ) );
                break;

            case token::array_row: {
                std::size_t element_count;
                token_stream >> element_count;

                variant::sparse_array_type::native_vector_type array;
                array.reserve( element_count );
                for ( std::size_t array_size = element_count; array_size > 0; --array_size ) {
                    const variant& crt = cx.stack().pop();
                    array.insert( array.begin(), crt );
                }
                variant::sparse_array_type sparse_array( array );
                cx.stack().push( interpreter_variant( variant( sparse_array ) ) );
            }
            break;

            case token::array: {
                std::size_t element_count;
                token_stream >> element_count;
                std::size_t col_width = 0;

                variant::sparse_array_type::native_vector_type array;
                array.reserve( element_count );
                for ( std::size_t array_size = element_count; array_size > 0; --array_size ) {
                    const interpreter_variant crt = cx.stack().pop();
                    if ( variant::type_array == crt.type() ) {
                        variant::sparse_array_type::native_vector_type::iterator pos = array.begin();
                        const variant::sparse_array_type& sp = crt.array();
                        for ( variant::sparse_array_type::const_iterator it = sp.begin(), end_it = sp.end(); it != end_it; ++it ) {
                            //foreach( const variant & v, crt.array() ) {
                            pos = array.insert( pos, *it ) + 1;
                            col_width++;
                        }
                    } else {
                        array.insert( array.begin(), crt );
                    }
                }
                if ( 0 == col_width ) {
                    col_width++;
                } else {
                    col_width /= element_count;
                }
                variant::sparse_array_type sparse_array( array );
                cx.stack().push( interpreter_variant( variant( sparse_array, col_width ) ) );
            }
            break;

            case token::boolean_false:
                cx.stack().push( interpreter_variant( false ) );
                break;

            case token::boolean_true:
                cx.stack().push( interpreter_variant( true ) );
                break;

            case token::brace: {
                std::size_t element_count;
                token_stream >> element_count;
            }
            break;

            case token::concatination: {
                const interpreter_variant rhs( cx.stack().pop() );
                const interpreter_variant lhs( cx.stack().pop() );
                if ( rhs.is_error() ) {
                    cx.stack().push( rhs );
                } else if ( lhs.is_error() ) {
                    cx.stack().push( lhs );
                } else {
                    cx.stack().push( interpreter_variant( lhs.as_string( cx.locale() ).append( rhs.as_string( cx.locale() ) ) ) );
                }
            }
            break;

            case token::digit: {
                double digit;
                token_stream >> digit;
                cx.stack().push( interpreter_variant( digit ) );
            }
            break;

            case token::division: {
                const interpreter_variant rhs( cx.stack().pop() );
                const interpreter_variant lhs( cx.stack().pop() );
                if ( ( rhs.is_numeric() && rhs == 0.0 ) ) {
                    cx.stack().push( interpreter_variant( variant::error_div_null ) );
                } else if ( ( rhs.is_string() && rhs.string().empty() )   ) {
                    cx.stack().push( interpreter_variant( variant::error_value ) );
                } else {
                    cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::div >( lhs, rhs ) );
                }
            }
            break;

            case token::empty:
                cx.stack().push( interpreter_variant( variant::type_empty ) );
                break;

            case token::equal:
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::eq>( cx.stack().pop(), cx.stack().pop() ) );
                break;

            case token::error: {
                variant::error_type e;
                token_stream >> e;
                cx.stack().push( interpreter_variant( e ) );
            }
            break;

            case token::exponent: {
                const interpreter_variant rhs( cx.stack().pop() );
                const interpreter_variant lhs( cx.stack().pop() );
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::exp >( lhs, rhs ) );
            }
            break;

            case token::function: {

                std::size_t function_name_index;
                function_entry* entry;
                std::size_t element_count;
                std::size_t jumptable_position;
                token_stream >> function_name_index >> entry >> element_count >> jumptable_position;
                function_parameter::subtree_vector_auto_type subtree;
                if ( jumptable_position ) {
                    const std::size_t jumptable_offset = token_stream.tellg();
                    jumptable_position += jumptable_offset;
                    token_stream.seekg( static_cast<int>( jumptable_position ), vector_io_device::seek_beginning );
                    std::vector<std::size_t> jumptable;
                    std::size_t tmp;
                    for ( unsigned int i = 0; i < element_count; ++i ) {
                        token_stream >> tmp;
                        jumptable.push_back( tmp + jumptable_offset );
                    }
                    jumptable.push_back( jumptable_position );
                    const std::size_t current_position = token_stream.tellg();

                    std::size_t subtree_size;
                    subtree.reset( new function_parameter::subtree_vector_type() );
                    subtree->reserve( jumptable.size() - 1 );
                    for ( std::vector<std::size_t>::const_iterator it = jumptable.begin(), end = ( jumptable.end() - 1 ); it != end; ++it ) {
                        function_parameter::positioned_op_codes_auto_type new_op( new positioned_op_codes( op.original_opcode ) );
                        subtree->push_back( new_op );
                        positioned_op_codes& tmp = **subtree->rbegin();
                        subtree_size = ( *( it + 1 ) ) - ( *it );
                        tmp.original_opcode.code.resize( subtree_size );
                        tmp.location_dependent_opcodes = op.location_dependent_opcodes;
                        token_stream.seekg( *it, vector_io_device::seek_beginning );
                        token_stream.read( &tmp.original_opcode.code[0], subtree_size );
                    }
                    token_stream.seekg( static_cast<int>( current_position ), vector_io_device::seek_beginning );
                }

                // if entry is null, try to rebind
                if ( NULL == entry && opcode_stream_helper::is_valid_pos( function_name_index ) ) {
                    try {
                        entry = &function_registry::instance().function_entry( op.original_opcode.stringtable[ function_name_index ] );
                    } catch ( const invalid_function_exception& ) {}
                }

                if ( NULL == entry ) {
                    // empty params from stack
                    for ( unsigned int i = 0; i < element_count; ++i && !cx.stack().empty() ) {
                        cx.stack().pop();
                    }
                    cx.stack().push( interpreter_variant( variant( variant::error_name ) ) );
                    if ( opcode_stream_helper::is_valid_pos( function_name_index ) ) {
                        cx.context().session().broken_dependencies().register_name_function( op.original_opcode.stringtable[ function_name_index ], cx.caller() );
                    }
                    break;
                }
                if ( jumptable_position ) {
                    element_count = 0;
                }
                //VERY IMPORTANT: subtree is a std::auto_ptr, don't use it here after passing it to function_parameter!!
                function_parameter parameters( cx, static_cast<unsigned int>( element_count ), subtree );

                //TODO (RIA): pack this once we are happy with it
                static const std::string    elem_name_func( "PALO.ENAME" );
                if ( elem_name_func == entry->internal_name() ) {
                    if ( i_dependency::cell_type == cx.caller()->type() ) {
                        range   node = cx.caller()->worksheet().lock()->range( sheet_range( cx.caller()->position() ) );
                        utf8_ci_string str( "\"elaborate_later\"" );
                        variant value_result = node.attribute( str );
                        variant::variant_array_type& array = value_result.array();
                        if ( !array.empty() && !( ( variant ) array[0] ).is_empty()  ) {


                            //1. param of 1 is in the form connection/database. split
                            std::string location = parameters[0].string();
                            std::string connection;
                            std::string database;
                            size_t div_pos = location.find( '/' );
                            if ( std::string::npos != div_pos ) {
                                connection = location.substr( 0, div_pos );
                                database = location.substr( div_pos + 1, location.size() );
                            }

                            attribute_set_type attrs;
                            node.clear_attributes();

                            if ( parameters.count() >= 4 ) {
                                if ( 1 == parameters[3].numeric() ) {
                                    attrs.add( std::string( "\"dblclick\"" ) ,
                                               std::string( "[\"hnd_dblCceOpen\",{\"working_mode\":1,\"serv_id\":\"" + connection +
                                                            "\",\"db_name\":\"" + database +
                                                            "\",\"dim_name\":\"" + parameters[1].string() +
                                                            "\",\"edit_data\":[[\"" + parameters[2].string() + "\",null,\"C\"]],\"pasteview_id\":\"pv_abcdefabcdefa\",\"edit_y\":2}]" ) );
                                    attrs.add( std::string( "\"palo_pe\"" ), std::string( "{\"type\":\"dim\",\"name\":\"" + parameters[1].string() + "\"}" ) );

                                    node.attribute( cx.context().session(), attrs );
                                } else if ( 3 == parameters[3].numeric() ) {

                                    attrs.add( std::string( "\"dblclick\"" ) ,
                                               std::string( "[\"hnd_dblCpv\"," + boost::lexical_cast<std::string>( cx.caller()->position().column() ) + "," + boost::lexical_cast<std::string>( cx.caller()->position().row() ) + ",\"pv_abcdefabcdefa\",\"" +
                                                            parameters[1].string() + "\",\""  + parameters[2].string() +  "\"]" ) );
                                    attrs.add( std::string( "\"palo_pe\"" ), std::string( "{\"type\":\"dim\",\"name\":\"" + parameters[1].string() + "\"}" ) );

                                    node.attribute( cx.context().session(), attrs );
                                }
                            }
                        }
                    }
                }

                cx.last_return_type( entry->return_type() );
                if ( entry->is_lazy() ) {
                    cx.raise_inside_function_count();
                    cx.stack().push( ( *entry )( parameters ) );
                    cx.lower_inside_function_count();
                } else {
                    cx.stack().push( ( *entry )( parameters ) );
                }

            }
            break;

            case token::greater_equal: {
                const interpreter_variant rhs( cx.stack().pop() );
                const interpreter_variant lhs( cx.stack().pop() );
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::gte>( lhs, rhs ) );
            }
            break;

            case token::greater: {
                const interpreter_variant rhs( cx.stack().pop() );
                const interpreter_variant lhs( cx.stack().pop() );
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::gt >( lhs, rhs ) );
            }
            break;

            case token::less_equal: {
                const interpreter_variant rhs( cx.stack().pop() );
                const interpreter_variant lhs( cx.stack().pop() );
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::le>( lhs, rhs ) );
            }
            break;

            case token::less: {
                const interpreter_variant rhs( cx.stack().pop() );
                const interpreter_variant lhs( cx.stack().pop() );
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::lt >( lhs, rhs ) );
            }
            break;

            case token::multiplication:
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::mul >( cx.stack().pop(), cx.stack().pop() ) );
                break;

            case token::named_formula: {
                std::size_t index;
                std::size_t workbook_index;
                std::size_t worksheet_index;
                std::size_t name_string_index;
                token_stream >> index >> name_string_index >> workbook_index >> worksheet_index;

                if ( opcode_stream_helper::is_valid_pos( index ) ) {
                    if (  shared_reference_type sr = references[ index ] ) {
                        const named_formula_reference& ref = named_formula_reference_cast( sr );
                        if ( ref.is_valid() ) {
                            if ( shared_named_formula_wrapper_type nf_wrapper = ref.internal_access() ) {
                                if ( shared_named_formula_type nf = nf_wrapper->named_formula() ) {
                                    if ( called_from_inside_nf ) {
                                        bool test = true;
                                        try {
                                            test = nf != cx.named_formula_initiator();
                                        } catch ( std::logic_error& ) {
                                        }
                                        if ( test ) {
                                            cx.stack().push( interpreter_variant( opcode_interpreterT<true>::calculate( nf->get_opcode(), cx ) ) );
                                            break;
                                        }
                                    } else {
                                        if ( nf != cx.caller() ) {
                                            const interpreter_variant tmp = interpreter_variant( opcode_interpreterT<true>::calculate( nf->get_opcode(), cx ) ) ;
                                            if ( tmp.is_error() && tmp.error_code() == variant::error_ref ) {
                                                //in this case try a lookup
                                                cx.stack().push( tmp );
                                            } else {
                                                cx.stack().push( tmp );
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                cx.stack().push( interpreter_variant( variant( variant::error_name ) ) );
            }
            break;

            case token::negation:
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::mul >( cx.stack().pop(), - 1.0 ) );
                break;

            case token::not_equal:
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::neq >( cx.stack().pop(), cx.stack().pop() ) );
                break;

            case token::percentage:
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::div >( cx.stack().pop(), percent ) );
                break;

            case token::range: {
                std::size_t index;
                ptrdiff_t position_string_index;
                std::size_t workbook_index;
                std::size_t worksheet_index;
                token_stream >> index >> position_string_index;

                if ( opcode_stream_helper::is_valid_pos( index ) ) {
                    shared_reference_type sr( references[ index ] );
                    if ( sr ) {
                        range_reference::actual actual_reference( range_reference_cast( sr ).actualize() );
                        if ( actual_reference.is_valid() ) {
                            const sheet_range area = actual_reference.position();

                            if ( area.count() == 1 ) {
                                locked_dependency_set_type::access dep_access( *actual_reference.operator ->() );
                                if ( ( *dep_access ).begin() != ( *dep_access ).end() ) {
                                    cx.stack().push( interpreter_variant( ( *( *dep_access ).begin() )->value( cx ), sr ) );
                                } else {
                                    cx.stack().push( interpreter_variant( variant(), sr ) );
                                }
                            } else {
                                variant retval( variant::type_array );
                                retval.column_width( area.column_count() );
                                variant::sparse_array_type& array = retval.array();
                                array.resize( area.count() );
                                const dependency_set_type& sd = *actual_reference->lock();
                                for ( dependency_set_type::const_iterator it = sd.begin(), end_it = sd.end(); it != end_it; ++it ) {
                                    //foreach( const shared_dependency_type & sd, *actual_reference->lock() ) {
                                    sheet_point new_offset( ( *it )->position() - area.upper_left() );
                                    array.set( ( new_offset.row() * area.column_count() ) + new_offset.column(), ( *it )->value( cx ) );
                                }
                                cx.stack().push( interpreter_variant( retval, sr ) );
                            }
                            break;
                        }
                    }
                } else {
                    token_stream >> workbook_index >> worksheet_index;
                }
                cx.stack().push( interpreter_variant( variant( variant::error_ref ) ) );
            }
            break;

            case token::subtraction: {
                const interpreter_variant rhs( cx.stack().pop() );
                const interpreter_variant lhs( cx.stack().pop() );
                cx.stack().push( opcode_interpreter_helper::call_function< variant( variant::* )( const variant& ) const, &variant::sub >( lhs, rhs ) );

            }
            break;

            case token::string: {
                std::size_t index;
                token_stream >> index;
                cx.stack().push( interpreter_variant( op.original_opcode.stringtable[ index ].get() ) );
            }
            break;

            case token::variable: {
                std::size_t index;
                token_stream >> index;
                cx.stack().push( interpreter_variant( cx.context().session().variable().variable( op.original_opcode.stringtable[ index ] ) ) );
            }
            break;

            case token::reference_list: {
                std::size_t element_count;
                token_stream >> element_count;
                std::string parameters;
                variant::variant_array_type a;
                for ( int children = ( element_count - 1 ); children > -1; --children ) {
                    a.set( children, cx.stack().pop() );
                }
                cx.stack().push( interpreter_variant( variant( a, static_cast<unsigned int>( element_count ) ) ) );
            }
            break;

            default:
                assert( ! "invalid token stream!" );
        }
    }

#ifdef _DEBUG
    assert( "after calculation the stack size has to be bigger than before" && cx.stack().size() >= 1 + stack_size );
#endif // _DEBUG
    if ( cx.is_inside_function() || cx.is_inside_named_formula()  ) {
        return cx.stack().pop();
    }

    if ( cx.caller()->is_array() ) {
        const variant& return_value = cx.stack().peek();
        if ( return_value.is_array() ) {
            const variant::variant_array_type::mapping_type& return_array = return_value.array().direct();
            if ( return_value.array().size() != return_array.size() && return_value.array().default_value().is_empty() ) {
                const variant real_return_value = cx.stack().pop();
                return variant( variant::variant_array_type( real_return_value.array().direct(), real_return_value.array().size(), variant( 0.0 ) ), real_return_value.column_width() );
            }
        }
    }
    if ( cx.stack().peek().is_empty() ) {
        cx.stack().pop();
        return variant( 0.0 );
    }
    return cx.stack().pop();
}

template class opcode_interpreterT<false>;
template class opcode_interpreterT<true>;
