/*
 * @brief wss file
 *
 * Copyright (C) 2006-2010 Jedox AG
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
 * SVN: $Id: FuncArgs.js 4781 2011-03-29 08:16:54Z predragm $
 *
 */

Jedox.wss.dlg.funcArgs = function(fn, from, preselection) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.FunctionArguments(fn, from, preselection));
};

Jedox.wss.dlg.FunctionArguments = (function() {

	return function (fn, from, preselection) {

		Jedox.wss.dlg.FunctionArguments.parent.constructor.call(this);
		this.id = 'wFuncArgs_dlg_wnd';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		/* ================ PRESELECTION WORK ================== */

		if (preselection){

			var activeFnc = preselection;

			var _pre = {
					fn: activeFnc.slice(1, activeFnc.indexOf('(')),
					args: activeFnc.slice(activeFnc.indexOf('(')+1, activeFnc.lastIndexOf(')')).split(',')
			}

			var xhr = new XMLHttpRequest();
			xhr.open('GET', '/be/fn_desc/'.concat(Jedox.wss.i18n.L10n, '.json'), false);
			xhr.send(null);

			var functions = Ext.util.JSON.decode(xhr.responseText);
			functions.cats.unshift( [ 'ALL', 'All'.localize() ]);

			if (!fn) {
				var ffn = functions.lookup_func[_pre.fn];
				var ff = functions.funcs[ffn];
				fn = ff;
			}
		}

		/* ======================================================== */

		var _fnCat = fn[0];
		var _fnName = fn[1];
		var _fnCall = fn[2];
		var _fnDesc = fn[3];
		var _fnParams = fn[4];

		var tabIndexInc = 1;

		if (!_fnDesc) _fnDesc = '_error: fnc_desc'.localize();

		var _activeParam;
		var _maxSequences;
		var _args = _fnParams.length;

		// Getting named ranges - for recogniting

		var position = Jedox.wss.app.environment.defaultSelection.getActiveRange().getActiveCell();
		var rawNR = Jedox.backend.ccmd(0, ["nlst", [position._x, position._y]]);
		var namedRangesList = [];
			for (var z=0; z<rawNR[0][1][0].length; z++){
				namedRangesList.push(rawNR[0][1][0][z].name);
			}

		function isInArray(value, array){
			var isIn = false;
			for (var c=0; c<array.length; c++){
				if (value == array[c]) isIn = true;
			}
			return isIn;
		};

		// EXTENDING COMPONENTS

		var selRangeBtn = Ext.extend(Ext.Button, {
			iconCls: 'select-range-icon',
			cls: 'x-btn-icon',
			tooltip: "Select Range".localize(),
			initComponent: function()
			{
			var that = this;
			// config
			Ext.apply(this, {});
			selRangeBtn.superclass.initComponent.call(this);
			}
		});

		var valField = Ext.extend(Ext.form.TextField, {
			width: 175,
			hideLabel: true,
			enableKeyEvents: true,
			initComponent: function()
			{
			var that = this;
			// config
			Ext.apply(this, {});
			selRangeBtn.superclass.initComponent.call(this);
			}
		});

		// finished extending

		function selRange(selected){
			that.win.show();
			setTimeout(function() {
				var f = Ext.getCmp('valFld_seq_'.concat(_activeParam));
				f.setValue(selected);
				_activeParam = '';
			}, 1);
		};

		function selRangeB(selected){
			that.win.show();
			setTimeout(function() {
				var f = Ext.getCmp('valFld_'.concat(_activeParam));
				 f.setValue(selected);
				_activeParam = '';
			}, 1);
		};

		var argsHolder = this.containers.mainPanel = new Ext.Panel({
			layout: 'form',
			id: 'argsHolder',
			baseCls: 'x-plain',
			width: 450,
			items: []
		});

		var argDescData = {};
		var sargDescData = {};
		var argTypeData = {};

		// Here be process of adding fields
		// SAMPLE:  var myNewGrid = new Ext.grid.GridPanel({ store: myStore, colModel: myColModel }); myTabPanel.add(myNewGrid); myTabPanel.setActiveTab(myNewGrid);
		argsHolder.removeAll(false);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		function addNewSeq(seq, hp){
			// adding new seqence
			allSeqs++;
			var _seqArgs = seq.m.length;
			for (var j=0; j<_seqArgs; j++){
				// adding sequence arguments
				lastSeqIndex=lastSeqIndex+1;

				sargDescData[j+lastSeqIndex] = seq.m[j].d;

				var sargPanel = new Ext.Panel({
					id: 'argPan_seq_'.concat(lastSeqIndex),
					layout: 'column',
					baseCls: 'x-plain',
					bodyStyle: 'margin-top: 5px;',
					border: false,
					frame: false,
					items:[
							{
								columnWidth: 0.3,
								autoHeight: true,
								baseCls: 'x-plain',
								border: false,
								style: 'text-align: right; margin-right: 10px;',
								frame: false,
								items: [{html: seq.m[j].n.concat(allSeqs), baseCls: 'x-plain'}]
							},
							{
								columnWidth: 0.43,
								xtype: 'fieldset',
								autoHeight: true,
								baseCls: 'x-plain',
								border: false,
								frame: false,
								items: [new valField({
									id: 'valFld_seq_'.concat(lastSeqIndex),
									tabIndex: tabIndexInc,
									listeners: {
										focus: function(){
											// focus listener

											var nr = this.id;
											nr = nr.split('_');
											nr = nr[2];
											that.win.remove('actAttribDesc');
											var dsp = {
													html: sargDescData[nr],
													baseCls: 'x-plain',
													height: 70,
													autoScroll: 'auto',
													id: 'actAttribDesc',
													bodyStyle: 'margin-left: 0px; margin-top: 5px; font-size: 11px;'
												};
											that.win.add(dsp);
											that.win.doLayout();
											// add new if necessary
											if (nr==lastSeqIndex && allSeqs<_maxSequences){
												// add new
												addNewSeq(rawSeq, lastSeqIndex);
											}
											//////////
										},
										keypress: function(el, e){
											var nr = this.id;
											nr = nr.split('_');
											nr = nr[2];
											var kp = e.getKey();
											if (kp==9) {
												nr = parseInt(nr);
												if (Ext.getCmp('valFld_seq_'.concat(nr+1)))
													{
//													Ext.getCmp('valFld_seq_'.concat(nr+1)).fireEvent('focus');
//													Ext.getCmp('valFld_seq_'.concat(nr+1)).focus(true, 1);
													}
											}
										},
										keyup: function(){
											////// keyup
											var nr = this.id;
											nr = nr.split('_');
											nr = nr[2];

											Ext.getCmp('valArg_val_'.concat(nr)).removeAll();
											var dsp = {html: '= '.concat(this.getValue()), baseCls: 'x-plain'};
											Ext.getCmp('valArg_val_'.concat(nr)).add(dsp);
											Ext.getCmp('valArg_val_'.concat(nr)).doLayout();
										}
									}
									})]
							},
							{
								columnWidth: 0.07,
								xtype: 'fieldset',
								autoHeight: true,
								baseCls: 'x-plain',
								border: false,
								frame: false,
								items: [
								        new selRangeBtn({
								        	id: 'valBtn_seq_'.concat(lastSeqIndex),
								        	tabIndex: tabIndexInc + 1,
								        	handler: function() {
											var nr = this.id;
											nr = nr.split('_');
											nr = nr[2];
											Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
						    					fnc: [this, selRange]
						  	    					,format: '{Sheet}!{Range}'
						  	    					,rng: Ext.getCmp('valFld_seq_'.concat(nr)).getValue()
						  	    					,omitInitSheet: true
						  	    				}]);
											_activeParam=nr;
											that.win.hide();
									}})]
							},
							{
								columnWidth: 0.2,
								autoHeight: true,
								baseCls: 'x-plain',
								border: false,
								id: 'valArg_val_'.concat(lastSeqIndex),
								style: 'text-align: left; margin-left: 10px; white-space:nowrap;',
								frame: false,
								items: [{html: '= '.concat(('fnArg_'.concat(seq.m[j].t)).localize()), baseCls: 'x-plain'}]
							}
					       ]
				});
				argsHolder.add(sargPanel);
				argsHolder.doLayout();
				tabIndexInc = tabIndexInc + 2;
				//this.containers.mainPanel = argsHolder;
				// finished adding sequence args
				}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////////////////////

		}

		var allSeqs = 0;
		var lastSeqIndex = 0;
		function parseSequence(seq){

			_maxSequences = seq.c;
			var _seqArgs = seq.m.length;
			allSeqs++;
			for (var j=0; j<_seqArgs; j++){
				// adding sequence arguments
				lastSeqIndex=j;
				sargDescData[j] = seq.m[j].d;

				var sargPanel = new Ext.Panel({
					id: 'argPan_seq_'.concat(j),
					layout: 'column',
					baseCls: 'x-plain',
					bodyStyle: 'margin-top: 5px;',
					border: false,
					frame: false,
					items:[
							{
								columnWidth: 0.3,
								autoHeight: true,
								baseCls: 'x-plain',
								border: false,
								style: 'text-align: right; margin-right: 10px;',
								frame: false,
								items: [{html: seq.m[j].n.concat(allSeqs), baseCls: 'x-plain'}]
							},
							{
								columnWidth: 0.43,
								xtype: 'fieldset',
								autoHeight: true,
								baseCls: 'x-plain',
								border: false,
								frame: false,
								items: [new valField({
									id: 'valFld_seq_'.concat(j),
									tabIndex: tabIndexInc,
									listeners: {
										focus: function(){
											// focus listener

											var nr = this.id;
											nr = nr.split('_');
											nr = nr[2];
											that.win.remove('actAttribDesc');
											var dsp = {
													html: sargDescData[nr],
													baseCls: 'x-plain',
													height: 70,
													autoScroll: 'auto',
													id: 'actAttribDesc',
													bodyStyle: 'margin-left: 0px; margin-top: 5px; font-size: 11px;'
												}
											that.win.add(dsp);
											that.win.doLayout();
											// add new if necessary
											if (nr==lastSeqIndex && allSeqs<_maxSequences){
												// add new
												//argsHolder.add(sargPanel);
												//argsHolder.doLayout();
												addNewSeq(rawSeq, lastSeqIndex);

											}
											//////////
										},
										keypress: function(el, e){
											var nr = this.id;
											nr = nr.split('_');
											nr = nr[2];
											var kp = e.getKey();
											if (kp==9) {
												nr = parseInt(nr);
												if (Ext.getCmp('valFld_seq_'.concat(nr+1)))
													{
//													Ext.getCmp('valFld_seq_'.concat(nr+1)).fireEvent('focus');
//													Ext.getCmp('valFld_seq_'.concat(nr+1)).focus(true, 1);
													}
											}
										},
										keyup: function(){
											////// keyup
											var nr = this.id;
											nr = nr.split('_');
											nr = nr[2];
											Ext.getCmp('valArg_val_'.concat(nr)).removeAll();
											var dsp = {html: '= '.concat(this.getValue()), baseCls: 'x-plain'};
											Ext.getCmp('valArg_val_'.concat(nr)).add(dsp);
											Ext.getCmp('valArg_val_'.concat(nr)).doLayout();
										}
									}
									})]
							},
							{
								columnWidth: 0.07,
								xtype: 'fieldset',
								autoHeight: true,
								baseCls: 'x-plain',
								border: false,
								frame: false,
								items: [new selRangeBtn({id: 'valBtn_seq_'.concat(j)
									,tabIndex: tabIndexInc + 1
									,handler: function() {
										var nr = this.id;
										nr = nr.split('_');
										nr = nr[2];
										Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
					    					fnc: [this, selRange]
						  	    					,format: '{Sheet}!{Range}'
						  	    					,rng: Ext.getCmp('valFld_seq_'.concat(nr)).getValue()
						  	    					,omitInitSheet: true
						  	    				}]);
										_activeParam=nr;
										that.win.hide();
									}
								}
								)]

							},
							{
								columnWidth: 0.2,
								autoHeight: true,
								baseCls: 'x-plain',
								id: 'valArg_val_'.concat(j),
								border: false,
								style: 'text-align: left; margin-left: 10px; white-space:nowrap;',
								frame: false,
								items: [{html: '= '.concat(('fnArg_'.concat(seq.m[j].t)).localize()), baseCls: 'x-plain'}]
							}
					       ]
				});
				argsHolder.add(sargPanel);
				tabIndexInc = tabIndexInc + 2;
				//this.containers.mainPanel = argsHolder;
				// finished adding sequence args
				}
		};

		for (var i=0; i<_args; i++){
			var rawSeq;
			if (_fnParams[i].t == 'sequence') {rawSeq=_fnParams[i]; parseSequence(_fnParams[i]); break;};
			argDescData[i] = _fnParams[i].d;
			argTypeData[i] = _fnParams[i].t;
			var argPanel = new Ext.Panel({
				id: 'argPan_'.concat(i),
				layout: 'column',
				baseCls: 'x-plain',
				bodyStyle: 'margin-top: 5px;',
				border: false,
				frame: false,
				items:[
						{
							columnWidth: 0.3,
							autoHeight: true,
							baseCls: 'x-plain',
							border: false,
							style: 'text-align: right; margin-right: 10px;',
							frame: false,
							items: [{html: _fnParams[i].n, baseCls: 'x-plain'}]
						},
						{
							columnWidth: 0.43,
							xtype: 'fieldset',
							autoHeight: true,
							baseCls: 'x-plain',
							border: false,
							frame: false,
							items: [new valField({
								id: 'valFld_'.concat(i),
								tabIndex: tabIndexInc,
								listeners: {
									focus: function(){
										var nr = this.id;
										nr = nr.split('_');
										nr = nr[1];
										that.win.remove('actAttribDesc');
										var dsp = {
												html: argDescData[nr],
												baseCls: 'x-plain',
												id: 'actAttribDesc',
												height: 70,
												autoScroll: 'auto',
												bodyStyle: 'margin-left: 0px; margin-top: 5px; font-size: 11px;'
											}
										that.win.add(dsp);
										that.win.doLayout();
									},
									keypress: function(el, e){
										var nr = this.id;
										nr = nr.split('_');
										nr = nr[1];
										var kp = e.getKey();
										nr = parseInt(nr);
										if (kp==9) {
											if (Ext.getCmp('valFld_'.concat(nr+1)))
												{
//												Ext.getCmp('valFld_'.concat(nr+1)).fireEvent('focus');
//												Ext.getCmp('valFld_'.concat(nr+1)).focus(true, 1);
												}
											else if (Ext.getCmp('valFld_seq_0'))
												{
//												Ext.getCmp('valFld_seq_0').fireEvent('focus');
//												Ext.getCmp('valFld_seq_0').focus(true, 1);
												}
										}
									},
									keyup: function(){
										////// keyup
										var nr = this.id;
										nr = nr.split('_');
										nr = nr[1];
										Ext.getCmp('val_val_'.concat(nr)).removeAll();
										var dsp = {html: '= '.concat(this.getValue()), baseCls: 'x-plain'};
										Ext.getCmp('val_val_'.concat(nr)).add(dsp);
										Ext.getCmp('val_val_'.concat(nr)).doLayout();
									},
									blur: function(){
										// for text flds only!
										var nr = this.id;
										nr = nr.split('_');
										nr = nr[1];
										if (argTypeData[nr] == 'text'){
											var vale = setQuotes(this.getValue());
											Ext.getCmp('val_val_'.concat(nr)).removeAll();
											var dsp = {html: '= '.concat(vale), baseCls: 'x-plain'};
											Ext.getCmp('val_val_'.concat(nr)).add(dsp);
											Ext.getCmp('val_val_'.concat(nr)).doLayout();
										}
									}
								}
								})]
						},
						{
							columnWidth: 0.07,
							xtype: 'fieldset',
							autoHeight: true,
							baseCls: 'x-plain',
							border: false,
							frame: false,
							items: [new selRangeBtn({id: 'valBtn_'.concat(i),
								tabIndex: tabIndexInc + 1,
								handler: function() {
								var nr = this.id;
								nr = nr.split('_');
								nr = nr[1];
								Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
			    					fnc: [this, selRangeB]
				  	    					,format: '{Sheet}!{Range}'
				  	    						,rng: Ext.getCmp('valFld_'.concat(nr)).getValue()
				  	    					,omitInitSheet: true
				  	    				}]);
								_activeParam=nr;
								that.win.hide();
								}})]
						},
						{
							columnWidth: 0.2,
							autoHeight: true,
							baseCls: 'x-plain',
							border: false,
							id: 'val_val_'.concat(i),
							style: 'text-align: left; margin-left: 10px; white-space:nowrap;',
							frame: false,
							items: [{html: '= '.concat(('fnArg_'.concat(_fnParams[i].t)).localize()), baseCls: 'x-plain'}]
						}
				       ]
			});
			argsHolder.add(argPanel);
			tabIndexInc = tabIndexInc + 2;
			//this.containers.mainPanel = argsHolder;
		}

		// end of adding

		if (_args < 1) argsHolder.add({html: 'fnc_no_params'.localize(), baseCls: 'x-plain'});
		argsHolder.doLayout();

		// checks if argument is a valid cell reference or a named range; if not, quotes will be added
		function setQuotes (value)
		{
			var refs = Jedox.wss.formula.parse(value);

			return refs.sgn.replace(/@\d+/g, '') == value.replace(/\$/g, '') || isInArray(value, namedRangesList) ? value : '"'.concat(value, '"');
		}

		function setFunction(){
			// final setting of fnc
			var tmpArr=[];
			for (var w=0; w<_args; w++){
				if (Ext.getCmp('valFld_'.concat(w))) {
					if (argTypeData[w] == 'text')
						var val = setQuotes(Ext.getCmp('valFld_'.concat(w)).getValue());
					else
						var val = Ext.getCmp('valFld_'.concat(w)).getValue();
					tmpArr.push(val);
				}
			}
			for (var z=0; z<allSeqs; z++){
				if (argTypeData[z] == 'text')
					var val = setQuotes(Ext.getCmp('valFld_seq_'.concat(z)).getValue());
				else
					var val = Ext.getCmp('valFld_seq_'.concat(z)).getValue();
				tmpArr.push(val);
			}
			var num = tmpArr.length;
			for (var r=num; r>-1; r--){
				if ((tmpArr[r]==undefined) || (tmpArr[r]=="") || (!tmpArr[r])) {
					tmpArr.splice(r,1);
				} else r=-1;
			}

			var func = ''.concat(_fnName,'(');
			var fDelimiter = Jedox.wss.i18n.separators[2];
			for (var t=0; t<tmpArr.length; t++){
				if (t==0) func = func.concat(tmpArr[t]);
				else func = func.concat(fDelimiter,tmpArr[t]);
			}
			func=func.concat(')');

			if (from.fn){
				from.fn('='.concat(func));
			}
			else {

				var env = Jedox.wss.app.environment,
				GridMode = Jedox.wss.grid.GridMode,
				inputField = env.inputField;


				Jedox.wss.general.setInputMode(GridMode.EDIT);
				Jedox.wss.app.lastInputMode = GridMode.READY;
				Jedox.wss.general.showInputField(null, false, true);

				inputField.value = (inputField.value.length == 0 || inputField.value.charAt(0) != '='  || from.id == 'fbar' ? '=' : inputField.value).concat(func);
				Jedox.wss.app.currFormula.setValue(inputField.value);

				Jedox.wss.keyboard.setFieldSize();
				Jedox.wss.general.focusInputField();
			}

			that.win.close();
		}

		this.win = new Ext.Window(
				{
					title : (from.id == 'widget')? 'Macro Arguments'.localize() : 'Function Arguments'.localize(),
					closable : true,
					id : 'wFuncArgs_dlg_wnd',
					autoDestroy : true,
					plain : true,
					constrain : true,
					cls: 'default-format-window',
					modal : true,
					resizable : false,
					enableHdMenu : false,
					animCollapse : false,
					width : 530,
					height : 400,
					layout : 'form',
					onEsc: Ext.emptyFn,
					bodyStyle : 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
					listeners : {
						close: function()
						{
							if (Jedox.wss.app.environment.inputMode != Jedox.wss.grid.GridMode.EDIT && (!from || from.id == 'fbar')){
								Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
								Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							}
							that.close();
							if (!from || from.id == 'fbar') Jedox.wss.app.activeSheet._defaultSelection.getCursorField().refresh();;
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.funcArgs);
						},
						show:function(){
							setTimeout(function(){
								//that.initFocus(true, 100);
							});
						},
						activate: function(win) {that.activate();}
					},
					items : [
					         new Ext.Panel({
					        	border: false,
					 			frame: false,
					 			autoHeight: true,
					 			id: 'sample',
					 			header: false,
					 			height: 200,
					 			baseCls: 'x-title-f',
					 			items: [
					 			        {
											autoWidth: true,
											xtype: 'fieldset',
											bodyStyle: 'padding-top: 0px; background-color: transparent;',
											layout: 'form',
											border: true,
											height: 200,
											autoScroll: true,
											title: _fnName,
											// TODO: dynamic function title
											items: [argsHolder]
										}
					 			        ]
					         }),
								{
									html: _fnDesc,
									baseCls: 'x-plain'
								},
								{
										html: '',
										height: 70,
										autoScroll: 'auto',
										baseCls: 'x-plain',
										id: 'actAttribDesc',
										bodyStyle: 'margin-left: 0px; margin-top: 5px; font-size: 11px;'
									}
					         ],
					buttons : [
								(this.components.OK = new Ext.Button({
									text: 'OK'.localize(),
									id: 'wFuncArgs_ok_btn',
									tabIndex: 102,
									handler: function(){
										setFunction();
										that.win.close();
									}
								})),
								(this.components.Cancel = new Ext.Button({
									text: 'Cancel'.localize(),
									id: 'wFuncArgs_cancel_btn',
									tabIndex: 103,
									ctCls: Jedox.kbd.Base.tags.NO_ENTER,
									handler: function(){
										if (from.id == 'control' || from.id == 'widget') Ext.getCmp('formatControlDialog').show();
										that.win.close();
									}
								}))
					           ]
				});

		this.setContext();
		this.win.show(this);

		/* ================= FINISH PRESELECTION ================= */
		if (preselection){
			// that.win.getEl().mask('Please wait'.localize());

			var valIndex = 0;
			var seqIndex = 0;

			if (_args>0) {
				for (var fi=0; fi<_pre.args.length; fi++){

					var tempFld = Ext.getCmp('valFld_'.concat(fi));
					if (tempFld){
						tempFld.focus();
						tempFld.setValue(_pre.args[fi]);
						valIndex++;
					} else {
						for (var si=seqIndex; si<_pre.args.length; si++){
							var tempSFld = Ext.getCmp('valFld_seq_'.concat(si));
							if (tempSFld){
								tempSFld.focus();
								tempSFld.setValue(_pre.args[valIndex+si]);
								seqIndex++;
							}
						}
					}
				}
			}
			// that.win.getEl().unmask();
		}
		/* ======================================================= */
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.FunctionArguments, Jedox.dlg.Dialog);