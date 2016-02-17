/**
 * \file
 * Copyright (C) 2006-2010 Jedox AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (Version 2) as published
 * by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may obtain a copy of the License at
 *
 * <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *   http://www.jedox.com/license_palo_bi_suite.txt
 * </a>
 *
 * If you are developing and distributing open source applications under the
 * GPL License, then you are free to use Palo under the GPL License.  For OEMs,
 * ISVs, and VARs who distribute Palo with their products, and do not license
 * and distribute their source code under the GPL, Jedox provides a flexible
 * OEM Commercial License.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "dependency_manager.hpp"

#include "wss/i_dependency.hpp"
#include "wss/worksheet.hpp"
#include "wss/not_implemented_exception.hpp"
#include "wss/reference.hpp"

#include "named_formula_dependency_wrapper.hpp"
#include "cell_manager.hpp"
//#include "move_callback.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
# include <boost/cast.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0
#include "cell.hpp"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define HIDE_TICKET_8810_FOR_NOW 1

struct dependency_manager_remove_callback {
    bool operator()( const geometry::rectangle_type&, shared_dependency_node_type& ) const {
        return true;
    }
};

/*!
 * \brief
 * node that holds the "interested" dependents and
 * their predecessors "existing cells".
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class dependency_node
{
public:
    dependency_node( const sheet_range& position, const weak_worksheet_type& ws )
        : reference( reference_type( position ) )
        , dependents()
        , precedents( dependency_node_reference::create( position, ws ) ) {}

    dependency_node( const dependency_node& other )
        : reference( other.reference )
        , dependents( other.dependents )
        , precedents( other.precedents ) {}

    ~dependency_node() {
        if ( ( *precedents->container().lock() ).empty() ) {
            // if ( !precedents->worksheet().expired() ) {
            // (fhofmann) if there are no cells in the region that would do the flag dirty for us on destruction we have to manually do it!
            locked_dependency_set_type::access d( dependents );
            std::for_each( d.get().begin(), d.get().end(), boost::bind( &i_dependency::internal_flag_dirty, _1 ) );
            //}
        }
    }

    // (fschaper) we don't have to store the reference type at this point
    // because the shared_dependency_node_reference_type "precedents" already
    // contains this information. but since the precedents object is exposed
    // and contains locks we duplicate the information here to speed up our
    // queries. since reference information also never changes it's quite save
    // to do so.
    const ::reference::type reference;
    locked_dependency_set_type dependents;                // observers of the region
    shared_dependency_node_reference_type precedents; // list of cells that fall into the region
};

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class move_node_info
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    move_node_info( const shared_dependency_node_type& node, const geometry::rectangle_type position )
        : m_node( node )
        , m_new_position( position ) {}

    /*!
     * \brief
     * dependency node that is being moved.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const shared_dependency_node_type& node() const {
        return m_node;
    }

    /*!
     * \brief
     * the coverage of the node (the nodes new position)
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const geometry::rectangle_type& area_coverage() const {
        return m_new_position;
    }

private:
    shared_dependency_node_type m_node;
    geometry::rectangle_type m_new_position;
};

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class dependency_manager::move_callback
{
public:
    typedef std::vector<move_node_info> node_info_block_type;

    /*!
     * \brief
     * callback
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline move_callback( const sheet_range& move_range, const sheet_point& target, node_info_block_type& block, bool is_whole_column_or_row_operation, bool is_move_on_same_sheet );

    /*!
     * \brief
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n );

private:
    const sheet_range& m_selection_range;
    const sheet_point& m_target;
    node_info_block_type& m_node_info_block;
    const geometry::point m_distance;
    const bool m_is_whole_column_or_row_operation;
    const bool m_is_move_on_same_sheet;
};




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * register a new cell with the nodes.
 *
 * when a new cell is created, it need be registered with all nodes that
 * intersect the cells position.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class dependency_manager::register_cell_callback
{
public:
    register_cell_callback( dependency_set_type& dependents, const shared_dependency_type& new_cell )
        : m_dependents( dependents )
        , m_new_cell( new_cell ) {}

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) {
        ( *n->precedents->container().lock() ).insert( m_new_cell );
        locked_dependency_set_type& ds = n->dependents;
        locked_dependency_set_type::access dep_access( ds );
        m_dependents.insert( ( *dep_access ).begin(), ( *dep_access ).end() );
        return true;
    }

private:
    dependency_set_type& m_dependents;
    const shared_dependency_type& m_new_cell;
};

class dependency_manager::register_array_master_cell_callback
{
public:
    register_array_master_cell_callback( dependency_set_type& dependents, const shared_dependency_type& new_cell, const geometry::rectangle_type array_coverage )
        : m_dependents( dependents )
        , m_new_cell( new_cell )
        , m_array_coverage( array_coverage ) {}

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) {
        if ( r.covers( m_array_coverage.upper_left() ) ) {
            //only register ourselves if we're at the right position
            ( *n->precedents->container().lock() ).insert( m_new_cell );
        }
        locked_dependency_set_type& ds = n->dependents;
        locked_dependency_set_type::access dep_access( ds );
        m_dependents.insert( ( *dep_access ).begin(), ( *dep_access ).end() );
        return true;
    }

private:
    dependency_set_type& m_dependents;
    const shared_dependency_type& m_new_cell;
    const geometry::rectangle_type m_array_coverage;
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * remove a cell from the reference list.
 *
 * if a cell gets deleted, it is in turn removed
 * from the range_reference since it is no longer
 * addressable.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class dependency_manager::unregister_cell_callback
{
public:
    unregister_cell_callback( const shared_dependency_type& cell_to_erase )
        : m_cell_to_erase( cell_to_erase ) {}

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) {
        ( *n->precedents->container().lock() ).erase( m_cell_to_erase );
        return true;
    }

private:
    const shared_dependency_type& m_cell_to_erase;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * erase a specific node!
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class dependency_manager::erase_node_callback
{
public:
    erase_node_callback( const shared_dependency_node_type& n )
        : m_node( n ) {}

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) const {
        return m_node == n;
    }

    shared_dependency_node_type m_node;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * erase callback. will erase every node that equals
 * the query region or is completely covered by it.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class dependency_manager::erase_matching_or_covered_region_callback
{
public:
    erase_matching_or_covered_region_callback( const sheet_range& region )
        : m_region( region ) {}

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) const {
        if ( m_region.covers( r ) ) {
            return true;
        }
        return false;
    }

    const sheet_range& m_region;
};

inline bool check_for_absolute_reference( const reference::type t )
{
    return t == reference::absolute;
}
class dependency_manager::erase_matching_or_covered_region_callback_for_nfs
{
public:
    erase_matching_or_covered_region_callback_for_nfs( const sheet_range& region )
        : m_region( region ) {}

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) const {
        if ( check_for_absolute_reference( n->reference ) && m_region.covers( r ) ) {
            return true;
        }
        return false;
    }

    const sheet_range& m_region;
};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * register a shared_dependency as dependent on the specified region.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class dependency_manager::register_dependent_callback
{
public:
    register_dependent_callback( const shared_dependency_type& d, const sheet_range& position )
        : m_dependency( d )
        , m_position( position )
        , m_inserted( false ) {}

    bool found_match() const {
        return m_inserted;
    }

    const shared_dependency_node_reference_type& reference() const {
        return m_precedents;
    }

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) {
        // the region needs to match exactly.
        if ( r == m_position &&  n->reference == reference_type( m_position ) ) {
            // $A$1 and $A1, A$1 and A1 will create individual nodes
            // in case we find an exact match we don't need to create
            // a individual node but reuse the existing one.
            ( *n->dependents.lock() ).insert( m_dependency );
            m_precedents = n->precedents;
            m_inserted = true;

        }
        return true;
    }

private:
    shared_dependency_type m_dependency;
    const sheet_range& m_position;
    shared_dependency_node_reference_type m_precedents;
    bool m_inserted;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * in case a formula no longer references a cell, the node will be updated
 * to reflect the change.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class dependency_manager::unregister_dependency_node_callback
{
public:
    unregister_dependency_node_callback( const sheet_range& selection_range, const shared_dependency_type& d )
        : m_selection_range( selection_range )
        , m_dependency( d ) {}

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) const {
        if ( n->precedents->position() == m_selection_range ) {
            locked_dependency_set_type::access dep_access( n->dependents );
            ( *dep_access ).erase( m_dependency );
            // in case there are no longer any dependent cells observing the
            // region we erase the node.
            return ( *dep_access ).size() == 0;
        }
        return false;
    }

private:
    const sheet_range& m_selection_range;
    shared_dependency_type m_dependency;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class dependency_manager::handle_named_formula_move_callback
{
public:
    typedef std::vector<shared_dependency_node_type> to_clear_node_list_type;

    handle_named_formula_move_callback( const sheet_range& selection_range, move_callback& mc, to_clear_node_list_type& nb )
        : m_selection_range( selection_range )
        , m_move_callback( mc )
        , m_node_block( nb ) {}

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) {
        if ( check_for_absolute_reference( n->reference ) ) {
            // nodes that have an absolute component are being treated
            // like we would any regular cell reference
            m_move_callback( r, n );
        } else {
            // relative named formulas stay relative to their position
            // on the sheet. we only need to re-reference cells for these
            // nodes since the cells _did_ move.
            m_node_block.push_back( n );
        }
        return true;
    }


private:
    template<bool row_fill_top_to_down, bool column_fill_left_to_right>
    struct sorting_helper {

        inline bool operator()( const shared_dependency_node_type& lhs, const shared_dependency_node_type& rhs ) const {
            const sheet_point lhs_upper_left =  lhs->precedents->position().upper_left();
            const sheet_point rhs_upper_left =  rhs->precedents->position().upper_left();
            return compare_row( lhs_upper_left, rhs_upper_left );
        }

    private:
        inline bool compare_row( const sheet_point& lhs_upper_left, const sheet_point& rhs_upper_left ) const {
            if ( lhs_upper_left.row() == rhs_upper_left.row() ) {
                return compare_column( lhs_upper_left, rhs_upper_left );
            }

            if ( row_fill_top_to_down ) {
                return lhs_upper_left.row() > rhs_upper_left.row();
            } else {
                return lhs_upper_left.row() < rhs_upper_left.row();
            }
        }

        inline bool compare_column( const sheet_point& lhs_upper_left, const sheet_point& rhs_upper_left ) const {
            if ( column_fill_left_to_right ) {
                return lhs_upper_left.column() > rhs_upper_left.column();
            } else {
                return lhs_upper_left.column() < rhs_upper_left.column();
            }
        }
    };

    template<bool row_fill_top_to_down, bool column_fill_left_to_right>
    inline void sort_list() {
        typedef sorting_helper<row_fill_top_to_down, column_fill_left_to_right> sorter;
        std::sort( m_node_block.begin(), m_node_block.end(), sorter() );
    }

public:
    inline void sort_list( const sheet_range& source, const sheet_point& target ) {

        const geometry::point distance( source.distance( target ) );
        const bool row_fill_top_to_down = distance.row() > 0;
        const bool column_fill_left_to_right = distance.column() < 0;
        if ( row_fill_top_to_down ) {
            if ( column_fill_left_to_right ) {
                sort_list<true, true>();
            } else {
                sort_list<true, false>();
            }
        } else {
            if ( column_fill_left_to_right ) {
                sort_list<false, true>();
            } else {
                sort_list<false, false>();
            }
        }
    }


private:
    sheet_range m_selection_range;
    move_callback& m_move_callback;
    to_clear_node_list_type& m_node_block;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class dependency_manager::query_dependents_callback
{
public:
    query_dependents_callback( dependency_set_type& dependents )
        : m_dependents( dependents ) {}

    bool operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n ) {
        dependency_node& dn = static_cast<dependency_node&>( *n );
        locked_dependency_set_type::access dep_access( dn.dependents );
        m_dependents.insert( ( *dep_access ).begin(), ( *dep_access ).end() );
        return true;
    }

private:
    dependency_set_type& m_dependents;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
struct dependency_manager::dependency_manager_helper : non_instantiable {
    static inline container_type& select_container( const bool inside_nf, const shared_dependency_type& sd, container_type& m_cell_dependencies, container_type& m_named_formula_dependencies ) {
        if ( inside_nf || sd->type() !=  i_dependency::cell_type ) {
            return m_named_formula_dependencies;
        }
        return m_cell_dependencies;
    }
};

dependency_manager::dependency_manager( worksheet& ws )
    : m_worksheet( ws )
{}

shared_dependency_node_reference_type dependency_manager::register_dependency( const shared_dependency_type& sd, const sheet_range& position, const bool inside_nf )
{
    container_type& actual_container = dependency_manager_helper::select_container( inside_nf, sd, m_cell_dependencies, m_named_formula_dependencies );

    register_dependent_callback register_callback( sd, position );
    actual_container.query( geometry::rectangle_type( position ), register_callback );

    shared_dependency_node_reference_type return_value;
    if ( register_callback.found_match() ) {
        return_value = register_callback.reference();
    } else {
        shared_dependency_node_type rn = boost::make_shared<dependency_node>( position, m_worksheet.shared_from_this() );
        return_value = rn->precedents;
        ( * rn->dependents.lock() ).insert( sd );
        actual_container.insert( geometry::rectangle_type( position ), rn );
    }
    return return_value;
}

void dependency_manager::unregister_dependency( const shared_dependency_type& sd, const sheet_range& region )
{
    container_type& actual_container = dependency_manager_helper::select_container( false, sd, m_cell_dependencies, m_named_formula_dependencies );

    unregister_dependency_node_callback unregister_callback( region, sd );
    // we actually only remove nodes in case all dependents have been
    // deleted from it. otherwise we only remove the passed dependency.
    actual_container.remove( region, unregister_callback );
}

dependency_set_type dependency_manager::query_dependents( const sheet_point& p )
{
    dependency_set_type return_value;
    query_dependents_callback dependents_callback( return_value );
    m_cell_dependencies.query( geometry::rectangle_type( p ), dependents_callback );
    return return_value;
}

dependency_set_type dependency_manager::update_precedents_get_dependents( const sheet_point& p, const shared_dependency_type& c )
{
    dependency_set_type return_value;
    register_cell_callback cell_callback( return_value, c );
    m_cell_dependencies.query( geometry::rectangle_type( p ), cell_callback );
    m_named_formula_dependencies.query( geometry::rectangle_type( p ), cell_callback );
    return return_value;
}

dependency_set_type dependency_manager::update_precedents_get_dependents_for_array_master( const sheet_range& r, const shared_dependency_type& c )
{
    dependency_set_type return_value;
    register_array_master_cell_callback cell_callback( return_value, c, r );
    m_cell_dependencies.query( geometry::rectangle_type( r ), cell_callback );
    m_named_formula_dependencies.query( geometry::rectangle_type( r ), cell_callback );
    return return_value;
}

void dependency_manager::erase_precedent( const geometry::rectangle_type& r, const shared_dependency_type& c )
{
    unregister_cell_callback cell_callback( c );
    m_cell_dependencies.query( r, cell_callback );
    m_named_formula_dependencies.query( r, cell_callback );
}

void dependency_manager::dump( std::ostream& os ) const
{
    throw not_implemented_exception();
}

inline void internal_and_flag_dirty( const shared_dependency_type& current )
{
    current->flag_dirty();
    current->internal_flag_dirty();
}

void dependency_manager::move( const sheet_range& selection_range, const sheet_point& target, cell_manager& target_manager, bool is_whole_column_or_row_operation )
{
    // a few values that are needed for both moves
    sheet_range::rectangles_type regions_to_be_erased;
    const bool same_sheet = &*target_manager.associated_worksheet() == &m_worksheet;

    // handle cell movement
    {
        if ( same_sheet ) {
            if ( is_whole_column_or_row_operation
                    && ( target.row() < selection_range.upper_left().row() || target.column() < selection_range.upper_left().column() ) ) {
                sheet_range moved_selection = selection_range.coverage().checked_offset( target );
                sheet_point selection_upper_left_part =  selection_range.upper_left().checked_offset( -1, -1 );
                sheet_range bigger_selection = moved_selection.enclose_point( selection_upper_left_part );
                regions_to_be_erased = bigger_selection.cut( selection_range );
            } else {
                regions_to_be_erased = selection_range.coverage().checked_offset( target ).cut( selection_range );
            }
            // remove all nodes that would be overwritten, cells referencing this
            // area must be invalidated. (#REF!)
            for ( sheet_range::rectangles_type::const_iterator it = regions_to_be_erased.begin(), end_it = regions_to_be_erased.end(); it != end_it; ++it ) {
                //foreach( const sheet_range & sr, regions_to_be_erased ) {
                erase_matching_or_covered_region_callback ermocrcb( *it );
                m_cell_dependencies.remove( *it, ermocrcb );
            }
        }

        move_callback::node_info_block_type rewritten_nodes;
        // get list of all nodes that need be changed
        move_callback move_cb( selection_range, target, rewritten_nodes, is_whole_column_or_row_operation, same_sheet );
        const geometry::rectangle_type selection_range_plus_moved_selection_range = selection_range.enclose( selection_range.checked_offset( selection_range.upper_left().distance( target ) ) );
        m_cell_dependencies.query( selection_range_plus_moved_selection_range, move_cb );
        for ( move_callback::node_info_block_type::const_iterator it = rewritten_nodes.begin(), end_it = rewritten_nodes.end(); it != end_it; ++it ) {
            //foreach( move_node_info & n, rewritten_nodes ) {
            // disconnect the node that we want to rewrite
            shared_dependency_node_type moved_node = ( *it ).node();
            // erase the node from the dependency tree
            erase_node_callback erase_callback( moved_node );
            m_cell_dependencies.remove( moved_node->precedents->position(), erase_callback );
            // update the area_coverage of the node and the precedent information
            //TODO check why we had this exception, use notes in ticket 8810 to reproduce
#ifdef HIDE_TICKET_8810_FOR_NOW
            try {
#endif // HIDE_TICKET_8810_FOR_NOW
                moved_node->precedents->position( ( *it ).area_coverage() );
                moved_node->precedents->worksheet( target_manager.associated_worksheet() );
                // update the list of covered cells
                locked_dependency_set_type::access container( moved_node->precedents->container() );
                target_manager.fill_range( sheet_range( ( *it ).area_coverage() ), container );
                // TODO here be dragons! m_cell_dependencies need be locked for this operation to be performed safely.
                target_manager.add_cell_move_node( moved_node );

                //this is needed for instance for function_row referencing some area that gets moved
                locked_dependency_set_type::access dep_access( moved_node->dependents );
                std::for_each( ( *dep_access ).begin(), ( *dep_access ).end(), boost::bind( &i_dependency::internal_flag_dirty, _1 ) );

#ifdef HIDE_TICKET_8810_FOR_NOW
            } catch ( const position_out_of_range_exception& ) {}
#endif // HIDE_TICKET_8810_FOR_NOW
        }
    }

    // handle named formula movement
    {

        if ( same_sheet && !regions_to_be_erased.empty() ) {
            // remove all nodes that would be overwritten, cells referencing this
            // area must be invalidated. (#REF!)
            for ( sheet_range::rectangles_type::const_iterator it = regions_to_be_erased.begin(), end_it = regions_to_be_erased.end(); it != end_it; ++it ) {
                //foreach( const sheet_range & sr, regions_to_be_erased ) {
                erase_matching_or_covered_region_callback_for_nfs ermocrcb( *it );
                m_named_formula_dependencies.remove( *it, ermocrcb );
            }
        }

        move_callback::node_info_block_type rewritten_nodes;
        move_callback move_cb( selection_range, target, rewritten_nodes, is_whole_column_or_row_operation, same_sheet );

        handle_named_formula_move_callback::to_clear_node_list_type clear_node_list;
        handle_named_formula_move_callback nf_cb( selection_range, move_cb, clear_node_list );
        m_named_formula_dependencies.query( selection_range, nf_cb );

        if ( !clear_node_list.empty() ) {
            nf_cb.sort_list( selection_range, target );
            dependency_set_type waiting_for_flag_dirty;
            // update the dependencies of all named formulas that are 'relative' on the sheet.
            for ( handle_named_formula_move_callback::to_clear_node_list_type::const_iterator it = clear_node_list.begin(), end_it = clear_node_list.end(); it != end_it; ++it ) {
                //foreach( const shared_dependency_node_type & n, clear_node_list ) {
                locked_dependency_set_type::access precedent_access( ( *it )->precedents->container() );
                locked_dependency_set_type::access dep_access( ( *it )->dependents );
                dependency_set_type::const_iterator dep_it = ( *dep_access ).begin(), dep_end = ( *dep_access ).end();
                waiting_for_flag_dirty.insert( dep_it, dep_end );
                for ( ; dep_it != dep_end; ++dep_it ) {
                    std::for_each( ( *precedent_access ).begin(), ( *precedent_access ).end(), boost::bind( &i_dependency::unregister_dependent, _1, *dep_it ) );
                }

                //( *precedent_access ).clear();
                m_worksheet.cells().fill_range( ( *it )->precedents->position(), *precedent_access );
            }
            std::for_each( waiting_for_flag_dirty.begin(), waiting_for_flag_dirty.end(), boost::bind( &internal_and_flag_dirty, _1 ) );
        }

        // all other cells are being treated as would regular cells.
        // TODO I'm not all to happy with this code duplication and
        // add_named_formula_move_node / add_cell_move_node separation
        // this will see some cleanup in the future.
        for ( move_callback::node_info_block_type::const_iterator it = rewritten_nodes.begin(), end_it = rewritten_nodes.end(); it != end_it; ++it ) {
            //foreach( const move_node_info & n, rewritten_nodes ) {
            shared_dependency_node_type moved_node = ( *it ).node();
            // erase the node from the dependency tree.
            erase_node_callback erase_callback( moved_node );
            m_named_formula_dependencies.remove( moved_node->precedents->position(), erase_callback );
            // update the area_coverage of the node and the precedent information
            moved_node->precedents->position( ( *it ).area_coverage() );
            moved_node->precedents->worksheet( target_manager.associated_worksheet() );
            const dependency_set_type& dt = moved_node->dependents.lock();
            for ( dependency_set_type::const_iterator dep_it = dt.begin(), end_it = dt.end(); dep_it != end_it; ++dep_it ) {
                ( *dep_it )->flag_moved();
            }
            // update the list of covered cells
            locked_dependency_set_type::access container( moved_node->precedents->container() );
            target_manager.fill_range( sheet_range( ( *it ).area_coverage() ), container );
            // TODO here be dragons! m_cell_dependencies need be locked for this operation to be performed safely.
            target_manager.add_named_formula_move_node( moved_node );
        }
    }
}

void dependency_manager::add_cell_move_node( const shared_dependency_node_type& element )
{
    m_cell_dependencies.insert( element->precedents->position(), element );
}

void dependency_manager::add_named_formula_move_node( const shared_dependency_node_type& element )
{
    m_named_formula_dependencies.insert( element->precedents->position(), element );
}

optional_sheet_range_type dependency_manager::used_range() const
{
    optional_sheet_range_type return_value;

    const container_type::optional_rectangle_type used_range = m_cell_dependencies.used_range();
    if ( used_range ) {
        return_value = *used_range;
    }

    const container_type::optional_rectangle_type nf_used_range = m_named_formula_dependencies.used_range();
    if ( nf_used_range ) {
        if ( return_value ) {
            ( *return_value ).enclose_into_self( *nf_used_range );
        } else {
            return_value = *nf_used_range;
        }
    }
    return return_value;
}

void dependency_manager::erase( const sheet_range& selected_range )
{
    erase_matching_or_covered_region_callback ermocrcb( selected_range );
    m_cell_dependencies.remove( selected_range, ermocrcb );
}

void dependency_manager::release_memory( bool purge )
{
    container_type::release_memory( purge );
}

std::ostream& operator <<( std::ostream& os, const dependency_manager& d )
{
    /*
        d.dump( os );
    */
    return os;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

