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
 *  Vali Nitu <vali@yalos-solutions.com>
 */

#include "parsed_cell_format.hpp"
#include "ControlTokens.hpp"

#include <map>
#include <boost/thread/mutex.hpp>

#include <wss/singleton.hpp>
#include <wss/locale.hpp>

namespace cell_format
{
    class cell_format_cache : public singleton< cell_format_cache >
    {
        FRIEND_CLASS singleton< cell_format_cache >;
    private:
        static const std::string                                                GENERIC_LOCALE_STRING;
        const locale                                                            generic_locale;
        class locale_cache
        {
        private:
            typedef std::map< std::string, const parsed_cell_format* >                  parsed_formats_type;
            typedef std::map< std::string, const parsed_cell_format* >::const_iterator  parsed_formats_iterator_type;

            typedef boost::mutex                                                mutex_type;
            typedef mutex_type::scoped_lock                                     lock_type;

            parsed_formats_type                                                 parsed_formats;
            mutable mutex_type                                                  mutex;
        public:
            const parsed_cell_format*           get( const std::string& format );
            void set( const parsed_cell_format* parsed_format, const std::string& format );
        };

        locale_cache*                                                           generic_locale_cache;

        typedef std::map< locale, locale_cache* >                               locale_map_type;
        typedef std::map< locale, locale_cache* >::iterator                     locale_map_type_iterator_type;

        locale_map_type                                                         cache;

        locale_cache* get_locale( const locale& loc );
        cell_format_cache();
        ~cell_format_cache();
    public:
        const parsed_cell_format& get( const std::string& format );
        const parsed_cell_format& get( const locale& loc, const std::string& format );
        void register_locale( const locale& loc );
    };

}
