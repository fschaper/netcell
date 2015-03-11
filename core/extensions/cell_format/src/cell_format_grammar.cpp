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

//#define BOOST_SPIRIT_DEBUG_TRACENODE

////#define BOOST_SPIRIT_DEBUG
////#define BOOST_SPIRIT_DEBUG_FLAGS BOOST_SPIRIT_DEBUG_FLAGS_NODES

#include "cell_format_grammar.hpp"

#include "ExceptionFactory.hpp"

#include <boost/ref.hpp> // for locale-dependent patterns

#include <boost/spirit/include/classic_loops.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_if.hpp>
//#include <boost/spirit/tree/ast.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>
#include <boost/spirit/include/classic_functor_parser.hpp>

using namespace boost;
using namespace boost::spirit::classic;

#ifdef BOOST_SPIRIT_DEBUG_TRACENODE
#define DEBUG_RULE(r) \
    m_rule_names[r.id().to_long()] = #r; BOOST_SPIRIT_DEBUG_RULE(r);
#else
#define DEBUG_RULE(r) \
    m_rule_names[r.id().to_long()] = #r;
#endif

namespace cell_format
{

    cell_format_grammar::cell_format_grammar( const ControlTokens& ct )
        : m_ct( ct )
    {}

    cell_format_grammar::~cell_format_grammar()
    {}

    template <cell_format_exception::Code code>
    struct ThrowCellFormatExceptionFnctr {

        template <typename IteratorT>
        void operator()( IteratorT /*first*/, IteratorT /*last*/ ) const {
            ExceptionFactory::raise( code );
        }
    };

    /*! helper to throw exceptions */
    template <cell_format_exception::Code code>
    ThrowCellFormatExceptionFnctr<code> throw_cellformat_exception()
    {
        return ThrowCellFormatExceptionFnctr<code>();
    }

    struct set_bool_a {
        set_bool_a( bool& b )
            : m_bool_value( b )
        {}

        template <typename IteratorT>
        void operator()( IteratorT /*first*/, IteratorT /*last*/ ) const {
            m_bool_value = true;
        }

    private:
        bool& m_bool_value;
    };

    struct unset_bool_a {
        unset_bool_a( bool& b )
            : m_bool_value( b )
        {}

        template <typename IteratorT>
        void operator()( IteratorT /*first*/, IteratorT /*last*/ ) const {
            m_bool_value = false;
        }

    private:
        bool& m_bool_value;
    };

    struct bool_is_set {
        bool_is_set( bool& b )
            : m_bool_value( b )
        {}

        bool operator()() const {
            return m_bool_value;
        }

    private:
        bool& m_bool_value;
    };

    struct peek_ch_functor {
        typedef nil_t result_t;

        template <typename ScannerT>
        std::ptrdiff_t operator()( ScannerT const& scan, result_t& /*result*/ ) const {
            return ( !scan.at_end() && *scan == *m_ch ) ? 0 : -1;
        }

        const char* m_ch;
    };

    functor_parser<peek_ch_functor> peek_ch_p( const char& ch )
    {
        functor_parser<peek_ch_functor> fp;
        fp.functor.m_ch = &ch;
        return fp;
    }

    //#pragma inline_depth(255)
    //#pragma inline_recursion(on)

