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

#pragma once

#include "optional.hpp"
#include "simple_types.hpp"

#include "persistent_alignment.hpp"
#include "persistent_protection.hpp"

#include <oxml/sml-styles.hpp>

namespace xlsx
{

    namespace sml = spreadsheetml;

    struct persistent_xf {
        optional<int>                       num_fmt_id;
        optional<int>                       font_id;
        optional<int>                       fill_id;
        optional<int>                       border_id;
        optional<int>                       xf_id;
        optional<persistent_alignment>      alignment;
        optional<persistent_protection>     protection;

        optional<bool>                      apply_number_format;
        optional<bool>                      apply_font;
        optional<bool>                      apply_fill;
        optional<bool>                      apply_border;
        optional<bool>                      apply_alignment;
        optional<bool>                      apply_protection;

        bool                                quote_prefix;

        persistent_xf( const sml::CT_Xf& node );
    };

}
