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

// wss
#include "FormatTokens.hpp"

namespace cell_format
{
    namespace tokens
    {

        /*! \brief FormatToken visitor.
        *
        *  \author Marek Pikulski <marek.pikulski@jedox.com>
        */
        class Visitor
        {
        public:
            virtual ~Visitor()
            {}

            virtual void visit( DateFormatToken& t ) = 0;

            virtual void visit( TimeFormatToken& t ) = 0;

            virtual void visit( AmPmToken& t ) = 0;

            virtual void visit( TimeSeparatorToken& t ) = 0;

            virtual void visit( DateSeparatorToken& t ) = 0;

            virtual void visit( NonFormatToken& t ) = 0;

            virtual void visit( WhitespaceToken& t ) = 0;

            virtual void visit( DecimalToken& t ) = 0;

            virtual void visit( ExponentToken& t ) = 0;

            virtual void visit( GeneralToken& t ) = 0;

            virtual void visit( NumberFormatChar& t ) = 0;

            virtual void visit( LocalizedToken& t ) = 0;

            virtual void visit( AtToken& t ) = 0;

            virtual void visit( ThousandToken& t ) = 0;

            virtual void visit( FractionIntegerToken& t ) = 0;

            virtual void visit( FractionNumeratorToken& t ) = 0;

            virtual void visit( FractionDenominatorToken& t ) = 0;

            virtual void visit( MeasuredSpaceToken& t ) = 0;

            virtual void visit( SignToken& t ) = 0;

            virtual void visit( PercentToken& t ) = 0;

            virtual void visit( FillToken& t ) = 0;
        };

        /*! \brief const FormatToken visitor.
        *
        *  \author Marek Pikulski <marek.pikulski@jedox.com>
        */
        class ConstVisitor
        {
        public:
            virtual ~ConstVisitor()
            {}

            virtual void visit( const DateFormatToken& t ) = 0;

            virtual void visit( const TimeFormatToken& t ) = 0;

            virtual void visit( const AmPmToken& t ) = 0;

            virtual void visit( const TimeSeparatorToken& t ) = 0;

            virtual void visit( const DateSeparatorToken& t ) = 0;

            virtual void visit( const NonFormatToken& t ) = 0;

            virtual void visit( const WhitespaceToken& t ) = 0;

            virtual void visit( const DecimalToken& t ) = 0;

            virtual void visit( const ExponentToken& t ) = 0;

            virtual void visit( const GeneralToken& t ) = 0;

            virtual void visit( const NumberFormatChar& t ) = 0;

            virtual void visit( const LocalizedToken& t ) = 0;

            virtual void visit( const AtToken& t ) = 0;

            virtual void visit( const ThousandToken& t ) = 0;

            virtual void visit( const FractionIntegerToken& t ) = 0;

            virtual void visit( const FractionNumeratorToken& t ) = 0;

            virtual void visit( const FractionDenominatorToken& t ) = 0;

            virtual void visit( const MeasuredSpaceToken& t ) = 0;

            virtual void visit( const SignToken& t ) = 0;

            virtual void visit( const PercentToken& t ) = 0;

            virtual void visit( const FillToken& t ) = 0;
        };

    }
}
