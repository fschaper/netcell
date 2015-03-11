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

#include "cell_format_cache.hpp"

#include "ExceptionFactory.hpp"

namespace cell_format
{

    const std::string      cell_format_cache::GENERIC_LOCALE_STRING     = "en-US";

    const parsed_cell_format* cell_format_cache::locale_cache::get( const std::string& format )
    {
        lock_type lock( mutex );
        parsed_formats_iterator_type    parsed_format = parsed_formats.find( format );
        if ( parsed_formats.end() != parsed_format ) {
            return parsed_format->second;
        } else {
            return NULL;
        }
    }

    void cell_format_cache::locale_cache::set( const parsed_cell_format* parsed_format, const std::string& format )
    {
        lock_type lock( mutex );

        parsed_formats[ format ] = parsed_format;
    }

    cell_format_cache::cell_format_cache() : generic_locale( locale::create( GENERIC_LOCALE_STRING ) )
    {
        generic_locale_cache = new locale_cache();
        cache[generic_locale] = generic_locale_cache;
    }

    cell_format_cache::~cell_format_cache()
    {
        for ( locale_map_type::iterator i = cache.begin(); i != cache.end(); i++ ) {
            delete i->second;
        }
    }

    cell_format_cache::locale_cache* cell_format_cache::get_locale( const locale& loc )
    {
        locale_map_type_iterator_type  it = cache.find( loc );
        if ( it != cache.end() ) {
            return it->second;
        }
        if ( "*" == loc.language() || "" == loc.language() ) {
            ExceptionFactory::raise( I18nException::E_UNKNOWN_LOCALE_REQUESTED );
        }
        //try only the major version. lookup the first match in the list
        for ( locale_map_type::iterator i = cache.begin(); i != cache.end(); i++ ) {
            if ( i->first.language() == loc.language() ) {
                return i->second;
            }
        }
        ExceptionFactory::raise( I18nException::E_UNKNOWN_LOCALE_REQUESTED );

        //compiler warning
        return NULL;
    }

    const parsed_cell_format& cell_format_cache::get( const locale& loc, const std::string& format )
    {
        locale_cache*           page                = get_locale( loc );
        const parsed_cell_format*       parsed_format       = page->get( format );
        if ( parsed_format ) {
            return *parsed_format;
        }


        if ( generic_locale_cache != page ) {
            //translate to generic locale
            std::string generic_format_string = parsed_cell_format::Allocator::instance().translate( loc, locale::create( "en" ),  format );

            //check if it is not yet in use
            parsed_format = generic_locale_cache->get( generic_format_string );

            if ( !parsed_format ) {
                //not in use, register first in generic
                parsed_format      = parsed_cell_format::Allocator::instance().get_new( generic_format_string );
                generic_locale_cache->set( parsed_format, generic_format_string );
            }
        } else {
            parsed_format      = parsed_cell_format::Allocator::instance().get_new( format );
        }

        page->set( parsed_format, format );
        return *parsed_format;
    }

    const parsed_cell_format& cell_format_cache::get( const std::string& format )
    {
        const parsed_cell_format*       parsed_format       = generic_locale_cache->get( format );
        if ( parsed_format ) {
            return *parsed_format;
        }

        parsed_format = parsed_cell_format::Allocator::instance().get_new( format );

        generic_locale_cache->set( parsed_format, format );
        return *parsed_format;
    }

    void cell_format_cache::register_locale( const locale& loc )
    {
        cache[loc] = new locale_cache();
    }

}
