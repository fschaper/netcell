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
#include "wss/deactivate_array_formula_command.hpp"
#include "wss/session.hpp"
#include "wss/worksheet.hpp"
#include "wss/range.hpp"
#include "wss/variant.hpp"

deactivate_array_formula_command::deactivate_array_formula_command( session& s, const sheet_range& formula_coverage )
    : abstract_undoable_command( s )
    , m_formula_coverage( formula_coverage )
{}

void deactivate_array_formula_command::execute()
{
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
#ifdef CORE_DO_UNDO_SUPPORT
    if ( m_undo_formula.is_empty() && supports_do_undo::check( ws ) ) {
        m_undo_formula = ws->range( sheet_range( m_formula_coverage.upper_left() ) ).formula( m_session );
    }
#endif
    ws->range( m_formula_coverage ).unset_array_formula( m_session );
}

void deactivate_array_formula_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    assert( "un_execute called on a command that is on a temporary wb or on a cloned sheet!" && supports_do_undo::check( ws ) );
    if ( !m_undo_formula.is_empty() ) {
        ws->range( m_formula_coverage ).array_formula( m_session, m_undo_formula );
    }
#endif
}

DEFINE_CLONEABLE( deactivate_array_formula_command );