template<class point_T>
typename point_T::integer_type get_leftmost_column( const point_T& lhs, const point_T& rhs )
{
    return std::min( lhs.column(), rhs.column() );
}

template<class point_T>
typename point_T::integer_type get_rightmost_column( const point_T& lhs, const point_T& rhs )
{
    return std::max( lhs.column(), rhs.column() );
}

template<class point_T>
typename point_T::integer_type get_leftmost_row( const point_T& lhs, const point_T& rhs )
{
    return std::min( lhs.row(), rhs.row() );
}

template<class point_T>
typename point_T::integer_type get_rightmost_row( const point_T& lhs, const point_T& rhs )
{
    return std::max( lhs.row(), rhs.row() );
}

struct move_callback_helper : non_instantiable {
    template<class range_T>
    static inline sheet_range sheet_range_from_other( const range_T& other, const reference::type ref_type_upper_left, const reference::type ref_type_lower_right ) {
        return sheet_range( sheet_point( other.upper_left(), ref_type_upper_left ),
                            sheet_point( other.lower_right(), ref_type_lower_right ) );
    }
};

dependency_manager::move_callback::move_callback( const sheet_range& move_range, const sheet_point& target, node_info_block_type& block, bool is_whole_column_or_row_operation, bool is_move_on_same_sheet )
    : m_selection_range( move_range )
    , m_target( target )
    , m_node_info_block( block )
    , m_distance( move_range.distance( target ) )
    , m_is_whole_column_or_row_operation( is_whole_column_or_row_operation )
    , m_is_move_on_same_sheet( is_move_on_same_sheet )
{}

