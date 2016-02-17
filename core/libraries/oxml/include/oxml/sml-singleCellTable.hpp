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

#ifndef SML_SINGLECELLTABLE_HPP
#define SML_SINGLECELLTABLE_HPP


#include "sml-baseTypes.hpp"
#include "sml-table.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_XmlPr;
	class CT_XmlCellPr;
	class CT_SingleXmlCell;
	class CT_SingleXmlCells;
	class sml_singleCellTable;

	class CT_XmlPr
	{
	public:
		poptional< CT_ExtensionList > extLst;
		UnsignedInt mapId;
		ST_Xstring xpath;
		ST_XmlDataType xmlDataType;
	};

	class CT_XmlCellPr
	{
	public:
		CT_XmlPr xmlPr;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt id;
		poptional< ST_Xstring > uniqueName;
	};

	class CT_SingleXmlCell
	{
	public:
		CT_XmlCellPr xmlCellPr;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt id;
		ST_CellRef r;
		UnsignedInt connectionId;
	};

	class CT_SingleXmlCells
	{
	public:
		std::vector< CT_SingleXmlCell > singleXmlCell;
	};

	class sml_singleCellTable
	{
	public:
		poptional< CT_SingleXmlCells > singleXmlCells;
	};

}
#endif

