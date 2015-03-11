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
 * SVN: $Id: ConditionalFormatting.js 4998 2011-05-26 08:50:15Z andrejv $
 *
 */

Jedox.wss.dlg.openConditionalFormatting = function(from, addParams, toEdit) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.ConditionalFormatting(from, addParams, toEdit));
};

Jedox.wss.dlg.ConditionalFormatting = (function() {

	return function (from, addParams, toEdit) {

		Jedox.wss.dlg.ConditionalFormatting.parent.constructor.call(this);
		this.id = 'conditionalFormatting';
		var that = this;

		//	addParams(parameters); - to return parameters to other dialog

		var initActiveItem = 0;
		var winw = 650;
		var rules = [];
		var _tmpRule = {sit: true};
		var _style;
		var _applies_to;

		var _pre = {};
		if (toEdit)
			for (var i in toEdit)
			{
				_pre[i] = _tmpRule[i] = toEdit[i];
			}

		var _wf;

		var _type;
		var _operator;
		var _operands;
		var _sit;
		var _format;
		var _protection;
		var _style;
		// from MR
		var _appliesTo;

		function setContainers(elements){
			// erase all containers, than add appropriate one

			for (var c in that.containers){
				delete that.containers[c];
			}

			for (var nc in elements){
				that.containers[nc] = elements[nc];
			}

		};

		var uniFButton = Ext.extend(Ext.Button, {
			iconCls: 'select-range-icon',
			cls: 'x-btn-icon',
			tooltip: "Select Range".localize(),
			initComponent: function()
			{
			var that = this;
			// config
			Ext.apply(this, {});
			uniFButton.superclass.initComponent.call(this);
			}
		});

		if (!_pre) _pre = {
				type: '',
				operator: '',
				operands: ['',''],
				sit: true,
				format: '',
				style: '',
				borders: {},
				lock: true
		}

		if (!_pre.operands) _pre.operands = '';

		_style = _pre.style;
		_applies_to = _pre.applies_to;
		if (_pre.id) var _id = _pre.id;
		_type = _pre.type;
		_operator = _pre.operator;
		_operands = _pre.operands;
		_sit = _pre.sit;
		_format = _pre.format;
		_style = _pre.style;
		_borders = _pre.borders? _pre.borders : {};
		_protection = _pre.lock;

		var _fromDlgF = false;

		if (Jedox.wss.app.environment.inputMode === Jedox.wss.grid.GridMode.DIALOG)
			_fromDlgF=true;
		else {
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}

		//	##########################	VARIABLES, STORES, FUNCTIONS, ETC	#############################

		var cndfmt = Jedox.wss.cndfmt;

		// this applies both if calleed from Manage Rules or directly
		// IMPORTANT


		var CTCSelected;
	//	if (!CTCSelected) CTCSelected = 'cell_value';

		var colorPalette = new Ext.ColorPalette({
			colors:  Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
			cls: 'wide-color-palette'
		});

		var mainMenuData = [
		                    // ['Format all cells based on their values'.localize()],
		                    ['Format only cells that contain'.localize().concat('...')],
		                    ['Format only top or bottom ranked values'.localize()],
		                    ['Format only values that are above or below average'.localize()],
		                    ['Format only unique or duplicate values'.localize()],
		                    ['Use a formula to determine which cells to format'.localize()]
		                     ];

		var mainMenuStore = new Ext.data.SimpleStore({
			fields: ['type'],
			data: mainMenuData
		});

		//	############################## UNIFORM SELECT FUNCTION
		function selRange(selected){
			that.win.show();
			setTimeout(function() {
				var f = Ext.getCmp(_wf);
				f.setValue(selected);
				_wf = '';
			}, 1);
		}

		var _ai_main;
		var _ai_topbot;
		var _ab_bel;
		var _unique;

		var secondaryCID, tertiarCID;

		//	NB: ai is shortened from Active Item
		function chooseMenu(dView, index, node, ev){
			Ext.getCmp('main_display').layout.setActiveItem(index);
			index = index + 1;
			_ai_main = index; //	this should be just index, TODO: when BOV enabled, delete +1
			if (index == 1) {
				that.win.setWidth(650);
				//set initial rule - complete
				_type = 'cell_value';
				_tmpRule.type =_type;
				if (!_operator) {
					_operator = 'between';
					_tmpRule.operator = _operator;
				}
			}
			else
				that.win.setWidth(500);

			if (index == 0) {
				that.win.setHeight(460);
				previewPanel.hide();
			}
			else {
				that.win.setHeight(420);
				previewPanel.show();
			}
			if (index == 2) {
				if (!_ai_topbot) _ai_topbot = 'top';
			}
			if (index == 3) if (!_ab_bel) _ab_bel = '>';
			if (index == 4) if (!_unique) _unique = 'duplicate_value';
			//if (index == 5) _tmpRule = {type: 'formula_true'};
			if (index == 5) _tmpRule.type = 'formula_true';

			// === setting main active containers
			var e = Ext.getCmp('main_display').layout.activeItem;

			// cells_that_contain ---> special settings
			var toSet = {};
			secondaryCID = false;
			tertiarCID = false;
			if (e.id != 'cells_that_contain'){
				toSet[e.id] = e;
			} else {
				toSet['CTCComboHolder'] = Ext.getCmp('CTCComboHolder');
				var subContainer = CTCCard.layout.activeItem;
				if (subContainer.id == 'ctc_secondary_container'){
					// specific case
					toSet[subContainer.items.items[0].id] = subContainer.items.items[0];
					secondaryCID = subContainer.items.items[0].id;
					toSet[subContainer.items.items[1].items.items[0].layout.activeItem.id] = subContainer.items.items[1].items.items[0].layout.activeItem;
					tertiarCID = subContainer.items.items[1].items.items[0].layout.activeItem.id;
				} else {
					// standard case -- just add to toSet
					toSet[subContainer.id] = subContainer;
					secondaryCID = subContainer.id;
				}
			}

			setContainers(toSet);
			that.containers.previewPanel = previewPanel;
		};

	//	function setBOVCard(combo, record, index){
	//	Ext.getCmp('based_on_value_card').layout.setActiveItem(index);
	//	if (index==1) {
	//	BOVMidpointType.setWidth(120);
	//	BOVMaximumType3.setWidth(120);
	//	BOVMaximumValue3.setWidth(95);
	//	BOVMidpointValue.setWidth(95);
	//	BOVMinimumType3.setWidth(120);
	//	BOVMinimumValue3.setWidth(95);
	//	}
	//	};


		var _ai_text;
		var _ai_cell_val;
		function setCTCCard(combo, record, index){
			Ext.getCmp('CTC_card').layout.setActiveItem(index);
			if ((index == 0) || (index == 1)) {
				that.win.setWidth(650);
				CTCRight.setWidth(460);
				CTCCellValue.setWidth(460);
			}
			else {
				that.win.setWidth(500);
				CTCRight.setWidth(300);
			}
			CTCSelected = CTCComboData[index][1];
			_type = CTCSelected;
			_tmpRule.type = _type;
			if (_type == 'text') {
				if (!_ai_text)
					_ai_text = 'contained';
				_tmpRule.operator = _ai_text;
			}
			if (_type == 'cell_value') {
				if (!_ai_cell_val)
					_ai_cell_val = 'between';
				_tmpRule.operator = _ai_cell_val;
			}

			if ((_type == 'blanks') || (_type == 'no_blanks') || (_type == 'errors') || (_type == 'no_errors'))
				_tmpRule = {
					type: _type
			};

			// setting containers
			var e = CTCCard.layout.activeItem;

			//var toSet = {};

			delete that.containers[tertiarCID];
			delete that.containers[secondaryCID];
			secondaryCID = false;
			tertiarCID = false;

			if (e.id != 'ctc_secondary_container'){
				that.containers[e.id] = e;
				secondaryCID = e.id;
			} else {
				that.containers[e.items.items[0].id] = e.items.items[0];
				secondaryCID = e.items.items[0].id;
				that.containers[e.items.items[1].items.items[0].layout.activeItem.id] = e.items.items[1].items.items[0].layout.activeItem;
				tertiarCID = e.items.items[1].items.items[0].layout.activeItem.id;
			}


		};

		// BASED ON VALUES COMPONENTS //
		/*
		var formatStyleBOVData = [
		                          ['2-Color Scale'.localize()],
		                          ['3-Color Scale'.localize()]
		                           ];

		var BOVTypeMinimumData = [
		                          ['Lowest value'.localize()],
		                          ['Number'.localize()],
		                          ['Percent'.localize()],
		                          ['Formula'.localize()],
		                          ['Percentile'.localize()]
		                           ];

		var BOVTypeMaximumData = [
		                          ['Highest value'.localize()],
		                          ['Number'.localize()],
		                          ['Percent'.localize()],
		                          ['Formula'.localize()],
		                          ['Percentile'.localize()]
		                           ];

		var BOVTypeMidpointData = [
		                           ['Number'.localize()],
		                           ['Percent'.localize()],
		                           ['Formula'.localize()],
		                           ['Percentile'.localize()]
		                            ];

		var BOVTypeMidpointStore = new Ext.data.SimpleStore({
			fields: ['format_style'],
			data: BOVTypeMidpointData
		});

		var BOVTypeMinimumStore = new Ext.data.SimpleStore({
			fields: ['format_style'],
			data: BOVTypeMinimumData
		});

		var BOVTypeMaximumStore = new Ext.data.SimpleStore({
			fields: ['format_style'],
			data: BOVTypeMaximumData
		});

		var formatStyleBOVStore = new Ext.data.SimpleStore({
			fields: ['format_style'],
			data: formatStyleBOVData
		});

		 */

		var _config = {
				colorButtonW: '120px',
				labelWidth: 60,
				textBoxW: 180,
				comboBoxW: 200,

				rowH: 25,
				margingSize: 2,

				minColor: '#FF6633',
				maxColor: '#33FF66',
				midColor: '#6633FF'
		};

		var state = {
				colorMin: _config.minColor,
				colorMax: _config.maxColor,
				colorMid: _config.midColor
		};

		function _setupColorButton(colorBtn, color, setWidth)
		{
			var tmpElem = Ext.DomQuery.selectNode('*[id=' + colorBtn.btnEl.id + ']');
			tmpElem.style.background = color;
			tmpElem.style.width = "100px";
		};

		var topBottomComboData = [
		                          ['Top'.localize(), 'top'],
		                          ['Bottom'.localize(), 'bottom']
		                           ];

		var topBottomComboStore = new Ext.data.SimpleStore({
			fields: ['rank', 'type'],
			data: topBottomComboData
		});

		var aboveBelowData = [
		                      ['above'.localize(), '>'],
		                      ['below'.localize(), '<'],
		                      ['equal or above'.localize(), '>='],
		                      ['equal or below'.localize(),'<='],
		                      ['1 std dev above'.localize(), 'std_dev_above_1'],
		                      ['1 std dev below'.localize(), 'std_dev_below_1'],
		                      ['2 std dev above'.localize(), 'std_dev_above_2'],
		                      ['2 std dev below'.localize(), 'std_dev_below_2'],
		                      ['3 std dev above'.localize(), 'std_dev_above_3'],
		                      ['3 std dev below'.localize(), 'std_dev_below_3']
		                       ];

		var aboveBelowStore = new Ext.data.SimpleStore({
			fields: ['type', 'operator'],
			data: aboveBelowData
		});

		var duplicateComboData = [
		                          ['duplicate'.localize(), 'duplicate_value'],
		                          ['unique'.localize(), 'unique_value']
		                           ];

		var duplicateComboStore = new Ext.data.SimpleStore({
			fields: ['type', 'rule_type'],
			data: duplicateComboData
		});

		var CTCComboData = [
		                    ['Cell Value'.localize(), 'cell_value'],
		                    ['Specific Text'.localize(), 'text'],
		                    ['Dates Occurring'.localize(), false], // !!! Missing dates! - NOT SUPPORTED
		                    ['Blanks'.localize(), 'blanks'],
		                    ['No Blanks'.localize(), 'no_blanks'],
		                    ['Errors'.localize(), 'errors'],
		                    ['No errors'.localize(), 'no_errors']
		                     ];

		var CTCComboStore = new Ext.data.SimpleStore({
			fields: ['with', 'value'],
			data: CTCComboData
		});

		var CTCComboDataCellValue = [
		                             ['between'.localize(), 'between'],
		                             ['not between'.localize(), 'not_between'],
		                             ['equal to'.localize(), '='],
		                             ['not equal to'.localize(), '<>'],
		                             ['greater than'.localize(), '>'],
		                             ['less than'.localize(), '<'],
		                             ['greater than or equal to'.localize(), '>='],
		                             ['less than or equal to'.localize(), '<=']
		                              ];

		var CTCComboStoreCellValue = new Ext.data.SimpleStore({
			fields: ['desc', 'operator'],
			data: CTCComboDataCellValue
		});

		var CTCComboDataSpecificText = [
		                                ['containing'.localize(), 'contained'],
		                                ['not containing'.localize(), 'not_contained'],
		                                ['beginning with'.localize(), 'begins_with'],
		                                ['ending with'.localize(), 'ends_with']
		                                 ];

		var CTCComboStoreSpecificText = new Ext.data.SimpleStore({
			fields: ['desc', 'operator'],
			data: CTCComboDataSpecificText
		});

		//	THIS IS NOT SUPPORTED YET
		var CTCComboDataDatesOccurring = [
		                                  ['Yesterday'.localize()],
		                                  ['Today'.localize()],
		                                  ['Tomorrow'.localize()],
		                                  ['In the last 7 days'.localize()],
		                                  ['Last week'.localize()],
		                                  ['This week'.localize()],
		                                  ['Next week'.localize()],
		                                  ['Last month'.localize()],
		                                  ['This month'.localize()],
		                                  ['Next month'.localize()]
		                                   ];

		var CTCComboStoreDatesOccurring = new Ext.data.SimpleStore({
			fields: ['desc'],
			data: CTCComboDataDatesOccurring
		});

	//	##########################	ELEMENTS	################################

		//	#### preview field - similar as in Format Cells
		var dummyList = [['<div style="line-height: 52px;">No Format Set</div>']];
		var dummyStore = new Ext.data.SimpleStore({
			fields: ['dummy'],
			data: dummyList
		});
		var tmpDummy = new Ext.data.Record.create([
		                                           {name: 'dummy'}
		                                           ]);
		// insert later: <div style="font-weight:'.concat(fontWeightGrid,'; font-family:',fontFamilyGrid,'; font-style:',fontStyleGrid,'; font-size:',fontSizeValue,'pt; ',fontEffects,';',fontColor,'">
		var formatPreview = new Ext.DataView({
			id: 'CF_format_preview',
			itemSelector: '.border-field-chooser',
			style: 'overflow:auto',
			autoWidth: true,
			singleSelect: true,
			store: dummyStore,
			cls: 'borderStyleSelect',
			tpl: new Ext.XTemplate(
					'<div class="format-sample-preview" id="CF_F_PRE_HOLD"><tpl for=".">',
					'<div style="display: table-cell; vertical-align: middle;">',
					'<div style="text-align: center; overflow: hidden;">',
					'{dummy}</div></div>',
					'</tpl></div>'
			)
		});

		var mainMenu = new Ext.DataView({
			id: 'main-cond-menu',
			store: mainMenuStore,
			tpl: new Ext.XTemplate(
					'<div style="background-color: #FFFFFF; border:1px solid #B5B8C8;"><tpl for=".">',
					'<div class="thumb-wrap">{type}<br /></div>',
					'</tpl></div>'
			),
			autoHeight: true,
			border: true,
			multiSelect: false,
			singleSelect: true,
			overClass: 'x-view-over',
			itemSelector: 'div.thumb-wrap',
			emptyText: 'Menu error, please contact support',
			listeners: {
			click: {fn: chooseMenu, scope: this}
		}
		});
		var fromFCDLG;
		var _edited_from_MCF = false;
		var openFCDLG = function(fmDesc, isEdit){
			fromFCDLG = fmDesc;
			_edited_from_MCF = true;

			// here setting DataView;

			// Here check for all parameters, BORDERS spec.

			if (!fromFCDLG[0].top) fromFCDLG[0].top={
					width: '',
					type: 'none',
					color: ''
				}

			if (!fromFCDLG[0].bottom) fromFCDLG[0].bottom={
					width: '',
					type: 'none',
					color: ''
				}

			if (!fromFCDLG[0].left) fromFCDLG[0].left={
					width: '',
					type: 'none',
					color: ''
				}

			if (!fromFCDLG[0].right) fromFCDLG[0].right={
					width: '',
					type: 'none',
					color: ''
				}

			for (var i in fromFCDLG[0].top){
				if (!fromFCDLG[0].top[i]) fromFCDLG[0].top[i]='';
			}

			for (var i in fromFCDLG[0].bottom){
				if (!fromFCDLG[0].bottom[i]) fromFCDLG[0].bottom[i]='';
			}

			for (var i in fromFCDLG[0].left){
				if (!fromFCDLG[0].left[i]) fromFCDLG[0].left[i]='';
			}

			for (var i in fromFCDLG[0].right){
				if (!fromFCDLG[0].right[i]) fromFCDLG[0].right[i]='';
			}

			_borders.top = fromFCDLG[0].top;
			_borders.bottom = fromFCDLG[0].bottom;
			_borders.left = fromFCDLG[0].left;
			_borders.right = fromFCDLG[0].right;

			/////////////////////////////////////////////////////////////

			var tmpRec = new tmpDummy({
				dummy: '<div style="font-style: '.concat(fromFCDLG[0].fontStyle, '; background:', fromFCDLG[0].backgroundColor,
						'; text-decoration:',fromFCDLG[0].textDecoration,'; font-weight: ',fromFCDLG[0].fontWeight,'; color:',fromFCDLG[0].color,
						'; background-image:',fromFCDLG[0].backgroundImage,
						';border-top:',fromFCDLG[0].top.width,' ',fromFCDLG[0].top.type,' ',fromFCDLG[0].top.color,';',
						';border-bottom:',fromFCDLG[0].bottom.width,' ',fromFCDLG[0].bottom.type,' ',fromFCDLG[0].bottom.color,';',
						';border-left:',fromFCDLG[0].left.width,' ',fromFCDLG[0].left.type,' ',fromFCDLG[0].left.color,';',
						';border-right:',fromFCDLG[0].right.width,' ',fromFCDLG[0].right.type,' ',fromFCDLG[0].right.color,
				'; line-height: 52px;">AaBbCcZz</div>')
			});

			dummyStore.removeAll();
			dummyStore.insert(0, tmpRec);

	//		for( var e in _style) {
	//			if (_style[e] == fromFCDLG[0][e]) delete fromFCDLG[0][e];
	//		}

			formatPreview.refresh();
			_style = fromFCDLG[0];
			_format = fromFCDLG[1];
			_protection = fromFCDLG[2];

			that.win.show();
			that.win.focus();
		};



		var previewPanel = this.containers.previewPanel = new Ext.Panel ({
			id: 'preview_panel',
			layout: 'column',
			baseCls: 'x-plain',
			hidden: true,
			border: false,
			frame: false,
			items: [
			        {
			        	width: 120,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'Preview'.localize().concat(':'),
			        	        	bodyStyle: 'font-weight: bold; margin-top: 20px;',
			        	        	baseCls: 'x-plain'
			        	        }
			        	        ]
			        }
			        ,
			        // col 2
			        {
			        	width: 280,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [formatPreview]
			        },
			        // col 3
			        {
			        	width: 100,
			        	//							  	layout: 'fit',
			        	//		        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        new Ext.Button({
			        	        	disabled: false,
			        	        	tabIndex: 100,
			        	        	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			        	        	id: 'fromConditionalFormatting',
			        	        	hidden: false,
			        	        	style: 'margin-top: 20px;margin-right: 10px;',
			        	        	enableToggle: false,
			        	        	minWidth: 100,
			        	        	text: 'Format'.localize().concat('...'),
			        	        	listeners: {
			        	        	click: {
			        	        	fn: function(){
			        	        	Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatCells, ['fromConditionalFormatting', 0, openFCDLG, [_format, _style, _borders, _protection]]);
			        	        },
			        	        scope: this
			        	        }
			        	        }
			        	        })]
			        }
			        ]
		});




	//	################################### all cells based on their values	#####################################
	//	HERE BE FORMATTING BASED ON VALUE - Disabled until implemented!
		/*
		var formatStyleBOV = new Ext.form.ComboBox({
			store: formatStyleBOVStore,
			displayField: 'format_style',
			id: 'formatStyleBOV',
			hideLabel: true,
			editable: false,
			typeAhead: true,
			mode: 'local',
			triggerAction: 'all',
			value: formatStyleBOVData[0][0],
			selectOnFocus: true,
			listWidth: 110,
			width: 110,
			listeners: {
			select: {
			fn: setBOVCard,
			scope: this
		}
		}
		});

		var BOVMinimumType = new Ext.form.ComboBox({
			store: BOVTypeMinimumStore,
			displayField: 'format_style',
			hideLabel: true,
			editable: false,
			typeAhead: true,
			mode: 'local',
			triggerAction: 'all',
			value: BOVTypeMinimumData[0][0],
			selectOnFocus: true,
			listWidth: 120,
			width: 120
	//		listeners: {
	//		select: {
	//		fn: setBOVCard,
	//		scope: this
	//		}
	//		}
		});

		var BOVMinimumType3 = new Ext.form.ComboBox({
			store: BOVTypeMinimumStore,
			displayField: 'format_style',
			hideLabel: true,
			editable: false,
			typeAhead: true,
			mode: 'local',
			triggerAction: 'all',
			value: BOVTypeMinimumData[0][0],
			selectOnFocus: true,
			listWidth: 121,
			width: 121
	//		listeners: {
	//		select: {
	//		fn: setBOVCard,
	//		scope: this
	//		}
	//		}
		});

		var BOVMaximumType = new Ext.form.ComboBox({
			store: BOVTypeMaximumStore,
			displayField: 'format_style',
			hideLabel: true,
			editable: false,
			typeAhead: true,
			mode: 'local',
			triggerAction: 'all',
			value: BOVTypeMaximumData[0][0],
			selectOnFocus: true,
			listWidth: 120,
			width: 120
	//		listeners: {
	//		select: {
	//		fn: setBOVCard,
	//		scope: this
	//		}
	//		}
		});

		var BOVMaximumType3 = new Ext.form.ComboBox({
			store: BOVTypeMaximumStore,
			displayField: 'format_style',
			hideLabel: true,
			editable: false,
			typeAhead: true,
			mode: 'local',
			triggerAction: 'all',
			value: BOVTypeMaximumData[0][0],
			selectOnFocus: true,
			listWidth: 121,
			width: 121
	//		listeners: {
	//		select: {
	//		fn: setBOVCard,
	//		scope: this
	//		}
	//		}
		});

		var BOVMidpointType = new Ext.form.ComboBox({
			store: BOVTypeMidpointStore,
			displayField: 'format_style',
			hideLabel: true,
			editable: false,
			typeAhead: true,
			mode: 'local',
			triggerAction: 'all',
			value: BOVTypeMidpointData[0][0],
			selectOnFocus: true,
			listWidth: 121,
			width: 121
	//		listeners: {
	//		select: {
	//		fn: setBOVCard,
	//		scope: this
	//		}
	//		}
		});


	//	################# SELECT RANGE BUTTONS	################

		var BOVMinValSelRngBtn=new uniFButton({
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{fnc: [this, selRange]}]); _wf = 'BOV_minimum_value'; that.win.hide()}
		});

		var BOVMaxValSelRngBtn=new Ext.Toolbar.Button({
			id: 'BOVMaxVal',
			iconCls: 'select-range-icon',
			cls: 'x-btn-icon',
			tooltip: "Select Range".localize(),
			handler:function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{fnc: [this, selRangeBOVMax]}]); _wf = 'BOV_maximum_value';that.win.hide()}
		});

		var BOVMinVal3SelRngBtn=new uniFButton({
			handler:function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{fnc: [this, selRangeBOVMin3]}]); _wf = 'BOV_minimum_value3'; that.win.hide()}
		});

		var BOVMaxVal3SelRngBtn=new uniFButton({
			handler:function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{fnc: [this, selRangeBOVMax3]}]); _wf = 'BOV_maximum_value3';that.win.hide()}
		});

		var BOVMidValSelRngBtn=new uniFButton({
			handler:function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{fnc: [this, selRangeBOVMid]}]); _wf = 'BOV_midpoint_value';that.win.hide()}
		});

	//	################################################

		var BOVMinimumValue = new Ext.form.TextField({
			name: 'BOV_minimum_value',
			id: 'BOV_minimum_value',
			width: 95,
			hideLabel: true,
			enableKeyEvents: true
		});

		var BOVMinimumValueContainer = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 95,
				    	   baseCls:'x-plain',
				    	   items:BOVMinimumValue
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:BOVMinValSelRngBtn
				       }
				       ]
		};

		var BOVMinimumValue3 = new Ext.form.TextField({
			name: 'BOV_minimum_value3',
			id: 'BOV_minimum_value3',
			width: 95,
			hideLabel: true,
			enableKeyEvents: true
		});

		var BOVMinimumValue3Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 95,
				    	   baseCls:'x-plain',
				    	   items:BOVMinimumValue3
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:BOVMinVal3SelRngBtn
				       }
				       ]
		};

		var BOVMaximumValue = new Ext.form.TextField({
			name: 'BOV_maximum_value',
			id: 'BOV_maximum_value',
			width: 95,
			hideLabel: true,
			enableKeyEvents: true
		});

		var BOVMaximumValueContainer = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 95,
				    	   baseCls:'x-plain',
				    	   items:BOVMaximumValue
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:BOVMaxValSelRngBtn
				       }
				       ]
		};

		var BOVMidpointValue = new Ext.form.TextField({
			name: 'BOV_midpoint_value',
			id: 'BOV_midpoint_value',
			width: 95,
			hideLabel: true,
			enableKeyEvents: true
		});

		var BOVMidpointValueContainer = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 95,
				    	   baseCls:'x-plain',
				    	   items:BOVMidpointValue
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:BOVMidValSelRngBtn
				       }
				       ]
		};

		var BOVMaximumValue3 = new Ext.form.TextField({
			name: 'BOV_maximum_value3',
			id: 'BOV_maximum_value3',
			width: 95,
			hideLabel: true,
			enableKeyEvents: true
		});

		var BOVMaximumValue3Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 95,
				    	   baseCls:'x-plain',
				    	   items:BOVMaximumValue3
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:BOVMaxVal3SelRngBtn
				       }
				       ]
		};


		var BOVMinimumColor = new Ext.Toolbar.SplitButton({
			minWidth: 120,
			id: 'BOVMinimumColor',
			menu: new Ext.menu.ColorMenu({
				colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
				cls: 'wide-color-palette',
				listeners: {
				select: function(colorP, colorStr)
				{
				state.colorMin = '#' + colorStr;
				_setupColorButton(BOVMinimumColor, state.colorMin, false);
				}
			//					beforeshow: function(thisMenu)
	//		{
	//		thisMenu.palette.select(state.colorMin);
	//		}
			}
			})
		});

		var BOVMinimumColor3 = new Ext.Toolbar.SplitButton({
			minWidth: 105,
			id: 'BOVMinimumColor3',
			menu: new Ext.menu.ColorMenu({
				colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
				cls: 'wide-color-palette',
				listeners: {
				select: function(colorP, colorStr)
				{
				state.colorMin = '#' + colorStr;
				_setupColorButton(BOVMinimumColor3, state.colorMin, false);
				}
			//					beforeshow: function(thisMenu)
	//		{
	//		thisMenu.palette.select(state.colorMin);
	//		}
			}
			})
		});

		var BOVMaximumColor = new Ext.Toolbar.SplitButton({
			minWidth: 120,
			id: 'BOVMaximumColor',
			menu: new Ext.menu.ColorMenu({
				colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
				cls: 'wide-color-palette',
				listeners: {
				select: function(colorP, colorStr)
				{
				state.colorMax = '#' + colorStr;
				_setupColorButton(BOVMaximumColor, state.colorMax, false);
				}
			//					beforeshow: function(thisMenu)
	//		{
	//		thisMenu.palette.select(state.colorMax);
	//		}
			}
			})
		});

		var BOVMaximumColor3 = new Ext.Toolbar.SplitButton({
			minWidth: 105,
			id: 'BOVMaximumColor3',
			menu: new Ext.menu.ColorMenu({
				colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
				cls: 'wide-color-palette',
				listeners: {
				select: function(colorP, colorStr)
				{
				state.colorMax = '#' + colorStr;
				_setupColorButton(BOVMaximumColor3, state.colorMax, false);
				}
			//					beforeshow: function(thisMenu)
	//		{
	//		thisMenu.palette.select(state.colorMax);
	//		}
			}
			})
		});

		var BOVMidpointColor = new Ext.Toolbar.SplitButton({
			minWidth: 105,
			id: 'BOVMidpointColor',
			menu: new Ext.menu.ColorMenu({
				colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
				cls: 'wide-color-palette',
				listeners: {
				select: function(colorP, colorStr)
				{
				state.colorMid = '#' + colorStr;
				_setupColorButton(BOVMidpointColor, state.colorMid, false);
				}
			//					beforeshow: function(thisMenu)
	//		{
	//		thisMenu.palette.select(state.colorMax);
	//		}
			}
			})
		});

		var color2Scale = new Ext.Panel({
			id: '2_color_scale',
			layout: 'column',
			baseCls: 'x-plain',
			border: false,
			frame: false,
			items: [
			        {
			        	columnWidth: 0.10,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'Type'.localize().concat(':'),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-top: 20px;'
			        	        },
			        	        {
			        	        	html: 'Value'.localize().concat(':'),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-top: 10px;'
			        	        },
			        	        {
			        	        	html: 'Color'.localize().concat(':'),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-top: 10px;'
			        	        }
			        	        ]
			        },
			        {
			        	columnWidth: 0.30,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'Minimum'.localize(),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-bottom:2px;'
			        	        },
			        	        BOVMinimumType,
			        	        BOVMinimumValueContainer,
			        	        BOVMinimumColor
			        	        ]
			        },
			        {
			        	columnWidth: 0.30,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: '&nbsp;',
			        	        	baseCls: 'x-plain'
			        	        }
			        	        ]
			        },
			        {
			        	columnWidth: 0.30,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'Maximum'.localize(),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-bottom:2px;'
			        	        },
			        	        BOVMaximumType,
			        	        BOVMaximumValueContainer,
			        	        BOVMaximumColor
			        	        ]
			        }
			        ]
		});

		var color3Scale = new Ext.Panel({
			id: '3_color_scale',
			layout: 'column',
			baseCls: 'x-plain',
			border: false,
			frame: false,
			items: [
			        {
			        	columnWidth: 0.10,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'Type'.localize().concat(':'),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-top: 20px;'
			        	        },
			        	        {
			        	        	html: 'Value'.localize().concat(':'),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-top: 10px;'
			        	        },
			        	        {
			        	        	html: 'Color'.localize().concat(':'),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-top: 10px;'
			        	        }
			        	        ]
			        },
			        {
			        	columnWidth: 0.30,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'Minimum'.localize(),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-bottom:2px;'
			        	        },
			        	        BOVMinimumType3,
			        	        BOVMinimumValue3Container,
			        	        BOVMinimumColor3
			        	        ]
			        },
			        {
			        	columnWidth: 0.30,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'Midpoint'.localize(),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-bottom:2px;'
			        	        },
			        	        BOVMidpointType,
			        	        BOVMidpointValueContainer,
			        	        BOVMidpointColor
			        	        ]
			        },
			        {
			        	columnWidth: 0.30,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'Maximum'.localize(),
			        	        	baseCls: 'x-plain',
			        	        	bodyStyle: 'margin-bottom:2px;'
			        	        },
			        	        BOVMaximumType3,
			        	        BOVMaximumValue3Container,
			        	        BOVMaximumColor3
			        	        ]
			        }
			        ]
		});

		var basedOnValuesCard = new Ext.Panel({
			id: 'based_on_value_card',
			layout: 'card',
			deferredRender: true,
			height: 95,
			autoWidth: true,
			baseCls: 'x-plain',
			border: false,
			activeItem: 0,
			//region: 'center',
			items: [color2Scale,
			        color3Scale]
		});

		var basedOnValues = new Ext.Panel({
			border: true,
			id: 'based_on_values',
			frame: true,
			baseCls:'main-panel-open',
			autoHeight: true,
			autoWidth: true,
			layout: 'form',
			items: [
			        {
			        	html: 'Format all cells based on their values'.localize().concat(':'),
			        	baseCls: 'x-plain',
			        	bodyStyle: 'margin-bottom: 10px;'
			        },
			        formatStyleBOV,
			        {
			        	baseCls: 'x-plain',
			        	bodyStyle: 'margin-bottom: 10px;',
			        	height: 0
			        },
			        basedOnValuesCard
			        ]
		});
		 */
		//	END OF BASED ON VALUE!


	//	######################################	only cells that contain	############################################
	//	############################################################################################################

		var CTCCombo = new Ext.form.ComboBox({
			store: CTCComboStore,
			displayField: 'with',
			hideLabel: true,
			editable: false,
			typeAhead: true,
			tabIndex: 10,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			mode: 'local',
			triggerAction: 'all',
			value: CTCComboData[0][0],
			selectOnFocus: true,
			listWidth: 115,
			width: 100,
			listeners: {
			select: {
			fn: setCTCCard,
			scope: this
		}
		}
		});

		var CTCComboCellValue = new Ext.form.ComboBox({
			store: CTCComboStoreCellValue,
			displayField: 'desc',
			hideLabel: true,
			editable: false,
			typeAhead: true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 11,
			mode: 'local',
			triggerAction: 'all',
			value: CTCComboDataCellValue[0][0],
			selectOnFocus: true,
			listWidth: 125,
			width: 110,
			listeners: {
			select: {
			fn: function(combo, record, index){
				Ext.getCmp('CTC_cell_value_card').layout.setActiveItem(index);
				if ((index == 0) || (index == 1)) {
					that.win.setWidth(650);
					//Ext.getCmp('ctc_main_right').layout.setWidth(480);
					//Ext.getCmp('ctc_nest').layout.setWidth(350);
				}
				else {
					//that.win.setWidth(500);
					//Ext.getCmp('ctc_main_right').layout.setWidth(300);
					//Ext.getCmp('ctc_nest').layout.setWidth(170);
				}
				_operator = CTCComboDataCellValue[index][1];
				_ai_cell_val = CTCComboDataCellValue[index][1];
				_tmpRule.operator = _operator;

				// setting containers
				var e = Ext.getCmp('CTC_cell_value_card').layout.activeItem;

				delete that.containers[tertiarCID];
				that.containers[e.id] = e;
				tertiarCID = e.id;
		},
		scope: this
		}
		}
		});

		var CTCComboSpecificText = new Ext.form.ComboBox({
			store: CTCComboStoreSpecificText,
			displayField: 'desc',
			hideLabel: true,
			editable: false,
			tabIndex: 32,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			typeAhead: true,
			mode: 'local',
			triggerAction: 'all',
			value: CTCComboDataSpecificText[0][0],
			selectOnFocus: true,
			listWidth: 100,
			width: 100,
			listeners: {
			select: {
			fn: function(combo, record, index) {
			_operator = CTCComboDataSpecificText[index][1];
			_tmpRule.operator = _operator;
			_ai_text = CTCComboDataSpecificText[index][1];
		},
		scope: this
		}
		}
		});


		var CTCComboDatesOccurring = new Ext.form.ComboBox({
			store: CTCComboStoreDatesOccurring,
			displayField: 'desc',
			hideLabel: true,
			editable: false,
			tabIndex: 34,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			typeAhead: true,
			mode: 'local',
			triggerAction: 'all',
			value: CTCComboDataDatesOccurring[0],
			selectOnFocus: true,
			listWidth: 120,
			width: 120,
			listeners: {
			select: {
			fn: function() {},
			scope: this
		}
		}
		});

		var CTCComboDatesOccHolder = new Ext.Panel({
			baseCls: 'x-plain',
			widh: 120,
			items: CTCComboDatesOccurring
		});

		var fromField1 = new Ext.form.TextField({
			name: 'fromfield1',
			id: 'fromfield1',
			width: 110,
			tabIndex: 12,
			value: (_pre.operands[0])? _pre.operands[0].replace(/=/i, "") : '',
			hideLabel: true,
			enableKeyEvents: true
		});

		var fromField1Button = new uniFButton({
			tabIndex: 13,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
					fnc: [this, selRange]
				    ,format: '{Sheet}!{Range}'
					,rng: Ext.getCmp('fromfield1').getValue()
			}]);
			_wf = 'fromfield1';
			that.win.hide();}
		});

		var fromField1Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 110,
				    	   baseCls:'x-plain',
				    	   items:fromField1
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:fromField1Button
				       }
				       ]
		};

		var fromField2 = new Ext.form.TextField({
			name: 'fromfield2',
			id: 'fromfield2',
			width: 110,
			tabIndex: 14,
			value: (_pre.operands[1])? _pre.operands[1].replace(/=/i, "") : '',
			hideLabel: true,
			enableKeyEvents: true
		});

		var fromField2Button = new uniFButton({
			tabIndex: 15,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '{Sheet}!{Range}'
						,rng: Ext.getCmp('fromfield2').getValue()
				}]);
				_wf = 'fromfield2';
				that.win.hide();}
		});

		var fromField2Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 110,
				    	   baseCls:'x-plain',
				    	   items:fromField2
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:fromField2Button
				       }
				       ]
		};

		var fromField3 = new Ext.form.TextField({
			name: 'fromfield3',
			id: 'fromfield3',
			width: 110,
			tabIndex: 16,
			value: (_pre.operands[0])? _pre.operands[0].replace(/=/i, "") : '',
			hideLabel: true,
			enableKeyEvents: true
		});

		var fromField3Button = new uniFButton({
			tabIndex: 17,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '{Sheet}!{Range}'
						,rng: Ext.getCmp('fromfield3').getValue()
				}]); _wf = 'fromfield3'; that.win.hide()}
		});

		var fromField3Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 110,
				    	   baseCls:'x-plain',
				    	   items:fromField3
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:fromField3Button
				       }
				       ]
		};

		var fromField4 = new Ext.form.TextField({
			name: 'fromfield4',
			id: 'fromfield4',
			width: 110,
			tabIndex: 18,
			value: (_pre.operands[1])? _pre.operands[1].replace(/=/i, "") : '',
			hideLabel: true,
			enableKeyEvents: true
		});

		var fromField4Button = new uniFButton({
			tabIndex: 19,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '{Sheet}!{Range}'
						,rng: Ext.getCmp('fromfield4').getValue()
				}]); _wf = 'fromfield4'; that.win.hide()}
		});

		var fromField4Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 110,
				    	   baseCls:'x-plain',
				    	   items:fromField4
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:fromField4Button
				       }
				       ]
		};

		function isArray(obj) {
			   if (obj.constructor.toString().indexOf("Array") == -1)
			      return false;
			   else
			      return true;
			}

		var tempOperands;
		if (isArray(_pre.operands)) tempOperands = _pre.operands[0] || ''; else tempOperands = _pre.operands || '';
		var formField5 = new Ext.form.TextField({
			name: 'formfield5',
			id: 'formfield5',
			tabIndex: 20,
			width: 180,
			hideLabel: true,
			value: tempOperands.replace(/=/i, ""),
			enableKeyEvents: true
		});

		var formField5Button = new uniFButton({
			tabIndex: 21,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '{Sheet}!{Range}'
						,rng: Ext.getCmp('formfield5').getValue()
				}]); _wf = 'formfield5'; that.win.hide()}
		});

		var formField5Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 180,
				    	   baseCls:'x-plain',
				    	   items:formField5
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:formField5Button
				       }
				       ]
		};

		var formField6 = new Ext.form.TextField({
			name: 'formfield6',
			id: 'formfield6',
			width: 180,
			tabIndex: 22,
			hideLabel: true,
			value: tempOperands.replace(/=/i, ""),
			enableKeyEvents: true
		});

		var formField6Button = new uniFButton({
			tabIndex: 23,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '{Sheet}!{Range}'
						,rng: Ext.getCmp('formfield6').getValue()
				}]); _wf = 'formfield6'; that.win.hide()}
		});

		var formField6Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 180,
				    	   baseCls:'x-plain',
				    	   items:formField6
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:formField6Button
				       }
				       ]
		};

		var formField7 = new Ext.form.TextField({
			name: 'formfield7',
			id: 'formfield7',
			width: 180,
			tabIndex: 24,
			value: tempOperands.replace(/=/i, ""),
			hideLabel: true,
			enableKeyEvents: true
		});

		var formField7Button = new uniFButton({
			tabIndex: 25,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '{Sheet}!{Range}'
						,rng: Ext.getCmp('formfield7').getValue()
				}]); _wf = 'formfield7'; that.win.hide()}
		});


		var formField7Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 180,
				    	   baseCls:'x-plain',
				    	   items:formField7
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:formField7Button
				       }
				       ]
		};

		var formField8 = new Ext.form.TextField({
			name: 'formfield8',
			id: 'formfield8',
			width: 180,
			tabIndex: 26,
			value: tempOperands.replace(/=/i, ""),
			hideLabel: true,
			enableKeyEvents: true
		});

		var formField8Button = new uniFButton({
			tabIndex: 27,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '{Sheet}!{Range}'
						,rng: Ext.getCmp('formfield8').getValue()
				}]); _wf = 'formfield8'; that.win.hide()}
		});


		var formField8Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 180,
				    	   baseCls:'x-plain',
				    	   items:formField8
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:formField8Button
				       }
				       ]
		};

		var formField9 = new Ext.form.TextField({
			name: 'formfield9',
			id: 'formfield9',
			width: 180,
			tabIndex: 28,
			value: tempOperands.replace(/=/i, ""),
			hideLabel: true,
			enableKeyEvents: true
		});

		var formField9Button = new uniFButton({
			tabIndex: 29,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '{Sheet}!{Range}'
						,rng: Ext.getCmp('formfield9').getValue()
				}]); _wf = 'formfield9'; that.win.hide()}
		});

		var formField9Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 180,
				    	   baseCls:'x-plain',
				    	   items:formField9
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:formField9Button
				       }
				       ]
		};

		var formField10 = new Ext.form.TextField({
			name: 'formfield10',
			id: 'formfield10',
			width: 180,
			tabIndex: 30,
			value: tempOperands.replace(/=/i, ""),
			hideLabel: true,
			enableKeyEvents: true
		});

		var formField10Button = new uniFButton({
			tabIndex: 31,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '{Sheet}!{Range}'
						,rng: Ext.getCmp('formfield10').getValue()
				}]); _wf = 'formfield10'; that.win.hide()}
		});


		var formField10Container = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 180,
				    	   baseCls:'x-plain',
				    	   items:formField10
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:formField10Button
				       }
				       ]
		};

		var specificTextfield = new Ext.form.TextField({
			name: 'specificTextfield',
			width: 180,
			tabIndex: 33,
			value: _pre.operands[0],
			hideLabel: true,
			enableKeyEvents: true
		});

		var CTCCellValueCard = new Ext.Panel({
			id: 'CTC_cell_value_card',
			layout: 'card',
			deferredRender: true,
			autoWidth: true,
			baseCls: 'x-plain',
			border: false,
			activeItem: 0,
			//region: 'center',
			items: [
			        //	CARD 1 //
			        new Ext.Panel({
			        	id: 'ctc_tertiar_container',
			        	layout: 'column',
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	autoWidth: true,
			        	items: [
			        	        {
			        	        	width: 160,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [fromField1Container]
			        	        },
			        	        {
			        	        	width: 55,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [{html: 'and'.localize(), baseCls:'x-plain', bodyStyle: 'padding-left: 5px; padding-right: 5px;'}]
			        	        },
			        	        {
			        	        	width: 160,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [fromField2Container]
			        	        }
			        	        ]
			        }),// card 2
			        new Ext.Panel({
			        	id: 'ctc_tertiar_container2',
			        	layout: 'column',
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	autoWidth: true,
			        	items: [
			        	        {
			        	        	width: 160,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [fromField3Container]
			        	        },
			        	        {
			        	        	width: 55,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [{html: 'and'.localize(), baseCls:'x-plain', bodyStyle: 'padding-left: 5px; padding-right: 5px;'}]
			        	        },
			        	        {
			        	        	width: 160,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [fromField4Container]
			        	        }
			        	        ]
			        }),
			        //	end of card 2 //
			        // card 3
			        new Ext.Panel({
			        	id: 'ctc_tertiar_container3',
			        	layout: 'column',
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	autoWidth: true,
			        	items: [
			        	        {
			        	        	width: 230,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [formField5Container]
			        	        }
			        	        ]
			        }),
			        new Ext.Panel({
			        	id: 'ctc_tertiar_container6',
			        	layout: 'column',
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	autoWidth: true,
			        	items: [
			        	        {
			        	        	width: 230,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [formField6Container]
			        	        }
			        	        ]
			        }),
			        new Ext.Panel({
			        	id: 'ctc_tertiar_container7',
			        	layout: 'column',
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	autoWidth: true,
			        	items: [
			        	        {
			        	        	width: 230,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [formField7Container]
			        	        }
			        	        ]
			        }),
			        new Ext.Panel({
			        	id: 'ctc_tertiar_container8',
			        	layout: 'column',
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	autoWidth: true,
			        	items: [
			        	        {
			        	        	width: 230,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [formField8Container]
			        	        }
			        	        ]
			        }),
			        new Ext.Panel({
			        	id: 'ctc_tertiar_container9',
			        	layout: 'column',
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	autoWidth: true,
			        	items: [
			        	        {
			        	        	width: 230,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [formField9Container]
			        	        }
			        	        ]
			        }),
			        new Ext.Panel({
			        	id: 'ctc_tertiar_container10',
			        	layout: 'column',
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	autoWidth: true,
			        	items: [
			        	        {
			        	        	width: 230,
			        	        	layout: 'form',
			        	        	xtype: 'fieldset',
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	autoHeight: true,
			        	        	border: false,
			        	        	frame: false,
			        	        	items: [formField10Container]
			        	        }
			        	        ]
			        })
			        ]
		});

	//	###########################################	CTC Cell value card - must contain one more card ########################
		var CTCCellValue = new Ext.Panel({
			id: 'ctc_secondary_container',
			layout: 'column',
			autoHeight: true,
			baseCls: 'x-plain',
			border: false,
			frame: false,
			items: [
			        {
			        	width: 150,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [CTCComboCellValue]
			        },
			        {
			        	width: 350,
			        	layout: 'form',
			        	id: 'ctc_nest',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [CTCCellValueCard]
			        }
			        ]
		});

		var CTCSpecificText = new Ext.Panel({
			id: 'ctc_specific_text',
			layout: 'column',
			baseCls: 'x-plain',
			border: false,
			frame: false,
			items: [
			        {
			        	//                            columnWidth: 0.3,
			        	width: 140,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [CTCComboSpecificText]
			        },
			        {
			        	width: 300,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [specificTextfield]
			        }
			        ]

		});


		var CTCCard = new Ext.Panel({
			id: 'CTC_card',
			layout: 'card',
			deferredRender: true,
			autoWidth: true,
			baseCls: 'x-plain',
			border: false,
			activeItem: 0,
			//region: 'center',
			items: [
			        CTCCellValue,
			        CTCSpecificText,
			        CTCComboDatesOccHolder,
			        {baseCls: 'x-plain'},
			        {baseCls: 'x-plain'},
			        {baseCls: 'x-plain'},
			        {baseCls: 'x-plain'}
			        ]
		});

		var CTCRight = new Ext.Panel({
			width: 470,
			id: 'ctc_right',
			baseCls: 'xplain',
			items: CTCCard
		});

		var CTCMainContainer = new Ext.Panel({
			id: 'ctc_main_container',
			layout: 'column',
			//height: 80,
			autoHeight: true,
			baseCls: 'x-plain',
			border: false,
			frame: false,
			items: [
			        {
			        	// columnWidth: 0.3,
			        	width: 140,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	id: 'CTCComboHolder',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [CTCCombo]
			        },
			        {
			        	//columnWidth: 0.7,
			        	//width: 480,
			        	id: 'ctc_main_right',
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        CTCRight
	//		        	        CTCCard
			        	        ]
			        }
			        ]
		});

		var cellsThatContain = new Ext.Panel({
			border: true,
			id: 'cells_that_contain',
			frame: true,
			baseCls:'main-panel-open',
			autoHeight: true,
			autoWidth: true,
			layout: 'form',
			items: [
			        {
			        	html: 'Format only cells with'.localize().concat(':'),
			        	baseCls: 'x-plain',
			        	bodyStyle: 'margin-bottom: 10px;'
			        },
			        CTCMainContainer]
		});

	//	#####################################	only top or bottom ranked values	##################################

		var topBottomCombo = new Ext.form.ComboBox({
			store: topBottomComboStore,
			displayField: 'rank',
			id: 'top_bottom_combo',
			hideLabel: true,
			editable: false,
			typeAhead: false,
			tabIndex: 50,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			mode: 'local',
			triggerAction: 'all',
			value: topBottomComboData[0][0],
			selectOnFocus: true,
			listWidth: 100,
			width: 100,
			listeners: {
			select: {
			fn: function(combo, record, index){
			_ai_topbot = topBottomComboData[index][1];
		},
		scope: this
		}
		}
		});

		/* **** */

		var topBottonFld = new Ext.form.TextField({
			name: 'top_bottom_value',
			id: 'top_bottom_value',
			width: 100,
			tabIndex: 51,
			hideLabel: true,
			enableKeyEvents: true,
			value: 10
		});

		var topBottomSSButton = new uniFButton({
			tabIndex: 52,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function() {
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
					fnc: [this, selRange]
					,format: '{Sheet}!{Range}'
					,rng: Ext.getCmp('top_bottom_value').getValue()
					}]);
				_wf = 'top_bottom_value'; that.win.hide()}
		});

		var topBottomValue = {
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 100,
				    	   baseCls:'x-plain',
				    	   items:topBottonFld
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:topBottomSSButton
				       }
				       ]
		};


		var topBotPerc;
		var topBottomCB = new Ext.form.Checkbox({
			fieldLabel: 'perc_of_sel_rng',
			hideLabel: true,
			tabIndex: 53,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			name: 'perc_of_sel_rng',
			boxLabel: '% of the selected range'.localize(),
			listeners: {
			check: {
			fn: function(){
			topBotPerc = this.getValue();
		}
		}
		}
		});

		var topBottomHolder = new Ext.Panel({
			id: 'top_bottom_holder',
			layout: 'column',
			baseCls: 'x-plain',
			border: false,
			frame: false,
			items: [
			        {
			        	columnWidth: 0.3,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	width: 100,
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [topBottomCombo]
			        },
			        {
			        	columnWidth: 0.30,
			        	layout: 'form',
			        	width: 130,
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [topBottomValue]
			        },
			        {
			        	columnWidth: 0.40,
			        	layout: 'form',
			        	width: 200,
			        	xtype: 'fieldset',
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [topBottomCB]
			        }
			        ]
		});

		var topBottomRanked = new Ext.Panel({
			border: true,
			id: 'top_bottom_ranked',
			frame: true,
			baseCls:'main-panel-open',
			autoHeight: true,
			autoWidth: true,
			layout: 'form',
			items: [
			        {
			        	html: 'Format values that rank in the'.localize().concat(':'),
			        	baseCls: 'x-plain',
			        	bodyStyle: 'margin-bottom: 10px;'
			        },
			        topBottomHolder
			        ]
		});

	//	#######################################	only values above/below average	#######################################
		var aboveBelowCombo = new Ext.form.ComboBox({
			store: aboveBelowStore,
			displayField: 'type',
			id: 'above_below_combo',
			hideLabel: true,
			editable: false,
			typeAhead: false,
			mode: 'local',
			tabIndex: 60,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			triggerAction: 'all',
			value: aboveBelowData[0][0],
			selectOnFocus: true,
			listWidth: 120,
			width: 120,
			listeners: {
			select: {
			fn: function(combo, record, index){
			_ab_bel = aboveBelowData[index][1];
		},
		scope: this
		}
		}
		});

		var aboveBelowHolder = new Ext.Panel({
			id: 'above_below_holder',
			layout: 'column',
			baseCls: 'x-plain',
			border: false,
			frame: false,
			items: [
			        {
			        	columnWidth: 0.4,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	width: 170,
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [aboveBelowCombo]
			        },
			        {
			        	columnWidth: 0.6,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	width: 250,
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'the average for the selected range'.localize(),
			        	        	baseCls: 'x-plain'
			        	        }
			        	        ]
			        }
			        ]
		});

		var aboveBelowAverage = new Ext.Panel({
			border: true,
			id: 'above_below_average',
			frame: true,
			baseCls:'main-panel-open',
			autoHeight: true,
			autoWidth: true,
			layout: 'form',
			items: [
			        {
			        	html: 'Format values that are'.localize().concat(':'),
			        	baseCls: 'x-plain',
			        	bodyStyle: 'margin-bottom: 10px;'
			        },
			        aboveBelowHolder]
		});

	//	#####################################	only unique or duplicate values		########################################

		var duplicateCombo = new Ext.form.ComboBox({
			store: duplicateComboStore,
			displayField: 'type',
			id: 'duplicate_combo',
			hideLabel: true,
			editable: false,
			typeAhead: false,
			tabIndex: 70,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			mode: 'local',
			triggerAction: 'all',
			value: duplicateComboData[0][0],
			selectOnFocus: true,
			listWidth: 120,
			width: 120,
			listeners: {
			select: {
			fn: function(combo, record, index){
			_unique = duplicateComboData[index][1];
		},
		scope: this
		}
		}
		});

		var duplicateHolder = new Ext.Panel({
			id: 'duplicate_holder',
			layout: 'column',
			baseCls: 'x-plain',
			border: false,
			frame: false,
			items: [
			        {
			        	columnWidth: 0.4,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	width: 170,
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [duplicateCombo]
			        },
			        {
			        	columnWidth: 0.6,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	width: 250,
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	autoHeight: true,
			        	border: false,
			        	frame: false,
			        	items: [
			        	        {
			        	        	html: 'values in the selected range'.localize(),
			        	        	baseCls: 'x-plain'
			        	        }
			        	        ]
			        }
			        ]
		});

		var uniqueDuplicate = new Ext.Panel({
			border: true,
			id: 'unique_duplicate',
			frame: true,
			baseCls:'main-panel-open',
			autoHeight: true,
			autoWidth: true,
			layout: 'form',
			items: [
			        {
			        	html: 'Format all'.localize().concat(':'),
			        	baseCls: 'x-plain',
			        	bodyStyle: 'margin-bottom: 10px;'
			        },
			        duplicateHolder]
		});

	//	################################	use a formula to determine	####################################################

		var useFormulaField = new Ext.form.TextField({
			name: 'formula_value',
			id: 'formula_value',
			width: 410,
			value: tempOperands,
			tabIndex: 80,
			hideLabel: true,
			enableKeyEvents: true
		});

		var formulaFieldButton = new uniFButton({
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 81,
			handler:function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
					    ,format: '={Sheet}!{Range}'
						,rng: Ext.getCmp('formula_value').getValue()
				}]); _wf = 'formula_value'; that.win.hide()}
		});

		var formulaContainer = {
				//panel',
				layout:'column',
				border:false,
				baseCls:'x-plain',
				items:[
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 410,
				    	   baseCls:'x-plain',
				    	   items:useFormulaField
				       },
				       {
				    	   layout:'form',
				    	   border:false,
				    	   width: 30,
				    	   baseCls:'x-plain',
				    	   items:formulaFieldButton
				       }
				       ]
		};

		var useFormula = new Ext.Panel({
			border: true,
			id: 'use_formula',
			frame: true,
			baseCls:'main-panel-open',
			autoHeight: true,
			autoWidth: true,
			layout: 'form',
			items: [
			        {
			        	html: 'Format values where this formula is true'.localize().concat(':'),
			        	baseCls: 'x-plain',
			        	bodyStyle: 'margin-bottom: 10px;'
			        },
			        formulaContainer
			        ]
		});

	//	#################################	end of subcomponents	########################################################
	//	#################################	main display	################################################################

		var mainDisplay = new Ext.Panel({
			id: 'main_display',
			layout: 'card',
			deferredRender: true,
			autoWidth: true,
			baseCls: 'x-plain',
			border: false,
			activeItem: initActiveItem,
			//region: 'center',
			items: [
			        //basedOnValues, //	TODO: activate when implemented
			        cellsThatContain,
			        topBottomRanked,
			        aboveBelowAverage,
			        uniqueDuplicate,
			        useFormula
			        ]
		});

		// ======================= MAIN FMT FUNCTION =============================

		function executeFormatting(){

			function setCondFormatting() {
				if (!fromFCDLG[1]) fromFCDLG[1]=[false];
				switch(_ai_main){
				// Cell value, between
				case 1:
					switch(_tmpRule.type) {

					case 'cell_value':

						switch(_tmpRule.operator) {
						case 'between':
							var _op1 = '='.concat(fromField1.getValue());
							var _op2 = '='.concat(fromField2.getValue());
							if ((!_op1) || (!_op2))
								alert('The value you entered is not a valid number, date, time or string');
							else {
								_tmpRule.operands = [_op1, _op2];
								_tmpRule.style = fromFCDLG[0];
								_tmpRule.format = fromFCDLG[1][0];

							}
							break;
							// cell value, not between
						case 'not_between':
							var _op3 = '='.concat(fromField3.getValue());
							var _op4 = '='.concat(fromField4.getValue());
							if ((!_op3) || (!_op4))
								alert('The value you entered is not a valid number, date, time or string');
							else {
								_tmpRule.operands = [_op3, _op4];
								_tmpRule.style = fromFCDLG[0];
								_tmpRule.format = fromFCDLG[1][0];
							}
							break;
							//	cell value, equal
						case '=':
							var _op5 = '='.concat(formField5.getValue());
							if (!_op5)
								alert('The value you entered is not a valid number, date, time or string');
							else {
								_tmpRule.operands = [_op5];
								_tmpRule.style = fromFCDLG[0];
								_tmpRule.format = fromFCDLG[1][0];
							}
							break;
							//	cell value, not equal
						case '<>':
							var _op6 = '='.concat(formField6.getValue());
							if (!_op6)
								alert('The value you entered is not a valid number, date, time or string');
							else {
								_tmpRule.operands = [_op6];
								_tmpRule.style = fromFCDLG[0];
								_tmpRule.format = fromFCDLG[1][0];
							}
							break;
							//	cell value, greater
						case '>':
							var _op7 = '='.concat(formField7.getValue());
							if (!_op7)
								alert('The value you entered is not a valid number, date, time or string');
							else {
								_tmpRule.operands = [_op7];
								_tmpRule.style = fromFCDLG[0];
								_tmpRule.format = fromFCDLG[1][0];
							}
							break;
							//	cell value, less
						case '<':
							var _op8 = '='.concat(formField8.getValue());
							if (!_op8)
								alert('The value you entered is not a valid number, date, time or string');
							else {
								_tmpRule.operands = [_op8];
								_tmpRule.style = fromFCDLG[0];
								_tmpRule.format = fromFCDLG[1][0];
							}
							break;
							//	cell value, greater =
						case '>=':
							var _op9 = '='.concat(formField9.getValue());
							if (!_op9)
								alert('The value you entered is not a valid number, date, time or string');
							else {
								_tmpRule.operands = [_op9];
								_tmpRule.style = fromFCDLG[0];
								_tmpRule.format = fromFCDLG[1][0];
							}
							break;
							//	cell value, less =
						case '<=':
							var _op10 = '='.concat(formField10.getValue());
							if (!_op10)
								alert('The value you entered is not a valid number, date, time or string');
							else {
								_tmpRule.operands = [_op10];
								_tmpRule.style = fromFCDLG[0];
								_tmpRule.format = fromFCDLG[1][0];
							}
							break;
						}
						//////////////////////////////////
						//	specific text
						break;
					case 'text':
						var _op = specificTextfield.getValue();
						if (!_op)
							alert('The value you entered is not a valid number, date, time or string');
						else {
							_tmpRule.operands = [_op];
							_tmpRule.style = fromFCDLG[0];
							_tmpRule.format = fromFCDLG[1][0];
						}
						break;
					case 'blanks':
						_tmpRule = {
								type: _tmpRule.type,
								style: fromFCDLG[0],
								format: fromFCDLG[1][0]
						}
						break;
					case 'no_blanks':
						_tmpRule = {
								type: _tmpRule.type,
								style: fromFCDLG[0],
								format: fromFCDLG[1][0]
						}
						break;
					case 'errors':
						_tmpRule = {
								type: _tmpRule.type,
								style: fromFCDLG[0],
								format: fromFCDLG[1][0]
						}
						break;
					case 'no_blanks':
						_tmpRule = {
								type: _tmpRule.type,
								style: fromFCDLG[0],
								format: fromFCDLG[1][0]
						}
						break;
					}


					break;
					// END OF CASE 1
					// top bottom
				case 2:
					var topBotN = topBottonFld.getValue();
					if (topBotPerc) {
						_tmpRule = {
								type: _ai_topbot.concat('_percent'),
								operator: topBotN
						}
					}
					else {
						_tmpRule = {
								type: _ai_topbot,
								operator: topBotN
						}
					}
					_tmpRule.style = fromFCDLG[0];
					_tmpRule.format = fromFCDLG[1][0];
					break;
					//	average value
				case 3:
					_tmpRule = {
							type: 'average_value',
							operator: _ab_bel
					}
					_tmpRule.style = fromFCDLG[0];
					_tmpRule.format = fromFCDLG[1][0];
					break;
				case 4:
					_tmpRule = {
							type: _unique
					}
					_tmpRule.style = fromFCDLG[0];
					_tmpRule.format = fromFCDLG[1][0];
					break;
				case 5:
					var tmpOperand = useFormulaField.getValue();
					tmpOperand = [tmpOperand];
					_tmpRule = {
							type: 'formula_true',
							operands: tmpOperand,
							operator: null,
							style: fromFCDLG[0],
							sit: true,
							format: null
					}
					_tmpRule.style = fromFCDLG[0];
					// delete borders, add new param;


					_tmpRule.format = fromFCDLG[1][0];
					break;

				}
				_tmpRule.borders={};
				_tmpRule.borders.top = (fromFCDLG[0])? fromFCDLG[0].top : '';
				_tmpRule.borders.bottom = (fromFCDLG[0])? fromFCDLG[0].bottom : '';
				_tmpRule.borders.left = (fromFCDLG[0])? fromFCDLG[0].left : '';
				_tmpRule.borders.right = (fromFCDLG[0])? fromFCDLG[0].right : '';

				if (fromFCDLG[2]==null)
					delete _tmpRule.lock;
				else
					_tmpRule.lock = fromFCDLG[2];

				if (_tmpRule.style) {
				delete _tmpRule.style.top;
				delete _tmpRule.style.bottom;
				delete _tmpRule.style.left;
				delete _tmpRule.style.right;
				};

				rules = [_tmpRule];
			}

			////// EXEC PART

			if (!fromFCDLG) fromFCDLG = [null, null, null];
			//setting rule, IF STAND-ALONE
			if ((from == 'fromConditionalManage') || (from == 'editFromConditionalManage')) {
				if ((from == 'editFromConditionalManage') && (!_edited_from_MCF)) {
					fromFCDLG[0] = _style;
					fromFCDLG[1] = _pre.format;
					fromFCDLG[2] = _pre.lock;
				}
				//	if from manage cond form. window
				setCondFormatting();
				rules[0].applies_to = Jedox.wss.app.environment.defaultSelection.getFormula(true);
	//			if (!rules[0].operands) rules[0].operands = [];

				var tArr = rules[0].style;
				for (var w in tArr) {
					if (!tArr[w]) delete tArr[w];
					switch(w) {
					case 'backgroundImage':
						if (tArr[w] == 'none') delete tArr[w];
						break;
					}
				}

				if (from == 'fromConditionalManage')
					var _isEdit = false;
				else
					if (from == 'editFromConditionalManage') {
						var _isEdit = true;
						rules[0].applies_to = _applies_to;
						rules[0].id = _id;

						if (_pre.lock != undefined && !rules[0].lock)
							rules[0].lock = _pre.lock;
					}

				rules[0].borders = _borders;

				var _output = rules;
				addParams(_output, _isEdit);
				that.win.close();
			}
			//	############# STANDARD OUTPUT
			else {
				setCondFormatting();
				var tArr = rules[0].style;
				for (var w in tArr) {
					if (!tArr[w]) delete tArr[w];
					switch(w) {
	//				case 'top': case 'bottom': case 'left': case 'right':
	//					if (tArr[w].color == '#' || tArr[w].type == '' || tArr[w].width == '')
	//						delete tArr[w];
	//					break;
					case 'backgroundImage':
						if (tArr[w] == 'none') delete tArr[w];
						break;
					}
				}
				cndfmt.set(undefined, rules);
				that.win.close();

//				Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
//				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
//				Jedox.wss.app.activeSheet._defaultSelection.getCursorField().refresh();
			}

		};

	//	##########################	MAIN WINDOW	################################
		var _title;
		if (from == 'editFromConditionalManage') _title = 'Edit Formatting Rule'.localize();
		else _title = 'New Formatting Rule'.localize();
		this.win = new Ext.Window({
			title: _title,
			closable: true,
			autoDestroy: true,
			id: 'conditional_formatting',
			cls: 'default-format-window',
			plain: true,
			constrain: true,
			modal: true,
			resizable: false,
			onEsc: Ext.emptyFn,
			animCollapse: false,
			width: winw, //should be 500 - BOV
			height: 420,
			//layout: 'form',
			items: [
			        new Ext.Panel({
			        	baseCls: 'x-title-f',
			        	labelWidth: 100,
			        	labelAlign: 'left',
			        	bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
			        	frame: false,
			        	header: false,
			        	monitorValid: true,
			        	autoHeight: true,
			        	autoWidth: true,
			        	items: [
			        	        {
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	border: true,
			        	        	autoHeight: true,
			        	        	xtype: 'fieldset',
			        	        	layout: 'form',
			        	        	frame: false,
			        	        	title: 'Select a Rule Type'.localize().concat(':'),
			        	        	items: [mainMenu]
			        	        },
			        	        {
			        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			        	        	border: true,
			        	        	autoHeight: true,
			        	        	//	height: 120,
			        	        	xtype: 'fieldset',
			        	        	layout: 'form',
			        	        	frame: false,
			        	        	title: 'Edit the Rule Description'.localize().concat(':'),
			        	        	items: [mainDisplay]
			        	        },
			        	        previewPanel
			        	        ]
			        })
			        ],
			        listeners: {
			close: function()
			{
			if (!_fromDlgF) {
				Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
			}
			that.close();
			Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.newName);
			},
			show: function(){
				setTimeout(function(){previewPanel.doLayout();}, 1);
				setTimeout(function(){
					//that.initFocus(true, 100);
				});
			},
			activate: function(win) {that.activate();}
		},
		buttons: [
			(this.components.OK = new Ext.Button({
				text: 'OK'.localize(),
				tabIndex: 1001,
				handler: function(){
					executeFormatting();
					that.win.close();
				}
			})),
			(this.components.Cancel = new Ext.Button({
				text: 'Cancel'.localize(),
				tabIndex: 1002,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function(){
					if ((from == 'fromConditionalManage') || (from == 'editFromConditionalManage')) {
						addParams(false, false);
					}
					that.win.close();
				}
			}))
			]
		});


		this.setContext();
		this.win.show(this);
	//	_setupColorButton(BOVMinimumColor, state.colorMin, false);
	//	_setupColorButton(BOVMaximumColor, state.colorMax, false);
	//	_setupColorButton(BOVMidpointColor, state.colorMid, false);
	//	_setupColorButton(BOVMaximumColor3, state.colorMax, false);
	//	_setupColorButton(BOVMinimumColor3, state.colorMin, false);
		if (toEdit) {
			switch (_pre.type) {
			// after BOV enabled, mainDisplay.layout.setActiveItem() indexes ++
			case 'cell_value':
				that.win.setWidth(650);
				_ai_main = 1;
				mainDisplay.layout.setActiveItem(0);
				mainMenu.select(0, false, false);
				chooseMenu(mainMenu, 0, '', '');
				// additional switch for parsing operands and operators
				switch (_pre.operator) {

				case '=':
					CTCComboCellValue.setValue('equal to');
					CTCCellValueCard.layout.setActiveItem(2);
					break;

				case '<>':
					CTCComboCellValue.setValue('not equal to');
					CTCCellValueCard.layout.setActiveItem(3);
					break;

				case '<=':
					CTCComboCellValue.setValue('less than or equal to');
					CTCCellValueCard.layout.setActiveItem(7);
					break;

				case '>=':
					CTCComboCellValue.setValue('greater than or equal to');
					CTCCellValueCard.layout.setActiveItem(6);
					break;

				case '<':
					CTCComboCellValue.setValue('less than');
					CTCCellValueCard.layout.setActiveItem(5);
					break;

				case '>':
					CTCComboCellValue.setValue('greater than');
					CTCCellValueCard.layout.setActiveItem(4);
					break;

				case 'between':
					CTCComboCellValue.setValue('between');
					CTCCellValueCard.layout.setActiveItem(0);
					break;

				case 'not_between':
					CTCComboCellValue.setValue('not between');
					CTCCellValueCard.layout.setActiveItem(1);
					break;

				default: //
				}

				break;

			case 'bottom_percent':
				that.win.setWidth(500);
				_ai_main = 2;
				mainDisplay.layout.setActiveItem(1);
				mainMenu.select(1, false, false);
				chooseMenu(mainMenu, 1, '', '');
				topBottomCombo.setValue('Bottom');
				topBottonFld.setValue(_pre.operator);
				topBottomCB.setValue(true);
				break;

			case 'average_value':
				_ai_main = 3;
				mainDisplay.layout.setActiveItem(2);
				mainMenu.select(2, false, false);
				chooseMenu(mainMenu, 2, '', '');
				switch (_pre.operator) {
				case '>':
					aboveBelowCombo.setValue('above');
					break;
				case '<':
					aboveBelowCombo.setValue('below');
					break;
				case '>=':
					aboveBelowCombo.setValue('equal or above');
					break;
				case '<=':
					aboveBelowCombo.setValue('equal or below');
					break;
				case 'std_dev_above_1':
					aboveBelowCombo.setValue('1 std dev above');
					break;
				case 'std_dev_above_2':
					aboveBelowCombo.setValue('2 std dev above');
					break;
				case 'std_dev_above_3':
					aboveBelowCombo.setValue('3 std dev above');
					break;
				case 'std_dev_above_4':
					aboveBelowCombo.setValue('4 std dev above');
					break;
				case 'std_dev_below_1':
					aboveBelowCombo.setValue('1 std dev below');
					break;
				case 'std_dev_below_2':
					aboveBelowCombo.setValue('2 std dev below');
					break;
				case 'std_dev_below_3':
					aboveBelowCombo.setValue('3 std dev below');
					break;
				case 'std_dev_below_4':
					aboveBelowCombo.setValue('4 std dev below');
					break;
				}
				break;

			case 'no_blanks':
				_ai_main = 1;
				mainDisplay.layout.setActiveItem(0);
				mainMenu.select(0, false, false);
				chooseMenu(mainMenu, 0, '', '');
				CTCCard.layout.setActiveItem(4);
				CTCCombo.setValue('No Blanks');
				break;

			case 'blanks':
				_ai_main = 1;
				mainDisplay.layout.setActiveItem(0);
				mainMenu.select(0, false, false);
				chooseMenu(mainMenu, 0, '', '');
				CTCCard.layout.setActiveItem(3);
				CTCCombo.setValue('Blanks');
				break;

			case 'no_errors':
				_ai_main = 1;
				mainDisplay.layout.setActiveItem(0);
				mainMenu.select(0, false, false);
				chooseMenu(mainMenu, 0, '', '');
				CTCCard.layout.setActiveItem(6);
				CTCCombo.setValue('No errors');
				break;

			case 'errors':
				_ai_main = 1;
				mainDisplay.layout.setActiveItem(0);
				mainMenu.select(0, false, false);
				chooseMenu(mainMenu, 0, '', '');
				CTCCard.layout.setActiveItem(5);
				CTCCombo.setValue('Errors');
				break;

			case 'formula_true':
				_ai_main = 5;
				mainDisplay.layout.setActiveItem(4);
				mainMenu.select(4, false, false);
				chooseMenu(mainMenu, 4, '', '');
				break;

			case 'text':
				_ai_main = 1;
				mainDisplay.layout.setActiveItem(0);
				mainMenu.select(0, false, false);
				chooseMenu(mainMenu, 0, '', '');
				CTCCard.layout.setActiveItem(1);
				CTCCombo.setValue('Specific Text');
				switch (_pre.operator) {
				case 'contained':
					CTCComboSpecificText.setValue('containing');
					break;
				case 'not_contained':
					CTCComboSpecificText.setValue('not containing');
					break;
				case 'begins_with':
					CTCComboSpecificText.setValue('beginning with');
					break;
				case 'ends_with':
					CTCComboSpecificText.setValue('ending with');
					break;
				}
				break;

			case 'top':
				_ai_main = 2;
				that.win.setWidth(500);
				mainDisplay.layout.setActiveItem(1);
				mainMenu.select(1, false, false);
				chooseMenu(mainMenu, 1, '', '');
				topBottomCombo.setValue('Top');
				topBottonFld.setValue(_pre.operator);
				topBottomCB.setValue(false);
				break;

			case 'top_percent':
				_ai_main = 2;
				that.win.setWidth(500);
				mainDisplay.layout.setActiveItem(1);
				mainMenu.select(1, false, false);
				chooseMenu(mainMenu, 1, '', '');
				topBottomCombo.setValue('Top');
				topBottonFld.setValue(_pre.operator);
				topBottomCB.setValue(true);
				break;

			case 'bottom':
				_ai_main = 2;
				that.win.setWidth(500);
				mainDisplay.layout.setActiveItem(1);
				mainMenu.select(1, false, false);
				chooseMenu(mainMenu, 1, '', '');
				topBottomCombo.setValue('Bottom');
				topBottonFld.setValue(_pre.operator);
				topBottomCB.setValue(false);
				break;

			case 'duplicate_value':
				_ai_main = 4;
				mainDisplay.layout.setActiveItem(3);
				mainMenu.select(3, false, false);
				chooseMenu(mainMenu, 3, '', '');
				duplicateCombo.setValue('duplicate');
				break;

			case 'unique_value':
				_ai_main = 4;
				mainDisplay.layout.setActiveItem(3);
				mainMenu.select(3, false, false);
				chooseMenu(mainMenu, 3, '', '');
				duplicateCombo.setValue('unique');
				break;

			default:
				mainDisplay.layout.setActiveItem(0);
			//mainMenu.select(0, false, false);
			//
			}
			var tmpRec = new tmpDummy({
				dummy: '<div style="font-style: '.concat(_style.fontStyle, '; background:', _style.backgroundColor, '; text-decoration:', _style.textDecoration, '; font-weight: ', _style.fontWeight, '; color:', _style.color, '; background-image:', _style.backgroundImage, ';border-top:', _borders.top.width, ' ', _borders.top.type, ' ', _borders.top.color, ';', ';border-bottom:', _borders.bottom.width, ' ', _borders.bottom.type, ' ', _borders.bottom.color, ';', ';border-left:', _borders.left.width, ' ', _borders.left.type, ' ', _borders.left.color, ';', ';border-right:', _borders.right.width, ' ', _borders.right.type, ' ', _borders.right.color, '; line-height: 52px;">AaBbCcZz</div>')
			});

			dummyStore.removeAll();
			dummyStore.insert(0, tmpRec);
			setTimeout(function(){formatPreview.refresh();},1);
			//formatPreview.refresh();
			_pre = {};
			for (var i in toEdit)
			{
				_pre[i] = _tmpRule[i] = toEdit[i];
			}
		}
		else {
			mainMenu.select(0, false, false);
			chooseMenu(mainMenu, 0, '', '');
		}

		previewPanel.show();


		//	setting predefined types, operators and operands
		if (!_ai_main) _ai_main = 0; // + 1;
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.ConditionalFormatting, Jedox.dlg.Dialog);
