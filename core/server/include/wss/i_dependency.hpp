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
#include <wss/sheet_point.hpp>
#include <wss/sheet_range.hpp>
#include <wss/reference_table.hpp>
#include <wss/locked_object.hpp>
#include <wss/i_lockable.hpp>
#include <set>

class variant;
class session;
class locale;
class calculation_context;
class interpreter_context;
class with_initiator;

/*!
 * \brief
 * interface all dependencies must implement.
 *
 * f.ex. a formula cell can be dependent on other cells
 * or to just give an example for example named ranges
 * (or how we call it "named formulas").
 * the relationship between the cell and f.ex. the named formula (or another
 * cell) is expressed via the i_dependency interface.
 *
 * In order to calculate A1 in "A1=B1+C2" we need to calculate B1 and C2.
 * Any change to B1 and C2 would in turn also require a recalculation of A1.
 * The i_dependency interface gives us the means to inform A1 that it needs to
 * update.
 *
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class i_dependency
    : public i_lockable

{
public:
    enum dependency_type {
        formula_type
        , named_formula_type
        , named_formula_wrapper_type
        , cell_type
        , free_formula_type
        , layout_coord_type
    };

    //this is optimization for dynarange operations where we don't clear the whole volatile cache
    enum chache_to_put_in {
        general = 0
        , persistent
    };

    virtual ~i_dependency() {}
    virtual dependency_type type() const = 0;
    virtual bool has_formula() const = 0;
    virtual bool has_precedents() const = 0;
    virtual bool has_dependents() const = 0;
    virtual referencetable_type precedents() const = 0;
    virtual referencetable_type precedents( const shared_dependency_type& sd ) const = 0;

    /*!
     * \brief
     * returns a list of dependencies from the dependency.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual const dependency_set_type& dependents() const = 0;

    /*!
     * \brief
     * returns the value of the dependency from a within a calculation round.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( calculation_context& ) const = 0;

    /*!
     * \brief
     * returns the value of the dependency from within the interpreter.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant value( interpreter_context& ) const = 0;

    /*!
     * \brief
     * set the dependency to the passed value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void value( session&, const variant&, const sheet_point& position = sheet_point( 0, 0 ) ) = 0;

    /*!
     * \brief
     * returns the formula (if any) from the dependency parsed with the passed locale setting.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::string formula( const locale& l ) const = 0;

    /*!
     * \brief
     * calculate the dependency.
     *
     * will be called from within the interpreter.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void calculate( interpreter_context& ) = 0;

    /*!
     * \brief
     * calculate the dependency.
     *
     * calculate the dependency using a calculation_context. The
     * calculation_context maintains f.ex. the volatile cache.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void calculate( calculation_context& ) = 0;

    /*!
     * \brief
     * returns the worksheet associated with "this" dependency.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual weak_worksheet_type worksheet() const = 0;

    /*!
     * \brief
     * register a dependency as observing "this" dependency.
     *
     * for a cell A1 with the formula "=B1+C1", A1 would be registered
     * as dependent on B1 and C1.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void register_dependent( const shared_dependency_type& ) = 0;

    /*!
     * \brief
     * unregister a dependency from observing "this" dependency.
     *
     * for a cell A1 with the formula "=B1+C1", A1 would be registered
     * as dependent on B1 and C1.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void unregister_dependent( const shared_dependency_type& ) = 0;

    /*!
     * \brief
     * will return true in case the cell is marked for recalculation or is of volatile state
     * and has not as of yet been cached for the current calculation cycle.
     *
     * \see
     * is_dirty | is_volatile
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual optional_variant_type fetch_cached_volatile( calculation_context& cc ) const = 0;

    /*!
     * \brief
     * returns true in case the dependency is in need of recalculation.
     *
     * if somebody sets a dependency to some value the value itself and all
     * dependents of the dependency will not be calculated immediately but instead
     * be flagged as being in the need of re-calculation. A state we call "dirty".
     * So in case the is_dirty flag is set that means that either one of the precedents
     * of this dependency or the dependency itself has changed.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_dirty() const = 0;

    /*!
     * \brief
     * For the most formulas we are able to cache the result of an operation but for
     * a small subset of functions we are not able to do so because their result depends
     * on some external state that can change without our knowledge. An example of this
     * kind of functions would be the RAND() and TIME() functions and all functions that
     * access some external database (like PALO). If a formula contains a function like
     * this the result of the formula will be treated as "volatile".
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_volatile() const = 0;

    /*!
     * \brief
     * returns true if the dependency is part of a cell array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool is_array() const = 0;

    /*!
     * \brief
     * in case the dependency is part of a cell array will return the size of the array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual sheet_range array_coverage() const = 0;

    /*!
     * \brief
     * marks the cell and all dependents for recalculation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool flag_dirty( const bool flag_dirty_even_if_volatile = false ) = 0;

    /*!
     * \brief
     * returns the position of the dependency on a sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual const sheet_point& position() const = 0;

    /*!
     * \brief
     * raised the volatile count.
     *
     * in case the dependency or one of it's precedents is marked as being volatile
     * all dependent cells are also marked as being volatile. An internal counter keeps
     * track of the number of volatile dependencies. If a dependency has volatile
     * precedents > 0 or is in itself volatile is_volatile will return true.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void raise_volatile_count() = 0;

    /*!
     * \brief
     * lowers the volatile count.
     *
     * the reverse of the method raise_volatile_count.
     * see the documentation of raise_volatile_count for more information.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void lower_volatile_count() = 0;

    /*!
     * \brief
     * returns the current volatile count
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual unsigned long volatile_count() const = 0;

    /*!
     * \brief
     * returns the current volatile count (excluding self)
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual unsigned long volatile_count_without_formula() const = 0;

    /*!
    * \brief
    * marks the cell for recalculation.
    *
    * this one is protected because only the current object
    * is flagged and all dependents are ignored. it's the
    * responsibility of the object "flagging" dirty to walk
    * the dependency tree to flag all dependents dirty.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    virtual void internal_flag_dirty() = 0;

    /*!
     * \brief
     * raise the volatile count of the dependency
     *
     * does not update the object dependencies but only the
     * object itself
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_raise_volatile_count() = 0;

    /*!
     * \brief
     * lower the volatile count of the dependency
     *
     * does not update the object dependencies but only the
     * object itself
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_lower_volatile_count() = 0;

    /*!
     * \brief
     * a cell inside a named_formula got moved, we have to tell that to the named formula!
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual void flag_moved() = 0;

    /*!
     * \brief
     * the area that is covered by the dependency's formula
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual optional_sheet_range_type coverage() const = 0;

    /*!
     * \brief
     * must return empty values in array expansions instead of N/A
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    virtual void must_fill_with_empty() {};

    /*!
     * \brief
     * overwrite this and return false if more persistent caching is
     * needed during dynarange operations (used in worksheet elements)
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual bool put_in_general_cache() const {
        return true;
    }

#ifdef _DEBUG
    /*!
     * \brief
     * debug information to make tracking of dependencies easier
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    virtual std::string get_debug_identifier() const = 0;
#endif // _DEBUG
};
