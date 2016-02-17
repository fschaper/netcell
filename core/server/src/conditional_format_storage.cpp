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
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/
#include "precompiled_header.hpp"
#include "conditional_format_storage.hpp"

#include <wss/workbook.hpp>
#include <wss/style_set.hpp>
#include "wss/rectangle.hpp"
#include "core_logging.hpp"

#include "conditional_format_locked_storage.hpp"

#include "conditional_format_rank.hpp"
#include "conditional_format_rule.hpp"
#include "conditional_format_utils.hpp"
#include "conditional_format_callbacks.hpp"
#include "conditional_format_style_unlock_type.hpp"
#include "wss/insert_from_temporary.hpp"
#include "wss/variant_conversion_exception.hpp"
#include "conditional_format_affected_range_list.hpp"
#include "copy_fill_iterator.hpp"

#ifdef _DEBUG
//#define TRACE_CORRECTNESS_OF_CF 1
#endif // _DEBUG

#define my_for_loop_start(it_type,it,end_it,container) for(it_type it = (container).begin(), end_it = (container).end(); it != end_it; ++it)

namespace cf
{
    struct conditional_format_reference : boost::noncopyable {
        conditional_format_reference( const shared_conditional_format_rule_type& r, const internal_lookup_id_type i )
            : rule( r )
            , format_style_border( new format_style_unlock_type() )
            , id( i ) {
#ifdef TRACE_CORRECTNESS_OF_CF
            LOG_CORE_DEBUG( ">>>>> NEW CF REFERENCE: id is: " << id );

#endif // TRACE_CORRECTNESS_OF_CF
        }

        ~conditional_format_reference() {
#ifdef TRACE_CORRECTNESS_OF_CF
            LOG_CORE_DEBUG( ">>>>> REMOVED CF REFERENCE: id is: " << id );
            if ( rule.use_count() > 1 ) {
                LOG_CORE_DEBUG( ">>>>> Rule is still in use!!" );
            }
#endif // TRACE_CORRECTNESS_OF_CF
        }


        shared_conditional_format_rule_type rule;
        shared_format_style_unlock_type format_style_border;
        internal_lookup_id_type id;

        inline const bool query_type_set( const conditional_format_manager::conditional_format_query_type q_type ) const {
            switch ( q_type ) {
                case conditional_format_manager::query_conditional_format_all:
                    return true;
                case conditional_format_manager::query_conditional_format_style:
                    return format_style_border->style;
                case conditional_format_manager::query_conditional_format_format:
                    return format_style_border->format;
                case conditional_format_manager::query_conditional_format_lock:
                    return format_style_border->unlocked;
                default:
                    assert( !"query for wrong type of cf" );
            }
            //to avoid VC++ 2010 warning about not all control paths returning a value
            return false;
        }
    };


#ifdef TRACE_CORRECTNESS_OF_CF
    struct conditional_format_check_callback {
        conditional_format_check_callback( const conditional_format_storage::lookup_map_type& m ) {
            foreach( const conditional_format_storage::lookup_map_type::value_type & n, m ) {
                check_set.insert( n.first );
            }
        }
        inline bool operator()( const rectangle_type& r, const internal_lookup_id_type id ) const {
            check_set.erase( id );
            return true;
        }

        mutable std::set<internal_lookup_id_type> check_set;
    };
#endif // _DEBUG

    inline void do_check( const conditional_format_storage::lookup_map_type& m, conditional_format_storage::r_container_type& m_rect_container )
    {
#ifdef TRACE_CORRECTNESS_OF_CF
        if ( m_rect_container.used_range() ) {
            conditional_format_check_callback cb( m );
            m_rect_container.query( *m_rect_container.used_range(), cb );
            if ( cb.check_set.empty() ) {
                LOG_CORE_DEBUG( ">>>>> ALL COVERED!" );
            } else {
                LOG_CORE_ERROR( ">>>>> NOT ALL COVERED!" );
            }
        }
#endif // _DEBUG
    }

    conditional_format_storage::conditional_format_storage( conditional_format_manager& m )
        : m_manager( m )
        , m_counter()
        , m_ranks( new conditional_format_rank() )
    {}

    conditional_format_storage::~conditional_format_storage() {}

