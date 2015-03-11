/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
*  Florian Schaper <florian.schaper@jedox.com>
*/
#undef ERROR
#undef GetMessage

#include "palo_wrapper.hpp"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/any.hpp>
#include "palo_context.hpp"
#include "palo_argument_list.hpp"
#include "logging.hpp"

#include <libpalo_ng/Palo/Exception/ElementNotFoundException.h>
#include <libpalo_ng/Network/SocketException.h>

#include <PaloSpreadsheetFuncs/WrongParamCountException.h>
#include <PaloSpreadsheetFuncs/ArgumentException.h>
#include <PaloSpreadsheetFuncs/InvalidRequestException.h>
#include <PaloSpreadsheetFuncs/SpreadsheetFuncsBase.h>
#include <PaloSpreadsheetFuncs/SpreadsheetFuncsException.h>
#include <libconnectionpool/Exception.h>
#include <libconnectionpool/ConnectionException.h>

#include <wss/type.hpp>
#include <wss/session.hpp>
#include <wss/variant.hpp>
#include "transform_result.hpp"

#ifdef _DEBUG
#define LOG_TIME_TAKEN_IN_PALO_FUNCTIONS 1
#endif

#ifdef LOG_TIME_TAKEN_IN_PALO_FUNCTIONS
#include <boost/timer.hpp>
const double min_palo_time_taken_for_timer_to_show_up = 0.2;
#define LOG_DEBUG_PALO_TIMING_BEGIN() boost::timer performance;
#define LOG_DEBUG_PALO_TIMING_END() if (performance.elapsed() >= min_palo_time_taken_for_timer_to_show_up){ LOG_PALO_DEBUG( function_name << " request completed in " << performance.elapsed() << " seconds." ); }
#else
#define LOG_DEBUG_PALO_TIMING_BEGIN()
#define LOG_DEBUG_PALO_TIMING_END()
#endif

#ifdef _DEBUG
#define LOG_PALO_EXCEPTION(msg) LOG_PALO_INFO( "exception caught in "<< parameter.context().caller()->get_debug_identifier()<<" : '" << msg );
#else
#define LOG_PALO_EXCEPTION(msg) LOG_PALO_INFO(msg );
#endif // _DEBUG

interpreter_variant palo_wrapper::operator()( palo_function p_function, const char* function_name, function_parameter& parameter )
{
#   undef ERROR
#   undef GetMessage

    palo_context settings;
    static spreadsheet_function& f = spreadsheet_function::instance();

    palo_argument_list arguments( parameter );
    GenericArgumentArray ga( arguments.get() );

    variant return_value;

    interpreter_context& ic = parameter.context();

    const bool is_array = ic.caller()->is_array();
    const bool is_inside = ic.is_inside_function() || ic.is_inside_named_formula();

    const size_t cols = is_array ? ic.caller()->array_coverage().column_count() : ( is_inside ? 0 : 1 );
    const size_t rows = is_array ? ( ic.caller()->array_coverage().count() / ic.caller()->array_coverage().column_count() ) : ( is_inside ? 0 : 1 );

    static const std::string palo_subset_function_name = "FPaloSubset";
    static const std::string palo_datav_function_name = "FPaloGetdataV";

    try {
        palo_cell_adapter tmp( parameter.session(), return_value, !ic.is_inside_named_formula(), rows, cols );

        if ( ! is_inside ) {
            ic.fill_array_with_empty_values();
        }

        const bool is_subset_inside_nf = ( !is_array ) && ic.is_inside_named_formula() && ( palo_subset_function_name.compare( function_name ) == 0 );

        if ( is_subset_inside_nf ) {
            tmp.set_subset_inside_nf();
        }

        LOG_DEBUG_PALO_TIMING_BEGIN();
        ( f.*p_function )( tmp, settings, ga );
        LOG_DEBUG_PALO_TIMING_END();

    } catch ( const jedox::palo::SocketExceptionConnectionTimedOut& e ) {
        return_value = variant( variant::error_value );
        return_value.error_message( e.what() );
        LOG_PALO_EXCEPTION( e.what() );
    } catch ( const Palo::Types::WrongParamCountException& e ) {
        return_value = variant( variant::error_value );
        return_value.error_message( e.what() );
        LOG_PALO_EXCEPTION( e.what() );
    } catch ( const jedox::palo::ElementNotFoundException& e ) {
        return_value = variant( variant::error_value );
        return_value.error_message( e.longDescription() );
        LOG_PALO_EXCEPTION( e.longDescription() );
    }   catch ( const Palo::Types::ConnectionException& e ) {
        return_value = variant( variant::error_value );
        return_value.error_message( e.what() );
        LOG_PALO_EXCEPTION( e.what() );
    }   catch ( const Palo::Types::Exception& e ) {
        return_value = variant( variant::error_value );
        return_value.error_message( e.what() );
        LOG_PALO_EXCEPTION( e.what() );
    }   catch ( const std::runtime_error& e ) {
        return_value = variant( variant::error_value );
        return_value.error_message( e.what() );
        LOG_PALO_EXCEPTION( e.what() );
    }   catch ( const std::exception& e ) {
        return_value = variant( variant::error_value );
        return_value.error_message( e.what() );
        LOG_PALO_EXCEPTION( e.what() );
    }
    if ( return_value.type() == variant::type_array ) {
        if ( palo_datav_function_name.compare( function_name ) == 0 ) {
            return_value.column_width( ic.caller()->array_coverage().column_count() );
        }
    }

    return interpreter_variant( return_value );
}
