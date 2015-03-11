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


namespace autofill_internal
{

    class sequence_number_fill_handler : public i_autofill_handler
    {
    private:
        int calls; // the number of calls of get_next for the actual row or column.
        int empties; // the number of filled in empty cells for the actual row or column.
        int leadingEmpties; // the number of leading empty cells in the source.
        int closingEmpties; // the number of closing empty cells in the source.
        int nums; // the number of numerical values in the source.
        double ym; // the arithmetical mean of the numerical values in the source.
        double diff; // the difference of the numerical values in the source.
        int stepEmpties; // the number of empty cells between two following numbers.
        bool regular; // flag if inner empty cells follow regularly.
        double actualNumber; // the actual number.
        double a; // the slope.
        double axb; // the slope multiplied with the zero point.
        double variance; // the variance of the slope.
        void prepare( const range& values, session& cx, int next, int vertical );
        variant get_next( const range& values, session& cx, int next, int vertical );



    public:
        sequence_number_fill_handler();
        bool handle_sequence( session& cx, const range& sequence, range& target );
    };

}



