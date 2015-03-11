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

#include "precompiled_header.hpp"
#include "stack_calculation.hpp"

#include "wss/i_dependency.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/calculation_context.hpp"
#include "wss/range_reference.hpp"
#include "wss/named_formula_reference.hpp"
#include "wss/reference_operation.hpp"
#include "wss/cyclic_dependency_set.hpp"


#include <utility> // std::pair
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
#endif
#ifdef _DEBUG
#   include "wss/singleton.hpp"
#endif // _DEBUG
#include "core_logging.hpp"




/*!
 * \brief
 * bring all precedents into order before calculation.
 *
 * sorts all precedents on the heap to stack problems
 * that would arise with an recursive approach.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct precedents_walker {
    typedef shared_dependency_type dependency_ptr_type;
    typedef const dependency_ptr_type& dependency_ptr_argument_type;
    typedef const i_dependency* raw_dependency_ptr_type;

    typedef set_to_use<raw_dependency_ptr_type>::type visitation_set_type;

    typedef std::stack<dependency_ptr_type> precedents_stack_type;

    typedef std::list<dependency_ptr_type> predecessor_list_type;
    typedef std::pair<raw_dependency_ptr_type, precedents_stack_type>  jump_info_type;
    typedef std::stack<jump_info_type> jump_stack_type;

    typedef cyclic_dependency_set::cyclic_dependency_set_type cyclic_dependency_set_type;


    static raw_dependency_ptr_type convert_to_raw( dependency_ptr_argument_type d ) {
        return d.get();
    }


    struct stack_data {
        typedef predecessor_list_type::const_iterator const_iterator;

        stack_data( cyclic_dependency_set_type& cyclic_dep_set ) : cyclic_dependencies( cyclic_dep_set ) {}


        ~stack_data() {
#ifdef _DEBUG
            assert( jump_back_stack.empty() || !cyclic_dependencies.empty() );
            assert( precedents_list.empty() );

#endif // _DEBUG
        }

        template<class selection_T>
        inline void check_and_push_on_right_stack( dependency_ptr_argument_type parent, dependency_ptr_argument_type d, size_t& current_counter, selection_T& select ) {
            check_if_current_in_predecessors( d );
            if ( check_if_calculated( convert_to_raw( d ) ) && select( d ) ) {
                ++current_counter;
                if ( current_counter > 1 ) {
                    if ( current_counter == 2 ) {
                        create_new_jump_back_stack( convert_to_raw( parent ) );
                    }
                    push_on_jump_back_stack( d );
                }  else {
                    push( d );
                }
                set_visited( d );
            } else if ( check_if_cyclic( d ) ) {
                cyclic_dependencies.insert( precedents_list.begin(), precedents_list.end() );
            }
        }

        inline void push_on_jump_back_stack( dependency_ptr_argument_type d ) {
            jump_back_stack.top().second.push( d );
            set_visited( d );
        }

        inline void create_new_jump_back_stack( raw_dependency_ptr_type d ) {
            jump_back_stack.push( std::make_pair( d, precedents_stack_type() ) );
        }

        inline void push( dependency_ptr_argument_type d ) {
            add_to_predecessors( d );
        }

        inline void push() {
            push( current_dep );
        }

        inline void pop() {
            precedents_list.pop_back();
        }

        inline void set_done( dependency_ptr_argument_type d ) {
            calculated_cells.insert( convert_to_raw( d ) );
        }

        inline void set_done() {
            set_done( current_dep );
        }

        inline void set_visited( dependency_ptr_argument_type d ) {
            visited_cells.insert( convert_to_raw( d ) );
        }

        inline bool check_if_current_in_predecessors( dependency_ptr_argument_type current ) {
            if ( !precedents_list.empty() ) {
                const_iterator end_it( precedents_list.end() );
                const_iterator begin_it( precedents_list.begin() );
                if ( end_it != std::find( begin_it, end_it, current ) ) {
                    cyclic_dependencies.insert( begin_it, end_it );
#ifdef _DEBUG
                    LOG_CORE_WARNING( "CYCLIC DEPENDENCIES FOUND! DUMPING LIST: " );
                    foreach( dependency_ptr_type d, precedents_list ) {
                        LOG_CORE_WARNING( " || " << d->get_debug_identifier() );
                    }
#else
                    LOG_CORE_TRACE( "CYCLIC DEPENDENCIES FOUND! - CHECK IF THIS IS AN ERROR IN THE CALCULATION ENGINE!" )
#endif // _DEBUG
                    return true;
                }
            }
            return false;
        }


        inline void add_to_predecessors( dependency_ptr_argument_type current ) {
            precedents_list.push_back( current );
        }

        inline bool check_if_calculated( raw_dependency_ptr_type current ) const {
            return calculated_cells.find( current ) == calculated_cells.end();
        }

        inline bool check_if_seen( raw_dependency_ptr_type current ) const {
            return visited_cells.find( current ) == visited_cells.end();
        }

        void operator++() {
            current_dep = *precedents_list.rbegin();
            precedents_list.pop_back();
            assert( "in the next step this might be calculated, but it was already!" && check_if_calculated( convert_to_raw( current_dep ) ) );
        }

        void initialize( dependency_ptr_argument_type ptr ) {
            current_dep = ptr;
            set_visited( ptr );
        }

        inline bool next() {
            if ( check_if_calculated( convert_to_raw( *precedents_list.rbegin() ) ) ) {
                current_dep = *precedents_list.rbegin();
                precedents_list.pop_back();
                return true;
            }
            precedents_list.pop_back();
            return false;
        }

        inline dependency_ptr_argument_type current() const {
            assert( "current not set!" && current_dep );
            return current_dep;
        }

        template<class selection_T>
        inline bool check( const selection_T& select ) {
            return select( current_dep ) && current_dep->has_precedents() && check_if_calculated( current_dep.get() ) && !check_if_cyclic( current_dep );
        }

        template<class selection_T>
        inline bool check( dependency_ptr_argument_type d, const selection_T& select ) {
            return select( d ) && check_if_calculated( d.get() );
        }

        template<class operation_T>
        inline void call_operation_on( const operation_T& operate_on ) {
            call_operation_on( operate_on, current_dep );
        }

        template<class operation_T>
        inline bool call_operation_on( const operation_T& operate_on, dependency_ptr_argument_type current ) {
            assert( "this one has already been calculated" && check_if_calculated( convert_to_raw( current ) ) );
            calculated_cells.insert( convert_to_raw( current ) );
            if ( !check_if_cyclic( current ) ) {
                operate_on( current );
                return true;
            }
            return false;
        }

        struct iteration_count_reached {
            typedef bool result_type;
            iteration_count_reached( calculation_cache& cc, const size_t maximum_iterations )
                : m_cc( cc ), m_maximum_iterations( maximum_iterations ) {}

            inline bool check( dependency_ptr_argument_type d ) const {
                return !m_cc.iteration_count_still_valid( *d, m_maximum_iterations );
            }

            template<class set_type>
            inline void set_all_to_max( set_type& set ) const {
                for ( typename set_type::const_iterator it = set.begin(), end_it = set.end(); it != end_it; ++it ) {
                    m_cc.set_iteration_count_to_max( **it, m_maximum_iterations );
                }
            }
        private:
            calculation_cache& m_cc;
            const size_t m_maximum_iterations;
        };

        template<class operation_T>
        struct conditional_operate_on {
            conditional_operate_on( const operation_T& operate_on, const iteration_count_reached& count_iterations )
                : m_operate_on( operate_on ), m_count_iterations( count_iterations ) {}

            inline void operator()( const shared_dependency_type& sd ) const {
                if ( !m_count_iterations.check( sd ) ) {
                    m_operate_on( sd );
                }
            }

            const operation_T& m_operate_on;
            const iteration_count_reached& m_count_iterations;
        };

        template<class operation_T>
        inline void calculate_cyclic_deps( const operation_T& operate_on, calculation_context& cc ) {
            typedef conditional_operate_on<operation_T> operate_on_type;
            if ( !cyclic_dependencies.empty() ) {
                cyclic_dependency_set& cyclic_dep_set = cc.cache().cyclic_dependencies();
                const cyclic_dependency_set::sorted_cyclic_dependency_set_type sorted_cyclic_deps = cyclic_dep_set.sorted_dependencies();
                size_t local_iteration_counter = cc.settings().maximum_iterations();
                iteration_count_reached count_iterations( cc.cache(), local_iteration_counter );
                operate_on_type conditional_operation( operate_on, count_iterations );
                do {
                    cyclic_dep_set.new_round();
                    std::for_each( sorted_cyclic_deps.begin(), sorted_cyclic_deps.end(), conditional_operation );
                } while ( --local_iteration_counter && cyclic_dep_set.got_value_change() ) ;
                count_iterations.set_all_to_max( cyclic_dependencies );
            }
        }

        inline bool has_precedents() const {
            return !precedents_list.empty();
        }

        inline bool check_if_cyclic() const {
            return check_if_cyclic( current_dep );
        }

        inline bool check_if_cyclic( dependency_ptr_argument_type current ) const {
            return cyclic_dependencies.find( current ) != cyclic_dependencies.end();
        }

        inline bool can_go_to_descent() {
            if ( can_jump() ) {
                if ( next() ) {
                    return true;
                }
                return false;
            }
            while ( has_precedents() ) {
                if ( next() ) {
                    return true;
                }
            }
            return false;
        }

    private:
        inline void remove_predecessors_on_jump() {}

        inline void remove_predecessor_that_is_done() {
            assert( "error in precedents walker, trying to remove more predecessors from the stack than possible!" && !precedents_list.empty() /*&& how_many_predecessors_to_remove*/ );
            precedents_list.pop_back();
        }

        inline bool can_jump() {
            if ( !jump_back_stack.empty() ) {
                assert( !jump_back_stack.top().second.empty() );
                if ( precedents_list.empty() || jump_back_stack.top().first == convert_to_raw( *precedents_list.rbegin() ) ) {
                    if ( prepare_jump( jump_back_stack.top() ) ) {
                        if ( jump_back_stack.top().second.empty() ) {
                            jump_back_stack.pop();
                        }
                        return true;
                    } else {
                        if ( jump_back_stack.top().second.empty() ) {
                            jump_back_stack.pop();
                        }
                    }
                }
            }
            return false;
        }

        inline bool prepare_jump( jump_info_type& jump_info ) {
            while ( !jump_info.second.empty() ) {
                if ( check_if_calculated( convert_to_raw( jump_info.second.top() ) ) ) {
                    push( jump_info.second.top() );
                    jump_info.second.pop();
                    return true;
                }
                jump_info.second.pop();
            }
            return false;
        }



        shared_dependency_type current_dep;
        jump_stack_type jump_back_stack;
        predecessor_list_type precedents_list;
        visitation_set_type visited_cells;
        visitation_set_type calculated_cells;
        cyclic_dependency_set_type& cyclic_dependencies;
    };

    /*!
     * \brief
     * put precedents on the stack based on the passed selection operation.
     *
     * will put all dependencies on the stack that match the passed selection
     * operation and that we haven't visited yet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class selection_T>
    class precedents_order_operation : boost::noncopyable
    {
    public:
        precedents_order_operation( const selection_T& select, stack_data& current_stack )
            : m_current_stack( current_stack )
            , m_selection( select )
            , m_current_counter( 0 ) {}

        void operator()( const shared_dependency_type& sd ) {
            // only add those dependencies that match "m_selection" and that we have yet to visit.
            m_current_stack.check_and_push_on_right_stack( m_parent, sd, m_current_counter, m_selection );
        }

        void reset( dependency_ptr_argument_type p ) {
            m_parent = p;
            m_current_counter = 0;
        }

        bool got_new_dependencies() const {
            return 0 != m_current_counter;
        }

    private:
        stack_data& m_current_stack;
        const selection_T& m_selection;
        size_t m_current_counter;
        shared_dependency_type m_parent;
    };

    /*!
     * \brief
     * iterate over all dependencies on the heap.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    template<class order_T>
    static inline void push_precedents_on_stack( stack_data& current_stack, const shared_dependency_type current, order_T& order ) {
        order.reset( current );
        reference_operation_for_stack_calculation( current, current->precedents(), order, true );
    }

    template<class selection_T, class operation_T>
    precedents_walker( const shared_dependency_type& ptr, const selection_T& select, const operation_T& operate_on, interpreter_context& ic ) {

        stack_data current_stack( ic.context().cache().cyclic_dependencies().cyclic_dependencies() );

        precedents_order_operation<selection_T> order( select, current_stack );
        current_stack.initialize( ptr );

descent:
        if ( current_stack.check( select ) ) {
            current_stack.push();
            push_precedents_on_stack( current_stack, current_stack.current(), order );
            if ( order.got_new_dependencies() ) {
                ++current_stack;
                goto descent;
            } else {
                current_stack.pop();
            }
        }

        current_stack.call_operation_on( operate_on );

        if ( current_stack.can_go_to_descent() ) {
            goto descent;
        }

        current_stack.calculate_cyclic_deps( operate_on, ic.context() );
    }

};

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * select all dependencies that are flagged as being dirty.
 *
 * select all dependencies that are volatile and not in
 * the calculation cache (is_dirty does that check for us).
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class select_dirty
{
public:
    select_dirty( calculation_context& cc, const cyclic_dependency_set& cyclic_dependencies  )
        : m_context( cc )
        , m_cyclic_dependencies( cyclic_dependencies ) {}

    bool operator()( const shared_dependency_type& sd ) const {
        // is_dirty will check for volatile cached and dirty state.
        const bool is_volatile = sd->is_volatile();
        const bool is_cyclic = m_cyclic_dependencies.check_if_cyclic( sd );

        return ( ( is_volatile || is_cyclic ) && !sd->fetch_cached_volatile( m_context ) )
               ||
               ( !is_volatile && !is_cyclic && sd->is_dirty() );
    }

private:
    calculation_context& m_context;
    const cyclic_dependency_set& m_cyclic_dependencies;
};

//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * precedents walker wrapper.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct internal_calculate {
    internal_calculate( interpreter_context& ic )
        : m_ic( ic ) {}

    inline void operator()( const shared_dependency_type& sd ) const {
        sd->calculate( m_ic );
    }

    mutable interpreter_context& m_ic;
};

//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * stack based calculation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void stack_based_calculation( const shared_dependency_type& sd, calculation_context& cc, interpreter_context& ic )
{
    precedents_walker walker( sd, select_dirty( cc, cc.cache().cyclic_dependencies() ), internal_calculate( ic ), ic );
}
