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

// wss
#include "CellFormatPrinter.hpp"

#include "FormatTokenVisitor.hpp"
#include "FormatSections.hpp"

#include "ExceptionFactory.hpp"

// stl
#include <sstream>
#include <iomanip>
#include <cmath>

#include <float.h>

namespace cell_format
{
    using namespace tokens;

    CellFormatPrinter::CellFormatPrinter( const ControlTokens& out_ct )
        : m_out_ct( out_ct )
    {}

    CellFormatPrinter::~CellFormatPrinter()
    {}

    class CellFormatPrinter::BasicVisitor : public ConstVisitor
    {
    public:
        BasicVisitor( std::string& result, const ControlTokens& out_ct )
            : result( result )
            , out_ct( out_ct )
        {}

        virtual ~BasicVisitor()
        {}

        virtual void visit( const DateFormatToken& t ) {
            char c;
            ControlTokens::DateOrder::DateOrderPart dop;
            bool escape = false;

            switch ( t.type ) {
                case DateFormatToken::Day:
                case DateFormatToken::Month:
                case DateFormatToken::Year:
                    dop = static_cast<ControlTokens::DateOrder::DateOrderPart>( t.type );
                    escape = true;
                    break;
                case DateFormatToken::Date1:
                    dop = out_ct.date_order[0];
                    break;
                case DateFormatToken::Date2:
                    dop = out_ct.date_order[1];
                    break;
                case DateFormatToken::Date3:
                    dop = out_ct.date_order[2];
                    break;
                default:
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                    dop = static_cast<ControlTokens::DateOrder::DateOrderPart>( -1 ); // never reached
            }

            switch ( dop ) {
                case ControlTokens::DateOrder::Day:
                    c = out_ct.format_codes.day;
                    break;
                case ControlTokens::DateOrder::Month:
                    c = out_ct.format_codes.month;
                    break;
                case ControlTokens::DateOrder::Year:
                    c = out_ct.format_codes.year;
                    break;
                default:
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                    c = 0; // never reached
            }

            if ( escape ) {
                result += "\"\"";
            }

            for ( unsigned int i = 0; i < t.digit_count; ++i ) {
                result += c;
            }

            if ( escape ) {
                result += "\"\"";
            }
        }

        virtual void visit( const TimeFormatToken& t ) {
            char c;

            switch ( t.type ) {
                case TimeFormatToken::Hour:
                    c = out_ct.format_codes.hour;
                    break;
                case TimeFormatToken::Minute:
                    c = out_ct.format_codes.minute;
                    break;
                case TimeFormatToken::Second:
                    c = out_ct.format_codes.second;
                    break;
                case TimeFormatToken::SecondFraction:
                    result += out_ct.format_codes.decimal;
                    c = '0';
                    break;
                default:
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                    c = 0; // never reached
            }

            if ( t.is_absolute ) {
                result += '[';
            }

            for ( unsigned int i = 0; i < t.digit_count; ++i ) {
                result += c;
            }

            if ( t.is_absolute ) {
                result += ']';
            }
        }

        virtual void visit( const AmPmToken& t ) {
            if ( t.short_form ) {
                if ( t.uppercase ) {
                    result += "A/P";
                } else {
                    result += "a/p";
                }
            } else {
                if ( t.uppercase ) {
                    result += "AM/PM";
                } else {
                    result += "am/pm";
                }
            }
        }

        virtual void visit( const TimeSeparatorToken& t ) {
            result += t.value;
        }

        virtual void visit( const DateSeparatorToken& t ) {
            if ( t.localized ) {
                result += out_ct.format_codes.date_separators[0];
            } else {
                result += std::string( "\"\"" ) + t.value + "\"\"";
            }
        }

        virtual void visit( const NonFormatToken& t ) {
            if ( t.value.size() == 1 ) {
                if ( !t.dont_escape ) {
                    result += '\\';
                }

                result += t.value;
            } else {
                if ( !t.dont_escape ) {
                    result += '"';
                }

                result += t.value;

                if ( !t.dont_escape ) {
                    result += '"';
                }
            }
        }

        virtual void visit( const WhitespaceToken& t ) {
            result += t.value;
        }

        virtual void visit( const DecimalToken& /*t*/ ) {
            result += out_ct.format_codes.decimal;
        }

        virtual void visit( const ExponentToken& t ) {
            if ( t.lower_case ) {
                result += 'e';
            } else {
                result += 'E';
            }

            if ( t.always_sign ) {
                result += '+';
            } else {
                result += '-';
            }
        }

        virtual void visit( const GeneralToken& /*t*/ ) {
            result += out_ct.format_codes.general;
        }

        virtual void visit( const NumberFormatChar& t ) {
            result += t.type;
        }

        virtual void visit( const LocalizedToken& t ) {
            switch ( t.type ) {
                case LocalizedToken::Currency:
                    result += out_ct.format_codes.currency;
                    break;
                case LocalizedToken::CurrencySpecial:
                    /*! \todo implement? */
                    result += "[$";
                    result += t.value;
                    result += ']';
                    break;
                default:
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }
        }

        virtual void visit( const AtToken& /*t*/ ) {
            result += '@';
        }

