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

#pragma once

#include "wss/point.hpp"
#include "wss/type.hpp"
#include "wss/opcode.hpp"
#include "wss/sheet_dimension.hpp"

class cell_manager;

/*!
 * \brief
 * opcode rewriter for copy operations.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template < bool inside_nf = false >
class opcode_rewriterT
{
public:
    static void rewrite( const shared_dependency_type& target_dependency, const geometry::point& distance, bool is_rewrite_to_clone_sheet, referencetable_type& references_to_rewrite, const referencetable_type& references, bool move_absolute_references = false );

    static void rewrite( const shared_dependency_type& target_dependency, const geometry::point& distance, const sheet_range& source_range, referencetable_type& references_to_rewrite, const referencetable_type& references, bool move_absolute_references = false );

    static void adjust_legacy_references( const shared_dependency_type& target_dependency, const geometry::point& distance, referencetable_type& references_to_rewrite );
private:
    static void rewrite( const shared_dependency_type& target_dependency, const geometry::point& distance, referencetable_type& references_to_rewrite, bool is_conditional, bool is_rewrite_to_clone_sheet, const sheet_range& source_range, const referencetable_type& references, bool move_absolute_references = false );
};

typedef opcode_rewriterT<false> opcode_rewriter;
