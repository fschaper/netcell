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

#include "cell_manager.hpp"

#include "wss/i_dependency.hpp"
#include "wss/server.hpp"
#include "wss/sleep.hpp"

#include "wss/lock_timeout_exception.hpp"
#include "wss/invalid_worksheet_exception.hpp"

#include "fill_operation.hpp"
#include "cell.hpp"
#include "named_formula.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

/*!
 * \brief
 * little helper, mostly for calculating the used range
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
struct cell_manager::cell_manager_helper : non_instantiable {
    static inline void add_position_to_container( const sheet_point& position, const shared_dependency_type& sd, cell_container_type& container, optional_sheet_range_type& used_range ) {
        container[ position.key() ] = sd;
        used_range.reset();
    }

    static inline void remove_position_from_used_range( const sheet_range& position, optional_sheet_range_type& used_range ) {
        if ( used_range ) {
            if ( used_range->lower_right().is_above_or_at_same_row( position.lower_right() )
                    || used_range->lower_right().is_right_of_or_at_same_column( position.lower_right() ) ) {
                used_range.reset();
            }
        }
    }

    static inline void remove_position_from_used_range( const sheet_point& position, optional_sheet_range_type& used_range ) {
        if ( used_range && ( used_range->lower_right().is_at_same_row( position ) || used_range->lower_right().is_at_same_column( position ) ) ) {
            used_range.reset();
        }
    }

    static inline void recalc_used_range_if_needed( const cell_container_type& container, optional_sheet_range_type& used_range ) {
        if ( !used_range && !container.empty() ) {

            sheet_point::integer_type rightmost_column = 0;
            sheet_point::integer_type bottom_row = 0;//sheet_point::row_from_key( container.rbegin()->first );

            for ( cell_container_type::const_iterator it = container.begin(), end_it = container.end(); it != end_it; ++it ) {
                const sheet_point::integer_type current_column = sheet_point::column_from_key( it->first );
                if ( rightmost_column < current_column ) {
                    rightmost_column = current_column;
                }
                const sheet_point::integer_type current_row = sheet_point::row_from_key( it->first );
                if ( bottom_row < current_row ) {
                    bottom_row = current_row;
                }
            }

            used_range = sheet_range( sheet_point( 0, 0 ), sheet_point( bottom_row, rightmost_column ) );
        }
    }
};

cell_manager::cell_manager( ::worksheet& ws )
    : m_mutex()
    , m_worksheet( ws )
    , m_dependency_manager( ws )
{}

cell_manager::~cell_manager()
{
    if ( server::instance().current_state() != server::state::running ) {
        return;
    }

    lock_type lock( m_mutex );
    for ( cell_container_type::const_iterator it = m_container.begin(), end_it = m_container.end(); it != end_it; ++it ) {
        //foreach( const cell_container_type::value_type & p, m_container ) {
#if defined(_DEBUG)
        sheet_point sp = sheet_point::from_key( ( *it ).first );
#endif // _DEBUG
        boost::shared_static_cast<cell>( ( *it ).second )->unload();
    }
}

shared_dependency_type cell_manager::create( const sheet_point& position )
{
    lock_type lock( m_mutex );
    return create( lock, position );
}

shared_dependency_type cell_manager::create( lock_type& lock, const sheet_point& position )
{
    cell_container_type::iterator it( m_container.find( position.key() ) );
    // in case the cell does not already exist, create it.
    if ( m_container.end() == it ) {
        // create a new cell at the target position
        shared_dependency_type shared_cell = cell::create( m_worksheet.shared_from_this(), position );
        // find all dependencies that have references which intersect with the new cells location
        // let B1=SUM(A:A). B1 now has a entry in the dependency manager which will cover A:A.
        // for every cell that intersects with the area A:A, connect the cell with B1.
        const locked_dependency_set_type& ds = m_dependency_manager.update_precedents_get_dependents( position, shared_cell );
        // connect the new cell with their dependencies.
        const dependency_set_type& dt = *( ds.lock() );
        for ( dependency_set_type::const_iterator itdt = dt.begin(), end_it = dt.end(); itdt != end_it; ++itdt ) {
            //foreach( const shared_dependency_type & sd, *( ds.lock() ) ) {
            // raw named formulas are never being connected to cells
            //TODO (fhofmann) check if this is right
            if ( ( *itdt )->type() == i_dependency::named_formula_type ) {
                if( ! boost::static_pointer_cast<named_formula>( *itdt )->is_relative() ) {
                    //if the name isn't relative, we didn't rewrite any opcodes, so we gotta connect the free formulas manually
                    boost::static_pointer_cast<named_formula>( *itdt )->register_wrappers_at_cell( shared_cell );
                }
            } else {
                shared_cell->register_dependent( *itdt );
            }
        }
        // add the new cell to the container and adjust the used range
        cell_manager_helper::add_position_to_container( position, shared_cell, m_container, m_used_range );

        // return the shared pointer.
        return shared_cell;
    }
    // the cell does already exist and we can return it directly.
    return it->second;
}

shared_dependency_type cell_manager::create_array_master( lock_type& lock, const sheet_range& r )
{
    const sheet_point master_position = r.upper_left();
    cell_container_type::iterator it( m_container.find( master_position.key() ) );
    // in case the cell does not already exist, create it.
    if ( m_container.end() == it ) {
        // create a new cell at the target position
        shared_dependency_type shared_cell = cell::create( m_worksheet.shared_from_this(), master_position );
        // find all dependencies that have references which intersect with the new cells location
        // let B1=SUM(A:A). B1 now has a entry in the dependency manager which will cover A:A.
        // for every cell that intersects with the area A:A, connect the cell with B1.
        const locked_dependency_set_type& ds = m_dependency_manager.update_precedents_get_dependents_for_array_master( r, shared_cell );
        // connect the new cell with their dependencies.
        // (fhofmann): we need to use a copy of the set here, because we are changing the set and run into crashes otherwise
        dependency_set_type dt = *( ds.lock() );
        for ( dependency_set_type::const_iterator itdt = dt.begin(), end_itdt = dt.end(); itdt != end_itdt; ++itdt ) {
            //foreach( const shared_dependency_type & sd, *( ds.lock() ) ) {
            // raw named formulas are never being connected to cells
            //TODO (fhofmann) check if this is right
            if ( ( *itdt )->type() == i_dependency::named_formula_type ) {
                if( ! boost::static_pointer_cast<named_formula>( *itdt )->is_relative() ) {
                    //if the name isn't relative, we didn't rewrite any opcodes, so we gotta connect the free formulas manually
                    boost::static_pointer_cast<named_formula>( *itdt )->register_wrappers_at_cell( shared_cell );
                }
            } else {
                shared_cell->register_dependent( *itdt );
            }
        }
        // add the new cell to the container and adjust the used range
        cell_manager_helper::add_position_to_container( master_position, shared_cell, m_container, m_used_range );

        // return the shared pointer.
        return shared_cell;
    }
    // the cell does already exist and we can return it directly.
    return it->second;
}

shared_dependency_type cell_manager::create_array_slave( lock_type& lock, const sheet_point& position, const shared_dependency_type& master_cell )
{
    cell_container_type::iterator it( m_container.find( position.key() ) );
    // in case the cell does not already exist, create it.
    if ( m_container.end() == it ) {
        // create a new cell at the target position
        shared_dependency_type shared_cell = cell::create( m_worksheet.shared_from_this(), position );
        // find all dependencies that have references which intersect with the new cells location
        // let B1=SUM(A:A). B1 now has a entry in the dependency manager which will cover A:A.
        // for every cell that intersects with the area A:A, connect the cell with B1.
        m_dependency_manager.update_precedents_get_dependents( position, shared_cell );
        // no need to connect the new cell with their dependencies, that was already done in the master cell

        // add the new cell to the container and adjust the used range
        cell_manager_helper::add_position_to_container( position, shared_cell, m_container, m_used_range );

        // return the shared pointer.
        return shared_cell;
    }
    // the cell does already exist, we have to move all dependents to the master cell.
    // (fhofmann): we need to use a copy of the set here, because we are changing the set and run into crashes otherwise
    dependency_set_type old_dependents( it->second->dependents() );
    for ( dependency_set_type::const_iterator itdt = old_dependents.begin(), end_itdt = old_dependents.end(); itdt != end_itdt; ++itdt ) {
        //foreach( const shared_dependency_type & sd, old_dependents ) {

        if ( ( *itdt )->type() == i_dependency::named_formula_type ) {
            if( ! boost::static_pointer_cast<named_formula>( *itdt )->is_relative() ) {
                //if the name isn't relative, we didn't rewrite any opcodes, so we gotta connect the free formulas manually
                boost::static_pointer_cast<named_formula>( *itdt )->unregister_wrappers_at_cell( it->second );
                boost::static_pointer_cast<named_formula>( *itdt )->register_wrappers_at_cell( master_cell );
            }
        } else {
            it->second->unregister_dependent( *itdt );
            master_cell->register_dependent( *itdt );
        }
    }
    return it->second;
}

/*!
 * \brief
 * move an array cell.
 * \detail
 * this is a mini version of move which will only move the array source to the arrays target!
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class cell_manager::perform_array_move
{
public:
    perform_array_move( cell_manager::lock_type& lock, const shared_worksheet_type& sw, cell_manager& target_cell_manager, const shared_dependency_type& master, const shared_dependency_array_type& slaves, range_lock::waiting_for_update_position_map_type& update_position_map )
        : m_worksheet( sw )
        , m_target_cell_manager( target_cell_manager )
        , m_master_cell( master )
        , m_slave_cells( slaves )
        , m_lock( lock )
        , m_waiting_for_update_position( update_position_map )
    {}

    void operator()( const sheet_point& source, const sheet_point& target ) {
        if ( m_master_cell->position() == source ) {
            m_target_cell_manager.internal_move_cell( m_lock, m_worksheet, m_master_cell, target );

            m_waiting_for_update_position.push_back( std::make_pair( m_master_cell, target ) );
        } else {
            shared_dependency_array_type::const_iterator it( std::find_if( m_slave_cells.begin(), m_slave_cells.end(), boost::bind( &i_dependency::position, _1 ) == source ) );
            assert( "error moving array formula, slave cell not found!" && it != m_slave_cells.end() );
            m_target_cell_manager.internal_move_cell( m_lock, m_worksheet, *it, target );
            m_waiting_for_update_position.push_back( std::make_pair( *it, target ) );
        }
    }

    static void do_initial_cleanup() {} //intentionally does nothing!
    static void do_postponed_stuff() {} //intentionally does nothing!

private:
    const shared_worksheet_type& m_worksheet;
    cell_manager& m_target_cell_manager;
    const shared_dependency_type& m_master_cell;
    const shared_dependency_array_type& m_slave_cells;
    cell_manager::lock_type& m_lock;
    range_lock::waiting_for_update_position_map_type& m_waiting_for_update_position;
};

shared_dependency_type cell_manager::move_array( shared_cell_type old_array_master, const sheet_range& source, const sheet_range& target, range_lock::waiting_for_update_position_map_type& update_position_map )
{

    lock_type lock( m_mutex );
    // get the source cell manager
    shared_worksheet_type sw = old_array_master->worksheet().lock();
    if ( ! sw ) {
        throw invalid_worksheet_exception();
    }

    m_array_manager.remove( source );

    if ( ! m_array_manager.add( target ) ) {
        throw can_not_change_part_of_an_array_exception();
    }
    shared_dependency_type old_master_dependency = boost::static_pointer_cast<i_dependency>( old_array_master );
    fill_operation fo( source, target );
    perform_array_move am( lock, sw, *this, old_master_dependency, old_array_master->get_slave_cells_if_array_master(), update_position_map );
    fo( am );
    return old_master_dependency;
}

shared_dependency_type cell_manager::create_array( const sheet_range& position )
{
    lock_type lock( m_mutex );
    if ( ! m_array_manager.add( position ) ) {
        throw can_not_change_part_of_an_array_exception();
    }

    shared_dependency_array_type cell_array;
    sheet_range::const_iterator it( position.begin() ), end( position.end() );
    shared_dependency_type array_master = create_array_master( lock, position );
    cell_array.push_back( array_master );
    ++it;//skip the master
    for ( ; it != end; ++it ) {
        cell_array.push_back( create_array_slave( lock, *it, array_master ) );
    }
    cell::initialize_array( position, cell_array );
    return cell_array[0];
}

void cell_manager::remove_array( const sheet_range& position )
{
    m_array_manager.remove( position );
}

shared_dependency_type cell_manager::get( const sheet_point& position )
{
    lock_type lock( m_mutex );
    cell_container_type::iterator it( m_container.find( position.key() ) );
    if ( m_container.end() != it ) {
        return it->second;
    }
    return shared_dependency_type();
}

void cell_manager::erase( lock_type& lock, session& s, const sheet_range& r )
{
    m_dependency_manager.erase( r );
    clear( lock, s, r );
}

void cell_manager::clear( lock_type&, session& s, const sheet_range& r )
{
    cell_manager_helper::remove_position_from_used_range( r, m_used_range );
    for ( sheet_range::const_iterator r_it = r.begin(), r_end_it = r.end(); r_it != r_end_it; ++r_it ) {
        cell_container_type::iterator it( m_container.find( r_it.key() ) );
        if ( m_container.end() != it ) {
            shared_cell_type shared_cell = boost::static_pointer_cast<cell>( it->second );
            const geometry::rectangle_type area_to_remove = shared_cell->is_master() ? geometry::rectangle_type( shared_cell->array_coverage() ) : geometry::rectangle_type( *r_it );
            shared_cell->unload();
            m_dependency_manager.erase_precedent( area_to_remove, it->second );
            m_container.erase( it );
        }
    }
}

void cell_manager::erase( session& s, const sheet_range& r )
{
    lock_type lock( m_mutex );
    if ( contains_partially_intersecting_array( r ) ) {
        throw can_not_change_part_of_an_array_exception();
    }
    erase( lock, s, r );
    m_array_manager.remove( r );
}

void cell_manager::clear( session& s, const sheet_range& r )
{
    lock_type lock( m_mutex );
    if ( contains_partially_intersecting_array( r ) ) {
        throw can_not_change_part_of_an_array_exception();
    }
    clear( lock, s, r );
    m_array_manager.remove( r );
}

void cell_manager::copy( session& s, const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, bool use_copy_move /* = false */, insert_shift_direction::type shift /* = insert_shift_direction::automatic */ )
{
    bool same_target_and_source_sheet = ( target_sheet.get() == &m_worksheet );
    if ( same_target_and_source_sheet && source_range.upper_left() == target_range.upper_left() ) {
        // if the copy operation has the same source and target, we have nothing to do.
        return;
    }

    bool could_lock_both_regions = true;
    unsigned int retry_count = 0;
    do {
        try {
            // prepare regional locks on the worksheets.
            range_lock source_lock( lock( source_range, lock::shared ) );
            sheet_range target_lock_range( ( target_range.coverage().count() < source_range.coverage().count() ) ? source_range.coverage().offset( target_range.upper_left() ) : target_range );
            range_lock target_lock( target_sheet->cells().lock( target_lock_range, lock::exclusive ) );

            if ( target_lock.contains_partially_intersecting_array() || ( source_lock.contains_partially_intersecting_array() && use_copy_move ) ) {
                throw can_not_change_part_of_an_array_exception();
            }
            const bool target_is_clone_sheet = target_sheet->hidden();

            source_lock.copy( s, target_lock, target_is_clone_sheet, use_copy_move );

        } catch ( const lock_timeout_exception& ) {
            // (fschaper) could not aquire at least one of the requested locks in due time.
            // both locks are now released. wait for a couple of milliseconds.
            could_lock_both_regions = false;
            utility::sleep( static_cast<unsigned int>( ( rand() + 1.0 ) * 100.0 ) );
        }
    } while ( !could_lock_both_regions && retry_count++ < 5 );

    if ( !could_lock_both_regions ) {
        // (fschaper) the operation did not succeed in acquiring both locks.
        // this hopefully never happens but report back to the caller now.
        throw lock_timeout_exception();
    }
}

