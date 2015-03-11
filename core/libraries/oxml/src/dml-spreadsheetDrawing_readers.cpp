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

#include "dml-spreadsheetDrawing_readers.hpp"
#include "dml-spreadsheetDrawing_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void ST_ColID_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_RowID_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Marker_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_col_literal))
			{
				driver()->push(localname, _col_reader.get_reader(&t()->col));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_colOff_literal))
			{
				driver()->push(localname, _colOff_reader.get_reader(&t()->colOff));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_row_literal))
			{
				driver()->push(localname, _row_reader.get_reader(&t()->row));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_rowOff_literal))
			{
				driver()->push(localname, _rowOff_reader.get_reader(&t()->rowOff));
				return;
			}
		}
		void CT_ShapeNonVisual_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvPr_literal))
			{
				driver()->push(localname, _cNvPr_reader.get_reader(&t()->cNvPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvSpPr_literal))
			{
				driver()->push(localname, _cNvSpPr_reader.get_reader(&t()->cNvSpPr));
				return;
			}
		}
		void CT_Shape_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_nvSpPr_literal))
			{
				driver()->push(localname, _nvSpPr_reader.get_reader(&t()->nvSpPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_spPr_literal))
			{
				driver()->push(localname, _spPr_reader.get_reader(&t()->spPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_style_literal))
			{
				driver()->push(localname, _style_reader.get_reader(&t()->style.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_txBody_literal))
			{
				driver()->push(localname, _txBody_reader.get_reader(&t()->txBody.getset()));
				return;
			}
		}
		void CT_Shape_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_macro_literal))
			{
				driver()->context()->parse(value, t()->macro.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_textlink_literal))
			{
				driver()->context()->parse(value, t()->textlink.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_fLocksText_literal))
			{
				driver()->context()->parse(value, t()->fLocksText);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_fPublished_literal))
			{
				driver()->context()->parse(value, t()->fPublished);
				return;
			}
		}
		void CT_GroupShapeNonVisual_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvPr_literal))
			{
				driver()->push(localname, _cNvPr_reader.get_reader(&t()->cNvPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvGrpSpPr_literal))
			{
				driver()->push(localname, _cNvGrpSpPr_reader.get_reader(&t()->cNvGrpSpPr));
				return;
			}
		}
		void CT_GraphicalObjectFrameNonVisual_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvPr_literal))
			{
				driver()->push(localname, _cNvPr_reader.get_reader(&t()->cNvPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvGraphicFramePr_literal))
			{
				driver()->push(localname, _cNvGraphicFramePr_reader.get_reader(&t()->cNvGraphicFramePr));
				return;
			}
		}
		void CT_GraphicalObjectFrame_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_nvGraphicFramePr_literal))
			{
				driver()->push(localname, _nvGraphicFramePr_reader.get_reader(&t()->nvGraphicFramePr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_xfrm_literal))
			{
				driver()->push(localname, _xfrm_reader.get_reader(&t()->xfrm));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_graphic_literal))
			{
				driver()->push(localname, _graphic_reader.get_reader(&t()->graphic));
				return;
			}
		}
		void CT_GraphicalObjectFrame_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_macro_literal))
			{
				driver()->context()->parse(value, t()->macro.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_fPublished_literal))
			{
				driver()->context()->parse(value, t()->fPublished);
				return;
			}
		}
		void CT_ConnectorNonVisual_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvPr_literal))
			{
				driver()->push(localname, _cNvPr_reader.get_reader(&t()->cNvPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvCxnSpPr_literal))
			{
				driver()->push(localname, _cNvCxnSpPr_reader.get_reader(&t()->cNvCxnSpPr));
				return;
			}
		}
		void CT_Connector_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_nvCxnSpPr_literal))
			{
				driver()->push(localname, _nvCxnSpPr_reader.get_reader(&t()->nvCxnSpPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_spPr_literal))
			{
				driver()->push(localname, _spPr_reader.get_reader(&t()->spPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_style_literal))
			{
				driver()->push(localname, _style_reader.get_reader(&t()->style.getset()));
				return;
			}
		}
		void CT_Connector_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_macro_literal))
			{
				driver()->context()->parse(value, t()->macro.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_fPublished_literal))
			{
				driver()->context()->parse(value, t()->fPublished);
				return;
			}
		}
		void CT_PictureNonVisual_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvPr_literal))
			{
				driver()->push(localname, _cNvPr_reader.get_reader(&t()->cNvPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cNvPicPr_literal))
			{
				driver()->push(localname, _cNvPicPr_reader.get_reader(&t()->cNvPicPr));
				return;
			}
		}
		void CT_Picture_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_nvPicPr_literal))
			{
				driver()->push(localname, _nvPicPr_reader.get_reader(&t()->nvPicPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_spPr_literal))
			{
				driver()->push(localname, _spPr_reader.get_reader(&t()->spPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_style_literal))
			{
				driver()->push(localname, _style_reader.get_reader(&t()->style.getset()));
				return;
			}
		}
		void CT_Picture_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_macro_literal))
			{
				driver()->context()->parse(value, t()->macro);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_fPublished_literal))
			{
				driver()->context()->parse(value, t()->fPublished);
				return;
			}
		}
		void CT_GroupShape_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_nvGrpSpPr_literal))
			{
				driver()->push(localname, _nvGrpSpPr_reader.get_reader(&t()->nvGrpSpPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_grpSpPr_literal))
			{
				driver()->push(localname, _grpSpPr_reader.get_reader(&t()->grpSpPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_sp_literal))
			{
				driver()->push(localname, _sp_reader.get_reader(&t()->sp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_grpSp_literal))
			{
				driver()->push(localname, _grpSp_reader.get_reader(&t()->grpSp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_graphicFrame_literal))
			{
				driver()->push(localname, _graphicFrame_reader.get_reader(&t()->graphicFrame.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cxnSp_literal))
			{
				driver()->push(localname, _cxnSp_reader.get_reader(&t()->cxnSp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_pic_literal))
			{
				driver()->push(localname, _pic_reader.get_reader(&t()->pic.getset()));
				return;
			}
		}
		void CT_AnchorClientData_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_fLocksWithSheet_literal))
			{
				driver()->context()->parse(value, t()->fLocksWithSheet);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_fPrintsWithSheet_literal))
			{
				driver()->context()->parse(value, t()->fPrintsWithSheet);
				return;
			}
		}
		void CT_TwoCellAnchor_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_from_literal))
			{
				driver()->push(localname, _from_reader.get_reader(&t()->from));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_to_literal))
			{
				driver()->push(localname, _to_reader.get_reader(&t()->to));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_sp_literal))
			{
				driver()->push(localname, _sp_reader.get_reader(&t()->sp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_grpSp_literal))
			{
				driver()->push(localname, _grpSp_reader.get_reader(&t()->grpSp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_graphicFrame_literal))
			{
				driver()->push(localname, _graphicFrame_reader.get_reader(&t()->graphicFrame.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_cxnSp_literal))
			{
				driver()->push(localname, _cxnSp_reader.get_reader(&t()->cxnSp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_pic_literal))
			{
				driver()->push(localname, _pic_reader.get_reader(&t()->pic.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_clientData_literal))
			{
				driver()->push(localname, _clientData_reader.get_reader(&t()->clientData));
				return;
			}
		}
		void CT_TwoCellAnchor_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_editAs_literal))
			{
				driver()->context()->parse(value, t()->editAs);
				return;
			}
		}
		void CT_Drawings_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_twoCellAnchor_literal))
			{
				t()->twoCellAnchor.resize(t()->twoCellAnchor.size()+1);
				driver()->push(localname, _twoCellAnchor_reader.get_reader(&t()->twoCellAnchor.back()));
				return;
			}
		}
		void dml_spreadsheetDrawing_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_spreadsheetDrawing_wsDr_literal))
			{
				driver()->push(localname, _wsDr_reader.get_reader(&t()->wsDr.getset()));
				return;
			}
		}
	}
}
