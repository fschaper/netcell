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
 * opcode m_reference table info block.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 *
 * \see
 * opcode_generator
 */
class WSS_MODULE reference_info
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    reference_info();

    reference_info( const reference_info& other );

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    reference_info( const shared_reference_type& r, bool worksheet_is_relative, bool is_single_cell, bool worksheet_given, bool workbook_given, const shared_worksheet_type& ws, const shared_workbook_type& wb );

    /*!
     * \brief
     * conversion operator
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline operator const shared_reference_type& () const {
        return m_reference;
    }

    /*!
     * \brief
     * forwarder method for the shared_ptr.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline i_dependency_reference* operator -> () const {
        return m_reference.operator ->();
    }

    /*!
     * \brief
     * forwarder method for the validity test of the shared_ptr.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline operator bool() const {
        return m_reference;
    }

    /*!
     * \brief
     * comparison operator.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    bool operator ==( const reference_info& rhs ) const;

    /*!
     * \brief
     * returns true if the reference was defined relative.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline bool relative_worksheet() const {
        return m_relative_worksheet;
    }

    /*!
     * \brief
     * returns true in case the position on the sheet defines a single
     * cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline bool is_single_cell() const {
        return m_is_single_cell;
    }

    /*!
     * \brief
     * check if this reference info is still valid
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    inline bool is_valid() const {
        return m_reference;
    }

    /*!
     * \brief
     * for lookups in case the reference gets invalidated and we still want to
     * to be able to pretty print the workbook/worksheet
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    inline const weak_worksheet_type& worksheet() const {
        return m_worksheet;
    }

    inline const weak_workbook_type& workbook() const {
        return m_workbook;
    }

    inline const bool workbook_given() const {
        return m_workbook_given;
    }

    inline const bool worksheet_given() const {
        return m_worksheet_given;
    }

private:
    bool m_relative_worksheet;
    bool m_is_single_cell;
    bool m_is_ref_error;
    shared_reference_type m_reference;
    /*!
     * \brief
     * for lookups in case the reference gets invalidated and we still want to
     * to be able to pretty print the workbook/worksheet
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    bool m_worksheet_given;
    bool m_workbook_given;
    weak_worksheet_type m_worksheet;
    weak_workbook_type m_workbook;
};
