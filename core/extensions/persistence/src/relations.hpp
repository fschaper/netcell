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

#pragma once

#include <string>
#include <ostream>
#include <vector>

#include <oxml/relationships.hpp>

namespace xlsx
{

    namespace export_helpers
    {

        class relations
        {
        public:
            struct relation {
                std::string     id;
                std::string     type;
                std::string     target;
                std::string     target_mode;
            };
        private:
            std::vector< relation > m_relations;
        public:

            std::string add( const std::string& target, const std::string& type );
            std::string add( const std::string& target, const std::string& target_mode, const std::string& type );
            void serialize( std::ostream& o );
            void deserialize( const rels_ns::CT_Relationships& input );

            std::string get( const std::string& id );
            const std::vector< relation >& list() const;
            void clear();
        };

    }

}
