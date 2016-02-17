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

#ifndef XIO_XML_BINDING_DRIVER_H
#define XIO_XML_BINDING_DRIVER_H


#include "context.hpp"
#include "type_reader.hpp"

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>


namespace xio { 
	namespace xml { 
		namespace binding {

			class context_type;

			class driver : public ::xercesc::DefaultHandler
			{
				struct reader_info {
					type_reader* reader;
					xcs::xstring terminator;
				};

				std::vector<reader_info> reader;

				binding::context_type* _context;

				bool catchCharData;
				std::vector<xcs::xstring> chars;

				void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs) 
				{
					if (reader.empty())
						throw std::exception();
					catchCharData = true;
					chars.clear();					
										
					reader.back().reader->start_element(uri, localname, qname, attrs);		
					//startElement can push new reader

					type_reader* r = reader.back().reader;
					for (XMLSize_t i = 0; i<attrs.getLength(); i++) 
						r->read_attribute(attrs.getURI(i), attrs.getLocalName(i), attrs.getQName(i), attrs.getValue(i));						
				}

				void endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname) {					
					if (localname == reader.back().terminator) {
						if (!chars.empty())
							reader.back().reader->read_value(get_characters());
						reader.pop_back();
					} else 
						reader.back().reader->end_element(uri, localname, qname);
					catchCharData = false;
				}

				void characters(const XMLCh* const chars, const XMLSize_t length) 
				{
					if (catchCharData) {
						//charData+=ucstring(chars, length);
						this->chars.push_back(xcs::xstring(chars, length));
					}
				}
			public:
				void push(const xcs::xstring& localName, type_reader* b) { 
					reader_info bi;
					bi.reader = b;
					bi.terminator = localName;		
					b->set_driver(this);
					reader.push_back(bi);
				}

				xcs::xstring get_characters() const { 
					if (chars.size()==1)
						return chars[0];					
					xcs::xstringstream ss;
					for (size_t i = 0; i<chars.size(); i++)
						ss<<chars[i];
					return ss.str();
				}

                binding::context_type* context() { return _context; }

				driver(binding::context_type* ctx, type_reader* doctype_reader) : _context(ctx) { push(xcs::xstring(), doctype_reader); }
			};
		}
	}
}

#endif

