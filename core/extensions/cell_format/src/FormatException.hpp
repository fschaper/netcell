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
 *  Marek Pikulski <marek.pikulski@jedox.com>
 */

#pragma once

// stl
#include <string>
#include <wss/wss_runtime_exception.hpp>
// wss

/*! \brief Base exception class.
*
*  \author Marek Pikulski <marek.pikulski@jedox.com>
*/
class FormatException
    : public wss_runtime_exception
{
public:
    FormatException( const std::string& msg ) : msg( msg ) {}
    //      Exception();
    //      virtual ~Exception() throw();

    /*! Returns the name of the exception class. */
    //      virtual std::string get_type() const = 0;

    //      virtual const char* what() const throw();

    /*! Returns a description of what happened. */
    //      virtual std::string get_message() const;

    /*! Returns an error code. */
    //      virtual int get_code() const = 0;


    virtual int error_code() const {
        return 0x003700;
    }
    virtual std::string haiku() const {
        return std::string( "" );
    }

protected:
    mutable std::string msg;
};