bool check_array_move( range_lock& source_lock, range_lock& target_lock, const bool same_target_and_source_sheet )
{
    if ( same_target_and_source_sheet ) {
        return !source_lock.array_move_okay( target_lock.coverage() );
    }
    return source_lock.contains_partially_intersecting_array() || target_lock.contains_partially_intersecting_array();
}

void cell_manager::move( session& s, const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, copy_format_from::type format_from, insert_shift_direction::type shift )
{
    bool same_target_and_source_sheet = ( target_sheet.get() == &m_worksheet );
    if ( source_range == target_range && same_target_and_source_sheet ) {
        // if the copy operation has the same source and target, we have nothing to do.
        return;
    }



    bool could_lock_both_regions = true;
    unsigned int retry_count = 0;
    do {
        try {
            // (fschaper) prepare regional locks on the worksheets.
            const bool is_whole_column_or_row_operation = ( shift == insert_shift_direction::entire_column || shift == insert_shift_direction::entire_row );
            const optional_sheet_range_type used_sheet_range = used_range();
            if ( used_sheet_range && ( used_sheet_range->does_intersect( source_range ) || used_sheet_range->does_intersect( source_range.coverage().checked_offset( target_range.upper_left() ) ) ) ) {
                range_lock source_lock( lock( source_range, lock::exclusive ) );
                sheet_range target_lock_range( source_range.coverage().checked_offset( target_range.upper_left() ) );
                range_lock target_lock( target_sheet->cells().lock( target_lock_range, lock::exclusive ) );

                if ( check_array_move( source_lock, target_lock, same_target_and_source_sheet ) ) {
                    throw can_not_change_part_of_an_array_exception();
                }

                source_lock.move( s, target_lock );
            }
            const optional_sheet_range_type used_dependency_range = m_dependency_manager.used_range();
            if ( used_dependency_range && ( used_dependency_range->does_intersect( source_range ) || used_dependency_range->does_intersect( source_range.coverage().checked_offset( target_range.upper_left() ) ) ) ) {
                m_dependency_manager.move( source_range, target_range.upper_left(), target_sheet->cells(), is_whole_column_or_row_operation );
            }
        } catch ( const lock_timeout_exception& ) {
            // (fschaper) could not aquire on of the requested locks in due time.
            // both locks are now released. wait for a couple of milliseconds.
            could_lock_both_regions = false;
            utility::sleep( static_cast<unsigned int>( ( rand() + 1.0 ) * 100.0 ) );
        }
    } while ( !could_lock_both_regions && retry_count++ < 5 );

    if ( !could_lock_both_regions ) {
        // (fschaper) the operation did not succeed in aquire both locks.
        // this hopefully never happens but report back to the caller now.
        throw lock_timeout_exception();
    }
}