bool dependency_manager::move_callback::operator()( const r::r_tree_rectangle_type& r, shared_dependency_node_type& n )
{
    typedef geometry::rectangle_type updated_range_type;
    const updated_range_type current_coverage = n->precedents->position();
    if (
        (
            m_is_move_on_same_sheet
            &&
            ( current_coverage.does_intersect( m_selection_range )
              ||
              current_coverage.does_intersect( m_selection_range.offset( m_distance ) )
            )
        )
        ||
        (
            !m_is_move_on_same_sheet
            &&
            ( current_coverage.does_intersect( m_selection_range ) )
        )
    ) {
        const updated_range_type intersection_between_current_and_selection = m_selection_range.intersection( current_coverage );
        const geometry::border_type source_area_border_type = current_coverage.border_match_type( intersection_between_current_and_selection );
        const geometry::border_type target_area_border_type = current_coverage.border_match_type( m_selection_range.offset( m_distance ).intersection( current_coverage ) );

        if ( source_area_border_type != geometry::border_none || target_area_border_type != geometry::border_none ) {

            const bool was_moved_upwards = m_distance.row() < 0;
            const bool was_moved_downwards = m_distance.row() > 0;
            const bool was_moved_left = m_distance.column() < 0;
            const bool was_moved_right = m_distance.column() > 0;
            const bool was_not_moved_horizontally = was_moved_left == false && was_moved_right == false;
            const bool was_not_moved_vertically = was_moved_upwards == false && was_moved_downwards == false;

            updated_range_type updated_range = current_coverage;

            switch ( ( source_area_border_type == geometry::border_none ) ? target_area_border_type : source_area_border_type ) {
                case geometry::border_none :
                    // implemented to get rid of an gcc warning.
                    break;

                case geometry::border_top :
                    if ( was_not_moved_horizontally ) {
                        // test if the range needs to be extended upwards
                        if ( was_moved_upwards ) {
                            updated_range = updated_range.enclose_point( updated_range.upper_left().offset( m_distance ) );
                            // here we have to test if the movement of a partial range actually
                            // cuts the rest of the range.
                        } else { //was moved downwards
                            if ( geometry::border_bottom == target_area_border_type || geometry::border_all == target_area_border_type ) {
                                // we moved above our original range
                                updated_range = intersection_between_current_and_selection.offset( m_distance );
                            } else {
                                const geometry::rectangle_type relocated_source_range( m_selection_range.offset( m_distance ) );
                                if ( m_selection_range.does_intersect( updated_range ) && relocated_source_range.does_intersect( updated_range ) ) {
                                    // only do something if the relocated selection does intersect the current range
                                    const geometry::rectangle_type tmp_current_coverage( *updated_range.subtract( m_selection_range ) );
                                    const geometry::rectangle_type transformed_intersection( intersection_between_current_and_selection.offset( m_distance ) );
                                    if ( m_selection_range.upper_left().row() < updated_range.upper_left().row()
                                            && transformed_intersection.lower_right().row() < updated_range.lower_right().row() ) {
                                        // shrink the range
                                        updated_range = updated_range_type( transformed_intersection.upper_left(),
                                                                            std::max( transformed_intersection.lower_right(), geometry::point( tmp_current_coverage.lower_right() ) ) );
                                    }
                                } else if ( relocated_source_range.does_intersect( updated_range ) ) {
                                    // only do something if the relocated selection does intersect the current range
                                    const geometry::rectangle_type tmp_current_coverage( *updated_range.subtract( relocated_source_range ) );
                                    const geometry::rectangle_type transformed_intersection( relocated_source_range.intersection( updated_range ) );
                                    if ( m_is_whole_column_or_row_operation ||  ( relocated_source_range.upper_left().row() < updated_range.upper_left().row()
                                                                                  && transformed_intersection.lower_right().row() < updated_range.lower_right().row() ) ) {
                                        // shrink the range
                                        updated_range = updated_range_type( transformed_intersection.upper_left()
                                                                            , std::max( transformed_intersection.lower_right(), geometry::point( tmp_current_coverage.lower_right() ) )
                                                                          );
                                    }
                                }
                            }
                        }
                    }
                    break;

                case geometry::border_bottom:
                    if ( was_not_moved_horizontally ) {
                        if ( was_moved_downwards ) {
                            updated_range = updated_range.enclose_point( updated_range.lower_right().offset( m_distance ) );
                        } else { //was_moved_upwards
                            if ( geometry::border_top == target_area_border_type || geometry::border_all == target_area_border_type ) {
                                // we moved above our original range
                                updated_range = intersection_between_current_and_selection.offset( m_distance );
                            } else {
                                const geometry::rectangle_type relocated_source_range( m_selection_range.offset( m_distance ) );
                                if ( m_selection_range.does_intersect( updated_range ) && relocated_source_range.does_intersect( updated_range ) ) {
                                    // only do something if the relocated selection does intersect the current range
                                    const geometry::rectangle_type tmp_current_coverage( *updated_range.subtract( m_selection_range ) );
                                    const geometry::rectangle_type transformed_intersection( intersection_between_current_and_selection.offset( m_distance ) );
                                    // selection extends outside the current range?
                                    if ( m_selection_range.lower_right().row() > updated_range.lower_right().row()
                                            && transformed_intersection.upper_left().row() > updated_range.upper_left().row() ) {
                                        // shrink the range
                                        updated_range = updated_range_type( std::min( transformed_intersection.upper_left(), geometry::point( tmp_current_coverage.upper_left() ) ),
                                                                            tmp_current_coverage.lower_right() );
                                    } else if ( tmp_current_coverage.lower_right().row() == transformed_intersection.upper_left().row() - m_distance.row() - 1 &&
                                                tmp_current_coverage.upper_left().column() == transformed_intersection.upper_left().column() &&
                                                tmp_current_coverage.lower_right().column() == transformed_intersection.lower_right().column() ) {
                                        updated_range = updated_range_type( tmp_current_coverage.upper_left(), transformed_intersection.lower_right() );
                                    }
                                } else if ( relocated_source_range.does_intersect( updated_range ) ) {
                                    // only do something if the relocated selection does intersect the current range
                                    const geometry::rectangle_type tmp_current_coverage( *updated_range.subtract( relocated_source_range ) );
                                    const geometry::rectangle_type transformed_intersection( relocated_source_range.intersection( updated_range ) );
                                    // selection extends outside the current range?
                                    if ( m_is_whole_column_or_row_operation || ( relocated_source_range.lower_right().row() > updated_range.lower_right().row()
                                                                                 && transformed_intersection.upper_left().row() > updated_range.upper_left().row() ) ) {
                                        // shrink the range
                                        //TODO check if std::min gives the right result here
                                        updated_range = updated_range_type(
                                                            std::min( transformed_intersection.upper_left(), geometry::point( tmp_current_coverage.upper_left() ) ),
                                                            tmp_current_coverage.lower_right() );
                                    }
                                }
                            }
                        }
                    }
                    break;

                case geometry::border_left:
                    if ( was_not_moved_vertically ) {
                        if ( was_moved_left ) {
                            updated_range = updated_range.enclose_point( updated_range.upper_left().offset( m_distance ) );
                        } else {//was moved right
                            if ( geometry::border_right == target_area_border_type || geometry::border_all == target_area_border_type ) {
                                // we moved above our original range
                                updated_range = intersection_between_current_and_selection.offset( m_distance );
                            } else {
                                // only do something if the selection intersects the current range
                                const geometry::rectangle_type relocated_source_range( m_selection_range.offset( m_distance ) );
                                if ( m_selection_range.does_intersect( updated_range ) && relocated_source_range.does_intersect( updated_range ) ) {
                                    // only do something if the relocated selection does intersect the current range
                                    const geometry::rectangle_type tmp_current_coverage( *updated_range.subtract( m_selection_range ) );
                                    const geometry::rectangle_type transformed_intersection( intersection_between_current_and_selection.offset( m_distance ) );
                                    // selection extends outside the current range?
                                    if ( m_selection_range.upper_left().column() < updated_range.upper_left().column()
                                            && transformed_intersection.lower_right().column() < updated_range.lower_right().column() ) {
                                        // shrink the range
                                        updated_range = updated_range_type( transformed_intersection.upper_left(),
                                                                            std::max( transformed_intersection.lower_right(), geometry::point( tmp_current_coverage.lower_right() ) ) );

                                    }
                                } else if ( relocated_source_range.does_intersect( updated_range ) ) {
                                    // only do something if the relocated selection does intersect the current range
                                    const geometry::rectangle_type tmp_current_coverage( *updated_range.subtract( relocated_source_range ) );
                                    const geometry::rectangle_type transformed_intersection( relocated_source_range.intersection( updated_range ) );
                                    // selection extends outside the current range?
                                    if ( m_is_whole_column_or_row_operation || ( relocated_source_range.upper_left().column() < updated_range.upper_left().column()
                                                                                 && transformed_intersection.lower_right().column() < updated_range.lower_right().column() ) ) {
                                        // shrink the range
                                        updated_range = updated_range_type( transformed_intersection.upper_left(),
                                                                            std::max( transformed_intersection.lower_right(), geometry::point( tmp_current_coverage.lower_right() ) ) );

                                    }
                                }
                            }
                        }
                    }
                    break;

                case geometry::border_right:
                    if ( was_not_moved_vertically ) {
                        if ( was_moved_right ) {
                            updated_range = updated_range.enclose_point( updated_range.lower_right().offset( m_distance ) );
                        } else {//was moved left
                            if ( geometry::border_left == target_area_border_type || geometry::border_all == target_area_border_type ) {
                                // we moved above our original range
                                updated_range = intersection_between_current_and_selection.offset( m_distance );
                            } else {
                                // only do something if the selection intersects the current range
                                const geometry::rectangle_type relocated_source_range( m_selection_range.offset( m_distance ) );
                                if ( m_selection_range.does_intersect( updated_range ) && relocated_source_range.does_intersect( updated_range ) ) {
                                    // only do something if the relocated selection does intersect the current range
                                    const geometry::rectangle_type tmp_current_coverage( *updated_range.subtract( m_selection_range ) );
                                    const geometry::rectangle_type transformed_intersection( intersection_between_current_and_selection.offset( m_distance ) );
                                    if ( tmp_current_coverage.lower_right().column() == transformed_intersection.upper_left().column() - m_distance.column() - 1 &&
                                            tmp_current_coverage.upper_left().row() == transformed_intersection.upper_left().row() &&
                                            tmp_current_coverage.lower_right().row() == transformed_intersection.lower_right().row() ) {
                                        // merge with the right
                                        updated_range = updated_range_type( tmp_current_coverage.upper_left(), transformed_intersection.lower_right() );
                                    }
                                    // selection extends outside the current range?
                                    else if ( m_selection_range.lower_right().column() > updated_range.lower_right().column()
                                              && transformed_intersection.upper_left().column() > updated_range.upper_left().column() ) {
                                        // shrink the range
                                        updated_range = updated_range_type(
                                                            updated_range_type::point_type( transformed_intersection.upper_left().row(), get_leftmost_column( transformed_intersection.upper_left(), tmp_current_coverage.upper_left() ) ),
                                                            tmp_current_coverage.lower_right() );
                                    }
                                } else if ( relocated_source_range.does_intersect( updated_range ) ) {
                                    const geometry::rectangle_type transformed_intersection( relocated_source_range.intersection( updated_range ) );
                                    // selection extends outside the current range?
                                    if ( m_is_whole_column_or_row_operation || ( relocated_source_range.lower_right().is_strict_right_of( updated_range.lower_right() )
                                                                                 && transformed_intersection.upper_left().is_strict_right_of( updated_range.upper_left() ) ) ) {
                                        const geometry::rectangle_type tmp_current_coverage( *updated_range.subtract( relocated_source_range ) );
                                        updated_range = updated_range_type( tmp_current_coverage.upper_left(), tmp_current_coverage.lower_right() );
                                    }
                                }
                            }
                        }
                    }
                    break;

                case geometry::border_all: {
                    updated_range = updated_range.offset( m_distance );
                }
                break;

            }

            //updated_range = n->precedents->position().cyclic_offset<false, sheet_dimension>( geometry::rectangle_type( n->precedents->position() ).distance( updated_range ) );

            if (  ( !m_is_move_on_same_sheet || updated_range != current_coverage ) ) {
                m_node_info_block.push_back( move_node_info( n, updated_range ) );
            }
        }
    }
    return true;
}
