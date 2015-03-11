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

#pragma once

#include <wss/define.hpp>
#include <wss/friend.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <functional> // for std::less
#   include <iterator>   // for std::bidirectional_iterator_tag
#   include <cassert>    // for assert
#   include <memory>     // for std::auto_ptr
#   include <cstdio>     // for NULL
#   include <cstdlib>    // for std::size_t
#   include <boost/noncopyable.hpp>
#endif

#if defined( WIN32 )
#   pragma warning( disable : 4517 ) // disable access-declaration deprecated warning
#endif

namespace tree
{
    namespace trait
    {
        /*!
        * \brief
        * defines allocator and node passing options
        * for the node object.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        template
        <
        class base_T
        >
        struct default_node_trait
        {
            typedef std::allocator<base_T> allocator_type;
            typedef std::auto_ptr<base_T> auto_type;
        };
    }

    namespace policy
    {
        /*!
        * \brief
        * provides ordered insertion based on an defined
        * comparison object.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        template
        <
        class derived_T
        , class comparator_T
        >
        struct ordered_insertion
        {
            typedef comparator_T comparator_type;
            typedef derived_T derived_type;

            void attach( derived_T* n ) {
                derived_T* self = static_cast<derived_T*>( this );

                // check for self reference and double insertion
                if ( n == this || self->m_parent == n ) {
                    return;
                }

                // if this node is currently attached to some other node
                // disconnect it.
                n->detach();

                // attach to the new parent node
                n->m_parent = static_cast<derived_type*>( this );

                if ( ! self->m_first_child ) {
                    // if this is the first node we can simply attach it as the
                    // first and last child node.
                    self->m_first_child = n;
                    self->m_tailing_child = self->m_first_child;
                } else {
                    if ( m_comparator( *( self->m_tailing_child ), *n ) ) {
                        // based on the comparison attach this node to the end of the
                        // parent. (f.ex. with comparison operator '<': if the node to be attached
                        // is of smaller value
                        n->m_previous = self->m_tailing_child;
                        self->m_tailing_child->m_next = n;
                        self->m_tailing_child = n;
                    } else {
                        // start from the beginning of the list and compare every sibling node
                        // with the current one until the comparison fails. then prepends the
                        // node to the one that was found.
                        derived_type* looked_up_node = self->m_first_child;
                        for ( ; looked_up_node && m_comparator( *looked_up_node, *n )
                                ; looked_up_node = looked_up_node->m_next );

                        if ( looked_up_node == self->m_first_child ) {
                            // we have to exchange the first child of the list with this node
                            // and attach the former first child as successor.
                            n->m_next = self->m_first_child;
                            self->m_first_child->m_previous = n;
                            self->m_first_child = n;
                        } else {
                            // then prepend the node to the one that was found.
                            n->m_next = looked_up_node;
                            n->m_previous = looked_up_node->m_previous;
                            looked_up_node->m_previous->m_next = n;
                            looked_up_node->m_previous = n;
                        }
                    }
                }
            }

            comparator_type m_comparator;
        };

        /*!
         * \brief
         * nodes are attached in the orderer
         * the user appends them.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class derived_T>
        struct unordered_insertion {
            typedef derived_T derived_type;

            void attach_front( derived_T* n ) {
                derived_T* self = static_cast<derived_T*>( this );

                // check for self reference and double insertion
                if ( n == self || self->m_parent == n ) {
                    return;
                }

                // if this node is currently attached to some other node
                // disconnect it.
                n->detach();

                if ( ! self->m_first_child ) {
                    self->m_tailing_child = n;
                } else {
                    n->m_next = self->m_first_child;
                    self->m_first_child->m_previous = n;
                }
                self->m_first_child = n;
                n->m_parent = self;
            }

            void attach( derived_T* n ) {
                derived_T* self = static_cast<derived_T*>( this );

                // check for self reference and double insertion
                if ( n == self || self->m_parent == n ) {
                    return;
                }

                // if this node is currently attached to some other node
                // disconnect it.
                n->detach();

                // attach to the new parent node
                n->m_parent = static_cast<derived_type*>( this );

                n->m_previous = self->m_tailing_child;
                if ( self->m_tailing_child ) {
                    self->m_tailing_child->m_next = n;
                }

                if ( ! self->m_first_child ) {
                    self->m_first_child = n;
                }

                self->m_tailing_child = n;
            }
        };
    }

    /*!
    * \brief
    * defines a node that can be attached to an other
    * node to form a tree.
    *
    * \param derived_T
    * class that is deriving from node using CRTP
    *
    * \param comparator_T
    * comparison operation that should be used to
    * perform sorted inserts into the tree.
    *
    * \param allocator_trait_T
    * allocator that will be used to free child nodes
    * still attached to a node when the destructor gets
    * called.
    *
    * defines a node that can be attached to another
    * node to form a tree. the insertion of the node
    * into the parent child list can be controlled with
    * an comparison operation.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    template
    <
    class derived_T
    , class attach_policy_T = policy::ordered_insertion<derived_T, std::less<derived_T> >
    , class allocator_trait_T = trait::default_node_trait<derived_T>
    >
    class node
        : boost::noncopyable
        , public attach_policy_T
    {
        FRIEND_CLASS friendship_wrapper<attach_policy_T>::type;

        class base_iterator;
        class iterate_shallow;
        class iterate_deep;

        template<class value_T, class traversal_T>
        class node_iterator;

    public:
        typedef derived_T derived_type;
        typedef node<derived_T, attach_policy_T, allocator_trait_T> self_type;
        typedef typename allocator_trait_T::auto_type auto_type;
        typedef typename allocator_trait_T::allocator_type allocator_type;
        typedef std::size_t size_type;

        typedef node_iterator<derived_T, iterate_shallow> shallow_iterator;
        typedef node_iterator<const derived_T, iterate_shallow> const_shallow_iterator;

        typedef node_iterator<derived_T, iterate_deep> deep_iterator;
        typedef node_iterator<const derived_T, iterate_deep> const_deep_iterator;

        /*!
        * \brief
        * default constructor
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        node()
            : m_parent( NULL )
            , m_first_child( NULL )
            , m_tailing_child( NULL )
            , m_next( NULL )
            , m_previous( NULL )
            , m_allocator() {}

        /*!
        * \brief
        * constructor.
        *
        * \param p
        * allocator that will be used to free memory of
        * nodes still attached to the subtree when the
        * destructor gets called.
        *
        * constructor which allows to pass an custom
        * allocator object.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        node( const allocator_type& p )
            : m_parent( NULL )
            , m_first_child( NULL )
            , m_tailing_child( NULL )
            , m_next( NULL )
            , m_previous( NULL )
            , m_allocator( p ) {}

        /*!
        * \brief
        * cloning copy-constructor.
        *
        * \param other
        * will use the clone method of the passed node to
        * create a copy of the tree.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        node( const node& other )
            : m_parent( NULL )
            , m_first_child( NULL )
            , m_tailing_child( NULL )
            , m_next( NULL )
            , m_previous( NULL )
            , m_allocator( other.m_allocator ) {
            shallow_iterator it( const_cast<node&>( other ).begin_shallow() );
            shallow_iterator end( const_cast<node&>( other ).end_shallow() );
            for ( ; it != end; ++it ) {
                attach( static_cast<const derived_type*>( it.operator ->() )->clone() );
            }
        }

        /*!
        * \brief
        * destructor.
        *
        * will free all nodes still attached to the node
        * on object destruction using the specified allocator.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        virtual ~node() {
            // detach node from it's parent node - if any
            detach();
            // free all child nodes
            derived_type* current_node = m_first_child;
            derived_type* next_node = m_first_child;
            while ( next_node ) {
                current_node = next_node;
                next_node = next_node->m_next;
                m_allocator.destroy( current_node );
            }
        }

        /*!
        * \brief
        * attaches the passed node to 'this' one.
        *
        * \param n
        * node to be attached.
        *
        * attaches the passed node to 'this' one.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        void attach( auto_type n ) {
            attach_policy_T::attach( n.release() );
        }

        /*!
        * \brief
        * detach node from parent node and return it.
        *
        * detaches the node from it's parent node and
        * returns it.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        auto_type release() {
            if ( has_parent() ) {
                return auto_type( detach() );
            } else {
                return auto_type();
            }
        }


        /*!
         * \brief
         * connect all children to the parent node and unhook
         * the node from the tree.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        auto_type unlink() {
            if ( has_parent() ) {
                derived_type* next_node = m_first_child;
                derived_type* child_to_connect_to_parent;
                while ( next_node ) {
                    child_to_connect_to_parent = next_node;
                    next_node = next_node->m_next;
                    m_parent->attach( child_to_connect_to_parent->release() );
                }
                return release();
            } else {
                // can not delete the root-node.
                return auto_type();
            }
        }

        /*!
        * \brief
        * returns true if the node holds child elements.
        *
        * \returns
        * true of there are child nodes attached, false otherwise.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        bool has_children() const {
            return m_first_child != NULL;
        }

        /*!
        * \brief
        * returns true if the node is connected to an parent node.
        *
        * \returns
        * true if connected to an parent nodes attached, false otherwise.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        bool has_parent() const {
            return m_parent != NULL;
        }

        /*!
        * \brief
        * returns the parent node, if any.
        *
        * \returns
        * returns the parent node or NULL pointer.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        derived_type* parent() const {
            return m_parent;
        }

        /*!
        * \brief
        * iterator that marks the beginning of all direct
        * child nodes.
        *
        * \returns
        * iterator pointing at the fist child element.
        *
        * this iterator might be used to iterate over all child
        * elements of the current node. points to the first child
        * in the list.
        *
        * \see
        * end_shallow
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        shallow_iterator begin_shallow() {
            return shallow_iterator( m_first_child, NULL, static_cast<derived_type*>( this ) );
        }

        /*!
        * \brief
        * iterator that marks the end of the list of
        * direct child nodes.
        *
        * \returns
        * iterator that points to one element after the end
        * of the child elements.
        *
        * this iterator is used in conjunction with the
        * begin_shallow iterator to iterate over all child elements
        * of the current node. --end_shallow() points to the
        * last element in the list of direct children.
        *
        * \see
        * begin_shallow
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        shallow_iterator end_shallow() {
            return shallow_iterator( NULL, m_tailing_child, static_cast<derived_type*>( this ) );
        }

        /*!
        * \brief
        * iterator that can be used to iterate over the complete branch.
        *
        * \returns
        * iterator pointing to the first direct child of the current
        * node.
        *
        * \remarks
        * use --begin_deep() to include the current node itself.
        *
        * \see
        * end_deep
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        deep_iterator begin_deep() {
            return deep_iterator( m_first_child, static_cast<derived_type*>( this ), static_cast<derived_type*>( this ) );
        }

        /*!
        * \brief
        * iterator that can be used to iterate over the complete branch.
        *
        * \returns
        * iterator pointing one element past the end of the branch.
        *
        * \see
        * begin_deep
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        deep_iterator end_deep() {
            return deep_iterator( NULL, find_branch_end(), static_cast<derived_type*>( this ) );
        }

        /*!
        * \brief
        * const iterator that marks the beginning of all direct
        * child nodes.
        *
        * \returns
        * const iterator pointing at the fist child element.
        *
        * this const iterator might be used to iterate over all child
        * elements of the current node. points to the first child
        * in the list.
        *
        * \see
        * end_shallow
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        const_shallow_iterator begin_shallow() const {
            return const_shallow_iterator( m_first_child, NULL, static_cast<const derived_type*>( this ) );
        }

        /*!
        * \brief
        * const iterator that marks the end of the list of
        * direct child nodes.
        *
        * \returns
        * const iterator that points to one element after the end
        * of the child elements.
        *
        * this const iterator is used in conjunction with the
        * begin_shallow const iterator to iterate over all child elements
        * of the current node. --end_shallow() points to the
        * last element in the list of direct children.
        *
        * \see
        * begin_shallow
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        const_shallow_iterator end_shallow() const {
            return const_shallow_iterator( NULL, m_tailing_child, static_cast<const derived_type*>( this ) );
        }

        /*!
        * \brief
        * const iterator that can be used to iterate over the complete branch.
        *
        * \returns
        * const iterator pointing to the first direct child of the current
        * node.
        *
        * \remarks
        * use --begin_deep() to include the current node itself.
        *
        * \see
        * end_deep
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        const_deep_iterator begin_deep() const {
            return const_deep_iterator( m_first_child, static_cast<const derived_type*>( this ), static_cast<const derived_type*>( this ) );
        }

        /*!
        * \brief
        * const iterator that can be used to iterate over the complete branch.
        *
        * \returns
        * const iterator pointing one element past the end of the branch.
        *
        * \see
        * begin_deep
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        const_deep_iterator end_deep() const {
            return const_deep_iterator( NULL, find_branch_end(), static_cast<const derived_type*>( this ) );
        }

        /*!
        * \brief
        * return the number of immediate child nodes.
        *
        * \returns
        * std::size_t number of immediate child nodes
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        size_type size() const {
            std::size_t count = 0;
            derived_type* next_node = m_first_child;
            while ( next_node ) {
                next_node = next_node->m_next;
                ++count;
            }
            return count;
        }

        void remove_first() {
            if ( m_first_child ) {
                m_first_child->release();
            }
        }

        void remove_last() {
            if ( m_tailing_child ) {
                m_tailing_child->release();
            }
        }

    private:
        /*!
        * \brief
        * detach the current node from it's parent node if any.
        *
        * \returns
        * returns pointer to itself
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        derived_type* detach() {
            if ( m_parent ) {
                // detach from parent if on the begin or end of the list
                if ( m_parent->m_first_child == this ) {
                    m_parent->m_first_child = m_next;
                }

                if ( m_parent->m_tailing_child == this ) {
                    m_parent->m_tailing_child = m_previous;
                }

                // detach from siblings
                if ( m_previous ) {
                    m_previous->m_next = m_next;
                }

                if ( m_next ) {
                    m_next->m_previous = m_previous;
                }

                m_next = NULL;
                m_previous = NULL;
                m_parent = NULL;
            }
            return static_cast<derived_type*>( this );
        }

        /*!
        * \brief
        * located the end of a branch in the tree using recursive lookup.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        derived_type* find_branch_end() const {
            // look for the end of the tree. if the tailing child of the current node does itself has
            // children, forward the search on to that node.
            if ( m_tailing_child ) {
                return m_tailing_child->m_first_child ? m_tailing_child->m_first_child->find_branch_end() : m_tailing_child;
            } else {
                return static_cast<derived_type*>( const_cast<self_type*>( this ) );
            }
        }

    private:
        derived_type* m_parent;
        derived_type* m_first_child;
        derived_type* m_tailing_child;
        derived_type* m_next;
        derived_type* m_previous;
        allocator_type m_allocator;
    };

    /*!
    * \brief
    * helper class for the node iterators.
    *
    * defines functionality common to the different
    * iteration strategies.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    template
    <
    class derived_T
    , class attach_policy_T
    , class allocator_trait_T
    >
    class node<derived_T, attach_policy_T, allocator_trait_T>::base_iterator
    {
    protected:
        typedef derived_T derived_type;
    public:
        base_iterator( const derived_type* start_node, const derived_type* previous_node, const derived_type* parent_node )
            : m_current_node( start_node )
            , m_previous_node( previous_node )
#  ifdef _DEBUG
            , m_parent( parent_node )
#  endif // _DEBUG
        {}

        base_iterator( const base_iterator& other )
            : m_current_node( other.m_current_node )
            , m_previous_node( other.m_previous_node )
#  ifdef _DEBUG
            , m_parent( other.m_parent )
#  endif // _DEBUG
        {}

        /*!
        * \brief
        * compares two iterators of the same type with one another for equality.
        *
        * \param rhs
        * iterator to compare for equality.
        *
        * \returns
        * true iff the the current and the past iterator point at the
        * same element.
        *
        * \see
        * iterate_shallow | iterate_deep
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        bool operator ==( const base_iterator& rhs ) const {
#  ifdef _DEBUG
            assert( "trying to compare the iterators of a different tree or different start-nodes in the same tree (which would be ok but isn't supported)!"
                    && m_parent == rhs.m_parent );
#  endif // _DEBUG
            return m_previous_node == rhs.m_previous_node
                   && m_current_node == rhs.m_current_node;
        }

        /*!
        * \brief
        * compares two iterators of the same type with one another for inequality.
        *
        * \param rhs
        * iterator to compare for inequality.
        *
        * \returns
        * true iff the the current and the past iterator don't point at the
        * same element.
        *
        * \see
        * iterate_shallow | iterate_deep
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        bool operator !=( const base_iterator& rhs ) const {
            return !( *this == rhs );
        }

    protected:
        const derived_type* m_current_node;
        const derived_type* m_previous_node;
# ifdef _DEBUG
        const derived_type* m_parent;
# endif // _DEBUG
    };

    /*!
    * \brief
    * iterates over the direct children of a node.
    *
    * iterates over the direct children of a node without
    * descending into their respective child elements.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    template
    <
    class derived_T
    , class attach_policy_T
    , class allocator_trait_T
    >
    class node<derived_T, attach_policy_T, allocator_trait_T>::iterate_shallow
        : public base_iterator
    {
    public:
        iterate_shallow( const iterate_shallow& other )
            : base_iterator( other ) {}

    protected:
        using base_iterator::m_current_node;
        using base_iterator::m_previous_node;

        iterate_shallow( const derived_type* start_node, const derived_type* previous_node, const derived_type* parent_node )
            : base_iterator( start_node, previous_node, parent_node ) {}

        /*!
        * \brief
        * moves the cursor forward in the list of child elements.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        const derived_type* next() {
            assert( "tried to iterate past the end of the tree!"
                    && m_current_node );

            m_previous_node = m_current_node;
            m_current_node = m_current_node->m_next;

            return m_current_node;
        }

        /*!
        * \brief
        * moves the cursor backwards in the list of child elements.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        const derived_type* previous() {
            assert( "tried to iterate past the beginning of the tree!"
                    && ( m_current_node || m_previous_node ) );

            m_current_node = m_previous_node;
            m_previous_node = m_previous_node->m_previous;

            return m_current_node;
        }
    };

    /*!
    * \brief
    * iterates over the complete branch of the current node.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    template
    <
    class derived_T
    , class attach_policy_T
    , class allocator_trait_T
    >
    class node<derived_T, attach_policy_T, allocator_trait_T>::iterate_deep
        : public base_iterator
    {
    public:
        iterate_deep( const iterate_shallow& other )
            : base_iterator( other ) {}

    protected:
        using base_iterator::m_current_node;
        using base_iterator::m_previous_node;

        iterate_deep( const derived_type* start_node, const derived_type* previous_node, const derived_type* parent_node )
            : base_iterator( start_node, previous_node, parent_node ) {}

        /*!
        * \brief
        * moves the cursor forward in the list of child elements
        * and descends into them where possible.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        const derived_type* next() {
            assert( "tried to iterate past the end of the tree!"
                    && m_current_node );

            m_previous_node = m_current_node;
            if ( m_current_node->m_first_child ) {
                // if the node has children of its own decent into
                // the child list before continuing on
                m_current_node = m_current_node->m_first_child;
            } else {
                if ( m_current_node->m_next ) {
                    // no children - if the current child node has
                    // a sibling proceed with that one
                    m_current_node = m_current_node->m_next;
                } else if ( m_current_node->m_parent ) {
                    // no more children on this level - if the node
                    // has a parent element select the next sibling
                    // of the current node
                    m_current_node = m_current_node->m_parent->m_next;
                } else {
                    m_current_node = NULL;
                }
            }

            return m_current_node;
        }

        /*!
        * \brief
        * moves the cursor backwards in the list of child elements
        * when the last element of the list was reached proceed with the parent.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        const derived_type* previous() {
            assert( "tried to iterate past the beginning of the tree!"
                    && ( m_current_node || m_previous_node ) );

            if ( m_previous_node ) {
                m_current_node = m_previous_node;
                m_previous_node = m_previous_node->m_previous;
            } else if ( m_current_node->m_parent ) {
                m_current_node = m_current_node->m_parent;
                m_previous_node = m_current_node->m_previous;
            }
            return m_current_node;
        }
    };

    /*!
    * \brief
    * iterator base template for node objects.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    template
    <
    class derived_T
    , class attach_policy_T
    , class allocator_trait_T
    >
    template
    <
    class value_T
    , class traversal_T
    >
    class node<derived_T, attach_policy_T, allocator_trait_T>::node_iterator
        : public traversal_T
    {
        using traversal_T::next;
        using traversal_T::previous;
        using traversal_T::m_current_node;
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef value_T value_type;
        typedef int difference_type;
        typedef value_T* pointer;
        typedef value_T& reference;
        typedef node_iterator<value_T, traversal_T> self_type;

        node_iterator( const derived_T* start_node, const derived_T* previous_node, const derived_T* parent_node )
            : traversal_T( start_node, previous_node, parent_node ) {}

        /*!
        * \brief
        * moves the cursor forward in the list of elements.
        *
        * \returns
        * the modified iterator.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        node_iterator& operator ++() {
            next();
            return *this;
        }

        /*!
        * \brief
        * moves the cursor backwards in the list of elements.
        *
        * \returns
        * the modified iterator.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        node_iterator& operator --() {
            previous();
            return *this;
        }

        /*!
        * \brief
        * moves the cursor forward in the list of elements.
        *
        * \returns
        * the state of the iterator before modification.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        node_iterator operator ++( int ) {
            self_type tmp( *this );
            ++( *this );
            return tmp;
        }

        /*!
        * \brief
        * moves the cursor backwards in the list of elements.
        *
        * \returns
        * the state of the iterator before modification.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        node_iterator operator --( int ) {
            self_type tmp( *this );
            --( *this );
            return tmp;
        }

        /*!
        * \brief
        * access the object the iterator is currently pointing to.
        *
        * \returns
        * pointer to the current node.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        pointer operator ->() const {
            return &( **this );
        }

        /*!
        * \brief
        * access the object the iterator is currently pointing to.
        *
        * \returns
        * reference to the current node.
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        reference operator *() const {
            return const_cast<reference>( *m_current_node );
        }
    };
}

