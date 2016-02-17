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
#include "CellFormatProcessor.hpp"

#include "FormatTokenVisitor.hpp"
#include "FormatSections.hpp"
#include "SerialDateTime.hpp"
#include "Fraction.hpp"

#include "ExceptionFactory.hpp"

// stl
#include <sstream>
#include <iomanip>

#include <cmath>
#include <float.h>
#include <limits.h>

// boost
#include <boost/lexical_cast.hpp>

namespace cell_format
{
    using namespace tokens;

    class CellFormatProcessor::BasicVisitor : public ConstVisitor
    {
    public:
        BasicVisitor( FormattedCell& result, const ControlTokens& out_ct )
            : result( result )
            , out_ct( out_ct )
        {}

        virtual ~BasicVisitor()
        {}

        virtual void visit( const DateFormatToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const TimeFormatToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const AmPmToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const TimeSeparatorToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const DateSeparatorToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const NonFormatToken& t ) {
            result.value += t.value;
        }

        virtual void visit( const WhitespaceToken& t ) {
            result.value += t.value;
        }

        virtual void visit( const DecimalToken& /*t*/ ) {
            result.value += out_ct.format_codes.decimal;
        }

        virtual void visit( const ExponentToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const GeneralToken& /*t*/ ) {
            ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
        }

        virtual void visit( const NumberFormatChar& /*t*/ ) {
            warn();
        }

        virtual void visit( const LocalizedToken& t ) {
            switch ( t.type ) {
                case LocalizedToken::Currency:
                    result.value += out_ct.format_codes.currency;
                    break;
                case LocalizedToken::CurrencySpecial:
                    /*! \todo implement? */
                    // advanced currency formats like [$xxx-yyy]
                    // xxx will be put out as constant by the current implementation
                {
                    std::string::size_type i = t.value.find( '-' );
                    result.value += ( i != std::string::npos ) ? t.value.substr( 0, i ) : t.value;
                }
                break;
                default:
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }
        }

        virtual void visit( const AtToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const ThousandToken& /*t*/ ) {
            result.value += out_ct.format_codes.thousand_separator;
        }

        virtual void visit( const FractionIntegerToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const FractionNumeratorToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const FractionDenominatorToken& /*t*/ ) {
            warn();
        }

        virtual void visit( const SignToken& t ) {
            result.value += t.value;
        }

        virtual void visit( const PercentToken& /*t*/ ) {
            result.value += '%';
        }

        virtual void visit( const FillToken& t ) {
            result.padding.idx = result.value.size();
            result.padding.value = t.value;
        }

        virtual void visit( const MeasuredSpaceToken& t ) {
            result.value += ' ';

            FormattedCell::MeasuredSpaceInfo msi;
            msi.idx = result.value.size() - 1;
            msi.width = t.value;

            result.spacing.push_back( msi );
        }

    protected:
        void warn() {
            ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
        }

        FormattedCell& result;
        const ControlTokens& out_ct;

        BasicVisitor& operator=( const BasicVisitor& );
    };

