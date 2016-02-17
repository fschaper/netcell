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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: WTPanel.js 5130 2011-07-19 10:03:10Z srdjanv $
 *
 */

// Override for IE
document.getElementsByClassName = function(cl) {
	var retnode = [];
	var myclass = new RegExp('\\b'+cl+'\\b');
	var elem = this.getElementsByTagName('*');
	for (var i = 0; i < elem.length; i++) {
		var classes = elem[i].className;
		if (myclass.test(classes)) retnode.push(elem[i]);
		}
	return retnode;
};

Jedox.studio.files.WTPanel = function(){

	var that = this;
	var timer;

	//this.activeGroup;
	//this.activeHierarchy;

	//this.node; //parent node id
	//this.selection; //selection id
	this.dblClickFlag=false;
	//this.selectedIndex;
	//this.selectedNode;
	//this.startClickTime;//time in miliseconds (for catching rename event)
	//this.activeRecord;//selected record (for Editor Grid View)

	//this.editFlag=false;
	//this.newRecord;
	this.newNodeFlag = false; //ne treba
	//this.onCutCopyParentNode;
	//this.onCutParentNode;
	//this.copyRecords; //record for copy and paste
	//this.cutRecords; //record for cut and paste
	this.fCtxDFlag = {open:false, openNT:false, cut:false, copy:false, rename:false, remove:false, exportBundle:false, properties:false, c_paste:false, c_new:false, c_properties:false, tag:false, c_importBundle:false};
	this.pasteAction = [];

	this.wssRegistar = {};
	this.hyperlinkRegistar = {};
	this.staticRegistar = {};
	this.newHyperlinkFlag = false;

	this._currentTab = false;
	this._renameFlag = false;
	this._stopUserInteraction = false;

	this._triggerSaveAsFromWSSFlag = false; //when true activeted Files tab is caused by WSS trigger and do not do refresh
	this._ghn = null; //last ghn from save as dialog from wss needed for refresh...
	//this._parentPerm;
	this._beforeCloseTriggerFlag = false;//flag needed for handling close trigger from wss
	var _commitedChanges = false; //details view ext triangle flag
	this._tms = 50000; //time in miliseconds
	this._NO_EXP = {'w3s_ahview':true, 'w3s_hyperlink':true, 'w3s_frameset':true, 'w3s_folder':true};

	this._typeOrderData = {
		'w3s_folder':1,
		'w3s_workbook':2,
		'w3s_frameset':3,
		'w3s_ahview':4,
		'w3s_hyperlink':5,
		'w3s_xls':6,
		'w3s_xlsx':7,
		'w3s_csv':8,
		'w3s_rtf':9,
		'w3s_txt':10,
		'w3s_doc':11,
		'w3s_pps':12,
		'w3s_ppt':13,
		'w3s_htm':14,
		'w3s_html':15,
		'w3s_gif':16,
		'w3s_jpg':17,
		'w3s_png':18,
		'w3s_pdf':19,
		'w3s_rar':20,
		'w3s_zip':21,
		'w3s_unknown':22
	}


	this.wbStore = new Ext.data.SimpleStore({
		fields: [
			{name: 'id', type: 'string'},
			{name: 'text',type: 'string'},
			{name: 'leaf'},
			{name: 'qtip', type: 'string'},
			{name: 'iconCls',type: 'string'},
			{name: 'img_src',type: 'string'},
			{name: 'type',type: 'string'},
			{name: 'perm_n'},
			{name: 'order'},
			{name:'size', type: 'float'},
			{name:'lastmod', type:'date', dateFormat:'timestamp'}
		],
		sortInfo:{field:'type', direction: 'ASC'},
		listeners:{
			update: function(store, record, operation) {

				if(_commitedChanges){
					_commitedChanges = !_commitedChanges;
					return;
				}

				_commitedChanges = true;
				that.rename(record.get('id'), record.get('text'));
				this.commitChanges();

			},
			add:function(store, records, index){
				if (that.copyRecord || that.cutRecord) {
					//alert('cut ili copy');
				}
				else {
					if (!that.newHyperlinkFlag){
						setTimeout(function(){
							var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
							if (cmp.getXType() === 'dataview') {
								cmp.select(cmp.store.getCount() - 1);

								var distance = cmp.el.dom.scrollHeight;

								cmp.el.scroll("bottom", distance);
								cmp.fireEvent('edit', cmp);
							}
							else {
								cmp.getSelectionModel().selectLastRow();
								cmp.fireEvent('edit', cmp);
							}
							that._renameFlag = true;
						});
					}
					else
						that.newHyperlinkFlag = false;

				}
			}

		}
	});



	var newBtn = {
		id: 'sWTPanel_new_btn',
		split: true,
		text:'New'.localize(),
		tabIndex: 101,
		iconCls:'new-icon',
		handler:function(){
			this.showMenu();
		},
		tooltip: {
			title: 'New'.localize(),
			text: 'Create new item'.localize()
		},
//		iconCls: 'view-menu-icon',
		menu: {
			cls: 'view-menu',
			autoWidth:true,
			items: [{
				id: 'sWTPanel_newSpdSht_btn',
				text:'New Workbook'.localize(),
				tooltip:{title:'New Workbook'.localize(), text:'Creates new workbook'.localize()},
				iconCls:'new-spreadsheet-icon',
		        handler:that.addWB,
				scope:this
			},{
				id: 'sWTPanel_newPivot_btn',
				text:'New Pivot'.localize(),
				tooltip:{title:'New Pivot'.localize(), text:'Creates new pivot grid'.localize()},
				iconCls:'new-pivot-icon',
		        handler:that.addURLPlugin,
				scope:this
			}, {
				id: 'sWTPanel_newHlink_btn',
		        text:'New Hyperlink'.localize(),
		        iconCls: 'w3s_hyperlink',
				handler: function(){that.addHyperlink()},
		        scope: that
		    },'-',{
		    	id: 'sWTPanel_newFldr_btn',
				text:'New Folder'.localize(),
				tooltip:{title:'New Folder'.localize(), text:'Creates new folder'.localize()},
				iconCls:'new-folder-icon',
		        handler:that.addFolder,
				scope:this
			}]
		}
	}


	var removeTlbBtn = {
		text:'Remove'.localize(),
		tabIndex: 102,
		tooltip:{title:'Remove'.localize(), text:'Remove selected items'.localize()},
		id:'delete', // u remove
        iconCls:'delete-icon',
		handler:this.remove,
		scope:this
	};

	var folderUpTlbBtn = {
		text:'Up'.localize(),
		tabIndex: 105,
		tooltip:{title:'Up'.localize(), text:'One level up'.localize()},
		iconCls:'folder-up-icon',
        handler:this.up,
		scope:this
	};


	var taggedMngTlbBtn = {
		text:'Tags'.localize(),
		tabIndex: 104,
		tooltip:{title:'Tags'.localize(), text:'Manage Tagged files'.localize()},
		iconCls:'tagged-edit-icon',
        handler:function(){Jedox.gen.load(Jedox.studio.app.dynJSRegistry.tagManager);},
		scope:this
	};


	var viewBtn = {
		split: true,
		tabIndex: 106,
		text:'View'.localize(),
		tooltip: {
			title: 'View'.localize(),
			text: 'Change view mode'.localize()
		},
		iconCls: 'view-menu-icon',
		handler: this.setView.createDelegate(this, []),
		menu: {
			id: 'view-menu',
			cls: 'view-menu',
			autoWidth: true,
	        style: {
	            overflow: 'visible'     // For the Combo popup
	        },
			items: [{
				text: 'List'.localize(),
				checked: true,
				group: 'rp-view',
				checkHandler: this.setView,
				scope: this,
				iconCls: 'view-list-icon'
			}, {
				text: 'Thumbnails'.localize(),
				checked: false,
				group: 'rp-view',
				checkHandler: this.setView,
				scope: this,
				iconCls: 'view-thumbnails-icon'
			}, {
				text: 'Details'.localize(),
				checked: false,
				group: 'rp-view',
				checkHandler: this.setView,
				scope: this,
				iconCls: 'view-details-icon'
			},'-',{
				text: 'Only for this folder'.localize(),
				checked: false,
				checkHandler: this.setFolderViewMode,
				scope:this
			}]
		}
	};

	var splitterTlbBtn = {
			xtype:'tbseparator'
	};

	var importBtn = {
			text:'Import'.localize(),
			tabIndex: 103,
			tooltip:{title:'Import'.localize(), text:'Import'.localize()},
			iconCls:'import-file',
			handler:function(){Jedox.gen.load(Jedox.studio.app.dynJSRegistry.importFile, [that.wbStore.getRange(), {g:that.activeGroup, h:that.activeHierarchy, p:that.node}])},
			scope:this
	};

	var refreshBtn = {
			text:'Refresh'.localize(),
			tabIndex: 107,
			tooltip:{title:'Refresh'.localize(), text:'Refresh this folder'.localize()},
			iconCls: 'refresh-icon',
			handler:function(){Ext.getCmp('sFiles_tree_tr').fireEvent('reloadHierarchy');},
			scope:this
	};


	var DataViewClass = Ext.extend(Ext.DataView, {
			focusedClass: "x-view-focused",
			focusEl: true,
			getXType:function(){
				return 'dataview';
			},
			afterRender: function()
			{
				DataViewClass.superclass.afterRender.call(this);
				var that = this;

				if (this.singleSelect || this.multiSelect)
				{
					if (this.focusEl === true)
					{
						this.focusEl = this.el.parent().parent().createChild({
							tag : "a",
							href : "#",
							cls : "x-view-focus",
							tabIndex : "-1"
						});
						this.focusEl.insertBefore(this.el.parent());
						this.focusEl.swallowEvent('click', true);
						this.renderedFocusEl = true;
					}
					else if (this.focusEl)
						this.focusEl = Ext.get(this.focusEl);

//					if (this.focusEl)
//					{
//						this.keyNav = new Ext.KeyNav(this.focusEl, {
////							"enter": function()
////							{
////								if (that.events.onkeyenter)
////									that.events.onkeyenter.fire();
////							},
////							scope: this,
////							forceKeyDown: true
////						});
//					}
				}
			},
			onClick: function(e)
			{
				var item = e.getTarget(this.itemSelector, this.el);
				if (item)
				{
					var index = this.indexOf(item);
					if (this.onItemClick(item, index, e) !== false)
					{
						this.fireEvent("click", this, index, item, e);
						this.retainFocus();
					}
				}
				else
				{
					if (this.fireEvent("containerclick", this, e) !== false)
					{
						this.clearSelections();
						this.retainFocus();
					}
				}
			},
			retainFocus: function()
			{
				if (this.focusEl)
					this.focusEl.focus();
			},
			doRetainFocus: function()
			{
				this.focusEl.focus();
			}
		});


//	var mainListView = new Ext.DataView({
	var mainListView = new DataViewClass({
//			itemSelector: 'div.row-const-list-selector',
			style: 'overflow:auto;',
		id: 'sFiles_mainList_dv',
		store: this.wbStore,
		tpl: new Ext.XTemplate('<div class="sFiles_mainList_dv"><tpl for=".">', '<div class="thumb-wrap">',
			'<div class="thumb" style="padding: 0px; text-align: left;"><div style="width: 16px; height: 16px; display: inline;"><img class="{img_src}" src="../lib/ext/resources/images/default/s.gif" width="16" height="16"></div>',
			'<span class="x-editable">&nbsp;{text}</span></div></div>', '</tpl></div>'),
		autoWidth:true,
		multiSelect: true,
		overClass: 'x-view-over',
		itemSelector: 'div.thumb-wrap',
		emptyText: '',
		plugins: [
                new Ext.DataView.DragSelector(),
                new Ext.DataView.LabelEditor({dataIndex: 'text'})
        ],
		listeners: {
			render:function(p){
				this.getEl().unselectable();
			},
			dblclick: function(dataView, index, node, e){
				that.onDblClick(dataView.store.getAt(index).get('id'), dataView.store.getAt(index).get('iconCls'));
			},
			click: function(dataView, index, node, e){
				that.selectedIndex = index;
//				that.selectedNode = node;
				that.selection = this.store.getAt(index).get('id');
				that.activeRecord = this.store.getAt(index);

				that.setInputMode();
			},
			contextmenu : function(dataView, index, node, e){
				var t = e.target;
				if(t.className == 'thumb'){
					dataView.clearSelections();
					that.onContainerContextMenu(e);
				}
				else {
					var args = {cmp:dataView, index:index, node:node, e:e}
					that.onContextMenu(args);
				}

				that.setInputMode();
			},
			// enable when change main list template like recent
//			containercontextmenu:function(dataView, e){
//				this.clearSelections();
//				that.onContainerContextMenu(e);
//			},
			edit:function (dataView){
				var node = dataView.getSelectedNodes();
				var record = dataView.getRecords(node);
				var index = dataView.getSelectedIndexes();
				var target = document.getElementsByClassName('x-editable');

				dataView.plugins[1].activeRecord = record[0];
				dataView.plugins[1].startEdit(target[index], record[0].data.text);

				//that.newNodeFlag = true;
			},
			containerclick:function(dataView, e){
				if (dataView.getSelectionCount() == 0)
					that.setNoSelectionInterface();
//				dataView.plugins[1].cancelEdit();
				that.setInputMode();
			},
			selectionchange:function(dataView, selections){
				if (selections.length == 0)
					that.setNoSelectionInterface();
				else
					that.setInterfacePermission();
			}
		}
	});




	var mainDetailsView = new Ext.grid.EditorGridPanel({
		id: 'main-details-view',
		colModel: new Ext.grid.ColumnModel([
			{id:'folder-name', header: "Name",width: 30,sortable: true, dataIndex: 'text', renderer:this.formatTitle, editor: new Ext.form.TextField({
				allowBlank: false,
	            listeners: {
					specialkey: function(field, e){
						if (e.getKey() == e.ENTER) {
							mainDetailsView.stopEditing();
							return false;
						}
					},
					beforeshow:function(){
						this.container.alignTo(this.gridEditor.boundEl, "tl", [25, 0]);
						this.setWidth(150);
					}
				}
			})},
			{header: "Size".localize(), width: 20, sortable: true, align:'right', dataIndex: 'size', renderer:function(c,f,g){
				return g.data.size? Ext.util.Format.fileSize(g.data.size):"";
			}},
			{header: "Type".localize(), width: 20, sortable: true, dataIndex: 'type'},
			{header: "Last Modified".localize(), width: 20, sortable: true, dataIndex: 'lastmod', renderer:function(c,f,g){
				return g.data.lastmod? g.data.lastmod.dateFormat('date_format'.localize()):"";
			}}
		]),
		store: this.wbStore,
		viewConfig: {
			forceFit: true,
			sortAscText: 'Sort Ascending'.localize(),
			sortDescText: 'Sort Descending'.localize(),
			columnsText: 'Columns'.localize(),
			groupByText: 'Group by'.localize()
		},
		sm: new Ext.grid.RowSelectionModel({
			//singleSelect: true
		}),
		autoScroll:true,
		border: false,
//		clicksToEdit:3,
		listeners: {
			rowdblclick: function(gridView, index, e){
				that.onDblClick(gridView.store.getAt(index).get('id'), gridView.store.getAt(index).get('iconCls'));
			},
			rowclick: function(gridView, index, e){
				that.selection = gridView.store.getAt(index).get('id');
				that.selectedIndex = index;
				var record = gridView.store.getAt(index);
//				if (that.activeRecord == record) {
//					var nowClickTime = new Date().getTime();
//					if (nowClickTime - that.startClickTime > 500 && nowClickTime - that.startClickTime < 1500) { // interval between two clicks for rename
//						gridView.getColumnModel().setEditable(0, true);
//						gridView.startEditing(index, 0);
//					}
//					else {
//						that.startClickTime = new Date().getTime();
//						gridView.getColumnModel().setEditable(0, false);
//					}
//				}
//				else {
//					that.startClickTime = new Date().getTime();
					gridView.getColumnModel().setEditable(0, false);
					that.activeRecord = record;
//				}
				that.setInterfacePermission(this.store.getAt(index).get('perm_n'));
				that.setInputMode();
			},
			rowselect:function(gridView, index){
//				that.selectedIndex = index;
//				that.selection = gridView.store.getAt(index).get('id');
//				that.activeRecord = gridView.store.getAt(index);

				gridView.getSelectionModel().selectRow(index);
			},
			rowcontextmenu:function(gridView, index, e){
				var args = {cmp:gridView, index:index, e:e}
				e.stopEvent();
				clearTimeout(timer);
				timer = setTimeout(function(){
					that.onContextMenu(args, true);
				}, 0);

				that.setInputMode();
			},
			edit:function (gridView){
				gridView.getColumnModel().setEditable(0, true);
				var record = gridView.getSelectionModel().getSelected();
				var index = gridView.store.indexOf(record);

				gridView.startEditing(index, 0);

					//that.newNodeFlag = true;
			},
			contextmenu:function(e){
				e.stopEvent();
				var gridView = this;
				timer = setTimeout(function(){
					gridView.getSelectionModel().clearSelections();
					that.onContainerContextMenu(e, true);
				}, 0);

				that.setInputMode();
			},
			validateedit: function(o){
				o.value = that.trim(o.value);
				var _ret = that.validateName(o.value, that.activeRecord.data.iconCls);
				return _ret;
			},
			cellcontextmenu:function(gridView, rowIndex, cellIndex, e ) {

				if (cellIndex > 0) {
					gridView.getSelectionModel().clearSelections();
					clearTimeout(timer);
					timer = setTimeout(function(){
						that.onContainerContextMenu(e);
					}, 0);
				}

			},
			keydown:function(e){
				return false;
			},
			keypress:function(e){
				if (e.keyCode in {38:true, 40:true})
					this.fireEvent('rowclick', this, that.getSelectedIndex());
			}
		}
	});


	var mainThumbnailsView =new DataViewClass({
		id: 'main-thumbnails-view',
		style: 'overflow:auto;',
		store: this.wbStore,
		tpl:new Ext.XTemplate(
			'<tpl for=".">','<div class="thumb-wrap" id="{text}">','<div class="thumb"><div class="{img_src}32"><img src="../lib/ext/resources/images/default/s.gif" title="{text}"></div></div>',
			'<span class="x-editable">{shortName}</span></div>','</tpl>','<div class="x-clear"></div>'),

		autoWidth:true,
		multiSelect: true,
		overClass: 'x-view-over',
		itemSelector: 'div.thumb-wrap',
		emptyText: '',
		plugins: [
                new Ext.DataView.DragSelector(),
                new Ext.DataView.LabelEditor({dataIndex: 'text'})
        ],
		prepareData: function(data){
                data.shortName = Ext.util.Format.ellipsis(data.text, 11);
                return data;
        },
		listeners: {
			render:function(p){
				this.getEl().unselectable();
			},
			dblclick: function(dataView, index, node, e){
				that.onDblClick(dataView.store.getAt(index).get('id'), dataView.store.getAt(index).get('iconCls'));
			},
			click: function(dataView, index, node, e){
				that.selectedIndex = index;
				that.selection = dataView.store.getAt(index).get('id');
				that.activeRecord = dataView.store.getAt(index);
				that.setInputMode();
			},
			contextmenu : function(dataView, index, node, e){
				var args = {cmp:dataView, index:index, node:node, e:e}
				that.onContextMenu(args);
				that.setInputMode();
			},
			edit:function (dataView){
				var node = dataView.getSelectedNodes();
				var record = dataView.getRecords(node);
				var index = dataView.getSelectedIndexes();

				var target = document.getElementsByClassName('x-editable');
				var step = target.length/2;

				dataView.plugins[1].activeRecord = record[0];
				dataView.plugins[1].startEdit(target[step + index[0]], record[0].data.text);

				//that.newNodeFlag = true;
			},
			containerclick:function(dataView, e){
				if (dataView.getSelectionCount() == 0)
					that.setNoSelectionInterface();
				dataView.plugins[1].cancelEdit();
				that.setInputMode();
			},
			selectionchange:function(dataView, selections){
				if (selections.length == 0)
					that.setNoSelectionInterface();
				else
					that.setInterfacePermission();
			}
		}
	});

	this.fTlb = new Ext.Toolbar({

		items:[newBtn, removeTlbBtn, splitterTlbBtn, importBtn, splitterTlbBtn, taggedMngTlbBtn, splitterTlbBtn, folderUpTlbBtn, splitterTlbBtn, viewBtn, refreshBtn],
		disabled:true
	});

	var _activePanels = {};

	var mainPanel = new Ext.Panel({
		id:'main-view-panel',
		layout:'card',
		border:false,
		tbar:this.fTlb,
		items:[mainListView, mainDetailsView, mainThumbnailsView],
		activeItem:0
	});


	this.wssPanel = new Ext.Panel({
		border:false,
		layout:'card',
		hideMode:'visibility',
		listeners:{
			beforehide:function(cmp){
				cmp.setHeight(0);
			}
		}
	});

	this.hyperlinkPanel = new Ext.Panel({
		border:false,
		layout:'card'
	});

	this.staticPanel = new Ext.Panel({
		border:false,
		layout:'card'
	});


	this.filesWSSPanel = new Ext.Panel({
		layout:'card',
		border:false,
		items:[mainPanel, this.wssPanel, this.hyperlinkPanel, this.staticPanel],
		activeItem:0
	});


	/*
		this.wss.defaultSrc URL params:
			wam - 'designer' or 'user'

			wb - workbook/template node name (n11, n33, ...)
			var_VARNAME - set variable var_VARNAME after WB load (var_Year, var_Month, etc). - works only when opening template in Reports
	 */




	//TODO: must be this
	this.filesNavigationTabPanel = new Ext.TabPanel({ //just tabs, no body
	 	id:'sFiles_navigation_tbp',
		border:false,
		bodyBorder:false,
		resizeTabs:true,
		tabWidth:150,
        minTabWidth: 120,
		enableTabScroll:true,
        items:[{
			id: 'files-tab',
			title: 'Files'.localize(),
			listeners: {
				activate: function(panel){
					if (that.filesWSSPanel.getLayout().activeItem){
						that.filesWSSPanel.getLayout().setActiveItem(0);
					}
				}
			}
		}],
		activeTab:0,
		listeners:{
			beforetabchange:function(tabPanel, newTab, currentTab){

				//because beforetabchange event activates when add new tab and when activate tab problem when loading broken wb and wss msg handle exception...
				if (newTab && currentTab && newTab.id == currentTab.id)
					return;

				var files = Jedox.studio.frames.files;

				if (files && files.Jedox.wss.app.environment && (files.Jedox.wss.app.environment.inputMode == files.Jedox.wss.grid.GridMode.DIALOG || files.Jedox.wss.general.switchSuspendModeAlert)){

					if (currentTab.type == 'wss'){ //from WSSTab where dialog is opened

						if (!that._currentTab)
							that._currentTab = currentTab;


						if (newTab.type == 'wss') { //access to other WSSTab
							Jedox.studio.app.showMessageERROR('Warrning', files.Jedox.wss.general.switchSuspendModeAlert? 'wb_in_suspend_mode'.localize():'wb_in_dlg_mode'.localize());
							return false;
						}
						else //access to other Tab
							return true;
					}
					else {//from other Tab
						if (newTab.type == 'wss'){
							if (newTab == that._currentTab) //access to WSSTab that has Dlg open
								return true;
							else { //access to other WSSTab
								setTimeout(function(){
									tabPanel.setActiveTab(that._currentTab.id);
									that.filesWSSPanel.getLayout().setActiveItem(1);
									Jedox.studio.app.showMessageERROR('Warrning', 'wb_in_dlg_mode'.localize());
								})
								return false;
							}
						}
						else
							return true;
					}
				}
				else {
					that._currentTab = false;

					//ie and webkit rendering problem hack
					if(!previewPanel.rerendered && Jedox.studio.app.defaultView == 'details' && mainPanel.getLayout().activeItem && mainPanel.getLayout().activeItem.id == 'main-details-view')
						setTimeout(function(){
							previewPanel.setWidth(previewPanel.getWidth()-1);
							setTimeout(function(){
								previewPanel.setWidth(previewPanel.getWidth()+1);
								previewPanel.rerendered = true;
							}, 100);
						});


					if ((newTab.id == 'files-tab' && Jedox.studio.app.resourcesRefreshFlag) && !that._triggerSaveAsFromWSSFlag) {
//							console.log('REFRESH');
							Ext.getCmp('sFiles_tree_tr').fireEvent('onRefresh', that._ghn.g, that._ghn.h,  that._ghn.n);
							Jedox.studio.app.resourcesRefreshFlag = false;
							that._ghn = null;
					}
					else {
						//retain focus on files after tab switch to files for keyboard events
						if (newTab.id == 'files-tab' && mainPanel.rendered) {
							setTimeout(function(){
								that.setFilesFocus();
							});
						}
					}
				}
			},
			beforeremove:function(tabPanel, cmp){
				var files = Jedox.studio.frames.files;
				if (files && files.Jedox.wss.app.environment && (files.Jedox.wss.app.environment.inputMode == files.Jedox.wss.grid.GridMode.DIALOG || files.Jedox.wss.general.switchSuspendModeAlert) && tabPanel.type == 'wss'){
					Jedox.studio.app.showMessageERROR('Warrning', files.Jedox.wss.general.switchSuspendModeAlert? 'wb_in_suspend_mode'.localize():'wb_in_dlg_mode'.localize());
					return false;
				}
			}
		}
    });


	var previewPanel = new Ext.Panel({
		layout:'table',
		layoutConfig: {
	    	columns: 1
		},
		borders:false,
		bodyBorder:false,
		items:[{id:'files-navigation-tab-panel', border:false, height:26, width:2000, rowspan:1, layout: 'fit', items:that.filesNavigationTabPanel }, {id:'files-content-panel', border:false, items:that.filesWSSPanel, layout:'fit', rowspan:2}],
		rerendered:Ext.isGecko, //ie and webkit rendering problem hack
		listeners:{
			resize:function(panel, adjWidth, adjHeight, rawWidth, rawHeight){
				Ext.getCmp('files-navigation-tab-panel').setWidth(adjWidth);
				Ext.getCmp('files-content-panel').setHeight(adjHeight - 26);
				Ext.getCmp('files-content-panel').setWidth(adjWidth);
			}
		}
	});



	Jedox.studio.files.WTPanel.superclass.constructor.call(this, {
		id:'wt-panel',
		//id:'main-view-panel',
		title:'File Manager'.localize(),
		layout:'fit',
		hideMode:'visibility',
		items:previewPanel,
		listeners:{
			show: function(pan){
				if (that.fTlb){
					Jedox.studio.app.containers.fPanFiles = that.fTlb;
					_activePanels['fPanFiles'] = true;
				}
			},
			hide: function(pan){
				delete Jedox.studio.app.containers.fPanFiles;
				delete _activePanels.fPanFiles;
				that.setHeight(0);
			}
		}
	});
}

