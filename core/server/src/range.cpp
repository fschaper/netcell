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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"

#include "wss/range.hpp"
#include "wss/variant.hpp"
#include "wss/bitcount.hpp"
#include "wss/auto_fill.hpp"
#include "wss/formatter.hpp"
#include "wss/worksheet.hpp"
#include "wss/application.hpp"
#include "wss/ast_formula.hpp"
#include "wss/a1conversion.hpp"
#include "wss/style_manager.hpp"
#include "wss/border_manager.hpp"
#include "wss/attribute_manager.hpp"
#include "wss/calculation_context.hpp"
#include "wss/merged_cell_manager.hpp"
#include "wss/sheet_layout_manager.hpp"
#include "wss/scoped_selection_state.hpp"
#include "wss/conditional_format_manager.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/can_not_change_part_of_an_array_exception.hpp"
#include "wss/can_not_change_merged_cell_exception.hpp"

#include "conditional_format_style_unlock_type.hpp"
#include "border_utility.hpp"
#include "core_logging.hpp"
#include "cell_manager.hpp"
#include "border.hpp"
#include "cell.hpp"

#include "value_manager_bool_specialization.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
#endif

//#define hide_bug_8135

/*!
 * \brief
 * this will generate log output for range operations
 * get/set of values/styles...
 *
 * default is enabled for debug builds
 * \see LOG_CORE_TRACE
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
//#define LOG_TRACE_RANGE_OPERATIONS 1

#if defined(LOG_TRACE_RANGE_OPERATIONS) && defined(_DEBUG) && !defined(LOG_CORE_TRACE_RANGE_OPERATIONS)
#   define LOG_CORE_TRACE_RANGE_OPERATIONS(message) LOG_CORE_TRACE(message)
#else
#   define LOG_CORE_TRACE_RANGE_OPERATIONS(message)
#endif // LOG_TRACE_DEPENDENCIES


/*!
 * \brief
 * little helper to compare for flags being set or not
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
template<typename T>
inline bool has_flag( const long flags_set, const T flag_to_check )
{
    return ( flags_set & flag_to_check ) == flag_to_check;
}

template<typename value_T, typename replacement_value_T, typename array_T>
inline void set_value_at_idx_if_not_empty( const size_t idx, const boost::optional<value_T>& value, const replacement_value_T& second_val, array_T& array )
{
    if ( value ) {
        set_value_at_idx_if_not_empty( idx, *value, array );
    } else {
        set_value_at_idx_if_not_empty( idx, second_val, array );
    }
}
template< typename array_T>
inline void set_value_at_idx_if_not_empty( const size_t idx, const style_manager_type::value_type& value, array_T& array, const bool skip_empties = true )
{
    if ( !value.empty() ) {
        array.set( idx, value.serialize( skip_empties ) );
    }
}

template<typename value_T, typename array_T>
inline void set_value_at_idx_if_not_empty( const size_t idx, const value_T& value, array_T& array )
{
    if ( !value.empty() ) {
        array.set( idx, value );
    }
}

inline variant _unarrayize_variant( const variant& value )
{

    if ( value.is_array() ) {
        if ( value.array().size() ) {
            return _unarrayize_variant( value.array()[ 0 ] );
        } else {
            return variant();
        }
    }
    return value;
}

inline void __trim_hyperlink( std::string& value )
{
    size_t start = value.find( '>' );
    if ( std::string::npos == start ) {
        return;
    }
    size_t stop = value.find( '<', start );
    if ( std::string::npos == stop ) {
        return;
    }
    value = value.substr( start + 1, stop - start - 1 );
}


range::range( weak_worksheet_type ws, const sheet_range& rr )
    : m_worksheet( ws )
    , m_referenced_rect( rr )
{}

range::range( const range& other )
    : m_worksheet( other.m_worksheet )
    , m_referenced_rect( other.m_referenced_rect )
{}

std::string range::address() const
{
    return a1conversion::to_a1::from_range( m_referenced_rect );
}

weak_worksheet_type range::worksheet() const
{
    return m_worksheet;
}

range range::column( unsigned int c ) const
{
    return range( m_worksheet, m_referenced_rect.column( c ) );
}

range range::row( unsigned int r ) const
{
    return range( m_worksheet, m_referenced_rect.row( r ) );
}

std::size_t range::count() const
{
    return m_referenced_rect.column_count() * m_referenced_rect.column_count();
}

geometry::point range::distance( const range& other ) const
{
    return m_referenced_rect.distance( other.coverage() );
}

void range::value( session& s, const variant& v,  const bool trim_hyperlink )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    // update the session with informations about the currently
    // selected range on the worksheet
    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( sw );
    s.selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "set value on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "] value [" << v << "]" );

    // lock the range on the sheet for write access
    range_lock lock( sw->cells().lock( m_referenced_rect, lock::exclusive ) );
    if ( !s.is_loading() ) { //lets assume we don't load partially intersecting arrays! ;-)
        if ( lock.contains_array() || lock.contains_partially_intersecting_array() ) {
            if ( lock.contains_partially_intersecting_array() ) {
                throw can_not_change_part_of_an_array_exception();
            }
            if ( lock.get( m_referenced_rect.upper_left() ) ) {
                if ( lock.get( m_referenced_rect.upper_left() )->array_coverage().count() == 1 ) {
                    lock.clear( s );
                }
            }
        }
    }

    // set all selected cells on the worksheet to their new value
    // and create them if they don't as of yet exist.
    if ( variant::type_array == v.type() ) {
        const variant::sparse_array_type& val = v.array();

        variant::sparse_array_type::const_iterator crt = val.begin();
        variant::sparse_array_type::const_iterator end = val.end();

        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            shared_dependency_type sd( lock.get( *it ) );
            if ( ! sd ) {
                sd = lock.create( *it );
                sw->layout().register_new_cell( sd, *it );
            }
            if( trim_hyperlink && variant::type_string == ( *crt ).type() && ( *crt ).string().substr( 0, 11 ) == "<span class" ) {
                std::string hyperlink_value = ( *crt ).as_string( s.locale() );
                __trim_hyperlink( hyperlink_value );
                sd->value( s, variant( hyperlink_value ) );
            } else {

                sd->value( s, *crt );

            }
            ++crt;
            if ( crt == end ) {
                // in this case there aren't any values
                // left to set and we would crash the
                // server by accessing the iterator
                break;
            }
        }
    } else {
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            shared_dependency_type sd( lock.get( *it ) );
            if ( ! sd ) {
                sd = lock.create( *it );
                sw->layout().register_new_cell( sd, *it );
            }
            if( trim_hyperlink && variant::type_string == v.type() && v.string().substr( 0, 11 ) == "<span class" ) {
                std::string hyperlink_value = v.as_string( s.locale() );
                __trim_hyperlink( hyperlink_value );
                sd->value( s, variant( hyperlink_value ) );
            } else {

                sd->value( s, v );

            }
        }
    }
    if ( !s.is_loading() ) {
        s.clear_cache();
        sw->parent()->flag_changed();
        sw->compute_view_independent( s );
    }
}

variant range::value( calculation_context& cc )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    scoped_selection_state scoped_selection( cc.session() );
    cc.session().selected().worksheet( sw );
    cc.session().selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get value on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    // lock the range on the sheet for read access
    range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );

    if ( m_referenced_rect.count() == 1 ) {
        shared_dependency_type sd( lock.get( m_referenced_rect.upper_left() ) );
        if ( sd ) {
            return sd->value( cc );
        } else {
            return variant( variant::type_empty );
        }
    } else {
        variant::sparse_array_type result_array( coverage().count() );
        variant::sparse_array_type::size_type index = 0;
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            shared_dependency_type sd( lock.get( *it ) );
            if ( sd ) {
                result_array.set( index, variant( sd->value( cc ) ) );
            }
            ++index;
        }
        return variant( result_array, coverage().column_count() );
    }
}

variant range::value( session& s ) const
{
    calculation_context cc( s, s.selected().application()->calculation_settings() );
    return const_cast<range*>( this )->value( cc );
}

variant range::formula( calculation_context& cc, bool supress_value /*= false*/ ) const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    scoped_selection_state scoped_selection( cc.session() );
    cc.session().selected().worksheet( sw );
    cc.session().selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get formula on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );

    if ( m_referenced_rect.count() == 1 ) {
        shared_dependency_type sd( lock.get( m_referenced_rect.upper_left() ) );
        if ( sd ) {
            if ( sd->has_formula() ) {
                return sd->formula( cc.session().locale() );
            } else if ( ! supress_value ) {
                return sd->value( cc );
            }
        }
        return variant( variant::type_empty );
    } else {
        variant::sparse_array_type result_array( coverage().count(), variant() );
        variant::sparse_array_type::size_type index = 0;
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            shared_dependency_type sd( lock.get( *it ) );
            if ( sd ) {
                if ( sd->has_formula() ) {
                    result_array.set( index, variant( sd->formula( cc.session().locale() ) ) );
                } else if ( ! supress_value ) {
                    result_array.set( index,  sd->value( cc ) );
                }
            }
            ++index;
        }
        return variant( result_array, coverage().column_count() );
    }
}