    class CellFormatProcessor::DecimalVisitor : public CellFormatProcessor::BasicVisitor
    {
    public:
        DecimalVisitor( FormattedCell& result, const ControlTokens& out_ct, double m_value, const DecimalFormatSection& s )
            : BasicVisitor( result, out_ct )
            , m_value( m_value )
            , s( s ) {
            using namespace std;

            string str;

            if ( s.digits.exp_integer > 0 ) {
                /* scientific format */
                ostringstream ostr;
                ostr << setiosflags( ios::scientific ) << setw( s.digits.integer + s.digits.fraction + 1 ) << setprecision( s.digits.fraction ) << fabs( m_value );
                str = ostr.str();
            } else {
                /* 'normal' format */
                m_value /= s.factor;

                ostringstream ostr;
                ostr << setiosflags( ios::fixed ) << setprecision( s.digits.fraction ) << fabs( m_value );
                str = ostr.str();
            }

            string::size_type i;
            if ( ( i = str.find( '.' ) ) == string::npos ) {
                if ( ( i = str.find( "e" ) ) == string::npos ) {
                    m_integer = str;
                } else {
                    m_integer = str.substr( 0, i );
                    m_exponent = str.substr( i + 2 );
                }
            } else {
                m_integer = str.substr( 0, i );
                str.erase( 0, i + 1 );

                if ( ( i = str.find( "e" ) ) == string::npos ) {
                    m_fraction = str;
                } else {
                    m_fraction = str.substr( 0, i );
                    m_exponent = str.substr( i + 2 );
                }
            }

            // strip leading zeroes
            if ( !m_exponent.empty() ) {
                while ( m_exponent[0] == '0' ) {
                    m_exponent.erase( 0, 1 );
                }
                if ( m_exponent.empty() ) {
                    m_exponent = "0";
                }
            }

            // replace trailing zeros with spaces
            if ( !m_fraction.empty() ) {
                string::size_type len = m_fraction.size();

                while ( len > 0 && m_fraction[len-1] == '0' ) {
                    --len;
                }

                m_fraction.resize( len );
                m_fraction.resize( s.digits.fraction, ' ' );
            }

            // output number sign
            if ( !s.suppress_sign && m_value < 0.0 ) {
                result.value += '-';
            }

            // no leading zeros required
            i = m_integer.find_first_of( "0123456789" );
            if ( i != string::npos && i == m_integer.size() - 1 )
                if ( m_integer[i] == '0' ) {
                    m_integer = "";
                }
        }

        ~DecimalVisitor()
        {}

        void visit( const ExponentToken& t ) {
            if ( t.lower_case ) {
                result.value += 'e';
            } else {
                result.value += 'E';
            }

            if ( fabs( m_value ) < 1.0 ) {
                result.value += '-';
            } else if ( t.always_sign ) {
                result.value += '+';
            }
        }

        void visit( const DecimalToken& t ) {
            // .0 style format
            trim_string( s.digits.integer, m_integer, s.have_thousand_sep );

            BasicVisitor::visit( t );
        }

        void visit( const NumberFormatChar& t ) {
            if ( m_digits_visited.integer < s.digits.integer ) {
                trim_string( s.digits.integer, m_integer, s.have_thousand_sep );

                if ( write( t.type, m_digits_visited.integer++, m_integer ) ) {
                    /* thousand sep. */
                    if ( s.have_thousand_sep && s.digits.exp_integer == 0
                            && ( ( s.digits.integer - m_digits_visited.integer ) % 3 == 0 )
                            //&& m_integer[m_digits_visited.integer-1] != ' ' // m_digits.integer > 0 holds
                            && m_digits_visited.integer != s.digits.integer ) {
                        result.value += out_ct.format_codes.thousand_separator;
                    }
                }
            } else if ( m_digits_visited.fraction < s.digits.fraction ) {
                write( t.type, m_digits_visited.fraction++, m_fraction );
            } else if ( m_digits_visited.exp_integer < s.digits.exp_integer ) {
                trim_string( s.digits.exp_integer, m_exponent );

                write( t.type, m_digits_visited.exp_integer++, m_exponent );
            } else {
                // exp_fraction
                write( t.type, 0, " " );
            }
        }

        // STL default format
        void visit( const GeneralToken& /*t*/ ) {
            using namespace std;

            ostringstream ostr;
            ostr << setprecision( 9 ) << fabs( m_value ); // 9 seems to be excel default
            string str = ostr.str();

            // localize
            string::size_type i = str.find( '.' );
            if ( i != string::npos ) {
                str[i] = out_ct.format_codes.decimal;
            }
            i = str.find( 'e' );
            if ( i != string::npos ) {
                str[i] = 'E';
            }

            result.value += str;
        }

    protected:
        //! trim string to new_length, output left-superfluent chars, insert spaces
        void trim_string( unsigned int new_length, std::string& str, bool thousand_sep = false ) {
            if ( new_length < str.size() ) {
                std::string::size_type diff = str.size() - new_length;

                while ( diff != 0 ) {
                    std::string::size_type n = ( ( diff + new_length ) % 3 == 0 )
                                               ? 3 : ( ( diff + new_length ) % 3 );

                    if ( diff < n ) {
                        result.value += str.substr( 0, diff );
                        str.erase( 0, diff );
                        break;
                    } else {
                        result.value += str.substr( 0, n );
                        str.erase( 0, n );

                        diff -= n;

                        if ( diff > 0 ) {
                            // thousand sep.
                            if ( thousand_sep && s.digits.exp_integer == 0 ) {
                                result.value += out_ct.format_codes.thousand_separator;
                            }
                        }
                    }
                }
            } else if ( new_length > str.size() ) {
                str.insert( 0, new_length - str.size(), ' ' );
            }
        }

