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

#ifndef DML_SHAPEPROPERTIES_HPP
#define DML_SHAPEPROPERTIES_HPP


#include "dml-baseTypes.hpp"
#include "dml-shapeGeometry.hpp"
#include "dml-shapeEffects.hpp"
#include "dml-shapeLineProperties.hpp"
#include "dml-shape3DScene.hpp"
#include "dml-shape3DStyles.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_ShapeProperties;
	class CT_GroupShapeProperties;

	class CT_ShapeProperties
	{
	public:
		poptional< CT_Transform2D > xfrm;
		poptional< CT_CustomGeometry2D > custGeom;
		poptional< CT_PresetGeometry2D > prstGeom;
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_BlipFillProperties > blipFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_GroupFillProperties > grpFill;
		poptional< CT_LineProperties > ln;
		poptional< CT_EffectList > effectLst;
		poptional< CT_EffectContainer > effectDag;
		poptional< CT_Scene3D > scene3d;
		poptional< CT_Shape3D > sp3d;
		poptional< CT_OfficeArtExtensionList > extLst;
		optional< ST_BlackWhiteMode > bwMode;
	};

	class CT_GroupShapeProperties
	{
	public:
		poptional< CT_GroupTransform2D > xfrm;
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_BlipFillProperties > blipFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_GroupFillProperties > grpFill;
		poptional< CT_EffectList > effectLst;
		poptional< CT_EffectContainer > effectDag;
		poptional< CT_Scene3D > scene3d;
		poptional< CT_OfficeArtExtensionList > extLst;
		optional< ST_BlackWhiteMode > bwMode;
	};

}
#endif

