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

#include "persistent_style.hpp"

namespace xlsx
{

    void persistent_style::store( sml::CT_Xf& out_xf ) const
    {
        out_xf.xfId = 0;
        if ( fill_id.present() ) {
            out_xf.fillId = fill_id.get();
            out_xf.applyFill = true;
        } else {
            out_xf.fillId = 0;
        }
        if ( font_id.present() ) {
            out_xf.fontId = font_id.get();
            out_xf.applyFont = true;
        } else {
            out_xf.fontId = 0;
        }
        if ( nfmt_id.present() ) {
            out_xf.numFmtId = nfmt_id.get();
            out_xf.applyNumberFormat = true;
        } else {
            out_xf.numFmtId = 0;
        }
        if ( border_id.present() ) {
            out_xf.borderId =  border_id.get();
            out_xf.applyBorder = true;
        } else {
            out_xf.borderId = 0;
        }

        if ( quote_prefix.present() ) {
            out_xf.quotePrefix = 1;
        }

        if ( locked.present() ||  hidden.present() ) {
            out_xf.applyProtection = true;
            sml::CT_CellProtection& out_prot = out_xf.protection.getset();
            if ( locked.present() ) {
                out_prot.locked = locked.get();
            }
            if ( hidden.present() ) {
                out_prot.hidden = hidden.get();
            }
        }
    }

}
