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

#pragma once

#include <wss/define.hpp>
#include <wss/base_command.hpp>
#include <wss/type.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/uuid/uuid.hpp>
#endif

/*!
 * \brief
 * delete a named formula
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class WSS_MODULE remove_named_formula_command
    : public base_command<i_command>
{
public:
    typedef void result_type;

    remove_named_formula_command( session& s, const std::string& name, const std::string& scope_ws );

    remove_named_formula_command( session& s, const std::string& id );

    /*!
        * \brief
        * execute the command functionality.
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
    virtual void execute();

    DECLARE_CLONEABLE( remove_named_formula_command );
private:
    std::string m_name;
    uuid_type m_uuid;
    long m_scope;
    weak_worksheet_type m_ws;
};

