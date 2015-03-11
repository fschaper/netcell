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
#include "wss/range_lock.hpp"
#include "wss/object_not_found_exception.hpp"
#include "wss/i_dependency.hpp"
#include "wss/worksheet.hpp"
#include "fill_operation.hpp"
#include "cell_manager.hpp"
#include "cell.hpp"

//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * copy cells from source to target region.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class range_lock::perform_copy
{
public:
    perform_copy( session& s, range_lock& m_source_region, range_lock& m_target_region, const bool is_copy_to_clone_sheet, const bool use_copy_move )
        : m_session( s )
        , m_source_region( m_source_region )
        , m_target_region( m_target_region )
        , m_use_copy_move( use_copy_move )
        , m_is_copy_to_clone_sheet( is_copy_to_clone_sheet ) {}

    void operator()( const sheet_point& source, const sheet_point& target ) {
        shared_dependency_type source_cell( m_source_region.get( source ) );
        if ( source_cell ) {

            const shared_cell_type& sc = boost::shared_static_cast<cell>( source_cell );

            if ( !source_cell->is_array() ) {
                shared_dependency_type target_cell( m_target_region.create( target ) );
                shared_cell_type tc = boost::shared_static_cast<cell>( target_cell );
                // only copy regular cells
                sc->copy( *tc, m_is_copy_to_clone_sheet, m_use_copy_move, m_source_region.coverage() );
            } else if ( source_cell->array_coverage().intersection( m_source_region.coverage() ).upper_left() == source_cell->position() ) {
                // handling of array cells.
                shared_dependency_type a_target_cell(
                    m_target_region.create_array(
                        source_cell->array_coverage().intersection( m_source_region.coverage() ).offset(
                            source_cell->position().distance( target )
                        )
                    )
                );
                shared_cell_type tc = boost::shared_static_cast<cell>( a_target_cell );
                sc->copy( *tc, m_is_copy_to_clone_sheet, m_use_copy_move, m_source_region.coverage() );
            }
        } else {
            m_target_region.clear( m_session, target );
        }
    }

    void do_initial_cleanup() {} //intentionally does nothing!
    void do_postponed_stuff() {} //intentionally does nothing!

private:
    session& m_session;
    range_lock& m_source_region;
    range_lock& m_target_region;
    const bool m_use_copy_move;
    const bool m_is_copy_to_clone_sheet;
};