void cell_manager::erase( session& /* s */, const sheet_range& source_range, erase_shift_direction::type shift  )
{}

dependency_set_type cell_manager::dependents( const sheet_range& source_range )
{
    lock_type lock( m_mutex );
    dependency_set_type return_value;
    for ( sheet_range::const_iterator it = source_range.begin(), end_it = source_range.end(); it != end_it; ++it ) {
        //foreach( const sheet_point & sp, source_range ) {
        const dependency_set_type tmp( m_dependency_manager.query_dependents( *it ) );
        return_value.insert( tmp.begin(), tmp.end() );
    }
    return return_value;
}

shared_reference_type cell_manager::register_dependency( const shared_dependency_type& sd, const sheet_range& position, const bool inside_nf )
{
    lock_type lock( m_mutex );
    shared_reference_type return_value = range_reference::create( sd, position, m_dependency_manager.register_dependency( sd, position, inside_nf ) );
    fill_range( position, *range_reference_cast( return_value ).actualize()->lock() );
    return return_value;
}

void cell_manager::unregister_dependency( const shared_dependency_type& sd, const sheet_range& position )
{
    lock_type lock( m_mutex );
    m_dependency_manager.unregister_dependency( sd, position );
}

void cell_manager::fill_range( const sheet_range& area, dependency_set_type& sdr )
{
    sdr.clear();
    cell_container_type::const_iterator m_container_end = m_container.end();
    for ( sheet_range::const_iterator ait = area.begin(), end_ait = area.end(); ait != end_ait; ++ait ) {
        //foreach( const sheet_point & sp, area ) {
        cell_container_type::iterator it( m_container.find( sheet_point( *ait ).key() ) );
        if ( m_container_end != it ) {
            sdr.insert( it->second );
        }
    }
}

