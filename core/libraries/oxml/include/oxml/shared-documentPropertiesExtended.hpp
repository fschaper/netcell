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

#ifndef SHARED_DOCUMENTPROPERTIESEXTENDED_HPP
#define SHARED_DOCUMENTPROPERTIESEXTENDED_HPP


#include "shared-documentPropertiesVariantTypes.hpp"

namespace extended_properties
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_VectorVariant;
	class CT_VectorLpstr;
	class CT_DigSigBlob;
	class CT_Properties;
	class shared_documentPropertiesExtended;

	class CT_VectorVariant
	{
	public:
		::docPropsVTypes::CT_Vector vector;
	};

	class CT_VectorLpstr
	{
	public:
		::docPropsVTypes::CT_Vector vector;
	};

	class CT_DigSigBlob
	{
	public:
		Base64Binary blob;
	};

	class CT_Properties
	{
	public:
		optional< String > Template;
		optional< String > Manager;
		optional< String > Company;
		optional< Int > Pages;
		optional< Int > Words;
		optional< Int > Characters;
		optional< String > PresentationFormat;
		optional< Int > Lines;
		optional< Int > Paragraphs;
		optional< Int > Slides;
		optional< Int > Notes;
		optional< Int > TotalTime;
		optional< Int > HiddenSlides;
		optional< Int > MMClips;
		optional< Boolean > ScaleCrop;
		poptional< CT_VectorVariant > HeadingPairs;
		poptional< CT_VectorLpstr > TitlesOfParts;
		optional< Boolean > LinksUpToDate;
		optional< Int > CharactersWithSpaces;
		optional< Boolean > SharedDoc;
		optional< String > HyperlinkBase;
		poptional< CT_VectorVariant > HLinks;
		optional< Boolean > HyperlinksChanged;
		poptional< CT_DigSigBlob > DigSig;
		optional< String > Application;
		optional< String > AppVersion;
		optional< Int > DocSecurity;
	};

	class shared_documentPropertiesExtended
	{
	public:
		poptional< CT_Properties > Properties;
	};

}
#endif

