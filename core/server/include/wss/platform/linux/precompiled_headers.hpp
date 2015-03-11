/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  \Author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#define HAS_PRECOMPILED_HEADER 1

#include <functional>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <iostream>
#include <ostream>
#include <fstream>
#include <climits>
#include <utility>
#include <cassert>
#include <sstream>
#include <locale>
#include <string>
#include <vector>
#include <limits>
#include <memory>
#include <cmath>
#include <stack>
#include <list>
#include <new>
#include <map>
#include <set>

// these defines have to be duplicated in the
// corresponding source files for compiles that are not using
// precompiled headers
#ifdef _DEBUG
//# define BOOST_SPIRIT_DEBUG
#endif
#define BOOST_SPIRIT_THREADSAFE
#define PHOENIX_LIMIT 8
#define BOOST_SPIRIT_CLOSURE_LIMIT 8
#define BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT 2

#include <boost/date_time/local_time/local_time.hpp>
#include <boost/spirit/include/classic_utility.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/spirit/include/phoenix1.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/spirit/include/classic.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/flyweight/no_tracking.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/thread/condition.hpp>
#include <boost/algorithm/minmax.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/type_traits.hpp>
#include <boost/make_shared.hpp>
#include <boost/call_traits.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time.hpp>
#include <boost/pool/pool.hpp>
#include <boost/flyweight.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>
#include <boost/integer.hpp>
#include <boost/signal.hpp>
#include <boost/thread.hpp>
#include <boost/assign.hpp>
#include <boost/atomic.hpp>
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include <boost/ref.hpp>
#include <boost/any.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/no_tracking.hpp>

#define BOOST_INTERLOCKED_INCREMENT( x )
#define BOOST_INTERLOCKED_DECREMENT( x )

#include <unicode/uchar.h>
#include <unicode/ustring.h>
#include <unicode/unistr.h>
