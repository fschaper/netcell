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

#include <wss/base_node.hpp>
#include <wss/type.hpp>

/*!
 * \brief
 * reference base node
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE reference_base_node
{
public:
    virtual ~reference_base_node();

    const weak_worksheet_type& worksheet() const;

    bool has_workbook() const;

    bool has_worksheet() const;

    std::string ref_error_worksheet() const;

    std::string ref_error_workbook() const;

protected:
    reference_base_node( const weak_worksheet_type& ws, const std::string& workbook, const std::string& worksheet );

    reference_base_node( const reference_base_node& other );

private:
    weak_worksheet_type m_worksheet_object;
    std::auto_ptr<std::string> m_workbook;
    std::auto_ptr<std::string> m_worksheet;
    bool m_workbook_given;
    bool m_worksheet_given;
};
