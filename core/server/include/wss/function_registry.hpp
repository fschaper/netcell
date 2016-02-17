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

#include <wss/define.hpp>
#include <wss/function_entry.hpp>
#include <wss/invalid_function_exception.hpp>
#include <wss/singleton.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <string>
# include <boost/scoped_ptr.hpp>
# include <boost/noncopyable.hpp>
#endif

/*!
 * \brief
 * server wide function catalog.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE function_registry
    : public singleton<function_registry>
{
    FRIEND_CLASS singleton<function_registry>;
public:
    /*!
     * \brief
     * register a function with the server.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void register_function( const ::function_entry& entry );

    /*!
     * \brief
     * retreive a function entry by it's internal name
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::function_entry& function_entry( const std::string& name ) const;

    /*!
     * \brief
     * returns true in case there is a function entry by the passed name
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool has_function_entry( const std::string& name ) const;

private:
    function_registry();
    ~function_registry();

private:
    struct function_registry_impl;
    boost::scoped_ptr<function_registry_impl> m_impl;
};

