/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG
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
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/
#include "precompiled_header.hpp"
#include "conditional_format_formula_writer.hpp"

#include <wss/free_formula.hpp>
#include <wss/session.hpp>
#include <wss/translation_map.hpp>
#include <wss/translation_table.hpp>
#include <wss/conditional_format_exception.hpp>
#include "conditional_format_utils.hpp"
#include "core_logging.hpp"

namespace cf
{
    struct conditional_format_formula_writer::conditional_format_formula_writer_helper {

        /*!
        * \brief
        * little helper that takes a string and returns the same string with leading equal sign removed
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string remove_leading_equal_sign( const std::string& formula ) {
            if ( formula.compare( 0, 1, "=" ) == 0 ) {
                return formula.substr( 1 );
            }
            return formula;
        }

        /*!
        * \brief
        * little helper that appends a language specific parameter separator
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void append_parameter_separator( session& s, std::string& formula ) {
            const shared_translation_map_type&  tr_map = translation_table::instance()[ s.locale() ];
            formula += tr_map->parameter_separator();
        }

        static inline void append_quotes( session&/* s*/, std::string& formula ) {
            formula.push_back( '"' );
        }

        /*!
        * \brief
        * little helper that starts the if function
        * returned string looks like: "IF(" for english locale
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string start_another_if( session& s ) {
            return lookup_function_translation( s, "IF" ) + "(";
        }

        /*!
        * \brief
        * little helper that starts the if function
        * returned string looks like: "=IF(" for english locale
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string start_if( session& s ) {
            return "=" + start_another_if( s );
        }

        /*!
        * \brief
        * little helper that takes an english function name and looks up the locale specific one
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string lookup_function_translation( session& s, const std::string& en_name ) {
            return en_name;
            //             const translation_map::function_translation_entry* translation_entry = NULL;
            //             try {
            //                 translation_entry = translation_table::instance()[ s.locale() ]->internal_name_lookup[ convert_utf8_ci( en_name ) ];
            //             } catch ( const invalid_translation_table_exception& ) {
            //             } catch ( const translation_exception& ) {}
            //
            //             if ( NULL != translation_entry ) {
            //                 return translation_entry->identifier;
            //             }
            //             throw conditional_format_exception( "error while creating formula - function: \"" + en_name + "\" not found" );
        }

        /*!
        * \brief
        * little helper that ends the if function
        * appends ";TRUE;FALSE)" to the string for english locale
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void end_if( session& s, std::string& formula ) {
            append_parameter_separator( s, formula );
            const shared_translation_map_type&  tr_map = translation_table::instance()[ s.locale() ];
            formula += tr_map->boolean_true();
            append_parameter_separator( s, formula );
            formula += tr_map->boolean_false();
            formula.push_back( ')' );
        }

        /*!
        * \brief
        * create formula for average function
        *
        * will append the following to a string:
        * "AVERAGE(<range_list_str>)"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void avg( session& s, std::string& formula, const std::string& range_list_str ) {
            formula += lookup_function_translation( s, "averagee" );
            formula.push_back( '(' );
            formula += range_list_str;
            formula.push_back( ')' );
        }

        /*!
        * \brief
        * create formula for average function
        *
        * will append the following to a string:
        * "STDEV(<range_list_str>)"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void stdev( session& s, std::string& formula, const std::string& range_list_str ) {
            formula += lookup_function_translation( s, "stdev" );
            formula.push_back( '(' );
            formula += range_list_str;
            formula.push_back( ')' );
        }

        static inline void count( session& s, std::string& formula, const std::string& range_list_str ) {
            formula += lookup_function_translation( s, "count" );
            formula.push_back( '(' );
            formula += range_list_str;
            formula.push_back( ')' );
        }

        static inline void large( session& s, std::string& formula, const std::string& range_list_str, const std::string& x_largest ) {
            formula += lookup_function_translation( s, "large" );
            formula.push_back( '(' );
            formula += range_list_str;
            append_parameter_separator( s, formula );
            formula += x_largest;
            formula.push_back( ')' );
        }

        static inline void large_for_percent( session& s, std::string& formula, const std::string& range_list_str, const std::string& x_largest ) {
            formula += lookup_function_translation( s, "large" );
            formula.push_back( '(' );
            formula += range_list_str;
            append_parameter_separator( s, formula );
            count( s, formula, range_list_str );
            formula += "*";
            formula += x_largest;
            formula += "/100";
            formula.push_back( ')' );
        }

        static inline void small( session& s, std::string& formula, const std::string& range_list_str, const std::string& x_smallest ) {
            formula += lookup_function_translation( s, "small" );
            formula.push_back( '(' );
            formula += range_list_str;
            append_parameter_separator( s, formula );
            formula += x_smallest;
            formula.push_back( ')' );
        }

        static inline void small_for_percent( session& s, std::string& formula, const std::string& range_list_str, const std::string& x_smallest ) {
            formula += lookup_function_translation( s, "small" );
            formula.push_back( '(' );
            formula += range_list_str;
            append_parameter_separator( s, formula );
            count( s, formula, range_list_str );
            formula += "*";
            formula += x_smallest;
            formula += "/100";
            formula.push_back( ')' );
        }

        /*!
        * \brief
        * create formula for average rules
        * depending on the operator this function will construct different formulas
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string average( session& s, const std::string& range_list_str, const conditional_format_rule::value_rule_operators op ) {

            std::string formula = "=IF(NOT(ISBLANK(";
            formula += range_list_str;
            formula += "))";
            conditional_format_formula_writer_helper::append_parameter_separator( s, formula );
            formula += range_list_str;
            switch ( op ) {

                case conditional_format_rule::EQ:
                    conditional_format_formula_writer_helper::equal( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    break;
                case conditional_format_rule::NEQ:
                    conditional_format_formula_writer_helper::not_equal( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    break;
                case conditional_format_rule::GT:
                    conditional_format_formula_writer_helper::greater( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    break;
                case conditional_format_rule::LT:
                    conditional_format_formula_writer_helper::less( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    break;
                case conditional_format_rule::GTE:
                    conditional_format_formula_writer_helper::greater_equal( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    break;
                case conditional_format_rule::LTE:
                    conditional_format_formula_writer_helper::less_equal( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    break;

                case conditional_format_rule::STD_DEV_ABOVE_1:
                    conditional_format_formula_writer_helper::greater( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    formula.push_back( '+' );
                    conditional_format_formula_writer_helper::stdev( s, formula, range_list_str );
                    break;

                case conditional_format_rule::STD_DEV_ABOVE_2:
                    conditional_format_formula_writer_helper::greater( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    formula += "+2*";
                    conditional_format_formula_writer_helper::stdev( s, formula, range_list_str );

                    break;

                case conditional_format_rule::STD_DEV_ABOVE_3:
                    conditional_format_formula_writer_helper::greater( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    formula += "+3*";
                    conditional_format_formula_writer_helper::stdev( s, formula, range_list_str );

                    break;

                case conditional_format_rule::STD_DEV_BELOW_1:
                    conditional_format_formula_writer_helper::less( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    formula += "-";
                    conditional_format_formula_writer_helper::stdev( s, formula, range_list_str );

                    break;

                case conditional_format_rule::STD_DEV_BELOW_2:
                    conditional_format_formula_writer_helper::less( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    formula += "-2*";
                    conditional_format_formula_writer_helper::stdev( s, formula, range_list_str );

                    break;

                case conditional_format_rule::STD_DEV_BELOW_3:
                    conditional_format_formula_writer_helper::less( formula );
                    conditional_format_formula_writer_helper::avg( s, formula, range_list_str );
                    formula += "-3*";
                    conditional_format_formula_writer_helper::stdev( s, formula, range_list_str );

                    break;

                default:
                    return "";
            }

            formula += ")";
            return formula;
        }

        /*!
        * \brief
        * create formula for unique rule
        *
        * will return the following string:
        * "=IF(ISUNIQUE(<range_list_str>);TRUE;FALSE)"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string unique( session& s, const std::string& range_list_str ) {
            return function_lookup_add_range( s, "isunique", range_list_str );
        }

        /*!
        * \brief
        * create formula for duplicate rule
        *
        * will return the following string:
        * "=IF(NOT(ISUNIQUE(<range_list_str>));TRUE;FALSE)"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string duplicate( session& s, const std::string& range_list_str ) {
            return function_lookup_add_range( s, "isduplicate", range_list_str );
        }

        /*!
        * \brief
        * create formula for top rule
        *
        * will return the following string:
        * "=IF(RANK(<range_list_str>;<range_list_str>) >= nr_of );TRUE;FALSE)"
        *
        * \NOTE nr_of can be anything that returns a number, i.e. A1, 5, 400/$A$4
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string top( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            std::string formula = "=";
            formula += range_list_str;
            formula += ">=";
            conditional_format_formula_writer_helper::large( s, formula, range_list_str, conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[0]->formula_without_sheet_references( s.locale(), position ) ) );
            return formula;
        }

        /*!
        * \brief
        * create formula for top percent rule
        *
        * will return the following string:
        * "=RANK(<range_list_str>;<range_list_str>)/COUNT(<range_list_str>) <= nr_of"
        *
        * \NOTE nr_of can be anything that returns a number, i.e. A1, 5, 400/$A$4
        * \NOTE nr_of is treated as percentage, so anything between 0 and 100 is okay!
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string top_percent( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            std::string formula = "=";
            formula += range_list_str;
            formula += ">=";
            conditional_format_formula_writer_helper::large_for_percent( s, formula, range_list_str, conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[0]->formula_without_sheet_references( s.locale(), position ) ) );
            return formula;
        }

        /*!
        * \brief
        * create formula for bottom rule
        *
        * will return the following string:
        * "=IF(RANK(<range_list_str>;<range_list_str>) <= nr_of );TRUE;FALSE)"
        *
        * \NOTE nr_of can be anything that returns a number, i.e. A1, 5, 400/$A$4
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string bottom( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            std::string formula = "=";
            formula += range_list_str;
            formula += "<=";
            conditional_format_formula_writer_helper::small( s, formula, range_list_str, conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[0]->formula_without_sheet_references( s.locale(), position ) ) );
            return formula;
        }

        /*!
        * \brief
        * create formula for bottom percent rule
        *
        * will return the following string:
        * "=IF(RANK(<range_list_str>;<range_list_str>) <= nr_of );TRUE;FALSE)"
        *
        * \NOTE nr_of can be anything that returns a number, i.e. A1, 5, 400/$A$4
        * \NOTE nr_of is treated as percentage, so anything between 0 and 100 is okay!
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string bottom_percent( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            std::string formula = "=";
            formula += range_list_str;
            formula += "<=";
            conditional_format_formula_writer_helper::small_for_percent( s, formula, range_list_str, conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[0]->formula_without_sheet_references( s.locale(), position ) ) );
            return formula;
        }

        /*!
        * \brief
        * little helper that appends an equal sign
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void equal( std::string& formula ) {
            formula.push_back( '=' );
        }

        /*!
        * \brief
        * little helper that appends a not-equal sign
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void not_equal( std::string& formula ) {
            formula += "<>";
        }

        /*!
        * \brief
        * little helper that appends a greater sign
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void greater( std::string& formula ) {
            formula.push_back( '>' );
        }

        /*!
        * \brief
        * little helper that appends a greater-equal sign
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void greater_equal( std::string& formula ) {
            formula += ">=";
        }

        /*!
        * \brief
        * little helper that appends a less sign
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void less( std::string& formula ) {
            formula.push_back( '<' );
        }

        /*!
        * \brief
        * little helper that appends a less-equal sign
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void less_equal( std::string& formula ) {
            formula += "<=";
        }

        /*!
        * \brief
        * little helper that appends min of two free formulas
        * appends "MIN(<first ff>;<second ff>)" to the string
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void append_min( session& s, std::string& formula, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            formula += lookup_function_translation( s, "min" );
            formula.push_back( '(' );
            formula += conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[0]->formula_without_sheet_references( s.locale(), position ) );
            append_parameter_separator( s, formula );
            formula += conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[1]->formula_without_sheet_references( s.locale(), position ) );
            formula.push_back( ')' );
        }

        /*!
        * \brief
        * little helper that appends max of two free formulas
        * appends "MAX(<first ff>;<second ff>)" to the string
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline void append_max( session& s, std::string& formula, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            formula += lookup_function_translation( s, "max" );
            formula.push_back( '(' );
            formula += conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[0]->formula_without_sheet_references( s.locale(), position ) );
            append_parameter_separator( s, formula );
            formula += conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[1]->formula_without_sheet_references( s.locale(), position ) );
            formula.push_back( ')' );
        }

        /*!
         * \brief
         * if we have a name error we assume that this should be treated as a string constant
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        static inline std::string transform_formula_to_string_if_name_error( session& s, const shared_free_formula_type& ff, const sheet_point& position ) {
            const variant value_of_ff = ff->value( s, position );
            if ( value_of_ff.type() == variant::type_error && value_of_ff.error_code() == variant::error_name ) {
                std::string return_string = "\"";
                return_string += remove_leading_equal_sign( ff->formula_without_sheet_references( s.locale(), position ) );
                return_string += "\"";
                return return_string;
            } else {
                return remove_leading_equal_sign( ff->formula_without_sheet_references( s.locale(), position ) );
            }
        }

        /*!
         * \brief
         * writes the formula for a value rule
         *
         * formulas look like this for 1 parameter rules:
         * "=IF( <operand1> <operator> <range as absolute reference>; TRUE; FALSE )"
         * i.e.: "=IF(15<$a$1:$a$6;TRUE;FALSE)"
         * and for 2 paramter rules (like between)
         * "=IF(MIN(<operand1>; <operand2>) <= IF( <range as absolute reference> <= MAX( <operand1>; <operand2> ); <range as absolute reference> ; MIN( <operand1>; <operand2> ) ); TRUE; FALSE)
         * same for not between with '>' instead of '<='
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        static inline void append_value_rule_opener( session& s, std::string& formula, const std::string& range_list_str ) {
            formula += range_list_str;
        }

        static inline void append_value_rule_end( session& s, std::string& formula, const std::string& operand, const std::string& range_list_str ) {
            formula += conditional_format_formula_writer_helper::remove_leading_equal_sign( operand );
        }

        static inline std::string value( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position, const conditional_format_rule::value_rule_operators op ) {
            //sanity check!
            if ( ffs.size() == 0 || ! ffs[0]->is_valid() ) {
                throw conditional_format_exception( "conditional_format_rule type CELL_VALUE called, but no operand1 set" );
            }
            std::string formula = "=";
            switch ( op ) {
                case conditional_format_rule::EQ:
                    append_value_rule_opener( s, formula, range_list_str );
                    conditional_format_formula_writer_helper::equal( formula );
                    append_value_rule_end( s, formula, ffs[0]->formula_without_sheet_references( s.locale(), position ), range_list_str );
                    break;
                case conditional_format_rule::NEQ:
                    append_value_rule_opener( s, formula, range_list_str );
                    conditional_format_formula_writer_helper::not_equal( formula );
                    append_value_rule_end( s, formula, ffs[0]->formula_without_sheet_references( s.locale(), position ), range_list_str );
                    break;
                case conditional_format_rule::GTE:
                    append_value_rule_opener( s, formula, range_list_str );
                    conditional_format_formula_writer_helper::greater_equal( formula );
                    append_value_rule_end( s, formula, ffs[0]->formula_without_sheet_references( s.locale(), position ), range_list_str );
                    break;
                case conditional_format_rule::LTE:
                    append_value_rule_opener( s, formula, range_list_str );
                    conditional_format_formula_writer_helper::less_equal( formula );
                    append_value_rule_end( s, formula, ffs[0]->formula_without_sheet_references( s.locale(), position ), range_list_str );
                    break;
                case conditional_format_rule::GT:
                    append_value_rule_opener( s, formula, range_list_str );
                    conditional_format_formula_writer_helper::greater( formula );
                    append_value_rule_end( s, formula, ffs[0]->formula_without_sheet_references( s.locale(), position ), range_list_str );
                    break;
                case conditional_format_rule::LT:
                    append_value_rule_opener( s, formula, range_list_str );
                    conditional_format_formula_writer_helper::less( formula );
                    append_value_rule_end( s, formula, ffs[0]->formula_without_sheet_references( s.locale(), position ), range_list_str );
                    break;
                case conditional_format_rule::BETWEEN:
                    // "=MIN(<operand1>; <operand2>) <= IF( <range as absolute reference> <= MAX( <operand1>; <operand2> ); <range as absolute reference> ; MIN( <operand1>; <operand2> ) )
                    //sanity check
                    if ( ffs.size() < 2 || ! ffs[1]->is_valid() ) {
                        throw conditional_format_exception( "conditional_format_rule type between/not between called, but no oeprand2 set" );
                    }
                    formula += "between(";
                    formula += conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[0]->formula_without_sheet_references( s.locale(), position ) );
                    append_parameter_separator( s, formula );
                    formula += range_list_str;
                    append_parameter_separator( s, formula );
                    formula += conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[1]->formula_without_sheet_references( s.locale(), position ) );
                    formula.push_back( ')' );
                    break;
                case conditional_format_rule::NBETWEEN:
                    // "=MIN(<operand1>; <operand2>) > IF( <range as absolute reference> > MAX( <operand1>; <operand2> ); <range as absolute reference> ; MIN( <operand1>; <operand2> ) )
                    //sanity check
                    if ( ffs.size() < 2 || ! ffs[1]->is_valid() ) {
                        throw conditional_format_exception( "conditional_format_rule type between/not between called, but no oeprand2 set" );
                    }
                    formula += "nbetween(";
                    formula += conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[0]->formula_without_sheet_references( s.locale(), position ) );
                    append_parameter_separator( s, formula );
                    formula += range_list_str;
                    append_parameter_separator( s, formula );
                    formula += conditional_format_formula_writer_helper::remove_leading_equal_sign( ffs[1]->formula_without_sheet_references( s.locale(), position ) );
                    formula.push_back( ')' );
                    break;
                default:
                    throw std::logic_error( "invalid case" );
            }
            return formula;
        }

        /*!
        * \brief
        * helper function that returns
        * "=IF(<en_function_name>(<range_list_str>);TRUE;FALSE)"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string function_lookup_add_range( session& s, const std::string& en_function_name, const std::string& range_list_str ) {
            std::string formula = "=";
            formula += lookup_function_translation( s, en_function_name );
            formula.push_back( '(' );
            formula += range_list_str;
            formula.push_back( ')' );
            return formula;
        }

        /*!
        * \brief
        * helper function that returns
        * "=IF(NOT(<en_function_name>(<range_list_str>));TRUE;FALSE)"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string not_function_lookup_add_range( session& s, const std::string& en_function_name, const std::string& range_list_str ) {
            std::string formula = "=";
            formula += lookup_function_translation( s, "not" );
            formula.push_back( '(' );
            formula += lookup_function_translation( s, en_function_name );
            formula.push_back( '(' );
            formula += range_list_str;
            formula.push_back( ')' );
            formula.push_back( ')' );
            return formula;
        }

        /*!
        * \brief returns error rule
        * "=IF(ISERROR(<range_list_str>);TRUE;FALSE)"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string errors( session& s, const std::string& range_list_str ) {
            return function_lookup_add_range( s, "iserror", range_list_str );
        }

        /*!
        * \brief returns error rule
        * "=IF(NOT(ISERROR(<range_list_str>));TRUE;FALSE)"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string no_errors( session& s, const std::string& range_list_str ) {
            return not_function_lookup_add_range( s, "iserror", range_list_str );
        }


        /*!
        * \brief returns blank rule
        * "=IF(ISBLANK(<range_list_str>);TRUE;FALSE)"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string blanks( session& s, const std::string& range_list_str ) {
            return function_lookup_add_range( s, "isblank", range_list_str );
        }

        /*!
        * \brief returns not blank rule
         * "=IF(NOT(ISBLANK(<range_list_str>));TRUE;FALSE)"
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        static inline std::string no_blanks( session& s, const std::string& range_list_str ) {
            return not_function_lookup_add_range( s, "isblank", range_list_str );
        }

        /*!
        * \brief returns formula-true-rule
        * "<formula_passed>"
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string formula( session& s,  const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            return ffs[0]->formula_without_sheet_references( s.locale(), position );
        }

        /*!
        * \brief returns text contained rule
        * =IF(NOT(ISERROR(SEARCH(<text_to_search>;<range as absolute reference>)));TRUE;FALSE)
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string text_contained_formula( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            std::string formula = "=";
            formula += lookup_function_translation( s, "not" );
            formula.push_back( '(' );
            formula += lookup_function_translation( s, "iserror" );
            formula.push_back( '(' );
            formula += lookup_function_translation( s, "search" );
            formula.push_back( '(' );
            formula += transform_formula_to_string_if_name_error( s, ffs[0], position );
            append_parameter_separator( s, formula );
            formula += range_list_str;
            formula.push_back( ')' );
            formula.push_back( ')' );
            formula.push_back( ')' );
            return formula;
        }

        /*!
        * \brief returns text not contained rule
        * =ISERROR(SEARCH(<text_to_search>;<range as absolute reference>))
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string text_not_contained_formula( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            std::string formula = "=";
            formula += lookup_function_translation( s, "iserror" );
            formula.push_back( '(' );
            formula += lookup_function_translation( s, "search" );
            formula.push_back( '(' );
            formula += transform_formula_to_string_if_name_error( s, ffs[0], position );
            append_parameter_separator( s, formula );
            formula += range_list_str;
            formula.push_back( ')' );
            formula.push_back( ')' );
            return formula;
        }

        /*!
         * \brief returns text begins with rule
         * =search(<operand>,<selected_range>)=1
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        static inline std::string text_begins_with_formula( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            std::string formula = "=";
            formula += lookup_function_translation( s, "search" );
            formula.push_back( '(' );
            formula += transform_formula_to_string_if_name_error( s, ffs[0], position );
            append_parameter_separator( s, formula );
            formula += range_list_str;
            formula.push_back( ')' );
            formula.push_back( '=' );
            formula.push_back( '1' );
            return formula;
        }

        /*!
        * \brief returns text ends with rule
        *  =NOT(ISERR(FIND("a";RIGHT($H$24:$H$27;LEN("a")))))
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string text_ends_with_formula( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const sheet_point& position ) {
            std::string formula = "=";
            formula += lookup_function_translation( s, "not" );
            formula.push_back( '(' );
            formula += lookup_function_translation( s, "iserror" );
            formula.push_back( '(' );
            formula += lookup_function_translation( s, "search" );
            formula.push_back( '(' );
            formula += transform_formula_to_string_if_name_error( s, ffs[0], position );
            append_parameter_separator( s, formula );
            formula += lookup_function_translation( s, "right" );
            formula.push_back( '(' );
            formula += range_list_str;
            append_parameter_separator( s, formula );
            formula += lookup_function_translation( s, "len" );
            formula.push_back( '(' );
            formula += transform_formula_to_string_if_name_error( s, ffs[0], position );
            formula.push_back( ')' );
            formula.push_back( ')' );
            formula.push_back( ')' );
            formula.push_back( ')' );
            formula.push_back( ')' );
            return formula;
        }

        /*!
        * \brief returns text rules depending on op
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string text( session& s, const std::string& range_list_str, const conditional_format_rule::operand_vec_type& ffs, const conditional_format_rule::text_rule_operators op, const sheet_point& position ) {
            switch ( op ) {
                case conditional_format_rule::CONTAINED:
                    return text_contained_formula( s, range_list_str, ffs, position );
                case conditional_format_rule::NOT_CONTAINED:
                    return text_not_contained_formula( s, range_list_str, ffs, position );
                case conditional_format_rule::BEGINS_WITH:
                    return text_begins_with_formula( s, range_list_str, ffs, position );
                case conditional_format_rule::ENDS_WITH:
                    return text_ends_with_formula( s, range_list_str, ffs, position );
                default:
                    return "";
            }
        }

        /*!
        * \brief main function that will call helpers to write the formula!
        * if an empty string is returned, something went wrong
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static inline std::string write_formula( session& s, const conditional_format_rule& rule, const geometry::rectangle_type& range, const sheet_point& position ) {
            switch ( rule.m_rule_type ) {
                case conditional_format_rule::CELL_VALUE:
                    return conditional_format_formula_writer_helper::value( s, conditional_format_utils::range_to_a1( s.locale(), position ), rule.m_operands, position, rule.m_op );
                case conditional_format_rule::TEXT:
                    return conditional_format_formula_writer_helper::text( s, conditional_format_utils::range_to_a1( s.locale(), range ), rule.m_operands, rule.m_text_op, position );
                case conditional_format_rule::BLANKS:
                    return conditional_format_formula_writer_helper::blanks( s, conditional_format_utils::range_to_a1( s.locale(), range ) );
                case conditional_format_rule::NO_BLANKS:
                    return conditional_format_formula_writer_helper::no_blanks( s, conditional_format_utils::range_to_a1( s.locale(), range ) );
                case conditional_format_rule::ERRORS:
                    return conditional_format_formula_writer_helper::errors( s, conditional_format_utils::range_to_a1( s.locale(), range ) );
                case conditional_format_rule::NO_ERRORS:
                    return conditional_format_formula_writer_helper::no_errors( s, conditional_format_utils::range_to_a1( s.locale(), range ) );
                case conditional_format_rule::TOP:
                    return conditional_format_formula_writer_helper::top( s, conditional_format_utils::range_to_a1( s.locale(), range ), rule.m_operands, position );
                case conditional_format_rule::BOTTOM:
                    return conditional_format_formula_writer_helper::bottom( s, conditional_format_utils::range_to_a1( s.locale(), range ), rule.m_operands, position );
                case conditional_format_rule::TOP_PERCENT:
                    return conditional_format_formula_writer_helper::top_percent( s, conditional_format_utils::range_to_a1( s.locale(), range ), rule.m_operands, position );
                case conditional_format_rule::BOTTOM_PERCENT:
                    return conditional_format_formula_writer_helper::bottom_percent( s, conditional_format_utils::range_to_a1( s.locale(), range ), rule.m_operands, position );
                case conditional_format_rule::DUPLICATE_VALUE:
                    return conditional_format_formula_writer_helper::duplicate( s, conditional_format_utils::range_to_a1( s.locale(), range ) );
                case conditional_format_rule::UNIQUE_VALUE:
                    return conditional_format_formula_writer_helper::unique( s, conditional_format_utils::range_to_a1( s.locale(), range ) );
                case conditional_format_rule::FORMULA_TRUE:
                    return conditional_format_formula_writer_helper::formula( s, rule.m_operands, position );
                    //                 case conditional_format_rule::COLOR_SCALE:
                    //                 case conditional_format_rule::ICON_SETS:
                    //                 case conditional_format_rule::DATA_BAR:
                    //                     throw not_implemented_exception();
                case conditional_format_rule::AVERAGE_VALUE:
                    return conditional_format_formula_writer_helper::average( s, conditional_format_utils::range_to_a1( s.locale(), range ), rule.m_op );
                default:
                    return "";
            }
            return "";
        }

    };

    shared_free_formula_type conditional_format_formula_writer::create_formula( session& s, const conditional_format_rule& rule, const shared_worksheet_type& ws, const geometry::rectangle_type& range, const sheet_point& position )
    {
        return create_formula_for_move( s, rule, ws, range, position, position );
    }
    shared_free_formula_type conditional_format_formula_writer::create_formula_for_move( session& s, const conditional_format_rule& rule, const shared_worksheet_type& ws, const geometry::rectangle_type& range, const sheet_point& old_position, const sheet_point& new_position )
    {
#ifdef _DEBUG
        const std::string formula_used = conditional_format_formula_writer_helper::write_formula( s, rule, range, old_position );
        LOG_CORE_TRACE( "CF Rule created with the following data: {" );
        LOG_CORE_TRACE( "\t - formula: \t \"" << formula_used << "\"" );
        LOG_CORE_TRACE( "\t - position: \t \"" << conditional_format_utils::range_to_a1( s.locale(), new_position ) << "\"" );
        LOG_CORE_TRACE( "\t - range: \t \"" << conditional_format_utils::range_to_a1( s.locale(), range ) << "\"" );
        foreach( const shared_free_formula_type & ff, rule.m_operands ) {
            LOG_CORE_TRACE( "\t - operand \t \"" << ff->formula_without_sheet_references( s.locale(), old_position ) << "\"" );
        }
        LOG_CORE_TRACE( "}" );
        return free_formula::create( s, variant( formula_used ), ws, new_position );
#else
        return free_formula::create( s, variant( conditional_format_formula_writer_helper::write_formula( s, rule, range, old_position ) ), ws, new_position );
#endif
    }
}
