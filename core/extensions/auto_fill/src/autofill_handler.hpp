/**
*  \file
*  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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
*  \Author
*  Florian Schaper <florian.schaper@jedox.com>
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*  Vali Nitu <vali@yalos-solutions.com>
*/

#pragma once

#include "precompiled_header.hpp"

// stl
#include <list>

// boost
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <wss/singleton.hpp>
#include <wss/locale.hpp>

#include <wss/i_autofill_handler.hpp>


class range;
class XMLListImport;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


namespace autofill_internal
{

    class autofill_handler : public i_autofill_handler
    {

    public:
        typedef boost::shared_ptr<i_autofill_handler> handler_type;
        typedef std::list<handler_type> handler_list_type;

    public:
        void register_handler( handler_type handler );
        bool handle_sequence( session& cx, const range& sequence, range& target );

        autofill_handler( const std::string& locale_dir );

        enum DragDirection {
            DRAG_LEFT
            , DRAG_RIGHT
            , DRAG_DOWN
            , DRAG_UP
        };


        //TODO
        // moved here to remove code duplication - AutofillHandler and the Sequence*FillHanders have to be redesigned at some point,
        // formats and styles could be copied in the AutofillHandler, not the different
        // Sequence*FillHander's
        /*static inline void handle_styles_and_formats( session& cx, range& rt, range& rs ) {
            rt.set_style( cx, rs.get_unconditional_style( cx ) );
            std::vector< std::string> tmp_formats(rs.get_format( cx ));
            if ( !tmp_formats.empty() ) {
                rt.set_format( cx, tmp_formats );
            }
            rt.set_attributes( cx, rs.get_attributes( cx )[0] );
            BOOST_FOREACH( const CFRuleReference& cf, rs.get_conditional_format_ref( cx ) ) {
                rt.set_conditional_format( cx, cf );
            }
        }*/

    private:
        handler_list_type m_handlers;
    };

}



