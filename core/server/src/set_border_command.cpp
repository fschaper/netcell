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
#include "wss/set_border_command.hpp"

#include "wss/worksheet.hpp"
#include "wss/invalid_worksheet_exception.hpp"

#include "border.hpp"
#include <wss/border_types.hpp>

set_border_command::set_border_command( session& s, const sheet_range& rect, const long type, const std::string& style )
    : abstract_undoable_command( s )
    , m_rect( rect )
    , m_type( type )
    , m_style( style )
{}

set_border_command::set_border_command( const set_border_command& other )
    : abstract_undoable_command( other.m_session )
    , m_rect( other.m_rect )
    , m_type( other.m_type )
    , m_style( other.m_style )
#ifdef CORE_DO_UNDO_SUPPORT
    , m_old_border( other.m_old_border )
#endif
{}
void set_border_command::execute()
{
    if ( 20000 < m_rect.count() ) {
        throw std::logic_error( std::string( "You are trying to set border on " + boost::lexical_cast< std::string >( m_rect.count()  ) + " cells. This would allocate too much memory!" ) );
    }
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    border_manager& bm = ws->borders();
#ifdef CORE_DO_UNDO_SUPPORT
    if ( supports_do_undo::check( ws ) ) {
        m_old_border = bm.get_list_for_undo( m_rect );
    }
#endif
    bm.border( m_rect, m_type, m_style );
}

void set_border_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    assert( "un_execute called on a command that is on a temporary wb or on a cloned sheet!" && supports_do_undo::check( ws ) );
    ws->borders().apply_list_for_undo( m_rect, m_old_border );
#endif
}

DEFINE_CLONEABLE( set_border_command );

set_border_command::~set_border_command()
{}
