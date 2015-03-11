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
 *  Marek Pikulski <marek.pikulski@jedox.com>
 */

#include "CellFormatMessagePool.hpp"

namespace cell_format
{

    CellFormatMessagePool::CellFormatMessagePool()
    {
        init();
    }

    CellFormatMessagePool::~CellFormatMessagePool()
    {}

    void CellFormatMessagePool::init()
    {
        m_msg_pool[cell_format_exception::E_UNKNOWN_ERROR] = "Unknown error.";
        m_msg_pool[cell_format_exception::E_DATETIME_TOKEN_FOLLOWED_BY_ZERO] = "A date/time format token may not be followed by \"0\".";
        m_msg_pool[cell_format_exception::E_PARSE_FAILED] = "The format string could not be parsed.";
        m_msg_pool[cell_format_exception::E_TOO_MANY_CONDITIONS] = "Too many conditions specified.";
        m_msg_pool[cell_format_exception::E_TOO_MANY_COLORS] = "Too many colors specified.";
        m_msg_pool[cell_format_exception::E_INVALID_CONDITIONS] = "Error parsing conditional format. Check format section types (text vs. non-text) and assure that your conditions cover every numeric value.";
        m_msg_pool[cell_format_exception::E_ABSOLUTETIME_AMPM_CONFLICT] = "You cannot use absolute time formatting and AM/PM simultaneously.";
        m_msg_pool[cell_format_exception::E_VALUE_OUT_OF_RANGE] = "A value is to big to be represented in the requested format.";
        m_msg_pool[cell_format_exception::E_INVALID_VALUE_TYPE] = "A value is of supported type.";
        m_msg_pool[cell_format_exception::E_SECOND_FRACTION_TOO_LONG] = "The fractional second part of a date-time format cannot exceed 4 digits.";
    }

    const CellFormatMessagePool& CellFormatMessagePool::getInstance()
    {
        static CellFormatMessagePool me;
        return me;
    }

}
