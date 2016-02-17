/*
 * @brief wss file
 *
 * Copyright (C) 2006-2009 Jedox AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (Version 2) as published
 * by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed in the hope thats it will be useful, but WITHOUT
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
 * \author
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com
 *
 * \version
 * SVN: $Id: InsertMacro.js 4295 2010-11-12 11:10:41Z srdjanv $
 *
 */


Jedox.wss.dlg.openInsertMacro = function(obj, from, callback){
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.InsertMacro(obj, from, callback));
};

Jedox.wss.dlg.InsertMacro = (function() {

	return function (obj, from, callback) {

		Jedox.wss.dlg.InsertMacro.parent.constructor.call(this);
		this.id = 'InsertMacro ';
		var that = this;

		Jedox.wss.macro.list([ this, openDialog_post, obj], Jedox.wss.macro.listFmt.FLAT);

		function openDialog_post(listData, obj){

			var thats = this;


			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
	  		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);


		/************************************
		  **** Main componenets *****
		************************************/

			var obj = obj;
			var listData = listData;


			var macroNameLbl = new Ext.form.Label({
				text:'Macro name'.localize().concat(':')
			});


			var macroNameTxf = new Ext.form.TextField({
				hideLabel:true,
				tabIndex: 1,
	//			value: '='.concat(Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName(), '!', Jedox.wss.app.environment.defaultSelection.getActiveRange().getValue(true)),
	//			value:'nesto za pocetak',
			  	width: 290,
				listeners:{
					focus:function(){
						if (functionListGrid.getSelectionModel().getCount() != 0){
							this.setValue('');
							functionListGrid.getSelectionModel().clearSelections();
							btnPanel.layout.setActiveItem(0);
							that.containers.btnPanel = btnPanel.items.items[0];
						}
					},
					blur:function(){
						if (!this.getValue())
							this.setValue(getDefaultMacroName());
						else {
							var rowIndex = functionListGrid.store.find('name', this.getValue());
							if (rowIndex != -1){
								functionListGrid.fireEvent('rowclick', functionListGrid, rowIndex);
								functionListGrid.getSelectionModel().selectRow(rowIndex);
							}
						}
					}
				}
			});

			var functionListData = [];

			for (var i=0; i<listData.length; i++)
				functionListData.push([listData[i]]);

			var functionListStore = new Ext.data.SimpleStore({
		        fields: [{name: 'name'}],
				data:functionListData
		    });


		    // create the Grid
		    var functionListGrid = new Ext.grid.GridPanel({
		        store: functionListStore,
		        columns: [
		            {id:'company',header: "Function", width: 270, sortable: true, dataIndex: 'name'}
		        ],
				sm: new Ext.grid.RowSelectionModel({
					singleSelect: true
				}),
				autoscroll:true,
		        stripeRows: true,
		        height:200,
		        width:290,
				listeners:{
					rowclick:function(grid, rowIndex, e){
						macroNameTxf.setValue(this.store.getAt(rowIndex).get('name'));
						btnPanel.layout.setActiveItem(1);
						that.containers.btnPanel = btnPanel.items.items[1];
					}
				}
		    });


			var okBtn = that.components.OK = new Ext.Button({
				text: 'OK'.localize(),
				tabIndex: 101,
				handler: function(){
					onOK();
				}
			});

			var cancelBtn = that.components.Cancel = new Ext.Button({
				text: 'Cancel'.localize(),
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 102,
				handler: function(){
					if (from == 'widget') Ext.getCmp('formatControlDialog').show();
					that.win.close();
				}
			});



			var newBtn = new Ext.Button({
				text: 'New'.localize(),
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 2,
				width: 70,
				handler: function(){
					onNew();
				}
			});

			var BRLbl = {
				html:'<br/>',
				baseCls:'x-plain'
			};

			var editBtn = new Ext.Button({
				text: 'Edit'.localize(),
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 3,
				width: 70,
				handler: function(){
					onEdit();
				}
			});


			var btnPanel = new Ext.Panel({
				layout:'card',
				baseCls: 'x-plain',
				style: 'padding-left: 10px; padding-top: 8px;',
				activeItem:0,
				items:[new Ext.Panel({
					layout:'form',
					border:false,
					baseCls: 'x-plain',
					items:[newBtn]
				}), new Ext.Panel({
					layout:'form',
					border:false,
					baseCls: 'x-plain',
					items:[editBtn]
				})]
			});


			var mainPanel = new Ext.Panel({
				layout: 'absolute',
				baseCls: 'x-plain',
				border: false,
				items:[
				       (that.containers.mainPanel = new Ext.Panel({
						layout: 'form',
						border: false,
						baseCls: 'x-plain',
						x: 5,
						y: 10,
						width: 292,
						height: 250,
						items: [
							macroNameLbl,
							macroNameTxf,
							functionListGrid
						]
					})),
					{
						layout:'form',
						baseCls: 'x-plain',
						x: 295,
						y: 18,
						height:50,
						items:[btnPanel]
					}]
			});


		/************************************
		  *****       Funcitons        *****
		************************************/

			function initDlg(){
				preselectMacro();
			}

			function getDefaultMacroName(){
	//			var defaultName = obj.name.concat('_', Jedox.wss.wsel[obj.type].events[0].funcname);
	//			functionListStore.find('name', defaultName);

				return (obj.id)? obj.name.concat('_', Jedox.wss.wsel[obj.type].events[0].funcname) : obj.name;
			}

			function preselectMacro(){

				var macro = (obj.id)? obj.macros[Jedox.wss.wsel[obj.type].events[0].name] : false;

				if (macro){
					var index = functionListGrid.store.find('name', macro);
					if (index >= 0) {
						setTimeout(function(){
							functionListGrid.fireEvent('rowclick', functionListGrid, index);
							functionListGrid.getSelectionModel().selectRow(index);
						}, 50);
					}
					else{
						Jedox.wss.general.showMsg('Application Error'.localize(), 'macro_preselection_err_msg'.localize(), Ext.MessageBox.ERROR);
					}
				}
				else {
					macroNameTxf.setValue(getDefaultMacroName());
				}
			}

			function onNew(){
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.editMacro, [{operation:'new', macro:macroNameTxf.getValue()}, refresh]);
	//			win.hide();
			}

			function onEdit(){
					Jedox.gen.load(Jedox.wss.app.dynJSRegistry.editMacro, [{operation:'edit', macro:macroNameTxf.getValue()}, refresh]);
	//			win.hide();
			}

			function onOK(){

				if (validate()) {
					var macro = macroNameTxf.getValue();
					var key = (obj.id) ? Jedox.wss.wsel[obj.type].events[0].name : obj.type;
					var macros = {};
					macros[key] = macro;

					var toSet = {
						id: obj.id,
						type: obj.type,
						name: obj.name,
						macros: macros
					};

					callback(toSet);
					that.win.close();
				}
			}

			function validate(){

				var selection = functionListGrid.getSelectionModel().getSelected();

				if(!selection){
					Jedox.wss.general.showMsg('Application Warning'.localize(), 'macro_selection_wrg_msg'.localize(), Ext.MessageBox.WARNING);
					return false;
				}

				return true;
			}

			function refresh(){
				Jedox.wss.macro.list([ thats, showDialog_post], Jedox.wss.macro.listFmt.FLAT);
			}

			function showDialog_post(listData){
				var refreshListData = [];

				for (var i=0; i<listData.length; i++)
					refreshListData.push([listData[i]]);

				setTimeout(function(){
					functionListStore.loadData(refreshListData);
					initDlg();
				}, 300);

			}


			that.win = new Ext.Window({
				id:'insert-macro-dlg',
				title:'Assign macro'.localize(),
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
				width: 400,
				height: 335,
				//plain: true,
				onEsc: Ext.emptyFn,
				items: mainPanel,
				listeners: {
					close: function()
					{
						Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
						Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
						that.close();
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.insertMacro);
					},
					show:function(){
						setTimeout(function(){
							//that.initFocus(true, 100);
						});
					},
					activate: function(win) {that.activate();}
				},
				buttons: [okBtn, cancelBtn]
			});


			that.setContext();
			that.win.show(that);
			that.containers.btnPanel = btnPanel.items.items[0];

			initDlg();

		}


	//	openDialog_post([["Module1.prki"] ,["Module1.krki"], ["ModuleTest.djuro"],  ["ModuleTest.pero"]]);


};
}
)();

Jedox.util.extend(Jedox.wss.dlg.InsertMacro, Jedox.dlg.Dialog);