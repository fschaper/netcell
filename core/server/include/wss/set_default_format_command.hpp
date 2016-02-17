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

#pragma once

#include <wss/define.hpp>
#include <wss/base_command.hpp>
#include <wss/i_undoable_command.hpp>
#include <wss/type.hpp>
#include "wss/user_return_format.hpp"

/*!
 * \brief
 * set the session default format
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
class WSS_MODULE set_default_format_command
    : public base_command<i_undoable_command>
{
public:
    typedef void result_type;

    set_default_format_command( session& s, user_return_format::default_format_set_type& new_format );

    virtual void execute();

    virtual void un_execute();

    DECLARE_CLONEABLE( set_default_format_command );

private:
    user_return_format::default_format_set_type m_new_format;
#ifdef CORE_DO_UNDO_SUPPORT
    user_return_format::default_format_set_type m_old_format;
#endif
};

