/*
 * @brief wss file
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
 * Andrej Vrhovac <andrej.vrhovac@develabs.com>
 *
 * \version
 * SVN: $Id: Format.js 4837 2011-04-13 12:25:05Z predragm $
 *
 */
Jedox.wss.dlg.formatCells = function(item, ev, addFn, preFmt) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.Format(item, ev, addFn, preFmt));
};

Jedox.wss.dlg.Format = (function() {

	return function (item, ev, addFn, preFmt) {

		Jedox.wss.dlg.Format.parent.constructor.call(this);
		this.id = 'wFormatCells_dlg_wnd';
		var that = this;


		var _fromDlgF = false;

		var _fontToDisable = false;

		if (Jedox.wss.app.environment.inputMode === Jedox.wss.grid.GridMode.DIALOG)
			_fromDlgF = true;
		else {
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}

		// if needed, here get all preselection!

		var selCoord = Jedox.wss.app.environment.selectedCellCoords;
		var env = Jedox.wss.app.environment, rngStartCoord = env.lastRangeStartCoord, rngEndCoord = env.lastRangeEndCoord;

		// for managing active containers
		var activeContainers = {};

		function setContainers(elements){
			// erase all containers, than add appropriate one

			for (var c in activeContainers){
				delete that.containers[c];
			}
			activeContainers = {};

			for (var nc in elements){
				that.containers[nc] = elements[nc];
				activeContainers[nc] = nc;
			}

		};

		var formatCellPreConf = Jedox.wss.app.activePane.getRangeStyle(
				[ rngStartCoord[0], rngStartCoord[1], rngEndCoord[0],
						rngEndCoord[1] ], {
					backgroundColor : '',
					fontWeight : '',
					fontFamily : '',
					textDecoration : '',
					fontSize : '',
					fontStyle : '',
					color : '',
					textAlign : '',
					verticalAlign : '',
					textIndent : '',
					whiteSpace : '',
					direction : '',
					backgroundImage : ''
				});

		var _preFont = {
			fontWeight : formatCellPreConf.fontWeight,
			fontFamily : formatCellPreConf.fontFamily,
			textDecoration : formatCellPreConf.textDecoration,
			fontSize : formatCellPreConf.fontSize,
			fontStyle : formatCellPreConf.fontStyle,
			color : formatCellPreConf.color
		}

		var _preAlignment = {
			textAlign : formatCellPreConf.textAlign,
			verticalAlign : formatCellPreConf.verticalAlign,
			textIndent : formatCellPreConf.textIndent,
			whiteSpace : formatCellPreConf.whiteSpace,
			direction : formatCellPreConf.direction
		}

		var _preFill = {
			backgroundColor : formatCellPreConf.backgroundColor,
			backgroundImage : formatCellPreConf.backgroundImage
		}

		/////// PRESELECTION FOR CONDITIONAL FMT
		var initStateCF = {};
		if (item=='fromConditionalFormatting'){
			_preFont = {
					fontWeight : preFmt[1]? preFmt[1].fontWeight : '',
					fontFamily : preFmt[1]? preFmt[1].fontFamily : '',
					textDecoration : preFmt[1]? preFmt[1].textDecoration : '',
					fontSize : preFmt[1]? preFmt[1].fontSize : '',
					fontStyle : preFmt[1]? preFmt[1].fontStyle : '',
					color : preFmt[1]? preFmt[1].color : ''
				}
			initStateCF.preFont = _preFont;

			_preAlignment = {
					textAlign : preFmt[1]? preFmt[1].textAlign : '',
					verticalAlign : preFmt[1]? preFmt[1].verticalAlign : '',
					textIndent : preFmt[1]? preFmt[1].textIndent : '',
					whiteSpace : preFmt[1]? preFmt[1].whiteSpace : '',
					direction : preFmt[1]? preFmt[1].direction : ''
				}

			initStateCF.preAlignment = _preAlignment;

			_preFill = {
					backgroundColor : preFmt[1]? preFmt[1].backgroundColor : '',
					backgroundImage : preFmt[1]? preFmt[1].backgroundImage : ''
				}

			initStateCF.preFill = _preFill;

			// non-standard preselection

			var _preBorders = preFmt[2]? preFmt[2] : '';

			initStateCF.preBorders = _preBorders
			var _preFormat = preFmt[0]? preFmt[0] : '';
			var _preProtection = preFmt[3];
		}
		else if (item=='fromPageSetup'){
			_preFont = {
					fontWeight : preFmt.fontWeight,
					fontFamily : preFmt.fontFamily,
					textDecoration : preFmt.textDecoration,
					fontSize : preFmt.fontSize,
					fontStyle : preFmt.fontStyle,
					color : preFmt.color
				}
			initStateCF.preFont = _preFont;
		}

		////////////////////////////////////////
		// //////////////////////////////////////

		var fontHolder = new Ext.Panel( {
			id : 'font',
			title : 'Font'.localize(),
			items : [ {} ]
		});

		var numberHolder = new Ext.Panel( {
			id : 'number',
			title : 'Number'.localize(),
			items : [ {} ],
			fbar: new Ext.Toolbar({items: [{}], hidden: true, style: 'margin-bottom: 1px; margin-right: 10px;'})
		});

		var alignmentHolder = new Ext.Panel( {
			id : 'alignment',
			title : 'Alignment'.localize(),
			items : [ {} ]
		});
		var borderHolder = new Ext.Panel( {
			id : 'border',
			title : 'Border'.localize(),
			items : [ {} ]
		});

		var fillHolder = new Ext.Panel( {
			id : 'fill',
			title : 'Fill'.localize(),
			items : [ {} ]
		});

		var protectionHolder = new Ext.Panel( {
			id : 'protection',
			title : 'Protection'.localize(),
			items : [ {} ]
		});

		var fontPann;
		var numberPann;
		var alignmentPann;
		var borderPann;
		var fillPann;
		var protectionPann;

		var isFromOther = false;
		var components = {
			number : false,
			alignment : false,
			font : false,
			border : false,
			fill : false,
			protection : false
		};

		var tabs = new Ext.TabPanel( {
			region : 'center',
			xtype : 'tabpanel',
			margins : '3 3 3 0',
			id: 'wFmtCells_tabs_tbp',
			layoutOnTabChange : true,
			activeTab : 0,
			baseCls : 'x-plain',
			defaults : {
				autoScroll : false,
				bodyStyle : 'background-color: transparent;'
			},

			items : [ numberHolder, alignmentHolder, fontHolder, borderHolder,
					fillHolder, protectionHolder ],
			listeners : {
				tabchange : function(el, e) {
					if (!components[e.id]) {
						switch (e.id) {
						case 'font':
							var fcb = function(fontPan) {
								fontPann = fontPan;
								fontHolder.removeAll();
								fontHolder.add(fontPan);
								fontHolder.doLayout();

							};
							// Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatFont,
							// [callback_function, preselection_array, disable_array]);

							// tabOffset = 300
							Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatFont, [ fcb, _preFont, _fontToDisable, false, 300, !!(item=='fromConditionalFormatting')]);
							break;
						case 'number':
							var ncb = function(numberPan, clrBtn) {
								numberPann = numberPan;
								numberHolder.removeAll();
								numberHolder.add(numberPan);
								if (clrBtn){
									var fbar = numberHolder.getFooterToolbar();
									fbar.removeAll();
									fbar.add(clrBtn);
									fbar.show(); fbar.doLayout();
								}
								numberHolder.doLayout();
							};
							// tabOffset = 100
							if (item=='fromConditionalFormatting')
								Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatNumber, [ ncb, _preFormat, false, isFromOther, 100, setContainers, true]);
							else
								Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatNumber, [ ncb, false, false, isFromOther, 100, setContainers]);
							break;
						case 'alignment':
							var acb = function(alignmentPan) {
								alignmentPann = alignmentPan;
								alignmentHolder.removeAll();
								alignmentHolder.add(alignmentPan);
								alignmentHolder.doLayout();
							};
							// tabOffset = 200
							Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatAlignment, [ acb, _preAlignment, false, 200]);
							break;
						case 'border':
							var bcb = function(borderPan) {
								borderPann = borderPan;
								borderHolder.removeAll();
								borderHolder.add(borderPan);
								borderHolder.doLayout();

							};
							// tabOffset = 400
							if (item=='fromConditionalFormatting')
								Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatBorder, [ bcb, _preBorders, false, isFromOther, 400, true]);
							else
							Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatBorder, [ bcb, false, false, isFromOther, 400]);
							break;
						case 'fill':
							var flcb = function(fillPan) {
								fillPann = fillPan;
								fillHolder.removeAll();
								fillHolder.add(fillPan);
								fillHolder.doLayout();

							};
							// tabOffset = 500
							if (item=='fromConditionalFormatting')
								Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatFill, [ flcb, _preFill, false, true, 500, true]);
							else
							Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatFill, [ flcb, _preFill, false, false, 500]);
							break;
						case 'protection':
							var pcb = function(protectionPan) {
								protectionPann = protectionPan;
								protectionHolder.removeAll();
								protectionHolder.add(protectionPan);
								protectionHolder.doLayout();

							};
							if (item=='fromConditionalFormatting')
							// tabOffset = 600
							Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatProtection, [ pcb, _preProtection, true, 600 ]);
							else
								Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatProtection, [ pcb, false, false, 600 ]);


							break;
					}
					// end of switch
					components[e.id] = true;
				}
					// here setting active container - tabChange
					setTimeout(function(){
						var toSet = {};
						if (e.id != 'number'){
							toSet[e.id] = e;
							if (item=='fromConditionalFormatting' && Ext.getCmp('CLR-'+e.id))
								toSet['clrBtnPan'] = Ext.getCmp('CLR-'+e.id).getFooterToolbar();
						} else {
							var ai = Ext.getCmp('main_format_content');
							if (ai) {
								toSet[(ai.layout.activeItem)? ai.layout.activeItem.id : ai.layout.container.items.items[0].id] = ai.layout.activeItem || ai.layout.container.items.items[0];
							}
							if (item=='fromConditionalFormatting')
								toSet['clrBtnPan'] = e.getFooterToolbar();
						}
						setContainers(toSet);
						// end of container management
					},1);
			}
			}
		});

		function applyFormatting(){

			var fontFormat = {};
			var alignFormat = {};
			var fillFormat = {};
			var borderFormat={};
			var numberFormat;
			var protectionFormat = null;

			function getFont(val) {
				fontFormat = val;
			}

			function getAlignment(val) {
				alignFormat = val;
			}

			function getFill(val) {
				fillFormat = val;
			}

			function getBorder(val) {
				borderFormat = val;
			}

			function getNumber(val) {
				numberFormat = val;
			}

			function getProtection(val){
				protectionFormat = val;
			}

			var bgColorT = '';

			var formatToSet = {};

			if (components.font) {
				fontPann.fireEvent('doFontSelect',
						getFont);
				for ( var fnt in fontFormat)
					formatToSet[fnt] = fontFormat[fnt];
			}

			if (components.alignment) {
				alignmentPann.fireEvent(
						'doSelectAlignment',
						getAlignment);
				for ( var aln in alignFormat)
					formatToSet[aln] = alignFormat[aln];
			}

			if (components.fill) {
				fillPann.fireEvent('formatFill',
						getFill);
				for ( var fil in fillFormat)
					formatToSet[fil] = fillFormat[fil];
				if (formatToSet.backgroundColor == '#-1-1-1')
					{formatToSet.backgroundColor = ''; bgColorT = '#-1-1-1'}
			}


			if (item == 'fromConditionalFormatting') {
				//////////////////////////////////////////////////////
				if (!components.font)
					for ( var fnt in initStateCF.preFont)
					formatToSet[fnt] = initStateCF.preFont[fnt];

				if (!components.fill)
					for ( var fill in initStateCF.preFill)
					formatToSet[fill] = initStateCF.preFill[fill];

				if (!components.alignment){
					for ( var al in initStateCF.preAlignment)
					formatToSet[al] = initStateCF.preAlignment[al];
				if (formatToSet.backgroundColor == '#-1-1-1')
				{formatToSet.backgroundColor = ''; bgColorT = '#-1-1-1'}
				}
				//////////////////////////////////////////////////////////////
				var cellFormattingString;

				if (components.border) {
					borderPann.fireEvent('doFormatBorders',
							getBorder);
					for ( var brd in borderFormat)
						formatToSet[brd] = borderFormat[brd];
				} else {
					for ( var brd in initStateCF.preBorders)
						formatToSet[brd] = initStateCF.preBorders[brd];
				}

				if (components.number) {
					numberPann.fireEvent('doFormatNumber',
							getNumber);
					cellFormattingString = numberFormat;
				}

				if (components.protection) {
					protectionPann.fireEvent('doLock',
							getProtection);
				}

					var FCtoCF = [
							formatToSet, cellFormattingString, protectionFormat

					];

					// Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					// Jedox.wss.app.lastInputMode =
					// Jedox.wss.grid.GridMode.READY;
					// Jedox.wss.app.activeSheet._defaultSelection.getCursorField().refresh();
					// RETURN FROM CFDLG!
					addFn(FCtoCF);
					that.win.close();
				}

				else if (item == 'fromPageSetup') {
					//	here page setup
					var FCtoPS = {
						fontFamily : fontFormat.fontFamily,
						textDecoration : fontFormat.textDecoration,
						fontWeight : fontFormat.fontWeight,
						fontSize : fontFormat.fontSize,
						fontStyle : fontFormat.fontStyle,
						color : fontFormat.color
					};

					that.win.close();
					// Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					// Jedox.wss.app.lastInputMode =
					// Jedox.wss.grid.GridMode.READY;
					// Jedox.wss.app.activeSheet._defaultSelection.getCursorField().refresh();
					// RETURN FROM CFDLG!
					addFn(FCtoPS);
				} else {

					//// REGULAR FUNCTION
					// stand-alone formatting
			if (components.number)
				numberPann.fireEvent('doFormatNumber');

			if (components.border)
				borderPann.fireEvent('doFormatBorders');

			if (components.protection)
				protectionPann.fireEvent('doLock');
			// ///////////////////////////////////////////////////////

			for ( var e in formatToSet) {
				if (!formatToSet[e]
						|| formatToSet[e] == ''
						|| formatToSet[e] == formatCellPreConf[e])
					delete formatToSet[e];
			}
			;
			if (bgColorT == '#-1-1-1') formatToSet.backgroundColor='';
					// fire format set
					Jedox.wss.style.set(formatToSet);
					that.win.close();
					// END OF STANDARD FNC
				}

			};

		this.win = new Ext.Window({
					id: 'wFormatCells_dlg_wnd',
					title : 'Format Cells'.localize(),
					closable : true,
					autoDestroy : true,
					plain : true,
					constrain : true,
					cls: 'default-format-window',
					modal : true,
					resizable : false,
					animCollapse : false,
					width : 475,
					height : 500,
					// border:false,
					layout : 'fit',
					items : [ tabs ],
					onEsc: Ext.emptyFn,
					listeners : {
						beforedestroy : function() {
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatCells);
						},
						show:function(){
							setTimeout(function(){
								//that.initFocus(true, 100);
							});
						},
						activate: function(win) {that.activate();},
						close : function() {
							if (!_fromDlgF) {
								Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
								Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							}

							if (components.alignment) Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatAlignment);
							if (components.border) Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatBorder);
							if (components.fill) Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatFill);
							if (components.font) Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatFont);
							if (components.number) Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatNumber);
							if (components.protection) Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatProtection);

							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatCells);
							Jedox.wss.app.activeSheet._defaultSelection.getCursorField().refresh();

							if (item == 'fromPageSetup')
								return false;

