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

#include "precompiled_header.hpp"

#include "autofill_handler.hpp"
#include "xml_list_reader.hpp"
#include "sequence_text_fill_handler.hpp"
#include "sequence_number_fill_handler.hpp"
#include "sequence_default_fill_handler.hpp"
#include <boost/foreach.hpp>
#include <iostream>


namespace autofill_internal
{

    void autofill_handler::register_handler( handler_type handler )
    {
        m_handlers.push_back( handler );
    }

    bool autofill_handler::handle_sequence( session& cx, const range& sequence, range& target )
    {
        handler_list_type::iterator it = m_handlers.begin();
        handler_list_type::iterator end = m_handlers.end();
        bool handler_matched = false;

        int width = sequence.coverage().column_count();
        int height = sequence.coverage().row_count();

        //TODO
        //ConditionalFormatManager& cf_manager = ConditionalFormatManager::get_instance();
        //ConditionalFormatManager::cf_reference_set_type cf_set = sequence.get_conditional_format_ref(cx);
        DragDirection drag_direction;

        if ( target.coverage().upper_left().row() > sequence.coverage().upper_left().row() ) { // drag downwards
            drag_direction = DRAG_DOWN;
            int col_offset = target.coverage().upper_left().column();
            for ( int j = col_offset; j < col_offset + width; j++ ) {
                // For each column take the appropriate handler.
                handler_matched = false;
                for ( it = m_handlers.begin(); ( it != end && !handler_matched ) ; ++it ) {
                    // TODO: a possible redesign?
                    range tmp_range( target.column( j ) );
                    handler_matched = ( *it )->handle_sequence( cx, sequence.column( j ), tmp_range );
                }
            }
        }

        if ( target.coverage().upper_left().row() < sequence.coverage().upper_left().row() ) { // drag upwards
            drag_direction = DRAG_UP;
            int col_offset = target.coverage().upper_left().column();
            for ( int j = col_offset; j < col_offset + width; j++ ) {
                // For each column take the appropriate handler.
                handler_matched = false;
                for ( it = m_handlers.begin(); ( it != end && !handler_matched ) ; ++it ) {
                    // TODO: a possible redesign?
                    range tmp_range( target.column( j ) );
                    handler_matched = ( *it )->handle_sequence( cx, sequence.column( j ), tmp_range );
                }
            }
        }

        if ( target.coverage().upper_left().column() > sequence.coverage().upper_left().column() ) { // drag rightwards
            drag_direction = DRAG_RIGHT;
            int row_offset = target.coverage().upper_left().row();
            for ( int j = row_offset; j < row_offset + height; j++ ) {
                // For each row take the appropriate handler.
                handler_matched = false;
                for ( it = m_handlers.begin(); ( it != end && !handler_matched ) ; ++it ) {
                    // TODO: a possible redesign?
                    range tmp_range( target.row( j ) );
                    handler_matched = ( *it )->handle_sequence( cx, sequence.row( j ), tmp_range );
                }
            }
        }

        if ( target.coverage().upper_left().column() < sequence.coverage().upper_left().column() ) { // drag leftwards
            drag_direction = DRAG_LEFT;
            int row_offset = target.coverage().upper_left().row();
            for ( int j = row_offset; j < row_offset + height; j++ ) {
                // For each row take the appropriate handler.
                handler_matched = false;
                for ( it = m_handlers.begin(); ( it != end && !handler_matched ) ; ++it ) {
                    // TODO: a possible redesign?
                    range tmp_range( target.row( j ) );
                    handler_matched = ( *it )->handle_sequence( cx, sequence.row( j ), tmp_range );
                }
            }
        }

        //TODO
        /*if ( !cf_set.empty() ) {
            BOOST_FOREACH( CFRuleReference ref, cf_set ) {
                cf_manager.autofill_move(cx, ref.get_id(), sequence, target, drag_direction );
            }
        }*/

        return handler_matched; // The last handler SequenceDefaultFillHander should always match.
    }

    autofill_handler::autofill_handler( const std::string& locale_dir )
    {
        register_handler( handler_type( new sequence_number_fill_handler() ) );

        xml_list_reader xml_register( *this );

        boost::filesystem::path local_folder_path( locale_dir );

        for ( boost::filesystem::directory_iterator it( local_folder_path ); it != boost::filesystem::directory_iterator(); ++it ) {

            if ( !boost::filesystem::is_directory( it->status() ) ) {
                continue;
            }
            boost::filesystem::path path( *it );
            path = path / "list/";

            try {
                std::string s = it->leaf();
                xml_register.read_list( path, s );
            } catch ( std::exception& ) { } //mask and continue. advance to the next folder.
        }

        register_handler( handler_type( new sequence_default_fill_handler() ) );
    }
}