variant range::has_formula() const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get formula on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );
    if ( m_referenced_rect.count() == 1 ) {
        shared_dependency_type sd( lock.get( m_referenced_rect.upper_left() ) );
        if ( sd ) {
            return sd->has_formula();
        } else {
            return false;
        }
    } else {
        variant::sparse_array_type result_array( coverage().count(), false );
        variant::sparse_array_type::size_type index = 0;
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            //foreach( const sheet_point & p, m_referenced_rect ) {
            shared_dependency_type sd( lock.get( *it ) );
            if ( sd ) {
                result_array.set( index , sd->has_formula() );
            } else {
                result_array.set( index, false );
            }
            ++index;
        }
        return variant( result_array, coverage().column_count() );
    }
}

variant range::formula( session& s, bool supress_value /*= false*/ ) const
{
    calculation_context cc( s, s.selected().application()->calculation_settings() );
    return formula( cc, supress_value );
}

void range::array_formula( session& s, const variant& v )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    if ( sw->merge().does_intersect( m_referenced_rect ) ) {
        throw can_not_change_merged_cell_exception();
    }
    const bool is_formula = ( v.is_string() && v.string().length() > 1 && v.string()[0] == '=' );

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( sw );
    s.selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "set array formula on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "] value [" << v << "]" );

    // if we actually have a formula
    if ( is_formula ) {
        // validate formula here;
        ast_formula ast_formula( s, sw, v.string() );
        // there is no array on the selected region
        std::auto_ptr<range_lock> lock( new range_lock( sw->cells().lock( m_referenced_rect, lock::exclusive ) ) );
        if ( !lock->contains_array() && !lock->contains_partially_intersecting_array() ) {
            // create an array
            shared_dependency_type sd( lock->create_array() );
            sd->value( s, v );
        }
        // we have an array setup already and it's intersecting with an existing array
        else {
            // copy old array coverage
            sheet_range old_array_coverage = m_referenced_rect;
            bool inside = false;
            bool outside = false;
            foreach( const sheet_range & existing, sw->array_region_list() ) {
                if ( existing.does_intersect( m_referenced_rect ) && m_referenced_rect.covers( existing ) ) {
                    outside = true;
                    old_array_coverage = existing;
                    break;
                } else if ( existing.covers( m_referenced_rect ) ) {
                    inside = true;
                    old_array_coverage = existing;
                    break;
                }
            }

            // override old array if selection is bigger than it or if selection is inside array and is 1 cell in size
            if (  inside ^ outside && ( outside || ( inside && m_referenced_rect.count() == 1 ) ) ) {
                if ( old_array_coverage.count() > m_referenced_rect.count() ) {
                    lock.reset( new range_lock( sw->cells().lock( old_array_coverage, lock::exclusive ) ) );
                    s.selected().range( old_array_coverage );
                }
                shared_dependency_type dep;
                if ( old_array_coverage != m_referenced_rect ) {
                    // clear old cells
                    lock->clear( s );
                    dep = lock->create_array();
                } else {
                    dep = lock->get( m_referenced_rect.upper_left() );

                }
                if ( dep.get() != NULL ) {
                    dep->value( s, v );
                } else {
                    throw can_not_change_part_of_an_array_exception();
                }
            } else {
                throw can_not_change_part_of_an_array_exception();
            }
        }
    }
    // constant value passed
    else {
        // just pass this value to cell
        value( s, v );
    }
    s.clear_cache();

    sw->parent()->flag_changed();

}


