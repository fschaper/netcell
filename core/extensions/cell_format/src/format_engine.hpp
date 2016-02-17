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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once

#include <wss/i_format.hpp>
#include "CellValue.hpp"

class locale;

namespace cell_format
{

    class format_engine
        :   public i_format
    {
    private:
        CellValue cell_value_converter( const variant& value, const ::locale& l );
        static const locale& get_english();
    public:
        std::string formatted_value( session& s, const std::string& format, const variant& value );
        std::string formatted_color( session& s, const std::string& format, const variant& value );
        std::string formatted_value_locale( session& s, const std::string& format, const variant& value );
        std::string generic_format_string( session& s, const std::string& format );
        bool find_format( session& s, const std::string& formatted_value, variant& value, std::string& format );
        std::string default_format_string( const locale& l, const unsigned int format_id );
    };

}
