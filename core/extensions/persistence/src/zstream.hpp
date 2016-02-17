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
#pragma once

#include "package.hpp"
#include <minizip/unzip.h>
#include <minizip/zip.h>

namespace xlsx
{
    namespace package
    {

        class ozipstreambuff : public std::streambuf
        {
            zipFile zf;
        public:
            ozipstreambuff( zipFile zf );
        private:
            int_type xsputc ( char_type c );
            std::streamsize xsputn ( const char_type* c, std::streamsize count );
            int_type overflow( int_type c );
        };

        class izipstreambuff : public std::streambuf
        {
            unzFile zf;

        public:
            izipstreambuff( unzFile zf );

        private:
            int_type xsgetc();
            std::streamsize xsgetn( char_type* buff, std::streamsize count );
            int_type underflow();
            int_type uflow();
        };

        class oizfstream : public std::ostream
        {
            zipFile zf;
            ozipstreambuff buf;
        public:
            oizfstream( zipFile zfile, const std::string& inzip_file_path );
            ~oizfstream();
            void close();
        };

        class iizfstream : public std::istream
        {
            unzFile zf;
            izipstreambuff buf;
        public:
            iizfstream( unzFile zfile, const std::string& inzip_file_path, const std::string& password );
            ~iizfstream();
            std::streambuf& get_buf() {
                return buf;
            }
            void close();
        };
    }
}
