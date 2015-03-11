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

#ifndef XIO_XML_SCHEMA_TYPES_H
#define XIO_XML_SCHEMA_TYPES_H

#include "../../xercesc/types.hpp"
#include "../../util/hex.hpp"
#include <vector>

namespace xio {
	namespace xml {
		namespace schema {

			typedef char Byte;
			typedef short Short;
			typedef int Int;
			typedef long Long;
			typedef std::string String;
			typedef std::string NormalizedString;
			typedef bool Boolean;
			typedef double Double;
			typedef unsigned int PositiveInteger;
			
			typedef unsigned char UnsignedByte;
			typedef unsigned int UnsignedInt;
			typedef unsigned short UnsignedShort;
			typedef unsigned long UnsignedLong;
			typedef std::string Language;
			
			typedef std::string Token;
			class DateTime {};
			typedef float Float;
			typedef double Decimal;
			typedef long long Int64;
			typedef unsigned long long UnsignedInt64;

			template<typename base_T, int size>
			class binary { 
			protected:
				std::vector<base_T> m_data;
			public:
				binary() {}
				binary(const std::vector<base_T>& d) : m_data(d) {}
				binary(const base_T* a, size_t cnt) : m_data(a, a+cnt) {}
				binary(const String& str) { 
					m_data.resize(str.length()/2);
					for (size_t i = 0; i<m_data.size(); ++i)
						::xio::util::hex::read(str, 2*size*i, 2*size, m_data[i]);
				}
				std::vector<base_T>& data() { return m_data; }
				const std::vector<base_T>& data() const { return m_data; }

				String encode() const { 
					std::stringstream res;					
					for(size_t i = 0; i<m_data.size(); i++) 
						for (int j = 2*size-1; j>=0; j--)
							res<<::xio::util::hex::lit((int)((m_data[i] >> (j*4)) & 0xF));						
					return res.str();
				}

				String serialize() const { return encode(); }
			};

			class hex_binary : public binary<UnsignedByte, 1>{ 
				std::vector<UnsignedByte> _data;
			public:
				hex_binary() {}
				hex_binary(const std::vector<UnsignedByte>& d) : binary<UnsignedByte, 1>(d) {}
				hex_binary(const UnsignedByte* a, size_t cnt) : binary<UnsignedByte, 1>(a, cnt) {}
				hex_binary(const String& s) :  binary<UnsignedByte, 1>(s) {}
			};

            typedef hex_binary HexBinary;

			class base64_binary : public binary<UnsignedInt64, 8>{ 
			public:
				base64_binary() {}
				base64_binary(const String& s) :  binary<UnsignedInt64, 8>(s) {}
				base64_binary(const UnsignedInt64* a, size_t cnt) : binary<UnsignedInt64, 8>(a, cnt) {}
			};

            typedef base64_binary Base64Binary;

			class AnySimpleType {};
			class AnyAtomicType {};

			template<typename T>
			class simple_parser {
			public:
				static bool parse(const String& v, T& res) {
					res = v;
					return true;
				}
			};

			template<typename T>
			class simple_serializer
			{
			public:
				static String serialize(const T& t) {
					return t.serialize();
				}
			};

			template<typename T>
			class list_type  {
				mutable std::vector<T> _values;
				mutable bool parsed;
				String _raw;
			public:

				typedef T item_type;				
				typedef typename std::vector< T>::iterator iterator;
				typedef typename std::vector< T>::const_iterator const_iterator;

				list_type() : parsed(false) {}
				list_type(const String& v) : parsed(false), _raw(v) {}

				operator const std::vector<T>&() const { return get(); }

				const_iterator begin() const { return get().begin(); }
				iterator begin() { return get().begin(); }

				const_iterator end() const { return get().end(); }
				iterator end() { return get().end(); }

				size_t size() const { return get().size(); }
				bool empty() const { return get().empty(); }

				String serialize() const {
					std::stringstream ss;
					const std::vector<T>& v = get();
					for (size_t i = 0; i<v.size(); i++)
					{
						if (i>0)
							ss<<" ";
						ss<<simple_serializer<T>::serialize(v[i]);
					}
					return ss.str();
				}

				operator String() const { return serialize(); }

				bool operator == (const String& s) const { return serialize() == s; }
				bool operator != (const String& s) const { return serialize() != s; }


			private:
				void parse() const {
					simple_parser<list_type> :: parse( _raw, _values);
					parsed = true;
				}

				const std::vector<T>& get() const { 
					if (!parsed)
						parse();
					return _values;
				}
			};

			template<>
			class simple_serializer<String>
			{
			public:
				static String serialize(const String& t) {
					return t;
				}
			};

			template<>
			class simple_serializer<Int>
			{
			public:
				static String serialize(const Int& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};

			template<>
			class simple_serializer<UnsignedInt>
			{
			public:
				static String serialize(const UnsignedInt& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};

			template<>
			class simple_serializer<Long>
			{
			public:
				static String serialize(const Long& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};

			template<>
			class simple_serializer<UnsignedLong>
			{
			public:
				static String serialize(const UnsignedLong& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};

			template<>
			class simple_serializer<Short>
			{
			public:
				static String serialize(const Short& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};

			template<>
			class simple_serializer<UnsignedShort>
			{
			public:
				static String serialize(const UnsignedShort& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};

			template<>
			class simple_serializer<Byte>
			{
			public:
				static String serialize(const Byte& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};

