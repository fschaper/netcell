/*!
 * Logging framework
 *
 * Copyright (c) 2007 by Florian Schaper <florian.schaper@jedox.com>
 * Jedox GmbH, Freiburg, Germany
 */

#include "precompiled_header.hpp"

#include <boost/bind.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <algorithm>
#include <cassert>

#include "core_logging.hpp"

namespace logging
{
    logger::~logger()
    {}

    void logger::level( log_level::level level )
    {
        m_current_loglevel = level;
        for ( handler_map_type::const_iterator it = m_handler_map.begin(), end = m_handler_map.end() ; it != end; ++it ) {
            it->second->level( level );
        }
    }

    log_level::level logger::level() const
    {
        return m_current_loglevel;
    }

    i_log_handler* logger::handler( i_log_handler::logger_name_type name )
    {
        handler_map_type::iterator it = m_handler_map.find( name );
        return it == m_handler_map.end() ? NULL : it->second.get();
    }

    void logger::register_handler( const shared_log_handler_type& handler )
    {
        assert( handler != NULL );
        m_handler_map[ handler->name() ] = handler;
    }

    void logger::unregister_handler( const shared_log_handler_type& handler )
    {
        assert( handler != NULL );
        m_handler_map.erase( handler->name() );
    }

    void logger::log( log_level::level level, const char* message )
    {
        for ( handler_map_type::const_iterator it = m_handler_map.begin(), end = m_handler_map.end() ; it != end; ++it ) {
            it->second->log( level, message );
        }
    }

    void logger::to_log( log_level::level level, const char* message )
    {
        instance().log( level, message );
    }

    void logger::to_log( log_level::level level, const std::string& message )
    {
        to_log( level, message.c_str() );
    }

    logger& logger::instance()
    {
        static logger instance;
        return instance;
    }

    logger::logger()
        : m_current_loglevel( log_level::error )
    {}

    logger::logger_name_type logger::name() const
    {
        return "main";
    }
}
