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

#include <wss/factory.hpp>
#include <wss/base_log_handler.hpp>

namespace logging
{
    /*!
     * \brief
     * logger that will output log messages to the primary console (stdout).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class console_logger
        : public base_log_handler
    {
    public:
        static const char* logger_name;

        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        console_logger();

        /*!
         * \brief
         * destructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        ~console_logger();

        /*!
         * \brief
         * return the logger name 'console'
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        logger_name_type name() const;

        /*!
         * \brief
         * use highlighter (if supported by the OS)
         *
         * \remarks
         * currently without functionality. always "on".
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void use_highlighter( bool use );

        /*!
         * \brief
         * uses highlighter.
         *
         * \remarks
         * currently without functionality. always "on".
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool uses_highligther() const;

    protected:
        /*!
         * \brief
         * passes a message to the log handler that
         * the handler should process.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void actual_log( log_level::level level, const std::string& message );

    private:
        bool m_use_highligther;
    };

    /*!
     * \brief
     * creator for the console logger.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class console_logger_creator
        : public factory<i_log_handler>::creator_base_type
    {
    public:
        typedef factory<i_log_handler>::creator_base_type::result_type result_type;

        result_type create() const;
    };
}

