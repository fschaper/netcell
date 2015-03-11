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

#ifndef DML_DOCUMENTPROPERTIES_READERS_HPP
#define DML_DOCUMENTPROPERTIES_READERS_HPP

#include "dml-documentProperties.hpp"
#include "dml-baseTypes_readers.hpp"
#include "dml-shapeGeometry_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_NonVisualDrawingProps_reader;
		class CT_ShapeLocking_reader;
		class CT_NonVisualDrawingShapeProps_reader;
		class CT_GroupLocking_reader;
		class CT_NonVisualGroupDrawingShapeProps_reader;
		class CT_GraphicalObjectFrameLocking_reader;
		class CT_NonVisualGraphicFrameProperties_reader;
		class CT_ConnectorLocking_reader;
		class CT_NonVisualConnectorProperties_reader;
		class CT_PictureLocking_reader;
		class CT_NonVisualPictureProperties_reader;

		class CT_NonVisualDrawingProps_reader : public type_reader
		{
			auto_type_reader< CT_Hyperlink_reader > _hlinkClick_reader;
			auto_type_reader< CT_Hyperlink_reader > _hlinkHover_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_NonVisualDrawingProps* t() { return static_cast<CT_NonVisualDrawingProps*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ShapeLocking_reader : public type_reader
		{
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_ShapeLocking* t() { return static_cast<CT_ShapeLocking*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_NonVisualDrawingShapeProps_reader : public type_reader
		{
			auto_type_reader< CT_ShapeLocking_reader > _spLocks_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_NonVisualDrawingShapeProps* t() { return static_cast<CT_NonVisualDrawingShapeProps*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupLocking_reader : public type_reader
		{
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_GroupLocking* t() { return static_cast<CT_GroupLocking*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_NonVisualGroupDrawingShapeProps_reader : public type_reader
		{
			auto_type_reader< CT_GroupLocking_reader > _grpSpLocks_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_NonVisualGroupDrawingShapeProps* t() { return static_cast<CT_NonVisualGroupDrawingShapeProps*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_GraphicalObjectFrameLocking_reader : public type_reader
		{
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_GraphicalObjectFrameLocking* t() { return static_cast<CT_GraphicalObjectFrameLocking*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_NonVisualGraphicFrameProperties_reader : public type_reader
		{
			auto_type_reader< CT_GraphicalObjectFrameLocking_reader > _graphicFrameLocks_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_NonVisualGraphicFrameProperties* t() { return static_cast<CT_NonVisualGraphicFrameProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ConnectorLocking_reader : public type_reader
		{
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_ConnectorLocking* t() { return static_cast<CT_ConnectorLocking*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_NonVisualConnectorProperties_reader : public type_reader
		{
			auto_type_reader< CT_ConnectorLocking_reader > _cxnSpLocks_reader;
			auto_type_reader< CT_Connection_reader > _stCxn_reader;
			auto_type_reader< CT_Connection_reader > _endCxn_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_NonVisualConnectorProperties* t() { return static_cast<CT_NonVisualConnectorProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_PictureLocking_reader : public type_reader
		{
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_PictureLocking* t() { return static_cast<CT_PictureLocking*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_NonVisualPictureProperties_reader : public type_reader
		{
			auto_type_reader< CT_PictureLocking_reader > _picLocks_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_NonVisualPictureProperties* t() { return static_cast<CT_NonVisualPictureProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

	}
}
#endif

