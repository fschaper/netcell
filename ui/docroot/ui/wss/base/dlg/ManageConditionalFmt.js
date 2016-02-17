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
 * SVN: $Id: ManageConditionalFmt.js 4663 2011-02-28 09:56:01Z andrejv $
 *
 */

Jedox.wss.dlg.manageConditionalFormatting = function(){
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.ManageCF());
};

Jedox.wss.dlg.ManageCF = (function() {

	return function () {

		Jedox.wss.dlg.ManageCF.parent.constructor.call(this);
		this.id = 'manageCF';
		var that = this;


		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		Array.prototype.findIndex = function(value){
			var ctr = "";
			for (var i=0; i < this.length; i++) {
				// use === to check for Matches. ie., identical (===), ;
				if (this[i][0] == value) {
					return i;
				}
			}
			return ctr;
		};

		function isArray(obj) {
			   if (obj.constructor.toString().indexOf("Array") == -1)
			      return false;
			   else
			      return true;
			}

		var fromCFDLG;
		var _applies_to;
		var _to_apply = [];
		var _to_delete = [];
		var _idd;
		var _selRow;
		var _selected;
		var _sel;
		var _currSel = false;
		var currWSId = Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetId();
		var _toEdit = false;

		var openCFDLG = function(fmDesc, toEdit){
			that.win.show();
			fromCFDLG = fmDesc;
			if (!fromCFDLG) return;
			if (toEdit) {
				fromCFDLG[0].id = _idd;
				fromCFDLG[0].applies_to = _applies_to;
				_toEdit = toEdit;

				var _double = false;
				for (var q=0; q<_to_apply.length; q++){
					if (fromCFDLG[0].id == _to_apply[q].id){
						_double = true;
						_to_apply[q] = fromCFDLG[0];
					}
				}

				if (!_double) _to_apply.push(fromCFDLG[0]);

				//_to_apply.push(fromCFDLG[0]);
				gridData.splice(_selIdx, 1, parseRawRule(fromCFDLG, true));
			}
			else {
				_to_apply.push(fromCFDLG[0]);
				//rawRules.push(fromCFDLG[0]);
				gridData.push(parseRawRule(fromCFDLG, true));
			}
			gridStore.loadData(gridData);
			grid.reconfigure(gridStore, gridCM);
			gridStore.loadData(gridData);
			Ext.getCmp('manage-cnd-apply-button').enable();
			Ext.getCmp('manage-cf-close-button').setText('Cancel');
		};

		//	##########################	Extensions	- Active checkbox ##########################
		Ext.grid.CheckColumn = function(config){
			Ext.apply(this, config);
			if (!this.id) {
				this.id = Ext.id();
			}
			this.renderer = this.renderer.createDelegate(this);
		};

		Ext.grid.CheckColumn.prototype = {
				init: function(grid){
			this.grid = grid;
			this.grid.on('render', function(){
				var view = this.grid.getView();
				view.mainBody.on('mousedown', this.onMouseDown, this);
			}, this);
		},
		onMouseDown: function(e, t){
			if (t.className && t.className.indexOf('x-grid3-cc-' + this.id) != -1) {
				e.stopEvent();
				var index = this.grid.getView().findRowIndex(t);
				var record = this.grid.store.getAt(index);
				record.set(this.dataIndex, !record.data[this.dataIndex]);
				_ident = gridData[index][0];
				var _tmp = gridData[index][1];
				var _tmc = gridData[index][2];
				var _act = record.data[this.dataIndex];
				//	to edit here
				//rawRules[index].sit = _act;
				_to_apply.push(rawRules[index]);

				Ext.getCmp('manage-cnd-apply-button').enable();
				Ext.getCmp('manage-cf-close-button').setText('Cancel');
			}
		},
		renderer: function(v, p, record){
			p.css += ' x-grid3-check-col-td';
			return '<div class="x-grid3-check-col' +
			(v ? '-on' : '') +
			' x-grid3-cc-' +
			this.id +
			'"> </div>';
		}
		};

		//	##########################	FUNCTIONS	##################################

		var cndfmt = Jedox.wss.cndfmt;

		//	get worksheets and put-in-store function
		var worksheets = Jedox.backend.wss.getSheets()[0];
		var putWSinStore = function(){
			for (i = 1; worksheets[i] != null; i = i + 2) {
				// currWSId
				var j = i - 1;
				if (worksheets[j] != currWSId)
					selectionData.push([worksheets[i], worksheets[j]]);
			};
		};

		//	##########################	STORES, DATA, ETC	##########################

		//	### HELPER DATA
		var helperData = [['duplicate'.localize(), 'duplicate_value'], ['unique'.localize(), 'unique_value'], ['Cell Value'.localize(), 'cell_value'], ['Specific Text'.localize(), 'text'], ['Dates Occurring'.localize(), 'dates_occ'], // !!! Missing dates! - NOT SUPPORTED
		                  ['Blanks'.localize(), 'blanks'], ['Use a formula'.localize(), 'formula_true'], ['No Blanks'.localize(), 'no_blanks'], ['Errors'.localize(), 'errors'], ['No errors'.localize(), 'no_errors'], ['between'.localize(), 'between'], ['not between'.localize(), 'not_between'], ['equal to'.localize(), '='], ['not equal to'.localize(), '<>'], ['grater than'.localize(), '>'], ['less than'.localize(), '<'], ['greater than or equal to'.localize(), '>='], ['less than or equal to'.localize(), '<='], ['containing'.localize(), 'contained'], ['not containing'.localize(), 'not_contained'], ['beginning with'.localize(), 'begins_with'], ['ending with'.localize(), 'ends_with'], ['Top'.localize(), 'top'], ['Bottom'.localize(), 'bottom'], ['Top'.localize(), 'top_percent'], ['Bottom'.localize(), 'bottom_percent'], ['duplicate'.localize(), 'duplicate_value'], ['unique'.localize(), 'unique_value'], ['Average Value'.localize(), 'average_value']];

		var helperDataAverage = [['above'.localize(), '>'], ['below'.localize(), '<'], ['equal or above'.localize(), '>='], ['equal or below'.localize(), '<='], ['1 std dev above'.localize(), 'std_dev_above_1'], ['1 std dev below'.localize(), 'std_dev_below_1'], ['2 std dev above'.localize(), 'std_dev_above_2'], ['2 std dev below'.localize(), 'std_dev_below_2'], ['3 std dev above'.localize(), 'std_dev_above_3'], ['3 std dev below'.localize(), 'std_dev_below_3']];

		var selectionData = [['Current Selection'.localize(), 'SCOPE_CURR_SEL'], ['This Worksheet'.localize(), 'SCOPE_CURR_WKS']];

		putWSinStore();

		var selectionStore = new Ext.data.SimpleStore({
			fields: ['rules_for', 'id'],
			data: selectionData
		});

		//	############# LOAD INITIAL -- LOAD
		var gridData = [    //			['alfa', 'format', '$D$5', false],
		                    ];

		var _currScope = cndfmt.SCOPE_CURR_SEL;
		var rawRules = cndfmt.get(_currScope);
		//	parse and add to gridData:

		var parseRawRule = function(_RR, _one){
			for (var i = 0; i < _RR.length; i++) {
				var _o = _RR[i];
				var _desc;
				for (var j = 0; j < helperData.length; j++) {
					if (_o.type == helperData[j][1])
						_desc = helperData[j][0];
				}
				//	now operator:
					if (_o.type == 'average_value') {
						for (var e = 0; e < helperDataAverage.length; e++) {
							if (_o.operator == helperDataAverage[e][1])
								_desc = _desc.concat(' ', helperDataAverage[e][0]);
						}
					}
					else {
						for (var e = 0; e < helperData.length; e++) {
							if (_o.operator == helperData[e][1])
								_desc = _desc.concat(' ', helperData[e][0]);
						}
					}

					if (_o.operands) {
					if (_o.operands.length == 1) {
						// if only one operand
						_desc = _desc.concat(' ', _o.operands[0].replace(/=/i, ""));
					}
					else {
						// if more than one operand
						if (isArray(_o.operands))
						for (var o = 0; o < _o.operands.length; o++) {
							if (o == 0)
								_desc = _desc.concat(' ', _o.operands[o].replace(/=/i, ""));
							else
								_desc = _desc.concat(' and ', _o.operands[o].replace(/=/i, ""));
						}
						else
							_desc = _desc.concat(' ', _o.operands.replace(/=/i, ""));
					}
					if (!(_o.operands instanceof Array)) _o.operands = [_o.operands];
					}

					if (!_o.style)
						_o.style = {};

					if (!_o.borders) _o.borders = {};
					if (!_o.borders.top)
						_o.borders.top = {
							width: '',
							type: '',
							color: ''
					};
					if (!_o.borders.bottom)
						_o.borders.bottom = {
							width: '',
							type: '',
							color: ''
					};
					if (!_o.borders.left)
						_o.borders.left = {
							width: '',
							type: '',
							color: ''
					};
					if (!_o.borders.right)
						_o.borders.right = {
							width: '',
							type: '',
							color: ''
					};

					var _sample = '<div style="font-style: '.concat(_o.style.fontStyle, '; background:', _o.style.backgroundColor, '; text-decoration:', _o.style.textDecoration, '; font-weight: ', _o.style.fontWeight, '; color:', _o.style.color, '; background-image:', _o.style.backgroundImage, ';border-top:', _o.borders.top.width, ' ', _o.borders.top.type, ' ', _o.borders.top.color, ';', ';border-bottom:', _o.borders.bottom.width, ' ', _o.borders.bottom.type, ' ', _o.borders.bottom.color, ';', ';border-left:', _o.borders.left.width, ' ', _o.borders.left.type, ' ', _o.borders.left.color, ';', ';border-right:', _o.borders.right.width, ' ', _o.borders.right.type, ' ', _o.borders.right.color, '; line-height: 18px; text-align: center;">AaBbCcZz</div>');
					if (!_desc)
						_desc = 'undefined';
					var id = _o.id;
					var _a = [_desc, _sample, _o.applies_to, true, i, id, _o];

					if (_one)
						return _a;
					else
						gridData.push(_a);
			}
		};

		parseRawRule(rawRules);

		var gridStore = new Ext.data.SimpleStore({
			fields: [{
				name: 'rule'
			}, {
				name: 'format'
			}, {
				name: 'applies'
			}, {
				name: 'stop'
			}, {
				name: 'id'
			},{
				name: 'realId'
			}]
		});
		gridStore.loadData(gridData);

		function changeSelection(combo, record, index){

			gridData = [];
			gridStore.removeAll();

			if (index == 1)
				{
					_currScope = cndfmt.SCOPE_CURR_WKS;
					rawRules = cndfmt.get(_currScope);
					_currSel = true;
				}
			else if (index == 0)
				{
					_currScope = cndfmt.SCOPE_CURR_SEL;
					rawRules = cndfmt.get(_currScope);
					_currSel = false;
				}
				else
					rawRules = cndfmt.get(selectionData[index][1]);

			parseRawRule(rawRules);
			gridStore.loadData(gridData);
			grid.reconfigure(gridStore, gridCM);
		}

		//	##########################	COMPONENTS	################################

		var selection = this.cmpFocus = new Ext.form.ComboBox({
			store: selectionStore,
			displayField: 'rules_for',
			id: 'wManageCF_selection_cmb',
			hideLabel: true,
			editable: false,
			tabIndex: 1,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			typeAhead: true,
			mode: 'local',
			value: selectionData[0][0],
			triggerAction: 'all',
			width: 200,
			listeners: {
			select: {
			fn: changeSelection,
			scope: this
		}
		}
		});

		var newRuleBtn = new Ext.Button({
			minWidth: 100,
			cls: "x-btn-text-icon",
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 2,
			iconCls: 'cnd_fmt_new',
			text: 'New Rule'.localize().concat('...'),
			listeners: {
			click: {
			fn: function(){

			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.conditionalFormatting, ['fromConditionalManage', openCFDLG]);
			that.win.hide();
		},
		scope: this
		}
		}
		});

		var editRuleBtn = new Ext.Button({
			minWidth: 100,
			cls: "x-btn-text-icon",
			iconCls: 'cnd_fmt_edit',
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 3,
			text: 'Edit Rule'.localize().concat('...'),
			listeners: {
			click: {
			fn: function(){

			if(isNaN(_selIdx)){
				Ext.Msg.alert('Edit Rule'.localize(), 'Please select rule to edit'.localize());
				return;
			}

			_selected = gridData[_selIdx][6].id;
			_applies_to = gridData[_selIdx][6].applies_to;
			_sel = gridData[_selIdx][4];
			_idd = gridData[_selIdx][5];

			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.conditionalFormatting, ['editFromConditionalManage', openCFDLG, gridData[_selIdx][6]]);
			that.win.hide();
		},
		scope: this
		}
		}
		});
		var _smt_to_delete = false;
		var deleRuleBtn = new Ext.Button({
			minWidth: 100,
			cls: "x-btn-text-icon",
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 4,
			iconCls: 'cnd_fmt_delete',
			text: 'Delete Rule'.localize(),
			listeners: {
			click: {
			fn: function(){
			_to_delete.push(_idd);
			_smt_to_delete = true;
			gridData.splice(_selIdx, 1);
			Ext.getCmp('manage-cnd-apply-button').enable();
			Ext.getCmp('manage-cf-close-button').setText('Cancel');
			gridStore.loadData(gridData);
			grid.reconfigure(gridStore, gridCM);

		},
		scope: this
		}
		}
		});

		// sorting handlers and elements

		var sortingArray = [];

		var upBtn = new Ext.Button({
			cls: "x-btn-icon",
			iconCls: 'cnd_fmt_up',
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 10,
			handler: function() {
				var toSelect = [];
				var selection = grid.getSelectionModel().getSelected();

				if (!selection) return;
				Ext.getCmp('manage-cnd-apply-button').enable();

				var n = gridStore.indexOf(selection);

				gridStore.remove(selection);
				if (n != 0)
					{
					gridStore.insert(n-1, selection);
					toSelect = n-1;
					}
				else
					{
					gridStore.insert(n, selection);
					toSelect = n;
					}

				sortingArray.push(selection.data.realId, 1);

				grid.getSelectionModel().selectRow(toSelect);
		}
		});

		var downBtn = new Ext.Button({
			cls: "x-btn-icon",
			iconCls: 'cnd_fmt_down',
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 11,
			handler: function() {
				var toSelect = [];
				var selection = grid.getSelectionModel().getSelected();

				if (!selection) return;
				Ext.getCmp('manage-cnd-apply-button').enable();

				var n = gridStore.indexOf(selection);
				var f = gridStore.collect('realId');

				gridStore.remove(selection);
				if (n != f.length-1)
					{
					gridStore.insert(n+1, selection);
					toSelect = n+1;
					}
				else
					{
					gridStore.insert(n, selection);
					toSelect = n;
					}

				sortingArray.push(selection.data.realId, -1);
				grid.getSelectionModel().selectRow(toSelect);
		}
		});

		// *** end of sorting elements ***

	//	var sit = new Ext.grid.CheckColumn({
	//		header: 'Stop If True'.localize(),
	//		dataIndex: 'stop',
	//		width: 90
	//	});

		var gridCM = new Ext.grid.ColumnModel([{
			id: 'rule',
			header: "Rule (applied in order shown)".localize(),
			width: 180,
			sortable: false,
			dataIndex: 'rule'
		}, {
			header: "Format".localize(),
			width: 120,
			sortable: false,
			dataIndex: 'format'
		}, {
			id: 'applies',
			header: "Applies to".localize(),
			width: 100,
			sortable: false,
			dataIndex: 'applies',
			editor: new Ext.form.TriggerField({
	        	id: 'triggerEditorF',
	        	listeners: {
	    			change: function(e, newValue, oldValue){
	    			var index = _selIdx;
	    			var record = grid.store.getAt(index);
	    			_ident = gridData[index][0];
	    			var _tmp = gridData[index][1];
	    			var _tmc = gridData[index][2];
	    			var _act = record.data[this.dataIndex];
	    			//	to edit here
	    			rawRules[index].applies_to = newValue;
	    			var _double = false;
	    			for (var q=0; q<_to_apply.length; q++){
	    				if (rawRules[index].id == _to_apply[q].id){
	    					_double = true;
	    					_to_apply[q].applies_to = rawRules[index].applies_to;
	    				}
	    			}

	    			if (!_double) _to_apply.push(rawRules[index]);

	    			Ext.getCmp('manage-cnd-apply-button').enable();
	    			Ext.getCmp('manage-cf-close-button').setText('Cancel');
	    		}
	    		},
	        	onTriggerClick : function(){
	        	// function for trigger click
	        	var stil = grid.getSelectionModel().getSelected().data.tf;
	        	var tData = grid.getSelectionModel().getSelected().data;

	        	function selRange(selected){
	        		that.win.show();
					setTimeout(function() {
						var index = _gid;
						var record = grid.store.getAt(index);
						_ident = gridData[index][0];
						var _tmp = gridData[index][1];
						var _tmc = gridData[index][2];

						//selected = selected.split('!');

						rawRules[index].applies_to = '='.concat(selected);

						var _double = false;
		    			for (var q=0; q<_to_apply.length; q++){
		    				if (rawRules[index].id == _to_apply[q].id){
		    					_double = true;
		    					_to_apply[q].applies_to = rawRules[index].applies_to;
		    				}
		    			}

		    			if (!_double) _to_apply.push(rawRules[index]);

						//_to_apply.push(rawRules[index]);

						record.set('applies', '='.concat(selected));
						Ext.getCmp('manage-cnd-apply-button').enable();
						Ext.getCmp('manage-cf-close-button').setText('Cancel');
					}, 1);
				}
	        	that.win.hide()
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
					fnc: [this, selRange]
					,rng: Ext.getCmp('triggerEditorF').getValue()
					,format: '{Sheet}!{Range}'
	    			,omitInitSheet: true
				}]);
				var _gid = grid.getSelectionModel().getSelected().data.id;

	        },
	        	triggerClass: 'hl-triggerFld-shSel',
	         	triggerConfig: {
	                     tag: 'span',
	                     cls: 'hl-triggerFld-shSel',
	                     cn: [{
	                         tag: 'img',
	                         src: Ext.BLANK_IMAGE_URL,
	                         cls: 'x-form-trigger ' + this.triggerClass
	                     }, {
	                         tag: 'img',
	                         src: Ext.BLANK_IMAGE_URL,
	                         cls: 'x-form-trigger hl-triggerFld-shSel'
	                     }]
	                 }
	             })

		}
		//,sit
		]);

		var _selIdx;

		var grid = new Ext.grid.EditorGridPanel({
			store: gridStore,
			clicksToEdit: 1,
			//plugins: sit,
			cm: gridCM,
			stripeRows: false,
			sm: new Ext.grid.RowSelectionModel({
				singleSelect: true
			}),
			viewConfig: {
	            forceFit: true
			},
			enableHdMenu: false,
			autoExpandColumn: 'applies',
			height: 200,
			autoWidth: true,
			baseCls: 'x-plain',
			listeners: {
				rowclick: function(gr, index, e) {
				_selRow = index;
			},
			rowdblclick: function(grid, rowIndex, e){
				_selected = gridData[rowIndex][6].id;
				_applies_to = gridData[rowIndex][6].applies_to;
				_sel = gridData[rowIndex][4];
				_idd = gridData[rowIndex][5];

		//		_selected = gridData[rowIndex].id;
		//_applies_to = gridData[rowIndex].applies_to;
		//		_sel = gridData[rowIndex][4];
		//		_idd = gridData[rowIndex][5];

		//		Jedox.gen.load(Jedox.wss.app.dynJSRegistry.conditionalFormatting, ['editFromConditionalManage', openCFDLG, rawRules[_sel]]);
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.conditionalFormatting, ['editFromConditionalManage', openCFDLG, gridData[rowIndex][6]]);
				that.win.hide();
			}
		}
		});

		grid.getSelectionModel().on('rowselect', function(sm, rowIdx, r){
			//        _selected = rawRules[rowIdx].id;
	//		_sel = gridData[rowIdx][4];
	//		_selIdx = rowIdx;
	//		_idd = gridData[rowIdx][5];
			_selected = gridData[rowIdx].id;
			_sel = gridData[rowIdx][4];
			_selIdx = rowIdx;
			_idd = gridData[rowIdx][5];
		});

		var mainApplyButton = {
				text: 'Apply'.localize(),
				disabled: true,
				tabIndex: 103,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				id: 'manage-cnd-apply-button',
				handler: function(){


			if (_to_apply.length)
				cndfmt.set(_currScope, _to_apply, sortingArray);
			else if (sortingArray.length > 0)
				cndfmt.set(_currScope, undefined, sortingArray);
			if (_smt_to_delete)
				cndfmt.remove(cndfmt.SCOPE_RULE_IDS, _to_delete);

				// REFRESH!!!
			// calbeck after saving

			_smt_to_delete = false;
			_to_apply = [];
			_to_delete = [];

			Ext.getCmp('manage-cnd-apply-button').disable();
			Ext.getCmp('manage-cf-close-button').setText('Close');

	//		gridData = [];
	//		gridStore.removeAll();
	//		rawRules = false;
	//
	//			if (_currSel)
	//				rawRules = cndfmt.get(cndfmt.SCOPE_CURR_WKS);
	//			else
	//				rawRules = cndfmt.get(cndfmt.SCOPE_CURR_SEL);
	//
	//			parseRawRule(rawRules);
	//			gridStore.loadData(gridData);
	//			grid.reconfigure(gridStore, gridCM);
		}
		}


		//	##########################	MAIN WINDOW	################################

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
			baseCls: 'x-title-f',
			labelWidth: 100,
			labelAlign: 'left',
			layout: 'form',
			bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
			frame: false,
			header: false,
			monitorValid: true,
			autoHeight: true,
			autoWidth: true,
			items: [{
				//panel selection,
				layout: 'column',
				border: false,
				baseCls: 'x-plain',
				items: [{
					layout: 'form',
					border: false,
					width: 160,
					baseCls: 'x-plain',
					items: [{
						html: 'Show formatting rules for'.localize().concat(':'),
						baseCls: 'x-plain',
						bodyStyle: 'padding-top: 3px;'
					}]
				}, {
					layout: 'form',
					border: false,
					autoWidth: true,
					baseCls: 'x-plain',
					items: selection
				}]
			},            //	button bar
			{
				//panel selection,
				layout: 'column',
				border: false,
				bodyStyle: 'padding-top: 3px; margin-bottom: 5px;',
				baseCls: 'x-plain',
				items: [{
					layout: 'form',
					border: false,
					width: 105,
					baseCls: 'x-plain',
					items: [newRuleBtn]
				}, {
					layout: 'form',
					border: false,
					width: 105,
					baseCls: 'x-plain',
					items: [editRuleBtn]
				}, {
					layout: 'form',
					border: false,
					width: 105,
					baseCls: 'x-plain',
					items: [deleRuleBtn]
				},
			    {
			     layout:'form',
			     border:false,
			     width: 30,
			     baseCls:'x-plain',
			     items:[upBtn]
				},
			    {
			     layout:'form',
			     border:false,
			     width: 30,
			     baseCls:'x-plain',
			     items:[downBtn]
				}
				]
			}, grid]
		})

		this.win = new Ext.Window({
			title: 'Conditional Formatting Rules Manager'.localize(),
			closable: true,
			autoDestroy: true,
			plain: true,
			constrain: true,
			modal: true,
			cls: 'default-format-window',
			resizable: false,
			animCollapse: false,
			onEsc: Ext.emptyFn,
			width: 600,
			height: 350,
			items: [mainPanel],
			listeners: {
				close: function(){
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.manageConditionalFormatting);
				},
				show:function(){
					setTimeout(function(){
						that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();}
		},

		buttons: [
				(this.components.OK = new Ext.Button({
					text: 'OK'.localize(),
					tabIndex: 101,
					handler: function(){
						if (_to_apply.length)
							cndfmt.set(_currScope, _to_apply, sortingArray);
						else if (sortingArray.length > 0)
							cndfmt.set(_currScope, undefined, sortingArray);
						if (_smt_to_delete)
							cndfmt.remove(cndfmt.SCOPE_RULE_IDS, _to_delete);
						that.win.close();
					}
				})),
				(this.components.Cancel = new Ext.Button({
					text: 'Cancel'.localize(),
					id: 'manage-cf-close-button',
					tabIndex: 102,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					handler: function(){
						that.win.close();
					}
				})),
				mainApplyButton
				]
		});


		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.ManageCF, Jedox.dlg.Dialog);
