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

#include <iostream>
#include <string>
#include <memory>

namespace xlsx
{
    namespace package
    {

        class IPackage
        {
        public:
            virtual std::auto_ptr<std::istream> get_file( const std::string& local_file_path ) = 0;
            virtual ~IPackage() {}
        };

        class IOutPackage
        {
        public:
            virtual std::auto_ptr<std::ostream> get_file( const std::string& local_file_path ) = 0;
            virtual ~IOutPackage() {}
        };

        class FolderPackage : public IPackage
        {
            std::string path;
        public:
            FolderPackage( const std::string& path ) ;
            ~FolderPackage( void );

            std::auto_ptr<std::istream> get_file( const std::string& local_file_path );
        private:
            std::string replace_all( const std::string& s, const std::string& a, const std::string& b );
        };

        class ipackage
        {
            std::auto_ptr<std::istream> cs;
            std::string fn;
        public:
            std::istream& current();
            std::istream& get( const std::string& filename );
            const std::string& current_filename() const;
            void close_current();
            virtual ~ipackage();
            operator std::istream& () {
                return current();
            }
            virtual bool exists( const std::string& filename ) = 0;
            virtual std::streambuf& get_buf( std::istream& s ) = 0;
        private:
            virtual std::auto_ptr<std::istream> create_stream( const std::string& filename ) = 0;
            virtual void close_stream( std::auto_ptr<std::istream> s ) = 0;
        };

        class opackage
        {
            std::auto_ptr<std::ostream> cs;
            std::string fn;
        public:
            std::ostream& current();
            std::ostream& get( const std::string& filename );
            const std::string& current_filename() const;
            void close_current();
            virtual ~opackage();
        private:
            virtual std::auto_ptr<std::ostream> create_stream( const std::string& filename ) = 0;
            virtual void close_stream( std::auto_ptr<std::ostream> s ) = 0;
        };
    }

}