void range::unset_array_formula( session& s )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    if ( sw->merge().does_intersect( m_referenced_rect ) ) {
        throw can_not_change_merged_cell_exception();
    }

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( sw );
    s.selected().range( m_referenced_rect );

    {
        range_lock lock( sw->cells().lock( m_referenced_rect, lock::exclusive ) );
        //get the master cell
        shared_dependency_type master_cell = lock.get( m_referenced_rect.upper_left() );
        if ( !master_cell || !master_cell->is_array() ) {
            //if there is no cell or its not an array, we can just return.
            return;
        } else if ( m_referenced_rect != master_cell->array_coverage() ) {
            throw can_not_change_part_of_an_array_exception();
        }

        const std::string seed_formula = master_cell->formula( s.locale() );
        assert( "array formula not in the right format!" && seed_formula.size() > 3 && seed_formula[0] == '{' && seed_formula[1] == '=' && seed_formula[seed_formula.size()-1] == '}' );

        //remove the old array
        lock.remove_array( m_referenced_rect );
        lock.clear( s );
        //set new value on seed cell
        const sheet_point upper_left_position = m_referenced_rect.upper_left();
        master_cell = lock.get( upper_left_position );
        if ( !master_cell ) {
            master_cell = lock.create( upper_left_position );
        }
        master_cell->value( s, seed_formula.substr( 1, seed_formula.size() - 2 ) );
        cell_manager& cells = sw->cells();
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            if ( *it == upper_left_position ) {
                continue;
            } else {
                cells.copy( s, upper_left_position, sheet_range( *it ), sw );
            }
        }
    }

    s.clear_cache();

    sw->parent()->flag_changed();

}

void range::style( session& s, const style_set_type& style_set, const bool dont_invalidate/* = false*/ )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( sw );
    s.selected().range( m_referenced_rect );
    {
        std::list<utf8_ci_string> tmps;
        for ( style_set_type::const_iterator it = style_set.begin(); it != style_set.end(); it++ ) {
            const std::string& key = convert_utf8_ci( it->first );
            if ( key.find( "border" ) != key.npos ) {
                if ( key.find( "left" ) != key.npos ) {
                    sw->borders().border( m_referenced_rect, border_types::left, it->second );
                }
                if ( key.find( "top" ) != key.npos ) {
                    sw->borders().border( m_referenced_rect, border_types::top, it->second );
                }
                if ( key.find( "right" ) != key.npos ) {
                    sw->borders().border( m_referenced_rect, border_types::right, it->second );
                }
                if ( key.find( "bottom" ) != key.npos ) {
                    sw->borders().border( m_referenced_rect, border_types::bottom, it->second );
                }
                tmps.push_back( it->first );
            }
            if ( key.find( "background-color" ) != key.npos ) {
                if ( it->second == "" ) {
                    const_cast<std::string*>( &it->second )->assign( "none" );
                }
            }
        }

        foreach( const utf8_ci_string & s, tmps ) {
            const_cast< style_set_type* > ( &style_set )->erase( s );
        }
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "set style on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "] style [" << style_set.serialize() << "]" );
    if ( style_set.empty() ) {
        sw->style().erase( coverage() );
    } else {
        sw->style().set( m_referenced_rect, style_set );
    }
    if ( !dont_invalidate ) {
        sw->layout().invalidate_rect( m_referenced_rect );
    }

    sw->parent()->flag_changed();

}

css_style_vec_type range::style( const bool skip_empties/* = true */ ) const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get style from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    // get the style and border manager for the worksheet
    const style_manager_type& sm = sw->style();
    const border_manager& bm = sw->borders();
    const format_manager_type& fm = sw->format();

    css_style_vec_type array( m_referenced_rect.count() , ( variant() ) );
    size_t idx = 0;


    formatter::shared_format_engine_type engine = formatter::instance().engine();

    // lock the range on the sheet for read access
    range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );

    // serialize styles.
    for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
        //foreach( const sheet_point & p, m_referenced_rect ) {
        key_value_set<css_serializer, css_unserializer> var = sm.get( *it );

        const format_manager_type::optional_value_type format = fm.get( *it );
        if ( format ) {
            var.add( std::string( "__number-format" ), *format );
        }

        set_value_at_idx_if_not_empty( idx, var, array, skip_empties );
        ++idx;
    }

    border_vec_type b_vec = bm.border( m_referenced_rect, cf::cf_vec_type(), false );
    const border_vec_type::mapping_type& v = b_vec.direct();
    for ( border_vec_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
        //foreach( const border_vec_type::mapping_type::value_type & b, b_vec.direct() ) {
        const variant current_value = array[( *it ).first];
        if ( current_value.is_string() ) {
            set_value_at_idx_if_not_empty( ( *it ).first, ( current_value.string() + ( border_utility::type_to_css( ( *it ).second ) ) ), array );
        } else {
            set_value_at_idx_if_not_empty( ( *it ).first, ( border_utility::type_to_css( ( *it ).second ) ), array );
        }
    }

    return array;
}

