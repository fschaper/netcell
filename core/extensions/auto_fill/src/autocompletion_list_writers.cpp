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

#include "precompiled_header.hpp"
#include "autocompletion_list_writers.hpp"
#include "autocompletion_list_literals.hpp"

namespace jedox
{
    namespace wss
    {
        namespace autofill_internal
        {
            namespace xio
            {
                void CT_autofill_list_writer::write_target_to( xml_writer& w )
                {
                    for ( size_t sqi = 0; sqi < t()->element.size(); ++sqi ) {
                        w.start_element( 0, autocompletion_list_element_literal );
                        w.write_element_value( context()->serialize( t()->element[sqi] ) );
                        w.end_element( 0, autocompletion_list_element_literal );
                    }
                }

                void autocompletion_list_writer::write_target_to( xml_writer& w )
                {
                    if ( t()->autofill_list.present() ) {
                        w.start_element( 0, autocompletion_list_autofill_list_literal );
                        w.attribute( 0, autocompletion_list_xmlns_literal, autocompletion_list_http_colon__slash__slash_tempuri_dot_org_slash_jedox_slash_wss_slash_auto_fill_literal );
                        w.attribute( autocompletion_list_xmlns_literal, autocompletion_list_NS_literal, autocompletion_list_http_colon__slash__slash_tempuri_dot_org_slash_jedox_slash_wss_slash_auto_fill_literal );
                        w.attribute( autocompletion_list_xmlns_literal, autocompletion_list_xs_literal, autocompletion_list_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal );
                        _autofill_list_writer.get_writer( context(), &t()->autofill_list.get() )->write_target_to( w );
                        w.end_element( 0, autocompletion_list_autofill_list_literal );
                    }
                }

            }
        }
    }
}
