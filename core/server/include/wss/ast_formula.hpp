/**
 *  \file
 *  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
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

#include <string>
#include <wss/formula_parser.hpp>
#include <wss/type.hpp>

#include <boost/noncopyable.hpp>

class session;

/*!
 * \brief
 * AST representation of the formula
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE ast_formula
    : boost::noncopyable
{
    friend class formula;
    friend class position_independent_formula;
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ast_formula( ::session& s, const weak_worksheet_type& ws, const std::string& formula );

    bool is_view_independent() const;
    bool executes_on_set() const;

    static bool test_formula( ::session& s, const weak_worksheet_type& ws, const std::string& formula );
private:
    /*!
     * \brief
     * release the AST
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_parser::parsing_result_auto_type& disown();

private:
    formula_parser::parsing_result_auto_type m_ast;
};
