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

#ifndef FUNCTION_TABLE_WRITERS_HPP
#define FUNCTION_TABLE_WRITERS_HPP

#include "function_table.hpp"
#include "function_table_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace jedox
{
    namespace wss
    {
        namespace xio
        {
            using namespace ::xercesc;
            using namespace ::xio::xcs;
            using namespace ::xio::xml::binding;

            class general_type_writer;
            class group_type_writer;
            class groups_type_writer;
            class parameter_type_writer;
            class sequence_type_writer;
            class parameters_type_writer;
            class syntax_type_writer;
            class description_type_writer;
            class function_type_writer;
            class translation_table_type_writer;
            class function_table_writer;

            class general_type_writer : public type_writer
            {
                general_type* t() {
                    return static_cast<general_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class group_type_writer : public type_writer
            {
                group_type* t() {
                    return static_cast<group_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class groups_type_writer : public type_writer
            {
                auto_type_writer< group_type_writer > _group_writer;
                groups_type* t() {
                    return static_cast<groups_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class parameter_type_writer : public type_writer
            {
                parameter_type* t() {
                    return static_cast<parameter_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class sequence_type_writer : public type_writer
            {
                auto_type_writer< parameter_type_writer > _parameter_writer;
                sequence_type* t() {
                    return static_cast<sequence_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class parameters_type_writer : public type_writer
            {
                auto_type_writer< parameter_type_writer > _parameter_writer;
                auto_type_writer< sequence_type_writer > _sequence_writer;
                parameters_type* t() {
                    return static_cast<parameters_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class syntax_type_writer : public type_writer
            {
                syntax_type* t() {
                    return static_cast<syntax_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class description_type_writer : public type_writer
            {
                auto_type_writer< parameters_type_writer > _parameters_writer;
                auto_type_writer< syntax_type_writer > _syntax_writer;
                description_type* t() {
                    return static_cast<description_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class function_type_writer : public type_writer
            {
                auto_type_writer< description_type_writer > _description_writer;
                function_type* t() {
                    return static_cast<function_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class translation_table_type_writer : public type_writer
            {
                auto_type_writer< general_type_writer > _general_writer;
                auto_type_writer< groups_type_writer > _groups_writer;
                auto_type_writer< function_type_writer > _function_writer;
                translation_table_type* t() {
                    return static_cast<translation_table_type*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

            class function_table_writer : public type_writer
            {
                auto_type_writer< translation_table_type_writer > _translation_table_writer;
                function_table* t() {
                    return static_cast<function_table*>( target() );
                }
            public:
                void write_target_to( xml_writer& w );
            };

        }
    }
}
#endif

