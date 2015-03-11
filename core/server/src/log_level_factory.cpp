/*!
 * Logging framework
 *
 * Copyright (c) 2007 by Florian Schaper <florian.schaper@jedox.com>
 * Jedox GmbH, Freiburg, Germany
 */

#include "precompiled_header.hpp"
#include "wss/log_level_factory.hpp"

namespace logging
{

    log_level_factory::log_level_factory() {}

    log_level_factory::~log_level_factory() {}

    log_level::level log_level_factory::create( const std::string& string )
    {
        log_level::level return_value;
        if ( string == "notice" ) {
            return_value = log_level::notice;
        } else if ( string == "warning" ) {
            return_value = log_level::warning;
        } else if ( string == "error" ) {
            return_value = log_level::error;
        } else if ( string == "info" ) {
            return_value = log_level::info;
        } else if ( string == "debug" ) {
            return_value = log_level::debug;
        } else if ( string == "trace" ) {
#ifdef _DEBUG
            return_value = log_level::trace;
#else
            return_value = log_level::debug;
#endif // _DEBUG
        } else if ( string == "critical" ) {
            return_value = log_level::critical;
        } else {
            return_value = log_level::error;
        }
        return return_value;
    }

    log_level_factory& log_level_factory::instance()
    {
        static log_level_factory instance;
        return instance;
    }

}