/*!
 * \brief
 * perform cell move operation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class range_lock::perform_move
{
    typedef std::list<sheet_range> range_list_type;

public:
    typedef range_lock::waiting_for_update_position_map_type waiting_for_update_position_map_type;
    perform_move( session& s, range_lock& m_source_region, range_lock& m_target_region )
        : m_session( s )
        , m_source_region( m_source_region )
        , m_target_region( m_target_region ) {}

    void do_initial_cleanup() {
        foreach( const sheet_range & r, m_target_region.coverage().cut( m_source_region.coverage() ) ) {
            m_target_region.erase( m_session, r );
        }
    }

    static inline void update_position( const waiting_for_update_position_map_type::value_type& v ) {
        boost::shared_static_cast<cell>( v.first )->update_position( v.second );
    }
    void do_postponed_stuff() {
        std::for_each( m_waiting_for_update_position.begin(), m_waiting_for_update_position.end(), boost::bind( &update_position, _1 ) );
    }

    void operator()( const sheet_point& source, const sheet_point& target ) {
        shared_dependency_type source_cell( m_source_region.get( source ) );
        if ( source_cell && !is_done_by_array_move_already( source, m_moved_array_cells ) ) {

            shared_cell_type sc = boost::static_pointer_cast<cell>( source_cell );
            shared_dependency_type target_cell( m_target_region.create( target ) );
            shared_cell_type tc = boost::static_pointer_cast<cell>( target_cell );

            if ( !source_cell->is_array() ) {
                // move regular cells
                m_target_region.move_cell( m_session, source_cell, target );
                m_waiting_for_update_position.push_back( std::make_pair( source_cell, target ) );
            } else {
                // handling of array cells.
                shared_dependency_type master_dependency;
                if ( sc->is_master() ) { //only move the master!
                    master_dependency = source_cell;
                    shared_cell_type master_cell = boost::static_pointer_cast<cell>( master_dependency );
                    const sheet_range source_array_range = sc->array_coverage();
                    const sheet_range target_array_range = source_array_range.offset( m_source_region.coverage().distance( m_target_region.coverage() ) );

                    shared_dependency_type a_target_cell( m_target_region.move_array( sc, source_array_range, target_array_range, m_waiting_for_update_position ) );


                    if ( source_array_range.does_intersect( target_array_range ) ) {
                        foreach( const sheet_range & tmp_range, source_array_range.cut( target_array_range ) ) {
                            m_source_region.clear( m_session, tmp_range );
                        }
                    } else {
                        m_source_region.clear( m_session, source_array_range );
                    }

                    //array source and target are done! we can safely ignore them now!
                    m_moved_array_cells.push_back( source_array_range );
                    m_moved_array_cells.push_back( target_array_range );
                }
            }
        }
    }

private:
    static inline bool is_done_by_array_move_already( const sheet_point& current, const range_list_type& ranges_to_skip ) {
        if ( !ranges_to_skip.empty() ) {
            for ( range_list_type::const_iterator it = ranges_to_skip.begin(), end_it = ranges_to_skip.end(); it != end_it; ++it ) {
                if ( it->covers( current ) ) {
                    return true;
                }
            }
        }
        return false;
    }

    session& m_session;
    range_lock& m_source_region;
    range_lock& m_target_region;
    range_list_type m_moved_array_cells;

    waiting_for_update_position_map_type m_waiting_for_update_position;
};

//////////////////////////////////////////////////////////////////////////

range_lock::range_lock( weak_worksheet_type ws, const shared_range_lock_keeper_type& lock )
    : m_manager( ws )
    , m_range_lock( lock )
{}

range_lock::range_lock( const range_lock& other )
    : m_manager( other.m_manager )
    , m_range_lock( other.m_range_lock )
{}

range_lock::~range_lock()
{
    shared_worksheet_type sw( m_manager.guardian_object().lock() );
    if ( sw && m_range_lock.use_count() < 3 ) {
        m_manager->cells().release_lock( m_range_lock );
    }
}

lock::type range_lock::type() const
{
    return m_range_lock->type();
}

const sheet_range& range_lock::coverage() const
{
    return m_range_lock->coverage();
}

bool range_lock::contains_partially_intersecting_array() const
{
    return m_manager->cells().contains_partially_intersecting_array( coverage() );
}


bool range_lock::array_move_okay( const sheet_range& target_range ) const
{
    return m_manager->cells().array_move_okay( coverage(), target_range );
}


bool range_lock::contains_array() const
{
    return m_manager->cells().contains_array( m_range_lock->coverage() );
}

dependency_set_type range_lock::dependents()
{
    return m_manager->cells().dependents( m_range_lock->coverage() );
}

shared_dependency_type range_lock::create( const sheet_point& position )
{
    assert( "need an exclusive lock to create cells!" && type() == lock::exclusive );
    assert( "position need be inside the locked range" && m_range_lock->coverage().covers( static_cast<geometry::point>( position ) ) );

    return m_manager->cells().create( position );
}

shared_dependency_type range_lock::create_array()
{
    return create_array( m_range_lock->coverage() );
}

shared_dependency_type range_lock::create_array( const sheet_range& position )
{
    assert( "need an exclusive lock to create array cells!" && type() == lock::exclusive );

    return m_manager->cells().create_array( position );
}

shared_dependency_type range_lock::move_array( shared_cell_type old_array_master, const sheet_range& source, const sheet_range& target, waiting_for_update_position_map_type& update_position_map )
{
    assert( "need an exclusive lock to move array cells!" && type() == lock::exclusive );

    return m_manager->cells().move_array( old_array_master, source, target, update_position_map );
}

void range_lock::remove_array( const sheet_range& position )
{
    assert( "need an exclusive lock to remove array cells!" && type() == lock::exclusive );

    return m_manager->cells().remove_array( position );
}

shared_dependency_type range_lock::get( const sheet_point& position )
{
    return m_manager->cells().get( position );
}

void range_lock::erase( session& s )
{
    assert( "need an exclusive lock to erase cells!" && type() == lock::exclusive );

    return m_manager->cells().erase( s, m_range_lock->coverage() );
}

void range_lock::erase( session& s, const sheet_point& position )
{
    assert( "need an exclusive lock to erase cells!" && type() == lock::exclusive );

    return m_manager->cells().erase( s, position );
}

void range_lock::erase( session& s, const sheet_range& position )
{
    assert( "need an exclusive lock to erase cells!" && type() == lock::exclusive );

    return m_manager->cells().erase( s, position );
}

void range_lock::clear( session& s )
{
    assert( "need an exclusive lock to clear cells!" && type() == lock::exclusive );

    return m_manager->cells().clear( s, m_range_lock->coverage() );
}

void range_lock::clear( session& s, const sheet_point& position )
{
    assert( "need an exclusive lock to clear cells!" && type() == lock::exclusive );

    return m_manager->cells().clear( s, position );
}

void range_lock::clear( session& s, const sheet_range& position )
{
    assert( "need an exclusive lock to clear cells!" && type() == lock::exclusive );

    return m_manager->cells().clear( s, position );
}

void range_lock::copy( session& s, range_lock& target, bool target_is_clone_sheet, bool use_copy_move )
{
    assert( "need an exclusive lock to move cells!" && target.type() == lock::exclusive );
    fill_operation fo( coverage(), target.coverage() );
    perform_copy pc( s, *this, target, target_is_clone_sheet, use_copy_move );
    fo( pc );
}

void range_lock::move( session& s, range_lock& target )
{
    assert( "need an exclusive lock to move cells!" && type() == lock::exclusive );
    fill_operation fo( coverage(), target.coverage() );
    perform_move pm( s, *this, target );
    fo( pm );
}

void range_lock::move_cell( session& s, const shared_dependency_type& sd, const sheet_point& position )
{
    assert( "need an exclusive lock to move cells!" && type() == lock::exclusive );
    m_manager->cells().move_cell( s, sd, position );
}
