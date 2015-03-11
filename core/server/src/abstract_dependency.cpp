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

#include "precompiled_header.hpp"
#include "abstract_dependency.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/calculation.hpp"
#include "actualize_dependencies.hpp"

/*!
 * \brief
 * careful, this will generate a lot of output!
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
#define LOG_TRACE_DEPENDENCIES 1

#if defined(LOG_TRACE_DEPENDENCIES) && defined(_DEBUG) && !defined(LOG_CORE_TRACE_DEPENDENCIES)
#   include <fstream>
#   include "debug_logging_helper.hpp"
#   include "wss/a1conversion.hpp"
#   include "core_logging.hpp"
//#   define LOG_CORE_TRACE_DEPENDENCIES(message) LOG_CORE_TRACE(message)
#   define LOG_CORE_TRACE_DEPENDENCIES(message)
#else
#   define LOG_CORE_TRACE_DEPENDENCIES(message)
#endif // LOG_TRACE_DEPENDENCIES
#include "named_formula_dependency_wrapper.hpp"
#include "wss/singleton.hpp"
#ifdef _DEBUG
#include "boost/detail/interlocked.hpp"
#endif // _DEBUG
#ifdef COUNT_RAISE_VOLATILE_CALLS
#include "boost/detail/interlocked.hpp"
#endif // COUNT_RAISE_VOLATILE_CALLS


/*!
 * \brief
 * little helper to make the comparisons more meaningful
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
struct abstract_dependency_helper : non_instantiable {
    static bool would_become_volatile( const unsigned long current_count ) {
        return current_count == 0;
    }

    static bool would_become_non_volatile( const unsigned long current_count ) {
        return current_count == 1;
    }
};

/*!
 * \brief
 * lock all dependencies we want to perform an operation on.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class abstract_dependency::locked_dependency_tree
    : boost::noncopyable
{
    typedef boost::detail::try_lock_wrapper<i_dependency> lock_type;

    typedef boost::shared_ptr<lock_type> shared_lock_type;
    typedef std::list<shared_lock_type> lock_list_type;

public:
    typedef dependency_set_type::iterator iterator;
    typedef dependency_set_type::const_iterator const_iterator;

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_dependency_tree( const i_dependency& skip )
        : m_skip( skip ) {}

    bool add( const shared_dependency_type& sd ) {
        if ( sd.get() == &m_skip || m_dependencies.find( sd ) != m_dependencies.end() ) {
            return true;
        }

        shared_lock_type sl( boost::make_shared<lock_type>( boost::ref( *sd ) ) );
        if ( ! sl->owns_lock() ) {
            return false;
        }

        m_dependencies.insert( sd );
        m_lock_list.push_back( sl );

        return true;
    }

    bool has( const shared_dependency_type& sd ) const {
        return m_dependencies.find( sd ) != m_dependencies.end();
    }

    iterator begin() {
        return m_dependencies.begin();
    }

    const_iterator begin() const {
        return m_dependencies.begin();
    }

    iterator end() {
        return m_dependencies.end();
    }

    const_iterator end() const {
        return m_dependencies.end();
    }

    bool empty() const {
        return m_dependencies.empty();
    }

private:
    const i_dependency& m_skip;
    dependency_set_type m_dependencies;
    lock_list_type m_lock_list;
};

/*!
 * \brief
 * lock all dependencies we want to perform an operation on.
 * same as above, but can have one element multiple times
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class abstract_dependency::locked_dependency_multitree
    : boost::noncopyable
{
    typedef map_to_use<shared_dependency_type, size_t>::type dependency_multiset_type;
    typedef boost::detail::try_lock_wrapper<i_dependency> lock_type;

    typedef boost::shared_ptr<lock_type> shared_lock_type;
    typedef std::list<shared_lock_type> lock_list_type;

public:
    typedef dependency_multiset_type::iterator iterator;
    typedef dependency_multiset_type::const_iterator const_iterator;

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_dependency_multitree( const i_dependency& skip )
        : m_skip( skip ) {}

    bool add( const shared_dependency_type& sd ) {
        if ( sd.get() == &m_skip || sd->type() == i_dependency::layout_coord_type ) {
            return true;
        }

        iterator it( m_dependencies.find( sd ) );
        if ( it != m_dependencies.end() ) {
            ++( it->second );
            return true;
        }


        shared_lock_type sl( boost::make_shared<lock_type>( boost::ref( *sd ) ) );
        if ( ! sl->owns_lock() ) {
            return false;
        }

        m_dependencies[sd] = 1;
        m_lock_list.push_back( sl );

        return true;
    }

    bool has( const shared_dependency_type& sd ) const {
        return m_dependencies.find( sd ) != m_dependencies.end();
    }

    iterator begin() {
        return m_dependencies.begin();
    }

    const_iterator begin() const {
        return m_dependencies.begin();
    }

    iterator end() {
        return m_dependencies.end();
    }

    const_iterator end() const {
        return m_dependencies.end();
    }

    bool empty() const {
        return m_dependencies.empty();
    }

private:
    const i_dependency& m_skip;
    dependency_multiset_type m_dependencies;
    lock_list_type m_lock_list;
};

//#ifdef _DEBUG
//abstract_dependency::abstract_dependency( const std::string& originator_string ) : m_originator_string( originator_string )
//{}
//#else
abstract_dependency::abstract_dependency()
{
#ifdef _DEBUG
    BOOST_INTERLOCKED_INCREMENT( &m_usage_counter );
#endif // _DEBUG

}
//#endif

abstract_dependency::~abstract_dependency()
{
#ifdef _DEBUG
    assert( "can't go below zero on the use count of dependencies!" && m_usage_counter != 0 );
    BOOST_INTERLOCKED_DECREMENT( &m_usage_counter );
#endif // _DEBUG

}

variant abstract_dependency::value( interpreter_context& ic ) const
{
    // (fschaper) in case this dependency started the calculation
    // we retrieve the current calculated value directly from
    // the calculation object to deal with the recursion.
    LOG_CORE_TRACE_DEPENDENCIES( "value called on : " + debug_logging_helper::get_identifier( const_cast<abstract_dependency*>( this )->shared_from_this() ) );
    if ( ic.initiator().get() == this ) {
        return ic.alias().value();
    } else {
        // (fschaper) regular value fetching. possibly starting another calculation
        // round if some precedents value changed in between.
        return const_cast<abstract_dependency*>( this )->internal_value( ic );
    }
}

void abstract_dependency::calculate( interpreter_context& ic )
{
    // (fschaper) in case this dependency started the calculation
    // we pass the call directly to the calculation object
    // to deal with the recursion.
    LOG_CORE_TRACE_DEPENDENCIES( "calculate called on : " + debug_logging_helper::get_identifier( shared_from_this() ) );

    if ( ic.caller().get() != this ) {
        interpreter_context::scoped_change_caller( ic, shared_from_this() );

        internal_calculate( ic );
    } else {
        internal_calculate( ic );
    }
}

bool abstract_dependency::has_dependents() const
{
    return !( * m_dependencies.lock() ).empty();
}

const dependency_set_type& abstract_dependency::dependents() const
{
    // (fschaper) return a copy of the dependency set.
    // (fhofmann) don't return a copy because its just too slow!
    // since it's a copy it does not necessarily reflect
    // the objects state by the time we release the lock.
    return locked_dependency_set_type::access( m_dependencies );
}


#ifdef _DEBUG
struct dep_tree : singleton<dep_tree> {
    typedef std::set<shared_dependency_type> child_list_type;
    typedef std::map<shared_dependency_type, child_list_type> tree_type;

    std::ostream& logger() {
        static std::auto_ptr<std::fstream> logging_stream;

        if (  logging_stream.get() == NULL ) {
            // (fschaper) this code is not thread safe. multiple requests issued by the UI at the same time
            // may re-initialize the logging stream. do not enable for release builds and use with care while debugging.
            logging_stream.reset( new std::fstream( "c:\\dependency_stream.txt", std::ios::out ) );
        }
        return *logging_stream;
    }

    void insert( shared_dependency_type from, shared_dependency_type to ) {
        tree[from].insert( to );
    }

    void remove( shared_dependency_type from, shared_dependency_type to ) {
        tree_type::iterator it( tree.find( from ) );
        if ( it != tree.end() ) {
            if ( it->second.find( to ) != it->second.end() ) {
                it->second.erase( to );
                if ( it->second.empty() ) {
                    tree.erase( it );
                }

            }

        }

    }


    struct node_type;
    typedef boost::shared_ptr<node_type> shared_node_type;
    typedef std::set<shared_node_type> node_list_type;

    struct node_type {
        node_type( shared_dependency_type sd ) : d( sd ) {}

        bool operator<( const node_type& other ) const {
            return d < other.d;
        }

        bool operator==( const node_type& other ) const {
            return d == other.d;
        }

        shared_dependency_type d;
        node_list_type children;
    };

    shared_node_type find_node_or_create( shared_dependency_type d ) const {
        foreach( shared_node_type n, current_tree_nodes ) {
            if ( n->d == d ) {
                return n;
            }
        }

        shared_node_type return_val( new node_type( d ) );
        current_tree_nodes.insert( return_val );
        return return_val;
    }

    node_list_type build_tree() const {
        current_tree_nodes.clear();
        typedef node_list_type::const_iterator const_iterator;
        foreach( tree_type::value_type v, tree ) {
            shared_node_type n = find_node_or_create( v.first );
            foreach( shared_dependency_type d, v.second ) {
                shared_node_type new_node = find_node_or_create( d );
                n->children.insert( new_node );
            }
        }
        return current_tree_nodes;
    }

    void print_node( std::ostream& os, shared_node_type n, const size_t current_tabs ) const {
        if ( n ) {
            os << current_tabs;
            for ( size_t i = 0; i < current_tabs; ++i ) {
                os << " ";
            }
            os << debug_logging_helper::get_identifier( n->d );
            os << std::endl;
            foreach( shared_node_type sn, n->children ) {
                print_node( os, sn, current_tabs + 1 );
            }
        }

    }



    tree_type tree;
    mutable node_list_type current_tree_nodes;
};

std::ostream& operator<<( std::ostream& os, dep_tree& t )
{
    foreach( dep_tree::shared_node_type n, t.build_tree() ) {
        t.print_node( os, n, 0 );
        os << std::endl;
    }
    return os;
}
#endif // _DEBUG

void abstract_dependency::register_dependent( const shared_dependency_type& sd )
{
    // update the list of dependencies with the new object
#ifdef _DEBUG
    //     dep_tree::instance().insert( shared_from_this(), sd );
    //     dep_tree::instance().logger() << "dumping dependency_tree" << std::endl
    //                                   << dep_tree::instance();
#endif
    LOG_CORE_TRACE_DEPENDENCIES( "registering : " + debug_logging_helper::get_identifier( sd ) + " as dependent of : " + debug_logging_helper::get_identifier( const_cast<abstract_dependency*>( this )->shared_from_this() ) );

    const bool is_a_known_dependency = !( ( *m_dependencies.lock() ).insert( sd ).second );

    // in case we try to connect the object to itself we have nothing more to do.
    if ( sd.get() != this && ! is_a_known_dependency ) {

        // in case the current object is of volatile nature, pass the volatile
        // state on to the registering dependency.
        if ( is_volatile() ) {
            sd->raise_volatile_count();
            sd->internal_raise_volatile_count();
        } else if ( is_dirty() ) {
            // in case the current object is dirty, so is the registering dependency.
            sd->flag_dirty();
        }

    }
}

void abstract_dependency::unregister_dependent( const shared_dependency_type& sd )
{
#ifdef _DEBUG
    //     dep_tree::instance().remove( shared_from_this(), sd );
    //     dep_tree::instance().logger() << "dumping dependency_tree" << std::endl
    //                                   << dep_tree::instance();
#endif // _DEBUG

    LOG_CORE_TRACE_DEPENDENCIES( "unregistering dependent: " + debug_logging_helper::get_identifier( sd ) + " from : " + debug_logging_helper::get_identifier( const_cast<abstract_dependency*>( this )->shared_from_this() ) );
    //     assert( "raw named_formulas shouldn't register as dependent of anything, ever, so theres no need to unregister them!"
    //             && sd->type() != i_dependency::named_formula_type );

    // see comment below for an explanation of why we do not simply erase the dependency.
    const bool dependency_has_been_erased_from_list = ( *m_dependencies.lock() ).erase( sd ) != 0;

    // (fschaper) only lower the volatile count in case that the dependency was registered.
    // a double de-registration does f.ex. occur in test_named_formula_with_volatile_value_wb_scope
    // when the workbook goes out of scope. maybe we can solve this case differently.
    if ( dependency_has_been_erased_from_list ) {
        if ( sd.get() != this ) {
            if ( is_volatile() ) {
                sd->lower_volatile_count();
                sd->internal_lower_volatile_count();
            }
        }
    }
}

FINAL bool abstract_dependency::flag_dirty( const bool flag_dirty_even_if_volatile /* = false */ )
{
    if ( flag_dirty_even_if_volatile && is_volatile() ) {
        //(fhofmann) don't do anything if we're volatile
        return true;
    }
    LOG_CORE_TRACE_DEPENDENCIES( "flagging cell and dependents dirty: " + debug_logging_helper::get_identifier( shared_from_this() ) );
    typedef std::stack<shared_dependency_type> shared_dependency_stack_type;

    locked_dependency_tree dependency_set( *this );
    shared_dependency_stack_type dependency_stack;

    dependency_stack.push( shared_from_this() );
    shared_dependency_type current;

    // (fschaper) traverse the dependency tree and try to lock all dependencies that are not
    // marked dirty.
    //
    // the only dependencies we need to lock are those that are not volatile
    // and that are not already dirty. it is an requirement of this method that
    // the calling derived object prevents the dependent cells from changing their
    // dirty state (which they could only do if they could access the derived
    // object).
    do {
        current = dependency_stack.top();
        dependency_stack.pop();

        // (fschaper) by adding the dependency we are trying to get exclusive access to all dependencies.
        // in case we can not aquire a lock on the dependency the add method will return false and
        // we will abort this operation thereby releasing all active locks
        // that we are currently holding on the stack.
        // the first dependency we will flag dirty is "us".
        bool could_lock_dependency = dependency_set.add( current );
        if ( ! could_lock_dependency ) {
            return false;
        }

        if ( current->has_dependents() ) {
            // (fschaper) from here on the dependency object of "current" is locked and we may
            // access "object" directly.
            const dependency_set_type& dep = current->dependents();
            for ( dependency_set_type::const_iterator it = dep.begin(), end_it = dep.end(); it != end_it; ++it ) {
                //foreach( const shared_dependency_type & dep, current->dependents() ) {
                // we may not put ourselves back on the stack, we only need to put dependencies on that are not already dirty
                // or volatile and we can ignore those that we have already seen.
                if ( this != ( *it ).get() && ! ( *it )->is_dirty() && ! ( *it )->is_volatile() && ! dependency_set.has( *it ) ) {
                    dependency_stack.push( *it );
                }
            }
        }
    } while ( ! dependency_stack.empty() );

    // (fschaper) all dependencies that did not previously have the dirty flag active
    // are now locked. we didn't need to address the dependencies that were
    // already flagged as being dirty since the cell they depend on (the dependency
    // calling from where we are calling this function) is supposed to be already
    // locked. since they depend on this cell they will be waiting for us before
    // they can change their state.

    LOG_CORE_TRACE_DEPENDENCIES( debug_logging_helper::list_dependencies( dependency_set ) );

    // flag all dependencies that didn't have the dirty flag assigned as dirty.
    std::for_each( dependency_set.begin(), dependency_set.end(), boost::bind( &i_dependency::internal_flag_dirty, _1 ) );

    return true;
}

