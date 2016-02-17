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
# include <boost/shared_ptr.hpp>
# include <boost/scoped_ptr.hpp>
#endif

/*!
 * \brief
 * mutex keeper
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class mutex_T
, class lock_T
>
class mutex_keeper
{
public:
    typedef mutex_T mutex_type;
    typedef lock_T lock_type;

    typedef boost::shared_ptr<mutex_keeper<mutex_type, lock_type> > shared_mutex_type;


    mutex_keeper( mutex_type& m )
        : m_mutex( m )
        , m_lock( new lock_type( m_mutex ) ) {}
private:
    mutex_type& m_mutex;
    boost::scoped_ptr<lock_type> m_lock;
};

/*!
 * \brief
 * holds an lock to an mutex during iterations.
 *
 * (keeps the lock as long as the iterators are on the stack).
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class iterator_base_T
, class mutex_keeper_T
>
class locking_iterator_wrapper
{
public:
    typedef mutex_keeper_T mutex_keeper_type;
    typedef typename mutex_keeper_type::shared_mutex_type shared_mutex_type;
    typedef locking_iterator_wrapper<iterator_base_T, mutex_keeper_T> this_type;
    typedef iterator_base_T iterator_base_type;

    typedef std::forward_iterator_tag iterator_category;
    typedef typename iterator_base_type::value_type        value_type;
    typedef typename iterator_base_type::difference_type   difference_type;
    typedef typename iterator_base_type::pointer           pointer;
    typedef typename iterator_base_type::reference         reference;

    locking_iterator_wrapper( const iterator_base_type& i, const shared_mutex_type& m )
        : m_iterator( i )
        , m_shared_mutex( m ) {}

    bool operator ==( const this_type& other ) const {
        return m_iterator == other.m_iterator;
    }

    bool operator !=( const this_type& other ) const {
        return m_iterator != other.m_iterator;
    }

    pointer operator ->() const {
        return m_iterator.operator ->();
    }

    reference operator *() const {
        return m_iterator.operator * ();
    }

    this_type& operator ++() {
        ++m_iterator;
        return *this;
    }

private:
    iterator_base_type m_iterator;
    shared_mutex_type m_shared_mutex;
};

