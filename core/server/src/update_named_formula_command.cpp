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
#include "wss/update_named_formula_command.hpp"
#include "wss/invalid_workbook_exception.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/session.hpp"
#include "wss/worksheet.hpp"
#include "wss/workbook.hpp"
#include "object_lookup.hpp"
#include "wss/named_formula_exception.hpp"
#include "wss/named_formula_accessor.hpp"

/*
update_named_formula_command::update_named_formula_command( session& s, const std::string& name, const variant& formula, const sheet_point& position / * = sheet_point * /, const std::string& comment / *= ""* / )
        : base_command( s )
        , m_name( name )
        , m_formula( formula )
        , m_scope( named_formula_scope::workbook_scope )
        , m_position( position )
        , m_comment( comment )
{
    shared_worksheet_type ws =  m_session.selected().worksheet().lock();
    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    m_ws = w

*/
update_named_formula_command::update_named_formula_command( session& s, const named_formula_identifier& nf_identifier, const key_val_map_type& k_v_map, const sheet_point& position /* = sheet_point */ )
    : base_command<i_command>::base_command( s )
    , m_position( position )
    , m_id( boost::uuids::nil_uuid() )
    , m_identifier( nf_identifier )
{
    std::string scope_ws = "";
    key_val_map_type::const_iterator it( k_v_map.find( "name" ) ), end_it( k_v_map.end() );
    if ( it != end_it ) {
        m_name = it->second;
    }
    it = k_v_map.find( "refers_to" );
    if ( it == end_it ) {
        throw named_formula_exception( "required 'refers_to' property not set in key_value_map!" );
    }
    m_formula = it->second;
    it = k_v_map.find( "scope" );
    if ( it != end_it ) {
        if ( it->second == "Workbook" ) {
            m_scope = named_formula_scope::workbook_scope;
        } else {
            scope_ws = it->second;
            m_scope = named_formula_scope::worksheet_scope;
        }
    } else {
        m_scope = named_formula_scope::workbook_scope;
    }
    it = k_v_map.find( "comment" );
    if ( it != end_it ) {
        m_comment = it->second;
    }
    shared_worksheet_type ws =  m_session.selected().worksheet().lock();
    if ( m_scope == named_formula_scope::worksheet_scope ) {
        if ( !scope_ws.empty() && !( ws->name() == scope_ws ) ) {
            //try a lookup
            try {
                ws = object_lookup::worksheet( s, ws, convert_utf8_ci( scope_ws ) );
            } catch ( const object_not_found_exception& ) {
                throw named_formula_exception( "requested worksheet '" + scope_ws + "' does not exist!" );
            }
        }
    }
    if ( ! ws ) {
        throw named_formula_exception( "no worksheet selected for current session!" );
    }
    m_ws = ws;
}


update_named_formula_command::update_named_formula_command( session& s, const std::string& id, const key_val_map_type& k_v_map, const sheet_point& position /* = sheet_point */ )
    : base_command<i_command>::base_command( s )
    , m_position( position )
    , m_id( id.empty() ? boost::uuids::nil_uuid() : boost::lexical_cast<uuid_type>( id ) )
    , m_identifier( "" )
{
    std::string scope_ws = "";
    key_val_map_type::const_iterator it( k_v_map.find( "name" ) ), end_it( k_v_map.end() );
    if ( it != end_it ) {
        m_name = it->second;
    }
    it = k_v_map.find( "refers_to" );
    if ( it == end_it ) {
        throw named_formula_exception( "required 'refers_to' property not set in key_value_map!" );
    }
    m_formula = it->second;
    it = k_v_map.find( "scope" );
    if ( it != end_it ) {
        if ( it->second == "Workbook" ) {
            m_scope = named_formula_scope::workbook_scope;
        } else {
            scope_ws = it->second;
            m_scope = named_formula_scope::worksheet_scope;
        }
    } else {
        m_scope = named_formula_scope::workbook_scope;
    }
    it = k_v_map.find( "comment" );
    if ( it != end_it ) {
        m_comment = it->second;
    }
    shared_worksheet_type ws =  m_session.selected().worksheet().lock();
    if ( m_scope == named_formula_scope::worksheet_scope ) {
        if ( !scope_ws.empty() && !( ws->name() == scope_ws ) ) {
            //try a lookup
            try {
                ws = object_lookup::worksheet( s, ws, convert_utf8_ci( scope_ws ) );
            } catch ( const object_not_found_exception& ) {
                throw named_formula_exception( "requested worksheet '" + scope_ws + "' does not exist!" );
            }
        }
    }
    if ( ! ws ) {
        throw named_formula_exception( "no worksheet selected for current session!" );
    }
    m_ws = ws;
}

void update_named_formula_command::execute()
{
    shared_worksheet_type ws =  m_ws.lock();
    if ( ! ws ) {
        throw named_formula_exception( "requested worksheet does not exist!" );
    }
    if ( m_id.is_nil() ) {
        if ( m_identifier.name().empty() ) {
            throw named_formula_exception( "no id and no name given!" );
        }
        shared_named_formula_accessor_type nf_accessor = ws->parent()->named_formulas().get_accessor( m_session, m_identifier );
        if ( !m_name.empty() ) {
            nf_accessor->name( m_session, m_name );
        }
        if ( !m_formula.is_empty() ) {
            nf_accessor->value( m_session, m_formula, m_position );
        }
        if ( !m_comment.empty() ) {
            nf_accessor->comment( m_comment );
        }
    } else {
        ws->parent()->named_formulas().update( m_session, m_id, m_name, m_formula, m_comment, m_position );
    }
}

update_named_formula_command::result_type update_named_formula_command::value() const
{
    shared_worksheet_type ws =  m_ws.lock();
    if ( ! ws ) {
        throw named_formula_exception( "requested worksheet does not exist!" );
    }
    if ( m_id.is_nil() ) {
        //TODO give the named formula accessor some kind of get_key_val_vec functionality
        i_named_formula_manager& names =  ws->parent()->named_formulas();
        return names.get_key_val_vec( m_session, names.get_accessor( m_session, m_identifier )->uuid() , m_position );

    }
    return ws->parent()->named_formulas().get_key_val_vec( m_session, m_id, m_position );
}

DEFINE_CLONEABLE( update_named_formula_command );