void cell_manager::dump( std::ostream& os ) const
{
    lock_type lock( m_mutex );
    m_dependency_manager.dump( os );
}

void cell_manager::release_lock( const shared_range_lock_keeper_type& lock )
{
    m_range_lock_handler.release( lock );
}

range_lock cell_manager::lock( const sheet_range& coverage, lock::type type )
{
    return range_lock( m_worksheet.shared_from_this(), m_range_lock_handler.aquire( coverage, type ) );
}

bool cell_manager::contains_array( const sheet_range& coverage ) const
{
    lock_type lock( m_mutex );
    return m_array_manager.contains_array( coverage );
}

bool cell_manager::contains_partially_intersecting_array( const sheet_range& coverage ) const
{
    lock_type lock( m_mutex );
    return m_array_manager.is_partially_intersecting( coverage );
}

bool cell_manager::array_move_okay( const sheet_range& source, const sheet_range& target ) const
{
    lock_type lock( m_mutex );
    return m_array_manager.array_move_okay( source, target );
}

optional_sheet_range_type cell_manager::used_range( bool include_unrealized_precedents ) const
{
    lock_type lock( m_mutex );

    cell_manager_helper::recalc_used_range_if_needed( m_container, m_used_range );

    if ( include_unrealized_precedents ) {
        const optional_sheet_range_type dependency_used_range = m_dependency_manager.used_range();
        if ( dependency_used_range ) {
            return m_used_range ? ( *m_used_range ).enclose( *dependency_used_range ) : dependency_used_range;
        }
    }

    return m_used_range;
}


