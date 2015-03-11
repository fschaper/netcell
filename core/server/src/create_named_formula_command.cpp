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
#include "wss/create_named_formula_command.hpp"
#include "wss/invalid_workbook_exception.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/workbook.hpp"
#include "wss/named_formula_exception.hpp"
#include "object_lookup.hpp"

create_named_formula_command::create_named_formula_command( session& s, const std::string& name, const variant& formula, const sheet_point& position /*= sheet_point( 0, 0 ) */, const std::string& comment /*= ""*/ )
    : base_command<i_command>::base_command( s )
    , m_name( name )
    , m_formula( formula )
    , m_scope( named_formula_scope::workbook_scope )
    , m_comment( comment )
    , m_position( position )
{
    shared_worksheet_type ws =  m_session.selected().worksheet().lock();
    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    m_ws = ws;
}

create_named_formula_command::create_named_formula_command( session& s, const std::string& name, const variant& formula, const uuid_type& sheet_id, const sheet_point& position /*= sheet_point( 0, 0 )*/, const std::string& comment /*= ""*/ )
    : base_command<i_command>::base_command( s )
    , m_name( name )
    , m_formula( formula )
    , m_scope( named_formula_scope::worksheet_scope )
    , m_comment( comment )
    , m_position( position )
{
    shared_workbook_type wb =  m_session.selected().workbook().lock();
    if ( ! wb ) {
        throw invalid_workbook_exception();
    }

    m_ws = wb->get( s, sheet_id );
}

create_named_formula_command::create_named_formula_command( session& s, const key_val_map_type& k_v_map, const sheet_point& position /* = sheet_point */ )
    : base_command<i_command>::base_command( s )
    , m_position( position )
{
    std::string scope_ws = "";
    key_val_map_type::const_iterator it( k_v_map.find( "name" ) ), end_it( k_v_map.end() );
    if ( it == end_it ) {
        throw named_formula_exception( "required 'name' property not set in key_value_map!" );
    } else {
        m_name = it->second;
    }
    it = k_v_map.find( "refers_to" );
    if ( it == end_it ) {
        throw named_formula_exception( "required 'refers_to' property not set in key_value_map!" );
    }
    m_formula = it->second;
    it = k_v_map.find( "scope" );
    if ( it != end_it ) {
        if ( it->second == "" ) {
            m_scope = named_formula_scope::workbook_scope;
        } else {
            scope_ws = it->second;
            m_scope = named_formula_scope::worksheet_scope;
        }
    } else {
        m_scope = named_formula_scope::workbook_scope;
    }
    it = k_v_map.find( "comment" );
    if ( it != end_it && !( it->second.empty() ) ) {
        m_comment = it->second;
    }
    shared_worksheet_type ws =  m_session.selected().worksheet().lock();

    if ( ! ws ) {
        throw named_formula_exception( "no worksheet selected for current session!" );
    }

    if ( m_scope == named_formula_scope::worksheet_scope ) {
        if ( !( ws->name() == scope_ws ) ) {
            //try a lookup
            try {
                ws = object_lookup::worksheet( s, ws, convert_utf8_ci( scope_ws ) );
            } catch ( const object_not_found_exception& ) {
                throw named_formula_exception( "requested worksheet '" + scope_ws + "' does not exist!" );
            }
        }
    }
    m_ws = ws;
}

void create_named_formula_command::execute()
{
    shared_worksheet_type ws = m_ws.lock();
    if ( ! ws ) {
        throw named_formula_exception( "requested worksheet does not exist!" );
    }
    ws->parent()->named_formulas().create( ( m_session ), m_name, m_formula, m_scope, ws, m_position );
    if ( !m_comment.empty() ) {
        ws->parent()->named_formulas().comment( m_comment, named_formula_identifier( m_name, m_scope == named_formula_scope::worksheet_scope  ? ws->uuid() : boost::uuids::nil_uuid() ) );
    }
}

create_named_formula_command::result_type create_named_formula_command::value() const
{
    shared_worksheet_type ws =  m_ws.lock();
    if ( ! ws ) {
        throw named_formula_exception( "requested worksheet does not exist!" );
    }
    const named_formula_identifier nf_identifier = named_formula_identifier( m_name, m_scope == named_formula_scope::worksheet_scope  ? ws->uuid() : boost::uuids::nil_uuid() );
    return ws->parent()->named_formulas().get_key_val_vec( m_session, nf_identifier, m_position );
}

DEFINE_CLONEABLE( create_named_formula_command );
