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
#include "wss/create_worksheet_element_command.hpp"
#include "wss/session.hpp"
#include "wss/worksheet.hpp"
#include "object_lookup.hpp"
#include "wss/worksheet_element_exception.hpp"
#include "wss/object_not_found_exception.hpp"
#include "command_helper.hpp"
#include "uuid_adjust.hpp"
#include "wss/worksheet_element_storage.hpp"

template<class T>
struct worksheet_element_cageT {
    typedef typename boost::shared_ptr<T> shared_parent_type;
    worksheet_element_cageT( session& s, const shared_parent_type& p, shared_worksheet_element_type e )
        : s( s ), wse( e ), parent( p ) {}

    ~worksheet_element_cageT() {
        if ( wse && parent ) {
            parent->elements().delete_worksheet_element( s, wse->uuid() );
        }
    }

    worksheet_element* operator->() const {
        return wse.operator ->();
    }

    void release() {
        wse.reset();
        parent.reset();
    }

private:
    session& s;
    shared_worksheet_element_type wse;
    shared_parent_type parent;
};


struct ws_element_creation_helper {
    template<class T>
    static inline ws_elem_id_type create( session& s, const boost::shared_ptr<T>& parent,  create_worksheet_element_command::key_value_vector_type& ws_elem_properties ) {
        typedef worksheet_element_cageT<T> worksheet_element_cage;
        worksheet_element_cage e( s, parent, worksheet_element::create( parent ) );
        e->properties( s, ws_elem_properties );
        const ws_elem_id_type id = e->uuid();
        //everything went well, lets release the poor thing!
        e.release();
        return id;
    }
};

create_worksheet_element_command::create_worksheet_element_command( session& s, const std::string& ws_id, const key_value_vector_type& ws_elem_properties, const bool wb_scope /* = false */ )
    : base_command<i_command>::base_command( s )
    , m_ws_elem_properties( ws_elem_properties )
    , m_wb_scope( wb_scope )
{
    if ( m_wb_scope ) {
        m_wb =  command_helper::worksheet( s, ws_id )->parent();
    } else {
        m_ws = command_helper::worksheet( s, ws_id );
    }
}

void create_worksheet_element_command::execute()
{
    if ( m_wb_scope ) {
        shared_workbook_type wb = m_wb.lock();
        if ( ! wb ) {
            throw object_not_found_exception( "workbook no longer present!" );
        }
        m_id = uuid_adjust::cast_uuid( ws_element_creation_helper::create( m_session, wb, m_ws_elem_properties ) );
    } else {
        shared_worksheet_type ws = m_ws.lock();
        if ( ! ws ) {
            throw object_not_found_exception( "worksheet no longer present!" );
        }
        m_id = uuid_adjust::cast_uuid( ws_element_creation_helper::create( m_session, ws, m_ws_elem_properties ) );
    }
}

create_worksheet_element_command::result_type create_worksheet_element_command::value() const
{
    return m_id;
}

DEFINE_CLONEABLE( create_worksheet_element_command );