css_style_vec_type range::style( session& s, const bool saving, const cf::cf_vec_type& cf_vec, const bool use_cf_vec  ) const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get style from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    // get the style and border manager for the worksheet
    const style_manager_type& sm = sw->style();
    const border_manager& bm = sw->borders();
    const format_manager_type& fm = sw->format();

    const cf::cf_vec_type& cfm_vec =
        saving
        ? cf::cf_vec_type()
        : ( use_cf_vec ? cf_vec : sw->conditional_formats().match( s, m_referenced_rect, conditional_format_manager::query_conditional_format_style ) );
    const bool no_conditional_formats = cfm_vec.empty();

    css_style_vec_type array( m_referenced_rect.count() ,/*css_style_type*/( variant() ) );
    size_t idx = 0;


    if ( no_conditional_formats ) {
        formatter::shared_format_engine_type engine = formatter::instance().engine();

        // lock the range on the sheet for read access
        range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );

        // serialize styles.
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            //foreach( const sheet_point & p, m_referenced_rect ) {
            key_value_set<css_serializer, css_unserializer> var = sm.get( *it );

            if ( !saving ) {
                shared_dependency_type sd( lock.get( *it ) );
                if ( sd ) {
                    const format_manager_type::optional_value_type format = fm.get( *it );
                    if ( format ) {
                        calculation_context cc( s, s.selected().application()->calculation_settings() );
                        variant tmp = sd->value( cc );

                        while ( tmp.is_array() ) {
                            tmp = tmp.array().size() > 0 ? tmp.array()[ 0 ] : variant();
                        }

                        std::string color = engine->formatted_color( s, *format, tmp );
                        if ( !color.empty() ) {
                            var.add( std::string( "color" ), color );
                        }
                    }
                }
            } else {
                const format_manager_type::optional_value_type format = fm.get( *it );
                if ( format ) {
                    var.add( std::string( "__number-format" ), *format );
                }
            }
            set_value_at_idx_if_not_empty( idx, var, array );
            ++idx;
        }
    } else {
        //conditional formats and saving are mutualy exclusive
        cf::cf_vec_type::const_iterator cfm_end( cfm_vec.end() );

        formatter::shared_format_engine_type engine = formatter::instance().engine();

        // lock the range on the sheet for read access
        range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            //foreach( const sheet_point & p, m_referenced_rect ) {
            std::string color;
            //handle color implied by the format
            shared_dependency_type sd( lock.get( *it ) );

            if ( sd ) {
                const format_manager_type::optional_value_type format = fm.get( *it );
                if ( format ) {

                    calculation_context cc( s, s.selected().application()->calculation_settings() );
                    variant tmp = sd->value( cc );
                    while ( tmp.is_array() ) {
                        tmp = tmp.array().size() > 0 ? tmp.array()[ 0 ] : variant();
                    }
                    color = engine->formatted_color( s, *format, tmp );
                    if ( !color.empty() ) {
                        color = "color:" + color;
                    }
                }
            }
            //handle conditional formatting
            cf::cf_vec_type::const_iterator cfm_it( cfm_vec.find( idx ) );

            if ( cfm_it != cfm_end && cfm_it->second->style ) {
                assert( cfm_it->second && " conditional_format_manager error, the returned vector had empty elements in there! " );
                style_set_type ss = cfm_it->second->style.get();
                ss.combine( sm.get( *it ) );
                set_value_at_idx_if_not_empty( idx, /* sm.get( p ).serialize() + cfm_it->second->style_str<false>()  */ ss.serialize() + color, array );
            } else {
                if ( color.empty() ) {
                    set_value_at_idx_if_not_empty( idx, sm.get( *it ), array );
                } else {
                    set_value_at_idx_if_not_empty( idx, sm.get( *it ).serialize() + color, array );
                }
            }
            ++idx;
        }
    }
    border_vec_type b_vec = bm.border( m_referenced_rect, cfm_vec, saving ? false : true );
    const border_vec_type::mapping_type& v = b_vec.direct();
    for ( border_vec_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
        //foreach( const border_vec_type::mapping_type::value_type & b, b_vec.direct() ) {
        const variant current_value = array[( *it ).first];
        if ( current_value.is_string() ) {
            set_value_at_idx_if_not_empty( ( *it ).first, /*css_style_type*/( current_value.string() + ( saving ?  border_utility::type_to_css( ( *it ).second ) : border_utility::type_to_css_only_left_and_top( ( *it ).second ) ) ), array );
        } else {
            set_value_at_idx_if_not_empty( ( *it ).first, ( saving ?  border_utility::type_to_css( ( *it ).second ) : border_utility::type_to_css_only_left_and_top( ( *it ).second ) ), array );
        }
    }

    return array;
}

void range::attribute( session& s, const attribute_set_type& attribute_set )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( sw );
    s.selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "set attribute on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "] attributes [" << attribute_set.serialize() << "]" );

    sw->attribute().set( m_referenced_rect, attribute_set );
    sw->parent()->flag_changed();

}

variant range::attribute() const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get attribute from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    attribute_manager& m = sw->attribute();
    optional_sheet_range_type attribute_range = m.used_range();

    variant::variant_array_type array( m_referenced_rect.count(), variant() );

    if ( !attribute_range.is_initialized() ) {
        return array;
    }

    size_t idx = 0;
    for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
        //foreach( const sheet_point & p, m_referenced_rect ) {
        const attribute_set_type& crt =  m.get( *it );
        if ( !crt.empty() ) {
            array.set( idx, crt.serialize() );
        }
        ++idx;
    }
    return array;
}

variant range::attribute( utf8_ci_string& key ) const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get attribute from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    attribute_manager& m = sw->attribute();
    variant::variant_array_type array( m_referenced_rect.count(), variant() );
    size_t idx = 0;
    for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
        //foreach( const sheet_point & p, m_referenced_rect ) {

        attribute_manager::value_type attrs =  m.get( *it );
        if ( !attrs.empty() ) {
            attribute_set_type::const_iterator begin = attrs.begin();
            attribute_set_type::const_iterator end = attrs.end();
            for ( attribute_set_type::const_iterator i = begin; i != end; i++ ) {
                if ( i->first == key ) {
                    array.set( idx, i->second );
                    break;
                }
            }
        }
        ++idx;
    }
    return array;
}

void range::clear_attributes()
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    sw->attribute().erase( m_referenced_rect );
}

range::range_set_type range::precedents()
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get precedents from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    range_set_type return_value;
    // lock the range on the sheet for read access
    range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );
    for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
        //foreach( const sheet_point & p, m_referenced_rect ) {
        shared_dependency_type sd( lock.get( *it ) );
        if ( sd ) {
            foreach( const shared_reference_type & sr, sd->precedents() ) {
                if ( sr->type() == i_dependency_reference::range_reference ) {
                    shared_worksheet_type srw = sr->worksheet().lock();
                    if ( srw ) {
                        return_value.insert( srw->range( range_reference_cast( sr ).actualize().position() ) );
                    }
                }
            }
        }
    }
    return return_value;
}

range::range_set_type range::dependents()
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get dependents from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    range_set_type return_value;
    // lock the range on the sheet for read access
    range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );
    const dependency_set_type& sd = lock.dependents();
    for ( dependency_set_type::const_iterator it = sd.begin(), end_it = sd.end(); it != end_it; ++it ) {
        //foreach( const shared_dependency_type & sd, lock.dependents() ) {
        shared_worksheet_type srw = ( *it )->worksheet().lock();
        if ( srw ) {
            return_value.insert( srw->range( ( *it )->position() ) );
        }
    }
    return return_value;
}

#ifdef hide_bug_8135

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include "wss/translation_table.hpp"

std::string do_hide_bug_8135( session& s, const std::string& input )
{
    char sep = translation_table::instance()[s.locale()]->parameter_separator()[0];

    boost::char_separator<char> b_sep( translation_table::instance()[s.locale()]->parameter_separator().c_str() );

    boost::tokenizer< boost::char_separator<char> > tokens( input, b_sep );

    std::set<std::string> uniques;

    variant err( variant::error_ref );

    bool first_time = true;

    foreach( const std::string & crt, tokens )  {

        if ( first_time ) {
            first_time = false;
            uniques.insert( crt );
            continue;
        }

        if ( crt == err.as_string( s.locale() ) || crt == err.as_string( s.locale() ) + ')' ) {
            continue;
        }
        if ( !crt.empty()  && crt[crt.size() - 1] == ')' ) {
            uniques.insert( crt.substr( 0, crt.size() - 1 ) );
        } else {
            uniques.insert( crt );
        }
    }

    if ( uniques.empty() ) {
        return input;
    }


    std::string result;

    std::set<std::string>::const_iterator i = uniques.begin();

    if ( i != uniques.end() ) {
        result = *i;
        i++;
    }

    while ( i != uniques.end() ) {
        result += ( sep + *i );
        i++;
    }

    if ( !result.empty()  && result[result.size() - 1] != ')' ) {
        result += ')';
    }

    return result;
}
#endif

