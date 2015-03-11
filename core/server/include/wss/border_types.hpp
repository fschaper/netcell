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

#include "wss/define.hpp"
#include "wss/type.hpp"
#include "wss/define.hpp"
#include "wss/flyweight_types.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/flyweight/flyweight.hpp>
# include <boost/flyweight/refcounted.hpp>
# include <boost/flyweight/hashed_factory.hpp>
# include <boost/flyweight/simple_locking.hpp>
# include <boost/flyweight/static_holder.hpp>
#endif

struct border_style_tag {};
//we only need to attach a tag, everything else can be left to default values
typedef internal_flyweights::border_style_flyweight_type border_style_flyweight_type;

struct border_types : non_instantiable {
    enum type {
        none = 0
        , top = 1
        , bottom = 2
        , left = 4
        , right = 8
        , outside = top | bottom | left | right
        //the following two are needed when setting borders on a range
        , inside_horizontal = 16
        , inside_vertical = 32

        , inside = inside_horizontal | inside_vertical
    };
};
typedef border_types conditional_format_border_types;
