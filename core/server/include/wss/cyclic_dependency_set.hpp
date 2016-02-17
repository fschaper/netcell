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
#include <wss/type.hpp>
#include <wss/sheet_point.hpp>
#include <wss/i_dependency.hpp>

#pragma once

struct cyclic_dependency_set_traits {
    inline bool operator()( const shared_dependency_type& lhs, const shared_dependency_type& rhs ) const {
        const sheet_point lhs_position = lhs->position();
        const sheet_point rhs_position = rhs->position();
        if ( lhs_position.row() == rhs_position.row() ) {
            if ( lhs_position.column() == rhs_position.column() ) {
                return lhs.get() < rhs.get();
            } else {
                return lhs_position.column() < rhs_position.column();
            }
        }
        return lhs_position.row() < rhs_position.row();
    }
};

struct cyclic_dependency_set {

    typedef dependency_set_type cyclic_dependency_set_type;

    typedef std::set<shared_dependency_type, cyclic_dependency_set_traits> sorted_cyclic_dependency_set_type;

    cyclic_dependency_set() : change_in_value( false ) {}

    inline void new_round() {
        change_in_value = false;
    }

    inline void value_changed() {
        change_in_value = true;
    }

    inline bool got_value_change() const {
        return change_in_value;
    }

    inline bool check_if_cyclic( const shared_dependency_type& d ) const {
        return cyclic_deps.find( d ) != cyclic_deps.end();
    }

    inline cyclic_dependency_set_type& cyclic_dependencies() {
        return cyclic_deps;
    }

    inline sorted_cyclic_dependency_set_type sorted_dependencies() {
        return sorted_cyclic_dependency_set_type( cyclic_deps.begin(), cyclic_deps.end() );
    }

    inline void clear() {
        cyclic_deps.clear();
    }
private:
    cyclic_dependency_set_type cyclic_deps;
    bool change_in_value;
};
