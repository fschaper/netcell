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
#include "wss/worksheet.hpp"

#include "wss/workbook.hpp"
#include "core_logging.hpp"
#include "wss/conditional_format_manager.hpp"
#include "wss/sheet_layout_manager.hpp"
#include "wss/a1conversion.hpp"
#include "named_formula_manager.hpp"
#include "wss/object_registry.hpp"
#include "wss/border_manager.hpp"
#include "cell_manager.hpp"
#include "wss/server.hpp"
#include "cell.hpp"
#include "uuid_adjust.hpp"
#include "wss/core2_compatibility.hpp"
#include "wss/range.hpp"
#include "wss/i_named_formula_manager.hpp"
#include "wss/merged_cell_manager.hpp"
#include "wss/variable_map.hpp"
#include "wss/worksheet_element_storage.hpp"
#include "wss/get_conditional_format.hpp"
#include "wss/used_range.hpp"
#include "wss/function_parameters.hpp"
#include "wss/invalid_worksheet_exception.hpp"

#include <oxml/custom_data.hpp>



/*!
* \brief
* private implementation.
*
* \author
* Florian Schaper <florian.schaper@jedox.com>
*/
struct worksheet::worksheet_impl {
    worksheet_impl( worksheet& ws, bool hidden )
        : m_cell_manager( ws )
        , m_conditional_formats( ws )
        , m_hidden( hidden ) {}
    typedef std::set< weak_dependency_type > view_independent_set_type;
    ~worksheet_impl() {}

    variable_map m_variable;
    cell_manager m_cell_manager;
    conditional_format_manager m_conditional_formats;
    border_manager m_borders;
    worksheet_element_storage m_elements;
    style_manager_type m_style;
    attribute_manager m_attribute;
    sheet_layout_manager m_layout;
    merged_cell_manager m_merge;
    locked_cell_manager_type m_locked;
    format_manager_type m_format;
    view_independent_set_type m_view_independents;

    const bool m_hidden;
};

worksheet::worksheet( const shared_workbook_type& wb, const utf8_ci_string& name, const bool hidden /* = false */ )
    : identifiable_object( name )
    , m_impl()
    , m_parent( wb )
{
    LOG_CORE_DEBUG( "created " << ( hidden ? "clone sheet " : "worksheet " ) << "object [" << this->uuid() << "] with name ["  << this->name() << "]" );
    m_impl.reset( new worksheet_impl( *this, hidden ) );
}

worksheet::~worksheet()
{
    on_global_before_delete( *this );

    parent()->named_formulas().unload_sheet( this->uuid() );
    if ( !hidden() ) {
        parent()->flag_changed();
    }
    LOG_CORE_DEBUG( "released " << ( m_impl->m_hidden ? "clone sheet " : "worksheet " ) << "object [" << this->uuid() << "] with name ["  << this->name() << "]"  );
    server::instance().object_registry().unset( *this );
}

shared_worksheet_type worksheet::create( const shared_workbook_type& wb, const utf8_ci_string& name, const bool hidden /* = false */ )
{
    shared_worksheet_type return_value( boost::make_shared<worksheet>( wb, name, hidden ) );
    return_value->m_weak_worksheet = return_value;
    return_value->m_impl->m_layout.worksheet( return_value );
    server::instance().object_registry().set( return_value );
    if ( !hidden ) {
        wb->flag_changed();
    }
    return return_value;
}


shared_workbook_type worksheet::parent() const
{
    return m_parent;
}

weak_worksheet_type worksheet::weak_pointer() const
{
    return m_weak_worksheet;
}

cell_manager& worksheet::cells()
{
    return m_impl->m_cell_manager;
}

const cell_manager& worksheet::cells() const
{
    return m_impl->m_cell_manager;
}

style_manager_type& worksheet::style()
{
    return m_impl->m_style;
}

const style_manager_type& worksheet::style() const
{
    return m_impl->m_style;
}

const format_manager_type& worksheet::format() const
{
    return m_impl->m_format;
}

format_manager_type& worksheet::format()
{
    return m_impl->m_format;
}

attribute_manager& worksheet::attribute()
{
    return m_impl->m_attribute;
}

const attribute_manager& worksheet::attribute() const
{
    return m_impl->m_attribute;
}

