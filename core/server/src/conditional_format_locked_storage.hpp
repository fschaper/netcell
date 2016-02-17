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
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/

#pragma once

#include "wss/worksheet.hpp"

class conditional_format_manager;

namespace cf
{
    class conditional_format_storage;

    class conditional_format_locked_storage
        : boost::noncopyable
    {
    public:
        typedef boost::uint_fast32_t lookup_id_type;

        typedef std::auto_ptr<conditional_format_locked_storage> auto_type;

        ~conditional_format_locked_storage();

        static auto_type create_locked_store( const shared_worksheet_type& ws  );

        conditional_format_storage& store();

    private:
        conditional_format_locked_storage( const shared_worksheet_type& ws, conditional_format_manager& manager );

        //keep a shared_ptr to the worksheet, so it doesn't get deleted before were finished!
        struct conditional_format_locked_storage_impl;
        boost::scoped_ptr<conditional_format_locked_storage_impl> m_impl;

    };
}
