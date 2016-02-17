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
#include "wss/get_named_formula_command.hpp"
#include "wss/workbook.hpp"
#include "wss/invalid_workbook_exception.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/named_formula_exception.hpp"

#include "object_lookup.hpp"
#include "wss/worksheet.hpp"

get_named_formula_command::get_named_formula_command( session& s, const std::string& name, const uuid_type& sheet_id, const sheet_point position /*= sheet_point( 0, 0 ) */ )
    : base_command<i_command>::base_command( s )
    , m_name( name )
    , m_scope( sheet_id.is_nil() ? named_formula_scope::workbook_scope : named_formula_scope::worksheet_scope )
    , m_position( position )
{
    if ( sheet_id.is_nil() ) {
        shared_worksheet_type ws =  m_session.selected().worksheet().lock();
        if ( ! ws ) {
            throw invalid_worksheet_exception();
        }
        m_ws = ws;
    } else {
        shared_workbook_type wb =  m_session.selected().workbook().lock();
        if ( ! wb ) {
            throw invalid_workbook_exception();
        }

        m_ws = wb->get( s, sheet_id );
    }
}

get_named_formula_command::get_named_formula_command( session& s, const std::string& name, const sheet_point position /*= sheet_point( 0, 0 )*/ )
    : base_command<i_command>::base_command( s )
    , m_name( name )
    , m_scope( named_formula_scope::workbook_scope )
    , m_position( position )
{
    shared_worksheet_type ws =  m_session.selected().worksheet().lock();
    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    m_ws = ws;
}

void get_named_formula_command::execute()
{
    shared_worksheet_type ws = m_ws.lock();
    if ( !ws ) {
        throw named_formula_exception( "requested worksheet does not exist!" );
    }
    const named_formula_identifier nf_identifier = named_formula_identifier( m_name, m_scope == named_formula_scope::worksheet_scope  ? ws->uuid() : boost::uuids::nil_uuid() );
    m_cached_val = ws->parent()->named_formulas().get_key_val_vec( m_session, nf_identifier, m_position );
}

get_named_formula_command::result_type get_named_formula_command::value() const
{
    return m_cached_val;
}

DEFINE_CLONEABLE( get_named_formula_command );
