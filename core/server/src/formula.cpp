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

#include "wss/locale.hpp"
#include "wss/syntax.hpp"
#include "wss/formula.hpp"
#include "wss/formula_parser.hpp"
#include "wss/calculation_context.hpp"
#include "wss/formula_parsing_context.hpp"
#include "wss/invalid_formula_exception.hpp"
#include "wss/object_not_found_exception.hpp"
#include "wss/variant_conversion_exception.hpp"

#include "wss/opcode_generator.hpp"
#include "wss/opcode_interpreter.hpp"
#include "wss/opcode_pretty_printer_context.hpp"
#include "wss/opcode_pretty_printer.hpp"
#include "wss/opcode_rewriter.hpp"
#include "wss/reference_table_coverage.hpp"
#include "wss/scoped_reference.hpp"
#include "named_formula_dependency_wrapper.hpp"
#include "wss/range_reference.hpp"

#define HIDE_TICKET_8810_FOR_NOW 1

formula::formula( ast_formula& ast, const shared_dependency_type& container, const sheet_point& created_at_position, const referencetable_type& references /*= referencetable_type()*/, const bool inside_nf /* = false */ )
    : m_opcode( created_at_position )
    , m_container( container )
    , m_is_volatile( false )
    , m_variable()
{
    formula_parser::parsing_result_auto_type result = ast.disown();
    // the check for correctness is done by the ast_formula object.
    assert( NULL != result.get() && result->is_success() );
    m_is_volatile = result->has_volatile();
    m_variable = result->variable();
    m_is_view_independent = result->view_independent();
    m_execute_on_set = result->executes_on_set();
    opcode_generator::create( container, *result->take_ownership(), m_opcode, references );
}

formula::formula( const formula& other, const shared_dependency_type& container, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range /*= sheet_range( sheet_point(0,0) )*/, const referencetable_type& references /*= referencetable_type()*/ )
    : m_opcode( other.m_opcode.original_opcode )
    , m_container( container )
    , m_is_volatile( other.m_is_volatile )
{
    scoped_reference<shared_dependency_type> sr( container );
    if ( use_copy_move ) {
        opcode_rewriter::rewrite( container, distance, source_range, m_opcode.original_opcode.location_dependent_reference.reference, references );
    } else {
        opcode_rewriter::rewrite( container, distance, is_rewrite_to_clone_sheet, m_opcode.original_opcode.location_dependent_reference.reference, references );
    }
    m_opcode.position = other.m_opcode.position.offset( distance );
    m_opcode.is_relative = other.m_opcode.is_relative;
}

formula::formula( const formula& other, const shared_dependency_type& container, const geometry::point& distance, const bool is_rewrite_to_clone_sheet )
    : m_opcode( other.m_opcode.original_opcode )
    , m_container( container )
    , m_is_volatile( other.m_is_volatile )
    , m_variable()
{
    scoped_reference<shared_dependency_type> sr( container );
    opcode_rewriter::rewrite( container, distance, false, m_opcode.original_opcode.location_dependent_reference.reference, m_opcode.original_opcode.location_dependent_reference.reference );
    m_opcode.position = m_opcode.position.cyclic_offset<false, sheet_dimension>( distance );
    //do a deep copy here
    m_opcode.location_dependent_opcodes.reset( new positioned_op_codes::location_dependent_opcode_map_type( *other.m_opcode.location_dependent_opcodes ) );
    if ( !m_opcode.location_dependent_opcodes->empty() ) {
        typedef positioned_op_codes::location_dependent_opcode_map_type::const_iterator const_iterator;
        typedef positioned_op_codes::location_dependent_opcode_map_type::iterator iterator;
        iterator it = m_opcode.location_dependent_opcodes->begin();
        const_iterator end_it = m_opcode.location_dependent_opcodes->end();
        for ( ; it != end_it; ++it ) {
            shared_dependency_type initiator( static_cast<named_formula_dependency_wrapper*>( it->first )->shared_from_this() );
            if ( initiator ) {
                opcode_rewriter::rewrite( initiator, distance, is_rewrite_to_clone_sheet, it->second.reference, it->second.reference );

            }
        }
    }
    m_opcode.is_relative = other.m_opcode.is_relative;
}

