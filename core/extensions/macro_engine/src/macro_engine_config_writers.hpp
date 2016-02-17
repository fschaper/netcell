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

#ifndef MACRO_ENGINE_CONFIG_WRITERS_HPP
#define MACRO_ENGINE_CONFIG_WRITERS_HPP

#include "macro_engine_config.hpp"
#include "macro_engine_config_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace macro_engine_settings
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class extension_type_writer;
        class macro_engine_config_php_macro_engine_config_php_extensions_extensions_writer;
        class macro_engine_config_php_macro_engine_config_php_extensions_writer;
        class include_path_type_writer;
        class macro_engine_config_php_macro_engine_config_php_files_include_paths_writer;
        class macro_engine_config_php_macro_engine_config_php_files_writer;
        class function_type_writer;
        class macro_engine_config_php_macro_engine_config_functions_writer;
        class CT_general_settings_writer;
        class macro_engine_config_php_macro_engine_config_writer;
        class macro_engine_config_writer;

        class extension_type_writer : public type_writer
        {
            extension_type* t() {
                return static_cast<extension_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class macro_engine_config_php_macro_engine_config_php_extensions_extensions_writer : public type_writer
        {
            auto_type_writer< extension_type_writer > _extension_writer;
            macro_engine_config_php_macro_engine_config_php_extensions_extensions* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_php_extensions_extensions*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class macro_engine_config_php_macro_engine_config_php_extensions_writer : public type_writer
        {
            auto_type_writer< macro_engine_config_php_macro_engine_config_php_extensions_extensions_writer > _extensions_writer;
            macro_engine_config_php_macro_engine_config_php_extensions* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_php_extensions*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class include_path_type_writer : public type_writer
        {
            include_path_type* t() {
                return static_cast<include_path_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class macro_engine_config_php_macro_engine_config_php_files_include_paths_writer : public type_writer
        {
            auto_type_writer< include_path_type_writer > _include_path_writer;
            macro_engine_config_php_macro_engine_config_php_files_include_paths* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_php_files_include_paths*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class macro_engine_config_php_macro_engine_config_php_files_writer : public type_writer
        {
            auto_type_writer< macro_engine_config_php_macro_engine_config_php_files_include_paths_writer > _include_paths_writer;
            macro_engine_config_php_macro_engine_config_php_files* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_php_files*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class function_type_writer : public type_writer
        {
            function_type* t() {
                return static_cast<function_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class macro_engine_config_php_macro_engine_config_functions_writer : public type_writer
        {
            auto_type_writer< function_type_writer > _function_writer;
            macro_engine_config_php_macro_engine_config_functions* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_functions*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_general_settings_writer : public type_writer
        {
            CT_general_settings* t() {
                return static_cast<CT_general_settings*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class macro_engine_config_php_macro_engine_config_writer : public type_writer
        {
            auto_type_writer< macro_engine_config_php_macro_engine_config_php_extensions_writer > _php_extensions_writer;
            auto_type_writer< macro_engine_config_php_macro_engine_config_php_files_writer > _php_files_writer;
            auto_type_writer< macro_engine_config_php_macro_engine_config_functions_writer > _functions_writer;
            auto_type_writer< CT_general_settings_writer > _general_settings_writer;
            macro_engine_config_php_macro_engine_config* t() {
                return static_cast<macro_engine_config_php_macro_engine_config*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class macro_engine_config_writer : public type_writer
        {
            auto_type_writer< macro_engine_config_php_macro_engine_config_writer > _php_macro_engine_config_writer;
            macro_engine_config* t() {
                return static_cast<macro_engine_config*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

    }
}
#endif

