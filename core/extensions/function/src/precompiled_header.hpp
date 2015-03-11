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

#ifdef WIN32
#pragma once
#endif

#define FUNCTION_HAS_PRECOMPILED_HEADER 1

#include <iostream>
#include <vector>
#include <map>
#include <cctype>
#include <string>
#define _USE_MATH_DEFINES
#include <complex>
#include <climits>
#ifdef __unix__
#   include <float.h>
#endif
#define NOMINMAX    // prevent declaration of the min & max macros under windows.



#include <algorithm>   // for use of std::min & std::max.
#include <boost/bind.hpp>
#include <boost/regex.hpp>  // for SEARCH with wildcards
#include <boost/array.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
#include <boost/optional.hpp>
#include <boost/iterator.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/as_array.hpp>
#include <boost/algorithm/string.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4267; disable:4127; disable:4244; disable:4100)
#endif

#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/numeric/ublas/lu.hpp>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <boost/math/distributions/beta.hpp>
#include <boost/math/distributions/gamma.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/fisher_f.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/distributions/students_t.hpp>
#include <boost/math/distributions/chi_squared.hpp>


#include <ctime>

#include <wss/calculation_context.hpp>
#include <wss/variant.hpp>
#include <wss/i_dependency.hpp>
#include <wss/function_registry.hpp>
//#include <wss/function_parameters.hpp>
#include <wss/sparse_range.hpp>
#include <wss/a1conversion.hpp>
#include <wss/syntax.hpp>
#include <wss/range_reference.hpp>
#include <wss/variant_conversion_exception.hpp>

#include "utility.hpp"
#include "function_helper.hpp"

#include <cmath>

class function_registry;

#include <wss/function_parameters.hpp>

//common functions


long long combin( long long number, long long number_chosen );
double binomdist_density( long long number_s, long long trials, double probability_s );
double binomdist_cumulative( long long number_s, long long trials, double probability_s );
double poisson_density( long long x, double mean );

