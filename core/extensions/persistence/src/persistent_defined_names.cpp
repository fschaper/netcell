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

#include "persistent_defined_names.hpp"
#include "wss/variant.hpp"
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

namespace xlsx
{

    void persistent_defined_names::register_names( const i_named_formula_manager::named_formula_list_type& defined_names, optional<int> sheet_id, const ::locale& l )
    {
        foreach( const i_named_formula_manager::named_formula_key_val_vec_type & nf_key_val, defined_names ) {
            persistent_defined_name     crt_name;

            bool workbook_scope = true;
            crt_name.local_sheet_id = sheet_id;
            for ( i_named_formula_manager::named_formula_key_val_vec_type::const_iterator item = nf_key_val.begin(); item != nf_key_val.end(); item++ ) {
                if ( "name" == item->first ) {
                    crt_name.name = item->second.as_string( l );
                }
                if ( "comment" == item->first ) {
                    crt_name.comment = item->second.as_string( l );
                }
                if ( "refers_to" == item->first ) {
                    crt_name.formula = item->second.as_string( l );
                }
                if ( "scope" == item->first ) {
                    workbook_scope = "Workbook" == item->second.as_string( l );
                }
                if ( "hidden" == item->first ) {
                    crt_name.hidden = true;
                    workbook_scope = "Workbook" == item->second.as_string( l );
                }
            }

            if ( !sheet_id.present() && !workbook_scope ) {
                continue;
            }

            if ( !crt_name.name.empty() && !crt_name.formula.empty() ) {
                m_defined_names.push_back( crt_name );
            }
        }
    }

    void persistent_defined_names::store( sml::CT_DefinedNames& out_dns ) const
    {
        if ( m_defined_names.empty() ) {
            return;
        }

        for ( std::vector< persistent_defined_name >::const_iterator i = m_defined_names.begin(); i != m_defined_names.end(); i++ ) {
            i->store( out_dns );
        }
    }

    void persistent_defined_names::clear()
    {
        m_defined_names.clear();
    }
}