formula::~formula()
{}

variant formula::calculate( interpreter_context& ic ) const
{
    try {
        return opcode_interpreter::calculate( m_opcode, ic );
    } catch ( const variant_conversion_exception& e ) {
        return e.operand();
    }
}

std::string formula::pretty_print( const locale& l, const bool always_add_sheet_references /* = false */ ) const
{
    opcode_pretty_printer_context ocx( m_opcode, m_container.lock(), l, false, always_add_sheet_references );
    return opcode_pretty_printer::create( ocx );
}

std::string formula::pretty_print( const locale& l, const shared_dependency_type& d, const bool always_add_sheet_references /* = true */ ) const
{
    opcode_pretty_printer_context ocx( m_opcode, m_container.lock(), l, d, false, always_add_sheet_references );
    return opcode_pretty_printer::create( ocx );
}

bool formula::has_precedents() const
{
    return m_opcode.original_opcode.location_dependent_reference.reference.size() > 0;
}

bool formula::is_volatile() const
{
    return m_is_volatile;
}

referencetable_type formula::precedents() const
{
    return m_opcode.original_opcode.location_dependent_reference.reference;
}

referencetable_type formula::precedents( const shared_dependency_type& target_dependency ) const
{
    if ( m_opcode.is_relative ) {
        positioned_op_codes::location_dependent_opcode_map_type::const_iterator it( m_opcode.location_dependent_opcodes->find( target_dependency.get() ) );
        if ( it == m_opcode.location_dependent_opcodes->end() ) {
            it = const_cast<positioned_op_codes*>( &m_opcode )->add_position( target_dependency );
        }
        return it->second.reference;
    } else {
        return m_opcode.original_opcode.location_dependent_reference.reference;
    }
}

const variable_map& formula::variable() const
{
    return m_variable;
}

optional_sheet_range_type formula::coverage() const
{
    return reference_table_coverage::coverage( m_opcode.original_opcode.location_dependent_reference.reference );
}

optional_sheet_range_type formula::coverage( const shared_dependency_type& target_dependency ) const
{
    if ( m_opcode.is_relative ) {
        positioned_op_codes::location_dependent_opcode_map_type::const_iterator it( m_opcode.location_dependent_opcodes->find( target_dependency.get() ) );
        if ( it == m_opcode.location_dependent_opcodes->end() ) {
            it = const_cast<positioned_op_codes*>( &m_opcode )->add_position( target_dependency );
        }
        return reference_table_coverage::coverage( it->second.reference );
    } else {
        return reference_table_coverage::coverage( m_opcode.original_opcode.location_dependent_reference.reference );
    }
}

void formula::add_position( const shared_dependency_type& target_dependency )
{
    if ( m_opcode.is_relative ) {
        m_opcode.add_position( target_dependency );
    }
}

void formula::remove_position( i_dependency* target_dependency )
{
    if ( m_opcode.is_relative ) {
        m_opcode.remove_position( target_dependency );
    }
}

void formula::update_position( const shared_dependency_type& target_dependency, const geometry::point& distance, const bool move_absolute_references )
{
    if ( m_opcode.is_relative ) {
        m_opcode.update_position( target_dependency, distance, move_absolute_references );
    }
}

void formula::update_position_without_rewrite( const shared_dependency_type& target_dependency, const geometry::point& distance )
{
    m_opcode.position = m_opcode.position + distance;
}

void formula::raise_volatile_count( const shared_dependency_type& d )
{
    if ( m_opcode.is_relative ) {
        positioned_op_codes::location_dependent_opcode_map_type::iterator it( m_opcode.location_dependent_opcodes->find( d.get() ) );
        if ( it != m_opcode.location_dependent_opcodes->end() ) {
            ++( it->second.volatile_count );
        }
    }
}

