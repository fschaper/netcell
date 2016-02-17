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
# include <boost/noncopyable.hpp>
#endif

/* \brief
 * template class for thread-safe singleton creation.
 *
 * the code should ensure, that the object will be instantiated
 * before the process enters the "main" method and any threads
 * could be spawned.
 *
 * <code>
 * class some_class : public threadsafe_singleton<some_class> {
 *     friend class threadsafe_singleton<some_class>;
 * private:
 *     some_class() {}
 * };
 * </code>
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 *
 * \reference
 * Cleary, Stephen. boost/pool/detail/singleton.hpp. 2000. 16 Mar 2009 <http://www.boost.org/doc/libs/1_36_0/boost/pool/detail/singleton.hpp>
 */
template<class base_T>
class threadsafe_singleton
    : public boost::noncopyable
{
    typedef threadsafe_singleton<base_T> singleton_type;
    typedef base_T object_type;
    struct instantiator {
        instantiator() {
            singleton_type::instance();
        }
        inline void noop() const {}
    };
    static instantiator m_instantiator;
public:
    static object_type& instance() {
        static object_type instance;
        m_instantiator.noop();
        return instance;
    }

protected:
    threadsafe_singleton() {}
    ~threadsafe_singleton() {}
};

template<class base_T>
typename threadsafe_singleton<base_T>::instantiator threadsafe_singleton<base_T>::m_instantiator;

