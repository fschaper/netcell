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


#include "sml-supplementaryWorkbooks_readers.hpp"
#include "sml-supplementaryWorkbooks_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_ExternalSheetName_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_val_literal))
			{
				driver()->context()->parse(value, t()->val.getset());
				return;
			}
		}
		void CT_ExternalSheetNames_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_sheetName_literal))
			{
				t()->sheetName.resize(t()->sheetName.size()+1);
				driver()->push(localname, _sheetName_reader.get_reader(&t()->sheetName.back()));
				return;
			}
		}
		void CT_ExternalDefinedName_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_refersTo_literal))
			{
				driver()->context()->parse(value, t()->refersTo.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId.getset());
				return;
			}
		}
		void CT_ExternalDefinedNames_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_definedName_literal))
			{
				t()->definedName.resize(t()->definedName.size()+1);
				driver()->push(localname, _definedName_reader.get_reader(&t()->definedName.back()));
				return;
			}
		}
		void CT_ExternalCell_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_v_literal))
			{
				driver()->push(localname, _v_reader.get_reader(&t()->v.getset()));
				return;
			}
		}
		void CT_ExternalCell_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_r_literal))
			{
				driver()->context()->parse(value, t()->r.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_vm_literal))
			{
				driver()->context()->parse(value, t()->vm);
				return;
			}
		}
		void CT_ExternalRow_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_cell_literal))
			{
				t()->cell.resize(t()->cell.size()+1);
				driver()->push(localname, _cell_reader.get_reader(&t()->cell.back()));
				return;
			}
		}
		void CT_ExternalRow_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
		}
		void CT_ExternalSheetData_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_row_literal))
			{
				t()->row.resize(t()->row.size()+1);
				driver()->push(localname, _row_reader.get_reader(&t()->row.back()));
				return;
			}
		}
		void CT_ExternalSheetData_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_refreshError_literal))
			{
				driver()->context()->parse(value, t()->refreshError);
				return;
			}
		}
		void CT_ExternalSheetDataSet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_sheetData_literal))
			{
				t()->sheetData.resize(t()->sheetData.size()+1);
				driver()->push(localname, _sheetData_reader.get_reader(&t()->sheetData.back()));
				return;
			}
		}
		void CT_ExternalBook_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_sheetNames_literal))
			{
				driver()->push(localname, _sheetNames_reader.get_reader(&t()->sheetNames.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_definedNames_literal))
			{
				driver()->push(localname, _definedNames_reader.get_reader(&t()->definedNames.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_sheetDataSet_literal))
			{
				driver()->push(localname, _sheetDataSet_reader.get_reader(&t()->sheetDataSet.getset()));
				return;
			}
		}
		void CT_ExternalBook_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
		}
		void CT_DdeValue_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_val_literal))
			{
				driver()->push(localname, _val_reader.get_reader(&t()->val));
				return;
			}
		}
		void CT_DdeValue_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
		}
		void CT_DdeValues_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_value_literal))
			{
				t()->value.resize(t()->value.size()+1);
				driver()->push(localname, _value_reader.get_reader(&t()->value.back()));
				return;
			}
		}
		void CT_DdeValues_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_rows_literal))
			{
				driver()->context()->parse(value, t()->rows);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_cols_literal))
			{
				driver()->context()->parse(value, t()->cols);
				return;
			}
		}
		void CT_DdeItem_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_values_literal))
			{
				driver()->push(localname, _values_reader.get_reader(&t()->values.getset()));
				return;
			}
		}
		void CT_DdeItem_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_ole_literal))
			{
				driver()->context()->parse(value, t()->ole);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_advise_literal))
			{
				driver()->context()->parse(value, t()->advise);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_preferPic_literal))
			{
				driver()->context()->parse(value, t()->preferPic);
				return;
			}
		}
		void CT_DdeItems_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_ddeItem_literal))
			{
				t()->ddeItem.resize(t()->ddeItem.size()+1);
				driver()->push(localname, _ddeItem_reader.get_reader(&t()->ddeItem.back()));
				return;
			}
		}
		void CT_DdeLink_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_ddeItems_literal))
			{
				driver()->push(localname, _ddeItems_reader.get_reader(&t()->ddeItems.getset()));
				return;
			}
		}
		void CT_DdeLink_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_ddeService_literal))
			{
				driver()->context()->parse(value, t()->ddeService);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_ddeTopic_literal))
			{
				driver()->context()->parse(value, t()->ddeTopic);
				return;
			}
		}
		void CT_OleItem_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_icon_literal))
			{
				driver()->context()->parse(value, t()->icon);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_advise_literal))
			{
				driver()->context()->parse(value, t()->advise);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_preferPic_literal))
			{
				driver()->context()->parse(value, t()->preferPic);
				return;
			}
		}
		void CT_OleItems_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_oleItem_literal))
			{
				t()->oleItem.resize(t()->oleItem.size()+1);
				driver()->push(localname, _oleItem_reader.get_reader(&t()->oleItem.back()));
				return;
			}
		}
		void CT_OleLink_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_oleItems_literal))
			{
				driver()->push(localname, _oleItems_reader.get_reader(&t()->oleItems.getset()));
				return;
			}
		}
		void CT_OleLink_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_progId_literal))
			{
				driver()->context()->parse(value, t()->progId);
				return;
			}
		}
		void CT_ExternalLink_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_externalBook_literal))
			{
				driver()->push(localname, _externalBook_reader.get_reader(&t()->externalBook.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_ddeLink_literal))
			{
				driver()->push(localname, _ddeLink_reader.get_reader(&t()->ddeLink.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_oleLink_literal))
			{
				driver()->push(localname, _oleLink_reader.get_reader(&t()->oleLink.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void sml_supplementaryWorkbooks_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_supplementaryWorkbooks_externalLink_literal))
			{
				driver()->push(localname, _externalLink_reader.get_reader(&t()->externalLink.getset()));
				return;
			}
		}
	}
}
