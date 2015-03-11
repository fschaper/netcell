
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
#if !defined( HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/enable_shared_from_this.hpp>
#endif
#include "wss/workbook.hpp"
#include "named_formula_manager.hpp"
#include "wss/worksheet_element_storage.hpp"
#include "wss/object_registry.hpp"
#include "core_logging.hpp"
#include "conditional_format_counter.hpp"
#include "wss/server.hpp"
#include "uuid_adjust.hpp"
#include "wss/core2_compatibility.hpp"

#include <oxml/custom_data.hpp>

template<>
object_container<workbook, worksheet>::value_type object_container<workbook, worksheet>::get( session& s, const utf8_ci_string& name ) const
{
    lock_type guard( m_mutex );
    if ( m_state == halted ) {
        throw object_unloading_exception();
    }

    if ( s.session_sheets().check( name ) ) {
        if ( this && ( s.session_sheets().session_sheet( name )->parent().get() == this ) ) {
            return s.session_sheets().session_sheet( name );
        }
    }
    object_order_lookup_type::const_iterator it = std::find_if( m_object_order.begin(), m_object_order.end(),
                                                  boost::bind( &object_type::name, _1 ) == name );

    if ( m_object_order.end() == it ) {
        throw object_not_found_exception( convert_utf8_ci( name ) );
    }

    return *it;
}

template<>
object_container<workbook, worksheet>::value_type object_container<workbook, worksheet>::get( session& s, const uuid_type& id ) const
{
    lock_type guard( m_mutex );
    if ( m_state == halted ) {
        throw object_unloading_exception();
    }
    if ( s.session_sheets().check( id ) ) {
        return s.session_sheets().session_sheet( id );
    }

    object_order_lookup_type::const_iterator it( std::find_if( m_object_order.begin(), m_object_order.end(),
                                                 boost::bind( &object_type::uuid, _1 ) == id ) );

    if ( m_object_order.end() == it ) {
        throw object_not_found_exception( boost::lexical_cast<std::string>( id ) );
    }

    return *it;
}

struct workbook::workbook_impl {
    workbook_impl( workbook* parent ) : m_named_formula_manager( parent ) {}

    named_formula_manager m_named_formula_manager;
    cf::counter_type m_cf_counter;
    worksheet_element_storage m_elements;
};

workbook::workbook( const shared_application_type& app, const utf8_ci_string& name )
    : identifiable_object( name )
    , m_application( app )
    , m_workbook_has_changes( false )
    , m_workbook_has_changes_autosave( false )
    , m_is_temp( false )
{
    m_impl.reset( new workbook_impl( this ) );
    //RIA: the following is a workaround for a WS8 bug that prevents the instantiation of count from
    //object_container;
    count();
    LOG_CORE_DEBUG( "created workbook object [" << this->uuid() << "] with name ["  << this->name() << "]" );
}

workbook::~workbook()
{
    on_global_workbook_delete( *this );
    LOG_CORE_DEBUG( "released workbook object [" << this->uuid() << "] with name ["  << this->name() << "]" );
    server::instance().object_registry().unset( *this );
}

shared_workbook_type workbook::create( const shared_application_type& app, const utf8_ci_string& name )
{
    shared_workbook_type return_value( boost::make_shared<workbook>( app, name ) );
    return_value->m_weak_workbook = return_value;
    server::instance().object_registry().set( return_value );
    return return_value;
}

shared_application_type workbook::parent() const
{
    return m_application;
}

void workbook::unload()
{
    halt();
    LOG_CORE_DEBUG( "unloading workbook object [" << this->uuid() << "] with name ["  << this->name() << "]"  );
    m_impl->m_named_formula_manager.unload();
    foreach( const shared_worksheet_type & ws, locking_iterator() ) {
        ws->unload();
    }
    clear();
}

i_named_formula_manager& workbook::named_formulas() const
{
    return m_impl->m_named_formula_manager;
}

void workbook::select( selection_state& s )
{
    LOG_CORE_TRACE( "selecting workbook object [" << this->uuid() << "]" );
    s.workbook( shared_from_this() );
}

variable_name_list_type workbook::variable_list()
{
    const variable_name_list_type tmp_from_wb( m_variable.list() );
    std::set< std::string > tmp_set( tmp_from_wb.begin(), tmp_from_wb.end() );
    foreach( const shared_worksheet_type & ws, locking_iterator() ) {
        variable_name_list_type tmp( ws->variable().list() );
        tmp_set.insert( tmp.begin(), tmp.end() );
    }
    return variable_name_list_type( tmp_set.begin(), tmp_set.end() );
}

variable_map& workbook::variable()
{
    return m_variable;
}


weak_workbook_type workbook::weak_pointer() const
{
    return m_weak_workbook;
}

const boost::uint_fast32_t workbook::get_next_cf_id() const
{
    return m_impl->m_cf_counter.get_next();
}

worksheet_element_storage& workbook::elements() const
{
    return m_impl->m_elements;
}

void workbook::flag_changed()
{
    m_workbook_has_changes = true;
    m_workbook_has_changes_autosave = true;
}

void workbook::flag_changed( bool val )
{
    m_workbook_has_changes = val;
}

void workbook::flag_changed_autosave( bool val )
{
    m_workbook_has_changes_autosave = val;
}

bool workbook::has_changes() const
{
    return m_workbook_has_changes;
}

bool workbook::has_changes_autosave() const
{
    return m_workbook_has_changes_autosave;
}

void workbook::deserialize( session& s, const spreadsheetml::CT_extended_data& data )
{
    namespace sml = spreadsheetml;

    this->version_major( data.version.major );
    this->version_minor( data.version.minor );
    const std::vector< sml::CT_worksheet_element >&  in_wselts = data.worksheet_elements.worksheet_element;

    for ( std::vector< sml::CT_worksheet_element >::const_iterator i = in_wselts.begin(), end_it = in_wselts.end(); i != end_it; ++i ) {
#ifdef _CORE2_COMPATIBILITY_ON_UUIDS_
        //TODO this is very ugly but won't stay like that! the uuid has to be found _before_ the creation of the ws element!
        if ( i->wse_id.value.present() ) {
            LOG_CORE_DEBUG( "core2 compatibility issue: uuid's will not be unique for multiple instances of this worksheet." );

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
}

void workbook::serialize( session& s, spreadsheetml::CT_extended_data& data ) const
{
    namespace sml = spreadsheetml;

    sml::CT_worksheet_elements& wselts  = data.worksheet_elements;

    foreach( const shared_worksheet_element_type & wse, m_impl->m_elements.list_all_elements() ) {
        sml::CT_worksheet_element wselt;
        wse->serialize( s, wselt );
        wselts.worksheet_element.push_back( wselt );
    }
}

boost::signal<void( const workbook& )> workbook::on_global_workbook_delete;

void workbook::is_temp( bool val )
{
    m_is_temp = val;
}
bool workbook::is_temp() const
{
    return m_is_temp;
}

void workbook::version_major( short major )
{
    m_version_major = major;
}

void workbook::version_minor( short minor )
{
    m_version_minor = minor;
}

short workbook::version_major()
{
    return m_version_major;
}

short workbook::version_minor()
{
    return m_version_minor;
}
