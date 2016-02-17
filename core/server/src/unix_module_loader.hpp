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
 *  Dragan Simic <dragan.simic@jedox.com>
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#include "i_module_loader.hpp"

#ifdef LINUX
/*!
 * \brief
 * Implementation of i_module_loader for the Unix target platform.
 *
 * handles the loading of .SO extensions and function name resolution
 *
 * \author
 * Dragan Simic <dragan.simic@jedox.com>
 */
class unix_module_loader: public i_module_loader
{
public:
    unix_module_loader( const boost::filesystem::path& filename );
    virtual void* function( const std::string& function_name ) const;

private:
    void* m_extension_module;
};
#endif // LINUX

