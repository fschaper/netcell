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
 *  <a href=<wss/http://www.jedox.com/license_palo_bi_suite.txt>>
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

#pragma once

#include <wss/type.hpp>
#include <wss/indexed_mapping.hpp>
#include <wss/i_dependency_reference.hpp>
#include <wss/i_dependency.hpp>
#include <wss/reference_table.hpp>
#include <wss/flyweight_types.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <vector>
#endif
/*!
 * \brief
 * references in combination with their reference count and the information if they are currently dirty
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
struct location_dependent_references {

    location_dependent_references() : is_dirty( true ), volatile_count( 0 ) {}
    //TODO use the volatile count here
    bool is_dirty;
    size_t volatile_count;
    referencetable_type reference;
};

/*!
 * \brief
 * opcode
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct opcode {
    typedef std::vector<char> sequence_type;
    typedef internal_flyweights::opcode_string_type opcode_string_type;
    typedef indexed_mapping<opcode_string_type> stringtable_type;

    // the opcode sequence
    sequence_type code;
    // list of references referred to by the opcode
    location_dependent_references location_dependent_reference;
    // stringtable
    stringtable_type stringtable;
};

/*!
 * \brief
 * opcode in combination with a position on the sheet
 * and references adjusted for every target dependency that needs this opcode
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
struct positioned_op_codes : boost::noncopyable {
    typedef map_to_use<i_dependency*, location_dependent_references>::type location_dependent_opcode_map_type;

    typedef boost::shared_ptr<location_dependent_opcode_map_type> shared_location_dependent_opcode_map_type;

    positioned_op_codes( const sheet_point& position = sheet_point( 0, 0 ) )
        : position( position )
        , location_dependent_opcodes( new location_dependent_opcode_map_type() )
        , is_relative( false ) {}
    positioned_op_codes( const opcode& other )
        : original_opcode( other )
        , position( sheet_point( 0, 0 ) )
        , location_dependent_opcodes( new location_dependent_opcode_map_type() )
        , is_relative( false ) {}

    location_dependent_opcode_map_type::iterator add_position( const shared_dependency_type& target_dependency );

    void remove_position( i_dependency* target_dependency );

    void update_position( const shared_dependency_type& target_dependency, const geometry::point& distance, bool move_absolute_references = false  );

    location_dependent_references& positional_references( const shared_dependency_type& target_dependency );

    const location_dependent_references& positional_references( const shared_dependency_type& target_dependency ) const;

    opcode original_opcode;

    sheet_point position;
    shared_location_dependent_opcode_map_type location_dependent_opcodes;
    bool is_relative;
};
