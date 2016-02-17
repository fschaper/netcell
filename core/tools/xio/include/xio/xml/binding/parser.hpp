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

#ifndef XIO_XML_BINDING_PARSER_H
#define XIO_XML_BINDING_PARSER_H

#include "driver.hpp"
#include <fstream>

namespace xio { 
	namespace xml { 
		namespace binding {

			class parser : public context_type {
			private:
				template<typename doc_T, typename reader_T>
				void parse_doc( std::istream& stream, doc_T& doc) {
					reader_T doc_reader;
					doc_reader.set_target(&doc);
					driver driver(this, &doc_reader);
					parse_stream(stream, &driver);
				}				
			public:
				template<typename doc_T>
				void parse_doc(std::istream& stream, doc_T& doc) {
					throw std::exception("parser::parse_doc function not specialized for given document type!");
				}

				template<typename doc_T>
				void parse_doc(const char* path, doc_T& doc) {
					std::ifstream fs(path);
					parse_doc(fs, doc);
				}
			};
		}
	}
}

#endif

