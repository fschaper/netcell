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

#include <fstream>
#include <stdexcept>

#include "zstream.hpp"

namespace xlsx
{
    namespace package
    {

        //output stream buffer

        ozipstreambuff::ozipstreambuff( zipFile zf ) : zf( zf ) {};
        ozipstreambuff::int_type ozipstreambuff::xsputc ( char_type c )
        {
            zipWriteInFileInZip( zf, &c, sizeof( char_type ) );
            return c;
        }

        std::streamsize ozipstreambuff::xsputn ( const char_type* c, std::streamsize count )
        {
            int err = zipWriteInFileInZip( zf, c, sizeof( char_type ) * count );
            if ( err < 0 ) {
                throw std::runtime_error( "Zip file write error!" );
            }
            return count;
        }

        ozipstreambuff::int_type ozipstreambuff::overflow( int_type c )
        {
            if ( traits_type::eq_int_type( traits_type::eof(), c ) ) {
                return ( traits_type::not_eof( c ) );    // EOF, return success code
            }
            zipWriteInFileInZip( zf, &c, sizeof( char_type ) );
            return c;
        }

        //input stream buffer

        izipstreambuff::izipstreambuff( unzFile zf ) : zf( zf ) {}

        std::streamsize izipstreambuff::xsgetn( char_type* buff, std::streamsize count )
        {
            int err = unzReadCurrentFile( zf, buff, sizeof( char_type ) * count );
            if ( err < 0 ) {
                throw std::runtime_error( "Zip file read error!" );
            }
            return err;
        };

        izipstreambuff::int_type izipstreambuff::underflow ( )
        {
            char_type c;
            int err = unzReadCurrentFile( zf, &c, sizeof( char_type ) );
            if ( err < 0 ) {
                throw std::runtime_error( "Zip file read error!" );
            } else if ( err == 1 ) {
                return c;
            }
            return -1;
        }

        izipstreambuff::int_type izipstreambuff::uflow ( )
        {
            char_type c;
            int err = unzReadCurrentFile( zf, &c, sizeof( char_type ) );
            if ( err < 0 ) {
                throw std::runtime_error( "Zip file read error!" );
            } else if ( err == 1 ) {
                return c;
            }
            return -1;
        }

        //output stream
        oizfstream::oizfstream( zipFile zfile, const std::string& inzip_file_path ) : std::ostream( &buf ), zf( zfile ), buf( zfile )
        {
            zipOpenNewFileInZip( zf, inzip_file_path.c_str(), 0, 0, 0, 0, 0, 0, 0, Z_DEFAULT_COMPRESSION );
        };
        oizfstream::~oizfstream() { }
        void oizfstream::close()
        {
            if ( zf != 0 ) {
                zipCloseFileInZip( zf );
                zf = 0;
            }
        }

        //input stream
        iizfstream::iizfstream( zipFile zfile, const std::string& inzip_file_path, const std::string& password ) : std::istream( &buf ), zf( zfile ), buf( zfile )
        {
#ifdef WIN32
            int iCaseSensitivity = 0;
#else
            int iCaseSensitivity = 1;
#endif
            if ( unzLocateFile( zf, inzip_file_path.c_str(), iCaseSensitivity ) != UNZ_OK ) {
                throw std::runtime_error( ( "Could not locate file '" + inzip_file_path + "' inside zip archive!" ).c_str() );
            }

            if ( unzOpenCurrentFilePassword( zf, password.empty() ? 0 : password.c_str() ) != UNZ_OK ) {
                throw std::runtime_error( ( "Could not open file '" + inzip_file_path + "' inside zip archive!" ).c_str() );
            }
        };
        iizfstream::~iizfstream() { }
        void iizfstream::close()
        {
            if ( zf != 0 ) {
                unzCloseCurrentFile( zf );
                zf = 0;
            }
        }
    }
}
