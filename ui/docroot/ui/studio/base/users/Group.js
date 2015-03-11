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
 * SVN: $Id: Group.js 4876 2011-04-20 11:52:41Z srdjanv $
 *
 */

Jedox.studio.users.Group = function(addFlag){

	var that = this;
	this.addFlag=addFlag;
	this.groupName = '';

	var prefs_level = {
		  SERVER: 0
		, GROUP: 1
		, USER: 2
	};


	this.availableUsersStore= new Ext.data.SimpleStore({
		fields: [
			{name: 'userName'}
		]
	});

	this.groupUsersStore= new Ext.data.SimpleStore({
		fields: [
			{name: 'userName'}
		]
	});

	this.availableRolesStore= new Ext.data.SimpleStore({
		fields: [
			{name: 'roleName'}
		]
	});

	this.groupRolesStore= new Ext.data.SimpleStore({
		fields: [
			{name: 'roleName'}
		]
	});


	this.generalTabLbl = {
		//id:'general-group-header',
		html:'Enter the General informations about Group'.localize() + '...<br><br><br>',
		autoWidth: true,
		baseCls: 'x-plain',
		bodyStyle: 'font-size:11;'
	}


	this.groupNameTxf = new Ext.form.TextField({
		fieldLabel: 'Group Name'.localize(),
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


	this.splitLine = {
		html: '<br><br>',
		baseCls: 'split-line',
		width: 315
	};



	this.optionsBtn = new Ext.Button({
			text: 'Options'.localize(),
			hidden:addFlag == 'add',
			tabIndex: 503,
			handler: function(){
				Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openPreferences, [prefs_level.GROUP, that.groupNameTxf.getValue()]);
			}
		});

	var optionsBtnContainer = {
		layout:'form',
		baseCls:'x-plain',
		width:315,
		buttonAlign:'right',
		buttons:[this.optionsBtn]
	}

	this.accountStatusChb = new Ext.form.Checkbox({
		fieldLabel: 'Active'.localize(), //until palo support added
		labelStyle: 'font-size:11px;'
//		hidden:true //until palo support added
	});


	this.memberOfTabLbl = {
		html:'Choose the users you want to asign to this group'.localize() + '<br><br><br>',
		autoWidth: true,
		baseCls: 'x-plain',
		bodyStyle: 'font-size:11;'
	};

	this.memberOfRTabLbl = {
			html:'Choose the roles you want to asign to this group'.localize() + '<br><br><br>',
			autoWidth: true,
			baseCls: 'x-plain',
			bodyStyle: 'font-size:11;'
		};

	this.memeberOfIS = {
		xtype: "itemselector",
		name: "itemselector",
		fieldLabel: "ItemSelector",
		cls: 'preview-properties-panel',
		hideLabel: true,
		fromStore:this.availableUsersStore,
		dataFields: ["userName"],
		toStore: this.groupUsersStore,
		drawUpIcon:false,
		drawDownIcon:false,
		tabIndex: 510,
		drawTopIcon:false,
		drawBotIcon:false,
		msWidth: 150,
		msHeight: 200,
		displayField: "userName",
		imagePath: "../../../lib/ext/extensions/multiselect",
		//switchToFrom:true,
		toLegend: "Assigned Users".localize(),
		fromLegend: "Available Users".localize()
	};

	this.memeberOfRIS = {
			xtype: "itemselector",
			name: "itemselector",
			fieldLabel: "ItemSelector",
			cls: 'preview-properties-panel',
			hideLabel: true,
			fromStore:this.availableRolesStore,
			dataFields: ["roleName"],
			toStore: this.groupRolesStore,
			drawUpIcon:false,
			drawDownIcon:false,
			tabIndex: 520,
			drawTopIcon:false,
			drawBotIcon:false,
			msWidth: 150,
			msHeight: 200,
			displayField: "roleName",
			imagePath: "../../../lib/ext/extensions/multiselect",
			//switchToFrom:true,
			toLegend: "Assigned Roles".localize(),
			fromLegend: "Available Roles".localize()
		}


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
				this.generalTabLbl, this.groupNameTxf,  this.descriptionTxa,
				this.splitLine, optionsBtnContainer, this.accountStatusChb
			]
		},
		{
            title: 'Assigned Users'.localize(),
			items:[this.memberOfTabLbl, this.memeberOfIS]
        },
        {
            title: 'Assigned Roles'.localize(),
			items:[this.memberOfRTabLbl, this.memeberOfRIS]
        }
		],
		listeners: {
			tabchange: function(tbp, active){
				if (that.addFlag || that.groupName) Jedox.studio.app.containers.ugrDetPan = active;
			}
		}
    });



	Jedox.studio.users.Group.superclass.constructor.call(this, {
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
		this.initMemberOf();

}

Ext.extend(Jedox.studio.users.Group, Ext.Panel, {

	initGroup:function(groupName){

		var that = this;

		var _protected_groups = {'admin':true};

		this.groupName = groupName;

		var db = 'System';
		var cube = '#_GROUP_GROUP_PROPERTIES';
		var order = ['#_GROUP_'];
		var props = ['groupName', 'description', 'inactive']; //properties from store needed for interface
		var cords = {'#_GROUP_':[groupName], '#_GROUP_PROPERTIES_':props};

		props.shift();

		function cb(result){
			if(!result){
				//error
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read data'.localize());
				return;
			}

			if(groupName in _protected_groups)
				that.groupNameTxf.disable();
			else
				that.groupNameTxf.enable();

			that.groupNameTxf.setValue(that.getPropsValue(groupName));
			that.descriptionTxa.setValue(that.getPropsValue(result[groupName]['description']));
			that.accountStatusChb.setValue(that.reverse(that.getPropsValue(result[groupName]['inactive'])));

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
		var ug_cube = '#_USER_GROUP';
		var ug_order = ['#_GROUP_'];
		var ug_cords = {'#_GROUP_':[that.groupName]};

		var ug_dim = '#_USER_';

		var ug_args = that.groupName? [Jedox.studio.users.paloConn, db, ug_cube, ug_order, ug_cords]:[Jedox.studio.users.paloConn, db, ug_dim];
		var ug_cmnd =  that.groupName? 'paloGet':'paloDir';

		function ug_cb(result){
			if(!result){
				//error
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read data'.localize());
				return;
			}

			var availableUsersData = [];
			var groupUsersData = [];

			if(that.groupName){
				for (group in result){
					for (user in result[group]){
						if (result[group][user] == '1')
							groupUsersData.push([user]);
						else
							availableUsersData.push([user]);
					}
				}
			}
			else{
				if(result instanceof Array)
					for(var i=0, count=result.length; i<count; i++)
						availableUsersData.push([result[i]]);
			}

			that.availableUsersStore.loadData(availableUsersData);
			that.groupUsersStore.loadData(groupUsersData);
		}

		Jedox.backend.rpc([this, ug_cb], 'common', ug_cmnd, ug_args);


		var gr_cube = '#_GROUP_ROLE';
		var gr_order = ['#_GROUP_'];
		var gr_cords = {'#_GROUP_':[that.groupName]};

		var gr_dim = '#_ROLE_';

		var gr_args = that.groupName? [Jedox.studio.users.paloConn, db, gr_cube, gr_order, gr_cords]:[Jedox.studio.users.paloConn, db, gr_dim];
		var gr_cmnd =  that.groupName? 'paloGet':'paloDir';

		function gr_cb(result){
			if(!result){
				//error
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read data'.localize());
				return;
			}

			var availableRolesData = [];
			var groupRolesData = [];

			if (that.groupName) {
				for (group in result) {
					for (role in result[group]) {
						if (result[group][role] == '1')
							groupRolesData.push([role]);
						else
							availableRolesData.push([role]);
					}
				}
			}
			else{
				if(result instanceof Array)
					for(var i=0, count=result.length; i<count; i++)
						availableRolesData.push([result[i]]);
			}

			that.availableRolesStore.loadData(availableRolesData);
			that.groupRolesStore.loadData(groupRolesData);
		}

		Jedox.backend.rpc([this, gr_cb], 'common', gr_cmnd, gr_args);

	},


	addGroup:function(addF){

		var that = this;

		var _protected_users = {'admin':true, '_internal_suite':true};
		var _protected_groups = {'admin':true};
		var _protected_roles = {'admin':true};

        if (this.validateForm()) {

			var db = 'System';
			var gg_cube = '#_GROUP_GROUP_PROPERTIES';
			var gg_data = {};
			var gg_order = ['#_GROUP_'];
			var add = true;


			var groupName = addF? this.groupNameTxf.getValue():this.groupName;
			var description = this.descriptionTxa.getValue();
			var status = this.reverse(this.accountStatusChb.getValue()? "1":"0");

			gg_data[groupName] = {
//				'groupName': groupName,
				'description': description,
				'inactive': status
			}

			function gg_cb(result){
				if (!result) {
					//error
					Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
					return;
				}

				var ug_cube = '#_USER_GROUP';
				var ug_data = {};
				var ug_order = ['#_GROUP_'];

				ug_data[groupName] = that.getGroupUsers();

				if (groupName in _protected_groups){
					for (i in _protected_users)
						delete ug_data[groupName][i];
				}

				function ug_cb(result){
					if (!result) {
						//error
						Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
						return;
					}

					var gr_cube = '#_GROUP_ROLE';
					var gr_data = {};
					var gr_order = ['#_GROUP_'];

					gr_data[groupName] = that.getGroupRoles();

					if (groupName in _protected_groups){
						for (i in _protected_roles)
							delete gr_data[groupName][i];
					}

					function gr_cb(result){
						if (!result) {
							//error
							Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
							return;
						}

						if (!addF && groupName != that.groupNameTxf.getValue()) {

							var r_db = 'System';
							var r_dim = '#_GROUP_';
							var r_data = {};

							var newGroupName = that.groupNameTxf.getValue();

							r_data[groupName] = newGroupName;


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
						(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [Jedox.studio.users.paloConn, db, gr_cube, gr_data, gr_order, add])).setOnSuccess([this, gr_cb]),
						(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
					)).setFlags(1).send();
				}


				(new Jedox.backend.RPCAsyncBatch(true,
					(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [Jedox.studio.users.paloConn, db, ug_cube, ug_data, ug_order, add])).setOnSuccess([this, ug_cb]),
					(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
				)).setFlags(1).send();

			}


			(new Jedox.backend.RPCAsyncBatch(true,
				(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [Jedox.studio.users.paloConn, db, gg_cube, gg_data, gg_order, add])).setOnSuccess([this, gg_cb]),
				(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
			)).setFlags(1).send();

		}

	},


	getGroupUsers: function(){

		var data = {}

		for (var i=0, auNmbr = this.memeberOfIS.fromStore.getCount(); i<auNmbr; i++)
			data[this.memeberOfIS.fromStore.getAt(i).get('userName')] = "";
		for (var i=0, guNmbr = this.memeberOfIS.toStore.getCount(); i<guNmbr; i++)
			data[this.memeberOfIS.toStore.getAt(i).get('userName')] = "1";

		return data;
	},


	getGroupRoles: function(){

		var data = {}

		for (var i=0, auNmbr = this.memeberOfRIS.fromStore.getCount(); i<auNmbr; i++)
			data[this.memeberOfRIS.fromStore.getAt(i).get('roleName')] = "";
		for (var i=0, guNmbr = this.memeberOfRIS.toStore.getCount(); i<guNmbr; i++)
			data[this.memeberOfRIS.toStore.getAt(i).get('roleName')] = "1";

		return data;
	},

	isError:function(result){
		if (result[0] === "!" && result.length === 2)
			return true;
		return false;

	},


	validateForm:function(){
		var that = this;
		var _return=true;

		function groupName(){
			var msg = 'Group name must start with a-z/A-Z/0-9 character and must contain at least two character'.localize();
//			var my_regexp = /^[a-zA-Z0-9]+[a-zA-Z0-9_\-@ \.]*$/; ///^[a-zA-Z][a-zA-Z0-9_\-@\.]+$/;
			var value = that.groupNameTxf.getValue();
			if (!Jedox.palo.utils.checkPaloName(value, 'elem')/*!my_regexp.test(value)*/){
				that.groupNameTxf.markInvalid(msg);
				_return=false;
			}
		}

		groupName();

		return _return;
	},


	onSave:function(){
		if (this.addFlag === 'add')
			this.addGroup(true);
		else
			this.addGroup(false);
	},

	onCancel:function(){
		if (this.addFlag) {
			this.ownerCt.ownerCt.refreshGroupList();
			this.ownerCt.ownerCt.remove(this.ownerCt);
		}
		else
			this.initGroup(this.groupName);
	},

	onClose:function(){
		if (this.addFlag) {
			this.ownerCt.ownerCt.refreshGroupList();
			this.ownerCt.ownerCt.remove(this.ownerCt);
			if(this.addFlag == 'add')
				Jedox.studio.app.showTopMsg('', 'Group added successefully'.localize());
			else
				Jedox.studio.app.showTopMsg('', 'Group updated successefully'.localize());
		}
		else {
			this.ownerCt.ownerCt.ownerCt.ownerCt.refreshGroupList();
			Jedox.studio.app.showTopMsg('', 'Group updated successefully'.localize());
		}
	}

});
