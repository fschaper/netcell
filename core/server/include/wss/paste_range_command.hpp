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

#pragma once

#include <wss/define.hpp>
#include <wss/abstract_undoable_command.hpp>
#include <wss/sheet_range.hpp>
#include <wss/variant.hpp>
#include <wss/session.hpp>
#include <wss/content_type.hpp>
#include <wss/clipboard.hpp>

/*!
 * \brief
 * paste range command.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE paste_range_command
    : public abstract_undoable_command
{
public:
    typedef void result_type;

    paste_range_command( session& s, const sheet_range& target, clipboard::clipboard_id_type id, int paste_type = content_type::all_plus_cf );

    virtual void execute();

    virtual void un_execute();

    DECLARE_CLONEABLE( paste_range_command );

private:
    sheet_range m_target;
    clipboard::clipboard_id_type m_clipboard_id;
    boost::optional<clipboard_entry> m_saved_clip_entry;
    int m_paste_type;
#ifdef CORE_DO_UNDO_SUPPORT
    variant m_old_value_target;
#endif
};

