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

#define WSS_MAJOR_VERSION 3
#define WSS_MINOR_VERSION 2.0

#ifndef WSS_BUILD_VERSION
#	define WSS_BUILD_VERSION $WCREV$
#endif

#ifndef WSS_BUILD_DATE
#	ifdef WIN32
#		define WSS_BUILD_DATE $WCNOW=%Y%m%d%H%M%S00200$
#	else
#		define WSS_BUILD_DATE $WCNOW$
#	endif
#endif

#ifndef WSS_REPO_DATE
#	ifdef WIN32
#		define WSS_REPO_DATE $WCDATE=%Y%m%d%H%M%S00200$
#	else
#		define WSS_REPO_DATE $WCDATE$
#	endif
#endif

#define WSS_TEXTIFY_HELPER(arg) #arg
#define WSS_TEXTIFY(arg) WSS_TEXTIFY_HELPER(arg)

#define WSS_VERSION ((WSS_MAJOR_VERSION * 1000) + (WSS_MINOR_VERSION * 100) + (WSS_BUILD_VERSION / 10000))
#define WSS_MAIN_VERSION_STRING WSS_TEXTIFY( WSS_MAJOR_VERSION ) "." WSS_TEXTIFY( WSS_MINOR_VERSION )
#define WSS_VERSION_STRING WSS_MAIN_VERSION_STRING "." WSS_TEXTIFY( WSS_BUILD_VERSION )

#define WSS_BUILD_DATE_STRING WSS_TEXTIFY( WSS_BUILD_DATE )
#define WSS_REPO_DATE_STRING WSS_TEXTIFY( WSS_REPO_DATE )


