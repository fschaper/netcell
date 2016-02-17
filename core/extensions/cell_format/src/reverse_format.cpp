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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "reverse_format.hpp"
#include "value_extractor.hpp"
#include "i18n.hpp"
#include "I18nException.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>



namespace cell_format
{
    void reverse_format::process_xml( const cfd::CT_ReverseFormats& input )
    {
        for ( std::vector< cfd::CT_ReverseFormat >::const_iterator i = input.ReverseFormat.begin(), e = input.ReverseFormat.end(); i != e; ++i ) {
            m_generic_values.push_back( key_val_type( i->rule, val_type( i->format, i->type ) ) );
        }
    }

    void reverse_format::localize_rule( std::string& rule, const ControlTokens& ct, const std::string& type )
    {

        std::vector<std::string> tokens;
        std::string localized_rule = "";
        std::string time_rule = "";

        if ( "date" == type ) {
            tokenize_rule( rule, tokens, "[:date_sep:]" );
            for ( size_t i = 0; i < tokens.size(); i++ ) {
                unsigned char idx = ct.date_order[i];
                switch ( idx ) {
                    case 0: {
                        if ( 3 == tokens.size() ) {
                            localized_rule += tokens[2];
                            if ( i != tokens.size() - 1 ) {
                                localized_rule += "[:date_sep:]";
                            }
                        }
                    }
                    break;
                    case 1: {
                        localized_rule += tokens[0];
                        if ( i != tokens.size() - 1 ) {
                            localized_rule += "[:date_sep:]";
                        }
                    }
                    break;
                    case 2: {
                        localized_rule += tokens[1];
                        if ( i != tokens.size() - 1 ) {
                            localized_rule += "[:date_sep:]";
                        }
                    }
                    break;
                }
            }

            rule = localized_rule;

        }

        if ( "date_time" == type ) {
            std::vector<std::string> date_time_tokens;
            tokenize_rule( rule, date_time_tokens, " " );
            tokenize_rule( date_time_tokens[ date_time_tokens.size() - 1 ], tokens, "[:date_sep:]" );
            for ( size_t i = 0; i < tokens.size(); i++ ) {
                unsigned char idx = ct.date_order[i];
                switch ( idx ) {
                    case 0: {
                        if ( 3 == tokens.size() ) {
                            localized_rule += tokens[2];
                            if ( i != tokens.size() - 1 ) {
                                localized_rule += "[:date_sep:]";
                            }
                        }
                    }
                    break;
                    case 1: {
                        localized_rule += tokens[0];
                        if ( i != tokens.size() - 1 ) {
                            localized_rule += "[:date_sep:]";
                        }
                    }
                    break;
                    case 2: {
                        localized_rule += tokens[1];
                        if ( i != tokens.size() - 1 ) {
                            localized_rule += "[:date_sep:]";
                        }
                    }
                    break;
                }
            }


            for ( size_t i = 0; i < date_time_tokens.size() - 1; i++ ) {
                time_rule += date_time_tokens[i];
                if ( i != date_time_tokens.size() - 2 ) {
                    time_rule += " ";
                }
            }

            localized_rule = time_rule + " " + localized_rule;

            rule = localized_rule;

        }

        if ( "bool" == type ) {
            //translate true/false
            std::string true_false = "";
            true_false += ct.booleans.true_name;
            true_false += "|";
            true_false += ct.booleans.false_name;
            boost::replace_all( rule, "true|false", true_false );
        }

        //upgrade digit grouping
        boost::replace_all( rule, "[:thousand_sep:]", std::string( "[" ) + ct.format_codes.thousand_separator + "]" );
        //upgrade decimal separator
        boost::replace_all( rule, "[:decimal_sep:]", std::string( "[" ) + ct.format_codes.decimal + "]" );
        //upgrade currency symbol
        boost::replace_all( rule, "[:currency_symbol:]", /* std::string( "(" ) + */ ct.format_codes.currency /*+ ")"*/ );
        boost::replace_all( rule, "$", "[$]" );
        //upgrade date separators
        std::string date_sep = "[";
        for ( size_t i = 0; i < ct.format_codes.date_separators.size() - 1; i++ ) {
            date_sep += ct.format_codes.date_separators[i];
            date_sep += '|';
        }
        date_sep += ct.format_codes.date_separators[ct.format_codes.date_separators.size()-1];
        date_sep += "]";
        boost::replace_all( rule, "[:date_sep:]", date_sep );
        //upgrade short month sequences
        std::string short_month = "(";
        for ( size_t i = 0; i < 11; i++ ) {
            short_month += ct.months[i].short_name + "|";
        }
        short_month += ct.months[11].short_name + ")";
        boost::replace_all( rule, "[:short_month:]", short_month );

        //upgrade long month sequences
        std::string long_month = "(";
        for ( size_t i = 0; i < 11; i++ ) {
            long_month += ct.months[i].long_name + "|";
        }
        long_month += ct.months[11].long_name + ")";
        boost::replace_all( rule, "[:long_month:]", long_month );

        //upgrade time separator
        std::string time_sep = "[";
        for ( size_t i = 0; i < ct.format_codes.time_separators.size() - 1; i++ ) {
            time_sep += ct.format_codes.time_separators[i];
            time_sep += '|';
        }
        time_sep += ct.format_codes.time_separators[ct.format_codes.time_separators.size()-1];
        time_sep += "]";
        boost::replace_all( rule, "[:time_sep:]", time_sep );
    }

