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

#include "precompiled_header.hpp"

#if !defined(FUNCTION_HAS_PRECOMPILED_HEADER ) || FUNCTION_HAS_PRECOMPILED_HEADER == 0
#   include "function_helper.hpp"
#   include <boost/regex.hpp>  // for SEARCH with wildcards
#   include <boost/range/as_array.hpp>
#   include <boost/foreach.hpp>
#   include <wss/variant_conversion_exception.hpp>
#   define foreach BOOST_FOREACH
#endif // FUNCTION_HAS_PRECOMPILED_HEADER == 0



struct calculate_search {
    static variant transform( const variant& f, const variant& t, const variant& b, const locale& l ) {
        try {
            const int begin = static_cast<int>( b.as_double() ) - 1;
            if ( begin < 0 ) {
                return variant( variant::error_value );
            }
            std::string text = t.as_string( l );
            if ( text.empty() ) {
                return variant( variant::error_value );
            }
            std::string find = f.as_string( l );
            // You can use the wildcard characters, question mark(?) and asterisk(*), in search.
            // If you want to find an actual question mark or asterisk, type a tilde (~) before the character.
            // A question mark matches any single character; an asterisk matches any sequence of characters.
            // If you want to find an actual question mark or asterisk, type a tilde(~) before the character.

            // Transform all characters x that we do not wish to be treated as special characters to \x.
            // Transform "?" to "." and "*" to ".*". This approximates what users are used to form the DOS commandline.
            static const char nospecialchars[] = {'\\', '|', '.', '+', '(', ')', '{', '}', '[', ']', '^', '$' };

            foreach( char s, boost::as_array( nospecialchars ) ) {
                size_t i = 0;
                while ( 1 ) {
                    i = find.find_first_of( s, i );
                    if ( i != std::string::npos ) {
                        find.insert( i, "\\" );
                        i += 2;
                    } else {
                        break;
                    }
                }
            }


            // Transform "~?" to "\\?" and "~*" to "\\*".
            boost::replace_all( find, "~?", "\\?" );
            boost::replace_all( find, "~*", "\\*" );


            // Transform "?" to ".".
            boost::replace_all( find, "?", "." );

            // Transform "*" to ".*?" (non-greedy).
            boost::replace_all( find, "*", ".*?" );

            // always start from the beginning
            //find.insert( 0, "^" );
            //if ( *( find.end() - 1 ) != '*' && *( find.end() - 2 ) != '\\' ) {
            //    find.push_back( '$' );
            //}

            //TODO: this function needs to work on arrays too
            const boost::regex reg( find );
            boost::smatch m;
            std::string::const_iterator start, end;
            start = text.begin() + begin;
            end = text.end();
            boost::match_results<std::string::const_iterator> what;

            if ( boost::regex_search( start, end, what, reg ) ) {
                size_t pos = 0;
                pos = what.position();
                return variant( static_cast<double>( pos + 1 + begin ) );
            }
        } catch ( const variant_conversion_exception& ) {}

        // If find is not found, the #VALUE! error value is returned.
        return variant( variant::error_value );

    }
};

/*!
* \brief
* SEARCH returns the number of the character at which a specific character
* or find string is first found, beginning with begin+1.
*
* \param function_parameter& parameters
* container of parameters and context which holds information about the current calculation state
*
* \param base_node& n
* AST presentation of the formula currently being calculated.
*
* \returns
* the number of the character at which a specific character or find string is first found
*
* \details
* Use SEARCH to determine the location of a character or find string within another text string.
* You can use the wildcard characters, question mark(?) and asterisk(*), in find.
* If you want to find an actual question mark or asterisk, type a tilde (~) before the character.
* A question mark matches any single character; an asterisk matches any sequence of characters.
* If you want to find an actual question mark or asterisk, type a tilde(~) before the character.
*
* \see
* function_searchb | function_find | function_findb | function_mid | function_replace | function_substitute
*
* \author
* Florian Schaper <florian.schaper@jedox.com>
* Matthias Roy <matthias.roy@jedox.com>
* Vali Nitu <vali@yalos-solutions.com>
*/
interpreter_variant function_search( function_parameter& parameters )
{
    if ( parameters.count() < 2 || parameters.count() > 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( 3 == parameters.count() ) {
        return function_helper::create_array_or_return_single_value<variant, variant, variant, calculate_search>( parameters[0], parameters[1], parameters[2], parameters.context().locale() );
    }
    variant v( 1.0 );
    return function_helper::create_array_or_return_single_value<variant, variant, variant, calculate_search>( parameters[0], parameters[1], v, parameters.context().locale() );
}