//							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
//							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
//							Jedox.wss.app.activeSheet._defaultSelection.getCursorField().refresh();
//							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatCells);
						}
					},
					buttons : [
								(this.components.OK = new Ext.Button({
									text: 'OK'.localize(),
									tabIndex: 1001,
									id: 'wFormatCells_ok_btn',
									handler: function(){
										applyFormatting();
										that.win.close();
									}
								})),
								(this.components.Cancel = new Ext.Button({
									text: 'Cancel'.localize(),
									tabIndex: 1002,
									id: 'wFormatCells_cancel_btn',
									ctCls: Jedox.kbd.Base.tags.NO_ENTER,
									handler: function(){
										that.win.close();
									}
								}))
								]
				});

		// select what to show:

		if (item == 'formatCellsBorders')
			tabs.setActiveTab('border');

		if (item == 'fromConditionalFormatting') {
			//tabs.remove('protection');
			tabs.remove('alignment');
			isFromOther = true;

			// make disabling objects
			_fontToDisable = {
				effects : true,
				size : true,
				type : true
			};
		}
		;

		if (item == 'fromPageSetup') {
			tabs.remove('protection');
			tabs.remove('number');
			tabs.remove('alignment');
			tabs.remove('border');
			tabs.remove('fill');
		}

		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.Format, Jedox.dlg.Dialog);