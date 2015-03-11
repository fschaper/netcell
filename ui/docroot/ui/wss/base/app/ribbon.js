/*
 * @brief ajax
 *
 * @file ribbon.js
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: ribbon.js 5118 2011-07-15 13:52:41Z drazenk $
 *
 */

Jedox.wss.app.initRibbon = function () {

	var ribbonButtonTemplate = new Ext.Template('<table id="{4}" cellspacing="0" class="x-btn {3}"><tbody class="{1}">',
			'<tr><td class="x-btn-tl"><i>&#160;</i></td><td class="x-btn-tc"></td><td class="x-btn-tr"><i>&#160;</i></td></tr>',
			'<tr><td class="x-btn-ml"><i>&#160;</i></td><td class="x-btn-mc">',
			'<em class="{2}" unselectable="on"><button type="{0}"></button></em>',
			'</td><td class="x-btn-mr"><i>&#160;</i></td></tr>',
			'<tr><td class="x-btn-bl"><i>&#160;</i></td><td class="x-btn-bc"></td><td class="x-btn-br"><i>&#160;</i></td></tr>',
			'</tbody></table>');

	var ribbon = Jedox.wss.app.toolbar = {};
	var rngClearType = Jedox.wss.range.ContentType;

	// Ribon Tabs.

	// ###############
	// #     HOME    #
	// ###############
   var home =  new Ext.Panel({
        title: 'Home'.localize(),
        tbar: new Ext.Toolbar({
			enableOverflow: true,
        	items: [{
            xtype: 'buttongroup',
            columns: 3,
            title: 'File'.localize(),
			height:90,
            items: [new Ext.Button({
                text: 'New<br>document'.localize(),
                scale: 'large',
                rowspan: 3,
                ctCls: 'ribbonButtons',
                iconCls: 'new-icon32',
                iconAlign: 'top',
				width:40,
				tooltip: "Create new document".localize(),
				handler: Jedox.wss.action.newWorkbook
				//,template: ribbonButtonTemplate
            }),{
                text: 'Open'.localize(), iconCls: 'open-icon',
				tooltip: "Open document".localize(),
				 handler: function(){
				 	Jedox.gen.load(Jedox.wss.app.dynJSRegistry.open, ['open']);
				}
            },{
                xtype:'splitbutton',
				text: 'Recent'.localize(), id: 'openRecentMenu',
				iconCls: 'open-recent-icon',
				menu: {
					items: [],
					listeners: {
						beforeshow: function ()
						{
							if (this.loaded)
								return true;

							var jwgnrl = Jedox.wss.general;
							Jedox.backend.rpc([ jwgnrl, jwgnrl.showRecent, this, Ext.get('openRecentMenu'), 'bl' ], 'common', 'fetchRecent', [ 'files', 'spreadsheet' ]);

							return false;
						},
						hide: function () { this.loaded = false; }
					}
				}
            },
			(ribbon.saveItem = new Ext.Toolbar.Button({text: 'Save'.localize(), iconCls: 'save-icon', tooltip: "Save document".localize(), handler: Jedox.wss.node.save})),
			(ribbon.saveAsItem = new Ext.Toolbar.Button({text: 'Save as'.localize(), iconCls: 'saveas-icon', tooltip: "Save As document".localize(), handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.open, ['save']);}})),
			{
                text: 'Import'.localize(),
				iconCls:'import-icon',
				handler: function(){
					Jedox.gen.load(Jedox.wss.app.dynJSRegistry.importFile);
				}
            },{
                xtype:'splitbutton',
				text: 'Export'.localize(),
				iconCls:'export-icon',
				menu: {
					items: [{
						text: "XLSX".localize(),
						iconCls: "icon_file_xlsx",
						handler: function () { Jedox.wss.action.exportToXLSX(); }
					}, {
						text: "XLSX Snapshot".localize(),
						iconCls: "icon_file_xlsx",
						handler: function () { Jedox.wss.action.exportToXLSX(true); }
					}, {
						text: "PDF".localize(),
						iconCls: "icon_file_pdf",
						handler: Jedox.wss.action.exportToPDF,
						disabled: !Jedox.wss.app.fopper
					}, {
						text: "HTML".localize(),
						iconCls: "icon_file_html",
						handler: Jedox.wss.action.exportToHTML
					}]
				}
            }
//            {
//                text: 'Close'.localize(),
//				iconCls: 'close-icon',
//				handler: function() {
//					if (Jedox.wss.wnd.active != null)
//						Jedox.wss.wnd.active.unload();
//				}
//            }
		]
        },{
            xtype: 'buttongroup',
            columns: 3,
            title: 'Operation'.localize(),
			bodyStyle: 'padding: 10px 2px 10px 2px',
			height:90,
			hidden: true,
            items: [
            	(ribbon.undoItem = new Ext.Button({
				    text: 'Undo'.localize(),
				    scale: 'large',
				    rowspan: 3,
				    ctCls: 'ribbonButtons',
				    iconCls: 'undo-icon32',
				    iconAlign: 'top',
					width: 40,
					tooltip: "Undo".localize(),
					handler: Jedox.wss.sheet.undo,
					template: ribbonButtonTemplate
				})),
				(ribbon.redoItem = new Ext.Button({
			        text: 'Redo'.localize(),
			        scale: 'large',
			        rowspan: 3,
			        ctCls: 'ribbonButtons',
			        iconCls: 'redo-icon32',
			        iconAlign: 'top',
					width: 40,
					tooltip: "Redo".localize(),
					handler: Jedox.wss.sheet.redo,
					template: ribbonButtonTemplate
			    }))
            ]
        },{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Clipboard'.localize(),
			height:90,
            items: [
				(ribbon.paste = new Ext.Button({
				    xtype:'splitbutton',
				    text: 'Paste'.localize(),
				    scale: 'large',
				    rowspan: 3,
				    ctCls: 'ribbonButtons',
				    iconCls: 'paste-icon32',
				    iconAlign: 'top',
					width:40,
				    arrowAlign:'bottom',
					tooltip: "Paste".localize(),
					disabled: true,
					template: ribbonButtonTemplate,
					handler: Jedox.wss.action.paste,
				    menu: [(ribbon.pasteSpec = new Ext.menu.Item({text: 'Paste Special'.localize(), disabled: true, handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pasteSpecial, []);}}))]
				})),
            {
                text: 'Cut'.localize(),
				iconCls: 'cut-icon',
				handler: function(){Jedox.wss.action.cut(false);}
            },{
                text: 'Copy'.localize(),
				iconCls: 'copy-icon',
				handler: function(){Jedox.wss.action.copy(false);}
            },
				(ribbon.formatPainter = new Ext.Toolbar.Button({
					text: "Format Painter".localize(),
					iconCls: 'formatpainter-icon',
					enableToggle: true,
					pressed: false,
					timer:null,
					clicked:false,
					listeners:{
						click:function(){
							var that = this;

							if(this.clicked){//Dbl click
								clearTimeout(this.timer);
								this.toggle(true, true);
								Jedox.wss.app.formatPainter = 2;
								Jedox.wss.action.copy(false);
								Jedox.wss.action.setCursorCSS(true);
							}
							else {//click
								this.timer = setTimeout(function(){
									clearTimeout(that.timer);
									that.clicked = false;
									if(that.pressed){
										Jedox.wss.app.formatPainter = 1;
										Jedox.wss.action.copy(false);
										Jedox.wss.action.setCursorCSS(true);
									}
									else {
										Jedox.wss.action.exitFormatPainter();
									}

								}, 400);
							}

							this.clicked = !this.clicked;
						}
					}}
				))
			]
        },{
            xtype: 'buttongroup',
            columns: 6,
            title: 'Font'.localize(),
			bodyStyle: 'padding-top:10px',
			height:90,
            items: [
			//    // Add dropdown list - Fonts.
		    // TODO: Apply font style to items in the dropdown list.
			// TODO: Make font-family dropdown list editable.
			(ribbon.fonts = new Ext.form.ComboBox({
		    	id: 'tbarFonts',
				displayField: 'fontname',
				valueField: 'fontdef',
				typeAhead: true,
				editable: true,
				mode: 'local',
				triggerAction: 'all',
				ctCls: 'toolbar-combo',
				selectOnFocus: true,
				forceSelection: true,
				value: Jedox.wss.app.cnfDefaultFont,
				listWidth: 160,
				width: 140,
				colspan: 5,
				style: 'margin-bottom: 1px',
				tpl: '<tpl for="."><div class="x-combo-list-item" style="font-family: {fontdef}; color: #15428B;">{fontname}</div></tpl>',

				store: new Ext.data.SimpleStore({
			        fields: ['fontname', 'fontdef'],
			        data : Jedox.wss.style.fonts
			    }),

			    listeners: {
					select: {fn: Jedox.wss.app.onFormatDropdownSelect, scope: this},
			    	focus: {fn: Jedox.wss.app.onFormatDropdownFocus, scope: this},
			    	blur: {fn: Jedox.wss.app.onFormatDropdownBlur, scope: this}
				}
		    })),

		    // Add dropdown list - Font Sizes.
			// TODO: Make font-size dropdown list editable.
		    (ribbon.fontSizes = new Ext.form.ComboBox({
		    	id: 'wToolbar_fontSize_cmb',
				displayField: 'fontsize',
				valueField: 'fontsize',
				typeAhead: true,
				editable: true,
				selectOnFocus: true,
				mode: 'local',
				triggerAction: 'all',
				forceSelection: false,
				value: Jedox.wss.app.cnfDefaultFontSize,
				listWidth: 110,
				width: 40,
				colspan: 1,
				style: 'margin-bottom: 1px',
				allowBlank: false,
		//		applyTo: Jedox.wss.app.formatToolbar.fontSizes,
				tpl: '<tpl for="."><div class="x-combo-list-item" style="font-size: {fontsize}pt; color: #15428B;">{fontsize}</div></tpl>',

				store: new Ext.data.SimpleStore({
			        fields: ['fontsize'],
			        data : Jedox.wss.style.fontSizes
			    }),

			    listeners: {
			    	change: {fn: Jedox.wss.app.onFormatDropdownChange, scope: this},
			    	select: {fn: Jedox.wss.app.onFormatDropdownSelect, scope: this},
			    	focus: {fn: Jedox.wss.app.onFormatDropdownFocus, scope: this},
			    	blur: {fn: Jedox.wss.app.onFormatDropdownBlur, scope: this},
			    	specialkey: {fn: Jedox.wss.app.onFormatDropdownSpecKey, scope: this}
				}
		    })),
		    (ribbon.bold = new Ext.Toolbar.Button({
				id: 'wToolbar_bold_btn',
                iconCls: 'icon_font'.concat('_bold'.localize()),
				enableToggle: true,
				pressed: false,
				tooltip: "Bold".localize(),
				toggleHandler: Jedox.wss.app.onFormatItemToggle
            })),
            (ribbon.italic = new Ext.Toolbar.Button({
				id: 'wToolbar_italic_btn',
                iconCls: 'icon_font'.concat('_italic'.localize()),
				enableToggle: true,
				pressed: false,
				tooltip: "Italic".localize(),
				toggleHandler: Jedox.wss.app.onFormatItemToggle
            })),
            (ribbon.underline = new Ext.Toolbar.Button({
				id: 'wToolbar_uLine_btn',
                iconCls: 'underline-icon',
				enableToggle: true,
				pressed: false,
				tooltip: "Underline".localize(),
				toggleHandler: Jedox.wss.app.onFormatItemToggle
            })),
            (ribbon.border = new Ext.Toolbar.SplitButton({
				id: 'tbarBorder',
                iconCls: 'icon-brd-bottom-norm',
				tooltip: 'Bottom Border'.localize(),
				handler: this.onBorderSelect,
				menu: {
					items: [
						{id: 'brd-bottom-norm', text: 'Bottom Border'.localize(), iconCls: 'icon-brd-bottom-norm', handler: this.onBorderSelect},
						{id: 'brd-top-norm', text: 'Top Border'.localize(), iconCls: 'icon-brd-top-norm', handler: this.onBorderSelect},
						{id: 'brd-left-norm', text: 'Left Border'.localize(), iconCls: 'icon-brd-left-norm', handler: this.onBorderSelect},
						{id: 'brd-right-norm', text: 'Right Border'.localize(), iconCls: 'icon-brd-right-norm', handler: this.onBorderSelect},
						'-',
						{id: 'brd-all-norm', text: 'All Borders'.localize(), iconCls: 'icon-brd-all-norm', handler: this.onBorderSelect},
						{id: 'brd-out-norm', text: 'Outside Borders'.localize(), iconCls: 'icon-brd-out-norm', handler: this.onBorderSelect},
						{id: 'brd-out-thick', text: 'Thick Outside Border'.localize(), iconCls: 'icon-brd-out-thick', handler: this.onBorderSelect},
						{id: 'brd-all-none', text: 'No Border'.localize(), iconCls: 'icon-brd-all-none', handler: this.onBorderSelect},
						'-',
						{id: 'brd-top-bottom-norm', text: 'Top and Bottom Border'.localize(), iconCls: 'icon-brd-top-bottom-norm', handler: this.onBorderSelect},
						{id: 'brd-bottom-thick', text: 'Thick Bottom Border'.localize(), iconCls: 'icon-brd-bottom-thick', handler: this.onBorderSelect},
						{id: 'brd-top-norm-bottom-thick', text: 'Top and Thick Bottom Border'.localize(), iconCls: 'icon-brd-top-norm-bottom-thick', handler: this.onBorderSelect},
						'-',
						{id: 'formatCellsBorders', text: 'More Borders'.localize().concat('...'), iconCls: 'icon-brd-more', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatCells, ['formatCellsBorders']);}}
					]
				}
            })),
            {
				xtype:'splitbutton',
				id: 'wToolbar_bgColor_btn',
				iconCls: 'iconbgcolor',
				tooltip: "Fill Color".localize(),
				handler: Jedox.wss.app.onColorSelect,
				menu: (ribbon.bgColor = new Ext.menu.Menu({
					id: 'wToolbar_bgColor_mn',
					colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
					cls: 'wide-color-palette',
					iconCls: 'no-icon',
					handler: Jedox.wss.app.onColorSelect,
					items: [
							{
								text: 'No Color'.localize(),
								id: 'bgNoColor',
								handler: Jedox.wss.app.onColorSelect
							},
							new Ext.ColorPalette({

								colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
								handler: Jedox.wss.app.onColorSelect,
								allowReselect: true
							})
							]
				}))
            },{
				xtype:'splitbutton',
				id: 'wToolbar_txtColor_btn',
				iconCls: 'icontextcolor',
				tooltip: "Font Color".localize(),
				handler: Jedox.wss.app.onColorSelect,
				menu: new Ext.menu.ColorMenu({
					id: 'wToolbar_txtColor_mn',
					iconCls: 'no-icon',
					colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
					cls: 'wide-color-palette',
					handler: Jedox.wss.app.onColorSelect
				})
            }]
        },{
            xtype: 'buttongroup',
            columns: 4,
			height:90,
            title: 'Alignment'.localize(),
            id: 'ribbonAlignment',
            items: [
                (ribbon.alignLeft = new Ext.Button({
					id: 'wToolbar_alignLeft_btn',
	                iconCls: 'leftalign-icon32',
					text:'Left'.localize().concat('...'),
					scale: 'large',
					iconAlign: 'top',
					width:40,
					rowspan: 2,
					ctCls: 'ribbonButtons',
					template: ribbonButtonTemplate,
					enableToggle: true,
					pressed: false,
					tooltip: "Align Text Left".localize(),
					toggleHandler: Jedox.wss.app.onFormatItemToggle,
					template: ribbonButtonTemplate
	            })),
	            (ribbon.alignCenter = new Ext.Button({
					id: 'wToolbar_alignCenter_btn',
	                iconCls: 'centeralign-icon32',
					text:'Center'.localize(),
					scale: 'large',
					iconAlign: 'top',
					width:40,
					rowspan: 2,
					template: ribbonButtonTemplate,
					ctCls: 'ribbonButtons',
					enableToggle: true,
					pressed: false,
					tooltip: "Align Text Center".localize(),
					toggleHandler: Jedox.wss.app.onFormatItemToggle
	            })),
	            (ribbon.alignRight = new Ext.Button({
					id: 'wToolbar_alignRight_btn',
	                iconCls: 'rightalign-icon32',
					text:'Right'.localize(),
					scale: 'large',
					iconAlign: 'top',
					width:40,
					rowspan: 2,
					template: ribbonButtonTemplate,
					ctCls: 'ribbonButtons',
					enableToggle: true,
					pressed: false,
					tooltip: "Align Text Right".localize(),
					toggleHandler: Jedox.wss.app.onFormatItemToggle
	            })),
	            {
					id: 'tbarMergeCells',
	                text: 'Merge Cells'.localize(),
					iconCls: 'mergecells-icon',
					tooltip: "Merge Cells".localize(),
					handler: function(){Jedox.wss.action.mergeCells(false);}
	            },{
					id: 'tbarUnmergeCells',
	                text: 'Unmerge Cells'.localize(),
					iconCls: 'unmergecells-icon',
					tooltip: "Unmerge Cells".localize(),
					handler: function(){Jedox.wss.action.mergeCells(true);}
	            }
            ],
			listeners:{
				hide:function(){
					doOverflow(this, true);
				},
				show:function(){
					doOverflow(this, false);
				}
			}
        },{
            xtype: 'buttongroup',
            columns: 4,
            title: 'Cells'.localize(),
			height:90,
            items: [new Ext.Button({
				xtype:'splitbutton',
				iconCls: 'insertrow-icon32',
				text:'Insert'.localize(),
                scale: 'large',
				iconAlign: 'top',
				width:40,
				rowspan: 3,
				template: ribbonButtonTemplate,
				ctCls: 'ribbonButtons',
				arrowAlign:'bottom',
                menu: [
                (ribbon.delRow = new Ext.menu.Item({text: 'Delete Rows'.localize(), iconCls: 'deleterow-icon', handler: function() {Jedox.wss.action.insDelRowCol('del', 'row');}})),
                (ribbon.delCol = new Ext.menu.Item({text: 'Delete Columns'.localize(), iconCls: 'deletecolumn-icon', handler: function() {Jedox.wss.action.insDelRowCol('del', 'col');}})),
                '-',
                {
                    text: 'Insert Sheet'.localize(),
					iconCls:'insertsheet-icon',
					handler: function(){Jedox.wss.app.activeBook.getSheetSelector().addSheet();}
                }]
            }),new Ext.Button({
				xtype:'splitbutton',
				iconCls: 'deleterow-icon32',
				text:'Delete'.localize(),
                scale: 'large',
				iconAlign: 'top',
				width:40,
				rowspan: 3,
				template: ribbonButtonTemplate,
				ctCls: 'ribbonButtons',
				arrowAlign:'bottom',
                menu: [
                (ribbon.insRow = new Ext.menu.Item({text: 'Insert Rows'.localize(), iconCls: 'insertrow-icon', handler: function() {Jedox.wss.action.insDelRowCol('ins', 'row');}})),
                (ribbon.insCol = new Ext.menu.Item({text: 'Insert Columns'.localize(), iconCls: 'insertcolumn-icon', handler: function() {Jedox.wss.action.insDelRowCol('ins', 'col');}})),
                '-',
                {
                    text: 'Delete Sheet'.localize()
                }]
            }),new Ext.Button({
				xtype:'splitbutton',
				iconCls: 'format-icon32',
				text:'Format'.localize(),
                scale: 'large',
				iconAlign: 'top',
				width:40,
				rowspan: 3,
				template: ribbonButtonTemplate,
				ctCls: 'ribbonButtons',
				arrowAlign:'bottom',
                menu: {        // <-- submenu by nested config object
                    items: [
                        // stick any markup in a menu
                        '<b class="menu-title">Cell Size</b>',
                        {
                            text: 'Row Height'.localize().concat('...'),
							iconCls: 'rowheight-icon',
							handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatColRow, [Jedox.wss.grid.headerType.ROW, Jedox.wss.sheet.getColRowSize(Jedox.wss.grid.headerType.ROW)]);}
                        }, {
                            text: 'AutoFit Row Height'.localize(),
							handler: function() {Jedox.wss.action.resizeRowCol(Jedox.wss.grid.headerType.ROW);}
                        },
						'-',{
                            text: 'Column Width'.localize(),
							iconCls: 'columnwidth-icon',
							handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatColRow, [Jedox.wss.grid.headerType.COLUMN, Jedox.wss.sheet.getColRowSize(Jedox.wss.grid.headerType.COLUMN)]);}
						}, {
                            text: 'AutoFit Column Width'.localize(),
							handler: function() {Jedox.wss.action.resizeRowCol(Jedox.wss.grid.headerType.COLUMN);}
                        },
						'<b class="menu-title">Organize Sheets</b>',
						{
                            text: 'Rename Sheet'.localize()
                        }, {
                            text: 'Move or Copy Sheet'.localize()
                        },'-',{
                            text: 'Format Cells'.localize(),
							iconCls:'formatcells-icon'
                        }
                    ]
                }
            }),
            (ribbon.lock = new Ext.Button({
				id: 'tbarLock',
                text: 'Lock<br>Unlock'.localize(),
				iconCls: 'lock-icon32',
                scale: 'large',
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
                iconAlign: 'top',
				width:40,
				enableToggle: true,
				pressed: true,
				tooltip: "Item Lock/Unlock".localize(),
				toggleHandler: Jedox.wss.style.toggleLock
            }))
            ],
			listeners:{
				hide:function(){
					doOverflow(this, true);
				},
				show:function(){
					doOverflow(this, false);
				}
			}
        },{
            xtype: 'buttongroup',
            columns: 1,
            title: 'Styles'.localize(),
			height:91,
            items: [new Ext.Button({
				xtype:'splitbutton',
                text: 'Conditional<br>Formating'.localize(),
                scale: 'large',
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
                iconCls: 'conditionalformat-icon32',
                iconAlign: 'top',
				width:50,
				menu: {
					items: [{
						text: "New Rule".localize().concat('...'),
						iconCls:'newrule-icon',
						handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.conditionalFormatting);}
					},{
						text: "Clear Rules".localize(),
						iconCls: 'clearrules-icon',
							menu: {
								items: [{
									text: "Clear Rules from Selected Cells".localize(),
									handler: function(){Jedox.wss.cndfmt.remove(Jedox.wss.cndfmt.SCOPE_CURR_SEL);}
								},{
									text: "Clear Rules from Entire Sheet".localize(),
									handler: function(){Jedox.wss.cndfmt.remove(Jedox.wss.cndfmt.SCOPE_CURR_WKS);}
								}]
							}
					},{
						text: "Manage Rules".localize().concat('...'),
						iconCls:'managerules-icon',
						handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.manageConditionalFormatting);}
					}]
				}
            })],
			listeners:{
				hide:function(){
					doOverflow(this, true);
				},
				show:function(){
					doOverflow(this, false);
				}
			}
        },{
            xtype: 'buttongroup',
            columns: 1,
            title: 'Editing'.localize(),
			height:90,
			items:[{
                xtype:'splitbutton',
				text: 'Clear'.localize(),
				iconCls:'clearall-icon',
				menu: {
					items: [{
						text: 'Clear All'.localize(),
						iconCls: 'clearall-icon',
						handler: function(){
							Jedox.wss.action.clear(rngClearType.ALL_CLEAR);
						}
					}, {
						text: 'Clear Formats'.localize(),
						iconCls: 'clearformats-icon',
						handler: function(){
							Jedox.wss.action.clear(rngClearType.STYLE | rngClearType.FORMAT | rngClearType.CNDFMT);
						}
					}, {
						text: 'Clear Contents'.localize(),
						iconCls: 'clearcontents-icon',
						handler: function(){
							Jedox.wss.action.clear(rngClearType.FORMULA);
						}
					}]
				}
			},{
                text: 'Go To'.localize(),
				iconCls: 'goto-icon',
				tooltip: "Go To".localize(),
				 handler: function(){
					Jedox.gen.load(Jedox.wss.app.dynJSRegistry.goTo);
				}
            }],
			listeners:{
				hide:function(){
					doOverflow(this, true);
				},
				show:function(){
					doOverflow(this, false);
				}
			}

        },{
            xtype: 'buttongroup',
            columns: 1,
            title: 'Mode'.localize(),
			height:90,
            items: [
                (ribbon.hbQuickView = new Ext.Toolbar.Button({
					id:'tbarQuickView',
					iconCls:'quickviewpreview-icon',
					text:"Quick View".localize(),
					tooltip: "Quick View".localize(),
					enableToggle: true,
					pressed: false,
					toggleHandler: function(button, state){
						Jedox.wss.hb.run(button, state);
						Ext.getCmp('tbarQuickView-d').toggle(state, true);
					},
					enable:function(){
						Ext.getCmp('tbarQuickView-d').enable();
						Ext.Toolbar.Button.prototype.enable.apply(this);
					},
					disable:function(){
						Ext.getCmp('tbarQuickView-d').disable();
						Ext.Toolbar.Button.prototype.disable.apply(this);
					}
                })),
                (ribbon.userModeView = new Ext.Toolbar.Button({
					id: 'tbarViewMode',
					text:'User Mode'.localize(),
					iconCls:'userpreview-icon',
					tooltip: "Open User Mode".localize(),
					handler: Jedox.wss.app.openViewMode,
					enable:function(){
						Ext.getCmp('tbarViewMode-d').enable();
						Ext.Toolbar.Button.prototype.enable.apply(this);
					},
					disable:function(){
						Ext.getCmp('tbarViewMode-d').disable();
						Ext.Toolbar.Button.prototype.disable.apply(this);
					}
                }))
            ]
        }],
			listeners:{
				hide:function(){
					doOverflow(this, true);
				},
				show:function(){
					doOverflow(this, false);
				}
			}
        // end of toolbar items
        })
    });


	// ###############
	// #    INSERT   #
	// ###############
	var insert = new Ext.Panel({
        title: 'Insert'.localize(),
        tbar: [{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Ilustrations',
			bodyStyle: 'padding:10px',
//	        style: {
//	            marginTop: '0px',
//				marginBottom:'0px'
//	        },
			height:90,
            items: [new Ext.Button({
                text: 'Picture'.localize(),
                scale: 'large',
                rowspan: 3,
                ctCls: 'ribbonButtons',
                template: ribbonButtonTemplate,
				colspan:2,
				width:50,
                iconCls: 'insertpicture-icon32',
                iconAlign: 'top',
				handler: function() {Jedox.wss.dlg.openInsertPicture();}
            })]
        },{
            xtype: 'buttongroup',
            columns: 1,
            title: 'Links'.localize(),
			bodyStyle: 'padding:10px',
			height:90,
            items: [new Ext.Button({
                text: 'Hyperlink'.localize(),
                scale: 'large',
                rowspan: 3,
                ctCls: 'ribbonButtons',
                template: ribbonButtonTemplate,
				width:50,
                iconCls: 'inserthl-icon32',
                iconAlign: 'top',
				handler: function(){var	env = Jedox.wss.app.environment, selCoord = env.selectedCellCoords; Jedox.gen.load(Jedox.wss.app.dynJSRegistry.openHL, [{defName: Jedox.wss.general.filterHLTags(selCoord[0], selCoord[1], env.selectedCellValue, false), handlers:{scope: Jedox.wss.hl, set: Jedox.wss.hl.set}}]);}
            })]
        },{
            xtype: 'buttongroup',
            columns: 3,
            title: 'Charts'.localize(),
			bodyStyle: 'padding:10px',
			height:90,
            items: [new Ext.Button({
                text: 'Chart'.localize(),
                scale: 'large',
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
				width:50,
                iconCls: 'insertchart-icon32',
                iconAlign: 'top',
				handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.chart, ['insert', 0]);}

            }),new Ext.Button({
                text: 'Micro Chart'.localize(),
                scale: 'large',
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
				width:50,
                iconCls: 'insertmicrochart-icon32',
                iconAlign: 'top',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.openMicroChart);}
            })]
        }]
    });


	// ###############
	// # PAGE LAYOUT #
	// ###############
	var pageLayout = new Ext.Panel({
        title: 'Page Layout'.localize(),
        tbar: [
//               {
//            xtype: 'buttongroup',
//            columns: 1,
//            title: 'Themes'.localize(),
//			bodyStyle: 'padding:0px 10px 0px 10px',
//			height:90,
//            items: [{
////				id: 'theme-default',
//				xtype:'splitbutton',
//				text: "Theme".localize(),
//				iconCls:'themeblue-icon32',
//				scale: 'large',
//				rowspan: 3,
//				template: ribbonButtonTemplate,
//				width:40,
//				iconAlign: 'top',
//				arrowAlign:'bottom',
//				menu: (ribbon.themeMenu = new Ext.menu.Menu({
//					items: [
//							{text: "Blue (default)".localize(), id: 'theme-default', enableToggle: true, checked: true, checkHandler: Jedox.wss.action.switchTheme},
//							{text: "Gray".localize(), id: 'theme-gray', enableToggle: true, checked: false, checkHandler: Jedox.wss.action.switchTheme},
//							{text: "Dark".localize(), id: 'theme-slate', enableToggle: true, checked: false, checkHandler: Jedox.wss.action.switchTheme}
//						]
//				}))
//			}]
//        },
        {
            xtype: 'buttongroup',
            columns: 2,
            title: 'Page Setup'.localize(),
			height:90,
            items: [new Ext.Button({
                text: 'Print<br>Preview'.localize(),
                scale: 'large',
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
				width:40,
                iconCls: 'printpreview-icon32',
                iconAlign: 'top',
				handler: Jedox.wss.action.exportToHTML
            }),{
                text: 'Page Setup'.localize(),
				iconCls: 'pagesetup-icon',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pageSetup);}
            }]
        }]
    });


	// ################
	// #   FORMULAS   #
	// ################
	var formulas = new Ext.Panel({
        title: 'Formulas'.localize(),
        tbar: [{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Function'.localize(),
            items: [new Ext.Button({
                text: 'Insert<br>Funciton'.localize(),
                scale: 'large',
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
				width:40,
                iconCls: 'insertfunction-icon32',
                iconAlign: 'top',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.insertFunction);}
            })]
        },{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Defined Names'.localize(),
			height:90,
            items: [new Ext.Button({
                text: 'Name<br> Manager'.localize(),
                scale: 'large',
                width: 90,
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
                iconCls: 'namedrange-icon32',
                iconAlign: 'top',
				handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.nameManager);}
            })
            // TODO: apply functionality like in Excel (srdjanv)
//            ,{
//                text: 'Define Name'.localize(), iconCls: 'newname-icon'
//            }
            ]
        },{
            xtype: 'buttongroup',
            columns: 3,
			title: 'Calculation'.localize(),
//			bodyStyle: 'padding:10px',
			height:90,
            items: [new Ext.Button({
                text: 'Refresh<br>Data'.localize(),
				iconCls:'refresh-icon',
				scale: 'large',
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
				width:50,
				iconAlign: 'top',
				handler: function () { Jedox.wss.sheet.refresh(); }
            }),{
				xtype:'tbspacer',
				width:10,
				rowspan:3
			}, {
				xtype: 'checkbox',
				id: 'autoRefreshDataMenu',
                boxLabel: 'Auto-Refresh Data'.localize(),
 				enableToggle: true,
				checked: false,
				handler: function () { this.checked ? Jedox.gen.load(Jedox.wss.app.dynJSRegistry.autoRefreshStart) : Jedox.wss.book.autoRefresh(0); },
				listeners: {
					beforerender: function () {this.setValue(Jedox.wss.app.activeBook && Jedox.wss.app.activeBook._autoRefresh > 0); }
				}
            },{
				xtype: 'checkbox',
				id: 'autoCalcDataItem',
                boxLabel: 'Auto-Calculate Data'.localize(),
 				enableToggle: true,
				checked: false,
				handler: function () { Jedox.wss.general.autoCalc(this.checked); },
				listeners: {
					beforerender: function () {this.setValue(Jedox.wss.app.autoCalc);}
				}
            }]
        },
        {
            xtype: 'buttongroup',
            columns: 2,
            title: 'Variables'.localize(),
            height: 90,
            items: [new Ext.Button({
                text: 'Variables'.localize(),
                //template: ribbonButtonTemplate,
                //ctCls: 'ribbonButtons',
				width:40,
                //iconCls: 'insertfunction-icon32',
                //iconAlign: 'top',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.privateVars);}
            })]
        }]
    });

	// ###############
	// #     VIEW    #
	// ###############
	var view = new Ext.Panel({
        title: 'View'.localize(),
        tbar: [{
            xtype: 'buttongroup',
            columns: 1,
            title: 'Show/Hide'.localize(),
			bodyStyle: 'padding:0px 10px 0px 10px; ',
			height:90,
            items: [
            /*{
				xtype: 'checkbox',
				boxLabel: "Toolbars".localize(),
				enableToggle: true,
				checked: true,
				checkHandler: function(btn, state){Jedox.wss.app.hideShowToolbar(state, '');}
			},*/
			{
				xtype: 'checkbox',
				boxLabel: "Formula Bar".localize(),
				enableToggle: true,
				checked: !Jedox.wss.app.initHideFormulaBar,
				handler: function(btn, state){Jedox.wss.app.hideShowFormulaBar(state);}
			},{
				xtype: 'checkbox',
				boxLabel: "Status Bar".localize(),
				enableToggle: true,
				checked: !Jedox.wss.app.initHideStatusBar,
				handler: function(btn, state){Jedox.wss.app.statusBar.hideShow(state);}
			}]
        },{
            xtype: 'buttongroup',
         	columns: 2,
			bodyStyle: 'padding:0px 10px 10px 10px; ',
            title: 'Window'.localize(),
			height:90,
            items: [new Ext.Button({
                text: 'Arrange <br>All'.localize(),
                scale: 'large',
				width:50,
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
                iconCls: 'arrangeall-icon32',
                iconAlign: 'top',
				handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.arrangeWindows); }
            }),{
                text: 'Hide'.localize(),
				iconCls: 'hide-icon',
				handler: function() { Jedox.wss.wnd.hideActive(); }
            },{
                text: 'Unhide'.localize(),
				iconCls: 'unhide-icon',
				handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.unhideWindow); }
            },{
                xtype:'splitbutton',
                text: 'Open documents'.localize(),
				iconCls: 'unhide-icon',
				menu: (ribbon.openDocs = new Ext.menu.Menu())
            }
            ]
        }]
    });


	// ###############
	// #  DEVELOPER  #
	// ###############
	var developer = new Ext.Panel({
        title: 'Developer'.localize(),
        tbar: [{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Controls'.localize(),
			height:90,
            items: [new Ext.Button({
                text: 'Macro <br>Editor'.localize(),
                scale: 'large',
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
				width:40,
                iconCls: 'macroeditor-icon32',
                iconAlign: 'top',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.editMacro);}
            }),{
                text: 'Combo Box'.localize(),
				iconCls: 'formcombobox-icon',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatControl, [{type: Jedox.wss.wsel.type.COMBO_BOX}]);}
            },{
                text: 'Check Box'.localize(),
				iconCls: 'formcheckbox-icon',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatControl, [{type: Jedox.wss.wsel.type.CHECK_BOX}]);}
            },{
                text: 'Button'.localize(),
				iconCls: 'formbutton-icon',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatControl, [{type: Jedox.wss.wsel.type.BUTTON}]);}
            }]
        },{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Dyna Ranges'.localize(),
			height:90,
            items: [
                (ribbon.newHBVert = new Ext.Button({
					id: 'newHBVertTbar',
	                text: 'Vertical <br> Dyna Range'.localize(),
	                scale: 'large',
	                rowspan: 3,
	                template: ribbonButtonTemplate,
	                ctCls: 'ribbonButtons',
	                iconCls: 'verdynarange-icon32',
	                iconAlign: 'top',
					handler: Jedox.wss.hb.addDynarange
                })),
                (ribbon.newHBHoriz = new Ext.Button({
					id: 'newHBHorizTbar',
	                text: 'Horizontal <br> Dyna Range'.localize(),
	                scale: 'large',
	                rowspan: 3,
	                template: ribbonButtonTemplate,
	                ctCls: 'ribbonButtons',
	                iconCls: 'hordynarange-icon32',
	                iconAlign: 'top',
					handler: Jedox.wss.hb.addDynarange
                }))
            ]
        },{
            xtype: 'buttongroup',
            columns: 1,
            title: 'Mode'.localize(),
			height:90,
            items: [
                (new Ext.Toolbar.Button({
					id:'tbarQuickView-d',
					iconCls:'quickviewpreview-icon',
					text:"Quick View".localize(),
					tooltip: "Quick View".localize(),
					enableToggle: true,
					pressed: false,
					toggleHandler:Jedox.wss.hb.run
                })),
                (new Ext.Toolbar.Button({
					id: 'tbarViewMode-d',
					text:'User Mode'.localize(),
					iconCls:'userpreview-icon',
					tooltip: "Open User Mode".localize(),
					handler: Jedox.wss.app.openViewMode
                }))
            ]
        }]
    });


	// ###############
	// #     PALO    #
	// ###############
	var palo = new Ext.Panel({
        title: 'Palo',
        tbar: [{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Create or Modify Reports'.localize(),
			height:90,
            items: [new Ext.Button({
                text: 'Paste <br>View'.localize(),
                scale: 'large',
                rowspan: 3,
                ctCls: 'ribbonButtons',
                template: ribbonButtonTemplate,
				width:40,
                iconCls: 'palopasteview-icon32',
                iconAlign: 'top',
				handler: function(){ Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pasteView);}
            }),{
                text: 'Paste Elements'.localize(),
				iconCls: 'palopasteelements-icon',
				handler: function(){ Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectElements);}
            },{
                text: 'Paste Subset'.localize(),
				iconCls: 'palopastesubset-icon',
				handler: function(){ Jedox.gen.load(Jedox.wss.app.dynJSRegistry.subsetEditor);}
            },{
                text: 'Paste Function'.localize(),
				iconCls: 'palopastefunction-icon',
				handler: function(){ Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pasteDataFunctions);}
            }]
        }
        /*
        , {
            xtype: 'buttongroup',
            columns: 2,
            title: 'Control and Modify Palo'.localize(),
            height:90,
			items: [
			new Ext.Button({
                text: 'Modeller'.localize(),
                scale: 'large',
                rowspan: 3,
                template: ribbonButtonTemplate,
                ctCls: 'ribbonButtons',
                iconCls: 'palomodeller-icon32',
                iconAlign: 'top',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.modeller);}
            }),
            {
                text: 'Import Data'.localize(),
				iconCls: 'paloimportdata-icon',
				width: 120,
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.paloImport);}
            }]
        }
        */
        /*
        ,{
            xtype: 'buttongroup',
            columns: 1,
			title: 'Save'.localize(),
			height:90,
            items: [{
                text: 'Save as Snapshot'.localize(),
				iconCls: 'palosaveassnapshoot-icon',
				disabled: true
            }]
        }
        */
