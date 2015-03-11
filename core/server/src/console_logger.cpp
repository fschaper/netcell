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

#include "precompiled_header.hpp"
#include "wss/console_logger.hpp"
#include "wss/singleton.hpp"
#include "wss/named_thread.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/bind.hpp>
#   include <boost/thread/thread.hpp>
#   include <boost/thread/mutex.hpp>
#   include <boost/thread/condition_variable.hpp>
#   include <iostream>
#   include <deque>
#endif // HAS_PRECOMPILED_HEADER == 0

#if defined(WIN32)
#   include <Windows.h>
#endif // WIN32

namespace logging
{
    /*!
     * \brief
     * queued console output.
     *
     * this class will still collide with any other direct output
     * of threads. If synchronization is needed for global std::cout
     * a thread safe stream operator has to be provided.
     *
     * \remarks
     * since the process does not synchronize it's shutdown with
     * this thread messages might get lost that weren't yet written
     * to std::cout. If this becomes a problem we will need to maintain
     * and wait on "state".
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class message_queue
        : public singleton<message_queue>
    {
        FRIEND_CLASS singleton<message_queue>;

        static const std::size_t max_peak_messages_before_forced_memory_collection = 10000;


        struct log_message {
            log_message() {}
            log_message( log_level::level level, const std::string& msg )
                : level( level )
                , message( msg ) {}
            log_level::level level;
            std::string message;
        };

        // changed from queue to deque since queue does not support "swap"
        typedef std::deque<log_message> string_queue_type;
        typedef boost::mutex mutex_type;
        typedef mutex_type::scoped_lock lock_type;

    public:
        void queue( log_level::level level, const std::string& message ) {
            {
                lock_type lock( m_mutex );
                m_queue.push_back( log_message( level, message ) );
            }
            m_has_new_message.notify_all();
        }

    private:
        message_queue() {
            is_terminating = false;
            boost::thread( boost::bind( &message_queue::message_loop, this ) );
        }

        ~message_queue() {
            is_terminating = true;
            m_has_new_message.notify_all();
            boost::this_thread::yield();
        }

        void message_loop() {
            name_thread( "console logger" );

            log_message current;
            bool has_message;
            std::size_t message_queue_peak = 0;

            while ( true ) {
                {
                    lock_type lock( m_mutex );

                    // check if the queue has allocated memory for more than max. peak size.
                    if ( m_queue.empty() && message_queue_peak > max_peak_messages_before_forced_memory_collection ) {
                        // force memory free for the container.
                        string_queue_type().swap( m_queue );
                        message_queue_peak = 0;
                    }

                    while ( m_queue.empty() ) {
                        m_has_new_message.wait( lock );
                        if ( is_terminating ) {
                            lock.unlock();
                            return;
                        }
                    }
                }

                std::size_t message_queue_size = 0;
                do {
                    has_message = false;
                    {
                        lock_type lock( m_mutex );
                        if ( ! m_queue.empty() ) {
                            current = m_queue.front();
                            m_queue.pop_front();
                            ++message_queue_size;
                            has_message = true;
                        }
                    }
                    if ( has_message ) {
#if defined(WIN32)
                        HANDLE console_handle = GetStdHandle( STD_OUTPUT_HANDLE );
                        CONSOLE_SCREEN_BUFFER_INFO cinfo;
                        GetConsoleScreenBufferInfo( console_handle, &cinfo );
                        WORD old_settings = cinfo.wAttributes;
                        WORD new_settings = old_settings;
                        switch ( current.level ) {
                            case log_level::critical:
                            case log_level::error:
                                new_settings = FOREGROUND_RED | FOREGROUND_INTENSITY;
                                break;

                            case log_level::warning:
                                new_settings = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
                                break;

                            default:
                                break;
                        }
                        SetConsoleTextAttribute( console_handle, new_settings );
#endif // WIN32
                        std::cout << current.message << std::endl;
#if defined(WIN32)
                        SetConsoleTextAttribute( console_handle, old_settings );
#endif // WIN32
                    }
                } while ( has_message );

                if ( message_queue_size > message_queue_peak ) {
                    message_queue_peak = message_queue_size;
                }
            }
        }

    private:
        boost::condition_variable m_has_new_message;
        mutable mutex_type m_mutex;
        string_queue_type m_queue;
        bool is_terminating;
    };


    console_logger::logger_name_type console_logger::name() const
    {
        return logger_name;
    }

    void console_logger::actual_log( log_level::level level, const std::string& message )
    {
        message_queue::instance().queue( level, message );
    }

    console_logger::~console_logger()
    {
        pass_repetition_message();
    }

    void console_logger::use_highlighter( bool use )
    {
        m_use_highligther = use;
    }

    bool console_logger::uses_highligther() const
    {
        return m_use_highligther;
    }

    console_logger::console_logger()
        : m_use_highligther( true )
    {}

    const char* console_logger::logger_name = "console";

    console_logger_creator::result_type console_logger_creator::create() const
    {
        return result_type( new console_logger() );
    }
}

