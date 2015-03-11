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

#include "number_extractor.hpp"

#include <boost/tokenizer.hpp>

namespace cell_format
{
    class trim_to_number
    {
    private:
        char m_decimal_sep;
    public:
        trim_to_number( char decimal_sep ) :  m_decimal_sep( decimal_sep ) {}
        bool operator ()( char value ) {
            return ( value != m_decimal_sep ) && ( value != '+' ) && ( value != '-' ) && ( value < '0' || value > '9' );
        }
    };

    number_extractor::operator variant()
    {
        std::string             crt_value   = m_formatted_value;
        std::string::iterator   new_end     = std::remove_if( crt_value.begin(), crt_value.end(), trim_to_number( m_control_tokens.format_codes.decimal ) );
        crt_value.erase( new_end, crt_value.end() );
        for ( std::string::iterator i = crt_value.begin(), e = crt_value.end(); i != e; i++ ) {
            if ( *i == m_control_tokens.format_codes.decimal ) {
                *i = '.';
            }
        }
        if ( std::string::npos == m_formatted_value.find( '(' ) ) {
            return variant( boost::lexical_cast< double >( crt_value ) );
        } else {
            return variant( -boost::lexical_cast< double >( crt_value ) );
        }
    }

}
