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
 * SVN: $Id: FTreePanel.js 5013 2011-05-30 09:27:32Z srdjanv $
 *
 */

Jedox.studio.files.FTreePanel = function(){

	var activeGroup;
	var gCmbSelectedIndex;
	var activeHierarchy = {};
	var selectedNode;
	var gCtxDFlag = {open:false, newGroup:false, deleteGroup:false, newHierarchy:false, properties:false, renameGroup:false, exportBundleAll:false, importBundleAll:false, exportBundle:false, importBundle:false}
	var hCtxDFlag = {open:false, deleteHierarchy:false, properties:false, exportBundle:false, importBundle:false}
	var fCtxDFlag = {open:false, cut:false, copy:false, rename:false, remove:false, properties:false, exportBundle:false, importBundle:false}
	var _groupNameList;
	var _hierarchyNameList;

	var refreshFlag = false;

	var _triggerSaveAsFromWSS = false;

	var _defaultHierarchyFlag = true; //indicates whether hierarchy is preselected as default when first time acccess resources

	var _preselect_cb = false;

	var _nodeClick_cb = false;

	var _onExploreFlag = true;

	var gStore = new Ext.data.SimpleStore({
	    fields: ['id', 'name', 'perm_g', 'perm_h'],
		listeners:{
			load:function(store, records, options){
				//pri ucitavanju
			},
			add:function(store, records, index){
				//doda se nova grupa
			},
			remove:function(store, record, index){
				//obrise se grupa
			}
		}
    });


	var gCmb = new Ext.form.ComboBox({
		id: 'sFiles_group_cmb',
		store: gStore,
		displayField: 'name',
		valueField: 'id',
		hideLabel: true,
		tabIndex: 10,
		readOnly: false,
		editable: false,
		//lazyRender: true,
		typeAhead: true,
		mode: 'local',
		triggerAction: 'all',
		selectOnFocus: true,
		listWidth: 150,
		width: 150,
		listeners: {
			select: function(cmb, record, index) {

				if (activeGroup != record.data) {

					var wssStudioHandler = {
						treeSetGroup: function(result){

							if (!result) {
								//show feedback
								Jedox.studio.app.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());
								return false;
							}

							activeGroup = record.data;
							fileTP.root.setText(record.data.name);
							fileTP.root.g_id = record.data.id;
							initHierarchies(activeGroup.id);
//							Ext.getCmp('wt-panel').clear();
//							Ext.getCmp('wt-panel').disableTlb();
							gCmbSelectedIndex = index;
						}
					}


					var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
					wssStudioStub.treeSetGroup('file', record.data.id);
				}
			},
			specialkey: function(el, e){
				this.autoSelect = false;
				switch(e.getKey()){
					case e.ESC:
						this.fireEvent('blur', this);
						break;
					case e.ENTER:
						var value = trim(this.getRawValue());
						if (value){
							this.fireEvent('blur', this, true);
							renameGroupFnc(this.getValue(),  value);
						}
						break;
				}
			},
			blur:function(cb, rnmF){
				this.setEditable(false);
				this.autoSelect = true;
				this.getStore().clearFilter();
				if(!rnmF)
					this.setValue(activeGroup.id);
			}
		}
	});

	var newGroupTlbBtn = {
		//text:'New Group',
		tooltip:{title:'New Folder Group'.localize(), text:'Creates New Group'.localize()},
		iconCls:'new-group-icon',
		handler: onAddGroup,
		scope: this
	}


	var editGTlbBtn = new Ext.SplitButton({
		split: true,
//		text:'Edit',
		tabIndex: 11,
		id: 'sFiles_group_btn',
		iconCls: 'tlb-menu-icon',
		tooltip: {
			title: 'Edit File Group'.localize(),
			text: 'Edit File Group...'.localize()
		},
		handler:function(){
			this.showMenu();
		},
		menu: {
			listeners:{
				beforeshow:function(){

					var perm_g = activeGroup? activeGroup.perm_g:0;

					setContainerInterfacePermission('group', {perm_g:perm_g, perm_h:perm_g});

					gCtxDFlag.newGroup? this.items.items[0].disable():this.items.items[0].enable();
					gCtxDFlag.renameGroup? this.items.items[4].disable():this.items.items[4].enable();
					gCtxDFlag.deleteGroup? this.items.items[5].disable():this.items.items[5].enable();
					gCtxDFlag.exportBundleAll? this.items.items[7].disable():this.items.items[7].enable();
					gCtxDFlag.exportBundle? this.items.items[8].disable():this.items.items[8].enable();
					gCtxDFlag.importBundleAll? this.items.items[9].disable():this.items.items[9].enable();
					gCtxDFlag.importBundle? this.items.items[10].disable():this.items.items[10].enable();
					gCtxDFlag.newHierarchy? this.items.items[12].disable():this.items.items[12].enable();
					gCtxDFlag.properties? this.items.items[14].disable():this.items.items[14].enable();
					perm_g? this.items.items[2].enable():this.items.items[2].disable(); //refresh Btn (disable when no group in list)

				}
			},
			autoWidth:true,
			id: 'sStudio_Files_mn',
			//width: 150,
			items: [{
				text: 'New Folder Group'.localize(),
				iconCls: 'new-group-icon',
				//group: 'rp-view',
				disabled:gCtxDFlag.newGroup,
				handler: onAddGroup,
				scope: this,
				id: 'sFilesGroupMenu_newFG_btn'
			}, '-', {
				text: 'Refresh Folder Group'.localize(),
//				disabled:gCtxDFlag.newHierarchy,
				handler: function(){refreshGroup();},
				iconCls: 'refresh-icon',
				scope: this,
				id: 'sFilesGroupMenu_refreshFG_btn'
			}, '-',{
				text: 'Rename Folder Group'.localize(),
				disabled:gCtxDFlag.renameGroup,
				iconCls: 'rename-icon',
				handler: function(){onRenameGroup();},
				scope: this,
				id: 'sFilesGroupMenu_renameFG_btn'
			}, {
				text: 'Delete Folder Group'.localize(),
				disabled:gCtxDFlag.deleteGroup,
				iconCls: 'delete-icon',
				handler: function(){onDeleteGroup(root);},
				scope: this,
				id: 'sFilesGroupMenu_deleteFG_btn'
			}, '-', {
                text:'Export All Folder Groups'.localize(),
				disabled:gCtxDFlag.exportBundleAll,
				handler: function(){Jedox.studio.files.bundle({t:'file', g:'', h:'', ns:[], 'name':'bundle'})},
				iconCls: 'export-bundle',
                scope: this,
                id: 'sFilesGroupMenu_exportAllFGs_btn'
            }, {
                text:'Export Folder Group'.localize(),
				disabled:gCtxDFlag.exportBundle,
				handler: function(){Jedox.studio.files.bundle({t:'file', g:activeGroup.id, h:'', ns:[], 'name':activeGroup.name})},
				iconCls: 'export-bundle',
                scope: this,
                id: 'sFilesGroupMenu_exportFG_btn'
            }, {
                text:'Import'.localize(),
				disabled:gCtxDFlag.importBundle,
				handler: function(){Jedox.gen.load(Jedox.studio.app.dynJSRegistry.importFile, ['file', {g:'', h:'', p:''}])},
				iconCls: 'import-file',
                scope: this,
                id: 'sFilesGroupMenu_import_btn'
            }, {
                text:'Import Into Group'.localize(),
				disabled:gCtxDFlag.importBundle,
				handler: function(){Jedox.gen.load(Jedox.studio.app.dynJSRegistry.importFile, ['file', {g:activeGroup.id, h:'', p:''}])},
				iconCls: 'import-bundle',
                scope: this,
                id: 'sFilesGroupMenu_importInGroup_btn'
            }, '-', {
				text: 'New Root Folder'.localize(),
				disabled:gCtxDFlag.newHierarchy,
				handler: onAddHierarchy,
				id: 'sFilesGroupMenu_newRootF_btn',
				iconCls: 'add-general',
				scope: this
			}, '-', {
				text: 'Properties'.localize(),
				disabled:gCtxDFlag.properties,
				iconCls: 'properties-icon',
				handler:function(){onGroupProperties(root);},
				scope: this,
				id: 'sFilesGroupMenu_properties_btn'
			}]
		}
	});




	var fTlb = new Ext.Toolbar({
		id:'f-tree-tlb'
		//items:[newGroupTlbBtn, gCmb, newHierarchyTlbBtn]
	});



	var root = new Ext.tree.TreeNode({
		text: 'root',
		draggable: false, // disable root node dragging
		editable:false,
		id: 'root',
		iconCls: 'w3s_group',
		expanded:true
	});

	var fileTP = new Ext.tree.TreePanel({
		id: 'sFiles_tree_tr',
		//tbar:fTlb,
		iconCls: 'folder-icon',
		animate:false,
		border: false,
		lines: true,
		containerScroll: true,
		ddScroll: true,
		autoScroll: true,
		height:50,
		enableDD: true,
		root:root,
		rootVisible: false,
		hidden:true,
		listeners: {
			click: function(node, e){

				if (!_nodeClick_cb) {

					var wssStudioHandler = {
						treeSetHierarchy: function(result){

							if (!result) {
								//show feedback
								Jedox.studio.app.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());
								return false;
							}

							fileTP.fireEvent('click', node);
						}
					}

					if (node.id != 'root') {
						if (node.attributes.type) {
							if (activeHierarchy.id != node.attributes.id) {
								var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
								wssStudioStub.treeSetHierarchy('file', node.attributes.id);
								_nodeClick_cb = true;
								activeHierarchy.id = node.attributes.id;
								return false;
							}
						}
						else
							if (activeHierarchy.id != node.attributes.h_uid) {
								var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
								wssStudioStub.treeSetHierarchy('file', node.attributes.h_uid);
								_nodeClick_cb = true;
								activeHierarchy.id = node.attributes.h_uid;
								return false;
							}
					}
				}
				else{
					_nodeClick_cb = false;
				}

				node.expand();
			},
			select: function(n_uid){
				var id = getNodeId(n_uid);
				var node = this.getNodeById(id);
				this.fireEvent('click', node);
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
			removeHierarchy: function(id){
				var node = this.getNodeById(id);
				if (node)
					node.remove();
			},
			up: function(n_uid){
				if (n_uid == 'root') {
					var parentNode = this.root;
					this.fireEvent('click', parentNode);
				}
				else {
					var id = getNodeId(n_uid);
					var node = this.getNodeById(id);
					if (node) {
						var parentNode = node.parentNode;
						this.fireEvent('click', parentNode);
					}
				}
			},
			addNode: function(n_uid, nodeData, perm_n){
				var newNode = new Ext.tree.TreeNode({
			        text: nodeData.text,
			        n_uid: nodeData.id,
					iconCls:nodeData.iconCls,
					h_uid:activeHierarchy.id,
					id:activeHierarchy.id + '_' + nodeData.id,
					qtip:nodeData.qtip,
					leaf:nodeData.leaf,
					perm_n: perm_n
			    });

				var id = getNodeId(n_uid);
				var parent = this.getNodeById(activeHierarchy.id);

				if (n_uid != 'root')
					parent = this.getNodeById(id);

				parent.appendChild(newNode);

			},
			editId: function(n_uid, newId){
				var id = getNodeId(n_uid);
				var node = this.getNodeById(id);
				node.attributes.id = newId;
				node.id = newId;
			},
			test: function(id){
				var node = this.getNodeById(id);
				node.attributes.loader.load(node);
			},
			replaceNode: function(n_uid, newParentId){ //TODO remane because there is one event listener with the same name

				var id = getNodeId(n_uid);
				var node = this.getNodeById(id);

				var newNode = {
					id:node.attributes.n_uid,
					text: node.attributes.text,
					leaf: node.attributes.leaf,
					qtip:node.attributes.qtip,
					iconCls:node.attributes.iconCls
				}

				this.fireEvent('removeNode', n_uid);
				this.fireEvent('addNode', newParentId, newNode);

			},

			contextmenu: function(node, e){
				selectedNode = fileTP.selModel.getSelectedNode();
				node.select();
				itemClicked = false;

				if (node.id == 'root')
					onGroupCtxMnu(node, e);
				else
					if (node.attributes.type)
						onHierarchyCtxMnu(node, e);
					else
						onFolderCtxMnu(node, e);

			},
			beforenodedrop:function(el){
				var tmpParent = el.target.attributes.h_uid || el.target.attributes.id;
				if (el.dropNode.attributes.h_uid === tmpParent)
					onDDCtxMnu(el, el.rawEvent);
				return false;
			},
			onEditTmpl: function(group, hierarchy, n){
				_onExploreFlag = true;
				preselectOnEditTmpl(group, hierarchy, n, false);
			},
			onRefresh: function(group, hierarchy, n){
				_onExploreFlag = false;
				_triggerSaveAsFromWSS = true;
				refreshFlag = true;
				refreshAndSelectPathButNotOpen(group, hierarchy, n);
			},
			onExplore: function(group, hierarchy, n){
				_onExploreFlag = true;
				refreshAndSelectPathButNotOpen(group, hierarchy, n);
			},
			refreshOnCopy: function(n){
				refreshOnCopy(n);
				refreshFlag = true;
			},
			keyPress:function(myEvent){
				keyboardDispacher(myEvent);
			},
			reloadActiveHierarchy:function(){
				reloadActiveHierarchy();
			},
			onGetPath:function(n_uid, cbFnc){
				if (n_uid == 'root')
					var id = activeHierarchy.id;
				else
					id = getNodeId(n_uid);

				var node = this.getNodeById(id);
				var path = node.getPath(['text']);
				cbFnc('/'.concat(path, '/'));
			},
			onNodeProperties:function(id){
				var node = fileTP.selModel.getSelectedNode();
				if (id == 'root')
					onHierarchyProperties(node);
				else {
					onProperties(node);
				}
			},
			setFolderViewMode:function(n_uid, mode){

				var node = n_uid == 'root'? fileTP.getNodeById(activeHierarchy.id):this.getNodeById(getNodeId(n_uid));

				if (node) {
					node.attributes.view = mode;
				}
			},
			reloadHierarchy:function(){
				reloadHierarchy();
			}
		}
	});


	var editor = new Ext.tree.TreeEditor(fileTP, null, {
		id: 'f-tree-node-editor',
		editDelay: 0,
		cancelOnEsc: true,
		allowBlank: false,
		ignoreNoChange: true,
		completeOnEnter: true,
		beforeNodeClick: Ext.emptyFn,
        onNodeDblClick: Ext.emptyFn,
        onNodeClick: Ext.emptyFn,
		listeners: {
			show: function() {
				this.field.selectText();
			}
		}
	});

	editor.on({
		complete : function(editor, newName, oldName){
			if (newName != oldName) {
				if (validateName(editor.editNode, oldName, newName)) {

					var parentId = editor.editNode.parentNode.attributes.type || editor.editNode.parentNode.attributes.id;
					var id = editor.editNode.attributes.id;

					function onSuccessCbHandler(result){

					}

					function onErrorCbHandler(result){

					}

					(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', parentId, 'renameNode', id, newName]))
						.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

				}
				else
					editor.cancelEdit();
			}
		}

	});


	var fileTreeSorter = new Ext.tree.TreeSorter(fileTP, {});

//	================================ functions ======================================================================


	function initTlb(){
		if (gCmb.rendered){
			if(_preselect_cb)
				_preselect_cb();

			//open recent if exist
			if(Jedox.studio.files.openRecentClb){
				Jedox.studio.files.openRecentClb();
			}

			return ;
		}

		fTlb.addField(gCmb);
		fTlb.add(editGTlbBtn);

		init();
	}


	function init(){

		// call back function
		function initGroups_cb(result){
			if (result){
				// call back function
				function selectGroup_cb(result){
					if (result){
						initHierarchies();
					}
					else{
						//open recent if exist
						if (Jedox.studio.files.openRecentClb)
							Jedox.studio.files.openRecentClb();
					}
				}

				fileTP.show();

				if(_preselect_cb)
					_preselect_cb();
				else
					selectGroup(getDefaultGroupIndex(), selectGroup_cb);
			}
			else {
				//open recent if exist
				if (Jedox.studio.files.openRecentClb)
					Jedox.studio.files.openRecentClb();
			}
		}

		initGroups(initGroups_cb);

	}

	function getDefaultGroupIndex(){
		var index = gStore.find('id', Jedox.studio.app.defaultFiles.group);
		return index != -1? index:0;
	}

	function getGroupIndex(group){
		var index = gStore.find('id', group);
		return index != -1? index:0;
	}

	function getActiveGroupIndex(){
		var index = gStore.find('id', activeGroup.id);
		return index != -1? index:0;
	}


	function initGroups(cb) {

		var wssStudioHandler = {
			treeMngGroup: function(result){

				_groupNameList = {};

				if (result == null) {
					//show feedback
					Jedox.studio.app.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());

					if(cb)
						cb(false);

					return false;
				}

				if (result instanceof Array){
					//no data
					return;
				}

				var gData = [];
//				_groupNameList = {};
				groupExist = true;

				for (var i in result) {
					gData.push([i, result[i].name, result[i].perm_g, result[i].perm_h]);
					_groupNameList[result[i].name] = i;
				}

				gStore.loadData(gData);
				gCmbSelectedIndex = 0;

				if(cb)
					cb(true);
			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.treeMngGroup('', 'listGroups', ['file']);

	}


	function selectGroup(index, cb){

		var wssStudioHandler = {
			treeSetGroup: function(result){

				if (!result) {
					//show feedback
					Jedox.studio.app.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());

					if(cb)
						cb(false);

					return false;
				}

				activeGroup = record.data
				gCmb.setValue(record.data.id);
				fileTP.root.setText(record.data.name);
				fileTP.root.g_id = record.data.id;

				if(cb)
					cb(true);
			}
		}

		if (gStore.getCount() > 0) {
			var record = gStore.getAt(index);

			if (!record)
				record = gStore.getAt(getDefaultGroupIndex());

			var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
			wssStudioStub.treeSetGroup('file', record.data.id);
		}
		else {
			activeGroup = null;
			gCmb.disable();

			if(cb)
				cb(false);

			return false;
		}
	}

	function refreshGroup(){

		// call back function
		function initGroups_cb(result){
			if (result){
				// call back function
				function selectGroup_cb(result){
					if (result)
						initHierarchies();
				}

				selectGroup(getActiveGroupIndex(), selectGroup_cb);
			}
		}

		initGroups(initGroups_cb);
	}


	function reloadHierarchy(){

		var h_node = fileTP.getNodeById(activeHierarchy.id);
	   	var selNode = fileTP.getSelectionModel().getSelectedNode();
		var id = selNode.attributes.id;
	   	var path = (selNode && selNode.ownerTree)? selNode.getPath() : false;

		function cb(){
			h_node.attributes.loader.baseParams.reload = false;

			if (path)
	   			fileTP.expandPath(path, false, function(bSuccess, oLastNode){
					if (bSuccess && oLastNode) {
							var node = fileTP.getNodeById(id);
							if (node){
								refreshFlag = true;
								fileTP.fireEvent('click', node);
							}

					}

				});
		}

		h_node.attributes.loader.baseParams.reload = true;
	   	h_node.reload(cb);
	}


	function initHierarchies(group, cb){

		var that = this;
		_hierarchyNameList = {};

		//remove all childe nodes if any
		var nodes=[];
		fileTP.root.eachChild(function(node){nodes.push(node);}, [fileTP]);
		for (var i=0; i<nodes.length; i++)
			nodes[i].remove();

		if (!group) group = activeGroup.id;
		var hData = [];


		var wssStudioHandler = {
			treeMngHierarchy: function(result){

				if (result != null && !result) {
					//show feedback
					Jedox.studio.app.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());
					return false;
				}



				for (var i in result) {
					fileTP.root.appendChild(new Ext.tree.AsyncTreeNode({
						id: i,
						text: result[i].name,
						draggable: false,
						editable: false,
						iconCls: 'w3s_hierarchy',
						perm_h:result[i].perm_h,
						perm_n:result[i].perm_n,
						view:result[i].view || false,
						type: 'root',
						loader: new Ext.tree.TreeLoader({
							dataUrl: '/be/erpc.php?wam=studio&c=Studio&m=treeDump',
							baseParams: {
								type: 'file',
								hierarchy: i,
								filter: 'folder',
								multi_h: true
							}
						})
					}));
					_hierarchyNameList[result[i].name] = i;
				}


				fileTreeSorter.doSort(fileTP.getRootNode());

				fileTP.root.expand(false, false, function(gNode){

					//callback fnc
					if (cb){
						cb();
						return;
					}


					if (_triggerSaveAsFromWSS){
						_triggerSaveAsFromWSS = false;
						return;
					}


					//preselect default or first hierarchy
					if (fileTP.root.hasChildNodes()){
						if (_defaultHierarchyFlag) {
							var hNode = fileTP.getNodeById(Jedox.studio.app.defaultFiles.hierarchy) || fileTP.getNodeById(fileTP.root.firstChild.attributes.id);
							_defaultHierarchyFlag = false;
						}
						else
							var hNode = fileTP.getNodeById(fileTP.root.firstChild.attributes.id);
					}
					else
						var hNode = fileTP.getNodeById(fileTP.root.attributes.id);


					if (hNode){
						hNode.expand(false, false, function(hNode){
							fileTP.fireEvent('click', hNode);
						});
					}

				});

			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.treeMngHierarchy('file', 'listHierarchies');

	}


	// =============================================================================================================


	function onGroupCtxMnu(node, e){
		var that = this;

		setContainerInterfacePermission({g:activeGroup.id, h:'meta', n:'group'});
		var groupCtxMnu = new Ext.menu.Menu({
			id: 'f-group-ctx-mnu',
			enableScrolling: false,
    		listeners: {
				hide: function(menu){
					menu.destroy();
				}
			},
			items: [{
				text: 'Open'.localize(),
				disabled:gCtxDFlag.open,
				iconCls: 'open-folder-icon',
				handler: function(){
					onOpen(node)
				},
				scope: that
			}, {
				text: 'Delete Group'.localize(),
				disabled:gCtxDFlag.deleteGroup,
				iconCls: 'delete-icon',
				handler: function(){onDeleteGroup(node);},
				scope: that
			}, '-', {
				text: 'New File Repository'.localize(),
				disabled:gCtxDFlag.newHierarchy,
				handler: onAddHierarchy,
				iconCls: 'add-general',
				scope: that
			}, '-', {
				text: 'Properties'.localize(),
				disabled:gCtxDFlag.properties,
				iconCls: 'properties-icon',
				handler:function(){onGroupProperties(node);},
				scope: that
			}]
		});
		groupCtxMnu.on('hide', onContextHide, groupCtxMnu);

		e.stopEvent();
		groupCtxMnu.showAt(e.getXY());
	}

	function onHierarchyCtxMnu(node, e){
		var that = this;
//		activeHierarchy.id = node.attributes.id;
		setContainerInterfacePermission('hierarchy', {perm_h:node.attributes.perm_h, perm_n:node.attributes.perm_n});

		var hierarchyCtxMnu = new Ext.menu.Menu({
			id: 'f-hierarchy-ctx-mnu',
			enableScrolling: false,
    		listeners: {
				hide: function(menu){
					menu.destroy();
				}
			},
			autoWidth:true,
			items: [{
				text: 'Open'.localize(),
				iconCls: 'open-folder-icon',
				disabled:hCtxDFlag.open,
				handler: function(){onOpen(node)},
				scope: that
			}, {
				text: 'Delete Root Folder'.localize(),
				disabled:hCtxDFlag.deleteHierarchy,
				iconCls: 'delete-icon',
				handler: function(){onDeleteHierarchy(node);},
				scope: that
			}, '-', {
				text:'Export'.localize(),
				iconCls: 'export-bundle',
				disabled:hCtxDFlag.exportBundle,
				handler: function(){Jedox.studio.files.bundle({t:'file', g:activeGroup.id, h:activeHierarchy.id, ns:[], 'name':node.attributes.text})},
                scope: that
            },{
				text:'Import'.localize(),
				iconCls: 'import-file',
				disabled:hCtxDFlag.importBundle,
				handler: function(){Jedox.gen.load(Jedox.studio.app.dynJSRegistry.importFile, ['file', {g:activeGroup.id, h:activeHierarchy.id, p:'root'}, getNodes()])},
                scope: that
            }, '-',{
				text: 'Properties'.localize(),
				disabled:hCtxDFlag.properties,
				iconCls: 'properties-icon',
				handler: function(){onHierarchyProperties(node);},
				scope: that
			}]
		});
//		hierarchyCtxMnu.on('hide', onContextHide, hierarchyCtxMnu);

		e.stopEvent();
		hierarchyCtxMnu.showAt(e.getXY());

	}




	function onFolderCtxMnu(node, e){
		var that = this;
		var parent = node.parentNode.attributes.type ? node.parentNode.attributes.id:node.parentNode.attributes.n_uid;
		setContainerInterfacePermission('node', {perm_n:node.attributes.perm_n});

		var folderCtxMnu = new Ext.menu.Menu({
			id: 'f-folder-ctx-mnu',
			enableScrolling: false,
    		listeners: {
				hide: function(menu){
					menu.destroy();
				}
			},
			items: [{
				text: 'Open'.localize(),
				iconCls: 'open-folder-icon',
				handler: function(){
					onOpen(node);
				},
				scope: that
			},
			'-',
//			{
//				text: 'Cut'.localize(),
//				disabled:true,
//				iconCls: 'cut-icon',
//				//handler:function(){var cmp = Ext.getCmp('main-view-panel').layout.activeItem; cmp.fireEvent('edit', cmp);},
//				scope: that
//			}, {
//				text: 'Copy'.localize(),
//				//handler:
//				disabled:true,
//				iconCls: 'copy-icon',
//				scope: that
//			},
//			'-',
			 {
				text: 'Rename'.localize(),
				disabled:fCtxDFlag.rename,
				iconCls: 'rename-icon',
				handler:function(){onRenameFolder(node);},
				scope: that
			}, {
				text: 'Delete'.localize(),
				iconCls: 'delete-icon',
				disabled:fCtxDFlag.remove,
				handler: function(){
					onDeleteFolder(node);
				},
				scope: that
			}, '-', {
				text:'Export'.localize(),
				iconCls: 'export-bundle',
				disabled:fCtxDFlag.exportBundle,
				handler: function(){Jedox.studio.files.bundle({t:'file', g:activeGroup.id, h:activeHierarchy.id, ns:[node.attributes.n_uid], 'name':node.attributes.text})},
                scope: that
            }, {
				text:'Import'.localize(),
				iconCls: 'import-file',
				disabled:fCtxDFlag.importBundle,
				handler: function(){Jedox.gen.load(Jedox.studio.app.dynJSRegistry.importFile, ['file', {g:activeGroup.id, h:activeHierarchy.id, p:node.attributes.n_uid}, getNodes()])},
                scope: that
            }, '-', {
				text: 'Properties'.localize(),
				disabled:fCtxDFlag.properties,
				iconCls: 'properties-icon',
				handler: function(){onProperties(node)},
				scope: that
			}],
			listeners:{
				itemclick : function(baseItem, e){
					itemClicked = true;
				}
			}
		});
		folderCtxMnu.on('hide', onContextHide, folderCtxMnu);

		e.stopEvent();
		folderCtxMnu.showAt(e.getXY());
	}


	function onDDCtxMnu(el, e){
		var that = this;
		var ddCtxMnu = new Ext.menu.Menu({
			id: 'f-group-ctx-mnu',
			enableScrolling: false,
    		listeners: {
				hide: function(menu){
					menu.destroy();
				}
			},
			items: [{
				text: 'Move'.localize(),
				iconCls: 'cut-icon',
				disabled:!(el.target.attributes.perm_n & Jedox.studio.access.permType.WRITE) || !(el.dropNode.attributes.perm_n & Jedox.studio.access.permType.WRITE),
				handler: function(){onMoveNode(el);},
				scope: that
			}, {
				text: 'Copy'.localize(),
				disabled:!(el.target.attributes.perm_n & Jedox.studio.access.permType.WRITE),
				iconCls: 'copy-icon',
				handler:function(){onCopyNode(el);},
				scope: that
			}]
		});
		ddCtxMnu.on('hide', onContextHide, ddCtxMnu);

		e.stopEvent();
		ddCtxMnu.showAt(e.getXY());
	}


	function onContextHide(ctxMnu){
        if(ctxMnu){
            ctxMnu.destroy();
            ctxMnu = null;
        }
//		if (!itemClicked)selectedNode.select();
    }

	// ======================================= CtxMnu handlers =======================================================

	function getNewItemCopyName(target, tmplName){
		var br = 0;
		var exist = true;
		var name = tmplName.toLowerCase();

		while (exist) {
			exist = false;
			if (br == 1)
				name = ('copy_of_name'.localize() + ' ' + tmplName).toLowerCase();
			if (br > 1)
				name = ('copy_num_of_name'.localize({num:br}) + ' ' + tmplName).toLowerCase();
			for (var i = 0; i < target.childNodes.length; i++) {
				if (name === target.childNodes[i].attributes.text.toLowerCase()) {
					br = br + 1;
					exist = true;
					break;
				}
			}
		}

		return (br == 1) ? ('copy_of_name'.localize() + ' ' + tmplName) : ((br > 0) ? ('copy_num_of_name'.localize({num:br}) + ' ' + tmplName) : (tmplName));
	}


	function onCopyNode (el){
		var parentId = el.target.attributes.id;
		var tmpParentId = el.target.attributes.type || parentId;

		if (checkNameAvailable(el.target, el.dropNode.attributes.text)){
			copyNode();
		}
		else{
			var newName = getNewItemCopyName(el.target, el.dropNode.attributes.text);
			copyNode(newName);
		}


		function copyNode(newName){

			function onSuccessCbHandler(newId){

				if (newId){
					if (newName){

						function onSuccessCbHandler(result){
							refreshOnCopy(newId);
						}

						function onErrorCbHandler(result){

						}

						(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', el.dropNode.attributes.id, 'renameNode', newId, newName]))
							.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();
					}
					else {
						refreshOnCopy(newId);
					}

				}
			}

			function onErrorCbHandler(result){
				var title = 'Copy folder'.localize();
				var message = 'copy_folder_error_msg'.localize({'folder_name': el.dropNode.attributes.text});
				Jedox.studio.app.showMessageERROR(title, message);
			}

			(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', el.dropNode.attributes.id, 'copyNode', tmpParentId]))
				.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

		}

	}

	function checkNameAvailable(target, name){
		for (var i=0; i<target.childNodes.length; i++)
			if (name === target.childNodes[i].attributes.text)
				return false;

		return true;
	}

	function getNodeByName(target, name){
		for (var i=0; i<target.childNodes.length; i++)
			if (name === target.childNodes[i].attributes.text)
				return target.childNodes[i];
	}

	function onMoveNode (el){

		/* move in the same folder // do nothing
		 * move in the other folder // do
		 * move in the other folder where one exist woth same name
		 */

//		var node = el.dropNode.attributes.n_uid;
//		var source = el.dropNode.parentNode.attributes.n_uid;
//		var target = el.target.attributes.n_uid;

		if (el.dropNode.parentNode.attributes.n_uid != el.target.attributes.n_uid){// different folder
			if (checkNameAvailable(el.target, el.dropNode.attributes.text)){
				moveNode();
			}
			else{
				var title = 'Confirm Item Replece'.localize();
				var message = 'replace_folder_warning_msg'.localize({'name': el.dropNode.attributes.text});
				var fn = function(){
					var nodeToRemove = getNodeByName(el.target, el.dropNode.attributes.text);
					var tmpParentId = el.target.attributes.type || el.target.attributes.n_uid;

					function onSuccessCbHandler(result){
						fileTP.fireEvent('removeNode', nodeToRemove.attributes.n_uid);
						moveNode();
					}

					function onErrorCbHandler(result){

					}

					(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', tmpParentId, 'removeNode', nodeToRemove.attributes.n_uid]))
						.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

				}

				Jedox.studio.app.showMessageQUESTION(title, message, fn);
			}

		}

		function moveNode(){

			var tmpParentId = el.target.attributes.type || el.target.attributes.n_uid;

				function onSuccessCbHandler(result){
					refreshOnCopy(tmpParentId);
				}

				function onErrorCbHandler(result){
//					var title = 'Cut folder'.localize();
//					var message = 'cut_folder_error_msg'.localize({'folder_name': el.dropNode.attributes.text});
//					Jedox.studio.app.showMessageERROR(title, message);
				}

				(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', el.dropNode.attributes.n_uid, 'moveNode', tmpParentId]))  //move in the database to database
					.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();
		}

	}

	function onOpen(node){
		refreshFlag = true;
		fileTP.fireEvent('click', node);
	}



	function setGroupData(group, name, description){

		function onSuccessCbHandler(result){
			fileTP.fireEvent('select', 'root');
			//initHierarchies(activeGroup.id);
		}

		function onErrorCbHandler(result){

		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'setGroupPropertiesData', ['file', group, name, description]))
			.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

	}


	function onAddGroup(){

		var that = this;

		var fn = function(gName, gDesc){

			var wssStudioHandler = {
				treeMngGroup: function(result){

					if (!result) {
						//show feedback
						Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
						return false;
					}

					// call back function
					function initGroups_cb(result){
						if (result){
							fileTP.show();
							gCmb.fireEvent('select', gCmb, gStore.getAt(gStore.getCount() - 1), (gStore.getCount() - 1));
							gCmb.setValue(gName);
						}
					}

					initGroups(initGroups_cb);

				}
			}

			var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
			wssStudioStub.treeMngGroup('', 'addGroup', 'file', {name: gName, desc: gDesc});


//----------------- New RPCAsyncRqst ------------------------------
//			function onSucccessCbHandler(result){
//
//					console.log('onSucccessCbHandler', result);
//					// call back function
//					function initGroups_cb(result){
//						if (result){
//							fileTP.show();
//							gCmb.fireEvent('select', gCmb, gStore.getAt(gStore.getCount() - 1), (gStore.getCount() - 1));
//							gCmb.setValue(gName);
//						}
//					}
//
//					initGroups(initGroups_cb);
//			}
//
//			function onErrorCbHandle(){
//				console.log('onErrorCbHandler');
//			}
//
//			(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngGroup', ['', 'addGroup', 'file', {name: gName, desc: gDesc}]))
//				.setOnSuccess([that, onSucccessCbHandler]).setOnError([that, onErrorCbHandle]).send();
//
//--------------------------------------------------------------------

		}

		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openAddGroup, ['New', fn, _groupNameList]);
	}


	function onGroupProperties (node){

		var renameFnc = function(gName, gDesc){

			if (gName in _groupNameList && _groupNameList[gName] != activeGroup.id) {
				var title = 'Error Renaming Group'.localize();
				var msg = 'rename_group_error_msg'.localize({'new_name':gName});
				Jedox.studio.app.showMessageERROR(title, msg);
			}
			else {
				setGroupData(activeGroup.id, gName, gDesc);
				var index = gStore.find('id', activeGroup.id);
				var record = gStore.getAt(index);
				record.set('name', gName);
				gCmb.setValue(activeGroup.id);
				root.setText(gName);
				updateList(_groupNameList, activeGroup.name, gName);
				activeGroup.name = gName;
			}
		}

		var refreshFnc = function(){

			// call back function
			function initGroups_cb(result){
				if (result){
					// call back function
					function selectGroup_cb(result){
						if (result)
							initHierarchies();
					}

					selectGroup(getActiveGroupIndex(), selectGroup_cb);
				}
			}

			initGroups(initGroups_cb);
		}

		function onSuccessCbHandler(data){
			Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openProperties, ['group', data, renameFnc, refreshFnc]);
		}

		function onErrorCbHandler(result){

		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'getGroupPropertiesData', ['file']))
			.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

	}

	function updateList(list, oldKey, newKey){
		var value = list[oldKey];
		list[newKey] = value;
		delete list[oldKey];
	}


	var renameGroupFnc = function(gId, gName){

			if (gName in _groupNameList && _groupNameList[gName] != activeGroup.id) {
				gCmb.setValue(activeGroup.id);
				var title = 'Error Renaming Group'.localize();
				var msg = 'rename_group_error_msg'.localize({
					'new_name': gName
				});
				Jedox.studio.app.showMessageERROR(title, msg);

			}
			else {

				var wssStudioHandler = {
					setGroupPropertiesData: function(result){

						if (!result) {
							//show feedback
							Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
							return false;
						}


						//initGroups();
						var index = gStore.find('id', activeGroup.id);
						var record = gStore.getAt(index);
						record.set('name', gName);
						gCmb.setValue(activeGroup.id);
						root.setText(gName);
						updateList(_groupNameList, activeGroup.name, gName);
						activeGroup.name = gName;
					}
				}

				var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
				wssStudioStub.setGroupPropertiesData('file', gId, gName, null);
			}

	}


	function onRenameGroup(){
		gCmb.setEditable(true);
		gCmb.focus(true);
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;
	}


	function onDeleteGroup(node){
		var title = 'Remove Group'.localize();
		if (gStore.getCount() == 1) {
			var errMsg = 'Can not delete group!'.localize();
			Jedox.studio.app.showMessageERROR(title, errMsg);
			return false;
		}
		//var msg = 'You are about to remove <b>' + node.attributes.text + '</b> group. This will remove all the hierarchies and all files within.<br>Are you sure you want do this?';
		var msg = 'remove_group_warning_msg'.localize({'name':node.attributes.text});
		var fn = function(){

			var wssStudioHandler = {
				treeMngGroup: function(result){

					if (!result) {
						//show feedback
						Jedox.studio.app.showMessageERROR('Delete Folder Group'.localize(), 'An error occured? Can not delete Folder Group!'.localize());
						return false;
					}

					init();
					Jedox.studio.app.showTopMsg('', 'Group removed successefully'.localize());
				}
			}

			var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
			wssStudioStub.treeMngGroup('file', 'removeGroup', node.g_id);

		}

		Jedox.studio.app.showMessageQUESTION(title, msg, fn);
	}


	function setHierarchyData(group, hierarchy, name, description, path){

		function onSucccessCbHandler(){
			initHierarchies(activeGroup.id);
			fileTP.fireEvent('select', 'root');
		}

		function onErrorCbHandle(){
			Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'setHierarchyPropertiesData', ['file', group, hierarchy, name, description, path]))
			.setOnSuccess([this, onSucccessCbHandler]).setOnError([this, onErrorCbHandle]).send();
	}


	function onAddHierarchy(){
		var fn = function(hName, hDesc, hPath){

			var wssStudioHandler = {
				treeMngHierarchy: function(result){

					if (!result) {
						//show feedback
						Jedox.studio.app.showMessageERROR('Database write error'.localize(), 'write_data_err'.localize());
						return false;
					}

					initHierarchies(activeGroup.id);

				}
			}

			var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
			wssStudioStub.treeMngHierarchy('file', 'addHierarchy', 'file', {name: hName, desc:hDesc, backend:{type:'local', location:hPath}});
		}
		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openAddHierarchy, [activeGroup.id, fn, _hierarchyNameList]);
	}


	function onHierarchyProperties (node){

		var renameFnc = function(hName, hDesc, hPath){

			if (hName != node.attributes.text && hName in _hierarchyNameList) {
				var title = 'Error Renaming Hierarchy'.localize();
				var msg = 'rename_hierarchy_error_msg'.localize({
					'new_name': hName
				});
				Jedox.studio.app.showMessageERROR(title, msg);
			}
			else {
				setHierarchyData(activeGroup.id, node.attributes.id, hName, hDesc, hPath);
			}
		}


		var refreshFnc = function(permission){
			if (permission == 'N')
				initHierarchies(activeGroup.id);
			else {
				var h_node = fileTP.getNodeById(activeHierarchy.id);
				var map = {'N':0, 'R':1, 'W':3, 'D':7}
				h_node.attributes.perm_h = map[permission];
				h_node.reload();
				h_node.select();
			}
		}

		function onSuccessCbHandler(data){
			Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openProperties, ['hierarchy', data, renameFnc, refreshFnc]);
		}

		function onErrorCbHandler(result){

		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'getHierarchyPropertiesData', ['file', node.attributes.id]))
			.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

	}


	function onDeleteHierarchy(node){
		var title = 'Remove Hierarchy'.localize();
		var msg = 'remove_hierarchy_warning_msg'.localize({'name': node.attributes.text});
		var fn = function(){

			var wssStudioHandler = {
				treeMngHierarchy: function(result){

					if (!result) {
						//show feedback
						Jedox.studio.app.showMessageERROR('Remove Hierarchy'.localize(), 'An error occured? Can not delete this hierarchy!'.localize());
						return false;
					}

					fileTP.fireEvent('removeHierarchy', node.attributes.id);
					Jedox.studio.app.showTopMsg('', 'Hierarchy removed successefully'.localize());
					Ext.getCmp('wt-panel').clear();
					Ext.getCmp('wt-panel').disableTlb();

					Jedox.studio.app.reportsRefreshFlag = true;
				}
			}

			var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
			wssStudioStub.treeMngHierarchy('file', 'removeHierarchy', node.attributes.id);

		}

		Jedox.studio.app.showMessageR_QUESTION_YND({nodes:['root'], container:true}, title, msg, fn);
	}


	function onDeleteFolder(node){
		var title = 'Remove Folder'.localize();
		var msg = 'remove_folder_warning_msg'.localize({'name':node.attributes.text});
		var fn = function(){
			var parentId = node.parentNode.attributes.id;
			var tmpParentId = node.parentNode.attributes.type || parentId;

			var wssStudioHandler = {
				treeMngNode: function(result){

					if (!result) {
						//show feedback
						Jedox.studio.app.showMessageERROR('Remove Folder'.localize(), 'An error occured? Can not delete this item!'.localize());
						return false;
					}

					fileTP.fireEvent('removeNode', node.attributes.n_uid);
					Jedox.studio.app.showTopMsg('', 'Folder removed successefully'.localize());
					fileTP.fireEvent('select', parentId);

					Jedox.studio.app.reportsRefreshFlag = true;
				}
			}

			var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
			wssStudioStub.treeMngNode('file', tmpParentId, 'removeNode', node.attributes.id);

		}

		Jedox.studio.app.showMessageR_QUESTION_YND({nodes:[node.attributes.n_uid], container:true}, title, msg, fn);
	}


	function onRenameFolder(node){
		editor.triggerEdit(node);
//		setTimeout('document.getElementById(\'tree-node-editor\').select()', 400);
	}

	function onProperties(node){

		function renameHandleFnc(newName){
			if (validateName(node, node.attributes.text, newName)) {
				var parentId = node.parentNode.attributes.type || node.parentNode.attributes.id;
				var id = node.attributes.id;

				function onSuccessCbHandler(result){
					node.setText(newName);
				}

				function onErrorCbHandler(result){

				}

				(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngNode', ['file', parentId, 'renameNode', id, newName]))
					.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

			}
		}

		var refreshFnc = function(){
			reloadActiveHierarchy();
		}

		function onSuccessCbHandler(data){
			Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openProperties, ['file', data, renameHandleFnc, refreshFnc]);
		}

		function onErrorCbHandler(result){

		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'getNodePropertiesData', ['file', activeGroup.id, activeHierarchy.id, node.attributes.n_uid]))
			.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

	}


	function reloadActiveHierarchy(){
		var h_node = fileTP.getNodeById(activeHierarchy.id);
		h_node.reload();
		fileTP.fireEvent('select', activeHierarchy.id);
	}

	function test(parentNode, name){
		parentNode.eachChild(function(node){console.log(node.attributes.text)}, [this]);
	}


	function getNodeId(n_uid){
		if (fileTP.getNodeById(n_uid))
			return n_uid;

		return activeHierarchy.id + '_' + n_uid;
	}

	function validateName(node, oldName, newName){
		var parent = node.parentNode;
		var _return = true;
		if (oldName != newName) {
			if (newName.length > 0 && newName.length < 64 ) {
				parent.eachChild(function(node){
					if (node.attributes.text.toLowerCase() == newName.toLowerCase()) {
						_return = false;
					}
				}, [this]);
			}
			else {
				var title = 'Error Renaming File or Folder'.localize();
				var msg = 'rename_item_long_error_msg'.localize({'old_name':oldName, 'new_name':newName});
				var fn = function(){
					node.setText(oldName);
//					node.text = oldName;
//					node.attributes.text = oldName;
					editor.triggerEdit(node);
//					setTimeout('document.getElementById(\'tree-node-editor\').select()', 400);
				}
				Jedox.studio.app.showMessageQUESTIONERROR(title, msg, fn);
				return false;
			}
		}


		if (!_return){
			var title = 'Error Renaming Folder'.localize();
			//var msg = 'Cannnot rename <b>' + oldName + '</b>: <br>A file with <b>' + newName + '</b> name, you specified already exists. Specify a different file name.';
			var msg = 'rename_folder_error_msg'.localize({'old_name':oldName, 'new_name':newName});
			var fn = function(){
				node.setText(oldName);
//				node.text = oldName;
//				node.attributes.text = oldName;
				editor.triggerEdit(node);
//				setTimeout('document.getElementById(\'tree-node-editor\').select()', 400);
			}
			Jedox.studio.app.showMessageQUESTIONERROR(title, msg, fn);
		}

		return _return;
	}

	function trim(s){
		return s.replace(/^\s+|\s+$/g, '');
	}


	function preselectOnEditTmpl(group, hierarchy, n, NOTopenFlag){

		var that = this;

	/**
	 * expand files tab
	 * select group
	 * init hierarchy
	 * expand parent node
	 * do click on parent on left
	 * select file on right
	 * open in new tab wss...
	 */

		_preselect_cb = function(){

			for (var i = 0, count = gStore.getCount(); i < count; i++)
				if (gStore.getAt(i).get('id') == group)
					break;

			selectGroup(i, function(result){

				if (result) {

					initHierarchies(group, function(){
						var hNode = fileTP.getNodeById(hierarchy);

						if (!hNode) {
							Jedox.studio.app.showMessageERROR('File Reference error'.localize(), 'files_ref_err_msg'.localize());
							return false;
						}

							hNode.expand(false, false, function(hNode){

							function onSuccessCbHandler(result){

								if (!result[0]) {
									//show feedback
									Jedox.studio.app.showMessageERROR('File Reference error'.localize(), 'files_ref_err_msg'.localize());
									return false;
								}

								var path = '/root/' + result[1];
								fileTP.expandPath(path, false, function(bSuccess, oLastNode){
									if (bSuccess && oLastNode) {
										if (result.length == 2 && result[1]) {
											var id = result[1].split('/')[result[1].split('/').length - 1];
											var node = fileTP.getNodeById(id);

											if (node) {
												fileTP.fireEvent('click', node);
												setTimeout(function(){//TODO rewrite
													Ext.getCmp('wt-panel').editWB(group, hierarchy, n, NOTopenFlag);
												},500);

											}
										}
									}

								});
							}


							(new Jedox.backend.RPCAsyncRqst('Studio', 'getElementPath', [group, hierarchy, n]))
								.setOnSuccess([that, onSuccessCbHandler]).send();


							});


					});
				}
			});

			_preselect_cb = false;
		}

		if(_onExploreFlag){
			_onExploreFlag = false;
			Ext.getCmp('sFiles_treeHolder_pnl').expand();
		}
		else{
			initTlb();
			Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;
		}


	}


	function refreshAndSelectPathButNotOpen(group, hierarchy, n){
//		console.log('refreshAndSelectPathButNotOpen');
		preselectOnEditTmpl(group, hierarchy, n, true)
	}


	function refreshOnCopy(n){

		var hNode = fileTP.getNodeById(activeHierarchy.id);
		hNode.reload(function(){

			hNode.expand(false, false, function(hNode){

				if (n != 'root'){
					var wssStudioHandler = {
						getElementPath: function(result){

							if (!result[0]) {
								//show feedback
								Jedox.studio.app.showMessageERROR('Database read error'.localize(), 'read_data_err'.localize());
								return false;
							}

							var path = '/root/' + result[1] + '/' + activeHierarchy.id + '_' + n;

							fileTP.expandPath(path, false, function(bSuccess, oLastNode){
								if (bSuccess && oLastNode) {
									if (result.length == 2 && result[1]) {
										var id = activeHierarchy.id + '_' + n;
										var node = fileTP.getNodeById(id);
										fileTP.fireEvent('click', node);
									}
								}

							});
						}
					}

					var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
					wssStudioStub.getElementPath(activeGroup.id, activeHierarchy.id, n);
				}
			});
		});

	}


	//nodes for import wizard to validate names
	function getNodes(){
		return Ext.getCmp('wt-panel').getNodes();
	}







	/**
	 * Set interface permissions
	 */



	function setContainerInterfacePermission(type, permObj){

		switch (type){
		    case 'group':
				setGroupInterfacePermission(permObj);
		        break;
		    case 'hierarchy':
				setHierarchyInterfacePermission(permObj);
		        break;
		    case 'node':
				setFolderInterfacePermission(permObj);
		        break;
		}


		function setGroupInterfacePermission(permObj){
//				console.log('setGroupInterfacePermission');
				var permType = Jedox.studio.access.permType;

				gCtxDFlag.exportBundleAll = !(Jedox.studio.access.perm_g & permType.WRITE); //allowed to read
				gCtxDFlag.importBundleAll = !(Jedox.studio.access.perm_g & permType.WRITE); //allowed to write

				gCtxDFlag.newGroup = !(Jedox.studio.access.perm_g & permType.WRITE);
				gCtxDFlag.renameGroup = !(permObj.perm_g & permType.WRITE);
				gCtxDFlag.deleteGroup = !(permObj.perm_g & permType.DELETE);
				gCtxDFlag.exportBundle = !(permObj.perm_g & permType.WRITE); //allowed to write into group
				gCtxDFlag.importBundle = !(permObj.perm_g & permType.WRITE); //allowed to write into group
				gCtxDFlag.properties = !(permObj.perm_g & permType.WRITE);
				gCtxDFlag.newHierarchy = !(permObj.perm_h & permType.WRITE);

		}


		function setHierarchyInterfacePermission(permObj){
//				console.log('setHierarchyInterfacePermission');
				var permType = Jedox.studio.access.permType;

				hCtxDFlag.deleteHierarchy = !(permObj.perm_h & permType.DELETE);
				hCtxDFlag.exportBundle = !(permObj.perm_h & permType.WRITE); //allowed to write into hierarchy
				hCtxDFlag.importBundle = !(permObj.perm_h & permType.WRITE); //allowed to write into hierarchy
				hCtxDFlag.properties = !(permObj.perm_h & permType.WRITE);
		}


		function setFolderInterfacePermission(permObj){
//				console.log('setFolderInterfacePermission');
				var permType = Jedox.studio.access.permType;

				fCtxDFlag.rename = !(permObj.perm_n & permType.WRITE);
				fCtxDFlag.remove = !(permObj.perm_n & permType.DELETE);
				fCtxDFlag.exportBundle = !(permObj.perm_n & permType.WRITE); //allowed write into folder
				fCtxDFlag.importBundle = !(permObj.perm_n & permType.WRITE); //allowed write into folder
				fCtxDFlag.properties = !(permObj.perm_n & permType.WRITE);
		}

	}



	/**
	 * Tree keyboard events
	 */

	function keyboardDispacher(myEvent){
		var that = Ext.getCmp('wt-panel');

		var o = {13:onENTER, 113:onF2, 46:onDELETE}


		if (myEvent.keyCode in o)
			o[myEvent.keyCode]();


		function onENTER(){
//			console.log('ENTER');
			var node = fileTP.selModel.getSelectedNode();
			if(node){
				refreshFlag = true;
				fileTP.fireEvent('click', node);
			}
		}

		function onF2(){
//			console.log('F2');
			var node = fileTP.selModel.getSelectedNode();

			if ((node.attributes.perm_h || node.attributes.perm_n) & Jedox.studio.access.permType.WRITE){
				onRenameFolder(node);
			}
			else {
				var title = 'Warning'.localize();
				var msg = 'You have no permission for this operation'.localize();
				Jedox.studio.app.showMessageERROR(title, msg);
			}

		}

		function onDELETE(){
//			console.log('DELETE');
			var node = fileTP.selModel.getSelectedNode();

			if ((node.attributes.perm_h || node.attributes.perm_n) & Jedox.studio.access.permType.DELETE){
				if (node.attributes.type == 'root')
					onDeleteHierarchy(node);
				else
					onDeleteFolder(node);
			}
			else {
				var title = 'Warning'.localize();
				var msg = 'You have no permission for this operation'.localize();
				Jedox.studio.app.showMessageERROR(title, msg);
			}
		}

	}

	//refresh function exposed for import bundle wizard
	Jedox.studio.files.refreshGH = function(){

		if (gCmb.rendered) {

			var selNode = fileTP.getSelectionModel().getSelectedNode();
			var id = selNode? selNode.attributes.id:null;
			var path = (selNode && selNode.ownerTree) ? selNode.getPath() : false;

			function initGroupsCbFnc(){

				function selectGroupCbFnc(){

					function initHierarchiesCbFnc(){
						if (path && path != '/root')
							fileTP.expandPath(path, false, function(bSuccess, oLastNode){
								if (bSuccess && oLastNode) {
									var node = fileTP.getNodeById(id);
									if (node){
										refreshFlag = true;
										fileTP.fireEvent('click', node);
									}
								}
							});
					}

					initHierarchies(activeGroup.id, initHierarchiesCbFnc);

				}

				selectGroup(getGroupIndex(activeGroup.id), selectGroupCbFnc);

			}

			initGroups(initGroupsCbFnc);
		}

	}


	//TODO: rewrite for click on hierarchy
	fileTP.on('click', function(n){
//		console.log(n);
		Ext.getCmp('wt-panel').activateFilesTab();
		var sn = fileTP.selModel.getSelectedNode() || {}; // selNode is null on initial selection
		if (n.id != sn.id && n.id != 'root' || refreshFlag) {
			if (n.attributes.type) {
				Ext.getCmp('wt-panel').initWTData(n.attributes.type, activeGroup.id, activeHierarchy.id, n.attributes.perm_n, n.attributes.view, n.attributes.text);
			}

			else {
				Ext.getCmp('wt-panel').initWTData(n.attributes.n_uid, activeGroup.id, activeHierarchy.id, n.attributes.perm_n, n.attributes.view, n.attributes.text);
			}

			refreshFlag = false;
		}
		else
			if (n.id == 'root') {
				Ext.getCmp('wt-panel').clear();
				Ext.getCmp('wt-panel').disableTlb();
			}


		//open recent after all init
		if (Jedox.studio.files.openRecentClb)
			Jedox.studio.files.openRecentClb();

//		Ext.getCmp('wt-panel').activateFilesTab();
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_navigation_FILES;

	});



	var mainPanel = new Ext.Panel({
		id:'rt-main-panel',
		tbar:fTlb,
		//tbar:[gCmb, editGTlbBtn, {text:'Novi'}, newHierarchyTlbBtn],
		border:false,
		autoScroll: true,
		items:[fileTP],
		listeners:{
			    initTlb: function(p){
				initTlb();
			}
		}
	});


	return mainPanel;
}