template<int volatile_count_to_trigger>
inline bool check_volatile_descent( const i_dependency* this_ptr, const shared_dependency_type& dep, const shared_dependency_type& current )
{
    return
        // don't add this
        ( dep.get() != this_ptr )
        &&
        //don't add layout coords
        ( dep->type() != i_dependency::layout_coord_type )
        &&
        (
            // the first level of dependencies will always be flagged
            current.get() == this_ptr
            // in case the dependency was already volatile we need to descent no further than this
            || current->volatile_count() == volatile_count_to_trigger
            // TODO check if this is needed!
            || current->type() == i_dependency::named_formula_wrapper_type );

}
#ifdef COUNT_RAISE_VOLATILE_CALLS
volatile long abstract_dependency::m_raise_volatile_counter = 0;
#endif // COUNT_RAISE_VOLATILE_CALLS

FINAL void abstract_dependency::raise_volatile_count()
{
#ifdef COUNT_RAISE_VOLATILE_CALLS
    BOOST_INTERLOCKED_INCREMENT( &m_raise_volatile_counter );
#endif // COUNT_RAISE_VOLATILE_CALLS


    if ( abstract_dependency_helper::would_become_volatile( volatile_count_without_formula() ) ) {
        LOG_CORE_TRACE_DEPENDENCIES( "raising volatile count of dependents of: " + debug_logging_helper::get_identifier( shared_from_this() ) );
        bool could_lock_dependency = false;
        do {
            typedef std::stack<shared_dependency_type> shared_dependency_stack_type;

            locked_dependency_multitree dependency_set( *this );
            shared_dependency_stack_type dependency_stack;

            dependency_stack.push( shared_from_this() );
            shared_dependency_type current;

            // (fschaper) traverse the dependency tree and try to lock all dependencies
            do {
                current = dependency_stack.top();
                dependency_stack.pop();

                // (fschaper) by adding the dependency we are trying to get exclusive access to all dependencies.
                // in case we can not aquire a lock on the dependency the add method will return false and
                // we will abort this operation thereby releasing all active locks
                // that we are currently holding on the stack.
                // the first dependency we will flag volatile is "us".
                could_lock_dependency = dependency_set.add( current );
                if ( ! could_lock_dependency ) {
                    continue;
                }

                if ( current->has_dependents() ) {
                    // (fschaper) from here on the dependency object of "current" is locked and we may
                    // access "object" directly.
                    const dependency_set_type& current_deps = current->dependents();
                    for ( dependency_set_type::const_iterator it = current_deps.begin(), end_it = current_deps.end(); it != end_it; ++it ) {
                        // (fschaper) to prevent recursion we do not put ourselves on the stack here
                        // the direct dependencies of a volatile dependency will always have their volatile count
                        // raised but we only descent deeper than this (flag a dependency of a dependency) in case
                        // it does not already have the volatile flag set.
                        // f.ex.:
                        // A1=RAND(), B1=RAND(), C1=A1+B1, D1=C1
                        // C1 will have a volatile count of 2 and D1 of 1
                        // in case we would assign a non volatile formula to B1 we would now lower the volatile
                        // count of C1 to 1 but since C1 itself is still volatile we don't need to proceed further
                        // than this and leave D1 with its volatile count of 1.
                        if ( check_volatile_descent<0>( this, *it, current ) ) {
                            if ( !dependency_set.has( *it ) ) {
                                dependency_stack.push( *it );
                            } else {
                                dependency_set.add( *it );
                            }
                        }
                    }
                }
            } while ( ! dependency_stack.empty() );

            LOG_CORE_TRACE_DEPENDENCIES( debug_logging_helper::list_dependencies( dependency_set ) );

            // raise the volatile flag for all dependencies.
            for ( locked_dependency_multitree::const_iterator it = dependency_set.begin(), end_it = dependency_set.end(); it != end_it; ++it ) {
                for ( size_t count = 0, end_count = it->second; count < end_count; ++count ) {
                    ( it->first )->internal_raise_volatile_count();
                }
            }

            //std::for_each( dependency_set.begin(), dependency_set.end(), boost::bind( &i_dependency::internal_raise_volatile_count, _1 ) );
        } while ( ! could_lock_dependency );
    }
}

