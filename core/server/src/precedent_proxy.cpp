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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"

#include "wss/precedent_proxy.hpp"
#include "wss/i_dependency.hpp"
#include "wss/invalid_reference_exception.hpp"
#include "wss/define.hpp"

#include "cell_manager.hpp"

precedent_proxy::precedent_proxy( const shared_dependency_type& issuing_dependency )
    : m_issuing_dependency( issuing_dependency )
{
    foreach( const reference_info & ri, issuing_dependency->precedents() ) {
        // we only care about range references
        if (  ri.is_valid() && ri->type() == i_dependency_reference::range_reference ) {
            // only cache valid references
            try {
                m_cached_references[ ri->worksheet() ][ range_reference_cast( ri ).actualize().position() ] = ri;
            } catch ( const invalid_reference_exception& ) {
                // we ignore invalid range references here.
            }
        }
    }
}

precedent_proxy::precedent_proxy( const shared_dependency_type& issuing_dependency, const referencetable_type& precedents )
    : m_issuing_dependency( issuing_dependency )
{
    foreach( const reference_info & ri, precedents ) {
        // we only care about range references
        if ( ri.is_valid() && ri->type() == i_dependency_reference::range_reference ) {
            // only cache valid references
            try {
                m_cached_references[ ri->worksheet() ][ range_reference_cast( ri ).actualize().position() ] = ri;
            } catch ( const invalid_reference_exception& ) {
                // we ignore invalid range references here.
            }
        }
    }
}

shared_reference_type precedent_proxy::register_dependency( cell_manager& cm, const sheet_range& area_of_interest, const bool inside_nf )
{
    shared_reference_type& return_value = m_cached_references[ cm.associated_worksheet() ][ area_of_interest ];
    if ( ! return_value ) {
        return_value = cm.register_dependency( m_issuing_dependency, area_of_interest, inside_nf );
    }
    return return_value;
}

const shared_dependency_type& precedent_proxy::initiator() const
{
    return m_issuing_dependency;
}

