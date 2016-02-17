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
 *  <a href=<wss/http://www.jedox.com/license_palo_bi_suite.txt>>
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
#include "wss/opcode_generator.hpp"

#include "wss/token_stream_specialization.hpp"
#include "named_formula_manager.hpp"
#include "wss/vector_io_device.hpp"
#include "wss/precedent_proxy.hpp"
#include "wss/binary_iostream.hpp"
#include "wss/a1conversion.hpp"
#include "wss/tree_visitor.hpp"
#include "wss/i_visitor.hpp"
#include "wss/workbook.hpp"
#include "wss/syntax.hpp"
#include "wss/opcode.hpp"
#include "wss/token.hpp"

#include "cell_manager.hpp"
#include "opcode_stream_helper.hpp"

/*!
 * \brief
 * opcode generator.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class opcode_generator::translator
    : public i_visitor
    , bottom_top_visitor<translator, base_node, true>
{
    friend class bottom_top_visitor<translator, base_node, true>;
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    translator( const shared_dependency_type& initiator, const base_node& ast, positioned_op_codes& ops, const referencetable_type& references )
        : m_stream()
        , m_opcode( ops )
        , m_initiator( initiator )
        , m_precedent_proxy( initiator, references ) {
        m_stream.open( &ops.original_opcode.code );
        // (fschaper) since we don't modify the AST anymore we will switch to const nodes. in the meantime
        // we will have to do with the outer interface already reflecting this change and have to live
        // with the const cast to base_node&.
        bottom_top_visitor<translator, base_node, true>::operator ()( const_cast<base_node&>( ast ) );
    }

    /*!
     * \brief
     * nothing to do here.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( root_node& ) {}

    /*!
     * \brief
     * set the addition token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( addition_node& ) {
        m_stream << token::addition;
    }

    /*!
     * \brief
     * set the subtraction token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( subtraction_node& ) {
        m_stream << token::subtraction;
    }

    /*!
     * \brief
     * set the multiplication token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( multiplication_node& ) {
        m_stream << token::multiplication;
    }

    /*!
     * \brief
     * set the division token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( division_node& ) {
        m_stream << token::division;
    }

    /*!
     * \brief
     * set the function imbrication token
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    virtual void visit( function_call_up_node& ) {
        m_stream << token::inc_fct_count;
    }

    /*!
     * \brief
     * set the function imbrication token
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    virtual void visit( function_call_down_node& ) {
        m_stream << token::dec_fct_count;
    }

    /*!
     * \brief
     * set the negation token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( negation_node& ) {
        m_stream << token::negation;
    }

    /*!
     * \brief
     * pass the digit token and the number to the stream
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( digit_node& n ) {
        m_stream << token::digit << n.get();
    }

    /*!
     * \brief
     * pass a range reference
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( range_node& n ) {
        shared_reference_type sr;
        shared_worksheet_type ws( n.worksheet().lock() );
        if ( ws && !n.is_ref_error() ) {
            sr = m_precedent_proxy.register_dependency( ws->cells(), n.range(), false );
        }
        m_stream << token::range;
        const bool worksheet_given = n.has_worksheet();
        const bool workbook_given = n.has_workbook();
        bool no_valid_reference_info = false;
        if ( sr || ( ws && ( worksheet_given || workbook_given ) ) ) {
            m_stream << ( m_opcode.original_opcode.location_dependent_reference.reference.set( reference_info(
                              sr,
                              ! worksheet_given,
                              n.is_single_cell(),
                              worksheet_given,
                              workbook_given,
                              worksheet_given ? ws : shared_worksheet_type(),
                              ( workbook_given && ws ) ? ws->parent() : shared_workbook_type()
                          ) ) );
        } else {
            m_stream << opcode_stream_helper::no_pos();
            no_valid_reference_info = true;
        }

        if ( sr && reference_type( n.range() ) != reference::absolute ) {
            m_opcode.is_relative = true;
        }

        if ( n.is_ref_error() ) {
            m_stream << opcode_stream_helper::no_pos();
        } else {
            if ( n.is_single_cell() ) {
                m_stream << m_opcode.original_opcode.stringtable.set( opcode::opcode_string_type( a1conversion::to_a1::from_point( n.range().upper_left() ) ) );
            } else {
                m_stream << m_opcode.original_opcode.stringtable.set( opcode::opcode_string_type( a1conversion::to_a1::from_range( n.range() ) ) );
            }
        }

        if ( no_valid_reference_info ) {
            if ( n.has_worksheet() ) {
                if ( n.has_workbook() ) {
                    m_stream << m_opcode.original_opcode.stringtable.set( opcode::opcode_string_type( n.ref_error_workbook() ) );
                } else {
                    m_stream << opcode_stream_helper::no_pos();
                }
                m_stream << m_opcode.original_opcode.stringtable.set( opcode::opcode_string_type( n.ref_error_worksheet() ) );
            } else {
                m_stream << opcode_stream_helper::no_pos();
                m_stream << opcode_stream_helper::no_pos();
            }
        }
    }

    /*!
     * \brief
     * pass a string reference
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( string_node& n ) {
        m_stream << token::string << m_opcode.original_opcode.stringtable.set( n.get() );
    }

    /*!
     * \brief
     * set empty (parameter) token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( empty_node& ) {
        m_stream << token::empty;
    }

    /*!
     * \brief
     * set greater than token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( greater_node& ) {
        m_stream << token::greater;
    }

    /*!
     * \brief
     * set less than token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( less_node& ) {
        m_stream << token::less;
    }

    /*!
     * \brief
     * set equal token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( equal_node& ) {
        m_stream << token::equal;
    }

    /*!
     * \brief
     * set not equal token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( not_equal_node& ) {
        m_stream << token::not_equal;
    }

    /*!
     * \brief
     * set greater equal token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( greater_equal_node& ) {
        m_stream << token::greater_equal;
    }

    /*!
     * \brief
     * set less equal token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( less_equal_node& ) {
        m_stream << token::less_equal;
    }

    /*!
     * \brief
     * set percentage equal token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( percentage_node& ) {
        m_stream << token::percentage;
    }

    /*!
     * \brief
     * set error token and code
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( error_node& n ) {
        m_stream << token::error << n.get();
    }

    /*!
     * \brief
     * set exponent token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( exponent_node& ) {
        m_stream << token::exponent;
    }

    /*!
     * \brief
     * set concatenation token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( concatenation_node& ) {
        m_stream << token::concatination;
    }

    /*!
     * \brief
     * set brace token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( brace_node& n ) {
        m_stream << token::brace << n.size();
    }

    /*!
     * \brief
     * pass a function definition to the token stream.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( function_node& n ) {
        m_stream << token::function;
        function_entry* ptr = NULL;
        if ( n.is_valid() == false ) {
            // function is invalid then store the index to the functions
            // name in the string table
            m_stream << m_opcode.original_opcode.stringtable.set( n.function_name() );
        } else {
            // valid function. set opcode_stream_helper::no_pos() to signify that there is no
            // function name to be resolved in the stringtable and resolve
            // the pointer to the function entry.
            m_stream << opcode_stream_helper::no_pos();
            ptr = &n.function_entry();
        }
        // store pointer to function entry and
        // number of parameters.
        function_node::size_type param_count = n.size();
        //if there is a param list, it is padded with 2 function imbrication markers: function ( raise param param ... param lower )
        if ( /*!n.lazy_evaluation() &&*/ param_count > 0 ) {
            param_count -= 2;
        }

        m_stream << ptr << param_count;
        std::size_t jumptable_relative_position = 0;
        const std::size_t jumptable_position_offset = m_stream.tellp();
        m_stream << jumptable_relative_position;
        if ( n.lazy_evaluation() ) {
            n.remove_first();
            n.remove_last();
            // when the function uses lazy evaluation (the parameters of the
            // functions are not already on the stack when the function gets
            // called but must be resolved by the function itself) create an
            // jumptable with the offsets to the individual parameters.
            std::list<std::size_t> jumptable_list;
            for ( base_node::shallow_iterator it = n.begin_shallow(), end = n.end_shallow(); it != end; ++it ) {
                // keep jump positions relative to the jumptable's relative offset
                jumptable_list.push_back( m_stream.tellp() - jumptable_position_offset - sizeof( std::size_t ) );
                bottom_top_visitor<translator, base_node, true>::operator ()( *it );
            }
            // save the real jumptable position
            // subtract the absolute offset to get the relative position.
            jumptable_relative_position = m_stream.tellp() - jumptable_position_offset - sizeof( std::size_t );
            for ( std::list<std::size_t>::const_iterator it = jumptable_list.begin(), end_it = jumptable_list.end(); it != end_it; ++it ) {
                //foreach( const std::size_t & p, jumptable_list ) {
                m_stream << *it;
            }
            const std::size_t current_offset = m_stream.tellp();
            // update the jumptable information and return to the current
            // write position.
            m_stream.seekp( static_cast<int>( jumptable_position_offset ), vector_io_device::seek_beginning );
            m_stream << jumptable_relative_position;
            m_stream.seekp( static_cast<int>( current_offset ), vector_io_device::seek_beginning );
        }
    }

    /*!
     * \brief
     * boolean true token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( boolean_true_node& ) {
        m_stream << token::boolean_true;
    }

    /*!
     * \brief
     * boolean false token
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( boolean_false_node& ) {
        m_stream << token::boolean_false;
    }

    /*!
     * \brief
     * pass a variable to the stream
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( variable_node& n ) {
        m_stream << token::variable << m_opcode.original_opcode.stringtable.set( n.name() );
    }

    /*!
     * \brief
     * pass a named formula to the stream
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( named_formula_node& n ) {

        shared_worksheet_type ws( n.worksheet().lock() );
        shared_reference_type sr;

        if ( ws ) {
            sr = static_cast<named_formula_manager&>( ws->parent()->named_formulas() ).register_dependency( m_initiator, convert_utf8_ci( n.name().get() ), ws->uuid(), n.scope() );
        }

        m_stream << token::named_formula;
        const bool worksheet_given = n.has_worksheet();
        const bool workbook_given = n.has_workbook();
        if ( sr || worksheet_given || workbook_given ) {
            m_stream << ( m_opcode.original_opcode.location_dependent_reference.reference.set( reference_info(
                              sr,
                              ! worksheet_given,
                              false,
                              worksheet_given,
                              workbook_given,
                              worksheet_given ? ws : shared_worksheet_type(),
                              ( workbook_given && ws ) ? ws->parent() : shared_workbook_type()
                          ) ) );
        } else {
            m_stream << opcode_stream_helper::no_pos();
        }

        m_stream << m_opcode.original_opcode.stringtable.set( n.name() );

        if ( n.has_workbook() ) {
            m_stream << m_opcode.original_opcode.stringtable.set( opcode::opcode_string_type( n.ref_error_workbook() ) );
        } else {
            m_stream << opcode_stream_helper::no_pos();
        }
        if ( n.has_worksheet() ) {
            m_stream << m_opcode.original_opcode.stringtable.set( opcode::opcode_string_type( n.ref_error_worksheet() ) );
        } else {
            m_stream << opcode_stream_helper::no_pos();
        }

        if ( sr && named_formula_reference_cast( sr ).has_relative_references() ) {
            m_opcode.is_relative = true;
        }
    }

    /*!
     * \brief
     * pass an array node to the stream
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( array_node& n ) {
        m_stream << token::array << n.size();
    }

    /*!
     * \brief
     * pass an array column to the stream
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( array_row_node& n ) {
        m_stream << token::array_row << n.size();
    }

    /*!
     * \brief
     * pass a reference list to the stream
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void visit( reference_list_node& n ) {
        m_stream << token::reference_list << n.size();
    }

private:
    /*!
     * \brief
     * not copyable.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    translator& operator =( const translator& );

private:
    binary_iostream<vector_io_device> m_stream;
    positioned_op_codes& m_opcode;
    const shared_dependency_type& m_initiator;
    precedent_proxy m_precedent_proxy;
};

void opcode_generator::create( const shared_dependency_type& initiator, const base_node& ast, positioned_op_codes& ops, const referencetable_type& references )
{
    translator t( initiator, ast, ops, references );
}

