/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
*  Dragan Simic <dragan.simic@jedox.com>
*/

#ifndef _LOGGINGWRAPPERS
# define _LOGGINGWRAPPERS

// jlib
#undef ERROR // prevent the ERROR macro from overwriting the ERROR enum value used as LogLevel state.
//#include <jedox/log/Logging.hpp>
#include <wss/logger.hpp>
// helper macros for UI backend service
#define LOG_UI_BACKEND_ERROR(x) LOG_ERROR("[ui_backend] " << x)
#define LOG_UI_BACKEND_DEBUG(x) LOG_DEBUG("[ui_backend] " << x)
#define LOG_UI_BACKEND_INFO(x)  LOG_INFO("[ui_backend] " << x)

// helper macros for making the code more readable
#define LOG_CCMD_ERROR(f, m) LOG_ERROR("[ui_backend:ccmd] " << f << " " << m)
#define LOG_CCMD_DEBUG(f, m) LOG_DEBUG("[ui_backend:ccmd] " << f << " " << m)
#define LOG_CCMD_INFO(f, m)  LOG_INFO("[ui_backend:ccmd] " << f << " " << m)

#define COUT_NUMLIST2(x, y) x << "," << y
#define COUT_NUMLIST3(x, y, z) COUT_NUMLIST2(x, y) << "," << z
#define COUT_NUMLIST4(x1, y1, x2, y2) COUT_NUMLIST2(x1, y1) << "/" << COUT_NUMLIST2(x2, y2)
#define COUT_NUMLIST8(x1, y1, x2, y2, x3, y3, x4, y4) COUT_NUMLIST4(x1, y1, x2, y2) << ":" << COUT_NUMLIST2(x3, y3, x4, y4)

// in addition to the passed message, also echo the currently active session
#define CLOG_SESS_ERROR(f, m) LOG_ERROR("[ui_backend] [sid:" << (session ? session : "no-session-id" ) << "] " << f << " " << m)
#define CLOG_SESS_DEBUG(f, m) LOG_DEBUG("[ui_backend] [sid:" << (session ? session : "no-session-id" ) << "] " << f << " " << m)
#define CLOG_SESS_INFO(f, m) LOG_INFO("[ui_backend] [sid:" << (session ? session : "no-session-id" ) << "] " << f << " " << m)

// used for logging along with CLOG_SESS_INFO/CLOG_SESS_ERROR
#define OUT_POINT(p) (p).row << "," << (p).column
#define OUT_RANGE(r) OUT_POINT((r).upper_left) << "/" << OUT_POINT((r).lower_right)

#endif // _LOGGINGWRAPPERS