template<bool adjust_position_for_ui>
const variant range::dependents( session& s )
{
    static const unsigned int position_offset = static_cast<unsigned int>( adjust_position_for_ui );
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get dependents from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    typedef std::pair< unsigned int, unsigned int > shallow_position_type;
    typedef std::pair< shallow_position_type, std::string > shallow_dependency;

    std::vector< shallow_dependency > unsorted_vect;

    // lock the range on the sheet for read access
    range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );
    const dependency_set_type& sd = lock.dependents();
    for ( dependency_set_type::const_iterator it = sd.begin(), end_it = sd.end(); it != end_it; ++it ) {
        if ( this->coverage().covers( ( *it )->position() ) ) {
            continue;
        }
        shared_worksheet_type srw = ( *it )->worksheet().lock();
        if ( srw && srw == sw ) {
            if ( ( *it )->type() == i_dependency::cell_type ) {
#ifdef hide_bug_8135
                unsorted_vect.push_back(  shallow_dependency( shallow_position_type( ( *it )->position().column() + position_offset, ( *it )->position().row() + position_offset ) , do_hide_bug_8135( s, ( *it )->formula( s.locale() ) ) ) );
#else
                unsorted_vect.push_back(  shallow_dependency( shallow_position_type( ( *it )->position().column() + position_offset, ( *it )->position().row() + position_offset ) , ( *it )->formula( s.locale() ) ) );
#endif
            }
        }
    }

    std::sort( unsorted_vect.begin(), unsorted_vect.end() );

    sparse_vector<variant> return_value;
    for ( std::vector< shallow_dependency >::const_iterator i = unsorted_vect.begin(), e = unsorted_vect.end(); i != e; ++i ) {
        sparse_vector<variant> position;

        position.push_back( variant( ( double )i->first.first ) );
        position.push_back( variant( ( double )i->first.second ) );
        sparse_vector<variant> crt;
        crt.push_back( variant( position ) );
        crt.push_back( variant( i->second ) );
        return_value.push_back( variant( crt ) );
    }

    return return_value;
}

//explicitly instantiate
template const variant range::dependents<true>( session& s );

//template const variant range::dependents<false>( session& s );

variant range::volatile_count() const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get volatile count from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    variant return_value;
    // lock the range on the sheet for read access
    range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );
    if ( m_referenced_rect.count() > 1 ) {
        return_value = variant( variant::type_array );
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            //foreach( const sheet_point & p, m_referenced_rect ) {
            shared_dependency_type sd( lock.get( *it ) );
            if ( sd ) {
                return_value.array().push_back( static_cast<double>( sd->volatile_count() ) );
            }
        }
    } else {
        shared_dependency_type sd( lock.get( m_referenced_rect.upper_left() ) );
        if ( sd ) {
            return_value = variant( static_cast<double>( sd->volatile_count() ) );
        }
    }
    return return_value;
}

void range::clear( session& s, const int type_of_content /* = content_type::all */, bool is_delete_column_row_operation /* = false */ )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "clear on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    if ( has_flag( type_of_content, content_type::formula ) || has_flag( type_of_content, content_type::value ) ) {
        sw->cells().lock( m_referenced_rect, lock::exclusive ).clear( s );
    }

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( sw );
    s.selected().range( m_referenced_rect );

    if ( has_flag( type_of_content, content_type::style ) ) {
        sw->style().erase( coverage() );
    }

    if ( has_flag( type_of_content, content_type::border ) ) {
        sw->lock().erase( coverage() );
        sw->borders().erase( coverage() );
        if ( !is_delete_column_row_operation ) {
            sw->merge().erase( coverage() );
        }
    }

    if ( has_flag( type_of_content, content_type::format ) ) {
        sw->format().erase( coverage() );
    }

    if ( has_flag( type_of_content, content_type::conditional_formats ) ) {
        sw->conditional_formats().erase( s, coverage() );
    }
    if ( has_flag( type_of_content, content_type::attributes ) ) {
        sw->attribute().erase( coverage() );
    }

    s.clear_cache();

    sw->parent()->flag_changed();
}

