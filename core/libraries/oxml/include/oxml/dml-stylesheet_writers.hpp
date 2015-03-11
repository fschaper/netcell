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

#ifndef DML_STYLESHEET_WRITERS_HPP
#define DML_STYLESHEET_WRITERS_HPP

#include "dml-stylesheet.hpp"
#include "dml-stylesheet_literals.hpp"
#include "dml-baseTypes_writers.hpp"
#include "dml-baseStylesheet_writers.hpp"
#include "dml-styleDefaults_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_ColorMapping_writer;
		class CT_ColorSchemeAndMapping_writer;
		class CT_ColorSchemeList_writer;
		class CT_OfficeStyleSheet_writer;
		class CT_BaseStylesOverride_writer;
		class CT_EmptyElement_writer;
		class dml_stylesheet_writer;
		class CT_ColorMappingOverride_writer;

		class CT_ColorMapping_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_ColorMapping* t() { return static_cast<CT_ColorMapping*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColorSchemeAndMapping_writer : public type_writer
		{
			auto_type_writer< CT_ColorScheme_writer > _clrScheme_writer;
			auto_type_writer< CT_ColorMapping_writer > _clrMap_writer;
			CT_ColorSchemeAndMapping* t() { return static_cast<CT_ColorSchemeAndMapping*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColorSchemeList_writer : public type_writer
		{
			auto_type_writer< CT_ColorSchemeAndMapping_writer > _extraClrScheme_writer;
			CT_ColorSchemeList* t() { return static_cast<CT_ColorSchemeList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OfficeStyleSheet_writer : public type_writer
		{
			auto_type_writer< CT_BaseStyles_writer > _themeElements_writer;
			auto_type_writer< CT_ObjectStyleDefaults_writer > _objectDefaults_writer;
			auto_type_writer< CT_ColorSchemeList_writer > _extraClrSchemeLst_writer;
			auto_type_writer< CT_CustomColorList_writer > _custClrLst_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_OfficeStyleSheet* t() { return static_cast<CT_OfficeStyleSheet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BaseStylesOverride_writer : public type_writer
		{
			auto_type_writer< CT_ColorScheme_writer > _clrScheme_writer;
			auto_type_writer< CT_FontScheme_writer > _fontScheme_writer;
			auto_type_writer< CT_StyleMatrix_writer > _fmtScheme_writer;
			CT_BaseStylesOverride* t() { return static_cast<CT_BaseStylesOverride*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_EmptyElement_writer : public type_writer
		{
			CT_EmptyElement* t() { return static_cast<CT_EmptyElement*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class dml_stylesheet_writer : public type_writer
		{
			auto_type_writer< CT_OfficeStyleSheet_writer > _theme_writer;
			auto_type_writer< CT_BaseStylesOverride_writer > _themeOverride_writer;
			auto_type_writer< CT_EmptyElement_writer > _themeManager_writer;
			dml_stylesheet* t() { return static_cast<dml_stylesheet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColorMappingOverride_writer : public type_writer
		{
			auto_type_writer< CT_EmptyElement_writer > _masterClrMapping_writer;
			auto_type_writer< CT_ColorMapping_writer > _overrideClrMapping_writer;
			CT_ColorMappingOverride* t() { return static_cast<CT_ColorMappingOverride*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

