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
#include "sequence_number_fill_handler.hpp"



namespace autofill_internal
{

    sequence_number_fill_handler::sequence_number_fill_handler()
    {
        calls = 0;
        empties = 0;
        leadingEmpties = 0;
        closingEmpties = 0;
        nums = 0;
        ym = 0.0;
        diff = 0.0;
        stepEmpties = 0;
        regular = true;
        actualNumber = 0.0;
        a = 0.0;
        axb = 0.0;
        variance = 0.0;
    }


    void sequence_number_fill_handler::prepare( const range& values, session& cx, int next, int vertical )
    {
        // If next == 0, we calculate previous values ( to the left or up ), else next values ( to the right or down ).
        // If vertical == 0, we calculate values to the left or right, else up or down.
        calls = 0;
        empties = 0;
        nums = 0;
        double xm = 0.0;
        ym = 0.0;
        variant val;
        double firstNumber = 0.0;
        leadingEmpties = 0;
        bool leading = true;
        // Count leading empties and numerical values. Calculate xm and ym.
        if ( vertical == 0 ) {
            unsigned int col_offset = values.coverage().upper_left().column();
            unsigned int col_count = values.coverage().column_count();
            for ( unsigned int i = col_offset; i < col_offset + col_count ; i++ ) {
                val = values.column( i ).value( cx );
                if ( variant::type_double == val.type() ) {
                    if ( leading ) {
                        firstNumber = val.numeric();
                    }
                    leading = false;
                    nums++;
                    xm += i - col_offset;
                    ym += val.numeric();
                } else {
                    if ( leading ) {
                        leadingEmpties++;
                    }
                }
            }
        } else {
            unsigned int row_offset = values.coverage().upper_left().row();
            unsigned int row_count = values.coverage().row_count();
            for ( unsigned int i = row_offset; i < row_offset + row_count ; i++ ) {
                val = values.row( i ).value( cx );
                if ( variant::type_double == val.type() ) {
                    if ( leading ) {
                        firstNumber = val.numeric();
                    }
                    leading = false;
                    nums++;
                    xm += i - row_offset;
                    ym += val.numeric();
                } else {
                    if ( leading ) {
                        leadingEmpties++;
                    }
                }
            }
        }

        if ( nums == 0 ) {
            return;
        }
        xm /= nums;
        ym /= nums;
        closingEmpties = 0;
        // Count closing empties:
        if ( vertical == 0 ) {
            unsigned int col_offset = values.coverage().upper_left().column();
            unsigned int col_count = values.coverage().column_count();
            for ( int i = col_offset + col_count - 1; i > -1; i-- ) {
                val = values.column( i ).value( cx );
                if ( variant::type_double == val.type() ) {
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
                if ( variant::type_double == val.type() ) {
                    break;
                } else {
                    closingEmpties++;
                }
            }
        }

        // Calculate the difference of the first two numerical values.
        diff = 0.0; // default.
        stepEmpties = 0;
        regular = true;
        if ( nums > 1 ) {
            int first = leadingEmpties;
            int second = first + 1;
            if ( vertical == 0 ) {
                unsigned int col_offset = values.coverage().upper_left().column();
                int col_count = values.coverage().column_count();
                val = values.column( col_offset + first ).value( cx );
                diff = - val.numeric();
                val = values.column( col_offset + second ).value( cx );
                for ( ; val.type() != variant::type_double; ( second++, val = values.column( col_offset + second ).value( cx ) ) ) {}
                stepEmpties = second - first - 1;
                diff += val.numeric();
                first = second;
                second = first + 1;
                while ( second < col_count - closingEmpties ) {
                    val = values.column( col_offset + second ).value( cx );
                    for ( ; val.type() != variant::type_double; ( second++, val = values.column( col_offset + second ).value( cx ) ) ) {}
                    if ( second - first - 1 != stepEmpties ) {
                        regular = false;
                        break;
                    }
                    first = second;
                    second = first + 1;
                }
            } else {
                unsigned int row_offset = values.coverage().upper_left().row();
                int row_count = values.coverage().row_count();
                val = values.row( row_offset + first ).value( cx );
                diff = - val.numeric();
                val = values.row( row_offset + second ).value( cx );
                for ( ; val.type() != variant::type_double; ( second++, val = values.row( row_offset + second ).value( cx ) ) ) {}
                stepEmpties = second - first - 1;
                diff += val.numeric();
                first = second;
                second = first + 1;
                while ( second < row_count - closingEmpties ) {
                    val = values.row( row_offset + second ).value( cx );
                    for ( ; val.type() != variant::type_double; ( second++, val = values.row( row_offset + second ).value( cx ) ) ) {}
                    if ( second - first - 1 != stepEmpties ) {
                        regular = false;
                        break;
                    }
                    first = second;
                    second = first + 1;
                }
            }
        }
        // Calculate the slope.
        double enumerator = 0.0;
        double denominator = 0.0;
        if ( vertical == 0 ) {
            unsigned int col_offset = values.coverage().upper_left().column();
            unsigned int col_count = values.coverage().column_count();
            for ( unsigned int i = col_offset; i < col_offset + col_count ; i++ ) {
                val = values.column( i ).value( cx );
                if ( variant::type_double == val.type() ) {
                    enumerator += ( i - col_offset - xm ) * ( val.numeric() - ym );
                    denominator += ( i - col_offset - xm ) * ( i - col_offset - xm );
                }
            }
        } else {
            unsigned int row_offset = values.coverage().upper_left().row();
            unsigned int row_count = values.coverage().row_count();
            for ( unsigned int i = row_offset; i < row_offset + row_count ; i++ ) {
                val = values.row( i ).value( cx );
                if ( variant::type_double == val.type() ) {
                    enumerator += ( i - row_offset - xm ) * ( val.numeric() - ym );
                    denominator += ( i - row_offset - xm ) * ( i - row_offset - xm );
                }
            }
        }
        a = ( nums == 1 ) ? 0.0 : ( enumerator / denominator );
        axb = a * xm - ym;
        // Calculate the variance of the slope.
        variance = 0.0;
        if ( nums > 2 ) {
            double residua = 0.0;
            double residuum;
            if ( vertical == 0 ) {
                unsigned int col_offset = values.coverage().upper_left().column();
                unsigned int col_count = values.coverage().column_count();
                for ( unsigned int i = col_offset; i < col_offset + col_count; i++ ) {
                    val = values.column( i ).value( cx );
                    if ( variant::type_double == val.type() ) {
                        residuum = val.numeric() - a * ( i - col_offset )  + axb;
                        residua += residuum * residuum;
                    }
                }
            } else {
                unsigned int row_offset = values.coverage().upper_left().row();
                unsigned int row_count = values.coverage().row_count();
                for ( unsigned int i = row_offset; i < row_offset + row_count; i++ ) {
                    val = values.row( i ).value( cx );
                    if ( variant::type_double == val.type() ) {
                        residuum = val.numeric() - a * ( i - row_offset ) + axb;
                        residua += residuum * residuum;
                    }
                }
            }
            variance = residua / ( ( nums - 2 ) * denominator );
        }

        if ( next == 0 ) {
            actualNumber = firstNumber;
        } else {
            actualNumber = firstNumber + diff * ( nums - 1 );
        }
    }

    variant sequence_number_fill_handler::get_next( const range& values, session& cx, int next, int vertical )
    {
        // If next == 0, we calculate previous values ( to the left or up ), else next values ( to the right or down ).
        // If vertical == 0, we calculate values to the left or right, else up or down.

        // If there are only empty cells, return type_empty.
        if ( nums == 0 ) {
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
            empties++;
            return variant::type_empty;
        }

        // If the sequence is exact, empty values are continued.
        if ( variance < 5.1259894389198492e-13 ) {
            if ( vertical == 0 ) {
                unsigned int col_offset = values.coverage().upper_left().column();
                if ( variant::type_empty == values.column( col_offset + ind ).value( cx ).type() ) {
                    calls++;
                    if ( regular ) {
                        // Only if the source is regular, inner empty cells are ignored.
                        empties++;
                    }
                    return variant::type_empty;
                }
            } else {
                unsigned int row_offset = values.coverage().upper_left().row();
                if ( variant::type_empty == values.row( row_offset + ind ).value( cx ).type() ) {
                    calls++;
                    if ( regular ) {
                        // Only if the source is regular, inner empty cells are ignored.
                        empties++;
                    }
                    return variant::type_empty;
                }
            }
        }

        if ( next == 0 ) {
            if ( variance < 5.1259894389198492e-13 && regular ) {
                actualNumber -= diff;
            } else {
                actualNumber = a * ( -1 - calls + empties + leadingEmpties ) - axb;
            }
        } else {
            if ( variance < 5.1259894389198492e-13 && regular ) {
                actualNumber += diff;
            } else {
                actualNumber = a * ( static_cast<int>( values.coverage().count() ) + calls - empties - closingEmpties ) - axb;
            }
        }
        calls++;
        return variant( actualNumber );
    }


    bool sequence_number_fill_handler::handle_sequence( session& cx, const range& sequence, range& target )
    {
        long int width = sequence.coverage().column_count();
        long int height = sequence.coverage().row_count();
        long int ind;

        // Check if there are only numbers or empty cells.
        int col_offset = sequence.coverage().upper_left().column();
        int row_offset = sequence.coverage().upper_left().row();
        for ( long int j = col_offset; j < col_offset + width; j++ ) {
            range row_range = range( sequence.column( j ) );
            for ( long int i = row_offset; i < row_offset + height; i++ ) {
                if ( variant( true ) == row_range.row( i ).has_formula() ) {
                    return false;
                }
                if ( variant::type_double != row_range.row( i ).value( cx ).type() &&
                        variant::type_empty != row_range.row( i ).value( cx ).type() ) {
                    return false; // This handler can only handle numbers and empty cells.
                }
            }
        }

        if ( target.coverage().upper_left().row() > sequence.coverage().upper_left().row() ) { // drag downwards

            int col_offset = sequence.coverage().upper_left().column();
            for ( long int j = col_offset; j < col_offset + width; j++ ) {

                this->prepare( sequence.column( j ), cx, 1, 1 );

                int row_offset = target.coverage().upper_left().row();
                range sequence_col = sequence.column( j );
                range target_col = target.column( j );
                long int row_count = static_cast<long int>( target_col.coverage().row_count() );
                for ( long int i = 0; i < row_count; i++ ) {
                    ind = i % height;
                    //range rs = sequence.row( ind ).column( j );
                    range rt = target_col.row( row_offset + i ) ;
                    variant tmp = get_next( sequence_col, cx, 1, 1 );
                    rt.value( cx, tmp ); // next vertical

                    //TODO
                    // also set style, format and attributes:
                    //AutoFillHandler::handle_styles_and_formats( cx, rt, rs );
                }
            }
        }

        if ( target.coverage().upper_left().row() < sequence.coverage().upper_left().row() ) { // drag upwards

            int col_offset = sequence.coverage().upper_left().column();
            for ( long int j = col_offset; j < col_offset + width; j++ ) {

                this->prepare( sequence.column( j ), cx, 0, 1 );

                int row_offset = target.coverage().upper_left().row();
                range sequence_col = sequence.column( j );
                range target_col = target.column( j );
                long int row_count = static_cast<long int>( target.coverage().row_count() );
                for ( long int i = 0; i < row_count; i++ ) {
                    ind = height - 1 - i % height;
                    //range rs = sequence.row( ind ).column( j );
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

                this->prepare( sequence.row( j ), cx, 1, 0 );

                int col_offset = target.coverage().upper_left().column();
                range sequence_row = sequence.row( j );
                range target_row = target.row( j );
                long int column_count = static_cast<long int>( target_row.coverage().column_count() );
                for ( long int i = 0; i < column_count; i++ ) {
                    ind = i % width;
                    //range rs = sequence.row( j ).column( ind );
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

                this->prepare( sequence.row( j ), cx, 0, 0 );

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

