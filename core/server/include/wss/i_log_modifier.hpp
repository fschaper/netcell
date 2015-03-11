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

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/shared_ptr.hpp>
#   include <string>
#endif

namespace logging
{

    class i_log_modifier;
    typedef boost::shared_ptr<i_log_modifier> shared_log_modifier_type;

    class i_log_handler;

    /*!
     * \brief
     * interface class for log-modifiers.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class i_log_modifier
    {
    public:
        virtual ~i_log_modifier() {}

    public:
        typedef const char* modifier_name_type;

    public:
        /*!
         * \brief
         * apply the modifier to the log message.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual void apply( log_level::level level, std::string& to_modify ) const = 0;

        /*!
         * \brief
         * return the unique name of the modifier.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        virtual modifier_name_type modifier_name() const = 0;
    };

}
