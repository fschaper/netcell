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


#include "sml-table_readers.hpp"
#include "sml-table_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_TableFormula_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_array_literal))
			{
				driver()->context()->parse(value, t()->array);
				return;
			}
			ST_Formula_reader::read_attribute(uri, localname, qname, value);
		}
		void CT_XmlColumnPr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_XmlColumnPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_mapId_literal))
			{
				driver()->context()->parse(value, t()->mapId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_xpath_literal))
			{
				driver()->context()->parse(value, t()->xpath);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_denormalized_literal))
			{
				driver()->context()->parse(value, t()->denormalized);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_xmlDataType_literal))
			{
				driver()->context()->parse(value, t()->xmlDataType);
				return;
			}
		}
		void CT_TableColumn_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_calculatedColumnFormula_literal))
			{
				driver()->push(localname, _calculatedColumnFormula_reader.get_reader(&t()->calculatedColumnFormula.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowFormula_literal))
			{
				driver()->push(localname, _totalsRowFormula_reader.get_reader(&t()->totalsRowFormula.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_xmlColumnPr_literal))
			{
				driver()->push(localname, _xmlColumnPr_reader.get_reader(&t()->xmlColumnPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_TableColumn_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_uniqueName_literal))
			{
				driver()->context()->parse(value, t()->uniqueName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowFunction_literal))
			{
				driver()->context()->parse(value, t()->totalsRowFunction);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowLabel_literal))
			{
				driver()->context()->parse(value, t()->totalsRowLabel.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_queryTableFieldId_literal))
			{
				driver()->context()->parse(value, t()->queryTableFieldId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_headerRowDxfId_literal))
			{
				driver()->context()->parse(value, t()->headerRowDxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_dataDxfId_literal))
			{
				driver()->context()->parse(value, t()->dataDxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowDxfId_literal))
			{
				driver()->context()->parse(value, t()->totalsRowDxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_headerRowCellStyle_literal))
			{
				driver()->context()->parse(value, t()->headerRowCellStyle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_dataCellStyle_literal))
			{
				driver()->context()->parse(value, t()->dataCellStyle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowCellStyle_literal))
			{
				driver()->context()->parse(value, t()->totalsRowCellStyle.getset());
				return;
			}
		}
		void CT_TableColumns_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_tableColumn_literal))
			{
				t()->tableColumn.resize(t()->tableColumn.size()+1);
				driver()->push(localname, _tableColumn_reader.get_reader(&t()->tableColumn.back()));
				return;
			}
		}
		void CT_TableColumns_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_TableStyleInfo_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_showFirstColumn_literal))
			{
				driver()->context()->parse(value, t()->showFirstColumn.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_showLastColumn_literal))
			{
				driver()->context()->parse(value, t()->showLastColumn.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_showRowStripes_literal))
			{
				driver()->context()->parse(value, t()->showRowStripes.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_showColumnStripes_literal))
			{
				driver()->context()->parse(value, t()->showColumnStripes.getset());
				return;
			}
		}
		void CT_Table_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_autoFilter_literal))
			{
				driver()->push(localname, _autoFilter_reader.get_reader(&t()->autoFilter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_sortState_literal))
			{
				driver()->push(localname, _sortState_reader.get_reader(&t()->sortState.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_tableColumns_literal))
			{
				driver()->push(localname, _tableColumns_reader.get_reader(&t()->tableColumns));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_tableStyleInfo_literal))
			{
				driver()->push(localname, _tableStyleInfo_reader.get_reader(&t()->tableStyleInfo.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Table_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_displayName_literal))
			{
				driver()->context()->parse(value, t()->displayName);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_comment_literal))
			{
				driver()->context()->parse(value, t()->comment.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_tableType_literal))
			{
				driver()->context()->parse(value, t()->tableType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_headerRowCount_literal))
			{
				driver()->context()->parse(value, t()->headerRowCount);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_insertRow_literal))
			{
				driver()->context()->parse(value, t()->insertRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_insertRowShift_literal))
			{
				driver()->context()->parse(value, t()->insertRowShift);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowCount_literal))
			{
				driver()->context()->parse(value, t()->totalsRowCount);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowShown_literal))
			{
				driver()->context()->parse(value, t()->totalsRowShown);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_published_literal))
			{
				driver()->context()->parse(value, t()->published);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_headerRowDxfId_literal))
			{
				driver()->context()->parse(value, t()->headerRowDxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_dataDxfId_literal))
			{
				driver()->context()->parse(value, t()->dataDxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowDxfId_literal))
			{
				driver()->context()->parse(value, t()->totalsRowDxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_headerRowBorderDxfId_literal))
			{
				driver()->context()->parse(value, t()->headerRowBorderDxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_tableBorderDxfId_literal))
			{
				driver()->context()->parse(value, t()->tableBorderDxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowBorderDxfId_literal))
			{
				driver()->context()->parse(value, t()->totalsRowBorderDxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_headerRowCellStyle_literal))
			{
				driver()->context()->parse(value, t()->headerRowCellStyle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_dataCellStyle_literal))
			{
				driver()->context()->parse(value, t()->dataCellStyle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_totalsRowCellStyle_literal))
			{
				driver()->context()->parse(value, t()->totalsRowCellStyle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_table_connectionId_literal))
			{
				driver()->context()->parse(value, t()->connectionId.getset());
				return;
			}
		}
		void sml_table_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_table_table_literal))
			{
				driver()->push(localname, _table_reader.get_reader(&t()->table.getset()));
				return;
			}
		}
	}
}
