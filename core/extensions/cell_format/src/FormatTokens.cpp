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

#include "FormatTokens.hpp"
#include "FormatTokenVisitor.hpp"

namespace cell_format
{
    namespace tokens
    {

        AmPmToken::AmPmToken()
        {}

        AmPmToken::~AmPmToken()
        {}

        void AmPmToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void AmPmToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        SignToken::SignToken()
        {}

        SignToken::~SignToken()
        {}

        void SignToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void SignToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        MeasuredSpaceToken::MeasuredSpaceToken()
        {}

        MeasuredSpaceToken::~MeasuredSpaceToken()
        {}

        void MeasuredSpaceToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void MeasuredSpaceToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        DateFormatToken::DateFormatToken()
            : escaped( false )
        {}

        DateFormatToken::~DateFormatToken()
        {}

        void DateFormatToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void DateFormatToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        TimeFormatToken::TimeFormatToken()
        {}

        TimeFormatToken::~TimeFormatToken()
        {}

        void TimeFormatToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void TimeFormatToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        TimeSeparatorToken::TimeSeparatorToken()
        {}

        TimeSeparatorToken::~TimeSeparatorToken()
        {}

        void TimeSeparatorToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void TimeSeparatorToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        DateSeparatorToken::DateSeparatorToken()
            : localized( false )
            , escaped( false )
        {}

        DateSeparatorToken::~DateSeparatorToken()
        {}

        void DateSeparatorToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void DateSeparatorToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        NonFormatToken::NonFormatToken()
            : dont_escape( false )
        {}

        NonFormatToken::~NonFormatToken()
        {}

        void NonFormatToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void NonFormatToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        WhitespaceToken::WhitespaceToken()
        {}

        WhitespaceToken::~WhitespaceToken()
        {}

        void WhitespaceToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void WhitespaceToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        DecimalToken::DecimalToken()
        {}

        DecimalToken::~DecimalToken()
        {}

        void DecimalToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void DecimalToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        NumberFormatChar::NumberFormatChar()
        {}

        NumberFormatChar::~NumberFormatChar()
        {}

        void NumberFormatChar::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void NumberFormatChar::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        ExponentToken::ExponentToken()
            : always_sign( true )
            , lower_case( false )
        {}

        ExponentToken::~ExponentToken()
        {}

        void ExponentToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void ExponentToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        GeneralToken::GeneralToken()
        {}

        GeneralToken::~GeneralToken()
        {}

        void GeneralToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void GeneralToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        LocalizedToken::LocalizedToken()
        {}

        LocalizedToken::~LocalizedToken()
        {}


        void LocalizedToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void LocalizedToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        AtToken::AtToken()
        {}

        AtToken::~AtToken()
        {}

        void AtToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void AtToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        ThousandToken::ThousandToken()
        {}

        ThousandToken::~ThousandToken()
        {}

        void ThousandToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void ThousandToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        FractionIntegerToken::FractionIntegerToken()
            : have_thousand( false )
        {}

        FractionIntegerToken::~FractionIntegerToken()
        {}

        void FractionIntegerToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void FractionIntegerToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        FractionNumeratorToken::FractionNumeratorToken()
        {}

        FractionNumeratorToken::~FractionNumeratorToken()
        {}

        void FractionNumeratorToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void FractionNumeratorToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        FractionDenominatorToken::FractionDenominatorToken()
            : is_fixed( false )
            , fixed_value( 0 )
        {}

        FractionDenominatorToken::~FractionDenominatorToken()
        {}

        void FractionDenominatorToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void FractionDenominatorToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        PercentToken::PercentToken()
        {}

        PercentToken::~PercentToken()
        {}

        void PercentToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void PercentToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }

        FillToken::FillToken()
        {}

        FillToken::~FillToken()
        {}

        void FillToken::accept( Visitor& visitor )
        {
            visitor.visit( *this );
        }

        void FillToken::accept( ConstVisitor& visitor ) const
        {
            visitor.visit( *this );
        }
    }

}
