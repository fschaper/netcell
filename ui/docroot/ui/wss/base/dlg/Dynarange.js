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
 *
 * \version
 * SVN: $Id: Dynarange.js 4379 2010-12-01 15:10:16Z mladent $
 *
 */

Jedox.wss.dlg.openDynarange = function (conf) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.Dynarange(conf));
};

Jedox.wss.dlg.Dynarange = (function() {

	return function (conf) {

		Jedox.wss.dlg.Dynarange.parent.constructor.call(this);
		this.id = 'Dynarange';
		var that = this;

		var _config = {
			imgPath: 'res/img/dialog/',

			winW: 580,
			rbWidth: 100,
			btmFsHeight: 180,

			sampleFieldSetH: 130,
			samplePanelW: 70,
			samplePanelH: 50,

			mainLabelW: 60,
			txtNameFieldW: 200,
			borderColorButtonW: 80,
			displayLabelW: 180,
			displayFieldW: 70,

			// hb config defaults
			columnWidth: 12.57,
			borderColor: '#000000'
		};

		var SoruceForm = Ext.extend(Ext.Panel,
		{
			// pre-config
			border: false,
			bodyStyle: 'background-color: transparent;',
			autoWidth: true,
			autoHeight: true,
			rbWidth: 100,
			labelWidth: 75,
			textWidth: 250,
			comboLabel: "Subset".localize(),
			textFieldLabel: "Formula".localize(),

			typeDisabled: false,
			functionValue: '',
			genData: null,
			previewValue: '',
			dynarangeConf: null,

			getFuncText: function()
			{
				return this._txtFunc.getValue();
			},

			getTypeDisabled: function()
			{
				return this.typeDisabled;
			},

			getGenData: function()
			{
				return (this.typeDisabled) ? [[-1, '', 'FN']] : this.genData;
			},

			getPreviewValue: function()
			{
				return (this.typeDisabled) ? '' : this.previewValue;
			},

			initComponent: function()
			{
				thats = this;

				// confing
				Ext.apply(this, {
					layout: 'form'
				});

				SoruceForm.superclass.initComponent.call(this);

				var setFuncText = function(result)
				{
					thats._txtFunc.setValue(result.ss_func);
					thats.genData = result._gendata;
					thats.previewValue = result._preview_val;
				};

				this._rbTypes = new Ext.form.Radio({
					checked: !this.typeDisabled,
					name: 'radioSourceForm',
					tabIndex: 3,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					boxLabel: this.comboLabel,

					hideLabel: true,
					listeners: {
						check: function(thisRb, isChecked)
						{
							if (isChecked)
							{
								thats.typeDisabled = false;

								thats._btnWizard.enable();
								thats._txtFunc.disable();
							}
						}
					}
				});

				this._btnWizard = new Ext.Button({
					disabled: this.typeDisabled,
					ctCls: 'stdButtonsSmall '.concat(Jedox.kbd.Base.tags.NO_ENTER),
					text: '...',
					tabIndex: 4,
					listeners: {
						click: function()
						{
							Jedox.gen.load(
								Jedox.wss.app.dynJSRegistry.subsetEditor,
								[
									{
										mode: 4,
										fnc: setFuncText,
										dynarange: ((thats.dynarangeConf._gendata[0][0] == -1) ? null : thats.dynarangeConf)
									}
								]
							);
						}
					}
				});

				this._rbFunc = new Ext.form.Radio({
					checked: this.typeDisabled,
					name: 'radioSourceForm',
					boxLabel: this.textFieldLabel,
					tabIndex: 2,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					hideLabel: true,
					listeners: {
						check: function(thisRb, isChecked)
						{
							if (isChecked)
							{
								thats.typeDisabled = true;

								thats._btnWizard.disable();
								thats._txtFunc.enable();
							}
						}
					}
				});

				this._txtFunc = new Ext.form.TextField({
					disabled: !this.typeDisabled,
					hideLabel: true,
					tabIndex: 5,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					width: this.textWidth,
					allowBlank: true,
					value: this.functionValue
				});

				this.add(new Ext.Panel({
							border: false,
							layout: 'column',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
										new Ext.Panel({
											labelWidth: this.labelWidth,
											border: false,
											layout: 'form',
											bodyStyle: 'background-color:transparent;',
											width: this.rbWidth,
											autoHeight: true,
											items: [this._rbFunc]
										}),
										new Ext.Panel({
											labelWidth: this.labelWidth,
											border: false,
											layout: 'form',
											bodyStyle: 'background-color:transparent;',
											width: this.rbWidth,
											autoHeight: true,
											items: [this._rbTypes]
										}),
										{
											border: false,
											bodyStyle: 'background-color:transparent;',
											html: '&nbsp;&nbsp;&nbsp;'
										},
										new Ext.Panel({
											border: false,
											layout: 'form',
											bodyStyle: 'background-color:transparent;',
											autoWidth: true,
											autoHeight: true,
											items: [this._btnWizard]
										})
									]
						})
				);
				this.add(this._txtFunc);
			}
		});

		var thats = this;

		var panelMain, panelDrillDownLevel, panelColWidth, panelcmbDrillDownLevel, panelSample, panelSrc, fsDisplay, fsBorder, fsSample, fsDirection, fsSource;
		var lblBorderColor, txtHbName, txtFixedColWidth, chbShowAlias, cmbDrillDownLevel, cmbBorderType, cmbBorderWidth, chbDrillDownLevel,
			chbIndentText, chbColWidth, btnBorderColor, btnOk, btnClose, rbRight, rbDown, rbFixedWidth, rbAutoWidth;

		// state variables
		var hbConf, borderColor;

		// +++ Stores and Records +++

		// Drill Down Level Record and Store
		var DrillDownLevelRecord = new Ext.data.Record.create([{
			name: 'name'
		}]);
		var storeDrillDownLevel = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// pattern filling style
		var storeBorderType = new Ext.data.SimpleStore({
			fields: [
				{name: 'id'},
				{name: 'name'},
				{name: 'style'}
			]
		});

		//
		var storeBorderWidth = new Ext.data.SimpleStore({
			fields: [
				{name: 'id'},
				{name: 'name'},
				{name: 'width'}
			]
		});
		// --- Stores and Records ---

		// +++ Store Functions +++
		// Drill down level list
		var _getDrillDownLevelList = function()
		{
			return [
				['1'],
				['2'],
				['3'],
				['4'],
				['5'],
				['6'],
				['7'],
				['8'],
				['9'],
				['10']
			];
		};

		// Border type
		var _getBorderTypeList = function()
		{
			return [
				[0, "None".localize(), 'none'],
				[1, "Solid".localize(), 'solid'],
				[2, "Dotted".localize(), 'dotted'],
				[3, "Dashed".localize(), 'dashed']
			];
		};

		// Border type
		var _getBorderWidthList = function()
		{
			return [
				[0, '1', '1'],
				[1, '2', '2']
			];
		};
		// --- Store Functions ---

		// *** INIT ***
		this.init = function(inHbConf)
		{
			// +++ inital settings +++
			var initHbConf = {
				dir: 0, // direction
				drill: true, // drill down enabled
				level: 2, // drill down begin level
				border: '1px solid #000000', // border css definition
				indent: false, // indent data enabled,
				name: "_name: UnnamedHb".localize()
			};

			hbConf = {};
			if (inHbConf)
			{
				hbConf = inHbConf;
				if (!inHbConf.cwidth)
					delete initHbConf.cwidth;
			}

			for (var prop in initHbConf)
				if (!hbConf[prop] && hbConf[prop] == null)
					hbConf[prop] = initHbConf[prop];

			borderColor = _getBorderInfo(hbConf.border)[2];

			storeDrillDownLevel.loadData(_getDrillDownLevelList());
			storeBorderType.loadData(_getBorderTypeList());
			storeBorderWidth.loadData(_getBorderWidthList());
			// --- inital settings ---

			// +++ Labels and TextBoxes +++
			// Border -> Color
			lblBorderColor = new Ext.form.MiscField({
				value: "Color".localize() + ':',
				height: 22,
				bodyStyle: 'background-color: transparent;',
				hideLabel: true
			});

			// Name
			txtHbName = new Ext.form.TextField({
				disabled: true,
				value: hbConf.id, //hbConf.name + hbConf.id,
				width: _config.txtNameFieldW,
				tabIndex: 1,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				fieldLabel: "Name".localize()
			});

			// Display -> Fixed Width
			txtFixedColWidth = new Ext.form.TextField({
				disabled: !(hbConf.cwidth) || (!!(hbConf.cwidth) && (hbConf.cwidth == 'auto')),
				value: ((hbConf.cwidth && hbConf.cwidth != 'auto') ? hbConf.cwidth : _config.columnWidth),
				hideLabel: true,
				tabIndex: 26,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				width: _config.displayFieldW + 5
			});
			// --- Labels and TextBoxes ---

			// +++ Buttons +++
			// Border -> Color
			btnBorderColor = new Ext.Toolbar.SplitButton({
				tabIndex: 30,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				menu: new Ext.menu.ColorMenu({
					colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
					cls: 'wide-color-palette',
					listeners: {
						select: function(colorP, colorStr)
						{
							borderColor = '#' + colorStr;
							var tmpElem = Ext.DomQuery.selectNode('*[id=' + btnBorderColor.btnEl.id + ']');
							tmpElem.style.background = borderColor;

							_updateBorderSample();
						},
						beforeshow: function(thisMenu)
						{
							thisMenu.palette.select(borderColor);
						}
					}
				})
			});

			// OK && Close
			btnOk = that.components.OK = new Ext.Button({
				text: "OK".localize(),
				tabIndex: 101,
				listeners: {
					click: function()
					{
						// Fill hbConf with new Properties
						hbConf.alias = chbShowAlias.getValue();
						hbConf.drill = chbDrillDownLevel.getValue();
						hbConf.level = cmbDrillDownLevel.getValue();
						hbConf.indent = chbIndentText.getValue();

						// Direction
						hbConf.dir = ((rbRight.getValue()) ? 1 : 0);

						// DONE: finish Border data
						hbConf.border = storeBorderWidth.getAt(storeBorderWidth.find('id', cmbBorderWidth.getValue())).get('width')  + 'px ' + storeBorderType.getAt(storeBorderType.find('id', cmbBorderType.getValue())).get('style') + ' ' + borderColor;

						if (chbColWidth.getValue())
							hbConf.cwidth = rbAutoWidth.getValue() ? 'auto' : txtFixedColWidth.getValue();
						else if (hbConf.cwidth)
							delete hbConf.cwidth;

						hbConf.ss_func = panelSrc.getFuncText(); // function
						hbConf._gendata = panelSrc.getGenData();
						hbConf._preview_val = panelSrc.getPreviewValue();

						Jedox.wss.hb.propDlgCB(hbConf);

						that.win.close();
					}
				}
			});
			btnClose = that.components.Cancel = new Ext.Button({
				text: "Close".localize(),
				tabIndex: 102,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					click: function()
					{
						that.win.close();
					}
				}
			});
			// --- Buttons ---

			// +++ Radio Buttons +++
			rbDown = new Ext.form.Radio({
				name: 'hbDirection',
				boxLabel: ("Vertical".localize()).concat('&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'),
				hideLabel: true,
				tabIndex: 10,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				checked: !(hbConf.dir)
			});
			rbRight = new Ext.form.Radio({
				name: 'hbDirection',
				boxLabel: "Horizontal".localize(),
				hideLabel: true,
				tabIndex: 11,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				checked: (hbConf.dir)
			});
			rbAutoWidth = new Ext.form.Radio({
				disabled: !(hbConf.cwidth),
				name: 'drColWidth',
				tabIndex: 27,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "auto".localize(),
				hideLabel: true,
				checked: !!(hbConf.cwidth) && (hbConf.cwidth == 'auto')
			});
			rbFixedWidth = new Ext.form.Radio({
				disabled: !(hbConf.cwidth),
				tabIndex: 25,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'drColWidth',
				boxLabel: ("fixed".localize()).concat('&nbsp;&nbsp;&nbsp;'),
				hideLabel: true,
				checked: !(hbConf.cwidth) || (hbConf.cwidth != 'auto'),
				listeners: {
					check: function(thisrB, checked)
					{
						if (checked)
							txtFixedColWidth.enable();
						else
							txtFixedColWidth.disable();
					}
				}
			});
			// --- Radio Buttons ---

			// +++ CheckBoxes +++
			// Display -> Drill Down
			chbDrillDownLevel = new Ext.form.Checkbox({
				checked: hbConf.drill,
				width: _config.displayLabelW,
				hideLabel: true,
				tabIndex: 21,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Drill down, begin at level".localize() + ':' + '&nbsp;&nbsp;&nbsp;',
				listeners: {
					check: function()
					{
						if (chbDrillDownLevel.getValue())
							cmbDrillDownLevel.enable();
						else
							cmbDrillDownLevel.disable();
					}
				}
			});

			// Display -> Indent Text
			chbIndentText = new Ext.form.Checkbox({
				checked: hbConf.indent,
				hideLabel: true,
				tabIndex: 23,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Indent Text".localize()
			});

			// Display -> Fixed Width
			chbColWidth = new Ext.form.Checkbox({
				checked: !!(hbConf.cwidth),
				width: _config.displayLabelW,
				hideLabel: true,
				tabIndex: 24,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Set column width".localize() + ':',
				listeners: {
					check: function(thisChb, checked)
					{
						if (checked)
						{
							rbAutoWidth.enable()
							rbFixedWidth.enable()
							if (rbFixedWidth.getValue())
								txtFixedColWidth.enable();
						}
						else
						{
							rbAutoWidth.disable()
							rbFixedWidth.disable()
							txtFixedColWidth.disable();
						}
					}
				}
			});
			// --- CheckBoxes ---

			// +++ ComboBoxes +++
			// Border -> Type
			cmbBorderType = new Ext.form.ComboBox({
				store: storeBorderType,
				width: 100,
				tabIndex: 31,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				bodyStyle: 'background-color:transparent;padding-left:30px;',
				hideLabel: true,
				typeAhead: true,
				selectOnFocus: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'id',
				displayField: 'name',
				tpl: new Ext.XTemplate('<tpl for=".">',
					'<div class="x-combo-list-item" style="cursor:pointer;line-height:18px;">',
						'<div style="margin-top:8px; border-top: 1px {style} rgb(0, 0, 0); width:20px; float:left;"></div>',
						'<div style="width:69%; margin-left:30%; text-align:left;">{name}</div>',
					'</div>',
				'</tpl>'),
				listeners: {
					select: function(thisCombo, record, index)
					{
						//cmbBorderType.id + '_styleDiv' => border-top:1px solid rgb(0, 0, 0)
						Ext.get(cmbBorderType.id + '_styleDiv').setStyle('border-top', '1px ' + record.get('style') + ' rgb(0, 0, 0)');
						_updateBorderSample();
					},
					render: function()
					{
						this.fieldDiv = Ext.DomHelper.insertFirst(this.el.up('div.x-form-field-wrap'), {
							tag: 'div', id: cmbBorderType.id + '_inputFieldDiv',
							style:'position:absolute;background-color:transparent;height:18px'
						});
						var tmpBorderStyle = _getBorderInfo(hbConf.border)[1];
						this.styleDiv = Ext.DomHelper.insertFirst(this.fieldDiv, {
							tag: 'div', id: cmbBorderType.id + '_styleDiv', style:'margin-top:10px;border-top:1px ' + tmpBorderStyle + ' rgb(0, 0, 0);width:20px;margin-left:4px;'
						});

						Ext.get(cmbBorderType.getItemId()).setStyle('padding-left', '30px');
					}
				}
			});

			// Border -> Width
			cmbBorderWidth = new Ext.form.ComboBox({
				store: storeBorderWidth,
				width: 100,
				tabIndex: 32,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				bodyStyle: 'background-color:transparent;padding-left:30px;',
				hideLabel: true,
				typeAhead: true,
				selectOnFocus: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'id',
				displayField: 'name',
				tpl: new Ext.XTemplate('<tpl for=".">',
					'<div class="x-combo-list-item" style="cursor:pointer;line-height:18px;">',
						'<div style="margin-top:8px; border-top: {width}px solid rgb(0, 0, 0); width:20px; float:left;"></div>',
						'<div style="width:69%; margin-left:30%; text-align:left;">{name}</div>',
					'</div>',
				'</tpl>'),
				listeners: {
					select: function(thisCombo, record, index)
					{
						//cmbBorderWidth.id + '_styleDiv' => border-top:1px solid rgb(0, 0, 0)
						Ext.get(cmbBorderWidth.id + '_styleDiv').setStyle('border-top', record.get('width') + 'px solid rgb(0, 0, 0)');
						_updateBorderSample();
					},
					render: function()
					{
						this.fieldDiv = Ext.DomHelper.insertFirst(this.el.up('div.x-form-field-wrap'), {
							tag: 'div', id: cmbBorderWidth.id + '_inputFieldDiv',
							style:'position:absolute;background-color:transparent;height:18px'
						});
						var tmpBorderWidth = _getBorderInfo(hbConf.border)[0];
						tmpBorderWidth = tmpBorderWidth.substring(0, tmpBorderWidth.length - 2);
						this.styleDiv = Ext.DomHelper.insertFirst(this.fieldDiv, {
							tag: 'div', id: cmbBorderWidth.id + '_styleDiv', style:'margin-top:10px;border-top:' + tmpBorderWidth + 'px solid rgb(0, 0, 0);width:20px;margin-left:4px;'
						});

						Ext.get(cmbBorderWidth.getItemId()).setStyle('padding-left', '30px');
					}
				}
			});

			// Display -> Use Alias
			chbShowAlias = new Ext.form.Checkbox({
				checked: hbConf.alias,
				hideLabel: true,
				tabIndex: 20,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Show Alias".localize()
			});

			// Display -> Drill Down
			cmbDrillDownLevel = new Ext.form.ComboBox({
				disabled: !(hbConf.drill),
				store: storeDrillDownLevel,
				width: _config.displayFieldW,
				bodyStyle: 'background-color:transparent;',
				hideLabel: true,
				tabIndex: 22,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				typeAhead: true,
				selectOnFocus: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'name',
				displayField: 'name'
			});
			panelcmbDrillDownLevel = new Ext.Panel({
				border: false,
				layout: 'form',
				bodyStyle: 'background-color:transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [cmbDrillDownLevel]
			});
			// --- ComboBoxes ---

			// +++ FieldSets and auxiliary Panels +++
			// => additional panels
			// Display -> Drill Down
			panelDrillDownLevel = new Ext.Panel({
				border: false,
				layout: 'column',
				bodyStyle: 'background-color:transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						autoWidth: true,
						autoHeight: true,
						items: [
							chbDrillDownLevel
						]
					}),
					panelcmbDrillDownLevel]
			});

			// Display -> Fixed Width
			panelColWidth = new Ext.Panel({
				border: false,
				layout: 'column',
				bodyStyle: 'background-color:transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [
					{
						html: '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;',
						baseCls:'x-plain'
					},
					new Ext.Panel({
						border: false,
						layout: 'column',
						bodyStyle: 'background-color:transparent;',
						autoWidth: true,
						autoHeight: true,
						items: [
							rbFixedWidth,
							txtFixedColWidth
						]
					}),
					{
						html: '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;',
						baseCls:'x-plain'
					},
					rbAutoWidth]
			});

			// Border -> Sample -> Sample
			panelSample = new Ext.Panel({
				border: false,
				style: 'margin:auto;margin-top:20px;',
				width: _config.samplePanelW,
				height: _config.samplePanelH
			});

			// Direction -> Down/Right
			panelDirection = new Ext.Panel({
				border: false,
				layout: 'column',
				bodyStyle: 'background-color:transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						width: _config.rbWidth,
						autoHeight: true,
						items: [
							rbDown
						]
					}),
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						width: _config.rbWidth,
						autoHeight: true,
						items: [
							rbRight
						]
					})
				]
			});

			// Source -> Subset/Manual
			panelSrc = new SoruceForm({
				genData: hbConf._gendata,
				previewValue: hbConf._preview_val,
				functionValue: hbConf.ss_func,
				dynarangeConf: hbConf,
				typeDisabled: (hbConf._gendata[0][0] == -1),

				rbWidth: _config.rbWidth,
				textWidth: _config.winW - 50
			});
			// <= additional panels

			// Source
			fsSource = new Ext.form.FieldSet({
				title: "Source".localize(),
				collapsible: false,
				autoWidth: true,
				autoHeight: true,
				items: [panelSrc]
			});

			// Direction
			fsDirection = new Ext.form.FieldSet({
				autoHeight: true,
				title: "Direction".localize(),
				items: [panelDirection]
			});

			// Display
			fsDisplay = new Ext.form.FieldSet({
	//			autoHeight: true,
				height: _config.btmFsHeight,
				width: _config.winW/2 - 18,
				title: "Display".localize(),
				items: [
					chbShowAlias,
					panelDrillDownLevel,
					chbIndentText,
					chbColWidth,
					panelColWidth
				]
			});

			// Border -> Sample
			fsSample = new Ext.form.FieldSet({
				title: "Sample".localize(),
				height: 130,
				width: _config.winW/4,
				style: 'margin-left:20px;',
				bodyStyle: 'text-align:center;',
				items: [panelSample]
			});

			// Border
			fsBorder = new Ext.form.FieldSet({
	//			autoHeight: true,
				height: _config.btmFsHeight,
				width: _config.winW/2 - 18,
				layout: 'column',
				title: "Border".localize(),
				items: [
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						autoWidth: true,
						autoHeight: true,
						items: [
							{
								html: "Color".localize() + ':',
								baseCls:'x-plain'
							},
							btnBorderColor,
							{
								html: "Type".localize() + ':',
								baseCls:'x-plain'
							},
							cmbBorderType,
							{
								html: "Width".localize() + ':',
								baseCls:'x-plain'
							},
							cmbBorderWidth
						]
					}),
					fsSample
				]
			});
			// --- FieldSets and auxiliary Panels ---

			// *** MAIN panel ***
			panelMain = that.containers.mainPanel = new Ext.Panel({
				autoHeight: true,
				labelWidth: _config.mainLabelW,
				layout: 'form',
				bodyStyle: 'padding: 5px 5px 0px; background-color: transparent;',
				items: [txtHbName, fsSource, fsDirection,
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [
										        fsDisplay
										]
									}),
									{
										html: '&nbsp;&nbsp;',
										baseCls:'x-plain'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [
										        fsBorder
										]
									})
								]
						})
					]
			});

			// *** Window ***
			that.win = new Ext.Window({
				hidden: true,
				layout: 'fit',
				title: "_tit: hb Properties".localize(),
				width: _config.winW,
				minWidth: _config.winW,
				autoHeight: true,
				closeAction: 'close',
				cls: 'default-format-window',
				autoDestroy: true,
				plain: true,
				modal: true,
				resizable: false,
				listeners: {
					activate: _resizeAll,
					show:function(){
						setTimeout(function(){
							//that.initFocus(true, 100);
						});
					},
					close: function()
					{
						Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
						Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
						that.close();
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.manageDynarange);
					}
				},
				items: [panelMain],
				buttons: [btnOk, btnClose]

			});

			// +++ setting data on items +++
			cmbDrillDownLevel.setValue(hbConf.level);

			var tmpBorderValues = _getBorderInfo(hbConf.border);
			tmpBorderValues[0] = tmpBorderValues[0].substring(0, tmpBorderValues[0].length - 2);

			cmbBorderType.setValue(storeBorderType.getAt(storeBorderType.find('style', tmpBorderValues[1])).get('id'));
			cmbBorderWidth.setValue(storeBorderWidth.getAt(storeBorderWidth.find('width', tmpBorderValues[0])).get('id'));
			// --- setting data on items --
		}

		this.show = function()
		{
			// Set DIALOG work on Grid
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

			that.setContext();
			that.win.show();

			_updateBorderSample();
		}

		// *** Other Functions ***
		var _getBorderInfo = function(borderStyle)
		{
			return borderStyle.split(' ');
		}

		var _updateBorderSample = function()
		{
			var tmpBorder = storeBorderWidth.getAt(storeBorderWidth.find('id', cmbBorderWidth.getValue())).get('width')  + 'px ' + storeBorderType.getAt(storeBorderType.find('id', cmbBorderType.getValue())).get('style') + ' ' + borderColor;
			Ext.get(panelSample.id).setStyle('border', tmpBorder);

	//		hbConf.border = storeBorderWidth.getAt(storeBorderWidth.find('id', cmbBorderWidth.getValue())).get('width')  + 'px ' + storeBorderType.getAt(storeBorderType.find('id', cmbBorderType.getValue())).get('style') + ' ' + borderColor;
		}
		// --- Other Functions ---

		// "resize" window and all components. Also positioning of components
		var _resizeAll = function()
		{
			if (panelMain.rendered)
			{
				that.activate();
				var tmpElem = Ext.DomQuery.selectNode('*[id=' + btnBorderColor.btnEl.id + ']');
				tmpElem.style.background = borderColor;
				tmpElem.style.width = _config.borderColorButtonW + 'px';
			}
		}

		this.init(conf);
		this.show();
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.Dynarange, Jedox.dlg.Dialog);