/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 */

#ifndef XIO_XERCESC_OSTREAM_H
#define XIO_XERCESC_OSTREAM_H

#include <ostream>
#include "utf8.hpp"
#include <xercesc/framework/XMLFormatter.hpp>


namespace xio
{
	namespace xcs
	{
		class ostream : public ::xercesc::XMLFormatTarget
		{
			std::ostream& _os;			
		public :
			ostream (std::ostream& is) : _os (is) {}

			void writeChars(const XMLByte* const toWrite, const XMLSize_t count, ::xercesc::XMLFormatter* const formatter)
			{
				_os.write((char*)toWrite, (std::streamsize)count);
			}
			void flush() { _os.flush(); };
		};
	}
}
  


#endif 
