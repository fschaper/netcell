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

#ifndef XIO_XERCES_UTF8_H
#define XIO_XERCES_UTF8_H

#include "types.hpp"
#include <xercesc/util/TransService.hpp>
#include <boost/scoped_array.hpp>

namespace xio {
	namespace xcs {

		class utf8_decoder {
		private:
			std::string xml_decode( const std::string& src ) {
				std::string buf = src;
				std::string decoded;
				std::string::size_type offset = 0;

				while ( std::string::npos != ( offset = buf.find( "_x00" ) ) ) {
					decoded += buf.substr( 0, offset );
					std ::string test = buf.substr( offset, 7 );
					if ( "_x0000_" == test ){
						decoded += (char)0;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0001_" == test ){
						decoded += (char)1;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0002_" == test ){
						decoded += (char)2;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0003_" == test ){
						decoded += (char)3;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0004_" == test ){
						decoded += (char)4;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0005_" == test ){
						decoded += (char)5;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0006_" == test ){
						decoded += (char)6;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0007_" == test ){
						decoded += (char)7;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0008_" == test ){
						decoded += (char)8;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0009_" == test ){
						decoded += (char)9;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x000A_" == test ){
						decoded += (char)10;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x000B_" == test ){
						decoded += (char)11;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x000C_" == test ){
						decoded += (char)12;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x000D_" == test ){
						decoded += (char)13;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x000E_" == test ){
						decoded += (char)14;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x000F_" == test ){
						decoded += (char)15;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0010_" == test ){
						decoded += (char)16;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0011_" == test ){
						decoded += (char)17;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0012_" == test ){
						decoded += (char)18;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0013_" == test ){
						decoded += (char)19;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0014_" == test ){
						decoded += (char)20;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0015_" == test ){
						decoded += (char)21;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0016_" == test ){
						decoded += (char)22;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0017_" == test ){
						decoded += (char)23;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0018_" == test ){
						decoded += (char)24;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x0019_" == test ){
						decoded += (char)25;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x001A_" == test ){
						decoded += (char)26;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x001B_" == test ){
						decoded += (char)27;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x001C_" == test ){
						decoded += (char)28;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x001D_" == test ){
						decoded += (char)29;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x001E_" == test ){
						decoded += (char)30;
						buf = buf.substr( offset + 7, buf.size() );
					} else if ( "_x001F_" == test ){
						decoded += (char)31;
						buf = buf.substr( offset + 7, buf.size() );
					} else {
						decoded += "_x00";
						buf = buf.substr( offset + 4, buf.size() );
					}					
				}
				decoded += buf;
				return decoded;
			}

			std::string xml_encode( const std::string& src, size_t first ){
				std::string encoded;
				for ( size_t i = 0; i < src.size(); i++ ){
					if ( i < first ){
						encoded += src[i];
					} else {
						switch ( src[i] ){
							case 0: encoded += "_x0000_"; break;
							case 1: encoded += "_x0001_"; break;
							case 2: encoded += "_x0002_"; break;
							case 3: encoded += "_x0003_"; break;
							case 4: encoded += "_x0004_"; break;
							case 5: encoded += "_x0005_"; break;
							case 6: encoded += "_x0006_"; break;
							case 7: encoded += "_x0007_"; break;
							case 8: encoded += "_x0008_"; break;
							case 9: encoded += "_x0009_"; break;
							case 10: encoded += "_x000A_"; break;
							case 11: encoded += "_x000B_"; break;
							case 12: encoded += "_x000C_"; break;
							case 13: encoded += "_x000D_"; break;
							case 14: encoded += "_x000E_"; break;
							case 15: encoded += "_x000F_"; break;
							case 16: encoded += "_x0010_"; break;
							case 17: encoded += "_x0011_"; break;
							case 18: encoded += "_x0012_"; break;
							case 19: encoded += "_x0013_"; break;
							case 20: encoded += "_x0014_"; break;
							case 21: encoded += "_x0015_"; break;
							case 22: encoded += "_x0016_"; break;
							case 23: encoded += "_x0017_"; break;
							case 24: encoded += "_x0018_"; break;
							case 25: encoded += "_x0019_"; break;
							case 26: encoded += "_x001A_"; break;
							case 27: encoded += "_x001B_"; break;
							case 28: encoded += "_x001C_"; break;
							case 29: encoded += "_x001D_"; break;
							case 30: encoded += "_x001E_"; break;
							case 31: encoded += "_x001F_"; break;
							default: encoded += src[i]; break;
						}
					}
				}

				return encoded;
			}
		public:
			std::string decode(const XMLCh* c, const XMLSize_t length) {
				if ( 0 == length )  return std::string();
				std::string result = std::string( (char*)::xercesc::TranscodeToStr( c, length + 1, "UTF-8").str() );
				if ( std::string::npos == result.find_first_of( "_x00" )  ) return result;

				return xml_decode( result );
			};

			xstring encode(const std::string& utf8) {
				if ( 0 == utf8.length() ) return xstring();
				for ( size_t i = 0; i < utf8.size(); i++ ){
					if ( utf8[i] < 32 ){
						std::string xml_encoded = xml_encode( utf8, i );
						return xstring( ::xercesc::TranscodeFromStr( ( XMLByte *) xml_encoded.c_str(), xml_encoded.size() + 1, "UTF-8" ).str() ); 
					}
				}
				return xstring( ::xercesc::TranscodeFromStr( ( XMLByte *) utf8.c_str(), utf8.size() + 1, "UTF-8" ).str() ); 
			}
		};

	}
}

#endif

