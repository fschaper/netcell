/**
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
 *  Dragan Simic <dragan.simic@develabs.com>
 */

#ifndef _DEBUG_DEFINES
#   define _DEBUG_DEFINES

#   ifdef DEBUG_EXTENSION_PHP_MACRO_ENGINE
#       define ZEND_DEBUG 1
#       define DEBUG_EXTENSION_PHP_MACRO_ENGINE_PHP_FUNCTIONS_HANDLERS
#       define DEBUG_EXTENSION_PHP_MACRO_ENGINE_PHP_MODULE_INIT
#       define DEBUG_EXTENSION_PHP_MACRO_ENGINE_PHP_MODULE_EXTENSION
#       define DEBUG_EXTENSION_PHP_MACRO_ENGINE_PHP_MAGIC_METHODS
#       define DEBUG_EXTENSION_PHP_MACRO_ENGINE_PHP_CLASS_CONSTRUCTORS
#       define DEBUG_EXTENSION_PHP_MACRO_ENGINE_PHP_GLOBAL_FUNCTIONS
#
#       ifdef __unix__
#           define WSSME_TSRM_DEBUGFILE "/tmp/php_wssme_debug.log"
#       else
#           define WSSME_TSRM_DEBUGFILE "C:\\php_wssme_debug.log"
#       endif
#   else
#       define WSSME_TSRM_DEBUGFILE NULL
#   endif

#endif // _DEBUG_DEFINES
