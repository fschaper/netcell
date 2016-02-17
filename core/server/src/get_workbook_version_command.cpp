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
 * Vali Nitu <vali@yalos-solution.com>
 */

#include "precompiled_header.hpp"
#include "wss/application.hpp"
#include "wss/get_workbook_version_command.hpp"



get_workbook_version_command::get_workbook_version_command(  session& s, const uuid_type& id  )
    : base_command<i_command>::base_command( s )
    , m_wb_id( id )
    , m_return()
{}

void get_workbook_version_command::execute()
{
    shared_workbook_type            wb;
    shared_application_type         app    = m_session.selected().application();

    if ( ! app ) {
        throw object_not_found_exception();
    }

    if ( m_wb_id.is_nil() ) {

        wb = m_session.selected().workbook().lock();

        if ( ! wb ) {
            throw object_not_found_exception();
        }

    } else {
        wb = app->get( m_session, m_wb_id );
    }


    m_return = std::string( "WSS workbook, version " ) + boost::lexical_cast< std::string >( wb->version_major() ) + "." + boost::lexical_cast< std::string >( wb->version_minor() );
}

const get_workbook_version_command::result_type& get_workbook_version_command::value() const
{
    return m_return;
}

DEFINE_CLONEABLE( get_workbook_version_command );

