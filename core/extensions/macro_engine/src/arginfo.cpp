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

#include "precompiled_header.hpp"
#define NEEDS_SOCKLEN_T
#include "php_includes.hpp"

ZEND_BEGIN_ARG_INFO_EX( wss_no_args, 0, ZEND_RETURN_VALUE, 0 )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX( wss_one_arg, 0, ZEND_RETURN_VALUE, 1 )
ZEND_ARG_PASS_INFO( 0 )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX( wss_two_args, 0, ZEND_RETURN_VALUE, 2 )
ZEND_ARG_PASS_INFO( 0 )
ZEND_ARG_PASS_INFO( 0 )
ZEND_END_ARG_INFO()
