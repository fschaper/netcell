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
#include "wss/remove_named_formula_command.hpp"
#include "wss/session.hpp"
#include "wss/workbook.hpp"
#include "object_lookup.hpp"
#include "wss/named_formula_exception.hpp"
#include "wss/named_formula_scope.hpp"
#include "wss/i_named_formula_manager.hpp"

remove_named_formula_command::remove_named_formula_command( session& s, const std::string& name, const std::string& scope_ws )
    : base_command<i_command>::base_command( s )
    , m_name( name )
    , m_scope( scope_ws.empty() ? named_formula_scope::worksheet_scope : named_formula_scope::workbook_scope )
{
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
        throw named_formula_exception( "requested worksheet does not exist!" );
    }
    m_ws = ws;
}

remove_named_formula_command::remove_named_formula_command( session& s, const std::string& id )
    : base_command<i_command>::base_command( s )
    , m_uuid( boost::lexical_cast<uuid_type>( id ) )
{
    shared_worksheet_type ws =  m_session.selected().worksheet().lock();

    if ( ! ws ) {
        throw named_formula_exception( "requested worksheet does not exist!" );
    }
    m_ws = ws;
}

void remove_named_formula_command::execute()
{
    shared_worksheet_type ws =  m_ws.lock();
    if ( ! ws ) {
        throw named_formula_exception( "requested worksheet does not exist!" );
    }
    if ( ! m_name.empty() ) {
        const named_formula_identifier nf_identifier = named_formula_identifier( m_name, m_scope == named_formula_scope::worksheet_scope  ? ws->uuid() : boost::uuids::nil_uuid() );
        ws->parent()->named_formulas().remove( m_session, nf_identifier );
    } else {
        ws->parent()->named_formulas().remove( m_session, m_uuid );
    }
}

DEFINE_CLONEABLE( remove_named_formula_command );
