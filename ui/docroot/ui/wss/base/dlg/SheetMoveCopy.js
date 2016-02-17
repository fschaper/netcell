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
 * SVN: $Id: SheetMoveCopy.js 4838 2011-04-13 12:34:27Z predragm $
 *
 */

//TO DO (select workbook listener)

Jedox.wss.dlg.openSheetMoveCopy = function () {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.SheetMoveCopy());
};

Jedox.wss.dlg.SheetMoveCopy = (function() {

	return function () {

		Jedox.wss.dlg.SheetMoveCopy.parent.constructor.call(this);
		this.id = 'SheetMoveCopy';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
	  	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);


	//############################### Data and Store ######################################
		var selectedSheetID='';
		var selectedSheetName='';
		var selectedIndex='';
		var AWName=Jedox.wss.wnd.active.getName();
		var AWID=Jedox.wss.app.activeBook.getUid();
		var workbook_id=AWID;
		var worksheet_id = Jedox.wss.app.activeBook.getWsId();
		var next_worksheet_id='';


		var AWName=Jedox.wss.wnd.active.getName();
		var AWID=Jedox.wss.app.activeBook.getUid();

		var bookReg = Jedox.wss.book.reg,
				WData = [],
				book;

		for (var id in bookReg)
		{
			book = bookReg[id];
			WData.push([ book.uid, book._name ]);
		}


		var wStore = new Ext.data.SimpleStore({
			  fields: ['workbookID','workbookName'],
			  data:WData
			  });


		var SData = [];
		var sStore = new Ext.data.SimpleStore({
			  fields: ['sheetID', 'sheetName']
			  //data:SData
		});

		loadSheetData();


	//############################### Components ######################################

		var toBookCmb = this.cmpFocus = new Ext.form.ComboBox({
			fieldLabel: 'To Book'.localize(),
			width: 250,
			tabIndex: 1,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			store:wStore,
			displayField:'workbookName',
			editable:false,
			mode: 'local',
		    triggerAction: 'all',
			listeners:{
				select:{fn:function(combo, record, index){
					workbook_id=WData[index][0];
					loadSheetData();
				}}
			}
		});


		var sheetList = new Ext.DataView({
			 id:'sheet-list',
			 store:sStore,
			 //tabIndex: 2,
			tpl: new Ext.XTemplate(
			     '<div class="sheet-list"><tpl for=".">',
			     '<div class="thumb-wrap">',
			     '<div class="thumb" style="padding: 0px; text-align: left;  ">{sheetName}</div></div>',
			     '</tpl></div>'
		     ),
		     multiSelect: false,
		     singleSelect: true,
		     overClass: 'x-view-over',
		     itemSelector: 'div.thumb-wrap',
		     emptyText: 'No images to display'.localize(),
			 autoWidth:true,
			 listeners: {
		    	containerclick: {fn: onContainerClick, scope: this},
				click:{fn:function(dataView, index, node, e){
					next_worksheet_id=SData[index][0];
					}},
				dblclick:{fn:function(dataView, index, node, e){
					next_worksheet_id=SData[index][0];
					moveWorksheet();
					that.win.close();
				}}
			 }

		});

		var createCopyChb=new Ext.form.Checkbox({
			hideLabel:true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 3,
			boxLabel: 'Create a copy'.localize(),
			name: 'rb-order',
			inputValue: 8
		})



	//############################### Functions ######################################

		function loadSheetData(){
			var worksheets = Jedox.backend.wss.getSheets(workbook_id)[0];
			SData = [];
			for(var i = 0; i < worksheets.length; i += 2)
				SData.push([worksheets[i], worksheets[i+1]]);
			SData.push(['', '(move to end)'.localize()]);
			sStore.loadData(SData);
		}

		function onContainerClick (dView, e) {
			e.stopEvent();
			return false;
		};

		function moveWorksheet(){
			if (sheetList.getSelectionCount() > 0) {
				if (workbook_id === AWID)
					workbook_id = '';
				if (createCopyChb.checked)
					Jedox.wss.app.activeBook.getSheetSelector().copySheet(worksheet_id, next_worksheet_id, workbook_id);
				else
					Jedox.wss.app.activeBook.getSheetSelector().moveSheet(worksheet_id, next_worksheet_id, workbook_id);
			}
		}



	//############################### Main Panel ######################################

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
						labelAlign:'top',
						modal:true,
						layout: 'form',
						baseCls:'main-panel',
						border:false,
						items: [
						toBookCmb,
						{
							html: 'Before sheet'.localize()+':',
							baseCls:'x-plain'
						},
						{
							autoScroll: true,
							layout:'fit',
							border:true,
							width: 250,
							height:150,
							items:sheetList
						},
						createCopyChb
		]
		});


	//############################### Open Dialog window ######################################

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px 5px 5px 5px'},
					title:'Move or Copy'.localize(),
					closable: true,
					closeAction: 'close',
			        autoDestroy: true,
			        cls: 'default-format-window',
			        plain: true,
			        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 280,
					height: 330,
					items: mainPanel,
					listeners: {
						close: function()
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.sheetMoveCopy);
						},
						show:function(){
							setTimeout(function(){
								that.initFocus(true, 100);
							});
						},
						activate: function(win) {that.activate();}
					},

					buttons: [(this.components.OK = new Ext.Button({
						text: 'OK'.localize(),
						tabIndex: 10,
						handler: function(){
							moveWorksheet();
							that.win.close();
						}
					})),
					(this.components.Cancel = new Ext.Button({
						text: 'Cancel'.localize(),
						tabIndex: 11,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						handler: function(){
							that.win.close();
						}
					}))]
		});

		this.setContext();
		this.win.show(this);
		toBookCmb.setValue(AWName);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.SheetMoveCopy, Jedox.dlg.Dialog);