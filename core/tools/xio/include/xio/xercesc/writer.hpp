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

#ifndef XIO_XERCES_WRITER_H
#define XIO_XERCES_WRITER_H


#include "types.hpp"
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/XMLChar.hpp>

namespace xio {
	namespace xcs {
		namespace sc {
			using namespace ::xercesc;
			 
			// default end-of-line sequence
			static const XMLCh  gEOLSeq[] =
			{
				chLF, chNull
			};

			//UTF-8
			static const XMLCh  gUTF8[] =
			{
				chLatin_U, chLatin_T, chLatin_F, chDash, chDigit_8, chNull
			};

			//</
			static const XMLCh  gEndElement[] =
			{
				chOpenAngle, chForwardSlash, chNull
			};

			//?>
			static const XMLCh  gEndPI[] =
			{
				chQuestion, chCloseAngle, chNull
			};

			//<?
			static const XMLCh  gStartPI[] =
			{
				chOpenAngle, chQuestion, chNull
			};

			//<?xml version="
			static const XMLCh  gXMLDecl_VersionInfo[] =
			{
				chOpenAngle, chQuestion, chLatin_x,     chLatin_m,  chLatin_l,  chSpace,
				chLatin_v,   chLatin_e,  chLatin_r,     chLatin_s,  chLatin_i,  chLatin_o,
				chLatin_n,   chEqual,    chDoubleQuote, chNull
			};

			static const XMLCh gXMLDecl_ver10[] =
			{
				chDigit_1, chPeriod, chDigit_0, chNull
			};

			//encoding="
			static const XMLCh  gXMLDecl_EncodingDecl[] =
			{
				chLatin_e,  chLatin_n,  chLatin_c,  chLatin_o,      chLatin_d, chLatin_i,
				chLatin_n,  chLatin_g,  chEqual,    chDoubleQuote,  chNull
			};

			//" standalone="
			static const XMLCh  gXMLDecl_SDDecl[] =
			{
				chLatin_s, chLatin_t, chLatin_a,   chLatin_n,    chLatin_d,   chLatin_a,
				chLatin_l, chLatin_o, chLatin_n,   chLatin_e,    chEqual,     chDoubleQuote,
				chNull
			};

			//"
			static const XMLCh  gXMLDecl_separator[] =
			{
				chDoubleQuote, chSpace, chNull
			};

			//?>
			static const XMLCh  gXMLDecl_endtag[] =
			{
				chQuestion, chCloseAngle,  chNull
			};

			//<![CDATA[
			static const XMLCh  gStartCDATA[] =
			{
				chOpenAngle, chBang,    chOpenSquare, chLatin_C, chLatin_D,
				chLatin_A,   chLatin_T, chLatin_A,    chOpenSquare, chNull
			};

			//]]>
			static const XMLCh  gEndCDATA[] =
			{
			//    chCloseSquare, chCloseAngle, chCloseAngle, chNull  // test only: ]>>
				  chCloseSquare, chCloseSquare, chCloseAngle, chNull
			};

			//<!--
			static const XMLCh  gStartComment[] =
			{
				chOpenAngle, chBang, chDash, chDash, chNull
			};

			//-->
			static const XMLCh  gEndComment[] =
			{
				chDash, chDash, chCloseAngle, chNull
			};

			//<!DOCTYPE
			static const XMLCh  gStartDoctype[] =
			{
				chOpenAngle, chBang,    chLatin_D, chLatin_O, chLatin_C, chLatin_T,
				chLatin_Y,   chLatin_P, chLatin_E, chSpace,   chNull
			};

			//PUBLIC "
			static const XMLCh  gPublic[] =
			{
				chLatin_P, chLatin_U, chLatin_B,     chLatin_L, chLatin_I,
				chLatin_C, chSpace,   chDoubleQuote, chNull
			};

			//SYSTEM "
			static const XMLCh  gSystem[] =
			{
				chLatin_S, chLatin_Y, chLatin_S,     chLatin_T, chLatin_E,
				chLatin_M, chSpace,   chDoubleQuote, chNull
			};

			//<!ENTITY
			static const XMLCh  gStartEntity[] =
			{
				chOpenAngle, chBang,    chLatin_E, chLatin_N, chLatin_T, chLatin_I,
				chLatin_T,   chLatin_Y, chSpace,   chNull
			};

			//NDATA "
			static const XMLCh  gNotation[] =
			{
				chLatin_N, chLatin_D,     chLatin_A, chLatin_T, chLatin_A,
				chSpace,   chDoubleQuote, chNull
			};

