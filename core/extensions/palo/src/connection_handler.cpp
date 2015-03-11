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
*  \author
*  Florian Schaper <florian.schaper@jedox.com>
*/

#include "connection_handler.hpp"


#if defined( WIN32 )
// #include <boost/thread/mutex.hpp> introduces the Windows.h and a whole
// bunch of defines that mess up our build.
#   undef ERROR
#   undef ERROR_NOT_FOUND
#endif
#include "spreadsheet_function.hpp"
#include "logging.hpp"

#ifdef _MSC_VER
# pragma warning ( disable : 4244 ) //warning C4244: '=' : conversion from 'unsigned long' to 'boost::uint8_t', possible loss of data
# pragma warning (push, 2)
#endif

#include <wss/server.hpp>

#ifdef _MSC_VER
# pragma warning ( pop )
#endif

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/exception.hpp>

#include <libconnectionpool/ConnectionException.h>
#include <libpalo_ng/Network/SocketException.h>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

//#include <boost/uuid/uuid.hpp>
//#include <boost/uuid/uuid_io.hpp>
//#include <boost/uuid/uuid_generators.hpp>

using namespace Palo::SpreadsheetFuncs;

namespace internal
{
    struct cached_palo_connection : public i_cached_connection {
        explicit cached_palo_connection( const shared_palo_server_type server ): m_server( server ) {}
    public:
        shared_palo_server_type m_server;
    };