    struct conditional_format_storage::cache_struct {
        cache_struct( const sheet_range& r ) : range( r ) {}
        const sheet_range range;
        cf_vec_type format_style_vec;
        // internal_id_set_type ids;
    };


    //TODO refacture this function!!
    bool conditional_format_storage::fill_cache( session& s, const all_ids_plus_cell_ids_type& ids_vec, const conditional_format_storage::conditional_format_query_type query_type, const sheet_range& range )
    {
        //cache a few values before the calculation starts:
        id_affected_range_map_type id_range_map( get_affected_ranges( ids_vec.first ) );
        if ( id_range_map.empty() ) {
            return false;
        }
        bool no_match = true;
        m_cache.reset( new cache_struct( range ) );
        cf_vec_type& format_style_vec =  m_cache->format_style_vec;
        //const format_style_unlock_vec_type::mapping_type& format_style_vec_direct =  format_style_vec.direct();
        //format_style_vec.resize( range.count() );
        cf_vec_type::size_type idx = 0;
        geometry::rectangle_iterator it( range.begin() ), end_it( range.end() ); //lets check the whole range
        for ( ; it != end_it; ++it, ++idx ) {
            my_for_loop_start( internal_id_list_vec_type::const_iterator, ids, ids_end, ids_vec.second ) {
                assert( it != end_it && "this should never happen :P - just kidding, heres the message: range doesn't fit returned size" );
                bool do_clone = false;
                bool stop_if_true_found = false;
                my_for_loop_start( internal_id_list_type::const_iterator, i, i_end, *ids ) {
                    //check for every position if the value returned is true
                    const conditional_format_storage::shared_conditional_format_reference_type& r = get( *i );
                    const sheet_point current_position = ( *it );
                    try {
                        const id_affected_range_map_type::const_iterator id_range_map_it( id_range_map.find( *i ) );
                        if ( id_range_map_it != id_range_map.end() ) {
                            my_for_loop_start( sheet_range::rectangles_type::const_iterator, current_rect, rects_end, id_range_map_it->second ) {
                                if ( current_rect->covers( current_position ) && r->rule->does_match( s, current_position, id_range_map_it->second ) ) {
                                    no_match = false;
                                    cf_vec_type::const_iterator direct_it = format_style_vec.find( idx );
                                    if ( direct_it == format_style_vec.end() ) {
                                        format_style_vec[idx] = r->format_style_border;
                                        do_clone = true;
                                    } else {
                                        assert( "uninitialized pointer in format style vec in on cf recalculation" && direct_it->second );
                                        if ( do_clone ) {
                                            shared_format_style_unlock_type tmp = direct_it->second->clone();
                                            tmp->combine( r->format_style_border );
                                            format_style_vec[idx] = tmp;
                                            do_clone = false;
                                        } else {
                                            direct_it->second->combine( r->format_style_border );
                                        }
                                    }
                                    if ( r->rule->stop_if_true() && r->query_type_set( query_type ) ) { //stop here, we're done!
                                        stop_if_true_found = true;
                                        break;
                                    }
                                }
                            }
                        }
                    } catch ( const variant_conversion_exception& ) {}
                    if ( stop_if_true_found ) {
                        break;
                    }
                }
                if ( stop_if_true_found ) {
                    break;
                }
            }
        }
        if ( no_match ) {
            format_style_vec.clear();
            return false;
        }
        return true;
    }

    rectangle_list_type conditional_format_storage::get_external_affected_ranges( const conditional_format_lookup_id_type id )
    {
        using namespace boost::assign;
        rectangle_list_type return_val;
        const internal_id_set_type& ids = m_external_id_lookup[id];
        my_for_loop_start( internal_id_set_type::const_iterator, it, end_it, ids ) {
            sheet_range::rectangles_type tmp_val( get_affected_range( *it ) );
            return_val.insert( return_val.end(), tmp_val.begin(), tmp_val.end() );
        }
        return return_val;
    }

    sheet_range::rectangles_type conditional_format_storage::get_affected_range( const internal_lookup_id_type id )
    {
        sheet_range::rectangles_type return_value;
        conditional_format_affected_range_lookup_callback c( return_value, id );
        r_container_type::optional_rectangle_type covered_range = m_rect_container.used_range();
        if ( covered_range ) {
            m_rect_container.query( *covered_range, c );
        }
        return return_value;
    }

