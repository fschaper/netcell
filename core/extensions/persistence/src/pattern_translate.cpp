/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "pattern_translate.hpp"
#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH

void pattern_translate::load( persistence_cfg::CT_patern_fills& fills )
{
    foreach( persistence_cfg::CT_patern_fill & crt, fills.pattern_fill ) {
        m_direct[ crt.patternType ] = crt.background_image;
        m_inverse[ crt.background_image ] = crt.patternType;
    }
}

std::string pattern_translate::internal_patern( const std::string& key )
{
    std::string return_val = m_direct[key];
    if ( !return_val.empty() ) {
        return_val = "background-image:" + return_val + ";";
    }
    return return_val;
}

std::string pattern_translate::internal_patern_val( const std::string& key )
{
    return m_direct[key];
}

std::string pattern_translate::external_patern( const std::string& key )
{
    if ( key == "none" || key == "gray125" ) {
        return key;
    }
    return m_inverse[key];
}
