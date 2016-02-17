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
 * SVN: $Id: Resources.js 4896 2011-04-27 10:45:47Z srdjanv $
 *
 */

Jedox.studio.files.dlg.Resources = function(mFlag, itemsFlag, callBackFn, node, tabOffset){

	if (!tabOffset) tabOffset = 0;
	var that = this;
	var _nodes; // pointer to nodes
	var _mode = mFlag;
	var _itemsFlag = itemsFlag;
	var _dependentsStore; // pointer to store
	var _resourcesData = {}; //init node resource data *data stored in database

	var _isDirty = false; //resources changed

	var resourcesStore = new Ext.data.SimpleStore({
		fields: [
			{name: 'path', type: 'string'},
			{name: 'group', type: 'string'},
			{name: 'hierarchy', type: 'string'},
			{name: 'node', type: 'string'}
		]
	});

	var resourcesGridPanel = new Ext.grid.GridPanel({
		colModel: new Ext.grid.ColumnModel([
			{header: "Path".localize(), width: 340, sortable: true,  menuDisabled:true, dataIndex: 'path'}
		]),
		store: resourcesStore,
		autoScroll:true,
		viewConfig: {
			autoFill: true
		},
		sm: new Ext.grid.RowSelectionModel({
			singleSelect: false
		})
	});

	var dependentsItemStore = new Ext.data.SimpleStore({
		fields: [
			{name: 'path', type: 'string'}
		]
	});

	var dependentsItemGridPanel = new Ext.grid.GridPanel({
		colModel: new Ext.grid.ColumnModel([
			{header: "Path".localize(), width: 340, sortable: true,  menuDisabled:true, dataIndex: 'path'}
		]),
		autoScroll:true,
		store: dependentsItemStore,
		viewConfig: {
			autoFill: true
		},
		sm: new Ext.grid.RowSelectionModel({
			singleSelect: false
		})
	});


	var dependentsItemsStore = new Ext.data.SimpleStore({
		fields: [
			{name: 'name', type: 'string'},
			{name: 'path', type: 'string'}
		]
	});

	var dependentsItemsGridPanel = new Ext.grid.GridPanel({
		colModel: new Ext.grid.ColumnModel([
			{header: "Spreadsheet".localize(), width: 170, sortable: true, dataIndex: 'name'},
			{header: "Path".localize(), width: 150, sortable: true,  menuDisabled:true, dataIndex: 'path'}
		]),
		autoScroll:true,
		store: dependentsItemsStore,
		viewConfig: {
			autoFill: true
		},
		sm: new Ext.grid.RowSelectionModel({
			singleSelect: false
		})
	});

	var btnHolder = new Ext.Toolbar({
		items:[
				{
					text: 'Add'.localize(),
					tabIndex: tabOffset + 1,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					handler: function(){
						that.insertMarkers(that.addMarkers);
					}
				}, {
					text: 'Remove'.localize(),
					tabIndex: tabOffset + 2,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					handler: function(){
						that.removeMarkers();
					}
				}
		       ]
	});

	var mainPanel = new Ext.Panel({
		layout: 'fit',
		width:365,
		height:350,
		bodyStyle: 'background-color: transparent;',
		border:false,
		fbar: btnHolder
	});


	// ----------------- PUBLIC FUNCTIONS---------------------------

	this.insertMarkers = function(callBackFnc){
		Jedox.studio.files.dlg.Markers(callBackFnc);
	}


	//callBackFnc
	this.addMarkers = function(records){

		var rCount = resourcesStore.getCount();

		for (var i = 0, mCount = records.length; i<mCount; i++){

			var equals = false;
			var data = records[i].data;

			for (var j = 0; j<rCount; j++){
				if (resourcesStore.getAt(j).data.node == data.node &&  resourcesStore.getAt(j).data.hierarchy == data.hierarchy && resourcesStore.getAt(j).data.group == data.group) {
					equals = true;
					break;
				}
			}

			if (!equals){
				resourcesStore.add(new Ext.data.Record(data));
				_isDirty = true;
			}

		}
	}

	this.removeMarkers = function(){

		var records = resourcesGridPanel.getSelectionModel().getSelections();

		for (var i = 0, count = records.length; i<count; i++){
			resourcesStore.remove(records[i]);
			_isDirty = true;
		}

	}


	function initData(nodes){

		_nodes = nodes;

		function onRSuccessCbHandler(result){
			resourcesStore.loadData(result);

			for (var i = 0, count = result.length, g, h, n; i<count; i++){
				g = result[i][1];
				h = result[i][2];
				n = result[i][3];

				_resourcesData[g.concat(h, n)] = [g, h, n];
			}
		}

		function onRErrorCbHandler(result){

		}

		function onDSuccessCbHandler(result){
			_dependentsStore.loadData(result);
		}

		function onDErrorCbHandler(result){

		}

		if (_mode == 'resources')
			(new Jedox.backend.RPCAsyncRqst('Studio', 'getResources', [nodes]))
				.setOnSuccess([this, onRSuccessCbHandler]).setOnError([this, onRErrorCbHandler]).send();
		else
			(new Jedox.backend.RPCAsyncRqst('Studio', 'getDependents', [nodes]))
				.setOnSuccess([this, onDSuccessCbHandler]).setOnError([this, onDErrorCbHandler]).send();
	}


	function setConfig(){
		if (_mode == 'resources')
			mainPanel.add(resourcesGridPanel);
		else{
			if (_itemsFlag){
				_dependentsStore = dependentsItemsStore;
				mainPanel.add(dependentsItemsGridPanel)
			}
			else {
				_dependentsStore = dependentsItemStore;
				mainPanel.add(dependentsItemGridPanel)
			}
		}
	}



	this.setResources = function(){

		if (_isDirty) {
			_isDirty = false;
			var resourcesData = {};

			for (var i = 0, count = resourcesStore.getCount(), g, h, n; i < count; i++) {
				g = resourcesStore.getAt(i).get('group');
				h = resourcesStore.getAt(i).get('hierarchy');
				n = resourcesStore.getAt(i).get('node');

				resourcesData[g.concat(h, n)] = [g, h, n];
			}

			(new Jedox.backend.RPCAsyncRqst('Studio', 'setResources', [_nodes[0], _resourcesData, resourcesData])).send();

		}
	}

	this.hideBtns = function(){
		mainPanel.buttons[0].hide();
		mainPanel.buttons[1].hide();
	}

	this.getPanel = function(nodes){
		setConfig();
		initData(nodes);
		if (_mode=='dependents') that.hideBtns();
		return [mainPanel, that.setResources];
	}

	var pp = this.getPanel(node);
	callBackFn(pp);

}




