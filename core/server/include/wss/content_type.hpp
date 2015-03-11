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

#include <wss/non_instantiable.hpp>
/*!
 * \brief
 *  content_type used for clear / copy / cut / paste etc.
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
struct content_type
        : non_instantiable {
    enum type {
        //the value or formula
        formula = 1
        //only styles
        , style = 2
        //only formats
        , format = 4
        //only attributes
        , attributes = 8
        //only conditional formats
        , conditional_formats = 16
        //just the value
        , value = 32
        , border = 64
        // for clear this version of all is appropriate!
        , all = ( formula | style | format | attributes | value | border )
        // for copy this version of all (all_plus_cf) is appropriate!
        , all_plus_cf = ( all | conditional_formats )
        , all_plus_cf_but_style = ( formula | conditional_formats | format | attributes | value | border )
    };
};
