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

#include <wss/invalid_name_exception.hpp>

#include <wss/boolean_combiner.hpp>
#include <wss/ci_string.hpp>
#include <wss/friend.hpp>
#include <wss/define.hpp>
#include <wss/type.hpp>

#if defined( WIN32 )
# pragma warning ( disable : 4251 ) // disable "needs to have dll-interface" warning
#endif // WIN32

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/thread/recursive_mutex.hpp>
# include <boost/uuid/uuid.hpp>
# include <boost/signal.hpp>
# include <string>
#endif

/*!
 * \brief
 * this needs to be fixed on the ui side first.. remove the following line(s) if worksheet elements can change the uuid on load!
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class worksheet_element;

/*!
     * \brief
     * provides identification facilities for objects.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
class WSS_MODULE identifiable_object
{
    /*!
    * \brief
    * this needs to be fixed on the ui side first.. remove the following line(s) if worksheet elements can change the uuid on load!
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    FRIEND_CLASS worksheet_element;
public:
    /*!
     * \brief
     * on before name change event handler.
     *
     * event handler that will be executed before the name
     * of the object gets changed. If one of the connected
     * handlers returns FALSE the renaming is aborted.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    boost::signal < bool( identifiable_object&, const utf8_ci_string& ), boolean_combiner<> > on_before_name_change;

    /*!
     * \brief
     * return the objects unique identifier.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline const boost::uuids::uuid& uuid() const {
        return m_uuid;
    }


    /*!
     * \brief
     * return the objects name.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline const utf8_ci_string& name() const {
        lock_type lock( m_mutex );
        return m_name;
    }

    /*!
     * \brief
     * set a new name for the object.
     *
     * if the object is renamed depends on the result of
     * the on_before_name_change event handler.
     *
     * \remarks
     * will trigger on_before_name_change event handler.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void name( const utf8_ci_string& name );

    /*!
     * \brief
     * test for equality
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator ==( const identifiable_object& other ) const;

    /*!
     * \brief
     * test for inequality
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator !=( const identifiable_object& other ) const;

protected:
    /*!
     * \brief
     * constructs a named identifiable object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    identifiable_object( const utf8_ci_string& name );

    /*!
     * \brief
     * copy constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    identifiable_object( const identifiable_object& other );

private:
    typedef boost::recursive_mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;

    mutable mutex_type m_mutex;
    utf8_ci_string m_name;
    boost::uuids::uuid m_uuid;
};


