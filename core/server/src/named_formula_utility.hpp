/**
 *  \file
 *  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 *
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include "wss/non_instantiable.hpp"
#include "wss/i_named_formula_manager.hpp"
#include "wss/calculation_context.hpp"
#include "wss/named_formula_scope.hpp"
#include "wss/session.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <string>
#   include <map>
#endif // HAS_PRECOMPILED_HEADER == 0

class named_formula;
class sheet_point;

namespace named_formula_utils
{
    class named_formula_utility
        : public non_instantiable
    {
    public:
        static i_named_formula_manager::key_val_vec_type get_key_val_vec( session& s, const named_formula& nf, const sheet_point& position );

        template<typename return_type>
        static return_type to_vector( session& s, const named_formula& nf, const sheet_point& position );

        static void copy_to_sheet( session& s, const named_formula& nf, const shared_worksheet_type& target_ws, const bool is_clone_sheet );

        static utf8_ci_string scope_as_string( const named_formula& nf );

        static bool check_scope_ws_same( const uuid_type& scope_ws_id, const named_formula& nf );

    };
}