        /* return true if a thousand-separator could be needed */
        bool write( char format_char, unsigned int digits_written, const std::string& data ) {
            switch ( format_char ) {
                case '#':
                    if ( data[digits_written] != ' ' ) {
                        result.value += data[digits_written];
                        return true;
                    }
                    break;
                case '?':
                    result.value += data[digits_written];
                    return data[digits_written] != ' ';
                case '0':
                    if ( data[digits_written] != ' ' ) {
                        result.value += data[digits_written];
                    } else {
                        result.value += '0';
                    }
                    return true;
            }

            return false;
        }

        DecimalFormatSection::DigitCounts m_digits_visited;

        double m_value;
        const DecimalFormatSection& s;
        std::string m_integer, m_fraction, m_exponent;

    private:
        DecimalVisitor& operator=( const DecimalVisitor& );
    };

    class CellFormatProcessor::FractionVisitor : public CellFormatProcessor::BasicVisitor
    {
    public:
        FractionVisitor( FormattedCell& result, const ControlTokens& out_ct, double value, const FractionFormatSection& fmt )
            : BasicVisitor( result, out_ct )
            , m_value( value )
            , m_fmt( fmt )
            , m_skip_ws( false )
            , m_skip_remainder( false )
            , m_recompute( true ) {
            //const FractionDenominatorToken& denom = dynamic_cast<const FractionDenominatorToken&>(fmt.tokens[fmt.denominator_idx]);

            if ( !fmt.suppress_sign && value < 0.0 ) {
                result.value += '-';
            }

            // percent etc.
            m_value *= m_fmt.factor;
        }

        ~FractionVisitor()
        {}

        void visit( const FractionIntegerToken& t ) {
            double val = floor( fabs( m_value ) );

            m_recompute = false;

            if ( val > UINT_MAX ) {
                ExceptionFactory::raise( cell_format_exception::E_VALUE_OUT_OF_RANGE );
            }


            const FractionDenominatorToken& denom = dynamic_cast<const FractionDenominatorToken&>( m_fmt.tokens[m_fmt.denominator_idx] );
            const bool have_integer = ( m_fmt.integer_idx != -1 );

            if ( denom.is_fixed ) {
                double val = ( have_integer ? ( fabs( m_value ) - floor( fabs( m_value ) ) ) : fabs( m_value ) ) * denom.fixed_value;

                if ( val > INT_MAX ) {
                    ExceptionFactory::raise( cell_format_exception::E_VALUE_OUT_OF_RANGE );
                }

                m_numerator = ( val - floor( val ) >= 0.5 ) ? ( ( int )val + 1 ) : ( ( int )val );

                m_denominator = boost::lexical_cast< int >( denom.format );
            } else {
                double max_denom = pow( 10.0, ( double )denom.format.size() ) - 1;

                Fraction::calculate( ( have_integer ? ( fabs( m_value ) - floor( fabs( m_value ) ) ) : fabs( m_value ) ), ( max_denom > INT_MAX ) ? INT_MAX : ( int )max_denom, m_numerator, m_denominator );
            }

            if ( m_numerator == m_denominator ) {
                val++;
                m_skip_ws = m_skip_remainder = true;
            } else if ( 0 == m_numerator ) {
                m_skip_ws = m_skip_remainder = true;
            }

            if ( 0 == ( unsigned int )val ) {
                m_skip_ws = true;
                if ( m_skip_remainder ) {
                    put_value( ( unsigned int )val, t.format, t.have_thousand );
                }
            } else {
                put_value( ( unsigned int )val, t.format, t.have_thousand );
            }
        }

