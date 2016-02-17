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

#include "content_types.hpp"
#include <algorithm>

namespace xlsx
{

    namespace export_helpers
    {

        void content_types::add( const std::string& part_name, const std::string& content_type )
        {

            m_overrides.push_back( override_entry( part_name, content_type )  );
        }

        void content_types::register_img_extension( const std::string& name )
        {
            if ( m_imgs.end() != std::find( m_imgs.begin(), m_imgs.end(), name ) ) {
                return;
            }
            m_imgs.push_back( name );
        }

        void content_types::serialize( std::ostream& o )
        {

            o << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>";
            o << "<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">";
            o << "<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>";
            o << "<Default Extension=\"xml\" ContentType=\"application/xml\"/>";
            for ( std::vector< std::string >::const_iterator i = m_imgs.begin(); i != m_imgs.end(); i++ ) {
                o << "<Default Extension=\"" + *i + "\" ContentType=\"image/" + *i + "\"/>";
            }
            for ( size_t i = 0; i < m_overrides.size(); i++ ) {
                o << "<Override PartName=\"" + m_overrides[i].part_name + "\" ContentType=\"" + m_overrides[i].content_type + "\"/>";
            }
            o << "</Types>";
        }

        void content_types::clear()
        {
            m_overrides.clear();
            m_imgs.clear();
        }


    }

}
