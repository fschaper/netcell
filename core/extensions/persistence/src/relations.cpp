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

#include "relations.hpp"
#include <sstream>

namespace xlsx
{

    namespace export_helpers
    {

        std::string relations::add( const std::string& target, const std::string& type )
        {

            std::stringstream ids;
            ids << "rId" << m_relations.size() + 1;

            std::string id = ids.str();

            relation r;

            r.id        = id;
            r.type      = type;
            r.target    = target;
            m_relations.push_back( r );

            return id;
        }

        std::string relations::add( const std::string& target, const std::string& target_mode, const std::string& type )
        {

            const std::string& id = add( target, type );
            std::vector< relation >::iterator it  = ( m_relations.end() - 1 );
            it->target_mode = target_mode;
            return id;
        }

        void relations::serialize( std::ostream& o )
        {

            o << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>";
            o << "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">";

            for ( size_t i = 0; i < m_relations.size(); i++ ) {
                if ( m_relations[i].target_mode.empty() ) {
                    o << "<Relationship Id=\"" << m_relations[i].id << "\" Type=\"" << m_relations[i].type << "\" Target=\"" << m_relations[i].target << "\" />";
                } else {
                    o << "<Relationship Id=\"" << m_relations[i].id << "\" Type=\"" << m_relations[i].type << "\" Target=\"" << m_relations[i].target << "\" TargetMode=\"" << m_relations[i].target_mode << "\" />";
                }
            }
            o << "</Relationships>";
        }

        void relations::deserialize( const rels_ns::CT_Relationships& input )
        {
            for ( std::vector< rels_ns::CT_Relationship >::const_iterator i = input.Relationship.begin(); i != input.Relationship.end(); i++ ) {
                relation r;
                if ( i->Id.present() ) {
                    r.id = i->Id.get();
                }

                if ( i->Type.present() ) {
                    r.type = i->Type.get();
                }

                if ( i->Target.present() ) {
                    r.target = i->Target.get();
                }

                if ( i->TargetMode.present() ) {
                    r.target_mode = i->TargetMode.get();
                }

                m_relations.push_back( r );
            }
        }

        std::string relations::get( const std::string& id )
        {
            for ( std::vector< relation >::const_iterator i = m_relations.begin(); i != m_relations.end(); i++ ) {
                if ( i->id == id ) {
                    return i->target;
                }
            }

            return "";
        }

        const std::vector< relations::relation >& relations::list() const
        {
            return m_relations;
        }

        void relations::clear()
        {
            m_relations.clear();
        }

    }

}
