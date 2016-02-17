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
 *  \author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#include "wss/define.hpp"
#include "i_module_loader.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/shared_ptr.hpp>
#   include <string>
#endif

template<typename function_T>
class extension_function_caller;

/*!
 * \brief
 * Platform independent wrapper around calling a function provided by an external library.
 *
 * \param return_T
 * result type of the function to call. will be resolved automatically.
 *
 * \param param1_T
 * first parameter to the function to call. will be resolved automatically.
 *
 * \param param2_T
 * second parameter to the function to call. will be resolved automatically.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<typename return_T, typename param1_T, typename param2_T>
class extension_function_caller < return_T( param1_T, param2_T ) >
{
public:
    /*!
     * \brief
     * Constructor.
     *
     * \param loader
     * i_module_loader implementation for your specific platform.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    extension_function_caller( const boost::shared_ptr<i_module_loader>& loader )
        : m_loader( loader ) {}

    /*!
     * \brief
     * executes the call of the passed extension function.
     *
     * \param function_name
     * name of the extension function to be called.
     *
     * \param arg1
     * fist parameter to the extension function.
     *
     * \param arg2
     * second parameter to the extension function.
     *
     * \throws std::runtime_error
     * in the case where the function can not be resolved forwards an std::runtime_error
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    return_T operator()( const std::string& function_name, param1_T arg1, param2_T arg2 ) const {
        typedef return_T( *external_function_type )( param1_T, param2_T );
        external_function_type external_function = reinterpret_cast<external_function_type>( m_loader->function( function_name ) );
        return ( *external_function )( arg1, arg2 );
    }

private:
    boost::shared_ptr<i_module_loader> m_loader;
};

