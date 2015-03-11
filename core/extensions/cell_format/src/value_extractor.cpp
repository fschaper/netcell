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

#include "value_extractor.hpp"

#include "number_extractor.hpp"
#include "date_extractor.hpp"
#include "time_extractor.hpp"
#include "date_time_extractor.hpp"

namespace cell_format
{
    value_extractor::value_extractor ( const ControlTokens& ct ) : m_ct( ct )
    {
    }

    variant value_extractor::operator ()( const std::string& formatted_value, const std::string& type )
    {
        if ( "number" == type ) {
            return number_extractor( m_ct, formatted_value );
        } else if ( "bool" == type ) {
            if ( m_ct.booleans.true_name == formatted_value ) {
                return variant( true );
            } else if ( m_ct.booleans.false_name == formatted_value ) {
                return variant( false );
            } else {
                throw std::logic_error( "Invalid logical value" );
            }
        } else if ( "date" == type ) {
            return date_extractor( m_ct, formatted_value );
        } else if ( "time" == type ) {
            return time_extractor( m_ct, formatted_value );
        } else if ( "date_time" == type ) {
            return date_time_extractor( m_ct, formatted_value );
        }

        return variant();
    }

}
