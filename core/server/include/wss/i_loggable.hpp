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
#include <wss/non_instantiable.hpp>

#if defined(error) || defined(debug)
# ifdef WIN32
#  pragma message ( "error or debug preprocessor define found! These will be unset!" )
# else
#  warning "ERROR or debug preprocessor define found! These will be unset!"
# endif
# undef error
# undef debug
#endif

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <string>
#endif

namespace logging
{
    /*!
     * \brief
     * log level definition.
     *
     * \remarks
     * level are given in the order of priority.
     * debug will provide trace | debug | info | notice | warning | error | critical
     * information while warning will output only warning | error | critical
     * messages.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct log_level
            : non_instantiable {
        enum level {
            //trace will be mapped to debug on release builds right now
            trace,
            debug,
            info,
            notice,
            warning,
            error,
            critical
        };
    };

    /*!
     * \brief
     * interface definition for an class that will take
     * log messages and forwards them to some sort of output
     * device like the screen, an file or network socket.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class i_loggable
    {
    public:
        virtual ~i_loggable() {}

    public:
        typedef const char* logger_name_type;

    public:
        /*!
         * \brief
         * name of the logger in question.
         *
         * \remarks
         * will also be used by some factory classes to lookup
         * the name.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual logger_name_type name() const = 0;

        /*!
         * \brief
         * sets the logger to handle log messages of an certain
         * level and above.
         *
         * \remarks
         * if set to 'warning' will accept warning log messages
         * as well as the levels error and critical.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual void level( log_level::level level ) = 0;

        /*!
         * \brief
         * returns the log-level the handler is currently set to.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual log_level::level level() const = 0;

        /*!
         * \brief
         * passes a log-level and a message to the log handler that
         * the handler should process.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual void log( log_level::level level, const char* message ) = 0;

        /*!
         * \brief
         * allows for logger configuration.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual void target( const std::string& ) {}
    };

}