sheet_layout_manager& worksheet::layout()
{
    return m_impl->m_layout;
}

const sheet_layout_manager& worksheet::layout() const
{
    return m_impl->m_layout;
}

merged_cell_manager& worksheet::merge()
{
    return m_impl->m_merge;
}

const merged_cell_manager& worksheet::merge() const
{
    return m_impl->m_merge;
}

locked_cell_manager_type& worksheet::lock()
{
    return m_impl->m_locked;
}

const locked_cell_manager_type& worksheet::lock() const
{
    return m_impl->m_locked;
}

variable_map& worksheet::variable()
{
    return m_impl->m_variable;
}

worksheet_element_storage& worksheet::elements()
{
    return m_impl->m_elements;
}

const worksheet_element_storage& worksheet::elements() const
{
    return m_impl->m_elements;
}

border_manager& worksheet::borders()
{
    return m_impl->m_borders;
}

const border_manager& worksheet::borders() const
{
    return m_impl->m_borders;
}

conditional_format_manager& worksheet::conditional_formats()
{
    return m_impl->m_conditional_formats;
}

const conditional_format_manager& worksheet::conditional_formats() const
{
    return m_impl->m_conditional_formats;
}

::range worksheet::range( const sheet_range& r )
{
    return ::range( shared_from_this(), r );
}

const ::range worksheet::range( const sheet_range& r ) const
{
    return ::range( const_cast<worksheet*>( this )->shared_from_this(), r );
}

optional_sheet_range_type worksheet::used_range( int query /*= ::used_range::all*/, bool include_fulls /* = true */ ) const
{
    optional_sheet_range_type return_value;
    if ( query & ::used_range::cell ) {
        optional_sheet_range_type cell_range( cells().used_range( ( query & ::used_range::precedents ) == ::used_range::precedents ) );
        if ( cell_range ) {
            return_value = cell_range;
        }
    }

    if ( query & ::used_range::style ) {
        optional_sheet_range_type style_range( style().used_range( include_fulls ) );
        if ( style_range ) {
            if ( return_value ) {
                ( *return_value ).enclose_into_self( *style_range );
            } else {
                return_value = style_range;
            }
        }

        optional_sheet_range_type border_range( borders().used_range() );
        if ( border_range ) {
            if ( return_value ) {
                ( *return_value ).enclose_into_self( *border_range );
            } else {
                return_value = border_range;
            }
        }

        optional_sheet_range_type merge_range( merge().used_range() );
        if ( merge_range ) {
            if ( return_value ) {
                ( *return_value ).enclose_into_self( *merge_range );
            } else {
                return_value = merge_range;
            }
        }

        optional_sheet_range_type format_range( format().used_range() );
        if ( format_range ) {
            if ( return_value ) {
                ( *return_value ).enclose_into_self( *format_range );
            } else {
                return_value = format_range;
            }
        }

        optional_sheet_range_type cf_range( conditional_formats().used_range() );
        if ( cf_range ) {
            if ( return_value ) {
                ( *return_value ).enclose_into_self( *cf_range );
            } else {
                return_value = cf_range;
            }
        }
    }

    if ( query & ::used_range::attribute ) {
        optional_sheet_range_type attribute_range( attribute().used_range() );
        if ( attribute_range ) {
            if ( return_value ) {
                ( *return_value ).enclose_into_self( *attribute_range );
            } else {
                return_value = attribute_range;
            }
        }
    }

    if ( query & ::used_range::lock ) {
        optional_sheet_range_type locked_cell_range( lock().used_range() );
        if ( locked_cell_range ) {
            if ( return_value ) {
                ( *return_value ).enclose_into_self( *locked_cell_range );
            } else {
                return_value = locked_cell_range;
            }
        }
    }

    if ( query & ::used_range::extended ) {
        worksheet_element_storage::key_vec_type key;
        key.push_back( "n_location" );
        worksheet_element_storage::key_value_vector_vector_type val = elements().get_worksheet_elements_filtered( *::session::thread_session(), worksheet_element_storage::id_vec_type(), key );
        foreach( const worksheet_element_storage::key_value_vector_type & wselt, val ) {
            const std::string& formula = wselt[0].second.string();
            try {
                const sheet_range& crt = a1conversion::from_a1::range( formula.substr( 1, formula.size() ) );
                if ( return_value ) {
                    if ( return_value->bottom() < crt.bottom() || return_value->right() < crt.right() ) {
                        ( *return_value ).enclose_into_self( crt );
                    }
                } else {
                    return_value = crt;
                }
            } catch ( boost::bad_lexical_cast& ) {
                //disregard locations like = $A$1:$A$10,$A$1.....
            }
        }
    }

    return return_value;
}