void cell_manager::move_cell( session& s, const shared_dependency_type& sd, const sheet_point& position )
{
    lock_type lock( m_mutex );
    // get the source cell manager
    shared_worksheet_type sw = boost::shared_static_cast<cell>( sd )->worksheet().lock();
    if ( ! sw ) {
        throw invalid_worksheet_exception();
    }
    internal_move_cell( lock, sw, sd, position );
}

void cell_manager::internal_move_cell( lock_type& lock, const shared_worksheet_type& sw, const shared_dependency_type& sd, const sheet_point& position )
{
    // release the cell from the source manager.
    sw->cells().release( sd->position() );
    // assign the new worksheet to the cell
    boost::shared_static_cast<cell>( sd )->worksheet( m_worksheet.shared_from_this() );
    // store the new cell in the cell container
    cell_manager_helper::add_position_to_container( position, sd, m_container, m_used_range );
}

void cell_manager::release( const sheet_point& position )
{
    lock_type lock( m_mutex );
    m_container.erase( position.key() );
    m_used_range.reset();
}

void cell_manager::add_cell_move_node( const shared_dependency_node_type& element )
{
    lock_type lock( m_mutex );
    m_dependency_manager.add_cell_move_node( element );
}

void cell_manager::add_named_formula_move_node( const shared_dependency_node_type& element )
{
    lock_type lock( m_mutex );
    m_dependency_manager.add_named_formula_move_node( element );
}

shared_worksheet_type cell_manager::associated_worksheet() const
{
    return m_worksheet.shared_from_this();
}

rectangle_list_type cell_manager::array_list() const
{
    lock_type lock( m_mutex );
    return m_array_manager.list();
}

cell_manager::existing_cell_list_type cell_manager::existing_cells() const
{
    existing_cell_list_type return_value;

    {
        lock_type lock( m_mutex );

        return_value.reserve( m_container.size() );
        //put all positions in the list
        for ( cell_container_type::const_iterator it = m_container.begin(), end_it = m_container.end(); it != end_it; ++it ) {
            return_value.push_back( it->second->position() );
        }
    }

    //sort positions
    std::sort( return_value.begin(), return_value.end() );

    return return_value;
}
