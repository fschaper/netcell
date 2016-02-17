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

#include <wss/interpreter_variant.hpp>
#include <wss/calculation_context.hpp>
#include <wss/with_initiator.hpp>
#include <wss/i_dependency.hpp>
#include <wss/stack.hpp>

class i_calculation;

/*!
 * \brief
 * information that need be available during an single
 * calculation run.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE interpreter_context
    : boost::noncopyable
    , public with_initiator
{
public:
    typedef ::stack<interpreter_variant> calculation_stack_type;

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    interpreter_context( const shared_dependency_type& d, ::i_calculation& alias, calculation_context& cc );

    /*!
     * \brief
     * constructor that is used when the interpreter should work with a named formula.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    interpreter_context( const shared_dependency_type& d, ::i_calculation& alias, calculation_context& cc, const shared_dependency_type& nf );

    inline ~interpreter_context() {
        m_calculation_context.interpreter_context( NULL );
    }
    /*!
     * \brief
     * will return the calculation object that will be used
     * to resolve cyclic calculations.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::i_calculation& alias();


    /*!
     * \brief
     * will return true in case the initiator is a array cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool has_array_return_type() const;

    /*!
     * \brief
     * returns the calculation stack.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    calculation_stack_type& stack();

    /*!
     * \brief
     * returns the calculation context.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    calculation_context& context();

    /*!
     * \brief
     * returns the locale used for the current calculation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const ::locale& locale() const;

    /*!
     * \brief
     * will return true if we are currently inside another function
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    bool is_inside_function() const;

    /*!
     * \brief
     * raise the inside function count
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void raise_inside_function_count();

    /*!
     * \brief
     * lower the inside function count
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void lower_inside_function_count();

    void fill_array_with_empty_values();

    /*!
     * \brief
     * set last known function return_type in the context
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void last_return_type( return_type_format::type return_type );

    /*!
     * \brief
     * get the last known function return_type in the context
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    return_type_format::type last_return_type() const;

    /*!
     * \brief
     * counts the number of lazy function calls that are nested (for instance function "if")
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    inline void lower_inside_lazy_function_count() {
        assert( "inside_lazy_function_count went below zero!" && m_inside_lazy_function_count > 0 );
        --m_inside_lazy_function_count;
    }
    inline void raise_inside_lazy_function_count() {
        ++m_inside_lazy_function_count;
    }
    inline int inside_lazy_function_count() {
        return m_inside_lazy_function_count;
    }
private:
    ::i_calculation& m_alias;
    calculation_context& m_calculation_context;
    calculation_stack_type m_stack;
    bool m_is_array_formula;
    int m_is_inside_function_count;
    return_type_format::type m_last_return_type;
    int m_inside_lazy_function_count;

};
