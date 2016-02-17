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

// boost
#include <boost/ptr_container/ptr_vector.hpp>

// wss
#include "FormatToken.hpp"
#include "Color.hpp"
#include "Condition.hpp"


namespace cell_format
{

    class FormatSectionVisitor;
    class FormatSectionConstVisitor;

    /*! A section of a cell format.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    struct FormatSection {
        FormatSection();
        virtual ~FormatSection();

        void visit_tokens( tokens::Visitor& v );
        void visit_tokens( tokens::ConstVisitor& v ) const;

        virtual void accept( FormatSectionVisitor& v ) = 0;
        virtual void accept( FormatSectionConstVisitor& v ) const = 0;

        /*! drop elements marked obsolete */
        void purge();

        // conditional format section is greater
        inline bool operator> ( const FormatSection& right ) const {
            return ! operator< ( right );
        }

        inline bool operator< ( const FormatSection& right ) const {
            return ( this->cond.op == Condition::none && right.cond.op != Condition::none );
        }

        virtual bool operator==( const FormatSection& other ) const = 0;

        /*! negation of == */
        bool operator!=( const FormatSection& other ) const {
            return !operator==( other );
        }

        enum Type {
            DateTime
            , Decimal
            , Fraction
            , Text
            , Empty
        };

        virtual Type get_type() const = 0;

        Condition cond;

        Color color;

        typedef boost::ptr_vector<tokens::FormatToken> TokenList;
        TokenList tokens;

    protected:
        class EqualVisitor;

        bool equals( const FormatSection& other ) const;
    };
}
