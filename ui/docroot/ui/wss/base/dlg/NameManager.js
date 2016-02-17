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
 * SVN: $Id: NameManager.js 4720 2011-03-18 10:05:03Z andrejv $
 *
 */

Jedox.wss.dlg.openNameManager = function (fromHL, preselection) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.NameManager(fromHL, preselection));
};

Jedox.wss.dlg.NameManager = (function() {

	return function (fromHL, preselection) {

		Jedox.wss.dlg.NameManager.parent.constructor.call(this);
		this.id = 'wNameMngr_dlg_wnd';
		var that = this;


		if (!fromHL){
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		  	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}

		var _selectedIndex;
		var selectedRange='';
		var selectedScope='';
		var namesRecords=[];

		var namesScopedToWorksheetFlag = false;
		var namesScopedToWorkbookFlag = false;
		var namesWithErrorsFlag = false;
		var namesWithoutErrorsFlag = false;



		var AttrRecord = new Ext.data.Record.create([
		 	{name: 'name'},
			{name: 'value'},
			{name: 'refersTo'},
			{name: 'scope'},
			{name: 'comment'}
		]);

		var nameManagerStore=new Ext.data.SimpleStore({
			fields: [{name: 'name'}, {name: 'value'},{name: 'refersTo'}, {name: 'scope'},{name: 'comment'}, {name:'uuid'}]
		});

		initNames();


		//================================ Components ============================================

		var mainDV=new Ext.grid.GridPanel({
			id: 'wNameMngr_names_grd',
			colModel:new Ext.grid.ColumnModel([
				{header: "Name".localize(), width: 30, sortable: true},
				{header: "Value".localize(), width: 20, sortable: true},
				{header: "Refers To".localize(), width: 20, sortable: true},
				{header: "Scope".localize(), width: 20, sortable: true},
				{header: "Comment".localize(), width: 20, sortable: true}
		]),
			store:nameManagerStore,
			viewConfig: {
	        	forceFit: true
	    	},
		    sm: new Ext.grid.RowSelectionModel({singleSelect:true}),
			width: 475,
			height:250,
			border:false,
		    iconCls:'icon-grid',
			listeners:{
	/*
			 	rowdblclick:{fn:function(gridView, index, e){
					var wb = AData[index][0];
					var ws = '';
					openWorkbook(wb, ws);
				}},
	*/
				rowclick:{fn:function(gridView, index,  e){
					_selectedIndex=index;
					toggleButtonsState(true);
					setRefersTo();
					toggleRefersToButtonsState(true);
				}}
			 }
		});

		var saveRangeBtn=new Ext.Toolbar.Button({
			iconCls: 'icon_save_doc',
			cls: 'x-btn-icon',
			tooltip: "Save Range".localize(),
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 11,
			disabled:true,
			handler:setNewRange
		});

		var cancelRangeBtn=new Ext.Toolbar.Button({
			iconCls: 'icon_cancel',
			cls: 'x-btn-icon',
			tabIndex: 10,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tooltip: "Cancel".localize(),
			disabled:true,
			handler:toggleRefersToButtonsState
		});


		var refersToTxf = new Ext.form.TextField({
			//fieldLabel: 'Refers To'.localize(),
			hideLabel:true,
			disabled:true,
			tabIndex: 12,
			value:'',
			width: 375
		});

		var selectRangeBtn=new Ext.Toolbar.Button({
			iconCls: 'select-range-icon',
			cls: 'x-btn-icon',
			tooltip: "Select Range".localize(),
			disabled:true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 13,
			handler: function()
			{
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [
					{
						fnc: [this, selRangeHandleFnc],
						rng: refersToTxf.getValue()
					}
				]);
				that.win.hide();
			}
		});




		//================================ Functions ============================================

		var selRangeHandleFnc=function(selected){
	//		var tmp=selected.split('!');
	//		selectedRange=tmpFormatRange(tmp[1]); // just temp
			var record = nameManagerStore.getAt(_selectedIndex);
			selectedScope=(record.get('scope')==='Workbook'.localize())? '':record.get('scope');

	//		var s= '=' + tmp[0] + '!' +selectedRange;
			that.win.show();
			refersToTxf.setValue(selected);
		}

		function initNames(){

			var position = Jedox.wss.app.environment.defaultSelection.getActiveRange().getActiveCell();
			var tmpResponse=Jedox.backend.ccmd(0, ["nlst", [position._x, position._y]]);
			var names=tmpResponse[0][1][0];

			var tmpRec;
			for (var i=0; i<names.length; i++){
				tmpRec = new AttrRecord({
				  	'name': names[i]['name'],
					'value': names[i]['value'],
					'refersTo': formatSource(names[i]['refers_to']),
					'scope': names[i]['scope'].localize(),
					'comment': names[i]['comment'],
					'uuid': names[i]['uuid']
				});

				nameManagerStore.add(tmpRec);
			}
		}

		function formatSource(s){
				var source = s.replace('=', '').split('!');
				var sheetName = source[0],
					range = source[1];

				return '='.concat(sheetName, (range? '!'.concat(range):''));
		}


		var newNameHandleFnc = function(newName){

			if (newName) {

				var position = Jedox.wss.app.environment.defaultSelection.getActiveRange().getActiveCell();
				var tmpScope = (newName[3] === 'Workbook'.localize())? '' : newName[3];

				var tmpResponse = Jedox.backend.ccmd(0, ["nadd", [position._x, position._y, {name: newName[0], refers_to: newName[2], scope: tmpScope, comment: newName[4]}]]);
				if (tmpResponse[0][0]) {

					var tmpRec = new AttrRecord({
						'name': newName[0],
						'value': tmpResponse[0][1][0]['value'],
						'refersTo': newName[2],
						'scope': newName[3],
						'comment': newName[4],
						'uuid': tmpResponse[0][1][0]['uuid']
					});

					nameManagerStore.add(tmpRec);
					that.win.show();
				}
				else
					showWarrningMessage();
			}
			else
				that.win.show();

		}

		function showWarrningMessage(){
			Ext.Msg.show({
			   title:'New Name'.localize() + '?',
			   msg: "Named formula couldn't be created".localize() + '.',
			   buttons: Ext.Msg.OK,
			   fn: function() {that.win.show()},
			   animEl: 'elId',
			   width:320,
			   icon: Ext.MessageBox.ERROR
			});
		}


		var editNameHandleFnc = function (editedName){

			if (editedName) {
				var record = nameManagerStore.getAt(_selectedIndex);
				var position = Jedox.wss.app.environment.defaultSelection.getActiveRange().getActiveCell();
				var tmpScope = (editedName[3] === 'Workbook'.localize())? '' : editedName[3];
				var tmpResponse = Jedox.backend.ccmd(0, ["nupd", [record.get('uuid'), position._x,position._y,{name: editedName[0], refers_to: editedName[2],  scope:tmpScope, comment: editedName[4]}]]);
				if (tmpResponse && tmpResponse[0] && tmpResponse[0][0]) {
					var record = nameManagerStore.getAt(_selectedIndex);
					record.set('name', editedName[0]);
					record.set('value', tmpResponse[0][1][0]['value']);
					record.set('refersTo', editedName[2]);
					record.set('comment', editedName[4]);
				}
				else
					showWarrningMessage();
			}

			that.win.show();
		}


		var removeName = function (){
			var record = nameManagerStore.getAt(_selectedIndex);
			Jedox.backend.ccmd(0, ["ndel", record.get('uuid')]);
			nameManagerStore.remove(nameManagerStore.getAt(_selectedIndex));
			toggleButtonsState();
		}



		function toggleButtonsState(enable) {
			if (enable){
				Ext.getCmp('wNameMngr_edit_btn').enable();
				Ext.getCmp('wNameMngr_delete_btn').enable();
				return;
			}
			Ext.getCmp('wNameMngr_edit_btn').disable();
			Ext.getCmp('wNameMngr_delete_btn').disable();

		}

		function toggleRefersToButtonsState(enable) {
			if (enable){
				saveRangeBtn.enable();
				cancelRangeBtn.enable();
				selectRangeBtn.enable();
				refersToTxf.enable();
				return;
			}
			saveRangeBtn.disable();
			cancelRangeBtn.disable();
			selectRangeBtn.disable();
			refersToTxf.setValue('');
			refersToTxf.disable();

		}


		function setRefersTo(){
			var record = nameManagerStore.getAt(_selectedIndex);
			var s=record.get('refersTo');
			refersToTxf.setValue(s);
		}


		function setNewRange(){
				var position = Jedox.wss.app.environment.defaultSelection.getActiveRange().getActiveCell();
				var record = nameManagerStore.getAt(_selectedIndex);
				var tmpScope = (record.get('scope') === 'Workbook'.localize())? '' : record.get('scope');

				var tmpResponse = Jedox.backend.ccmd(0, ["nupd", [record.get('uuid'), position._x,position._y,{scope:tmpScope, refers_to: refersToTxf.getValue()}]]);

				record.set('value', tmpResponse[0][1][0]['value']);
				record.set('refersTo', refersToTxf.getValue());
				toggleRefersToButtonsState();
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


		var _errCONST = {"#NULL":true, "#DIV/0!":true, "#VALUE!":true, "#REF!":true, "#NAME?":true, "#NUM!":true, "#N/A":true, "#INSUFFICIENT_RIGHTS":true, "#MAX_ITERATIONS_EXCEEDED":true, "#EXTENSION_ERROR":true}

		function filterFunc(record, id){
			//If the function returns true the Record is included, otherwise it is filtered out.
			var retVal=true;

			if (namesScopedToWorksheetFlag)
				retVal = (record.get('scope') !== 'Workbook'.localize()) ? true : false;
			else
				if (namesScopedToWorkbookFlag)
					retVal = (record.get('scope') === 'Workbook'.localize())? true : false;

			if (retVal) {
				if (namesWithErrorsFlag)
					retVal = (record.get('value') in _errCONST || record.get('refersTo') in _errCONST) ? true : false;
				else
					if (namesWithoutErrorsFlag)
						retVal = (record.get('value') in _errCONST || record.get('refersTo') in _errCONST) ? false : true;
			}

			return retVal;
		}


		function  clearCheckedMenu () {
			var filterMenu = Ext.getCmp('filter-btn').menu.items.items;

			for (var i=2; i<filterMenu.length; i++)
				if (i!==4 && i!==7)
					filterMenu[i].setChecked(false);

			namesScopedToWorksheetFlag = false;
			namesScopedToWorkbookFlag = false;
			namesWithErrorsFlag = false;
			namesWithoutErrorsFlag = false;

			nameManagerStore.clearFilter(false);
		}

		var topBtnPanel = new Ext.Panel({
			id: 'buttonsHolder',
			baseCls: 'x-plain',
			layout: 'column',
			style: 'padding-top: 8px; padding-left: 5px;',
			items: [
			        {
			        	layout: 'form',
			        	columnWidth: 0.3,
			        	baseCls: 'x-plain',
			        	items: [
								new Ext.Button({
									text: 'New'.localize().concat('...'),
									id: 'wNameMngr_new_btn',
									tabIndex: 1,
									minWidth: 70,
									ctCls: Jedox.kbd.Base.tags.NO_ENTER,
									handler: function() {
										Jedox.gen.load(Jedox.wss.app.dynJSRegistry.newName, [newNameHandleFnc, '', nameManagerStore]);
										that.win.hide();
										}
								})
			        	        ]

			        },
			        {
			        	layout: 'form',
			        	columnWidth: 0.3,
			        	baseCls: 'x-plain',
			        	items: [
								new Ext.Button({
										id:'wNameMngr_edit_btn',
										text: 'Edit'.localize(),
										ctCls: Jedox.kbd.Base.tags.NO_ENTER,
										tabIndex: 2,
										minWidth: 70,
										disabled:true,
										handler: function() {
											Jedox.gen.load(Jedox.wss.app.dynJSRegistry.newName, [editNameHandleFnc, nameManagerStore.getAt(_selectedIndex), nameManagerStore]);
											that.win.hide();
										}
									})
			        	        ]

			        },
			        {
			        	layout: 'form',
			        	columnWidth: 0.3,
			        	baseCls: 'x-plain',
			        	items: [
								new Ext.Button({
										id:'wNameMngr_delete_btn',
										ctCls: Jedox.kbd.Base.tags.NO_ENTER,
										tabIndex: 3,
										minWidth: 70,
										text: 'Delete'.localize(),
										disabled:true,
										handler:removeName
										})
			        	        ]

			        }
			        ]
		});

		//================================ Main Panel ============================================

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
						layout: 'absolute',
						baseCls:'x-plain',
						//border:false,
						items: [
						{
							//top panel,
							layout:'column',
							border:false,
							baseCls:'main-panel',
							width: 500,
							height:40,
							x:0,
							y:0,
							items:[
							{
								//top left panel',
								layout:'form',
								border:false,
								baseCls:'top-left-bottom-panel',
								width: 250,
								height:30,
								items: [topBtnPanel]
							},
							{
							//title:right panel,
							layout:'form',
							border:false,
							baseCls:'toolbar-panel',
							width: 235,
							height:30,
							style: 'padding-top: 8px; padding-left: 60px;',
							items: [
							        new Ext.Button({
										id:'filter-btn',
										text: 'Filter'.localize(),
										tabIndex: 5,
										minWidth: 70,
										ctCls: Jedox.kbd.Base.tags.NO_ENTER,
										split:true,
										//disabled:true,
										menu:{
							                id:'filter-menu',
							                cls:'view-menu',
							                width:220,
							                items: [{
							                    text:'Clear'.localize(),
							                    handler:clearCheckedMenu
				},
											'-',
											{
							                    text:'Names Scoped to Worksheet'.localize(),
							                    checked:false,
							                    group:'names-group',
												handler:function(){namesScopedToWorksheetFlag = true; namesScopedToWorkbookFlag = false; nameManagerStore.filterBy(filterFunc);}

				},{
							                    text:'Names Scoped to Workbook'.localize(),
							                    checked:false,
							                    group:'names-group',
												handler:function(){namesScopedToWorksheetFlag = false; namesScopedToWorkbookFlag = true; nameManagerStore.filterBy(filterFunc);}
				},
											'-',
											{
							                    text:'Names With Errors'.localize(),
							                    checked:false,
							                    group:'errors-group',
							                    handler:function(){namesWithErrorsFlag = true; namesWithoutErrorsFlag = false;	nameManagerStore.filterBy(filterFunc);	}
				},
											{
							                    text:'Names Without Errors'.localize(),
							                    checked:false,
							                    group:'errors-group',
							                    handler:function(){namesWithErrorsFlag = false; namesWithoutErrorsFlag = true;	nameManagerStore.filterBy(filterFunc);	}
			/*
				},
											'-',
											{
							                    text:'Defined Names'.localize(),
							                    checked:false,
							                    group:'rest-group',
							                    scope:this
			*/
				}

											]
							            }
							})
		]
							}
							]
						 },
						{
							//main panel,
							layout:'fit',
							defaults: {bodyStyle: 'padding:0px'},
							width: 475,
							height:250,
							autoScroll:true,
							x:5,
							y:40,
							items:mainDV
							//detailsView
						},
							{
								html:'Refers To'.localize() + ':',
								baseCls:'x-plain',
								x:5,
								y:300
		},
						{
							// bottom panel',
							layout:'column',
							border:false,
							baseCls:'top-left-bottom-panel',
							width: 500,
							height:30,
							x:5,
							y:320,
							items:[
								{
									layout:'form',
									border:false,
									width: 30,
									baseCls:'main-panel',
									items:cancelRangeBtn
								},
								{
									layout:'form',
									border:false,
									width: 30,
									baseCls:'main-panel',
									items:saveRangeBtn
								},
								{
									layout:'form',
									border:false,
									width: 380,
									baseCls:'main-panel',
									items:refersToTxf
		},
								{
									layout:'form',
									border:false,
									width: 30,
									baseCls:'main-panel',
									items:selectRangeBtn
		}

							]
						}
		]
		});


		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					id:'wNameMngr_dlg_wnd',
					//defaults: {bodyStyle:'padding:10px 5px 5px 15px'},
					title:'Name Manager'.localize(),
					closable: true,
					closeAction: 'close',
			        autoDestroy: true,
			        plain: true,
			        constrain: true,
			        cls: 'default-format-window',
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 500,
					height: 430,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function()
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.nameManager);
						},
						show:function(){
							setTimeout(function(){
								//that.initFocus(true, 100);
							});
						},
						activate: function(win) {that.activate();}
					},

					buttons: [
					(this.components.Cancel = new Ext.Button({
						text: 'Close'.localize(),
						id:'wNameMngr_close_btn',
						tabIndex: 101,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						handler: function(){
							that.win.close();
						}
					}))]
		});

		if (fromHL)
			{
			mainDV.autoHeight = false;
			mainDV.height = 250;
			mainDV.enableHdMenu = false;
			fromHL(mainDV, preselection);
			}
		else {
			this.setContext();
			that.win.show(that);
		}

	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.NameManager, Jedox.dlg.Dialog);