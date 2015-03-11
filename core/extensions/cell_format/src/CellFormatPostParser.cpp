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

#include "CellFormatPostParser.hpp"

#include "FormatTokenVisitor.hpp"
#include "ExceptionFactory.hpp"
#include "FormatSections.hpp"

#include <vector>
#include <limits.h>

namespace cell_format
{
    using namespace tokens;

    /*! \brief Discards all nodes.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class CellFormatPostParser::SimpleVisitor : public Visitor
    {
    public:
        SimpleVisitor()
            : m_idx( -1 )
        {}

        virtual ~SimpleVisitor()
        {}

        virtual void visit( DateFormatToken& ) {
            ++m_idx;
        }

        virtual void visit( TimeFormatToken& ) {
            ++m_idx;
        }

        virtual void visit( AmPmToken& ) {
            ++m_idx;
        }

        virtual void visit( TimeSeparatorToken& ) {
            ++m_idx;
        }

        virtual void visit( DateSeparatorToken& ) {
            ++m_idx;
        }

        virtual void visit( NonFormatToken& ) {
            ++m_idx;
        }

        virtual void visit( WhitespaceToken& ) {
            ++m_idx;
        }

        virtual void visit( DecimalToken& ) {
            ++m_idx;
        }

        virtual void visit( ExponentToken& ) {
            ++m_idx;
        }

        virtual void visit( GeneralToken& ) {
            ++m_idx;
        }

        virtual void visit( NumberFormatChar& ) {
            ++m_idx;
        }

        virtual void visit( LocalizedToken& ) {
            ++m_idx;
        }

        virtual void visit( AtToken& ) {
            ++m_idx;
        }

        virtual void visit( ThousandToken& ) {
            ++m_idx;
        }

        virtual void visit( FractionIntegerToken& ) {
            ++m_idx;
        }

        virtual void visit( FractionNumeratorToken& ) {
            ++m_idx;
        }

        virtual void visit( FractionDenominatorToken& ) {
            ++m_idx;
        }

        virtual void visit( MeasuredSpaceToken& ) {
            ++m_idx;
        }

        virtual void visit( SignToken& ) {
            ++m_idx;
        }

        virtual void visit( PercentToken& ) {
            ++m_idx;
        }

        virtual void visit( FillToken& ) {
            ++m_idx;
        }

    protected:
        int m_idx;
    };

    /*!
    * Tags fraction formats with additional information.
    * - check if denominator is a "true number" and setup numerator adequately
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class CellFormatPostParser::FractionVisitor : public CellFormatPostParser::SimpleVisitor
    {
    public:
        FractionVisitor( FractionFormatSection& fmt )
            : m_fmt( fmt ) {

            if ( m_fmt.cond.op != Condition::none && m_fmt.cond.operand == 0.0 ) {
                m_fmt.suppress_sign = true;
            }
        }

        virtual ~FractionVisitor()
        {}

        virtual void visit( PercentToken& t ) {
            SimpleVisitor::visit( t );

            m_fmt.factor *= 100.0;
        }

        virtual void visit( FractionIntegerToken& t ) {
            SimpleVisitor::visit( t );

            m_fmt.integer_idx = m_idx;
        }

        virtual void visit( FractionNumeratorToken& t ) {
            SimpleVisitor::visit( t );

            m_fmt.numerator_idx = m_idx;
        }

        virtual void visit( FractionDenominatorToken& t ) {
            SimpleVisitor::visit( t );

            int denom = atoi( t.format.c_str() );
            if ( denom == 0 ) {
                t.is_fixed = false;
            } else {
                if ( denom == INT_MAX || denom == INT_MIN ) {
                    ExceptionFactory::raise( cell_format_exception::E_VALUE_OUT_OF_RANGE );
                }

                t.is_fixed = true;
                t.fixed_value = denom;
            }

            m_fmt.denominator_idx = m_idx;
        }

    private:
        FractionVisitor& operator =( const FractionVisitor& );

        FractionFormatSection& m_fmt;
    };

    /*!
    * - Tags decimal formats with additional information.
    * - Handles thousand-separators "[0#?],[0#?]"
    *       vs. m_factor "[0#?],[~0#?]" (<- after integer and/or fraction part only!)
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class CellFormatPostParser::DecimalVisitor : public CellFormatPostParser::SimpleVisitor
    {
    public:
        DecimalVisitor( DecimalFormatSection& fmt )
            : m_current_part( Integer )
            , m_last_num_char_idx( -1 )
            , m_last_thsnd_idx( -1 )
            , m_fmt( fmt )
            , m_factor( 1.0 ) {
            if ( m_fmt.cond.op != Condition::none && m_fmt.cond.operand == 0.0 ) {
                m_fmt.suppress_sign = true;
            }
        }

        virtual ~DecimalVisitor() {
            if ( m_last_thsnd_idx != -1 ) {
                // got a factor control sequence
                handle_factor();
            }

            // update
            m_fmt.factor = ( m_factor == 0.0 ? 1.0 : m_factor );
        }

        virtual void visit( PercentToken& t ) {
            SimpleVisitor::visit( t );

            m_factor /= 100.0;
        }

        virtual void visit( ThousandToken& t ) {
            SimpleVisitor::visit( t );

            if ( m_last_thsnd_idx != -1 ) {
                // last was non-format char (will be render according to dest. locale)

                // discard last and this thsnd
                m_last_thsnd_idx = m_last_num_char_idx = -1;
            } else {
                if ( m_last_num_char_idx != -1 ) {
                    if ( m_last_num_char_idx + 1 == m_idx ) { // directly preceeding
                        m_last_thsnd_idx = m_idx;
                    } else {
                        m_last_num_char_idx = -1;
                    }
                }
            }
        }

        virtual void visit( NumberFormatChar& t ) {
            SimpleVisitor::visit( t );

            // update digit count
            switch ( m_current_part ) {
                case Integer:
                    ++m_fmt.digits.integer;
                    break;
                case Fraction:
                    ++m_fmt.digits.fraction;
                    break;
                case Exp_Integer:
                    ++m_fmt.digits.exp_integer;
                    break;
                case Exp_Fraction:
                    ++m_fmt.digits.exp_fraction;
                    break;
            }

            if ( m_last_thsnd_idx != -1 ) {
                if ( m_last_thsnd_idx + 1 == m_idx ) { // directly preceeding
                    m_fmt.have_thousand_sep = true;
                    m_fmt.tokens.at( m_last_thsnd_idx ).mark_obsolete();
                }
                m_last_thsnd_idx = -1;
            }

            m_last_num_char_idx = m_idx;
        }

        virtual void visit( DecimalToken& t ) {
            SimpleVisitor::visit( t );

            if ( m_current_part == Integer ) {
                m_current_part = Fraction;
            } else if ( m_current_part == Exp_Integer ) {
                m_current_part = Exp_Fraction;
            } else {
                ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }

            if ( m_last_thsnd_idx != -1 ) {
                // got a m_factor control sequence
                handle_factor();
            }
        }

        virtual void visit( ExponentToken& t ) {
            SimpleVisitor::visit( t );

            if ( m_current_part == Integer || m_current_part == Fraction ) {
                m_current_part = Exp_Integer;
            } else {
                ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }

            // no factors supported with Exponents
            m_factor = 0.0;
        }

    private:
        DecimalVisitor& operator =( const DecimalVisitor& );

        void handle_factor() {
            ThousandToken& t = dynamic_cast<ThousandToken&>( m_fmt.tokens.at( m_last_thsnd_idx ) );

            while ( t.count-- > 0 ) {
                m_factor *= 1000.0;
            }

            t.mark_obsolete();

            m_last_thsnd_idx = m_last_num_char_idx = -1;
        }

        enum {
            Integer
            , Fraction
            , Exp_Integer
            , Exp_Fraction
        } m_current_part;

        // thousand vs. m_factor
        int m_last_num_char_idx; // -1 if none
        int m_last_thsnd_idx; // -1 if none

        DecimalFormatSection& m_fmt;
        double m_factor; // 0.0 if scientific format
    };

    /*!
    * - Recognizes dates given in the local date-order.
    * - Resolves ambiguities (e.g. minute vs. month)
    *     A 'm' immediatelity following 'h' or followed by 's'
    *     will be treated as minute part.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class CellFormatPostParser::DateTimeVisitor : public CellFormatPostParser::SimpleVisitor
    {
    public:
        DateTimeVisitor( DateTimeFormatSection& fmt, const ControlTokens& ct )
            : m_ct( ct )
            , m_fmt( fmt )
            , m_have_absolute( false )
        {}

        virtual ~DateTimeVisitor() {
            if ( m_have_absolute && m_fmt.have_ampm ) {
                ExceptionFactory::raise( cell_format_exception::E_ABSOLUTETIME_AMPM_CONFLICT );
            }
        }

        virtual void visit( DateFormatToken& dt ) {
            SimpleVisitor::visit( dt );

            if ( !dt.escaped ) {
                if ( ( ( _date.have_part == 0 ) || ( _date.have_part <= 2 && _date.last_idx + 1 == m_idx ) )
                        && static_cast<cell_format::tokens::DateFormatToken::Type>( m_ct.date_order[_date.have_part] ) == dt.type ) {
                    _date.last_idx = _date.idx[_date.have_part] = m_idx;
                    ++_date.have_part;

                    if ( _date.have_part == 3 ) {
                        // got an entire date
                        dynamic_cast<DateFormatToken&>( m_fmt.tokens[_date.idx[0]] ).type = DateFormatToken::Date1;
                        dynamic_cast<DateFormatToken&>( m_fmt.tokens[_date.idx[1]] ).type = DateFormatToken::Date2;
                        dynamic_cast<DateFormatToken&>( m_fmt.tokens[_date.idx[2]] ).type = DateFormatToken::Date3;
                        _date.have_part = 0;
                    }
                } else {
                    _date.have_part = 0;
                }
            }

            // month could be minute
            if ( dt.type == DateFormatToken::Month ) {
                _time.idx = m_idx;

                if ( _time.have_hours && _time.last_idx + 1 == m_idx ) {
                    convert_to_minute();

                    _time.have_hours = false;
                    _time.have_minutes = false;
                    _time.last_idx = m_idx;
                } else {
                    _time.have_hours = false;
                    _time.have_minutes = true;
                    _time.last_idx = m_idx;
                }
            }
        }

        virtual void visit( TimeFormatToken& tt ) {
            SimpleVisitor::visit( tt );

            if ( tt.type == TimeFormatToken::Hour ) {
                _time.have_hours = true;
                _time.have_minutes = false;
                _time.last_idx = m_idx;
            } else if ( tt.type == TimeFormatToken::Second ) {
                if ( _time.have_minutes && _time.last_idx + 1 == m_idx ) {
                    convert_to_minute();

                    _time.have_hours = false;
                    _time.have_minutes = false;
                    _time.last_idx = m_idx;
                } else {
                    _time.have_hours = false;
                    _time.have_minutes = true;
                    _time.last_idx = m_idx;
                }
            } else if ( tt.type == TimeFormatToken::SecondFraction || tt.type == TimeFormatToken::Minute ) {
            } else {
                ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }

            if ( tt.is_absolute ) {
                m_have_absolute = true;
            }

            // second fraction cannot be long than four digits
            if ( tt.type == TimeFormatToken::SecondFraction && tt.digit_count >= 4 ) {
                ExceptionFactory::raise( cell_format_exception::E_SECOND_FRACTION_TOO_LONG );
            }

            if ( tt.type == TimeFormatToken::SecondFraction ) {
                m_fmt.have_second_fraction = true;
            }
        }

        virtual void visit( DateSeparatorToken& dst ) {
            SimpleVisitor::visit( dst );

            // update
            if ( _date.last_idx + 1 == m_idx ) {
                ++_date.last_idx;
            }

            if ( !dst.escaped && dst.value == m_ct.format_codes.date_separators[0] ) {
                dst.localized = true;
            }
        }

        virtual void visit( TimeSeparatorToken& tst ) {
            SimpleVisitor::visit( tst );

            // update
            if ( _time.last_idx + 1 == m_idx ) {
                ++_time.last_idx;
            }
        }

        virtual void visit( WhitespaceToken& wt ) {
            SimpleVisitor::visit( wt );

            if ( _date.last_idx + 1 == m_idx ) {
                ++_date.last_idx;
            }
            if ( _time.last_idx + 1 == m_idx ) {
                ++_time.last_idx;
            }
        }

        virtual void visit( AmPmToken& t ) {
            SimpleVisitor::visit( t );

            m_fmt.have_ampm = true;
        }

    private:
        DateTimeVisitor& operator =( const DateTimeVisitor& );

        // convert token at _time.idx into minute token
        void convert_to_minute() {
            std::auto_ptr<TimeFormatToken> t( new TimeFormatToken() );

            t->type = TimeFormatToken::Minute;
            t->digit_count = dynamic_cast<const DateFormatToken&>( m_fmt.tokens[_time.idx] ).digit_count;
            t->is_absolute = false;

            m_fmt.tokens.replace( _time.idx, t );
        }

        const ControlTokens& m_ct;
        DateTimeFormatSection& m_fmt;

        // state for time-specific code (month vs. minute)
        struct _Time {
            _Time() : have_hours( false ), have_minutes( false ), last_idx( -1 ) {}

            bool have_hours;
            bool have_minutes; // we got sth. that could be the minute part

            int idx; // considered token

            int last_idx;
        } _time;

        // state for date-specific code (recognize in-order dates)
        struct _Date {
            _Date() : have_part( 0 ), last_idx( -1 ) {}

            int idx[3]; // considered tokens

            unsigned char have_part; // the date parts we already got (0 = none)
            int last_idx; // last validated m_idx - if not m_idx-1 then have_part:=0
        } _date;

        bool m_have_absolute;
    };

    CellFormatPostParser::CellFormatPostParser( const ControlTokens& in_ct )
        : m_in_ct( in_ct )
    {}

    CellFormatPostParser::~CellFormatPostParser()
    {}

    /*! Selects the appropriate visitor.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class CellFormatPostParser::VisitorSelector : public FormatSectionVisitor
    {
    public:
        VisitorSelector( const ControlTokens& ct, const parsed_cell_format& fmt )
            : m_ct( ct )
            , m_fmt( fmt )
        {}

        ~VisitorSelector()
        {}

        void visit( DecimalFormatSection& s ) {
            DecimalVisitor v( s );
            s.visit_tokens( v );

            // an _empty_ format is a "general" if not conditionless without color
            // or conditional without condition and color
            if ( s.tokens.empty() && ( ( s.color != Color::_UNSET_ ) || ( !m_fmt.is_conditionless() && ( s.cond.op != Condition::none ) ) ) ) {
                s.tokens.push_back( new GeneralToken() );
            }
        }

        void visit( FractionFormatSection& s ) {
            FractionVisitor v( s );
            s.visit_tokens( v );
        }

        void visit( DateTimeFormatSection& s ) {
            CellFormatPostParser::DateTimeVisitor v( s, m_ct );
            s.visit_tokens( v );
        }

        void visit( TextFormatSection& /*s*/ )
        {}

        void visit( EmptyFormatSection& /*s*/ ) {
            ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR ); // this should never be reached
        }

    private:
        VisitorSelector& operator =( const VisitorSelector& );

        const ControlTokens& m_ct;
        const parsed_cell_format& m_fmt;
    };

    void CellFormatPostParser::parse( parsed_cell_format& fmt ) const
    {
        VisitorSelector v( m_in_ct, fmt );

        for ( parsed_cell_format::FormatSections::iterator i = fmt.m_sections->begin(), e = fmt.m_sections->end(); i != e; ++i ) {
            i->accept( v );
            i->purge();
        }

        /* move conditionless format m_sections to the end */
        // very simple sort ;) (we need EXACT sort here, 'equal' shall should not be swapped */
        for ( size_t i = 0, l = fmt.m_sections->size(); i < l; ++i ) {
            for ( size_t j = 0; j < i; ++j ) {
                if ( ( *fmt.m_sections )[j] < ( *fmt.m_sections )[j+1] ) {
                    // swap
                    parsed_cell_format::FormatSections::auto_type t = fmt.m_sections->release( fmt.m_sections->begin() + j );
                    fmt.m_sections->insert( fmt.m_sections->begin() + j, std::auto_ptr<FormatSection>( fmt.m_sections->release( fmt.m_sections->begin() + j ).release() ) );
                    fmt.m_sections->insert( fmt.m_sections->begin() + j + 1, std::auto_ptr<FormatSection>( t.release() ) );
                }
            }
        }
    }
}
