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

#include <stdexcept>
#include "zstream.hpp"
#include "zpackage.hpp"


namespace xlsx
{
    namespace package
    {

        //class izpackage
        izpackage::izpackage() : uf( 0 ) {};
        izpackage::izpackage( const std::string& f ) : uf( 0 )
        {
            open( f, "" );
        };
        izpackage::izpackage( const std::string& f, const std::string& pass ) : uf( 0 )
        {
            open( f, pass );
        };

        void izpackage::open( const std::string& f, const std::string& pass )
        {
            close();
            uf = unzOpen( f.c_str() );
            if ( uf == NULL ) {
                throw std::runtime_error( "Could not open zip archive!" );
            }
            filename = f;
            password = pass;
        }
        bool izpackage::open() const
        {
            return uf != NULL;
        }
        void izpackage::close()
        {
            if ( uf ) {
                close_current();
                unzClose( uf );
                uf = 0;
            }
        }

        bool izpackage::exists( const std::string& filename )
        {
#ifdef WIN32
            int iCaseSensitivity = 0;
#else
            int iCaseSensitivity = 1;
#endif
            if ( unzLocateFile( uf, filename.c_str(), iCaseSensitivity ) != UNZ_OK ) {
                return false;
            }
            if ( unzOpenCurrentFilePassword( uf, password.empty() ? 0 : password.c_str() ) != UNZ_OK ) {
                return false;
            }
            return true;
        }

        izpackage::~izpackage()
        {
            close();
        }

        std::streambuf& izpackage::get_buf( std::istream& s )
        {
            return static_cast< iizfstream& >( s ).get_buf();
        }

        std::auto_ptr<std::istream> izpackage::create_stream( const std::string& filename )
        {
            return std::auto_ptr<std::istream>( new iizfstream( uf, filename, password ) );
        }

        void izpackage::close_stream( std::auto_ptr<std::istream> s )
        {
            iizfstream* zs = ( iizfstream* )s.get();
            zs->close();
        }


        //class ozpackage

        ozpackage::ozpackage() : zf( 0 ) {};
        ozpackage::ozpackage( const std::string& f ) : zf( 0 )
        {
            open( f, "" );
        };
        ozpackage::ozpackage( const std::string& f, const std::string& pass ) : zf( 0 )
        {
            open( f, pass );
        };

        void ozpackage::open( const std::string& f, const std::string& pass )
        {
            close();
            zf = zipOpen( f.c_str(), APPEND_STATUS_CREATE );
            if ( zf == NULL ) {
                throw std::runtime_error( "Could not open zip archive!" );
            }
            filename = f;
            password = pass;
        }
        bool ozpackage::open() const
        {
            return zf != NULL;
        }
        void ozpackage::close()
        {
            if ( zf ) {
                close_current();
                zipClose( zf, 0 );
                zf = 0;
            }
        }


        ozpackage::~ozpackage()
        {
            close();
        }

        std::auto_ptr<std::ostream> ozpackage::create_stream( const std::string& filename )
        {
            return std::auto_ptr<std::ostream>( new oizfstream( zf, filename ) );
        }

        void ozpackage::close_stream( std::auto_ptr<std::ostream> s )
        {
            oizfstream* zs = ( oizfstream* )s.get();
            zs->close();
        }
    }
}
