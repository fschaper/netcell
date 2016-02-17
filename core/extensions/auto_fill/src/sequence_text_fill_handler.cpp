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
#include "sequence_text_fill_handler.hpp"
#include <wss/locale.hpp>



namespace autofill_internal
{

    sequence_text_fill_handler::sequence_text_fill_handler() : m_locale( locale::create( "en" ) )
    {

        calls = 0;
        leadingEmpties = 0;
        closingEmpties = 0;
        texts = 0;
        step = 0;
        actualIndex = 0;

    }

    void sequence_text_fill_handler::set_list( const std::vector<std::string>& List, locale& list_locale )
    {
        m_locale = list_locale;
        m_List = List;
    }

    bool sequence_text_fill_handler::prepare( const range& values, session& cx, int next, int vertical )
    {
        // If next == 0, we calculate previous values ( to the left or up ), else next values ( to the right or down ).
        // If vertical == 0, we calculate values to the left or right, else up or down.


        calls = 0;
        texts = 0;
        variant val;
        leadingEmpties = 0;

        bool leading = true;
        // Count leading empties and text values.
        if ( vertical == 0 ) {
            unsigned int col_offset = values.coverage().upper_left().column();
            unsigned int col_count = values.coverage().column_count();
            for ( unsigned int i = col_offset; i < col_offset + col_count; i++ ) {
                val = values.column( i ).value( cx );
                if ( variant::type_string == val.type() ) {
                    leading = false;
                    texts++;
                } else {
                    if ( leading ) {
                        leadingEmpties++;
                    }
                }
            }
        } else {
            unsigned int row_offset = values.coverage().upper_left().row();
            unsigned int row_count = values.coverage().row_count();
            for ( unsigned int i = row_offset; i < row_offset + row_count; i++ ) {
                val = values.row( i ).value( cx );
                if ( variant::type_string == val.type() ) {
                    leading = false;
                    texts++;
                } else {
                    if ( leading ) {
                        leadingEmpties++;
                    }
                }
            }
        }
        // If there are only empty cells, get_next will return type_empty.
        if ( texts == 0 ) {
            return true;
        }
        closingEmpties = 0;
        // Count closing empties:
        if ( vertical == 0 ) {
            unsigned int col_offset = values.coverage().upper_left().column();
            unsigned int col_count = values.coverage().column_count();
            for ( int i = col_offset + col_count - 1; i > -1; i-- ) {
                val = values.column( i ).value( cx );
                if ( variant::type_string == val.type() ) {
                    break;
                } else {
                    closingEmpties++;
                }
            }
        } else {
            unsigned int row_offset = values.coverage().upper_left().row();
            unsigned int row_count = values.coverage().row_count();
            for ( int i = row_offset + row_count - 1; i > -1; i-- ) {
                val = values.row( i ).value( cx );
                if ( variant::type_string == val.type() ) {
                    break;
                } else {
                    closingEmpties++;
                }
            }
        }

        std::vector<int> ind( values.coverage().count() ); // list-indices corresponding to the values.
        if ( vertical == 0 ) {
            unsigned int col_offset = values.coverage().upper_left().column();
            unsigned int col_count = values.coverage().column_count();
            for ( unsigned int i = col_offset; i < col_offset + col_count ; i++ ) {
                variant val = values.column( i ).value( cx );
                if ( val.type() == variant::type_string ) {
                    for ( int k = 0; k < static_cast<int>( m_List.size() ); k++ ) {
                        if ( ( val.string() ).compare( m_List[k] ) == 0 ) {
                            ind[i-col_offset] = k; // Fill in list-index.
                            break;
                        }
                    }
                } else {
                    ind[i-col_offset] = -1; // for empty cell.
                }
            }
        } else {
            unsigned int row_offset = values.coverage().upper_left().row();
            unsigned int row_count = values.coverage().row_count();
            for ( unsigned int i = row_offset; i < row_offset + row_count; i++ ) {
                variant val = values.row( i ).value( cx );
                if ( val.type() == variant::type_string ) {
                    for ( int k = 0; k < static_cast<int>( m_List.size() ); k++ ) {
                        if ( ( val.string() ).compare( m_List[k] ) == 0 ) {
                            ind[i-row_offset] = k; // Fill in list-index.
                            break;
                        }
                    }
                } else {
                    ind[i-row_offset] = -1; // for empty cell.
                }
            }
        }

        // Calculate the step and stepEmpties.
        step = 1; // default.
        stepEmpties = 0;
        if ( texts > 1 ) {
            int first = leadingEmpties;
            int second = first + 1;
            for ( ; ind[second] == -1; second++ ) {}
            stepEmpties = second - first - 1;
            step = ( ind[second] - ind[first] + static_cast<int>( m_List.size() ) ) % static_cast<int>( m_List.size() );
            first = second;
            second = first + 1;
            while ( second < static_cast<int>( values.coverage().count() ) - closingEmpties ) {
                for ( ; ind[second] == -1; second++ ) {}
                if ( second - first - 1 != stepEmpties ) {
                    return false; // stepEmpties is not unique.
                }
                if ( ( ind[second] - ind[first] + static_cast<int>( m_List.size() ) ) % static_cast<int>( m_List.size() ) != step ) {
                    return false; // step is not unique.
                }
                first = second;
                second = first + 1;
            }
        }

        // Set the actualIndex.
        if ( next == 0 ) {
            actualIndex = ind[leadingEmpties];
        } else {
            actualIndex = ind[static_cast<int>( values.coverage().count() )-1-closingEmpties];
        }

        return true;
    }


