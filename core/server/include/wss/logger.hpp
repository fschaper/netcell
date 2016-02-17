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
#include <wss/i_logger.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <map>
#   include <boost/noncopyable.hpp>
#   include <boost/shared_ptr.hpp>
#   include <sstream>
#endif

#ifdef _WIN32
# pragma warning( disable : 4275 4251 ) // disable warnings about logger members needing dll interface.
#endif

#undef debug
#undef info
#undef notice
#undef warning
#undef error
#undef critical
#undef LOG

#define LOG( log_level, message ) { if( ::logging::logger::instance().check_level( (log_level) ) ) { std::stringstream msg; msg << message; ::logging::logger::to_log( (log_level), msg.str() ); } }
#define LOG_TRACE( message ) LOG( ::logging::log_level::trace, message )
#define LOG_DEBUG( message ) LOG( ::logging::log_level::debug, message )
#define LOG_INFO( message ) LOG( ::logging::log_level::info, message )
#define LOG_NOTICE( message ) LOG( ::logging::log_level::notice, message )
#define LOG_WARNING( message ) LOG( ::logging::log_level::warning, message )
#define LOG_ERROR( message ) LOG( ::logging::log_level::error, message )
#define LOG_CRITICAL( message ) LOG( ::logging::log_level::critical, message )

namespace logging
{
    /*!
     * \brief
     * logger.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class WSS_MODULE logger
        : public i_logger
        , boost::noncopyable
    {
    public:
        /*!
         * \brief
         * name of the logger.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        logger_name_type name() const;

        /*!
         * \brief
         * set the log-level the logger should react on.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void level( log_level::level level );

        /*!
         * \brief
         * returns the log level the logger is currently set to.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        log_level::level level() const;

        bool check_level( log_level::level l ) const {
            return level() <= l;
        }

        /*!
         * \brief
         * get handler by name.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        i_log_handler* handler( i_log_handler::logger_name_type name );

        /*!
         * \brief
         * register an handler with the logger.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void register_handler( const shared_log_handler_type& handler );

        /*!
         * \brief
         * unregister an handler from the logger.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void unregister_handler( const shared_log_handler_type& handler );

        /*!
         * \brief
         * log a message with a given log level.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void log( log_level::level level, const char* message );

        /*!
         * \brief
         * convenience method. log a message with a given log level.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static void to_log( log_level::level level, const char* message );

        /*!
         * \brief
         * convenience method. log a message with a given loglevel.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static void to_log( log_level::level level, const std::string& message );

    public:
        /*!
         * \brief
         * get the instance of logger.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static logger& instance();

    private:
        logger();
        ~logger();

    private:
        typedef std::map<logger_name_type, shared_log_handler_type> handler_map_type;

    private:
        log_level::level m_current_loglevel;
        handler_map_type m_handler_map;
    };
}
