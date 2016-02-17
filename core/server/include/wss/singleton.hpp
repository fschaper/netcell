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

#include <wss/friend.hpp>
#include <wss/singleton_dependency.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/utility/enable_if.hpp>
# include <boost/noncopyable.hpp>
#endif


/* \brief
 * template class for singleton creation.
 *
 * <code>
 * class some_class : public singleton<some_class> {
 *     friend class singleton<some_class>;
 * private:
 *     some_class() {}
 * };
 * </code>
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template < class derived_T, class dependency_T = no_dependency >
class singleton
    : public boost::noncopyable
{
public:
    static derived_T& instance() {
        // in case the singleton has dependency requirements, these will be resolved
        // before the singleton is initialized for the first time.
        static dependency_T dependency;
        dependency.dummy();
        // all dependencies are instantiated (if any). we can safely
        // instantiate the singleton.
        static derived_T instance;
        return instance;
    }

protected:
    singleton() {}
    ~singleton() {}
};
