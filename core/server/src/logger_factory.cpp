/*!
 * Logging framework
 *
 * Copyright (c) 2007 by Florian Schaper <florian.schaper@jedox.com>
 * Jedox GmbH, Freiburg, Germany
 */

#include "precompiled_header.hpp"
#include "wss/logger_factory.hpp"
#include "wss/loggers.hpp"

namespace logging
{
    logger_factory::logger_factory()
    {
        register_creator( console_logger::logger_name, boost::make_shared<console_logger_creator>() );
        register_creator( file_logger::logger_name, boost::make_shared<file_logger_creator>() );
        register_creator( socket_logger::logger_name, boost::make_shared<socket_logger_creator>() );
    }

    logger_factory::~logger_factory() {}

    logger_factory& logger_factory::instance()
    {
        static logger_factory instance;
        return instance;
    }
}
