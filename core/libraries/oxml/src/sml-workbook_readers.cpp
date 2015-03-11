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


#include "sml-workbook_readers.hpp"
#include "sml-workbook_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_SheetBackgroundPicture_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
		}
		void CT_FileVersion_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_appName_literal))
			{
				driver()->context()->parse(value, t()->appName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_lastEdited_literal))
			{
				driver()->context()->parse(value, t()->lastEdited.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_lowestEdited_literal))
			{
				driver()->context()->parse(value, t()->lowestEdited.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_rupBuild_literal))
			{
				driver()->context()->parse(value, t()->rupBuild.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_codeName_literal))
			{
				driver()->context()->parse(value, t()->codeName.getset());
				return;
			}
		}
		void CT_FileSharing_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_readOnlyRecommended_literal))
			{
				driver()->context()->parse(value, t()->readOnlyRecommended);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_userName_literal))
			{
				driver()->context()->parse(value, t()->userName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_reservationPassword_literal))
			{
				driver()->context()->parse(value, t()->reservationPassword.getset());
				return;
			}
		}
		void CT_WorkbookPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_date1904_literal))
			{
				driver()->context()->parse(value, t()->date1904);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showObjects_literal))
			{
				driver()->context()->parse(value, t()->showObjects);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showBorderUnselectedTables_literal))
			{
				driver()->context()->parse(value, t()->showBorderUnselectedTables);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_filterPrivacy_literal))
			{
				driver()->context()->parse(value, t()->filterPrivacy);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_promptedSolutions_literal))
			{
				driver()->context()->parse(value, t()->promptedSolutions);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showInkAnnotation_literal))
			{
				driver()->context()->parse(value, t()->showInkAnnotation);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_backupFile_literal))
			{
				driver()->context()->parse(value, t()->backupFile);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_saveExternalLinkValues_literal))
			{
				driver()->context()->parse(value, t()->saveExternalLinkValues);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_updateLinks_literal))
			{
				driver()->context()->parse(value, t()->updateLinks);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_codeName_literal))
			{
				driver()->context()->parse(value, t()->codeName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_hidePivotFieldList_literal))
			{
				driver()->context()->parse(value, t()->hidePivotFieldList);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showPivotChartFilter_literal))
			{
				driver()->context()->parse(value, t()->showPivotChartFilter);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_allowRefreshQuery_literal))
			{
				driver()->context()->parse(value, t()->allowRefreshQuery);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_publishItems_literal))
			{
				driver()->context()->parse(value, t()->publishItems);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_checkCompatibility_literal))
			{
				driver()->context()->parse(value, t()->checkCompatibility);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_autoCompressPictures_literal))
			{
				driver()->context()->parse(value, t()->autoCompressPictures);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_refreshAllConnections_literal))
			{
				driver()->context()->parse(value, t()->refreshAllConnections);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_defaultThemeVersion_literal))
			{
				driver()->context()->parse(value, t()->defaultThemeVersion.getset());
				return;
			}
		}
		void CT_WorkbookProtection_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_workbookPassword_literal))
			{
				driver()->context()->parse(value, t()->workbookPassword.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_revisionsPassword_literal))
			{
				driver()->context()->parse(value, t()->revisionsPassword.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_lockStructure_literal))
			{
				driver()->context()->parse(value, t()->lockStructure);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_lockWindows_literal))
			{
				driver()->context()->parse(value, t()->lockWindows);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_lockRevision_literal))
			{
				driver()->context()->parse(value, t()->lockRevision);
				return;
			}
		}
		void CT_BookView_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_BookView_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_visibility_literal))
			{
				driver()->context()->parse(value, t()->visibility);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_minimized_literal))
			{
				driver()->context()->parse(value, t()->minimized);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showHorizontalScroll_literal))
			{
				driver()->context()->parse(value, t()->showHorizontalScroll);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showVerticalScroll_literal))
			{
				driver()->context()->parse(value, t()->showVerticalScroll);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showSheetTabs_literal))
			{
				driver()->context()->parse(value, t()->showSheetTabs);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_xWindow_literal))
			{
				driver()->context()->parse(value, t()->xWindow.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_yWindow_literal))
			{
				driver()->context()->parse(value, t()->yWindow.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_windowWidth_literal))
			{
				driver()->context()->parse(value, t()->windowWidth.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_windowHeight_literal))
			{
				driver()->context()->parse(value, t()->windowHeight.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_tabRatio_literal))
			{
				driver()->context()->parse(value, t()->tabRatio);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_firstSheet_literal))
			{
				driver()->context()->parse(value, t()->firstSheet);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_activeTab_literal))
			{
				driver()->context()->parse(value, t()->activeTab);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_autoFilterDateGrouping_literal))
			{
				driver()->context()->parse(value, t()->autoFilterDateGrouping);
				return;
			}
		}
		void CT_BookViews_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_workbookView_literal))
			{
				t()->workbookView.resize(t()->workbookView.size()+1);
				driver()->push(localname, _workbookView_reader.get_reader(&t()->workbookView.back()));
				return;
			}
		}
		void CT_Sheet_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_state_literal))
			{
				driver()->context()->parse(value, t()->state);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
		}
		void CT_Sheets_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_sheet_literal))
			{
				t()->sheet.resize(t()->sheet.size()+1);
				driver()->push(localname, _sheet_reader.get_reader(&t()->sheet.back()));
				return;
			}
		}
		void CT_FunctionGroup_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
		}
		void CT_FunctionGroups_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_functionGroup_literal))
			{
				driver()->push(localname, _functionGroup_reader.get_reader(&t()->functionGroup.getset()));
				return;
			}
		}
		void CT_FunctionGroups_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_builtInGroupCount_literal))
			{
				driver()->context()->parse(value, t()->builtInGroupCount);
				return;
			}
		}
		void CT_ExternalReference_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
		}
		void CT_ExternalReferences_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_externalReference_literal))
			{
				t()->externalReference.resize(t()->externalReference.size()+1);
				driver()->push(localname, _externalReference_reader.get_reader(&t()->externalReference.back()));
				return;
			}
		}
		void CT_DefinedName_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_comment_literal))
			{
				driver()->context()->parse(value, t()->comment.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_customMenu_literal))
			{
				driver()->context()->parse(value, t()->customMenu.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_description_literal))
			{
				driver()->context()->parse(value, t()->description.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_help_literal))
			{
				driver()->context()->parse(value, t()->help.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_statusBar_literal))
			{
				driver()->context()->parse(value, t()->statusBar.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_localSheetId_literal))
			{
				driver()->context()->parse(value, t()->localSheetId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_hidden_literal))
			{
				driver()->context()->parse(value, t()->hidden);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_function_literal))
			{
				driver()->context()->parse(value, t()->function);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_vbProcedure_literal))
			{
				driver()->context()->parse(value, t()->vbProcedure);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_xlm_literal))
			{
				driver()->context()->parse(value, t()->xlm);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_functionGroupId_literal))
			{
				driver()->context()->parse(value, t()->functionGroupId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_shortcutKey_literal))
			{
				driver()->context()->parse(value, t()->shortcutKey.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_publishToServer_literal))
			{
				driver()->context()->parse(value, t()->publishToServer);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_workbookParameter_literal))
			{
				driver()->context()->parse(value, t()->workbookParameter);
				return;
			}
			ST_Formula_reader::read_attribute(uri, localname, qname, value);
		}
		void CT_DefinedNames_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_definedName_literal))
			{
				t()->definedName.resize(t()->definedName.size()+1);
				driver()->push(localname, _definedName_reader.get_reader(&t()->definedName.back()));
				return;
			}
		}
		void CT_CalcPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_calcId_literal))
			{
				driver()->context()->parse(value, t()->calcId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_calcMode_literal))
			{
				driver()->context()->parse(value, t()->calcMode);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_fullCalcOnLoad_literal))
			{
				driver()->context()->parse(value, t()->fullCalcOnLoad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_refMode_literal))
			{
				driver()->context()->parse(value, t()->refMode);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_iterate_literal))
			{
				driver()->context()->parse(value, t()->iterate);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_iterateCount_literal))
			{
				driver()->context()->parse(value, t()->iterateCount);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_iterateDelta_literal))
			{
				driver()->context()->parse(value, t()->iterateDelta);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_fullPrecision_literal))
			{
				driver()->context()->parse(value, t()->fullPrecision);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_calcCompleted_literal))
			{
				driver()->context()->parse(value, t()->calcCompleted);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_calcOnSave_literal))
			{
				driver()->context()->parse(value, t()->calcOnSave);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_concurrentCalc_literal))
			{
				driver()->context()->parse(value, t()->concurrentCalc);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_concurrentManualCount_literal))
			{
				driver()->context()->parse(value, t()->concurrentManualCount.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_forceFullCalc_literal))
			{
				driver()->context()->parse(value, t()->forceFullCalc.getset());
				return;
			}
		}
		void CT_OleSize_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
		}
		void CT_CustomWorkbookView_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CustomWorkbookView_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_guid_literal))
			{
				driver()->context()->parse(value, t()->guid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_autoUpdate_literal))
			{
				driver()->context()->parse(value, t()->autoUpdate);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_mergeInterval_literal))
			{
				driver()->context()->parse(value, t()->mergeInterval.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_changesSavedWin_literal))
			{
				driver()->context()->parse(value, t()->changesSavedWin);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_onlySync_literal))
			{
				driver()->context()->parse(value, t()->onlySync);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_personalView_literal))
			{
				driver()->context()->parse(value, t()->personalView);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_includePrintSettings_literal))
			{
				driver()->context()->parse(value, t()->includePrintSettings);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_includeHiddenRowCol_literal))
			{
				driver()->context()->parse(value, t()->includeHiddenRowCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_maximized_literal))
			{
				driver()->context()->parse(value, t()->maximized);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_minimized_literal))
			{
				driver()->context()->parse(value, t()->minimized);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showHorizontalScroll_literal))
			{
				driver()->context()->parse(value, t()->showHorizontalScroll);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showVerticalScroll_literal))
			{
				driver()->context()->parse(value, t()->showVerticalScroll);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showSheetTabs_literal))
			{
				driver()->context()->parse(value, t()->showSheetTabs);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_xWindow_literal))
			{
				driver()->context()->parse(value, t()->xWindow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_yWindow_literal))
			{
				driver()->context()->parse(value, t()->yWindow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_windowWidth_literal))
			{
				driver()->context()->parse(value, t()->windowWidth);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_windowHeight_literal))
			{
				driver()->context()->parse(value, t()->windowHeight);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_tabRatio_literal))
			{
				driver()->context()->parse(value, t()->tabRatio);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_activeSheetId_literal))
			{
				driver()->context()->parse(value, t()->activeSheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showFormulaBar_literal))
			{
				driver()->context()->parse(value, t()->showFormulaBar);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showStatusbar_literal))
			{
				driver()->context()->parse(value, t()->showStatusbar);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showComments_literal))
			{
				driver()->context()->parse(value, t()->showComments);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_showObjects_literal))
			{
				driver()->context()->parse(value, t()->showObjects);
				return;
			}
		}
		void CT_CustomWorkbookViews_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_customWorkbookView_literal))
			{
				t()->customWorkbookView.resize(t()->customWorkbookView.size()+1);
				driver()->push(localname, _customWorkbookView_reader.get_reader(&t()->customWorkbookView.back()));
				return;
			}
		}
		void CT_PivotCache_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_cacheId_literal))
			{
				driver()->context()->parse(value, t()->cacheId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
		}
		void CT_PivotCaches_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_pivotCache_literal))
			{
				t()->pivotCache.resize(t()->pivotCache.size()+1);
				driver()->push(localname, _pivotCache_reader.get_reader(&t()->pivotCache.back()));
				return;
			}
		}
		void CT_SmartTagPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_embed_literal))
			{
				driver()->context()->parse(value, t()->embed);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_show_literal))
			{
				driver()->context()->parse(value, t()->show);
				return;
			}
		}
		void CT_SmartTagType_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_namespaceUri_literal))
			{
				driver()->context()->parse(value, t()->namespaceUri.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_url_literal))
			{
				driver()->context()->parse(value, t()->url.getset());
				return;
			}
		}
		void CT_SmartTagTypes_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_smartTagType_literal))
			{
				t()->smartTagType.resize(t()->smartTagType.size()+1);
				driver()->push(localname, _smartTagType_reader.get_reader(&t()->smartTagType.back()));
				return;
			}
		}
		void CT_WebPublishing_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_css_literal))
			{
				driver()->context()->parse(value, t()->css);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_thicket_literal))
			{
				driver()->context()->parse(value, t()->thicket);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_longFileNames_literal))
			{
				driver()->context()->parse(value, t()->longFileNames);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_vml_literal))
			{
				driver()->context()->parse(value, t()->vml);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_allowPng_literal))
			{
				driver()->context()->parse(value, t()->allowPng);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_targetScreenSize_literal))
			{
				driver()->context()->parse(value, t()->targetScreenSize);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_dpi_literal))
			{
				driver()->context()->parse(value, t()->dpi);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_codePage_literal))
			{
				driver()->context()->parse(value, t()->codePage.getset());
				return;
			}
		}
		void CT_FileRecoveryPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_autoRecover_literal))
			{
				driver()->context()->parse(value, t()->autoRecover);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_crashSave_literal))
			{
				driver()->context()->parse(value, t()->crashSave);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_dataExtractLoad_literal))
			{
				driver()->context()->parse(value, t()->dataExtractLoad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_repairLoad_literal))
			{
				driver()->context()->parse(value, t()->repairLoad);
				return;
			}
		}
		void CT_WebPublishObject_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_divId_literal))
			{
				driver()->context()->parse(value, t()->divId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_sourceObject_literal))
			{
				driver()->context()->parse(value, t()->sourceObject.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_destinationFile_literal))
			{
				driver()->context()->parse(value, t()->destinationFile);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_title_literal))
			{
				driver()->context()->parse(value, t()->title.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_autoRepublish_literal))
			{
				driver()->context()->parse(value, t()->autoRepublish);
				return;
			}
		}
		void CT_WebPublishObjects_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_webPublishObject_literal))
			{
				t()->webPublishObject.resize(t()->webPublishObject.size()+1);
				driver()->push(localname, _webPublishObject_reader.get_reader(&t()->webPublishObject.back()));
				return;
			}
		}
		void CT_WebPublishObjects_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Workbook_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_fileVersion_literal))
			{
				driver()->push(localname, _fileVersion_reader.get_reader(&t()->fileVersion.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_fileSharing_literal))
			{
				driver()->push(localname, _fileSharing_reader.get_reader(&t()->fileSharing.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_workbookPr_literal))
			{
				driver()->push(localname, _workbookPr_reader.get_reader(&t()->workbookPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_workbookProtection_literal))
			{
				driver()->push(localname, _workbookProtection_reader.get_reader(&t()->workbookProtection.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_bookViews_literal))
			{
				driver()->push(localname, _bookViews_reader.get_reader(&t()->bookViews.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_sheets_literal))
			{
				driver()->push(localname, _sheets_reader.get_reader(&t()->sheets));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_functionGroups_literal))
			{
				driver()->push(localname, _functionGroups_reader.get_reader(&t()->functionGroups.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_externalReferences_literal))
			{
				driver()->push(localname, _externalReferences_reader.get_reader(&t()->externalReferences.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_definedNames_literal))
			{
				driver()->push(localname, _definedNames_reader.get_reader(&t()->definedNames.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_calcPr_literal))
			{
				driver()->push(localname, _calcPr_reader.get_reader(&t()->calcPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_oleSize_literal))
			{
				driver()->push(localname, _oleSize_reader.get_reader(&t()->oleSize.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_customWorkbookViews_literal))
			{
				driver()->push(localname, _customWorkbookViews_reader.get_reader(&t()->customWorkbookViews.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_pivotCaches_literal))
			{
				driver()->push(localname, _pivotCaches_reader.get_reader(&t()->pivotCaches.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_smartTagPr_literal))
			{
				driver()->push(localname, _smartTagPr_reader.get_reader(&t()->smartTagPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_smartTagTypes_literal))
			{
				driver()->push(localname, _smartTagTypes_reader.get_reader(&t()->smartTagTypes.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_webPublishing_literal))
			{
				driver()->push(localname, _webPublishing_reader.get_reader(&t()->webPublishing.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_fileRecoveryPr_literal))
			{
				t()->fileRecoveryPr.resize(t()->fileRecoveryPr.size()+1);
				driver()->push(localname, _fileRecoveryPr_reader.get_reader(&t()->fileRecoveryPr.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_webPublishObjects_literal))
			{
				driver()->push(localname, _webPublishObjects_reader.get_reader(&t()->webPublishObjects.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_workbook_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void sml_workbook_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_workbook_workbook_literal))
			{
				driver()->push(localname, _workbook_reader.get_reader(&t()->workbook.getset()));
				return;
			}
		}
	}
}
