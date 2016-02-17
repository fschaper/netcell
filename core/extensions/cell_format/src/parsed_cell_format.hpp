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
 *  Dragan Simic <dragan.simic@develabs.com>
 */

#pragma once

//boost
#include <boost/thread/mutex.hpp>

// stl
#include <memory>

// wss
#include <wss/singleton.hpp>
#include <wss/locale.hpp>

#include "FormatSection.hpp"

namespace cell_format
{
    /*! \brief Data type representing a preparsed cell format.
    *
    *  \author
    * Marek Pikulski <marek.pikulski@jedox.com>
    */
    class parsed_cell_format
    {
    public:
        parsed_cell_format( bool conditionless = false );
        parsed_cell_format( const parsed_cell_format& other );
        virtual ~parsed_cell_format();

        bool operator==( const parsed_cell_format& other ) const;
        bool operator!=( const parsed_cell_format& other ) const;

        typedef boost::ptr_vector< FormatSection > FormatSections;

        const FormatSections& get_sections() const;
        bool is_conditionless() const;

        class Allocator : public singleton< Allocator >
        {
            FRIEND_CLASS singleton< Allocator >;
        private:
            typedef boost::mutex                                                mutex_type;
            typedef mutex_type::scoped_lock                                     lock_type;

            mutable mutex_type                                                  mutex;

            std::vector< parsed_cell_format* > m_data;
            Allocator();
            ~Allocator();
        public:
            parsed_cell_format* get_new( const std::string& format );
            const std::string translate( const locale& from, const locale& to, const std::string& format );
            //          const std::string localize( const locale& loc, const std::string &format );
        };
    protected:
        mutable std::auto_ptr< FormatSections > m_sections;
        bool                m_conditionless; // conditionless format list

        friend class CellFormatPostParser;
        friend class CellFormatParseTreeConverter;
    };
}
