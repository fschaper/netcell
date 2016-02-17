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
 *  Marek Pikulski <marek.pikulski@jedox.com>
 */

#ifndef HAVE_SAFE_NUMBER_CAST_H
#define HAVE_SAFE_NUMBER_CAST_H

// stl
#include <map>

#include <cassert>

namespace cell_format
{
    /*!
     * Class providing range checked casts.
     *
     * \author Marek Pikulski <marek.pikulski@jedox.com>
     */
    template<typename T, typename U>
    class checked_number_cast
    {
    public:
        checked_number_cast( const U u ) {}
        ~checked_number_cast() {}

        operator T() const {
            const bool checked_number_cast_implemented = false;
            assert( true == checked_number_cast_implemented );
        }
    };

    // partial specialization
    template <typename U>
    class checked_number_cast<unsigned int, U>
    {
    public:
        checked_number_cast( const U u ) : u( u ) {}
        ~checked_number_cast() {}

        inline operator unsigned int() const;

    private:
        U u;
    };

    template<typename T, typename U>
    inline checked_number_cast<T, U> checked_number_cast_impl( const U u );

    template<typename T, typename U>
    inline checked_number_cast<T, U> checked_number_cast_impl( const U u )
    {
        return checked_number_cast<T, U>( u );
    }
}

// implementation
#include "checked_number_cast.ipp"

#endif
