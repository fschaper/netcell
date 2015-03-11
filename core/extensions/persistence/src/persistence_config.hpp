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
 */


// This file has been auto-generated. Don't change it by hand!

#ifndef PERSISTENCE_CONFIG_HPP
#define PERSISTENCE_CONFIG_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace persistence_cfg
{
    using namespace ::xio;
    using namespace ::xio::xml::schema;

    class CT_patern_fill;
    class CT_patern_fills;
    class CT_persistence_config;
    class persistence_config;

    class CT_patern_fill
    {
    public:
        String patternType;
        String background_image;
    };

    class CT_patern_fills
    {
    public:
        std::vector< CT_patern_fill > pattern_fill;
    };

    class CT_persistence_config
    {
    public:
        CT_patern_fills pattern_fills;
    };

    class persistence_config
    {
    public:
        poptional< CT_persistence_config > persistence_settings;
    };

}
#endif