    /*!
     * \brief
     * provides database field name to database offset resolution
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class name_to_field_mapping
    {
    public:
        name_to_field_mapping( const StringArray& mapping ) {
            int counter = 0;
            foreach( const std::string & s, mapping ) {
                m_mapping.insert( mapping_type::value_type( s, counter++ ) );
            }
        }

        int operator []( const std::string& key ) const {
            mapping_type::const_iterator it( m_mapping.find( key ) );
            if ( m_mapping.end() == it ) {
                return npos;
            }
            return it->second;
        }

        std::size_t size() const {
            return m_mapping.size();
        }

        static const int npos = -1;

    private:
        typedef map_to_use<std::string, int>::type mapping_type;
        mapping_type m_mapping;
    };

    /*!
     * \brief
     * convenience interface to provide easy conversion of CellValue types.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class cell_value_element_proxy
    {
    public:
        cell_value_element_proxy( const CellValue& e )
            : m_element( e ) {}

        /*!
         * \brief
         * convert the CellValue to string type.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        std::string as_string() const {
            switch ( m_element.type ) {
                case CellValue::NUMERIC:
                    return boost::lexical_cast<std::string>( m_element.val.d );
                    break;

                case CellValue::STRING:
                    return m_element.val.s;
                    break;

                case CellValue::ERR:
                default:
                    assert( !"CellValue is of unknown or error type!" );
            }
            return "";
        }

        /*!
         * \brief
         * convert the CellValue to numeric type.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        double as_numeric() const {
            switch ( m_element.type ) {
                case CellValue::NUMERIC:
                    return m_element.val.d;
                    break;

                case CellValue::STRING:
                    return boost::lexical_cast<double>( m_element.val.s );
                    break;

                case CellValue::ERR:
                default:
                    assert( !"CellValue is of unknown or error type!" );
            }
            return 0.0;
        }

        /*!
         * \brief
         * convert the CellValue to boolean
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool as_boolean() const {
            switch ( m_element.type ) {
                case CellValue::NUMERIC:
                    return m_element.val.d != 0.0;
                    break;

                case CellValue::STRING:
                    return boost::lexical_cast<double>( m_element.val.s ) != 0.0;
                    break;

                case CellValue::ERR:
                default:
                    assert( !"CellValue is of unknown or error type!" );
            }
            return false;
        }

        /*!
         * \brief
         * return the CellValues numeric value.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        double numeric() const {
            assert( "CellValue is not of numeric type" && m_element.type == CellValue::NUMERIC );
            return m_element.val.d;
        }

        /*!
         * \brief
         * return the CellValues string value.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        const std::string& string() const {
            assert( "CellValue is not of string type" && m_element.type == CellValue::STRING );
            return m_element.val.s;
        }

        /*!
         * \brief
         * interpret the CellValue as boolean.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool boolean() const {
            assert( "CellValue is not of numeric type" && m_element.type == CellValue::NUMERIC );
            return m_element.val.d != 0.0;
        }

    public:
        CellValue m_element;
    };

    /*!
     * \brief
     *
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class lookup_default
    {
    public:
        lookup_default( const char* field_name )
            : m_field_name( field_name ) {}

        lookup_default( const std::string& field_name )
            : m_field_name( field_name ) {}

        lookup_default( const std::string& field_name, const CellValue& default_value )
            : m_field_name( field_name )
            , m_default( default_value ) {}

        const std::string name() const {
            return m_field_name;
        }

        const CellValue& fallback() const {
            return m_default;
        }

    private:
        std::string m_field_name;
        CellValue m_default;
    };

    /*!
     * \brief
     * convenience interface to provide easy access to rows of data.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class cell_value_helper
    {
    public:
        cell_value_helper( const CellValueArray& cva, const name_to_field_mapping& nfm )
            : m_cell_value_array( cva )
            , m_name_to_field_mapping( nfm )
            , m_current_offset( 0 ) {}

        /*!
         * \brief
         * proceeds to the next row of information.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void next() {
            m_current_offset += m_name_to_field_mapping.size();
        }

        /*!
         * \brief
         * returns true if there is still another row of information.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool has_next() const {
            return m_current_offset < m_cell_value_array.size();
        }

        /*!
         * \brief
         * provides access to a CellValue based on the current row offset.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        cell_value_element_proxy operator[]( const lookup_default& lookup ) const {
            const int field_offset =  m_name_to_field_mapping[ lookup.name() ];
            if ( field_offset == name_to_field_mapping::npos ) {
                return cell_value_element_proxy( lookup.fallback() );
            }
            return cell_value_element_proxy( m_cell_value_array[ m_current_offset + field_offset ] );
        }

    private:
        const CellValueArray& m_cell_value_array;
        const name_to_field_mapping& m_name_to_field_mapping;
        std::size_t m_current_offset;
    };

    void invalidate_session( session& s )
    {
        connection_handler::instance().invalidate_session( s.uuid() );
    }
}

connection_handler::connection_handler()
{
    session_handler& sh = server::instance().session_handler();
    sh.on_logout.connect( &internal::invalidate_session );
}

connection_handler& connection_handler::instance()
{
    static connection_handler i;
    return i;
}

void connection_handler::connect( const std::string& hostname, unsigned short port, const std::string& username, const std::string& password )
{
    static spreadsheet_function& sf = spreadsheet_function::instance();
    m_master_connection = static_cast<SpreadsheetFuncsBase&>( sf ).FPaloWebInit( hostname, port, username, password );
}

void connection_handler::synchronize_settings()
{
    if ( ! m_master_connection ) {
        throw master_connection_failed_exception();
    }

    LOG_PALO_DEBUG( "synchronizing connection settings with master table." );

    static const std::string database_name( "Config" );
    static const std::string attribute_dimension_name( "#_connections_" );
    static const std::string dimension_name( "connections" );
    static const std::string cube_name( "#_connections" );

    StringArrayArray area;

    static spreadsheet_function& sf = spreadsheet_function::instance();
    // TODO (fschaper) get the list of database field names. it would be save to do this only once since we
    // don't have to except that the database will change on us during server runtime.
    static_cast<SpreadsheetFuncsBase&>( sf ).FPaloPing( m_master_connection );
    area.push_back( static_cast<SpreadsheetFuncsBase&>( sf ).FPaloDimensionListElementsSimple( m_master_connection, database_name, attribute_dimension_name ) );
    area.push_back( static_cast<SpreadsheetFuncsBase&>( sf ).FPaloDimensionListElementsSimple( m_master_connection, database_name, dimension_name ) );
    DimensionElementInfoSimpleArray dimension_element_result = static_cast<SpreadsheetFuncsBase&>( sf ).FPaloDimensionListElements( m_master_connection, database_name, dimension_name, false );

    element_id_mapping_type element_id_mapping;
    for ( DimensionElementInfoSimpleArray::const_iterator info_it = dimension_element_result.begin(), info_end = dimension_element_result.end();
            info_it != info_end; ++info_it ) {
        element_id_mapping[ info_it->name ] = info_it->identifier;
    }
    //TODO: somebody could delete connections too


    CellValueArray connection_table( static_cast<SpreadsheetFuncsBase&>( sf ).FPaloGetdataV( m_master_connection, database_name, cube_name, area ) );
    internal::name_to_field_mapping nfm( area[ 0 ] );
    internal::cell_value_helper cva( connection_table, nfm );

    // list of connection uuids that are enlisted in the master database.
    // will be used to sync the local table of connections to identify
    // any connection that is no longer registered in the master server
    // database.
    set_to_use<entry_uuid_type>::type seen_connections;
    {
        // from here on we have to lock our entry table.
        lock_type lock( m_mutex );

        for ( ; cva.has_next(); cva.next() ) {

            // we only handle palo connections
            if ( cva[ "type" ].string() == "palo" ) {
                // do we know it already?
                entry_uuid_type uuid = element_id_mapping[ cva["name"].string() ];

                seen_connections.insert( uuid );

                const bool is_a_known_connection = m_connections.find( uuid ) != m_connections.end();
                const bool is_marked_active = cva[ "active" ].as_boolean();
                const bool is_dynamic = cva[ internal::lookup_default( "useLoginCred", false ) ].as_boolean();

                // the underlaying connection converts connection handles to uppercase for lookup.
                const connection_handle_type connection_handle = boost::to_upper_copy( cva[ "name" ].string() );

                if ( is_a_known_connection ) {
                    // we already know about this connection.
                    connection_entry& entry = m_connections[ uuid ];
                    if ( is_marked_active ) {
                        // has the dynamic flag changed?
                        // the other parameters don't matter in this case since we
                        // reestablish the connection anew anyway.
                        const bool entry_is_dynamic = entry.dynamic;
                        if ( is_dynamic != entry_is_dynamic ) {
                            if ( is_dynamic ) {
                                entry.dynamic = dynamic_connection( cva[ "host" ].string()
                                                                    , static_cast<unsigned short>( cva[ "port" ].as_numeric() ) );
                                // the connection is now marked dynamic.
                                // remove the static connection.
                                ConnectionPool::remove( entry.connection_handle, false );
                            } else {
                                // the connection is no longer dynamic
                                // connect to the server statically.
                                remove_dynamic_connections( lock, entry );
                                add_connection( uuid, connection_handle, cva[ "host" ].string(), static_cast<unsigned short>( cva[ "port" ].as_numeric() ), cva[ "username" ].string(), cva[ "password" ].string() );
                            }
                        } else { // is_dynamic
                            // dynamic flag stayed the same.
                            // Have the connection parameters changed?
                            if ( is_dynamic ) {
                                const dynamic_connection& dynamic_c = *entry.dynamic;
                                const bool connection_parameters_have_changed =
                                    dynamic_c.hostname != cva[ "host" ].string()
                                    || dynamic_c.port != static_cast<unsigned short>( cva[ "port" ].as_numeric() );
                                if ( connection_parameters_have_changed ) {
                                    // remove from dynamic map
                                    remove_dynamic_connections( lock, entry );
                                    entry.dynamic = dynamic_connection( cva[ "host" ].string()
                                                                        , static_cast<unsigned short>( cva[ "port" ].as_numeric() ) );
                                }
                            } else {
                                assert( "the connection pool has lost our entry?" && ConnectionPool::connMap.find( entry.connection_handle ) != ConnectionPool::connMap.end() );
                                const ConnectionData& pool_data = ConnectionPool::connMap[ entry.connection_handle ];
                                const bool connection_parameters_have_changed =
                                    pool_data.hostname != cva[ "host" ].string()
                                    || pool_data.port != static_cast<unsigned short>( cva[ "port" ].as_numeric() )
                                    || pool_data.username != cva[ "username" ].string()
                                    || pool_data.password != cva[ "password" ].string()
                                    || entry.connection_handle != connection_handle;
                                if ( connection_parameters_have_changed ) {
                                    // remove the old connection and re-establish it with the new settings.
                                    ConnectionPool::remove( entry.connection_handle, false );
                                    add_connection( uuid, connection_handle, cva[ "host" ].string(), static_cast<unsigned short>( cva[ "port" ].as_numeric() ), cva[ "username" ].string(), cva[ "password" ].string() );
                                } // if connection_parameters_have_changed
                            }

                            // the connection handle is safe to set.
                            entry.connection_handle = connection_handle;
                        } // if/else is_marked_active

                    } else { // is_marked_active
                        // no longer marked as being active.
                        if ( entry.dynamic ) {
                            // remove from dynamic table.
                            remove_dynamic_connections( lock, entry );
                        } else {
                            // remove from static table.
                            ConnectionPool::remove( entry.connection_handle, false );
                        }
                        // we no longer need to maintain the record.
                        // we now also do not need to maintain the information in the map until it's
                        // marked as active.
                        m_connections.erase( uuid );
                    }
                } else if ( is_marked_active ) {
                    // a new connection has to be established.
                    connection_entry& entry = m_connections[ uuid ];
                    entry.connection_handle = connection_handle;
                    entry.is_active = is_marked_active;
                    if ( ! is_dynamic ) {
                        add_connection( uuid, connection_handle, cva[ "host" ].string(), static_cast<unsigned short>( cva[ "port" ].as_numeric() ), cva[ "username" ].string(), cva[ "password" ].string() );
                    } else {
                        // add to the dynamic table.
                        entry.dynamic = dynamic_connection( cva[ "host" ].string()
                                                            , static_cast<unsigned short>( cva[ "port" ].as_numeric() ) );
                    }

                } // if/else is_a_known_connection

            } // if palo connection

        } // for

        // remove all connections that are no longer listed in the master table.
        for ( connection_map_type::iterator it( m_connections.begin() )
                ; it != m_connections.end(); ) {
            if ( seen_connections.find( it->first ) == seen_connections.end() )  {
                if ( ! it->second.dynamic ) {
                    // remove from static table.
                    ConnectionPool::remove( it->second.connection_handle, false );
                } else {
                    remove_dynamic_connections( lock, it->second );
                }
                m_connections.erase( it++ );
            } else {
                ++it;
            }
        }

        // update the lookup table
        m_entry_lookup.clear();
        for ( connection_map_type::iterator v_it = m_connections.begin(), v_end = m_connections.end(); v_it != v_end; ++v_it ) {
            m_entry_lookup.insert( handle_lookup_type::value_type( v_it->second.connection_handle, &( v_it->second ) ) );
        }
    }
}

shared_palo_server_type connection_handler::internal_get( session& s, const std::string& key )
{
    {
        //first we check our cache attached to the session
        const connection_cache::palo_connection_cache_type& cached_connections = s.internal_access_connections();
        connection_cache::const_iterator it( cached_connections.find( key ) );
        if ( it != cached_connections.end() ) {
            return boost::static_pointer_cast<internal::cached_palo_connection>( it->second )->m_server;
        }
    }

    // the ConnectionPool is not synchronized so we have to
    // use our mutex as a global lock for that object too.
    lock_type lock( m_mutex );
    const connection_handle_type search_key = boost::to_upper_copy( key );
    shared_palo_server_type return_value;
    try {
        // try to get a static connection directly from the pool
        return_value = ConnectionPool::get( key );
    } catch ( const ConnectionException& ) {
        // ok, this might be a dynamic connection. try to look it up.
        handle_lookup_type::iterator it( m_entry_lookup.find( search_key ) );
        if ( it != m_entry_lookup.end() ) {
            connection_entry& entry = *it->second;
            if ( entry.dynamic ) {
                dynamic_connection& dynamic = *entry.dynamic;
                // does the current session already have a server connection
                // for the requested handle?
                dynamic_connection::session_to_handle_mapping_type::iterator it( dynamic.session_handle_map.find( s.uuid() ) );
                if ( it != dynamic.session_handle_map.end() ) {
                    // return existing connection
                    return_value = ConnectionPool::get( it->second );
                } else {
                    // create a new connection based on the users authentication
                    // settings.
                    boost::uuids::random_generator gen;
                    const connection_handle_type connection_handle =  boost::lexical_cast<connection_handle_type>( gen() );
                    // try to create the connection at this point. if we get a exception here we will
                    // not have an invalid entry in our connection map.
                    ConnectionPool::add( connection_handle, ConnectionData( dynamic.hostname, dynamic.port, s.username(), s.password() ) );
                    return_value = ConnectionPool::get( connection_handle );
                    dynamic.session_handle_map[ s.uuid() ] = connection_handle;
                }
            }
        }
    }
    //cache the return value before giving it back
    s.cache_connection( key, shared_cached_connection_type( new internal::cached_palo_connection( return_value ) ) );
    return return_value;
}

shared_palo_server_type connection_handler::get( session& s, const std::string& key )
{
    if ( !s.palo_connection_unreachable( key ) ) {
        if ( shared_palo_server_type return_value = internal_get( s, key ) ) {
            if ( s.palo_connection_pinged( key ) ) {
                return return_value;
            } else {
                try {
                    // if we have identified a connection to be used
                    // try to "ping" the server to see if the server can be accessed.
                    static_cast<SpreadsheetFuncsBase&>( spreadsheet_function::instance() ).FPaloPing( return_value );
                    s.set_palo_connection_pinged( key );
                    return return_value;
                } catch ( const jedox::palo::SocketExceptionConnectionTimedOut& e ) {
                    s.set_palo_connection_unreachable( key );
                    throw e;
                    // in case a connection has timed out the connection will be erased
                    // and only be re-established after a repeated call to synchronize_settings
                    /*foreach( connection_map_type::value_type & v, m_connections ) {
                        connection_entry& entry = v.second;
                        if ( entry.connection_handle == key ) {
                            remove( s, entry.connection_handle );
                            m_connections.erase( v.first );
                            m_entry_lookup.erase(  boost::to_upper_copy( key ) );
                            break;
                        }
                    }*/
                }
            }
        }
    }
    throw ConnectionException( CurrentSourceLocation, "Unknown connection: \"" + key + "\"" );
}

