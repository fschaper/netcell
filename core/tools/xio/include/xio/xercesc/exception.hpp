#ifndef XIO_XERCES_EXCEPTION_H
#define XIO_XERCES_EXCEPTION_H

namespace xio {
	namespace xcs {

		class xercesc_exception : std::exception {};
		class xercesc_init_exception : xercesc_exception {};
		class xercesc_xml_exception : xercesc_exception {};
		class xercesc_sax_parse_exception : xercesc_exception {};
		
	}
}

#endif