FINAL void abstract_dependency::lower_volatile_count()
{
    //only do something on dependents if we would reach a volatile count of zero
    if ( abstract_dependency_helper::would_become_non_volatile( volatile_count() ) ) {

        LOG_CORE_TRACE_DEPENDENCIES( std::string( "lowering volatile count of dependents of: " ) + debug_logging_helper::get_identifier( shared_from_this() ) );
        bool could_lock_dependency = false;
        do {
            typedef std::stack<shared_dependency_type> shared_dependency_stack_type;

            locked_dependency_multitree dependency_set( *this );
            shared_dependency_stack_type dependency_stack;

            dependency_stack.push( shared_from_this() );
            shared_dependency_type current;
            // (fschaper) traverse the dependency tree and try to lock all dependencies
            do {
                current = dependency_stack.top();
                dependency_stack.pop();

                if ( current->has_dependents() ) {
                    // (fschaper) to prevent recursion we do not put ourselves on the stack here
                    // the direct dependencies of a volatile dependency will always have their volatile count
                    // lowered but we only descent deeper than this (flag a dependency of a dependency) in case
                    // it would loose its volatile qualifier.
                    // f.ex.:
                    // A1=RAND(), B1=RAND(), C1=A1+B1, D1=C1
                    // C1 will have a volatile count of 2 and D1 of 1
                    // in case we would assign a non volatile formula to B1 we would now lower the volatile
                    // count of C1 to 1 but since C1 itself is still volatile we don't need to proceed further
                    // than this and leave D1 with its volatile count of 1.
                    // (fhofmann) fixed the idea noted above to actually work ;-)
                    const dependency_set_type& dep = current->dependents();
                    for ( dependency_set_type::const_iterator it = dep.begin(), end_it = dep.end(); it != end_it; ++it ) {
                        if ( check_volatile_descent<1>( this, *it, current ) ) {
                            if ( !dependency_set.has( *it ) ) {
                                dependency_stack.push( *it );
                            } else {
                                dependency_set.add( *it );
                            }
                        }
                    }
                }

                // (fschaper) by adding the dependency we are trying to get exclusive access to all dependencies.
                // in case we can not aquire a lock on the dependency the add method will return false and
                // we will abort this operation thereby releasing all active locks
                // that we are currently holding on the stack.
                // the first dependency we will lower the volatile count from is "us".
                could_lock_dependency = dependency_set.add( current );
                if ( ! could_lock_dependency ) {
                    continue;
                }


            } while ( ! dependency_stack.empty() );

            LOG_CORE_TRACE_DEPENDENCIES( debug_logging_helper::list_dependencies( dependency_set ) );

            // lower the volatile flag for all dependencies.
            for ( locked_dependency_multitree::const_iterator it = dependency_set.begin(), end_it = dependency_set.end(); it != end_it; ++it ) {
                //foreach( const shared_dependency_type & sd, dependency_set ) {
                if ( it->first && !( ( it->first )->type() == i_dependency::named_formula_wrapper_type && boost::shared_static_cast<named_formula_dependency_wrapper>( ( it->first ) )->check_if_initiator_is_free_formula() ) ) {
                    for ( size_t count = 0, end_count = it->second; count < end_count; ++count ) {
                        ( it->first )->internal_lower_volatile_count();
                    }
                }

            }

            //std::for_each( dependency_set.begin(), dependency_set.end(), boost::bind( &i_dependency::internal_lower_volatile_count, _1 ) );

        } while ( ! could_lock_dependency );
    }
}

optional_sheet_range_type abstract_dependency::coverage() const
{
    return optional_sheet_range_type();
}

void abstract_dependency::lock()
{
    m_dependencies.unguard().mutex.lock();
}

bool abstract_dependency::try_lock()
{
    return m_dependencies.unguard().mutex.try_lock();
}

void abstract_dependency::unlock()
{
    m_dependencies.unguard().mutex.unlock();
}

void abstract_dependency::flag_moved()
{
    // intentionally does nothing here.
    // only used for named formulas
}

#ifdef _DEBUG
FINAL void abstract_dependency::friendly_name( const std::string& name )
{
    m_friendly_name = name;
}

FINAL std::string& abstract_dependency::friendly_name()
{
    return m_friendly_name;
}

size_t abstract_dependency::use_count()
{
    return m_usage_counter;
}

volatile long abstract_dependency::m_usage_counter = 0;

#endif