//        ,{
//            xtype: 'buttongroup',
//            columns: 1,
//            title: 'Info'.localize(),
//			height:90,
//            items: [{
//                text: 'About Palo'.localize(),
//				iconCls: 'paloabout-icon',
//				disabled : true
//            }]
//        }
        ]
    });

	// ###############
	// #     HELP    #
	// ###############
	var help = new Ext.Panel({
        title: 'Help'.localize(),
        tbar: [
			{
			    xtype: 'buttongroup',
			 	columns: 1,
				bodyStyle: 'padding:0px 10px 10px 10px; ',
				height:90,
			    title: 'Window',
			    items: [
				    {
				        text: "Jedox Online".localize(),
						iconCls: 'hide-icon',
						handler:function(){window.open("http://www.jedox.com" ,"_blank")}
				    }
//				  {
//						text: "About Palo Suite".localize(),
//						iconCls: 'hide-icon',
//					}
				]
			}
		]
	});

	// Create Ribbon.
	Jedox.wss.app.ribbon = new Ext.TabPanel({
		id: 'ribbon-main-panel',
		border:false,
		layoutOnTabChange: true,
		renderTo: 'ribbon',
		items: [home, insert, pageLayout, formulas, view, developer, palo, help],
		activeTab: 0
	});



	function doOverflow(btngrp, hide){

		/*
		 * check if buttonGroup is hidden;
		 * if yes, set small icons (16px)
		 * if not, set large icons (32px)
		 *
		 * NB:	this is applied only for HOME tab, since it is the biggest and only one affected by window resizing;
		 * 		if other tabs need same functionality, same listener and function should be applied
		 */

		for (var i=0, items = btngrp.items.items, count = items.length; i<count; i++){
			var currClass = items[i].iconCls;
			if (currClass) {
				var newClass = hide? currClass.replace(/32/i, '16') : currClass.replace(/16/i, '32');
				items[i].setIconClass(newClass);
			}
		}
	}

	Ext.DomQuery.selectNode('*[class*=iconbgcolor]').style.borderLeft = "solid 4px #FF0000";
	Ext.DomQuery.selectNode('*[class*=icontextcolor]').style.borderLeft = "solid 4px #FFFF00";


	Jedox.wss.app.toolbar.resize = function(){
		Jedox.wss.app.ribbon.doLayout();
	}


};