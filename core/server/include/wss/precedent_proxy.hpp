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
#include <wss/reference_table.hpp>

class cell_manager;

/*!
 * \brief
 * caches the current precedents of a formula so already registered areas of interest (precedents)
 * can be reused.
 *
 * this is actually not only an optimization step but mandatory since upon destruction
 * shared_dependency_references will unregister them selfs from the sheet possibly
 * corrupting the new formula which might be interested in partly the same areas.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE precedent_proxy
{
public:
    /*!
     * \brief
     * constructor.
     *
     * will call the precedents method of the issuing dependency
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    precedent_proxy( const shared_dependency_type& issuing_dependency );

    /*!
     * \brief
     * constructor.
     *
     * pass a list of precedents the proxy will use. will not call the precedents
     * method of the passed dependency as opposed to the second constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    precedent_proxy( const shared_dependency_type& issuing_dependency, const referencetable_type& precedents );

    /*!
     * \brief
     * will first look up the requested dependency in the list of already available connections
     * and return those if available. otherwise will redirect the call to the cell_manager to create
     * and cache the new reference.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_reference_type register_dependency( cell_manager& cm, const sheet_range& area_of_interest, const bool inside_nf = false );

    /*!
     * \brief
     * return the initiator
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const shared_dependency_type& initiator() const;

private:
    typedef std::map<sheet_range, shared_reference_type> position_to_reference_map_type;
    typedef std::map<weak_worksheet_type, position_to_reference_map_type> worksheet_mapping_type;
    const shared_dependency_type& m_issuing_dependency;
    worksheet_mapping_type m_cached_references;
};

