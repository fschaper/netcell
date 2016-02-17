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

#ifndef XIO_XML_BINDING_TYPE_READER_H
#define XIO_XML_BINDING_TYPE_READER_H

#include <memory>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <boost/noncopyable.hpp>
#include "../schema/types.hpp"
#include "../../xercesc/types.hpp"


namespace xio { 
	namespace xml { 
		namespace binding {

			class driver;

			class type_reader {
			public:
				type_reader() : m_driver(0), m_target(0) { }
				virtual ~type_reader() {}	
			protected:
				virtual void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs) {}
				virtual void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname) {}
				virtual void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value) {}
				virtual void read_value(const xcs::xstring& val) {}
                binding::driver* driver() const { return m_driver; }
			private:
				friend class driver;
                void set_driver(binding::driver* d) { m_driver = d; }
			public:
				void* target() const { return m_target; }
				void set_target(void* target) { m_target = target; }
            private:
                binding::driver* m_driver;	
                void* m_target;
			};

			template<class reader_T>
			class auto_type_reader 
                : boost::noncopyable
            {
				std::auto_ptr< reader_T > m_reader;
			public:
				type_reader* get_reader(void* target) {
					if (m_reader.get() == 0) 
						m_reader.reset(new reader_T());
					m_reader->set_target(target);
					return m_reader.get();
				}
			};
		}
	}
}

#endif

