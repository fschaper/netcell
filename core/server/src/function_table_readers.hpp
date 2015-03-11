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

#ifndef FUNCTION_TABLE_READERS_HPP
#define FUNCTION_TABLE_READERS_HPP

#include "function_table.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace jedox
{
    namespace wss
    {
        namespace xio
        {
            using namespace ::xercesc;
            using namespace ::xio::xcs;
            using namespace ::xio::xml::binding;

            class general_type_reader;
            class group_type_reader;
            class groups_type_reader;
            class parameter_type_reader;
            class sequence_type_reader;
            class parameters_type_reader;
            class syntax_type_reader;
            class description_type_reader;
            class function_type_reader;
            class translation_table_type_reader;
            class function_table_reader;

            class general_type_reader : public type_reader
            {
            protected:
                general_type* t() {
                    return static_cast<general_type*>( target() );
                }
                void end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
            };

            class group_type_reader : public type_reader
            {
            protected:
                group_type* t() {
                    return static_cast<group_type*>( target() );
                }
                void end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
                void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
            };

            class groups_type_reader : public type_reader
            {
                auto_type_reader< group_type_reader > _group_reader;
            protected:
                groups_type* t() {
                    return static_cast<groups_type*>( target() );
                }
                void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            };

            class parameter_type_reader : public type_reader
            {
            protected:
                parameter_type* t() {
                    return static_cast<parameter_type*>( target() );
                }
                void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
                void read_value( const xstring& val );
            };

            class sequence_type_reader : public type_reader
            {
                auto_type_reader< parameter_type_reader > _parameter_reader;
            protected:
                sequence_type* t() {
                    return static_cast<sequence_type*>( target() );
                }
                void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
                void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
            };

            class parameters_type_reader : public type_reader
            {
                auto_type_reader< parameter_type_reader > _parameter_reader;
                auto_type_reader< sequence_type_reader > _sequence_reader;
            protected:
                parameters_type* t() {
                    return static_cast<parameters_type*>( target() );
                }
                void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            };

            class syntax_type_reader : public type_reader
            {
            protected:
                syntax_type* t() {
                    return static_cast<syntax_type*>( target() );
                }
                void end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
            };

            class description_type_reader : public type_reader
            {
                auto_type_reader< parameters_type_reader > _parameters_reader;
                auto_type_reader< syntax_type_reader > _syntax_reader;
            protected:
                description_type* t() {
                    return static_cast<description_type*>( target() );
                }
                void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
                void end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
            };

            class function_type_reader : public type_reader
            {
                auto_type_reader< description_type_reader > _description_reader;
            protected:
                function_type* t() {
                    return static_cast<function_type*>( target() );
                }
                void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
                void end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
                void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
            };

            class translation_table_type_reader : public type_reader
            {
                auto_type_reader< general_type_reader > _general_reader;
                auto_type_reader< groups_type_reader > _groups_reader;
                auto_type_reader< function_type_reader > _function_reader;
            protected:
                translation_table_type* t() {
                    return static_cast<translation_table_type*>( target() );
                }
                void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
                void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
            };

            class function_table_reader : public type_reader
            {
                auto_type_reader< translation_table_type_reader > _translation_table_reader;
            protected:
                function_table* t() {
                    return static_cast<function_table*>( target() );
                }
                void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            };

        }
    }
}
#endif

