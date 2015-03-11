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
 *  Doru Paraschiv <doru@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

#include <wss/server.hpp>
#include <wss/auto_fill.hpp>

#include "autofill_handler.hpp"

/*!
 * \brief
 * initialize the AUTO_FILL extension and hook into WSS.
 *
 * \param server
 * server instances.
 *
 * \param config_file
 * path and filename to the configuration file for this module.
 *
 * \returns
 * true if the extension could be initialized successfully otherwise
 * returns false.
 *
 * \throws std::exception
 * will throw an exception if the configuration file could not be parsed
 */
extern "C" bool initialize_extension( server& server, const std::string& config_file )
{
    try {
        auto_fill::instance().register_engine( auto_fill::shared_engine_type( new autofill_internal::autofill_handler( config_file ) ) );
        return true;
    } catch ( const std::runtime_error& ) {
        // TODO (fschaper) specialize the error here
    }

    return false;
}
