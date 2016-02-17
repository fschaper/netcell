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

#include "parsed_cell_format.hpp"
#include "CellFormatParseTree.hpp"
#include "ControlTokens.hpp"

namespace cell_format
{

    /*! \brief Converts a CellFormatParseTree into a parsed_cell_format.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class CellFormatParseTreeConverter
    {
    public:
        CellFormatParseTreeConverter( const ControlTokens& in_ct );
        ~CellFormatParseTreeConverter();

        struct conversion_request {
            conversion_request( const CellFormatParseTreeConverter& conv, const CellFormatParseTree& tree )
                : conv( conv )
                , tree( tree )
            {}

            const CellFormatParseTreeConverter& conv;
            const CellFormatParseTree& tree;

            conversion_request& operator =( const conversion_request& );

            parsed_cell_format& operator>>( parsed_cell_format& fmt ) {
                conv.convert( fmt, tree );
                return fmt;
            }
        };

        /*! \brief main method */
        void convert( parsed_cell_format& result, const CellFormatParseTree& tree ) const;

    private:
        CellFormatParseTreeConverter& operator =( const CellFormatParseTreeConverter& );

        static void check_conditions( parsed_cell_format& result, bool is_conditionless );

        const ControlTokens& m_in_ct;
    };

    inline CellFormatParseTreeConverter::conversion_request operator>> ( const CellFormatParseTree& tree, const CellFormatParseTreeConverter& m )
    {
        return CellFormatParseTreeConverter::conversion_request( m, tree );
    }
}
