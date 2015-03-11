/*!
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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

#include "i_php_function_wrapper.hpp"

/*!
 * \brief
 * wraps a PHP function as an worksheetserver function.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class php_redirected_spreadsheet_function
    : public i_php_function_wrapper
{
public:
    /*!
     * \brief
     * worksheetserver function callback.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    interpreter_variant operator()( function_parameter& parameters ) const;

    /*!
     * \brief
     * factory method.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_function_handler_type create( const std::string spreadsheet_function_name );

    /*!
     * \brief
     * determine the volatile flag for current workbook function
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    bool is_volatile() const;

    /*!
     * \brief
     * determine the view_independent flag for current workbook function
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    bool is_view_independent() const;

private:
    /*!
     * \brief
     * constructor
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    php_redirected_spreadsheet_function( const std::string& spreadsheet_function_name );

private:
    std::string m_spreadsheet_function_name;
};
