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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once
#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/flyweight.hpp>
#   include <boost/flyweight/refcounted.hpp>
#endif

namespace bfw = boost::flyweights;
namespace internal_flyweights
{

    struct opcode_string_tag {};
    //we only need to attach a tag, everything else can be left to default values
    typedef bfw::flyweight<std::string, bfw::tag<opcode_string_tag> > opcode_string_type;


    struct border_style_tag {};
    typedef bfw::flyweight<std::string, bfw::tag<border_style_tag>, bfw::refcounted > border_style_flyweight_type;

    struct cf_format_tag {};
    //we only need to attach a tag, everything else can be left to default values
    typedef bfw::flyweight<std::string, bfw::tag<cf_format_tag>, bfw::refcounted > conditional_format_format_type;

    //     struct variant_tag {};
    //     typedef bfw::flyweight<std::string, bfw::tag<variant_tag> > variant_string_type;

    inline void init()
    {
        opcode_string_type::init();
        border_style_flyweight_type::init();
        conditional_format_format_type::init();
        //variant_string_type::init();
    }
}
