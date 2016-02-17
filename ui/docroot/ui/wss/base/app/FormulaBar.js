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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com
 *
 * \version
 * SVN: $Id: FormulaBar.js 4674 2011-03-07 09:58:50Z djordjez $
 *
 */

Jedox.wss.app.initFormulaBar = function () {


	var that = this;

	var _expanded = false;
	var _minHeight = 22;
	var _maxHeight = 50;

	var _isWebKit = Ext.isWebKit;
	var _defaultCSS = 'overflow-y:auto; overflow-x:hidden';
	var _webkitCSSexp = 'padding:2px 0px 2px 0px!important; height:44px !important;overflow-y:auto; overflow-x:hidden;'
	var _webkitCSSclps = 'padding:2px 0px 2px 0 !important; height:16px !important;overflow-y:auto; overflow-x:hidden;'

	var _formulaBar = Ext.get('formulaBar'); //Formula Bar Container div





	//Curent Coordinate

	Jedox.wss.app.currCoord = new Ext.form.TextField({
		id: 'wFrmlBar_currCoord_fld',
		hideLabel:true,
		style:'text-align:center;',
		enableKeyEvents:true,
		width: 170,
		tmpValue:false,
		listeners: {
			keydown:function(txf, e){
				switch(e.getKey()){
					case 9: //TAB
						e.stopEvent();
						break;
					case 13: //ENTER
						e.stopEvent();
						var value = txf.getValue();
						if(value){
							if(!(Jedox.wss.book.goTo(value))){
								insertName(value);
								this.setValue(value);
							}
						}
						else
							this.setValue(this.tmpValue);//if case of ""
						this.getEl().blur();
						break;
					case 27: //ESC
						e.stopEvent();
						this.setValue(this.tmpValue);
						this.getEl().blur();
						break;
				}
			},
			focus:function(txf){
				this.tmpValue = this.getValue();
				this.getEl().applyStyles('text-align:left;');

				Jedox.wss.app.lastInputMode = Jedox.wss.app.environment.inputMode;
				Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.CNTRL);

				setTimeout(function(){txf.selectText();});
			},
			blur:function(){
				this.getEl().applyStyles('text-align:center;');

				Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputMode);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
			}
		}
	});

	Jedox.wss.app.currCoord.render("currCoord");




	//Toolbar

	var formulaTlbContainer = new Ext.Panel({
		layout:'absolute',
		width: 75,
		height: 24,
		border: false,
		baseCls: 'x-plain',
		innerTlb:false,
		items:[{
			border: false,
			x:0,
			y:-3,
			tbar: [
				Jedox.wss.app.formulaTlb = new Ext.Toolbar({
					items:[{
						tooltip: {
							text: 'Cancel'.localize()
						},
						iconCls: 'cancel_formula_icon',
						id: 'wFrmlBar_cancel_btn',
						disabled:true,
						handler:onCancel,
						scope: this
					}, {
						tooltip: {
							text: 'Enter'.localize()
						},
						iconCls: 'enter_formula_icon',
						id: 'wFrmlBar_enter_btn',
						disabled:true,
						handler:onEnter,
						scope: this
					}, {
						tooltip: {
							text: 'Insert Function'.localize()
						},
						iconCls: 'insert_formula_icon',
						id: 'wFrmlBar_insert_btn',
						handler:onInsertFunction,
						scope: this
					}],
					setMode:function(mode){ // public for enable/disable Cancel/Enter btns
						if(mode){
							this.items.items[0].enable();
							this.items.items[1].enable();
						}
						else {
							this.items.items[0].disable();
							this.items.items[1].disable();
						}
					}

				})
			]
		}]
	});

	formulaTlbContainer.render("formulaTlb");






	//Current Formula  txa

	Jedox.wss.app.currFormula = new Ext.form.TextArea({
		id:'wFrmlBar_currFormula_tx',
		hideLabel:true,
		enableKeyEvents:true,
		width: '100%',
		height:22,
		style:_isWebKit? _webkitCSSclps:_defaultCSS,
		listeners:{
	        render: function() {
				this.getEl().on('mousedown', function(){
					Jedox.wss.keyboard.skipInpFldBlur = true;
					Jedox.wss.general.mouseDownOnFormFld();
				});
	        },
			focus:function(){
				this.tmpValue = this.getValue();
				Jedox.wss.general.focusOnFormFld();
			},
			keyup:function(txa, e){
				Jedox.wss.keyboard.setFieldContent(e);
			},
			blur:function(){
				Jedox.wss.app.fromFormulaField = false;
			}
		}
	});

	Jedox.wss.app.currFormula.render("formulaInfo");






	//Expand/Collapse txa btn

   Jedox.wss.app.expandBtn = new Ext.Panel({
		layout:'card',
		activeItem:0,
		border:false,
		baseCls:'x-plain',
		defaults:{
			baseCls:'x-plain',
			border:false,
			width:16
		},
		items:[{
			layout:'absolute',
			height:23,
			items:[
				new Ext.ux.ImageButton({
					id: 'wFrmlBar_expand_btn',
					autoEl: {tag: 'img', src: '/ui/lib/ext/resources/images/default/s.gif'},
				    width: 16,
				    height: 22,
					x:0,
					y:1,
					cls: 'formula-info-exp-icon',
					imgNormal: '/ui/lib/ext/resources/images/default/s.gif',
				    imgOver: '/ui/lib/ext/resources/images/default/s.gif',
				    imgClicked: '/ui/lib/ext/resources/images/default/s.gif',
				    actionFn: function(){
						expand();
					}
				})
			]
		},{
			layout:'absolute',
			height:52,
			items:[
				new Ext.ux.ImageButton({
					autoEl: {tag: 'img', src: '/ui/lib/ext/resources/images/default/s.gif'},
				    width: 16,
				    height: 50,
					x:0,
					y:1,
					cls: 'formula-info-clps-icon',
					imgNormal: '/ui/lib/ext/resources/images/default/s.gif',
				    imgOver: '/ui/lib/ext/resources/images/default/s.gif',
				    imgClicked: '/ui/lib/ext/resources/images/default/s.gif',
				    actionFn: function(){
						expand();
					}
				})
			]
		}]
	});

	Jedox.wss.app.expandBtn.render("expandBtn");





	//Btn handler fuctions

	function onCancel(btn, e){
		Jedox.wss.action.cancelGridInput();
	}

	function onEnter(btn, e){
		Jedox.wss.action.sendGridInput(e);
	}

	function onInsertFunction(){
		Jedox.gen.load(Jedox.wss.app.dynJSRegistry.insertFunction, [{id:'fbar', fn:null}, Jedox.wss.app.currFormula.getValue()]);
	}

	function expand(w, h){

		if (_expanded){
			_formulaBar.setHeight(25); //FormulaBar container
			Jedox.wss.app.currFormula.setHeight(_minHeight); //txa
			if (_isWebKit)
				Jedox.wss.app.currFormula.getEl().applyStyles(_webkitCSSclps);
			Jedox.wss.app.expandBtn.getLayout().setActiveItem(0); //exp/clps btn
		}
		else {
			_formulaBar.setHeight(53); //FormulaBar container
			Jedox.wss.app.currFormula.setHeight(_maxHeight); //txa
			if (_isWebKit)
				Jedox.wss.app.currFormula.getEl().applyStyles(_webkitCSSexp);
			Jedox.wss.app.expandBtn.getLayout().setActiveItem(1); //exp/clps btn
		}

		_expanded = !_expanded;
		Jedox.wss.app.expandCollapseFormulaBar(); //resize grid
	}

	function insertName(name){

		if (validateName(name)) {

			var position = Jedox.wss.app.environment.defaultSelection.getActiveRange().getActiveCell(),
				tmpScope = '', //workbook scope
				refers_to = '='.concat(getSheetName(), '!', Jedox.wss.app.environment.defaultSelection.getActiveRange().getValue(true)),
				cmds = [];

				function onErrClb(){
					showMessage('New name'.localize(), 'inset_name_err_msg'.localize(), 'ERROR');
				}

			cmds.push(["nadd", [position._x, position._y, {name: name, refers_to: refers_to, scope: tmpScope, comment: ''}]]);
			(new Jedox.backend.CCmdDiffAsyncRqst(cmds)).setOnError([this, onErrClb]).send();
		}
		else
			showMessage('New Name'.localize(), 'currCoord_validate_err_msg'.localize(), 'WARNING');


		function validateName(name){
			var result=false;

			var my_regexp_ALLOWED_CHARS = /^[a-zA-Z_\\][a-zA-Z0-9_\-\.]+$/;
			var my_regexp_RESERVED_NAMES = /^([a-zA-Z]{1,2}[0-9]{1,5})+$/;
			var my_regexp_RESERVED_CELL_REF = /^[rR]{1}[0-9]{1,5}([cC]{1}[0-9]{1,5})*$/;

			if (((name.length>1 && name.length<256) && (my_regexp_ALLOWED_CHARS.test(name) && !my_regexp_RESERVED_NAMES.test(name))) && !my_regexp_RESERVED_CELL_REF.test(name)){
				result=true;
			}

			return result;
		}


		function getSheetName(){
			var sheetName = Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName();
			return sheetName.search(/ /) >= 0? sheetName = '\''.concat(sheetName, '\''):sheetName
		}

		function showMessage(title, msg, type){
			Ext.Msg.show({
			   title:title,
			   msg: msg,
			   buttons: Ext.Msg.OK,
			   fn: function() {Jedox.wss.app.currCoord.setValue(Jedox.wss.app.currCoord.tmpValue)},
			   animEl: 'elId',
			   width:320,
			   icon: Ext.MessageBox[type]
			});
		}

	}

}