    void reverse_format::localize_format( std::string& format, const ControlTokens& ct )
    {
        boost::replace_all( format, "[$]", ct.format_codes.currency );
    }

    void reverse_format::load_locale( const locale& l )
    {
        const           ControlTokens&      ct = i18n::instance()[ l ];
        map_type        localized_values;
        for ( map_type::const_iterator i = m_generic_values.begin(), e = m_generic_values.end(); i != e; i++ ) {
            std::string rule = i->first;
            std::string format = i->second.first;
            std::string type = i->second.second;
            localize_rule( rule, ct, type );
            localize_format( format, ct );
            localized_values.push_back( key_val_type( rule, val_type( format, i->second.second ) ) );
        }
        m_localized_values[l] = localized_values;
    }

    bool reverse_format::find_format( const locale& l, const std::string& formatted_value, variant& value, std::string& format )
    {
        map_type    localized_values = m_localized_values[l];
        if ( localized_values.empty() ) {
            try {
                load_locale( l );
                localized_values = m_localized_values[l];
            } catch ( cell_format::I18nException e ) {
                //throw std::logic_error( "unknown locale" );
                return false;
            }
        }

        std::string lower_case_value = formatted_value;
        for ( size_t i = 0;  i < lower_case_value.size(); i++ ) {
            lower_case_value[i] = std::tolower( lower_case_value[i], std::locale() );
        }

        for ( map_type::const_iterator i = localized_values.begin(), e = localized_values.end(); i != e; i++ ) {
            boost::smatch smatch;
            if ( boost::regex_match( lower_case_value, smatch, boost::regex( i->first, boost::regex::perl ) ) ) {
                format = i->second.first;
                try {
                    value = value_extractor( i18n::instance()[ l ] )( lower_case_value, i->second.second );
                    return true;
                } catch ( std::bad_cast& ) { //any conversion error should be masked. go for the next match
                } catch ( std::logic_error& ) { //any conversion error should be masked. go for the next match
                }
            }
        }

        return false;
    }


    void reverse_format::tokenize_rule( const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters )
    {
        std::string s = str;
        std::string::size_type pos = s.find( delimiters );

        while ( pos != s.npos ) {
            tokens.push_back( std::string( s.begin(), s.begin() + pos ) );
            s = std::string( s.begin() + pos + delimiters.length(), s.end() );
            pos = s.find( delimiters );
        }

        tokens.push_back( s );
    }
}
