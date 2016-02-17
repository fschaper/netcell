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

#include <wss/rectangle.hpp>
#include <wss/delete_object.hpp>

#include <boost/optional.hpp>

#include <wss/allocation.hpp>

namespace r
{
    using namespace geometry;
    // typedef sheet_range r_tree_rectangle_type;
    typedef geometry::rectangle_type r_tree_rectangle_type;
    namespace utility
    {
        /*!
         * \brief
         * performs a comparison operation on the second element of a pair.
         *
         * \param type_T
         * pair type to do the comparison on
         *
         * \param policy_T
         * policy to be applied. f.ex. std::less
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class type_T, template <class> class policy_T>
        class unary_compare_second : public std::unary_function<type_T, typename type_T::second_type >
        {
        public:
            typedef typename std::unary_function<type_T, typename type_T::second_type >::result_type result_type;
            typedef typename std::unary_function<type_T, typename type_T::second_type >::argument_type argument_type;

            unary_compare_second( const typename type_T::second_type& value ) : m_value( value ) {}
            result_type operator()( const argument_type& argument ) const {
                return policy_T<typename type_T::second_type>()( argument.second, m_value );
            }
        private:
            const typename type_T::second_type& m_value;
        };

        /*!
         * \brief
         * performs a comparison operation on the second element of a pair.
         *
         * \param type_T
         * pair type to do the comparison on
         *
         * \param policy_T
         * policy to be applied. f.ex. std::less
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class type_T, template <class> class policy_T>
        struct binary_compare_second : public std::binary_function<type_T, type_T, bool> {
            typedef typename std::binary_function<type_T, type_T, bool >::result_type result_type;
            typedef typename std::binary_function<type_T, type_T, bool >::first_argument_type first_argument_type;
            typedef typename std::binary_function<type_T, type_T, bool >::second_argument_type second_argument_type;

            result_type operator()( const first_argument_type& p1, const second_argument_type& p2 ) const {
                return policy_T<typename type_T::second_type>()( p1.second, p2.second );
            }
        };

        static inline size_t calc_area_enlargement( const r_tree_rectangle_type& r1, const r_tree_rectangle_type& r2 )
        {
            typedef r_tree_rectangle_type::integer_type my_int_t;
            const my_int_t upper_left_row       = std::min( r1.upper_left().row(),      r2.upper_left().row() ) ;
            const my_int_t upper_left_column    = std::min( r1.upper_left().column(),   r2.upper_left().column() );
            const my_int_t lower_right_row      = std::max( r1.lower_right().row(),     r2.lower_right().row() );
            const my_int_t lower_right_column   = std::max( r1.lower_right().column(),  r2.lower_right().column() );

            return ( ( lower_right_column - upper_left_column ) + 1 ) * ( ( lower_right_row - upper_left_row ) + 1 ) - r1.area();
        }
    }

    /*!
     * \brief
     * r tree implementation
     *
     * based on the paper
     * A. Guttman, R-trees: A dynamic index structure for spatial searching (1984).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template
    <
    class value_T
    , unsigned int min_leaves = 15
    , unsigned int max_leaves = 35
    >
    class tree
    {
        // assert that min_leaves > 2 and min_leaves <= ( max_leaves / 2)
        BOOST_STATIC_ASSERT( min_leaves >= 2 && min_leaves <= ( max_leaves / 2 ) );

        /*!
         * \brief
         * result for runtime type detection.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct node
                : non_instantiable {
            enum type { leaf, branch };
        };

        /*!
         * \brief
         * base functionality for all node types.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct node_base {
            /*!
             * \brief
             * constructor.
             *
             * all nodes feature a position.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
        protected:
            node_base( const r_tree_rectangle_type& position )
                : position( position ) {}
        public:
            /*!
             * \brief
             * destructor.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            virtual ~node_base() {}

            virtual void destroy() = 0;

            /*!
             * \brief
             * returns the type of node.
             *
             * deriving classes will have to implement this.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            virtual typename node::type type() const = 0;

            // position of the node
            r_tree_rectangle_type position;
        };

        /*!
         * \brief
         * leaf node.
         *
         * leaf nodes, by definition only maintain a position
         * and a value.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct leaf_node : node_base {
            friend class memory::pooled_creator<leaf_node>;

        private:
            leaf_node( const r_tree_rectangle_type& position, const value_T& value )
                : node_base( position ), value( value ) {}

        public:
            static leaf_node* create( const r_tree_rectangle_type& position, const value_T& value ) {
                return memory::pooled_creator<leaf_node>::create( position, value );
            }
            /*!
             * \brief
             * RTI information that this is a leaf node
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            virtual typename node::type type() const {
                return node::leaf;
            }

            virtual void destroy() {
                memory::pooled_creator<leaf_node>::destroy( this );
            }

            // mutable value of the node.
            // since the value of the node does not change the state of the tree
            // it may be mutable.
            mutable value_T value;
        };

        /*!
         * \brief
         * sorting algorithm that will sort two passed nodes by their area.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct sort_by_area
                : std::binary_function<const node_base* const, const node_base* const, bool> {
            bool operator()( const node_base* const left, const node_base* const right ) const {
                return left->position.area() < right->position.area();
            }
        };

        /*!
         * \brief
         * branch node. may contain other branch nodes or leaf nodes.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct branch_node : node_base {

            friend class memory::pooled_creator<branch_node>;

            typedef node_base* value_type;
            typedef std::vector<node_base*> childnode_container_type;

            // we implement the two typedefs in order to be able to use
            // the back_inserter_iterator.
            typedef typename childnode_container_type::reference reference;
            typedef typename childnode_container_type::const_reference const_reference;

            /*!
             * \brief
             * constructor.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
        private:
            branch_node( const r_tree_rectangle_type& position )
                : node_base( position ) {
                childnodes.reserve( max_leaves );
            }
        public:
            static branch_node* create( const r_tree_rectangle_type& position ) {
                return memory::pooled_creator<branch_node>::create( position );
            }

            /*!
             * \brief
             * destructor.
             *
             * will free all contained branch/leaf nodes.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            ~branch_node() {}

            virtual void destroy() {
                std::for_each( childnodes.begin(), childnodes.end(), boost::bind( &node_base::destroy, _1 ) );
                memory::pooled_creator<branch_node>::destroy( this );
            }

            /*!
             * \brief
             * RTI information that signifies the object as being a branch node.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            virtual typename node::type type() const {
                return node::branch;
            }

            /*!
             * \brief
             * will return true in case the object contains objects that are of
             * leaf type.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            inline bool is_leaf_node() const {
                return !childnodes.empty() && childnodes.front()->type() == node::leaf;
            }

            /*!
             * \brief
             * add the passed node to the branch and adjust the bounding rect.
             *
             * \param
             * node_base * node - the node to be added to the object.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            inline void push_back( node_base* node ) {
                this->position.intrusive_enclose_into_self( node->position );
                childnodes.push_back( node );
            }

            /*!
             * \brief
             * will iterate through all contained objects to readjust the
             * bounding rect.
             *
             * in case we have added or removed an element from the tree
             * all nodes from that branch will have to update their bounding
             * rect.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            inline void readjust_bounds() {
                if ( ! childnodes.empty() ) {
                    r_tree_rectangle_type tmp( childnodes[ 0 ]->position );
                    for ( typename childnode_container_type::const_iterator it = childnodes.begin(), end = childnodes.end()
                            ; it != end; ++it ) {
                        tmp.intrusive_enclose_into_self( ( *it )->position );
                    }
                    this->position = tmp;
                }
            }

            // childnodes
            childnode_container_type childnodes;
        };

        /*!
         * \brief
         * callback to find and merge nodes
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        class erase_mergable_nodes
        {
        public:
            /*!
             * \brief
             * constructor.
             *
             * \param
             * r_tree_rectangle_type& merge_area - the passed rectangle will be updated so it encloses
             *                 all nodes that were erased by the operation.
             *
             * \param
             * const value_T& search_value - the value that a node needs to contain in order to
             *                 be able to merge.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            erase_mergable_nodes( r_tree_rectangle_type& merge_area, const value_T& search_value )
                : m_merge_area( merge_area )
                , m_search_value( search_value ) {}

            /*!
             * \brief
             * test if two nodes could be merged into one (a border is adjacent or one node encloses
             * the other) and both nodes carry the same information. In that case the operation will
             * return true, signifying that the old node has to be removed as the node to be added
             * to the tree will now enclose "area(old node) U area(new node)" the both respective areas.
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            bool operator()( const r_tree_rectangle_type& r, const value_T& v ) const {
                // in case the border of the original area to be added matches and the value is the same
                // enclose the nodes bounding rect into the area to be returned.
                if ( m_merge_area.border_contact_type( r ) != contact_none && v == m_search_value ) {
                    m_merge_area.intrusive_enclose_into_self( r );
                    // erase the old node information
                    return true;
                }
                // the node has to stay - either because the nodes information differs
                // or there is no contacting border.
                return false;
            }

        private:
            mutable r_tree_rectangle_type& m_merge_area;
            const value_T& m_search_value;
        };

        typedef std::list<branch_node*> reinsertion_list_type;

    public:
        static void release_memory( bool purge = false ) {
            memory::pooled_creator<branch_node>::release_memory( purge );
            memory::pooled_creator<leaf_node>::release_memory( purge );
        }

        typedef value_T value_type;
        /*!
         * \brief
         * minimum number of leaves a node has to hold to be maintained.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static const unsigned int min_leaves_per_node = min_leaves;

        /*!
         * \brief
         * maximum number of leaves a node may hold before it is split.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static const unsigned int max_leaves_per_node = max_leaves;

        /*!
         * \brief
         * used for the "used range" method.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        typedef boost::optional<r_tree_rectangle_type> optional_rectangle_type;

        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        tree()
            : m_root( NULL )
        {}

        /*!
         * \brief
         * copy constructor.
         *
         * will create a copy of the tree.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        tree( const tree& other )
            : m_root( static_cast<branch_node*>( other.m_root ) ) {}

        /*!
         * \brief
         * destructor.
         *
         * will free all nodes.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        ~tree() {
            if ( m_root != NULL ) {
                m_root->destroy();
                m_root = NULL;
            }
        }

        /*!
         * \brief
         * insert a new value into the tree for the passed position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void insert( const r_tree_rectangle_type& position, value_type value, bool try_merge = false ) {
            if ( try_merge ) {
                // the area in the container that will need to be set to the new value
                // in case we could find nodes that we could merge the callback will
                // enclose the old node coverage and remove the old information.
                // essential we will in the end either get the original area back (no merge found)
                // or an enlarged area where we will insert the new information
                r_tree_rectangle_type merge_area( position );
                // callback with border matching test
                erase_mergable_nodes eraser( merge_area, value );
                // to find all nodes with possibly matching borders grow the search rectangle
                // so other borders might possibly intersect. as long as we can remove nodes
                // and merge their areas, continue the operation
                geometry::generic_rectangle<geometry::point> tmp_pos = position.grow( 1, 1 );
                while ( remove( tmp_pos, eraser ) == true );
                // in case the merge_area is larger than the original requests area
                // we have performed a merge. in that case we call insert again, this time with our
                // updated rectangle and try again with the new rectangles boundaries.
                if ( merge_area != position ) {
                    insert( merge_area, value, true );
                    return;
                }
            }

            leaf_node* leaf = leaf_node::create( position, value );
            if ( m_root ) {
                // the internal insert function will determine the location at which
                // the node will be inserted starting from the root node.
                insert( leaf, m_root );
            } else {
                // in case that we don't have a root node yet we have to add one.
                // (CL1 initialize: set N to be the root node)
                m_root = branch_node::create( position );
                static_cast<branch_node*>( m_root )->childnodes.push_back( leaf );
            }
        }

        /*!
         * \brief
         * fires the callback for all leaf nodes in the tree that
         * intersect with "position". In case the callback returns
         * true the node will be removed from the tree.
         *
         * as a side-effect nodes may be re-inserted in case a branch
         * would otherwise contain less than min. nodes.
         *
         * callback signature:
         * bool callback( const r_tree_rectangle_type& node_position, value& );
         *
         * \param
         * const r_tree_rectangle_type& position - position that in case it intersects with
         *       a nodes position will result in the callback being called.
         *
         * \param
         * const remove_callback_T& callback - callback that will be called
         *       for every intersecting node. in case the callback returns
         *       true, the node will be removed from the tree.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class remove_callback_T>
        bool remove( const r_tree_rectangle_type& position, const remove_callback_T& callback ) {
            if ( ! m_root ) {
                // nothing to remove.
                return false;
            }

            reinsertion_list_type reinsertion_list;
            bool did_remove = remove( m_root, position, reinsertion_list, callback );

            if ( m_root->childnodes.empty() ) {
                m_root->destroy();
                m_root = NULL;
            }

            // re-connect all leaf nodes from the reinsertion list.
            for ( typename reinsertion_list_type::iterator it = reinsertion_list.begin(), end = reinsertion_list.end()
                    ; it != end; ++it ) {
                assert( ( *it )->type() == node::branch );
                reinsert( *it );
            }

            return did_remove;
        }

        /*!
         * \brief
         * query the tree for leaf nodes which intersect with the passed position.
         *
         * the callback will be fired for every position found in the tree
         * until the callback returns false to terminate the search.
         *
         * callback signature:
         * bool callback( const r_tree_rectangle_type& node_position, value& );
         *
         * \param
         * const r_tree_rectangle_type& position - position that in case it intersects with
         *       a nodes position will result in the callback being called.
         *
         * \param
         * const query_callback_T& callback - callback that will be called
         *       for every intersecting node. in case the callback returns
         *       false, the search will be aborted.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class query_callback_T>
        void query( const r_tree_rectangle_type& position, query_callback_T& callback ) {
            if ( ! m_root ) {
                // nothing to query.
                return;
            }

            query( m_root, position, callback );
        }

        /*!
         * \brief
         * max. continuous region that is covered by the tree.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        optional_rectangle_type used_range() const {
            if ( m_root ) {
                return m_root->position;
            } else {
                return boost::optional<r_tree_rectangle_type>();
            }
        }

    private:
        /*!
         * \brief
         * re-insert nodes that were removed from the tree during a remove
         * operation when a node would otherwise have had less than "min"
         * elements.
         *
         * \param
         * branch_node * parent_node - under filled node whose leaves
         *                             should be re-inserted.
         *
         * \see
         * r_tree::remove
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void reinsert( branch_node* parent_node ) {
            assert( parent_node->type() == node::branch );

            if ( parent_node->is_leaf_node() ) {
                // re-insert all leaf nodes
                typename branch_node::childnode_container_type& childnodes = parent_node->childnodes;
                if ( ! m_root && ! childnodes.empty() ) {
                    m_root = branch_node::create( ( *childnodes.begin() )->position );
                    static_cast<branch_node*>( m_root )->childnodes.push_back( static_cast<leaf_node*>( *childnodes.begin() ) );
                    childnodes.erase( childnodes.begin() );
                }
                while ( ! childnodes.empty() ) {
                    insert( static_cast<leaf_node*>( *childnodes.begin() ), m_root );
                    childnodes.erase( childnodes.begin() );
                }
            } else {
                // traverse the subtree recursively to find and re-connect all
                // leaf nodes.
                while ( ! parent_node->childnodes.empty() ) {
                    branch_node* subtree = static_cast<branch_node*>( *parent_node->childnodes.begin() );
                    reinsert( subtree );
                    parent_node->childnodes.erase( parent_node->childnodes.begin() );
                }
            }
            parent_node->destroy();
        }

        /*!
         * \brief
         * query the tree for leaf nodes which intersect with the passed position.
         *
         * the callback will be fired for every position found in the tree
         * until the callback returns false to terminate the search.
         *
         * will recurse for every branch which intersects with the search
         * rectangle.
         *
         * callback signature:
         * bool callback( const r_tree_rectangle_type& node_position, value& );
         *
         * \param
         * branch_node * parent_node - branch to start the query from
         *
         * \param
         * const r_tree_rectangle_type& position - position that in case it intersects with
         *       a nodes position will result in the callback being called.
         *
         * \param
         * const query_callback_T& callback - callback that will be called
         *       for every intersecting node. in case the callback returns
         *       false, the search will be aborted.
         *
         * \return
         * true in case the query shall be continue it's search. false in case
         * the query should abort.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class query_callback_T>
        bool query( branch_node* parent_node, const r_tree_rectangle_type& r, query_callback_T& callback ) {
            assert( parent_node->type() == node::branch );
            bool continue_query = true;
            if ( ! parent_node->is_leaf_node() ) {
                // in case the current node does not contain leaf-nodes we descend
                // further down the tree.
                typename branch_node::childnode_container_type& childnodes = parent_node->childnodes;
                for ( typename branch_node::childnode_container_type::iterator it = childnodes.begin()
                        ; continue_query && it != childnodes.end(); ++it ) {
                    // call query for all nodes which do intersect with
                    // the rectangle we want to search for.
                    if ( ( *it )->position.does_intersect( r ) ) {
                        continue_query = query( static_cast<branch_node*>( *it ), r, callback );
                    }
                }
            } else {
                // in case a leaf node intersects with the search region and the callback
                // requests termination of the query, abort.
                typename branch_node::childnode_container_type& childnodes = parent_node->childnodes;
                for ( typename branch_node::childnode_container_type::iterator it = childnodes.begin()
                        ; continue_query && it != childnodes.end(); ++it ) {
                    if ( ( *it )->position.does_intersect( r ) ) {
                        assert( ( *it )->type() == node::leaf );
                        continue_query = callback( static_cast<const r_tree_rectangle_type&>( ( *it )->position ), static_cast<leaf_node*>( *it )->value );
                    }
                }
            }
            return continue_query;
        }

        /*!
         * \brief
         * fires the callback for all leaf nodes in the tree that
         * intersect with "position". In case the callback returns
         * true the node will be removed from the tree.
         *
         * as a side-effect nodes may be re-inserted in case a branch
         * would otherwise contain less than min. nodes.
         *
         * callback signature:
         * bool callback( const r_tree_rectangle_type& node_position, value& );
         *
         * \param
         * branch_node * parent_node - branch where to search for nodes to
         *       be removed.
         *
         * \param
         * const r_tree_rectangle_type& position - position that in case it intersects with
         *       a nodes position will result in the callback being called.
         *
         * \param
         * const remove_callback_T& callback - callback that will be called
         *       for every intersecting node. in case the callback returns
         *       true, the node will be removed from the tree.
         *
         * \return
         * returns true in case a node has been removed. in that case the parent
         * nodes have to re-adjust their bounding rect's.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class remove_callback_T>
        bool remove( branch_node* parent_node, const r_tree_rectangle_type& r, reinsertion_list_type& reinsertion_list, const remove_callback_T& callback ) {
            assert( parent_node->type() == node::branch );

            bool element_was_removed = false;
            if ( ! parent_node->is_leaf_node() ) {
                // in case the current node does not contain leaf-nodes we descend
                // further down the tree.
                typename branch_node::childnode_container_type& childnodes = parent_node->childnodes;
                for ( typename branch_node::childnode_container_type::iterator it = childnodes.begin()
                        ; it != childnodes.end(); ) {
                    // call remove for all nodes which do intersect with
                    // the rectangle we want to remove.
                    if ( ( *it )->position.does_intersect( r ) ) {
                        element_was_removed = remove( static_cast<branch_node*>( *it ), r, reinsertion_list, callback );
                        // in case an element was removed from the tree check if
                        // the node still contains enough nodes to be maintained.
                        if ( element_was_removed && static_cast<branch_node*>( *it )->childnodes.size() < min_leaves_per_node ) {
                            reinsertion_list.push_back( static_cast<branch_node*>( *it ) );
                            it = childnodes.erase( it );
                        } else {
                            ++it;
                        }
                    } else {
                        ++it;
                    }
                }
            } else {
                // in case a leaf node intersects with the search region and the callback
                // requests deletion, remove the node and propagate the change.
                typename branch_node::childnode_container_type& childnodes = parent_node->childnodes;
                for ( typename branch_node::childnode_container_type::iterator it = childnodes.begin()
                        ; it != childnodes.end(); ) {
                    assert( ( *it )->type() == node::leaf );
                    if ( ( *it )->position.does_intersect( r ) && callback( static_cast<const r_tree_rectangle_type&>( ( *it )->position ), static_cast<leaf_node*>( *it )->value ) ) {
                        ( *it )->destroy();
                        // erase will return an iterator to the next element (or end).
                        it = childnodes.erase( it );
                        element_was_removed = true;
                    } else {
                        ++it;
                    }
                }
            }

            // in case a node was removed, readjust the bounding rect.
            if ( element_was_removed ) {
                parent_node->readjust_bounds();
            }

            return element_was_removed;
        }

        /*!
         * \brief
         * will find the branch in which to insert the new node
         * the decision is based upon area enlargement. the node that would see
         * the smallest increase of it's area in case the new rectangle was inserted
         * will be chosen. in case more than one node ties, the node with the smallest
         * increase in area will be chosen.
         *
         * \param
         * branch_node * parent_node - branch to start the search from
         *
         * \param
         * const r_tree_rectangle_type& r - position of the new node to be inserted.
         *
         * \returns
         * branch where the new node should be inserted.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        branch_node* choose_subtree( branch_node* parent_node, const r_tree_rectangle_type& r ) {
            assert( parent_node->type() == node::branch );

            typename branch_node::childnode_container_type& childnodes = parent_node->childnodes;
            if ( childnodes.size() > 1 ) {
                typedef std::pair<typename branch_node::childnode_container_type::size_type, unsigned int> area_lookup_pair_type;
                typedef std::vector<area_lookup_pair_type> area_lookup_list_type;

                // determine the area enlargement for all nodes
                //area_lookup_list_type area_enlargement;
                //area_enlargement.reserve( parent_node->childnodes.size() );
                typedef typename branch_node::childnode_container_type::size_type my_size_t;
                my_size_t counter = 0;
                typename branch_node::childnode_container_type::const_iterator it = childnodes.begin();
                my_size_t first = utility::calc_area_enlargement( ( *it )->position, r );
                ++it;
                my_size_t second = utility::calc_area_enlargement( ( *it )->position, r );
                unsigned int first_idx = 0, second_idx = 1;
                if ( second > first ) {
                    std::swap( second, first );
                    std::swap( second_idx, first_idx );
                }
                for ( typename branch_node::childnode_container_type::const_iterator end = childnodes.end(); it != end; ++it ) {
                    const my_size_t current = utility::calc_area_enlargement( ( *it )->position, r );
                    if ( current < first ) {
                        second = first;
                        second_idx = first_idx;
                        first = current;
                        first_idx = counter;
                    } else if ( current < second ) {
                        second = current;
                        second_idx = counter;
                    }
                }
                // optimization: only sort up to the second element to make tie decision.
                // if ( first != second ) {
                return static_cast<branch_node*>( childnodes[ first_idx ] );
                //                 } else {
                //                     // at least two of the areas have the same enlargement factor.
                //                     // we have to sort the whole vector to be able to find all nodes which share a common area factor.
                //                     std::sort( area_enlargement.begin(), area_enlargement.end(), utility::binary_compare_second<area_lookup_pair_type, std::less>() );
                //                     // in the range of nodes which have the same enlargement factor find the one with
                //                     // the smallest area.
                //                     typename area_lookup_list_type::const_iterator find_it = std::find_if( area_enlargement.begin(), area_enlargement.end(), utility::unary_compare_second<area_lookup_pair_type, std::not_equal_to>( area_enlargement[0].second ) );
                //                     typename branch_node::childnode_container_type::iterator childnode_end = ( find_it == area_enlargement.end() ) ? childnodes.end() : childnodes.begin() + find_it->first;
                //                     return static_cast<branch_node*>( *std::min_element( childnodes.begin(), childnode_end, sort_by_area() ) );
                //                 }
            } else {
                return static_cast<branch_node*>( parent_node->childnodes[0] );
            }
        }

        void insert( leaf_node* node_to_insert, branch_node* parent_node ) {
            assert( parent_node->type() == node::branch && node_to_insert->type() == node::leaf );

            // adjust the bounding rect of the root node
            parent_node->position.intrusive_enclose_into_self( node_to_insert->position );

            if ( parent_node->is_leaf_node() ) {
                parent_node->push_back( node_to_insert );
            } else {
                // search for a suitable branch to insert the new node in
                // and descent until a leaf is found. enlarge the bounding rect
                // as we go.
                branch_node* branch = parent_node;
                while ( ! branch->is_leaf_node() ) {
                    branch = choose_subtree( branch, node_to_insert->position );
                    branch->position.intrusive_enclose_into_self( node_to_insert->position );
                }
                // call recursively to be able to adjust the tree
                // in case the parent fills up.
                insert( node_to_insert, branch );
            }

            // split the node to form into two nodes in case it overflows.
            if ( parent_node->childnodes.size() > tree::max_leaves_per_node ) {

                // pick seeds. the first two elements in the map "area_sort" will
                // be the ones which are most inefficient when grouped together.
                typename branch_node::childnode_container_type& childnodes = parent_node->childnodes;
                {
                    // the largest amount of wasted space. initialize
                    // to absolute minimum for the data type.
                    long largest_amount_of_wasted_space_found = std::numeric_limits<long>::min();
                    // the two entries that formed the wasted space.
                    std::pair<typename branch_node::childnode_container_type::size_type, typename branch_node::childnode_container_type::size_type> pair;

                    for ( typename branch_node::childnode_container_type::size_type index_e1 = 0, end_index = childnodes.size();
                            index_e1 != end_index; ++index_e1 ) {
                        const node_base* const e1 = childnodes[index_e1];
                        for ( typename branch_node::childnode_container_type::size_type index_e2 = index_e1 + 1;
                                index_e2 != end_index; ++index_e2 ) {
                            const node_base* const e2 = childnodes[index_e2];
                            const long wasted_space = utility::calc_area_enlargement( e1->position, e2->position ) - e2->position.area(); // e1->position.enclose( e2->position ).area() - e1->position.area() - e2->position.area();
                            if ( wasted_space > largest_amount_of_wasted_space_found ) {
                                largest_amount_of_wasted_space_found = wasted_space;
                                pair = std::make_pair( index_e1, index_e2 );
                            }
                        }
                    }
                    // the first pair in the map will be the one that we have identified
                    // as being the most wasteful when put into one group.
                    // we swap their position in the child node list so both are at
                    // the beginning of our list to simplify the rest of the algorithm.

                    // safeguard against pair.second == 0
                    if ( pair.second == 0 ) {
                        std::swap( childnodes[ 1 ], childnodes[pair.first] );
                    } else {
                        std::swap( childnodes[ 0 ], childnodes[pair.first] );
                        std::swap( childnodes[ 1 ], childnodes[pair.second] );
                    }
                }

                // create the two new branch nodes as the two groups to sort
                // the rest of the child elements under.
                branch_node* group_1 = branch_node::create( childnodes[0]->position );
                group_1->childnodes.push_back( childnodes[0] );
                childnodes[0] = group_1;
                branch_node* group_2 = branch_node::create( childnodes[1]->position );
                group_2->childnodes.push_back( childnodes[1] );
                childnodes[1] = group_2;

                // get rid of the magic number. number of groups the node will be split into.
                const typename  branch_node::childnode_container_type::size_type number_of_group_nodes = 2;

                // starting from the second element (starting right behind our two new group nodes)
                // sort the rest of the nodes into one of the two groups.
                {
                    // a requirement for the r-tree is that min_leaves_per_node is <= (max_leaves_per_node/2)
                    // to ensure that both nodes will meet the minimum node size requirement we will have
                    // to introduce an additional check during our sort by the time
                    // the number of remaining nodes reaches min_leaves_per_node. until that point however
                    // we can skip the tests required even though this means partial code duplication.

                    // sort the elements into one of the two groups until the remaining elements
                    // equal min_leaves_per_node.
                    typename branch_node::childnode_container_type::iterator it = childnodes.begin() + number_of_group_nodes
                            , end = childnodes.end() - min_leaves_per_node;
                    do {
                        for ( ; it != end; ++it ) {
                            const unsigned int area_enlargement_cost_group1 = utility::calc_area_enlargement( group_1->position, ( *it )->position ); // ( group_1->position.enclose( ( *it )->position ).area() - group_1->position.area() );
                            const unsigned int area_enlargement_cost_group2 = utility::calc_area_enlargement( group_2->position, ( *it )->position ); //( group_2->position.enclose( ( *it )->position ).area() - group_2->position.area() );

                            // we could call insert here - but directly adding the nodes
                            // is more efficient (and we need no overflow treatment here).
                            if ( area_enlargement_cost_group1 < area_enlargement_cost_group2 ) {
                                group_1->push_back( *it );
                            } else {
                                group_2->push_back( *it );
                            }
                        }
                        end = childnodes.end();
                        // in case both nodes have already reached min_leaves_per_node we can
                        // continue with the check-less insert
                        if ( group_1->childnodes.size() < min_leaves_per_node
                                || group_2->childnodes.size() < min_leaves_per_node ) {
                            // for the rest of the elements we have to ensure that both groups will
                            typename branch_node::childnode_container_type::size_type remaining_childnode_counter = std::distance( it, end );
                            for ( ; it != end; ++it ) {
                                // in case one of the two nodes need the rest of the remaining elements
                                // to reach min_leaves_per_node number of elements we assign the
                                // test of the nodes directly.
                                if ( ( group_1->childnodes.size() + remaining_childnode_counter ) == min_leaves_per_node ) {
                                    typename branch_node::childnode_container_type::size_type items_required_to_reach_min = min_leaves_per_node - group_1->childnodes.size();
                                    std::back_insert_iterator<branch_node> pusher( *group_1 );
                                    std::copy( it, it + items_required_to_reach_min, pusher );
                                    // we have copied all elements. set the iterator to end
                                    // to be able to exit the loop.
                                    it = end;
                                    break;
                                } else if ( ( group_2->childnodes.size() + remaining_childnode_counter ) == min_leaves_per_node ) {
                                    typename branch_node::childnode_container_type::size_type items_required_to_reach_min = min_leaves_per_node - group_2->childnodes.size();
                                    std::back_insert_iterator<branch_node> pusher( *group_2 );
                                    std::copy( it, it + items_required_to_reach_min, pusher );
                                    // we have copied all elements. set the iterator to end
                                    // to be able to exit the loop.
                                    it = end;
                                    break;
                                }

                                const unsigned int area_enlargement_cost_group1 = utility::calc_area_enlargement( group_1->position, ( *it )->position ); // ( group_1->position.enclose( ( *it )->position ).area() - group_1->position.area() );
                                const unsigned int area_enlargement_cost_group2 = utility::calc_area_enlargement( group_2->position, ( *it )->position ); //( group_2->position.enclose( ( *it )->position ).area() - group_2->position.area() );

                                if ( area_enlargement_cost_group1 < area_enlargement_cost_group2 ) {
                                    group_1->push_back( *it );
                                } else {
                                    group_2->push_back( *it );
                                }
                                --remaining_childnode_counter;
                            }
                        }
                    } while ( it != childnodes.end() );

                    // since we have grouped add elements besides our new two branches we have to erase
                    // the pointers from the old node.
                    parent_node->childnodes.erase( childnodes.begin() + number_of_group_nodes, childnodes.end() );
                }
            }
        }

    private:
        branch_node* m_root;
    };
}
