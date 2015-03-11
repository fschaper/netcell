/*
 * @brief ajax
 *
 * @file Group.js
 *
 * Copyright (C) 2006-2009 Jedox AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (Version 2) as published
 * by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may obtain a copy of the License at
 *
 * <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *   http://www.jedox.com/license_palo_bi_suite.txt
 * </a>
 *
 * If you are developing and distributing open source applications under the
 * GPL License, then you are free to use Palo under the GPL License.  For OEMs,
 * ISVs, and VARs who distribute Palo with their products, and do not license
 * and distribute their source code under the GPL, Jedox provides a flexible
 * OEM Commercial License.
 *
 * \author
 * Srdjan Vukadinovic <srdjan.vukadinovic.com>
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: dynJSRegistry.js 4310 2010-11-18 07:52:20Z mladent $
 *
 */

Jedox.wss.app.dynJSRegistry = {
// name: [filename, [folder, subfolder, subsubfolder], function_to_call ('' if nothing to call), autoload_on_startup, loaded, base_folder, base_namespace]
	formatCells: ['Format.js', ['dlg'], 'formatCells', false, false, 'base', 'wss'],
	chart: ['InsertChart.js', ['dlg', 'chart'], 'openChartDialog', false, false, 'base', 'wss'],
	editChart: ['EditChart.js', ['dlg', 'chart'], 'editChartDialog', false, false, 'base', 'wss'],
	editChartType: ['EditChartType.js', ['dlg', 'chart'], 'editChartTypeDialog', false, false, 'base', 'wss'],
	editSourceData: ['EditSourceData.js', ['dlg', 'chart'], 'editSourceDataDialog', false, false, 'base', 'wss'],
	editMacro:['EditMacro.js', ['dlg'], 'openEditMacro', false, false, 'base', 'wss'],
	insertMacro:['InsertMacro.js', ['dlg'], 'openInsertMacro', false, false, 'base', 'wss'],
	find:['Find.js', ['dlg'], 'openFindDialog', false, false, 'base', 'wss'],
	open: ['Open.js', ['dlg'], 'openOpenDialog', false, false, 'base', 'wss'],
	insertFunction: ['InsertFunction.js', ['dlg'], 'openInsertFunctionDialog', false, false, 'base', 'wss'],
	conditionalFormatting: ['ConditionalFormatting.js', ['dlg'], 'openConditionalFormatting', false, false, 'base', 'wss'],
	manageConditionalFormatting:['ManageConditionalFmt.js', ['dlg'], 'manageConditionalFormatting', false, false, 'base', 'wss'],
	formatColRow:['FormatColRow.js', ['dlg'], 'openFormatColRow', false, false, 'base', 'wss'],
	importFile: ['Import.js', ['dlg'], 'openImportDialog', false, false, 'base', 'wss'],
	openMicroChart: ['Microchart.js', ['dlg', 'chart'], 'openMicroChart', false, false, 'base', 'wss'],
	manageDynarange:['Dynarange.js', ['dlg'], 'openDynarange', false, false, 'base', 'wss'],
	sheetMoveCopy:['SheetMoveCopy.js', ['dlg'], 'openSheetMoveCopy', false, false, 'base', 'wss'],
	nameManager:['NameManager.js', ['dlg'], 'openNameManager', false, false, 'base', 'wss'],
	newName:['NewName.js', ['dlg'], 'openNewName', false, false, 'base', 'wss'],
	selectRange:['SelectRange.js', ['dlg'], 'openSelectRangeDialog', false, false, 'base', 'wss'],
	renameSheet:['RenameSheet.js', ['dlg'], 'openRenameSheet', false, false, 'base', 'wss'],
	pageSetup:['PageSetup.js', ['dlg'], 'openPageSetup', false, false, 'base', 'wss'],
	customHeaderFooter:['CustomHeaderFooter.js', ['dlg'], 'openCustomHeaderFooter', false, false, 'base', 'wss'],
	arrangeWindows:['ArrangeWindows.js', ['dlg'], 'openArrangeWindows', false, false, 'base', 'wss'],
	unhideWindow:['UnhideWindow.js', ['dlg'], 'openUnhideDialog', false, false, 'base', 'wss'],
	paloTextEditor:['CellTextEditor.js', ['palo'], 'openCellTE', false, false, 'base', 'wss'],
//	modeller:['Modeller.js', ['palo'], 'openModellerDialog', false, false, '../common/base', ''],
//	cubeWizard:['CubeWizard.js', ['palo'], 'openCubeWizard', false, false, '../common/base', ''],
//	paloWizard:['PaloWizard.js', ['palo'], 'openPaloWizard', false, false, '../common/base', ''],
//	ruleEditor:['RuleEditor.js', ['palo'], 'ruleEditor', false, false, '../common/base', ''],
	subsetEditor:['SubsetEditor.js', ['palo'], 'openSubsetEditor', false, false, '../common/base', ''],
	chooseElement:['ChooseElement.js', ['palo'], 'openChooseElement', false, false, '../common/base', ''],
	pasteView:['PasteView.js', ['palo'], 'PasteView', false, false, 'base', 'wss'],
	selectElements:['SelectElements.js', ['palo'], 'SelectElements', false, false, 'base', 'wss'],
	pasteDataFunctions:['PasteFuncs.js', ['palo'], 'PasteDataFunctions', false, false, 'base', 'wss'],
	paloImport:['PaloImport.js', ['palo'], 'openPaloImport', false, false, 'base', 'wss'],
	openHL:['InsertHyperlink.js', ['dlg'], 'openHL', false, false, 'base', 'wss'],
	hlVarList:['HlVarList.js', ['dlg'], 'hlVarList', false, false, 'base', 'wss'],
	funcArgs:['FuncArgs.js', ['dlg'], 'funcArgs', false, false, 'base', 'wss'],
	formatControl:['FormatControl.js', ['dlg'], 'formatControl', false, false, 'base', 'wss'],
	pasteSpecial:['PasteSpecial.js', ['dlg'], 'openPasteSpecial', false, false, 'base', 'wss'],
	autoRefreshStart:['AutoRefresh.js', ['dlg'], 'autoRefreshStart', false, false, 'base', 'wss'],
	quickPublish: ['QuickPublish.js', ['dlg'], 'quickPublish', false, false, 'base', 'wss'],
	recover: ['Recover.js', ['dlg'], 'openRecoverDialog', false, false, 'base', 'wss'],
	goTo:['GoTo.js', ['dlg'], 'openGoTo', false, false, 'base', 'wss'],
	privateVars: ['PrivateVars.js', ['dlg'], 'privateVars', false, false, 'base', 'wss'],
	pictureProperties: ['PictureProperties.js', ['dlg'], 'openPictureProperties', false, false, 'base', 'wss'],
	openConstListEditorWin:['ConstListEditorWin.js', ['dlg'], 'openConstListEditorWin', false, false, '../common/base', ''],

//	FORMATTING CLASSES
	formatFont: ['Font.js', ['dlg', 'format'], 'font', false, false, 'base', 'wss'],
	formatNumber: ['Number.js', ['dlg', 'format'], 'number', false, false, 'base', 'wss'],
	formatAlignment: ['Alignment.js', ['dlg', 'format'], 'alignment', false, false, 'base', 'wss'],
	formatBorder: ['Border.js', ['dlg', 'format'], 'border', false, false, 'base', 'wss'],
	formatFill: ['Fill.js', ['dlg', 'format'], 'fill', false, false, 'base', 'wss'],
	formatProtection: ['Protection.js', ['dlg', 'format'], 'protection', false, false, 'base', 'wss'],
	moreColors: ['MoreColors.js', ['dlg', 'format'], 'moreColors', false, false, 'base', 'wss'],

//	FORM ELEMENTS AND WIDGETS CLASSES
	fwSource: ['Source.js', ['dlg', 'control'], 'source', false, false, 'base', 'wss'],
	fwTarget: ['Target.js', ['dlg', 'control'], 'target', false, false, 'base', 'wss'],
	fwContent: ['Content.js', ['dlg', 'control'], 'content', false, false, 'base', 'wss'],

//	Size & Positioning panel for floating elements
	FESizePositionPanel: ['SizePosPanel.js', ['dlg'], 'FESizePos', false, false, 'base', 'wss']
}