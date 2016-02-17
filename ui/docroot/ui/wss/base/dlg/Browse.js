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
 * SVN: $Id: Browse.js 5110 2011-07-11 18:24:40Z djordjez $
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


Jedox.wss.dlg.Browse = function(OSHflag, closeWinFnc, preselectMode, tabOffset, onSelectDVFn){

	/*
	 * OSHflag Open || Save As flag || Hyperlink  || Save As then Quick Publish flag
	 * Win title Save As || Open
	 * Btn Save || Open
	 * Cmb Save as type || Files of type
	 */


	//############################### Data and Store ######################################

	//references to components that depends of OSHflag
	var that = this;
	var title;
	var btn;
	var typeCmb;
	var hyperlink = {'removeTlbBtn':false, 'newFolderTlbBtn':false, 'fileTypesCmb':false}
	that.closeFnc = closeWinFnc;
	if (!tabOffset) tabOffset = 0;

	//that.activeGroup;
	that.activeHierarchy = {};
	//that.selectionId;
	//that.parentNode;
//	that.dlgTlb;
	that._isHyperlink = false;

	that._preselectMode = preselectMode ? true:false;

	that._selectAfterDump_cb = false;

	that._nodeClick_cb = false;
	that._overrideNode = null;

	var handleDblClick = true;
	var _triggerSnapshotChbOnSelect = false;
//	that._parentPerm;

	var _commitedChanges = false;

	var _configObj = {
		panelHeight:70
	}

	var _filterFrameset = true; //Open, Save As (show frameset files in that dialog with folders and wss files)
	var _filterXLSX = true;

	that._typeOrderData = {
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

	that.PERM_TYPES =
	{
		NONE: 0,
	 	READ: 1,
	 	WRITE: 2,
	 	DELETE: 4,
	 	SPLASH: 8
	};

	that.gStore = new Ext.data.SimpleStore({
	    fields: ['id', 'name']
	});


	that.fStore = new Ext.data.SimpleStore({
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
		sortInfo:{field:'order', direction: 'ASC'},
		listeners:{
			add:function(store, records, index){
				that.onEdit();
			},
			update: function(store, record, operation) {

				if(_commitedChanges){
					_commitedChanges = !_commitedChanges;
					return;
				}

				_commitedChanges = true;
				that.rename(record.get('id'), record.get('text'));
				this.commitChanges();
			}
		}
	});


	var folderTypeData = [
		['My Workbook Documents'.localize(), 'my_workbook_documents']
	]

	var folderTypeNavigationStore = new Ext.data.SimpleStore({
		fields: ['label', 'icon'],
		data: folderTypeData
	});

	var fileTypes = [['0', 'Work Sheet Files'.localize()], ['1', 'All Files'.localize()]]

	var fileTypesStore = new Ext.data.SimpleStore({
		fields: ['code', 'option'],
		data: fileTypes
	});


	var saveTypes = [['0', 'Work Sheet Files (*.wss)'.localize()]]

	var exportTypes = [['0', 'All Workbook Files'.localize()]]

	var saveTypesStore = new Ext.data.SimpleStore({
		fields: ['code', 'option'],
		data: saveTypes
	});

	var fileNameData = [];

	var fileNameStore = new Ext.data.SimpleStore({
		fields: ['fileName', 'g', 'h', 'n'],
		data: fileNameData
	});




	//############################### Components ######################################

	var pathTxf = new Ext.form.TextField({
		fieldLabel: 'Path'.localize(),
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		allowBlank: false,
		width: 200
	});


	that.gCmb = new Ext.form.ComboBox({
		id: 'sFiles_lookIn_cmb',
		store: that.gStore,
		displayField: 'name',
		valueField: 'id',
		fieldLabel: 'Look in'.localize(),
		readOnly: false,
		editable: false,
		lazyRender: true,
		typeAhead: true,
		mode: 'local',
		triggerAction: 'all',
		//value: this.getGValue(),
		selectOnFocus: true,
		width: 330,
		tabIndex: 1 + tabOffset,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		listeners: {
			select: function(cmb, record, index){
				if (that.activeGroup != record.data) {

					var wssStudioHandler = {
						treeSetGroup: function(result){

							if (!result) {
								//show feedback
								that.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());
								return false;
							}

						that.activeGroup = record.data;
						that.hierarchyTP.root.setText(record.data.name);
						that.initHierarchies(that.activeGroup.id);
						}
					}


					var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
					wssStudioStub.treeSetGroup('wss', record.data.id);
				}
			}
		}
	});



	var root = new Ext.tree.TreeNode({
		text: 'root',
		draggable: false, // disable root node dragging
		editable:false,
		id: 'root',
		iconCls: 'w3s_group',
		expanded:true
	});

	that.hierarchyTP = new Ext.tree.TreePanel({
		id: 'wFiles_filesTree_tr',
		border: false,
		lines: true,
		heigth: 100,
		containerScroll: true,
		ddScroll: true,
		autoScroll: true,
		collapseFirst: false,
		root:root,
		rootVisible:false,
		collapseFirst: true,
		listeners: {
			click: function(node, e){

				if (!that._nodeClick_cb) {

					var wssStudioHandler = {
						treeSetHierarchy: function(result){

							if (!result) {
								//show feedback
								that.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());
								return false;
							}

							that.hierarchyTP.fireEvent('click', node);
						}
					}

					if (node.id != 'root') {
						if (node.attributes.type) {
							if (that.activeHierarchy.id != node.attributes.id) {
								var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
								wssStudioStub.treeSetHierarchy('wss', node.attributes.id);
								_nodeClick_cb = true;
								that.activeHierarchy.id = node.attributes.id;
								return false;
							}
						}
						else
							if (that.activeHierarchy.id != node.attributes.h_uid) {
								var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
								wssStudioStub.treeSetHierarchy('wss', node.attributes.h_uid);
								_nodeClick_cb = true;
								that.activeHierarchy.id = node.attributes.h_uid;
								return false;
							}
					}
				}
				else{
					that._nodeClick_cb = false;
				}

				node.expand();

			},
			select: function(id){
				var node = this.getNodeById(id);
				this.fireEvent('click', node);
			},
			up: function(sn){
				if (sn) {
					var parentNode = sn.parentNode;
					if (parentNode)
						this.fireEvent('click', parentNode);
				}
			},
			renameNode: function(n_uid, newName){
				var id = getNodeId(n_uid);
				var node = this.getNodeById(id);
				if (node)
					node.setText(newName);
			},
			removeNode: function(n_uid){
				var id = getNodeId(n_uid);
				var node = this.getNodeById(id);
				if (node)
					node.remove();
			},
			addNode: function(n_uid, nodeData, perm_n){

				var newNode = new Ext.tree.TreeNode({
			        text: nodeData.text,
			        n_uid: nodeData.id,
					iconCls:nodeData.iconCls,
					h_uid:that.activeHierarchy.id,
					id:that.activeHierarchy.id + '_' + nodeData.id,
					qtip:nodeData.qtip,
					leaf:nodeData.leaf,
					perm_n: nodeData.perm_n
			    });


				var parent = this.getNodeById(that.activeHierarchy.id);

				if (n_uid != 'root')
					parent = this.getNodeById(getNodeId(n_uid));

				parent.appendChild(newNode);
			}
		}
	});

	that.hierarchyTP.on('click', function(n){
		var sn = that.hierarchyTP.getSelectionModel().getSelectedNode() || {}; // selNode is null on initial selection
		if (n.id != sn.id && n.id!='root')
			if (n.attributes.type)
				initFilesData(n.attributes.type, n.attributes.perm_n);
			else
				initFilesData(n.attributes.n_uid, n.attributes.perm_n);
		else if (n.id =='root'){
			clear();
		}

	});


	that.hierarchyTreeSorter = new Ext.tree.TreeSorter(that.hierarchyTP, {});


	var mainListView = new Ext.DataView({
		id: 'wFiles_mainList_dv',
		store: that.fStore,
		tpl: new Ext.XTemplate(
				'<div class="wFiles_mainList_dv"><tpl for=".">', '<div class="thumb-wrap">',
				'<div class="thumb" style="padding: 0px; text-align: left;">',
				'<div style="width: 16px; height: 16px; display: inline;">',
				'<img class="{img_src}" src="/ui/lib/ext/resources/images/default/s.gif" width="16" height="16"></div>',
				'<span class="x-editable">&nbsp;{text}</span></div></div>', '</tpl></div>'
			),
		autoWidth:true,
		multiSelect: false,
		autoScroll:true,
		singleSelect: true,
		overClass: 'x-view-over',
		itemSelector: 'div.thumb-wrap',
		emptyText: '',
		plugins: [new Ext.DataView.DragSelector(),
			new Ext.DataView.LabelEditor({
				dataIndex: 'text',
				onMouseDown : function(ed, value){
					return;
				},
			    onSave : function(ed, value){
					var trimValue =  this.trim(value);
					if (that.validateNewFolderName(this.activeRecord.data.text, trimValue, this.activeRecord.data.iconCls)) {
						this.activeRecord.set(this.dataIndex, trimValue);
					}
			    },
				trim:function(s){
					return s.replace(/^\s+|\s+$/g, '');
				}
			})],
		listeners: {
			dblclick:function(dataView, index, node, e){
				var dblClckdRecord = dataView.store.getAt(index);
				onDblClick(dblClckdRecord.get('id'), dblClckdRecord.get('iconCls'));
			},
			click:function(dataView, index, node, e){
				var value = '';
				if (that.fStore.getAt(index).get('iconCls') != 'w3s_folder') {
					value = that.fStore.getAt(index).get('text');
					that.selectionId  = that.fStore.getAt(index).get('id');
					if (!isClicked(value)) {
						var g = that.gCmb.getValue();
						var h = that.activeHierarchy.id;
						var n = that.selectionId;
						fileNameData.unshift(new Array(value, g, h, n));
						fileNameStore.loadData(fileNameData);
					}
				}
					that.fileNameCmb.setValue(value);
				if (OSHflag === 'hyperlink') {
					var data = that.onInsertHyperlink(true) || {t: 'folder'};
					onSelectDVFn(data);
				}

				if(_triggerSnapshotChbOnSelect)
					triggerSnapshotChb(that.selectionId);
			},
			edit:function (dataView){
				var node = dataView.getSelectedNodes();
				var record = dataView.getRecords(node);
				var index = dataView.getSelectedIndexes();
				var target = document.getElementsByClassName('x-editable');

				dataView.plugins[1].activeRecord = record[0];
				dataView.plugins[1].startEdit(target[index], record[0].data.text);
			}
		}
	});



	var mainDetailsView = new Ext.grid.EditorGridPanel({
		id: 'main-details-view',
		colModel: new Ext.grid.ColumnModel([
			{id:'folder-name', header: "Name",width: 30,sortable: true, dataIndex: 'text', renderer:formatTitle, editor: new Ext.form.TextField({allowBlank: false})},
			{header: "Size", width: 15, sortable: true, align:'right', dataIndex: 'size',renderer:function(c,f,g){
				return g.data.size? Ext.util.Format.fileSize(g.data.size):"";
			}},
			{header: "Type", width: 20, sortable: true, dataIndex: 'type'},
			{header: "Last Modified", width: 30, sortable: true, dataIndex: 'lastmod', renderer:function(c,f,g){
				return g.data.lastmod? g.data.lastmod.dateFormat('date_format'.localize()):"";
			}}
		]),
		store: that.fStore,
		viewConfig: {
			forceFit: true
		},
		sm: new Ext.grid.RowSelectionModel({
			singleSelect: true
		}),
		border: false,
		iconCls: 'icon-grid',
		listeners: {
			rowdblclick: function(gridView, index, e) {
				var dblClckdRecord = gridView.store.getAt(index);
				onDblClick(dblClckdRecord.get('id'), dblClckdRecord.get('iconCls'));
			},
			rowclick:function(gridView, index, e){
				var value = '';
				if (that.fStore.getAt(index).get('iconCls') != 'w3s_folder') {
					value = that.fStore.getAt(index).get('text');
					that.selectionId  = that.fStore.getAt(index).get('id');
					if (!isClicked(value)) {
						var g = that.gCmb.getValue();
						var h = that.activeHierarchy.id;
						var n = that.selectionId;
						fileNameData.unshift(new Array(value, g, h, n));
						fileNameStore.loadData(fileNameData);
					}
				}
					that.fileNameCmb.setValue(value);
				if (OSHflag === 'hyperlink') {
					var data = that.onInsertHyperlink(true) || {t: 'folder'};
					onSelectDVFn(data);
				}

				if(_triggerSnapshotChbOnSelect)
					triggerSnapshotChb(that.selectionId);

			},
			edit:function (gridView){
				gridView.getColumnModel().setEditable(0, true);
				var record = gridView.getSelectionModel().getSelected();
				var index = gridView.store.indexOf(record);

				gridView.startEditing(index, 0);
			},
			validateedit: function(o){
				o.value = that.trim(o.value);
				var record = this.getSelectionModel().getSelected();
				var _ret = that.validateNewFolderName(record.data.text, o.value, record.data.iconCls);
				return _ret;
			}
		}
	});



	var mainThumbnailsView = new Ext.DataView({
		id: 'main-thumbnails-view',
		store: that.fStore,
		tpl:new Ext.XTemplate(
			'<tpl for=".">','<div class="thumb-wrap" id="{text}">','<div class="thumb"><div class="{img_src}32"><img src="/ui/lib/ext/resources/images/default/s.gif" title="{text}"></div></div>',
			'<span class="x-editable">{shortName}</span></div>','</tpl>','<div class="x-clear"></div>'),
		autoWidth:true,
		multiSelect: false,
		singleSelect: true,
		overClass: 'x-view-over',
		itemSelector: 'div.thumb-wrap',
		emptyText: '',
		plugins: [new Ext.DataView.DragSelector(),
			new Ext.DataView.LabelEditor({
				dataIndex: 'text',
				onMouseDown : function(ed, value){
					return;
				},
			    onSave : function(ed, value){
					var trimValue =  this.trim(value);
					if (that.validateNewFolderName(this.activeRecord.data.text, trimValue, this.activeRecord.data.iconCls)) {
						this.activeRecord.set(this.dataIndex, trimValue);
					}
			    },
				trim:function(s){
					return s.replace(/^\s+|\s+$/g, '');
				}
			})
		],
		prepareData: function(data){
                data.shortName = Ext.util.Format.ellipsis(data.text, 11);
                return data;
        },
		listeners: {
			dblclick:function(dataView, index, node, e){
				var dblClckdRecord = dataView.store.getAt(index);
				onDblClick(dblClckdRecord.get('id'), dblClckdRecord.get('iconCls'));
			},
			click:function(dataView, index, node, e){
				var value = '';
				if (that.fStore.getAt(index).get('iconCls') != 'w3s_folder') {
					value = that.fStore.getAt(index).get('text');
					that.selectionId  = that.fStore.getAt(index).get('id');
					if (!isClicked(value)) {
						var g = that.gCmb.getValue();
						var h = that.activeHierarchy.id;
						var n = that.selectionId;
						fileNameData.unshift(new Array(value, g, h, n));
						fileNameStore.loadData(fileNameData);
					}
				}
					that.fileNameCmb.setValue(value);
				if (OSHflag === 'hyperlink') {
					var data = that.onInsertHyperlink(true) || {t: 'folder'};
					onSelectDVFn(data);
				}

				if(_triggerSnapshotChbOnSelect)
					triggerSnapshotChb(that.selectionId);
			},
			edit:function (dataView){

				var node = dataView.getSelectedNodes();
				var record = dataView.getRecords(node);
				var index = dataView.getSelectedIndexes();
				var target = document.getElementsByClassName('x-editable');
				var step = target.length/2;

				dataView.plugins[1].activeRecord = record[0];
				dataView.plugins[1].startEdit(target[step + index[0]], record[0].data.text);
			}
		}
	});


	that.fileNameCmb = new Ext.form.ComboBox({
		store: fileNameStore,
		displayField: 'fileName',
		id: 'wFiles_fileNameBrowse_cmb',
		fieldLabel: 'File name'.localize(),
		typeAhead: true,
		mode: 'local',
		triggerAction: 'all',
		width: 400,
		tabIndex: 6 + tabOffset,
		listeners:{
			select: function(cmb, record, index){
				that.selectionId = record.data.n;
				clearAllSelections();
			}
		}
	});


	function clearAllSelections(){
		mainListView.clearSelections();
		mainThumbnailsView.clearSelections();
		mainDetailsView.getSelectionModel().clearSelections();
	}



	var fileTypesCmb = new Ext.form.ComboBox({
		fieldLabel: 'Files of type'.localize(),
		width: 400,
		store: fileTypesStore,
		displayField: 'option',
		valueField:'code',
		typeAhead: true,
		editable:false,
		mode: 'local',
		triggerAction: 'all',
		selectOnFocus: true,
		tabIndex: 7 + tabOffset,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		listeners:{
			select: function(cmb, record, index){
				if (cmb.getValue() == 0)
					that.fStore.filterBy(filterFunc);
				else
					that.fStore.clearFilter(false);
			}

		}
	});


	var saveTypesCmb = new Ext.form.ComboBox({
		fieldLabel: 'Save as type'.localize(),
		width: 400,
		store: saveTypesStore,
		displayField: 'option',
		valueField:'code',
		typeAhead: true,
		editable:false,
		mode: 'local',
		tabIndex: 8 + tabOffset,
		triggerAction: 'all',
		selectOnFocus: true
//		listeners:{
//			select: function(cmb, record, index){
//				if (cmb.getValue() == 0)
//					fStore.filterBy(filterFunc);
//				else
//					fStore.clearFilter(false);
//			}
//		}
	});


	that.saveAsSnapshotChb = new Ext.form.Checkbox({
		boxLabel: 'Save as snapshot'.localize(),
		tabIndex: 9 + tabOffset,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		hidden:true,
		checked:false
	});

	that.convertToWSSChb = new Ext.form.Checkbox({
		boxLabel: 'Convert'.localize(),
		tabIndex: 10 + tabOffset,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		hidden:true,
		checked:true,
		listeners:{
			check:function(){
				if(this.checked){
					that.showLogChb.show();
				}
				else
					that.showLogChb.hide();
					that.showLogChb.setValue(false);
			}
		}
	});

	that.showLogChb = new Ext.form.Checkbox({
		boxLabel: 'Show log'.localize(),
		tabIndex: 11 + tabOffset,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		hidden:true,
		checked:false
	});


	//############################### Functions ######################################

	function getNodeId(n_uid){
		if (that.hierarchyTP.getNodeById(n_uid))
			return n_uid;

		return that.activeHierarchy.id + '_' + n_uid;
	}


	function isClicked(value){
		var flag = false;
		for (var i = 0; i < fileNameData.length; i++) {
			if (value === fileNameData[i][0]) {
				flag = true;
				break;
			}
		}
		return flag;
	}

	function onContainerClick(dView, e){
		e.stopEvent();
		return false;
	};

	function setView(m, pressed){
		if (!m) { // cycle if not a menu item click
			var viewMenu = Ext.menu.MenuMgr.get('view-menu');
			viewMenu.render();
			var items = viewMenu.items.items;
			var b = items[0], r = items[1], h = items[2];
			if (b.checked) {
				r.setChecked(true);
			}
			else
				if (r.checked) {
					h.setChecked(true);
				}
				else
					if (h.checked) {
						b.setChecked(true);
					}
			return;
		}
		if (pressed) {
			var mvp = Ext.getCmp('main-view-panel');
			switch (m.text) {
				case 'List'.localize():
					mvp.layout.setActiveItem('wFiles_mainList_dv')
					mvp.ownerCt.doLayout();
					//btn.setIconClass('preview-bottom');
					break;

				case 'Thumbnails'.localize():
					mvp.layout.setActiveItem('main-thumbnails-view');
					mvp.ownerCt.doLayout();
					break;
				case 'Details'.localize():
					mvp.layout.setActiveItem('main-details-view')
					mvp.ownerCt.doLayout();
					break;
			}
		}
	};

	function initInterface(){

		switch(OSHflag){
			case 'import':
				_filterFrameset = false;
				_configObj.panelHeight += 20;
				_triggerSnapshotChbOnSelect = true;
				title = 'Open'.localize();
				that.fileNameCmb.setEditable(false);
				typeCmb = fileTypesCmb;
				typeCmb.getStore().loadData(exportTypes);// wss, xlsx, folder
				break;
			case 'open':
				_filterXLSX = false;
				title = 'Open'.localize();
				typeCmb = fileTypesCmb;
				typeCmb.getStore().loadData(fileTypes.slice(0, 1));// just wss files and folders
				break;
			case 'export':
				title = 'Save As'.localize();
				typeCmb = saveTypesCmb;
				typeCmb.getStore().loadData(exportTypes);// wss, xlsx, folder
				handleDblClick = false;
				_filterFrameset = false;
				_configObj.panelHeight += 40;
				that.convertToWSSChb.show();
				that.showLogChb.show();
				break;
			case 'save':
				_filterXLSX = false;
				title = 'Save As'.localize();
				typeCmb = saveTypesCmb;
				handleDblClick = false;
				_configObj.panelHeight += 20;
				that.saveAsSnapshotChb.show();
				break;
			case 'hyperlink':
				typeCmb = {html:'', baseCls:'x-plain'};
				hyperlink.removeTlbBtn = hyperlink.newFolderTlbBtn = true;
				that._isHyperlink = true;
				handleDblClick = false;
				break;
		}

	}

	initInterface();


	function init(){
		// call back function
		function initGroups_cb(result){
			if (result){
				// call back function
				function selectGroup_cb(result){
					if (result)
						that.initHierarchies();
				}

				that.selectGroup(getDefaultGroupIndex(), selectGroup_cb);
			}
		}

		that.initGroups(initGroups_cb);


	}


	function getDefaultGroupIndex(){
		var index = that.gStore.find('id', Jedox.wss.app.defaultFiles.group);
		return index != -1? index:0;
	}


	function initFilesData(node, parentPerm){

		var wssStudioHandler = {
			treeMngNode: function(result){

				if (!result) {
					//show feedback
					that.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());
					return false;
				}

				var fData=[];
				for (var i=0; i<result.length; i++)
					fData.push([result[i].id, result[i].text, result[i].leaf, result[i].qtip, result[i].iconCls, img_src(result[i].iconCls.concat(result[i].hasAs? '_as':'')), that.getType(result[i].iconCls), result[i].perm_n, that._typeOrderData[result[i].iconCls], result[i].size, result[i].mtime]);


				that.fStore.loadData(fData);
				filterStore();
				that.fStore.sort('text', 'ASC');
				that.fStore.sort('order', 'ASC');
				clearFileNames();
				that._parentPerm = parentPerm;

				that.setContainerInterfacePermission(parentPerm);
				that.setUpTlbBtnState(node != 'root');

				//onPreselectPath select node
				if(that._selectAfterDump_cb){
					that._selectAfterDump_cb();
					_selectAfterDump_cb = false;
				}
			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.treeMngNode('wss', node, 'dump', 0);
	}


	function filterStore(){
		if (fileTypesCmb.getValue() == 0)
			that.fStore.filterBy(filterFunc);
	}

	function clearFileNames(){
		if (OSHflag === 'save' || OSHflag === 'saveqp')
			return false;

		fileNameData = [['']];
		fileNameStore.removeAll();
		that.fileNameCmb.setValue('');
	}

	function img_src(iconCls){
		return iconCls;
	}

	function onDblClick(id, iconCls){
		if (iconCls === 'w3s_folder'){
			propagateSelection(id)
		}
		else {
			if (!that._isHyperlink && handleDblClick)
				that.openWB(id);
		}
	}


	function propagateSelection(n_uid){
		var id = that.hierarchyTP.getNodeById(n_uid)? n_uid:that.activeHierarchy.id + '_' + n_uid;

		that.hierarchyTP.fireEvent('select', id);
	}


	function formatTitle(value, p, record) {
        return String.format(
                '<div class="topic"><img class="{0}" src="/ui/lib/ext/resources/images/default/s.gif" width="16" height="16" /><span style="vertical-align:top;">&nbsp;&nbsp;{1}</span></div>',
                record.data.img_src, value
        );
    }


	function filterFunc(record, id){
		//If the function returns true the Record is included, otherwise it is filtered out.
		return (record.get('iconCls') === 'w3s_workbook' || record.get('iconCls') === 'w3s_folder' || (_filterFrameset && record.get('iconCls') === 'w3s_frameset') || (_filterXLSX && record.get('iconCls') === 'w3s_xlsx'))? true : false;
	}

	function clearFilter(record, id){
		//If the function returns true the Record is included, otherwise it is filtered out.
		return record.get('iconCls') !== 'w3s_workbook' ? true : false;
	}


	function onUp(){
		var sn = that.hierarchyTP.selModel.getSelectedNode();
		that.hierarchyTP.fireEvent('up', sn);
	}



	function clear(){
		that.fStore.removeAll();
		filterStore();
		clearFileNames();
	}

	function triggerSnapshotChb(id){
		if(that.getTypeById(id) in {'workbook':true, "frameset":true})
			that.saveAsSnapshotChb.show();
		else{
			that.saveAsSnapshotChb.setValue(false);
			that.saveAsSnapshotChb.hide();
		}
	}



	//############################### Main Panel ######################################
Jedox.wss.dlg.Browse.superclass.constructor.call(this, {
		id: 'open-save-dlg-browse-panel',
		//modal:true,
		layout: 'absolute',
		baseCls: 'x-plain',
		border: false,
		height:350,
		items: [{
			//title: 'top-table-panel',
			layout: 'column',
			border: false,
			baseCls: 'x-plain',
			width: 600,
			height: 40,
			x: 0,
			y: 0,
			items: [{
				//title:'panel za Look in',
				layout: 'form',
				//labelWidth:120,
				border: false,
				baseCls: 'top-left-bottom-panel',
				width: 460,
				items:that.gCmb
			}, {
				//title:'panel za toolbar',
				border: false,
				baseCls: 'toolbar-panel',
				id: 'browseToolbarHolder',
				width: 130,
				height: 30,
				tbar: that.dlgTlb = new Ext.Toolbar({
					items:[{
//					tooltip: {
//						title: 'Up'.localize(),
//						text: 'Go Up one level'.localize()
//					},
					iconCls: 'folder-up-icon',
					id: 'sFiles_folderUp_btn',
					handler:onUp,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					scope: this,
					tabIndex: 2 + tabOffset
					}, '-', {
//					tooltip: {
//						title: 'Delete'.localize(),
//						text: 'Delete'.localize().concat('...')
//					},
					iconCls: 'delete-icon',
					id: 'sFiles_delete_btn',
					handler:that.remove,
//					hidden:hyperlink.removeTlbBtn,
					hidden:true,
					scope: this,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 3 + tabOffset
					}, {
//					tooltip: {
//						title: 'New Folder'.localize(),
//						text: 'Adds New folder to the list'.localize()
//					},
					iconCls: 'new-folder-icon',
					id: 'sFiles_newFolder_btn',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
//					hidden:hyperlink.newFolderTlbBtn,
					scope: this,
//					hidden:true,
					handler:that.addFolder,
					tabIndex: 4 + tabOffset
				}, {
					split: true,
//					tooltip: {
//						title: 'View'.localize(),
//						text: 'View'.localize().concat('...')
//					},
					iconCls: 'view-menu-icon',
					id: 'sFiles_viewType_btn',
					handler: setView.createDelegate(this, []),
					tabIndex: 5 + tabOffset,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					menu: {
						id: 'view-menu',
						cls: 'view-menu',
						width: 110,
						items: [{
							text: 'List'.localize(),
							checked: true,
							group: 'rp-view',
							checkHandler: setView,
							scope: this,
							iconCls: 'view-list-icon'
						}, {
							text: 'Thumbnails'.localize(),
							checked: false,
							group: 'rp-view',
							checkHandler: setView,
							scope: this,
							iconCls: 'view-thumbnails-icon'
						}, {
							text: 'Details'.localize(),
							checked: false,
							group: 'rp-view',
							checkHandler: setView,
							scope: this,
							iconCls: 'view-details-icon'
						}]
					}
				}]
				})
			}]
		}, {
			//title: 'left-table-panel',
			baseCls: 'left-panel',
			layout: 'fit',
			border: false,
			width: 200,
			height: 210,
			x: 5,
			y: 40,
			items:that.hierarchyTP
		}, {
			//title: 'main-table-panel',
			id: 'main-view-panel',
			layout: 'card',
			autoScroll:true,
			defaults: {
				bodyStyle: 'padding:0px'
			},
			width: 370,
			height: 210,
			x: 210,
			y: 40,
			items: [mainListView, mainThumbnailsView, mainDetailsView],
			activeItem:0
			//detailsView
		}, {
			//title: 'bottom-table-panel',
			layout: 'form',
			//labelWidth:120,
			border: false,
			baseCls: 'top-left-bottom-panel',
			width: 600,
			height: _configObj.panelHeight,
			x: 0,
			y: 248,
			items: [that.fileNameCmb, typeCmb, that.saveAsSnapshotChb, that.convertToWSSChb, that.showLogChb]
		}]
	});

	if(!that._preselectMode)
		init();

	fileTypesCmb.setValue(that._isHyperlink ? '1':'0');
	saveTypesCmb.setValue('0');

}



