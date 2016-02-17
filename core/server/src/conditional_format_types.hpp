/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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

#include "wss/type.hpp"


namespace cf
{
    //this is just a trick to enforce the right usage of internal and external lookup ids, external ids are uints..
    typedef boost::int_fast32_t internal_lookup_id_type;

    class conditional_format_rank;

    //a few typedefs to make life easier
    typedef set_to_use<internal_lookup_id_type>::type internal_id_set_type;
    typedef map_to_use< internal_lookup_id_type, sheet_range::rectangles_type>::type id_affected_range_map_type;
    typedef std::list<internal_lookup_id_type> internal_id_list_type;
    typedef std::vector<internal_id_list_type> internal_id_list_vec_type;
    typedef std::pair<internal_id_set_type, internal_id_list_vec_type> all_ids_plus_cell_ids_type;
}
