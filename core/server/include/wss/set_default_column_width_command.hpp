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
#include <wss/define.hpp>

/*!
 * \brief
 * sets the default column width
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE set_default_column_width_command
    : public abstract_undoable_command
{
public:
    typedef void result_type;

    set_default_column_width_command( session& s, unsigned int column_width );

    /*!
     * \brief
     * execute the command functionality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void execute();

    /*!
     * \brief
     * execute the command functionality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void un_execute();

    /*!
     * \brief
     * clone the command.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    DECLARE_CLONEABLE( set_default_column_width_command );

private:
#ifdef CORE_DO_UNDO_SUPPORT
    unsigned int m_old_height;
#endif
    unsigned int m_new_width;
    weak_worksheet_type m_worksheet;
};

