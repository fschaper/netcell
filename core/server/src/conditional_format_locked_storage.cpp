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
#include "precompiled_header.hpp"
#include "conditional_format_locked_storage.hpp"
#include "wss/conditional_format_manager.hpp"
#include "conditional_format_storage.hpp"

namespace cf
{

    struct conditional_format_locked_storage::conditional_format_locked_storage_impl {

        conditional_format_locked_storage_impl( const shared_worksheet_type& ws, conditional_format_manager& manager )
            : m_ws( ws )
            , m_manager( manager ) {
            m_lock.reset( new conditional_format_manager::lock_type( manager.m_mutex ) );
        }

        inline conditional_format_storage& store() {
            return m_manager.get_store( *m_lock );
        }

        //keep a shared_ptr to the worksheet, so it doesn't get deleted before were finished!
        shared_worksheet_type m_ws;
        conditional_format_manager& m_manager;
        boost::scoped_ptr<conditional_format_manager::lock_type> m_lock;
    };

    conditional_format_locked_storage::auto_type conditional_format_locked_storage::create_locked_store( const shared_worksheet_type& ws )
    {
        return auto_type( new conditional_format_locked_storage( ws, ws->conditional_formats() ) );
    }

    conditional_format_storage& conditional_format_locked_storage::store()
    {
        return m_impl->store();
    }

    conditional_format_locked_storage::conditional_format_locked_storage( const shared_worksheet_type& ws, conditional_format_manager& manager )
        : m_impl( new conditional_format_locked_storage_impl( ws, manager ) )
    {}

    conditional_format_locked_storage::~conditional_format_locked_storage()
    {}
}