    variant sequence_text_fill_handler::get_next( const range& values, session& cx, int next, int vertical )
    {
        // If next == 0, we calculate previous values ( to the left or up ), else next values ( to the right or down ).
        // If vertical == 0, we calculate values to the left or right, else up or down.

        // If there are only empty cells, return type_empty.
        if ( texts == 0 ) {
            return variant::type_empty;
        }

        int ind;
        if ( next == 0 ) {
            ind = static_cast<int>( values.coverage().count() ) - 1 - calls % static_cast<int>( values.coverage().count() );
        } else {
            ind = calls % static_cast<int>( values.coverage().count() );
        }
        // In position of leading or closing empties, return type_empty.
        if ( ind < leadingEmpties || ind > static_cast<int>( values.coverage().count() ) - 1 - closingEmpties ) {
            calls++;
            return variant::type_empty;
        }
        // In position of inner empties, return type_empty.
        if ( stepEmpties > 0 ) {
            if ( ( ind - leadingEmpties ) % ( stepEmpties + 1 ) != 0 ) {
                calls++;
                return variant::type_empty;
            }
        }

        if ( next == 0 ) {
            actualIndex = ( actualIndex - step + static_cast<int>( m_List.size() ) ) % static_cast<int>( m_List.size() );
        } else {
            actualIndex = ( actualIndex + step ) % static_cast<int>( m_List.size() );
        }
        calls++;
        return variant( m_List[actualIndex] );
    }

