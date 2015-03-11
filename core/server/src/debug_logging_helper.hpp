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

#pragma once

#include <wss/type.hpp>

#if defined(_DEBUG)
#   include "wss/a1conversion.hpp"
#   include "named_formula.hpp"
#   include "named_formula_dependency_wrapper.hpp"
#   include "wss/free_formula.hpp"

/*!
 * \brief
 * little helper to generate meaningful trace output for dependency identification
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class debug_logging_helper : non_instantiable
{
public:
    template<class ptr_type>
    static inline std::string get_identifier( ptr_type sd ) {
        return sd->get_debug_identifier();
    }

    //print the list of dependents
    template<class dependency_set_T>
    static inline std::string list_dependencies( const dependency_set_T& dependency_set ) {
        if ( dependency_set.empty() ) {
            return "LIST EMPTY!";
        }
        std::string return_val( "\n>>>starting list: \n" );
        foreach( const shared_dependency_type & current_d, dependency_set ) {
            return_val += ">>>\t";
            return_val += debug_logging_helper::get_identifier( current_d );
            return_val += "\n";
        }
        return_val += ">>>done with list";
        return return_val;
    }

};

#endif //_DEBUG