			static const XMLByte  BOM_utf8[]    = {(XMLByte)0xEF, (XMLByte)0xBB, (XMLByte)0xBF, (XMLByte) 0};
			static const XMLByte  BOM_utf16be[] = {(XMLByte)0xFE, (XMLByte)0xFF, (XMLByte) 0};
			static const XMLByte  BOM_utf16le[] = {(XMLByte)0xFF, (XMLByte)0xFE, (XMLByte) 0};
			static const XMLByte  BOM_ucs4be[]  = {(XMLByte)0x00, (XMLByte)0x00, (XMLByte)0xFE, (XMLByte)0xFF, (XMLByte) 0};
			static const XMLByte  BOM_ucs4le[]  = {(XMLByte)0xFF, (XMLByte)0xFE, (XMLByte)0x00, (XMLByte)0x00, (XMLByte) 0};
		}


		class xml_writer { 
			::xercesc::XMLFormatTarget* target;
			::xercesc::XMLFormatter* formatter;

			bool currentElementIsEmpty;
			bool startElementIsOpen;

		public:
			xml_writer(::xercesc::XMLFormatTarget* t) : target(t) {
				formatter = new ::xercesc::XMLFormatter(sc::gUTF8, sc::gXMLDecl_ver10, target);
				startElementIsOpen = false;
			}

			~xml_writer() { 
				delete formatter;
			}

			xml_writer& start_element(const XMLCh* const prefix, const XMLCh* const name) {
				check_start_element_open();
				*formatter << ::xercesc::XMLFormatter::NoEscapes;
				*formatter << ::xercesc::chOpenAngle;
				write_prefix_name(prefix, name);
				currentElementIsEmpty = true;
				startElementIsOpen = true;
				return *this;
			}

			xml_writer& end_element(const XMLCh* const prefix, const XMLCh* const name) {
				if (startElementIsOpen) {					
					*formatter << ::xercesc::XMLFormatter::NoEscapes;
					*formatter << ::xercesc::chForwardSlash;
					*formatter << ::xercesc::chCloseAngle;					
				} else {
					*formatter << ::xercesc::XMLFormatter::NoEscapes;					
					*formatter << ::xercesc::chOpenAngle;
					*formatter << ::xercesc::chForwardSlash;
					write_prefix_name(prefix, name);
					*formatter << ::xercesc::chCloseAngle;
				}		
				startElementIsOpen = false;
				return *this;
			}

			xml_writer& start_attribute(const XMLCh* const prefix, const XMLCh* const name) {
				write_space();
			    write_prefix_name(prefix, name);
				return *this;
			}

			xml_writer& end_attribute(const XMLCh* const value) {
				*formatter << ::xercesc::XMLFormatter::NoEscapes;
				*formatter << ::xercesc::chEqual;
				*formatter << ::xercesc::chDoubleQuote;
				*formatter << ::xercesc::XMLFormatter::AttrEscapes;
				*formatter << value;
				*formatter << ::xercesc::XMLFormatter::NoEscapes;
				*formatter << ::xercesc::chDoubleQuote;
				return *this;
			}

			xml_writer& end_attribute(const xstring& value) {
				return end_attribute(value.c_str());
			}

			xml_writer& attribute(const XMLCh* prefix, const XMLCh* name, const XMLCh* const value) {
				start_attribute(prefix, name);
				end_attribute(value);
				return *this;
			}

			xml_writer& attribute(const XMLCh* prefix, const XMLCh* name, const xstring& value) {
				return attribute(prefix, name, value.c_str());
			}

			xml_writer& write_xml_declaration() {
				*formatter << ::xercesc::XMLFormatter::NoEscapes;
				*formatter << sc::gXMLDecl_VersionInfo << sc::gXMLDecl_ver10 << sc::gXMLDecl_separator;
                *formatter << sc::gXMLDecl_EncodingDecl << sc::gUTF8 << sc::gXMLDecl_separator;
				const XMLCh* st = true ? ::xercesc::XMLUni::fgYesString : ::xercesc::XMLUni::fgNoString;
				*formatter << sc::gXMLDecl_SDDecl << st << sc::gXMLDecl_separator;
                *formatter << sc::gXMLDecl_endtag;
				return *this;
			}

			xml_writer& write_utf8_bom() {
				formatter->writeBOM(sc::BOM_utf8, 3);
				return *this;
			}

			xml_writer& write_element_value(const XMLCh* const value) {
				check_start_element_open();
				*formatter << ::xercesc::XMLFormatter::StdEscapes;
				*formatter << value;			
				return *this;
			}

			xml_writer& write_element_value(const xstring& value) {
				return write_element_value(value.c_str());
			}

		protected:
			void check_start_element_open() {
				if (startElementIsOpen) {
					*formatter << ::xercesc::chCloseAngle;
					startElementIsOpen = false;
				}
			}

			void write_prefix_name(const XMLCh* prefix, const XMLCh* name) {
				if (prefix!=NULL)
					*formatter << prefix << ::xercesc::chColon;
				*formatter << name;
			}

			void write_space() {
				*formatter << ::xercesc::chSpace;
			}


		private:
			
		};

	}
}

#endif
