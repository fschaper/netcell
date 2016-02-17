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
 *  Radu Ialovoi <ialovoi@yahoo.com>
 *  Radu Racariu <radu@yalos-solutions.com>
 */

#include <iostream>
#include <sstream>
#include <string>
#include "high_resolution_timer.hpp"

#define TIMED_COMMAND_EXEC( CMD ){\
        std::stringstream ss;\
        ss << "Command @" << BOOST_STRINGIZE(CMD) << " executed in: ~";\
        boost::high_resolution_timer t;\
        CMD.execute();\
        const double& el = t.elapsed();\
        ss << boost::lexical_cast<std::string>( el * 1000 ) << " miliseconds.";\
        BOOST_TEST_MESSAGE( ss.str() );\
        \
    }

#if defined(_DEBUG) && defined(_WSS_UNIT_TESTS)
#  if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#    include<string>
#    include<boost/lexical_cast.hpp>
#  endif
#  undef assert
#  undef my_assert
#  define assert(e) ((void) ((e) ? 0 : throw_on_assertion (#e, __FILE__, __LINE__)))
#  if !defined(_MY_ASSERT_ALREADY_DEFINED_ )
#  define _MY_ASSERT_ALREADY_DEFINED_
template<class err_T, class filename_T, class line_T>
inline void throw_on_assertion( const err_T e, const filename_T file, const line_T line )
{
    throw std::runtime_error( boost::lexical_cast<std::string>( file ) + ":" + boost::lexical_cast<std::string>( line ) + ": failed assertion " + std::string( e ) );
}
#  endif
#endif

#include <boost/test/unit_test.hpp>

#define TYPED_CHECK_EQUAL( type, obj, val ) \
    try{\
        BOOST_CHECK_NO_THROW( dynamic_cast<const type&>( (obj) ); );\
        dynamic_cast<const type&>( (obj) );\
        BOOST_CHECK_EQUAL( dynamic_cast<const type&>( (obj) ).value(), ( val ) );\
    } catch (std::bad_cast&) {};

#define TEST_GET_VALUE( obj, val ) TYPED_CHECK_EQUAL( get_value_command, obj, val );


#define TYPED_CHECK_CLOSE( type, obj, val, tolerance ) \
    try{\
        BOOST_CHECK_NO_THROW( dynamic_cast<const type&>( (obj) ); );\
        dynamic_cast<const type&>( (obj) );\
        BOOST_CHECK_CLOSE( dynamic_cast<const type&>( (obj) ).value().numeric(), ( val ) , ( tolerance ));\
    } catch (std::bad_cast&) {};

#define TEST_GET_CLOSE( obj, val, tolerance ) TYPED_CHECK_CLOSE( get_value_command, obj, val, tolerance );

