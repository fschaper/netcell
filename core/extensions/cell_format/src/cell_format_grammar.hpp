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

#include "ControlTokens.hpp"

#define BOOST_SPIRIT_THREADSAFE

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_common.hpp>

#include <map>

/*! \todo - the code below should declare a subrule in future versions. Rule is used right now,
*        because subrule didn't seem capable of creating a parse tree.
*        - no_node_d[] seems broken
*        - infix_node_d[] breaks difference operator
*        - consider using lex/yacc instead of boost::spirit
*/
#define CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE(id, name) \
    typedef boost::spirit::classic::rule<ScannerT, boost::spirit::classic::parser_context<>, boost::spirit::classic::parser_tag<id> > name ## _t; name ## _t name;
//typedef boost::spirit::classic::subrule<id> name ## _t; name ## _t name;

namespace cell_format
{

    /*! \brief Contains the cell format grammar definition.
    */
    struct cell_format_grammar : public boost::spirit::classic::grammar<cell_format_grammar> {
        cell_format_grammar( const ControlTokens& ct );
        ~cell_format_grammar();
        cell_format_grammar& operator =( const cell_format_grammar& );

        template <typename ScannerT>
        struct definition {
            definition( const cell_format_grammar& self );

            // general rules
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 1,  format_list ) // start
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 2,  conditionless_format_list )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 3,  conditional_format_list )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 4,  list_separator )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 5,  format_part )

            // number formats
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 32,  decimal_number_format )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 33,  fractional_number_format )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 35,  condition )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 36,  condition_selective )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 37,  cmp_op )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 38,  number )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 39,  digit )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 40,  decimal_nonformat )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 41,  exponent )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 42,  number_format_part ) // a sequence of 0#?, optionally separated by non-format chars
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 43,  number_format_char )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 44,  decimal )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 45,  fraction )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 46,  thousand )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 47,  currency )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 48,  integer_format_part )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 49,  numerator_format_part )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 50,  denominator_format_part )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 51,  fraction_sep )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 52,  sign )

            // text format
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 60,  text_format )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 61,  at )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 62,  text_nonformat )

            // general
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 71,  general )

            // empty (epsilon)
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 72,  empty_format )

            // date/time rules
            //! \todo [hh] -> closure is_bracketed? + ss,00
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 10, datetime_format )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 11, datetime_token )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 12, year )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 13, month )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 14, day )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 15, hour )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 16, minute )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 17, second )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 18, ampm )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 19, second_fraction ) // fractional second part
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 20, absolute_time ) // e.g. seconds non-modulo 60
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 21, date_separator )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 22, time_separator )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 23, datetime_nonformat )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 24, escaped_date_token )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 25, escaped_date_separator )

            // non-format specific tokens
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 80, generic_nonformat )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 81, whitespace )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 82, string )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 83, escaped_character )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 84, color )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 85, color_name )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 86, currency_special )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 87, measured_space )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 88, fill )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 89, red )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 90, black )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 91, cyan )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 92, magenta )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 93, white )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 94, blue )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 95, green )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 96, yellow )
            CELL_FORMAT_GRAMMAR_DECLARE_SUBRULE( 97, percent )

            const format_list_t& start() const {
                return format_list;
            }
        };

        /*! Helper to force automatic template instantiation. */
        boost::spirit::classic::tree_parse_info<> pt_parse( const std::string& s );

        typedef std::map<int, std::string> RuleNames;
        static const std::string get_rule_name( int id );

    private:
        static RuleNames m_rule_names;

        const ControlTokens& m_ct;
    };
}
