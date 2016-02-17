/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  \Author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/thread/mutex.hpp>
#   include <boost/noncopyable.hpp>
#   include <boost/thread/locks.hpp>
#   include <exception>
#endif

/*!
 * \brief
 * this exception will be thrown when trying to access the shared
 * object while a lock could not be acquired.
 *
 * this will only happen if some try_lock or timed_lock is used.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class unable_to_acquire_lock_exception
    : std::runtime_error
{
public:
    unable_to_acquire_lock_exception()
        : std::runtime_error( "unable to acquire lock on object." ) {}
};

namespace trait
{
    namespace internal
    {
        /*!
         * \brief
         * implementation of a dummy lock compatible
         * with the locked object class.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct dummy_mutex {
            struct scoped_lock {
                scoped_lock( dummy_mutex& ) {}
                scoped_lock( const scoped_lock& ) {}
                inline  bool owns_lock() const {
                    return true;
                }
                inline dummy_mutex release() const {
                    return dummy_mutex();
                }
            };
            inline void lock() {}
            inline void unlock() {}
            inline bool try_lock() {
                return true;
            }
            inline dummy_mutex& operator* () {
                return *this;
            }
        };
    }

    /*!
     * \brief
     * dummy lock which does not actually do anything.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct dummy_lock_trait {
        typedef internal::dummy_mutex mutex_type;
        typedef internal::dummy_mutex::scoped_lock lock_type;
    };

    /*!
     * \brief
     * boost locking adapter.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template < class mutex_T = typename boost::mutex, class lock_T = typename mutex_T::scoped_lock >
    struct boost_lock_trait
    {
        typedef mutex_T mutex_type;
        typedef lock_T lock_type;
    };
}

/*!
 * \brief
 * class that provides only locked access to a shared resource.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template < class object_T, class mutex_trait_T = trait::dummy_lock_trait >
class locked_object
{
public:
    typedef object_T object_type;
    typedef typename mutex_trait_T::mutex_type mutex_type;
    typedef typename mutex_trait_T::lock_type lock_type;
    typedef locked_object<object_type, mutex_trait_T> locked_object_type;

    /*!
     * \brief
     * default constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_object()
        : m_mutex()
        , m_object() // value initialize object_T
    {}

    /*!
     * \brief
     * construct by copy constructing the contained type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_object( const object_type& object )
        : m_mutex()
        , m_object( object ) {}

    /*!
     * \brief
     * create by copy construction.
     *
     * be aware that this will actually "lock" the object
     * for the time of the copying.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_object( const locked_object& other )
        : m_mutex()
        , m_object( *other.lock() ) {}

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~locked_object() {
    }

    /*!
     * \brief
     * this class provides access to the contained object.
     *
     * while you have a instance of "access" on the stack
     * the object will be locked.
     *
     * you must never try to instantiate more than one
     * access object at any one time (deadlock!).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class access
        : boost::noncopyable
    {
        friend class locked_object<object_type, mutex_trait_T>;
    public:
        /*!
         * \brief
         * constructs an access object from the locked object.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        access( const locked_object_type& lo )
            : m_lock( lo.m_mutex )
            , m_object( lo.m_object ) {}

        /*!
         * \brief
         * return a reference to the object.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        object_type& get() {
            if ( ! owns_lock() ) {
                throw unable_to_acquire_lock_exception();
            }
            return m_object;
        }

        /*!
         * \brief
         * return a const reference to the object.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        const object_type& get() const {
            if ( ! owns_lock() ) {
                throw unable_to_acquire_lock_exception();
            }
            return m_object;
        }

        /*!
         * \brief
         * returns true when the mutex lock is locked.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool owns_lock() const {
            return m_lock.owns_lock();
        }

        /*!
         * \brief
         * return a reference to the object.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        operator object_type&() {
            return get();
        }

        /*!
         * \brief
         * return a const reference to the object.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        operator const object_type&() const {
            return get();
        }

        /*!
         * \brief
         * return a reference to the object.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        object_type& operator *() {
            return get();
        }

        /*!
         * \brief
         * return a const reference to the object.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        const object_type& operator *() const {
            return get();
        }

    protected:
        /*!
         * \brief
         * copy constructor.
         *
         * \remarks
         * the copy constructor is only accessible by the
         * locked_object class to allow the copy on a call
         * to "lock". RVO will be used there but we have
         * to have a definition present anyway to allow for
         * copies.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        access( const access& a )
            : m_lock( *a.m_lock.release() )
            , m_object( a.m_object ) {
        }

    private:
        mutable lock_type m_lock;
        object_type& m_object;
    };

    /*!
     * \brief
     * provides "one time" locked access to the object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline access lock() const {
        return access( static_cast<const locked_object_type&>( *this ) );
    }

    /*!
     * \brief
     * provides direct access to the mutex and object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct unguarded {
        unguarded( mutex_type& m, object_type& o ) : mutex( m ), object( o ) {}
        mutex_type& mutex;
        object_type& object;
    };

    /*!
     * \brief
     * provide direct access to the mutex and object.
     *
     * obviously use this one with great care!
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline unguarded unguard() {
        return unguarded( m_mutex, m_object );
    }

private:
    mutable mutex_type m_mutex;
    mutable object_type m_object;
};
