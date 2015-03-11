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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: MenuBar.js 5128 2011-07-18 14:31:43Z predragm $
 *
 */

Jedox.wss.app.initMenuBar = function () {

	var menu = Jedox.wss.app.menubar = {},
		rngClearType = Jedox.wss.range.ContentType;

	// Create Menubar and place it in Jedox.wss.app namespace.
    Jedox.wss.app.Menu = new Ext.Toolbar({
    	cls: "extmenubar"
    });

	// Create menu items.
    Jedox.wss.app.Menu.add(

		// ###############
		// #     FILE    #
		// ###############
    	{
			text: "File".localize(),
			cls: "extmenubaritem",
			id: "wMenuBar_file_btn",
			menu: (menu.fileMenu = new Ext.menu.Menu(
				{
			        id: "wMenuBar_file_mn",
			        cls: 'default-format-window',
			        items: [
			           	{text: "New".localize().concat('...'), id: 'wMenuBar_fileNew_btn', iconCls: "icon_new_doc", handler: Jedox.wss.action.newWorkbook},
						{text: "Open".localize().concat('...'), id:'wMenuBar_fileOpen_btn', iconCls: "icon_open_doc", handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.open, ['open']);}},

						{ text: 'Open Recent'.localize(), id: 'wMenuBar_fileRecent_btn',
							menu: {
								items: [],
								cls: 'default-format-window',
								listeners: {
									beforeshow: function ()
									{
										if (this.loaded)
											return true;

										var jwgnrl = Jedox.wss.general;
										Jedox.backend.rpc([ jwgnrl, jwgnrl.showRecent, this, this.parentMenu.activeItem.getEl(), 'tr', this.parentMenu ], 'common', 'fetchRecent', [ 'files', [ 'spreadsheet' ] ]);

										return false;
									}
								}
							}
						},

						{text: "Import".localize().concat('...'), id:'wMenuBar_fileImport_btn', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.importFile);}},
						{text: "Export".localize(), id:'wMenuBar_fileExp_btn', menu: {
								cls: 'default-format-window',
								items: [
									{text: "XLSX".localize(), id:'wMenuBar_fileExpXLSX_btn', iconCls: "icon_file_xlsx", handler: function () { Jedox.wss.action.exportToXLSX(); } },
									{text: "XLSX Snapshot".localize(), id:'wMenuBar_fileExpXLSXS_btn', iconCls: "icon_file_xlsx", handler: function () { Jedox.wss.action.exportToXLSX(true); } },
									{text: "PDF".localize(), id:'wMenuBar_fileExpPDF_btn', iconCls: "icon_file_pdf", handler: Jedox.wss.action.exportToPDF, disabled: !Jedox.wss.app.fopper},
									{text: "HTML".localize(), id:'wMenuBar_fileExpHTML_btn', iconCls: "icon_file_html", handler: Jedox.wss.action.exportToHTML}
								]
							}
						},
						{text: "Quick Publish".localize(), id:'wMenuBar_fileQuickP_btn', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.quickPublish);}},
						{text: "Close".localize(), id:'wMenuBar_fileClose_btn', handler: function() { if (Jedox.wss.wnd.active != null) Jedox.wss.wnd.active.unload(); } },
						"-",
						(menu.saveItem = new Ext.menu.Item({text: "Save".localize(), id:'wMenuBar_fileSave_btn', handler: Jedox.wss.node.save, iconCls: "icon_save_doc"})),
						(menu.saveAsItem = new Ext.menu.Item({text: "Save as".localize().concat('...'), id:'wMenuBar_fileSaveAs_btn', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.open, ['save']);}})),
						//{text: "Save Workspace".localize().concat('...'), disabled: true},
						//{text: "File Search".localize(), disabled: true},
						//"-",
						//{text: "Permission".localize(), disabled: true},
						"-",
						{text: "Page Setup".localize().concat('...'), id:'wMenuBar_filePageStp_btn', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pageSetup);}},
						//{text: "Print Area".localize(), disabled: true},
						//{text: "File Search".localize(), disabled: true},
						{text: "Print Preview".localize(), id:'wMenuBar_filePrintPrv_btn', handler: Jedox.wss.action.exportToHTML}
						//{text: "Print".localize().concat('...'), disabled: true},
						//"-",
						//{text: "Send to".localize(), disabled: true},
						//{text: "Properties".localize(), disabled: true}
			           ],
			    listeners: {
						hide: function () { this.items.get('wMenuBar_fileRecent_btn').menu.loaded = false; }
					}
				}
			))
		},

		// ###############
		// #     EDIT    #
		// ###############
        {
			text: "Edit".localize(),
	        cls: "extmenubaritem",
	        id: "wMenuBar_edit_btn",
			menu: new Ext.menu.Menu({
	        	id: "wMenuBar_edit_mn",
	        	cls: 'default-format-window',
	        	items: [
					(menu.undoItem = new Ext.menu.Item({text: "Undo".localize(), id:'wMenuBar_editUndo_btn', iconCls: 'icon_undo', handler: Jedox.wss.sheet.undo, hidden: true})),
					(menu.redoItem = new Ext.menu.Item({text: "Redo".localize(), id:'wMenuBar_editRedo_btn', iconCls: 'icon_redo', handler: Jedox.wss.sheet.redo, hidden: true})),
					//"-",
					{text: "Cut".localize(), id:'wMenuBar_editCut_btn', iconCls: 'icon_cut', handler: function(){Jedox.wss.action.cut(false);}},
					{text: "Copy".localize(), id:'wMenuBar_editCopy_btn', iconCls: 'icon_copy', handler: function(){Jedox.wss.action.copy(false);}},
					//{text: "WSS Clipboard".localize().concat('...'), disabled: true},
					(menu.paste = new Ext.menu.Item({text: "Paste".localize(), id:'wMenuBar_editPaste_btn', iconCls: 'icon_paste', disabled: true, handler: Jedox.wss.action.paste})),
					(menu.pasteSpec = new Ext.menu.Item({text: "Paste Special".localize().concat('...'), id:'wMenuBar_editPasteSpc_btn', disabled: true, handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pasteSpecial, []);}})),
					//{text: "Paste as Hyperlink".localize(), disabled: true},
					"-",
					//{text: "Fill".localize(), disabled: true},
					{text: "Clear".localize(), id:'wMenuBar_editClear_btn', iconCls: 'icon_clear_all',
						menu: {
							cls: 'default-format-window',
							items: [
							     {text: "Clear All".localize(), id:'wMenuBar_editClrAll_btn', iconCls: 'icon_clear_all', handler: function() {Jedox.wss.action.clear(rngClearType.ALL_CLEAR);}},
							     {text: "Clear Formats".localize(), id:'wMenuBar_editClrFmt_btn', iconCls: 'icon_clear_formats', handler: function() {Jedox.wss.action.clear(rngClearType.STYLE | rngClearType.FORMAT | rngClearType.CNDFMT);}},
							     {text: "Clear Contents".localize(), id:'wMenuBar_editClrCnts_btn', iconCls: 'icon_clear_content', handler: function() {Jedox.wss.action.clear(rngClearType.FORMULA);}}
							]
						}
					},
					(menu.delRow = new Ext.menu.Item({text: "Delete Rows".localize(), id:'wMenuBar_editDltRow_btn', iconCls: 'icon_del_row', handler: function() {Jedox.wss.action.insDelRowCol('del', 'row');}})),
					(menu.delCol = new Ext.menu.Item({text: "Delete Columns".localize(), id:'wMenuBar_editDltCol_btn', iconCls: 'icon_del_col', handler: function() {Jedox.wss.action.insDelRowCol('del', 'col');}})),
					//{text: "Delete Sheet".localize(), disabled: true},
					//{text: "Move or Copy Sheet".localize(), disabled: true},
					"-",
					//{text: "Find".localize().concat('...'), disabled: true},
					//{text: "Replace".concat('...').localize(), disabled: true},
					{text: "Go To".localize().concat('...'), id:'wMenuBar_editGoTo_btn', iconCls:'icon_goto', handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.goTo);}}
					//"-",
					//{text: "Links".localize().concat('...'), disabled: true},
					//{text: "Object".localize(), disabled: true}
				]
	        })
		},

		// ###############
		// #     VIEW    #
		// ###############
        {
			text: "View".localize(),
	        cls: "extmenubaritem",
	        id: "wMenuBar_view_btn",
			menu: new Ext.menu.Menu({
	        	id: "wMenuBar_view_mn",
	        	cls: 'default-format-window',
	        	items: [
					//{text: "Normal".localize(), disabled: true},
					//{text: "Page Break Preview".localize(), disabled: true},
					//"-",
					//{text: "Task Pane".localize(), disabled: true},
					{text: "Toolbars".localize(), id:'wMenuBar_viewTlbr_btn', enableToggle: true, checked: !Jedox.wss.app.initHideToolbar, checkHandler: function(btn, state){Jedox.wss.app.hideShowToolbar(state, '');}},
					{text: "Formula Bar".localize(), id:'wMenuBar_viewFrmlbr_btn', enableToggle: true, checked: !Jedox.wss.app.initHideFormulaBar, checkHandler: function(btn, state){Jedox.wss.app.hideShowFormulaBar(state);}},
					{text: "Status Bar".localize(), id:'wMenuBar_viewStsbr_btn', enableToggle: true, checked: !Jedox.wss.app.initHideStatusBar, checkHandler: function(btn, state){Jedox.wss.app.statusBar.hideShow(state);}},
					"-",
					(menu.hbQuickView = new Ext.menu.CheckItem({text: "Quick View".localize(), id:'wMenuBar_viewQuickV_btn', enableToggle: true, checked: false, checkHandler: Jedox.wss.hb.run})),
					(menu.userModeView = new Ext.menu.Item({text: "User Mode".localize(), id:'wMenuBar_viewUserMd_btn', handler: Jedox.wss.app.openViewMode}))
//					,"-",
//					{
//						text: "Theme".localize(),
//						iconCls: "res/img/bar/ico_theme.png",
//						menu: (menu.themeMenu = new Ext.menu.Menu({
//							items: [
//									{text: "Blue (default)".localize(), id: 'theme-default', enableToggle: true, checked: true, checkHandler: Jedox.wss.action.switchTheme},
//									{text: "Gray".localize(), id: 'theme-gray', enableToggle: true, checked: false, checkHandler: Jedox.wss.action.switchTheme}
//								]
//						}))
//					}
					//{text: "Header and Footer".localize().concat('...'), disabled: true},
					//{text: "Comments".localize(), disabled: true},
					//"-",
					//{text: "Custom View".localize().concat('...'), disabled: true},
					//{text: "Full Screen".localize(), disabled: true},
					//{text: "Zoom".localize().concat('...'), disabled: true}
				]
	        })
		},

		// ##############
		// #   INSERT   #
		// ##############
        {
			text: "Insert".localize(),
	        cls: "extmenubaritem",
	        id: "wMenuBar_insert_btn",
			menu: new Ext.menu.Menu({
	        	id: "wMenuBar_insert_mn",
	        	cls: 'default-format-window',
	        	items: [
					(menu.insRow = new Ext.menu.Item({text: "Rows".localize(), id:'wMenuBar_insertRows_btn', iconCls: 'icon_ins_row', handler: function() {Jedox.wss.action.insDelRowCol('ins', 'row');}})),
					(menu.insCol = new Ext.menu.Item({text: "Columns".localize(), id:'wMenuBar_insertColumns_btn', iconCls: 'icon_ins_col', handler: function() {Jedox.wss.action.insDelRowCol('ins', 'col');}})),
					{text: "Worksheet".localize(), id:'wMenuBar_insertWrkSht_btn', iconCls: 'icon_ins_sheet', handler: function(){Jedox.wss.app.activeBook.getSheetSelector().addSheet();}},
					{text: "Chart".localize().concat('...'), id:'wMenuBar_insertChart_btn', handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.chart, ['insert', 0]);}, iconCls: "icon_insert_chart"},
					{text: "Micro Chart".localize().concat('...'), id:'wMenuBar_insertMChart_btn', handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.openMicroChart);},iconCls: "icon_insert_chart"},

					//{text: "Symbol".localize().concat('...'), disabled: true},
					"-",
					//{text: "Page Break".localize(), disabled: true},
					{text: "Function".localize().concat('...'), id:'wMenuBar_insertFnc_btn', iconCls: 'icon_ins_func', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.insertFunction, [{id:'fbar', fn:null}, Jedox.wss.app.currFormula.getValue()]);}},
					{text: "Name".localize(), id:'wMenuBar_insertName_btn', iconCls: 'icon_name_mgr', handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.nameManager);}},
					//{text: "Comment".localize(), disabled: true},
					"-",
					{text: "Picture".localize(), id:'wMenuBar_insertPct_btn', iconCls: 'icon_ins_picture', handler: function() {Jedox.wss.dlg.openInsertPicture();}},

					//{text: "Picture".localize().concat('...'), iconCls: 'icon_ins_picture', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.insertPicture);}},

					//{text: "Diagram".localize().concat('...'), disabled: true},
					//{text: "Object".localize().concat('...'), disabled: true},
					{text: "Hyperlink".localize().concat('...'), id:'wMenuBar_insertHLink_btn', iconCls: 'icon_insert_hyperlink', handler: function() {var	env = Jedox.wss.app.environment, selCoord = env.selectedCellCoords; Jedox.gen.load(Jedox.wss.app.dynJSRegistry.openHL, [{defName: Jedox.wss.general.filterHLTags(selCoord[0], selCoord[1], env.selectedCellValue, false), handlers:{scope: Jedox.wss.hl, set: Jedox.wss.hl.set}}]);}}
				]
	        })
		},

		// ##############
		// #   FORMAT   #
		// ##############
        {
			text: "Format".localize(),
	        cls: "extmenubaritem",
	        id: "wMenuBar_format_btn",
			menu: new Ext.menu.Menu({
	        	id: "wMenuBar_format_mn",
	        	cls: 'default-format-window',
	        	items: [
					{text: "Cells".localize().concat('...'), id: "wMenuBar_formatCells_btn", iconCls: 'icon_edit', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatCells);}},
					'-',
					{text: "Row Height".localize().concat('...'), id:'wMenuBar_formatRHeight_btn', iconCls: 'icon_row_height', handler: function() {
						Jedox.gen.load(
							Jedox.wss.app.dynJSRegistry.formatColRow,
							[Jedox.wss.grid.headerType.ROW, Jedox.wss.sheet.getColRowSize(Jedox.wss.grid.headerType.ROW)]
						);}
					},
					{text: "Autofit Row Height".localize(), id:'wMenuBar_formatARHeight_btn', handler: function() {Jedox.wss.action.resizeRowCol(Jedox.wss.grid.headerType.ROW);}},
					'-',
					{text: "Column Width".localize().concat('...'), id:'wMenuBar_formatCWidth_btn', iconCls: 'icon_col_width', handler: function() {
						Jedox.gen.load(
							Jedox.wss.app.dynJSRegistry.formatColRow,
							[Jedox.wss.grid.headerType.COLUMN, Jedox.wss.sheet.getColRowSize(Jedox.wss.grid.headerType.COLUMN)]
						);}
					},
					{text: "Autofit Column Width".localize(), id:'wMenuBar_formatACWidth_btn', handler: function() {Jedox.wss.action.resizeRowCol(Jedox.wss.grid.headerType.COLUMN);}},
					'-',
					//{text: "Sheet".localize(), disabled: true},
					{text: "Merge Cells".localize(), id:'wMenuBar_formatMrgC_btn', iconCls: 'icon_merge_cells', handler: function(){Jedox.wss.action.mergeCells(false);}},
					{text: "Unmerge Cells".localize(), id:'wMenuBar_formatUMrgC_btn', iconCls: 'icon_unmerge_cells', handler: function(){Jedox.wss.action.mergeCells(true);}},
					"-",
					//{text: "AutoFormat".localize().concat('...'), disabled: true},
					{text: "Conditional Formatting".localize(), id:'wMenuBar_formatCndFmt_btn', iconCls: "icon_conditional_fmt",
						menu: {
							id:'wMenuBar_formatCndFmt_mn',
							cls: 'default-format-window',
							items: [
								{text: "New Rule".localize().concat('...'), id:'wMenuBar_formatCndFmtNR_btn', iconCls: "icon_cnd_new", handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.conditionalFormatting);}},
								{text: "Clear Rules".localize(), id:'wMenuBar_formatCndFmtCR_btn', iconCls: "icon_cnd_clear",
									menu: {
										id:'wMenuBar_formatCndFmtCR_mn',
										cls: 'default-format-window',
										items: [
											{text: "Clear Rules from Selected Cells".localize(), id:'wMenuBar_formatCndFmtCRSC_btn', handler: function(){Jedox.wss.cndfmt.remove(Jedox.wss.cndfmt.SCOPE_CURR_SEL);}},
											{text: "Clear Rules from Entire Sheet".localize(), id:'wMenuBar_formatCndFmtCRES_btn', handler: function(){Jedox.wss.cndfmt.remove(Jedox.wss.cndfmt.SCOPE_CURR_WKS);}}
										]
									}
								},
								{text: "Manage Rules".localize().concat('...'), id:'wMenuBar_formatCndFmtMR_btn', iconCls: "icon_cnd_manage", handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.manageConditionalFormatting);}}
					]
						}
					}
					//{text: "Style".localize().concat('...'), disabled: true}
				]
	        })
		},

		// ###############
		// #     PALO    #
		// ###############
        {
			text: "Palo".localize(),
	        cls: "extmenubaritem",
	        id: "wMenuBar_palo_btn",
			menu: new Ext.menu.Menu({
	        	id: "wMenuBar_palo_mn",
	        	cls: 'default-format-window',
	        	items: [
					{text: "Paste View".localize().concat('...'), id:'wMenuBar_paloPasteV_btn', iconCls: 'icon_palo_pasteview', handler: function(){ Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pasteView);}},
					"-",
					{text: "Paste Elements".localize().concat('...'), id:'wMenuBar_paloPasteE_btn', iconCls: 'icon_palo_pasteelements', handler: function(){ Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectElements);}},
					{text: "Paste Subset".localize().concat('...'), id:'wMenuBar_paloPasteS_btn', iconCls: 'icon_palo_pastesubset', handler: function(){ Jedox.gen.load(Jedox.wss.app.dynJSRegistry.subsetEditor);}},
					{text: "Paste Data Function".localize().concat('...'), id:'wMenuBar_paloPasteDF_btn', iconCls: 'icon_palo_pastedatafn', handler: function(){ Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pasteDataFunctions);}}
					//,
					//"-",
					//{text: "Modeller".localize().concat('...'), iconCls: 'icon_palo_modeller', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.modeller);}},
					//{text: "Data Import".localize().concat('...'), iconCls: 'icon_palo_dataimport', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.paloImport);}},
					//{text: "Save as Snapshot".localize().concat('...'), iconCls: 'icon_palo_saveassnap', disabled: true}
					//"-",
					//{text: "WikiPalo".localize(), iconCls: 'icon_palo_wiki', handler:function(){window.open("http://wikipalo.com/site.php?id=palo" ,"_blank")}}
					//{text: "Palo Wizard".localize().concat('...'), handler: function(){ var paloWizard = new Jedox.palo.PaloWizard(); paloWizard.init(); paloWizard.show(); } }
					//"-",
					//{text: "About".localize().concat('...'), iconCls: 'res/img/menu/ico_palo_meni_about.png', disabled : true }
				]
	        })
		},

		// ###############
		// #     DATA    #
		// ###############
        {
			text: "Data".localize(),
	        cls: "extmenubaritem",
	        id: "wMenuBar_data_btn",
			menu: new Ext.menu.Menu({
	        	id: "wMenuBar_data_mn",
	        	cls: 'default-format-window',
	        	items: [
	        	    /*
					{text: "Sort".localize().concat('...'), disabled: true},
					{text: "Filter".localize(), disabled: true},
					{text: "Form".localize().concat('...'), disabled: true},
					{text: "Subtotals".localize().concat('...'), disabled: true},
					{text: "Validation".localize().concat('...'), disabled: true},
					"-",
					{text: "Table".localize().concat('...'), disabled: true},
					{text: "Text to Columns".localize().concat('...'), disabled: true},
					{text: "Consolidate".localize().concat('...'), disabled: true},
					{text: "Group and Outline".localize(), disabled: true},
					"-",
					{text: "Import External Data".localize(), disabled: true},
					{text: "List".localize(), disabled: true},
					{text: "XML".localize(), disabled: true},
					"-",
					*/
					  { text: 'Refresh Data'.localize(), id:'wMenuBar_dataRDt_btn', handler: function () { Jedox.wss.sheet.refresh(); } }
					, { text: 'Auto-Refresh Data'.localize(), id: 'wMenuBar_dataARDt_btn', enableToggle: true, checked: false,
							checkHandler: function () { this.checked ? Jedox.gen.load(Jedox.wss.app.dynJSRegistry.autoRefreshStart) : Jedox.wss.book.autoRefresh(0); }
						}
					, '-'
					, { text: 'Auto-Calculate Data'.localize(), id: 'wMenuBar_dataACDt_btn', enableToggle: true, checked: false,
							checkHandler: function () { Jedox.wss.general.autoCalc(this.checked); }
						}
					, '-'
					, { text: 'Variables'.localize(), id: 'wMenuBar_dataVariables_btn', iconCls: 'icon_variables',
						handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.privateVars);}}
					],
				listeners: {
					beforeshow: function ()
					{
						var aBook = Jedox.wss.app.activeBook;
						this.items.get('wMenuBar_dataARDt_btn').setChecked(aBook && aBook._autoRefresh > 0, true);

						this.items.get('wMenuBar_dataACDt_btn').setChecked(Jedox.wss.app.autoCalc, true);
					}
				}
	        })
		},

		// ################
		// #     TOOLS    #
		// ################
        {
			text: "Tools".localize(),
	        cls: "extmenubaritem",
	        id: "wMenuBar_tools_btn",
			menu: new Ext.menu.Menu({
	        	id: "ToolsMenu",
	        	cls: 'default-format-window',
	        	items: [
	        	    /*
					{text: "Spelling".localize().concat('...'), disabled: true},
					{text: "Research".localize().concat('...'), disabled: true},
					{text: "Error Checking".localize().concat('...'), disabled: true},
					"-",
					{text: "Shared Workspace".localize().concat('...'), disabled: true},
					{text: "Share Workbook".localize().concat('...'), disabled: true},
					{text: "Track Changes".localize(), disabled: true},
					{text: "Compare and Merge Workbooks".localize(), disabled: true},
					{text: "Online Collaboration".localize(), disabled: true},
					"-",
					{text: "Goal Seek".localize().concat('...'), disabled: true},
					{text: "Scenarios".localize().concat('...'), disabled: true},
					{text: "Formula Auditing".localize(), disabled: true},
					"-",
					*/
			        {
			        	text: "DynaRanges".localize(),
			        	id:'wMenuBar_toolsDynaR_btn',
			        	iconCls: 'icon_dynaranges',
			        	menu: {
							cls: 'default-format-window',
							items: [
								(menu.newHBVert = new Ext.menu.Item({id: 'wMenuBar_newHBVert_btn', text: "Vertical DynaRange".localize(), iconCls: 'icon_vert_dynarange', handler: Jedox.wss.hb.addDynarange})),
								(menu.newHBHoriz = new Ext.menu.Item({id: 'wMenuBar_newHBHoriz_btn', text: "Horizontal DynaRange".localize(), iconCls: 'icon_hor_dynarange', handler: Jedox.wss.hb.addDynarange}))
							]
						}
			        },
			        "-",
			        {text: "Form Elements".localize(), id:'wMenuBar_toolsFrmEl_btn', iconCls: 'icon_form_elems', menu:
								{
			        				id:'wMenuBar_toolsFrmEl_mn',
			        				cls: 'default-format-window',
			        				items: [
										{text: "ComboBox".localize().concat('...'), id:'wMenuBar_toolsCmb_btn', iconCls: 'icon_form_combo', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatControl, [{type: Jedox.wss.wsel.type.COMBO_BOX}]);}}
										, {text: "CheckBox".localize().concat('...'), id:'wMenuBar_toolsChb_btn', iconCls: 'icon_form_checkbox', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatControl, [{type: Jedox.wss.wsel.type.CHECK_BOX}]);}}
										, {text: "Button".localize().concat('...'), id:'wMenuBar_toolsBtn_btn', iconCls: 'icon_form_button', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatControl, [{type: Jedox.wss.wsel.type.BUTTON}]);}}
									]
								}
							},
							{text: "Macros".localize(), id:'wMenuBar_toolsMcrs_btn', iconCls: 'icon_macro', menu:
								{
									id:'wMenuBar_toolsMcrs_mn',
									cls: 'default-format-window',
									items: [
										{text: "Macro Editor".localize().concat('...'), id:'wMenuBar_toolsMcrsE_btn', iconCls: 'icon_macro_editor', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.editMacro);}}
									]
								}
							}
							//,
							/*
							{text: "Add-Ins".localize().concat('...'), disabled: true},
							{text: "AutoCorrect Options".localize().concat('...'), disabled: true},
							{text: "Customize".localize().concat('...'), disabled: true},
							*/
							//'-',
							//{text: "Options".localize().concat('...'), disabled: true}
						]
			        })
		},

		// ###############
		// #   WINDOW    #
		// ###############
        {
			text: "Window".localize(),
	        cls: "extmenubaritem",
	        id: "wMenuBar_window_btn",
			menu: (menu.windowMenu = new Ext.menu.Menu(
				{
					id: 'wMenuBar_window_mn',
					cls: 'default-format-window',
					items: [
						// { text: 'New Window'.localize(), disabled: true },
						{ text: 'Arrange'.localize().concat('...'), id:'wMenuBar_windowArr_btn', handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.arrangeWindows); } },
						// { text: 'Compare Side by Side with'.localize().concat('...'), disabled: true },
						{ text: 'Hide'.localize(), id:'wMenuBar_windowHd_btn', handler: function() { Jedox.wss.wnd.hideActive(); } },
						{ text: 'Unhide'.localize().concat('...'), id:'wMenuBar_windowUhd_btn', handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.unhideWindow); } },
						'-'
					],
					listeners: {
						beforeshow: function ()
						{
							var wndReg = Jedox.wss.wnd.reg,
									lnks = this.find('_lnk', ''),
									cnt = 0;

							for (var i = lnks.length - 1; i >= 0; --i)
								this.remove(lnks[i]);

							for (var id in wndReg)
								this.addMenuItem({ _lnk: '', _id: id, text: ''.concat(++cnt, '. ', wndReg[id].getName()), handler: function (item) { Jedox.wss.wnd.selectById(item.initialConfig._id); } });
						}
					}
				}
			))
		},

		// ###############
		// #     HELP    #
		// ###############
        {
			text: "Help".localize(),
	        cls: "extmenubaritem",
	        id: "wMenuBar_help_btn",
			menu: new Ext.menu.Menu({
	        	id: "wMenuBar_help_mn",
	        	cls: 'default-format-window',
	        	items: [
					//{text: "Worksheet-Server Help".localize(), disabled: true},
					//"-",
	//				{text: "Jedox Online".localize(), href: "http://www.jedox.com"},
					{text: "Jedox Online".localize(), id:'wMenuBar_helpJ_btn', handler:function(){window.open("http://www.jedox.com" ,"_blank")}}
					//{text: "Contact us".localize(), disabled: true},
					//"-",
					//{text: "Check for Updates".localize(), disabled: true},
					//{text: "Customer Feedback Options".localize(), disabled: true},
					//"-",
					//{text: "About Palo Suite".localize(), disabled: true}
				]
	        })
		}
	);

	Jedox.wss.app.Menu.render("MenuPlaceholder");
}