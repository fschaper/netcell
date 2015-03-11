/**
*  \file
*  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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
*  \Author
*
*  Vali Nitu <vali@yalos-solutions.com>
*/

#include "precompiled_header.hpp"
#include "auto_save_filesystem.hpp"


autosave_filesystem_iterator::autosave_filesystem_iterator( const bfs::path& path, const std::string& username, const std::string& session_id, const std::string& filename )
    : m_it( bfs::directory_iterator( path ) )
{
    m_test = "("
             + ( filename.empty() ? ".*\\.wss" : boost::replace_all_copy( filename, "+", "\\+" ) ) + ")\\.("
             + ( username.empty() ? ".*" : username )
             + ")\\.("
             + ( session_id.empty() ? ".*" : session_id )
             + ")\\.~(\\d+)$";

    while ( !match() ) {
        ++m_it;
    }
}

autosave_filesystem_iterator& autosave_filesystem_iterator::operator ++()
{
    ++m_it;
    while ( !match() ) {
        ++m_it;
    }
    return *this;
}

bool autosave_filesystem_iterator::match()
{
    if ( m_it == bfs::directory_iterator() ) {
        return true;
    }

    boost::regex reg( m_test, boost::match_perl );
    boost::smatch results;
    std::string s = m_it->leaf();
    bool success = boost::regex_match( s, results, reg );

    return success;
}

bfs::directory_iterator& autosave_filesystem_iterator::operator *()
{
    return m_it;
}

bool autosave_filesystem_iterator::operator ==( autosave_filesystem_iterator& it )
{
    return ( m_it == it.m_it );
}

bool autosave_filesystem_iterator::operator !=( autosave_filesystem_iterator& it )
{
    return !( *this  == it );
}

bool autosave_filesystem_iterator::end() const
{
    return bfs::directory_iterator() == m_it;
}

