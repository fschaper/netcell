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

#include "FormatSection.hpp"

namespace cell_format
{

    FormatSection::FormatSection()
    {}

    FormatSection::~FormatSection()
    {}

    void FormatSection::visit_tokens( tokens::Visitor& v )
    {
        for ( FormatSection::TokenList::iterator i = tokens.begin(), e = tokens.end(); i != e; ++i ) {
            i->accept( v );
        }
    }

    void FormatSection::visit_tokens( tokens::ConstVisitor& v ) const
    {
        for ( FormatSection::TokenList::const_iterator i = tokens.begin(), e = tokens.end(); i != e; ++i ) {
            i->accept( v );
        }
    }

    void FormatSection::purge()
    {
        using namespace tokens;

        tokens.erase_if( FormatToken::IsObsoleteFunctor() );
    }

    bool FormatSection::equals( const FormatSection& other ) const
    {
        if ( cond == other.cond && color == other.color ) {
            if ( tokens.size() != other.tokens.size() ) {
                return false;
            }

            for ( FormatSection::TokenList::const_iterator i = tokens.begin(), e = tokens.end(), j = other.tokens.begin(); i != e; ++i, ++j ) {
                if ( *i != *j ) {
                    return false;
                }
            }

            return true;
        } else {
            return false;
        }
    }
}
