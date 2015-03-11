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

#include "persistent_nfmts.hpp"
#include "string_utils.hpp"
#include "oxml_utils.hpp"

namespace xlsx
{

    std::string persistent_nfmts::read_format( const ssmap& format_rules )
    {
        ssmap::const_iterator it;
        if ( ( it = format_rules.find( "__number-format" ) ) != format_rules.end() ) {
            return it->second;
        }
        return std::string();
    }

    bool persistent_nfmts::register_format( const ssmap& props, int& format_id )
    {
        std::string format_str = read_format( props );
        format_str = format_str == "general" ? "General" : format_str;

        //predefined
        format_id = oxml_utils::format_id( format_str );
        if ( format_id != -1 ) {
            return true;
        }


        std::map<std::string, int>::iterator it = m_nfmt_map.find( format_str );
        if ( it != m_nfmt_map.end() ) {
            format_id = m_nfmts[it->second].m_id;
            return true;
        }

        persistent_nfmt format;
        int i = ( int )m_nfmts.size();
        format.m_id = i + 500;
        format.m_format_code = format_str;
        m_nfmts.push_back( format );
        m_nfmt_map[format_str] = i;
        format_id = format.m_id;

        return true;
    }

    bool persistent_nfmts::empty() const
    {
        return m_nfmts.empty();
    }

    void persistent_nfmts::clear()
    {
        m_nfmts.clear();
        m_nfmt_map.clear();
    }

    void persistent_nfmts::store( sml::CT_NumFmts& out_nfs ) const
    {
        out_nfs.count = ( int )m_nfmts.size();
        for ( size_t i = 0; i < m_nfmts.size(); i++ ) {
            sml::CT_NumFmt out_nf;
            out_nf.numFmtId     = m_nfmts[i].m_id;
            out_nf.formatCode   = m_nfmts[i].m_format_code;
            out_nfs.numFmt.push_back( out_nf );
        }
    }

    void persistent_nfmts::load( const sml::CT_NumFmts& in_nfs )
    {
        m_nfmts.clear();
        m_nfmt_map.clear();

        for ( std::vector<sml::CT_NumFmt>::const_iterator it = in_nfs.numFmt.begin(); it != in_nfs.numFmt.end(); it++ ) {
            m_nfmts.push_back( persistent_nfmt( *it ) );
        }
    }

    const std::string persistent_nfmts::str( const size_t idx ) const
    {
        for ( std::vector< persistent_nfmt >::const_iterator i = m_nfmts.begin(); i != m_nfmts.end(); i++ ) {
            if ( idx == ( size_t )( i->m_id ) ) {
                if ( ";;;" == i->m_format_code ) {
                    return ";;;\" \"";
                } else {
                    return i->m_format_code;
                }
            }
        }

        return oxml_utils::format_code( idx );
    }

}
