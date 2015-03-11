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
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/bind.hpp>

#include <wss/sparse_vector.hpp>
#include <wss/variant.hpp>
#include <wss/define.hpp>

#include <algorithm>
#include <functional>

BOOST_AUTO_TEST_SUITE( sparse_vector_test )

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sparse_vector_out_of_range_test )
{
    sparse_vector<variant> v( 5 );
    BOOST_CHECK_THROW( v[5], std::out_of_range );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sparse_vector_value_test )
{
    sparse_vector<variant> v( 5 );
    BOOST_CHECK_EQUAL( v[0], variant() );
    BOOST_CHECK_EQUAL( v[1], variant() );
    BOOST_CHECK_EQUAL( v[2], variant() );
    BOOST_CHECK_EQUAL( v[3], variant() );
    BOOST_CHECK_EQUAL( v[4], variant() );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sparse_vector_default_value_test )
{
    sparse_vector<variant> v( 5, variant( true ) );
    BOOST_CHECK_EQUAL( v[0], variant( true ) );
    BOOST_CHECK_EQUAL( v[4], variant( true ) );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sparse_vector_push_back_test )
{
    sparse_vector<variant> v( variant( 2.0 ) );
    v.push_back( variant( 1.0 ) );
    v.push_back( variant( 2.0 ) );
    v.push_back( variant( 3.0 ) );

    BOOST_CHECK_EQUAL( v[0], variant( 1.0 ) );
    BOOST_CHECK_EQUAL( v[1], variant( 2.0 ) );
    BOOST_CHECK_EQUAL( v[2], variant( 3.0 ) );
    BOOST_CHECK_EQUAL( v.direct().size(), 2 );
    BOOST_CHECK_EQUAL( v.size(), 3 );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sparse_vector_iteration_test )
{
    sparse_vector<variant> v1( variant( 2.0 ) );
    v1.push_back( variant( 1.0 ) );
    v1.push_back( variant( 2.0 ) );
    v1.push_back( variant( 3.0 ) );

    using namespace boost::assign;
    std::vector<variant> v2;
    v2 += 1.0, 2.0, 3.0;

    BOOST_CHECK_EQUAL_COLLECTIONS( v1.begin(), v1.end(), v2.begin(), v2.end() );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sparse_vector_empty_iteration_test )
{
    sparse_vector<variant> v;
    BOOST_CHECK_EQUAL( v.begin() == v.end(), true );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sparse_vector_empty_test )
{
    sparse_vector<variant> v;
    BOOST_CHECK_EQUAL( v.empty(), true );
    v.push_back( variant() );
    BOOST_CHECK_EQUAL( v.empty(), false );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sparse_vector_stl_test )
{
    using namespace boost::assign;

    sparse_vector<variant> v;
    v += 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0;

    namespace ba = boost::accumulators;
    variant result( ba::extract::sum( std::for_each( v.begin(), v.end(), ba::accumulator_set<variant, ba::features<ba::tag::sum> >() ) ) );

    BOOST_CHECK_EQUAL( variant( 55.0 ), result );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sparse_vector_with_defaults_stl_test )
{
    using namespace boost::assign;

    sparse_vector<variant> v( variant( 5.0 ) );
    v += 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0;

    typedef variant::sparse_array_type::mapping_type::value_type mapping_value_type;

    namespace ba = boost::accumulators;
    variant result( variant::type_double );
    result += v.default_value().numeric() * ( v.size() - v.direct().size() );
    result += ba::extract::sum( std::for_each( boost::make_transform_iterator( v.direct().begin(), boost::bind( &mapping_value_type::second, _1 ) ), boost::make_transform_iterator( v.direct().end(), boost::bind( &mapping_value_type::second, _1 ) ), ba::accumulator_set<variant, ba::features<ba::tag::sum> >() ) );

    BOOST_CHECK_EQUAL( variant( 55.0 ), result );
}

BOOST_AUTO_TEST_SUITE_END()

