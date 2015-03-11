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
 *  this program; if not, log to the Free Software Foundation, Inc., 59 Temple
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
 */

#ifndef XIO_XML_BINDING_CONTEXT_H
#define XIO_XML_BINDING_CONTEXT_H

#include <vector>

#include <xercesc/util/XMLBigInteger.hpp>
#include <xercesc/util/XMLDouble.hpp>
#include <xercesc/util/XMLFloat.hpp>

#include "driver.hpp"
#include "../../xml/schema/types.hpp"
#include "../../xercesc/context.hpp"
#include "../../xercesc/types.hpp"
#include "../../xercesc/utf8.hpp"

namespace xio { 
	namespace xml { 
		namespace binding {

			class context_type : public xcs::context {				
			public:
				context_type() {
					utf8 = new xcs::utf8_decoder();
				}
				~context_type() {
					delete utf8;
				}
				template<typename T> bool parse_string(const xcs::xstring& v, T& res) const {
					std::string s = utf8->decode(v.c_str(), v.length());
					return ::xio::xml::schema::simple_parser<T>::parse(s, res);					
				}

				template<typename T> xio::xcs::xstring serialize_to_string(const T& v) const {
					std::string s = ::xio::xml::schema::simple_serializer<T>::serialize(v);
					return utf8->encode( s );					
				}

				template<typename T> xio::xcs::xstring serialize(const T& v) const {
					return serialize_to_string<T>(v);				
				}

				template<typename T> bool parse_numeric(const xcs::xstring& v, T& res) const {
					res = (T) XERCES_CPP_NAMESPACE::XMLBigInteger(v.c_str()).intValue();
					return true;
				}

				template<typename T> bool parse(const xcs::xstring& v, T& res) const {
					return parse_string<T>(v, res);
				}
            private:
                mutable xcs::utf8_decoder* utf8;
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::Int >(const xcs::xstring& v, ::xio::xml::schema::Int& res) const {
				return parse_numeric(v, res);
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::UnsignedInt >(const xcs::xstring& v, ::xio::xml::schema::UnsignedInt& res) const {
				return parse_numeric(v, res); 
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::Long >(const xcs::xstring& v, ::xio::xml::schema::Long& res) const {
				return parse_numeric(v, res);
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::UnsignedLong >(const xcs::xstring& v, ::xio::xml::schema::UnsignedLong& res) const {
				return parse_numeric(v, res);
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::Double >(const xcs::xstring& v, ::xio::xml::schema::Double& res) const {
				res = XERCES_CPP_NAMESPACE::XMLDouble(v.c_str()).getValue();
				return true;
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::Float >(const xcs::xstring& v, ::xio::xml::schema::Float& res) const {
				res = (::xio::xml::schema::Float) XERCES_CPP_NAMESPACE::XMLFloat(v.c_str()).getValue();
				return true;
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::UnsignedByte >(const xcs::xstring& v, ::xio::xml::schema::UnsignedByte& res) const {
				::xio::xml::schema::UnsignedInt m;
				if (!parse_numeric(v, m))
					return false;
				res = (::xio::xml::schema::UnsignedByte)m; 
				return true; 

			};

			template<> inline bool context_type::parse< ::xio::xml::schema::Byte >(const xcs::xstring& v, ::xio::xml::schema::Byte& res) const {
				::xio::xml::schema::Int m;
				if (!parse_numeric(v, m))
					return false;
				res = (::xio::xml::schema::Byte) m; 
				return true; 
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::UnsignedShort >(const xcs::xstring& v, ::xio::xml::schema::UnsignedShort& res) const {
				return parse_numeric(v, res);
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::Short >(const xcs::xstring& v, ::xio::xml::schema::Short& res) const {
				return parse_numeric(v, res);
			};

			template<> inline bool context_type::parse< ::xio::xml::schema::DateTime >(const xcs::xstring& v, ::xio::xml::schema::DateTime& res) const {
				return false; 
			};
		}
	}
}

#endif
