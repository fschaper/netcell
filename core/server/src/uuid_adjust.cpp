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

/*!
 * \brief
 * helper class to fix old uuids.
 *
 * \author
 * Radu Ialovoi <ialovoi.@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

#include "uuid_adjust.hpp"
#include "core_logging.hpp"

uuid_adjust::uuid_adjust( const std::string& broken_uuid )
{
#ifndef _CORE2_COMPATIBILITY_ON_UUIDS_
    assert( !"uuid_adjust should only be used if we need core2 compatibility!!" );
#endif

    tokenizer tokens( broken_uuid, separator( "-" ) );

    m_token_iter = tokens.begin();
    m_token_end  = tokens.end();

    if ( !advance( 8 ) ) {
        return;
    }
    m_well_formed_uuid_string += "-";

    if ( !advance( 4 ) ) {
        return;
    }
    m_well_formed_uuid_string += "-";

    if ( !advance( 4 ) ) {
        return;
    }
    m_well_formed_uuid_string += "-";

    if ( !advance( 4 ) ) {
        return;
    }
    m_well_formed_uuid_string += "-";

    advance( 12 );

}

uuid_adjust::uuid_adjust( const uuid_type& uuid ) : m_well_formed_uuid_string( boost::uuids::to_string( uuid ) )
{
    if ( std::string::npos == m_well_formed_uuid_string.find( "-0" ) && '0' != m_well_formed_uuid_string[0]  ) {
        return;
    }
    std::string str_buf( "" );
    str_buf.reserve( m_well_formed_uuid_string.size() );
    bool skip_zero = true;
    for ( size_t i = 0; i < m_well_formed_uuid_string.size(); i++ ) {
        const char crt_char = m_well_formed_uuid_string[i];
        if ( skip_zero && '0' == crt_char  ) {
        } else {
            skip_zero = '-' == crt_char;
            str_buf += crt_char;
        }
    }
    m_well_formed_uuid_string.swap( str_buf );
}

bool uuid_adjust::advance( const unsigned char group_size )
{
    if ( m_token_end == m_token_iter ) {
        return false;
    }

    for ( unsigned char i = group_size; i > m_token_iter->size(); i-- ) {
        m_well_formed_uuid_string += "0";
    }
    m_well_formed_uuid_string += *m_token_iter;
    m_token_iter++;
    return true;
}

uuid_adjust::operator const std::string&()
{
    return m_well_formed_uuid_string;
}
