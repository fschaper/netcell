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

#pragma once

#include "Exception.hpp"

namespace cell_format
{
    /*! \brief Cell format exception.
    *
    * This exception will be raised if something goes wrong inside CellFormatter.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class cell_format_exception : public Exception
    {
    public:
        ~cell_format_exception() throw();

        /*! \brief Error codes. */
        enum Code {
            E_UNKNOWN_ERROR,
            E_DATETIME_TOKEN_FOLLOWED_BY_ZERO,
            E_PARSE_FAILED,
            E_TOO_MANY_CONDITIONS,
            E_TOO_MANY_COLORS,
            E_INVALID_CONDITIONS,
            E_ABSOLUTETIME_AMPM_CONFLICT,
            E_VALUE_OUT_OF_RANGE,
            E_INVALID_VALUE_TYPE,
            E_SECOND_FRACTION_TOO_LONG
        };

        std::string get_type() const;

        std::string get_message() const;

        int get_code() const;

    protected:
        cell_format_exception( const Code& code );

        Code m_code;

        friend class ExceptionFactory;
    };
}
