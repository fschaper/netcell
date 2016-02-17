/**
 *  \file
 *  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 *
 *  \author
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"
#include "wss/layout_coord.hpp"
#include "wss/variant.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/text_metrics.hpp"
#include "wss/formatter.hpp"
#include "wss/conditional_format_manager.hpp"
#include "conditional_format_style_unlock_type.hpp"

shared_dependency_type layout_coord::create(  weak_worksheet_type ws, bool is_row  )
{
    return boost::make_shared<layout_coord>( ws, is_row );
}

layout_coord::layout_coord(  weak_worksheet_type ws, bool is_row  )
    : m_is_dirty( true )
    , m_value( 0 )
    , m_worksheet(  ws )
    , m_is_row( is_row )
{
}

void layout_coord::worksheet( weak_worksheet_type& ws )
{
    m_worksheet = ws;
}

i_dependency::dependency_type layout_coord::type() const
{
    return layout_coord_type;
}
bool layout_coord::has_formula() const
{
    return false;
}
bool layout_coord::has_precedents() const
{
    return false;
}
bool layout_coord::has_dependents() const
{
    return false;
}
referencetable_type layout_coord::precedents()  const
{
    return referencetable_type();
}

referencetable_type layout_coord::precedents( const shared_dependency_type& sd )  const
{
    return referencetable_type();
}

const dependency_set_type& layout_coord::dependents() const
{
    static const dependency_set_type dummy;
    return dummy;
}

variant layout_coord::value( calculation_context& cc ) const
{
    if ( m_is_dirty ) {
        const_cast< layout_coord* >( this )->recompute( cc );
    }
    return variant( ( double ) m_value );
}

variant layout_coord::value( interpreter_context& ic ) const
{
    return value( ic.context() );
}

void layout_coord::value( session&, const variant&, const sheet_point& position/* = sheet_point( 0, 0 )*/ )
{
}

std::string layout_coord::formula( const locale& l ) const
{
    return std::string();
}

void layout_coord::calculate( interpreter_context& )
{
}

void layout_coord::calculate( calculation_context& )
{
}

weak_worksheet_type layout_coord::worksheet() const
{
    return weak_worksheet_type();
}

void layout_coord::register_dependent( const shared_dependency_type& dep )
{
    m_cells.insert( dep );
}

void layout_coord::unregister_dependent( const shared_dependency_type& )
{
}

optional_variant_type layout_coord::fetch_cached_volatile( calculation_context& cc ) const
{
    return optional_variant_type();
}

bool layout_coord::is_dirty() const
{
    return false;
}

bool layout_coord::is_volatile() const
{
    return false;
}

bool layout_coord::is_array() const
{
    return false;
}

sheet_range layout_coord::array_coverage() const
{
    return sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 0 ) );
}

bool layout_coord::flag_dirty( const bool flag_dirty_even_if_volatile/* = false */ )
{
    return false;
}

const sheet_point& layout_coord::position() const
{
    static const sheet_point dummy( 0, 0 );
    return dummy;
}

void layout_coord::flag_relative()
{
}

void layout_coord::raise_volatile_count()
{
}

void layout_coord::lower_volatile_count()
{
}

unsigned long layout_coord::volatile_count() const
{
    return 0;
}

unsigned long layout_coord::volatile_count_without_formula() const
{
    return 0;
}

void layout_coord::internal_flag_dirty()
{
    //TODO: we can implement various more evolved caching here.
    m_is_dirty = true;
}

void layout_coord::internal_raise_volatile_count()
{
}

void layout_coord::internal_lower_volatile_count()
{
}

void layout_coord::flag_moved()
{
}

optional_sheet_range_type layout_coord::coverage() const
{
    return optional_sheet_range_type();
}

void layout_coord::lock()
{
}

bool layout_coord::try_lock()
{
    return true;
}

void layout_coord::unlock()
{
}

#ifdef _DEBUG

std::string layout_coord::get_debug_identifier( void ) const
{
    static const std::string    return_value( "layout_coord" );
    return return_value;
}

#endif

inline variant unarrayize_variant( const variant& value )
{
    if ( value.is_array() ) {
        if ( value.array().size() ) {
            return unarrayize_variant( value.array()[ 0 ] );
        } else {
            return variant();
        }
    }
    if ( value.is_empty() ) {
        return variant( 0.0 );
    } else {
        return value;
    }
}

void trim_hyperlink( std::string& value )
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

void layout_coord::recompute( calculation_context& cc )
{
    std::set< weak_dependency_type > to_delete;
    shared_worksheet_type sw = m_worksheet.lock();
    if ( ! sw ) {
        //do not throw. don't recompute anylonger
        return;
    }
    m_value = 0;

    conditional_format_manager&             cfm = sw->conditional_formats();
    format_manager_type&                    fm = sw->format();
    formatter::shared_format_engine_type    format_engine = formatter::instance().engine();
    text_metrics::shared_engine_type        text_metric_engine = text_metrics::instance().engine();
    const style_manager_type&               sm = sw->style();

    if ( !format_engine || !text_metric_engine ) {
        return;
    }

    foreach( const weak_dependency_type & dep, m_cells ) {
        shared_dependency_type sd = dep.lock();
        if ( sd ) {
            const format_manager_type::optional_value_type format = fm.get( sd->position() );
            const variant tmp = unarrayize_variant( sd->value( cc ) );
            std::string formatted_value;
            if ( format ) {
                formatted_value = format_engine->formatted_value( cc.session(), *format, tmp );
            } else {
                formatted_value = tmp.as_string( cc.session().locale() );
            }
            //correction for hyperlink
            if ( formatted_value.substr( 0, 11 ) == "<span class" ) {
                trim_hyperlink( formatted_value );
            }

            key_value_set<css_serializer, css_unserializer>  style = sm.get( sd->position() );

            const cf::cf_vec_type cfm_vec = cfm.match( cc.session(), sheet_range( sd->position(), sd->position() ), conditional_format_manager::query_conditional_format_style );
            if ( !cfm_vec.empty() ) {
                cf::cf_vec_type::const_iterator cfm_end( cfm_vec.end() );
                cf::cf_vec_type::const_iterator cfm_it( cfm_vec.find( 0 ) );
                if ( cfm_it != cfm_end ) {
                    if ( cfm_it->second->style ) {
                        style.combine( cfm_it->second->style.get() );
                    }
                }
            }

            i_text_metrics::text_box box = text_metric_engine->measure_text( style,  i_text_metrics::text_dpi_pair( 96, 96 ),  variant( formatted_value ) );
            if ( m_is_row ) {
                if ( box.second > m_value ) {
                    m_value = box.second;
                }
            } else {
                if ( box.first > m_value ) {
                    m_value = box.first;
                }
            }
        } else {
            to_delete.insert( dep );
        }
    }

    foreach( const weak_dependency_type & dep, to_delete ) {
        m_cells.erase( m_cells.find( dep ) );
    }

    m_value += 2;

    m_is_dirty = false;
}


