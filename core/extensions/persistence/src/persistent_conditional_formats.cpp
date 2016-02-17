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
 *  Marko Stijak <marko.stijak@jedox.com>
 *  Vali Nitu <vali@yalos-solutions.com>
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "persistent_conditional_formats.hpp"
#include "persistent_color.hpp"
#include "persistent_theme.hpp"
#include "persistent_color_table.hpp"
#include "persistent_styles.hpp"
#include "string_utils.hpp"
#include "css_utils.hpp"
#include <wss/variant.hpp>
#include <wss/conditional_format_manager.hpp>
#include <wss/set_conditional_format.hpp>
#include <wss/session.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>

namespace xlsx
{
    extern boost::regex match_export_var_regex;
    extern std::string atChr_str;

    void persistent_conditional_formats::register_cf( const std::string& key, persistent_conditional_format& map )
    {
        cf_map[ key ].push_back( map );
    }

    void persistent_conditional_formats::store( std::vector< sml::CT_ConditionalFormatting >& out_map )
    {
        int priority = 0;
        if ( cf_map.empty() ) {
            return;
        }

        std::map<std::string, std::vector< persistent_conditional_format > >::iterator ocfit;
        for ( ocfit = cf_map.begin(); ocfit != cf_map.end(); ocfit++ ) {
            sml::CT_ConditionalFormatting out_cf;
            out_cf.sqref = ocfit->first;
            bool addGroup = false;
            std::vector<std::string> range_part = string_utils::split( ocfit->first, ":" );
            std::string cellReference = range_part.size() ? range_part[0] : "";
            for ( int p = 0; p < ( int )ocfit->second.size(); p++ ) {
                bool valid = true;
                size_t add_operands = 0;
                sml::CT_CfRule out_cfRule;
                out_cfRule.priority = ++priority;
                persistent_conditional_format& cf = ocfit->second[p];
                out_cfRule.dxfId = cf.dxf_id;
                out_cfRule.stopIfTrue = cf.stop_if_true;

                if ( cf.rule == "average_value" ) {
                    if ( cf.op == "std_dev_above_1" ) {
                        add_operands = 1;
                        out_cfRule.stdDev = 1;
                        out_cfRule.type = sml::ST_CfType::aboveAverage;
                        out_cfRule.aboveAverage = true;
                    } else if ( cf.op == "std_dev_above_2" ) {
                        add_operands = 1;
                        out_cfRule.stdDev = 2;
                        out_cfRule.type = sml::ST_CfType::aboveAverage;
                        out_cfRule.aboveAverage = true;
                    } else if ( cf.op == "std_dev_above_3" ) {
                        add_operands = 1;
                        out_cfRule.stdDev = 3;
                        out_cfRule.type = sml::ST_CfType::aboveAverage;
                        out_cfRule.aboveAverage = true;
                    } else if ( cf.op == "std_dev_below_1" ) {
                        add_operands = 1;
                        out_cfRule.stdDev = 1;
                        out_cfRule.type = sml::ST_CfType::aboveAverage;
                        out_cfRule.aboveAverage = false;
                    } else if ( cf.op == "std_dev_below_2" ) {
                        add_operands = 1;
                        out_cfRule.stdDev = 2;
                        out_cfRule.type = sml::ST_CfType::aboveAverage;
                        out_cfRule.aboveAverage = false;
                    } else if ( cf.op == "std_dev_below_3" ) {
                        add_operands = 1;
                        out_cfRule.stdDev = 3;
                        out_cfRule.type = sml::ST_CfType::aboveAverage;
                        out_cfRule.aboveAverage = false;
                    } else if ( cf.op.length() > 0 ) {
                        if ( cf.op[0] == '>' ) {
                            out_cfRule.type = sml::ST_CfType::aboveAverage;
                            out_cfRule.aboveAverage = true;
                        } else if ( cf.op[0] == '<' ) {
                            out_cfRule.type = sml::ST_CfType::aboveAverage;
                            out_cfRule.aboveAverage = false;
                        }
                        if ( cf.op.length() == 2 && cf.op[1] == '=' ) {
                            out_cfRule.equalAverage = true;
                        }
                    }
                } else if ( cf.rule == "text" ) {
                    if ( cf.operands.size() > 0 ) {
                        out_cfRule.text = cf.operands[0];
                        std::stringstream formula;
                        if ( cf.op == "begins_with" ) {
                            out_cfRule.type = sml::ST_CfType::beginsWith;
                            formula << "LEFT(";
                            formula << range_part[0];
                            formula << ",";
                            formula << cf.operands[0].length();
                            formula << ")=\"";
                            formula << cf.operands[0];
                            formula << "\"";
                            out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::beginsWith;
                            out_cfRule.formula.push_back( formula.str() );
                        } else if ( cf.op == "ends_with" ) {
                            out_cfRule.type = sml::ST_CfType::endsWith;
                            formula << "RIGHT(";
                            formula << range_part[0];
                            formula << ",";
                            formula << cf.operands[0].length();
                            formula << ")=\"";
                            formula << cf.operands[0];
                            formula << "\"";
                            out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::endsWith;
                            out_cfRule.formula.push_back( formula.str() );
                        } else if ( cf.op == "contained" ) {
                            out_cfRule.type = sml::ST_CfType::containsText;
                            formula << "NOT(ISERROR(SEARCH(\"";
                            formula << cf.operands[0];
                            formula << "\",";
                            formula << range_part[0];
                            formula << ")))";
                            out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::containsText;
                            out_cfRule.formula.push_back( formula.str() );
                        }
                    } else {
                        valid = false;
                    }
                } else if ( cf.rule == "cell_value" ) {
                    out_cfRule.type = sml::ST_CfType::cellIs;
                    if ( cf.op == "<" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::lessThan;
                    } else if ( cf.op == "<=" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::lessThanOrEqual;
                    } else if ( cf.op == "=" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::equal;
                    } else if ( cf.op == "<>" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::notEqual;
                    } else if ( cf.op == ">=" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::greaterThanOrEqual;
                    } else if ( cf.op == ">" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::greaterThan;
                    } else if ( cf.op == "between" ) {
                        add_operands = 2;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::between;
                    } else if ( cf.op == "not_between" ) {
                        add_operands = 2;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::notBetween;
                    } else if ( cf.op == "contained" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::containsText;
                    } else if ( cf.op == "not_contained" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::notContains;
                    } else if ( cf.op == "begins_with" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::beginsWith;
                    } else if ( cf.op == "ends_with" ) {
                        add_operands = 1;
                        out_cfRule._operator_ = sml::ST_ConditionalFormattingOperator::endsWith;
                    }
                } else if ( cf.rule == "color_scale" ) {
                    valid = false;

                } else if ( cf.rule == "blanks" ) {
                    out_cfRule.type = sml::ST_CfType::containsBlanks;
                    out_cfRule.formula.push_back( "LEN(TRIM(" + cellReference + "))=0" );
                } else if ( cf.rule == "errors" ) {
                    out_cfRule.type = sml::ST_CfType::containsErrors;
                    out_cfRule.formula.push_back( "ISERROR(" + cellReference + ")" );
                } else if ( cf.rule == "duplicate_value" ) {
                    out_cfRule.type = sml::ST_CfType::duplicateValues;
                } else if ( cf.rule == "formula_true" ) {
                    out_cfRule.type = sml::ST_CfType::expression;
                    add_operands = 1;
                } else if ( cf.rule == "no_blanks" ) {
                    out_cfRule.type = sml::ST_CfType::notContainsBlanks;
                    out_cfRule.formula.push_back( "LEN(TRIM(" + cellReference + "))>0" );
                } else if ( cf.rule == "no_errors" ) {
                    out_cfRule.type = sml::ST_CfType::notContainsErrors;
                    out_cfRule.formula.push_back( "NOT(ISERROR(" + cellReference + "))" );
                } else if ( cf.rule == "unique_value" ) {
                    out_cfRule.type = sml::ST_CfType::uniqueValues;
                } else if ( cf.rule == "bottom" ) {
                    out_cfRule.type = sml::ST_CfType::top10;
                    out_cfRule.bottom = true;
                    int rank;
                    if ( string_utils::parse( cf.op, rank ) ) {
                        if ( 0 != rank ) {
                            out_cfRule.rank = rank;
                        } else {
                            out_cfRule.rank = 10;
                        }
                    }
                    if ( !cf.operands.empty() ) {
                        sml::CT_Extension operand;
                        operand.uri = cf.operands[0];
                        out_cf.extLst.getset().ext.push_back( operand );
                    }
                } else if ( cf.rule == "bottom_percent" ) {
                    out_cfRule.type = sml::ST_CfType::top10;
                    out_cfRule.bottom = true;
                    out_cfRule.percent = true;
                    int rank;
                    if ( string_utils::parse( cf.op, rank ) ) {
                        if ( 0 != rank ) {
                            out_cfRule.rank = rank;
                        } else {
                            out_cfRule.rank = 10;
                        }
                    }
                    if ( !cf.operands.empty() ) {
                        sml::CT_Extension operand;
                        operand.uri = cf.operands[0];
                        out_cf.extLst.getset().ext.push_back( operand );
                    }
                } else if ( cf.rule == "top" ) {
                    out_cfRule.type = sml::ST_CfType::top10;
                    int rank;
                    if ( string_utils::parse( cf.op, rank ) ) {
                        if ( 0 != rank ) {
                            out_cfRule.rank = rank;
                        } else {
                            out_cfRule.rank = 10;
                        }
                    }
                    if ( !cf.operands.empty() ) {
                        sml::CT_Extension operand;
                        operand.uri = cf.operands[0];
                        out_cf.extLst.getset().ext.push_back( operand );
                    }
                } else if ( cf.rule == "top_percent" ) {
                    out_cfRule.type = sml::ST_CfType::top10;
                    out_cfRule.percent = true;
                    int rank;
                    if ( string_utils::parse( cf.op, rank ) ) {
                        if ( 0 != rank ) {
                            out_cfRule.rank = rank;
                        } else {
                            out_cfRule.rank = 10;
                        }
                    }
                    if ( !cf.operands.empty() ) {
                        sml::CT_Extension operand;
                        operand.uri = cf.operands[0];
                        out_cf.extLst.getset().ext.push_back( operand );
                    }
                } else {
                    valid = false;
                }

                if ( add_operands > cf.operands.size() ) {
                    valid = false;
                }

                for ( size_t o = 0; o < cf.operands.size() && o < add_operands; o++ ) {
                    out_cfRule.formula.push_back( cf.operands[o] );
                }

                if ( valid ) {
                    addGroup = true;
                    out_cf.cfRule.push_back( out_cfRule );
                }
            }
            if ( addGroup ) {
                out_map.push_back( out_cf );
            }
        }
    }