        void visit( const FractionNumeratorToken& t ) {
            if ( m_skip_remainder ) {
                return;
            }

            if ( m_recompute ) {
                const FractionDenominatorToken& denom = dynamic_cast<const FractionDenominatorToken&>( m_fmt.tokens[m_fmt.denominator_idx] );
                const bool have_integer = ( m_fmt.integer_idx != -1 );

                if ( denom.is_fixed ) {
                    double val = ( have_integer ? ( fabs( m_value ) - floor( fabs( m_value ) ) ) : fabs( m_value ) ) * denom.fixed_value;

                    if ( val > INT_MAX ) {
                        ExceptionFactory::raise( cell_format_exception::E_VALUE_OUT_OF_RANGE );
                    }

                    m_numerator = ( val - floor( val ) >= 0.5 ) ? ( ( int )val + 1 ) : ( ( int )val );

                    m_denominator = boost::lexical_cast< int >( denom.format );
                } else {
                    double max_denom = pow( 10.0, ( double )denom.format.size() ) - 1;

                    Fraction::calculate( ( have_integer ? ( fabs( m_value ) - floor( fabs( m_value ) ) ) : fabs( m_value ) ), ( max_denom > INT_MAX ) ? INT_MAX : ( int )max_denom, m_numerator, m_denominator );
                }
            }

            put_value( m_numerator, t.format, false );
        }

        void visit( const FractionDenominatorToken& t ) {
            m_skip_ws = true;

            if ( m_skip_remainder ) {
                return;
            }

            if ( t.is_fixed ) {
                result.value += t.format;
            } else {
                put_value( m_denominator, t.format, false, true );
            }
        }

        void visit( const WhitespaceToken& t ) {
            if ( m_skip_ws ) {
                return;
            }

            result.value += t.value;
        }

        virtual void visit( const NonFormatToken& t ) {
            if ( m_skip_remainder ) {
                return;
            }

            result.value += t.value;
        }

    protected:
        void put_value( unsigned int val, const std::string& format, bool have_thousand, bool align_left = false ) {
            using namespace std;

            ostringstream ostr;
            ostr << setw( ( std::streamsize )format.size() ) << setiosflags( align_left ? ios::left : ios::right )  << val;
            string str = ostr.str();

            // handle overflow
            while ( format.size() < str.size() ) {
                result.value += str[0];
                str.erase( 0, 1 );
                if ( have_thousand && ( str.size() % 3 ) == 0 ) {
                    result.value += out_ct.format_codes.thousand_separator;
                }
            }

            // write output
            for ( string::const_iterator i = format.begin(), e = format.end(), j = str.begin(), f = str.end(), h = str.begin(); i != e; ++i, ++j ) {
                if ( have_thousand && ( ( f - j ) % 3 ) == 0 && j != h ) {
                    result.value += out_ct.format_codes.thousand_separator;
                }

                switch ( *i ) {
                    case '0':
                        if ( *j != ' ' ) {
                            result.value += *j;
                        } else {
                            result.value += '0';
                        }
                        break;
                    case '?':
                        result.value += *j;
                        break;
                    case '#':
                        if ( *j != ' ' ) {
                            result.value += *j;
                        }
                        break;
                    default:
                        ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                }
            }
        }

        double      m_value;
        int         m_numerator;
        int         m_denominator;

        const       FractionFormatSection& m_fmt;
        bool        m_skip_ws;
        bool        m_skip_remainder;
        bool        m_recompute;
    private:
        FractionVisitor& operator=( const FractionVisitor& );
    };

    class CellFormatProcessor::TextVisitor : public CellFormatProcessor::BasicVisitor
    {
    public:
        TextVisitor( FormattedCell& result, const ControlTokens& out_ct, const std::string& value )
            : BasicVisitor( result, out_ct )
            , m_value( value )
        {}

        ~TextVisitor()
        {}

        void visit( const AtToken& /*t*/ ) {
            result.value += m_value;
        }

    protected:
        const std::string m_value;

    private:
        TextVisitor& operator=( const TextVisitor& );
    };

    class CellFormatProcessor::DateTimeVisitor : public CellFormatProcessor::BasicVisitor
    {
    public:
        DateTimeVisitor( FormattedCell& result, const ControlTokens& out_ct, double value, const DateTimeFormatSection& s )
            : BasicVisitor( result, out_ct )
            , m_ns( SerialDateTime( value ).get_non_serial() )
            , m_fmt( s )
            , m_serial( value )
        {}

        ~DateTimeVisitor()
        {}

