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

#include "persistent_border.hpp"
#include "persistent_alignment.hpp"
#include "persistent_nfmt.hpp"
#include "persistent_font.hpp"
#include "persistent_protection.hpp"
#include "persistent_dxf.hpp"

namespace xlsx
{

    const std::string persistent_dxf::style_str() const
    {
        std::string result = "";
        if ( fill.present() ) {
            result.append( fill.get().str() );
        }
        if ( font.present() ) {
            result.append( font.get().str() );
        }
        if ( alignment.present() ) {
            result.append( alignment.get().str() );
        }


        return result;
    }

    void persistent_dxf::store( sml::CT_Dxf& out_dxf ) const
    {

        if ( font.present() ) {
            sml::CT_Font&    out_font = out_dxf.font.getset();
            font.get().store( out_font );
        }

        if ( num_fmt.present() ) {
            sml::CT_NumFmt&    out_num_fmt = out_dxf.numFmt.getset();
            num_fmt.get().store( out_num_fmt );
        }

        if ( fill.present() ) {
            sml::CT_Fill&    out_fill = out_dxf.fill.getset();
            fill.get().store( out_fill );
        } else {
            persistent_fill fill( 0 );
            out_dxf.fill.getset();
        }

        if ( alignment.present() ) {
            sml::CT_CellAlignment&    out_alignment = out_dxf.alignment.getset();
            alignment.get().store( out_alignment );
        }

        if ( border.present() ) {
            sml::CT_Border&    out_border = out_dxf.border.getset();
            border.get().store( out_border );
        }

        if ( protection.present() ) {
            sml::CT_CellProtection&    out_protection = out_dxf.protection.getset();
            protection.get().store( out_protection );
        }
    }
}