    id_affected_range_map_type conditional_format_storage::get_affected_ranges( const internal_id_set_type& ids )
    {
        id_affected_range_map_type return_val;
        my_for_loop_start( internal_id_set_type::const_iterator, it, end_it, ids ) {
            return_val[*it] = get_affected_range( *it );
        }
        return return_val;
    }

    all_ids_plus_cell_ids_type conditional_format_storage::sorted_ids_plus_cell_lookup( const sheet_range& r )
    {
        internal_id_list_vec_type lookup_vec;
        internal_id_set_type id_set( ids( r ) );
        if ( !id_set.empty() ) {
            lookup_vec.push_back( m_ranks->sort( id_set ) );
        }
        return all_ids_plus_cell_ids_type( id_set, lookup_vec );
    }

    internal_id_set_type conditional_format_storage::ids( const sheet_range& r )
    {
        internal_id_set_type id_set;
        conditional_format_id_lookup_callback c( id_set );
        r_container_type::optional_rectangle_type covered_range = m_rect_container.used_range();
        if ( covered_range && covered_range->does_intersect( r ) ) {
            m_rect_container.query( r, c );
        }
        return id_set;
    }

    internal_id_set_type conditional_format_storage::ids( const sheet_range::rectangles_type& ranges )
    {
        internal_id_set_type id_set;
        if ( ranges.empty() ) {
            const_iterator it( m_lookup_map.begin() ), end_it( m_lookup_map.end() );
            for ( ; it != end_it; ++it ) {
                id_set.insert( it->first );
            }
        } else {
            my_for_loop_start( sheet_range::rectangles_type::const_iterator, r, end_r, ranges ) {
                internal_id_set_type tmp_id_set = ids( *r );
                id_set.insert( tmp_id_set.begin(), tmp_id_set.end() );

            }
        }
        return id_set;
    }

    const conditional_format_storage::shared_conditional_format_reference_type& conditional_format_storage::get( const internal_lookup_id_type internal_id ) const
    {
        const_iterator it( m_lookup_map.find( internal_id ) );
        if ( it != m_lookup_map.end() ) {
            return it->second;
        }
        static shared_conditional_format_reference_type dummy;
        return dummy;
    }

    get_conditionalformat_list_type conditional_format_storage::get( session& s, const sheet_range::rectangles_type& ranges )
    {
        get_conditionalformat_list_type return_val;
        get( return_val, s, false, ranges );
        return return_val;
    }

    void conditional_format_storage::get( get_conditionalformat_list_type& return_val, session& s, const bool solve_formulas /* = false */, const sheet_range::rectangles_type& ranges /* = sheet_range::rectangles_type */ )
    {
        internal_id_set_type already_passed_external_ids;
        const internal_id_list_type sorted_id_list =  m_ranks->sort( ids( ranges ) );

        my_for_loop_start( internal_id_list_type::const_iterator, i, end_i, sorted_id_list ) {
            const shared_conditional_format_reference_type& ref = get( *i );
            if ( ref && already_passed_external_ids.insert( ref->id ).second ) { //check if we did that one already!
                const rectangle_list_type affected_ranges = get_external_affected_ranges( ref->id );
                const sheet_point position = affected_ranges.empty() ? sheet_point( 0, 0 ) : affected_ranges.begin()->upper_left();
                return_val.push_back(
                    get_conditional_format(
                        ref->id
                        , ref->rule->to_string( s, solve_formulas )
                        , ref->format_style_border->format_str()
                        , ref->format_style_border->style_str()
                        , ref->format_style_border->return_border()
                        , ref->rule->get_operand_as_string_array( s, position )
                        , conditional_format_affected_range_list( affected_ranges ).to_a1( s.locale() )
                        , ref->format_style_border->unlocked
                    )
                );
            }
        }
    }

    const internal_id_set_type& conditional_format_storage::get_internal_ids( const conditional_format_lookup_id_type id ) const
    {
        external_id_lookup_map_type::const_iterator it( m_external_id_lookup.find( id ) );
        if ( it != m_external_id_lookup.end() ) {
            return it->second;
        }
        static internal_id_set_type dummy;
        return dummy;
    }

