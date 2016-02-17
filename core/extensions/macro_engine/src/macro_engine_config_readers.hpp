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

#ifndef MACRO_ENGINE_CONFIG_READERS_HPP
#define MACRO_ENGINE_CONFIG_READERS_HPP

#include "macro_engine_config.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace macro_engine_settings
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class extension_type_reader;
        class macro_engine_config_php_macro_engine_config_php_extensions_extensions_reader;
        class macro_engine_config_php_macro_engine_config_php_extensions_reader;
        class include_path_type_reader;
        class macro_engine_config_php_macro_engine_config_php_files_include_paths_reader;
        class macro_engine_config_php_macro_engine_config_php_files_reader;
        class function_type_reader;
        class macro_engine_config_php_macro_engine_config_functions_reader;
        class CT_general_settings_reader;
        class macro_engine_config_php_macro_engine_config_reader;
        class macro_engine_config_reader;

        class extension_type_reader : public type_reader
        {
        protected:
            extension_type* t() {
                return static_cast<extension_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class macro_engine_config_php_macro_engine_config_php_extensions_extensions_reader : public type_reader
        {
            auto_type_reader< extension_type_reader > _extension_reader;
        protected:
            macro_engine_config_php_macro_engine_config_php_extensions_extensions* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_php_extensions_extensions*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class macro_engine_config_php_macro_engine_config_php_extensions_reader : public type_reader
        {
            auto_type_reader< macro_engine_config_php_macro_engine_config_php_extensions_extensions_reader > _extensions_reader;
        protected:
            macro_engine_config_php_macro_engine_config_php_extensions* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_php_extensions*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class include_path_type_reader : public type_reader
        {
        protected:
            include_path_type* t() {
                return static_cast<include_path_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class macro_engine_config_php_macro_engine_config_php_files_include_paths_reader : public type_reader
        {
            auto_type_reader< include_path_type_reader > _include_path_reader;
        protected:
            macro_engine_config_php_macro_engine_config_php_files_include_paths* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_php_files_include_paths*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class macro_engine_config_php_macro_engine_config_php_files_reader : public type_reader
        {
            auto_type_reader< macro_engine_config_php_macro_engine_config_php_files_include_paths_reader > _include_paths_reader;
        protected:
            macro_engine_config_php_macro_engine_config_php_files* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_php_files*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class function_type_reader : public type_reader
        {
        protected:
            function_type* t() {
                return static_cast<function_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class macro_engine_config_php_macro_engine_config_functions_reader : public type_reader
        {
            auto_type_reader< function_type_reader > _function_reader;
        protected:
            macro_engine_config_php_macro_engine_config_functions* t() {
                return static_cast<macro_engine_config_php_macro_engine_config_functions*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_general_settings_reader : public type_reader
        {
        protected:
            CT_general_settings* t() {
                return static_cast<CT_general_settings*>( target() );
            }
            void end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
        };

        class macro_engine_config_php_macro_engine_config_reader : public type_reader
        {
            auto_type_reader< macro_engine_config_php_macro_engine_config_php_extensions_reader > _php_extensions_reader;
            auto_type_reader< macro_engine_config_php_macro_engine_config_php_files_reader > _php_files_reader;
            auto_type_reader< macro_engine_config_php_macro_engine_config_functions_reader > _functions_reader;
            auto_type_reader< CT_general_settings_reader > _general_settings_reader;
        protected:
            macro_engine_config_php_macro_engine_config* t() {
                return static_cast<macro_engine_config_php_macro_engine_config*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
        };

        class macro_engine_config_reader : public type_reader
        {
            auto_type_reader< macro_engine_config_php_macro_engine_config_reader > _php_macro_engine_config_reader;
        protected:
            macro_engine_config* t() {
                return static_cast<macro_engine_config*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

    }
}
#endif