void formula::lower_volatile_count( const shared_dependency_type& d )
{
    if ( m_opcode.is_relative ) {
        positioned_op_codes::location_dependent_opcode_map_type::iterator it( m_opcode.location_dependent_opcodes->find( d.get() ) );
        if ( it != m_opcode.location_dependent_opcodes->end() ) {
            location_dependent_references& ref = it->second;
#ifdef HIDE_TICKET_8110_FOR_NOW
            if ( ref.volatile_count > 0 ) {
#else
            assert( "tried to lower volatile count below zero!" && ref.volatile_count > 0 );
#endif // HIDE_TICKET_8110_FOR_NOW
                --( ref.volatile_count );
#ifdef HIDE_TICKET_8110_FOR_NOW
            }
#endif // HIDE_TICKET_8110_FOR_NOW
            // when the volatile count reaches zero we still need to calculate
            // everything one more time
            if ( ( ref.volatile_count ) == 0 ) {
                flag_dirty( d );
                d->flag_dirty();
            }
        }
    }
}

size_t formula::volatile_count( const shared_dependency_type& d ) const
{
    return volatile_count_without_formula( d ) + ( m_is_volatile ? 1 : 0 );
}


size_t formula::volatile_count_without_formula( const shared_dependency_type& d ) const
{
    positioned_op_codes::location_dependent_opcode_map_type::const_iterator it( m_opcode.location_dependent_opcodes->find( d.get() ) );
    if ( it != m_opcode.location_dependent_opcodes->end() ) {
        return it->second.volatile_count;
    }
    return 0;
}

struct formula_helper : non_instantiable {
    template<bool is_dirty>
    static void set_dirty_flag( const shared_dependency_type& d, positioned_op_codes::location_dependent_opcode_map_type& location_dependent_opcodes ) {
        positioned_op_codes::location_dependent_opcode_map_type::iterator it( location_dependent_opcodes.find( d.get() ) );
        if ( it != location_dependent_opcodes.end() ) {
            it->second.is_dirty = is_dirty;
        }
    }
};
void formula::flag_dirty( const shared_dependency_type& d )
{
    if ( m_opcode.is_relative ) {
        formula_helper::set_dirty_flag<true>( d, *m_opcode.location_dependent_opcodes );
    } else if ( shared_dependency_type container = m_container.lock() ) {
        container->internal_flag_dirty();
    }
}

bool formula::is_dirty( const shared_dependency_type& d ) const
{
    if ( m_opcode.is_relative ) {
        positioned_op_codes::location_dependent_opcode_map_type::const_iterator it( m_opcode.location_dependent_opcodes->find( d.get() ) );
        if ( it != m_opcode.location_dependent_opcodes->end() ) {
            return it->second.is_dirty;
        }
    }
    if ( shared_dependency_type container = m_container.lock() ) {
        return container->is_dirty();
    }
    return false;
}

void formula::unflag_dirty( const shared_dependency_type& d )
{
    if ( m_opcode.is_relative ) {
        formula_helper::set_dirty_flag<false>( d, *m_opcode.location_dependent_opcodes );
    }
}

bool formula::is_view_independent() const
{
    return m_is_view_independent;
}

bool formula::executes_on_set() const
{
    return m_execute_on_set;
}

void formula::adjust_legacy_references( const sheet_point& position )
{
    shared_dependency_type d = m_container.lock();
    if ( d ) {
        opcode_rewriter::adjust_legacy_references( d, geometry::point( position ), m_opcode.original_opcode.location_dependent_reference.reference );
    }
    assert( "this has to be called before there are any location dependent references registered!" && ( !m_opcode.location_dependent_opcodes || m_opcode.location_dependent_opcodes->empty() ) );
}