void worksheet::select( selection_state& s )
{
    LOG_CORE_TRACE( "selecting worksheet object [" << this->uuid() << "] with name ["  << this->name() << "]" );
    s.worksheet( shared_from_this() );
}

void worksheet::unload()
{
    m_parent->named_formulas().unload_sheet( this->uuid() );
    LOG_CORE_DEBUG( "unloading " << ( hidden() ? "clone sheet " : "worksheet " ) << "object [" << this->uuid() << "] with name ["  << this->name() << "]"  );
    session*    crt_session = session::thread_session();
    if ( NULL != crt_session ) {
        crt_session->session_sheets().notify_sheet_unload( this->uuid() );
    }
}

shared_worksheet_type worksheet::copy( session& s, shared_workbook_type target_wb, const uuid_type& next_ws_uuid /*= boost::uuids::nil_uuid() */ ) const
{
    shared_worksheet_type copied_ws = target_wb->add( name(), next_ws_uuid, true );
    copy_everything_into_target_sheet( s, copied_ws );
    s.clear_cache();
    return copied_ws;
}

shared_worksheet_type worksheet::create_session_sheet( session& s, const shared_worksheet_type& source_ws )
{
    if ( source_ws->hidden() ) {
        throw invalid_worksheet_exception( "trying to create a session sheet from a session sheet, thats not a good idea!" );
    }
    return create( source_ws->parent(), source_ws->name(), true );
}

void worksheet::fill_session_sheet( session& s, const shared_worksheet_type& session_sheet ) const
{
    copy_everything_into_target_sheet( s, session_sheet );
    session_sheet->layout().worksheet( session_sheet );
    s.clear_cache();
}

void worksheet::copy_everything_into_target_sheet( session& s, const shared_worksheet_type& target_sheet ) const
{
    static_cast<named_formula_manager&>( parent()->named_formulas() ).copy_to_sheet( s, uuid(), target_sheet );
    elements().copy_to_sheet( s, target_sheet );
    layout().copy_everything_to_other( target_sheet->layout() );
    target_sheet->style() = style();
    //different copy for cells to not have a huge used range in case someone is using styles on whole rows/columns
    {
        optional_sheet_range_type source_sheet_used_range =  used_range( ::used_range::cell );
        if ( source_sheet_used_range ) {
            ::range source_range = range( *source_sheet_used_range );
            ::range target_range = target_sheet->range( *source_sheet_used_range );
            source_range.copy( s, target_range, false, insert_shift_direction::automatic, content_type::formula | content_type::value );
            // copy view_independents
            if ( !this->m_impl->m_view_independents.empty() ) {
                range_lock lock( target_sheet->cells().lock( *source_sheet_used_range, lock::shared ) );
                for (
                    worksheet_impl::view_independent_set_type::const_iterator it = this->m_impl->m_view_independents.begin(), end_it =  this->m_impl->m_view_independents.end();
                    it != end_it;
                    ++it
                ) {
                    if ( shared_dependency_type sd = it->lock() ) {
                        target_sheet->register_view_independent( lock.get( sd->position() ) );
                    }
                }
            }
        }
    }
    {
        optional_sheet_range_type source_sheet_used_range =  used_range( ::used_range::style | ::used_range::attribute | ::used_range::lock );
        if ( source_sheet_used_range ) {
            ::range source_range = range( *source_sheet_used_range );
            ::range target_range = target_sheet->range( *source_sheet_used_range );
            source_range.copy( s, target_range, false, insert_shift_direction::automatic, content_type::conditional_formats | content_type::format | content_type::attributes | content_type::border );
        }
    }
}

const bool worksheet::hidden()
{
    return m_impl->m_hidden;
}

