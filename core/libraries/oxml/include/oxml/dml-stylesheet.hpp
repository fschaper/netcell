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

#ifndef DML_STYLESHEET_HPP
#define DML_STYLESHEET_HPP


#include "dml-baseTypes.hpp"
#include "dml-baseStylesheet.hpp"
#include "dml-styleDefaults.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_ColorMapping;
	class CT_ColorSchemeAndMapping;
	class CT_ColorSchemeList;
	class CT_OfficeStyleSheet;
	class CT_BaseStylesOverride;
	class CT_EmptyElement;
	class dml_stylesheet;
	class CT_ColorMappingOverride;

	class CT_ColorMapping
	{
	public:
		poptional< CT_OfficeArtExtensionList > extLst;
		ST_ColorSchemeIndex bg1;
		ST_ColorSchemeIndex tx1;
		ST_ColorSchemeIndex bg2;
		ST_ColorSchemeIndex tx2;
		ST_ColorSchemeIndex accent1;
		ST_ColorSchemeIndex accent2;
		ST_ColorSchemeIndex accent3;
		ST_ColorSchemeIndex accent4;
		ST_ColorSchemeIndex accent5;
		ST_ColorSchemeIndex accent6;
		ST_ColorSchemeIndex hlink;
		ST_ColorSchemeIndex folHlink;
	};

	class CT_ColorSchemeAndMapping
	{
	public:
		CT_ColorScheme clrScheme;
		poptional< CT_ColorMapping > clrMap;
	};

	class CT_ColorSchemeList
	{
	public:
		std::vector< CT_ColorSchemeAndMapping > extraClrScheme;
	};

	class CT_OfficeStyleSheet
	{
	public:
		CT_OfficeStyleSheet() : name("") {}
		CT_BaseStyles themeElements;
		poptional< CT_ObjectStyleDefaults > objectDefaults;
		poptional< CT_ColorSchemeList > extraClrSchemeLst;
		poptional< CT_CustomColorList > custClrLst;
		poptional< CT_OfficeArtExtensionList > extLst;
		String name;
	};

	class CT_BaseStylesOverride
	{
	public:
		poptional< CT_ColorScheme > clrScheme;
		poptional< CT_FontScheme > fontScheme;
		poptional< CT_StyleMatrix > fmtScheme;
	};

	class CT_EmptyElement
	{
	public:
	};

	class dml_stylesheet
	{
	public:
		poptional< CT_OfficeStyleSheet > theme;
		poptional< CT_BaseStylesOverride > themeOverride;
		poptional< CT_EmptyElement > themeManager;
	};

	class CT_ColorMappingOverride
	{
	public:
		poptional< CT_EmptyElement > masterClrMapping;
		poptional< CT_ColorMapping > overrideClrMapping;
	};

}
#endif

