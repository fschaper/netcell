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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/set_value_command.hpp"
#include "wss/worksheet.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/formatter.hpp"
#include "wss/core2_compatibility.hpp"
#include "wss/range.hpp"

set_value_command::set_value_command( session& s, const sheet_range& p, const variant& v )
    : abstract_undoable_command( s )
    , m_position( p )
    , m_new_value( v )
{}

void set_value_command::execute()
{
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();

    range r = ws->range( m_position );
#ifdef CORE_DO_UNDO_SUPPORT
    if ( supports_do_undo::check( ws ) ) {
        m_old_value = r.formula( m_session );
    }
#endif

#ifdef _CORE2_COMPATIBILITY_ON_AUTO_DETECT_INPUT_
    r.value( m_session, m_new_value );
#else
    variant value;
    std::string format;
    variant old_format = r.format( m_session );

    if ( variant::type_string == m_new_value.type() ) {
        bool allow_type_detection = true;
        bool is_quote_prefixed = false;

        if ( m_new_value.string()[0] == '\'' ) {
            is_quote_prefixed = true;
            allow_type_detection = false;
        }

        foreach( const variant::sparse_array_type::mapping_type::value_type & v, old_format.array().direct() ) {
            if ( v.second.string() == "@" ) {
                allow_type_detection = false;
                break;
            } else {
                size_t quotes = 0;
                size_t semicolumns = 0;
                const std::string& actual_val = v.second.string();

                for ( size_t i = 0, e = actual_val.size(); i < e; ++i ) {
                    if ( '\"' == actual_val[i] ) {
                        quotes++;
                    } else if ( ';' == actual_val[i] ) {
                        semicolumns++;
                    }
                }
                if ( 3 == semicolumns && 8 == quotes ) {
                    allow_type_detection = false;
                    break;
                }
            }
        }

        if ( is_quote_prefixed ) {

            r.style( m_session, style_set_type::unserialize( "quotePrefix:1;" ) );
        }

        if ( allow_type_detection  ) {
            //test a recognized format
            if ( formatter::instance().engine() && formatter::instance().engine()->find_format( m_session, m_new_value.string(), value, format ) ) {
                if ( 0 == r.format( m_session ).array().direct().size() ) {
                    r.format( m_session, format );
                }
                r.value( m_session, value );
                return;
            }

            //test a possible formula
            std::string formula_candidate = m_new_value.string();
            //only promote strings starting woth '+'/'-'
            if ( !formula_candidate.empty() && formula_candidate[0] != '=' && ( formula_candidate[0] == '-' || formula_candidate[0] == '+' ) ) {
                formula_candidate = "=" + formula_candidate;
                if ( r.validate_formula( m_session, formula_candidate ) ) {
                    r.value( m_session, variant( formula_candidate ) );
                    return;
                }
            }
        }
    }

    r.value( m_session, m_new_value );
#endif
}

void set_value_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    assert( "un_execute called on a command that is on a temporary wb or on a cloned sheet!" && supports_do_undo::check( ws ) );
    range r = ws->range( m_position );
    m_new_value = r.formula( m_session );
    r.value( m_session, m_old_value );
#endif
}

DEFINE_CLONEABLE( set_value_command );