Ext.extend(Jedox.wss.dlg.Browse, Ext.Panel, {

	initComponent: function(){
		var that = this;
		Jedox.wss.dlg.Browse.superclass.initComponent.call(this);


		this.onOpen = function(){
			var name = that.fileNameCmb.getValue();
			var id = that.selectionId; //that.getIdByName(name); because name is unique with files same type and in open dlg mode could work
			if(name && id)
				that.openWB(id);
		}


		this.onSave = function(cb){

			var parentId = that.getParentId();
			var group = that.gCmb.getValue();
			var hierarchy = that.activeHierarchy.id;

			if (!parentId)
				return false;

			var fileName = that.trim(that.fileNameCmb.getValue());
			var s = fileName.toLowerCase().indexOf('.wss');

			if(s>0 && s === fileName.length-4)
				fileName = that.trim(fileName.slice(0, length-4));

			if (that.validateName(fileName)){


				function doSave(){

					var saveAsSnapshot = that.saveAsSnapshotChb.getValue();

					that.closeFnc();

					var activeBook = Jedox.wss.app.activeBook,
							oldMeta = activeBook._meta,
							oldName = activeBook._name;

					try {
						for (var triggers = Jedox.wss.events.triggers.saveAsWorkbook_before, i = triggers.length - 1; i >= 0; i--)
							triggers[i][0]['saveAsWorkbook_before'].call(parent, triggers[i][1], oldMeta, oldName);
					} catch (e) {
						Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
						return;
					}


					function save_post(saveRes){

						if (!saveRes[0]) {
							Ext.MessageBox.show({
								title: 'Save As'.localize(),
								msg: saveRes[1].localize(saveRes[2]),
								modal: true,
								buttons: Ext.MessageBox.OK,
								icon: Ext.MessageBox.WARNING,
								fn: Ext.emptyFn,
								minWidth: 300
							});

						}
						else {

							var newWbMeta = {
								g: saveRes[1].group,
								h: saveRes[1].hierarchy,
								n: saveRes[1].node,
								p: saveRes[1].perm
							};

							activeBook.setName(fileName);
							activeBook.setMeta(newWbMeta);

							activeBook.setWbId(saveRes[1].wbid);
							Jedox.wss.action.adjustToACL();

							if (saveAsSnapshot)
								Jedox.wss.sheet.refresh();

							//that.closeFnc();

							try {
								for (var triggers = Jedox.wss.events.triggers.saveAsWorkbook_after, i = triggers.length - 1; i >= 0; i--)
									triggers[i][0]['saveAsWorkbook_after'].call(parent, triggers[i][1], {
										g: newWbMeta.g,
										h: newWbMeta.h,
										n: newWbMeta.n
									}, oldName, fileName);
							}
							catch (e) {
								Jedox.wss.general.showMsg('Application Error', e.message, Ext.MessageBox.ERROR);
							}

							if (cb instanceof Array && cb.length > 1)
								cb[1].call(cb[0]);
						}
					}

					(new Jedox.backend.RPCAsyncRqst('WSS', 'save_workbook', [group, hierarchy, fileName, parentId, that._overrideNode, true, saveAsSnapshot]))
						.setOnSuccess([that, save_post]).send();

				}


				if (that._overrideNode) {

					Ext.MessageBox.show({
						title: 'Save As'.localize(),
						msg: 'save_as_override_msg'.localize({'fileName':fileName}),
						closable: false,
						buttons: Ext.Msg.OKCANCEL,
						icon: Ext.MessageBox.WARNING,
						minWidth: 300,
			   			fn: function(btn) {
		   					if (btn != 'ok')
		   						return;
							doSave();
		   				}

					});
				}
				else {
					doSave();
				}


			}
			else {
					Ext.MessageBox.show({
						title: 'Save As'.localize(),
						msg: 'save_as_err_msg'.localize({'fileName':fileName}),
						modal: true,
						buttons: Ext.MessageBox.OK,
						icon: Ext.MessageBox.WARNING,
						fn: Ext.emptyFn,
						minWidth: 300
					});
			}

		}


		this.onInsertHyperlink = function(dfb){

			var g = that.activeGroup ? that.activeGroup.id:null;
			var h = that.activeHierarchy? that.activeHierarchy.id:null;
			var n = that.selectionId;

			if (g && h && n){
				var result =  Jedox.backend.studio.getNodeHyperlinkPropertiesData(g, h, n);
				if (result)
					return result;
				else
					return false;
			}
			else {
				if (dfb) return;
				var title = 'Insert Hyperlink'.localize();
				var message = '_hl_no_selected_file'.localize();
				that.showMessageALERT(title, message);
			}

		}



		this.preselectPath = function(ghn){

			that.initGroups(function(result){
				if (result){
					for (var i = 0, count = that.gStore.getCount(); i < count; i++) {
						if (that.gStore.getAt(i).get('id') == ghn.g)
							break;
					}

					that.selectGroup(i, function(result){
						if (result) {
							that.initHierarchies(ghn.g, function(){
								var hNode = that.hierarchyTP.getNodeById(ghn.h);
								if (hNode) {
									hNode.expand(false, false, function(hNode){
										var wssStudioHandler = {
											getElementPath: function(result){

												if (!result[0]) {
													//show feedback
													that.showMessageERROR('Hyperlink Error'.localize(), '_hl_missing_target_node'.localize());
													return false;
												}

												var path = '/root/' + result[1];
												that.hierarchyTP.expandPath(path, false, function(bSuccess, oLastNode){
													if (bSuccess && oLastNode) {
														if (result.length == 2 && result[1]) {
															var id = result[1].split('/')[result[1].split('/').length - 1];
															var node = that.hierarchyTP.getNodeById(id);
															if (node) {

																that._selectAfterDump_cb = function(){
																	that.selectNode(ghn.n);
																}

																that.hierarchyTP.fireEvent('click', node);

															}
														}
													}

												});
											}
										}

										var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
										wssStudioStub.getElementPath(ghn.g, ghn.h, ghn.n);
									});
								}

							});
						}
					});

				}
			});

		}

		this.setExportInterfaceParams = function(convert, log){
			this.convertToWSSChb.setValue(convert);
			this.showLogChb.setValue(log);
		}


		this.getExportData = function(cb){
			var parentId = that.getParentId();
			var group = that.gCmb.getValue();
			var hierarchy = that.activeHierarchy.id;
			var fileName = that.trim(that.fileNameCmb.getValue());
			var convert = that.convertToWSSChb.getValue()? 1:0;
			var log = that.showLogChb.getValue()? 1:0;

			var s = fileName.toLowerCase().indexOf('.wss');

			if(s>0 && s === fileName.length-4)
				fileName = that.trim(fileName.slice(0, length-4));

			if (that.validateName(fileName)) {


				if (that._overrideNode) {

					Ext.MessageBox.show({
						title: 'Save As'.localize(),
						msg: 'save_as_override_msg'.localize({'fileName':fileName}),
						closable: false,
						buttons: Ext.Msg.OKCANCEL,
						icon: Ext.MessageBox.WARNING,
						minWidth: 300,
			   			fn: function(btn) {
		   					if (btn != 'ok')
		   						return;
		   					cb((group && hierarchy && parentId && fileName) ? {g:group, h:hierarchy, p:parentId, name:fileName, override:that._overrideNode, convert:convert, log:log}:null);
		   				}

					});
				}
				else {
					cb((group && hierarchy && parentId && fileName) ? {g:group, h:hierarchy, p:parentId, name:fileName, override:that._overrideNode, convert:convert, log:log}:null);
				}

			}
			else {
					Ext.MessageBox.show({
						title: 'Export'.localize(),
						msg: 'save_as_err_msg'.localize({'fileName':fileName}),
						modal: true,
						buttons: Ext.MessageBox.OK,
						icon: Ext.MessageBox.WARNING,
						minWidth: 300,
						fn:Ext.emptyFn
					});
			}

		}

		this.getImportData = function(){
			var group = that.gCmb.getValue();
			var hierarchy = that.activeHierarchy.id;
			var fileName = that.trim(that.fileNameCmb.getValue());
			var id = that.selectionId; //that.getIdByName(fileName); bug if two files with same name

			var snapshot = that.saveAsSnapshotChb.getValue();
			var convert = that.getTypeById(id) == 'workbook' ? 1:0;

			return (group && hierarchy && id && fileName) ? {g:group, h:hierarchy, n:id, name:fileName, snapshot:snapshot, convert:convert}:null;

		}


	},


	showMessageERROR:function (title, message){

		Ext.Msg.show({
			title:title,
			msg: message,
			buttons: Ext.Msg.OK,
			animEl: 'elId',
			icon: Ext.MessageBox.ERROR
		});
	},

	showMessageALERT:function (title, message){

		Ext.Msg.show({
			title:title,
			msg: message,
			buttons: Ext.Msg.OK,
			animEl: 'elId',
			icon: Ext.MessageBox.WARNING
		});
	},

	showMsg:function (title, msg, icon, cb){

		Ext.MessageBox.show({
			title: title,
			msg: msg,
			icon: icon,
			modal: true,
			buttons: Ext.MessageBox.OK,
			fn: function(){
				if (cb instanceof Array && cb.length > 1)
					cb[1].apply(cb[0], cb.slice(2));
			}
		});
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

	getRelativePath:function(id){
		var parent = this.hierarchyTP.getNodeById(this.activeHierarchy.id + '_' + this.getParentId()).getPath('text');
		var fileName = this.getFileName(this.fileNameCmb.getValue());

		return parent.concat('/', fileName).slice(1);
	},

	getFileName:function(name){
		var extension;
		var iconCls;
		for (var i=0; i<this.fStore.getCount(); i++){
			if (this.fStore.getAt(i).data.text === name){
				iconCls = this.fStore.getAt(i).data.iconCls;
				break;
			}
		}

		switch (iconCls){
			case 'w3s_workbook':
				extension = '.wss';
				break;
			case 'w3s_jpg':
				extension = '.jpg';
				break;
			case 'w3s_png':
				extension = '.png';
				break;
			case 'w3s_gif':
				extension = '.gif';
				break;
			case 'w3s_txt':
				extension = '.txt';
				break;
			case 'w3s_rtf':
				extension = '.rtf';
				break;
			case 'w3s_pdf':
				extension = '.pdf';
				break;
			case 'w3s_zip':
				extension = '.zip';
				break;
			case 'w3s_rar':
				extension = '.rar';
				break;
			case 'w3s_doc':
				extension = '.doc';
				break;
			case 'w3s_csv':
				extension = '.csv';
				break;
			case 'w3s_pps':
				extension = '.pps';
				break;
			case 'w3s_ppt':
				extension = '.ppt';
				break;
			case 'w3s_xls':
				extension = '.xls';
				break;
			case 'w3s_xlsx':
				extension = '.xlsx';
				break;
			case 'w3s_hyperlink':
				extension = '.hyperlink';
				break;
			case 'w3s_html':
				extension = '.html';
				break;
			default:
				extension = '.unknown';
				break;
		}

		return name.concat(extension);
	},


	openWB:function (id){

		var that = this;
		var group = this.gCmb.getValue();
		var hierarchy = this.activeHierarchy.id;
		var name = this.fileNameCmb.getValue();
		var type = this.getTypeById(id); //workbook || frameset;

		try {
			that.closeFnc();
			for (var triggers = Jedox.wss.events.triggers.openWorkbook_before, i = triggers.length - 1; i >= 0; i--)
				triggers[i][0]['openWorkbook_before'].call(parent, triggers[i][1], {g: group, h: hierarchy, n: id}, name, false);

			Jedox.wss.node.load(null, type, id, group, hierarchy, {vars: true});

			for (var triggers = Jedox.wss.events.triggers.openWorkbook_after, i = triggers.length - 1; i >= 0; i--)
				triggers[i][0]['openWorkbook_after'].call(parent, triggers[i][1], {g: group, h: hierarchy, n: id}, name);

		} catch (e) {
			Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
		}
	},

	getParentId:function (){
		var sn = this.hierarchyTP.selModel.getSelectedNode();
		if (sn)
			if (sn.attributes.type)
				return sn.attributes.type;
			else if (sn.id === 'root')
				return null;
			else
				return sn.attributes.n_uid;
	},

	getIdByName:function (name){
		for (var i = 0; i<this.fStore.getCount(); i++)
			if (name === this.fStore.getAt(i).get('text'))
				return this.fStore.getAt(i).get('id');
	},

	getTypeById:function (id){
		for (var i = 0; i<this.fStore.getCount(); i++)
			if (id === this.fStore.getAt(i).get('id'))
				return this.fStore.getAt(i).get('iconCls').split('_').pop();
	},

	trim:function (s){
		return s.replace(/^\s+|\s+$/g, '');
	},

	validateName:function (name) {
		var that = this;

		that._overrideNode = null;

		function validateInput(){
			/*
			var my_regexp = /^[a-zA-Z0-9_\-=+][a-zA-Z0-9_\-@\.,\()\ ]*$/;
			if (!my_regexp.test(name))
				return false;
			*/

			return name.length > 0;
		}

		if (!validateInput())
			return false;

		name = that.trim(name).toLowerCase();
		for (var i = 0; i < that.fStore.getCount(); i++) {
			if (name === that.fStore.getAt(i).get('text').toLowerCase() && that.fStore.getAt(i).get('iconCls') == "w3s_workbook"){
				that._overrideNode = that.fStore.getAt(i).get('id');
				return true;
			}
		}

		return true;
	},


	initGroups:function(cb) {
		var that = this;

		var wssStudioHandler = {
			treeMngGroup: function(result){

				if (!result) {
					//show feedback
					that.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());

					if(cb)
						cb(false);

					return false;
				}

				var gData = [];

				for (var i in result)
					gData.push([i, result[i].name]);

				that.gStore.loadData(gData);

				if(cb)
					cb(true);
			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.treeMngGroup('', 'listGroups', ['file']);

	},


	selectGroup:function(index, cb){

		var that = this;

		var wssStudioHandler = {
			treeSetGroup: function(result){

				if (!result) {
					//show feedback
					that.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());

					if(cb)
						cb(false);

					return false;
				}

				that.activeGroup = record.data
				that.gCmb.setValue(record.data.id);
				that.hierarchyTP.root.setText(record.data.name);
				that.hierarchyTP.root.g_id = record.data.id;

				if(cb)
					cb(true);
			}
		}

		if (that.gStore.getCount() > 0) {
			var record = that.gStore.getAt(index);

			if(record){
				var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
				wssStudioStub.treeSetGroup('wss', record.data.id);
			}
			else{
				that.showMessageERROR('Hyperlink Error'.localize(), '_hl_missing_target_node'.localize());

				that.activeGroup = null;
				if(cb)
					cb(false);

				return false;
			}

		}
		else {
			that.activeGroup = null;
			that.gCmb.disable();

			if(cb)
				cb(false);

			return false;
		}
	},


	initHierarchies:function(group, cb){

		var that = this;

		//remove all childe nodes if any
		var nodes=[];
		this.hierarchyTP.root.eachChild(function(node){nodes.push(node);}, [this.hierarchyTP]);
		for (var i=0; i<nodes.length; i++)
			nodes[i].remove();

		if (!group) group = this.activeGroup.id;
		var hData = [];


		var wssStudioHandler = {
			treeMngHierarchy: function(result){

				if (result != null && !result) {
					//show feedback
					that.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());
					return false;
				}



				for (var i in result) {
					that.hierarchyTP.root.appendChild(new Ext.tree.AsyncTreeNode({
						id: i,
						text: result[i].name,
						draggable: false,
						editable:false,
						iconCls: 'w3s_hierarchy',
						perm_h:result[i].perm_h,
						perm_n:result[i].perm_n,
						type: 'root',
						loader: new Ext.tree.TreeLoader({
							dataUrl: '/be/erpc.php?wam='.concat(Jedox.wss.app.appModeS, '&c=Studio&m=treeDump'),
							baseParams: { type: 'wss', hierarchy: i, filter: 'folder', multi_h: true }
						})
					}));
				}

				that.hierarchyTreeSorter.doSort(that.hierarchyTP.getRootNode());

				that.hierarchyTP.root.expand(false, false, function(gNode){

					//callback fnc
					if (cb){
						cb();
						return;
					}

					//preselect default or first hierarchy
					if (that.hierarchyTP.root.hasChildNodes()) {
						var hNode;
						if (that.hierarchyTP.root.hasChildNodes())
							hNode = that.hierarchyTP.getNodeById(Jedox.wss.app.defaultFiles.hierarchy) || that.hierarchyTP.getNodeById(that.hierarchyTP.root.firstChild.attributes.id);
						else
							hNode = that.hierarchyTP.getNodeById(that.hierarchyTP.root.attributes.id);

						if (hNode){
							hNode.expand(false, false, function(hNode){
								that.hierarchyTP.fireEvent('click', hNode);
							});
						}

					}
				});

			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.treeMngHierarchy('wss', 'listHierarchies');

	},



	selectNode:function(n){
		for (var i = 0; i < this.fStore.getCount(); i++)
			if (this.fStore.getAt(i).get('id') == n)
				break;

		Ext.getCmp('wFiles_mainList_dv').select(i);
		Ext.getCmp('main-thumbnails-view').select(i);
		Ext.getCmp('main-details-view').getSelectionModel().selectRow(i);

		this.selectionId  = this.fStore.getAt(i).get('id');
		this.fileNameCmb.setValue(this.fStore.getAt(i).get('text'));
	},


	rename:function(id, newName){

		var that = this;

		function onSucccessCbHandler(){
			that.hierarchyTP.fireEvent('renameNode', id, newName);
		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['wss', this.getParentId(), 'renameNode', id, newName]))
			.setOnSuccess([this, onSucccessCbHandler]).send();
	},


	getNewItemName:function(tmplName, iconCls){
		var br = 1;
		var exist = true;
		var name = tmplName.toLowerCase();

		while (exist){
			exist = false;
			if (br >1) name = tmplName.toLowerCase() + ' (' + br + ')';
			this.fStore.each( function(record){
				if (record.data.text.toLowerCase() == name && (iconCls && iconCls == record.data.iconCls)){
					br= br+1;
					exist = true;
					return false;
				}
			}, [this] )
		}

		return br>1? tmplName + ' (' + br + ')':tmplName;
	},

	validateNewFolderName:function(oldName, newName, iconCls){

		var name = newName.toLowerCase(),
			valid = true,
			that = this;

		if(oldName != newName){

			if(oldName.toLowerCase() == name)
				return valid;

			this.fStore.each( function(record){
				if (record.data.text.toLowerCase() == name && (iconCls && iconCls == record.data.iconCls)){
					that.showMsg('Application Error'.localize(), 'new_folder_name_warrning'.localize({'new_name':newName}), Ext.MessageBox.WARNING, [that, that.onEdit]);
					valid = false;
					return false;
				}
			}, [this] );
		}

		return valid;
	},


	onEdit:function(){
		setTimeout(function(){
			var cmp = Ext.getCmp('main-view-panel').getLayout().activeItem;

			switch(cmp.id){
				case 'wFiles_mainList_dv':
					cmp.select(cmp.store.getCount() - 1);
					var distance = cmp.el.dom.scrollHeight;
					cmp.el.scroll("bottom", distance);
					cmp.fireEvent('edit', cmp);
					break;
				case 'main-thumbnails-view':
					cmp.select(cmp.store.getCount() - 1);
					var distance = cmp.el.dom.scrollHeight;
					cmp.el.scroll("bottom", distance);
					cmp.fireEvent('edit', cmp);
					break;
				default:
					cmp.getSelectionModel().selectLastRow();
					cmp.fireEvent('edit', cmp);
			}

		});
	},


	addFolder:function(){

		var that = this;

		var parent = this.getParentId();

		var iconCls = 'w3s_folder',
			text = this.getNewItemName('New Folder'.localize(), iconCls),
			leaf = false,
			qtip = '',
			type = iconCls.split('_')[1],
			img_src = iconCls,
			perm_n = this._parentPerm;


		//--------------------------------------
		function onSucccessCbHandler(id){

				var newRecord = new Ext.data.Record({
					'id':id,
					'text':text,
					'leaf':leaf,
					'qtip':qtip,
					'iconCls':iconCls,
					'img_src':img_src,
					'type':that.getType(iconCls),
					'perm_n':perm_n,
					'order': that._typeOrderData[iconCls]
				});

				that.fStore.add(newRecord);
				that.selectionId = id;

				var newNode = {
					id:id,
					text: text,
					leaf: leaf,
					qtip:qtip,
					iconCls:iconCls,
					perm_n:perm_n
				}

				that.hierarchyTP.fireEvent('addNode', parent, newNode);
		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['wss', parent, 'addNode', leaf, type, {name: text, desc: qtip}]))
			.setOnSuccess([that, onSucccessCbHandler]).send();
	},

	getType: function(iconCls){

		var _return = '';

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

	setContainerInterfacePermission:function(parentPerm){

		var tlbBtns = this.dlgTlb.items.items;

		!!(parentPerm & this.PERM_TYPES.WRITE)? tlbBtns[3].enable():tlbBtns[3].disable(); //new folder tlb btn
	},

	setUpTlbBtnState:function(state){

		var tlbBtns = this.dlgTlb.items.items;

		state ? tlbBtns[0].enable():tlbBtns[0].disable(); //up tlb btn
	},

	checkImportPermission:function(){
		return !!(this._parentPerm & this.PERM_TYPES.WRITE);
	},

	getTopToolbar:function(){
		return Ext.getCmp('browseToolbarHolder').getTopToolbar();
	}

})