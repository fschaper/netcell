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


// This file has been auto-generated. Don't change it by hand!

#ifndef DML_STYLESHEET_READERS_HPP
#define DML_STYLESHEET_READERS_HPP

#include "dml-stylesheet.hpp"
#include "dml-baseTypes_readers.hpp"
#include "dml-baseStylesheet_readers.hpp"
#include "dml-styleDefaults_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_ColorMapping_reader;
		class CT_ColorSchemeAndMapping_reader;
		class CT_ColorSchemeList_reader;
		class CT_OfficeStyleSheet_reader;
		class CT_BaseStylesOverride_reader;
		class CT_EmptyElement_reader;
		class dml_stylesheet_reader;
		class CT_ColorMappingOverride_reader;

		class CT_ColorMapping_reader : public type_reader
		{
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_ColorMapping* t() { return static_cast<CT_ColorMapping*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ColorSchemeAndMapping_reader : public type_reader
		{
			auto_type_reader< CT_ColorScheme_reader > _clrScheme_reader;
			auto_type_reader< CT_ColorMapping_reader > _clrMap_reader;
		protected:
			CT_ColorSchemeAndMapping* t() { return static_cast<CT_ColorSchemeAndMapping*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ColorSchemeList_reader : public type_reader
		{
			auto_type_reader< CT_ColorSchemeAndMapping_reader > _extraClrScheme_reader;
		protected:
			CT_ColorSchemeList* t() { return static_cast<CT_ColorSchemeList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_OfficeStyleSheet_reader : public type_reader
		{
			auto_type_reader< CT_BaseStyles_reader > _themeElements_reader;
			auto_type_reader< CT_ObjectStyleDefaults_reader > _objectDefaults_reader;
			auto_type_reader< CT_ColorSchemeList_reader > _extraClrSchemeLst_reader;
			auto_type_reader< CT_CustomColorList_reader > _custClrLst_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_OfficeStyleSheet* t() { return static_cast<CT_OfficeStyleSheet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_BaseStylesOverride_reader : public type_reader
		{
			auto_type_reader< CT_ColorScheme_reader > _clrScheme_reader;
			auto_type_reader< CT_FontScheme_reader > _fontScheme_reader;
			auto_type_reader< CT_StyleMatrix_reader > _fmtScheme_reader;
		protected:
			CT_BaseStylesOverride* t() { return static_cast<CT_BaseStylesOverride*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_EmptyElement_reader : public type_reader
		{
		protected:
			CT_EmptyElement* t() { return static_cast<CT_EmptyElement*>(target()); }
		};

		class dml_stylesheet_reader : public type_reader
		{
			auto_type_reader< CT_OfficeStyleSheet_reader > _theme_reader;
			auto_type_reader< CT_BaseStylesOverride_reader > _themeOverride_reader;
			auto_type_reader< CT_EmptyElement_reader > _themeManager_reader;
		protected:
			dml_stylesheet* t() { return static_cast<dml_stylesheet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ColorMappingOverride_reader : public type_reader
		{
			auto_type_reader< CT_EmptyElement_reader > _masterClrMapping_reader;
			auto_type_reader< CT_ColorMapping_reader > _overrideClrMapping_reader;
		protected:
			CT_ColorMappingOverride* t() { return static_cast<CT_ColorMappingOverride*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

