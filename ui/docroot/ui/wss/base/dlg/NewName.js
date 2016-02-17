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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com
 *
 * \version
 * SVN: $Id: NewName.js 4720 2011-03-18 10:05:03Z andrejv $
 *
 */

Jedox.wss.dlg.openNewName = function(newNameHandleFnc, selectedName, nameManagerStore) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.NewName(newNameHandleFnc, selectedName, nameManagerStore));
};

Jedox.wss.dlg.NewName = (function() {

	return function (newNameHandleFnc, selectedName, nameManagerStore) {

		Jedox.wss.dlg.NewName.parent.constructor.call(this);
		this.id = 'wNewName_dlg_wnd';
		var that = this;


		var _fromDlgF = false;
		var selectedScope='';
		var selectedRange='';
		var _newNameHandleFncFlag = false; //flag for calling function

		 if (Jedox.wss.app.environment.inputMode === Jedox.wss.grid.GridMode.DIALOG)
		 	_fromDlgF=true;
		 else {
		 	Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		 	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		 }

		var newName=[];
		var dlgTitle='';

		var worksheets = Jedox.backend.wss.getSheets()[0];

		var scopeData=[['', 'Workbook'.localize()]];
		for(var i = 0; i < worksheets.length; i += 2)
			scopeData.push([worksheets[i], worksheets[i+1]]);

		var scopeStore = new Ext.data.SimpleStore({
			  fields: ['sheetID', 'sheetName'],
			  data:scopeData
		});

		if (selectedName)
			dlgTitle='Edit Name'.localize();
		else
			dlgTitle='New Name'.localize();




		//================================ Components ============================================

		var nameTxf = this.cmpFocus = new Ext.form.TextField({
			fieldLabel: 'Name'.localize(),
			id: 'wNewName_name_fld',
			tabIndex: 1,
			width: 200
		});

		var scopeCmb=new Ext.form.ComboBox({
			fieldLabel: 'Scope'.localize(),
			id: 'wNewName_scope_cmb',
			width: 135,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 2,
			store:scopeStore,
			displayField:'sheetName',
			editable:false,
			mode: 'local',
		    triggerAction: 'all',
			listeners:{
				select : function(combo, record, index) {
	//				selectedScope=combo.getValue()==='Workbook'? '':combo.getValue();
					selectedScope = index==0? '':combo.getValue();
					//setRefersTo();
				}
			}
		});

		var commentTxa = new Ext.form.TextArea({
			fieldLabel: 'Comment'.localize(),
			id: 'wNewName_comment_tx',
			width: 200,
			tabIndex: 3
		});

		var refersToTxf = new Ext.form.TextField({
			fieldLabel: 'Refers To'.localize(),
			id: 'wNewName_refersto_fld',
//			value: '=' + Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName() + '!' + tmpFormatRange(Jedox.wss.app.environment.defaultSelection.getActiveRange().getValue()),
			value: '='.concat(Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName(true), '!', Jedox.wss.app.environment.defaultSelection.getActiveRange().getValue(true)),
			width: 170,
			tabIndex: 4
		});

		var selectRangeBtn=new Ext.Toolbar.Button({
			id: 'selRangeBegin',
			iconCls: 'select-range-icon',
			cls: 'x-btn-icon',
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 5,
			tooltip: "Select Range".localize(),
			handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [
				{
					fnc: [this, selRangeHandleFnc],
					rng: refersToTxf.getValue()
				}
			]);
			that.win.hide();}
		});

		//================================ Functions ============================================

		function selRangeHandleFnc(selected){
	//		var tmp=selected.split('!');
	//		selectedRange=tmpFormatRange(tmp[1]); // just temp
	//		var s= '=' + tmp[0] + '!' +selectedRange;
			that.win.show();
			refersToTxf.setValue(selected);
		}

		function tmpFormatRange(sr){
			var tmp=sr.split(':');
			var formatedRange='';
			for (var i = 0; i < tmp.length; i++) {
				if (i>0)
					formatedRange+=':';
				for (var j = 0; j < tmp[i].length; j++) {
					if (j == 0 || (parseInt(tmp[i].charAt(j)) && !(parseInt(tmp[i].charAt(j-1)))))
						formatedRange += '$' + tmp[i].charAt(j);
					else
						formatedRange += tmp[i].charAt(j);
				}
			}

			return formatedRange;
		}


		function openSelectRangeDialog (){
			that.win.hide();
			minWin.show();
		}

	/*
		function setRefersTo(){
			var selected=selectedRange===''? Jedox.wss.app.environment.defaultSelection.getActiveRange().getValue():selectedRange;
			var usklicnik='!';
			if (selectedScope==='')
				usklicnik='';
			var s= '='+ selectedScope + usklicnik +selected;
			refersToTxf.setValue(s);
		}
	*/


		function initName(){
			if (selectedName){
				nameTxf.setValue(selectedName.get('name'));
				scopeCmb.setValue(selectedName.get('scope'));
				selectedScope=selectedName.get('scope');
				scopeCmb.disable();
				commentTxa.setValue(selectedName.get('comment'));
				refersToTxf.setValue(selectedName.get('refersTo'));
			}
		}

		function validateName(){
			var name=nameTxf.getValue();
			var refersTo=refersToTxf.getValue();
			var returnValue=false;

			var my_regexp_ALLOWED_CHARS = /^[a-zA-Z_\\][a-zA-Z0-9_\-\.]+$/;
			var my_regexp_RESERVED_NAMES = /^([a-zA-Z]{1,2}[0-9]{1,5})+$/;
			var my_regexp_RESERVED_CELL_REF = /^[rR]{1}[0-9]{1,5}([cC]{1}[0-9]{1,5})*$/;

			if (((name.length>1 && name.length<256 && refersTo.length>0) && (my_regexp_ALLOWED_CHARS.test(name) && !my_regexp_RESERVED_NAMES.test(name))) && !my_regexp_RESERVED_CELL_REF.test(name)){
				returnValue=true;
				nameManagerStore.each( function(record){
					if (record.data.name.toLowerCase() == name.toLowerCase() && record.data.scope == scopeCmb.getValue()){
						returnValue = record!=selectedName? false:true;
					}
				}, [this])
			}

			return returnValue;
		}


		function addNewName(){
			if (validateName()) {
				var newName = [nameTxf.getValue(), '', refersToTxf.getValue(), scopeCmb.getValue(), commentTxa.getValue()];
				newNameHandleFnc(newName);
				_newNameHandleFncFlag = true;
				that.win.close();
			}
			else
				setTimeout(function(){Ext.Msg.show({
				   	title:'Warning'.localize() + '...',
				   	msg: 'newNameDlg_NameWarningMsg'.localize(),
				   	buttons: Ext.Msg.OK,
				   	icon: Ext.MessageBox.WARNING
				});},0);
		}


		//================================ Main Panel ============================================

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
			modal:true,
			layout: 'form',
			baseCls:'x-plain',
			border:false,
			items:[
				nameTxf,
				scopeCmb,
				commentTxa,
				{
				//title: 'top-table-panel',
				layout:'column',
				border:false,
				baseCls:'main-panel',
				items:[
					{
						//title:'panel za Look in',
						layout:'form',
						border:false,
						width: 280,
						baseCls:'x-plain',
						items:refersToTxf
					},
					{
						layout:'form',
						border:false,
						width: 30,
						baseCls:'x-plain',
						items:selectRangeBtn
					}
				]
			 	}
		]
		});

		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px'},
					title:dlgTitle,
					closable: true,
					closeAction: 'close',
			        autoDestroy: true,
			        plain: true,
			        id: 'wNewName_dlg_wnd',
			        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
			        cls: 'default-format-window',
					layout: 'fit',
					width: 350,
					height: 240,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function()
						{
							if (!_newNameHandleFncFlag)
								newNameHandleFnc();


							 if (!_fromDlgF) {
								 Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
								 Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							 }
							 that.close();
							 Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.newName);
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
								id: 'wNewName_ok_btn',
								tabIndex: 10,
								handler: function(){
									addNewName();
									that.win.close();
								}
							})),
							(this.components.Cancel = new Ext.Button({
								text: 'Cancel'.localize(),
								id: 'wNewName_cancel_btn',
								tabIndex: 11,
								ctCls: Jedox.kbd.Base.tags.NO_ENTER,
								handler: function(){
									that.win.close();
								}
							}))
					          ]
		});

		this.setContext();
		this.win.show(this);

		scopeCmb.setValue('Workbook'.localize());
		initName();

	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.NewName, Jedox.dlg.Dialog);
