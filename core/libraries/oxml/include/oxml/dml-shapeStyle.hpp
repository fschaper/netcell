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

#ifndef DML_SHAPESTYLE_HPP
#define DML_SHAPESTYLE_HPP


#include "dml-baseTypes.hpp"
#include "dml-baseStylesheet.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_StyleMatrixReference;
	class CT_FontReference;
	class CT_ShapeStyle;

	class CT_StyleMatrixReference
	{
	public:
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
		ST_StyleMatrixColumnIndex idx;
	};

	class CT_FontReference
	{
	public:
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
		ST_FontCollectionIndex idx;
	};

	class CT_ShapeStyle
	{
	public:
		CT_StyleMatrixReference lnRef;
		CT_StyleMatrixReference fillRef;
		CT_StyleMatrixReference effectRef;
		CT_FontReference fontRef;
	};

}
#endif

