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

#include <boost/test/unit_test.hpp>
#include <wss/node.hpp>

BOOST_AUTO_TEST_SUITE( node_test )

/*!
 * \brief
 * mockup object to test the node class.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class mokup_node
    : public tree::node<mokup_node>
{
public:
    mokup_node( unsigned int weight ) : m_weight( weight ) {}
    auto_type clone() const {
        return auto_type( new mokup_node( *this ) );
    }
    unsigned int weight() const {
        return m_weight;
    }
    bool operator <( const mokup_node& rhs ) const {
        return weight() < rhs.weight();
    }
private:
    unsigned int m_weight;
};

/*!
 * \brief
 * test the proper construction of a node
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( constructor_test )
{
    mokup_node::auto_type c( new mokup_node( 1 ) );

    // a newly created node must have the size of 0 because it can't
    // have any child nodes
    BOOST_CHECK_EQUAL( c->size(), 0 );

    // the shallow_begin iterator must point to the shallow_end iterator
    BOOST_ASSERT( c->begin_shallow() == c->end_shallow() );

    // the deep_begin iterator must point to the deep_end iterator
    BOOST_ASSERT( c->begin_deep() == c->end_deep() );

    // begin_deep -1 must point to the node itself. I would have preferred
    // that begin_deep would point to the initial node but found no nice way
    // to accomplish this without further overhead.
    BOOST_ASSERT( ( --c->begin_deep() ).operator ->() == c.get() );

    // a single node has no parent object
    BOOST_CHECK_EQUAL( c->has_parent(), false );
    BOOST_ASSERT( c->parent() == NULL );

    // a single node has no child objects
    BOOST_CHECK_EQUAL( c->has_children(), false );

    // a single node can not be detached
    BOOST_ASSERT( c->release().get() == NULL );
    BOOST_ASSERT( c.get() != NULL );
}

/*!
 * \brief
 * test the attachment of one node to another.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( attach_test )
{
    mokup_node::auto_type c( new mokup_node( 1 ) );
    mokup_node::auto_type d( new mokup_node( 2 ) );
    const mokup_node* d_ptr = d.get();

    c->attach( d );
    // since d is attached to c, c must have child elements
    BOOST_CHECK_EQUAL( c->has_children(), true );
    // the shallow iterator must point to d
    BOOST_ASSERT( c->begin_shallow().operator ->() == d_ptr );
    // since d is attached to c, c must be the parent element for d
    BOOST_CHECK_EQUAL( d_ptr->has_parent(), true );
}

/*!
 * \brief
 * test shallow iteration
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( iterate_shallow_test )
{
    mokup_node::auto_type c( new mokup_node( 1 ) );
    mokup_node::auto_type d( new mokup_node( 2 ) );
    mokup_node::auto_type e( new mokup_node( 3 ) );
    mokup_node::auto_type f( new mokup_node( 4 ) );

    const mokup_node* c_ptr = c.get();
    const mokup_node* d_ptr = d.get();
    const mokup_node* e_ptr = e.get();
    const mokup_node* f_ptr = f.get();

    c->attach( d );
    c->attach( e );
    c->attach( f );

    mokup_node::shallow_iterator current( c->begin_shallow() );

    BOOST_ASSERT( ( current ) != c->end_shallow() );
    BOOST_ASSERT( ( current ).operator->() == d_ptr );
    BOOST_ASSERT( ( current ) != c->end_shallow() );
    BOOST_ASSERT( ( ++current ).operator->() == e_ptr );
    BOOST_ASSERT( ( current ) != c->end_shallow() );
    BOOST_ASSERT( ( ++current ).operator->() == f_ptr );
    BOOST_ASSERT( ( ++current ) == c->end_shallow() );
}


/*!
 * \brief
 * test that an attached node has the proper parent.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( parent_test )
{
    mokup_node::auto_type c( new mokup_node( 1 ) );
    mokup_node::auto_type d( new mokup_node( 2 ) );
    const mokup_node* d_ptr = d.get();

    c->attach( d );
    BOOST_CHECK_EQUAL( d_ptr->parent(), c.get() );
}

/*!
 * \brief
 * test the release of nodes from the tree.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( release_test )
{
    mokup_node::auto_type c( new mokup_node( 1 ) );
    mokup_node::auto_type d( new mokup_node( 2 ) );
    const mokup_node* d_ptr = d.get();

    c->attach( d );
    mokup_node::auto_type newd = c->begin_shallow()->release();

    // the node released must be the one we attached
    BOOST_CHECK_EQUAL( d_ptr, newd.get() );
    BOOST_ASSERT( newd->parent() == NULL );

    // c no longer has any child elements
    BOOST_CHECK_EQUAL( c->has_children(), false );

    // d no longer has an parent
    BOOST_CHECK_EQUAL( d_ptr->has_parent(), false );
}

/*!
 * \brief
 * test deep iteration
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( iterate_deep_test )
{
    mokup_node::auto_type c( new mokup_node( 1 ) );
    mokup_node::auto_type d( new mokup_node( 2 ) );
    mokup_node::auto_type e( new mokup_node( 3 ) );
    mokup_node::auto_type f( new mokup_node( 4 ) );

    const mokup_node* c_ptr = c.get();
    const mokup_node* d_ptr = d.get();
    const mokup_node* e_ptr = e.get();
    const mokup_node* f_ptr = f.get();

    c->attach( d );
    e->attach( f );
    c->attach( e );

    mokup_node::deep_iterator current( c->begin_deep() );

    BOOST_ASSERT( ( --current ).operator->() == c_ptr );
    BOOST_ASSERT( ( current ) != c->end_deep() );
    BOOST_ASSERT( ( ++current ).operator->() == d_ptr );
    BOOST_ASSERT( ( current ) != c->end_deep() );
    BOOST_ASSERT( ( ++current ).operator->() == e_ptr );
    BOOST_ASSERT( ( current ) != c->end_deep() );
    BOOST_ASSERT( ( ++current ).operator->() == f_ptr );
    BOOST_ASSERT( ( ++current ) == c->end_deep() );
}

/*!
 * \brief
 * test "unlinking" of nodes from the tree.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( unlink_test )
{
    mokup_node::auto_type c( new mokup_node( 1 ) );
    mokup_node::auto_type d( new mokup_node( 2 ) );
    mokup_node::auto_type e( new mokup_node( 3 ) );
    mokup_node::auto_type f( new mokup_node( 4 ) );

    const mokup_node* c_ptr = c.get();
    mokup_node* d_ptr = d.get();
    const mokup_node* e_ptr = e.get();
    const mokup_node* f_ptr = f.get();

    c->attach( d );
    e->attach( f );
    c->attach( e );

    mokup_node::auto_type unlinked = d_ptr->unlink();
    BOOST_ASSERT( unlinked.get() == d_ptr );
    BOOST_ASSERT( unlinked->has_parent() == false );
    BOOST_ASSERT( unlinked->has_children() == false );

    mokup_node::deep_iterator current( c->begin_deep() );

    BOOST_ASSERT( ( --current ).operator->() == c_ptr );
    BOOST_ASSERT( ( current ) != c->end_deep() );
    BOOST_ASSERT( ( ++current ).operator->() == e_ptr );
    BOOST_ASSERT( ( current ) != c->end_deep() );
    BOOST_ASSERT( ( ++current ).operator->() == f_ptr );
}

BOOST_AUTO_TEST_SUITE_END()
