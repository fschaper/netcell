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

#ifndef DML_SHAPEPROPERTIES_READERS_HPP
#define DML_SHAPEPROPERTIES_READERS_HPP

#include "dml-shapeProperties.hpp"
#include "dml-baseTypes_readers.hpp"
#include "dml-shapeGeometry_readers.hpp"
#include "dml-shapeEffects_readers.hpp"
#include "dml-shapeLineProperties_readers.hpp"
#include "dml-shape3DScene_readers.hpp"
#include "dml-shape3DStyles_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_ShapeProperties_reader;
		class CT_GroupShapeProperties_reader;

		class CT_ShapeProperties_reader : public type_reader
		{
			auto_type_reader< CT_Transform2D_reader > _xfrm_reader;
			auto_type_reader< CT_CustomGeometry2D_reader > _custGeom_reader;
			auto_type_reader< CT_PresetGeometry2D_reader > _prstGeom_reader;
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_GroupFillProperties_reader > _grpFill_reader;
			auto_type_reader< CT_LineProperties_reader > _ln_reader;
			auto_type_reader< CT_EffectList_reader > _effectLst_reader;
			auto_type_reader< CT_EffectContainer_reader > _effectDag_reader;
			auto_type_reader< CT_Scene3D_reader > _scene3d_reader;
			auto_type_reader< CT_Shape3D_reader > _sp3d_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_ShapeProperties* t() { return static_cast<CT_ShapeProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupShapeProperties_reader : public type_reader
		{
			auto_type_reader< CT_GroupTransform2D_reader > _xfrm_reader;
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_GroupFillProperties_reader > _grpFill_reader;
			auto_type_reader< CT_EffectList_reader > _effectLst_reader;
			auto_type_reader< CT_EffectContainer_reader > _effectDag_reader;
			auto_type_reader< CT_Scene3D_reader > _scene3d_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_GroupShapeProperties* t() { return static_cast<CT_GroupShapeProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

	}
}
#endif

