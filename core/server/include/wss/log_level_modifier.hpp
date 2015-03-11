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
#include <wss/i_log_modifier.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <string>
#endif

namespace logging
{
    /*!
     * \brief
     * pass the currently set log-level to the output stream.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class log_level_modifier
        : public i_log_modifier
    {
    public:
        /*!
         * \brief
         * apply modifier to log message
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void apply( log_level::level level, std::string& to_modify ) const;

        /*!
         * \brief
         * return the name of the modifier.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        modifier_name_type modifier_name() const;

        /*!
         * \brief
         * return the name of the modifier.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static modifier_name_type name();
    };

    /*!
     * \brief
     * creator for the log_level modifier.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class log_level_modifier_creator
        : public factory<i_log_modifier>::creator_base_type
    {
    public:
        typedef factory<i_log_modifier>::creator_base_type::result_type result_type;

        result_type create() const;
    };
}
