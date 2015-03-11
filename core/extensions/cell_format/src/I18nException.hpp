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

#include <wss/wss_runtime_exception.hpp>
#include "Exception.hpp"

namespace cell_format
{

    /*! \brief Internationalization exception.
    *
    * This exception will be raised if some locale handling routine fails.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class I18nException : public wss_runtime_exception
    {
    public:
        ~I18nException() throw() {}

        std::string get_type() const {
            return "I18nException";
        }

        enum Code {
            E_XML_FILE_OPEN_FAILED,
            E_XML_FILE_PARSE,
            E_XML_UNKNOWN_BASE_LOCALE,
            E_UNKNOWN_LOCALE_REQUESTED,
            E_UNKNOWN_FORMAT_ID_REQUESTED,
        };

        int get_code() const {
            return code;
        }

        virtual int error_code() const {
            return 0x003800;
        }
        virtual std::string haiku() const {
            return std::string( "" );
        }
    protected:
        I18nException( const Code& code )
            : code( code )
        {}

        Code code;

        friend class ExceptionFactory;
    };
}