void connection_handler::add( const std::string& key, const ConnectionData& cd )
{
    // connections can only be added via palo studio
    LOG_PALO_WARNING( "request denied to manually add a palo connection '" << key << "'." );
    throw std::runtime_error( "not implemented!" );
}

shared_palo_server_type connection_handler::get( const std::string& key, bool adjustFailedMap /* = true */ )
{
    assert( !"this method is not to be called!" );
    throw std::runtime_error( "not implemented!" );
}

void connection_handler::remove( const std::string& key, const bool do_logout /* = false */ )
{
    // connections can not be removed manually but only via the studio
    LOG_PALO_WARNING( "request denied to manually remove palo connection '" << key << "'." );
    throw std::runtime_error( "not implemented!" );
}

void connection_handler::remove( session& s, const std::string& key )
{
    try {
        shared_palo_server_type server = get( s, key );
        if ( server ) {
            server->logout();
        }
    } catch ( ... ) { //in case there are any exception thrown while logging out we don't care
    }
    //only remove the connection, logout is already done
    s.remove_connection( key );
    ConnectionPool::remove( key, false );

}

void connection_handler::remove_dynamic_connections( lock_type& lock, connection_entry& entry )
{
    // remove from dynamic table.
    const dynamic_connection::session_to_handle_mapping_type& map = ( *entry.dynamic ).session_handle_map;
    for ( dynamic_connection::session_to_handle_mapping_type::const_iterator it = map.begin(), end = map.end()
            ; it != end
            ; ++it ) {
        ConnectionPool::remove( it->second, false );
    }
    entry.dynamic.reset();
}

void connection_handler::add_connection( const entry_uuid_type& entry_uuid, const connection_handle_type& handle, const std::string& hostname, unsigned short port, const std::string& username, const std::string& password )
{
    try {
        ConnectionPool::add( handle, ConnectionData( hostname, port, username, password ) );
    } catch ( const ConnectionException& e ) {
        // the connection failed to register, remove it from the map
        // and rethrow the exception.
        m_connections.erase( entry_uuid );
        throw e;
    }
}

void connection_handler::invalidate_session( const session_id_type& s )
{
    lock_type lock( m_mutex );
    foreach( connection_map_type::value_type & v, m_connections ) {
        connection_entry& entry = v.second;
        if ( entry.dynamic ) {
            // the entry has dynamic connections.
            dynamic_connection::session_to_handle_mapping_type& map = ( *entry.dynamic ).session_handle_map;
            dynamic_connection::session_to_handle_mapping_type::iterator it( map.find( s ) );
            // try to find our session in the mapping.
            if ( it != map.end() ) {
                // remove the mapped connection
                ConnectionPool::remove( it->second );
                // erase the dynamic mapping for this session
                map.erase( it );
            }
        }
    }
}

