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

#ifndef PERSISTENCE_CONFIG_READERS_HPP
#define PERSISTENCE_CONFIG_READERS_HPP

#include "persistence_config.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace persistence_cfg
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class CT_patern_fill_reader;
        class CT_patern_fills_reader;
        class CT_persistence_config_reader;
        class persistence_config_reader;

        class CT_patern_fill_reader : public type_reader
        {
        protected:
            CT_patern_fill* t() {
                return static_cast<CT_patern_fill*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_patern_fills_reader : public type_reader
        {
            auto_type_reader< CT_patern_fill_reader > _pattern_fill_reader;
        protected:
            CT_patern_fills* t() {
                return static_cast<CT_patern_fills*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_persistence_config_reader : public type_reader
        {
            auto_type_reader< CT_patern_fills_reader > _pattern_fills_reader;
        protected:
            CT_persistence_config* t() {
                return static_cast<CT_persistence_config*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class persistence_config_reader : public type_reader
        {
            auto_type_reader< CT_persistence_config_reader > _persistence_settings_reader;
        protected:
            persistence_config* t() {
                return static_cast<persistence_config*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

    }
}
#endif

