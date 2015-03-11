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
#include "function_table_readers.hpp"
#include "function_table_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace jedox
{
    namespace wss
    {
        namespace xio
        {
            void general_type_reader::end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_parameter_separator_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->parameter_separator );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_column_separator_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->column_separator );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_row_separator_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->row_separator );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_use_dot_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->use_dot );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_boolean_true_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->boolean_true );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_boolean_false_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->boolean_false );
                    return;
                }
            }
            void group_type_reader::end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_translation_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->translation );
                    return;
                }
            }
            void group_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_id_literal ) ) {
                    driver()->context()->parse( value, t()->id );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_name_literal ) ) {
                    driver()->context()->parse( value, t()->name );
                    return;
                }
            }
            void groups_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_group_literal ) ) {
                    t()->group.resize( t()->group.size() + 1 );
                    driver()->push( localname, _group_reader.get_reader( &t()->group.back() ) );
                    return;
                }
            }
            void parameter_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_name_literal ) ) {
                    driver()->context()->parse( value, t()->name );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_type_literal ) ) {
                    driver()->context()->parse( value, t()->type.getset() );
                    return;
                }
            }
            void parameter_type_reader::read_value( const xstring& val )
            {{
                    driver()->context()->parse( val, *t() );
                }
            }
            void sequence_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_parameter_literal ) ) {
                    driver()->push( localname, _parameter_reader.get_reader( &t()->parameter ) );
                    return;
                }
            }
            void sequence_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_from_literal ) ) {
                    driver()->context()->parse( value, t()->from );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_to_literal ) ) {
                    driver()->context()->parse( value, t()->to );
                    return;
                }
            }
            void parameters_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_parameter_literal ) ) {
                    t()->parameter.resize( t()->parameter.size() + 1 );
                    driver()->push( localname, _parameter_reader.get_reader( &t()->parameter.back() ) );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_sequence_literal ) ) {
                    driver()->push( localname, _sequence_reader.get_reader( &t()->sequence.getset() ) );
                    return;
                }
            }
            void syntax_type_reader::end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_parameters_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->parameters );
                    return;
                }
            }
            void description_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_parameters_literal ) ) {
                    driver()->push( localname, _parameters_reader.get_reader( &t()->parameters.getset() ) );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_syntax_literal ) ) {
                    driver()->push( localname, _syntax_reader.get_reader( &t()->syntax ) );
                    return;
                }
            }
            void description_type_reader::end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table__short__literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->_short_ );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table__long__literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->_long_ );
                    return;
                }
            }
            void function_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_description_literal ) ) {
                    driver()->push( localname, _description_reader.get_reader( &t()->description ) );
                    return;
                }
            }
            void function_type_reader::end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_translation_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->translation );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_comment_literal ) ) {
                    driver()->context()->parse( driver()->get_characters(), t()->comment );
                    return;
                }
            }
            void function_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_name_literal ) ) {
                    driver()->context()->parse( value, t()->name );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_category_literal ) ) {
                    driver()->context()->parse( value, t()->category );
                    return;
                }
            }
            void translation_table_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_general_literal ) ) {
                    driver()->push( localname, _general_reader.get_reader( &t()->general ) );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_groups_literal ) ) {
                    driver()->push( localname, _groups_reader.get_reader( &t()->groups ) );
                    return;
                }
                if ( ::xercesc::XMLString::equals( localname, function_table_function_literal ) ) {
                    t()->function.resize( t()->function.size() + 1 );
                    driver()->push( localname, _function_reader.get_reader( &t()->function.back() ) );
                    return;
                }
            }
            void translation_table_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_lang_literal ) ) {
                    driver()->context()->parse( value, t()->lang );
                    return;
                }
            }
            void function_table_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
            {
                if ( ::xercesc::XMLString::equals( localname, function_table_translation_table_literal ) ) {
                    driver()->push( localname, _translation_table_reader.get_reader( &t()->translation_table.getset() ) );
                    return;
                }
            }
        }
    }
}