void worksheet::insert_row( session& s, unsigned int row, unsigned int row_count, const copy_format_from::type format_from /* = copy_format_from::left_or_above */ )
{
    optional_sheet_range_type optional_used_sheet_range( used_range( ::used_range::all | ::used_range::precedents ) );

    if ( optional_used_sheet_range ) {
        sheet_range used_sheet_range( ( *optional_used_sheet_range ).enclose_point( sheet_point( 0, 0 ) ) );

        if ( used_sheet_range.lower_right().row() >= static_cast<int>( sheet_dimension::max_row ) ) {
            //shift data out of the sheet for now
            used_sheet_range = sheet_range( sheet_point( 0, 0 ), sheet_point( sheet_dimension::max_row  - row_count, used_sheet_range.lower_right().column() )  );
        }

        // we don't need to do anything in case somebody wants to insert rows
        // that are below the used range.
        if ( used_sheet_range.lower_right().row() >= ( sheet_range::integer_type ) ( row ) ) {
            sheet_range lower_section( sheet_point( row, used_sheet_range.upper_left().column() ), used_sheet_range.lower_right() );
            if ( used_sheet_range.does_intersect( lower_section ) ) {
                sheet_range source_rect = used_sheet_range.intersection( lower_section );
                ::range target( range( sheet_range( sheet_point( row + row_count, source_rect.upper_left().column() ) ) ) );
                range( source_rect ).move( s, target, true, format_from, insert_shift_direction::entire_row, content_type::all_plus_cf_but_style );
            }
        }
        style().shift_rows( row, row_count );
        if ( copy_format_from::none != format_from ) {
            sheet_range format_source( sheet_point( 0, 0 ), sheet_point( 0, 0 ) );
            switch ( format_from ) {
                case copy_format_from::left_or_above:
                    if ( 0 == row ) { //cant copy styles from negative row index..
                        break;
                    }
                    format_source = sheet_range( sheet_point( row - 1, used_sheet_range.upper_left().column() ), sheet_point( row - 1, used_sheet_range.lower_right().column() ) );
                    break;
                case copy_format_from::right_or_below:
                    if ( sheet_dimension::max_row == row ) { //cant copy styles from too big row index..
                        break;
                    }
                    format_source = sheet_range( sheet_point( row + row_count, used_sheet_range.upper_left().column() ), sheet_point( row + row_count, used_sheet_range.lower_right().column() ) );
                    break;
                default:
                    break;
            }

            if ( used_sheet_range.does_intersect( format_source ) ) {
                sheet_range format_target( sheet_range( sheet_point( row, format_source.upper_left().column() ), sheet_point( row + row_count - 1, format_source.lower_right().column() ) ) );
                long copy_content = content_type::border | content_type::format | content_type::attributes;
                if ( !m_impl->m_hidden ) {
                    copy_content |= content_type::conditional_formats;
                }
                ::range format_target_range( range( format_target ) );
                range( format_source.intersection( used_sheet_range ) ).copy( s, format_target_range, true, insert_shift_direction::automatic, copy_content );
            }
        }
    }
    layout().shift_rows( row, row_count );
    if ( copy_format_from::none != format_from ) {
        layout().row_height( sheet_layout_trait::line_type( row, row + row_count ), layout().row_height( copy_format_from::left_or_above == format_from ? row - 1 : row + row_count ) );
    }


    s.clear_cache();
}

