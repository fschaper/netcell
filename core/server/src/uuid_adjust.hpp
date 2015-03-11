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
#include <wss/core2_compatibility.hpp>
#include <wss/type.hpp>

#pragma once


/*!
 * \brief
 * helper class to fix old uuids.
 *
 * \author
 * Radu Ialovoi <ialovoi.@yalos-solutions.com>
 */
class uuid_adjust
{
private:
    typedef boost::char_separator<char>                         separator;
    typedef boost::tokenizer< boost::char_separator< char > >   tokenizer;

    std::string                     m_well_formed_uuid_string;
    tokenizer::const_iterator       m_token_iter;
    tokenizer::const_iterator       m_token_end;

    uuid_adjust( const std::string& broken_uuid );
    uuid_adjust( const uuid_type& uuid );

    operator const std::string&();
    bool advance( const unsigned char group_size );

public:

#ifdef _CORE2_COMPATIBILITY_ON_UUIDS_

    inline static std::string cast_uuid( const uuid_type& uuid ) {
        return uuid_adjust( uuid );
    }

    inline static uuid_type cast_uuid( const std::string& uuid ) {
        return boost::lexical_cast<uuid_type>( static_cast<std::string>( uuid_adjust( uuid ) ) );
    }
    /*
        template<class return_type>
        inline static return_type cast_uuid( const std::string& uuid ) {
            return boost::lexical_cast<return_type>( uuid );
        }

        template<class return_type>
        inline static return_type cast_uuid( const ws_elem_id_type uuid ) {
            return boost::lexical_cast<return_type>( uuid );
        }
    */
#else

    inline static std::string cast_uuid( const uuid_type& uuid ) {
        return boost::uuids::to_string( uuid );
    }

    inline static uuid_type cast_uuid( const std::string& uuid ) {
        return boost::uuids::to_string( uuid );
    }

    template<class return_type>
    inline static return_type cast_uuid( const std::string& uuid ) {
        return boost::lexical_cast<return_type>( uuid );
    }

    template<class return_type>
    inline static return_type cast_uuid( const ws_elem_id_type uuid ) {
        return boost::lexical_cast<return_type>( uuid );
    }

#endif
};