void range::copy( session& s, range& target, const bool whole_column_or_row, const insert_shift_direction::type shift_direction /* = insert_shift_direction::automatic */, const int type_of_content /* = content_type::all_plus_cf */ ) const
{
    shared_worksheet_type source_sheet = m_worksheet.lock();
    if ( ! source_sheet ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    shared_worksheet_type target_sheet = target.worksheet().lock();
    if ( ! target_sheet ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    const bool same_sheet = ( source_sheet == target_sheet );

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( source_sheet );
    s.selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "copy on worksheet [" << source_sheet->uuid() << "][" << source_sheet->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    if ( has_flag( type_of_content, content_type::formula )  ) {
        source_sheet->cells().copy( s, coverage(), target.coverage(), target_sheet, false, shift_direction );
    } else if ( has_flag( type_of_content, content_type::value ) ) {
        target.value( s, value( s ), true );
    }

    if ( has_flag( type_of_content, content_type::style ) ) {
        source_sheet->style().copy( coverage(), target.coverage(), target_sheet->style(), shift_direction );
    }

    if ( has_flag( type_of_content, content_type::border ) ) {
        source_sheet->lock().copy( coverage(), target.coverage(), target_sheet->lock() );
        if ( ! whole_column_or_row ) {
            if ( insert_shift_direction::automatic == shift_direction ) { //when shifting cell verically or horizontally the border are not copied to the inserted cells
                source_sheet->borders().copy( coverage(), target.coverage(), same_sheet ? shared_worksheet_type() : target_sheet, shift_direction );
            }
            source_sheet->merge().copy( coverage(), target.coverage(), target_sheet->merge() );
        }
    }

    if ( has_flag( type_of_content, content_type::conditional_formats ) ) {
        source_sheet->conditional_formats().copy( s, coverage(), target.coverage(), same_sheet ? shared_worksheet_type() : target_sheet );
    }

    if ( has_flag( type_of_content, content_type::format ) ) {
        source_sheet->format().copy( coverage(), target.coverage(), target_sheet->format(), shift_direction );
    }

    if ( has_flag( type_of_content, content_type::attributes ) ) {
        source_sheet->attribute().copy( coverage(), target.coverage(), target_sheet->attribute(), shift_direction );
    }
    s.clear_cache();

    target_sheet->parent()->flag_changed();
}

void range::copy_move( session& s, range& target, const insert_shift_direction::type shift_direction /* = insert_shift_direction::automatic */, const int type_of_content /* = content_type::all_plus_cf */ ) const
{
    shared_worksheet_type source_sheet = m_worksheet.lock();
    if ( ! source_sheet ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    shared_worksheet_type target_sheet = target.worksheet().lock();
    if ( ! target_sheet ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }
    const bool same_sheet = ( source_sheet == target_sheet );

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( source_sheet );
    s.selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "copy_move on worksheet [" << source_sheet->uuid() << "][" << source_sheet->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    if ( has_flag( type_of_content, content_type::formula )  ) {
        source_sheet->cells().copy( s, coverage(), target.coverage(), target_sheet, true, shift_direction );
    } else if ( has_flag( type_of_content, content_type::value ) ) {
        target.value( s, value( s ) );
    }

    if ( has_flag( type_of_content, content_type::style ) ) {
        source_sheet->style().copy( coverage(), target.coverage(), target_sheet->style(), shift_direction );
    }

    if ( has_flag( type_of_content, content_type::border ) ) {
        source_sheet->lock().copy( coverage(), target.coverage(), target_sheet->lock(), shift_direction );
        source_sheet->borders().copy( coverage(), target.coverage(), same_sheet ? shared_worksheet_type() : target_sheet, shift_direction );
        source_sheet->merge().copy( coverage(), target.coverage(), target_sheet->merge() );
    }

    if ( has_flag( type_of_content, content_type::conditional_formats ) ) {
        source_sheet->conditional_formats().copy( s, coverage(), target.coverage(), same_sheet ? shared_worksheet_type() : target_sheet, true );
    }

    if ( has_flag( type_of_content, content_type::format ) ) {
        source_sheet->format().copy( coverage(), target.coverage(), target_sheet->format(), shift_direction );
    }

    if ( has_flag( type_of_content, content_type::attributes ) ) {
        source_sheet->attribute().copy( coverage(), target.coverage(), target_sheet->attribute(), shift_direction );
    }
    s.clear_cache();

    target_sheet->parent()->flag_changed();

}

void range::move( session& s, range& target, const bool whole_column_or_row, const copy_format_from::type format_from /* = copy_format_from::left_or_above */, insert_shift_direction::type shift_direction /* = insert_shift_direction::automatic */, const int type_of_content /* = content_type::all_plus_cf */ ) const
{
    shared_worksheet_type source_sheet = m_worksheet.lock();
    if ( ! source_sheet ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    shared_worksheet_type target_sheet = target.worksheet().lock();
    if ( ! target_sheet ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }
    const bool same_sheet = ( source_sheet == target_sheet );

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( source_sheet );
    s.selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "move on worksheet [" << source_sheet->uuid() << "][" << source_sheet->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    const bool move_styles = has_flag( type_of_content, content_type::style );
    const bool move_borders = has_flag( type_of_content, content_type::border );

    if ( move_borders ) {
        source_sheet->merge().move( coverage(), target.coverage(), target_sheet->merge(), whole_column_or_row );
    }

    if ( has_flag( type_of_content, content_type::formula ) ) {
        source_sheet->cells().move( s, coverage(), target.coverage(), target_sheet, format_from, shift_direction );
    } else if ( has_flag( type_of_content, content_type::value ) ) {
        //in this case we only want to move values, not formulas
        target.value( s, value( s ) );
        const sheet_range::rectangles_type& ranges_to_erase = coverage().cut( target.coverage() );
        for ( sheet_range::rectangles_type::const_iterator it = ranges_to_erase.begin(), end_it = ranges_to_erase.end(); it != end_it; ++it ) {
            source_sheet->cells().erase( s, *it, erase_shift_direction::automatic );
        }
    }

    if ( move_styles ) {
        source_sheet->style().move( coverage(), target.coverage(), target_sheet->style(), format_from, shift_direction );
    }
    if ( move_borders ) {
        source_sheet->lock().move( coverage(), target.coverage(), target_sheet->lock(), format_from, shift_direction );
        source_sheet->borders().move( coverage(), target.coverage(), same_sheet ? shared_worksheet_type() : target_sheet, format_from, shift_direction );
    }

    if ( has_flag( type_of_content, content_type::conditional_formats ) ) {
        source_sheet->conditional_formats().move( s, coverage(), target.coverage().upper_left(), same_sheet ? shared_worksheet_type() : target_sheet );
    }

    if ( has_flag( type_of_content, content_type::format ) ) {
        source_sheet->format().move( coverage(), target.coverage(), target_sheet->format(), format_from, shift_direction );
    }

    if ( has_flag( type_of_content, content_type::attributes ) ) {
        source_sheet->attribute().move( coverage(), target.coverage(), target_sheet->attribute(), format_from, shift_direction );
    }
    s.clear_cache();

    target_sheet->parent()->flag_changed();
}

bool range::operator<( const range& rhs ) const
{
    return m_referenced_rect < rhs.coverage();
}

void range::merge( session& s )
{
    if ( 1 == coverage().count() ) {
        return;
    }
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }

    {
        //handle borders
        border_manager& b_manager = ws->borders();
        border_vec_type tmp_vec( b_manager.border( coverage(), cf::cf_vec_type(), true, true, false ) );
        border_vec_type::const_iterator it( tmp_vec.begin() ), end_it( tmp_vec.end() );
        b_manager.erase( coverage() );
        if ( ! tmp_vec.empty() && tmp_vec.size() == 4 ) {
            b_manager.border( coverage().top(), tmp_vec[0] );
            b_manager.border( coverage().bottom(), tmp_vec[1] );
            b_manager.border( coverage().left(), tmp_vec[2] );
            b_manager.border( coverage().right(), tmp_vec[3] );
        }
    }

    cell_manager& cells = ws->cells();

    if ( !s.is_loading() ) {
        range_lock lock( cells.lock( m_referenced_rect, lock::exclusive ) );
        calculation_context cc( s, s.selected().application()->calculation_settings() );
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            shared_dependency_type sd( lock.get( *it ) );
            if ( sd && ( ! sd->value( cc ).is_empty() ) ) {
                if ( *it != coverage().upper_left() ) {
                    range target( ws->range( coverage().upper_left() ) );
                    ws->range( sheet_range( *it ) ).move( s, target, false );
                }
                break;
            }
        }
    }
    style( s, ws->style().get( coverage().upper_left() ) );
    const format_manager_type::optional_value_type f = ws->format().get( coverage().upper_left() );
    if ( f ) {
        format( s, *f );
    }

    const sheet_range::rectangles_type& rt = coverage().cut( sheet_range( coverage().upper_left() ) );
    for ( sheet_range::rectangles_type::const_iterator it = rt.begin(), end_it = rt.end(); it != end_it; ++it ) {
        cells.lock( *it, lock::exclusive ).clear( s );
    }

    ws->merge().create( coverage() );
    s.clear_cache();

    ws->parent()->flag_changed();
}

void range::un_merge( session& s )
{
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }

    ws->merge().erase( coverage() );
    s.clear_cache();

    ws->parent()->flag_changed();

}

style_manager_type::undo_list_type range::style_undo_list() const
{
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }

    return ws->style().get_list_for_undo( m_referenced_rect );
}

