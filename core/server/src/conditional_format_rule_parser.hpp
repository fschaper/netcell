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
 *  \Author
 *  Florian Schaper <florian.schaper@jedox.com>
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "conditional_format_rule.hpp"
#include <wss/conditional_format_exception.hpp>

//boost
#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# pragma warning( push )
# pragma warning( disable : 4267 )
#  include <boost/lexical_cast.hpp>
# pragma warning( pop )
# include <boost/algorithm/string.hpp>
#endif
#include "conditional_format_utils.hpp"

namespace cf
{
    class conditional_format_rule_parser
    {

    public:
        conditional_format_rule_parser( const std::string& rule, conditional_format_rule& cfrule )
            : m_rule( rule )
            , m_cfrule( cfrule ) {}

        bool parse( session& s, const shared_worksheet_type& ws, const sheet_point& position ) {
            try {
                //set rule name
                size_t current_position_in_string = m_rule.find_first_of( "(" );
                if ( current_position_in_string == std::string::npos ) {
                    throw conditional_format_exception();
                }
                m_cfrule.m_rulename = boost::algorithm::to_lower_copy( m_rule.substr( 0, current_position_in_string ) );
                if ( m_cfrule.m_rulename == "cell_value" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::CELL_VALUE;
                } else if ( m_cfrule.m_rulename == "text" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::TEXT;
                } else if ( m_cfrule.m_rulename == "blanks" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::BLANKS;
                } else if ( m_cfrule.m_rulename == "no_blanks" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::NO_BLANKS;
                } else if ( m_cfrule.m_rulename == "errors" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::ERRORS;
                } else if ( m_cfrule.m_rulename == "no_errors" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::NO_ERRORS;
                } else if ( m_cfrule.m_rulename == "top" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::TOP;
                } else if ( m_cfrule.m_rulename == "bottom" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::BOTTOM;
                } else if ( m_cfrule.m_rulename == "top_percent" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::TOP_PERCENT;
                } else if ( m_cfrule.m_rulename == "bottom_percent" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::BOTTOM_PERCENT;
                } else if ( m_cfrule.m_rulename == "duplicate_value" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::DUPLICATE_VALUE;
                } else if ( m_cfrule.m_rulename == "unique_value" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::UNIQUE_VALUE;
                } else if ( m_cfrule.m_rulename == "formula_true" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::FORMULA_TRUE;
                    //                 } else if ( m_cfrule.m_rulename == "color_scale" ) {
                    //                     throw not_implemented_exception();
                    //                 } else if ( m_cfrule.m_rulename == "data_bar" ) {
                    //                     throw not_implemented_exception();
                    //                 } else if ( m_cfrule.m_rulename == "icon_sets" ) {
                    //                     throw not_implemented_exception();
                } else if ( m_cfrule.m_rulename == "average_value" ) {
                    m_cfrule.m_rule_type = conditional_format_rule::AVERAGE_VALUE;
                } else {
                    throw conditional_format_exception();
                }

                //set operator
                //need to adjust, because get_one will add one to position...
                ++current_position_in_string;
                std::string tmp = boost::algorithm::to_lower_copy( get_one( current_position_in_string ) );

                switch ( m_cfrule.m_rule_type ) {

                    case conditional_format_rule::CELL_VALUE:
                        if ( tmp == "=" ) {
                            m_cfrule.m_op = conditional_format_rule::EQ;
                        } else if ( tmp == ">" ) {
                            m_cfrule.m_op = conditional_format_rule::GT;
                        } else if ( tmp == "<" ) {
                            m_cfrule.m_op = conditional_format_rule::LT;
                        } else if ( tmp == "<>" ) {
                            m_cfrule.m_op = conditional_format_rule::NEQ;
                        } else if ( tmp == ">=" ) {
                            m_cfrule.m_op = conditional_format_rule::GTE;
                        } else if ( tmp == "<=" ) {
                            m_cfrule.m_op = conditional_format_rule::LTE;
                        } else if ( tmp == "between" ) {
                            m_cfrule.m_op = conditional_format_rule::BETWEEN;
                        } else if ( tmp == "not_between" ) {
                            m_cfrule.m_op = conditional_format_rule::NBETWEEN;
                        } else {
                            throw conditional_format_exception();
                        }
                        //check number of operand(s) for sanity
                        if ( m_cfrule.m_op == conditional_format_rule::BETWEEN || m_cfrule.m_op == conditional_format_rule::NBETWEEN ) {
                            if ( m_cfrule.m_operands.size() != 2 ) {
                                throw conditional_format_exception();
                            }
                        } else if ( m_cfrule.m_operands.size() != 1 ) {
                            throw conditional_format_exception();
                        }
                        break;

                    case conditional_format_rule::TEXT:
                        m_cfrule.m_op = conditional_format_rule::none;
                        if ( tmp == "contained" ) {
                            m_cfrule.m_text_op = conditional_format_rule::CONTAINED;
                        } else if ( tmp == "not_contained" ) {
                            m_cfrule.m_text_op = conditional_format_rule::NOT_CONTAINED;
                        } else if ( tmp == "begins_with" ) {
                            m_cfrule.m_text_op = conditional_format_rule::BEGINS_WITH;
                        } else if ( tmp == "ends_with" ) {
                            m_cfrule.m_text_op = conditional_format_rule::ENDS_WITH;
                        } else {
                            m_cfrule.m_text_op = conditional_format_rule::undefined;
                        }
                        break;

                    case conditional_format_rule::FORMULA_TRUE:
                        //check number of operand(s) for sanity
                        if ( m_cfrule.m_operands.size() != 1 ) {
                            throw conditional_format_exception();
                        }
                        break;

                    case conditional_format_rule::AVERAGE_VALUE:
                        if ( tmp == "=" ) {
                            m_cfrule.m_op = conditional_format_rule::EQ;
                        } else if ( tmp == ">" ) {
                            m_cfrule.m_op = conditional_format_rule::GT;
                        } else if ( tmp == "<" ) {
                            m_cfrule.m_op = conditional_format_rule::LT;
                        } else if ( tmp == ">=" ) {
                            m_cfrule.m_op = conditional_format_rule::GTE;
                        } else if ( tmp == "<=" ) {
                            m_cfrule.m_op = conditional_format_rule::LTE;
                        } else if ( tmp == "<>" ) {
                            m_cfrule.m_op = conditional_format_rule::NEQ;
                        } else if ( tmp == "std_dev_above_1" ) {
                            m_cfrule.m_op = conditional_format_rule::STD_DEV_ABOVE_1;
                        } else if ( tmp == "std_dev_above_2" ) {
                            m_cfrule.m_op = conditional_format_rule::STD_DEV_ABOVE_2;
                        } else if ( tmp == "std_dev_above_3" ) {
                            m_cfrule.m_op = conditional_format_rule::STD_DEV_ABOVE_3;
                        } else if ( tmp == "std_dev_below_1" ) {
                            m_cfrule.m_op = conditional_format_rule::STD_DEV_BELOW_1;
                        } else if ( tmp == "std_dev_below_2" ) {
                            m_cfrule.m_op = conditional_format_rule::STD_DEV_BELOW_2;
                        } else if ( tmp == "std_dev_below_3" ) {
                            m_cfrule.m_op = conditional_format_rule::STD_DEV_BELOW_3;
                        } else {
                            m_cfrule.m_op = conditional_format_rule::none;
                        }
                        //check number of operand(s) for sanity
                        //                         if ( m_cfrule.m_operands.size() != 1 ) {
                        //                             throw conditional_format_exception();
                        //                         }
                        break;

                    case conditional_format_rule::TOP:
                    case  conditional_format_rule::BOTTOM:
                    case  conditional_format_rule::TOP_PERCENT:
                    case  conditional_format_rule::BOTTOM_PERCENT:
                        conditional_format_utils::add_free_formula( m_cfrule.m_operands, s, variant( tmp ), ws, position  );
                        break;

                    default:
                        break;
                } //end switch
                ++current_position_in_string;
                tmp = get_one( current_position_in_string );
                try {
                    m_cfrule.m_stop_if_true = boost::lexical_cast< bool >( tmp );
                } catch ( boost::bad_lexical_cast& /*bad*/ ) {
                    m_cfrule.m_stop_if_true = false;
                }
                ++current_position_in_string;
                if ( m_rule.compare( current_position_in_string, 1, ")" ) == 0 ) {
                    return true;
                }
            } catch ( conditional_format_exception /*e*/ ) {
                m_cfrule.m_op = conditional_format_rule::none;
                m_cfrule.m_text_op = conditional_format_rule::undefined;
                m_cfrule.m_rule_type = conditional_format_rule::UNDEFINED_TYPE;
                return false;

            }
            return false;
        }
        inline std::string get_one( size_t& position ) {
            size_t tmp_position = position;
            position = m_rule.find_first_of( ";", tmp_position );
            if ( position == std::string::npos ) {
                throw conditional_format_exception();
            }
            return m_rule.substr( tmp_position, position - tmp_position );
        }

    private:
        const std::string& m_rule;
        conditional_format_rule& m_cfrule;
    };
}