    void conditional_format_storage::insert( session& s, const set_conditional_format& cf_format, const conditional_format_lookup_id_type next_id, const shared_worksheet_type& ws, const sheet_point& position, const bool is_relative /* = false */ )
    {
        do_check( m_lookup_map, m_rect_container );

        internal_id_set_type internal_ids;
        sheet_range::rectangles_type ranges = cf_format.selected_range();
        my_for_loop_start( sheet_range::rectangles_type::const_iterator, r, r_end, ranges ) {
            internal_lookup_id_type internal_id = m_counter.get_next();
            shared_conditional_format_reference_type ref( boost::make_shared<conditional_format_reference>( conditional_format_utils::parse( s, cf_format.operands(), cf_format.rule(), ws, *r, position, is_relative ), next_id ) );
            ref->format_style_border = cf_format.format_style_unlock_information();
            //add the areas to the rectangle container
            internal_insert( *r, internal_id, next_id, ref );
        }
        //clear the cache
        m_cache.reset();
        do_check( m_lookup_map, m_rect_container );

    }

    void conditional_format_storage::update( session& s, const conditional_format_lookup_id_type id, const set_conditional_format& cf_format, const shared_worksheet_type& ws, const sheet_point& position )
    {
        do_check( m_lookup_map, m_rect_container );

        //for now we just gonna remove the rule and add it again.
        remove( id );
        internal_id_set_type internal_ids;
        sheet_range::rectangles_type ranges = cf_format.selected_range();
        my_for_loop_start( sheet_range::rectangles_type::const_iterator, r, r_end, ranges ) {
            internal_lookup_id_type internal_id = m_counter.get_next();
            shared_conditional_format_reference_type ref( boost::make_shared<conditional_format_reference>( conditional_format_utils::parse( s, cf_format.operands(), cf_format.rule(), ws, *r, position ), id ) );
            ref->format_style_border = cf_format.format_style_unlock_information();
            //add the areas to the rectangle container
            internal_insert( *r, internal_id, id, ref );
        }
        //clear the cache
        m_cache.reset();
        do_check( m_lookup_map, m_rect_container );
    }

    void conditional_format_storage::remove( const conditional_format_lookup_id_type id )
    {
        do_check( m_lookup_map, m_rect_container );
        external_id_lookup_map_type::iterator it( m_external_id_lookup.find( id ) );
        if ( it != m_external_id_lookup.end() ) {
            //get a copy here, because the iterator will be manipulated!
            internal_id_set_type ids = it->second;
            internal_remove( ids );
            m_external_id_lookup.erase( id );
        }
        do_check( m_lookup_map, m_rect_container );
    }

    void conditional_format_storage::internal_remove( const internal_id_set_type& ids )
    {
        do_check( m_lookup_map, m_rect_container );
        conditional_format_erase_ids_callback c( ids );
        r_container_type::optional_rectangle_type covered_range = m_rect_container.used_range();
        if ( covered_range ) {
            m_rect_container.remove( *covered_range, c );
            my_for_loop_start( internal_id_set_type::const_iterator, it, end_it, ids ) {
                internal_remove_from_maps( *it );
            }
        }
        do_check( m_lookup_map, m_rect_container );
    }

    void conditional_format_storage::internal_remove_from_maps( const internal_lookup_id_type i )
    {
        external_id_lookup_map_type::iterator it( m_external_id_lookup.find( i ) );
        if ( it != m_external_id_lookup.end() ) {
            it->second.erase( i );
            if ( it->second.empty() ) {
                m_external_id_lookup.erase( it );
            }
        }
        m_ranks->remove( i );
        m_lookup_map.erase( i );
    }

    void conditional_format_storage::remove( session& s, const sheet_range::rectangles_type& ranges, const internal_id_list_type& ids )
    {
        do_check( m_lookup_map, m_rect_container );
        my_for_loop_start( sheet_range::rectangles_type::const_iterator, it, end_it, ranges ) {
            remove( s, *it, ids );
        }
        //clear the cache
        m_cache.reset();
        do_check( m_lookup_map, m_rect_container );
    }

