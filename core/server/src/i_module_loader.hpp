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

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/filesystem/path.hpp>
#   include <string>
#endif

/*!
 * \brief
 * Interface for Implementation which handles the loading
 * and function resolving on a specific platform.
 *
 * Inherit from i_module_loader and implement specific module
 * loading procedures for your target platform
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class i_module_loader
{
public:
    virtual ~i_module_loader() {}

    /*!
     * \brief
     * returns a pointer to the extension function identified by 'name'.
     *
     * \param function_name
     * name of the function whose function pointer should be returned.
     *
     * \throws std::runtime_error
     * in the case where the function can not be resolved throws an std::runtime_error
     *
     * \returns
     * pointer to the function in the extension
     *
     * \remarks
     * if no function by that name could be resolved the method returns an
     * NULL pointer.
     */
    virtual void* function( const std::string& function_name ) const = 0;
};
