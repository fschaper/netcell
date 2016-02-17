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

#include <wss/sheet_range.hpp>
#include <wss/type.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/make_shared.hpp>
#endif

class dependency_node_reference;
typedef boost::shared_ptr<dependency_node_reference> shared_dependency_node_reference_type;
typedef boost::weak_ptr<dependency_node_reference> weak_dependency_node_reference_type;

/*!
 * \brief
 * reference to a set of dependencies.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class dependency_node_reference
{
    template< class T, class A1, class A2 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const& a1, A2 const& a2 );
public:
    ~dependency_node_reference();

    /*!
     * \brief
     * factory method to create a shared dependency node.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_dependency_node_reference_type create( const sheet_range& position, const weak_worksheet_type& ws );

    /*!
     * \brief
     * return the position and reference type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sheet_range position() const;

    /*!
     * \brief
     * the position on the sheet may change but not the reference type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void position( const geometry::rectangle_type& r );

    /*!
     * \brief
     * return the worksheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    weak_worksheet_type worksheet() const;

    /*!
     * \brief
     * change the worksheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void worksheet( const weak_worksheet_type& ws );

    /*!
     * \brief
     * return the list of registered precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_dependency_set_type& container();

private:
    dependency_node_reference( const sheet_range& position, const weak_worksheet_type& ws );

private:
    typedef locked_object<sheet_range> locked_position_type;
    locked_position_type m_position;
    locked_dependency_set_type m_precedents;
    weak_worksheet_type m_worksheet;
};
