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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/define.hpp>
#include <wss/type.hpp>

namespace cf
{
    typedef boost::int_fast32_t internal_lookup_id_type;
    template < class id_typeT = long >
    class conditional_format_counterT : boost::noncopyable
    {
        typedef boost::mutex mutex_type;
        typedef mutex_type::scoped_lock lock_type;

    public:
        typedef id_typeT id_type;

        conditional_format_counterT() : m_counter( 1 ) {}

        ~conditional_format_counterT() {}

        inline id_type get_next() const {
            lock_type lock( m_mutex );
            return ++m_counter;
        }

    private:
        mutable mutex_type m_mutex;
        mutable volatile id_type m_counter;
    };

    typedef conditional_format_counterT<> counter_type;
    typedef conditional_format_counterT<internal_lookup_id_type> internal_counter_type;
}