void worksheet::insert_column( session& s, unsigned int column, unsigned int column_count, const copy_format_from::type format_from /* = copy_format_from::left_or_above */ )
{

    optional_sheet_range_type optional_used_sheet_range( used_range( ::used_range::all | ::used_range::precedents ) );

    if ( optional_used_sheet_range ) {

        sheet_range used_sheet_range( ( *optional_used_sheet_range ).enclose_point( sheet_point( 0, 0 ) ) );

        if ( used_sheet_range.lower_right().column() >= static_cast<int>( sheet_dimension::max_column ) ) {
            //shift data out of the sheet for now
            used_sheet_range = sheet_range( sheet_point( 0, 0 ), sheet_point( used_sheet_range.lower_right().row(), sheet_dimension::max_column - column_count )  );
        }

        // sanity check
        if ( used_sheet_range.lower_right().column() >= ( sheet_range::integer_type ) ( column ) ) {
            const sheet_range right_section( sheet_point( 0, column ), sheet_point( sheet_dimension::max_row, sheet_dimension::max_column ) );
            if ( used_sheet_range.does_intersect( right_section ) ) {
                sheet_range source_rect = used_sheet_range.intersection( right_section );
                ::range target( range( sheet_range( sheet_point( used_sheet_range.upper_left().row(), column + column_count ) ) ) );
                range( source_rect ).move( s, target, true, format_from, insert_shift_direction::entire_column, content_type::all_plus_cf_but_style );
            }
        }
        style().shift_columns( column, column_count );
        if ( copy_format_from::none != format_from ) {
            sheet_range format_source( sheet_point( 0, 0 ), sheet_point( 0, 0 ) );
            switch ( format_from ) {
                case copy_format_from::left_or_above:
                    if ( 0 == column ) { //cant copy styles from negative row index..
                        break;
                    }
                    format_source = sheet_range( sheet_point( used_sheet_range.upper_left().row(), column - 1 ), sheet_point( used_sheet_range.lower_right().row(), column - 1 ) );
                    break;

                case copy_format_from::right_or_below:
                    if ( sheet_dimension::max_column == column ) { //cant copy styles from too big row index..
                        break;
                    }
                    format_source = sheet_range( sheet_point( used_sheet_range.upper_left().row(), column + column_count ), sheet_point( used_sheet_range.lower_right().row(), column + column_count ) );
                    break;

                default:
                    break;
            }
            if ( used_sheet_range.does_intersect( format_source ) ) {
                sheet_range format_target( sheet_range( sheet_point( format_source.upper_left().row(), column ), sheet_point( format_source.lower_right().row(), column + column_count - 1 ) ) );
                long copy_content = content_type::border | content_type::format | content_type::attributes;
                if ( !m_impl->m_hidden ) {
                    copy_content |= content_type::conditional_formats;
                }
                ::range format_target_range( range( format_target ) );
                range( format_source.intersection( used_sheet_range ) ).copy( s, format_target_range, true, insert_shift_direction::automatic,  copy_content );
            }
        }
    }
    layout().shift_columns( column, column_count );
    if ( copy_format_from::none != format_from ) {
        layout().column_width( sheet_layout_trait::line_type( column, column + column_count ), layout().column_width( copy_format_from::left_or_above == format_from ? column - 1 : column + column_count ) );
    }

    s.clear_cache();
}

void worksheet::delete_row( session& s, unsigned int row, unsigned int row_count )
{
    // get the worksheets used range (styles, cells, formatting and _precedent_ informations from the dependency manager).
    optional_sheet_range_type optional_used_sheet_range( used_range( ::used_range::all | ::used_range::precedents ) );
    // sanity check.
    if ( optional_used_sheet_range ) {
        const sheet_range used_sheet_range( *optional_used_sheet_range );
        if ( ( static_cast<unsigned int>( used_sheet_range.lower_right().row() ) >= row ) ) {

            static const int remaining_types_to_clear = ( content_type::border | content_type::format | content_type::attributes | content_type::conditional_formats );
            // we need to move
            const sheet_point::integer_type lower_selection_lower_row = std::max<sheet_point::integer_type>( used_sheet_range.lower_right().row(), row + row_count );
            const sheet_range lower_selection( sheet_range( sheet_point( row + row_count, used_sheet_range.upper_left().column() ), sheet_point( lower_selection_lower_row, used_sheet_range.lower_right().column() ) ) );
            const sheet_range target_selection( sheet_point( row, used_sheet_range.upper_left().column() ) );
            const sheet_point lower_right_point( std::max( target_selection.upper_left().row(), lower_selection.upper_left().row() - 1 ), lower_selection.lower_right().column() );
            const sheet_range lower_clear_selection( target_selection.lower_left(), lower_right_point );
            // target where we move the remainder
            ::range target_range( range( target_selection ) );
            // clear the area of styles etc
            cells().lock( lower_clear_selection, lock::exclusive ).erase( s );
            range( lower_clear_selection ).clear( s, remaining_types_to_clear, true );

            // move the remainder now
            range( lower_selection ).move( s, target_range, true, copy_format_from::none, insert_shift_direction::entire_row, content_type::all_plus_cf_but_style );
        }
        style().unshift_rows( row, row_count );
    }
    layout().shift_rows( row, 0 - row_count );
    s.clear_cache();
}