void range::style_undo_list( const style_manager_type::undo_list_type& l )
{
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }

    ws->style().apply_list_for_undo( m_referenced_rect, l );

    ws->parent()->flag_changed();

}

format_manager_type::undo_list_type range::format_undo_list() const
{
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }

    return ws->format().get_list_for_undo( m_referenced_rect );
}

void range::format_undo_list( const format_manager_type::undo_list_type& undo_list )
{
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }

    ws->format().apply_list_for_undo( m_referenced_rect, undo_list );

    ws->parent()->flag_changed();

}

attribute_manager::undo_list_type range::attribute_undo_list() const
{
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    return ws->attribute().get_list_for_undo( m_referenced_rect );
}

void range::attribute_undo_list( const attribute_manager::undo_list_type& l )
{
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    ws->attribute().apply_list_for_undo( m_referenced_rect, l );

    ws->parent()->flag_changed();

}

unlocked_cells_vec_type range::un_locked( session& s, const cf::cf_vec_type& cf_vec, const bool use_cf_vec  ) const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get locked cells from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    const cf::cf_vec_type& cfm_vec = use_cf_vec ? cf_vec : sw->conditional_formats().match( s, m_referenced_rect, conditional_format_manager::query_conditional_format_lock );
    unlocked_cells_vec_type array( m_referenced_rect.count(), false );
    locked_cell_manager_type& m = sw->lock();

    size_t idx = 0;
    for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
        const locked_cell_manager_type::optional_value_type result = m.get( *it );
        if ( result && *result ) {
            array.set( idx, true );
        }
        ++idx;
    }

    if ( !cfm_vec.empty() ) {
        for ( cf::cf_vec_type::const_iterator it = cfm_vec.begin(), end_it = cfm_vec.end(); it != end_it; ++it ) {
            assert( " shared ptr returned from cf manager not initialized! " && ( *it ).second );
            if ( ( *it ).second->unlocked ) {
                array.set( ( *it ).first, !*( *it ).second->unlocked );
            }
        }
    }
    return array;
}

void range::un_locked( session& s, const bool unlocked )
{

    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( sw );
    s.selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "set locked cells on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "] [ " << ( unlocked ? "unlocked" : "locked" ) << "]" );

    sw->lock().set( ( geometry::generic_rectangle<sheet_point> )m_referenced_rect, unlocked );

    sw->parent()->flag_changed();

}

locked_cell_manager_type::undo_list_type range::un_locked_undo_list_type() const
{
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    return ws->lock().get_list_for_undo( m_referenced_rect );
}

void range::un_locked_undo_list_type( const locked_cell_manager_type::undo_list_type& l )
{
    shared_worksheet_type ws = m_worksheet.lock();

    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    ws->lock().apply_list_for_undo( m_referenced_rect, l );

    ws->parent()->flag_changed();

}

void range::format( session& s, const std::string& format_string, const bool dont_invalidate/* = false*/ )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    scoped_selection_state scoped_selection( s );
    s.selected().worksheet( sw );
    s.selected().range( m_referenced_rect );

    LOG_CORE_TRACE_RANGE_OPERATIONS( "set format on worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "] format [" << format_string << "]" );

    sw->format().set( m_referenced_rect, format_string );

    if ( !dont_invalidate ) {
        sw->layout().invalidate_rect( m_referenced_rect );
    }

    sw->parent()->flag_changed();

}

variant range::formatted_value( session& s, const cf::cf_vec_type& cf_vec, const bool use_cf_vec ) const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    calculation_context cc( s, s.selected().application()->calculation_settings() );

    formatter::shared_format_engine_type    engine = formatter::instance().engine();

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get formated value from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    // get the format manager for the worksheet
    format_manager_type& fm = sw->format();

    variant::variant_array_type array(  m_referenced_rect.count(), variant() );

    // lock the range on the sheet for read access
    range_lock lock( sw->cells().lock( m_referenced_rect, lock::shared ) );

    const cf::cf_vec_type& cfm_vec = use_cf_vec ? cf_vec : sw->conditional_formats().match( s, m_referenced_rect, conditional_format_manager::query_conditional_format_format );

    size_t idx = 0;
    if ( cfm_vec.empty() ) {
        // serialize values.
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            shared_dependency_type sd( lock.get( *it ) );
            if ( sd ) {
                const format_manager_type::optional_value_type format = fm.get( *it );
                const variant tmp = _unarrayize_variant( sd->value( cc ) );
                if ( format ) {
                    array.set( idx, engine->formatted_value( s, *format, tmp ) );
                } else if ( !tmp.is_of_empty_value() ) {
                    static const std::string dummy = "";
                    array.set( idx, engine->formatted_value( s, dummy, tmp ) );
                }
            }
            ++idx;
        }
    } else {
        cf::cf_vec_type::const_iterator cfm_end( cfm_vec.end() );
        // serialize values.
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            shared_dependency_type sd( lock.get( *it ) );
            if ( sd ) {
                cf::cf_vec_type::const_iterator cfm_it( cfm_vec.find( idx ) );
                if ( cfm_it != cfm_end && cfm_it->second->format ) {
                    const variant tmp = _unarrayize_variant( sd->value( cc ) );
                    array.set( idx, engine->formatted_value( s,  cfm_it->second->format->get(), tmp ) );
                } else {
                    const format_manager_type::optional_value_type format = fm.get( *it );
                    const variant tmp = _unarrayize_variant( sd->value( cc ) );
                    if ( format ) {
                        array.set( idx, engine->formatted_value( s, *format, tmp ) );
                    } else if ( !tmp.is_of_empty_value() ) {
                        static const std::string dummy = "";
                        array.set( idx, engine->formatted_value( s, dummy, tmp ) );
                    }
                }
            }
            ++idx;
        }
    }

    return array;
}

