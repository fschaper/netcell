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
*  \Author
*  Florian Schaper <florian.schaper@jedox.com>
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*  Vali Nitu <vali@yalos-solutions.com>
*/

#pragma once

#include "precompiled_header.hpp"
#include <wss/i_autofill_handler.hpp>
#include <wss/variant.hpp>
#include <wss/locale.hpp>


namespace autofill_internal
{

    class sequence_text_fill_handler : public i_autofill_handler
    {
    private:
        std::vector<std::string>    m_List;
        locale                      m_locale;
        int calls; // the number of calls of get_next for the actual row or column.
        int leadingEmpties; // the number of leading empty cells in the source.
        int closingEmpties; // the number of closing empty cells in the source.
        int texts; // the number of texts in the source.
        int step; // the step-size through the list (always positive).
        int stepEmpties; // the number of empty cells between two following texts (must be unique).
        int actualIndex; // the list-index of the actual value.
        bool prepare( const range& values, session& cx, int next, int vertical );
        variant get_next( const range& values, session& cx, int next, int vertical );

    public:
        sequence_text_fill_handler();
        void set_list( const std::vector<std::string>& List, locale& list_locale );
        bool handle_sequence( session& cx, const range& sequence, range& target );
    };

}



