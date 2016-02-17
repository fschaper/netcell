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

#include "FormatToken.hpp"

#include "FormatTokenVisitor.hpp"

#include <typeinfo> // std::bad_cast

namespace cell_format
{
    namespace tokens
    {

        FormatToken::FormatToken()
            : m_obsolete( false )
        {}

        FormatToken::~FormatToken()
        {}

        void FormatToken::mark_obsolete()
        {
            m_obsolete = true;
        }

        bool FormatToken::is_obsolete() const
        {
            return m_obsolete;
        }

        class FormatToken::EqualityVisitor : public tokens::ConstVisitor
        {
        public:
            EqualityVisitor( const FormatToken& right )
                : right( right )
                , equal( false )
            {}

            virtual ~EqualityVisitor()
            {}

            virtual void visit( const DateFormatToken& t ) {
                equal = check_equal<DateFormatToken>( t );
            }

            virtual void visit( const TimeFormatToken& t ) {
                equal = check_equal<TimeFormatToken>( t );
            }

            virtual void visit( const AmPmToken& t ) {
                equal = check_equal<AmPmToken>( t );
            }

            virtual void visit( const TimeSeparatorToken& t ) {
                equal = check_equal<TimeSeparatorToken>( t );
            }

            virtual void visit( const DateSeparatorToken& t ) {
                equal = check_equal<DateSeparatorToken>( t );
            }

            virtual void visit( const NonFormatToken& t ) {
                equal = check_equal<NonFormatToken>( t );
            }

            virtual void visit( const WhitespaceToken& t ) {
                equal = check_equal<WhitespaceToken>( t );
            }

            virtual void visit( const DecimalToken& t ) {
                equal = check_equal<DecimalToken>( t );
            }

            virtual void visit( const ExponentToken& t ) {
                equal = check_equal<ExponentToken>( t );
            }

            virtual void visit( const GeneralToken& t ) {
                equal = check_equal<GeneralToken>( t );
            }

            virtual void visit( const NumberFormatChar& t ) {
                equal = check_equal<NumberFormatChar>( t );
            }

            virtual void visit( const LocalizedToken& t ) {
                equal = check_equal<LocalizedToken>( t );
            }

            virtual void visit( const AtToken& t ) {
                equal = check_equal<AtToken>( t );
            }

            virtual void visit( const ThousandToken& t ) {
                equal = check_equal<ThousandToken>( t );
            }

            virtual void visit( const FractionIntegerToken& t ) {
                equal = check_equal<FractionIntegerToken>( t );
            }

            virtual void visit( const FractionNumeratorToken& t ) {
                equal = check_equal<FractionNumeratorToken>( t );
            }

            virtual void visit( const FractionDenominatorToken& t ) {
                equal = check_equal<FractionDenominatorToken>( t );
            }

            virtual void visit( const MeasuredSpaceToken& t ) {
                equal = check_equal<MeasuredSpaceToken>( t );
            }

            virtual void visit( const SignToken& t ) {
                equal = check_equal<SignToken>( t );
            }

            virtual void visit( const PercentToken& t ) {
                equal = check_equal<PercentToken>( t );
            }

            virtual void visit( const FillToken& t ) {
                equal = check_equal<FillToken>( t );
            }

            operator bool() {
                return equal;
            }

        protected:
            template<typename T>
            bool check_equal( const T& left ) {
                try {
                    const T& r = dynamic_cast<const T&>( right );

                    return left == r;
                } catch ( std::bad_cast& ) {
                    return false;
                }
            }

            const FormatToken& right;
            bool equal;

        private:
            EqualityVisitor& operator=( const EqualityVisitor& );
        };

        bool FormatToken::operator ==( const FormatToken& other ) const
        {
            EqualityVisitor eqv( other );

            accept( eqv );

            return eqv;
        }
    }
}
