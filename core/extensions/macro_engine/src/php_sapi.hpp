/*!
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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

#include <wss/friend.hpp>
#include <wss/singleton.hpp>
#include <wss/logging.hpp>
#include <wss/session.hpp>
#include <boost/signal.hpp>

struct _zval_struct;
struct _zend_module_entry;
typedef _zend_module_entry zend_module_entry;
class i_task;

/*!
 * \brief
 * creates the environment for a php request.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class php_requestor
    : private boost::noncopyable
{
    friend class php_sapi;
    friend class scoped_php_thread;
public:
    ~php_requestor() {}

    /*!
     * \brief
     * start a new bridge php request
     *
     * creates a new php request, set's the users session object and executes
     * "Task"
     *
     * \param cx
     * session context of the user
     *
     * \param ar
     * active range A1 coordinates (from the interpreter context)
     *
     * \param task
     * task to be executed under the created request
     *
     * \param ic
     * the interpreter_context we're running on
     */
    void execute( session& s, const std::string& active_range, const i_task& task, interpreter_context* ic = NULL );

private:
    php_requestor() {}
    // thread book keeping
    static boost::atomic_int m_thread_count;

};

/* \brief
 * initialization of the PHP scripting engine.
 *
 * This class has to be instantiated for every process
 * before calling any other PHP functions.
 *
 * \remarks
 * call this once per process.
 *
 * could not use ThreadSafe Singleton here because the process
 * has to be fully build up before calling PHP SAPI startup functions.
 */
class php_sapi
    : public singleton<php_sapi>
{
    FRIEND_CLASS singleton<php_sapi>;


public:
    typedef std::auto_ptr<php_requestor> auto_requestor_type;
    typedef boost::signal < void( const std::string& ) > on_unbuffered_write_type;
    typedef boost::signal < void( _zval_struct* ) > on_handle_trackvars_type;
    typedef boost::signal < void( int log_level, const std::string& ) > on_log_message_type;
    typedef std::vector<std::string> extensions_list_type;

public:
    /* \brief
     * event that will be fired whenever a PHP function writes to stdout
     */
    on_unbuffered_write_type on_unbuffered_write;

    /* \brief
     * event that will be fired whenever a PHP request startup occurs
     */
    on_handle_trackvars_type on_handle_trackvars;

    /* \brief
     * event that will be fired whenever PHP generates a log message
     */
    on_log_message_type on_log_message;

public:
    bool initialize( logging::log_level::level log_level,
                     const std::string& php_basedir,
                     const std::string& include_paths,
                     const std::string& dynamic_extensions_basedir,
                     const std::string& ini_directives,
                     const extensions_list_type& dynamic_extensions_list,
                     zend_module_entry& additional_modules,
                     unsigned num_additional_modules );

    auto_requestor_type requestor() const;

    void free_thread();
    void shutdown();
    const std::string& get_php_basedir() const;

    static const int max_expected_thread_count = 128;
private:
    php_sapi();

protected:
    bool            m_initialized;
    std::string     m_php_basedir;
private:
    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;

    mutable mutex_type m_mutex;
};

