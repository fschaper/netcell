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
 *  this program; if not, log to the Free Software Foundation, Inc., 59 Temple
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

#include "precompiled_header.hpp"
#include "wss/base_log_handler.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <ostream>
#   include <cassert>
#endif // HAS_PRECOMPILED_HEADER == 0

namespace logging
{
    base_log_handler::base_log_handler()
        : m_level( log_level::error )
        , m_show_repeated( false )
        , m_repeat_count( 0 )
    {}

    void base_log_handler::level( log_level::level level )
    {
        m_level = level;
    }

    log_level::level base_log_handler::level() const
    {
        return m_level;
    }

    void base_log_handler::register_modifier( unsigned int /*priority*/, const shared_log_modifier_type& modifier )
    {
        assert( modifier != NULL );
        m_modifier_map[ modifier->modifier_name()] = modifier;
    }

    void base_log_handler::unregister_modifier( const shared_log_modifier_type& modifier )
    {
        assert( modifier != NULL );
        m_modifier_map.erase( modifier->modifier_name() );
    }

    void base_log_handler::apply_modifiers( log_level::level level, std::string& message )
    {
        for ( modifier_map_type::const_iterator it = m_modifier_map.begin(), end = m_modifier_map.end() ; it != end; ++it ) {
            ( *it ).second->apply( level, message );
        }
    }

    bool base_log_handler::show_repeated() const
    {
        return m_show_repeated;
    }

    void base_log_handler::show_repeated( bool show )
    {
        if ( show && m_repeat_count ) {
            pass_repetition_message();
        }
        m_show_repeated = show;
    }

    void base_log_handler::log( log_level::level l, const char* message )
    {
        if ( l >= level() ) {
            std::string msg( message );
            if ( check_for_repetition( message ) ) {
                return;
            }
            apply_modifiers( l, msg );
            actual_log( l, msg );
        }
    }

    bool base_log_handler::check_for_repetition( const std::string& message )
    {
        if ( ! m_show_repeated ) {
            lock_type lock( m_repetition_counter_guard );
            if ( message == m_last_message ) {
                ++m_repeat_count;
                return true;
            } else {
                pass_repetition_message();
                m_last_message = message;
                m_repeat_count = 0;
            }
        }
        return false;
    }

    void base_log_handler::pass_repetition_message()
    {
        if ( m_repeat_count ) {
            std::stringstream sstream;
            sstream << "last message repeated " << m_repeat_count << " times!" << std::endl;
            actual_log( log_level::info, sstream.str() );
        }
    }
}

