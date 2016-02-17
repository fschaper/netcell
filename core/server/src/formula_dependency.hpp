/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include "wss/type.hpp"
#include "wss/define.hpp"
#include "wss/allocation.hpp"
#include "wss/abstract_dependency.hpp"
#include "wss/locked_object.hpp"

/*!
 * \brief
 * class that contains formula handling, dependencies and calculation related things.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class formula_dependency
    : public abstract_dependency
{
public:
    /*!
    * \brief
    * return true in case the formula has precedents.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    virtual bool has_precedents() const;

    /*!
     * \brief
     * returns the precedents of the formula (if any)
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual referencetable_type precedents() const;

    /*!
     * \brief
     * returns the formula as localized string.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::string formula( const locale& l ) const;

    /*!
     * \brief
     * calculates the formula on demand and returns the
     * calculates value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( calculation_context& cc ) const;

    /*!
     * \brief
     * calculates the formula on demand and returns the
     * calculates value. (called from within the interpreter).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( interpreter_context& ic ) const;

    /*!
     * \brief
     * calculate the formula from withing the interpreter.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void calculate( interpreter_context& ic );

    /*!
     * \brief
     * returns true in case the dependency is dirty or volatile and uncached.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_dirty_or_uncached_volatile( calculation_context& cc ) const;

    /*!
    * \brief
    * returns true in case the formula is flagged dirty.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    virtual bool is_dirty() const;

    /*!
     * \brief
     * returns true in case the formula is flagged volatile
     * or depends on volatile dependencies.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_volatile() const;

    /*!
     * \brief
     * return true in case the kernel belong to an array formula.
     *
     * needed to conform to the cell_kernel interface.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_array() const;

    /*!
     * \brief
     * returns the array coverage.
     *
     * needed to conform to the cell_kernel interface.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual sheet_range array_coverage() const;

    /*!
     * \brief
     * flag the dependency dirty.
     *
     * one of our precedents changed and we have to recalculate upon request.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void flag_dirty();

    /*!
     * \brief
     * the formula or one of our precedents is of volatile state so
     * we have to raise the volatile state.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void raise_volatile_count();

    /*!
     * \brief
     * the formula or one of our precedents is no longer of volatile state so
     * we have to lower the volatile count.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void lower_volatile_count();

    /*!
     * \brief
     * returns the range covered by the formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    optional_sheet_range_type coverage( const sheet_point& position = sheet_point( 0, 0 ) ) const;

    /*!
     * \brief
     * destructor.
     *
     * will lover the volatile count on all dependencies if nesesarry.
     *
     * TODO: (fschaper) like the dirty flagging this has to become a
     * locking operation in abstract_dependency.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual ~formula_dependency();

protected:
    /*!
     * \brief
     * constructor.
     *
     * initialize the formula and flag all dependents as volatile if necessary.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_dependency( abstract_dependency& parent, locked_dependency_type& dependencies, ast_formula& ast );

    /*!
     * \brief
     * constructor.
     *
     * alternate constructor used for copying formulas.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_dependency( abstract_dependency& parent, locked_dependency_type& dependencies, const formula_dependency& other, const geometry::point& distance, bool use_copy_move, const sheet_range& source_range );

    /*!
     * \brief
     * copy construct the formula kernel.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_dependency( const formula_dependency& other );

protected:
    abstract_dependency& m_parent;
    locked_dependency_type& m_dependents;
    ::formula m_formula;
    unsigned int m_volatile_count;
    bool m_is_dirty;
    mutable variant m_cached_value;
};
