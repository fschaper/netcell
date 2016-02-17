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

#include <cstddef>

namespace policy
{
    /*!
     * \brief
     * thread safe counter. where available
     * use atomic increment/decrement facilities.
     *
     * \remark
     * notice that the ++ and -- operators don't
     * return *this. that is by design.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class threadsafe_counter
    {
        typedef boost::mutex mutex_type;
        typedef boost::mutex::scoped_lock lock_type;
    public:
        threadsafe_counter( std::size_t )
            : m_count( 1 ) {}

        std::size_t operator ++() {
            lock_type lock( m_mutex );
            return ++m_count;
        }

        std::size_t operator --() {
            lock_type lock( m_mutex );
            return --m_count;
        }

        operator std::size_t() const {
            lock_type lock( m_mutex );
            return m_count;
        }

    private:
        boost::mutex m_mutex;
        std::size_t m_count;
    };
}

/*!
 * \brief
 * shared pointer which calls back to an passed
 * action object with it's current use count whenever
 * a copy gets destroyed.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template < class action_T, class counter_T = policy::threadsafe_counter >
class shared_action_pointer
{
public:
    typedef action_T action_type;
    typedef shared_action_pointer self_type;
    typedef counter_T counter_type;

private:
    static const unsigned int null = 0;

    /*!
     * \brief
     * keeps the refcount and the action object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct keeper {
        keeper( const action_type& action )
            : count( 1 )
            , action( action ) {}

        counter_type count;
        action_type action;
    };

public:
    /*!
     * \brief
     * constructor.
     *
     * initialize the shared_action_pointer with it's action object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_action_pointer( const action_type& action )
        : m_keeper( new keeper( action ) ) {}

    /*!
     * \brief
     * copy constructor.
     *
     * the shared_pointer will raise the reference count of the original.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_action_pointer( const self_type& other )
        : m_keeper( &( ++( *other.m_keeper->count ) ) ) {}

    /*!
     * \brief
     * destructor.
     *
     * will lower the reference count and call into it's
     * action object with the new reference count.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~shared_action_pointer() {
        --( *m_keeper->count );
        // the action object may not throw!
        m_keeper->action( *m_keeper->count );
        if ( ! *m_keeper->count ) {
            delete m_keeper;
            m_keeper = null;
        }
    }

    /*!
     * \brief
     * assignment operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_action_pointer& operator =( const self_type& rhs ) {
        shared_action_pointer tmp( rhs );
        swap( tmp );
        return *this;
    }

    /*!
     * \brief
     * swap the guts of one object with the other.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void swap( self_type& other ) throw() {
        std::swap( m_keeper, other.m_keeper );
    }

    /*!
     * \brief
     * current use count of the object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    std::size_type use_count() const {
        return m_keeper->count;
    }

    /*!
     * \brief
     * returns the associated action object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    action_type& get() {
        return m_keeper->action;
    }

    /*!
     * \brief
     * returns the associated action object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const action_type& get() const {
        return m_keeper->action;
    }

    /*!
     * \brief
     * returns the associated action object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const action_type& operator *() const {
        return m_keeper->action;
    }

    /*!
     * \brief
     * returns the associated action object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    action_type& operator *() {
        return m_keeper->action;
    }

    /*!
     * \brief
     * test for equality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator ==( const self_type& other ) const {
        return m_keeper == other.m_keeper;
    }

    /*!
     * \brief
     * test for inequality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator !=( const self_type& other ) const {
        return m_keeper != other.m_keeper;
    }

    /*!
     * \brief
     * test for less than.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator <( const self_type& other ) const {
        return m_keeper < other.m_keeper;
    }

    /*!
     * \brief
     * test for larger than.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator >( const self_type& other ) const {
        return m_keeper > other.m_keeper;
    }

private:
    mutable keeper* m_keeper;
};