			template<>
			class simple_serializer<UnsignedByte>
			{
			public:
				static String serialize(const UnsignedByte& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};

			template<>
			class simple_serializer<Double>
			{
			public:
				static String serialize(const Double& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};

			template<>
			class simple_serializer<Float>
			{
			public:
				static String serialize(const Float& t) {
					std::stringstream ss; 
					ss<<t;
					return ss.str();
				}
			};


			template<>
			class simple_serializer<Boolean>
			{
			public:
				static String serialize(const Boolean& t) {
					return t ? "true" : "false";
				}
			};

			template<>
			class simple_serializer<DateTime>
			{
			public:
				static String serialize(const DateTime& t) {
					throw std::exception();
				}
			};
			
			
			template<>
			class simple_parser<Int> {
			public:
				static bool parse(const String& v, Int& res) {
					std::stringstream ss(v);
					ss>>res;
					return true;
				}
			};

			template<>
			class simple_parser<UnsignedInt> {
			public:
				static bool parse(const String& v, UnsignedInt& res) {
					std::stringstream ss(v);
					ss>>res;
					return true;
				}
			};

			template<>
			class simple_parser<Long> {
			public:
				static bool parse(const String& v, Long& res) {
					std::stringstream ss(v);
					ss>>res;
					return true;
				}
			};

			template<>
			class simple_parser<UnsignedLong> {
			public:
				static bool parse(const String& v, Long& res) {
					std::stringstream ss(v);
					ss>>res;
					return true;
				}
			};


			template<>
			class simple_parser<Short> {
			public:
				static bool parse(const String& v, Short& res) {
					std::stringstream ss(v);
					ss>>res;
					return true;
				}
			};

			template<>
			class simple_parser<UnsignedShort> {
			public:
				static bool parse(const String& v, UnsignedShort& res) {
					std::stringstream ss(v);
					ss>>res;
					return true;
				}
			};

			template<>
			class simple_parser<Double> {
			public:
				static bool parse(const String& v, Double& res) {
					std::stringstream ss(v);
					ss>>res;
					return true;
				}
			};

			template<>
			class simple_parser<Float> {
			public:
				static bool parse(const String& v, Float& res) {
					std::stringstream ss(v);
					ss>>res;
					return true;
				}
			};

			template<>
			class simple_parser<Boolean> {
			public:
				static bool parse(const String& v, Boolean& res) {
					if (v=="0" || v=="false") {
						res = false;
						return true;
					}
					if (v=="1" || v=="true") {
						res = true;
						return true;
					}
					return false; 
				}
			};			

			template<>
			class simple_parser<UnsignedByte> {
			public:
				static bool parse(const String& v, UnsignedByte& res) {
					Int i;
					if (simple_parser<Int>::parse(v, i)) {
						res = i;
						return true;
					}
					return false;
				}
			};

			template<>
			class simple_parser<Byte> {
			public:
				static bool parse(const String& v, Byte& res) {
					Int i;
					if (simple_parser<Int>::parse(v, i)) {
						res = i;
						return true;
					}
					return false;
				}
			};

			template<>
			class simple_parser<String> {
			public:
				static bool parse(const String& v, String& res) {
					res = v;
					return true;
				}
			};			

			template<typename T>
			class simple_parser<list_type<T> > {
			public:
				static bool parse(const String& v, std::vector<T>& res) {					
					size_t p2;
					size_t p1 = 0;
					typename list_type<T>::item_type i;
					bool ok = true;
					do {
						p2 = v.find_first_of(' ', p1);
						if (p2!=String::npos) {
							if (p2>p1) {
								ok = ok && simple_parser<typename list_type<T>::item_type>::parse(v.substr(p1, p2-p1), i);								
								res.push_back(i);
							}
						} else {
							if (p1<v.size()) {
								ok = ok && simple_parser<typename list_type<T>::item_type>::parse(v.substr(p1), i);																
								res.push_back(i);
							}
						}
						p1 = p2+1;
					} while (p1!=0);					
					return ok;
				}
			};


			//simple_types

			template<typename T>
			class simple_type : AnySimpleType { 
				T _value;
			public:				

				typedef T native_type;

				simple_type() {}
				simple_type(const T& v) : _value(v) {}
				simple_type(const simple_type& v) : _value(v._value) {}				

				T& operator = (const T& val) { _value = val; return _value; }
				operator T&() { return _value; }
				operator const T&() const { return _value; }

				void set(const T& v) { _value = v; }
				const T& get() const { return _value; }

				void read(const String& str) { simple_parser<T>::parse(str, _value); }
				String serialize() const { return simple_serializer<T>::serialize(_value); }

				bool operator == (const T& v) const { return _value == v; };
				bool operator != (const T& v) const { return _value != v; };

				bool operator == (const String& s) const { return serialize() == s; };
				bool operator != (const String& s) const { return serialize() != s; };
			};

			template<>
			class simple_type<String> : AnySimpleType { 
				String _value;
			public:				

				typedef String native_type;

				simple_type() {}
				simple_type(const String& v) : _value(v) {}
				simple_type(const simple_type& v) : _value(v._value) {}				

				String& operator = (const String& val) { _value = val; return _value; }
				operator String&() { return _value; }
				operator const String&() const { return _value; }

				void set(const String& v) { _value = v; }
				const String& get() const { return _value; }

				bool operator == (const String& s) const { return _value == s; }
				bool operator != (const String& s) const { return _value != s; }

				String serialize() const { return _value; }
			};



		}
	}
}

#endif

