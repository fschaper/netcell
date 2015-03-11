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
 * SVN: $Id: Source.js 5111 2011-07-13 13:58:25Z lukap $
 *
 */

Jedox.wss.dlg.control.source = function(callback, _pre, tabOffset, thats) {

	if (!tabOffset) tabOffset = 0;
	// =========== components ===============

	var srcComboData = [
	                    ['none', 'None'.localize()],
	                    ['range', 'Range'.localize()],
	                    ['function', 'Function'.localize()],
	                    ['macro', 'Macro'.localize()],
	                    ['subset', 'Subset'.localize()]
	                    ];

	var srcDatReg = {
			'none': 0,
			'': 0,
			'range': 1,
			'function': 2,
			'macro': 3,
			'subset': 4
	}

	var srcPreType = (srcDatReg[_pre.srctype])? srcDatReg[_pre.srctype] : 0;
	var srcType = (_pre.srctype)? _pre.srctype : 'none';

	var srcComboStore = new Ext.data.ArrayStore({
	    fields: ['src', 'desc'],
	    idIndex: 0,
	    data: srcComboData
	});

	var srcCombo = new Ext.form.ComboBox({
	    typeAhead: false,
	    editable: false,
	    triggerAction: 'all',
	    disabled: thats.typeDisabled,
	    width: 150,
	    value: srcComboData[srcPreType][1],
	    lazyRender:true,
	    tabIndex: tabOffset + 2,
	    ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	    mode: 'local',
	    store: srcComboStore,
	    valueField: 'src',
	    displayField: 'desc',
	    listeners: {
			select: function(c, r, i){
				sourceCardHolder.layout.setActiveItem(i);
				sourceCardHolder.doLayout();
				sourceCardHolder.layout.activeItem.doLayout();
				thats.containers.srcCard = sourceCardHolder.layout.activeItem;
				formulaField.setValue('');
				srcType = srcComboData[i][0];
			}
		}
		});

	function selRange(selected){
		Ext.getCmp('formatControlDialog').show();
		setTimeout(function() {
			rangeFld.setValue(selected);
			formulaField.setValue('='.concat(selected));
		}, 1);
	};

	var selectorBtn = new Ext.Button({
		id: 'selBtnsrc',
		iconCls: 'select-range-icon',
		tabIndex: tabOffset + 4,
	    ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		cls: 'x-btn-icon',
		tooltip: "Select Range".localize(),
		handler: function() {
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
				fnc: [this, selRange]
  					,format: '{Sheet}!{Range}'
  					,rng: rangeFld.getValue()
  					,omitInitSheet: true
  				}]);
			Ext.getCmp('formatControlDialog').hide();
	}
	});


	// ===============================

	var srcTypeOld = 'none';
	var sourceWiz = new Ext.form.Radio({
			checked: !thats.typeDisabled,
			name: 'radioSourceForm',
			tabIndex: tabOffset + 1,
		    ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			//hideLabel: true,
		    boxLabel: '',
		    style: 'height: 25px;',
			listeners: {
				check: function(thisRb, isChecked)
				{
					if (isChecked)
					{
						thats.typeDisabled = false;
						if (_pre.type == Jedox.wss.wsel.type.WIDGET){
							srcCombo.enable();
							sourceCardHolder.layout.activeItem.enable();
							srcType = srcTypeOld;
						} else {
							subsetBtnS.enable();
						}
						formulaField.disable();
					}
				}
			}
		});

	var sourceFormula = new Ext.form.Radio({
		checked: thats.typeDisabled,
		name: 'radioSourceForm',
		tabIndex: tabOffset + 10,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		boxLabel: 'Formula'.localize(),
		hideLabel: true,
		listeners: {
			check: function(thisRb, isChecked)
			{
				if (isChecked)
				{
					thats.typeDisabled = true;
					if (_pre.type == Jedox.wss.wsel.type.WIDGET){
						srcCombo.disable();
						sourceCardHolder.layout.activeItem.disable();
						srcTypeOld = srcType;
						srcType = 'custom';
					} else {
						subsetBtnS.disable();
					}
					formulaField.enable();
				}
			}
		}
	});

	// ========= card range

	var rangeFld = new Ext.form.Field({
		hideLabel: true,
		width: 150,
		tabIndex: tabOffset + 3,
	    ctCls: Jedox.kbd.Base.tags.NO_ENTER
	});

	var cardRangeHolder = new Ext.Panel({
		layout: 'column',
		baseCls: 'x-plain',
		bodyStyle: 'padding-left: 10px;',
		autoWidth: true,
		items: [
				new Ext.Panel({
					baseCls: 'x-plain',
					width: 150,
					border:false,
					layout: 'form',
					items: [rangeFld]
				}),
				new Ext.Panel({
					baseCls: 'x-plain',
					layout:'form',
					border:false,
					width: 50,
					items: [selectorBtn]
				})
		        ]
	});

	var cardRange = new Ext.Panel({
		layout: 'form',
		xtype: 'fieldset',
		autoHeight: true,
		baseCls: 'x-plain',
		autoWidth: true,
		items: [cardRangeHolder],
		listeners: {
			enable: function(p){
				rangeFld.enable();
				selectorBtn.enable();
			},
			disable: function(p){
				rangeFld.disable();
				selectorBtn.disable();
			}
		}
	});


	// =========== c r ==================

	// =========== function

	var setFuncFn = function(cnf)
	{
		Ext.getCmp('formatControlDialog').show();
		formulaField.setValue(cnf);
		fnArgsButton.enable();
		//thats._gendata = cnf._gendata;
	};

	var fnButton = new Ext.Button({
		id: 'fnbtn',
		tabIndex: tabOffset + 5,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		iconCls: 'insert_formula_icon',
		text: 'Select Function'.localize(),
		cls: 'x-btn-icon-text',
		handler: function(){
			Ext.getCmp('formatControlDialog').hide();
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.insertFunction, [{id:'control', fn:setFuncFn}, formulaField.getValue()]);
		}
	});

	var fnArgDisabled = (_pre.src && _pre.srctype == 'function')? false:true;
	var fnArgsButton = new Ext.Button({
		id: 'fnargsbtn',
		tabIndex: tabOffset + 6,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		iconCls: 'insert_formula_icon',
		text: 'Function Arguments'.localize(),
		disabled: fnArgDisabled,
		cls: 'x-btn-icon-text',
		handler: function(){
			Ext.getCmp('formatControlDialog').hide();
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.funcArgs, [ false, {fn: setFuncFn, id: 'control'}, formulaField.getValue() ]);
		}
	});

	var cardFunction = new Ext.Panel({
		layout: 'column',
		xtype: 'fieldset',
		autoHeight: true,
		bodyStyle: 'padding-left: 10px;',
		baseCls: 'x-plain',
		autoWidth: true,
		items: [
				new Ext.Panel({
					baseCls: 'x-plain',
					width: 105,
					items: [fnButton]
				}),
				new Ext.Panel({
					baseCls: 'x-plain',
					width: 130,
					items: [fnArgsButton]
				})],
		listeners: {
			enable: function(p){
				fnButton.enable();
				fnArgsButton.enable();
			},
			disable: function(p){
				fnButton.disable();
				fnArgsButton.disable();
			}
		}
	});

	// ======== fn

	//======= macro

	var _getMacroData = function() {
		return {
			type: Jedox.wss.wsel.type.WIDGET,
			name: Ext.getCmp('txtName').getValue(),
			macros: {}
		};
	};

	var tmpMacro = (thats._gendata && _pre.srctype == 'macro')? thats._gendata : false;

	var setFunctionFromMacro = function(args){
		//
		Ext.getCmp('formatControlDialog').show();
		formulaField.setValue(args);
	};

	var getMacro = function(data){
		tmpMacro = data;
		var macroName = data.macros.Widget.slice(data.macros.Widget.indexOf('.')+1);
		var ff = [
		          'MACRO',
		          macroName,
		          macroName.concat('(argument1, argument2,...)'),
		          'Adds any parameter to custom function',
		          [
		           {
		        	   t: 'sequence',
		        	   c: 30,
		        	   m: [
		        	       {
		        	    	   t: 'any',
		        	    	   n: 'Parameter',
		        	    	   d: 'parameter1, parameter2, ... are 1 to 30 parameters to be passed to macro function. Any type allowed.'
		        	       }
		        	       ]
		           }
		           ]
		          ];
		macroArgsBtn.enable();
		thats._gendata = retPanel._gendata = data;
		Jedox.gen.load(Jedox.wss.app.dynJSRegistry.funcArgs, [ ff, {fn: setFunctionFromMacro, id: 'widget'} ]);
	}

	var macroAssignBtn = new Ext.Button({
		iconCls: 'icon_macro',
		text: 'Assign Macro'.localize(),
		tabIndex: tabOffset + 6,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		cls: 'x-btn-icon-text',
		handler: function(){
			Ext.getCmp('formatControlDialog').hide();
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.insertMacro, [_getMacroData(), 'widget', getMacro]);
		}
	});




	var macroArgsBtn = new Ext.Button({
		iconCls: 'icon_macro_editor',
		text: 'Macro Arguments'.localize(),
		cls: 'x-btn-icon-text',
		tabIndex: tabOffset + 7,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		disabled: !tmpMacro,
		handler: function(){
			var macroName = (tmpMacro.macros)? tmpMacro.macros.Widget.slice(tmpMacro.macros.Widget.indexOf('.')+1) : _pre.src.slice(1, _pre.src.indexOf('('));
			var ff = [
			          'MACRO',
			          macroName,
			          macroName.concat('(argument1, argument2,...)'),
			          'Adds any parameter to custom function',
			          [
			           {
			        	   t: 'sequence',
			        	   c: 30,
			        	   m: [
			        	       {
			        	    	   t: 'any',
			        	    	   n: 'Parameter',
			        	    	   d: 'parameter1, parameter2, ... are 1 to 30 parameters to be passed to macro function. Any type allowed.'
			        	       }
			        	       ]
			           }
			           ]
			          ];
			Ext.getCmp('formatControlDialog').hide();
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.funcArgs, [ ff, {fn: setFunctionFromMacro, id: 'widget'}, formulaField.getValue() ]);
		}
	});

	var cardMacro = new Ext.Panel({
		layout: 'column',
		autoHeight: true,
		bodyStyle: 'padding-left: 10px;',
		baseCls: 'x-plain',
		autoWidth: true,
		items: [
				new Ext.Panel({
					baseCls: 'x-plain',
					width: 105,
					items: [macroAssignBtn]
				}),
				new Ext.Panel({
					baseCls: 'x-plain',
					width: 120,
					items: [macroArgsBtn]
				})
		        ],
        listeners: {
			enable: function(p){
				macroAssignBtn.enable();
				macroArgsBtn.enable();
			},
			disable: function(p){
				macroAssignBtn.disable();
				macroArgsBtn.disable();
			}
		}
	});

	// ===== m

	// ====== subset

	var setFuncText = function(cnf)
	{
		formulaField.setValue(cnf.ss_func);
		retPanel._gendata = thats._gendata = cnf._gendata;
	};

	var subsetBtn = new Ext.Button({
		iconCls: 'icon_palo_pastesubset',
		text: 'Subset Editor'.localize(),
		cls: 'x-btn-icon-text',
		tabIndex: tabOffset + 8,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		handler: function(){
			Jedox.gen.load(
				Jedox.wss.app.dynJSRegistry.subsetEditor,
				[
				 	{
				 		mode: 3,
				 		fnc: setFuncText,
				 		dynarange: {_gendata: thats._gendata}
				 	}
				]
			);
		}
	});

	var subsetBtnS = new Ext.Button({
		id: 'wSource_SSE_btn',
		iconCls: 'icon_palo_pastesubset',
		text: 'Subset Editor'.localize(),
		tabIndex: tabOffset + 9,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		cls: 'x-btn-icon-text',
		handler: function(){
			Jedox.gen.load(
				Jedox.wss.app.dynJSRegistry.subsetEditor,
				[
				 	{
				 		mode: 3,
				 		fnc: setFuncText,
				 		dynarange: {_gendata: thats._gendata}
				 	}
				]
			);
		}
	});

	var cardSubset = new Ext.Panel({
		layout: 'form',
		autoHeight: true,
		bodyStyle: 'padding-left: 10px;',
		baseCls: 'x-plain',
		autoWidth: true,
		items: [subsetBtn],
		listeners: {
			enable: function(p){
				subsetBtn.enable();
			},
			disable: function(p){
				subsetBtn.disable();
			}
		}
	});

	// =============

	var sourceCardHolder = new Ext.Panel({
		layout: 'card',
		baseCls: 'x-plain',
		autoWidth: true,
		activeItem: srcPreType,
		deferredRender: true,
		items:[
		       {baseCls: 'x-plain', autoWidth: true},//none
		       cardRange,
		       cardFunction,
		       cardMacro,
		       cardSubset
		       ],
		listeners: {
			afterLayout: function(p, l){
				thats.containers.srcCard = p.layout.activeItem;
			}
		}
	});


	var wizPan = new Ext.Panel({
		layout: 'column',
		baseCls: 'x-plain',
		border: false,
		items: [
		        (thats.containers.srcR = new Ext.Panel({
		        	baseCls: 'x-plain',
		        	width: 18,
		        	items: [sourceWiz]
		        })),
		        (thats.containers.srcCmb = new Ext.Panel({
		        	baseCls: 'x-plain',
		        	width: 150,
		        	items: [(_pre.type == Jedox.wss.wsel.type.WIDGET)? srcCombo: {html: 'Subset'.localize(), baseCls: 'x-plain', style: 'padding-top: 4px;'}]
		        })),
		        (thats.containers.srcCard = new Ext.Panel({
		        	baseCls: 'x-plain',
		        	layout: 'form',
		        	xtype: 'fieldset',
		        	width: 250,
		        	items: [(_pre.type == Jedox.wss.wsel.type.WIDGET)? sourceCardHolder: subsetBtnS]
		        }))
		        ]
	});


	//////////////////////////

	var formulaField = new Ext.form.Field({
		hideLabel: true,
		disabled: !thats.typeDisabled,
		allowBlank: true,
		tabIndex: tabOffset + 11,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		value: thats.functionValue,
		width: 420
	});

	var ffHolder = new Ext.Panel({
		baseCls: 'x-plain',
		bodyStyle: 'padding-left: 18px;',
		items: [formulaField]
	});


	//============================================================================================


	var fsSource = Ext.extend(Ext.form.FieldSet,{

		getFuncText: function()
		{
			return formulaField.getValue();
		},

		getTypeDisabled: function()
		{
			return thats.typeDisabled;
		},

		getSrcType: function(){

			return srcType;
		},

		getGenData: function()
		{
			if (thats.typeDisabled)
				return [];

			return this._gendata;
		},
		_gendata: (_pre._gendata)? _pre._gendata : [],

		initComponent: function(){
			Ext.apply(this, {});
			fsSource.superclass.initComponent.call(this);
		}
	});

	var ffPan = thats.containers.formulaFld = new Ext.Panel({
		baseCls: 'x-plain',
		layout: 'form',
		items: [sourceFormula, ffHolder]
	});

	var retPanel = new fsSource({
		title: "Source".localize(),
		collapsible: false,
		id: 'src_pan',
    	autoWidth: true,
    	autoHeight: true,
		items: [wizPan, ffPan],
		listeners: {
			afterLayout: function(p, l){
				// if (_pre.type == Jedox.wss.wsel.type.WIDGET){
					// preselection for widgets
				//}
			}
		}
	});

	// widgets preselection

	switch (_pre.srctype){
	case 'range':
		rangeFld.setValue(_pre.src);
		break;
	case 'function':

		break;
	case 'macro':

		break;
	case 'subset':
		//retPanel._gendata = _pre._gendata;
		break;
	}

	//

	callback(retPanel);

};