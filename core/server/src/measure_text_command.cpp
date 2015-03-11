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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"
#include "wss/measure_text_command.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/missing_text_metrics_exception.hpp"
#include "wss/text_metrics.hpp"
#include "wss/worksheet.hpp"
#include "wss/application.hpp"
#include "wss/range.hpp"
#include "wss/invalid_application_exception.hpp"

measure_text_command::measure_text_command( session& s, const unsigned int idx, const bool measure_row )
    : base_command<i_command>::base_command( s )
    , m_idx( idx )
    , m_measure_row( measure_row )
    , m_return( 0 )
{}

void measure_text_command::execute()
{
    shared_worksheet_type ws = m_session.selected().worksheet().lock();
    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }

    text_metrics::shared_engine_type text_metrics_engine = text_metrics::instance().engine();
    if ( !text_metrics_engine ) {
        throw missing_text_metrics_exception();
    }

    shared_application_type app = m_session.selected().application();
    if ( ! app ) {
        throw invalid_application_exception();
    }
    std::string default_style = app->default_style().serialize();

    //TODO: introduce DPI on session level
    i_text_metrics::text_dpi_pair resolution( 91, 91 );

    optional_sheet_range_type used_range = ws->used_range();

    if ( !used_range ) {
        return;
    }

    if ( m_measure_row ) {
        unsigned int i = 0;
        range r = ws->range( sheet_range( sheet_point( m_idx - 1, 0 ), sheet_point( m_idx - 1, used_range->lower_right().column() ) ) );
        variant::sparse_array_type styles = r.style( m_session )/*.array()*/;
        variant formatted_values = r.formatted_value( m_session );

        foreach( const variant & v, formatted_values.array() ) {
            i++;
            std::string value = v.string();
            if ( "" == value ) {
                continue;
            }

            variant style = styles[i-1];
            std::string format = style.string();
            if ( "" == format ) {
                format = default_style;
            }

            i_text_metrics::text_box    crt =  text_metrics_engine->measure_text(
                                                   style_set_type::unserialize( format ),
                                                   resolution,
                                                   value );
            if ( crt.second > m_return ) {
                m_return = crt.second;
            }
        }
    } else {
        unsigned int i = 0;
        range r = ws->range( sheet_range( sheet_point( 0, m_idx ), sheet_point( used_range->lower_right().row(), m_idx ) ) );
        variant::sparse_array_type styles = r.style( m_session )/*.array()*/;
        variant formatted_values = r.formatted_value( m_session );

        foreach( const variant & v, formatted_values.array() ) {
            i++;
            std::string value = v.string();
            if ( "" == value ) {
                continue;
            }

            variant style = styles[i-1];
            std::string format = style.string();
            if ( "" == format ) {
                format = default_style;
            }

            i_text_metrics::text_box    crt =  text_metrics_engine->measure_text(
                                                   style_set_type::unserialize( format ),
                                                   resolution,
                                                   value );
            if ( crt.second > m_return ) {
                m_return = crt.second;
            }
        }
    }
}

measure_text_command::result_type measure_text_command::value() const
{
    return m_return;
}

DEFINE_CLONEABLE( measure_text_command );
