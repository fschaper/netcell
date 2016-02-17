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


#include "sml-queryTable_readers.hpp"
#include "sml-queryTable_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_QueryTableField_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_QueryTableField_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_dataBound_literal))
			{
				driver()->context()->parse(value, t()->dataBound);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_rowNumbers_literal))
			{
				driver()->context()->parse(value, t()->rowNumbers);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_fillFormulas_literal))
			{
				driver()->context()->parse(value, t()->fillFormulas);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_clipped_literal))
			{
				driver()->context()->parse(value, t()->clipped);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_tableColumnId_literal))
			{
				driver()->context()->parse(value, t()->tableColumnId);
				return;
			}
		}
		void CT_QueryTableFields_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_queryTableField_literal))
			{
				t()->queryTableField.resize(t()->queryTableField.size()+1);
				driver()->push(localname, _queryTableField_reader.get_reader(&t()->queryTableField.back()));
				return;
			}
		}
		void CT_QueryTableFields_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_DeletedField_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
		}
		void CT_QueryTableDeletedFields_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_deletedField_literal))
			{
				t()->deletedField.resize(t()->deletedField.size()+1);
				driver()->push(localname, _deletedField_reader.get_reader(&t()->deletedField.back()));
				return;
			}
		}
		void CT_QueryTableDeletedFields_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_QueryTableRefresh_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_queryTableFields_literal))
			{
				driver()->push(localname, _queryTableFields_reader.get_reader(&t()->queryTableFields));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_queryTableDeletedFields_literal))
			{
				driver()->push(localname, _queryTableDeletedFields_reader.get_reader(&t()->queryTableDeletedFields.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_sortState_literal))
			{
				driver()->push(localname, _sortState_reader.get_reader(&t()->sortState.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_QueryTableRefresh_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_preserveSortFilterLayout_literal))
			{
				driver()->context()->parse(value, t()->preserveSortFilterLayout);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_fieldIdWrapped_literal))
			{
				driver()->context()->parse(value, t()->fieldIdWrapped);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_headersInLastRefresh_literal))
			{
				driver()->context()->parse(value, t()->headersInLastRefresh);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_minimumVersion_literal))
			{
				driver()->context()->parse(value, t()->minimumVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_nextId_literal))
			{
				driver()->context()->parse(value, t()->nextId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_unboundColumnsLeft_literal))
			{
				driver()->context()->parse(value, t()->unboundColumnsLeft);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_unboundColumnsRight_literal))
			{
				driver()->context()->parse(value, t()->unboundColumnsRight);
				return;
			}
		}
		void CT_QueryTable_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_queryTableRefresh_literal))
			{
				driver()->push(localname, _queryTableRefresh_reader.get_reader(&t()->queryTableRefresh.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_QueryTable_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_headers_literal))
			{
				driver()->context()->parse(value, t()->headers);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_rowNumbers_literal))
			{
				driver()->context()->parse(value, t()->rowNumbers);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_disableRefresh_literal))
			{
				driver()->context()->parse(value, t()->disableRefresh);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_backgroundRefresh_literal))
			{
				driver()->context()->parse(value, t()->backgroundRefresh);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_firstBackgroundRefresh_literal))
			{
				driver()->context()->parse(value, t()->firstBackgroundRefresh);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_refreshOnLoad_literal))
			{
				driver()->context()->parse(value, t()->refreshOnLoad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_growShrinkType_literal))
			{
				driver()->context()->parse(value, t()->growShrinkType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_fillFormulas_literal))
			{
				driver()->context()->parse(value, t()->fillFormulas);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_removeDataOnSave_literal))
			{
				driver()->context()->parse(value, t()->removeDataOnSave);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_disableEdit_literal))
			{
				driver()->context()->parse(value, t()->disableEdit);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_preserveFormatting_literal))
			{
				driver()->context()->parse(value, t()->preserveFormatting);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_adjustColumnWidth_literal))
			{
				driver()->context()->parse(value, t()->adjustColumnWidth);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_intermediate_literal))
			{
				driver()->context()->parse(value, t()->intermediate);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_connectionId_literal))
			{
				driver()->context()->parse(value, t()->connectionId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_autoFormatId_literal))
			{
				driver()->context()->parse(value, t()->autoFormatId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_applyNumberFormats_literal))
			{
				driver()->context()->parse(value, t()->applyNumberFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_applyBorderFormats_literal))
			{
				driver()->context()->parse(value, t()->applyBorderFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_applyFontFormats_literal))
			{
				driver()->context()->parse(value, t()->applyFontFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_applyPatternFormats_literal))
			{
				driver()->context()->parse(value, t()->applyPatternFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_applyAlignmentFormats_literal))
			{
				driver()->context()->parse(value, t()->applyAlignmentFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_queryTable_applyWidthHeightFormats_literal))
			{
				driver()->context()->parse(value, t()->applyWidthHeightFormats.getset());
				return;
			}
		}
		void sml_queryTable_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_queryTable_queryTable_literal))
			{
				driver()->push(localname, _queryTable_reader.get_reader(&t()->queryTable.getset()));
				return;
			}
		}
	}
}