        virtual void visit( const ThousandToken& /*t*/ ) {
            result += out_ct.format_codes.thousand_separator;
        }

        virtual void visit( const FractionIntegerToken& t ) {
            if ( t.have_thousand ) {
                if ( t.format.size() < 1 ) {
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                }

                std::string tmp = t.format;
                tmp.insert( tmp.size() - 1, 1, out_ct.format_codes.thousand_separator );

                result += tmp;
            } else {
                result += t.format;
            }
        }

        virtual void visit( const FractionNumeratorToken& t ) {
            result += t.format;
        }

        virtual void visit( const FractionDenominatorToken& t ) {
            result += t.format;
        }

        virtual void visit( const SignToken& t ) {
            result += t.value;
        }

        virtual void visit( const PercentToken& /*t*/ ) {
            result += '%';
        }

        virtual void visit( const FillToken& t ) {
            result += '*';
            result += t.value;
        }

        /*! \todo fully implement */
        virtual void visit( const MeasuredSpaceToken& t ) {
            result += '_';
            result += t.value;
        }

    protected:
        void warn() {
            ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
        }

        std::string& result;
        const ControlTokens& out_ct;

    private:
        BasicVisitor& operator=( const BasicVisitor& );
    };

    class CellFormatPrinter::DecimalVisitor : public CellFormatPrinter::BasicVisitor
    {
    public:
        DecimalVisitor( std::string& result, const ControlTokens& out_ct, const DecimalFormatSection& fmt )
            : BasicVisitor( result, out_ct )
            , m_fmt( fmt )
            , digits_left( fmt.digits.integer )
            , factor( fmt.factor )
            , factor_idx( static_cast<size_t>( -1 ) ) {
            if ( m_fmt.digits.integer < 1 && m_fmt.have_thousand_sep ) {
                ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }
        }

        virtual ~DecimalVisitor() {
            // factor is now calculated (only the part due to thousand separators remains)

            if ( std::fabs( factor - 1.0 ) > DBL_EPSILON ) {
                if ( factor_idx == static_cast<size_t>( -1 ) ) {
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                }

                double e = std::log( factor ) / std::log( 10.0 ); // neg. exponent
                if ( e < -DBL_EPSILON ) {
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                }

                int i = static_cast<int>( std::floor( e ) );

                size_t num_thousands = ( ( e - i ) > 0.5 ) ? i + 1 : i;

                if ( num_thousands % 3 != 0 ) {
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                } else {
                    num_thousands /= 3;
                }

                result.insert( factor_idx, num_thousands, out_ct.format_codes.thousand_separator );
            }
        }

        virtual void visit( const NumberFormatChar& t ) {
            if ( m_fmt.have_thousand_sep && ( 0 == ( digits_left % 3 ) ) && ( 0 != digits_left ) ) {
                result += out_ct.format_codes.thousand_separator;
            }

            BasicVisitor::visit( t );

            factor_idx = result.size();

            if ( digits_left > 0 ) {
                --digits_left;
            }
        }

        virtual void visit( const PercentToken& t ) {
            factor *= 100.0;

            BasicVisitor::visit( t );
        }

    protected:
        const DecimalFormatSection& m_fmt;
        size_t digits_left;
        double factor;
        size_t factor_idx;
    };

    class CellFormatPrinter::VisitorSelector : public FormatSectionConstVisitor
    {
    public:
        VisitorSelector( std::string& result, const ControlTokens& out_ct )
            : m_result( result )
            , m_out_ct( out_ct )
        {}

        ~VisitorSelector()
        {}

        void visit( const DecimalFormatSection& s ) {
            DecimalVisitor v( m_result, m_out_ct, s );

            s.visit_tokens( v );
        }

        void visit( const FractionFormatSection& s ) {
            BasicVisitor v( m_result, m_out_ct );

            s.visit_tokens( v );
        }

        void visit( const DateTimeFormatSection& s ) {
            BasicVisitor v( m_result, m_out_ct );

            s.visit_tokens( v );
        }

        void visit( const TextFormatSection& s ) {
            BasicVisitor v( m_result, m_out_ct );

            s.visit_tokens( v );
        }

        void visit( const EmptyFormatSection& /*s*/ ) {
            ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR ); // this should never be reached
        }

    protected:
        std::string& m_result;
        const ControlTokens& m_out_ct;

    private:
        VisitorSelector& operator=( const VisitorSelector& );
    };

    std::string CellFormatPrinter::process( const parsed_cell_format& format ) const
    {
        std::string result;

        VisitorSelector v( result, m_out_ct );

        for ( parsed_cell_format::FormatSections::const_iterator i = format.get_sections().begin(), e = format.get_sections().end(); i != e; ) {
            const FormatSection& fs = *i;

            if ( !format.is_conditionless() ) {
                if ( fs.cond.op != Condition::none ) {
                    result += fs.cond.to_string( m_out_ct );
                }
            }

            if ( fs.color > Color::_UNSET_ || fs.color < Color::Red ) {
                ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }

            if ( fs.color != Color::_UNSET_ ) {
                result += '[';
                result += m_out_ct.colors[fs.color];
                result += ']';
            }

            fs.accept( v );

            if ( ++i != e ) {
                result += m_out_ct.format_codes.list_separator;
            }
        }

        return result;
    }
}
