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

#ifndef DML_DOCUMENTPROPERTIES_WRITERS_HPP
#define DML_DOCUMENTPROPERTIES_WRITERS_HPP

#include "dml-documentProperties.hpp"
#include "dml-documentProperties_literals.hpp"
#include "dml-baseTypes_writers.hpp"
#include "dml-shapeGeometry_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_NonVisualDrawingProps_writer;
		class CT_ShapeLocking_writer;
		class CT_NonVisualDrawingShapeProps_writer;
		class CT_GroupLocking_writer;
		class CT_NonVisualGroupDrawingShapeProps_writer;
		class CT_GraphicalObjectFrameLocking_writer;
		class CT_NonVisualGraphicFrameProperties_writer;
		class CT_ConnectorLocking_writer;
		class CT_NonVisualConnectorProperties_writer;
		class CT_PictureLocking_writer;
		class CT_NonVisualPictureProperties_writer;

		class CT_NonVisualDrawingProps_writer : public type_writer
		{
			auto_type_writer< CT_Hyperlink_writer > _hlinkClick_writer;
			auto_type_writer< CT_Hyperlink_writer > _hlinkHover_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_NonVisualDrawingProps* t() { return static_cast<CT_NonVisualDrawingProps*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ShapeLocking_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_ShapeLocking* t() { return static_cast<CT_ShapeLocking*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_NonVisualDrawingShapeProps_writer : public type_writer
		{
			auto_type_writer< CT_ShapeLocking_writer > _spLocks_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_NonVisualDrawingShapeProps* t() { return static_cast<CT_NonVisualDrawingShapeProps*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupLocking_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_GroupLocking* t() { return static_cast<CT_GroupLocking*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_NonVisualGroupDrawingShapeProps_writer : public type_writer
		{
			auto_type_writer< CT_GroupLocking_writer > _grpSpLocks_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_NonVisualGroupDrawingShapeProps* t() { return static_cast<CT_NonVisualGroupDrawingShapeProps*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GraphicalObjectFrameLocking_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_GraphicalObjectFrameLocking* t() { return static_cast<CT_GraphicalObjectFrameLocking*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_NonVisualGraphicFrameProperties_writer : public type_writer
		{
			auto_type_writer< CT_GraphicalObjectFrameLocking_writer > _graphicFrameLocks_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_NonVisualGraphicFrameProperties* t() { return static_cast<CT_NonVisualGraphicFrameProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ConnectorLocking_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_ConnectorLocking* t() { return static_cast<CT_ConnectorLocking*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_NonVisualConnectorProperties_writer : public type_writer
		{
			auto_type_writer< CT_ConnectorLocking_writer > _cxnSpLocks_writer;
			auto_type_writer< CT_Connection_writer > _stCxn_writer;
			auto_type_writer< CT_Connection_writer > _endCxn_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_NonVisualConnectorProperties* t() { return static_cast<CT_NonVisualConnectorProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PictureLocking_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_PictureLocking* t() { return static_cast<CT_PictureLocking*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_NonVisualPictureProperties_writer : public type_writer
		{
			auto_type_writer< CT_PictureLocking_writer > _picLocks_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_NonVisualPictureProperties* t() { return static_cast<CT_NonVisualPictureProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

