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
*
*  \author
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/

#pragma once

#include <wss/define.hpp>
#include <wss/type.hpp>
#include <wss/non_instantiable.hpp>
#include <wss/session.hpp>
#include <wss/invalid_worksheet_exception.hpp>
#include <wss/worksheet.hpp>
#include <wss/workbook.hpp>

class worksheet_element_storage;

struct command_helper : non_instantiable {

    /*!
     * \brief functions to get a shared_worksheet_type given different parameters
     *  lookups will be performed
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline shared_worksheet_type worksheet( session& s, const std::string& id  ) {
        return command_helper::worksheet( s, id.empty() ? boost::uuids::nil_uuid() : boost::lexical_cast<boost::uuids::uuid>( id ) );
    }

    static inline shared_worksheet_type worksheet( session& s, const boost::uuids::uuid& id = boost::uuids::nil_uuid() ) {
        shared_worksheet_type ws = s.selected().worksheet().lock();
        if ( ! ws ) {
            throw invalid_worksheet_exception( "no worksheet selected!" );
        }
        return command_helper::internal_worksheet( s, ws, id );
    }

    static inline shared_worksheet_type worksheet( session& s, const shared_worksheet_type& ws, const boost::uuids::uuid& id = boost::uuids::nil_uuid() ) {
        if ( ! ws ) {
            throw invalid_worksheet_exception();
        }
        return command_helper::internal_worksheet( s, ws, id );
    }

    /*!
     * \brief functions to get the worksheet_element_storage from a workbook or worksheet
     *  lookups will be performed
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline worksheet_element_storage& elements( const bool use_workbook, const weak_workbook_type& wwb, const weak_worksheet_type& wws ) {
        if ( use_workbook ) {
            return command_helper::elements( wwb );
        } else {
            return command_helper::elements( wws ) ;
        }
    }

    static inline worksheet_element_storage& elements( const weak_worksheet_type& wws ) {
        shared_worksheet_type ws = wws.lock();
        if ( ! ws ) {
            throw object_not_found_exception();
        }
        return ws->elements();
    }

    static inline worksheet_element_storage& elements( const weak_workbook_type& wwb ) {
        shared_workbook_type wb = wwb.lock();
        if ( ! wb ) {
            throw object_not_found_exception();
        }
        return wb->elements();
    }

private:
    static inline shared_worksheet_type internal_worksheet( session& s, const shared_worksheet_type& ws, const boost::uuids::uuid& id ) {
        if ( id.is_nil() ) {
            return ws;
        } else {
            return ws->parent()->get( s, id );
        }
    }
};
