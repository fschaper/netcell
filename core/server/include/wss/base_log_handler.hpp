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

#include <wss/i_log_handler.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/thread/mutex.hpp>
#   include <iosfwd>
#   include <string>
#   include <map>
#endif

namespace logging
{
    /*!
     * \brief
     * base class for log handlers that takes care of the modifier registering/unregistering
     * functionality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class base_log_handler
        : public i_log_handler
    {
        typedef boost::mutex mutex_type;
        typedef mutex_type::scoped_lock lock_type;
    public:
        virtual void level( log_level::level level );

        virtual log_level::level level() const;

        virtual void register_modifier( unsigned int priority, const shared_log_modifier_type& modifier );

        virtual void unregister_modifier( const shared_log_modifier_type& modifier );

        virtual void log( log_level::level l, const char* message );

        bool show_repeated() const;

        void show_repeated( bool show );

    protected:
        base_log_handler();

        virtual void actual_log( log_level::level level, const std::string& message ) = 0;

        void pass_repetition_message();

    private:
        bool check_for_repetition( const std::string& message );

        void apply_modifiers( log_level::level level, std::string& message );

        typedef std::map<std::string, shared_log_modifier_type> modifier_map_type;

    private:
        mutable mutex_type m_repetition_counter_guard;
        log_level::level m_level;
        modifier_map_type m_modifier_map;

        bool m_show_repeated;
        std::string m_last_message;
        unsigned int m_repeat_count;
    };

}
