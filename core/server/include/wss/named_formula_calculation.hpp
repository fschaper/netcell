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

#include <wss/abstract_calculation.hpp>

/*!
 * \brief
 * calculation object for named formulas.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class named_formula_calculation
    : public abstract_calculation
{
public:
    /*!
     * \brief
     * default constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    named_formula_calculation( const named_formula_calculation& other );

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    named_formula_calculation( calculation_context& cc, const shared_named_formula_kernel_type& kernel, const shared_dependency_type& formula_container, const ::formula& f, const variant& old_value, long token_id );

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~named_formula_calculation();

    /*!
     * \brief
     * calculates the formula by first calculating all of it's precedents.
     *
     * will calculate the formula in case the dirty flag is set on the formula.
     * in case the operation results in a new value will flag all dependents as
     * dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void operator()( const shared_dependency_type& named_formula, long different_token_id );

    void operator_with_different_initiator( const shared_dependency_type& named_formula );
    variant operator_with_different_initiator( interpreter_context& ic );

    /*!
     * \brief
     * calculates the formula by first calculating all of it's precedents.
     *
     * will calculate the formula in case the dirty flag is set on the formula.
     * in case the operation results in a new value will flag all dependents as
     * dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant operator()( interpreter_context& ic );
    void operator()();
private:
    inline bool named_formula_initiator( const shared_dependency_type& named_formula, long different_token_id );
    inline const shared_dependency_type& named_formula_initiator() const {
        return m_named_formula;
    }
    inline bool has_named_formula_initiator() const {
        return m_named_formula;
    }
    shared_named_formula_kernel_type m_kernel;
    shared_dependency_type m_named_formula;
};

