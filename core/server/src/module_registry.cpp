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
#include "wss/module_registry.hpp"
#include "wss/define.hpp"
#include "wss/server.hpp"
#include "core_logging.hpp"
#include "wss/extension_function_call_failed_exception.hpp"
#include "wss/extension_module_load_exception.hpp"
#include "extension_function_caller.hpp"
#include "extension.hpp"

module_registry::module_registry()
{}

void module_registry::register_extension( const boost::filesystem::path& module, const std::string& configuration )
{
    if ( std::find( m_module_list.begin(), m_module_list.end(), module.string() ) != m_module_list.end() ) {
        return;
    }

    LOG_CORE_DEBUG( "loading extension module '" << module << "'" );
    typedef boost::shared_ptr<i_module_loader> shared_module_loader_type;
    shared_module_loader_type loader;
    try {
#ifdef WIN32
        loader = boost::make_shared<win32_module_loader>( module );
#   ifndef STDCALL
#       define STDCALL __stdcall
#   endif
#elif LINUX
        loader = boost::make_shared<unix_module_loader>( module );
#   ifndef STDCALL
#       define STDCALL
#   endif
#else
#   error unknown loader required
#endif
    } catch ( const extension_module_load_exception& e ) {
        LOG_CORE_ERROR( "failed to load extension module '" << module << "'" );
        throw e;
    }

    typedef extension_function_caller < bool( server&, const std::string& ) > caller_type;
    caller_type c( loader );
    try {
        LOG_CORE_DEBUG( "initializing extension '" << module << "'" );
        if ( !c( "initialize_extension", server::instance(), configuration ) ) {
            throw extension_module_load_exception();
        }
    } catch ( const extension_function_call_failed_exception& e ) {
        LOG_CORE_ERROR( "failed to initialize extension module '" << module << "'" );
        throw e;
    }

    m_module_list.push_back( module.string() );
}

const module_registry::module_list_type& module_registry::modules() const
{
    return m_module_list;
}
