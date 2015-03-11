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

#include <wss/i_loggable.hpp>
#include <wss/i_log_handler.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/shared_ptr.hpp>
#endif

namespace logging
{
    /*!
     * \brief
     * interface class for log handlers.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class i_logger
        : public i_loggable
    {
    public:
        virtual ~i_logger() {}

    public:
        typedef boost::shared_ptr<i_log_handler> shared_log_handler_type;

    public:
        /*!
         * \brief
         * return the log handler registered by the passed name.
         *
         * \returns
         * a pointer to the log-handler registered under the name or NULL if
         * no handler could be found under that identifier.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual i_log_handler* handler( i_log_handler::logger_name_type name ) = 0;

        /*!
         * \brief
         * register a log handler with the logger.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual void register_handler( const shared_log_handler_type& handler ) = 0;

        /*!
         * \brief
         * unregister a log handler with the logger.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual void unregister_handler( const shared_log_handler_type& handler ) = 0;
    };

}
