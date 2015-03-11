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
 *  <a href=<wss/http://www.jedox.com/license_palo_bi_suite.txt>>
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
#include "wss/reference_table.hpp"

class base_node;
struct positioned_op_codes;
/*!
 * \brief
 * generates an opcode sequence from an passed AST.
 *
 * \remarks
 * we could use boost::spirit to generate an AST directly
 * without having to create our own node set.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class opcode_generator
{
    class translator;
public:
    /*!
     * \brief
     * create opcode from passed AST
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static void create( const shared_dependency_type& initiator, const base_node& ast, positioned_op_codes& ops, const referencetable_type& references );
};