    void persistent_conditional_formats::load_rule(
        const std::vector <sml::CT_CfRule >& in_rule_map,
        const persistent_theme& theme,
        conditional_format_manager& cf_manager,
        session& s,
        const rectangle_list_type& range,
        const persistent_styles& styles,
        const bool is_core3,
        const std::string additional_param/* = ""*/ )

    {
        for ( std::vector< sml::CT_CfRule >::const_reverse_iterator ruleIt = in_rule_map.rbegin(); ruleIt != in_rule_map.rend(); ruleIt++ ) {
            std::stringstream               rule;
            std::vector< std::string >      text_operands;
            variant::sparse_array_type      rule_operands;
            bool                            valid = false;
            bool                            skip_formulas = false;

            switch ( ruleIt->type.get() ) {
                case sml::ST_CfType::aboveAverage:
                    rule << "average_value(";
                    if ( ruleIt->stdDev.present() ) {
                        int sd = ruleIt->stdDev.get();
                        if ( sd > 0 && sd < 4 ) {
                            rule << "std_dev_";
                            rule << ( ruleIt->aboveAverage ? "above_" : "below_" );
                            rule << sd;
                            valid = true;
                        }
                    } else {
                        rule << ( ruleIt->aboveAverage ? ">" : "<" );
                        if ( ruleIt->equalAverage ) {
                            rule << "=";
                        }
                        valid = true;
                    }
                    break;
                case sml::ST_CfType::beginsWith:
                    rule << "text(begins_with";
                    skip_formulas = true;
                    valid = true;
                    break;
                case sml::ST_CfType::cellIs:
                    if ( ruleIt->_operator_.present() ) {
                        switch ( ruleIt->_operator_.get() ) {
                            case sml::ST_ConditionalFormattingOperator::lessThan:
                                rule << "cell_value(<";
                                break;
                            case sml::ST_ConditionalFormattingOperator::lessThanOrEqual:
                                rule << "cell_value(<=";
                                break;
                            case sml::ST_ConditionalFormattingOperator::equal:
                                rule << "cell_value(=";
                                break;
                            case sml::ST_ConditionalFormattingOperator::notEqual:
                                rule << "cell_value(<>";
                                break;
                            case sml::ST_ConditionalFormattingOperator::greaterThanOrEqual:
                                rule << "cell_value(>=";
                                break;
                            case sml::ST_ConditionalFormattingOperator::greaterThan:
                                rule << "cell_value(>";
                                break;
                            case sml::ST_ConditionalFormattingOperator::between:
                                rule << "cell_value(between";
                                break;
                            case sml::ST_ConditionalFormattingOperator::notBetween:
                                rule << "cell_value(not_between";
                                break;
                            case sml::ST_ConditionalFormattingOperator::containsText:
                                rule << "text(contained";
                                break;
                            case sml::ST_ConditionalFormattingOperator::notContains:
                                rule << "text(not_contained";
                                break;
                            case sml::ST_ConditionalFormattingOperator::beginsWith:
                                rule << "text(begins_with";
                                break;
                            case sml::ST_ConditionalFormattingOperator::endsWith:
                                rule << "text(ends_with";
                                break;
                        }
                        valid = true;
                    }
                    break;
                case sml::ST_CfType::colorScale: {
                    rule << "color_scale(";
                    std::vector<long> color_scale;
                    if ( ruleIt->colorScale.present() ) {
                        std::vector<sml::CT_Color>::const_iterator colIt;
                        for ( colIt = ruleIt->colorScale.get().color.begin(); colIt != ruleIt->colorScale.get().color.end(); colIt++ ) {
                            color_scale.push_back( persistent_color( *colIt, theme, styles.color_table() ).m_color );
                        }
                        if ( color_scale.size() > 1 ) {
                            rule_operands.push_back( css_utils::color2string( color_scale.front() ) );
                            rule_operands.push_back( css_utils::color2string( color_scale.back() ) );
                            valid = true;
                        }
                    }
                }
                break;
                case sml::ST_CfType::containsBlanks:
                    rule << "blanks(";
                    valid = true;
                    break;
                case sml::ST_CfType::containsErrors:
                    rule << "errors(";
                    valid = true;
                    break;
                case sml::ST_CfType::containsText:
                    rule << "text(contained";
                    skip_formulas = true;
                    valid = true;
                    break;
                case sml::ST_CfType::dataBar:
                    break;
                case sml::ST_CfType::duplicateValues:
                    rule << "duplicate_value(undefined";
                    valid = true;
                    break;
                case sml::ST_CfType::endsWith:
                    rule << "text(ends_with";
                    skip_formulas = true;
                    valid = true;
                    break;
                case sml::ST_CfType::expression:
                    rule << "formula_true(";
                    valid = true;
                    break;

                case sml::ST_CfType::iconSet:
                    break;
                case sml::ST_CfType::notContainsBlanks:
                    rule << "no_blanks(";
                    valid = true;
                    break;
                case sml::ST_CfType::notContainsErrors:
                    rule << "no_errors(";
                    valid = true;
                    break;
                case sml::ST_CfType::notContainsText:
                    break;
                case sml::ST_CfType::timePeriod:
                    break;
                case sml::ST_CfType::top10: {
                    rule << ( ruleIt->bottom ? "bottom" : "top" );
                    if ( ruleIt->percent ) {
                        rule << "_percent";
                    }
                    rule << "(";
                    if ( additional_param.empty() ) {
                        int rank = ruleIt->rank.present() ? ruleIt->rank.get() : 10;
                        rule << rank;
                    } else {
                        rule << additional_param;
                    }
                    valid = true;
                }
                break;
                case sml::ST_CfType::uniqueValues:
                    rule << "unique_value(undefined";
                    valid = true;
                    break;
            }

            if ( ruleIt->text.present() ) {
                rule_operands.push_back( ruleIt->text.get() );
            }

            if ( !valid ) {
                continue;
            }

            if ( !skip_formulas ) {
                for ( std::vector<sml::ST_Formula>::const_iterator fit = ruleIt->formula.begin(); fit != ruleIt->formula.end(); fit++ ) {
                    rule_operands.push_back( boost::replace_all_regex_copy( ( std::string )( *fit ), match_export_var_regex, atChr_str ) );
                }
            }


            rule << ";";
            if ( ruleIt->stopIfTrue ) {
                rule << "1";
            } else {
                rule << "0";
            }
            rule << ";)";

            set_conditional_format cf;
            cf.rule( rule.str() );

            if ( !rule_operands.empty() ) {
                cf.operands( rule_operands );
            }

            if ( ruleIt->dxfId.present() ) {

                if ( styles.has_dxf( ruleIt->dxfId.get() ) ) {
                    const persistent_dxf& dxf = styles.dxf_at( ruleIt->dxfId.get() );

                    const std::string style = dxf.style_str();
                    if ( !style.empty() ) {
                        cf.style( style );
                    }

                    if ( dxf.num_fmt.present() ) {
                        cf.format( dxf.num_fmt.get().m_format_code );
                    }

                    if ( dxf.protection.present() ) {
                        if ( dxf.protection.get().locked.present() ) {
                            cf.unlock_cells( dxf.protection.get().locked.get() );
                        }
                    }

                    if ( dxf.border.present() ) {
                        dxf.border.get().apply( cf );
                    }

                    for ( rectangle_list_type::const_iterator i = range.begin(), e = range.end(); i != e; i++ ) {
                        cf.selected_range( *i );
                    }
                    cf_manager.add( s, cf, is_core3 );
                }
            }
        }
    }
}
