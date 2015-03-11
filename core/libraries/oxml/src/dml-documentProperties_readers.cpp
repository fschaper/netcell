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

#include "dml-documentProperties_readers.hpp"
#include "dml-documentProperties_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_NonVisualDrawingProps_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_hlinkClick_literal))
			{
				driver()->push(localname, _hlinkClick_reader.get_reader(&t()->hlinkClick.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_hlinkHover_literal))
			{
				driver()->push(localname, _hlinkHover_reader.get_reader(&t()->hlinkHover.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_NonVisualDrawingProps_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_descr_literal))
			{
				driver()->context()->parse(value, t()->descr);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_hidden_literal))
			{
				driver()->context()->parse(value, t()->hidden);
				return;
			}
		}
		void CT_ShapeLocking_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ShapeLocking_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noGrp_literal))
			{
				driver()->context()->parse(value, t()->noGrp);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noSelect_literal))
			{
				driver()->context()->parse(value, t()->noSelect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noRot_literal))
			{
				driver()->context()->parse(value, t()->noRot);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeAspect_literal))
			{
				driver()->context()->parse(value, t()->noChangeAspect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noMove_literal))
			{
				driver()->context()->parse(value, t()->noMove);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noResize_literal))
			{
				driver()->context()->parse(value, t()->noResize);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noEditPoints_literal))
			{
				driver()->context()->parse(value, t()->noEditPoints);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noAdjustHandles_literal))
			{
				driver()->context()->parse(value, t()->noAdjustHandles);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeArrowheads_literal))
			{
				driver()->context()->parse(value, t()->noChangeArrowheads);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeShapeType_literal))
			{
				driver()->context()->parse(value, t()->noChangeShapeType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noTextEdit_literal))
			{
				driver()->context()->parse(value, t()->noTextEdit);
				return;
			}
		}
		void CT_NonVisualDrawingShapeProps_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_spLocks_literal))
			{
				driver()->push(localname, _spLocks_reader.get_reader(&t()->spLocks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_NonVisualDrawingShapeProps_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_txBox_literal))
			{
				driver()->context()->parse(value, t()->txBox);
				return;
			}
		}
		void CT_GroupLocking_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_GroupLocking_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noGrp_literal))
			{
				driver()->context()->parse(value, t()->noGrp);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noUngrp_literal))
			{
				driver()->context()->parse(value, t()->noUngrp);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noSelect_literal))
			{
				driver()->context()->parse(value, t()->noSelect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noRot_literal))
			{
				driver()->context()->parse(value, t()->noRot);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeAspect_literal))
			{
				driver()->context()->parse(value, t()->noChangeAspect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noMove_literal))
			{
				driver()->context()->parse(value, t()->noMove);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noResize_literal))
			{
				driver()->context()->parse(value, t()->noResize);
				return;
			}
		}
		void CT_NonVisualGroupDrawingShapeProps_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_grpSpLocks_literal))
			{
				driver()->push(localname, _grpSpLocks_reader.get_reader(&t()->grpSpLocks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_GraphicalObjectFrameLocking_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_GraphicalObjectFrameLocking_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noGrp_literal))
			{
				driver()->context()->parse(value, t()->noGrp);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noDrilldown_literal))
			{
				driver()->context()->parse(value, t()->noDrilldown);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noSelect_literal))
			{
				driver()->context()->parse(value, t()->noSelect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeAspect_literal))
			{
				driver()->context()->parse(value, t()->noChangeAspect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noMove_literal))
			{
				driver()->context()->parse(value, t()->noMove);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noResize_literal))
			{
				driver()->context()->parse(value, t()->noResize);
				return;
			}
		}
		void CT_NonVisualGraphicFrameProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_graphicFrameLocks_literal))
			{
				driver()->push(localname, _graphicFrameLocks_reader.get_reader(&t()->graphicFrameLocks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ConnectorLocking_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ConnectorLocking_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noGrp_literal))
			{
				driver()->context()->parse(value, t()->noGrp);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noSelect_literal))
			{
				driver()->context()->parse(value, t()->noSelect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noRot_literal))
			{
				driver()->context()->parse(value, t()->noRot);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeAspect_literal))
			{
				driver()->context()->parse(value, t()->noChangeAspect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noMove_literal))
			{
				driver()->context()->parse(value, t()->noMove);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noResize_literal))
			{
				driver()->context()->parse(value, t()->noResize);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noEditPoints_literal))
			{
				driver()->context()->parse(value, t()->noEditPoints);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noAdjustHandles_literal))
			{
				driver()->context()->parse(value, t()->noAdjustHandles);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeArrowheads_literal))
			{
				driver()->context()->parse(value, t()->noChangeArrowheads);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeShapeType_literal))
			{
				driver()->context()->parse(value, t()->noChangeShapeType);
				return;
			}
		}
		void CT_NonVisualConnectorProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_cxnSpLocks_literal))
			{
				driver()->push(localname, _cxnSpLocks_reader.get_reader(&t()->cxnSpLocks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_stCxn_literal))
			{
				driver()->push(localname, _stCxn_reader.get_reader(&t()->stCxn.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_endCxn_literal))
			{
				driver()->push(localname, _endCxn_reader.get_reader(&t()->endCxn.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PictureLocking_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PictureLocking_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noGrp_literal))
			{
				driver()->context()->parse(value, t()->noGrp);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noSelect_literal))
			{
				driver()->context()->parse(value, t()->noSelect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noRot_literal))
			{
				driver()->context()->parse(value, t()->noRot);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeAspect_literal))
			{
				driver()->context()->parse(value, t()->noChangeAspect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noMove_literal))
			{
				driver()->context()->parse(value, t()->noMove);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noResize_literal))
			{
				driver()->context()->parse(value, t()->noResize);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noEditPoints_literal))
			{
				driver()->context()->parse(value, t()->noEditPoints);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noAdjustHandles_literal))
			{
				driver()->context()->parse(value, t()->noAdjustHandles);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeArrowheads_literal))
			{
				driver()->context()->parse(value, t()->noChangeArrowheads);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noChangeShapeType_literal))
			{
				driver()->context()->parse(value, t()->noChangeShapeType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_noCrop_literal))
			{
				driver()->context()->parse(value, t()->noCrop);
				return;
			}
		}
		void CT_NonVisualPictureProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_picLocks_literal))
			{
				driver()->push(localname, _picLocks_reader.get_reader(&t()->picLocks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_NonVisualPictureProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_documentProperties_preferRelativeResize_literal))
			{
				driver()->context()->parse(value, t()->preferRelativeResize);
				return;
			}
		}
	}
}
