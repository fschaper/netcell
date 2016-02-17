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
#include "sequence_default_fill_handler.hpp"



namespace autofill_internal
{

    bool sequence_default_fill_handler::handle_sequence( session& cx, const range& sequence, range& target )
    {
        long int width = sequence.coverage().column_count();
        long int height = sequence.coverage().row_count();
        long int ind;

        if ( target.coverage().upper_left().row() > sequence.coverage().upper_left().row() ) { // drag downwards

            int col_offset = sequence.coverage().upper_left().column();
            for ( long int j = col_offset; j < col_offset + width; j++ ) {

                int row_offset = target.coverage().upper_left().row();
                int seq_row_offset = sequence.coverage().upper_left().row();
                range sequence_col = sequence.column( j );
                range target_col = target.column( j );
                long int row_count = static_cast<long int>( target_col.coverage().row_count() );
                for ( long int i = 0; i < row_count ; i++ ) {
                    ind = i % height;
                    range rs = range( sequence_col.row( seq_row_offset + ind ) );
                    range rt = target_col.row( row_offset + i );
                    if ( variant ( true ) == rs.has_formula() ) {
                        rs.copy( cx, rt );
                    } else {
                        rt.value( cx, rs.value( cx ) ); // next vertical

                        //TODO
                        // also set style, format and attributes:
                        //AutoFillHandler::handle_styles_and_formats( cx, rt, rs );
                    }
                }
            }
        }

        if ( target.coverage().upper_left().row() < sequence.coverage().upper_left().row() ) { // drag upwards

            int col_offset = sequence.coverage().upper_left().column();
            for ( long int j = col_offset; j < col_offset + width; j++ ) {

                int row_offset = target.coverage().upper_left().row();
                int seq_row_offset = sequence.coverage().upper_left().row();
                range sequence_col = sequence.column( j );
                range target_col = target.column( j );
                long int row_count = static_cast<long int>( target.coverage().row_count() );
                for ( long int i = 0; i < row_count; i++ ) {
                    ind = height - 1 - i % height;
                    range rs = sequence_col.row( seq_row_offset + ind );
                    range rt = target_col.row( row_offset + row_count - 1 - i );
                    if ( variant( true ) == rs.has_formula() ) {
                        rs.copy( cx, rt );
                    } else {
                        rt.value( cx, rs.value( cx ) ); // previous vertical

                        //TODO
                        // also set style, format and attributes:
                        //AutoFillHandler::handle_styles_and_formats( cx, rt, rs );
                    }
                }
            }
        }

        if ( target.coverage().upper_left().column() > sequence.coverage().upper_left().column() ) { // drag rightwards

            int row_offset = sequence.coverage().upper_left().row();
            for ( long int j = row_offset; j < row_offset + height; j++ ) {
                int col_offset = target.coverage().upper_left().column();
                int seq_col_offset = sequence.coverage().upper_left().column();
                range sequence_row = sequence.row( j );
                range target_row = target.row( j );
                long int column_count = static_cast<long int>( target_row.coverage().column_count() );
                for ( long int i = 0; i < column_count; i++ ) {
                    ind = i % width;
                    range rs = sequence_row.column( seq_col_offset + ind );
                    range rt = target_row.column( col_offset + i );
                    if ( variant( true ) == rs.has_formula() ) {
                        rs.copy( cx, rt );
                    } else {
                        rt.value( cx, rs.value( cx ) ); // next horizontal

                        //TODO
                        // also set style, format and attributes:
                        //AutoFillHandler::handle_styles_and_formats( cx, rt, rs );
                    }
                }
            }
        }

        if ( target.coverage().upper_left().column() < sequence.coverage().upper_left().column() ) { // drag leftwards

            int row_offset = sequence.coverage().upper_left().row();
            for ( long int j = row_offset; j < row_offset + height; j++ ) {
                int col_offset = target.coverage().upper_left().column();
                int seq_col_offset = sequence.coverage().upper_left().column();
                range sequence_row = sequence.row( j );
                range target_row = target.row( j );
                long int column_count = static_cast<long int>( target.coverage().column_count() );
                for ( long int i = 0; i < column_count; i++ ) {
                    ind = width - 1 - i % width;
                    range rs = sequence_row.column( seq_col_offset + ind );
                    range rt = target_row.column( col_offset + column_count - 1 - i );
                    if ( variant( true ) == rs.has_formula() ) {
                        rs.copy( cx, rt );
                    } else {
                        rt.value( cx, rs.value( cx ) ); // previous horizontal

                        //TODO
                        // also set style, format and attributes:
                        //AutoFillHandler::handle_styles_and_formats( cx, rt, rs );
                    }
                }
            }
        }

        return true;
    }


}

