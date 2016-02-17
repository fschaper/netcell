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

#include <wss/type.hpp>
#include <wss/sheet_range.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#   include <boost/uuid/uuid.hpp>
#endif

/*!
 * \brief
 * active selection of the user.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE selection_state
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    selection_state();

    ~selection_state();

    /*!
     * \brief
     * currently selected application object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline const shared_application_type& application() const {
        return m_application;
    }

    /*!
     * \brief
     * currently selected workbook object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline weak_workbook_type workbook() const {
        return m_workbook;
    }

    /*!
     * \brief
     * currently selected worksheet object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline weak_worksheet_type worksheet() const {
        return m_worksheet;
    }

    /*!
     * \brief
     * currently selected range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline const sheet_range& range() const {
        return m_range_on_sheet;
    }

    /*!
     * \brief
     * sets the active application object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void application( const shared_application_type& app );

    /*!
     * \brief
     * sets the active workbook object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void workbook( const shared_workbook_type& wb );

    /*!
     * \brief
     * sets the active worksheet object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void worksheet( const shared_worksheet_type& ws );

    /*!
     * \brief
     * sets the active range object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline void range( const sheet_range& r ) {
        m_range_on_sheet = r;
    }

private:
    // we keep a copy of any shared pointer to an application
    // so the garbage collector will not unload any app object
    // that is still in use. We have - however - to be careful
    // where we keep selection_state laying around.
    shared_application_type m_application;
    weak_workbook_type m_workbook;
    weak_worksheet_type m_worksheet;
    sheet_range m_range_on_sheet;
    typedef std::map< uuid_type, weak_worksheet_type > active_sheet_map;
    active_sheet_map m_workbook_active_worksheet;
};

