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

// stl
#include <string>

// wss
#include "FormatToken.hpp"
#include "ControlTokens.hpp"

namespace cell_format
{
    namespace tokens
    {
        /*! \brief am/pm */
        class AmPmToken : public FormatToken
        {
        public:
            AmPmToken();
            virtual ~AmPmToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const AmPmToken& other ) const {
                return uppercase == other.uppercase
                       && short_form == other.short_form;
            }

            bool uppercase;
            bool short_form;
        };

        /*! \brief An element of a date/time format. */
        class DateFormatToken : public FormatToken
        {
        public:
            DateFormatToken();
            virtual ~DateFormatToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const DateFormatToken& other ) const {
                return type == other.type
                       && digit_count == other.digit_count;
            }

            enum Type {
                Year = ControlTokens::DateOrder::Year,
                Month = ControlTokens::DateOrder::Month,
                Day = ControlTokens::DateOrder::Day,
                Date1 = 7,
                Date2 = 8,
                Date3 = 9
            } type;

            unsigned int digit_count;
            bool escaped; // had been escaped using ""...""
        };

        /*! \brief An element of a time format. */
        class TimeFormatToken : public FormatToken
        {
        public:
            TimeFormatToken();
            virtual ~TimeFormatToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const TimeFormatToken& other ) const {
                return type == other.type
                       && digit_count == other.digit_count
                       && is_absolute == other.is_absolute;
            }

            enum Type {
                Hour, Minute, Second, SecondFraction
            } type;

            unsigned int digit_count;
            bool is_absolute; //! [hh] etc.
        };

        /*! \brief What the name suggests. */
        class TimeSeparatorToken : public FormatToken
        {
        public:
            TimeSeparatorToken();
            virtual ~TimeSeparatorToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const TimeSeparatorToken& other ) const {
                return value == other.value;
            }

            char value;
        };

        /*! \brief What the name suggests. */
        class DateSeparatorToken : public FormatToken
        {
        public:
            DateSeparatorToken();
            virtual ~DateSeparatorToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const DateSeparatorToken& other ) const {
                if ( localized ) {
                    return other.localized;
                } else {
                    return localized == other.localized && value == other.value;
                }
            }

            char value;
            bool localized; // value is default date separator (first in list), it will be localized
            bool escaped; // had been escaped using ""...""
        };

        /*! \brief What the name suggests. */
        class WhitespaceToken : public FormatToken
        {
        public:
            WhitespaceToken();
            virtual ~WhitespaceToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const WhitespaceToken& other ) const {
                return value == other.value;
            }

            std::string value;
        };

        /*! \brief What the name suggests. */
        class DecimalToken : public FormatToken
        {
        public:
            DecimalToken();
            virtual ~DecimalToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const DecimalToken& /*other*/ ) const {
                return true;
            }
        };

        /*! \brief What the name suggests. */
        class ExponentToken : public FormatToken
        {
        public:
            ExponentToken();
            virtual ~ExponentToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const ExponentToken& other ) const {
                return always_sign == other.always_sign
                       && lower_case == other.lower_case;
            }

            bool always_sign;
            bool lower_case;
        };

        /*! \brief What the name suggests. */
        class GeneralToken : public FormatToken
        {
        public:
            GeneralToken();
            virtual ~GeneralToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const GeneralToken& /*other*/ ) const {
                return true;
            }
        };

        /*! \brief What the name suggests. */
        class ThousandToken : public FormatToken
        {
        public:
            ThousandToken();
            virtual ~ThousandToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const ThousandToken& other ) const {
                return count == other.count;
            }

            int count;
        };

        /*! \brief What the name suggests (used in text formats). */
        class AtToken : public FormatToken
        {
        public:
            AtToken();
            virtual ~AtToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const AtToken& /*other*/ ) const {
                return true;
            }
        };

        /*! \brief What the name suggests (used in text formats). */
        class FractionIntegerToken : public FormatToken
        {
        public:
            FractionIntegerToken();
            virtual ~FractionIntegerToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const FractionIntegerToken& other ) const {
                return format == other.format
                       && have_thousand == other.have_thousand;
            }

            std::string format;
            bool have_thousand;
        };

        /*! \brief What the name suggests (used in text formats). */
        class FractionNumeratorToken : public FormatToken
        {
        public:
            FractionNumeratorToken();
            virtual ~FractionNumeratorToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const FractionNumeratorToken& other ) const {
                return format == other.format;
            }

            std::string format;
        };

        /*! \brief What the name suggests (used in text formats). */
        class FractionDenominatorToken : public FormatToken
        {
        public:
            FractionDenominatorToken();
            virtual ~FractionDenominatorToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const FractionDenominatorToken& other ) const {
                return format == other.format
                       && is_fixed == other.is_fixed
                       && fixed_value == other.fixed_value;
            }

            std::string format;
            bool is_fixed;
            int fixed_value;
        };

        /*! \brief An element of a number format. */
        class NumberFormatChar : public FormatToken
        {
        public:
            NumberFormatChar();
            virtual ~NumberFormatChar();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const NumberFormatChar& other ) const {
                return type == other.type;
            }

            char type; // one of #?0
        };

        /*! \brief A locale specific element of a format. */
        class LocalizedToken : public FormatToken
        {
        public:
            LocalizedToken();
            virtual ~LocalizedToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const LocalizedToken& other ) const {
                return type == other.type
                       && value == other.value;
            }

            enum Type {
                Currency, CurrencySpecial
            } type;

            std::string value;
        };

        /*! \brief What the name suggests. */
        class MeasuredSpaceToken : public FormatToken
        {
        public:
            MeasuredSpaceToken();
            virtual ~MeasuredSpaceToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const MeasuredSpaceToken& other ) const {
                return value == other.value;
            }

            char value;
        };

        /*! \brief A static element of a format without further meaning. */
        class NonFormatToken : public FormatToken
        {
        public:
            NonFormatToken();
            virtual ~NonFormatToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const NonFormatToken& other ) const {
                return value == other.value;
            }

            std::string value;
            bool dont_escape; // don't escape in CellFormatPrinter
        };

        /*! \brief What the name suggests. */
        class SignToken : public FormatToken
        {
        public:
            SignToken();
            virtual ~SignToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const SignToken& other ) const {
                return value == other.value;
            }

            char value;
        };

        /*! \brief What the name suggests. */
        class PercentToken : public FormatToken
        {
        public:
            PercentToken();
            virtual ~PercentToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const PercentToken& /*other*/ ) const {
                return true;
            }
        };

        /*! \brief What the name suggests. */
        class FillToken : public FormatToken
        {
        public:
            FillToken();
            virtual ~FillToken();

            virtual void accept( Visitor& visitor );
            virtual void accept( ConstVisitor& visitor ) const;

            inline bool operator==( const FillToken& other ) const {
                return value == other.value;
            }

            char value;
        };
    }
}
