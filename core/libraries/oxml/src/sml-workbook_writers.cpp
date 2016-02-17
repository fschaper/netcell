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


#include "sml-workbook_writers.hpp"
#include "sml-workbook_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_SheetBackgroundPicture_writer::write_target_to(xml_writer& w) {
			w.attribute(sml_workbook_r_literal, sml_workbook_id_literal, context()->serialize(t()->id));
		}

		void CT_FileVersion_writer::write_target_to(xml_writer& w) {
			if (t()->appName.present())
				w.attribute(0, sml_workbook_appName_literal, context()->serialize(t()->appName.get()));
			if (t()->lastEdited.present())
				w.attribute(0, sml_workbook_lastEdited_literal, context()->serialize(t()->lastEdited.get()));
			if (t()->lowestEdited.present())
				w.attribute(0, sml_workbook_lowestEdited_literal, context()->serialize(t()->lowestEdited.get()));
			if (t()->rupBuild.present())
				w.attribute(0, sml_workbook_rupBuild_literal, context()->serialize(t()->rupBuild.get()));
			if (t()->codeName.present())
				w.attribute(0, sml_workbook_codeName_literal, context()->serialize(t()->codeName.get()));
		}

		void CT_FileSharing_writer::write_target_to(xml_writer& w) {
			if (t()->readOnlyRecommended != false)
				w.attribute(0, sml_workbook_readOnlyRecommended_literal, context()->serialize(t()->readOnlyRecommended));
			if (t()->userName.present())
				w.attribute(0, sml_workbook_userName_literal, context()->serialize(t()->userName.get()));
			if (t()->reservationPassword.present())
				w.attribute(0, sml_workbook_reservationPassword_literal, context()->serialize(t()->reservationPassword.get()));
		}

		void CT_WorkbookPr_writer::write_target_to(xml_writer& w) {
			if (t()->date1904 != false)
				w.attribute(0, sml_workbook_date1904_literal, context()->serialize(t()->date1904));
			if (t()->showObjects != ST_Objects::all_literal)
				w.attribute(0, sml_workbook_showObjects_literal, context()->serialize(t()->showObjects));
			if (t()->showBorderUnselectedTables != true)
				w.attribute(0, sml_workbook_showBorderUnselectedTables_literal, context()->serialize(t()->showBorderUnselectedTables));
			if (t()->filterPrivacy != false)
				w.attribute(0, sml_workbook_filterPrivacy_literal, context()->serialize(t()->filterPrivacy));
			if (t()->promptedSolutions != false)
				w.attribute(0, sml_workbook_promptedSolutions_literal, context()->serialize(t()->promptedSolutions));
			if (t()->showInkAnnotation != true)
				w.attribute(0, sml_workbook_showInkAnnotation_literal, context()->serialize(t()->showInkAnnotation));
			if (t()->backupFile != false)
				w.attribute(0, sml_workbook_backupFile_literal, context()->serialize(t()->backupFile));
			if (t()->saveExternalLinkValues != true)
				w.attribute(0, sml_workbook_saveExternalLinkValues_literal, context()->serialize(t()->saveExternalLinkValues));
			if (t()->updateLinks != ST_UpdateLinks::userSet_literal)
				w.attribute(0, sml_workbook_updateLinks_literal, context()->serialize(t()->updateLinks));
			if (t()->codeName.present())
				w.attribute(0, sml_workbook_codeName_literal, context()->serialize(t()->codeName.get()));
			if (t()->hidePivotFieldList != false)
				w.attribute(0, sml_workbook_hidePivotFieldList_literal, context()->serialize(t()->hidePivotFieldList));
			if (t()->showPivotChartFilter != false)
				w.attribute(0, sml_workbook_showPivotChartFilter_literal, context()->serialize(t()->showPivotChartFilter));
			if (t()->allowRefreshQuery != false)
				w.attribute(0, sml_workbook_allowRefreshQuery_literal, context()->serialize(t()->allowRefreshQuery));
			if (t()->publishItems != false)
				w.attribute(0, sml_workbook_publishItems_literal, context()->serialize(t()->publishItems));
			if (t()->checkCompatibility != false)
				w.attribute(0, sml_workbook_checkCompatibility_literal, context()->serialize(t()->checkCompatibility));
			if (t()->autoCompressPictures != true)
				w.attribute(0, sml_workbook_autoCompressPictures_literal, context()->serialize(t()->autoCompressPictures));
			if (t()->refreshAllConnections != false)
				w.attribute(0, sml_workbook_refreshAllConnections_literal, context()->serialize(t()->refreshAllConnections));
			if (t()->defaultThemeVersion.present())
				w.attribute(0, sml_workbook_defaultThemeVersion_literal, context()->serialize(t()->defaultThemeVersion.get()));
		}

		void CT_WorkbookProtection_writer::write_target_to(xml_writer& w) {
			if (t()->workbookPassword.present())
				w.attribute(0, sml_workbook_workbookPassword_literal, context()->serialize(t()->workbookPassword.get()));
			if (t()->revisionsPassword.present())
				w.attribute(0, sml_workbook_revisionsPassword_literal, context()->serialize(t()->revisionsPassword.get()));
			if (t()->lockStructure != false)
				w.attribute(0, sml_workbook_lockStructure_literal, context()->serialize(t()->lockStructure));
			if (t()->lockWindows != false)
				w.attribute(0, sml_workbook_lockWindows_literal, context()->serialize(t()->lockWindows));
			if (t()->lockRevision != false)
				w.attribute(0, sml_workbook_lockRevision_literal, context()->serialize(t()->lockRevision));
		}

		void CT_BookView_writer::write_target_to(xml_writer& w) {
			if (t()->visibility != ST_Visibility::visible_literal)
				w.attribute(0, sml_workbook_visibility_literal, context()->serialize(t()->visibility));
			if (t()->minimized != false)
				w.attribute(0, sml_workbook_minimized_literal, context()->serialize(t()->minimized));
			if (t()->showHorizontalScroll != true)
				w.attribute(0, sml_workbook_showHorizontalScroll_literal, context()->serialize(t()->showHorizontalScroll));
			if (t()->showVerticalScroll != true)
				w.attribute(0, sml_workbook_showVerticalScroll_literal, context()->serialize(t()->showVerticalScroll));
			if (t()->showSheetTabs != true)
				w.attribute(0, sml_workbook_showSheetTabs_literal, context()->serialize(t()->showSheetTabs));
			if (t()->xWindow.present())
				w.attribute(0, sml_workbook_xWindow_literal, context()->serialize(t()->xWindow.get()));
			if (t()->yWindow.present())
				w.attribute(0, sml_workbook_yWindow_literal, context()->serialize(t()->yWindow.get()));
			if (t()->windowWidth.present())
				w.attribute(0, sml_workbook_windowWidth_literal, context()->serialize(t()->windowWidth.get()));
			if (t()->windowHeight.present())
				w.attribute(0, sml_workbook_windowHeight_literal, context()->serialize(t()->windowHeight.get()));
			if (t()->tabRatio != 600U)
				w.attribute(0, sml_workbook_tabRatio_literal, context()->serialize(t()->tabRatio));
			if (t()->firstSheet != 0U)
				w.attribute(0, sml_workbook_firstSheet_literal, context()->serialize(t()->firstSheet));
			if (t()->activeTab != 0U)
				w.attribute(0, sml_workbook_activeTab_literal, context()->serialize(t()->activeTab));
			if (t()->autoFilterDateGrouping != true)
				w.attribute(0, sml_workbook_autoFilterDateGrouping_literal, context()->serialize(t()->autoFilterDateGrouping));
			if (t()->extLst.present()) {
				w.start_element(0, sml_workbook_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_workbook_extLst_literal);
			}
		}

		void CT_BookViews_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->workbookView.size(); ++sqi) {
				w.start_element(0, sml_workbook_workbookView_literal);
				_workbookView_writer.get_writer(context(), &t()->workbookView[sqi])->write_target_to(w);
				w.end_element(0, sml_workbook_workbookView_literal);
			}
		}

		void CT_Sheet_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_workbook_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_workbook_sheetId_literal, context()->serialize(t()->sheetId));
			if (t()->state != ST_SheetState::visible_literal)
				w.attribute(0, sml_workbook_state_literal, context()->serialize(t()->state));
			w.attribute(sml_workbook_r_literal, sml_workbook_id_literal, context()->serialize(t()->id));
		}

		void CT_Sheets_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->sheet.size(); ++sqi) {
				w.start_element(0, sml_workbook_sheet_literal);
				_sheet_writer.get_writer(context(), &t()->sheet[sqi])->write_target_to(w);
				w.end_element(0, sml_workbook_sheet_literal);
			}
		}

		void CT_FunctionGroup_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, sml_workbook_name_literal, context()->serialize(t()->name.get()));
		}

		void CT_FunctionGroups_writer::write_target_to(xml_writer& w) {
			if (t()->builtInGroupCount != 16U)
				w.attribute(0, sml_workbook_builtInGroupCount_literal, context()->serialize(t()->builtInGroupCount));
			if (t()->functionGroup.present()) {
				w.start_element(0, sml_workbook_functionGroup_literal);
				_functionGroup_writer.get_writer(context(), &t()->functionGroup.get())->write_target_to(w);
				w.end_element(0, sml_workbook_functionGroup_literal);
			}
		}

		void CT_ExternalReference_writer::write_target_to(xml_writer& w) {
			w.attribute(sml_workbook_r_literal, sml_workbook_id_literal, context()->serialize(t()->id));
		}

		void CT_ExternalReferences_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->externalReference.size(); ++sqi) {
				w.start_element(0, sml_workbook_externalReference_literal);
				_externalReference_writer.get_writer(context(), &t()->externalReference[sqi])->write_target_to(w);
				w.end_element(0, sml_workbook_externalReference_literal);
			}
		}

		void CT_DefinedName_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_workbook_name_literal, context()->serialize(t()->name));
			if (t()->comment.present())
				w.attribute(0, sml_workbook_comment_literal, context()->serialize(t()->comment.get()));
			if (t()->customMenu.present())
				w.attribute(0, sml_workbook_customMenu_literal, context()->serialize(t()->customMenu.get()));
			if (t()->description.present())
				w.attribute(0, sml_workbook_description_literal, context()->serialize(t()->description.get()));
			if (t()->help.present())
				w.attribute(0, sml_workbook_help_literal, context()->serialize(t()->help.get()));
			if (t()->statusBar.present())
				w.attribute(0, sml_workbook_statusBar_literal, context()->serialize(t()->statusBar.get()));
			if (t()->localSheetId.present())
				w.attribute(0, sml_workbook_localSheetId_literal, context()->serialize(t()->localSheetId.get()));
			if (t()->hidden != false)
				w.attribute(0, sml_workbook_hidden_literal, context()->serialize(t()->hidden));
			if (t()->function != false)
				w.attribute(0, sml_workbook_function_literal, context()->serialize(t()->function));
			if (t()->vbProcedure != false)
				w.attribute(0, sml_workbook_vbProcedure_literal, context()->serialize(t()->vbProcedure));
			if (t()->xlm != false)
				w.attribute(0, sml_workbook_xlm_literal, context()->serialize(t()->xlm));
			if (t()->functionGroupId.present())
				w.attribute(0, sml_workbook_functionGroupId_literal, context()->serialize(t()->functionGroupId.get()));
			if (t()->shortcutKey.present())
				w.attribute(0, sml_workbook_shortcutKey_literal, context()->serialize(t()->shortcutKey.get()));
			if (t()->publishToServer != false)
				w.attribute(0, sml_workbook_publishToServer_literal, context()->serialize(t()->publishToServer));
			if (t()->workbookParameter != false)
				w.attribute(0, sml_workbook_workbookParameter_literal, context()->serialize(t()->workbookParameter));
			ST_Formula_writer::write_target_to(w);
		}

		void CT_DefinedNames_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->definedName.size(); ++sqi) {
				w.start_element(0, sml_workbook_definedName_literal);
				_definedName_writer.get_writer(context(), &t()->definedName[sqi])->write_target_to(w);
				w.end_element(0, sml_workbook_definedName_literal);
			}
		}

		void CT_CalcPr_writer::write_target_to(xml_writer& w) {
			if (t()->calcId.present())
				w.attribute(0, sml_workbook_calcId_literal, context()->serialize(t()->calcId.get()));
			if (t()->calcMode != ST_CalcMode::_auto__literal)
				w.attribute(0, sml_workbook_calcMode_literal, context()->serialize(t()->calcMode));
			if (t()->fullCalcOnLoad != false)
				w.attribute(0, sml_workbook_fullCalcOnLoad_literal, context()->serialize(t()->fullCalcOnLoad));
			if (t()->refMode != ST_RefMode::A1_literal)
				w.attribute(0, sml_workbook_refMode_literal, context()->serialize(t()->refMode));
			if (t()->iterate != false)
				w.attribute(0, sml_workbook_iterate_literal, context()->serialize(t()->iterate));
			if (t()->iterateCount != 100U)
				w.attribute(0, sml_workbook_iterateCount_literal, context()->serialize(t()->iterateCount));
			if (t()->iterateDelta != 0.001)
				w.attribute(0, sml_workbook_iterateDelta_literal, context()->serialize(t()->iterateDelta));
			if (t()->fullPrecision != true)
				w.attribute(0, sml_workbook_fullPrecision_literal, context()->serialize(t()->fullPrecision));
			if (t()->calcCompleted != true)
				w.attribute(0, sml_workbook_calcCompleted_literal, context()->serialize(t()->calcCompleted));
			if (t()->calcOnSave != true)
				w.attribute(0, sml_workbook_calcOnSave_literal, context()->serialize(t()->calcOnSave));
			if (t()->concurrentCalc != true)
				w.attribute(0, sml_workbook_concurrentCalc_literal, context()->serialize(t()->concurrentCalc));
			if (t()->concurrentManualCount.present())
				w.attribute(0, sml_workbook_concurrentManualCount_literal, context()->serialize(t()->concurrentManualCount.get()));
			if (t()->forceFullCalc.present())
				w.attribute(0, sml_workbook_forceFullCalc_literal, context()->serialize(t()->forceFullCalc.get()));
		}

		void CT_OleSize_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_workbook_ref_literal, context()->serialize(t()->ref));
		}

		void CT_CustomWorkbookView_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_workbook_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_workbook_guid_literal, context()->serialize(t()->guid));
			if (t()->autoUpdate != false)
				w.attribute(0, sml_workbook_autoUpdate_literal, context()->serialize(t()->autoUpdate));
			if (t()->mergeInterval.present())
				w.attribute(0, sml_workbook_mergeInterval_literal, context()->serialize(t()->mergeInterval.get()));
			if (t()->changesSavedWin != false)
				w.attribute(0, sml_workbook_changesSavedWin_literal, context()->serialize(t()->changesSavedWin));
			if (t()->onlySync != false)
				w.attribute(0, sml_workbook_onlySync_literal, context()->serialize(t()->onlySync));
			if (t()->personalView != false)
				w.attribute(0, sml_workbook_personalView_literal, context()->serialize(t()->personalView));
			if (t()->includePrintSettings != true)
				w.attribute(0, sml_workbook_includePrintSettings_literal, context()->serialize(t()->includePrintSettings));
			if (t()->includeHiddenRowCol != true)
				w.attribute(0, sml_workbook_includeHiddenRowCol_literal, context()->serialize(t()->includeHiddenRowCol));
			if (t()->maximized != false)
				w.attribute(0, sml_workbook_maximized_literal, context()->serialize(t()->maximized));
			if (t()->minimized != false)
				w.attribute(0, sml_workbook_minimized_literal, context()->serialize(t()->minimized));
			if (t()->showHorizontalScroll != true)
				w.attribute(0, sml_workbook_showHorizontalScroll_literal, context()->serialize(t()->showHorizontalScroll));
			if (t()->showVerticalScroll != true)
				w.attribute(0, sml_workbook_showVerticalScroll_literal, context()->serialize(t()->showVerticalScroll));
			if (t()->showSheetTabs != true)
				w.attribute(0, sml_workbook_showSheetTabs_literal, context()->serialize(t()->showSheetTabs));
			if (t()->xWindow != 0)
				w.attribute(0, sml_workbook_xWindow_literal, context()->serialize(t()->xWindow));
			if (t()->yWindow != 0)
				w.attribute(0, sml_workbook_yWindow_literal, context()->serialize(t()->yWindow));
			w.attribute(0, sml_workbook_windowWidth_literal, context()->serialize(t()->windowWidth));
			w.attribute(0, sml_workbook_windowHeight_literal, context()->serialize(t()->windowHeight));
			if (t()->tabRatio != 600U)
				w.attribute(0, sml_workbook_tabRatio_literal, context()->serialize(t()->tabRatio));
			w.attribute(0, sml_workbook_activeSheetId_literal, context()->serialize(t()->activeSheetId));
			if (t()->showFormulaBar != true)
				w.attribute(0, sml_workbook_showFormulaBar_literal, context()->serialize(t()->showFormulaBar));
			if (t()->showStatusbar != true)
				w.attribute(0, sml_workbook_showStatusbar_literal, context()->serialize(t()->showStatusbar));
			if (t()->showComments != ST_Comments::commIndicator_literal)
				w.attribute(0, sml_workbook_showComments_literal, context()->serialize(t()->showComments));
			if (t()->showObjects != ST_Objects::all_literal)
				w.attribute(0, sml_workbook_showObjects_literal, context()->serialize(t()->showObjects));
			if (t()->extLst.present()) {
				w.start_element(0, sml_workbook_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_workbook_extLst_literal);
			}
		}

		void CT_CustomWorkbookViews_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->customWorkbookView.size(); ++sqi) {
				w.start_element(0, sml_workbook_customWorkbookView_literal);
				_customWorkbookView_writer.get_writer(context(), &t()->customWorkbookView[sqi])->write_target_to(w);
				w.end_element(0, sml_workbook_customWorkbookView_literal);
			}
		}

		void CT_PivotCache_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_workbook_cacheId_literal, context()->serialize(t()->cacheId));
			w.attribute(sml_workbook_r_literal, sml_workbook_id_literal, context()->serialize(t()->id));
		}

		void CT_PivotCaches_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->pivotCache.size(); ++sqi) {
				w.start_element(0, sml_workbook_pivotCache_literal);
				_pivotCache_writer.get_writer(context(), &t()->pivotCache[sqi])->write_target_to(w);
				w.end_element(0, sml_workbook_pivotCache_literal);
			}
		}

		void CT_SmartTagPr_writer::write_target_to(xml_writer& w) {
			if (t()->embed != false)
				w.attribute(0, sml_workbook_embed_literal, context()->serialize(t()->embed));
			if (t()->show != ST_SmartTagShow::all_literal)
				w.attribute(0, sml_workbook_show_literal, context()->serialize(t()->show));
		}

		void CT_SmartTagType_writer::write_target_to(xml_writer& w) {
			if (t()->namespaceUri.present())
				w.attribute(0, sml_workbook_namespaceUri_literal, context()->serialize(t()->namespaceUri.get()));
			if (t()->name.present())
				w.attribute(0, sml_workbook_name_literal, context()->serialize(t()->name.get()));
			if (t()->url.present())
				w.attribute(0, sml_workbook_url_literal, context()->serialize(t()->url.get()));
		}

		void CT_SmartTagTypes_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->smartTagType.size(); ++sqi) {
				w.start_element(0, sml_workbook_smartTagType_literal);
				_smartTagType_writer.get_writer(context(), &t()->smartTagType[sqi])->write_target_to(w);
				w.end_element(0, sml_workbook_smartTagType_literal);
			}
		}

		void CT_WebPublishing_writer::write_target_to(xml_writer& w) {
			if (t()->css != true)
				w.attribute(0, sml_workbook_css_literal, context()->serialize(t()->css));
			if (t()->thicket != true)
				w.attribute(0, sml_workbook_thicket_literal, context()->serialize(t()->thicket));
			if (t()->longFileNames != true)
				w.attribute(0, sml_workbook_longFileNames_literal, context()->serialize(t()->longFileNames));
			if (t()->vml != false)
				w.attribute(0, sml_workbook_vml_literal, context()->serialize(t()->vml));
			if (t()->allowPng != false)
				w.attribute(0, sml_workbook_allowPng_literal, context()->serialize(t()->allowPng));
			if (t()->targetScreenSize != ST_TargetScreenSize::_800x600__literal)
				w.attribute(0, sml_workbook_targetScreenSize_literal, context()->serialize(t()->targetScreenSize));
			if (t()->dpi != 96U)
				w.attribute(0, sml_workbook_dpi_literal, context()->serialize(t()->dpi));
			if (t()->codePage.present())
				w.attribute(0, sml_workbook_codePage_literal, context()->serialize(t()->codePage.get()));
		}

		void CT_FileRecoveryPr_writer::write_target_to(xml_writer& w) {
			if (t()->autoRecover != true)
				w.attribute(0, sml_workbook_autoRecover_literal, context()->serialize(t()->autoRecover));
			if (t()->crashSave != false)
				w.attribute(0, sml_workbook_crashSave_literal, context()->serialize(t()->crashSave));
			if (t()->dataExtractLoad != false)
				w.attribute(0, sml_workbook_dataExtractLoad_literal, context()->serialize(t()->dataExtractLoad));
			if (t()->repairLoad != false)
				w.attribute(0, sml_workbook_repairLoad_literal, context()->serialize(t()->repairLoad));
		}

		void CT_WebPublishObject_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_workbook_id_literal, context()->serialize(t()->id));
			w.attribute(0, sml_workbook_divId_literal, context()->serialize(t()->divId));
			if (t()->sourceObject.present())
				w.attribute(0, sml_workbook_sourceObject_literal, context()->serialize(t()->sourceObject.get()));
			w.attribute(0, sml_workbook_destinationFile_literal, context()->serialize(t()->destinationFile));
			if (t()->title.present())
				w.attribute(0, sml_workbook_title_literal, context()->serialize(t()->title.get()));
			if (t()->autoRepublish != false)
				w.attribute(0, sml_workbook_autoRepublish_literal, context()->serialize(t()->autoRepublish));
		}

		void CT_WebPublishObjects_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_workbook_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->webPublishObject.size(); ++sqi) {
				w.start_element(0, sml_workbook_webPublishObject_literal);
				_webPublishObject_writer.get_writer(context(), &t()->webPublishObject[sqi])->write_target_to(w);
				w.end_element(0, sml_workbook_webPublishObject_literal);
			}
		}

		void CT_Workbook_writer::write_target_to(xml_writer& w) {
			if (t()->fileVersion.present()) {
				w.start_element(0, sml_workbook_fileVersion_literal);
				_fileVersion_writer.get_writer(context(), &t()->fileVersion.get())->write_target_to(w);
				w.end_element(0, sml_workbook_fileVersion_literal);
			}
			if (t()->fileSharing.present()) {
				w.start_element(0, sml_workbook_fileSharing_literal);
				_fileSharing_writer.get_writer(context(), &t()->fileSharing.get())->write_target_to(w);
				w.end_element(0, sml_workbook_fileSharing_literal);
			}
			if (t()->workbookPr.present()) {
				w.start_element(0, sml_workbook_workbookPr_literal);
				_workbookPr_writer.get_writer(context(), &t()->workbookPr.get())->write_target_to(w);
				w.end_element(0, sml_workbook_workbookPr_literal);
			}
			if (t()->workbookProtection.present()) {
				w.start_element(0, sml_workbook_workbookProtection_literal);
				_workbookProtection_writer.get_writer(context(), &t()->workbookProtection.get())->write_target_to(w);
				w.end_element(0, sml_workbook_workbookProtection_literal);
			}
			if (t()->bookViews.present()) {
				w.start_element(0, sml_workbook_bookViews_literal);
				_bookViews_writer.get_writer(context(), &t()->bookViews.get())->write_target_to(w);
				w.end_element(0, sml_workbook_bookViews_literal);
			}
			w.start_element(0, sml_workbook_sheets_literal);
			_sheets_writer.get_writer(context(), &t()->sheets)->write_target_to(w);
			w.end_element(0, sml_workbook_sheets_literal);
			if (t()->functionGroups.present()) {
				w.start_element(0, sml_workbook_functionGroups_literal);
				_functionGroups_writer.get_writer(context(), &t()->functionGroups.get())->write_target_to(w);
				w.end_element(0, sml_workbook_functionGroups_literal);
			}
			if (t()->externalReferences.present()) {
				w.start_element(0, sml_workbook_externalReferences_literal);
				_externalReferences_writer.get_writer(context(), &t()->externalReferences.get())->write_target_to(w);
				w.end_element(0, sml_workbook_externalReferences_literal);
			}
			if (t()->definedNames.present()) {
				w.start_element(0, sml_workbook_definedNames_literal);
				_definedNames_writer.get_writer(context(), &t()->definedNames.get())->write_target_to(w);
				w.end_element(0, sml_workbook_definedNames_literal);
			}
			if (t()->calcPr.present()) {
				w.start_element(0, sml_workbook_calcPr_literal);
				_calcPr_writer.get_writer(context(), &t()->calcPr.get())->write_target_to(w);
				w.end_element(0, sml_workbook_calcPr_literal);
			}
			if (t()->oleSize.present()) {
				w.start_element(0, sml_workbook_oleSize_literal);
				_oleSize_writer.get_writer(context(), &t()->oleSize.get())->write_target_to(w);
				w.end_element(0, sml_workbook_oleSize_literal);
			}
			if (t()->customWorkbookViews.present()) {
				w.start_element(0, sml_workbook_customWorkbookViews_literal);
				_customWorkbookViews_writer.get_writer(context(), &t()->customWorkbookViews.get())->write_target_to(w);
				w.end_element(0, sml_workbook_customWorkbookViews_literal);
			}
			if (t()->pivotCaches.present()) {
				w.start_element(0, sml_workbook_pivotCaches_literal);
				_pivotCaches_writer.get_writer(context(), &t()->pivotCaches.get())->write_target_to(w);
				w.end_element(0, sml_workbook_pivotCaches_literal);
			}
			if (t()->smartTagPr.present()) {
				w.start_element(0, sml_workbook_smartTagPr_literal);
				_smartTagPr_writer.get_writer(context(), &t()->smartTagPr.get())->write_target_to(w);
				w.end_element(0, sml_workbook_smartTagPr_literal);
			}
			if (t()->smartTagTypes.present()) {
				w.start_element(0, sml_workbook_smartTagTypes_literal);
				_smartTagTypes_writer.get_writer(context(), &t()->smartTagTypes.get())->write_target_to(w);
				w.end_element(0, sml_workbook_smartTagTypes_literal);
			}
			if (t()->webPublishing.present()) {
				w.start_element(0, sml_workbook_webPublishing_literal);
				_webPublishing_writer.get_writer(context(), &t()->webPublishing.get())->write_target_to(w);
				w.end_element(0, sml_workbook_webPublishing_literal);
			}
			for (size_t sqi = 0; sqi<t()->fileRecoveryPr.size(); ++sqi) {
				w.start_element(0, sml_workbook_fileRecoveryPr_literal);
				_fileRecoveryPr_writer.get_writer(context(), &t()->fileRecoveryPr[sqi])->write_target_to(w);
				w.end_element(0, sml_workbook_fileRecoveryPr_literal);
			}
			if (t()->webPublishObjects.present()) {
				w.start_element(0, sml_workbook_webPublishObjects_literal);
				_webPublishObjects_writer.get_writer(context(), &t()->webPublishObjects.get())->write_target_to(w);
				w.end_element(0, sml_workbook_webPublishObjects_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_workbook_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_workbook_extLst_literal);
			}
		}

		void sml_workbook_writer::write_target_to(xml_writer& w) {
			if (t()->workbook.present()) {
				w.start_element(0, sml_workbook_workbook_literal);
					w.attribute(0, sml_workbook_xmlns_literal, sml_workbook_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_workbook_xmlns_literal, sml_workbook_r_literal, sml_workbook_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_workbook_xmlns_literal, sml_workbook_xsd_literal, sml_workbook_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_workbook_writer.get_writer(context(), &t()->workbook.get())->write_target_to(w);
				w.end_element(0, sml_workbook_workbook_literal);
			}
		}

	}
}