void worksheet::delete_column( session& s, unsigned int column, unsigned int column_count )
{
    optional_sheet_range_type optional_used_sheet_range( used_range( ::used_range::all | ::used_range::precedents ) );
    if ( optional_used_sheet_range ) {
        sheet_range used_sheet_range( *optional_used_sheet_range );
        static const int remaining_types_to_clear = ( content_type::border | content_type::format | content_type::attributes | content_type::conditional_formats );
        // move
        const sheet_point::integer_type lower_selection_right_col = std::max<sheet_point::integer_type>( used_sheet_range.lower_right().column(), column + column_count );
        const sheet_range right_selection( sheet_point( used_sheet_range.upper_left().row(), column + column_count ), sheet_point( used_sheet_range.lower_right().row(), lower_selection_right_col ) );
        const sheet_range target_selection( sheet_point( used_sheet_range.upper_left().row(), column ) );
        const sheet_point lower_right_point( right_selection.lower_left().row(), std::max( target_selection.upper_left().column(),  right_selection.lower_left().column() - 1 ) );
        const sheet_range left_clear_selection( target_selection.upper_left(), lower_right_point );

        // target where we move the remainder
        ::range target_range( range( target_selection ) );
        // clear the area before we move the remainder to invalidate all references
        cells().lock( left_clear_selection, lock::exclusive ).erase( s );
        range( left_clear_selection ).clear( s, remaining_types_to_clear, true );
        // move the remainder now
        range( right_selection ).move( s, target_range, true, copy_format_from::none, insert_shift_direction::entire_column, content_type::all_plus_cf_but_style );
        //}
        style().unshift_columns( column, column_count );
    }
    layout().shift_columns( column, 0 - column_count );
    s.clear_cache();
}


void worksheet::insert_cells( session& s, const sheet_range& rect, const insert_shift_direction::type shift_direction /*= insert_shift_direction::horizontally*/, copy_format_from::type format_from /*= copy_format_from::left_or_above */ )
{
    const optional_sheet_range_type optional_used_range = used_range();
    if ( optional_used_range && rect.does_intersect( *optional_used_range ) ) {
        const bool shift_right = ( shift_direction == insert_shift_direction::horizontally );
        sheet_range used_sheet_range( ( *optional_used_range ).enclose_point( sheet_point( 0, 0 ) ) );


        //the section that will be moved
        sheet_range source( sheet_point( 0, 0 ) );

        //adjust used range so that we don't move out of the sheet
        if ( shift_right ) {
            if ( used_sheet_range.lower_right().column() >= static_cast<int>( sheet_dimension::max_column ) ) {
                //shift data out of the sheet for now
                used_sheet_range = sheet_range( sheet_point( 0, 0 ), sheet_point( used_sheet_range.lower_right().row(), ( sheet_dimension::max_column - 1 ) - rect.column_count() )  );
            }
            source =  sheet_range( rect.upper_left(), sheet_point( rect.lower_right().row(), used_sheet_range.lower_right().column() ) );
        } else {
            if ( used_sheet_range.lower_right().row() >= static_cast<int>( sheet_dimension::max_row ) ) {
                //shift data out of the sheet for now
                used_sheet_range = sheet_range( sheet_point( 0, 0 ), sheet_point( ( sheet_dimension::max_row - 1 )  - rect.row_count(), used_sheet_range.lower_right().column() )  );
            }
            source =  sheet_range( rect.upper_left(), sheet_point(  used_sheet_range.lower_right().row(), rect.lower_right().column() ) );
        }

        ::range target( range(
                            shift_right
                            ?
                            source.checked_offset( sheet_point( 0, rect.column_count() ) )
                            :
                            source.checked_offset( sheet_point( rect.row_count(), 0 ) )
                        ) );

        range( source ).move( s, target, false, format_from, shift_direction );

        switch ( format_from ) {
            case copy_format_from::left_or_above: {
                if ( ( shift_right && rect.upper_left().column() == 0 ) || ( !shift_right && rect.upper_left().row() == 0 ) ) {
                    break;
                }

                ::range format_target_range( range( rect ) );

                static const long copy_content = content_type::style | content_type::format | content_type::attributes | content_type::conditional_formats;
                range(
                    shift_right
                    ?
                    sheet_range(
                        rect.upper_left().offset( 0, -1 ),
                        rect.lower_left().offset( 0, -1 )
                    )
                    :
                    sheet_range(
                        rect.upper_left().offset( -1, 0 ),
                        rect.upper_right().offset( -1, 0 )
                    )
                ).copy( s, format_target_range, false, shift_direction, copy_content );
            }
            break;

            case copy_format_from::right_or_below: {
                if ( ( shift_right && rect.upper_left().column() == ( sheet_range::integer_type ) ( sheet_dimension::max_column ) ) || ( !shift_right && rect.upper_left().row() == ( sheet_range::integer_type ) ( sheet_dimension::max_row ) ) ) {
                    break;
                }

                ::range format_target_range( range( rect ) );

                static const long copy_content = content_type::style | content_type::format | content_type::attributes | content_type::conditional_formats;
                range(
                    shift_right
                    ?
                    sheet_range(
                        rect.upper_right().offset( 0, 1 ),
                        rect.lower_right().offset( 0, 1 )
                    )
                    :
                    sheet_range(
                        rect.lower_left().offset( 1, 0 ),
                        rect.lower_right().offset( 1, 0 )
                    )
                ).copy( s, format_target_range, false, shift_direction, copy_content );
            }
            break;

            default:
                break;
        }
    }
}


