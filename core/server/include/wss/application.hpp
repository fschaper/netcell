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
#include <wss/identifiable_object.hpp>
#include <wss/calculation_setting.hpp>
#include <wss/object_container.hpp>
#include <wss/style_set.hpp>
#include <wss/workbook.hpp>

#if defined( WIN32 )
# pragma warning ( disable : 4251 4275 ) // disable "needs to have dll-interface" warning
#endif // WIN32

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/enable_shared_from_this.hpp>
# include <boost/noncopyable.hpp>
# include <list>
#endif

/*!
 * \brief
 * Application representation.
 *
 * \see
 * workbook | worksheet
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE application
    : public identifiable_object
    , public object_container<application, workbook>
    , public boost::enable_shared_from_this<application>
    , boost::noncopyable
{
    friend class server;
    template< class T, class A1 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const& a1 );
public:
    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~application();

    /*!
     * \brief
     * application wide calculation_settings settings.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline ::calculation_settings& calculation_settings() {
        return m_calculation_settings;
    }

    /*!
     * \brief
     * select as active application.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void select( selection_state& s );

    /*!
     * \brief
     * application default style.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    style_set_type& default_style();

    /*!
     * \brief
     * application default style.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const style_set_type& default_style() const;

    /*!
     * \brief
     * get information about the workbooks
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    id_name_path_mapping_vec_type list_workbooks() const;

private:
    template<class, class, class>
    friend struct policy::no_parent;
    /*!
     * \brief
     * factory method.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_application_type create( const utf8_ci_string& name );

    template<class, class, template<class, class, class> class, class >
    friend class object_container;

    /*!
     * \brief
     * unload the application from memory.
     *
     * will in turn call unload on all workbooks.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unload();

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    application( const utf8_ci_string& name );

private:
    ::calculation_settings m_calculation_settings;
    style_set_type m_default_style;
};

