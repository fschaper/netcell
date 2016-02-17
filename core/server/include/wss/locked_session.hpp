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
 *\
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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com> refactored this starting from session holder
 */

#pragma once

#include <wss/define.hpp>
#include <wss/session.hpp>

/*!
 * \brief
 * session holder
 *
 * \remarks
 * a single session object may only be used by one thread at the same
 * time. this holder helps to enforce this policy.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE locked_session
{
    friend class session_handler;
    friend class auto_save;
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_session();

    /*!
     * \brief
     * copy constructor.
     *
     * \remarks
     * !!! the copy constructor will not really copy the object
     * like with a std::auto_ptr the original copy will loose
     * the handle to the session by copying !!!
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_session( const locked_session& other );

    /*!
     * \brief
     * assignment operator
     *
     * \remarks
     * !!! the copy constructor will not really copy the object
     * like with a std::auto_ptr the original copy will loose
     * the handle to the session by copying !!!
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_session& operator =( const locked_session& rhs );

    /*!
     * \brief
     * destructor.
     *
     * will return the session object to the session handler
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~locked_session();

    /*!
     * \brief
     * the session will not return to the session handler
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void destroy();

    /*!
     * \brief
     * will convert to true in case the session is initialized.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    operator bool() const;

    /*!
     * \brief
     * access to the session object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const session* operator ->() const;

    /*!
     * \brief
     * access to the session object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    session* operator ->();

    /*!
     * \brief
     * access to the session object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    session& operator *() const;

    /*!
         * \brief
         * access to the session object.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
    session& operator *();

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_session( const shared_session_type& session );

    mutable shared_session_type m_session;
    mutable bool m_return_session;

    typedef boost::unique_lock< session::session_sync_obj >  lock;
    std::auto_ptr< lock >                           m_lock;
};

