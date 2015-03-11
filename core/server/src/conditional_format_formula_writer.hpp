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
#include <wss/define.hpp>
#include <wss/type.hpp>
#include "conditional_format_rule.hpp"

namespace cf
{
    class conditional_format_formula_writer : public non_instantiable
    {
        struct conditional_format_formula_writer_helper;
    public:
        static shared_free_formula_type create_formula( session& s, const conditional_format_rule& rule, const shared_worksheet_type& ws, const geometry::rectangle_type& range, const sheet_point& position );
        static shared_free_formula_type create_formula_for_move( session& s, const conditional_format_rule& rule, const shared_worksheet_type& ws, const geometry::rectangle_type& range, const sheet_point& old_position, const sheet_point& new_position );

    };
}
