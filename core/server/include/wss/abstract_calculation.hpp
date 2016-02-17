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

#include <wss/i_calculation.hpp>
#include <wss/variant.hpp>
#include <wss/calculation_setting.hpp>
#include <wss/interpreter_context.hpp>

#pragma once

class formula;
class calculation_context;

/*!
 * \brief
 * abstract base class for calculation objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE abstract_calculation
    : public i_calculation
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    abstract_calculation( calculation_context& cc, const shared_dependency_type& formula_container, const ::formula& formula, const variant& old_value, long token_id );

    /*!
     * \brief
     * return the interim calculation result.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual const variant& value() const;

    static inline bool check_minimum_change( const calculation_context& cc, const variant& old_value, const variant& new_value ) {
        return new_value.is_double() && ( ( ! old_value.is_double() ) || ( std::abs( new_value.numeric() - old_value.numeric() ) ) > cc.settings().minimum_change() );
    }

protected:
    inline bool check_minimum_change( const variant& new_value ) const {
        return check_minimum_change( m_cc, m_cached_value, new_value );
    }

    shared_dependency_type m_formula_container;
    ::formula const* m_formula;
    variant m_cached_value;
    long m_token;
    bool m_calculation_performed;
    calculation_context& m_cc;
};

