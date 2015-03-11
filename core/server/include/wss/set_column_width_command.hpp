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
#include <wss/type.hpp>
#include <wss/sheet_layout_trait.hpp>

/*!
 * \brief
 * sets the width of an column
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE set_column_width_command
    : public abstract_undoable_command
{
public:
    set_column_width_command( session& s, const sheet_layout_trait::line_type& line, unsigned int column_width );

    /*!
     * \brief
     * execute the command functionality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void execute();

    virtual void un_execute();

    DECLARE_CLONEABLE( set_column_width_command );
private:
    sheet_layout_trait::integer_type m_new_column_width;
#ifdef CORE_DO_UNDO_SUPPORT
    sheet_layout_trait::sparse_indexed_vector_type m_old_column_width;
#endif
    sheet_layout_trait::line_type m_line;
    weak_worksheet_type m_worksheet;
};

