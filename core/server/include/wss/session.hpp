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
#include <wss/selection_state.hpp>
#include <wss/clipboard.hpp>
#include <wss/variable_store.hpp>
#include <wss/type.hpp>
#include <wss/calculation_cache.hpp>
#include <wss/friend.hpp>
#include <wss/arbitrary_storage.hpp>
#include <wss/user_return_format.hpp>
#include <wss/i_cached_connection.hpp>
#include <wss/transaction_wrapper.hpp>
#include <wss/calculation_setting.hpp>
#include <wss/broken_evaluation_dependencies.h>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/scoped_ptr.hpp>
#   include <boost/uuid/uuid.hpp>
#   include <boost/make_shared.hpp>
#   include <boost/thread/tss.hpp>
#   include <boost/enable_shared_from_this.hpp>
#endif

class locale;
class session_sheet_map;
class calculation_context;
class locked_session;

namespace xlsx
{
    class scoped_set_session_to_importing;
}

/*!
 * \brief
 * user session.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE session
    : boost::noncopyable
    , public boost::enable_shared_from_this<session>
{
    friend class calculation_context;
    friend class session_handler;
    friend class locked_session;
    friend class xlsx::scoped_set_session_to_importing;

    template< class T, class A1, class A2, class A3, class A4 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const& );
public:
    /*!
     * \brief
     * creates a session.
     *
     * a session should always be acquired by the session_handler.
     * use with care.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_session_type create( const ::locale& l, const std::string& username = "", const std::string password = "", const group_set_type& groups = group_set_type() );

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~session();

    /*!
     * \brief
     * return the session object associated with the current thread.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static session* thread_session();

    /*!
     * \brief
     * username used to log on to the server.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& username() const;

    /*!
     * \brief
     * password used to log on to the server.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& password() const;

    /*!
     * \brief
     * list of groups the user is a member of.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const group_set_type& groups() const;

    /*!
     * \brief
     * get the users active locale.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const ::locale& locale() const;

    /*!
     * \brief
     * set the users active locale.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void locale( const ::locale& l );

    /*!
     * \brief
     * return the current selection state of the current session.
     *
     * returns the active application, workbook, worksheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    selection_state& selected();

    /*!
     * \brief
     * returns a const reference to the selected state.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const selection_state& selected() const;

    /*!
     * \brief
     * sets the selection state for the session.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void selected( const selection_state& s );

    /*!
     * \brief
     * uuid of the current session.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const uuid_type& uuid() const;

    /*!
     * \brief
     * returns the clipboard associated with the session.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::clipboard& clipboard();

    /*!
     * \brief
     * returns all variables associated with the session.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variable_store& variable();

    /*!
     * \brief
     * list of sheets that are available only to the current session.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    session_sheet_map& session_sheets();

    /*!
     * \brief
     * resets the sessions timeout count.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void revitalize();

    /*!
     * \brief
     * returns true of the sessions lifetime exceeded the session_handlers
     * configured session lifespan.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool has_timed_out() const;

    /*!
     * \brief
     * clear the calculation cache
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    inline void clear_cache() {
        if ( !m_is_loading ) {
            m_calculation_cache.clear( m_dont_clear_caches );
            m_palo_connection_cache.clear_pinged_and_unreachable_cache();
        }
    }

    /*!
     * \brief
     * cache palo connections
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    inline const connection_cache::palo_connection_cache_type& internal_access_connections() const {
        return m_palo_connection_cache.internal_access();
    }

    inline void cache_connection( const std::string& key, const shared_cached_connection_type& connection ) {
        m_palo_connection_cache.cache_connection( key, connection );
    }
    inline void remove_connection( const std::string& key ) {
        m_palo_connection_cache.remove_connection( key );
    }

    inline bool palo_connection_pinged( const std::string& key )const {
        return m_palo_connection_cache.get_pinged( key );
    }

    inline void set_palo_connection_pinged( const std::string& key ) {
        m_palo_connection_cache.set_pinged( key );
    }

    inline bool palo_connection_unreachable( const std::string& key )const {
        return m_palo_connection_cache.is_unreachable( key );
    }

    inline void set_palo_connection_unreachable( const std::string& key ) {
        m_palo_connection_cache.set_unreachable( key );
    }

    void clear_connection_cache() {
        m_palo_connection_cache.clear_all();
    }

    /*!
     * \brief
     * return the current calculation token for the object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline unsigned long calculation_token() const {
        return m_calculation_cache.calculation_token();
    }

    /*!
     * \brief
     * returns the sessions arbitrary storage.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    arbitrary_storage& storage();

    /*!
    * \brief
    * returns the sessions undo/redo transaction log.
    *
    * \author
    * Radu Racariu <radu.racariu@yalos-solutions.com>
    */
    transaction_wrapper& undo_redo_log();

    /*!
     * \brief
     * return the object used for user preferred function return format.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    user_return_format& user_format();

    /*!
    * \brief
    * returns a manager for dependencies that could not be calculated
    * due to unresolved function names
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    broken_evaluation_dependencies& broken_dependencies();

    /*!
     * \brief
     * from here on the cache won't be cleared until end_calculation is called
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void begin_calculation( const bool clear_one_more_time = true );

    /*!
     * \brief
     * start clearing the calculation cache again
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void end_calculation();

    /*!
     * \brief
     * save all open documents
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void autosave();

    /*!
     * \brief
     * remove autosaved documents
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void remove_autosave( const std::string& path );
    void remove_autosave();

    const ::calculation_settings& calculation_settings();

    static int max_lazy_function_count;

    inline const bool is_loading() const {
        return m_is_loading;
    }

    /*!
     * \brief
     * retrieve user name and pass
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    const std::string& username() {
        return m_username;
    }
    const std::string& password() {
        return m_password;
    }

    /*!
       * \brief
       * access the calculation cache
       *
       *
       * \see calculation_context | calculation_cache
       * \author
       * Frieder Hofmann <frieder.hofmann@jedox.com>
       */
    inline calculation_cache& cache() {
        return m_calculation_cache;
    }

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    session( const ::locale& l, const std::string& username, const std::string password, const group_set_type& groups );

    /*!
     * \brief
     * associate the current session with the current thread.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void associate_with_current_thread();

    inline void is_loading( bool val ) {
        m_is_loading = val;
    }
private:
    typedef boost::scoped_ptr<session_sheet_map> session_sheet_map_type;
    ::locale m_locale;
    selection_state m_selected_objects;
    uuid_type m_uuid;
    ::clipboard m_clipboard;
    variable_store m_variable_store;
    session_sheet_map_type m_session_sheets;
    boost::posix_time::ptime m_timeout;
    const std::string m_username;
    const std::string m_password;
    const group_set_type m_groups;
    calculation_cache m_calculation_cache;
    arbitrary_storage m_arbitrary_storage;
    boost::scoped_ptr<transaction_wrapper> m_transaction;
    static boost::thread_specific_ptr<session*> m_current_session;
    std::auto_ptr< user_return_format > m_user_return_format;
    broken_evaluation_dependencies m_broken_evaluation_dependencies;
    //don't clear the volatile cache if this is set
    bool m_dont_clear_caches;
    bool m_is_loading;
    connection_cache m_palo_connection_cache;

    //shortcut
    ::calculation_settings const* m_calculation_settings;
    //RIA: locking semantics
private:
    typedef boost::mutex                            session_sync_obj;
    session_sync_obj m_lock;
};

