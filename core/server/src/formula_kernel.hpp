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

#include "wss/type.hpp"
#include "wss/define.hpp"
#include "wss/allocation.hpp"
#include "wss/locked_object.hpp"
#include "wss/ast_formula.hpp"
#include "wss/formula.hpp"
#include "wss/calculation.hpp"
#include "abstract_dependency.hpp"

/*!
 * \brief
 * class that contains formula handling, dependencies and calculation related things.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class formula_kernel
    : public boost::enable_shared_from_this<formula_kernel>
{
    friend class formula_calculation;

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const&, A5 const&, A6 const&, A7 const& );

    template< class T, class A1, class A2, class A3 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const& );

    template< class T, class A1, class A2>
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const& );

public:
    /*!
     * \brief
     * factory method.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_formula_kernel_type create( const shared_dependency_type& parent, ast_formula& ast, const referencetable_type& reference_table = referencetable_type() );

    /*!
     * \brief
     * factory method.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_formula_kernel_type create( const shared_dependency_type& parent, const formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& references );

    /*!
     * \brief
     * destructor.
     *
     * will lower the volatile count on all dependencies if necessary.
     *
     * TODO: (fschaper) like the dirty flagging this has to become a
     * locking operation in abstract_dependency.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~formula_kernel();

    /*!
     * \brief
     * let the formula kernel unregister itself.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unload();

    /*!
     * \brief
     * registers the formula kernels parent as dependent on the precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void connect_precedents();
    /*!
     * \brief
     * return true in case the formula has precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool has_precedents() const;

    /*!
     * \brief
     * returns the precedents of the formula (if any)
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    referencetable_type precedents() const;

    /*!
     * \brief
     * returns the formula as localized string.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    std::string formula( const locale& l ) const;

    /*!
     * \brief
     * return the current value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant value() const;

    /*!
     * \brief
     * returns a calculation object that will be used to trigger the calculation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_calculation delayed_calculation( calculation_context& cc );

    /*!
     * \brief
     * returns true in case the dependency is dirty or volatile and uncached.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    optional_variant_type fetch_cached_volatile( calculation_context& cc ) const;

    /*!
     * \brief
     * returns true in case the formula is flagged dirty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline bool is_dirty() const {
        return m_is_dirty;
    }


    /*!
     * \brief
     * returns true in case the formula is flagged volatile
     * or depends on volatile dependencies.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline bool is_volatile() const {
        return m_formula.is_volatile() || m_volatile_count > 0;
    }

    /*!
     * \brief
     * returns the number of volatile dependencies (including itself).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline unsigned long volatile_count() const {
        return m_volatile_count + ( m_formula.is_volatile() ? 1 : 0 );
    }

    /*!
    * \brief
    * returns the number of volatile dependencies (excluding itself).
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    unsigned long volatile_count_without_formula() const;

    /*!
     * \brief
     * flag the dependency dirty.
     *
     * one of our precedents changed and we have to recalculate upon request.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void flag_dirty();

    /*!
     * \brief
     * the formula or one of our precedents is of volatile state so
     * we have to raise the volatile state.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void internal_raise_volatile_count();

    /*!
     * \brief
     * the formula or one of our precedents is no longer of volatile state so
     * we have to lower the volatile count.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void internal_lower_volatile_count();

    /*!
     * \brief
     * returns the range covered by the formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    optional_sheet_range_type coverage() const;

protected:
    /*!
     * \brief
     * update the cached value in case the passed token is still valid.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void update_value( calculation_context& cc, const variant& v, long token_id );

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
    formula_kernel( const shared_dependency_type& parent, ast_formula& ast, const referencetable_type& reference_table );

private:
    /*!
     * \brief
     * constructor.
     *
     * alternate constructor used for copying formulas.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula_kernel( const shared_dependency_type& parent, const formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& references );

private:
    shared_dependency_type m_container;
protected:
    ::formula m_formula;
private:
    long m_update_token;
    unsigned int m_volatile_count;
    variant m_cached_value;
    bool m_is_dirty;
    bool m_unload_triggered;
};
