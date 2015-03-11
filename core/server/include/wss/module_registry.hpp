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

#include <wss/singleton.hpp>
#include <wss/define.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/filesystem/path.hpp>
#   include <string>
#   include <list>
#endif

/*!
 * \brief
 * module loader
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE module_registry
    : public singleton<module_registry>
{
    FRIEND_CLASS singleton<module_registry>;
public:
    typedef std::list<std::string> module_list_type;

    /*!
     * \brief
     * register a extension
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void register_extension( const boost::filesystem::path& module, const std::string& configuation = "" );

    /*!
     * \brief
     * retreive a list of registered modules.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const module_list_type& modules() const;

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    module_registry();

private:
    module_list_type m_module_list;
};

