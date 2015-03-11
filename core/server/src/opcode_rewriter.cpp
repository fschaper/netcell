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
#include "wss/opcode_rewriter.hpp"
#include "wss/i_dependency.hpp"
#include "wss/define.hpp"
#include "wss/named_formula_reference.hpp"
#include "wss/i_named_formula_manager.hpp"
#include "wss/workbook.hpp"
#include "wss/precedent_proxy.hpp"

#include "cell_manager.hpp"

/*!
 * \brief
 * legacy sheet_dimensions
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct legacy_sheet_dimension
        : non_instantiable {
    static const unsigned int max_row = 65535;  // 0 .. 65535
    static const unsigned int max_column = 255; // 0 .. 255
    //static const boost::uint_fast64_t max_cells = ( ( boost::uint_fast64_t ) max_row + 1 ) * ( ( boost::uint_fast64_t ) max_column + 1 );
};

template<bool inside_nf>
void opcode_rewriterT<inside_nf>::rewrite( const shared_dependency_type& target_dependency, const geometry::point& distance, referencetable_type& references_to_rewrite, bool is_conditional, bool is_rewrite_to_clone_sheet, const sheet_range& source_range, const referencetable_type& references, bool move_absolute_references )
{
    referencetable_type::size_type current = 1;
    precedent_proxy proxy( target_dependency, references );
    referencetable_type::const_iterator it = references_to_rewrite.begin(), end_it = references_to_rewrite.end();
    for ( ; it != end_it; ++it, ++current ) {
        if ( ( *it ) ) {
            if ( ( *it )->type() == i_dependency_reference::range_reference ) {
                range_reference::actual actual_reference( range_reference_cast( ( *it ) ).actualize() );
                if ( actual_reference.is_valid() && ( ! is_conditional || source_range.covers( actual_reference.position() ) ) ) {
                    // if a worksheet was explicitly specified together with the cell position
                    // we will still reference the same sheet.
                    shared_worksheet_type sw = actual_reference.worksheet().lock();
                    if ( ! sw || ( *it ).relative_worksheet() ) {
                        // the position will target the current worksheet.
                        sw = target_dependency->worksheet().lock();
                    } else if ( is_rewrite_to_clone_sheet ) {
                        if ( shared_worksheet_type target_sheet = target_dependency->worksheet().lock() ) {
                            if ( sw->name() == target_sheet->name() ) {
                                sw = target_sheet;
                            }
                        }
                        //TODO (fhofmann: this line isn't nice but is needed to solve ticket 8069 for wb scoped names)
                    } else if ( !target_dependency->worksheet().expired() && target_dependency->worksheet().lock()->hidden() ) {
                        shared_worksheet_type target_ws = target_dependency->worksheet().lock();
                        if ( target_ws->name() == sw->name() && target_ws->parent() == sw->parent() ) {
                            sw = target_dependency->worksheet().lock();
                        }
                    }
                    if ( !sw ) {
                        //when unloading the worksheet might be already deleted
                        continue;
                    }
                    try {
                        // calculate the new cell we are pointing to
                        const sheet_range target_position = ( target_dependency->type() == i_dependency::named_formula_wrapper_type
                                                              || target_dependency->type() == i_dependency::named_formula_type )
                                                            ?
                                                            ( is_conditional
                                                              ? actual_reference.position().cyclic_offset<true, sheet_dimension>( distance )
                                                              : actual_reference.position().cyclic_offset<false, sheet_dimension>( distance ) )
                                                                : ( is_conditional
                                                                    ?
                                                                    actual_reference.position().offset_move_absolute_references( distance )
                                                                    : actual_reference.position().offset( distance ) );
                        const reference_info& ref_info = *it;
                        references_to_rewrite[ current ] = reference_info(
                                                               proxy.register_dependency(  sw->cells(), target_position, inside_nf ),
                                                               ref_info.relative_worksheet(),
                                                               ref_info.is_single_cell(),
                                                               ref_info.worksheet_given(),
                                                               ref_info.workbook_given(),
                                                               !ref_info.worksheet().expired() ? sw : shared_worksheet_type(),
                                                               ( !ref_info.workbook().expired() && sw ) ? sw->parent() : shared_workbook_type()
                                                           );
                    } catch ( const position_out_of_range_exception& ) {
                        // the new position of the cell would be outside the sheet
                        // we now have to invalidate the cell to emit an #REF! error
                        const reference_info& ref_info = *it;
                        references_to_rewrite[ current ] = reference_info(
                                                               shared_reference_type(),
                                                               ref_info.relative_worksheet(),
                                                               ref_info.is_single_cell(),
                                                               ref_info.worksheet_given(),
                                                               ref_info.workbook_given(),
                                                               !ref_info.worksheet().expired() ? sw : shared_worksheet_type(),
                                                               ( !ref_info.workbook().expired() && sw ) ? sw->parent() : shared_workbook_type()
                                                           );
                    }
                }
            } else if ( ( *it )->type() == i_dependency_reference::named_formula_reference ) {
                const named_formula_reference& nf_ref = named_formula_reference_cast( ( *it ) );
                if ( nf_ref.is_valid() ) {
                    // if a worksheet was explicitly specified together with the cell position
                    // we will still reference the same sheet.
                    shared_worksheet_type sw = nf_ref.nf_worksheet().lock();
                    const bool relative_worksheet = ( *it ).relative_worksheet();
                    if ( ! sw || relative_worksheet ) {
                        // the position will target the current worksheet.
                        sw = target_dependency->worksheet().lock();
                    }
                    if ( !sw ) {
                        //when unloading the worksheet might be already deleted
                        continue;
                    }
                    const reference_info& ref_info = *it;
                    references_to_rewrite[ current ] = reference_info(
                                                           sw->parent()->named_formulas().register_dependency( target_dependency, named_formula_identifier( nf_ref.name(), sw->uuid() ), nf_ref.scope()  ),
                                                           ref_info.relative_worksheet(),
                                                           ref_info.is_single_cell(),
                                                           ref_info.worksheet_given(),
                                                           ref_info.workbook_given(),
                                                           !ref_info.worksheet().expired() ? sw : shared_worksheet_type(),
                                                           ( !ref_info.workbook().expired() && sw ) ? sw->parent() : shared_workbook_type()
                                                       );
                } else {
                    // no change required, the reference stays the same.
                    references_to_rewrite[ current ] = ( *it );
                }
            } else {
                assert( !"reference is of invalid type!" );
            }
        }
    }
}

template<bool inside_nf>
void opcode_rewriterT<inside_nf>::rewrite( const shared_dependency_type& target_dependency, const geometry::point& distance, bool is_rewrite_to_clone_sheet, referencetable_type& references_to_rewrite, const referencetable_type& references, bool move_absolute_references )
{
    rewrite( target_dependency, distance, references_to_rewrite, false, is_rewrite_to_clone_sheet, sheet_point( 0, 0 ), references, move_absolute_references );
}

template<bool inside_nf>
void opcode_rewriterT<inside_nf>::rewrite( const shared_dependency_type& target_dependency, const geometry::point& distance, const sheet_range& source_range, referencetable_type& references_to_rewrite, const referencetable_type& references, bool move_absolute_references )
{
    rewrite( target_dependency, distance,  references_to_rewrite, true, false, source_range, references, move_absolute_references );
}

template<bool inside_nf>
void opcode_rewriterT<inside_nf>::adjust_legacy_references( const shared_dependency_type& target_dependency, const geometry::point& distance, referencetable_type& references_to_rewrite )
{
    if ( sheet_dimension::max_column == legacy_sheet_dimension::max_column && sheet_dimension::max_row == legacy_sheet_dimension:: max_row ) {
        //nothing to do in that case!
        return;
    }
    referencetable_type::size_type current = 1;
    referencetable_type references;
    precedent_proxy proxy( target_dependency, references );
    const geometry::point minus_distance( -distance.row(), -distance.column() );
    referencetable_type::const_iterator it = references_to_rewrite.begin(), end_it = references_to_rewrite.end();
    for ( ; it != end_it; ++it, ++current ) {
        if ( ( *it ) ) {
            if ( ( *it )->type() == i_dependency_reference::range_reference ) {
                range_reference::actual actual_reference( range_reference_cast( ( *it ) ).actualize() );
                if ( actual_reference.is_valid() ) {
                    // if a worksheet was explicitly specified together with the cell position
                    // we will still reference the same sheet.
                    shared_worksheet_type sw = actual_reference.worksheet().lock();
                    if ( ! sw || ( *it ).relative_worksheet() ) {
                        // the position will target the current worksheet.
                        sw = target_dependency->worksheet().lock();
                    }
                    // calculate the new cell we are pointing to
                    const sheet_range old_position = actual_reference.position();

                    const sheet_range target_position_legacy_style = actual_reference.position().cyclic_offset<false, legacy_sheet_dimension>( distance );
                    const sheet_range new_position = target_position_legacy_style.cyclic_offset<false, sheet_dimension>( minus_distance );

                    if ( old_position != new_position ) {
                        references_to_rewrite[ current ] = reference_info(
                                                               proxy.register_dependency( sw->cells(), new_position, inside_nf ),
                                                               ( *it ).relative_worksheet(),
                                                               ( *it ).is_single_cell(),
                                                               ( *it ).worksheet_given(),
                                                               ( *it ).workbook_given(),
                                                               !( *it ).worksheet().expired() ? sw : shared_worksheet_type(),
                                                               ( !( *it ).workbook().expired() && sw ) ? sw->parent() : shared_workbook_type()
                                                           );
                    }
                }
            } else {
                // no change required, the reference stays the same.
                references_to_rewrite[ current ] = ( *it );
            }
        }
    }
}

template class opcode_rewriterT<true>;
template class opcode_rewriterT<false>;
