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
 *  Radu Racariu <radu@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

/*!
 * \brief
 * Counts the number of cells within a range that meet the given criteria.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of the cells within the range that meet the given criteria
 *
 * \details
 * Use criteria in the form of a number, expression, or text that defines which cells will be counted.
 * For example, criteria can be expressed as 32, "32", ">32", "apples".
 *
 * \see
 * function_sumif | function_if | function_countblank
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_countif( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the first parameter is no range, COUNTIF returns the #VALUE! error value.
    if ( parameters[0].i_type() != interpreter_variant::type_range ) {
        return interpreter_variant( variant::error_value );
    }

    // If an array is given, only take the first value.
    if ( parameters[1].type() == variant::type_array ) {
        const variant::sparse_array_type& arr = parameters[1].array();
        interpreter_variant newVal = interpreter_variant( arr[0] );
        parameters[1] = newVal;
    }

    // If a number is given, convert into String.
    if ( parameters[1].type() == variant::type_double ) {
        std::stringstream ssStream;
        ssStream << parameters[1].numeric();
        interpreter_variant newVal = interpreter_variant( ssStream.str() );
        parameters[1] = newVal;
    }

    // If a boolean is given, convert into String.
    if ( parameters[1].type() == variant::type_bool ) {
        if ( parameters[1].numeric() == 0 ) {
            parameters[1] = interpreter_variant( variant( "false" ) );
        } else {
            parameters[1] = interpreter_variant( variant( "true" ) );
        }
    }

    // If empty is given, take empty String.
    if ( parameters[1].type() == variant::type_empty ) {
        parameters[1] = interpreter_variant( variant( "" ) );
    }

    // Comparison method, always assuming String.
    int compareMethod = 0;
    std::string compareWith = "";
    if ( parameters[1].type() == variant::type_string ) {
        // Unequal
        if ( ( parameters[1].string() ).substr( 0, 2 ) == "<>" ) {
            compareMethod = 1;
            compareWith = ( parameters[1].string() ).substr( 2 );
        }
        // Smaller equal
        else if ( ( parameters[1].string() ).substr( 0, 2 ) == "<=" ) {
            compareMethod = 2;
            compareWith = ( parameters[1].string() ).substr( 2 );
        }
        // Greater equal
        else if ( ( parameters[1].string() ).substr( 0, 2 ) == ">=" ) {
            compareMethod = 3;
            compareWith = ( parameters[1].string() ).substr( 2 );
        }
        // Smaller
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == "<" ) {
            compareMethod = 4;
            compareWith = ( parameters[1].string() ).substr( 1 );
        }
        // Greater
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == ">" ) {
            compareMethod = 5;
            compareWith = ( parameters[1].string() ).substr( 1 );
        }
        // Equal
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == "=" ) {
            compareMethod = 0;
            compareWith = ( parameters[1].string() ).substr( 1 );
        }
        // Without operator
        else {
            compareWith = parameters[1].string();
        }
    } else {
        return interpreter_variant( variant::error_value );
    }

    double result = 0;
    range_reference& rref = range_reference_cast( parameters[0].reference() );
    sparse_range_array sra( rref, parameters.context() );
    //prepare compareWith before we enter the loop
    double compareDouble = 0.0;
    bool cast_was_good = true;
    try {
        compareDouble = boost::lexical_cast<double>( compareWith );
    } catch ( boost::bad_lexical_cast& ) {
        cast_was_good = false;

    }

    for ( unsigned int i = 0; i < sra.size(); i++ ) {
        switch ( sra[i].type() ) {
            case variant::type_double:
                if (  !cast_was_good ) {
                    continue;
                }
                switch ( compareMethod ) {
                    case 0:
                        if ( sra[i].numeric() == compareDouble ) {
                            result++;
                        }
                        break;
                    case 1:
                        if ( sra[i].numeric() != compareDouble ) {
                            result++;
                        }
                        break;
                    case 2:
                        if ( sra[i].numeric() <= compareDouble ) {
                            result++;
                        }
                        break;
                    case 3:
                        if ( sra[i].numeric() >= compareDouble ) {
                            result++;
                        }
                        break;
                    case 4:
                        if ( sra[i].numeric() < compareDouble ) {
                            result++;
                        }
                        break;
                    case 5:
                        if ( sra[i].numeric() > compareDouble ) {
                            result++;
                        }
                        break;
                    default:
                        if ( sra[i].numeric() == compareDouble ) {
                            result++;
                        }
                }
                break;
            case variant::type_bool:
                try {
                    std::string lowerString = compareWith;
                    boost::algorithm::to_lower( lowerString );
                    double compareBool = static_cast<double> ( boost::lexical_cast<bool>( lowerString ) );
                    switch ( compareMethod ) {
                        case 0:
                            if ( sra[i].numeric() == compareBool ) {
                                result++;
                            }
                            break;
                        case 1:
                            if ( sra[i].numeric() != compareBool ) {
                                result++;
                            }
                            break;
                        case 2:
                            if ( sra[i].numeric() <= compareBool ) {
                                result++;
                            }
                            break;
                        case 3:
                            if ( sra[i].numeric() >= compareBool ) {
                                result++;
                            }
                            break;
                        case 4:
                            if ( sra[i].numeric() < compareBool ) {
                                result++;
                            }
                            break;
                        case 5:
                            if ( sra[i].numeric() > compareBool ) {
                                result++;
                            }
                            break;
                        default:
                            if ( sra[i].numeric() == compareBool ) {
                                result++;
                            }
                    }
                } catch ( boost::bad_lexical_cast& ) {
                    continue;
                }
                break;
            case variant::type_string:
                switch ( compareMethod ) {
                    case 0:
                        if ( boost::algorithm::iequals( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                        break;
                    case 1:
                        if ( !boost::algorithm::iequals( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                        break;
                    case 2:
                        if ( !boost::algorithm::ilexicographical_compare( compareWith, sra[i].string() ) ) {
                            result++;
                        }
                        break;
                    case 3:
                        if ( !boost::algorithm::ilexicographical_compare( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                        break;
                    case 4:
                        if ( boost::algorithm::ilexicographical_compare( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                        break;
                    case 5:
                        if ( boost::algorithm::ilexicographical_compare( compareWith, sra[i].string() ) ) {
                            result++;
                        }
                        break;
                    default:
                        if ( boost::algorithm::iequals( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                }
                break;
            default:
                continue;
        }
    }
    return interpreter_variant( variant( result ) );
    // Counts the number of cells within a range that meet the given criteria.
}