    template <typename ScannerT>
    cell_format_grammar::definition<ScannerT>::definition( const cell_format_grammar& self )
    {
        const ControlTokens& ct = self.m_ct;

        const char* date_separators = "./-";//ct.format_codes.date_separators.c_str();
        const char* time_separators = ct.format_codes.time_separators.c_str();

        const char* currency_str = ct.format_codes.currency.c_str();

        const char* general_str = ct.format_codes.general.c_str();

        const char* black_str = ct.colors[Color::Black].c_str();
        const char* blue_str = ct.colors[Color::Blue].c_str();
        const char* cyan_str = ct.colors[Color::Cyan].c_str();
        const char* green_str = ct.colors[Color::Green].c_str();
        const char* magenta_str = ct.colors[Color::Magenta].c_str();
        const char* red_str = ct.colors[Color::Red].c_str();
        const char* white_str = ct.colors[Color::White].c_str();
        const char* yellow_str = ct.colors[Color::Yellow].c_str();

        bool conditions_allowed;

        /// for subrule
        /*first =*/
        (
            format_list = conditionless_format_list | conditional_format_list,

            conditionless_format_list
            = eps_p[unset_bool_a( conditions_allowed )]
              /*>> (format_part >> !(list_separator >> (text_format
                      | (format_part >> !(list_separator >> (text_format
                          | (format_part >> !(list_separator >> text_format))))))))*/


              >> ( format_part )
              >> !( list_separator >> format_part )
              >> !( list_separator >> format_part )
              >> !( list_separator >> text_format )
              >> end_p,
            conditional_format_list
            = eps_p[set_bool_a( conditions_allowed )]
              >> ( format_part % list_separator )
              >> end_p,
            list_separator
            = ch_p( cref( ct.format_codes.list_separator ) ),
            format_part
            = ( empty_format >> ( peek_ch_p( ct.format_codes.list_separator ) | end_p ) )
              | ( datetime_format >> ( peek_ch_p( ct.format_codes.list_separator ) | end_p ) )
              | ( decimal_number_format >> ( peek_ch_p( ct.format_codes.list_separator ) | end_p ) )
              | ( fractional_number_format >> ( peek_ch_p( ct.format_codes.list_separator ) | end_p ) )
              | ( text_format >> ( peek_ch_p( ct.format_codes.list_separator ) | end_p ) ),

            // number format
            decimal_number_format
            = ( number_format_part
                >> !( decimal >> number_format_part )
                >> !( exponent >> number_format_part >> !( decimal >> number_format_part ) ) )
              | ( *( decimal_nonformat | condition_selective | color ) // ".0" style format
                  >> decimal >> number_format_part
                  >> !( exponent >> number_format_part >> !( decimal >> number_format_part ) ) )
              | ( *( decimal_nonformat | condition_selective | color ) // general format
                  >> general
                  >> *( currency | condition_selective | color | decimal_nonformat ) )
              | ( *( decimal_nonformat ) // condition/color-only formats
                  >> if_p( bool_is_set( conditions_allowed ) )[eps_p].else_p[nothing_p] >> ( condition | color )
                  >> *( currency | condition_selective | color | decimal_nonformat ) )
              | ( *( decimal_nonformat ) // condition/color-only formats (other branch of if - need this to get a nice parse-tree)
                  >> if_p( bool_is_set( conditions_allowed ) )[nothing_p].else_p[eps_p]
                  >> *( currency | condition_selective | color | decimal_nonformat ) ),
            fractional_number_format
            = ( *fraction_sep
                >> integer_format_part
                >> *fraction_sep
                >> numerator_format_part
                >> *fraction_sep
                >> fraction
                >> *fraction_sep
                >> denominator_format_part
                >> *fraction_sep )
              | ( *fraction_sep
                  >> numerator_format_part
                  >> *fraction_sep
                  >> fraction
                  >> *fraction_sep
                  >> denominator_format_part
                  >> *fraction_sep ),
            integer_format_part
            = +( +chset_p( "0#?" ) >> *thousand ),
            numerator_format_part
            = leaf_node_d[ +chset_p( "0#?" ) ],
            denominator_format_part
            = leaf_node_d[ ( +chset_p( "0#?" ) ) | uint_p ],
            number_format_part
            =  *( color
                  | condition_selective
                  | thousand
                  | currency
                  | sign
                  | percent
                  | decimal_nonformat
                )
               >> +number_format_char
               >> *( number_format_char
                     | color
                     | condition_selective
                     | thousand
                     | currency
                     | sign
                     | percent
                     | decimal_nonformat
                   ),
            condition_selective
            = if_p( bool_is_set( conditions_allowed ) )[eps_p].else_p[nothing_p] >> condition,
            condition
            = confix_p( '[' >> !whitespace, cmp_op >> !whitespace >> number, !whitespace >> ']' ),
            cmp_op
            = leaf_node_d[ str_p( "<>" ) | str_p( ">=" ) | str_p( "<=" ) | ch_p( '<' )
                           | ch_p( '>' ) | ch_p( '=' ) ],
            number
            = leaf_node_d[
                  int_p
                  >> !( ch_p( cref( ct.format_codes.decimal ) ) >> uint_p )
                  >> !( as_lower_d[ch_p( 'e' )] >> int_p >> !( decimal >> uint_p ) )
              ],
            decimal_nonformat
            = generic_nonformat
              | ( anychar_p - ( at | general | fraction | color | condition | number_format_char | exponent | decimal | list_separator | thousand | day | month | year | hour | minute | second ) ),
            fraction_sep
            = color
              | condition_selective
              | percent
              | generic_nonformat
              | sign
              | ( anychar_p - ( digit_p | number_format_char | fraction | at | list_separator | thousand ) ),
            exponent
            = str_p( "e+" ) | str_p( "e-" ) | str_p( "E+" ) | str_p( "E-" ),
            number_format_char
            = chset_p( "0#?" ),
            decimal
            = ch_p( cref( ct.format_codes.decimal ) ),
            fraction
            = ch_p( '/' ),
            thousand
            = +ch_p( cref( ct.format_codes.thousand_separator ) ),
            currency
            = str_p( currency_str ),
            sign
            = ch_p( '=' ) | ch_p( '-' ) | ch_p( '+' ),

            // text format
            text_format
            = *( color | text_nonformat )
              >> !at >> *( color | text_nonformat ),
            text_nonformat
            = generic_nonformat | ( anychar_p - ( list_separator | at | absolute_time | escaped_date_token | hour | month | minute | second | day | year | second_fraction | ampm | number_format_char | decimal ) ),
            at
            = ch_p( '@' ),

            // generic
            general
            = leaf_node_d[ as_lower_d[str_p( general_str )] ],

            // date/time format
            datetime_format
            = *( ( condition_selective | color | datetime_nonformat ) - general )
              >> +( datetime_token - ( general | currency | second_fraction | escaped_date_separator | date_separator | time_separator ) ) // format ".0" is not second_fraction
              >> *( ( datetime_token | condition_selective | color | datetime_nonformat )
                    - ( list_separator | general | currency ) ),
            datetime_token
            = ( ( absolute_time | escaped_date_token | hour | month | minute | second | day | year | second_fraction | ampm )
                >> if_p( ch_p( '0' ) )[ eps_p[ throw_cellformat_exception<cell_format_exception::E_DATETIME_TOKEN_FOLLOWED_BY_ZERO>() ] ] )
              | date_separator | escaped_date_separator
              | time_separator,
            year
            = leaf_node_d[ as_lower_d[ +ch_p( cref( ct.format_codes.year ) ) ] ],
            month
            = leaf_node_d[ as_lower_d[ +ch_p( cref( ct.format_codes.month ) ) ] ],
            day
            = leaf_node_d[ as_lower_d[ +ch_p( cref( ct.format_codes.day ) ) ] ],
            escaped_date_token
            = str_p( "\"\"" ) >> ( year | month | day ) >> str_p( "\"\"" ),
            hour
            = leaf_node_d[ as_lower_d[ +ch_p( cref( ct.format_codes.hour ) ) ] ],
            minute
            = leaf_node_d[ as_lower_d[ +ch_p( cref( ct.format_codes.minute ) ) ] ],
            second
            = leaf_node_d[ as_lower_d[ +ch_p( cref( ct.format_codes.second ) ) ] ],
            second_fraction
            = leaf_node_d[ ch_p( cref( ct.format_codes.decimal ) ) >> +ch_p( '0' ) ],
            ampm
            = as_lower_d[ str_p( "a/p" ) | str_p( "am/pm" ) ],
            absolute_time
            = ( ch_p( '[' ) >> ( *space_p ) ) >> ( hour | minute | second ) >> ( ( *space_p ) >> ch_p( ']' ) ),
            date_separator
            = ( ( chset_p( date_separators ) - ( ch_p( '+' ) | ch_p( '-' ) | decimal ) ) >> nothing_p )
              //>> if_p(ch_p('0'))[ eps_p[ throw_cellformat_exception<cell_format_exception::E_DATETIME_TOKEN_FOLLOWED_BY_ZERO>() ] ])
              | chset_p( date_separators ),
            escaped_date_separator
            = str_p( "\"\"" ) >> date_separator >> str_p( "\"\"" ),
            time_separator
            = ( ( chset_p( time_separators ) - ( ch_p( '+' ) | ch_p( '-' ) | decimal ) ) >> nothing_p )
              //>> if_p(ch_p('0'))[ eps_p[ throw_cellformat_exception<cell_format_exception::E_DATETIME_TOKEN_FOLLOWED_BY_ZERO>() ] ])
              | chset_p( time_separators ),
            datetime_nonformat
            = ( generic_nonformat - escaped_date_token ) | ( anychar_p - ( chset_p( "0#?" ) | condition | datetime_token | at | color | currency ) ),

            // other
            generic_nonformat
            = string
              | whitespace
              | escaped_character
              | measured_space
              | fill
              | currency_special, //! \todo support this feature
            percent
            = ch_p( '%' ),
            whitespace
            = +space_p,
            string
            = confix_p( '"', *anychar_p, '"' ),
            escaped_character
            = discard_first_node_d[ ch_p( '\\' ) >> anychar_p ],
            measured_space
            = discard_first_node_d[ ch_p( '_' ) >> anychar_p ],
            fill
            = discard_first_node_d[ ch_p( '*' ) >> anychar_p ],
            color
            = confix_p( '[' >> !whitespace, color_name, !whitespace >> ']' ),
            color_name
            = black | blue | cyan | green | magenta | red | white | yellow,
            currency_special
            = leaf_node_d[ confix_p( "[$", *anychar_p, "]" ) ],
            black
            = no_node_d[as_lower_d[black_str]],
            blue
            = no_node_d[as_lower_d[blue_str]],
            cyan
            = no_node_d[as_lower_d[cyan_str]],
            green
            = no_node_d[as_lower_d[green_str]],
            magenta
            = no_node_d[as_lower_d[magenta_str]],
            red
            = no_node_d[as_lower_d[red_str]],
            white
            = no_node_d[as_lower_d[white_str]],
            yellow
            = no_node_d[as_lower_d[yellow_str]],

            // empty format
            empty_format
            = epsilon_p
        );
    }

    boost::spirit::classic::tree_parse_info<> cell_format_grammar::pt_parse( const std::string& s )
    {
        return spirit::classic::pt_parse( s.c_str(), *this, nothing_p );
    }

    const std::string cell_format_grammar::get_rule_name( int id )
    {
        RuleNames::const_iterator i = m_rule_names.find( id );

        if ( i == m_rule_names.end() ) {
            return "<unknown>";
        } else {
            return i->second;
        }
    }

    cell_format_grammar::RuleNames cell_format_grammar::m_rule_names;

}
