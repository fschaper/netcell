/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
#ifdef copy_address_rewriter_on

#include "precompiled_header.hpp"

#include "copy_address_rewriter.hpp"

#include "wss/i_dependency_reference.hpp"
#include "wss/i_dependency.hpp"
#include "wss/worksheet.hpp"
#include "wss/range_reference.hpp"
#include "wss/base_visitor.hpp"
#include "wss/tree_visitor.hpp"
#include "wss/syntax.hpp"

#include "cell_manager.hpp"

class copy_address_rewriter::rewriter_context
{
public:
    rewriter_context( const shared_dependency_type& target_dependency, reference_set& references, const geometry::point& distance )
        : m_target_dependency( target_dependency )
        , m_precedents( references )
        , m_worksheet( target_dependency->worksheet().lock() )
        , m_distance( distance )
        , m_source_range( sheet_point( 0, 0 ) )
        , m_use_conditional_copy( false ) {}

    rewriter_context( const shared_dependency_type& target_dependency, reference_set& references, const geometry::point& distance, const sheet_range& source_range )
        : m_target_dependency( target_dependency )
        , m_precedents( references )
        , m_worksheet( target_dependency->worksheet().lock() )
        , m_distance( distance )
        , m_source_range( source_range )
        , m_use_conditional_copy( true ) {}

    const geometry::point& distance() const {
        return m_distance;
    }

    const shared_worksheet_type& worksheet() const {
        return m_worksheet;
    }

    const shared_dependency_type& target_dependency() const {
        return m_target_dependency;
    }

    reference_set& precedents() const {
        return m_precedents;
    }

    bool is_conditional() const {
        return m_use_conditional_copy;
    }

    const sheet_range& source_range() const {
        return m_source_range;
    }

private:
    const shared_dependency_type& m_target_dependency;
    reference_set& m_precedents;
    shared_worksheet_type m_worksheet;
    geometry::point m_distance;
    sheet_range m_source_range;
    bool m_use_conditional_copy;
};

class copy_address_rewriter::rewriter
    : public base_visitor
    , public bottom_top_visitor<rewriter, base_node>
{
public:
    rewriter( base_node& ast, const rewriter_context& context )
        : m_context( context ) {
        bottom_top_visitor<rewriter, base_node>::operator ()( ast );
    }

    virtual void visit( range_node& n ) {
        if ( n.is_valid() ) {
            if ( ! m_context.is_conditional() || m_context.source_range().is_inside( n.reference()->position() ) ) {
                // TODO: we actually have nothing to do here in case we deal with an absolute address
                // on the same worksheet. we might want to optimize for this later on.

                // TODO: we might also want to treat cells as ranges in all cases.
                try {
                    // calculate the new cell we are pointing to
                    sheet_range target_position = m_context.target_dependency()->type() == i_dependency::named_formula_type
                                                  ? n.reference()->position().cyclic_offset( m_context.distance() )
                                                  : n.reference()->position().offset( m_context.distance() );

                    shared_worksheet_type sw;
                    if ( n.has_worksheet() ) {
                        // if a worksheet was explicitly specified together with the cell position
                        // we will still reference the same sheet.
                        sw = range_reference_cast( n.reference() ).worksheet().lock();
                    } else {
                        // the position will target the current worksheet.
                        sw = m_context.worksheet();
                    }
                    shared_reference_type ref( sw->cells().register_dependency( m_context.target_dependency(), target_position ) );
                    m_context.precedents().add( ref );
                    n.update_reference( ref );
                } catch ( const position_out_of_range_exception& ) {
                    // the new position of the cell would be outside the sheet
                    // we now have to invalidate the cell to emit an #REF! error
                    n.invalidate();
                }
            }
        }
    }

private:
    const rewriter_context& m_context;
};

void copy_address_rewriter::operator()( const shared_dependency_type& target_dependency, const geometry::point& distance, reference_set& precedents, base_node& ast )
{
    rewriter( ast, rewriter_context( target_dependency, precedents, distance ) );
}

void copy_address_rewriter::operator()( const shared_dependency_type& target_dependency, const geometry::point& distance, const sheet_range& source_range, reference_set& precedents, base_node& ast )
{
    rewriter( ast, rewriter_context( target_dependency, precedents, distance, source_range ) );
}
#endif