    void conditional_format_storage::external_remove( session& s, const sheet_range& range, const id_list_type& external_ids )
    {
        do_check( m_lookup_map, m_rect_container );
        internal_id_list_type internal_ids;
        my_for_loop_start( id_list_type::const_iterator, it, end_it, external_ids ) {
            insert_from_temporary( internal_ids, m_external_id_lookup[*it] );
        }
        remove( s, range, internal_ids );
        do_check( m_lookup_map, m_rect_container );
    }

    void conditional_format_storage::external_remove( session& s, const sheet_range::rectangles_type& ranges, const id_list_type& external_ids )
    {
        do_check( m_lookup_map, m_rect_container );
        if ( ranges.empty() ) {
            if ( external_ids.empty() ) {
                //remove everything
                m_rect_container = r_container_type();
                m_lookup_map.clear();
                m_external_id_lookup.clear();
                m_ranks.reset( new conditional_format_rank() );
            } else {
                my_for_loop_start( id_list_type::const_iterator, it, end_it, external_ids ) {
                    remove( *it );
                }
            }
        } else {
            my_for_loop_start( sheet_range::rectangles_type::const_iterator, r, end_r, ranges ) {
                external_remove( s, *r, external_ids );
            }
        }
        //clear the cache
        m_cache.reset();
        do_check( m_lookup_map, m_rect_container );
    }

    void conditional_format_storage::remove( session& s, const sheet_range& range, const internal_id_list_type& internal_ids )
    {
        do_check( m_lookup_map, m_rect_container );
        conditional_format_erase_ids_in_region_callback::partially_erased_id_set_type partially_erased_internal_ids;
        conditional_format_erase_ids_in_region_callback::completely_erased_id_set_type completely_erased_internal_ids;
        if ( internal_ids.empty() ) {
            conditional_format_erase_region_callback c( range, 0, partially_erased_internal_ids, completely_erased_internal_ids );
            m_rect_container.remove( range, c );
        } else {
            conditional_format_erase_ids_in_region_callback c( range, internal_id_set_type( internal_ids.begin(), internal_ids.end() ), partially_erased_internal_ids, completely_erased_internal_ids );
            m_rect_container.remove( range, c );
        }
        {
            //adjust partially deleted areas!
            my_for_loop_start( conditional_format_erase_ids_in_region_callback::partially_erased_id_set_type::const_iterator,
                               it, it_end, partially_erased_internal_ids ) {
                shared_conditional_format_reference_type old_ref = m_lookup_map[it->first];
                geometry::rectangle_type::rectangles_type cut_vec = it->second.cut( range );
                my_for_loop_start( geometry::rectangle_type::rectangles_type::const_iterator, r, r_end, cut_vec ) {
                    internal_lookup_id_type next_internal_id = m_counter.get_next();
                    shared_conditional_format_rule_type new_rule = old_ref->rule->clone_with_new_range_for_copy( s, *r, it->second, shared_worksheet_type() );
                    shared_conditional_format_reference_type new_ref( boost::make_shared<conditional_format_reference>( new_rule, old_ref->id  ) );
                    internal_insert( *r, next_internal_id, old_ref->id, new_ref );
                }
                iterator c_it( m_lookup_map.find( it->first ) );
                external_id_lookup_map_type::iterator e_it( m_external_id_lookup.find( c_it->second->id ) );
                e_it->second.erase( it->first );
                if ( e_it->second.empty() ) {
                    m_external_id_lookup.erase( e_it );
                }
                m_lookup_map.erase( c_it );
            }
        }
        {
            //remove completely erased references
            my_for_loop_start( conditional_format_erase_ids_in_region_callback::completely_erased_id_set_type::const_iterator,
                               it, it_end, completely_erased_internal_ids ) {
                iterator c_it( m_lookup_map.find( *it ) );
                external_id_lookup_map_type::iterator e_it( m_external_id_lookup.find( c_it->second->id ) );
                e_it->second.erase( *it );
                if ( e_it->second.empty() ) {
                    m_external_id_lookup.erase( e_it );
                }
                m_lookup_map.erase( c_it );
            }
        }
        do_check( m_lookup_map, m_rect_container );
    }

