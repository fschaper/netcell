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
*  Vali Nitu <vali@yalos-solutions.com>
*/

#include <boost/filesystem.hpp>
#include <string>
#include "wss/define.hpp"

namespace bfs = boost::filesystem;

/*!
 * \brief
 * autosave files iterator
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
class WSS_MODULE autosave_filesystem_iterator
{
public:
    autosave_filesystem_iterator( const bfs::path& path, const std::string& username = std::string( "" ), const std::string& session_id = std::string( "" ), const std::string& filename = std::string( "" ) );

    autosave_filesystem_iterator& operator ++();

    bool end() const;

    bfs::directory_iterator& operator *();

    bool operator ==( autosave_filesystem_iterator& it );

    bool operator !=( autosave_filesystem_iterator& it );


private:
    bool match();

private:
    bfs::directory_iterator     m_it;
    std::string                 m_test;
};


