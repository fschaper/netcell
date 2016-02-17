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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#include <wss/type.hpp>
#include <wss/variant.hpp>
#include <wss/sheet_point.hpp>
#include <wss/destroying_auto_pointer.hpp>
#include <wss/i_dependency.hpp>
#include <wss/locked_object.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/thread/recursive_mutex.hpp>
# include <boost/enable_shared_from_this.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

#define FINAL

//#define COUNT_RAISE_VOLATILE_CALLS 1

/*!
 * \brief
 * Common functionality shared by all dependencies.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class abstract_dependency
    : public i_dependency
    , public boost::enable_shared_from_this<abstract_dependency>
{
protected:
    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;

public:
    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual ~abstract_dependency();

    /*!
     * \brief
     * returns the value of the dependency from within the interpreter.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    FINAL variant value( interpreter_context& ic ) const;

    /*!
     * \brief
     * calculate the dependency.
     *
     * will be called from within the interpreter.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    FINAL void calculate( interpreter_context& ic );

    /*!
     * \brief
     * flag the current instance and all registers dependents as being dirty.
     *
     * returns true in case the operation was successful.
     *
     * this method only locks and flags all dependencies that are
     * not already in dirty state. you will have to lock the calling
     * dependency so no currently unlocked cell can change it's state.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    FINAL bool flag_dirty( const bool flag_dirty_even_if_volatile = false );

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
    FINAL void raise_volatile_count();

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
    FINAL void lower_volatile_count();

    /*!
     * \brief
     * return true in case other dependencies are registered
     * with this object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool has_dependents() const;

    /*!
     * \brief
     * return all dependents from the dependency.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual const dependency_set_type& dependents() const;

    /*!
     * \brief
     * register dependent with the dependency.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    FINAL virtual void register_dependent( const shared_dependency_type& sd );

    /*!
     * \brief
     * unregister dependent with the dependency.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    FINAL virtual void unregister_dependent( const shared_dependency_type& sd );

    /*!
     * \brief
     * flags the dependency as moved.
     *
     * only implemented for named formulas and ignored by the rest of
     * the dependencies (like for example cells).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void flag_moved();

    /*!
     * \brief
     * lock the dependency list.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void lock();

    /*!
     * \brief
     * try lock the dependency list.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool try_lock();

    /*!
     * \brief
     * unlock the dependency list.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void unlock();

    /*!
     * \brief
     * returns the area covered by the dependency
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual optional_sheet_range_type coverage() const;

    virtual referencetable_type precedents( const shared_dependency_type& sd ) const {
        return referencetable_type();
    }

#ifdef _DEBUG
    /*!
     * \brief
     * friendly name for debug
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    FINAL void friendly_name( const std::string& name );

    /*!
     * \brief
     * friendly name for debug
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    FINAL std::string& friendly_name();

    /*!
     * \brief
     * get the current number of dependencies in the core
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static size_t use_count();
#endif
protected:
    /*!
     * \brief
     *
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual variant internal_value( interpreter_context& ) = 0;

    /*!
     * \brief
     *
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void internal_calculate( interpreter_context& ) = 0;

protected:
    /*!
     * \brief
     * constructor.
     *
     * it has to be ensured the object is always contained in
     * a boost::shared_ptr from all deriving classes.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    //#ifdef _DEBUG
    //    abstract_dependency( const std::string& originator_string );
    //#else
    abstract_dependency();
    //#endif
    /*!
     * \brief
     * list of dependencies which "depend" upon/(observe) the state of
     * the current object
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_dependency_set_type m_dependencies;

private:
    class locked_dependency_tree;
    class locked_dependency_multitree;
#ifdef COUNT_RAISE_VOLATILE_CALLS
    volatile static long m_raise_volatile_counter;
#endif // COUNT_RAISE_VOLATILE_CALLS
#ifdef _DEBUG
    std::string m_friendly_name;
    volatile static long m_usage_counter;
#endif
};