        void visit( const DateFormatToken& t ) {
            using namespace std;

            if ( is_token_type( t, DateFormatToken::Year ) ) {
                unsigned int val = m_ns.Y;

                if ( t.digit_count == 2 ) {
                    val %= 100;
                } else if ( t.digit_count != 4 ) {
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                }

                ostringstream ostr;
                ostr << setfill( '0' ) << setw( t.digit_count ) << val;
                result.value += ostr.str();
            } else if ( is_token_type( t, DateFormatToken::Month ) || is_token_type( t, DateFormatToken::Day ) ) {
                if ( t.digit_count <= 2 ) {
                    unsigned int val;

                    if ( is_token_type( t, DateFormatToken::Month ) ) {
                        val = m_ns.M;
                    } else {
                        val = m_ns.D;
                    }

                    ostringstream ostr;
                    ostr << setfill( '0' ) << setw( t.digit_count ) << val;
                    result.value += ostr.str();
                } else {
                    string::size_type len = result.value.size();

                    if ( is_token_type( t, DateFormatToken::Month ) ) {
                        if ( t.digit_count == 3 ) {
                            result.value += out_ct.months[m_ns.M-1].short_name;
                        } else if ( t.digit_count == 5 ) {
                            result.value += out_ct.months[m_ns.M-1].short_name[0];
                        } else {
                            result.value += out_ct.months[m_ns.M-1].long_name;
                        }
                    } else {
                        if ( t.digit_count == 3 ) {
                            result.value += out_ct.days_of_week[SerialDateTime( m_serial ).get_day_of_week()].short_name;
                        } else {
                            result.value += out_ct.days_of_week[SerialDateTime( m_serial ).get_day_of_week()].long_name;
                        }
                    }

                    // strings should begin with capital letter
                    result.value[len] = toupper( result.value[len] );
                }
            } else {
                ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }
        }

        void visit( const TimeFormatToken& t ) {
            double val = 0.0;

            if ( t.is_absolute ) {
                if ( t.type == TimeFormatToken::Hour || t.type == TimeFormatToken::Minute || t.type == TimeFormatToken::Second ) {
                    val = ( ( int )m_serial * 24 ) + m_ns.h;

                    if ( t.type == TimeFormatToken::Minute || t.type == TimeFormatToken::Second ) {
                        val *= 60;
                        val += m_ns.m;

                        if ( t.type == TimeFormatToken::Second ) {
                            val *= 60;
                            val += m_ns.s;
                        }
                    }
                } else {
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                }
            } else {
                switch ( t.type ) {
                    case TimeFormatToken::Hour:
                        val = m_ns.h;
                        if ( m_fmt.have_ampm ) {
                            if (  m_ns.h > 12 ) {
                                val -= 12;
                            } else if ( 0 == val ) {
                                val += 12;
                            }
                        }
                        break;
                    case TimeFormatToken::Minute:
                        val = m_ns.m;
                        break;
                    case TimeFormatToken::Second:
                        val = m_ns.s;
                        if ( m_fmt.have_second_fraction ) {
                            val = floor( val );
                        }
                        break;
                    case TimeFormatToken::SecondFraction:
                        result.value += out_ct.format_codes.decimal;
                        val = m_ns.s - floor( m_ns.s );
                        for ( unsigned int i = 0; i < t.digit_count; ++i ) {
                            val *= 10;
                        }
                        break;
                    default:
                        ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                }
            }

            using namespace std;

            ostringstream ostr;
            ostr << setiosflags( ios::fixed ) << resetiosflags( ios::showpoint )
                 << setprecision( 0 ) << setfill( '0' ) << setw( t.digit_count ) << val;
            result.value += ostr.str();
        }

        void visit( const AmPmToken& t ) {
            if ( m_ns.h < 12 ) {
                if ( t.uppercase ) {
                    if ( t.short_form ) {
                        result.value += 'A';
                    } else {
                        result.value += "AM";
                    }
                } else {
                    if ( t.short_form ) {
                        result.value += 'a';
                    } else {
                        result.value += "am";
                    }
                }
            } else {
                if ( t.uppercase ) {
                    if ( t.short_form ) {
                        result.value += 'P';
                    } else {
                        result.value += "PM";
                    }
                } else {
                    if ( t.short_form ) {
                        result.value += 'p';
                    } else {
                        result.value += "pm";
                    }
                }
            }
        }

        void visit( const TimeSeparatorToken& t ) {
            result.value += t.value;
        }