Jedox.studio.files.dlg.Markers = function(callBackFnc, framesetF){

	var _Markers = (function() {

		return function(callBackFnc, framesetF){

			_Markers.parent.constructor.call(this);

			this.id = 'markers';
			var that = this;


			var markersStore = new Ext.data.SimpleStore({
				fields: [
					{name: 'path', type: 'string'},
					{name: 'group', type: 'string'},
					{name: 'hierarchy', type: 'string'},
					{name: 'node', type: 'string'},
					{name: 'context', type: 'string'},
					{name: 'type', type: 'string'},
					{name: 'tag', type: 'string'}
				]
			});

			var resourcesObj = {
				singleSelect:false,
				closeOnInsert:false,
				fetchTaggedArgs:['files', 'spreadsheet', 'RES']
			}

			var frameObj = {
				singleSelect:true,
				closeOnInsert:true,
				fetchTaggedArgs:['files', 'spreadsheet', 'FRAME']
			}

			var configObj = framesetF? frameObj:resourcesObj;

			var markersGP = new Ext.grid.GridPanel({
				id: 'markers-list',
				colModel: new Ext.grid.ColumnModel({
					columns:[
						{header: "Path".localize(), sortable: true, menuDisabled:true, dataIndex: 'path'}
					]
				}),
				store: markersStore,
				viewConfig: new Ext.grid.GridView({
					autoFill:true
				}),
				autoScroll:true,
				sm: new Ext.grid.RowSelectionModel({
					singleSelect: false
				}),
				listeners:{
					rowdblclick: function(gridView, index, e){
						doInsertMarkers(true);
					}
				}
			});

			var markersPanel = new Ext.Panel({
				layout: 'fit',
				bodyStyle: 'background-color: transparent;',
				width:365,
				height:380,
				border:false,
				items:markersGP
			});

			this.win = new Ext.Window({
				title:'Add From Markers'.localize(),
				closable: true,
				closeAction: 'close',
		        autoDestroy: true,
		        plain: true,
				bodyBorder:false,
		        constrain: true,
		        modal: true,
				border:false,
		        resizable: false,
		        animCollapse: false,
				layout: 'fit',
				width: 500,
				height: 300,
				items: [markersPanel],
				listeners: {
					close: function()
					{
						Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
						Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.fileMarkers);
						that.close();
					},
					activate: function(win) {that.activate();}
				},
				buttons: [
					(this.components.OK = new Ext.Button({
						text: 'Insert'.localize(),
						tabIndex: 10,
						handler: function(){
							doInsertMarkers();
						}
					})),
					(this.components.INESRT = new Ext.Button({
						text: 'Insert and Untag'.localize(),
						tabIndex: 11,
						handler: function(){
							doInsertMarkers(true);
						}
					})),
					(this.components.Cancel = new Ext.Button({
						text: 'Close'.localize(),
						tabIndex: 12,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						handler: function(){
							that.win.close();
						}
					}))
				]
			});


			// function

			function initMarkersData(){


				function onSuccessCbHandler(result){

					markersStore.loadData(objectsToRecords(result));
				}

				(new Jedox.backend.RPCAsyncRqst('Studio', 'fetchTagged', configObj.fetchTaggedArgs))
					.setOnSuccess([this, onSuccessCbHandler]).send();
			}


			function doInsertMarkers(untg){

				var selectedRecords = markersGP.getSelectionModel().getSelections();

				if(selectedRecords.length < 1)
					return;

				callBackFnc(selectedRecords);

				if(untg)
					onRemoveSelected(selectedRecords, !configObj.closeOnInsert);

				if(configObj.closeOnInsert)
					that.win.close();

			}


			function onRemoveSelected(selectedRecords, rfsh){

				function cb(result){
					if(rfsh)
						initMarkersData();
				}

				Jedox.backend.rpc([this, cb], 'common', 'removeTagged', [recordsToObjects(selectedRecords)]);

			}


			function recordsToObjects(selectedRecords){

				var items = [];

				for (var i = 0, count = selectedRecords.length; i< count; i++)
					items.push({
						'context':selectedRecords[i]['data']['context'],
						'type':selectedRecords[i]['data']['type'],
						'location':{
							'group':selectedRecords[i]['data']['group'],
							'hierarchy':selectedRecords[i]['data']['hierarchy'],
							'node':selectedRecords[i]['data']['node'],
							'path':selectedRecords[i]['data']['path']
						},
						'tag':selectedRecords[i]['data']['tag']
					});

				return items;
			}

			function objectsToRecords(objects){

					var items = [];

					for (var i =0, count = objects.length; i<count; i++)
						items.push([objects[i].location.path, objects[i].location.group, objects[i].location.hierarchy, objects[i].location.node, objects[i]['context'], objects[i]['type'], objects[i]['tag']]);

					return items;

			}


			initMarkersData();

			this.setContext();
			this.win.show(this);

		}
	})();



	Jedox.util.extend(_Markers, Jedox.dlg.Dialog);
	Jedox.dlg.dlgRegistry.add(new _Markers(callBackFnc, framesetF));
}
