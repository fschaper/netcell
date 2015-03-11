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
 * SVN: $Id: Role.js 5087 2011-06-29 14:22:30Z mladent $
 *
 */

Jedox.studio.users.Role = function(addFlag){

	this.addFlag=addFlag;
	this.roleName = '';

	var that = this;

	this.permKey = {
			D: 'Full Access'.localize(),
			W: 'Writable'.localize(),
			R: 'Read Only'.localize(),
			N: 'No Access'.localize(),
			// special permissions
			S: 'Splash'.localize()
	}

	this.permData = [
	                  ['S', 'Splash'.localize()],
	                  ['D', 'Full Access'.localize()],
	                  ['W', 'Writable'.localize()],
	                  ['R', 'Read Only'.localize()],
	                  ['N', 'No Access'.localize()]
	                  ];

	this.permStore = new Ext.data.SimpleStore({
		fields: [
					{name: 'perm'},
					{name: 'permD'}
				]
			});

	this.permStore.loadData(this.permData);

	this.rightObjReg = {
			'user': {
				desc: 'robj_desc_user'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'password': {
				desc: 'robj_desc_password'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'group': {
				desc: 'robj_desc_group'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'database': {
				desc: 'robj_desc_database'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'cube': {
				desc: 'robj_desc_cube'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'dimension': {
				desc: 'robj_desc_dimension'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'dimension element': {
				desc: 'robj_desc_dimElements'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'cell data': {
				desc: 'robj_desc_cellData'.localize(),
				defPerm: 'S',
				allowedPerms: ['S', 'D', 'W', 'R', 'N']
			},
			'rights': {
				desc: 'robj_desc_rights'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'system operations': {
				desc: 'robj_desc_sysOperations'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'event processor': {
				desc: 'robj_desc_eventProc'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'sub-set view': {
				desc: 'robj_desc_subsetView'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'user info': {
				desc: 'robj_desc_userInfo'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'rule': {
				desc: 'robj_desc_rule'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'ste_reports': {
				desc: 'robj_desc_report'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'ste_files': {
				desc: 'robj_desc_file'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'ste_palo': {
				desc: 'robj_desc_olap'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'ste_users': {
				desc: 'robj_desc_userManager'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'ste_etl': {
				desc: 'robj_desc_etl'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'ste_conns': {
				desc: 'robj_desc_connection'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'ste_scheduler': {
				desc: 'robj_desc_scheduler'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			},
			'drillthrough': {
				desc: 'robj_desc_drillthrough'.localize(),
				defPerm: 'D',
				allowedPerms: ['D', 'W', 'R', 'N']
			}
	}

	this.generalTabLbl = {
		//id:'general-role-header',
		html:'Enter the General informations about Role'.localize() + '...<br><br><br>',
		autoWidth: true,
		baseCls: 'x-plain'
	}

	this.availableGroupStore= new Ext.data.SimpleStore({
		fields: [
			{name: 'groupName'}
		]
	});

	this.roleGroupStore= new Ext.data.SimpleStore({
		fields: [
			{name: 'groupName'}
		]
	});


	this.roleNameTxf = new Ext.form.TextField({
		fieldLabel: 'Role Name'.localize(),
		labelStyle: 'font-size:11px;',
		tabIndex: 500,
		cls: 'preview-properties-panel',
		allowBlank: false,
		width: 200
	});

	this.descriptionTxa = new Ext.form.TextArea({
		fieldLabel: 'Description'.localize(),
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		tabIndex: 501,
		name: 'description',
		width: 200
	});

	this.statusCB = new Ext.form.Checkbox({
		fieldLabel: 'Active'.localize()
	});

	this.memberOfTabLbl = {
			html:'Choose the groups you want to asign to this role'.localize() + '<br><br><br>',
			autoWidth: true,
			baseCls: 'x-plain'
		};

	this.memeberOfIS = {
			xtype: "itemselector",
			name: "itemselector",
			fieldLabel: "ItemSelector",
			cls: 'preview-properties-panel',
			hideLabel: true,
			fromStore:this.availableGroupStore,
			dataFields: ["groupName"],
			toStore: this.roleGroupStore,
			drawUpIcon:false,
			tabIndex: 510,
			drawDownIcon:false,
			drawTopIcon:false,
			drawBotIcon:false,
			msWidth: 150,
			msHeight: 200,
			displayField: "groupName",
			imagePath: "../../../lib/ext/extensions/multiselect",
			//switchToFrom:true,
			toLegend: "Role Members".localize(),
			fromLegend: "Available Groups".localize()
		}

	this.rightsGridStore = new Ext.data.SimpleStore({
        fields: [
			{name: 'rightObj'},
			{name: 'rightDesc'},
			{name: 'permission'},
			{name: 'permH'}
        ]
		//,sortInfo:{field:'rightObj', direction:'ASC'}
        ,listeners: {
			update: function(st, rec, op){
      		  	rec.set('permH', that.newPerm);
      		  	that.newPerm = false;
			}
		}
    });

	this.editor = new Ext.ux.grid.RowEditor({
        saveText: 'Update'.localize(),
        id: 'gridRowEditorUsers',
        style : {"z-index" : 7000, "font-size": "11px"},
        listeners: {
			afteredit: function(el, changed){
			},
			beforeedit: function(e, f, m, t){
			}
		}
    });

	/* Override grid so that editors are rendered into document body instead of grid scroller.
	 * This allows the textarea editors and row editors to expand outside of the bottom of the grid if needed.
	 * Quick and elegant solution.
	 */
	/*
	 * disabled by d_lenz request
	Ext.override(Ext.grid.GridView, {
	    getEditorParent: function() {
	        return document.body;
	    }
	});
	*/

	this.rowIndex = 0;
	this.newPerm = false;

	this.assignedRightsGrid = new Ext.grid.EditorGridPanel({
		store: this.rightsGridStore,
		autoWidth: true,
		autoHeight: true,
		id: 'assignedRightsGrid',
		ctCls: 'tplMap-Grid',
		border: true,
		frame: true,
		plugins: [this.editor],
		stripeRows: false,
		sm: new Ext.grid.RowSelectionModel({
			singleSelect: false,
			moveEditorOnEnter: false
			}),
		enableHdMenu: false,
		viewConfig: {
            forceFit:true
        },
        baseCls: 'x-plain',
		columns: [
		          {
		        	  id: 'rightObject',
		        	  header: 'Object name'.localize(),
					  autoWidth:true,
		        	  sortable: false,
		        	  dataIndex: 'rightObj'
		          },
		          {
		        	  id: 'rightDescription',
		        	  header: 'Object description'.localize(),
					  autoWidth:true,
		        	  sortable: false,
		        	  dataIndex: 'rightDesc'
		          },
		          {
		        	  id: 'objPerm',
		        	  header: 'Object permission'.localize(),
					  autoWidth:true,
		        	  sortable: false,
		        	  dataIndex: 'permission',
		        	  editor: new Ext.form.ComboBox({
							typeAhead: false,
							triggerAction: 'all',
							id: 'permComboEditor',
							lazyRender: true,
							editable: false,
							store: this.permStore,
							mode: 'local',
							displayField: 'permD',
							listeners: {
		        		  		select: function (el, rec, index){
				        			that.newPerm = rec.data.perm;
				        	  	}
				        	  }
		        	  })
		          }
		          ],
		 listeners: {
        	rowclick: function(grid, index, e){
        		that.rowIndex = index;
        		var robj = grid.getSelectionModel().getSelected().data;
        		var aPerms = that.rightObjReg[robj.rightObj].allowedPerms;
        		that.permData=[];
        		for (var i=0; i<aPerms.length; i++){
        			that.permData.push([aPerms[i], that.permKey[aPerms[i]]]);
        		}
        		that.permStore.loadData(that.permData);
	        },
	        resize: function(){
	        	this.fireEvent('columnresize');
	        }
        }
	});


	this.tabPanel = new Ext.TabPanel({
        activeTab: 0,
        width:400,
        height:350,
		bodyStyle: 'border-left:none; border-right:none; border-top:1; border-bottom:1;',
        enableTabScroll: true,
		plain:true,
        defaults:{
			autoScroll: true,
			bodyStyle: 'padding:10px',
			layout: 'form'
		},
        items:[{
            title: 'General'.localize(),
			items:[
				this.generalTabLbl, this.roleNameTxf, this.descriptionTxa, this.statusCB
			]
		}
		,{
            title: 'Role Members'.localize(),
			items:[this.memberOfTabLbl, this.memeberOfIS]
        },
        {
        	title: 'Assigned rights'.localize(),
        	items: [{
				layout: 'fit',
				autoWidth:true,
				border:false,
				items: this.assignedRightsGrid
			}]
        }
		],
		listeners: {
			tabchange: function(tbp, active){
				if (that.addFlag || that.roleName) Jedox.studio.app.containers.ugrDetPan = active;
			}
		}
    });



	Jedox.studio.users.Role.superclass.constructor.call(this, {
		labelAlign: 'right',
		border:false,
		bodyStyle:'padding:5px',
		cls:'preview-properties-panel',
		layout:'fit',
		items:[
		this.tabPanel
		],
		fbar: new Ext.Toolbar({
			items: [{
				text: 'Save'.localize(),
				handler:this.onSave,
				tabIndex: 900,
				scope:this
			},
			{
	    		text: 'Cancel'.localize(),
				handler:this.onCancel,
				tabIndex: 901,
				scope:this
			}]
		})
	});

	if (this.addFlag==='add')
		{this.roleName = ''; this.initMemberOf();}
}

Ext.extend(Jedox.studio.users.Role, Ext.Panel, {

	initRole:function(roleName){

		var that = this;

		var _protected_roles = {'admin':true};

		this.roleName = roleName;

		var db = 'System';
		var cube = '#_ROLE_ROLE_PROPERTIES';
		var order = ['#_ROLE_'];
		var props = [/*'name', */'description', 'inactive']; //properties from store needed for interface
		var cords = {'#_ROLE_':[roleName], '#_ROLE_PROPERTIES_':props};

		//props.shift();

		function cb(result){
			if(!result){
				//error
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read data'.localize());
				return;
			}

			if(roleName in _protected_roles)
				that.roleNameTxf.disable();
			else
				that.roleNameTxf.enable();

			that.roleNameTxf.setValue(that.getPropsValue(roleName));
			that.descriptionTxa.setValue(that.getPropsValue(result[roleName]['description']));
			that.statusCB.setValue(that.reverse(that.getPropsValue(result[roleName]['inactive'])));

			that.initMemberOf();
		}

		Jedox.backend.rpc([this, cb], 'common', 'paloGet', [Jedox.studio.users.paloConn, db, cube, order, cords]);

	},

	reverse:function(v){

		var reverseObj = {
			"0":"1",
			"1":"0"
		}

		return v? reverseObj[v]:reverseObj["0"];
	},

	getPropsValue:function(value){
		if(value != undefined)
			return value;

		return ""; // could be undefined or not set string
	},


	initMemberOf:function(){

		var that = this;

		var db = 'System';
		var rg_cube = '#_GROUP_ROLE';
		var rg_order = ['#_ROLE_'];
		var rg_cords = {'#_ROLE_':[that.roleName]};

		var rg_dim = '#_GROUP_';

		var rg_args = that.roleName? [Jedox.studio.users.paloConn, db, rg_cube, rg_order, rg_cords]:[Jedox.studio.users.paloConn, db, rg_dim];
		var rg_cmnd =  that.roleName? 'paloGet':'paloDir';

		function rg_cb(result){

			if(!result){
				//error
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read data'.localize());
				return;
			}

			var availableGroupsData = [];
			var roleGroupData = [];


			if (that.roleName) {
				for (role in result) {
					for (group in result[role]) {
						if (result[role][group] == '1')
							roleGroupData.push([group]);
						else
							availableGroupsData.push([group]);
					}
				}
			}
			else{
				if(result instanceof Array)
					for(var i=0, count=result.length; i<count; i++)
						availableGroupsData.push([result[i]]);
			}

			that.availableGroupStore.loadData(availableGroupsData);
			that.roleGroupStore.loadData(roleGroupData);
		}

		Jedox.backend.rpc([this, rg_cb], 'common', rg_cmnd, rg_args);


		var rr_cube = '#_ROLE_RIGHT_OBJECT';
		var rr_order = ['#_ROLE_'];
		var rr_cords = {'#_ROLE_':[that.roleName]};

		var rr_dim = '#_RIGHT_OBJECT_';

		var rr_args = that.roleName? [Jedox.studio.users.paloConn, db, rr_cube, rr_order, rr_cords]:[Jedox.studio.users.paloConn, db, rr_dim];
		var rr_cmnd =  that.roleName? 'paloGet':'paloDir';

		function rr_cb(result){

			if(!result){
				//error
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read data'.localize());
				return;
			}

			var robjData = [];

			if (that.roleName) {
				for (role in result) {
					for (r_obj in result[role]) {
						if (!that.rightObjReg[r_obj]) {
							that.rightObjReg[r_obj] = {
								desc: 'unknown right object'.localize(),
								defPerm: 'D',
								allowedPerms: ['D', 'W', 'R', 'N']
							}
						}
						robjData.push((result[role][r_obj] != '') ? [r_obj, that.rightObjReg[r_obj].desc, that.permKey[result[role][r_obj]], result[role][r_obj]] : [r_obj, that.rightObjReg[r_obj].desc, that.permKey[that.rightObjReg[r_obj].defPerm], that.rightObjReg[r_obj].defPerm]);
					}
				}
			}
			else{
				if(result instanceof Array)
					for(var i=0, count=result.length; i<count; i++)
						robjData.push([result[i], that.rightObjReg[result[i]].desc, that.permKey[that.rightObjReg[result[i]].defPerm], that.rightObjReg[result[i]].defPerm]);
			}

			that.rightsGridStore.loadData(robjData);
		}

		Jedox.backend.rpc([this, rr_cb], 'common', rr_cmnd, rr_args);

	},


	addRole:function(addF){

		var that = this;

		var _protected_groups = {'admin':true};
		var _protected_roles = {'admin':true};
		var _protected_rights = {'user':true,'password':true,'group':true,'database':true,'cube':true,'dimension':true,'dimension element':true,'cell data':true,'rights':true,'system operations':true,'event processor':true,'sub-set view':true,'user info':true,'rule':true};



        if (this.validateForm()) {

			var db = 'System';
			var rr_cube = '#_ROLE_ROLE_PROPERTIES';
			var rr_data = {};
			var rr_order = ['#_ROLE_'];
			var add = true;


			var roleName = addF? this.roleNameTxf.getValue():this.roleName;
			var roleDesc = this.descriptionTxa.getValue();
			var roleStatus = this.reverse(this.statusCB.getValue()? "1":"0");

			rr_data[roleName] = {
				//'name': roleName,
				'description': roleDesc,
				'inactive': roleStatus
			}

			function rr_cb(result){
				if (!result) {
					//error
					Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
					return;
				}

				var gr_cube = '#_GROUP_ROLE';
				var gr_data = {};
				var gr_order = ['#_ROLE_'];

				gr_data[roleName] = that.getRoleGroups();

				if (roleName in _protected_roles){
					for (i in _protected_groups)
						delete gr_data[roleName][i];
				}

				function gr_cb(result){
					if (!result) {
						//error
						Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
						return;
					}


					var ro_cube = '#_ROLE_RIGHT_OBJECT';
					var ro_data = {};
					var ro_order = ['#_ROLE_'];

					ro_data[roleName] = that.getRoleRights();

					if (roleName in _protected_roles){
						for (i in _protected_rights)
							delete ro_data[roleName][i];
					}

					function ro_cb(result){
						if (!result) {
							//error
							Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
							return;
						}


						if (!addF && roleName != that.roleNameTxf.getValue()) {

							var r_db = 'System';
							var r_dim = '#_ROLE_';
							var r_data = {};

							var newRoleName = that.roleNameTxf.getValue();

							r_data[roleName] = newRoleName;


							function r_cb(result){
								if (!result) {
									//error
									Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
									return;
								}

								that.onClose();
							}


							(new Jedox.backend.RPCAsyncBatch(true,
								(new Jedox.backend.RPCAsyncRqst('common', 'paloRename', [Jedox.studio.users.paloConn, r_db, r_dim, r_data])).setOnSuccess([this, r_cb]),
								(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
							)).setFlags(1).send();

						}
						else {
							that.onClose();
						}

					}


					(new Jedox.backend.RPCAsyncBatch(true,
						(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [Jedox.studio.users.paloConn, db, ro_cube, ro_data, ro_order, add])).setOnSuccess([this, ro_cb]),
						(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
					)).setFlags(1).send();

				}


				(new Jedox.backend.RPCAsyncBatch(true,
					(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [Jedox.studio.users.paloConn, db, gr_cube, gr_data, gr_order, add])).setOnSuccess([this, gr_cb]),
					(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
				)).setFlags(1).send();

			}


			(new Jedox.backend.RPCAsyncBatch(true,
				(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [Jedox.studio.users.paloConn, db, rr_cube, rr_data, rr_order, add])).setOnSuccess([this, rr_cb]),
				(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
			)).setFlags(1).send();

		}
	},


	getRoleGroups: function(){

		var data = {}

		for (var i=0, auNmbr = this.memeberOfIS.fromStore.getCount(); i<auNmbr; i++)
			data[this.memeberOfIS.fromStore.getAt(i).get('groupName')] = "";
		for (var i=0, guNmbr = this.memeberOfIS.toStore.getCount(); i<guNmbr; i++)
			data[this.memeberOfIS.toStore.getAt(i).get('groupName')] = "1";

		return data;
	},


	getRoleRights: function() {
		var data = this.rightsGridStore;
		var cnt = data.getCount();

		var rights = {};

		for (var i=0; i<cnt; i++){
			var el = data.getAt(i);
			rights[el.get('rightObj')] = el.get('permH');
		}
		return rights;
	},

	isError:function(result){
		if (result[0] === "!" && result.length === 2)
			return true;
		return false;

	},

	validateForm:function(){
		var that = this;
		var _return=true;

		function roleName(){
			var msg = 'Role name must start with a-z/A-Z character and must contain at least two character'.localize();
//			var my_regexp = /^[a-zA-Z][a-zA-Z0-9_\-@\.]+$/;
			var value = that.roleNameTxf.getValue();
			if (!Jedox.palo.utils.checkPaloName(value, 'elem')/*!my_regexp.test(value)*/){
				that.roleNameTxf.markInvalid(msg);
				_return=false;
			}
		}

		roleName();

		return _return;
	},

	onSave:function(){
		// remove rowEditor if visible
		if (Ext.getCmp('gridRowEditorUsers')) Ext.getCmp('gridRowEditorUsers').stopEditing(false);
		if (this.addFlag === 'add')
			this.addRole(true);
		else
			this.addRole(false);
	},

	onCancel:function(){
		// remove rowEditor if visible
		if (Ext.getCmp('gridRowEditorUsers')) Ext.getCmp('gridRowEditorUsers').stopEditing(false);
		if (this.addFlag) {
			this.ownerCt.ownerCt.refreshRoleList();
			this.ownerCt.ownerCt.remove(this.ownerCt);
		}
		else
			this.initRole(this.roleName);
	},

	onClose:function(){
		// remove rowEditor if visible
		if (Ext.getCmp('gridRowEditorUsers')) Ext.getCmp('gridRowEditorUsers').stopEditing(false);
		if (this.addFlag) {
			this.ownerCt.ownerCt.refreshRoleList();
			this.ownerCt.ownerCt.remove(this.ownerCt);
			if(this.addFlag == 'add')
				Jedox.studio.app.showTopMsg('', 'Role added successefully'.localize());
			else
				Jedox.studio.app.showTopMsg('', 'Role updated successefully'.localize());
		}
		else {
			this.ownerCt.ownerCt.ownerCt.ownerCt.refreshRoleList();
			Jedox.studio.app.showTopMsg('', 'Role updated successefully'.localize());
		}
	}

});