    conditional_format_storage::return_vec_type conditional_format_storage::match( session& s, const sheet_range& range, const conditional_format_query_type query_type )
    {

#ifdef TRACE_CORRECTNESS_OF_CF
        LOG_CORE_DEBUG( ">>>>> CURRENTLY FEATURING: " << m_lookup_map.size() << " CFs!" );
#endif // TRACE_CORRECTNESS_OF_CF

        if ( m_lookup_map.empty() ) {
            return cf_vec_type();
        }
        bool recalc_needed = false;
        if ( !m_cache || m_cache->range != range ) {
            recalc_needed = true;
        } else {
            const internal_id_set_type int_ids = ids( range );
            my_for_loop_start( internal_id_set_type::const_iterator, it, end_it, int_ids ) {
                //             for (internal_id_set_type::const_iterator it = int_ids.begin(), end_it = int_ids.end(); it != end_it; ++it)
                //             {
                if ( m_lookup_map[*it]->rule->is_dirty( s ) ) {
                    recalc_needed = true;
                    break;
                }
            }
        }
        if ( recalc_needed ) {
            if ( fill_cache( s, sorted_ids_plus_cell_lookup( range ), query_type, range ) ) {
                if ( m_cache.get() == NULL ) {
                    LOG_CORE_DEBUG( "recalc of conditional formatting didn't succeed" );
                    return cf_vec_type();
                }
            } else {
                //there are no CFs in the specified area, lets return an empty vector
                return cf_vec_type();
            }
        }
        //assert( "conditional format recalc created the wrong size of return vec!" && m_cache->format_style_vec.size() == range.count() && m_cache->range == range );

        return m_cache->format_style_vec;
    }

    void conditional_format_storage::move( session& s, const sheet_range& source, const sheet_point& target, shared_worksheet_type target_sheet /* = shared_worksheet_type */ )
    {
        do_check( m_lookup_map, m_rect_container );

        const bool same_sheet = ( !target_sheet );
        const geometry::point dist( source.distance( target ) );
        const sheet_range local_target = source.checked_offset( dist );

        conditional_format_move_callback::partially_erased_id_set_type partially_moved_nodes;
        conditional_format_move_callback::completely_erased_id_set_type completely_moved_nodes;
        conditional_format_locked_storage::auto_type locked_target(
            same_sheet ? NULL : conditional_format_locked_storage::create_locked_store( target_sheet ).release() );
        conditional_format_storage& target_store = same_sheet ? ( *this ) : locked_target->store();

        if ( same_sheet ) {
            const sheet_range::rectangles_type cut_rects = local_target.cut( source );
            my_for_loop_start( sheet_range::rectangles_type::const_iterator, it, end_it, cut_rects ) {
                remove( s, *it, internal_id_list_type() );
            }
        } else {
            target_store.remove( s, local_target, internal_id_list_type() );
        }
        // get list of all nodes that need be changed
        conditional_format_move_callback move_cb( source, 0, partially_moved_nodes, completely_moved_nodes );
        m_rect_container.remove( source, move_cb );

        my_for_loop_start( conditional_format_move_callback::partially_erased_id_set_type::const_iterator,
                           it, end_it, partially_moved_nodes ) {
            const geometry::rectangle_type moved_part = it->second.intersection( source );
            const geometry::rectangle_type::rectangles_type remaining_parts = it->second.cut( moved_part );
            my_for_loop_start( geometry::rectangle_type::rectangles_type::const_iterator, current_remaining_part, current_remaining_part_end_it, remaining_parts ) {
                internal_create_clone_and_insert_for_move( s, sheet_range( *current_remaining_part ), it->second, m_lookup_map[it->first], 0, target_sheet );
            }
            // clone the node that need be changed
            const conditional_format_lookup_id_type new_external_id = same_sheet ? static_cast<conditional_format_lookup_id_type>( 0 ) : target_sheet->parent()->get_next_cf_id();
            target_store.internal_create_clone_and_insert_for_move( s, sheet_range( it->second.intersection( source ).offset( dist ) ), it->second, m_lookup_map[it->first], new_external_id, target_sheet );
            iterator c_it( m_lookup_map.find( it->first ) );
            external_id_lookup_map_type::iterator e_it( m_external_id_lookup.find( c_it->second->id ) );
            e_it->second.erase( it->first );
            if ( e_it->second.empty() ) {
                m_external_id_lookup.erase( e_it );
            }
            m_lookup_map.erase( c_it );
        }

        //minor optimization, if the moved node was completely covered we don't have to compute the intersection with the source range.
        // we just move the complete rectangle in this case.
        my_for_loop_start( conditional_format_move_callback::completely_erased_id_set_type::const_iterator,
                           it, end_it, completely_moved_nodes ) {
            // clone the node that need be changed
            const conditional_format_lookup_id_type new_external_id = same_sheet ? static_cast<conditional_format_lookup_id_type>( 0 ) : target_sheet->parent()->get_next_cf_id();
            target_store.internal_create_clone_and_insert_for_move( s, sheet_range( it->second.offset( dist ) ), it->second, m_lookup_map[it->first], new_external_id, target_sheet );

            iterator c_it( m_lookup_map.find( it->first ) );
            external_id_lookup_map_type::iterator e_it( m_external_id_lookup.find( c_it->second->id ) );
            e_it->second.erase( it->first );
            if ( e_it->second.empty() ) {
                m_external_id_lookup.erase( e_it );
            }
            m_lookup_map.erase( c_it );
        }

        //clear the cache
        m_cache.reset();
        if ( !same_sheet ) {
            target_store.m_cache.reset();
        }
        do_check( m_lookup_map, m_rect_container );

    }

