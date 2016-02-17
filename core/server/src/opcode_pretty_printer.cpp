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
*  Florian Schaper <florian.schaper@jedox.com>
*/

#include "precompiled_header.hpp"
#include "wss/opcode_pretty_printer.hpp"
#include "wss/opcode_pretty_printer_context.hpp"
#include "wss/vector_io_device.hpp"
#include "wss/a1conversion.hpp"
#include "wss/i_dependency.hpp"
#include "wss/binary_istream.hpp"
#include "wss/token_stream_specialization.hpp"
#include "wss/translation_table.hpp"
#include "wss/function_entry.hpp"
#include "wss/range_reference.hpp"
#include "wss/named_formula_reference.hpp"
#include "wss/worksheet.hpp"
#include "wss/workbook.hpp"
#include "wss/opcode.hpp"
#include "wss/token.hpp"
#include "wss/stack.hpp"

#include "opcode_stream_helper.hpp"
#include "wss/double_to_string.hpp"

struct opcode_pretty_printer_helper : non_instantiable {

    static inline std::string get_error_string( const variant::error_type e, const opcode_pretty_printer_context& cx ) {
        return to_upper_copy_utf8( cx.active_translation().error_translation().get<translation_map::error_mapping::code_tag>().find( e )->second );
    }

    template<class contained_T>
    static inline utf8_ci_string name_lookup( const bool return_ref_if_not_found, const typename boost::weak_ptr<contained_T>& w_ptr, const opcode_pretty_printer_context& cx, bool& got_a_ref_error ) {
        if ( typename boost::shared_ptr<contained_T> s_ptr = w_ptr.lock() ) {
            return s_ptr->name();
        }
        if ( return_ref_if_not_found ) {
            got_a_ref_error = true;
            convert_utf8_ci( get_error_string( variant::error_ref, cx ) );
        }
        return utf8_ci_string();
    }

    static inline std::string invalid_reference_string( const reference_info& ref_info, const opcode_pretty_printer_context& cx ) {
        return invalid_reference_string( ref_info, cx, get_error_string( variant::error_ref, cx ) );
    }

    static inline std::string invalid_reference_string( const reference_info& ref_info, const opcode_pretty_printer_context& cx, const std::string& ref_error_string ) {
        //this isn't exactly like other spreadsheet applications do it
        std::stringstream a1_notation;
        if ( ! handle_worksheet_and_workbook( a1_notation, ref_info, cx ) ) {
            a1_notation << ref_error_string;
            return a1_notation.str();
        }
        return ref_error_string;
    }

private:
    static inline bool handle_worksheet_and_workbook( std::stringstream& a1_notation, const reference_info& ref_info,  const opcode_pretty_printer_context& cx ) {
        bool got_a_ref_error = false;
        const utf8_ci_string worksheet_name = name_lookup( ref_info.worksheet_given(), ref_info.worksheet(), cx, got_a_ref_error );
        if ( !worksheet_name.empty() ) {
            bool needs_quotes = a1conversion::to_a1::needs_quotes( worksheet_name );
            const utf8_ci_string workbook_name = name_lookup( ref_info.workbook_given(), ref_info.workbook(), cx, got_a_ref_error );
            if ( !workbook_name.empty() ) {
                needs_quotes = needs_quotes || a1conversion::to_a1::needs_quotes( workbook_name );
                if ( needs_quotes ) {
                    a1_notation << "'";
                }
                a1_notation << "[" << workbook_name << "]";
            } else if ( needs_quotes ) {
                a1_notation << "'";
            }
            a1_notation << worksheet_name;
            if ( needs_quotes ) {
                a1_notation << "'";
            }
            a1_notation  << "!";
        }
        return got_a_ref_error;
    }
};

