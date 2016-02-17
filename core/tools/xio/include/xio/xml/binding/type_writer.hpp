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

#ifndef XIO_XML_BINDING_TYPE_WRITER_H
#define XIO_XML_BINDING_TYPE_WRITER_H

#include "context.hpp"
#include "../../xercesc/writer.hpp"


namespace xio { 
	namespace xml { 
		namespace binding {
			
			class type_writer {
			public:
				type_writer() : m_target(0), m_context(0) { }
				virtual ~type_writer() {}	
			public:
				virtual void write_target_to(::xio::xcs::xml_writer& w) = 0;				
			public:
				void set_context(context_type* context) { m_context = context; }
                        binding::context_type* context() { return m_context; }
			public:
				void* target() const { return m_target; }
				void set_target(void* target) { m_target = target; }
            private:
                void* m_target;
                binding::context_type* m_context;					
			};

			template<class writer_T>
			class auto_type_writer {
			public:
				type_writer* get_writer(binding::context_type* context, void* target) {
					if (m_writer.get() == 0) 
						m_writer.reset(new writer_T());
					m_writer->set_context(context);
					m_writer->set_target(target);
					return m_writer.get();
				}
            private:
                std::auto_ptr<writer_T> m_writer;
			};
		}
	}
}

#endif