Ext.extend(Jedox.studio.files.WTPanel, Ext.Panel, {
	initComponent: function()
	{
		var that = this;
		Jedox.studio.files.WTPanel.superclass.initComponent.call(this);

		//because of the "this" scope
		this.renameHandleFnc = function(newName){
			if (that.validateName(newName, that.activeRecord.data.iconCls))
				that.activeRecord.set('text', newName);
		}

		this.refreshHandleFnc =	function(){
			Ext.getCmp('sFiles_tree_tr').fireEvent('reloadActiveHierarchy');
//			Ext.getCmp('sFiles_tree_tr').fireEvent('onRefresh', that.activeGroup, that.activeHierarchy, that.selection);

		}

		this.importHandleFnc = function(res, showLog){
			setTimeout(function(){
				that.initWTData(that.node, that.activeGroup, that.activeHierarchy, that._parentPerm);
				if(res['log'] && showLog){
					that.showLogMsg('Import'.localize(), 'imp_success_msg'.localize().concat('<br><br>', 'Import log'.localize()), Ext.MessageBox.INFO, res['log'], false);
				}
			}, 200);
		}
	},

	showLogMsg: function(title, msg, dlgIcon, value, cb){
		Ext.MessageBox.show({
			title: title,
			msg: msg,
			icon: dlgIcon,
			modal: true,
			width:400,
			buttons: Ext.MessageBox.OK,
            prompt:true,
            multiline: true,
			value:value,
			fn: function(){
				if (cb instanceof Array && cb.length > 1)
					cb[1].apply(cb[0], cb.slice(2));
			}
		});
	},


	setView: function (m, pressed){

		if(this._setViewModeFlag) //when preselection dont trigger
			return;

		var that = this;

		var viewMenu = Ext.menu.MenuMgr.get('view-menu');
		viewMenu.render();
		var items = viewMenu.items.items;
		var onlyForThisFolderChb = items[4];

		var view = 'list';


		if (!m) { // cycle if not a menu item click
			var b = items[0], r = items[1], h = items[2];
			if (b.checked) {
				r.setChecked(true);
			}
			else
				if (r.checked) {
					h.setChecked(true);
					view = 'list';
				}
				else
					if (h.checked) {
						b.setChecked(true);
						view = 'details';
					}

			return;
		}


		if (pressed) { // cycle if not a menu item click
			var mvp = Ext.getCmp('main-view-panel');
			switch (m.text) {
				case 'List'.localize():
					mvp.getLayout().setActiveItem('sFiles_mainList_dv')
					mvp.ownerCt.doLayout();
					//btn.setIconClass('preview-bottom');
					break;
				case 'Thumbnails'.localize():
					mvp.getLayout().setActiveItem('main-thumbnails-view');
					mvp.ownerCt.doLayout();
					view = 'icons';
					break;
				case 'Details'.localize():
					mvp.getLayout().setActiveItem('main-details-view')
					mvp.ownerCt.doLayout();
					view = 'details';
					break;
			}


			if (onlyForThisFolderChb.checked){
				this.setFolderViewMode(onlyForThisFolderChb, true, view);
			}
			else
				Jedox.studio.app.defaultView = view;


			this.setInputMode();
			this.clearAllSelections();
		}

	},




	initWTData: function(node, group, hierarchy, parentPerm, view, name){

		var that = this;

		this.node = node;
		this.containerName = name;
		this.selection = null;

		if (this.activeGroup != group || this.activeHierarchy != hierarchy){
			this.copyRecords = null; //record for copy and paste
			this.cutRecords = null;//record for cut and paste
		}

		this.activeGroup = group;
		this.activeHierarchy = hierarchy;
		this._parentPerm = parentPerm;

//------------------------ asinc -----------------------

		var wssStudioHandler = {
			treeMngNode: function(result){

				if (!result) {
					//show feedback
					Jedox.studio.app.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());
					return false;
				}

				var wbData=[];
				var type;

				for (var i = 0; i < result.length; i++)
					wbData.push([result[i].id, result[i].text, result[i].leaf, result[i].qtip, result[i].iconCls, that.img_src(result[i].iconCls.concat(result[i].hasAs? '_as':'')), that.getType(result[i].iconCls), result[i].perm_n, that._typeOrderData[result[i].iconCls], result[i].size, result[i].mtime]);


				that.wbStore.removeAll();

				//setViewMode
				that.setViewMode(view);

				that.wbStore.loadData(wbData);
				that.wbStore.sort('text', 'ASC');
				that.wbStore.sort('order', 'ASC');

				that.enableTlb();
				that.setContainerInterfacePermission(parentPerm);
				that.setUpTlbBtnState(node != 'root');


			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.treeMngNode('file', this.node, 'dump', 0);
	},

	setViewMode:function(mode){ //preselection view mode

		var that = this;

		this._setViewModeFlag = true;

		var viewMenu = Ext.menu.MenuMgr.get('view-menu');
		viewMenu.render();

		var items = viewMenu.items.items;

		var viewMode = Jedox.studio.app.defaultView;
		if(mode){
			items[4].setChecked(true);
			viewMode = mode;
		}
		else{
			items[4].setChecked(false);
		}

			var mvp = Ext.getCmp('main-view-panel');
			switch (viewMode) {
				case 'list':
					mvp.getLayout().setActiveItem('sFiles_mainList_dv');
					mvp.ownerCt.doLayout();
					items[0].setChecked(true);
					break;
				case 'icons':
					mvp.getLayout().setActiveItem('main-thumbnails-view');
					mvp.ownerCt.doLayout();
					items[1].setChecked(true);
					break;
				case 'details':
					mvp.getLayout().setActiveItem('main-details-view');
					mvp.ownerCt.doLayout();
					items[2].setChecked(true);
					break;
			}

		setTimeout(function(){
			that._setViewModeFlag = false;
		});

	},

	getViewMode:function(){

		var mode = 'list';

			var viewMenu = Ext.menu.MenuMgr.get('view-menu');
			viewMenu.render();
			var items = viewMenu.items.items;
			var b = items[0], r = items[1], h = items[2];

			if (r.checked)
				mode = 'icons';
			else if(h.checked)
				mode = 'details';

			return mode;

	},


	setFolderViewMode:function(m, pressed, view){ //if view private view mode changed with checkbox checked

		if (this._setViewModeFlag)
			return;

		var that = this;

		var mode = view? view:(pressed? this.getViewMode():pressed);

		var wssStudioHandler = {
			setFilesUserView: function(result){

				if (!result) {
					//show feedback
					Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
					return false;
				}

				Ext.getCmp('sFiles_tree_tr').fireEvent('setFolderViewMode', that.node, mode);
				that.setInputMode();

			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.setFilesUserView('file', this.node, mode);

	},

	clear:function(){
		this.wbStore.removeAll();
	},

	img_src:function(iconCls){
		return iconCls;
	},

	getType:function(iconCls){

		var _return;

		switch (iconCls){
			case 'w3s_folder':
				_return = 'Folder'.localize();
				break;
			case 'w3s_workbook':
				_return = 'Spreadsheet'.localize();
				break;
			case 'w3s_frameset':
				_return = 'Frameset'.localize();
				break;
			case 'w3s_hyperlink':
				_return = 'Hyperlink'.localize();
				break;
			case 'w3s_csv':
				_return = 'Microsoft Office Excel Comma Separated Values File'.localize();
				break;
			case 'w3s_doc':
				_return = 'Microsoft Office Word 97 - 2003'.localize();
				break;
			case 'w3s_pdf':
				_return = 'Adobe Acrobat Document'.localize();
				break;
			case 'w3s_gif':
				_return = 'GIF Image'.localize();
				break;
			case 'w3s_htm':
			case 'w3s_html':
				_return = 'Firefox Document'.localize();
				break;
			case 'w3s_jpg':
				_return = 'JPEG Image'.localize();
				break;
			case 'w3s_png':
				_return = 'PNG Image'.localize();
				break;
			case 'w3s_pps':
				_return = 'Microsoft Office PowerPoint 97 - 2003 Show'.localize();
				break;
			case 'w3s_ppt':
				_return = 'Microsoft Office PowerPoint 97 - 2003 Presentation'.localize();
				break;
			case 'w3s_rar':
				_return = 'WinZip File'.localize();
				break;
			case 'w3s_rtf':
				_return = 'Rich Text Format'.localize();
				break;
			case 'w3s_txt':
				_return = 'Text Document'.localize();
				break;
			case 'w3s_xls':
				_return = 'Microsoft Office Excel 97 - 2003 Workbook'.localize();
				break;
			case 'w3s_xlsx':
				_return = 'Microsoft Office Excel Workbook'.localize();
				break;
			case 'w3s_zip':
				_return = 'WinZip File'.localize();
				break;
			case 'w3s_unknown':
				_return = 'Unknown File format'.localize();
				break;
			case 'w3s_ahview':
				_return = 'Palo Pivot'.localize();
				break;
			default :
				_return = 'Unknown File format'.localize();
				break;
		}

		return _return;

	},


	formatTitle: function(value, p, record) {
		return String.format(
                '<div class="topic"><img class="{0}" src="../lib/ext/resources/images/default/s.gif" width="16" height="16" /><span style="vertical-align:top;">&nbsp;&nbsp;{1}</span></div>',
                record.data.img_src, value
        );
    },


	onDblClick:function(id, iconCls){
		var that = this;

		switch(iconCls){
			case 'w3s_folder':
				Ext.getCmp('sFiles_tree_tr').fireEvent('select', id);
				break;
			case 'w3s_workbook':
			case 'w3s_frameset':
				this.openWB(id);
				break;
			case 'w3s_hyperlink':
			case 'w3s_ahview':
				this.openHyperlink(id);
				break;
			default :
				this.openStatic(id);
				break;
		}

		setTimeout(function(){
			that._stopUserInteraction = false;
		}, 3000);
	},


	addFolder:function(){

		var that = this;

		var iconCls = 'w3s_folder';
		var text = this.getNewItemName('New Folder'.localize(), iconCls);
		var leaf = false;
		var qtip = '';
		var type = iconCls.split('_')[1];
		var img_src = this.img_src(iconCls);
		var perm_n = this._parentPerm;

//------------------------ asinc -----------------------

		var wssStudioHandler = {
			treeMngNode: function(result){

				if (!result) {
					//show feedback
					Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
					return false;
				}

				var newRecord = new Ext.data.Record({
					'id':result,
					'text':text,
					'leaf':leaf,
					'qtip':qtip,
					'iconCls':iconCls,
					'img_src':img_src,
					'perm_n':perm_n
				});

				that.wbStore.add(newRecord);
				that.newNodeFlag = true;
				that.activeRecord = newRecord;
				that.newRecord = newRecord;
				that.selection = result;

				var newNode = {
					id:result,
					text: text,
					leaf: leaf,
					qtip:qtip,
					iconCls:iconCls,
					perm_n:perm_n
				}

				//doClick on parent
				Ext.getCmp('sFiles_tree_tr').fireEvent('addNode', that.node, newNode, perm_n);

			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.treeMngNode('file', this.node, 'addNode', leaf, type, {name: text, desc: qtip});


		this.setInputMode();
	},


	addWB:function(){

		var that = this;

		var iconCls = 'w3s_workbook';
		var text = this.getNewItemName('New Workbook'.localize(), iconCls);
		var leaf = true;
		var qtip = '';

		var type = iconCls.split('_')[1];
		var img_src = this.img_src(iconCls);
		var perm_n = this._parentPerm;


//------------------------ asinc -----------------------

		var wssStudioHandler = {
			treeMngNode: function(result){

				if (!result) {
					//show feedback
					Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
					return false;
				}

				var newRecord = new Ext.data.Record({
					'id':result,
					'text':text,
					'leaf':leaf,
					'qtip':qtip,
					'iconCls':iconCls,
					'img_src':img_src,
					'perm_n':perm_n
				});

				that.wbStore.add(newRecord);
				that.newNodeFlag = true;
				that.activeRecord = that.newRecord = newRecord;
				that.selection = result;
				that.setInputMode();

			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.treeMngNode('file', this.node, 'addNode', leaf, type, {name: text, desc: qtip});


		this.setInputMode();

	},


	addHyperlink:function(){
		var that = this;

		function fn(name, desc, url, target){
			var text = name;
			var leaf = true;
			var qtip = desc;
			var iconCls = 'w3s_hyperlink';
			var type = iconCls.split('_')[1];
			var img_src = that.img_src(iconCls);
			var perm_n = that._parentPerm;


			for (var i = 0, items = that.wbStore.data.items, count = items.length; i < count; i++) {
				var item = items[i].data;
				var newFileName = text;
				if (newFileName == item.text && item.type == 'Hyperlink'.localize()) {
					Jedox.studio.app.showMessageERROR('Hyperlink name error'.localize(), 'add_hpl_err_file_exists'.localize({'new_name':newFileName}));
					return false;
				}
			}


//------------------------ asinc -----------------------

			var wssStudioHandler = {
				treeMngNode: function(result){

					if (!result) {
						//show feedback
						Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
						return false;
					}

					var newRecord = new Ext.data.Record({
						'id':result,
						'text':name,
						'leaf':leaf,
						'qtip':qtip,
						'iconCls':iconCls,
						'img_src':img_src,
						'type':'Hyperlink'.localize(),
						'perm_n':perm_n
					});

					that.newHyperlinkFlag = true;
					that.wbStore.add(newRecord);
					that.newNodeFlag = true;
					that.activeRecord = newRecord;
					that.newRecord = newRecord;
					that.selection = result;
					that.setInputMode();
				}
			}

			var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
			wssStudioStub.treeMngNode('file', that.node, 'addNode', leaf, type, {
						name: name,
						desc: qtip,
						hyperlink: {
							type: 'url',
							target: target,
							url: url
						}
					});

			return true;
		}

		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openAddHyperlink, [fn]);

	},


	addURLPlugin:function(){
		var that = this;

			var iconCls = 'w3s_ahview';
			var text = this.getNewItemName('New Pivot'.localize(), iconCls);
			var leaf = true;
			var qtip = '';

			var type = 'urlplugin';
			var subtype = iconCls.split('_')[1];
			var img_src = that.img_src(iconCls);
			var perm_n = this._parentPerm;


//------------------------ asinc -----------------------

			var wssStudioHandler = {
				treeMngNode: function(result){

					if (!result) {
						//show feedback
						Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
						return false;
					}

					var newRecord = new Ext.data.Record({
						'id':result,
						'text':text,
						'leaf':leaf,
						'qtip':qtip,
						'iconCls':iconCls,
						'img_src':img_src,
						'type':that.getType(iconCls),
						'perm_n':perm_n
					});


					that.wbStore.add(newRecord);
					that.newNodeFlag = true;
					that.activeRecord = that.newRecord = newRecord;
					that.selection = result;
					that.setInputMode();

				}
			}

			var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
			wssStudioStub.treeMngNode('file', that.node, 'addNode', leaf, type, {
					name: text,
					desc: qtip,
					type:type,
					subtype:subtype,
					params:{
						hideToolbar:0,
						hideSave:0,
						hideFilter:0,
						hideStaticFilter:0,
						hideHorizontalAxis:0,
						hideVerticalAxis:0,
						hideConnectionPicker:1
					}
				});

	},


	getNewItemName:function(tmplName, iconCls){
		var br = 1;
		var exist = true;
		var name = tmplName.toLowerCase();

		while (exist){
			exist = false;
			if (br >1) name = tmplName.toLowerCase() + ' (' + br + ')';
			this.wbStore.each( function(record){
				if (record.data.text.toLowerCase() == name && (iconCls && iconCls == record.data.iconCls)){
					br= br+1;
					exist = true;
					return false;
				}
			}, [this] )
		}

		return br>1? tmplName + ' (' + br + ')':tmplName;
	},


	getNewItemCopyName:function(tmplName, iconCls){
		var br = 0;
		var exist = true;
		var name = tmplName.toLowerCase();

		while (exist){
			exist = false;
			if (br == 1) name = ('copy_of_name'.localize() + ' ' + tmplName).toLowerCase();
			if (br >1) name = ('copy_num_of_name'.localize({num:br}) + ' ' + tmplName).toLowerCase();
			this.wbStore.each( function(record){
				if (record.data.text.toLowerCase() == name && (iconCls && iconCls == record.data.iconCls)){
					br= br+1;
					exist = true;
					return false;
				}
			}, [this] )
		}

		return (br == 1)? ('copy_of_name'.localize() + ' ' + tmplName): ((br>0)? ('copy_num_of_name'.localize({num:br}) + ' ' + tmplName):(tmplName));

	},

	getNodes:function(){
		return this.wbStore.getRange();
	},

	getSelectedRecords:function(){
		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		var selectedRecords;

		if (cmp.getXType() === 'dataview'){
			var nodes = cmp.getSelectedNodes();
			selectedRecords = cmp.getRecords(nodes);
		}
		else
			selectedRecords = cmp.getSelectionModel().getSelections();

			return selectedRecords;
	},

	getSelectedNodes:function(){

		var records = this.getSelectedRecords(),
			ns = [];

		for(var i=0, count = records.length; i<count; i++){
			ns.push(records[i].data.id);
		}

		return ns;
	},

	getSelectedIndex:function(){
		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		var selectedIndex = -1;

		if (cmp.getXType() === 'dataview'){
			var selections = cmp.getSelectedIndexes();
			if (selections instanceof Array && selections.length > 0)
				selectedIndex = selections[0];
		}
		else{
			if(cmp.getSelectionModel().hasSelection())
				for(var i=0, sm = cmp.getSelectionModel(), count = cmp.getStore().getCount(); i<count; i++)
					if(sm.isSelected(i)){
						selectedIndex = i;
						break;
					}
		}

		return selectedIndex;
	},



	getRecordByName:function(name){
		var r;
		this.wbStore.each( function(record){
				if (record.data.text.toLowerCase() == name.toLowerCase()){
					r = record;
					return false;
				}
			}, [this])
		return r;
	},

	getRecordById:function(id){
		var r;
		this.wbStore.each( function(record){
				if (record.data.id == id){
					r = record;
					return false;
				}
			}, [this])
		return r;
	},


	remove:function(){

		this.setInputMode();
		var that = this;
		var title = 'Remove Item'.localize();

//		if (this.selection){
//			console.log(this.selection);
			var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
			if (cmp.getXType() === 'dataview'){
				var nodes = cmp.getSelectedNodes();
				var removeRecords = cmp.getRecords(nodes);
			}
			else
				var removeRecords = cmp.getSelectionModel().getSelections();

			if (removeRecords.length){
//			console.log(removeRecords.length);
			if (removeRecords.length>1){
				var msg = 'remove_items_warning_msg'.localize({'nmb':removeRecords.length});
				var rnodes = [];
				for (var i=0; i < removeRecords.length; i++)
					rnodes.push(removeRecords[i].data.id); //nodes for referrers list

				var fn = function (){

					var removeAction = [],
						noPermsNames = [],
						permType = Jedox.studio.access.permType;

					for (var i=0; i < removeRecords.length; i++) {
						if(removeRecords[i].data['perm_n'] & permType.DELETE)
							removeAction.push([that.node, 'removeNode', removeRecords[i].data.id]);
						else
							noPermsNames.push(' '.concat(removeRecords[i].data['text']));
					}


					if(removeAction.length > 0){

						function onSuccessCbHandler(result){

							for (var i=0; i < removeRecords.length; i++) {
								Ext.getCmp('sFiles_tree_tr').fireEvent('removeNode', removeRecords[i].data.id);
							}

							that.initWTData(that.node, that.activeGroup, that.activeHierarchy, that._parentPerm);
	//						Jedox.studio.app.showTopMsg('', 'Items removed successefully'.localize());
							Jedox.studio.app.reportsRefreshFlag = true;

							//show msg of items that could not be removed because of permission;
							if(noPermsNames.length > 0)
								Jedox.studio.app.showMessageERROR('Application Error'.localize(), 'remove_items_no_perms_err_msg'.localize({names:noPermsNames.toString()}));

						}

						function onErrorCbHandler(result){

						}

						(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', removeAction]))
							.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

					}
				}

//				Jedox.studio.app.showMessageQUESTION(title, msg, fn);
				Jedox.studio.app.showMessageR_QUESTION_YND({nodes:rnodes, container:true}, title, msg, fn);
			}else{

				var selectionID = removeRecords[0].data.id;
				var msg = 'remove_item_warning_msg'.localize({'name':removeRecords[0].data.text});
				var fn = function (){

					function onSuccessCbHandler(result){
						Ext.getCmp('sFiles_tree_tr').fireEvent('removeNode', selectionID);
						that.initWTData(that.node, that.activeGroup, that.activeHierarchy, that._parentPerm);
						Jedox.studio.app.showTopMsg('', 'Item removed successefully'.localize());
						Jedox.studio.app.reportsRefreshFlag = true;
					}

					function onErrorCbHandler(result){

					}

					(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', that.node, 'removeNode', selectionID]))
						.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();


				}

//				Jedox.studio.app.showMessageQUESTION(title, msg, fn);
				Jedox.studio.app.showMessageR_QUESTION_YND({nodes:[selectionID], container:!removeRecords[0].data.leaf}, title, msg, fn);
			}

		}
		else {
			var msg = 'You did\'t select an item. Select an Item and try again.'.localize();
			Jedox.studio.app.showMessageERROR(title, msg);
			//Ext.getCmp('sFiles_tree_tr').fireEvent('test');
		}

	},

	removeRecord:function(r){
		var id = r.data.id;

		this.wbStore.remove(r);
		Ext.getCmp('sFiles_tree_tr').fireEvent('removeNode', id);
	},


	rename:function(id, newName){

		var that = this;

		function onSuccessCbHandler(result){
			Ext.getCmp('sFiles_tree_tr').fireEvent('renameNode', id, newName);
			that._renameFlag = false;
		}

		function onErrorCbHandler(result){
			Jedox.studio.app.showMessageERROR('Cant rename file!');
			that._renameFlag = false;
		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', this.node, 'renameNode', id, newName]))
			.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();


	},


	findById:function(id){
		var index = this.wbStore.findExact('id', id);
		return this.wbStore.getAt(index).get('text');
	},

	getTypeById:function(id){
		var index = this.wbStore.findExact('id', id);
		return this.wbStore.getAt(index).get('iconCls').replace('w3s_', '') || 'workbook';
	},

	isURLPlugin:function(id){
		var index = this.wbStore.findExact('id', id);
		return this.wbStore.getAt(index).get('iconCls') == 'w3s_ahview'? true:false;
	},

	findByText:function(text){
		var index = this.wbStore.findExact('text', text);
		return this.wbStore.getAt(index).get('id');
	},

	up:function(){
		Ext.getCmp('sFiles_tree_tr').fireEvent('up', this.node);
		this.setInputMode();
	},


	onContainerContextMenu:function(e, ieHack){
		var that = this;

		this.setNoSelectionInterface();

		if (this.fTlb.disabled)
			return;

            var menu = new Ext.menu.Menu({
                id:'f-gc-ctx',
                enableScrolling: false,
				autoWidth:true,
			  	listeners: {
			   		hide: function(menu){
			    		menu.destroy();
			   		}
			  	},
                items: [{
                    text:'Paste'.localize(),
					disabled:that.fCtxDFlag.c_paste  || !(this.copyRecords || this.cutRecords),
					iconCls: 'paste-icon',
					handler:function(){that.onPasteNEW();},
                    scope: that
                },'-',{
					text:'New'.localize(),
					iconCls:'new-icon',
					disabled:that.fCtxDFlag.c_new,
					menu:{
						cls: 'view-menu',
						autoWidth:true,
						items: [{
							text:'New Workbook'.localize(),
							iconCls:'new-spreadsheet-icon',
					        handler:that.addWB,
							scope:that
						},{
							text:'New Pivot'.localize(),
							tooltip:{title:'Palo Pivot'.localize(), text:'Creates new pivot grid'.localize()},
							iconCls:'new-pivot-icon',
					        handler:that.addURLPlugin,
							scope:that
						}, {
		                    text:'New Hyperlink'.localize(),
		                    iconCls: 'w3s_hyperlink',
							handler: function(){that.addHyperlink()},
		                    scope: that
		                },'-',{
							text:'Folder'.localize(),
							tooltip:{title:'New Folder'.localize(), text:'Creates new folder'.localize()},
							iconCls:'new-folder-icon',
					        handler:that.addFolder,
							scope:that
						}]
					}
				},'-',
//                {
//					iconCls: 'import-file',
//                    text:'Import file'.localize(),
//					disabled:that.fCtxDFlag.c_new,
//					handler: function(){Jedox.gen.load(Jedox.studio.app.dynJSRegistry.importFile, [that.wbStore.getRange(), {g:that.activeGroup, h:that.activeHierarchy, p:that.node}])},
//                    scope: that
//                },
				{
					iconCls: 'import-file',
                    text:'Import'.localize(),
					disabled:that.fCtxDFlag.c_importBundle,
					handler: function(){Jedox.gen.load(Jedox.studio.app.dynJSRegistry.importFile, [that.wbStore.getRange(), {g:that.activeGroup, h:that.activeHierarchy, p:that.node}])},
                    scope: that
                }, '-',{
                    text:'Properties'.localize(),
                    iconCls: 'properties-icon',
					disabled:that.fCtxDFlag.c_properties,
					handler:function(){that.onProperties(that.node, true)},
                    scope: that
                }]
            });

//		if(!ieHack)
//			e.stopEvent(); //IE bug

		menu.showAt(e.getXY());
	},

	showTagMenu:function (res, menu, alignEl, alignPos, parentMenu, name){

		var that = this;

		menu.removeAll();

		var predefinedItems = [{
				text:'As Resource'.localize(),
				value:'RES',
				handler:function (item) { that.onTagClick(item, name); }
			},{
				text:'As Frame'.localize(),
				value:'FRAME',
				handler:function (item) { that.onTagClick(item, name); }
			}
		];

		menu.add(predefinedItems);
		menu.addSeparator();

		for (var i = 0, br = 0, count = res.length; i<count; i++)
		{
			if (res[i] != 'RES' && res[i] != 'FRAME') {
				menu.addMenuItem({
					text: res[i],
					value:null,
					handler: function(item){
						that.onTagClick(item, name);
					}
				});
				br++;
			}
		}

		if (br >0)
			menu.addSeparator();

		menu.addMenuItem({
			text: 'New Tag'.localize(),
			handler: function(item){
				that.onNewTag(item, name);
			}
		});

		menu.loaded = true;
		menu.show(alignEl, alignPos, parentMenu);
	},

	onTagClick:function(item, name){

		var that = this;

		function cb(path){

			function rpc_cb(result){
				if (!result)
					Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
			}

			Jedox.backend.rpc([this, rpc_cb], 'common', 'addTagged', ['files', 'spreadsheet',
				{group:that.activeGroup, hierarchy: that.activeHierarchy, node: that.selection, path: path.concat(name)}, item.value || item.text]);
		}

		Ext.getCmp('sFiles_tree_tr').fireEvent('onGetPath', that.node, cb);
	},

	onNewTag:function(menuItem, name){

		var that = this;

		function cb(path){

				var item = {group:that.activeGroup, hierarchy: that.activeHierarchy, node: that.selection, path: path.concat(name)};
				Jedox.gen.load(Jedox.studio.app.dynJSRegistry.addTag, [item]);
		}

		Ext.getCmp('sFiles_tree_tr').fireEvent('onGetPath', that.node, cb);
	},

	onContextMenu : function(args, ieHack){

		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		if (cmp.getXType() === 'dataview'){
			var nodes = cmp.getSelectedNodes();
			var selectedRecords = cmp.getRecords(nodes);
			if (selectedRecords.length == 0 || !this.checkIsSelected(selectedRecords, args.cmp.store.getAt(args.index))){
				args.cmp.select(args.node);
				args.cmp.fireEvent('click', args.cmp, args.index, args.node, args.e);
			}
		}
		else{
			var selectedRecords = cmp.getSelectionModel().getSelections();
			if (selectedRecords.length == 0 || !this.checkIsSelected(selectedRecords, args.cmp.store.getAt(args.index))){
				args.cmp.fireEvent('rowselect', args.cmp, args.index);
				args.cmp.fireEvent('rowclick', args.cmp, args.index);
			}
		}


		var openInNewTabFlag = args.cmp.store.getAt(args.index).get('iconCls') === 'w3s_folder'? true:false;
		var that = this;
        var menu = new Ext.menu.Menu({
                id:'sFiles_mainListViewCtx_mn',
                enableScrolling: false,
        		listeners: {
    				hide: function(menu){
    					menu.destroy();
    				}
    			},
                items: [{
                    text:'Open'.localize(),
					disabled:that.fCtxDFlag.open,
					iconCls: 'open-folder-icon',
					handler:function(){that.onDblClick(that.selection, args.cmp.store.getAt(args.index).get('iconCls'))},
                    scope: that
                },{
                    text:'Open in New Window'.localize(),
                    iconCls: 'new-tab-icon',
					disabled:that.fCtxDFlag.openNT || openInNewTabFlag,
					handler:function(){that.openInNewWindow({g:that.activeGroup, h:that.activeHierarchy, n:that.selection, t:args.cmp.store.getAt(args.index).get('img_src').replace('w3s_', '')}, args.cmp.store.getAt(args.index).get('text'));},
                    scope: that
                },'-',{
                    text:'Cut'.localize(),
                    iconCls: 'cut-icon',
					disabled:that.fCtxDFlag.cut,
					handler:this.onCut,
                    scope: that
                },
				{
                    text:'Copy'.localize(),
                    iconCls: 'copy-icon',
					disabled:that.fCtxDFlag.copy,
					handler:this.onCopy,
                    scope: that
                },'-',{
                    text:'Rename'.localize(),
                    iconCls: 'rename-icon',
					disabled:that.fCtxDFlag.rename,
					handler:function(){var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem; cmp.fireEvent('edit', cmp);that._renameFlag = true;},
                    scope: that
                },{
					text:'Remove'.localize(),
					iconCls: 'delete-icon',
					disabled:that.fCtxDFlag.remove,
					handler:function(){that.remove()},
                    scope: that
                },'-',{
                    text:'Mark/Tag'.localize().concat('...'),
					id: 'tagMenu_btn',
                    iconCls: 'mark-workbook-icon',
					disabled:args.cmp.store.getAt(args.index).get('iconCls') === 'w3s_workbook' && !that.fCtxDFlag.tag? false:true,
					menu: {
						items:[],
						listeners: {
							beforeshow: function ()
							{
								if (this.loaded)
									return true;

								Jedox.backend.rpc([ that, that.showTagMenu, this, this.parentMenu.activeItem.getEl(), 'tr', this.parentMenu, args.cmp.store.getAt(args.index).get('text')], 'common', 'distinctTagged', [ 'files', 'spreadsheet' ]);

								return false;
							},
							hide: function () { this.loaded = false; }
						}
					}
                },'-',{
                    text:'Export'.localize(),
                    iconCls: 'export-bundle',
//					disabled:(args.cmp.store.getAt(args.index).get('iconCls') in that._NO_EXP),
					disabled:that.fCtxDFlag.exportBundle,
					handler: function(){
						if(that.isForBundle())
							Jedox.studio.files.bundle({t:'file', g:that.activeGroup, h:that.activeHierarchy, ns:that.getSelectedNodes(), 'name':that.getContinerName()})
						else
							Jedox.studio.files.exportFile({g:that.activeGroup, h:that.activeHierarchy, n:that.selection}, 'file');
					},
                    scope: this
                },'-',{
                    text:'Properties'.localize(),
                    iconCls: 'properties-icon',
					disabled:that.fCtxDFlag.properties,
					handler: function(){that.onProperties(that.selection, false)},
                    scope: this
                }]
            });

		if (!ieHack)
			args.e.stopEvent(); //IE bug

		menu.showAt(args.e.getXY());

		//disable contex menu when multiple items selected
		if (selectedRecords.length > 1 && this.checkIsSelected(selectedRecords, args.cmp.store.getAt(args.index))) {
			var menuItems = [0, 1, 6, 9, /*11, */13];
			for (var i = 0; i < menuItems.length; i++) {
				menu.items.items[menuItems[i]].disable();
			}
		}

    },

	getContinerName:function(){
		var records = this.getSelectedRecords();

		if(records.length == 1){

			if(records[0].data.iconCls in this._NO_EXP)
				return records[0].data.text;
		}

		return this.containerName;
	},

	isForBundle:function(){

		var records = this.getSelectedRecords();

		if(records.length == 1){

			if(records[0].data.iconCls in this._NO_EXP)
				return true;

			return false;
		}

		return true;
	},

	onContextHide : function(){
        if(this.ctxNode){
            this.ctxNode.ui.removeClass('x-node-ctx');
            this.ctxNode = null;
        }
    },

	checkIsSelected:function(selectedRecords, clickTarget){
		for (var i = 0; i<selectedRecords.length; i++){
			if (selectedRecords[i]==clickTarget)
				return true;
		}

		return false;
	},


	addMarker:function(markObj){
		var key = markObj.g.concat(markObj.h, markObj.n);
		if (!(key in Jedox.studio.app.markers))
			Jedox.studio.app.markers[key] = markObj;
	},

	onCopy:function(){
		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		if (cmp.getXType() === 'dataview'){
			var nodes = cmp.getSelectedNodes();
			this.copyRecords = cmp.getRecords(nodes);
		}
		else
			this.copyRecords = cmp.getSelectionModel().getSelections();

		if(this.copyRecords.length == 1 && !this.checkPermission(this.copyRecords, Jedox.studio.access.permType.WRITE)){ //when multiple select skip check for permission
			this.copyRecords = null;
			return;
		}

		this.onCutCopyParentNode = this.node;
	},

	checkPermission:function(records, perm){

		for(var i=0, count=records.length; i<count; i++){
			if(!(records[i].data.perm_n & perm)){
				var title = 'Warning'.localize();
				var msg = 'You have no permission for this operation'.localize();
				Jedox.studio.app.showMessageERROR(title, msg);
				return false;
			}
		}

		return true;
	},


	onCut:function(){
		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		if (cmp.getXType() === 'dataview'){
			var nodes = cmp.getSelectedNodes();
			this.cutRecords =  cmp.getRecords(nodes);
		}
		else
			this.cutRecords = cmp.getSelectionModel().getSelections();

		if(this.cutRecords.length == 1 && !this.checkPermission(this.cutRecords, Jedox.studio.access.permType.DELETE)){ //when multiple select skip check for permission
			this.cutRecords = null;
			return;
		}

		this.onCutCopyParentNode = this.node;
	},


	onPasteNEW:function(){

		var that = this;
		that.pasteAction = [];

		var removeNodes = [];
		var copyNodes = [];
		var cutNodes = [];
		var copyInSameFolderFlag = false;

		var operation;
		var pasteRecords;
		var perm; //permission to compare with (depends on action)
		var noPermsNames = [];

		if (that.cutRecords){
			pasteRecords = that.cutRecords;
			operation = 'moveNode';
			perm = Jedox.studio.access.permType.DELETE;
		}
		else if (that.copyRecords){
			pasteRecords = that.copyRecords;
			operation = 'copyNode';
			perm = Jedox.studio.access.permType.WRITE;
		}
		else
			return;



		function walkThroughtRecords(index){
			var i = index + 1 || 0;
			var BREAKflag = false;

			if (i == pasteRecords.length) {
				executePasteAction();
				return;
			}

			for (; i < pasteRecords.length; i++) {

					if(pasteRecords[i].data['perm_n'] & perm){

						for (var j = 0, count = that.wbStore.getCount(); j < count; j++) {

							if (that.wbStore.getAt(j).data.text.toLowerCase() == pasteRecords[i].data.text.toLowerCase()) {
								showQuestionDlg(pasteRecords[i], that.wbStore.getAt(j), i, walkThroughtRecords);
								BREAKflag = true;break;
							}
						}
						if (BREAKflag) break;

						var action = [pasteRecords[i].data.id, operation, that.node];
						that.pasteAction.push(action);

						if (i == pasteRecords.length - 1) {
							executePasteAction();
							return;
						}

					}
					else
						noPermsNames.push(' '.concat(pasteRecords[i].data['text']));
			}

//			executePasteAction();
		}

		function showQuestionDlg(pasteRecord, removeRecord, index, callBackFnc){
			switch (operation){
				case 'moveNode':
					showCutQuestionDlg(pasteRecord, removeRecord, index, callBackFnc)
					break;
				case 'copyNode':
					showCopyQuestionDlg(pasteRecord, removeRecord, index, callBackFnc)
					break;
			}
		}


		function showCopyQuestionDlg(copyRecord, removeRecord, index, callBackFnc){
//			console.log(operation);
			if (copyRecord != removeRecord) {

				var title = 'Confirm Item Replace'.localize();
				var message = 'replace_folder_warning_msg'.localize({
					'name': removeRecord.data.text
				});
				var fnYES = function(){


					var removeAction = [that.node, 'removeNode', removeRecord.data.id];
					var copyAction = [copyRecord.data.id, 'copyNode', that.node];
					that.pasteAction.push(removeAction, copyAction);
					callBackFnc(index);
				}
				var fnNO = function(){
					callBackFnc(index);
				}

				Jedox.studio.app.showMessageQUESTION_YN(title, message, fnYES, fnNO);
			}
			else {

				function onSuccessCbHandler(newId){

					var newName = that.getNewItemCopyName(copyRecord.data.text, copyRecord.data.iconCls);
					that.rename(newId, newName);
					copyInSameFolderFlag = true;
					callBackFnc(index);
				}

				function onErrorCbHandler(result){

				}

				(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', copyRecord.data.id, 'copyNode', that.node]))
					.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();


			}
		}

		function showCutQuestionDlg(cutRecord, removeRecord, index, callBackFnc){
//			console.log(operation);
			if (cutRecord != removeRecord) {
				var title = 'Confirm Item Replace'.localize();
				var message = 'replace_folder_warning_msg'.localize({
					'name': removeRecord.data.text
				});
				var fnYES = function(){
					var removeAction = [that.node, 'removeNode', removeRecord.data.id];
					var cutAction = [cutRecord.data.id, 'moveNode', that.node];
					that.pasteAction.push(removeAction, cutAction);
					//				removeNodePropagateInterface(removeRecord);
					//				cutNodePropagateInterface(cutRecord);
					callBackFnc(index);
				}
				var fnNO = function(){
					callBackFnc(index);
				}

				Jedox.studio.app.showMessageQUESTION_YN(title, message, fnYES, fnNO);
			}
			else {
				callBackFnc(index);
			}
		}

		function cleanClipboard(){
			that.copyRecords = null;
			that.cutRecords = null;
		}


		function propagateInterface(){
//			console.log('propagateInterface');
			Ext.getCmp('sFiles_tree_tr').fireEvent('refreshOnCopy', that.node);
//			that.initWTData(that.node, that.activeGroup, that.activeHierarchy, that._parentPerm);
		}


		function executePasteAction(){

			if (that.pasteAction.length>0){

				function onSuccessCbHandler(result){
					propagateInterface();
				}

				function onErrorCbHandler(result){

				}

				(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', that.pasteAction]))
					.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

			}

			if (copyInSameFolderFlag){
				propagateInterface();
			}

			if(noPermsNames.length > 0){
				Jedox.studio.app.showMessageERROR('Application Error'.localize(), 'paste_items_no_perms_err_msg'.localize({names:noPermsNames.toString()}));
				noPermsNames = [];
			}


			cleanClipboard();
		}


		walkThroughtRecords();
	},

	activateFilesTab:function(){
		this.filesNavigationTabPanel.setActiveTab(0);
		this.filesWSSPanel.getLayout().setActiveItem('main-view-panel');
	},

	onRename:function(){
		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		cmp.fireEvent('edit', cmp);
		this._renameFlag = true;
	},

	onProperties:function(node, cFlag){ //container Flag

		if(cFlag){
			Ext.getCmp('sFiles_tree_tr').fireEvent('onNodeProperties', node);
			return;
		}

		var that = this;

		function onSuccessCbHandler(data){
			switch (data.type){
				case 'Hyperlink':
					that.onHyperlinkProperties(node, data);
					break;
				case 'Urlplugin':
					that.onURLPluginProperties(node, data);
					break;
				case 'Frameset':
					that.onFramesetProperties(node, data);
					break;
				default:
					Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openProperties, ['file', data, this.renameHandleFnc, this.refreshHandleFnc]);
			}
		}

		function onErrorCbHandler(result){

		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'getNodePropertiesData', ['file', this.activeGroup, this.activeHierarchy, node]))
			.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();


	},


	onHyperlinkProperties:function (node, data){
		var that = this;

		var fn = function(hName, hDesc, hPath, hTarget){

			function onSuccessCbHandler(result){
				that.renameHandleFnc(hName);
			}

			function onErrorCbHandler(result){

			}

			(new Jedox.backend.RPCAsyncRqst('Studio', 'setHyperlinkPropertiesData', ['file', that.activeGroup, that.activeHierarchy, node, {
				desc: hDesc,
				target: hTarget,
				url: hPath
			}])).setOnSuccess([that, onSuccessCbHandler]).setOnError([that, onErrorCbHandler]).send();


		}

		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openProperties, ['hyperlink', data, fn, that.refreshHandleFnc]);
	},

	onURLPluginProperties:function (node, data){
		var that = this;

		var fn = function(name, desc, params){

			function onSuccessCbHandler(result){
				that.renameHandleFnc(name);
			}

			function onErrorCbHandler(result){

			}

			(new Jedox.backend.RPCAsyncRqst('Studio', 'setURLPluginPropertiesData', ['file', that.activeGroup, that.activeHierarchy, node,  desc, params]))
				.setOnSuccess([that, onSuccessCbHandler]).setOnError([that, onErrorCbHandler]).send();

		}

		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openProperties, ['urlplugin', data, fn, that.refreshHandleFnc]);
	},

	onFramesetProperties:function (node, data){
		var that = this;

		var fn = function(name, desc, frameset){

			function onSuccessCbHandler(result){
				that.renameHandleFnc(name);
			}

			function onErrorCbHandler(result){

			}

			(new Jedox.backend.RPCAsyncRqst('Studio', 'setFramesetPropertiesData', ['file', that.activeGroup, that.activeHierarchy, node,  desc, frameset]))
				.setOnSuccess([that, onSuccessCbHandler]).setOnError([that, onErrorCbHandler]).send();

		}

		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openProperties, ['frameset', data, fn, that.refreshHandleFnc]);
	},


	validateName:function(value, iconCls){

		var that = this;
		var id = this.selection;
		var oldName = this.activeRecord.data.text;
		var _return = true;

		//name changed validation
		if (oldName != value) {
			if(oldName.toLowerCase() == value.toLowerCase())
				return _return;
			//name length validation
			if (value.length < 64) {
				//char validation
				/*
				var my_regexp = /^[a-zA-Z0-9_\-=+][a-zA-Z0-9_\-@\.,\()\ ]*$/;
				if (!(my_regexp.test(value))) {
					showErrMsg('Error Renaming File or Folder'.localize(), 'rename_item_format_err_msg'.localize({'new_name':value}));
					_return = false;
				}
				*/

				//name exist validation
				this.wbStore.each(function(record){
					if (record.data.text.toLowerCase() == value.toLowerCase() && (iconCls && iconCls == record.data.iconCls)) {
						showErrMsg('Error Renaming File or Folder'.localize(), 'rename_item_error_msg'.localize({'old_name':oldName, 'new_name':value}));
						_return = false;
					}
				}, [this]);

			}
			else {
				showErrMsg('Error Renaming File or Folder'.localize(), 'rename_item_long_error_msg'.localize({'old_name':oldName, 'new_name':value}));
				_return = false;
			}
		}
		else {
			_return = false;
		}



		function showErrMsg(title, msg){
			var fn = function(){
				var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
				cmp.fireEvent('edit', cmp);
			}
			Jedox.studio.app.showMessageQUESTIONERROR(title, msg, fn);
		}

		return _return;
	},


	trim:function(s){
		return s.replace(/^\s+|\s+$/g, '');
	},

	disableTlb:function(){
		this.fTlb.disable();
	},

	enableTlb:function(){
		if (this.fTlb.disabled)
			this.fTlb.enable();
	},

	getWSSURL:function(g, h, n, t){
		var page = '/ui/wss/index.php?',
			wb = n,
			grp = g,
			hrc = h,
			getParams = Ext.urlDecode(window.location.href.split('?', 2)[1]),
			ntype = t;

		if (this.activeRecord)
			ntype = this.activeRecord.get('iconCls').split('_').pop();

		var url = Ext.urlAppend(page.concat('wam=designer&wb=', wb, '&grp=', grp, '&hrc=', hrc, (ntype ? '&ntype='.concat(ntype) : '')), Ext.urlEncode(getParams));
//		console.log(url);
		return url;
	},


	/* There are several cases that might occur depends on parameters
	 *
	 * 1. from Palo BI Suite on dblClick (id)
	 * 2. open WB from WSS (id, ghn, name)
	 * 3. new WB form WSS (id, ghn, name) (id = name and ghn={g:'nn', h:'nn', n:name})
	 *
	 */


	openWB: function(id, w3s_data){ //ghn={g:group, h:hierarchy, n:node}

		var that = this;

		function sessOKClbFnc(id, w3s_data){

			that.activateFlag = false;

			var title = w3s_data? w3s_data.title? w3s_data.title:w3s_data.name : that.findById(id);


			if (!w3s_data)
				var w3s_data = {
					group:that.activeGroup,
					hierarchy:that.activeHierarchy,
					node:id,
					type:that.getTypeById(id),
					name:title,
					close_trigger:false, // close from wss
					open_trigger:false, // open from wss
					switch_trigger:false, // switch from wss
					loaded:false //already loaded
				}

			var tab_uid = that.getTabUID(w3s_data.group, w3s_data.hierarchy, w3s_data.node);

			function showWBTab(tabid){
				if (!NWtab) {
					var NWtab = new Ext.Panel({
						id: tabid,
						uid:tab_uid,
						title: title,
						layout: 'fit',
						bodyStyle: 'border-left:1; border-right:1; border-top:none; border-bottom:1;',
						header: false,
						//tabTip: 'Add New User',
						closable: true,
						minimizable: true,
						border: true,
						group:w3s_data.group,
						hierarchy:w3s_data.hierarchy,
						node:w3s_data.node,
						w3s_data:w3s_data,
						type:'wss',
						listeners: {
							beforeclose: function(panel){
							/*
							 * this event occures only when click on tab close with mouse and if that tab is not active than activate, but not close
							 * WSS trigger will call remove tab and that will trigger desroy event nad kill tab...
							 *
							 */
	//							that._beforeCloseTriggerFlag = true; //flag needed for handling close trigger from wss

								var files = Jedox.studio.frames.files;

								if (files && files.Jedox.wss.app.environment && (files.Jedox.wss.app.environment.inputMode == files.Jedox.wss.grid.GridMode.DIALOG || files.Jedox.wss.general.switchSuspendModeAlert)){
									Jedox.studio.app.showMessageERROR('Warrning', files.Jedox.wss.general.switchSuspendModeAlert? 'wb_in_suspend_mode'.localize():'wb_in_dlg_mode'.localize());
									return false;
								}


						 		var ghn = {
									g: this.w3s_data.group,
									h: this.w3s_data.hierarchy,
									n: this.w3s_data.node
								}

							 	if (that.filesNavigationTabPanel.getActiveTab() != panel){
									if (ghn.g == 'nn' && ghn.h == 'nn')  //new and imported workbooks that are not saved
										Jedox.studio.frames.files.Jedox.wss.wnd.closeByMeta(this.w3s_data.name);
									else
										Jedox.studio.frames.files.Jedox.wss.wnd.closeByMeta(this.w3s_data.name, ghn);

									return false;
								}

							 	if (files.Jedox.wss.wnd.active)
							 		files.Jedox.wss.wnd.active.unload();

								return false;
							},
							beforedestroy: function(panel){
								if (this.w3s_data.close_trigger)
									return true;
							},
							destroy : function(panel) {

								delete that.wssRegistar[this.uid];

								if (that.filesNavigationTabPanel.items.items.length == 1) {
									that.filesNavigationTabPanel.setActiveTab(0);
									that.filesWSSPanel.getLayout().setActiveItem('main-view-panel');
								}
								else {
									switch (that.filesNavigationTabPanel.getActiveTab().type) {
										case 'hyperlink':
											that.filesWSSPanel.getLayout().setActiveItem(2);
											break;
										case 'static':
											that.filesWSSPanel.getLayout().setActiveItem(3);
											break;
										case 'wss':
											break;
										default:
											that.filesNavigationTabPanel.setActiveTab(0);
											that.filesWSSPanel.getLayout().setActiveItem('main-view-panel');
											break;
									}
								}
							},
							beforehide: function(panel){
								if (that.filesNavigationTabPanel.getActiveTab() == that.filesNavigationTabPanel.getComponent(0))
									that.filesWSSPanel.getLayout().setActiveItem('main-view-panel');
							},
							activate:function(panel){
								if (that._currentTab) {// if modal Dlg is opened in this tab
									that.filesWSSPanel.getLayout().setActiveItem(1);
									return true;
								}

								if (this.w3s_data.open_trigger){
									that.filesWSSPanel.getLayout().setActiveItem(1);
									this.w3s_data.open_trigger = false;
									this.w3s_data.loaded = true;
									return true;
								}

								if (this.w3s_data.switch_trigger){
									that.filesWSSPanel.getLayout().setActiveItem(1);
									this.w3s_data.switch_trigger = false;
									return true;
								}

								if (that.activateFlag) { // WSS is loaded in Studio
									that.filesWSSPanel.getLayout().setActiveItem(1);
									if (this.w3s_data.loaded) {
										var ghn = {
											g: this.w3s_data.group,
											h: this.w3s_data.hierarchy,
											n: this.w3s_data.node
										}

										if (ghn.g == 'nn' && ghn.h == 'nn')
											ghn = null;

										Jedox.studio.frames.files.Jedox.wss.wnd.selectByMeta(this.w3s_data.name, ghn);
									}
									else {
	//									Jedox.studio.frames.files.Jedox.wss.book.load(null, this.w3s_data.node, this.w3s_data.group, this.w3s_data.hierarchy);
										Jedox.studio.frames.files.Jedox.wss.node.load(null, this.w3s_data.type, this.w3s_data.node, this.w3s_data.group, this.w3s_data.hierarchy);
										this.w3s_data.loaded = true;
									}
								}
								else { //first time WSS loading in Studio
									if (Jedox.studio.frames.files) { // when activate tab
										that.filesWSSPanel.getLayout().setActiveItem(1);
									}
									else
										this.w3s_data.loaded = true;
								}
							}
						}
					});
					that.filesNavigationTabPanel.add(NWtab);
					//add to registar
					if (!(tab_uid in that.wssRegistar))
						that.wssRegistar[tab_uid] = NWtab.id;
				}

				NWtab.show();
				that.filesNavigationTabPanel.setActiveTab(NWtab);
			}

			if (!Jedox.studio.frames.files){
				Ext.MessageBox.show( {
					title : "Palo Suite".localize(),
					msg: "wss_open_wait".localize(),
					closable : false,
					icon : 'largeLoadingImage'
				});
				showWBTab();
				that.wss = {
					xtype: 'iframepanel',
					id: 'wssframe-designer-mode',
					border: false,
					frameStyle: {
						overflow:'hidden'
						},
					defaultSrc: that.getWSSURL(w3s_data.group, w3s_data.hierarchy, id, w3s_data.type),
					listeners: {
						documentloaded :function(){

							var index = -1;

							for(var i = 0, count = frames.length; i < count; i++){
								if (frames[i].name == 'wssframe-designer-mode') {
									index = i;
									break;
								}
							}

							if(index != -1){
								Jedox.studio.frames.files = frames[index];
								Jedox.studio.frames.files.Jedox.wss.events.registerPlugin(new Jedox.studio.plugin.WSSPluginFiles());
							}

							Ext.MessageBox.hide();
						},
						resize: function()
						{
							if (Ext.isGecko)
								setTimeout(function ()
								{
									if (Jedox.studio.frames.files)
										Jedox.studio.frames.files.Ext.dd.DragDropMgr._onResize();
								}, 0);
						}
					}
				}

				that.wssPanel.add(that.wss);
				that.filesWSSPanel.getLayout().setActiveItem(1);
				that.filesWSSPanel.getLayout().activeItem.getLayout().setActiveItem(0);
			}
			else {
				//files already exist
				that.activateFlag = true;
				showWBTab((tab_uid in that.wssRegistar)? that.wssRegistar[tab_uid]:Ext.id());
			}

		}

		//check if session is valid
		this.verifySession([this, sessOKClbFnc, id, w3s_data]);

	},

	getHyperlinkURL:function(g, h, n, successClbFnc){

		function onSuccessCbHandler(result){
			successClbFnc(result);
		}

		function onErrorCbHandler(result){

		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'getHyperlinkURL', ['file', g, h, n]))
			.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

	},

	getURLPluginURL:function(g, h, n, successClbFnc){

		function onSuccessCbHandler(result){
			successClbFnc(result);
		}

		function onErrorCbHandler(result){

		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'getURLPluginURL', ['file', g, h, n]))
			.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();


	},

	getStaticURL:function(g, h, n, name){
//		return '/be/studio/static.php/?t=file&g='.concat(g, '&h=', h, '&n=', n);
		return '/be/studio/static.php/'.concat(escape(name), '?t=file&g=', g, '&h=', h, '&n=', n);
	},

	getHyperlinkTabID:function(g, h, n){
		var tabID =  g.concat('-', h, '-', n, '-hyperlink');
		return tabID;
	},


	getStaticTabID:function(g, h, n){
		var tabID =  g.concat('-', h, '-', n, '-static');
		return tabID;
	},


	openHyperlink:function(id, hyperlink_data){
		var that = this;

		var hyperlink_data = hyperlink_data;

		if (!hyperlink_data)
			that.isURLPlugin(id) ? that.getURLPluginURL(that.activeGroup, that.activeHierarchy, id, urlDataCb) : that.getHyperlinkURL(that.activeGroup, that.activeHierarchy, id, urlDataCb);
		else
			continueOpenHyperlink();



		function urlDataCb(urlData){

			hyperlink_data = {
				group: that.activeGroup,
				hierarchy: that.activeHierarchy,
				node: id,
				name: that.findById(id),
				urlData:urlData,
				hyperlinkID: that.getHyperlinkTabID(that.activeGroup, that.activeHierarchy, id),
				frameID: that.getHyperlinkTabID(that.activeGroup, that.activeHierarchy, id) + '-frame',
				urlPlugin: that.isURLPlugin(id)
			}

			continueOpenHyperlink();
		}

		function continueOpenHyperlink(){

			if (hyperlink_data.urlData.target == 'blank') {
				that.openInNewWindow({g:hyperlink_data.group, h:hyperlink_data.hierarchy, n:id, t:hyperlink_data.urlPlugin? 'ahview':'hyperlink'}, hyperlink_data.name);
				return;
			}


			function showHiperlinkTab(newFlag){
				if (newFlag) {
					var NWtab = new Ext.Panel({
						id: hyperlink_data.hyperlinkID,
						title: hyperlink_data.name,
						layout: 'fit',
						bodyStyle: 'border-left:1; border-right:1; border-top:none; border-bottom:1;',
						header: false,
						closable: true,
						minimizable: true,
						border: true,
						type:'hyperlink',
						hyperlink_data:hyperlink_data,
						listeners: {
							destroy : function(panel) {
								Ext.getCmp(that.hyperlinkRegistar[this.id]).destroy();
								that.hyperlinkPanel.remove(that.hyperlinkRegistar[this.id]);
								delete that.hyperlinkRegistar[this.id];
							},
							beforehide: function(panel){
								if (that.filesNavigationTabPanel.getActiveTab() == that.filesNavigationTabPanel.getComponent(0))
									that.filesWSSPanel.getLayout().setActiveItem('main-view-panel');
							},
							activate:function(panel){
								that.filesWSSPanel.getLayout().setActiveItem(2);
								if (this.opened)
									that.filesWSSPanel.getLayout().activeItem.getLayout().setActiveItem(that.hyperlinkRegistar[this.id]);
								else
									this.opened = true;
							}
						}
					});

					that.filesNavigationTabPanel.add(NWtab);
				}
				Ext.getCmp(hyperlink_data.hyperlinkID).show();
				that.filesNavigationTabPanel.setActiveTab(Ext.getCmp(hyperlink_data.hyperlinkID));
			}


			if (hyperlink_data.hyperlinkID in that.hyperlinkRegistar){

				showHiperlinkTab(false);
			}
			else {

				showHiperlinkTab(true);
				var loaded = false;

				Ext.MessageBox.show( {
					title : "Palo Suite".localize(),
					msg: hyperlink_data.urlPlugin? "wss_openpivot_wait".localize() : "wss_openhl_wait".localize(),
					closable : false,
					buttons: Ext.Msg.CANCEL,
					icon : 'largeLoadingImage',
					fn: function(){
						that.closeUnloadedTab();
					}
				});

				// if not loaded in _tms close messagebox
				setTimeout(function(){
					if(!loaded){
						Ext.MessageBox.hide();
					}
				}, that._tms);

				var hyperlinkIFrame = {
					xtype: 'iframepanel',
					id: hyperlink_data.frameID,
					border: false,
					defaultSrc:hyperlink_data.urlData.url,
					listeners: {
						documentloaded :function(){
							loaded = true;
							Ext.MessageBox.hide();
						}
					}
				};

				that.hyperlinkPanel.add(hyperlinkIFrame);
				that.hyperlinkRegistar[hyperlink_data.hyperlinkID] = hyperlink_data.frameID;
				that.filesWSSPanel.getLayout().setActiveItem(2);
				that.filesWSSPanel.getLayout().activeItem.getLayout().setActiveItem(that.hyperlinkRegistar[hyperlink_data.hyperlinkID]);
			}
		}
	},

	closeUnloadedTab:function(){
		var tab = this.filesNavigationTabPanel.getActiveTab();

		if (tab){
			this.filesNavigationTabPanel.remove(tab);
		}
	},

	getStaticReg:function(key){
		return this.staticRegistar[key];
	},

	openStatic:function(id, static_data){

		var that = this;

		if (!static_data)
			var static_data = {
				group:that.activeGroup,
				hierarchy:that.activeHierarchy,
				node:id,
				name:that.findById(id),
				type:that.activeRecord.get('iconCls').split('_').pop(),
				url:that.getStaticURL(that.activeGroup, that.activeHierarchy, id, that.findById(id)),
				staticID:that.getStaticTabID(that.activeGroup, that.activeHierarchy, id),
				frameID:that.getStaticTabID(that.activeGroup, that.activeHierarchy, id) + '-frame'
			}

		if(!(Jedox.wss.app.fileTypesReg[static_data.type])){
			Jedox.studio.files.exportFile({g: static_data.group, h: static_data.hierarchy, n: static_data.node}, 'file');
			return;
		}

		function showStaticTab(newFlag){
			if (newFlag) {
				var NWtab = new Ext.Panel({
					id: static_data.staticID,
					title: static_data.name,
					layout: 'fit',
					bodyStyle: 'border-left:1; border-right:1; border-top:none; border-bottom:1;',
					header: false,
					closable: true,
					minimizable: true,
					border: true,
					opened:false,
					static_data:static_data,
					type:'static',
					listeners: {
						destroy : function(panel) {
							Ext.getCmp(that.staticRegistar[this.id]).destroy();
							that.staticPanel.remove(that.staticRegistar[this.id]);
							delete that.staticRegistar[this.id];
						},
						beforehide: function(panel){
							if (that.filesNavigationTabPanel.getActiveTab() == that.filesNavigationTabPanel.getComponent(0))
								that.filesWSSPanel.getLayout().setActiveItem('main-view-panel');
						},
						activate:function(panel){
								that.filesWSSPanel.getLayout().setActiveItem(3);
								if (this.opened)
									that.filesWSSPanel.getLayout().activeItem.getLayout().setActiveItem(that.staticRegistar[this.id]);
								else
									this.opened = true;

						}
					}
				});

				that.filesNavigationTabPanel.add(NWtab);
			}

			Ext.getCmp(static_data.staticID).show();
			that.filesNavigationTabPanel.setActiveTab(Ext.getCmp(static_data.staticID));
		}


		if (static_data.staticID in that.staticRegistar){

			showStaticTab(false);
		}
		else {

			showStaticTab(true);

			var staticIFrame = {
				xtype: 'iframepanel',
				id: static_data.frameID,
				border: false,
				defaultSrc:static_data.url,
				listeners: {
					documentloaded :function(){
//						console.log('loaded');
//						that.addRecent(static_data, 'static', static_data.type);
					}
				}
			};
			that.staticPanel.add(staticIFrame);
			that.staticRegistar[static_data.staticID] = static_data.frameID;
			that.filesWSSPanel.getLayout().setActiveItem(3);
			that.filesWSSPanel.getLayout().activeItem.getLayout().setActiveItem(that.staticRegistar[static_data.staticID]);
		}
	},


	openHyperlinkURLFromWSS:function(urlData){

		var that = this;
		if (urlData.target == '_blank') {
			window.open(urlData.url ,"_blank");
			return;
		}
		var hyperlinkID = urlData.url.concat('-hyperlink');
		var frameID = hyperlinkID + '-frame';
		var title = urlData.title;

		function showHiperlinkTab(newFlag){
			if (newFlag) {
				var NWtab = new Ext.Panel({
					id: hyperlinkID,
					title: title,
					layout: 'fit',
					bodyStyle: 'border-left:1; border-right:1; border-top:none; border-bottom:1;',
					header: false,
					closable: true,
					minimizable: true,
					border: true,
					type:'hyperlink',
					listeners: {
						destroy : function(panel) {
							Ext.getCmp(that.hyperlinkRegistar[this.id]).destroy();
							that.hyperlinkPanel.remove(that.hyperlinkRegistar[this.id]);
							delete that.hyperlinkRegistar[this.id];
						},
						beforehide: function(panel){
							if (that.filesNavigationTabPanel.getActiveTab() == that.filesNavigationTabPanel.getComponent(0))
								that.filesWSSPanel.getLayout().setActiveItem('main-view-panel');
						},
						activate:function(panel){
							that.filesWSSPanel.getLayout().setActiveItem(2);
							if (this.opened)
								that.filesWSSPanel.getLayout().activeItem.getLayout().setActiveItem(that.hyperlinkRegistar[this.id]);
							else
								this.opened = true;
						}
					}
				});

				that.filesNavigationTabPanel.add(NWtab);
			}
			Ext.getCmp(hyperlinkID).show();
			that.filesNavigationTabPanel.setActiveTab(Ext.getCmp(hyperlinkID));
		}


		if (hyperlinkID in that.hyperlinkRegistar){

			showHiperlinkTab(false);
		}
		else {

			showHiperlinkTab(true);

			var hyperlinkIFrame = {
				xtype: 'iframepanel',
				id: frameID,
				border: false,
				defaultSrc:urlData.url,
				listeners: {
					documentloaded :function(){
//						console.log('loaded');
					}
				}
			};

			that.hyperlinkPanel.add(hyperlinkIFrame);
			that.hyperlinkRegistar[hyperlinkID] = frameID;
			that.filesWSSPanel.getLayout().setActiveItem(2);
			that.filesWSSPanel.getLayout().activeItem.getLayout().setActiveItem(that.hyperlinkRegistar[hyperlinkID]);
		}
	},

	verifySession:function(cb){

		function onSuccessCbHandler(result){
			if(!result){
				var title = 'Logout'.localize();
				var msg = 'session_expired'.localize();
				var callBackFnc = function(){
					window.location.href = '/ui/login/?r';
				}

				Jedox.studio.app.showMessageQUESTIONERROR(title, msg, callBackFnc);
			}
			else{
				if (cb instanceof Array && cb.length > 1)
					cb[1].apply(cb[0], cb.slice(2));
			}
		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'verifySess', []))
			.setOnSuccess([this, onSuccessCbHandler]).send();

	},


	openInNewWindow:function(ghnt, name) {
		// Change "_blank" to something like "newWindow" to load all links in the same new window

		var that = this;

		switch (ghnt.t){
			case 'workbook':
			case 'frameset':
				//check if session is valid
				this.verifySession([this, function(ghnt, name){window.open(that.getWSSURL(ghnt.g, ghnt.h, ghnt.n, ghnt.t) ,"_blank");}, ghnt, name]);
				break;
			case 'hyperlink':
				this.getHyperlinkURL(ghnt.g, ghnt.h, ghnt.n, function(urlData){window.open(urlData.url ,"_blank");});
				break;
			case 'ahview':
				this.getURLPluginURL(ghnt.g, ghnt.h, ghnt.n, function(urlData){window.open(urlData.url ,"_blank");});
				break;
			default :
				window.open(this.getStaticURL(ghnt.g, ghnt.h, ghnt.n, name) ,"_blank");
				break;
		}

	},



	//retain focus on files after tab switch to files for keyboard events
	setFilesFocus:function(index){

		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		var index = index || this.getSelectedIndex();

		if (index && index != -1) {
			if (cmp.getXType() === 'dataview') {
				cmp.select(index);
				cmp.fireEvent('click', cmp, index);
				cmp.retainFocus();
			}
			else {
				cmp.fireEvent('rowclick', cmp, index);
				cmp.getSelectionModel().selectRow(index);
				cmp.getView().focusEl.focus();
			}
		}
	},



	editWB:function(group, hierarchy, n, NOTopenFlag){

	/**
	 * expand files tab
	 * select group
	 * init hierarchy
	 * expand parent node
	 * do click on parent on left
	 * select file on right
	 * open in new tab wss...
	 */
        //do select where ever he is

		for (var i = 0; i < this.wbStore.getCount(); i++)
			if (this.wbStore.getAt(i).get('id') == n) {
				this.setFilesFocus(i);
				break;
			}

		if (!NOTopenFlag)
			this.openWB(n);

	},

	getTabUID:function(group, hierarchy, node){
		return group.concat('-', hierarchy, '-', node);
	},

	getDefaultW3S_data:function(ghn, name){
		var wss = {
			group:ghn.g,
			hierarchy:ghn.h,
			node:ghn.n,
			type:ghn.t? ghn.t:'workbook',
			name:name,
			close_trigger:false,
			open_trigger:false,
			switch_trigger:false,
			loaded:false
		}

		return wss;
	},

	getDefaultStatic_data:function(ghnt, name){
		var that = this;
		var static_data = {
			group:ghnt.g,
			hierarchy:ghnt.h,
			node:ghnt.n,
			name:name,
			type:ghnt.t,
			path:ghnt.p || null,
			url:that.getStaticURL(ghnt.g, ghnt.h, ghnt.n, name),
			staticID:that.getStaticTabID(ghnt.g, ghnt.h, ghnt.n),
			frameID:that.getStaticTabID(ghnt.g, ghnt.h, ghnt.n) + '-frame'
		}

		return static_data;
	},

	getDefaultHyperlink_data:function(ghnt, name, cb){
		var that = this;

		function urlDataCb(urlData){

			var hyperlink_data = {
				group:ghnt.g,
				hierarchy:ghnt.h,
				node:ghnt.n,
				name:name,
				type:ghnt.t,
				path:ghnt.p || null,
				urlData:urlData,
				hyperlinkID:that.getHyperlinkTabID(ghnt.g, ghnt.h, ghnt.n),
				frameID:that.getHyperlinkTabID(ghnt.g, ghnt.h, ghnt.n) + '-frame',
				urlPlugin:ghnt.t == 'ahview'? true:false
			}

			cb(hyperlink_data);
		}

		if(ghnt.t == 'ahview')
			that.getURLPluginURL(ghnt.g, ghnt.h, ghnt.n, urlDataCb);
		else
			that.getHyperlinkURL(ghnt.g, ghnt.h, ghnt.n, urlDataCb);

	},



	/**
	 * WSS Triggers function
	 */


	openRecent:function(ghntp, name, type){

		var that = this;
		var data;

		switch(type){
			case 'spreadsheet':
			case 'frameset':
				var w3s_data = this.getDefaultW3S_data(ghntp, name);
				this.openWB(ghntp.n, w3s_data);
				break;
			case 'static':
				var static_data = this.getDefaultStatic_data(ghntp, name);
				this.openStatic(ghntp.n, static_data);
				break;
			case 'hyperlink':
				this.getDefaultHyperlink_data(ghntp, name, function (hyperlink_data){that.openHyperlink(ghntp.n, hyperlink_data);});
				break;
			default:
				break;
		}
	},

	triggerOpenWB_beforeFromWSS:function(ghn, name){

		function onSuccessCbHandler(perm){
			if ((perm == -1)){
				throw 'follHLInvalidRng'.localize();
			}
		}

		function onErrorCbHandler(result){

		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'getNodePermission', [ghn.g, ghn.h, ghn.n]))
			.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

	},

	triggerOpenWBFromWSS:function(ghn, name){

		var w3s_data = this.getDefaultW3S_data(ghn, name);
		w3s_data.open_trigger = true;
		this.openWB(ghn.n, w3s_data);
	},

	triggerCloseWBFromWSS:function(ghn, name){

		if (this._beforeCloseTriggerFlag && !this._triggerSaveAsFromWSSFlag){
			this._beforeCloseTriggerFlag = !this._beforeCloseTriggerFlag;
			return;
		}

		if (ghn)
			var tab_uid = this.getTabUID(ghn.g, ghn.h, ghn.n);
		else
			var tab_uid = this.getTabUID('nn', 'nn', name);

		var tab = this.filesNavigationTabPanel.getComponent(this.resolveWSSTabID(tab_uid));

		if (tab){
			tab.w3s_data.close_trigger = true;
			this.filesNavigationTabPanel.remove(tab);
		}
	},

	triggerSwitchWBFromWSS:function(ghn, name){
		if (!ghn)
			var ghn={g:'nn', h:'nn', n:name}

		var tab_uid = this.getTabUID(ghn.g, ghn.h, ghn.n);
		var tab = this.filesNavigationTabPanel.getComponent(this.resolveWSSTabID(tab_uid));

		if (tab && tab != this.filesNavigationTabPanel.getActiveTab()){
			tab.w3s_data.switch_trigger = true;
			this.filesNavigationTabPanel.activate(tab);
		}
	},

	triggerNewWBFromWSS:function(name){
		var ghn = {g:'nn', h:'nn', n:name};
		var w3s_data = this.getDefaultW3S_data(ghn, name);
		w3s_data.open_trigger = true;
//		w3s_data.title = name.concat(' (NEW)');
		this.openWB(ghn.n, w3s_data);
	},


	triggerSaveAsFromWSS:function(ghn, oldName, name){
//		console.log(ghn);
		this._triggerSaveAsFromWSSFlag = true;
		Jedox.studio.app.resourcesRefreshFlag = true;
		this._ghn = ghn;
//		this.triggerCloseWBFromWSS(null, oldName);

		var tab = this.filesNavigationTabPanel.getActiveTab();
		if (tab){
			tab.w3s_data.close_trigger = true;
			this.filesNavigationTabPanel.remove(tab);
		}

		this.triggerOpenWBFromWSS(ghn, name);
		this._triggerSaveAsFromWSSFlag = false;
		Jedox.studio.frames.files.Jedox.wss.wnd.selectByMeta(name, ghn);
	},


	triggerHideWBFromWSS:function(ghn, name){
		if (!ghn)
			var ghn={g:'nn', h:'nn', n:name}

		var tab_uid = this.getTabUID(ghn.g, ghn.h, ghn.n);
		var tab = this.filesNavigationTabPanel.getComponent(this.resolveWSSTabID(tab_uid));
		tab.setTitle(tab.title + ' - hidden');
		tab.disabled=true;
	},

	triggerUnhideWBFromWSS:function(ghn, name){
		if (!ghn)
			var ghn={g:'nn', h:'nn', n:name}

		var tab_uid = this.getTabUID(ghn.g, ghn.h, ghn.n);
		var tab = this.filesNavigationTabPanel.getComponent(this.resolveWSSTabID(tab_uid));
		tab.setTitle(tab.title.replace(' - hidden', '' ));
		tab.disabled=false;
	},

	triggerImportWBFromWSS:function(name){
		var ghn = {g:'nn', h:'nn', n:name};
		var w3s_data = this.getDefaultW3S_data(ghn, name);
		w3s_data.open_trigger = true;
//		w3s_data.title = name.concat(' (IMPORT)');
		this.openWB(ghn.n, w3s_data);
	},


	triggerOpenURLFromWSS:function(url, title, target){

		var urlData = {url:url, title:title, target:target};
		this.openHyperlinkURLFromWSS(urlData);
	},

	triggerOpenStaticFromWSS:function(ghnt, target, chkACLs){

		var that = this;

		if(chkACLs)
			this.triggerOpenWB_beforeFromWSS(ghnt);

		var wssStudioHandler = {
			getNodeName: function(name){

				if (!name) {
					//show feedback
					return false;
				}

				switch (target){
					case '_new':
						if (ghnt.t == 'hyperlink' || ghnt.t == 'ahview'){
							that.getDefaultHyperlink_data(ghnt, name, function (hyperlink_data){that.openHyperlink(ghnt.n, hyperlink_data);});
						}
						else {
							var static_data = that.getDefaultStatic_data(ghnt, name);
							that.openStatic(ghnt.n, static_data);
						}
						break;
					case '_blank':
						that.openInNewWindow(ghnt, name);
						break;
					case '_export':
						Jedox.studio.files.exportFile({g: ghnt.g, h: ghnt.h, n: ghnt.n}, 'file');
						break;
				}

			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.getNodeName(ghnt.g, ghnt.h, ghnt.n);
	},

	triggerReplaceNodeFromWSS:function(oldGhn, newGhn, newName){

		var old_tab_uid = this.getTabUID(oldGhn.g, oldGhn.h, oldGhn.n);
		var new_tab_uid = this.getTabUID(newGhn.g, newGhn.h, newGhn.n);
		var tab = this.filesNavigationTabPanel.getComponent(this.resolveWSSTabID(old_tab_uid));

		tab.uid = new_tab_uid;
		tab.w3s_data['group'] = tab.group = newGhn.g;
		tab.w3s_data['hierarchy'] = tab.hierarchy = newGhn.h;
		tab.w3s_data['node'] = tab.node = newGhn.n;
		tab.w3s_data['name'] = newName;
		tab.w3s_data['loaded'] = true;

		this.wssRegistar[new_tab_uid] = this.wssRegistar[old_tab_uid];
		delete this.wssRegistar[old_tab_uid];

		tab.setTitle(newName);

	},


	resolveWSSTabID:function(uid){
		if(uid in this.wssRegistar)
			return this.wssRegistar[uid];

		return false;
	},

	/**
	 * Set interface permissions
	 */

	clearAllSelections:function(){
		Ext.getCmp('sFiles_mainList_dv').clearSelections();
		Ext.getCmp('main-thumbnails-view').clearSelections();
		Ext.getCmp('main-details-view').getSelectionModel().clearSelections();

		this.setNoSelectionInterface();
	},

	setNoSelectionInterface:function(){
		this.fTlb.items.items[1].disable();
	},

	setUpTlbBtnState:function(state){
		var tlbBtns = this.fTlb.items.items;
		state ? tlbBtns[7].enable():tlbBtns[7].disable(); //up tlb btn
	},

	setContainerInterfacePermission:function(parentPerm){

		var permType = Jedox.studio.access.permType;

		var tlbBtns = this.fTlb.items.items;

		!(parentPerm & permType.WRITE)? tlbBtns[0].disable():tlbBtns[0].enable(); //new tlb btn
		tlbBtns[1].disable(); //remove tlb btn always disable when no selection
		!(parentPerm & permType.WRITE)? tlbBtns[3].disable():tlbBtns[3].enable(); //import tlb btn
		!(parentPerm & permType.WRITE)? tlbBtns[5].disable():tlbBtns[5].enable(); //import tlb btn

		this.fCtxDFlag.c_paste = this.fCtxDFlag.c_new = this.fCtxDFlag.c_properties = this.fCtxDFlag.c_importBundle = !(parentPerm & permType.WRITE);

	},

	getMultipleSelectedRecords:function(){

		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		if (cmp.getXType() === 'dataview'){
			var nodes = cmp.getSelectedNodes();
			var selectedRecords = cmp.getRecords(nodes);
		}
		else
			var selectedRecords = cmp.getSelectionModel().getSelections();

		return selectedRecords;
	},

	setInterfacePermission:function(nodePerm){

		var permType = Jedox.studio.access.permType;
		var multipleSelectedRecords = this.getMultipleSelectedRecords();

		var nodePerm = multipleSelectedRecords.length == 1 ? multipleSelectedRecords[0].get('perm_n'):false;  // if false multiple selection

		if(nodePerm){
			!(nodePerm & permType.DELETE)? this.fTlb.items.items[1].disable():this.fTlb.items.items[1].enable(); //remove tlb btn
			this.fCtxDFlag.openNT = !(this._parentPerm & permType.WRITE);
			this.fCtxDFlag.cut = !(nodePerm & permType.DELETE);
			this.fCtxDFlag.copy = !(nodePerm & permType.WRITE);
			this.fCtxDFlag.rename = !(nodePerm & permType.WRITE);
			this.fCtxDFlag.remove = !(nodePerm & permType.DELETE);
			this.fCtxDFlag.properties = !(nodePerm & permType.WRITE);
			this.fCtxDFlag.tag = !(nodePerm & permType.WRITE);
			this.fCtxDFlag.exportBundle = !(nodePerm & permType.WRITE);
		}
		else {
			//multiselection
				this.enableTlb();
				this.resetInterfacePermission();
				this.fCtxDFlag.cut = this.fCtxDFlag.remove = this.fCtxDFlag.copy = true;

				for(var i=0, count=multipleSelectedRecords.length, permType=Jedox.studio.access.permType; i<count; i++){
					if (this.fCtxDFlag.cut && this.fCtxDFlag.remove && multipleSelectedRecords[i].get('perm_n') & permType.DELETE) {
						this.fCtxDFlag.cut = this.fCtxDFlag.remove = false;
					}
					if (this.fCtxDFlag.copy && multipleSelectedRecords[i].get('perm_n') & permType.WRITE) {
						this.fCtxDFlag.copy = false;
					}

					if (this.fCtxDFlag.exportBundle && multipleSelectedRecords[i].get('perm_n') & permType.WRITE) {
						this.fCtxDFlag.exportBundle = false;
					}
				}

				this.fCtxDFlag.remove? this.fTlb.items.items[1].disable():this.fTlb.items.items[1].enable();
		}

	},


	resetInterfacePermission:function(){

			this.enableTlb();
			this.fCtxDFlag.open = false;
			this.fCtxDFlag.openNT = false;
			this.fCtxDFlag.cut = false;
			this.fCtxDFlag.copy = false;
			this.fCtxDFlag.rename = false;
			this.fCtxDFlag.remove = false;
			this.fCtxDFlag.properties = false;
			this.fCtxDFlag.tag = false;
	},


	setInputMode:function(){
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_content_FILES;
	},


	moveSelection:function(operation){

		var that = this;
		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		var storeCount = cmp.store.getCount();
		if (storeCount == 0)
			return;
		var selectedIndex = that.getSelectedIndex();
			selectedIndex = selectedIndex == -1 ? 0:selectedIndex;

		switch (operation){
			case 'UP':
				selectedIndex==0? selectedIndex=storeCount-1:selectedIndex -=1;
				break;
			case 'DOWN':
				selectedIndex==storeCount-1? selectedIndex=0:selectedIndex +=1;
				break;
		}

		if (cmp.getXType() === 'dataview'){
			cmp.select(selectedIndex);
			cmp.fireEvent('click', cmp, selectedIndex, cmp.getNode(selectedIndex));
		}
		else{
			cmp.getSelectionModel().selectRow(selectedIndex);
			cmp.fireEvent('rowclick', cmp, selectedIndex);
		}

	},

	onScroll:function(operation){
		var that = this;
		var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;
		var storeCount = cmp.store.getCount();

		switch (operation){
			case 'UP':
				that.selectedIndex=0;
				break;
			case 'DOWN':
				that.selectedIndex=storeCount-1;
				break;
		}

		if (cmp.getXType() === 'dataview') {
			cmp.select(that.selectedIndex);

			var nodeEl = cmp.getSelectedNodes()[0];
			var cmpEl = cmp.getEl();
			Ext.fly(nodeEl).scrollIntoView(cmpEl);
		}
		else {
			that.selectedIndex==0? cmp.getSelectionModel().selectFirstRow():cmp.getSelectionModel().selectLastRow();
		}
	},


	keyboardDispacher:function(myEvent){

		var that = Ext.getCmp('wt-panel');

		var o = {13:onENTER, 27:onESC, 113:onF2, 46:onDELETE, 33:onPAGEUP, 34:onPAGEDOWN, 37:onLEFT, 38:onUP, 39:onRIGHT, 40:onDOWN, 67:onCTRL_c, 88:onCTRL_x, 86:onCTRL_v, 65:onCTRL_a}


		if (myEvent.keyCode in o)
			o[myEvent.keyCode]();


		function onENTER(){

			if(that._renameFlag || that._stopUserInteraction) //Stil not finish rename
				return;

			var selectedRecords = that.getSelectedRecords();
			if (selectedRecords.length == 1){
				that.onDblClick(selectedRecords[0].data.id, selectedRecords[0].data.iconCls);
				that._stopUserInteraction = true;
			}
		}

		function onESC(){
//			console.log('ESC');
		}

		function onF2(){
			var selectedRecords = that.getSelectedRecords();
			if (selectedRecords.length == 1){
				if (!that.fCtxDFlag.rename)
					that.onRename();
				else {
					var title = 'Warning'.localize();
					var msg = 'You have no permission for this operation'.localize();
					Jedox.studio.app.showMessageERROR(title, msg);
				}
			}


//			console.log('F2');
		}

		function onDELETE(){
//			console.log('DELETE');
			if (!that.fCtxDFlag.remove)
				that.remove();
			else {
				var title = 'Warning'.localize();
				var msg = 'You have no permission for this operation'.localize();
				Jedox.studio.app.showMessageERROR(title, msg);
			}
		}

		function onPAGEUP(){
			that.onScroll('UP');
//			console.log('PAGEUP');
		}

		function onPAGEDOWN(){
			that.onScroll('DOWN');
//			console.log('PAGEDOWN');
		}

		function onLEFT(){
			that.moveSelection('UP');
//			console.log('LEFT');
		}

		function onUP(){
			that.moveSelection('UP');
//			console.log('UP');
		}

		function onRIGHT(){
			that.moveSelection('DOWN');
//			console.log('RIGHT');
		}

		function onDOWN(){
			that.moveSelection('DOWN');
//			console.log('DOWN');
		}

		function onCTRL_c(){
			that.onCopy();
//			console.log('CTRL_c');
		}

		function onCTRL_x(){
			that.onCut();
		}

		function onCTRL_v(){
			if (!that.fCtxDFlag.c_paste)
				that.onPasteNEW();
			else {
				var title = 'Warning'.localize();
				var msg = 'You have no permission for this operation'.localize();
				Jedox.studio.app.showMessageERROR(title, msg);
			}
//			console.log('CTRL_v');
		}

		function onCTRL_a(){
//			console.log('CTRL_a');
		}

	}

});
