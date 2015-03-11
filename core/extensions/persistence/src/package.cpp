/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  Marko Stijak <marko.stijak@jedox.com>
 */

#include "package.hpp"

#include <fstream>
#include <sstream>

namespace xlsx
{
    namespace package
    {

        FolderPackage::FolderPackage( const std::string& fpath ) : path( fpath )
        {
            if ( path[path.length()-1] != '\\' ) {
                path.push_back( '\\' );
            }
        }

        FolderPackage::~FolderPackage( void ) {}

        std::auto_ptr<std::istream> FolderPackage::get_file( const std::string& local_file_path )
        {
            std::string p = replace_all( path + local_file_path, "/", "\\" );
            return std::auto_ptr<std::istream>( new std::ifstream( p.c_str() ) );
        }

        std::string FolderPackage::replace_all( const std::string& s, const std::string& a, const std::string& b )
        {
            std::string ss = s;
            size_t i;
            while ( ( i = ss.find( a ) ) != std::string::npos ) {
                ss = ss.replace( i, a.size(), b );
            }
            return ss;
        }

        //ipackage

        std::istream& ipackage::current()
        {
            return *cs;
        }
        std::istream& ipackage::get( const std::string& filename )
        {
            close_current();
            cs = create_stream( filename );
            fn = filename;
            return current();
        }
        const std::string& ipackage::current_filename() const
        {
            return fn;
        }
        void ipackage::close_current()
        {
            if ( cs.get() ) {
                close_stream( cs ); //auto_ptr argument will destroy pointer
                fn = std::string();
            }
        }
        ipackage::~ipackage() {}

        //opackage

        std::ostream& opackage::current()
        {
            return *cs;
        }
        std::ostream& opackage::get( const std::string& filename )
        {
            close_current();
            cs = create_stream( filename );
            fn = filename;
            return current();
        }
        const std::string& opackage::current_filename() const
        {
            return fn;
        }
        void opackage::close_current()
        {
            if ( cs.get() ) {
                close_stream( cs );
                fn = std::string();
            }
        }
        opackage::~opackage() {}
    }

}
