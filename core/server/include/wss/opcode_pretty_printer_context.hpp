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
#include <wss/type.hpp>

struct positioned_op_codes;
class locale;
class translation_map;

/*!
 * \brief
 * context used during opcode traversal to generate a string representation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class opcode_pretty_printer_context
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    opcode_pretty_printer_context( const positioned_op_codes& c, const shared_dependency_type& current, const ::locale& l, bool resolve_named_formulas = false, const bool always_add_sheet_references = true  );

    /*!
     * \brief
     * constructor that is used when the pretty printing should be done with a given initiator
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    opcode_pretty_printer_context( const positioned_op_codes& c, const shared_dependency_type& current, const ::locale& l, const shared_dependency_type& d, bool resolve_named_formulas = false, const bool always_add_sheet_references = true );

    /*!
     * \brief
     * AST root node.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const positioned_op_codes& code() const;

    /*!
     * \brief
     * dependency for which the AST is to be reversed.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const shared_dependency_type& current() const;

    /*!
     * \brief
     * active translation table.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const ::translation_map& active_translation() const;

    /*!
     * \brief
     * returns true when named formulas should be resolved.
     *
     * \remarks
     * resolving named formulas in this context means that
     * instead of just the name of the named formula the
     * actual AST is expanded.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool resolve_named_formulas() const;

    inline const bool always_add_sheet_references() const {
        return m_always_add_sheet_references;
    }

    /*!
     * \brief
     * check if an initiator was given
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    bool initiator_given() const;

    /*!
     * \brief
     * get the initiator
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    const shared_dependency_type& initiator() const;

private:
    const positioned_op_codes& m_code;
    const shared_dependency_type& m_current;
    const translation_map& m_active_translation_map;
    //carefull this doesn't need to be set!
    shared_dependency_type m_initiator;
    const bool m_resolve_named_formulas;
    const bool m_always_add_sheet_references;
    opcode_pretty_printer_context& operator =( const opcode_pretty_printer_context& );
};
