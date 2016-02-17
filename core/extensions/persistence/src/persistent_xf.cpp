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

#include "persistent_xf.hpp"

namespace xlsx
{

    persistent_xf::persistent_xf( const sml::CT_Xf& node )
    {
        if ( node.numFmtId.present() ) {
            num_fmt_id = ( int )node.numFmtId.get();
        } else {
            num_fmt_id = 0;
        }
        if ( node.fontId.present() ) {
            font_id = ( int )node.fontId.get();
        } else {
            font_id = 0;
        }
        if ( node.fillId.present() ) {
            fill_id = ( int )node.fillId.get();
        } else {
            fill_id = 0;
        }
        if ( node.borderId.present() ) {
            border_id = ( int )node.borderId.get();
        } else {
            border_id = 0;
        }
        if ( node.xfId.present() ) {
            xf_id = ( int )node.xfId.get();
        } else {
            xf_id = 0;
        }
        if ( node.applyNumberFormat.present() ) {
            apply_number_format = ( bool )node.applyNumberFormat.get();
        } else {
            apply_number_format = node.numFmtId.present();
        }
        if ( node.applyFont.present() ) {
            apply_font = ( bool )node.applyFont.get();
        } else {
            apply_font = node.fontId.present();
        }
        if ( node.applyFill.present() ) {
            apply_fill = ( bool )node.applyFill.get();
        } else {
            apply_fill = node.fillId.present();
        }
        if ( node.applyBorder.present() ) {
            apply_border = ( bool )node.applyBorder.get();
        }  else {
            apply_border = node.borderId.present() ;
        }
        if ( node.applyAlignment.present() ) {
            apply_alignment = ( bool )node.applyAlignment.get();
        } else {
            apply_alignment = node.alignment.present();
        }
        if ( node.applyProtection.present() ) {
            apply_protection = ( bool )node.applyProtection.get();
        } else {
            apply_protection = node.protection.present();
        }

        if ( node.alignment.present() ) {
            alignment = persistent_alignment( node.alignment.get() );
        }
        if ( node.protection.present() ) {
            protection = persistent_protection( node.protection.get() );
        }

        quote_prefix = node.quotePrefix;
    }

}