variant range::format( session& s, const cf::cf_vec_type& cf_vec, const bool use_cf_vec ) const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "get format from worksheet [" << sw->uuid() << "][" << sw->name() << "] range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "]" );

    // get the format manager for the worksheet
    format_manager_type& fm = sw->format();

    variant::variant_array_type array( m_referenced_rect.count(), variant() );

    const cf::cf_vec_type& cfm_vec = use_cf_vec ? cf_vec : sw->conditional_formats().match( s, m_referenced_rect, conditional_format_manager::query_conditional_format_format );

    size_t idx = 0;
    if ( cfm_vec.empty() ) {
        // serialize formats.
        for ( sheet_range::const_iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            const format_manager_type::optional_value_type format = fm.get( *it );
            if ( format ) {
                array.set( idx, *format );
            }
            ++idx;
        }
    } else {
        cf::cf_vec_type::const_iterator cfm_end( cfm_vec.end() );

        for ( sheet_range::iterator it = m_referenced_rect.begin(), end_it = m_referenced_rect.end(); it != end_it; ++it ) {
            cf::cf_vec_type::const_iterator cfm_it( cfm_vec.find( idx ) );
            if ( cfm_it != cfm_end && cfm_it->second && cfm_it->second->format ) {
                array.set( idx, cfm_it->second->format->get() );
            } else {
                const format_manager_type::optional_value_type format = fm.get( *it );
                if ( format ) {
                    array.set( idx, *format );
                }
            }
            ++idx;
        }
    }

    return array;
}

void range::copy_fill( session& s, range& target )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    auto_fill::shared_engine_type& engine = auto_fill::instance().engine();
    if ( !engine ) {
        LOG_CORE_WARNING( "autofill engine missing." );
        return;
    }

    LOG_CORE_TRACE_RANGE_OPERATIONS( "copyfill on worksheet [" << sw->uuid() << "][" << sw->name() << "] from range [" << a1conversion::formatting::as_a1() << m_referenced_rect << "] to range [" << a1conversion::formatting::as_a1() << target.coverage() << "]" );

    engine->handle_sequence( s, *this, target );


    sheet_range& copy_range = const_cast<sheet_range&>( coverage() );
    sheet_range& target_range = const_cast<sheet_range&>( target.coverage() );
    sheet_range target_range_copy = const_cast<sheet_range&>( target.coverage() );

    if ( target.coverage().area() > coverage().area() && coverage().area() > 1 ) {
        int iterations = target_range_copy.coverage().area() / coverage().area();
        int mod  = target_range_copy.coverage().area() % coverage().area();
        target_range = coverage().offset(  coverage().distance( target_range ) );
        sheet_range cut = target_range_copy.cut( target_range )[0];
        while ( iterations-- ) {
            copy_styles_formats_attributes( s, sw, copy_range, target_range, sw );
            target_range = target_range.offset( target_range.distance( cut ) );
            if ( cut.area() > target_range.area() ) {
                cut = cut.cut( target_range.offset( target_range.distance( cut ) ) )[0];
            }
        }
        if ( mod != 0 ) {
            copy_range = cut.offset(  cut.distance( coverage() ) );
            copy_styles_formats_attributes( s, sw, copy_range, cut, sw );
        }
    } else if ( target.coverage().area() < coverage().area() ) {
        copy_range = target.coverage().offset(  target.coverage().distance( coverage() ) );
        copy_styles_formats_attributes( s, sw, copy_range, target_range, sw );
    } else {
        copy_styles_formats_attributes( s, sw, copy_range, target_range, sw );
    }

    s.clear_cache();

    sw->parent()->flag_changed();

}

void range::copy_styles_formats_attributes ( session& s, const shared_worksheet_type& source_sheet, sheet_range& source, sheet_range& target, const shared_worksheet_type& target_sheet )
{
    content_type::type type_of_content = content_type::all_plus_cf;
    insert_shift_direction::type shift_direction = insert_shift_direction::automatic;
    bool same_sheet = ( target_sheet == source_sheet );

    if ( has_flag( type_of_content, content_type::style ) ) {
        source_sheet->style().copy( source, target, target_sheet->style(), shift_direction );
        source_sheet->merge().copy( source, target, target_sheet->merge() );
    }

    if ( has_flag( type_of_content, content_type::border ) ) {
        source_sheet->borders().copy( source, target, same_sheet ? shared_worksheet_type() : target_sheet, shift_direction );
    }

    if ( has_flag( type_of_content, content_type::conditional_formats ) ) {
        source_sheet->conditional_formats().copy( s, source, target, same_sheet ? shared_worksheet_type() : target_sheet );
    }

    if ( has_flag( type_of_content, content_type::format ) ) {
        source_sheet->format().copy( source, target, target_sheet->format(), shift_direction );
    }

    if ( has_flag( type_of_content, content_type::attributes ) ) {
        source_sheet->attribute().copy( source, target, target_sheet->attribute(), shift_direction );
    }
}

const sheet_layout_trait::integer_type range::width( session& s ) const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    const sheet_layout_manager&    layout = sw->layout();

    sheet_point::integer_type row         = m_referenced_rect.upper_left().row();
    sheet_point::integer_type start_col   = m_referenced_rect.upper_left().column();
    sheet_point::integer_type end_col     = m_referenced_rect.lower_right().column();

    sheet_point  extension( 0, 0 );

    if ( sw->merge().extend_point( sheet_point( row, end_col ), extension ) ) {
        end_col = extension.column();
    }

    sheet_layout_trait::integer_type    result = 0;
    for ( sheet_point::integer_type crt = start_col; crt <= end_col; crt++ ) {
        result += layout.column_width( crt );
    }

    return result;
}

const sheet_layout_trait::integer_type range::height( session& s ) const
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    const sheet_layout_manager&    layout = sw->layout();

    sheet_point::integer_type col         = m_referenced_rect.upper_left().column();
    sheet_point::integer_type start_row   = m_referenced_rect.upper_left().row();
    sheet_point::integer_type end_row     = m_referenced_rect.lower_right().row();

    sheet_point  extension( 0, 0 );

    if ( sw->merge().extend_point( sheet_point( end_row, col ), extension ) ) {
        end_row = extension.row();
    }

    sheet_layout_trait::integer_type    result = 0;
    for ( sheet_point::integer_type crt = start_row; crt <= end_row; crt++ ) {
        result += layout.row_height( crt );
    }

    return result;
}

bool range::validate_formula( session& s, std::string& formula )
{
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        LOG_CORE_WARNING( "requested worksheet no longer exists." );
        throw invalid_worksheet_exception();
    }

    if ( !ast_formula::test_formula( s, m_worksheet, formula ) ) {
        return false;
    }

    shared_dependency_type shared_cell = cell::create( sw, sheet_point( 0, 0 ) );
    shared_cell->value( s, variant( formula ) );
    calculation_context cc( s );
    return variant::type_error != shared_cell->value( cc ).type();
}