        void visit( const DateSeparatorToken& t ) {
            if ( t.localized ) {
                result.value += out_ct.format_codes.date_separators[0];
            } else {
                result.value += t.value;
            }
        }

    private:
        bool is_token_type( const DateFormatToken& dt, DateFormatToken::Type type ) {
            return ( dt.type == type )
                   || ( dt.type == DateFormatToken::Date1 && static_cast<cell_format::tokens::DateFormatToken::Type>( out_ct.date_order[0] ) == type )
                   || ( dt.type == DateFormatToken::Date2 && static_cast<cell_format::tokens::DateFormatToken::Type>( out_ct.date_order[1] ) == type )
                   || ( dt.type == DateFormatToken::Date3 && static_cast<cell_format::tokens::DateFormatToken::Type>( out_ct.date_order[2] ) == type );
        }

        const SerialDateTime::NonSerial m_ns;
        const DateTimeFormatSection& m_fmt;
        double m_serial;

        DateTimeVisitor& operator=( const DateTimeVisitor& );
    };

    class CellFormatProcessor::GenericVisitor : public CellFormatProcessor::BasicVisitor
    {
    public:
        GenericVisitor( FormattedCell& result, const ControlTokens& out_ct )
            : BasicVisitor( result, out_ct )
        {}

        ~GenericVisitor()
        {}

    private:
        GenericVisitor& operator=( const GenericVisitor& );
    };

    class CellFormatProcessor::VisitorSelector : public FormatSectionConstVisitor
    {
    public:
        VisitorSelector( FormattedCell& result, const ControlTokens& out_ct, const CellValue& value )
            : m_format_matched( false )
            , m_result( result )
            , m_out_ct( out_ct )
            , m_value( value ) {}

        ~VisitorSelector()
        {}

        void visit( const DecimalFormatSection& s ) {
            if ( m_value.get_type() == CellValue::Number && s.cond.matches( m_value.get_number() ) ) {
                DecimalVisitor v( m_result, m_out_ct, m_value.get_number(), s );
                s.visit_tokens( v );
                m_format_matched = true;
            }
        }

        void visit( const FractionFormatSection& s ) {
            if ( m_value.get_type() == CellValue::Number && s.cond.matches( m_value.get_number() ) ) {
                FractionVisitor v( m_result, m_out_ct, m_value.get_number(), s );
                s.visit_tokens( v );
                m_format_matched = true;
            }
        }

        void visit( const DateTimeFormatSection& s ) {
            if ( m_value.get_type() == CellValue::Number && s.cond.matches( m_value.get_number() ) ) {
                DateTimeVisitor v( m_result, m_out_ct, m_value.get_number(), s );
                s.visit_tokens( v );
                m_format_matched = true;
            }
        }

        void visit( const TextFormatSection& s ) {
            if ( m_value.get_type() == CellValue::String ) {
                TextVisitor v( m_result, m_out_ct, m_value.get_string() );
                s.visit_tokens( v );
                m_format_matched = true;
            }
        }

        void visit( const EmptyFormatSection& /*s*/ ) {
            ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR ); // this should never be reached
        }

        bool formatApplied() const {
            return m_format_matched;
        }

    protected:
        bool m_format_matched;
        FormattedCell& m_result;
        const ControlTokens& m_out_ct;
        const CellValue& m_value;

    private:
        VisitorSelector& operator=( const VisitorSelector& );
    };

    CellFormatProcessor::CellFormatProcessor( const ControlTokens& out_ct )
        : m_out_ct( out_ct )
    {}

    CellFormatProcessor::~CellFormatProcessor()
    {}

    FormattedCell CellFormatProcessor::process( const parsed_cell_format& format, const CellValue& val ) const
    {
        FormattedCell result;

        VisitorSelector v( result, m_out_ct, val );

        for ( parsed_cell_format::FormatSections::const_iterator i = format.get_sections().begin(), e = format.get_sections().end(); i != e; ++i ) {
            i->accept( v );
            if ( v.formatApplied() ) {
                result.color = i->color;
                break;
            }
        }

        // default string format
        if ( !v.formatApplied() ) {
            if ( val.get_type() == CellValue::String ) {
                result.value = val.get_string();
            } else {
                ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );    // should never happen
            }
        }

        return result;
    }
}
