/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
*  Predrag Malicevic <predrag.malicevic@develabs.com>
*/

#include "precompiled_header.hpp"
#include "SnapshotManager.hpp"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

SnapshotManager::Snapshot::Snapshot ( const sheet_range& coords, const unsigned long property_set, const variant& values, const unsigned short dimension_set,
                                      const sheet_layout_trait::sparse_value_range_type& col_widths, const sheet_layout_trait::sparse_value_range_type& row_heights, const sheet_point& used_range, const std::string& uid = "" )
    : coords( coords )
    , property_set( property_set )
    , values( values )
    , dimension_set( dimension_set )
    , col_widths( col_widths )
    , row_heights( row_heights )
    , used_range( used_range )
    , uid( uid )
{}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

SnapshotManager::snapshot_auto_type SnapshotManager::make_snapshot ( session& scx, const sheet_range& coords, const unsigned long property_set, const unsigned short dimension_set ) const
{
    shared_worksheet_type sheet = scx.selected().worksheet().lock();

    if ( !sheet ) {
        throw invalid_worksheet_exception();
    }

    get_server_query_command values_cmd( scx, coords, property_set );

    sheet_layout_trait::sparse_value_range_type col_widths, row_heights;

    if ( dimension_set & DimensionTypes::COLS ) {
        get_sparse_column_width_command col_widths_cmd( scx, sheet_layout_trait::line_type( 0, sheet_dimension::max_column ) );
        col_widths = execute_command<get_sparse_column_width_command>()( col_widths_cmd );
    }

    if ( dimension_set & DimensionTypes::ROWS ) {
        get_sparse_row_height_command row_heights_cmd( scx, sheet_layout_trait::line_type( 0, sheet_dimension::max_row ) );
        row_heights = execute_command<get_sparse_row_height_command>()( row_heights_cmd );
    }
    const optional_sheet_range_type used_range = sheet->used_range( used_range::all_extended );
    return snapshot_auto_type( new Snapshot( coords, property_set, execute_command<get_server_query_command>()( values_cmd ), dimension_set, col_widths, row_heights, used_range ? static_cast<sheet_point>( used_range->lower_right() ) : sheet_point( 0, 0 ) ) );
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

const std::string SnapshotManager::save_snapshot ( const std::string& session_uid, snapshot_auto_type snapshot, const unsigned short ttl, const std::string& snapshot_uid = "" )
{
    lock_t lock( m_mutex );

    snapshots_session_storage_t& sess_snapshots = m_snapshots_storage[session_uid];
    snapshots_list_t& snapshots_list = sess_snapshots.first;
    snapshots_map_t& snapshots_map = sess_snapshots.second;

    std::string uid;

    if ( snapshot_uid == "" ) {

        snapshot->uid = uid = boost::lexical_cast< std::string > ( boost::uuids::random_generator()() );

        snapshots_map.insert( snapshots_map_t::value_type( uid, snapshot.release() ) );
        snapshots_list.push_back( snapshot_uid_ttl_pair_t( uid, ttl ) );
    } else {
        snapshot->uid = uid = snapshot_uid;

        snapshots_map_t::iterator map_it = snapshots_map.find( uid );

        if ( map_it == snapshots_map.end() ) {
            snapshots_map.insert( snapshots_map_t::value_type( uid, snapshot.release() ) );
        } else {
            delete ( *map_it ).second;
            ( *map_it ).second = snapshot.release();
        }
    }

    LOG_UI_BACKEND_DEBUG( "session manager saved a snapshot for session " << session_uid );

    return uid;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

SnapshotManager::snapshot_auto_type SnapshotManager::get_snapshot ( const std::string& session_uid, const std::string& snapshot_uid = "" )
{
    lock_t lock( m_mutex );

    snapshots_storage_t::iterator sess_it;

    if ( ( sess_it = m_snapshots_storage.find( session_uid ) ) == m_snapshots_storage.end() ) {
        return snapshot_auto_type();
    }

    snapshots_session_storage_t& sess_snapshots = ( *sess_it ).second;
    snapshots_list_t& snapshots_list = sess_snapshots.first;
    snapshots_map_t& snapshots_map = sess_snapshots.second;

    snapshots_map_t::iterator map_it = snapshots_map.end(), map_it_end = map_it;

    if ( snapshot_uid == "" ) {
        while ( !snapshots_list.empty() ) {
            const snapshot_uid_ttl_pair_t uid_ttl_pair = snapshots_list.back();
            snapshots_list.pop_back();

            if ( ( map_it = snapshots_map.find( uid_ttl_pair.first ) ) != map_it_end ) {
                break;
            }
        }

        if ( map_it == map_it_end ) {
            return snapshot_auto_type();
        }

        snapshot_auto_type snapshot( ( *map_it ).second );
        snapshots_map.erase( map_it );

        return snapshot;
    }

    if ( ( map_it = snapshots_map.find( snapshot_uid ) ) == map_it_end ) {
        return snapshot_auto_type();
    }

    snapshot_auto_type snapshot( ( *map_it ).second );
    snapshots_map.erase( map_it );

    return snapshot;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void SnapshotManager::remove_snapshots ( const std::string& session_uid )
{
    lock_t lock( m_mutex );

    snapshots_storage_t::iterator sess_it;

    if ( ( sess_it = m_snapshots_storage.find( session_uid ) ) == m_snapshots_storage.end() ) {
        return;
    }

    snapshots_map_t& snapshots_map = ( *sess_it ).second.second;

    snapshots_map_t::iterator map_it = snapshots_map.begin(), map_it_end = snapshots_map.end();

    if ( map_it == map_it_end ) {
        return;
    }

    for ( ; map_it != map_it_end; ++map_it ) {
        delete ( *map_it ).second;
    }

    m_snapshots_storage.erase( sess_it );

    LOG_UI_BACKEND_DEBUG( "snapshot manager removed snapshots for session " << session_uid );
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

const std::string SnapshotManager::diff_snapshots ( session& scx, const std::string& session_uid, const std::string& snapshot_old_uid = "" )
{
    shared_worksheet_type sheet = scx.selected().worksheet().lock();

    if ( !sheet ) {
        throw invalid_worksheet_exception();
    }

    snapshot_auto_type snapshot_old = get_snapshot( session_uid, snapshot_old_uid );

    if ( snapshot_old.get() == NULL ) {
        return std::string( "" );
    }

    std::stringstream diff;

    get_server_query_command values_cmd( scx, snapshot_old->coords, snapshot_old->property_set );

    diff_values( scx, diff, snapshot_old->coords, snapshot_old->property_set, snapshot_old->values, execute_command<get_server_query_command>()( values_cmd ) );

    if ( snapshot_old->dimension_set & DimensionTypes::COLS ) {
        get_sparse_column_width_command col_widths_cmd( scx, sheet_layout_trait::line_type( 0, sheet_dimension::max_column ) );
        diff_dimensions( diff, DimensionTypes::COLS, snapshot_old->col_widths, execute_command<get_sparse_column_width_command>()( col_widths_cmd ) );
    }

    if ( snapshot_old->dimension_set & DimensionTypes::ROWS ) {
        get_sparse_row_height_command row_heights_cmd( scx, sheet_layout_trait::line_type( 0, sheet_dimension::max_row ) );
        diff_dimensions( diff, DimensionTypes::ROWS, snapshot_old->row_heights, execute_command<get_sparse_row_height_command>()( row_heights_cmd ) );
    }

    const optional_sheet_range_type used_range = sheet->used_range( used_range::all_extended );
    const sheet_point new_used_range = used_range ? used_range->lower_right() : sheet_point( 0, 0 );

    if ( new_used_range != snapshot_old->used_range ) {
        diff << ",[\"curn\"," << new_used_range.column() + 1 << "," <<  new_used_range.row() + 1 << ']';
    }

    return diff.str();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

const std::string SnapshotManager::diff_snapshots ( session& scx, const std::string& session_uid, const std::string& snapshot_old_uid = "", const std::string& snapshot_new_uid = "" )
{
    snapshot_auto_type snapshot_new = get_snapshot( session_uid, snapshot_new_uid ),
                       snapshot_old = get_snapshot( session_uid, snapshot_old_uid );

    if ( snapshot_new.get() == NULL || snapshot_old.get() == NULL ) {
        return std::string( "" );
    }

    const sheet_range& coords_new = snapshot_new->coords,
                       & coords_old = snapshot_old->coords;

    if ( snapshot_new->property_set != snapshot_old->property_set || snapshot_new->dimension_set != snapshot_old->dimension_set
            || coords_new.column_count() != coords_old.column_count() || coords_new.row_count() != coords_old.row_count() ) {
        return std::string( "" );
    }

    std::stringstream diff;

    diff_values( scx, diff, coords_new, snapshot_new->property_set, snapshot_old->values, snapshot_new->values );

    if ( snapshot_old->dimension_set & DimensionTypes::COLS ) {
        diff_dimensions( diff, DimensionTypes::COLS, snapshot_old->col_widths, snapshot_new->col_widths );
    }

    if ( snapshot_old->dimension_set & DimensionTypes::ROWS ) {
        diff_dimensions( diff, DimensionTypes::ROWS, snapshot_old->row_heights, snapshot_new->row_heights );
    }

    if ( snapshot_new->used_range != snapshot_old->used_range ) {
        diff << ",[\"curn\"," << snapshot_new->used_range.column() + 1 << "," <<  snapshot_new->used_range.row() + 1 << ']';
    }

    return diff.str();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void SnapshotManager::diff_values ( session& scx, std::stringstream& diff, const sheet_range& coords, const unsigned long property_set, const variant& vals_old, const variant& vals_new ) const
{
    if ( vals_old.array().size() != vals_new.array().size() ) {
        return;
    }

    std::stringstream regions, region, cell;

    unsigned x1 = coords.upper_left().column() + 1, x2 = coords.lower_right().column() + 1, y = coords.upper_left().row() + 1,
             x = x1, x_old = sheet_dimension::max_column + 2, y_old = sheet_dimension::max_row + 2,
             region_x = 0, region_y = 0, region_w = 0;

    for ( variant::variant_array_type::const_iterator it_old = vals_old.array().begin(), it_new = vals_new.array().begin(), it_end = vals_old.array().end(); it_old != it_end; ) {
        cell.str( "" );

        if ( property_set & get_server_query_command::query_value ) {
            if ( *it_new != *it_old ) {
                cell << "{\"v\":" << m_json_serializer(  *it_new );

                if ( ( *it_new ).type() != ( *it_old ).type() ) {
                    cell << ",\"t\":";

                    switch ( ( *it_new ).type() ) {
                        case variant::type_double:
                            cell << "\"n\"";
                            break;

                        case variant::type_bool:
                            cell << "\"b\"";
                            break;

                        case variant::type_string:
                            cell << ( ( *it_new ).string().size() && ( *it_new ).string().at( 0 ) == '<' ? "\"h\"" : "\"s\"" );
                            break;

                        case variant::type_empty:
                            cell << "\"e\"";
                            break;

                        default:
                            cell << "\"s\"";
                            break;
                    }
                } else if ( ( *it_new ).type() == variant::type_string ) {
                    bool new_is_h = ( *it_new ).string().size() && ( *it_new ).string().at( 0 ) == '<';

                    if ( new_is_h ^ ( ( *it_old ).string().size() && ( *it_old ).string().at( 0 ) == '<' ) ) {
                        cell << ",\"t\":" << ( new_is_h ? "\"h\"" : "\"s\"" );
                    }
                }
            }

            ++it_old;
            ++it_new;
        }

        if ( property_set & get_server_query_command::query_formula ) {
            ++it_old, ++it_new;
        }

        if ( property_set & get_server_query_command::query_style ) {
            if ( *it_new != *it_old ) {
                if ( ( *it_new ).type() == variant::type_empty ) {
                    cell << ",\"s\":\"\"";
                } else if ( ( *it_new ).string().size() ) {
                    cell << ",\"s\":" << m_json_serializer(  ( *it_new ).string() );
                } else if ( ( *it_old ).type() != variant::type_empty ) {
                    cell << ",\"s\":\"\"";
                }
            }

            ++it_old;
            ++it_new;
        }

        if ( property_set & get_server_query_command::query_formula_where_exists ) {
            if ( *it_new != *it_old ) {
                cell << ",\"f\":" << ( ( *it_new ).type() != variant::type_empty ? m_json_serializer(  ( *it_new ).string() ) : "\"\"" );
            }

            ++it_old;
            ++it_new;
        }

        if ( property_set & get_server_query_command::query_attribute ) {
            if ( *it_new != *it_old ) {
                if ( ( *it_new ).type() == variant::type_empty ) {
                    cell << ",\"a\":\"\"";
                } else if ( ( *it_new ).string().size() ) {
                    cell << ",\"a\":" << ( *it_new ).string();
                } else if ( ( *it_old ).type() != variant::type_empty ) {
                    cell << ",\"a\":\"\"";
                }
            }

            ++it_old;
            ++it_new;
        }

        if ( property_set & get_server_query_command::query_dimensions ) {
            ++it_old, ++it_new;
        }

        if ( property_set & get_server_query_command::query_formatted_value ) {
            if ( *it_new != *it_old ) {
                if ( ( *it_new ).type() == variant::type_empty ) {
                    cell << ",\"l\":\"\"";
                } else if ( ( *it_new ).string().size() ) {
                    cell << ",\"l\":" << m_json_serializer(  ( *it_new ).string() );
                } else if ( ( *it_old ).type() != variant::type_empty ) {
                    cell << ",\"l\":\"\"";
                }
            }

            ++it_old;
            ++it_new;
        }

        if ( property_set & get_server_query_command::query_format ) {
            if ( *it_new != *it_old ) {
                if ( ( *it_new ).type() == variant::type_empty ) {
                    cell << ",\"o\":\"\"";
                } else if ( ( *it_new ).string().size() ) {
                    cell << ",\"o\":" << m_json_serializer(  ( *it_new ).string() );
                } else if ( ( *it_old ).type() != variant::type_empty ) {
                    cell << ",\"o\":\"\"";
                }
            }

            ++it_old;
            ++it_new;
        }

        if ( property_set & get_server_query_command::query_merge ) {
            if ( *it_new != *it_old ) {
                cell << ",\"m\":" << ( ( *it_new ).type() != variant::type_empty ? m_json_serializer(  ( *it_new ).array() ) : "\"\"" );
            }

            ++it_old;
            ++it_new;
        }

        if ( property_set & get_server_query_command::query_formula_with_named_ranges ) {
            if ( *it_new != *it_old ) {
                cell << ",\"n\":" << ( ( *it_new ).type() != variant::type_empty ? m_json_serializer(  ( *it_new ).array() ) : "\"\"" );
            }

            ++it_old;
            ++it_new;
        }

        if ( property_set & get_server_query_command::query_lock ) {
            if ( *it_new != *it_old ) {
                if ( ( *it_new ).type() == variant::type_empty ) {
                    cell << ",\"k\":true";
                } else if ( !( *it_new ).numeric() ) {
                    cell << ",\"k\":false";
                } else if ( ( *it_old ).type() != variant::type_empty ) {
                    cell << ",\"k\":true";
                }
            }

            ++it_old;
            ++it_new;
        }

        if ( cell.str().size() ) {
            cell << '}';

            cell.seekp( 0, std::ios_base::beg ) << '{';

            if ( y == y_old && x == x_old + 1 && ( region_w == 0 || region_w > x - region_x ) ) {
                region << "," << cell.rdbuf();
            } else if ( y == y_old + 1 && x == region_x && ( region_w == 0 || x_old == region_x + region_w - 1 ) ) {
                if ( region_w == 0 ) {
                    region_w = x_old - x + 1;
                }

                region << "," << cell.rdbuf();
            } else {
                if ( region.str().size() ) {
                    regions << ",[" << region_x << "," << region_y << "," << region_w << "," << region.rdbuf() << ']';
                    region.str( "" );
                }

                region_x = x;
                region_y = y;
                region_w = 0;
                region << cell.rdbuf();
            }

            x_old = x;

            if ( y != y_old ) {
                y_old = y;
            }
        }

        if ( ++x > x2 ) {
            x = x1;
            ++y;
        }
    }

    if ( region.str().size() ) {
        regions << ",[" << region_x << "," << region_y << "," << region_w << "," << region.rdbuf() << ']';
    }

    if ( regions.str().size() ) {
        diff << ",[\"crgn\",{\"cm\":true}" << regions.str() << ']';
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void SnapshotManager::diff_dimensions ( std::stringstream& diff, const DimensionTypes::Type dims_type, const sheet_layout_trait::sparse_value_range_type& dims_old, const sheet_layout_trait::sparse_value_range_type& dims_new ) const
{
    std::stringstream ccr, vals;

    const unsigned idx_max = dims_type == DimensionTypes::COLS ? sheet_dimension::max_column + 1 : sheet_dimension::max_row + 1;

    unsigned idx_old = idx_max, idx_new = idx_max, idx = 0,
             val_old = 0, val_new = 0,
             from = 0, to = 0;

    long val = 0, val_last = 0;

    bool next_new = true, next_old = true,
         same = false,
         not1st = false;

    unsigned short cond = 2;

    for ( sheet_layout_trait::sparse_value_range_type::const_iterator it_old = dims_old.begin(), it_new = dims_new.begin(), it_old_end = dims_old.end(), it_new_end = dims_new.end(); cond; ) {
        if ( next_new ) {
            if ( it_new != it_new_end ) {
                idx_new = *it_new;
                ++it_new;
                val_new = *it_new;
                ++it_new;
            } else {
                idx_new = idx_max;
                val_new = 0;
                --cond;
            }

            next_new = false;
        }

        if ( next_old ) {
            if ( it_old != it_old_end ) {
                idx_old = *it_old;
                ++it_old;
                val_old = *it_old;
                ++it_old;
            } else {
                idx_old = idx_max;
                val_old = 0;
                --cond;
            }

            next_old = false;
        }

        if ( idx_new < idx_old ) {
            next_new = true;
            idx = idx_new;
            val = val_new;
        } else if ( idx_new > idx_old ) {
            next_old = true;
            idx = idx_old;
            val = -1;
        } else {
            next_new = true;
            next_old = true;

            if ( val_new == val_old ) {
                continue;
            } else {
                idx = idx_new;
                val = val_new;
            }
        }

        if ( not1st && idx == to + 1 ) {
            ++to;
            vals << ',' << val;

            if ( same && val != val_last ) {
                same = false;
            }
        } else {
            if ( not1st ) {
                ccr << ",[" << ++from << ',' << ++to;

                if ( same ) {
                    ccr << ',' << val_last << ']';
                } else {
                    ccr << vals.str() << ']';
                }
            } else {
                not1st = true;
            }

            from = to = idx;

            vals.str( "" );
            vals << ',' << val;

            same = true;
            val_last = val;
        }
    }

    if ( not1st ) {
        ccr << ",[" << ++from << ',' << ++to;

        if ( same ) {
            ccr << ',' << val_last << ']';
        } else {
            ccr << vals.str() << ']';
        }
    }

    if ( ccr.str().size() ) {
        diff << ",[\"ccr\"," << ( dims_type - 1 ) << ccr.str() << ']';
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void SnapshotManager::gc_startup ()
{
    if ( m_gc_state == State::HALTED ) {
        boost::thread::thread( boost::bind( &SnapshotManager::gc_run, this ) );
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool SnapshotManager::gc_shutdown ()
{
    if ( m_gc_state == State::RUNNING ) {
        LOG_UI_BACKEND_INFO( "snapshot manager gc shutting down ..." );
        m_gc_state = State::SHUTTING_DOWN;

        // notify the gc_start function that we're stopping now
        m_wait_condvar.notify_all();
    }

    return m_gc_state == State::HALTED;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool SnapshotManager::gc_is_running () const
{
    return m_gc_state == State::RUNNING;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool SnapshotManager::gc_is_shutting_down () const
{
    return m_gc_state == State::SHUTTING_DOWN;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool SnapshotManager::gc_is_halted () const
{
    return m_gc_state == State::HALTED;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void SnapshotManager::gc_set_interval ( const unsigned interval )
{
    m_gc_interval = interval;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void SnapshotManager::gc_run ()
{
    name_thread( "ui_backend snapshot manager gc" );

    m_gc_state = State::RUNNING;

    while ( m_gc_state == State::RUNNING ) {
        boost::xtime xt;
        boost::xtime_get( &xt, boost::TIME_UTC );
        xt.sec += m_gc_interval;

        lock_t wait_lock( m_wait_mutex );
        m_wait_condvar.timed_wait( wait_lock, xt );

        if ( m_gc_state != State::RUNNING ) {
            break;
        }

        LOG_UI_BACKEND_DEBUG( "snapshot manager gc woke up" );

        unsigned long count = 0;

        {
            lock_t lock( m_mutex );

            for ( snapshots_storage_t::iterator sess_it = m_snapshots_storage.begin(); sess_it != m_snapshots_storage.end(); ) {
                snapshots_session_storage_t& sess_snapshots = ( *sess_it ).second;
                snapshots_list_t& snapshots_list = sess_snapshots.first;
                snapshots_map_t& snapshots_map = sess_snapshots.second;

                snapshots_map_t::iterator map_it;

                for ( snapshots_list_t::iterator list_it = snapshots_list.begin(); list_it != snapshots_list.end(); ) {
                    snapshot_uid_ttl_pair_t& uid_ttl_pair = *list_it;

                    if ( !uid_ttl_pair.second || --uid_ttl_pair.second ) {
                        ++list_it;
                        continue;
                    }

                    if ( ( map_it = snapshots_map.find( uid_ttl_pair.first ) ) != snapshots_map.end() ) {
                        delete ( *map_it ).second;
                        snapshots_map.erase( map_it );
                    }

                    snapshots_list.erase( list_it++ );

                    ++count;
                }

                if ( snapshots_list.empty() && snapshots_map.empty() ) {
                    m_snapshots_storage.erase( sess_it++ );
                } else {
                    ++sess_it;
                }
            }
        }

        LOG_UI_BACKEND_DEBUG( "snapshot manager gc removed " << count << " snapshot(s)" );
    }

    m_gc_state = State::HALTED;
    LOG_UI_BACKEND_INFO( "snapshot manager gc halted" );
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

SnapshotManager::SnapshotManager ()
    : m_mutex()
    , m_wait_mutex()
    , m_wait_condvar()
    , m_gc_state( State::HALTED )
    , m_gc_interval( 300 )
    , m_json_serializer()
    , m_snapshots_storage()
{}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

