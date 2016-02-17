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
#include <wss/locking_iterator_wrapper.hpp>

#include <wss/invalid_name_exception.hpp>
#include <wss/object_not_found_exception.hpp>
#include <wss/object_unloading_exception.hpp>
#include <wss/session.hpp>
#include <wss/session_sheet_map.hpp>
#include <wss/locked_object.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/thread/recursive_mutex.hpp>
#ifdef _WIN32
# pragma warning( push )
# pragma warning( disable : 4267 )
# pragma warning( pop )
#endif
# include <boost/lexical_cast.hpp>
# include <boost/uuid/uuid_generators.hpp>
# include <boost/uuid/uuid_io.hpp>
# include <boost/noncopyable.hpp>
# include <boost/shared_ptr.hpp>
# include <boost/foreach.hpp>
# include <boost/bind.hpp>
# include <functional>
# include <string>
# include <list>
# include <map>
#endif

class i_identifiable_object;
class object_lookup;

namespace policy
{
    /*!
     * \brief
     * used when the deriving object will be
     * constructed without an parent object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template
    <
    class return_T
    , class object_T
    , class parent_T
    >
    struct no_parent
    {
        return_T operator()( parent_T& /*parent*/, const utf8_ci_string& parameter ) {
            return object_T::create( parameter );
        }
    };

    /*!
     * \brief
     * used when the deriving object will be
     * constructed with an parent object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template
    <
    class return_T
    , class object_T
    , class parent_T
    >
    struct has_parent
    {
        return_T operator()( parent_T& parent, const utf8_ci_string& parameter ) {
            return object_T::create( parent.shared_from_this(), parameter );
        }
    };
}

/*!
 * \brief
 * object storage.
 *
 * \todo
 * o this container will benefit from an additional container
 * that will be used solely for the name lookup of objects.
 * if wen want to map object names for direct lookup we need
 * to ensure that we will always have the most recent "name"
 * of the contained object. - fschaper
 *
 * o by the time we support moving objects from one of these
 * containers to another we need to support disconnecting
 * from the on_before_name_change event handler. - fschaper
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class base_T
, class contained_T
, template<class, class, class> class parent_creator_T = policy::has_parent
, class locked_object_trait_T = trait::dummy_lock_trait
>
class WSS_MODULE object_container
{
    FRIEND_CLASS object_lookup;
    typedef boost::shared_ptr<contained_T> value_type;
    typedef std::list<value_type> object_order_lookup_type;

    typedef boost::recursive_mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;
public:
    typedef base_T base_type;
    typedef contained_T object_type;
    typedef object_container<base_T, contained_T, parent_creator_T> container_type;

protected:
    enum container_mode { active, halted };

    /*!
     * \brief
     * set the container in halted state.
     *
     * prevents adding of new objects to the container.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void halt() {
        lock_type guard( m_mutex );
        m_state = halted;
    }

    /*!
     * \brief
     * allows objects to be added to the container.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void start() {
        lock_type guard( m_mutex );
        m_state = active;
    }

    /*!
     * \brief
     * clear all elements from the container.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void clear() {
        lock_type guard( m_mutex );
        m_object_order.clear();
    }

public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    object_container()
        : m_state( active ) {}

    /*!
     * \brief
     * locking iterator wrapper.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class iterator_pair
    {
    public:
        typedef locking_iterator_wrapper<typename object_order_lookup_type::iterator, mutex_keeper<mutex_type, lock_type> > iterator;
        typedef locking_iterator_wrapper<typename object_order_lookup_type::const_iterator, mutex_keeper<mutex_type, lock_type> > const_iterator;

        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        iterator_pair( typename object_order_lookup_type::iterator it_begin, typename object_order_lookup_type::iterator it_end, const typename mutex_keeper<mutex_type, lock_type>::shared_mutex_type& shared_mutex )
            : m_it_begin( it_begin )
            , m_it_end( it_end )
            , m_shared_mutex( shared_mutex ) {}

        /*!
         * \brief
         * begin iterator
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        iterator begin() {
            return iterator( m_it_begin, m_shared_mutex );
        }

        /*!
         * \brief
         * end iterator
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        iterator end() {
            return iterator( m_it_end, m_shared_mutex );
        }

        /*!
         * \brief
         * const begin iterator.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        const_iterator begin() const {
            return const_iterator( m_it_begin, m_shared_mutex );
        }

        /*!
         * \brief
         * const end iterator.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        const_iterator end() const {
            return const_iterator( m_it_end, m_shared_mutex );
        }

    private:
        typename object_order_lookup_type::iterator m_it_begin;
        typename object_order_lookup_type::iterator m_it_end;
        typename mutex_keeper<mutex_type, lock_type>::shared_mutex_type m_shared_mutex;
    };

    /*!
     * \brief
     * add a new element to the container.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    value_type add( const utf8_ci_string& name, const uuid_type& next_id = boost::uuids::nil_uuid(), const bool find_new_name = false ) {
        lock_type guard( m_mutex );
        if ( m_state == halted ) {
            throw object_unloading_exception();
        }

        const bool is_unique = find_new_name ? true : std::find_if( m_object_order.begin(), m_object_order.end(),
                               boost::bind( &object_type::name, _1 ) == name ) == m_object_order.end();
        if ( ! is_unique ) {
            throw invalid_name_exception();
        }

        value_type new_object( parent_creator_T<value_type, object_type, base_type>()( static_cast<base_type&>( *this ), find_new_name ? get_next_free_name( guard, name ) : name ) );

        if ( ! next_id.is_nil() ) {
            typename object_order_lookup_type::iterator it( std::find_if( m_object_order.begin(), m_object_order.end(),
                                                            boost::bind( &object_type::uuid, _1 ) == next_id ) );
            if ( m_object_order.end() != it ) {
                m_object_order.insert( it, new_object );
            } else {
                m_object_order.push_back( new_object );
            }
        } else {
            m_object_order.push_back( new_object );
        }

        new_object->on_before_name_change.connect( has_unique_name( *this ) );

        return new_object;
    }

    /*!
     * \brief
     * remove element from container by name.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void remove( const utf8_ci_string& name ) {
        lock_type guard( m_mutex );
        if ( m_state == halted ) {
            throw object_unloading_exception();
        }
        typename object_order_lookup_type::iterator it( std::find_if( m_object_order.begin(), m_object_order.end(),
                                                        boost::bind( &object_type::name, _1 ) == name ) );
        if ( m_object_order.end() != it ) {
            ( *it )->unload();
            m_object_order.erase( it );
        }
    }

    /*!
     * \brief
     * remove element from container by uuid.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void remove( const uuid_type& id ) {
        lock_type guard( m_mutex );
        if ( m_state == halted ) {
            throw object_unloading_exception();
        }
        typename object_order_lookup_type::iterator it( std::find_if( m_object_order.begin(), m_object_order.end(),
                                                        boost::bind( &object_type::uuid, _1 ) == id ) );
        if ( m_object_order.end() != it ) {
            ( *it )->unload();
            m_object_order.erase( it );
        }
    }

    /*!
     * \brief
     * get element from container by name.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    value_type get( session& s, const utf8_ci_string& name ) const {
        lock_type guard( m_mutex );
        if ( m_state == halted ) {
            throw object_unloading_exception();
        }
        typename object_order_lookup_type::const_iterator it = std::find_if( m_object_order.begin(), m_object_order.end(),
                boost::bind( &object_type::name, _1 ) == name );

        if ( m_object_order.end() == it ) {
            throw object_not_found_exception( convert_utf8_ci( name ) );
        }

        return *it;
    }

    /*!
     * \brief
     * get element from container by uuid.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    value_type get( session& s, const uuid_type& id ) const {
        lock_type guard( m_mutex );
        if ( m_state == halted ) {
            throw object_unloading_exception();
        }
        typename object_order_lookup_type::const_iterator it( std::find_if( m_object_order.begin(), m_object_order.end(),
                boost::bind( &object_type::uuid, _1 ) == id ) );

        if ( m_object_order.end() == it ) {
            throw object_not_found_exception( boost::lexical_cast<std::string>( id ) );
        }

        return *it;
    }

    void move( session& s, const uuid_type& id, const uuid_type& next_id ) {
        lock_type guard( m_mutex );
        if ( m_state == halted ) {
            throw object_unloading_exception();
        }
        typename object_order_lookup_type::iterator it( std::find_if( m_object_order.begin(), m_object_order.end(),
                                                        boost::bind( &object_type::uuid, _1 ) == id ) );

        if ( m_object_order.end() == it ) {
            throw object_not_found_exception( boost::lexical_cast<std::string>( id ) );
        }

        //move it to the position before next_id
        //if no next id is given, copy it to the end
        m_object_order.splice(
            next_id.is_nil() ? m_object_order.end()
            : (
                std::find_if( m_object_order.begin(), m_object_order.end(),
                              boost::bind( &object_type::uuid, _1 ) == next_id ) )
            , m_object_order, it );
    }

    /*!
     * \brief
     * return the number of elements the object contains.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    typename object_order_lookup_type::size_type count() const {
        return m_object_order.size();
    }

    /*!
     * \brief
     * retrieve locking iterators.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    iterator_pair locking_iterator() {
        typename iterator_pair::iterator::shared_mutex_type sm( boost::make_shared<typename iterator_pair::iterator::mutex_keeper_type>( boost::ref( m_mutex ) ) );
        return iterator_pair( m_object_order.begin(), m_object_order.end(), sm );
    }

private:
    const utf8_ci_string get_next_free_name( lock_type&, const utf8_ci_string& name ) {
        utf8_ci_string new_name = name;
        std::size_t count = 2;

        if ( name.size() > 2 && name.compare( name.size() - 1, 1, ")" ) == 0 ) {
            std::string::size_type position = name.find_last_of( "(" );
            if ( position != std::string::npos ) {
                ++position;
                if ( position != std::string::npos ) {
                    try {
                        count = boost::lexical_cast<size_t>( name.substr( position, 1 ) );
                        new_name = name.substr( 0, position - 2 );
                    } catch ( boost::bad_lexical_cast& ) {
                        try {
                            count = boost::lexical_cast<size_t>( name.substr( position, 2 ) );
                            new_name =  name.substr( 0, position - 3 );
                        } catch ( boost::bad_lexical_cast& ) {
                            new_name = name;
                        }
                    }
                }
            }
        }

        bool found_name_is_valid = false;
        typename object_order_lookup_type::const_iterator it = std::find_if( m_object_order.begin(), m_object_order.end(),
                boost::bind( &object_type::name, _1 ) == new_name );

        if ( m_object_order.end() == it ) {
            found_name_is_valid = true;
            count = 2;
        }


        while ( !found_name_is_valid ) { //create a new name, i.e. try to copy "Sheet1" to "Sheet1 (1)", "Sheet1 (2)" ...
            typename object_order_lookup_type::const_iterator it = std::find_if( m_object_order.begin(), m_object_order.end(),
                    boost::bind( &object_type::name, _1 ) == new_name + " (" + boost::lexical_cast< utf8_ci_string >( ( unsigned int ) count ) + ")"  );


            if ( m_object_order.end() == it ) {
                found_name_is_valid = true;

            } else {
                ++count;
            }
        }

        return new_name + " (" + boost::lexical_cast< utf8_ci_string >( count ) + ")";
    }

    /*!
     * \brief
     * determine if a name is already in use for this container.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct has_unique_name {
        has_unique_name( const object_container& obj )
            : m_obj( obj ) {}

        bool operator()( identifiable_object& i, const utf8_ci_string& name ) const {
            lock_type guard( m_obj.m_mutex );
            return std::find_if( m_obj.m_object_order.begin(), m_obj.m_object_order.end(),
                                 boost::bind( &object_type::name, _1 ) == name && boost::bind( &identifiable_object::operator !=, _1, boost::cref( i ) ) ) == m_obj.m_object_order.end();
        }

        const object_container& m_obj;
    };

private:
    //    typedef locked_object<object_order_lookup_type> locked_object_order_lookup_type;
    mutable mutex_type m_mutex;
    object_order_lookup_type m_object_order;
    container_mode m_state;
};
