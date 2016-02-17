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

#include <wss/variable_map.hpp>
#include <wss/destroying_auto_pointer.hpp>

class base_node;

/*!
 * \brief
 * formula parsing result
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE formula_parsing_result
    : boost::noncopyable
{
public:
    /*!
     * \brief
     * constrcutor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_parsing_result();

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~formula_parsing_result();

    /*!
     * \brief
     * list of variables used in the formula
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const variable_map& variable() const;

    /*!
     * \brief
     * returns true in case the formula could be entirely parsed.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_success() const;

    /*!
     * \brief
     * returns true in case the formula has volatile functions.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool has_volatile() const;

    /*!
     * \brief
     * returns true in case the formula has view independent functions.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    bool view_independent() const;

    /*!
     * \brief
     * returns true in case the formula has view independent functions.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    bool executes_on_set() const;

    /*!
     * \brief
     * pass ownership of the contained AST
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    destroying_auto_pointer<base_node> take_ownership() const;

protected:
    bool m_is_success;
    bool m_has_volatile;
    variable_map m_variable;
    destroying_auto_pointer<base_node> m_root;
    bool m_has_view_independent;
    bool m_execute_on_set;
};

