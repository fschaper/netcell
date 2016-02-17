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

#include <wss/variant.hpp>
#include <wss/locale.hpp>
#include "php_includes.hpp"

/*!
 * \brief
 * convert values between zend and worksheetserver format.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class value_converter
{
public:
    /*!
     * \brief
     * convert variant to zend value format.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void operator ()( const ::locale& l, zval* zend_value, const variant& value ) const;

    /*!
     * \brief
     * convert zend value to variant format.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant operator()( zval* zend_value TSRMLS_DC, const variant& v = variant() );

private:
    /*!
     * \brief
     * internal helper function for zend hashtable traversion.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static int hashtable_callback( void* zend_value, void* wss_value TSRMLS_DC );

    /*!
     * \brief
     * handle value-array to zend zval array conversion
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void operator ()( zval* zend_value, const variant& value ) const;

    /*!
     * \brief
     * handle value-array to zend zval  matrix conversion
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void operator ()( zval* zend_value, const variant& value, size_t col_size ) const;
};
