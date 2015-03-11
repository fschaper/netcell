/**
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
 *  Dragan Simic <dragan.simic@develabs.com>
 */

#ifdef _PHPSAPI
//#   define _PHPSAPI

// wss
#include <wss/define.hpp>

// jlib
#include <jedox/event/EventHandler.hpp>
#include <jedox/pattern/creational/Singleton.hpp>
#include <jedox/log/ILogable.hpp>

// stl
#include <string>
#include <vector>

// boost
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/mutex.hpp>

// php extension headers
#include "PHPBridge_Headers.hpp"

struct _zval_struct;
struct _zend_module_entry;

class PHPSapi;

class PHPRequestor: private boost::noncopyable, public boost::enable_shared_from_this<PHPRequestor>
{
    friend class PHPSapi;

public:
    ~PHPRequestor();

private:
    PHPRequestor();
};

using jedox::pattern::creational::Singleton;
using jedox::event::EventHandler;

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
class PHPSapi: public Singleton<PHPSapi>
{
    FRIEND_CLASS Singleton<PHPSapi>;

    static const int MAX_EXPECTED_THREAD_COUNT = 128;

public:
    typedef std::auto_ptr<PHPRequestor> auto_requestor_type;
    typedef EventHandler<void( const std::string& )> on_unbuffered_write_type;
    typedef EventHandler<void( _zval_struct* )> on_handle_trackvars_type;
    typedef EventHandler<void( int log_level, const std::string& )> on_log_message_type;
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
    bool initialize( const jedox::log::LogLevel::Level log_level,
                     const std::string& php_basedir,
                     const std::string& include_paths,
                     const std::string& dynext_basedir,
                     const extensions_list_type& dynext_list,
                     zend_module_entry& additional_modules,
                     unsigned num_additional_modules );

    const std::string& get_php_basedir() const;
    auto_requestor_type get_requestor() const;
    void free_thread();

private:
    PHPSapi();
    ~PHPSapi();

protected:
    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;

    mutable mutex_type m_mutex;
    bool m_initialized;
    std::string m_php_basedir;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class PhpLogLevelConverter
{
public:
    PhpLogLevelConverter();

    std::string operator()( const jedox::log::LogLevel::Level log_level ) const;
    jedox::log::LogLevel::Level operator()( int php_level ) const;
};

# endif // _PHPSAPI
