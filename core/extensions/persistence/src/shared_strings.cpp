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

#include "shared_strings.hpp"

namespace xlsx
{

    namespace sml = spreadsheetml;

    void shared_strings::clear()
    {
        m_string_count          = 0;
        m_string_uniquecount    = 0;

        m_strings.clear();
        m_string_map.clear();
    }

    int shared_strings::register_string( const std::string& s )
    {
        std::map< std::string, int >::iterator it;

        ++m_string_count;

        if ( ( it = m_string_map.find ( s ) ) == m_string_map.end() ) {
            ++m_string_uniquecount;
            m_strings.push_back( s );
            m_string_map[s] = m_string_uniquecount - 1;
            return m_string_uniquecount - 1;
        }
        return it->second;
    }

    void shared_strings::store( std::ostream& os )  const
    {

        sml::sml_sharedStringTable    doc;
        sml::CT_Sst&                    sst = doc.sst.getset();
        sml::CT_Rst                     rs;

        sst.count               = m_string_count;
        sst.uniqueCount         = m_string_uniquecount;

        for ( size_t i = 0; i < m_strings.size(); i++ ) {
            rs.t    = m_strings[i];
            sst.si.push_back( rs );
        }

        const_cast< shared_strings* >( this )->serialize_doc( os, doc );
    }

    void shared_strings::load( package::ipackage& package )
    {
        if ( !package.exists( "xl/sharedStrings.xml" ) ) {
            return;
        }

        sml::sml_sharedStringTable sstDoc;
        parse_doc( package.get( "xl/sharedStrings.xml" ), sstDoc );

        if ( !sstDoc.sst.present() ) {
            return;
        }

        const sml::CT_Sst& sst = sstDoc.sst.get();

        m_strings.clear();

        for ( std::vector< sml::CT_Rst >::const_iterator i = sst.si.begin(); i != sst.si.end(); i++ ) {
            if ( i->t.present() ) {
                m_strings.push_back( i->t.get() );
            } else {
                //ignore formatting info and just concate parts
                std::stringstream text;
                for ( std::vector<sml::CT_RElt>::const_iterator r = i->r.begin(); r != i->r.end(); r++ ) {
                    text << ( const std::string& ) r->t;
                }
                m_strings.push_back( text.str() );
            }
        }
    }

    std::string shared_strings::at( int idx )
    {
        if ( idx < 0 || idx >= static_cast<int>( m_strings.size() ) ) {
            std::stringstream buf;
            buf << "invalid ID: " << idx;
            return buf.str();
        }

        return m_strings.at( idx );
    }
}
