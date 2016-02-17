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
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/

#include "precompiled_header.hpp"
#include "wss/opcode.hpp"
#include "abstract_dependency.hpp"
#include "wss/opcode_rewriter.hpp"

location_dependent_references& positioned_op_codes::positional_references( const shared_dependency_type& target_dependency )
{
    assert( "uninitialized target dependency passed to opcode!" && target_dependency  );
    if ( is_relative ) {
        location_dependent_opcode_map_type::iterator it( location_dependent_opcodes->find( target_dependency.get() ) );
        if ( it != location_dependent_opcodes->end() ) {
            return it->second;
        }
        return add_position( target_dependency )->second;
    } else {
        return original_opcode.location_dependent_reference;
    }
}

const location_dependent_references& positioned_op_codes::positional_references( const shared_dependency_type& target_dependency ) const
{
    return const_cast<positioned_op_codes*>( this )->positional_references( target_dependency );
}

positioned_op_codes::location_dependent_opcode_map_type::iterator positioned_op_codes::add_position( const shared_dependency_type& target_dependency )
{
    assert( "uninitialized target dependency passed to opcode!" && target_dependency );
    assert( "only add positional reference if we're relative!" && is_relative );
    location_dependent_references new_references( original_opcode.location_dependent_reference );
    opcode_rewriterT<true>::rewrite( target_dependency, position.distance( target_dependency->position() ), false, new_references.reference, referencetable_type() );
    return location_dependent_opcodes->insert(
               location_dependent_opcode_map_type::value_type( target_dependency.get(), new_references ) ).first;
}

void positioned_op_codes::remove_position( i_dependency* target_dependency )
{
    assert( "only add positional reference if we're relative!" && is_relative );
    location_dependent_opcodes->erase( target_dependency );
}

void positioned_op_codes::update_position( const shared_dependency_type& target_dependency, const geometry::point& distance, bool move_absolute_references )
{
    assert( "uninitialized target dependency passed to opcode!" && target_dependency  );
    assert( "only add positional reference if we're relative!" && is_relative );
    location_dependent_opcode_map_type::iterator it( location_dependent_opcodes->find( target_dependency.get() ) );
    if ( it == location_dependent_opcodes->end() ) {
        it = add_position( target_dependency );
    }
    opcode_rewriterT<true>::rewrite( target_dependency, distance, false, it->second.reference, it->second.reference, move_absolute_references );
    it->second.is_dirty = true;

}
