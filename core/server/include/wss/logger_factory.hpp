/*!
 * Logging framework
 *
 * Copyright (c) 2007 by Florian Schaper <florian.schaper@jedox.com>
 * Jedox GmbH, Freiburg, Germany
 */

#pragma once

#include <wss/factory.hpp>
#include <wss/i_log_handler.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#endif

namespace logging
{
    /*!
     * \brief
     * factory for creating logger by logger name.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class logger_factory
        : public factory<i_log_handler>
        , boost::noncopyable
    {
    public:
        /*!
         * \brief
         * return singleton instance.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static logger_factory& instance();

    private:
        logger_factory();
        ~logger_factory();
    };

}