void worksheet::delete_cells( session& s, const sheet_range& rect, const insert_shift_direction::type shift_direction/* = insert_shift_direction::horizontally*/ )
{
    optional_sheet_range_type optional_used_range = used_range();
    if ( optional_used_range && rect.does_intersect( *optional_used_range ) ) {
        const sheet_range used_sheet_range = *optional_used_range;
        /*
        ::range delete_section( range( rect ) ) ;
        delete_section.erase( s );*/


        const bool shift_right = ( shift_direction == insert_shift_direction::horizontally );

        ::range target( range( sheet_range (
                                   rect.upper_left(),
                                   shift_right
                                   ?
                                   sheet_point(
                                       rect.lower_right().row(),
                                       used_sheet_range.lower_right().column()
                                   )
                                   :
                                   sheet_point(
                                       used_sheet_range.lower_right().row(),
                                       rect.lower_right().column()
                                   )
                               ) ) );
        //the section that will be moved
        const sheet_range source(
            shift_right
            ?
            target.coverage().checked_offset( sheet_point( 0, rect.column_count() ) )
            :
            target.coverage().checked_offset( sheet_point( rect.row_count(), 0 ) )
        );
        range( source ).move( s, target, false, copy_format_from::none, shift_direction );
    }

}

rectangle_list_type worksheet::merged_range_list() const
{
    return merge().merged_range_list();
}

void worksheet::deserialize( session& s, const spreadsheetml::CT_extended_data& data )
{
    namespace sml = spreadsheetml;

    const std::vector< sml::CT_worksheet_element >&  in_wselts = data.worksheet_elements.worksheet_element;

    for ( std::vector< sml::CT_worksheet_element >::const_iterator i = in_wselts.begin(), end_it = in_wselts.end(); i != end_it; ++i ) {
#ifdef _CORE2_COMPATIBILITY_ON_UUIDS_
        //TODO this is very ugly but won't stay like that! the uuid has to be found _before_ the creation of the ws element!
        if ( i->wse_id.value.present() ) {
            LOG_CORE_DEBUG( "core2 compatibility issue:\
                              uuid's will not be unique for multiple instances of this worksheet." );

            std::string uuid_string( i->wse_id.value.get() );

            shared_worksheet_element_type wselt = worksheet_element::create( shared_from_this(), uuid_adjust::cast_uuid( uuid_string ) );

            try {
                wselt->deserialize( s, *i );
            } catch ( const invalid_formula_exception& e ) {
                LOG_CORE_ERROR( "error during import: " << e.what() );
            }
        } else {
#endif // _CORE2_COMPATIBILITY_ON_UUIDS_
            shared_worksheet_element_type   wselt = worksheet_element::create( shared_from_this() );
            try {
                wselt->deserialize( s, *i );
            } catch ( const invalid_formula_exception& e ) {
                LOG_CORE_ERROR( "error during import: " << e.what() );
            }
#ifdef _CORE2_COMPATIBILITY_ON_UUIDS_
        }
#endif // _CORE2_COMPATIBILITY_ON_UUIDS_

    }

    for ( std::vector< sml::CT_cell_attribute >::const_iterator i = data.cell_attributes.cell_attribute.begin(), end_it = data.cell_attributes.cell_attribute.end(); i != end_it; ++i ) {
        ::range             crt_range = range( sheet_range( sheet_point( i->row.get(), i->col.get() ) ) );
        attribute_set_type  crt_attributes;
        for ( std::vector< spreadsheetml::CT_attribute >::const_iterator j = i->attributes.attribute.begin(); j != i->attributes.attribute.end(); j++ ) {
            if ( !j->name.present() ) {
                continue;
            }
            if ( !j->value.present() ) {
                continue;
            }
            crt_attributes.add( j->name.get(), j->value.get() );
        }

        crt_range.attribute( s, crt_attributes );
    }
}

