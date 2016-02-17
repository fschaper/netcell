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

/*!
 * \brief
 * initiator class.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE with_initiator
{
public:
    class scoped_change_caller
    {
    private:
        with_initiator&             m_initiator;
        shared_dependency_type&     m_old_caller;
    public:
        scoped_change_caller( with_initiator& initiator,  const shared_dependency_type& caller );
        ~scoped_change_caller();
    };

    /*!
     * \brief
     * set the initiator for the current calculation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    with_initiator( const shared_dependency_type& initiator );

    /*!
     * \brief
     * set the initiator for the current calculation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    with_initiator( const shared_dependency_type& initiator, const shared_dependency_type& named_formula );

    /*!
     * \brief
     * retrieve the initiator for the current calculation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const shared_dependency_type& initiator() const;

    /*!
     * \brief
     * returns true in case a named formula is currently being calculated.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_inside_named_formula() const;

    /*!
     * \brief
     * returns the named formula initiator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const shared_dependency_type& named_formula_initiator() const;

    inline void is_inside_named_formula( bool val ) {
        m_is_inside_named_formula = val;
    }

    const shared_dependency_type& caller() const;
private:
    const shared_dependency_type& m_initiator;
    shared_dependency_type m_caller;
    shared_dependency_type m_named_formula;
    bool m_is_inside_named_formula;
};
