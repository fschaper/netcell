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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "metrics_engine.hpp"
#include <wss/variant.hpp>


namespace textmetric_internal
{
    metrics_engine::metrics_engine ( unsigned int dpi, style_set_type& default_style )
        :  m_dpi( dpi )
        , m_default_style( default_style )
    {
    }

    std::pair<unsigned int, unsigned int> metrics_engine::measure_text( const style_set_type& style, const std::pair<unsigned int, unsigned int>& resolution, const variant& value )
    {
        unsigned int xdpi = resolution.first;
        if ( 0 == xdpi ) {
            xdpi = m_dpi;
        }
        unsigned int ydpi = resolution.second;
        if ( 0 == ydpi ) {
            ydpi = m_dpi;
        }

        text_metric_intf    intf( m_default_style, style, value.string(), xdpi, ydpi );
        intf.parse();
        return std::pair<unsigned int, unsigned int>( intf.get_width(), intf.get_height() );
    }

}