    void conditional_format_storage::copy( session& s, const sheet_range& source, const sheet_range& target, const shared_workbook_type& wb, shared_worksheet_type target_sheet, const bool use_copy_move /* = false */ )
    {
        do_check( m_lookup_map, m_rect_container );

        const bool same_sheet = ( !target_sheet );
        const geometry::point distance( source.distance( target ) );
        const sheet_range local_target = target.enclose( source.offset( distance ) );

        conditional_format_copy_callback::partially_erased_id_set_type partially_copied_nodes;
        conditional_format_copy_callback::completely_erased_id_set_type completely_copied_nodes;

        // get list of all nodes that need be changed
        conditional_format_copy_callback move_cb( source, 0, partially_copied_nodes, completely_copied_nodes );
        m_rect_container.remove( source, move_cb );

        conditional_format_locked_storage::auto_type locked_target(
            same_sheet ? NULL : conditional_format_locked_storage::create_locked_store( target_sheet ).release() );
        conditional_format_storage& target_store = same_sheet ? *this : locked_target->store();
        target_store.remove( s, local_target, internal_id_list_type() );


        copy_fill_iterator it( source, local_target );

        my_for_loop_start( conditional_format_move_callback::partially_erased_id_set_type::const_iterator,
                           node_it, end_it, partially_copied_nodes ) {
            // clone the node that need be changed
            //TODO insert copy_fill_iterator here
            const sheet_range affected_range( node_it->second.intersection( source ) );
            it.reset();
            const std::list<sheet_range> target_list( it.whole_target_area( affected_range ) );
            for ( std::list<sheet_range>::const_iterator current_target_it = target_list.begin(), end_it = target_list.end(); current_target_it != end_it; ++current_target_it ) {
                if ( use_copy_move ) {
                    target_store.internal_create_clone_and_insert_for_copy_move( s, *current_target_it, node_it->second, m_lookup_map[node_it->first], wb->get_next_cf_id(), distance, source );
                } else {
                    target_store.internal_create_clone_and_insert_for_move( s, *current_target_it, *current_target_it, m_lookup_map[node_it->first], wb->get_next_cf_id(), target_sheet );
                }
            }
        }

        //minor optimization, if the copied node was completely covered we don't have to compute the intersection with the source range.
        // we just copy the complete rectangle in this case.

        my_for_loop_start( conditional_format_move_callback::completely_erased_id_set_type::const_iterator,
                           node_it, end_it, completely_copied_nodes ) {
            // clone the node that need be changed
            it.reset();
            const std::list<sheet_range> target_list( it.whole_target_area( node_it->second  ) );
            for ( std::list<sheet_range>::const_iterator current_target_it = target_list.begin(), end_it = target_list.end(); current_target_it != end_it; ++current_target_it ) {
                if ( use_copy_move ) {
                    target_store.internal_create_clone_and_insert_for_copy_move( s, *current_target_it, node_it->second, m_lookup_map[node_it->first], wb->get_next_cf_id(), distance, source );
                } else {
                    target_store.internal_create_clone_and_insert_for_move( s, *current_target_it, node_it->second, m_lookup_map[node_it->first], wb->get_next_cf_id(), target_sheet );
                }
            }
        }

        target_store.m_cache.reset();
        do_check( m_lookup_map, m_rect_container );

    }

