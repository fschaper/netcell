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
 *  Vali Nitu <vali@yalos-solutions.com>
 */

#include "precompiled_header.hpp"
#include "wss/set_default_format_command.hpp"
#include "wss/invalid_session_exception.hpp"
#include "wss/session.hpp"


set_default_format_command::set_default_format_command( session& s, user_return_format::default_format_set_type& new_format )
    : base_command<i_undoable_command>::base_command( s )
    , m_new_format( new_format )
{
}

void set_default_format_command::execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    m_old_format = m_session.user_format().default_format();
#endif
    m_session.user_format().default_format( m_new_format );
}

void set_default_format_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    m_new_format = m_session.user_format().default_format();
    m_session.user_format().default_format( m_old_format );
#endif
}

DEFINE_CLONEABLE( set_default_format_command );
