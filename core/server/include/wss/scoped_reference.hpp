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

namespace policy
{
    template<class shared_T>
    struct allow_uninitialized {
        static inline void check_reference( const shared_T& ) {}
    };
}

/*!
 * \brief
 * access a reference to an object held by a boost::shared_ptr.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template < class shared_T, template <class> class policy_T = policy::allow_uninitialized >
class scoped_reference
    : boost::noncopyable
{
public:
    typedef typename shared_T::element_type element_type;
    typedef shared_T shared_type;
    typedef element_type& reference_type;
    typedef element_type* pointer_type;
    typedef policy_T<shared_type> policy_type;

    scoped_reference( const shared_type& element )
        : m_element( element )
        , m_reference( *element ) {
        policy_type::check_reference( element );
    }

    inline operator reference_type() {
        return m_reference;
    }

    inline pointer_type operator ->() {
        return &m_reference;
    }

    inline reference_type operator *() {
        return m_reference;
    }

private:
    shared_type m_element;
    reference_type m_reference;
};

