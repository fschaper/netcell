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

#ifndef XIO_XERCESC_ISTREAM_H
#define XIO_XERCESC_ISTREAM_H

#include <istream>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>

namespace xio
{
	namespace xcs
	{
		class istream : public ::xercesc::BinInputStream
		{
			std::istream& _is;
		public :
			istream (std::istream& is) : _is (is) {}

			XMLFilePos curPos () const
			{
				return static_cast<XMLFilePos> (_is.tellg ());
			}

			XMLSize_t readBytes (XMLByte* const buf, const XMLSize_t size)
			{
				if (_is.eof ())
					return 0;

				std::ios_base::iostate old (_is.exceptions ());
				_is.exceptions (old & ~std::ios_base::failbit);

				_is.read (reinterpret_cast<char*> (buf),
					static_cast<std::streamsize> (size));

				if (_is.fail () && _is.eof ())
					_is.clear (_is.rdstate () & ~std::ios_base::failbit);

				_is.exceptions (old);
				
				if (!(_is.bad () || _is.fail ()))
					return static_cast<XMLSize_t> (_is.gcount ());
				else
					return 0;
			}

			const XMLCh* getContentType () const { return 0; }
		};


		class istream_input : public ::xercesc::InputSource
		{
		public :
			istream_input (std::istream& is) : _is (is) { }			
			::xercesc::BinInputStream* makeStream () const { return new istream (_is); }
		private :
			std::istream& _is;
		};
	}
}
  


#endif 
