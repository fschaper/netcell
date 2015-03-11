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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 * Andrej Vrhovac <andrej.vrhovac@develabs.com>
 *
 * \version
 * SVN: $Id: Microchart.js 4837 2011-04-13 12:25:05Z predragm $
 *
 */

Jedox.wss.dlg.chart.openMicroChart = function(inIsEditT){
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.chart.MicroChart(inIsEditT));
};

Jedox.wss.dlg.chart.MicroChart = (function() {
	return function (inIsEditT)
	{
		Jedox.wss.dlg.chart.MicroChart.parent.constructor.call(this);
		this.id = 'microChart';
		var that = this,
			_config =
			{
				imgPath : 'res/img/dialog/',

				winW : 500,
				winH : 370,

				winWhiskerH : 230,
				winPieH : 200,

				colorButtonW : '100px',
				labelWidth : 60,
				textBoxW : 180,
				comboBoxW : 200,

				rowH : 28,
				margingSize : 2,

				posColor : '#000000',
				negColor : '#000000',

				firstColor : '#000000',
				lastColor : '#000000',
				minColor : '#000000',
				maxColor : '#000000',

				winColor : '#000000',
				loseColor : '#000000',
				tieColor : '#000000',

				pieColor : '#000000'
			};

		var _getMChartScaling = function() {
			return [ [ "0..max".localize() ], [ "min..max".localize() ],
					[ "user defined".localize() ] ];
		}

		var win, btnColorPos, btnColorNeg, btnColorFirst, btnColorLast, btnColorMin, btnColorMax, btnSoruceSelect, btnTargetSelect, btnScaleMinSelect, btnScaleMaxSelect, btnColorWin, btnColorTie, btnColorLose, btnColorPie,
			chkFirst, chkLast, chkMinMax, cmbScaling, txtSource, txtTarget, txtMin, txtMax,
			// state variables
			state, isEdit;

		// NAVIGATION
		var navigation = [
		                  ['Bar'.localize(), 'mchart-bar'],
		                  ['Line'.localize(), 'mchart-line'],
		                  ['Dots'.localize(), 'mchart-dots'],
		                  ['Doted Line'.localize(), 'mchart-dotted'],
		                  ['Whisker'.localize(), 'mchart-whisker'],
		                  ['Pie'.localize(), 'mchart-pie']
		                   ];

		var navigationStore = new Ext.data.SimpleStore({
			fields: ['description', 'image'],
			data: navigation
		});

		// Store and Record for Type ComboBox
		var TypeRecord = new Ext.data.Record.create( [ {
			name : 'name'
		} ]);

		// Store and Record for Scaling ComboBox
		var ScalingRecord = new Ext.data.Record.create( [ {
			name : 'name'
		} ]);
		var storeScaling = new Ext.data.SimpleStore( {
			fields : [ {
				name : 'name'
			} ]
		});

		this.init = function(inIsEdit) {
			// Init tooltips for Ext JS
			Ext.QuickTips.init();
			isEdit = inIsEdit;

			// Load stores
			storeScaling.loadData(_getMChartScaling());

			state = {
				type : navigation[0][0],
				type_index : 0,
				scaling : storeScaling.getAt(0).get('name'),

				source : '',
				target : '',

				scaleMin : '',
				scaleMax : '',

				colorPos : _config.posColor,
				colorNeg : _config.negColor,
				colorFirst : _config.firstColor,
				colorLast : _config.lastColor,
				colorMin : _config.minColor,
				colorMax : _config.maxColor,

				colorWin : _config.winColor,
				colorLose : _config.loseColor,
				colorTie : _config.tieColor,

				colorPie : _config.pieColor,

				showFirst : false,
				showLast : false,
				showMinMax : false
			};

			// *** CheckBoxes ***
			chkFirst = new Ext.form.Checkbox( {
				checked : state.showFirst,
				hideLabel : true,
				tabIndex: 24,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				id: 'chkFirst'
			});
			chkLast = new Ext.form.Checkbox( {
				checked : state.showFirst,
				hideLabel : true,
				tabIndex: 26,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				id: 'chkLast'
			});
			chkMinMax = new Ext.form.Checkbox( {
				checked : state.showFirst,
				hideLabel : true,
				tabIndex: 29,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				id: 'chkMinMax'
			});
			// --- CheckBoxes ---

			// *** Buttons ***
			// Color Button for Positive Values
			btnColorPos = new Ext.Toolbar.SplitButton(
					{
						id: 'posButton',
						tabIndex: 20,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						style: 'margin-left:auto;margin-right:auto;',
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorPos = '#' + colorStr;
											_setupColorButton(btnColorPos,
													state.colorPos, false);
										},
										beforeshow : function(thisMenu) {
											//thisMenu.palette.select(state.colorPos);
									}
									}
								})
					});

			// Color Button for Negative Values
			btnColorNeg = new Ext.Toolbar.SplitButton(
					{
						id: 'negButton',
						tabIndex: 21,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						style: 'margin-left:auto;margin-right:auto;',
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorNeg = '#' + colorStr;
											_setupColorButton(btnColorNeg,
													state.colorNeg, false);
										},
										beforeshow : function(thisMenu) {
											thisMenu.palette.select(state.colorNeg);
										}
									}
								})
					});

			// Color Button for First Value
			btnColorFirst = new Ext.Toolbar.SplitButton(
					{
						tabIndex: 22,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorFirst = '#' + colorStr;
											_setupColorButton(btnColorFirst,
													state.colorFirst, false);
										},
										beforeshow : function(thisMenu) {
											thisMenu.palette
													.select(state.colorFirst);
										}
									}
								})
					});

			// Color Button for Last Value
			btnColorLast = new Ext.Toolbar.SplitButton(
					{
						tabIndex: 25,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorLast = '#' + colorStr;
											_setupColorButton(btnColorLast,
													state.colorLast, false);
										},
										beforeshow : function(thisMenu) {
											thisMenu.palette
													.select(state.colorLast);
										}
									}
								})
					});

			// Color Button for Min Value
			btnColorMin = new Ext.Toolbar.SplitButton(
					{
						tabIndex: 27,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorMin = '#' + colorStr;
											_setupColorButton(btnColorMin,
													state.colorMin, false);
										},
										beforeshow : function(thisMenu) {
											thisMenu.palette.select(state.colorMin);
										}
									}
								})
					});

			// Color Button for Max Value
			btnColorMax = new Ext.Toolbar.SplitButton(
					{
						minWidth : 50,
						tabIndex: 28,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorMax = '#' + colorStr;
											_setupColorButton(btnColorMax,
													state.colorMax, false);
										},
										beforeshow : function(thisMenu) {
											thisMenu.palette.select(state.colorMax);
										}
									}
								})
					});

			// Color Button for Whisker Win Value
			btnColorWin = new Ext.Toolbar.SplitButton(
					{
						tabIndex: 40,
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorWin = '#' + colorStr;
											_setupColorButton(btnColorWin,
													state.colorWin, false);
										},
										beforeshow : function(thisMenu) {
											thisMenu.palette.select(state.colorWin);
										}
									}
								})
					});

			// Color Button for Whisker Lose Value
			btnColorLose = new Ext.Toolbar.SplitButton(
					{
						tabIndex: 42,
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorLose = '#' + colorStr;
											_setupColorButton(btnColorLose,
													state.colorLose, false);
										},
										beforeshow : function(thisMenu) {
											thisMenu.palette
													.select(state.colorLose);
										}
									}
								})
					});

			// Color Button for Whisker Tie Value
			btnColorTie = new Ext.Toolbar.SplitButton(
					{
						tabIndex: 41,
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorTie = '#' + colorStr;
											_setupColorButton(btnColorTie,
													state.colorTie, false);
										},
										beforeshow : function(thisMenu) {
											thisMenu.palette.select(state.colorTie);
										}
									}
								})
					});

			// Color Button for Pie micro charts
			btnColorPie = new Ext.Toolbar.SplitButton(
					{
						id: 'btnColorPie',
						menu : new Ext.menu.ColorMenu(
								{
									colors : Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
									cls : 'wide-color-palette',
									listeners : {
										select : function(colorP, colorStr) {
											state.colorPie = '#' + colorStr;
											_setupColorButton(btnColorPie,
													state.colorPie, false);
										},
										beforeshow : function(thisMenu) {
											thisMenu.palette.select(state.colorPie);
										}
									}
								})
					});

			// Select Range button for Source
			btnSoruceSelect = new Ext.Toolbar.Button( {
				iconCls : 'select-range-icon',
				cls : 'x-btn-icon',
				tabIndex: 11,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tooltip : "Select Range".localize(),
				listeners : {
					click : function() {
						that.win.hide();
						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange,
								[ {
									fnc : [this, function(tmpStr) {
										txtSource.setValue(tmpStr);
										that.win.show();
									}],
									format : '{Sheet}!{Range}',
									rng: txtSource.getValue()
								} ]);
					}
				}
			});

			// Select Range button for Target
			btnTargetSelect = new Ext.Toolbar.Button( {
				disabled : true,
				tabIndex: 13,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				iconCls : 'select-range-icon',
				cls : 'x-btn-icon',
				tooltip : "Select Cell".localize(),
				listeners : {
					click : function() {
						that.win.hide();
						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange,
								[ {
									fnc : [this, function(tmpStr) {
										txtTarget.setValue(tmpStr);
										that.win.show();
									}],
									singleCell : true,
									format : '{Range}',
									rng: txtTarget.getValue()
								} ]);
					}
				}
			});

			// Select Range button for Scale Min
			btnScaleMinSelect = new Ext.Toolbar.Button( {
				disabled : true,
				iconCls : 'select-range-icon',
				cls : 'x-btn-icon',
				tabIndex: 32,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tooltip : "Select Cell".localize(),
				listeners : {
					click : function() {
						that.win.hide();
						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange,
								[ {
									fnc : [this, function(tmpStr) {
										txtMin.setValue(tmpStr);
										that.win.show();
									}],
									singleCell : true,
									format : '{Sheet}!{Range}',
									rng: txtMin.getValue()
								} ]);
					}
				}
			});

			// Select Range button for Scale Max
			btnScaleMaxSelect = new Ext.Toolbar.Button( {
				disabled : true,
				tabIndex: 34,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				iconCls : 'select-range-icon',
				cls : 'x-btn-icon',
				tooltip : "Select Cell".localize(),
				listeners : {
					click : function() {
						that.win.hide();
						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange,
								[ {
									fnc : [this, function(tmpStr) {
										txtMax.setValue(tmpStr);
										that.win.show();
									}],
									singleCell : true,
									format : '{Sheet}!{Range}',
									rng: txtMax.getValue()
								} ]);
					}
				}
			});
			// --- Buttons ---

			// *** ComboBoxes ***

			// Scaling Combo + Panel
			cmbScaling = new Ext.form.ComboBox( {
				store : storeScaling,
				id: 'cmbScaling',
				width: 155,
				tabIndex: 30,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				bodyStyle : 'background-color:transparent;',
				typeAhead : true,
				selectOnFocus : true,
				fieldLabel : "Scaling".localize(),
				editable : false,
				forceSelection : true,
				triggerAction : 'all',
				mode : 'local',
				valueField : 'name',
				displayField : 'name',
				listeners: {
					select: _handleScaleChange
				}
			});
			cmbScaling.setValue(state.scaling);
			// --- ComboBoxes ---

			// *** TextBoxes ***
			// Source and Target + border Panel
			txtSource = that.cmpFocus = new Ext.form.TextField( {
				value : state.source,
				tabIndex: 10,
				fieldLabel : "Source".localize(),
				autoWidth: true,
				id: 'txtSource'
			});
			txtTarget = new Ext.form.TextField( {
				disabled : true,
				tabIndex: 12,
				value : state.target,
				fieldLabel : "Target".localize(),
				autoWidth: true,
				id: 'txtTarget'
			});

			// Min and Max TextBoxes + border Panel
			txtMin = new Ext.form.TextField( {
				disabled : true,
				tabIndex: 31,
				value : state.scaleMin,
				fieldLabel : "Min".localize(),
				id: 'txtMin'
			});
			txtMax = new Ext.form.TextField( {
				disabled : true,
				tabIndex: 33,
				value : state.scaleMax,
				fieldLabel : "Max".localize(),
				id: 'txtMax'
			});

			// COLOR PANELS
			var primaryColorPanel = new Ext.Panel({
				baseCls: 'x-plain',
				id: 'primaryColorPanel',
				border: false,
				layout: 'form',
				items: [
				        //color selectors
				        new Ext.Panel({
				        	layout: 'column',
				        	border: false,
				        	baseCls: 'x-plain',
				        	bodyStyle: 'margin-bottom: 5px;',
				        	items: [
				        	        {
				        	        	html: 'Pos. Values'.localize(),
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.30
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.20,
				        	        	items: btnColorPos
				        	        },
				        	        {
				        	        	html: 'Neg. Values'.localize(),
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.30
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.20,
				        	        	items: btnColorNeg
				        	        }
				        	        ]
				        }),
				        {
				        	baseCls: 'x-plain',
				        	bodyStyle: 'margin-top: 5px;',
				        	html: '<div style="border-top: 1px solid #B5B8C8;"></div>'
				        },
				        {
				        	html: 'Values'.localize(),
				        	baseCls: 'x-plain',
				        	bodyStyle: 'text-align: right; margin-top: 5px;'
				        },
				        new Ext.Panel({
				        	layout: 'column',
				        	border: false,
				        	baseCls: 'x-plain',
				        	items: [
				        	        {
				        	        	html: 'First'.localize(),
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.35
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.55,
				        	        	items: btnColorFirst
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.10,
				        	        	items: chkFirst
				        	        }
				        	        ]
				        }),
				        new Ext.Panel({
				        	layout: 'column',
				        	border: false,
				        	baseCls: 'x-plain',
				        	items: [
				        	        {
				        	        	html: 'Last'.localize(),
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.35
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.55,
				        	        	items: btnColorLast
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.10,
				        	        	items: chkLast
				        	        }
				        	        ]
				        }),
				        new Ext.Panel({
				        	// MINMAX holder
				        	layout: 'column',
				        	border: false,
				        	baseCls: 'x-plain',
				        	items: [
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.90,
				        	        	items: [
				        	        	        new Ext.Panel({
				        	        	        	layout: 'column',
				        	        	        	border: false,
				        	        	        	baseCls: 'x-plain',
				        	        	        	items: [
				        	        	        	        {
				    			        	        	html: 'Min'.localize(),
				    			        	        	baseCls: 'x-plain',
				    			        	        	columnWidth : 0.39
				    			        	        },
				    			        	        {
				    			        	        	layout: 'form',
				    			        	        	border: false,
				    			        	        	baseCls: 'x-plain',
				    			        	        	columnWidth : 0.61,
				    			        	        	items: btnColorMin
				    			        	        }]
				        	        	        }),
				        	        	        new Ext.Panel({
				        	        	        	layout: 'column',
				        	        	        	border: false,
				        	        	        	baseCls: 'x-plain',
				        	        	        	bodyStyle: 'padding-top: 7px;',
				        	        	        	items: [
				        	        	        	        {
				    			        	        	html: 'Max'.localize(),
				    			        	        	baseCls: 'x-plain',
				    			        	        	columnWidth : 0.39
				    			        	        },
				    			        	        {
				    			        	        	layout: 'form',
				    			        	        	border: false,
				    			        	        	baseCls: 'x-plain',
				    			        	        	columnWidth : 0.61,
				    			        	        	items: btnColorMax
				    			        	        }]
				        	        	        })
				        	        	        ]
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	bodyStyle: 'padding-top: 14px;',
				        	        	columnWidth : 0.10,
				        	        	items: chkMinMax
				        	        }
				        	        ]
				        })
				        ]
			});

			var secondaryColorPanel = new Ext.Panel({
				baseCls: 'x-plain',
				border: false,
				id: 'secondaryColorPanel',
				layout: 'form',
				items: [
				        //color selectors
				        new Ext.Panel({
				        	layout: 'column',
				        	border: false,
				        	baseCls: 'x-plain',
				        	items: [
				        	        {
				        	        	html: 'Win'.localize(),
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.35
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.65,
				        	        	items: btnColorWin
				        	        }
				        	        ]
				        }),
				        new Ext.Panel({
				        	layout: 'column',
				        	border: false,
				        	bodyStyle: 'padding-top: 7px;',
				        	baseCls: 'x-plain',
				        	items: [
				        	        {
				        	        	html: 'Tie'.localize(),
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.35
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.65,
				        	        	items: btnColorTie
				        	        }
				        	        ]
				        }),
				        new Ext.Panel({
				        	layout: 'column',
				        	border: false,
				        	bodyStyle: 'padding-top: 7px;',
				        	baseCls: 'x-plain',
				        	items: [
				        	        {
				        	        	html: 'Lose'.localize(),
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.35
				        	        },
				        	        {
				        	        	layout: 'form',
				        	        	border: false,
				        	        	baseCls: 'x-plain',
				        	        	columnWidth : 0.65,
				        	        	items: btnColorLose
				        	        }
				        	        ]
				        })
				        ]
			});


			// ###############################################################################

			var scalingPanel = new Ext.Panel({
				border: 'false',
				baseCls: 'x-plain',
				id: 'scalingPanel',
				layout: 'form',
				items: [
				    cmbScaling,
					new Ext.Panel({
						layout: 'column',
						border: false,
						baseCls: 'x-plain',
						items: [
						        {
						        	layout: 'form',
						        	border: false,
						        	baseCls: 'x-plain',
						        	items: txtMin
						        },
						        {
						        	layout: 'form',
						        	border: false,
						        	baseCls: 'x-plain',
						        	items: btnScaleMinSelect
						        }
						        ]
					}),
					new Ext.Panel({
						layout: 'column',
						border: false,
						baseCls: 'x-plain',
						items: [
						        {
						        	layout: 'form',
						        	border: false,
						        	baseCls: 'x-plain',
						        	items: txtMax
						        },
						        {
						        	layout: 'form',
						        	border: false,
						        	baseCls: 'x-plain',
						        	items: btnScaleMaxSelect
						        }
						        ]
					})
				        ]
			});

			var topFldPanel = that.containers.topPanel = new Ext.Panel({
				layout: 'form',
				baseCls: 'x-plain',
				items: [
					//txtSource, txtTarget
					new Ext.Panel({
						layout: 'column',
						border: false,
						baseCls: 'x-plain',
						items: [
						        {
						        	layout: 'form',
						        	border: false,
						        	baseCls: 'x-plain',
						        	items: txtSource
						        },
						        {
						        	layout: 'form',
						        	border: false,
						        	baseCls: 'x-plain',
						        	items: btnSoruceSelect
						        }
						        ]
					}),
					new Ext.Panel({
						layout: 'column',
						border: false,
						baseCls: 'x-plain',
						items: [
						        {
						        	layout: 'form',
						        	border: false,
						        	baseCls: 'x-plain',
						        	items: txtTarget
						        },
						        {
						        	layout: 'form',
						        	border: false,
						        	baseCls: 'x-plain',
						        	items: btnTargetSelect
						        }
						        ]
					})
				        ]
			});

			var mainPanel = new Ext.Panel({
				layout: 'form',
				bodyStyle: 'padding-left: 10px; background-color:transparent;',
				border: false,
				items: [
				        topFldPanel,
				        // HERE COLOR PANEL !!!
				        new Ext.Panel({
				        	layout : 'form',
							xtype : 'fieldset',
							autoHeight : true,
							baseCls : 'x-plain',
							border : false,
							frame : false,
							items : [ {
								border : true,
								autoHeight : true,
								xtype : 'fieldset',
								layout : 'card',
								id: 'generalColorCt',
								frame : false,
								title : 'Color'.localize(),
								activeItem: 0,
								layoutOnCardChange: true,
								// Color Panel. Must have 3 container panels, depending of MicroChart type ( {bar, line, dots, dottedLine}, {whisker}, {pie})
								items : [
								         primaryColorPanel,
								         secondaryColorPanel,
								         new Ext.Panel({
								        	 width: 100,
								        	 id: 'colorPieBtnPanel',
								        	 baseCls: 'x-plain',
								        	 items: btnColorPie
								         })
								         ]
							} ]
				        })
				        // End of Color Panel
				        ,scalingPanel
				        ]
			});

			mainPanel.doLayout();

			var navigationView = new Ext.DataView({
				id: 'chart-navigation',
				store: navigationStore,
				tpl: new Ext.XTemplate(
						'<div class="hyperlink-navigation"><tpl for=".">', '<div class="thumb-wrap">',
						'<div class="thumb" style="padding: 5px; text-align: left; font-size: 11px;"><img class="{image}" src="../lib/ext/resources/images/default/s.gif" width="55" height="20"/>',
						'<div style="display:inline; position: absolute; left: 100px;">{description}</div></div></div></tpl>','</div>'
						),
						autoHeight: true,
						multiSelect: false,
						singleSelect: true,
						overClass: 'x-view-over',
						itemSelector: 'div.thumb-wrap',
						emptyText: 'No images to display'.localize(),
						listeners: {
								click: function(cmp, index, node, e){
									var gcct = Ext.getCmp('generalColorCt').layout;
									state.type_index = index;
									state.type = navigation[index][0];
									if (index >= 0 && index <= 3)  // Bar, Line, Dots, DotedLine
										{
										gcct.setActiveItem(0);
										scalingPanel.show();
										that.containers.scalingPanel = scalingPanel;
										}
									else if (index == 4) // Whisker
										{
										gcct.setActiveItem(1);
										scalingPanel.hide();
										delete that.containers.scalingPanel;
										}
									else if (index == 5) // Pie
										{
										gcct.setActiveItem(2);
										scalingPanel.hide();
										delete that.containers.scalingPanel;
										}

									that.containers.mainPanel = gcct.activeItem;
									setTimeout(function(){_resizeAll(); mainPanel.doLayout();},10);
									 }
									 }
			});


			// *** Window ***
			that.win = new Ext.Window(
			{
				hidden : true,
				layout : 'fit',
				title : "Micro Chart".localize(),
				width : 500,
				height : 440,
				bodyStyle : 'padding: 10px;',
				cls: 'default-format-window',
				autoDestroy : true,
				plain : true,
				modal : true,
				resizable : false,
				onEsc: Ext.emptyFn,
				listeners : {
					activate : function(win){
						that.activate();
						_resizeAll();
					},
					show:function(){
						setTimeout(function(){
							that.initFocus(true, 200);
						});
					},
					close : function() {
						Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
						Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
						that.close();
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.openMicroChart);
					}
				},
				items : [ new Ext.Panel(
						{
							id : 'microChartWinCtPanel',
							layout : 'column',
							baseCls : 'x-plain',
							border : false,
							frame : false,
							items : [
									{
										//	right side of border tab - column start
										columnWidth : 0.35,
										layout : 'form',
										xtype : 'fieldset',
										autoHeight : true,
										baseCls : 'x-plain',
										border : false,
										frame : false,
										items : [ {
											border : true,
											autoHeight : true,
											xtype : 'fieldset',
											layout : 'form',
											frame : false,
											title : 'Micro Chart Type'.localize(),
											items : [navigationView]
										} ]
									},
									{
										//	right side of border tab - column start
										columnWidth : 0.65,
										layout : 'form',
										xtype : 'fieldset',
										autoHeight : true,
										autoScroll : false,
										border : false,
										frame : false,
										items : [mainPanel] // items!
									} ]
						}) ],
				buttons : [
						(this.components.OK = new Ext.Button({
							text: 'OK'.localize(),
							tabIndex: 101,
							handler: function(){
								// need to fill Data in state object
								var tmpVal;

								state.source = txtSource.getValue();
								state.target = txtTarget.getValue();
								state.target_cell = [ 1, 1 ];
								state.scaling = cmbScaling.getValue();
								state.scaling_index = storeScaling.find('name', cmbScaling.getValue());

								state.scaleMin = txtMin.getValue();
								state.scaleMax = txtMax.getValue();

								state.showFirst = chkFirst.getValue();
								state.showLast = chkLast.getValue();
								state.showMinMax = chkMinMax.getValue();

								// send information to server
								var activeBook = Jedox.wss.app.activeBook;
								var upperLeftCoords = Jedox.wss.app.environment.defaultSelection.getActiveRange().getUpperLeft();

								state.upCellX = upperLeftCoords.getX();
								state.upCellY = upperLeftCoords.getY();

								Jedox.backend.rpc_cb('mc_getFuncFromState',[ state ]);
								that.win.close();
							}
						})),
						(this.components.Cancel = new Ext.Button({
							text: 'Cancel'.localize(),
							tabIndex: 102,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							handler: function(){
								that.win.close();
							}
						}))
				]
			});
		} /* <--- end of this.init */

		this.show = function()
		{
			// Set DIALOG work on Grid
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

			//
			that.win.show(that);

			// Setting inital values for state variables
			var upperLeftCoords = Jedox.wss.app.environment.defaultSelection.getActiveRange().getUpperLeft();
			var tmpVal = Jedox.wss.app.activePane.getCellFormula(upperLeftCoords.getX(), upperLeftCoords.getY());

			if (isEdit && tmpVal)
			{
				var mcRpc = new Jedox.backend.RPCAsyncRqst('microchart', 'getStateFromFunc', [tmpVal, Jedox.wss.i18n.separators[2]]);
				mcRpc.setOnSuccess([
					that,
					function(result)
					{
						for ( var prop in result)
							state[prop] = result[prop];
						_setValuesFromState();
						Ext.MessageBox.hide();
					}
				]);
				mcRpc.setOnError([that, function() {}]);
				mcRpc.setOnTimeout([that, function() { Ext.MessageBox.hide(); }]);
				mcRpc.send();

				Ext.MessageBox.show( {
					title : "Please wait".localize(),
					id: 'obtDataMsg',
					msg : '<b><br>' + "Obtaining data!".localize() + '</b>',
					closable : false,
					icon : 'largeLoadingImage'
				});
			} else {
				Ext.getCmp('chart-navigation').select(0);
				Ext.getCmp('chart-navigation').fireEvent('click', this, 0);
			}
		}

		// *** Other Functions ***
		var _setupColorButton = function(colorBtn, color, setWidth) {
			var tmpElem = Ext.DomQuery
					.selectNode('*[id=' + colorBtn.btnEl.id + ']');
			if (color && color != '')
				tmpElem.style.background = color;
			else
				tmpElem.style.background = "#000000";

			tmpElem.style.width = (colorBtn.id == 'posButton' || colorBtn.id == 'negButton')? "20px" : "100px";
			tmpElem.style.height = "15px";
		}

		var _changeLayoutByType = function(index) {
			Ext.getCmp('chart-navigation').fireEvent('click', this, index);
			Ext.getCmp('chart-navigation').select(index);
		}

		var _handleScaleChange = function(combo, record, index)
		{
			// when it's selected "user defined"
			if (index == 2)
			{
				Ext.getCmp('txtMin').enable();
				Ext.getCmp('txtMax').enable();
				btnScaleMinSelect.enable();
				btnScaleMaxSelect.enable();
			}
			else
			{
				Ext.getCmp('txtMin').disable();
				Ext.getCmp('txtMax').disable();
				btnScaleMinSelect.disable();
				btnScaleMaxSelect.disable();
			}
		}

		var _setValuesFromState = function() {
			if (state) {
				_changeLayoutByType(state.type_index);
				Ext.getCmp('txtSource').setValue(state.source);
				Ext.getCmp('txtTarget').setValue(state.target);

				if (state.type_index <= 3) // Bars, Lines, Dots and DotedLines
				{
					Ext.getCmp('cmbScaling').setValue(storeScaling.getAt(state.scaling_index)
							.get('name'));
					_handleScaleChange(storeScaling, storeScaling
							.getAt(state.scaling_index), state.scaling_index);

					Ext.getCmp('txtMin').setValue(state.scaleMin);
					Ext.getCmp('txtMax').setValue(state.scaleMax);
					_setupColorButton(btnColorPos, state.colorPos);
					_setupColorButton(btnColorNeg, state.colorNeg);
					_setupColorButton(btnColorFirst, state.colorFirst);
					_setupColorButton(btnColorLast, state.colorLast);
					_setupColorButton(btnColorMin, state.colorMin);
					_setupColorButton(btnColorMax, state.colorMax);

					Ext.getCmp('chkFirst').setValue(state.showFirst);
					Ext.getCmp('chkLast').setValue(state.showLast);
					Ext.getCmp('chkMinMax').setValue(state.showMinMax);
				} else if (state.type_index == 4) {
					_setupColorButton(btnColorWin, state.colorWin);
					_setupColorButton(btnColorTie, state.colorTie);
					_setupColorButton(btnColorLose, state.colorLose);
				} else if (state.type_index == 5)
					_setupColorButton(btnColorPie, state.colorPie);
			}
		}
		// --- Other Functions ---

		// "resize" window and all components. Also positioning of components
		var _resizeAll = function()
		{
			setTimeout(function() {
				// *** Buttons
					// panelPN.doLayout();
					if (state.type_index == 5)  _setupColorButton(btnColorPie, state.colorPie, true); // ColorButton PIE COLOR
					else if (state.type_index == 4) {
						// Color Button Win
						 _setupColorButton(btnColorWin, state.colorWin, true);
						// Color Button Tie
						 _setupColorButton(btnColorTie, state.colorTie, true);
						// Color Button Lose
						 _setupColorButton(btnColorLose, state.colorLose, true);
					}
					else {
					// Color Button +
					 _setupColorButton(btnColorPos, state.colorPos, true);
					// Color Button -
					 _setupColorButton(btnColorNeg, state.colorNeg, true);
					// Color Button First
					_setupColorButton(btnColorFirst, state.colorFirst, true);
					// Color Button Last
					_setupColorButton(btnColorLast, state.colorLast, true);
					// Color Button Min
					_setupColorButton(btnColorMin, state.colorMin, true);
					// Color Button Max
					_setupColorButton(btnColorMax, state.colorMax, true);
					}
				},
				1
			);
		}

		this.init(inIsEditT);
		this.setContext();
		this.show();
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.chart.MicroChart, Jedox.dlg.Dialog);