    bool sequence_text_fill_handler::handle_sequence( session& cx, const range& sequence, range& target )
    {
        long int width = sequence.coverage().column_count();
        long int height = sequence.coverage().row_count();
        long int ind;
        variant val;
        bool contained;

        if ( cx.locale().language() != m_locale.language() ) {
            return false;
        }

        // Check if there are only texts from the list or empty cells.

        int col_offset = sequence.coverage().upper_left().column();
        int row_offset = sequence.coverage().upper_left().row();
        for ( long int j = col_offset; j < col_offset + width; j++ ) {
            range row_range = range( sequence.column( j ) );
            for ( long int i = row_offset; i < row_offset + height; i++ ) {
                range crt = row_range.row( i ) ;
                if ( variant( true ) == crt.has_formula() ) {
                    return false;
                }

                val =  crt.value( cx ) ;
                if ( variant::type_string != val.type()  && variant::type_empty != val.type() ) {
                    return false; // This handler can only handle texts and empty cells.
                }


                if ( variant::type_string == val.type() ) {
                    contained = false;
                    for ( int k = 0; k < static_cast<int>( m_List.size() ); k++ ) {
                        if ( ( val.string() ).compare( m_List[k] ) == 0 ) {
                            contained = true;
                            break;
                        }
                    }
                    if ( !contained ) {
                        return false; // This handler can only handle texts from the list.
                    }
                }
            }
        }

        if ( target.coverage().upper_left().row() > sequence.coverage().upper_left().row() ) { // drag downwards

            int col_offset = sequence.coverage().upper_left().column();
            for ( long int j = col_offset; j < col_offset + width; j++ ) {
                if ( !this->prepare( sequence.column( j ), cx, 1, 1 ) ) {
                    return false;
                }
                int row_offset = target.coverage().upper_left().row();
                range sequence_col = sequence.column( j );
                range target_col = target.column( j );
                long int row_count = static_cast<long int>( target_col.coverage().row_count() );
                for ( long int i = 0; i < row_count; i++ ) {
                    ind = i % height;
                    //range rs = range( sequence_col.row( ind ) );
                    range rt = target_col.row( row_offset + i ) ;
                    variant tmp = get_next( sequence_col, cx, 1, 1 );
                    rt.value( cx, tmp ); // next vertical

                    //TODO
                    // also set style, format and attributes:
                    //autofill_handler::handle_styles_and_formats( cx, rt, rs );
                }
            }
        }

        if ( target.coverage().upper_left().row() < sequence.coverage().upper_left().row() ) { // drag upwards

            int col_offset = sequence.coverage().upper_left().column();
            for ( long int j = col_offset; j < col_offset + width; j++ ) {
                if ( !this->prepare( sequence.column( j ), cx, 0, 1 ) ) {
                    return false;
                }
                int row_offset = target.coverage().upper_left().row();
                range sequence_col = sequence.column( j );
                range target_col = target.column( j );
                long int row_count = static_cast<long int>( target.coverage().row_count() );
                for ( long int i = 0; i < row_count; i++ ) {
                    ind = height - 1 - i % height;
                    //range rs = range( sequence.row( ind ).column( j ) );
                    range rt = target_col.row( row_offset + row_count - 1 - i );
                    rt.value( cx, get_next( sequence_col, cx, 0, 1 ) ); // previous vertical

                    //TODO
                    // also set style, format and attributes:
                    //AutoFillHandler::handle_styles_and_formats( cx, rt, rs );
                }
            }
        }

        if ( target.coverage().upper_left().column() > sequence.coverage().upper_left().column() ) { // drag rightwards

            int row_offset = sequence.coverage().upper_left().row();
            for ( long int j = row_offset; j < row_offset + height; j++ ) {
                if ( !this->prepare( sequence.row( j ), cx, 1, 0 ) ) {
                    return false;
                }
                int col_offset = target.coverage().upper_left().column();
                range sequence_row = sequence.row( j );
                range target_row = target.row( j );
                long int column_count = static_cast<long int>( target_row.coverage().column_count() );
                for ( long int i = 0; i < column_count; i++ ) {
                    ind = i % width;
                    //range rs = range( sequence.row( j ).column( ind ) );
                    range rt = target_row.column( col_offset + i );
                    rt.value( cx, get_next( sequence_row, cx, 1, 0 ) ); // next horizontal

                    //TODO
                    // also set style, format and attributes:
                    //AutoFillHandler::handle_styles_and_formats( cx, rt, rs );
                }
            }
        }

        if ( target.coverage().upper_left().column() < sequence.coverage().upper_left().column() ) { // drag leftwards

            int row_offset = sequence.coverage().upper_left().row();
            for ( long int j = row_offset; j < row_offset + height; j++ ) {
                if ( !this->prepare( sequence.row( j ), cx, 0, 0 ) ) {
                    return false;
                }
                int col_offset = target.coverage().upper_left().column();
                range sequence_row = sequence.row( j );
                range target_row = target.row( j );
                long int column_count = static_cast<long int>( target.coverage().column_count() );
                for ( long int i = 0; i < column_count; i++ ) {
                    ind = width - 1 - i % width;
                    //range rs = sequence.row( j ).column( ind );
                    range rt = target_row.column( col_offset + column_count - 1 - i );
                    rt.value( cx, get_next( sequence_row, cx, 0, 0 ) ); // previous horizontal

                    //TODO
                    // also set style, format and attributes:
                    //AutoFillHandler::handle_styles_and_formats( cx, rt, rs );
                }
            }
        }

        return true;
    }


}

