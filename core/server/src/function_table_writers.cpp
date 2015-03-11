/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 */


// This file has been auto-generated. Don't change it by hand!

#include "precompiled_header.hpp"
#include "function_table_writers.hpp"
#include "function_table_literals.hpp"

namespace jedox
{
    namespace wss
    {
        namespace xio
        {
            void general_type_writer::write_target_to( xml_writer& w )
            {
                w.start_element( 0, function_table_parameter_separator_literal );
                w.write_element_value( context()->serialize( t()->parameter_separator ) );
                w.end_element( 0, function_table_parameter_separator_literal );
                w.start_element( 0, function_table_column_separator_literal );
                w.write_element_value( context()->serialize( t()->column_separator ) );
                w.end_element( 0, function_table_column_separator_literal );
                w.start_element( 0, function_table_row_separator_literal );
                w.write_element_value( context()->serialize( t()->row_separator ) );
                w.end_element( 0, function_table_row_separator_literal );
                w.start_element( 0, function_table_use_dot_literal );
                w.write_element_value( context()->serialize( t()->use_dot ) );
                w.end_element( 0, function_table_use_dot_literal );
                w.start_element( 0, function_table_boolean_true_literal );
                w.write_element_value( context()->serialize( t()->boolean_true ) );
                w.end_element( 0, function_table_boolean_true_literal );
                w.start_element( 0, function_table_boolean_false_literal );
                w.write_element_value( context()->serialize( t()->boolean_false ) );
                w.end_element( 0, function_table_boolean_false_literal );
            }

            void group_type_writer::write_target_to( xml_writer& w )
            {
                w.attribute( 0, function_table_id_literal, context()->serialize( t()->id ) );
                w.attribute( 0, function_table_name_literal, context()->serialize( t()->name ) );
                w.start_element( 0, function_table_translation_literal );
                w.write_element_value( context()->serialize( t()->translation ) );
                w.end_element( 0, function_table_translation_literal );
            }

            void groups_type_writer::write_target_to( xml_writer& w )
            {
                for ( size_t sqi = 0; sqi < t()->group.size(); ++sqi ) {
                    w.start_element( 0, function_table_group_literal );
                    _group_writer.get_writer( context(), &t()->group[sqi] )->write_target_to( w );
                    w.end_element( 0, function_table_group_literal );
                }
            }

            void parameter_type_writer::write_target_to( xml_writer& w )
            {
                w.attribute( 0, function_table_name_literal, context()->serialize( t()->name ) );
                if ( t()->type.present() ) {
                    w.attribute( 0, function_table_type_literal, context()->serialize( t()->type.get() ) );
                }
                w.write_element_value( context()->serialize( *t() ) );
            }

            void sequence_type_writer::write_target_to( xml_writer& w )
            {
                w.attribute( 0, function_table_from_literal, context()->serialize( t()->from ) );
                w.attribute( 0, function_table_to_literal, context()->serialize( t()->to ) );
                w.start_element( 0, function_table_parameter_literal );
                _parameter_writer.get_writer( context(), &t()->parameter )->write_target_to( w );
                w.end_element( 0, function_table_parameter_literal );
            }

            void parameters_type_writer::write_target_to( xml_writer& w )
            {
                for ( size_t sqi = 0; sqi < t()->parameter.size(); ++sqi ) {
                    w.start_element( 0, function_table_parameter_literal );
                    _parameter_writer.get_writer( context(), &t()->parameter[sqi] )->write_target_to( w );
                    w.end_element( 0, function_table_parameter_literal );
                }
                if ( t()->sequence.present() ) {
                    w.start_element( 0, function_table_sequence_literal );
                    _sequence_writer.get_writer( context(), &t()->sequence.get() )->write_target_to( w );
                    w.end_element( 0, function_table_sequence_literal );
                }
            }

            void syntax_type_writer::write_target_to( xml_writer& w )
            {
                w.start_element( 0, function_table_parameters_literal );
                w.write_element_value( context()->serialize( t()->parameters ) );
                w.end_element( 0, function_table_parameters_literal );
            }

            void description_type_writer::write_target_to( xml_writer& w )
            {
                if ( t()->parameters.present() ) {
                    w.start_element( 0, function_table_parameters_literal );
                    _parameters_writer.get_writer( context(), &t()->parameters.get() )->write_target_to( w );
                    w.end_element( 0, function_table_parameters_literal );
                }
                w.start_element( 0, function_table_syntax_literal );
                _syntax_writer.get_writer( context(), &t()->syntax )->write_target_to( w );
                w.end_element( 0, function_table_syntax_literal );
                w.start_element( 0, function_table__short__literal );
                w.write_element_value( context()->serialize( t()->_short_ ) );
                w.end_element( 0, function_table__short__literal );
                w.start_element( 0, function_table__long__literal );
                w.write_element_value( context()->serialize( t()->_long_ ) );
                w.end_element( 0, function_table__long__literal );
            }

            void function_type_writer::write_target_to( xml_writer& w )
            {
                w.attribute( 0, function_table_name_literal, context()->serialize( t()->name ) );
                w.attribute( 0, function_table_category_literal, context()->serialize( t()->category ) );
                w.start_element( 0, function_table_translation_literal );
                w.write_element_value( context()->serialize( t()->translation ) );
                w.end_element( 0, function_table_translation_literal );
                w.start_element( 0, function_table_description_literal );
                _description_writer.get_writer( context(), &t()->description )->write_target_to( w );
                w.end_element( 0, function_table_description_literal );
                w.start_element( 0, function_table_comment_literal );
                w.write_element_value( context()->serialize( t()->comment ) );
                w.end_element( 0, function_table_comment_literal );
            }

            void translation_table_type_writer::write_target_to( xml_writer& w )
            {
                w.attribute( 0, function_table_lang_literal, context()->serialize( t()->lang ) );
                w.start_element( 0, function_table_general_literal );
                _general_writer.get_writer( context(), &t()->general )->write_target_to( w );
                w.end_element( 0, function_table_general_literal );
                w.start_element( 0, function_table_groups_literal );
                _groups_writer.get_writer( context(), &t()->groups )->write_target_to( w );
                w.end_element( 0, function_table_groups_literal );
                for ( size_t sqi = 0; sqi < t()->function.size(); ++sqi ) {
                    w.start_element( 0, function_table_function_literal );
                    _function_writer.get_writer( context(), &t()->function[sqi] )->write_target_to( w );
                    w.end_element( 0, function_table_function_literal );
                }
            }

            void function_table_writer::write_target_to( xml_writer& w )
            {
                if ( t()->translation_table.present() ) {
                    w.start_element( 0, function_table_translation_table_literal );
                    w.attribute( 0, function_table_xmlns_literal, function_table_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                    w.attribute( function_table_xmlns_literal, function_table_xs_literal, function_table_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal );
                    _translation_table_writer.get_writer( context(), &t()->translation_table.get() )->write_target_to( w );
                    w.end_element( 0, function_table_translation_table_literal );
                }
            }

        }
    }
}
