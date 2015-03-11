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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "named_formula_utility.hpp"
#include "named_formula.hpp"
#include "wss/named_formula_reference.hpp"
#include "wss/sheet_point.hpp"
#include "wss/application.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/worksheet.hpp"
#include "named_formula_manager.hpp"

namespace named_formula_utils
{
    template<typename return_type>
    struct help_convert_to_string : non_instantiable {
        static return_type convert( const session&/* s*/, const variant& v ) {
            return v;
        }

        static return_type convert( const session&/* s*/, const std::string& v ) {
            return return_type( v );
        }
    };

    template<>
    struct help_convert_to_string<std::string> : non_instantiable {
        static std::string convert( const session& s, const variant& v ) {
            return v.as_string( s.locale() );
        }

        static std::string convert( const session&/* s*/, const std::string& v ) {
            return v;
        }
    };

    utf8_ci_string named_formula_utility::scope_as_string( const named_formula& nf )
    {
        if ( nf.scope() == named_formula_scope::workbook_scope ) {
            return "Workbook";
        }
        shared_worksheet_type ws = nf.worksheet().lock();
        if ( !ws ) {
            throw invalid_worksheet_exception();
        }
        return ws->name();
    }

    template<typename return_type>
    return_type named_formula_utility::to_vector( session& s, const named_formula& nf, const sheet_point& position )
    {
        return_type return_vec;
        typedef typename return_type::value_type kv_type;
        typedef help_convert_to_string<typename kv_type::second_type> converter;
        return_vec.push_back( kv_type( "uuid" , converter::convert( s, boost::lexical_cast<std::string>( nf.uuid() ) ) ) );
        return_vec.push_back( kv_type( "name",  converter::convert( s, convert_utf8_ci( nf.name() ) ) ) );
        return_vec.push_back( kv_type( "scope",  converter::convert( s, convert_utf8_ci( scope_as_string ( nf ) ) ) ) );
        return_vec.push_back( kv_type( "comment",  converter::convert( s, nf.comment() ) ) );
        calculation_context c( s, s.selected().application()->calculation_settings() );
        return_vec.push_back( kv_type( "value",  converter::convert( s, nf.value( c, position ) ) ) );
        return_vec.push_back( kv_type( "refers_to",  converter::convert( s, nf.formula( s.locale(), position ) ) ) );
        return return_vec;
    }

    template i_named_formula_manager::key_val_vec_type named_formula_utility::to_vector( session& s, const named_formula& nf, const sheet_point& position );
    template i_named_formula_manager::named_formula_key_val_vec_type named_formula_utility::to_vector( session& s, const named_formula& nf, const sheet_point& position );

    bool named_formula_utility::check_scope_ws_same( const uuid_type& scope_ws_id, const named_formula& nf )
    {
        shared_worksheet_type ws = nf.worksheet().lock();
        if ( ws && ( ws->uuid() == scope_ws_id ) ) {
            return true;
        }
        return false;
    }

    void named_formula_utility::copy_to_sheet( session& s, const named_formula& nf, const shared_worksheet_type& target_ws, const bool is_clone_sheet )
    {
        static_cast<named_formula_manager&>( target_ws->parent()->named_formulas() ).create( s, nf, target_ws );
        if ( !nf.comment().empty() ) {
            target_ws->parent()->named_formulas().comment( nf.comment(), named_formula_identifier( nf.name() , target_ws->uuid() ) );
        }
    }

    i_named_formula_manager::key_val_vec_type named_formula_utility::get_key_val_vec( session& s, const named_formula& nf, const sheet_point& position )
    {
        typedef std::pair<std::string, std::string> kv_pair_type;
        i_named_formula_manager::key_val_vec_type return_vec;
        return_vec.reserve( 6 );

        kv_pair_type tmp_uuid( "uuid", boost::lexical_cast<std::string>( nf.uuid() ) );
        return_vec.push_back( tmp_uuid );

        kv_pair_type tmp_name( "name", convert_utf8_ci( nf.name() ) );
        return_vec.push_back( tmp_name );
        shared_worksheet_type ws = nf.worksheet().lock();
        if ( ! ws ) {
            throw object_not_found_exception();
        }

        kv_pair_type tmp_scope( "scope", convert_utf8_ci( nf.scope_as_string() ) );
        return_vec.push_back( tmp_scope );

        kv_pair_type tmp_comment( "comment", nf.comment() );
        return_vec.push_back( tmp_comment );

        calculation_context cc( s, s.selected().application()->calculation_settings() );
        kv_pair_type tmp_value( "value", nf.value( cc, position ).as_string( s.locale() ) );
        return_vec.push_back( tmp_value );

        kv_pair_type tmp_refers_to( "refers_to", nf.formula( s.locale(), position ) );
        return_vec.push_back( tmp_refers_to );

        return return_vec;
    }
}
