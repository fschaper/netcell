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

#include <memory>
#include "ControlTokens.hpp"
#include "CellFormatParseTree.hpp"

namespace cell_format
{
    /*! \brief Recognizes syntax elements and return parse tree.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class CellFormatParser
    {
    public:
        CellFormatParser( const ControlTokens& in_ct );
        ~CellFormatParser();

        /*! \brief Parse to tree. */
        void parse( CellFormatParseTree& tree, const std::string& s ) const;

        struct ParseRequest {
            ParseRequest( const CellFormatParser& parser, const std::string& s )
                : parser( parser )
                , s( s )
            {}

            /*! \brief Calls CellFormatParser::parse() */
            CellFormatParseTree& operator>> ( CellFormatParseTree& tree ) {
                parser.parse( tree, s );
                return tree;
            }

            ParseRequest& operator =( const ParseRequest& );

            const CellFormatParser& parser;
            const std::string& s;
        };

    private:
        class CellFormatParserImpl;

        /*! \todo Don't instatiate this too often. */
        std::auto_ptr<CellFormatParserImpl> m_impl;
    };

    inline CellFormatParser::ParseRequest operator >>( const std::string& s, const CellFormatParser& parser )
    {
        return CellFormatParser::ParseRequest( parser, s );
    }
}
