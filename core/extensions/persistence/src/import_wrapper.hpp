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

#include <wss/i_import_filter.hpp>
#include "xlsx_import_filter.hpp"

namespace xlsx
{

    class import_wrapper :   public i_import_filter
    {

        virtual const import_filter_extension_list_type& extensions() const {
            static import_filter_extension_list_type    extensions;
            if ( extensions.empty() ) {
                extensions.push_back( std::string( "xlsx" ) );
                extensions.push_back( std::string( "wss" ) );
            }
            return extensions;
        }

#ifdef _WIN32
# pragma warning( disable : 4290 )
#endif
        virtual shared_workbook_type do_import( session& s, application& a, std::vector<std::string>& report,  const boost::filesystem::path& in_file, const bool is_native = true ) {
            std::auto_ptr< xlsx_import_filter > instance( new xlsx_import_filter );
            shared_workbook_type result = instance->do_import( s, a, in_file, is_native );
            report = instance->get_progress_list();
            return result;
        }
        virtual bool extended_data_import( session& s, application& a, const boost::filesystem::path& in_file ) {
            std::auto_ptr< xlsx_import_filter > instance( new xlsx_import_filter );
            return instance->extended_data_import( s, a, in_file );
        }
#ifdef _WIN32
# pragma warning( default : 4290 )
#endif
    };
}
