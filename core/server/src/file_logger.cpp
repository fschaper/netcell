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
#include "wss/file_logger.hpp"

namespace logging
{
    file_logger::~file_logger()
    {
        if ( m_log_file.good() ) {
            pass_repetition_message();
            m_log_file.close();
        }
    }

    void file_logger::log_file( const boost::filesystem::path& filename )
    {
        m_log_file.open( filename.file_string().c_str(), std::ios::app );
    }

    file_logger::logger_name_type file_logger::name() const
    {
        return logger_name;
    }

    void file_logger::actual_log( log_level::level /*level*/, const std::string& message )
    {
        if ( m_log_file.good() ) {
            m_log_file << message << std::endl;
        }
    }

    void file_logger::target( const std::string& target )
    {
        log_file( target );
    }

    const char* file_logger::logger_name = "file";

    file_logger_creator::result_type file_logger_creator::create() const
    {
        return result_type( new file_logger() );
    }
}
