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
 * Andrej Vrhovac <andrej.vrhovac@develabs.com>
 *
 * \version
 * SVN: $Id: QuickPublish.js 5022 2011-06-01 07:35:29Z lukap $
 *
 */

Jedox.wss.dlg.quickPublish = function() {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.QuickPublish());
};

Jedox.wss.dlg.QuickPublish = (function() {

	return function () {

		Jedox.wss.dlg.QuickPublish.parent.constructor.call(this);
		this.id = 'QuickPublish';
		var that = this;


		if (!Jedox.wss.app.activeBook._meta)
			{
			Ext.Msg.show({
				   title:'Quick Publish'.localize(),
				   msg: '_QP_unsaved_warning'.localize(),
				   buttons: Ext.Msg.YESNO,
				   fn: function(btn){
						if(btn=='yes') Jedox.gen.load(Jedox.wss.app.dynJSRegistry.open, ['saveqp']);
					},
				   animEl: 'elId',
				   icon: Ext.MessageBox.WARNING
				});
			return;
		}

		// Direct exporting workbook to report dialog
		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		var studio = Jedox.backend.studio;

		var groupData = [];
		var groupStore;
		var _groups;
		var hierarchyData = [];
		var _hierarchies;
		var hierarchyStore;
		var _i;
		var selectedNode
		var group = {
				index : '',
				group : '',
				name : ''
		};
		var hierarchy = {
				index : '',
				hr : '',
				name : ''
		};

		var pNode;

		var loadGroups = function() {
			groupData = [];
			// adding groups
			_groups = studio.treeMngGroup('', 'listGroups', [ 'report' ]);
			for ( var i in _groups) {
				groupData.push( [ i, _groups[i].name ]);
			}
			;
		};

		var loadHierarchies = function() {
			hierarchyData = [];
			_hierarchies = studio.treeMngHierarchy('wss_report', 'listHierarchies');
			if (!_hierarchies) {
				_i = false;
			} else {
				_i = true;
				if (Ext.getCmp('sReports_tree_tr')) {
				}

				for ( var i in _hierarchies) {
					hierarchyData.push( [ i, _hierarchies[i].name ]);
				}
			}
		};

		groupStore = new Ext.data.SimpleStore( {
			fields : [ 'group', 'name' ],
			data : groupData
		});
		hierarchyStore = new Ext.data.SimpleStore( {
			fields : [ 'hierarchy', 'name' ],
			data : hierarchyData
		});
		// LOADING GROUPS
		loadGroups();
		group.name = groupData[0][1];
		group.index = 0;
		group.group = groupData[0][0];
		studio.treeSetGroup('wss_report', group.group);

		// LOADING HIERARCHIES
		loadHierarchies();
		hierarchy.index = 0;
		hierarchy.name = hierarchyData[0][1];
		hierarchy.hr = hierarchyData[0][0];
		studio.treeSetHierarchy('wss_report', hierarchy.hr);

		// END OF LOAD

		groupStore.loadData(groupData);
		hierarchyStore.loadData(hierarchyData);

		var docTitle = Jedox.wss.app.activeBook._name;

		var groupCombo = this.cmpFocus = new Ext.form.ComboBox( {
			id : 'sReports_group_cmb',
			store : groupStore,
			displayField : 'name',
			hideLabel : true,
			readOnly : false,
			tabIndex: 1,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			editable : false,
			lazyRender : true,
			typeAhead : true,
			mode : 'local',
			triggerAction : 'all',
			value : groupData[0][1],
			selectOnFocus : true,
			listWidth : 145,
			width : 145,
			listeners : {
			select : function(cmb, rec, index) {
			group.index = index;
			studio.treeSetGroup('wss_report', groupData[index][0]);
			loadHierarchies();
			group.group = groupData[index][0];
			if (_i) {
				hierarchy.hr = hierarchyData[0][0];
				studio.treeSetHierarchy('wss_report', hierarchyData[0][0]);
				hierarchyStore.loadData(hierarchyData);
				hierarchyCombo.setValue(hierarchyData[0][1]);
				group.group = groupData[index][0];

				treeLoader.baseParams.hierarchy = hierarchy.hr;
				tree.root.reload();
				tree.root.setText(hierarchyData[0][1]);

				hierarchy.name = hierarchyData[0][1];

				hierarchyCombo.enable();
				Ext.getCmp('publishBtn').enable();
			} else {
				hierarchyCombo.setValue('');
				hierarchyCombo.disable();
				treeLoader.baseParams.hierarchy = '';
				tree.root.setText('');
				tree.root.reload();
				Ext.getCmp('publishBtn').disable();
			}

		}
		}
		});

		var hierarchyCombo = new Ext.form.ComboBox(
				{
					store : hierarchyStore,
					id : 'hierarchyComboTB',
					displayField : 'name',
					hideLabel : true,
					disabled : false,
					editable : false,
					readOnly : false,
					typeAhead : true,
					lazyRender : true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 2,
					lazyInit : true,
					mode : 'local',
					triggerAction : 'all',
					value : hierarchyData[0][1],
					selectOnFocus : true,
					listWidth : 145,
					width : 145,
					listeners : {
					select : function(cmb, rec, index) {
					if (!hierarchyData[index])
						index = 0;
					hierarchy.hr = hierarchyData[index][0];
					hierarchy.index = index;
					hierarchy.name = hierarchyData[index][1];
					studio.treeSetHierarchy('wss_report',
							hierarchyData[index][0]);
					treeLoader.baseParams.hierarchy = hierarchy.hr;

					tree.root.reload();
					tree.root.setText(hierarchyData[index][1]);
				}
				}
				});

		var Tree = Ext.tree;

		var treeLoader = new Tree.TreeLoader( {
			dataUrl: '/be/erpc.php?wam='.concat(Jedox.wss.app.appModeS, '&c=Studio&m=treeDump'),
			baseParams : {
			type : 'wss_report',
			hierarchy : hierarchy.hr,
			filter: 'rfolder'
		},
		preloadChildren : true
		});

		var ttb = new Ext.Toolbar({
			items:[
				{xtype: 'tbtext', text: 'Group'.localize().concat(':')},
				groupCombo,
				{xtype:'tbseparator'},
				{xtype: 'tbtext', text:'Hierarchy'.localize().concat(':') },
				hierarchyCombo
			       ]
		});

		var tree = new Tree.TreePanel( {
			id : 'sReports_tree_tr',
			autowidth : true,
			hidden : false,
			animate : false,
			rootVisible : true,
			autoScroll : true,
			containerScroll : true,
			ddScroll : true,
			border : true,
			loader : treeLoader,
			enableDD : false,
			height: 260,
			listeners : {
			click : function(node, e) {
			pNode = node.attributes.id;
		}
		}

		        // ///////////////////////////////// END OF TOOLBAR
		});

		var initRootText;
		initRootText = (hierarchyData.length == 0)? '': hierarchyData[hierarchy.index][1];
		// set the root node
		var root = new Tree.AsyncTreeNode({
			text: initRootText,
			draggable:false, // disable root node dragging
			id:'root',
			expanded: true,
			iconCls: 'w3s_hierarchy',
			editable: false,
			loader: treeLoader
		});
		tree.setRootNode(root);

		var rName = new Ext.form.TextField({
			id: 'rName',
			value: docTitle,
			tabIndex: 4,
			width: 299,
			fieldLabel: 'Report name'.localize(),
			validator: function(vl){
			if (vl.replace(/^\s+|\s+$/g, '') == '') {
				Ext.getCmp('publishBtn').disable();
				return 'Report must have name'.localize();
			}
			else {
				Ext.getCmp('publishBtn').enable();
				return true;
			}
		}
		});

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
	       	baseCls: 'x-plain',
	    	layout: 'form',
	    	autoHeight: true,
	    	items: [
	    	         {
	    	        	 html: '_QP_directions'.localize(),
	    	        	 baseCls: 'x-plain',
	    	        	 bodyStyle: 'margin-bottom: 10px;'
	    	         },
	    	         ttb,
	    	         tree,
	    	         {
	    	        	 bodyStyle: 'padding-top: 10px;',
	    	        	 items: rName,
	    	        	 layout: 'form',
	    	        	 baseCls: 'x-plain'
	    	         }
	    	         ]
		});

		this.win = new Ext.Window(
				{
					title : 'Quick Publish'.localize(),
					closable : true,
					id : 'quick-publish',
					autoDestroy : true,
					cls: 'default-format-window',
					plain : true,
					constrain : true,
					modal : true,
					resizable : false,
					enableHdMenu : false,
					onEsc: Ext.emptyFn,
					animCollapse : false,
					width : 440,
					height : 440,
					layout : 'fit',
					bodyStyle : 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
					listeners : {
						close : function() {
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.quickPublish);
							studio.removeFromSessionCurrGH('wss_report');
						},
						show:function(){
							setTimeout(function(){
								that.initFocus(true, 100);
							});
						},
						activate: function(win) {that.activate();}
					},
					items : [mainPanel],
			         buttons : [
							(this.components.OK = new Ext.Button({
								text: 'Publish'.localize(),
								id: 'publishBtn',
								tabIndex: 10,
								handler: function(){
									publish();
								}
							})),
							(this.components.Cancel = new Ext.Button({
								text: 'Cancel'.localize(),
								tabIndex: 11,
								ctCls: Jedox.kbd.Base.tags.NO_ENTER,
								handler: function(){
									that.win.close();
								}
							}))
							]
				});

		function trim(s){
			return s.replace(/^\s+|\s+$/g, '');
		};

		function validateName(nname, children, selected) {

			var n = 0;
			var is = true;
			nname = trim(nname);
			var name = nname;

			while (is) {
				is = false;
				if ( n > 0 ) {
					name = nname + ' (' + (n) + ')';
				}
				for (var i = 0; i < children.length; i++) {
					if ((trim(children[i].text.toLowerCase()) == name.toLowerCase())) {
						n++;
						is = true;
					}
				}
			}
			return name;

		};



		function publish(){
			// do publishing
			if (!pNode) {
				Ext.Msg.show({
					title : 'Quick Publish'.localize(),
					msg : '_QP_noSelection'.localize(),
					buttons : Ext.Msg.OK,
					animEl : 'elId',
					icon : Ext.MessageBox.WARNING
				});
				return;
			}

			// check for duplicates
			var content = studio.treeMngNode('wss_report', pNode, 'dump', 0);
			docTitle = rName.getValue();
			var noDouble = false;
			for (var q=0; q<content.length; q++){
				if ((content[q].text == docTitle) && content[q].leaf) noDouble = true;
			}
			if (noDouble){
				Ext.Msg.show({
					title:'Quick Publish'.localize(),
					msg: '_QP_double_warning'.localize({'rName':docTitle}),
					buttons: Ext.Msg.OK,
					fn: function(btn){
					// validate new name
					var nnm = validateName(docTitle, content, true);
					rName.setValue(nnm);
					docTitle = nnm;
					rName.focus(true, 10);
				},
				animEl: 'elId',
				icon: Ext.MessageBox.WARNING
				});
			}
			else {
				var src = Jedox.wss.app.activeBook._meta;
				var pb = studio.treeMngNode('wss_report', pNode, 'addNode', true, 'template', {
					name: docTitle,
					'ref': {
					'group': src.g,
					'hierarchy': src.h,
					'node': src.n,
					'type': 'workbook'
				}
				});
				if(pb)
				{
					Ext.Msg.show( {
						title : 'Quick Publish'.localize(),
						msg : '_QP_success'.localize(),
						buttons : Ext.Msg.OK,
						animEl : 'elId',
						icon : Ext.MessageBox.INFO,
						fn: function(){that.win.close();}
					});
				}
				else{
					Ext.Msg.show( {
						title : 'Quick Publish'.localize(),
						msg : '_QP_error'.localize(),
						buttons : Ext.Msg.OK,
						animEl : 'elId',
						icon : Ext.MessageBox.ERROR,
						fn: function(){that.win.close();}
					});
				}
			}
		}

		this.setContext();
		this.win.show(this);
		tree.root.reload();
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.QuickPublish, Jedox.dlg.Dialog);