void worksheet::serialize( session& s, spreadsheetml::CT_extended_data& data ) const
{
    namespace sml = spreadsheetml;

    sml::CT_worksheet_elements& wselts  = data.worksheet_elements;

    foreach( const shared_worksheet_element_type & wse, m_impl->m_elements.list_all_elements() ) {
        if ( variant( "img" ) == wse->property( s, "e_type" ).second ) {
            continue;
        }
        sml::CT_worksheet_element wselt;
        wse->serialize( s, wselt );
        wselts.worksheet_element.push_back( wselt );
    }

    optional_sheet_range_type range = used_range( used_range::all, false );

    if ( !range ) {
        return;
    }

    const attribute_manager& m = attribute();
    optional_sheet_range_type attribute_range = m.used_range();

    if ( !attribute_range.is_initialized() ) {
        return;
    }

    sheet_range sr = attribute_range.get();

    for ( sheet_range::const_iterator it = sr.begin(), end_it = sr.end(); it != end_it; ++it ) {
        sml::CT_cell_attribute          cell_attribute;

        cell_attribute.row = ( *it ).row();
        cell_attribute.col = ( *it ).column();

        attribute_set_type attributes = m.get( *it );

        for ( attribute_set_type::const_iterator i = attributes.begin(); i != attributes.end(); i++ ) {
            sml::CT_attribute out_attr;
            out_attr.name = convert_utf8_ci( i->first );
            out_attr.value = i->second;

            cell_attribute.attributes.attribute.push_back( out_attr );
        }

        data.cell_attributes.cell_attribute.push_back( cell_attribute );
    }
}

rectangle_list_type worksheet::array_region_list()
{
    return m_impl->m_cell_manager.array_list();
}

void worksheet::register_view_independent( const shared_dependency_type& dep )
{
    m_impl->m_view_independents.insert( weak_dependency_type( dep ) );
}

bool worksheet::is_view_independent( const shared_dependency_type& dep )
{
    return m_impl->m_view_independents.find( dep ) != m_impl->m_view_independents.end();
}

void worksheet::compute_view_independent( session& s )
{
    if ( m_impl->m_view_independents.empty() || s.cache().view_independents_done() ) {
        return;
    }

    calculation_context cc( s, s.selected().application()->calculation_settings() );
    std::set< weak_dependency_type > to_delete;
    for ( weak_dependency_set_type::const_iterator it = m_impl->m_view_independents.begin(), end_it = m_impl->m_view_independents.end();
            it != end_it; ++it ) {
        shared_dependency_type sd = it->lock();
        if ( sd ) {
            sd->value( cc );
        } else {
            to_delete.insert( *it );
        }
    }

    for ( weak_dependency_set_type::const_iterator it = to_delete.begin(), end_it = to_delete.end();
            it != end_it; ++it ) {
        m_impl->m_view_independents.erase( m_impl->m_view_independents.find( *it ) );
    }
    s.cache().view_independents_done( true );
}

worksheet::existing_cell_list_type worksheet::existing_cells() const
{
    return  m_impl->m_cell_manager.existing_cells();
}

void worksheet::name( const utf8_ci_string& new_name )
{
    if ( !hidden() ) {
        parent()->flag_changed();
    }
    identifiable_object::name( new_name );
}

boost::signal < void( const worksheet& ) > worksheet::on_global_before_delete;