    inline void copy_style_information( const conditional_format_storage::shared_conditional_format_reference_type& old_ref, const conditional_format_storage::shared_conditional_format_reference_type& new_ref )
    {
        new_ref->format_style_border->format = old_ref->format_style_border->format;
        new_ref->format_style_border->unlocked = old_ref->format_style_border->unlocked;
        new_ref->format_style_border->border = old_ref->format_style_border->border;
        new_ref->format_style_border->style = old_ref->format_style_border->style;
    }

    void conditional_format_storage::internal_create_clone_and_insert_for_move( session& s, const sheet_range& r, const sheet_range& old_range, const shared_conditional_format_reference_type& old_ref, const conditional_format_lookup_id_type new_id, const shared_worksheet_type& target_ws )
    {
        if ( old_ref && old_ref->rule ) {
            const internal_lookup_id_type old_id = ( new_id != 0 ? new_id : old_ref->id );
            shared_conditional_format_rule_type new_rule = old_ref->rule->clone_with_new_range_for_move( s, r, old_range, target_ws );
            shared_conditional_format_reference_type new_ref( boost::make_shared<conditional_format_reference>( new_rule, old_id  ) );
            copy_style_information( old_ref, new_ref );
            internal_insert( r, m_counter.get_next(), old_id, new_ref );
        }
    }

    void conditional_format_storage::internal_create_clone_and_insert_for_copy_move( session& s, const sheet_range& r, const sheet_range& old_range, const shared_conditional_format_reference_type& old_ref, const conditional_format_lookup_id_type new_id, const geometry::point& distance, const sheet_range& source_range )
    {
        if ( old_ref && old_ref->rule ) {
            const internal_lookup_id_type old_id = ( new_id != 0 ? new_id : old_ref->id );
            shared_conditional_format_rule_type new_rule = old_ref->rule->clone_with_new_range_for_copy_move( s, r, old_range, source_range, distance );
            shared_conditional_format_reference_type new_ref( boost::make_shared<conditional_format_reference>( new_rule, old_id  ) );
            copy_style_information( old_ref, new_ref );
            internal_insert( r, m_counter.get_next(), old_id, new_ref );
        }
    }

    void conditional_format_storage::internal_insert( const sheet_range& r, const internal_lookup_id_type internal_id, const conditional_format_lookup_id_type external_id, const shared_conditional_format_reference_type& new_ref )
    {
        if ( !new_ref || !new_ref->rule || !new_ref->rule->parsing_successful() ) {
            return;
        }

        m_lookup_map[internal_id] = new_ref;
        m_external_id_lookup[external_id].insert( internal_id );
        m_rect_container.insert( geometry::rectangle_type( r ), internal_id, false );
        m_ranks->add( internal_id );
    }

    void conditional_format_storage::move_up( session& /* s */, const conditional_format_lookup_id_type id, const sheet_range::rectangles_type& selected_region )
    {
        external_id_lookup_map_type::const_iterator it( m_external_id_lookup.find( id ) );
        if ( it != m_external_id_lookup.end() ) {
            m_ranks->move_up( it->second, ids( selected_region ) );
            //clear the cache
            m_cache.reset();
        }
    }

    void conditional_format_storage::move_down( session& /* s */, const conditional_format_lookup_id_type id, const sheet_range::rectangles_type& selected_region )
    {
        external_id_lookup_map_type::const_iterator it( m_external_id_lookup.find( id ) );
        if ( it != m_external_id_lookup.end() ) {
            m_ranks->move_down( it->second, ids( selected_region ) );
            //clear the cache
            m_cache.reset();
        }
    }

    void conditional_format_storage::release_memory( bool purge )
    {
        r_container_type::release_memory( purge );
    }
}