/*!
 * \brief
 * opcode pretty printer.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
std::string opcode_pretty_printer::create( opcode_pretty_printer_context& cx )
{
    binary_istream<vector_io_device> token_stream;
    typedef stack<std::string> formula_stack_type;
    formula_stack_type f_stack;

    token_stream.open( const_cast<opcode::sequence_type*>( &cx.code().original_opcode.code ) );
    token::type current_token;
    referencetable_type& references = cx.initiator_given()
                                      ? const_cast<positioned_op_codes*>( &cx.code() )->positional_references( cx.initiator() ).reference
                                      : const_cast<positioned_op_codes*>( &cx.code() )->original_opcode.location_dependent_reference.reference;

    double_to_string double_converter;
    while ( ! token_stream.eof() ) {
        token_stream >> current_token;
        switch ( current_token ) {

            case token::addition:
                f_stack.push( f_stack.pop().append( "+" ).append( f_stack.pop() ) );
                break;

            case token::array_row: {
                std::size_t element_count;
                token_stream >> element_count;

                std::stringstream sstream;
                if ( element_count ) {
                    std::string parameters;
                    for ( std::size_t children = ( element_count - 1 ); children > 0; --children ) {
                        parameters = std::string( cx.active_translation().column_separator() ).append( f_stack.pop() ).append( parameters );
                    }
                    sstream << f_stack.pop() << parameters;
                }

                f_stack.push( sstream.str() );
            }
            break;

            case token::array: {
                std::size_t element_count;
                token_stream >> element_count;

                std::stringstream sstream;
                sstream << "{";
                if ( element_count ) {
                    std::string parameters;
                    for ( std::size_t children = ( element_count - 1 ); children > 0; --children ) {
                        parameters = std::string( cx.active_translation().row_separator() ).append( f_stack.pop() ).append( parameters );
                    }
                    sstream << f_stack.pop() << parameters;
                }
                sstream << "}";

                f_stack.push( sstream.str() );
            }
            break;

            case token::boolean_false:
                f_stack.push( cx.active_translation().boolean_false() );
                break;

            case token::boolean_true:
                f_stack.push( cx.active_translation().boolean_true() );
                break;

            case token::brace: {
                std::size_t element_count;
                token_stream >> element_count;
                std::stringstream sstream;
                sstream << "(";
                for ( std::size_t children = element_count; children > 0; --children ) {
                    sstream << f_stack.pop();
                }
                sstream << ")";
                f_stack.push( sstream.str() );
            }
            break;

            case token::concatination:
                f_stack.push( f_stack.pop().append( "&" ).append( f_stack.pop() ) );
                break;

            case token::digit: {
                double digit;
                token_stream >> digit;
                if ( cx.active_translation().use_dot_as_real_separator() ) {
                    f_stack.push( double_converter( digit ) );
                } else {
                    f_stack.push( boost::replace_all_copy( double_converter( digit ), ".", "," ) );
                }
            }
            break;

            case token::division:
                f_stack.push( f_stack.pop().append( "/" ).append( f_stack.pop() ) );
                break;

            case token::empty:
                f_stack.push( "" );
                break;

            case token::equal:
                f_stack.push( f_stack.pop().append( "=" ).append( f_stack.pop() ) );
                break;

            case token::error: {
                variant::error_type e;
                token_stream >> e;
                f_stack.push( opcode_pretty_printer_helper::get_error_string( e, cx ) );
            }
            break;

            case token::exponent:
                f_stack.push( f_stack.pop().append( "^" ).append( f_stack.pop() ) );
                break;

            case token::function: {
                ptrdiff_t function_name_index;
                function_entry* entry;
                std::size_t element_count;
                std::size_t jumptable_position;

                token_stream >> function_name_index >> entry >> element_count >> jumptable_position;

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
                    for ( std::vector<std::size_t>::const_iterator it = jumptable.begin(), end = ( jumptable.end() - 1 ); it != end; ++it ) {
                        positioned_op_codes tmp( cx.code().original_opcode );
                        //TODO check if we need the next line
                        tmp.location_dependent_opcodes = cx.code().location_dependent_opcodes;
                        subtree_size = ( *( it + 1 ) ) - ( *it );
                        tmp.original_opcode.code.resize( subtree_size );
                        token_stream.seekg( *it, vector_io_device::seek_beginning );
                        token_stream.read( &tmp.original_opcode.code[0], subtree_size );
                        if ( cx.initiator_given() ) {
                            opcode_pretty_printer_context ctx( tmp, cx.current(), cx.active_translation().locale(), cx.initiator(), cx.resolve_named_formulas(), cx.always_add_sheet_references() );
                            f_stack.push( opcode_pretty_printer::create( ctx ).substr( 1 ) );
                        } else {
                            opcode_pretty_printer_context ctx( tmp, cx.current(), cx.active_translation().locale(), cx.resolve_named_formulas() );
                            f_stack.push( opcode_pretty_printer::create( ctx ).substr( 1 ) );
                        }
                    }
                    token_stream.seekg( static_cast<int>( current_position ), vector_io_device::seek_beginning );
                }

                std::stringstream sstream;

                if ( opcode_stream_helper::is_valid_pos( function_name_index ) ) {
                    sstream << cx.code().original_opcode.stringtable[ function_name_index ];
                } else {
                    try {
                        sstream << cx.active_translation().external_name_lookup[ entry->internal_name() ]->translation;
                    } catch ( const translation_exception& ) {
                        sstream << entry->internal_name();
                    }
                }

                sstream << "(";
                if ( element_count ) {
                    std::string parameters;
                    for ( std::size_t children = ( element_count - 1 ); children > 0; --children ) {
                        parameters = std::string( cx.active_translation().parameter_separator() ).append( f_stack.pop() ).append( parameters );
                    }
                    sstream << f_stack.pop() << parameters;
                }
                sstream << ")";

                f_stack.push( sstream.str() );
            }
            break;

            case token::greater_equal:
                f_stack.push( f_stack.pop().append( ">=" ).append( f_stack.pop() ) );
                break;

            case token::greater:
                f_stack.push( f_stack.pop().append( ">" ).append( f_stack.pop() ) );
                break;

            case token::less_equal:
                f_stack.push( f_stack.pop().append( "<=" ).append( f_stack.pop() ) );
                break;

            case token::less:
                f_stack.push( f_stack.pop().append( "<" ).append( f_stack.pop() ) );
                break;

            case token::multiplication:
                f_stack.push( f_stack.pop().append( "*" ).append( f_stack.pop() ) );
                break;

            case token::named_formula: {
                std::size_t index;
                std::size_t workbook_index;
                std::size_t worksheet_index;
                std::size_t name_string_index;

                token_stream >> index >> name_string_index >> workbook_index >> worksheet_index;

                std::stringstream a1_notation;
                if ( opcode_stream_helper::is_valid_pos( index ) ) {
                    const reference_info ref_info = references[ index ];
                    const shared_reference_type& ref = ref_info;
                    // test if the reference is valid.
                    if ( ref.get() != NULL ) {
                        named_formula_reference& nfr = named_formula_reference_cast( ref );
                        if ( nfr.is_valid() ) {
                            shared_worksheet_type referenced_worksheet = nfr.nf_worksheet().lock();
                            if ( !referenced_worksheet && nfr.nf_is_workbook_scope() ) {
                                referenced_worksheet = cx.current()->worksheet().lock();
                            }
                            if ( ! referenced_worksheet ) {
                                f_stack.push( opcode_pretty_printer_helper::get_error_string( variant::error_name, cx ) );
                                continue;
                            }

                            shared_worksheet_type current_worksheet( cx.current()->worksheet().lock() );
                            std::stringstream a1_notation;
                            if ( ref_info.worksheet_given() || opcode_stream_helper::is_valid_pos( worksheet_index ) ) {
                                const utf8_ci_string worksheet_name = referenced_worksheet->name();
                                bool needs_quotes = a1conversion::to_a1::needs_quotes( worksheet_name );
                                if ( ref_info.workbook_given() ) {
                                    utf8_ci_string workbook_name = referenced_worksheet->parent()->name();
                                    needs_quotes = needs_quotes || a1conversion::to_a1::needs_quotes( workbook_name );
                                    if ( needs_quotes ) {
                                        a1_notation << "'";
                                    }
                                    a1_notation << "[" << workbook_name << "]";
                                }
                                a1_notation << worksheet_name << "!";
                                if ( needs_quotes ) {
                                    a1_notation << "'";
                                }
                            }

                            a1_notation << convert_utf8_ci( nfr.name() );
                            f_stack.push( a1_notation.str() );
                        } else {

                            if ( opcode_stream_helper::is_valid_pos( workbook_index ) ) {
                                utf8_ci_string workbook_name = convert_utf8_ci( cx.code().original_opcode.stringtable[ workbook_index ] );
                                const utf8_ci_string worksheet_name = convert_utf8_ci( cx.code().original_opcode.stringtable[ worksheet_index ] );
                                const bool needs_quotes = a1conversion::to_a1::needs_quotes( workbook_name ) || a1conversion::to_a1::needs_quotes( worksheet_name );
                                if ( needs_quotes ) {
                                    a1_notation << "'";
                                }
                                a1_notation << "[" << workbook_name << "]" << worksheet_name;
                                if ( needs_quotes ) {
                                    a1_notation << "'";
                                }
                                a1_notation << "!";
                            } else if ( opcode_stream_helper::is_valid_pos( worksheet_index ) ) {
                                const utf8_ci_string worksheet_name = convert_utf8_ci( cx.code().original_opcode.stringtable[ worksheet_index ] );
                                const bool needs_quotes = a1conversion::to_a1::needs_quotes( worksheet_name );
                                if ( needs_quotes ) {
                                    a1_notation << "'";
                                }
                                a1_notation << worksheet_name;
                                if ( needs_quotes ) {
                                    a1_notation << "'";
                                }
                                a1_notation << "!";
                            }
                            a1_notation << convert_utf8_ci( nfr.name() );
                            f_stack.push( a1_notation.str() );
                        }
                        continue;
                    }
                }

                if ( opcode_stream_helper::is_valid_pos( workbook_index ) ) {
                    const utf8_ci_string workbook_name = convert_utf8_ci( cx.code().original_opcode.stringtable[ workbook_index ] );
                    if ( opcode_stream_helper::is_valid_pos( worksheet_index ) ) {
                        const utf8_ci_string worksheet_name = convert_utf8_ci( cx.code().original_opcode.stringtable[ worksheet_index ] );
                        const bool needs_quotes = a1conversion::to_a1::needs_quotes( workbook_name ) || a1conversion::to_a1::needs_quotes( worksheet_name );
                        if ( needs_quotes ) {
                            a1_notation << "'";
                        }
                        a1_notation << "[" << workbook_name << "]" << worksheet_name;
                        if ( needs_quotes ) {
                            a1_notation << "'";
                        }
                    } else {
                        const utf8_ci_string workbook_name = convert_utf8_ci( cx.code().original_opcode.stringtable[ workbook_index ] );
                        const bool needs_quotes = a1conversion::to_a1::needs_quotes( workbook_name );
                        if ( needs_quotes ) {
                            a1_notation << "'";
                        }
                        a1_notation << workbook_index;
                        if ( needs_quotes ) {
                            a1_notation << "'";
                        }
                    }
                    a1_notation << "!";
                } else if ( opcode_stream_helper::is_valid_pos( worksheet_index ) ) {
                    const utf8_ci_string worksheet_name = convert_utf8_ci( cx.code().original_opcode.stringtable[ worksheet_index ] );
                    const bool needs_quotes = a1conversion::to_a1::needs_quotes( worksheet_name );
                    if ( needs_quotes ) {
                        a1_notation << "'";
                    }
                    a1_notation << worksheet_name;
                    if ( needs_quotes ) {
                        a1_notation << "'";
                    }
                    a1_notation << "!";
                }
                a1_notation << cx.code().original_opcode.stringtable[ name_string_index ];
                f_stack.push( a1_notation.str() );
            }
            break;

            case token::negation:
                f_stack.push( std::string( "-" ).append( f_stack.pop() ) );
                break;

            case token::not_equal:
                f_stack.push( f_stack.pop().append( "<>" ).append( f_stack.pop() ) );
                break;

            case token::percentage:
                f_stack.push( f_stack.pop().append( "%" ) );
                break;

            case token::range: {
                std::size_t index;
                token_stream >> index /*>> workbook_index >> worksheet_index*/;
                std::size_t position_string_index;
                token_stream >> position_string_index;

                if ( opcode_stream_helper::is_valid_pos( index ) ) {
                    const reference_info& ref_info = references[ index ];
                    if ( ! ref_info.is_valid() ) {
                        f_stack.push( opcode_pretty_printer_helper::invalid_reference_string( ref_info, cx ) );
                        continue;
                    }
                    const shared_reference_type& ref = ref_info;
                    range_reference::actual actual_reference = range_reference_cast( ref ).actualize();
                    // test if the reference is valid.

                    if ( actual_reference.is_valid() ) {

                        shared_worksheet_type referenced_worksheet( actual_reference.worksheet() );
                        if ( ! referenced_worksheet ) {
                            f_stack.push( opcode_pretty_printer_helper::get_error_string( variant::error_ref, cx ).append( "!" ).append( a1conversion::to_a1::from_range( actual_reference.position() ) ) );
                            continue;
                        }

                        shared_worksheet_type current_worksheet( cx.current()->worksheet().lock() );
                        std::stringstream a1_notation;
                        if ( ref_info.worksheet_given() || !current_worksheet || referenced_worksheet != current_worksheet || ( cx.always_add_sheet_references() && cx.current()->type() == i_dependency::named_formula_type )  ) {
                            const utf8_ci_string worksheet_name = referenced_worksheet->name();
                            bool needs_quotes = a1conversion::to_a1::needs_quotes( worksheet_name );
                            if ( ref_info.workbook_given() || !current_worksheet || referenced_worksheet->parent() != current_worksheet->parent() ) {
                                utf8_ci_string workbook_name = referenced_worksheet->parent()->name();
                                needs_quotes = needs_quotes || a1conversion::to_a1::needs_quotes( workbook_name );
                                if ( needs_quotes ) {
                                    a1_notation << "'";
                                }
                                a1_notation << "[" << workbook_name << "]";
                            } else if ( needs_quotes ) {
                                a1_notation << "'";
                            }
                            a1_notation << worksheet_name;
                            if ( needs_quotes ) {
                                a1_notation << "'";
                            }
                            a1_notation  << "!";
                        }

                        if ( ref_info.is_single_cell() ) {
                            a1_notation << a1conversion::to_a1::from_point( actual_reference.position().upper_left() );
                        } else {
                            a1_notation << a1conversion::to_a1::from_range( actual_reference.position() );
                        }
                        f_stack.push( a1_notation.str() );
                        continue;
                    } else {
                        f_stack.push( opcode_pretty_printer_helper::invalid_reference_string( ref_info, cx ) );
                        continue;
                    }


                } else {
                    std::size_t worksheet_index;
                    std::size_t workbook_index;
                    token_stream >> workbook_index >> worksheet_index;
                    std::stringstream a1_notation;
                    if ( opcode_stream_helper::is_valid_pos( worksheet_index ) ) {
                        const utf8_ci_string worksheet_name =  convert_utf8_ci( cx.code().original_opcode.stringtable[worksheet_index] );
                        bool needs_quotes = a1conversion::to_a1::needs_quotes( worksheet_name );
                        if ( opcode_stream_helper::is_valid_pos( workbook_index ) ) {
                            const utf8_ci_string workbook_name = convert_utf8_ci( cx.code().original_opcode.stringtable[workbook_index] );
                            needs_quotes = needs_quotes || a1conversion::to_a1::needs_quotes( workbook_name );
                            if ( needs_quotes ) {
                                a1_notation << "'";
                            }
                            a1_notation << "[" << workbook_name << "]";
                        } else if ( needs_quotes ) {
                            a1_notation << "'";
                        }
                        a1_notation << worksheet_name;
                        if ( needs_quotes ) {
                            a1_notation << "'";
                        }
                        a1_notation  << "!";
                    }
                    if ( opcode_stream_helper::is_valid_pos( position_string_index ) ) {
                        a1_notation << cx.code().original_opcode.stringtable[position_string_index];
                    } else {
                        a1_notation << opcode_pretty_printer_helper::get_error_string( variant::error_ref, cx );
                    }
                    f_stack.push( a1_notation.str() );
                    continue;
                }
            }
            break;

            case token::subtraction:
                f_stack.push( f_stack.pop().append( "-" ).append( f_stack.pop() ) );
                break;

            case token::string: {
                std::size_t index;
                token_stream >> index;
                f_stack.push( std::string( "\"" ).append( boost::replace_all_copy( cx.code().original_opcode.stringtable[ index ].get(), "\"", "\"\"" ) ).append( "\"" ) );
            }
            break;

            case token::variable: {
                std::size_t index;
                token_stream >> index;
                f_stack.push( std::string( "@" ).append( cx.code().original_opcode.stringtable[ index ] ) );
            }
            break;

            case token::reference_list: {
                std::size_t element_count;
                token_stream >> element_count;
                std::string parameters;
                for ( std::size_t children = ( element_count - 1 ); children > 0; --children ) {
                    parameters = std::string( cx.active_translation().parameter_separator() ).append( f_stack.pop() ).append( parameters );
                }
                f_stack.push( f_stack.pop().append( parameters ) );
            }
            break;

            case token::dec_fct_count:
            case token::inc_fct_count:
                break;

            default:
                assert( ! "invalid token stream!" );
        }
    }

    return std::string( "=" ).append( f_stack.pop() );
}
