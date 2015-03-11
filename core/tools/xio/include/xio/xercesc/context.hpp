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

#ifndef XIO_XERCES_CONTEXT_H
#define XIO_XERCES_CONTEXT_H

#include "exception.hpp"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/TransService.hpp>

#include "istream.hpp"
#include <memory>

namespace xio {
	namespace xcs {

		class platform_auto_init_object {			
		public:
			platform_auto_init_object() {
				try {
					::xercesc::XMLPlatformUtils::Initialize();
				}
				catch (const ::xercesc::XMLException&) {
					throw xercesc_init_exception();
				}
			}
			~platform_auto_init_object() {
				::xercesc::XMLPlatformUtils::Terminate();
			}
		};		

		class context : platform_auto_init_object {
		private:
			class fatal_error_handler : public ::xercesc::ErrorHandler {
			friend class context;
			public:
			
				fatal_error_handler()
				{
					had_fatal_err = false;
					line_nr = 0;
				
					xercesc::XMLTransService::Codes failReason;
					utf8Transcoder = xercesc::XMLPlatformUtils::fgTransService->makeNewTranscoderFor("UTF-8", failReason,16*1024);
				}

				~fatal_error_handler()
				{
					delete utf8Transcoder;	
				}

				virtual void 	warning (const xercesc::SAXParseException &exc)
				{
				}
				virtual void 	error (const xercesc::SAXParseException &exc)
				{
				}
				virtual void 	fatalError (const xercesc::SAXParseException &exc)
				{
					had_fatal_err = true;

					const XMLCh* msg = exc.getMessage();

					XMLSize_t msg_len = ::xercesc::XMLString::stringLen(msg);

					XMLByte* converted = new XMLByte[msg_len*2+1];
					XMLSize_t chars_eaten = 0;

					for ( XMLSize_t i = 0; i < msg_len*2 + 1; ++i ) {
						converted[i]=0;
					}

					utf8Transcoder->transcodeTo( msg, msg_len, converted, msg_len*2+1, chars_eaten, ::xercesc::XMLTranscoder::UnRep_RepChar );

					last_error_msg = (char*)converted;
					line_nr = ( unsigned int )( exc.getLineNumber() );
				}
				virtual void 	resetErrors ()
				{
					had_fatal_err = false;
					last_error_msg.clear();
					line_nr = 0;
				}

				bool had_errors()
				{
					return had_fatal_err;
				}

			private:
				::xercesc::XMLTranscoder* utf8Transcoder;
				bool had_fatal_err;
				std::string last_error_msg;
				unsigned int line_nr;
			};
		public:
			context() : warn_on_fatal_error( false ){};
			bool warn_on_fatal_error;

			bool had_errors()
			{
				return err_handler.had_errors( );
			}

			void get_error_info( int& line_nr, std::string& error_msg )
			{
				line_nr = err_handler.line_nr;
				error_msg = err_handler.last_error_msg;
			}
		protected:
			fatal_error_handler err_handler;
			void parse_stream(std::istream& stream, ::xercesc::ContentHandler* handler) {		
				std::auto_ptr< ::xercesc::SAX2XMLReader> parser(::xercesc::XMLReaderFactory::createXMLReader());
				parser->setFeature(::xercesc::XMLUni::fgSAX2CoreValidation, true);
				parser->setFeature(::xercesc::XMLUni::fgSAX2CoreNameSpaces, true);   // optional

				parser->setContentHandler(handler);

				if ( warn_on_fatal_error ) {
					parser->setErrorHandler( &err_handler );
				}
				try {
					istream_input input(stream);
					parser->parse(input);
				}
				catch (const ::xercesc::XMLException& ) {
					throw xercesc_xml_exception();
				}
				catch (const ::xercesc::SAXParseException& ) {
					throw xercesc_sax_parse_exception();
				}
				catch (...) {
					throw xercesc_exception();
				}
			}


		};
	}
}

#endif

