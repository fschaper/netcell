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

#include "CellFormatParseTreeConverter.hpp"

#include "ParseTreeImpl.hpp"
#include "cell_format_grammar.hpp"
#include "ExceptionFactory.hpp"
#include "FormatTokens.hpp"
#include "FormatSections.hpp"
#include "checked_number_cast.hpp"

#include <stdlib.h> // strtod
#include <float.h>

namespace cell_format
{

    using namespace tokens;

    CellFormatParseTreeConverter::CellFormatParseTreeConverter( const ControlTokens& in_ct )
        : m_in_ct( in_ct )
    {}

    CellFormatParseTreeConverter::~CellFormatParseTreeConverter()
    {}

    using namespace boost::spirit::classic;

    typedef tree_match<const char*> tree_match_type;
    typedef cell_format_grammar::definition<void> definition_type;

#define ID_OF(node, m_rule) \
    ((definition_type::m_rule ## _t::id().to_long()) == (node).value.id().to_long())

    static void _get_entire_match( const tree_match_type::node_t& root, std::string& s )
    {
        if ( root.value.end() - root.value.begin() > 0 ) {
            s += std::string( root.value.begin(), root.value.end() );
        }

        // recurse
        for ( tree_match_type::node_t::const_tree_iterator i = root.children.begin(), e = root.children.end(); i != e; ++i ) {
            _get_entire_match( *i, s );
        }
    }

    /*! traverses the tree recursively and appends FormatTokens to format. */
    static void _parse_format( const tree_match_type::node_t& root, FormatSection& format, const ControlTokens& in_ct )
    {
        if ( ID_OF( root, ampm ) ) {
            const tree_match_type::node_t& node = root.children.front();

            std::auto_ptr<AmPmToken> ampm( new AmPmToken() );

            ampm->short_form = ( node.value.end() - node.value.begin() <= 3 );
            ampm->uppercase = ( *node.value.begin() == 'A' );

            //std::cerr << *ampm;
            format.tokens.push_back( ampm );
        } else if ( ID_OF( root, escaped_date_token ) || ID_OF( root, year ) || ID_OF( root, month ) || ID_OF( root, day ) ) {
            const tree_match_type::node_t& node = ID_OF( root, escaped_date_token ) ? root.children[1].children.front() : root.children.front();

            std::auto_ptr<DateFormatToken> dt( new DateFormatToken() );

            if ( ID_OF( root, escaped_date_token ) ) {
                dt->escaped = true;

                if ( ID_OF( node, year ) ) {
                    dt->type = DateFormatToken::Year;
                } else if ( ID_OF( node, month ) ) {
                    dt->type = DateFormatToken::Month;
                } else if ( ID_OF( node, day ) ) {
                    dt->type = DateFormatToken::Day;
                }
            } else {
                if ( ID_OF( root, year ) ) {
                    dt->type = DateFormatToken::Year;
                } else if ( ID_OF( root, month ) ) {
                    dt->type = DateFormatToken::Month;
                } else if ( ID_OF( root, day ) ) {
                    dt->type = DateFormatToken::Day;
                }
            }

            dt->digit_count = checked_number_cast_impl<unsigned int>( node.value.end() - node.value.begin() );

            //std::cerr << *dt;
            format.tokens.push_back( dt );
        } else if ( ID_OF( root, hour ) || ID_OF( root, minute ) || ID_OF( root, second )
                    || ID_OF( root, second_fraction ) ) {
            const tree_match_type::node_t& node = root.children.front();

            std::auto_ptr<TimeFormatToken> tt( new TimeFormatToken() );

            tt->is_absolute = false;

            tt->digit_count = checked_number_cast_impl<unsigned int>( node.value.end() - node.value.begin() );

            if ( ID_OF( root, hour ) ) {
                tt->type = TimeFormatToken::Hour;
            } else if ( ID_OF( root, minute ) ) {
                tt->type = TimeFormatToken::Minute;
            } else if ( ID_OF( root, second ) ) {
                tt->type = TimeFormatToken::Second;
            } else if ( ID_OF( root, second_fraction ) ) {
                tt->type = TimeFormatToken::SecondFraction;
                --tt->digit_count;
            }

            //std::cerr << *tt;
            format.tokens.push_back( tt );
        } else if ( ID_OF( root, absolute_time ) ) {
            // recurse
            for ( tree_match_type::node_t::const_tree_iterator i = root.children.begin(), e = root.children.end(); i != e; ++i ) {
                if ( ID_OF( *i, hour ) || ID_OF( *i, minute ) || ID_OF( *i, second ) ) {
                    _parse_format( *i, format, in_ct );
                    break;
                }
            }
            // update
            dynamic_cast<TimeFormatToken&>( format.tokens.back() ).is_absolute = true;
            //std::cerr << dynamic_cast<TimeFormatToken&>(format.tokens.back());
        } else if ( ID_OF( root, date_separator ) || ID_OF( root, escaped_date_separator ) ) {
            const tree_match_type::node_t& node = ID_OF( root, escaped_date_separator ) ? root.children[1].children.front() : root.children.front();

            std::auto_ptr<DateSeparatorToken> t( new DateSeparatorToken() );

            t->value = *node.value.begin();
            t->escaped = ID_OF( root, escaped_date_separator );

            //std::cerr << *t;

            format.tokens.push_back( t );
        } else if ( ID_OF( root, time_separator ) ) {
            std::auto_ptr<TimeSeparatorToken> t( new TimeSeparatorToken() );

            t->value = *root.children.front().value.begin();

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, whitespace ) ) {
            std::auto_ptr<WhitespaceToken> t( new WhitespaceToken() );

            _get_entire_match( root, t->value );

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, sign ) ) {
            std::auto_ptr<SignToken> t( new SignToken() );

            t->value = *root.children.front().value.begin();

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, string ) || ID_OF( root, escaped_character )
                    || ( ID_OF( root, datetime_nonformat ) && root.children.size() == 0 )
                    || ( ID_OF( root, decimal_nonformat ) && root.children.size() == 0 )
                    || ( ID_OF( root, text_nonformat ) && root.children.size() == 0 )
                    || ( ID_OF( root, fraction_sep ) && root.children.size() == 0 )
                    || ID_OF( root, fraction ) ) {

            std::auto_ptr<NonFormatToken> t( new NonFormatToken() );

            _get_entire_match( root, t->value );

            // remove quotes
            if ( ID_OF( root, string ) ) {
                t->value.erase( 0, 1 );
                t->value.resize( t->value.size() - 1 );
            }

            if ( ID_OF( root, fraction ) ) {
                t->dont_escape = true;
            }

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, number_format_char ) ) {
            std::auto_ptr<NumberFormatChar> t( new NumberFormatChar() );

            t->type = *root.children.front().value.begin();

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, exponent ) ) {
            std::auto_ptr<ExponentToken> t( new ExponentToken() );

            t->always_sign = ( *( root.children.front().value.end() - 1 ) == '+' );
            t->lower_case = ( *root.children.front().value.begin() == 'e' );

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, general ) ) {
            format.tokens.push_back( new GeneralToken() );
            //std::cerr << dynamic_cast<GeneralToken&>(format.tokens.back());
        } else if ( ID_OF( root, decimal ) ) {
            format.tokens.push_back( new DecimalToken() );
            //std::cerr << dynamic_cast<DecimalToken&>(format.tokens.back());
        } else if ( ID_OF( root, thousand ) ) {
            std::auto_ptr<ThousandToken> t( new ThousandToken() );

            t->count = checked_number_cast_impl<unsigned int>( root.children.size() );

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, at ) ) {
            format.tokens.push_back( new AtToken() );
        } else if ( ID_OF( root, currency ) || ID_OF( root, currency_special ) ) {
            std::auto_ptr<LocalizedToken> t( new LocalizedToken() );

            if ( ID_OF( root, currency_special ) ) {
                const tree_match_type::node_t& node = root.children.front();

                t->type = LocalizedToken::CurrencySpecial;
                t->value = std::string( node.value.begin() + 2, node.value.end() - 1 );
            } else {
                t->type = LocalizedToken::Currency;
                t->value = "";
            }

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, integer_format_part ) ) {
            std::auto_ptr<FractionIntegerToken> t( new FractionIntegerToken() );

            for ( tree_match_type::node_t::const_tree_iterator i = root.children.begin(), e = root.children.end(); i != e; ++i ) {
                if ( ID_OF( *i, thousand ) ) {
                    t->have_thousand = true;
                } else {
                    t->format += std::string( i->value.begin(), i->value.end() );
                }
            }

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, numerator_format_part ) ) {
            const tree_match_type::node_t& node = root.children.front();

            std::auto_ptr<FractionNumeratorToken> t( new FractionNumeratorToken() );

            t->format = std::string( node.value.begin(), node.value.end() );

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, percent ) ) {
            std::auto_ptr<PercentToken> t( new PercentToken() );

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, denominator_format_part ) ) {
            const tree_match_type::node_t& node = root.children.front();

            std::auto_ptr<FractionDenominatorToken> t( new FractionDenominatorToken() );

            t->format = std::string( node.value.begin(), node.value.end() );

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, black ) || ID_OF( root, blue ) || ID_OF( root, cyan ) || ID_OF( root, green )
                    || ID_OF( root, magenta ) || ID_OF( root, red ) || ID_OF( root, white ) || ID_OF( root, yellow ) ) {

            if ( format.color != Color::_UNSET_ ) {
                ExceptionFactory::raise( cell_format_exception::E_TOO_MANY_COLORS );
            }

            if ( ID_OF( root, black ) ) {
                format.color = Color::Black;
            } else if ( ID_OF( root, blue ) ) {
                format.color = Color::Blue;
            } else if ( ID_OF( root, cyan ) ) {
                format.color = Color::Cyan;
            } else if ( ID_OF( root, green ) ) {
                format.color = Color::Green;
            } else if ( ID_OF( root, magenta ) ) {
                format.color = Color::Magenta;
            } else if ( ID_OF( root, red ) ) {
                format.color = Color::Red;
            } else if ( ID_OF( root, white ) ) {
                format.color = Color::White;
            } else if ( ID_OF( root, yellow ) ) {
                format.color = Color::Yellow;
            } else {
                ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }

        } else if ( ID_OF( root, measured_space ) ) {
            const tree_match_type::node_t& node = root.children.front();

            std::auto_ptr<MeasuredSpaceToken> t( new MeasuredSpaceToken() );

            t->value = *node.value.begin();

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, fill ) ) {
            const tree_match_type::node_t& node = root.children.front();

            std::auto_ptr<FillToken> t( new FillToken() );

            t->value = *node.value.begin();

            //std::cerr << *t;
            format.tokens.push_back( t );
        } else if ( ID_OF( root, condition ) ) {
            if ( format.cond.op != Condition::none ) {
                ExceptionFactory::raise( cell_format_exception::E_TOO_MANY_CONDITIONS );
            }

            for ( tree_match_type::node_t::const_tree_iterator i = root.children.begin(), e = root.children.end(); i != e; ++i ) {
                if ( ID_OF( *i, cmp_op ) ) {
                    std::string s( i->children.front().value.begin(), i->children.front().value.end() );

                    if ( s == "<>" ) {
                        format.cond.op = Condition::NEQ;
                    } else if ( s == "=" ) {
                        format.cond.op = Condition::EQ;
                    } else if ( s == "<=" ) {
                        format.cond.op = Condition::LTE;
                    } else if ( s == ">=" ) {
                        format.cond.op = Condition::GTE;
                    } else if ( s == "<" ) {
                        format.cond.op = Condition::LT;
                    } else if ( s == ">" ) {
                        format.cond.op = Condition::GT;
                    } else {
                        ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                    }
                } else if ( ID_OF( *i, number ) ) {
                    std::string s( i->children.front().value.begin(), i->children.front().value.end() );

                    // replace decimal
                    for ( std::string::iterator j = s.begin(), f = s.end(); j != f; ++j )
                        if ( *j == in_ct.format_codes.decimal ) {
                            *j = '.';
                        }

                    const char* t = s.c_str();
                    char* end = 0;

                    format.cond.operand = strtod( t, &end );

                    if ( end != t + strlen( t ) ) {
                        ExceptionFactory::raise( cell_format_exception::E_PARSE_FAILED );
                    }
                }
            }
        } else {
            // recurse
            for ( tree_match_type::node_t::const_tree_iterator i = root.children.begin(), e = root.children.end(); i != e; ++i ) {
                _parse_format( *i, format, in_ct );
            }
        }
    }

    void CellFormatParseTreeConverter::check_conditions( parsed_cell_format& result, bool is_conditionless )
    {
        /* EmptyFormatSection's are DecimalFormatSection's, except the last format section. */

        for ( parsed_cell_format::FormatSections::iterator i = result.m_sections->begin(), e = result.m_sections->end(); i != e; ++i ) {
            if ( i->get_type() == FormatSection::Empty ) {
                std::auto_ptr<FormatSection> updated;

                if ( i + 1 == e ) {
                    updated.reset( new TextFormatSection() );
                } else {
                    updated.reset( new DecimalFormatSection() );
                }

                result.m_sections->replace( i, updated );
            }
        }


        if ( is_conditionless ) {
            /* Add default conditions to conditionless formats. */

            if ( result.m_sections->size() == 0
                    || ( result.m_sections->size() == 1 && result.m_sections->front().get_type() == FormatSection::Text ) ) {
                /* this happens when we get an empty string */
                std::auto_ptr<DecimalFormatSection> f( new DecimalFormatSection() );

                f->tokens.push_back( new GeneralToken() );

                result.m_sections->insert( result.m_sections->begin(), f );
            } else if ( result.m_sections->size() == 1 ) {
                // nothing to do
            } else if ( result.m_sections->size() == 2 ) {
                if ( result.m_sections->at( 0 ).get_type() == FormatSection::Text ) {
                    ExceptionFactory::raise( cell_format_exception::E_INVALID_CONDITIONS );
                }

                if ( result.m_sections->at( 1 ).get_type() != FormatSection::Text ) {
                    // need to fix conditions
                    result.m_sections->at( 0 ).cond.op = Condition::GTE;
                    result.m_sections->at( 0 ).cond.operand = 0.0;

                    result.m_sections->at( 1 ).cond.op = Condition::LT;
                    result.m_sections->at( 1 ).cond.operand = 0.0;
                }
            } else if ( result.m_sections->size() == 3 ) {
                if ( result.m_sections->at( 0 ).get_type() == FormatSection::Text
                        || result.m_sections->at( 1 ).get_type() == FormatSection::Text ) {
                    ExceptionFactory::raise( cell_format_exception::E_INVALID_CONDITIONS );
                }

                if ( result.m_sections->at( 2 ).get_type() != FormatSection::Text ) {
                    // fix conditions
                    result.m_sections->at( 0 ).cond.op = Condition::GT;
                    result.m_sections->at( 0 ).cond.operand = 0.0;

                    result.m_sections->at( 1 ).cond.op = Condition::LT;
                    result.m_sections->at( 1 ).cond.operand = 0.0;

                    result.m_sections->at( 2 ).cond.op = Condition::EQ;
                    result.m_sections->at( 2 ).cond.operand = 0.0;
                } else {
                    // fix conditions
                    result.m_sections->at( 0 ).cond.op = Condition::GTE;
                    result.m_sections->at( 0 ).cond.operand = 0.0;

                    result.m_sections->at( 1 ).cond.op = Condition::LT;
                    result.m_sections->at( 1 ).cond.operand = 0.0;
                }
            } else if ( result.m_sections->size() == 4 ) {
                if ( result.m_sections->at( 0 ).get_type() == FormatSection::Text
                        || result.m_sections->at( 1 ).get_type() == FormatSection::Text
                        || result.m_sections->at( 2 ).get_type() == FormatSection::Text
                        || result.m_sections->at( 3 ).get_type() != FormatSection::Text ) {
                    ExceptionFactory::raise( cell_format_exception::E_INVALID_CONDITIONS );
                }

                // fix conditions
                result.m_sections->at( 0 ).cond.op = Condition::GT;
                result.m_sections->at( 0 ).cond.operand = 0.0;

                result.m_sections->at( 1 ).cond.op = Condition::LT;
                result.m_sections->at( 1 ).cond.operand = 0.0;

                result.m_sections->at( 2 ).cond.op = Condition::EQ;
                result.m_sections->at( 2 ).cond.operand = 0.0;
            } else {
                ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
            }
        } else {
            /* check if every possible numeric value matches a format */

            double min = DBL_MAX; // lower bound for range ob formattable values
            double max = DBL_MIN; // upper bound for range ob formattable values
            bool min_inclusive = false, max_inclusive = false; // is one of the bounds contained in the range of formattable values?

            for ( parsed_cell_format::FormatSections::iterator i = result.m_sections->begin(), e = result.m_sections->end(); i != e; ++i ) {
                if ( i->cond.op == Condition::LT || i->cond.op == Condition::LTE || i->cond.op == Condition::NEQ ) {
                    if ( i->cond.operand > max ) {
                        max = i->cond.operand;

                        max_inclusive = ( i->cond.op == Condition::LTE );
                    }
                }
                if ( i->cond.op == Condition::GT || i->cond.op == Condition::GTE || i->cond.op == Condition::NEQ ) {
                    if ( i->cond.operand < min ) {
                        min = i->cond.operand;

                        min_inclusive = ( i->cond.op == Condition::GTE );
                    }
                }
                if ( i->cond.op == Condition::none ) { // everything is alright
                    return;
                }
            }

            // check if range equals the "real" numbers
            if ( ( min > max ) || ( min == max && !min_inclusive && !max_inclusive ) ) {
                ExceptionFactory::raise( cell_format_exception::E_INVALID_CONDITIONS );
            }
        }
    }

    /*! \TODO implement */
    void CellFormatParseTreeConverter::convert( parsed_cell_format& result, const CellFormatParseTree& tree ) const
    {
        const tree_parse_info<>& match = tree.get_impl().match;

        const tree_match_type::node_t& format_list = match.trees.front().children.front();

        result.m_conditionless = ID_OF( format_list, conditionless_format_list );

        // for some reason spirit parse tree does not contain zero-length matches
        // as generated by empty_format rule...
        if ( format_list.children.empty() || ID_OF( format_list.children.front(), list_separator ) ) {
            std::auto_ptr<FormatSection> format;
            format.reset( new EmptyFormatSection() );
            result.m_sections->push_back( format );
        }

        // for each format string
        for ( tree_match_type::node_t::const_tree_iterator i = format_list.children.begin(), e = format_list.children.end(); i != e; ++i ) {
            const tree_match_type::node_t& format_section = ID_OF( *i, format_part ) ? i->children.front() : *i;

            std::auto_ptr<FormatSection> format;

            if ( ID_OF( format_section, datetime_format ) ) {
                format.reset( new DateTimeFormatSection() );
            } else if ( ID_OF( format_section, decimal_number_format ) ) {
                format.reset( new DecimalFormatSection() );
            } else if ( ID_OF( format_section, fractional_number_format ) ) {
                format.reset( new FractionFormatSection() );
            } else if ( ID_OF( format_section, text_format ) ) {
                format.reset( new TextFormatSection() );
            } else if ( ID_OF( format_section, empty_format ) ) {
                format.reset( new EmptyFormatSection() );
            } else {
                if ( ID_OF( *i, format_part ) ) {
                    ExceptionFactory::raise( cell_format_exception::E_UNKNOWN_ERROR );
                }

                // for some reason spirit parse tree does not contain zero-length matches
                // as generated by empty_format rule...
                if ( ID_OF( *i, list_separator ) && ( i + 1 == e || ID_OF( *( i + 1 ), list_separator ) ) ) {
                    format.reset( new EmptyFormatSection() );
                    result.m_sections->push_back( format );
                }

                continue;
            }

            _parse_format( format_section, *format, m_in_ct );

            result.m_sections->push_back( format );
        }

        /* Check for/add valid conditions. */
        check_conditions( result, format_list.value.id() == definition_type::conditionless_format_list_t::id() );
    }

}
