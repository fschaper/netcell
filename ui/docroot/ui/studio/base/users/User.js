/*
 * @brief ajax
 *
 * @file User.js
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
 * SVN: $Id: User.js 4876 2011-04-20 11:52:41Z srdjanv $
 *
 * \see
 * LICENSE.txt
 *
 */

//TODO: validation, localization
Jedox.studio.users.User = function(addFlag){

	var that = this;
	this.addFlag=addFlag;
	this.userName='';

	var prefs_level = {
		  SERVER: 0
		, GROUP: 1
		, USER: 2
	};


	this.availableGroupsStore= new Ext.data.SimpleStore({
		fields: [
			{name: 'groupName'}
		]
	});

	this.userGroupsStore= new Ext.data.SimpleStore({
		fields: [
			{name: 'groupName'}
		]
	});


	this.generalTabLbl = {
		//id: 'general-user-header',
		html: 'General informations about user'.localize() + '...<br><br><br>',
		autoWidth: true,
		baseCls: 'x-plain',
		bodyStyle: 'font-size:11;'
	}


	this.userNameTxf = new Ext.form.TextField({
		fieldLabel: 'User Name'.localize(),
		tabIndex: 500,
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		name: 'userName',
		allowBlank: false,
		width: 200
	});


	this.fullNameTxf = new Ext.form.TextField({
		fieldLabel: 'Full Name'.localize(),
		labelStyle: 'font-size:11px;',
		tabIndex: 501,
		cls: 'preview-properties-panel',
		name: 'fullName',
		width: 200
	});

	this.descriptionTxa = new Ext.form.TextArea({
		fieldLabel: 'Description'.localize(),
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		name: 'description',
		tabIndex: 502,
		width: 200
	});

	this.splitLine = {
		html: '<br><br>',
		baseCls: 'split-line',
		width: 315
	};

	this.passwordTxf = new Ext.form.TextField({
		fieldLabel: 'Set password'.localize(),
		inputType:'password',
		tabIndex: 503,
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		name: 'password',
		width: 200,
		baseCls: 'x-plain'
	});

	this.confirmPasswordTxf = new Ext.form.TextField({
		fieldLabel: 'Confirm Password'.localize(),
		inputType:'password',
		tabIndex: 504,
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		name: 'confirmPassword',
		width: 200,
		baseCls: 'x-plain',
		listeners:{
			blur:function(){

				var cmfmsg = 'Confirm password with the same value'.localize() + '...';
				var value = that.passwordTxf.getValue();
				var cmfvalue = that.confirmPasswordTxf.getValue();

				if (value!=cmfvalue){
					that.confirmPasswordTxf.markInvalid(cmfmsg);
				}

			}
		}
	});

	this.optionsBtn = new Ext.Button({
			text: 'Options'.localize(),
			hidden:addFlag == 'add',
			tabIndex: 505,
			handler: function(){
				Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openPreferences, [prefs_level.USER, that.userNameTxf.getValue()]);
			}
		});

	var optionsBtnContainer = {
		layout:'form',
		baseCls:'x-plain',
		width:315,
		buttonAlign:'right',
		fbar: new Ext.Toolbar({items:[this.optionsBtn]})
	}

	this.accountStatusChb = new Ext.form.Checkbox({
		fieldLabel: 'Active'.localize(), //until palo support added
		labelStyle: 'font-size:11px;'
	});


	this.memberOfTabLbl = {
		html: 'Choose the group which the user is part of'.localize() +'<br><br><br>',
		autoWidth: true,
		baseCls: 'x-plain',
		bodyStyle: 'font-size:11;'
	}

	this.memeberOfIS = {
		xtype: "itemselector",
		name: "itemselector",
		fieldLabel: "ItemSelector",
		tabIndex: 500,
		cls: 'preview-properties-panel',
		hideLabel: true,
		fromStore:this.availableGroupsStore,
		dataFields: ["groupName"],
		toStore: this.userGroupsStore,
		drawUpIcon:false,
		drawDownIcon:false,
		drawTopIcon:false,
		drawBotIcon:false,
		msWidth: 150,
		msHeight: 200,
		displayField: "groupName",
		imagePath: "../../../lib/ext/extensions/multiselect",
		//switchToFrom:true,
		toLegend: "Assigned Groups".localize(),
		fromLegend: "Available Groups".localize()
	}


	this.tabPanel = new Ext.TabPanel({
        activeTab: 0,
        width:400,
        height:400,
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
					this.generalTabLbl, this.userNameTxf, this.fullNameTxf, this.descriptionTxa,
					this.splitLine, this.passwordTxf, this.confirmPasswordTxf,
					this.splitLine, optionsBtnContainer, this.accountStatusChb, {html:'<br><br>', autoWidth: true, baseCls:'x-plain'}]
            },{
                title: 'Assigned Groups'.localize(),
				items:[this.memberOfTabLbl, this.memeberOfIS]
            }
        ],
        listeners: {
			tabchange: function(tbp, active){
				if (that.addFlag || that.userName) Jedox.studio.app.containers.ugrDetPan = active;
			}
		}
    });


	Jedox.studio.users.User.superclass.constructor.call(this, {
		labelAlign: 'right',
		border:false,
		bodyStyle:'padding:5px',
		cls:'preview-properties-panel',
		layout:'fit',
		items:[this.tabPanel],
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
//				handler:this.validateForm,
				scope:this
			}]
		})
	});

	if (this.addFlag==='add')
		this.initMemberOf();

}

Ext.extend(Jedox.studio.users.User, Ext.Panel, {

	initUser:function(userName){

		var that = this;

		var _protected_users = {'admin':true, '_internal_suite':true};

		this.userName=userName;

		var db = 'System';
		var cube = '#_USER_USER_PROPERTIES';
		var order = ['#_USER_'];
		var props = ['userName', 'fullName', 'description', 'inactive']; //properties from store needed for interface
		var cords = {'#_USER_':[userName], '#_USER_PROPERTIES_':props};

		props.shift();

		function cb(result){
			if(!result){
				//error
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read data'.localize());
				return;
			}

			if(userName in _protected_users){
				that.userNameTxf.disable();
				that.accountStatusChb.disable();
			}
			else{
				that.userNameTxf.enable();
				that.accountStatusChb.enable();
			}

			that.userNameTxf.setValue(that.getPropsValue(userName));
			that.fullNameTxf.setValue(that.getPropsValue(result[userName]['fullName']));
			that.descriptionTxa.setValue(that.getPropsValue(result[userName]['description']));
			that.passwordTxf.setValue("");
			that.confirmPasswordTxf.setValue("");
			that.accountStatusChb.setValue(that.getPropsValue(that.reverse(result[userName]['inactive'])));

			if(that.userName == '_internal_suite'){
				that.buttons[0].disable();
				that.buttons[1].disable();
				that.optionsBtn.disable();
			}
			else{
				that.buttons[0].enable();
				that.buttons[1].enable();
				that.optionsBtn.enable();
			}

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
		var cube = '#_USER_GROUP';
		var order = ['#_USER_'];
		var cords = {'#_USER_':[that.userName]};

		var dim = '#_GROUP_';

		var args = that.userName? [Jedox.studio.users.paloConn, db, cube, order, cords]:[Jedox.studio.users.paloConn, db, dim];
		var cmnd =  that.userName? 'paloGet':'paloDir';

		function cb(result){
			if(!result){
				//error
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read data'.localize());
				return;
			}

			var availableGroupsData = [];
			var userGroupsData = [];

			if (that.userName) {
				for (user in result) {
					for (group in result[user]) {
						if (result[user][group] == '1')
							userGroupsData.push([group]);
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

			that.availableGroupsStore.loadData(availableGroupsData);
			that.userGroupsStore.loadData(userGroupsData);

		}

		Jedox.backend.rpc([this, cb], 'common', cmnd, args);

	},


	addUser:function(addF){

		var that = this;

		var _protected_users = {'admin':true, '_internal_suite':true};
		var _protected_groups = {'admin':true};

        if (this.validateForm(addF)) {

			var db = 'System';
			var cube = '#_USER_USER_PROPERTIES';
			var data = {};
			var order = ['#_USER_'];
			var add = true;


			var userName = addF? this.userNameTxf.getValue():this.userName;
			var fullName = this.fullNameTxf.getValue();
			var description = this.descriptionTxa.getValue();
			var password = this.passwordTxf.getValue();
			var status = this.reverse(this.accountStatusChb.getValue()? "1":"0");

			data[userName] = {
//				'userName': userName,
				'fullName': fullName,
				'description': description,
				'password': password,
				'inactive': status
			}

			// when update if password not set do not update password
			if(!addF && password == "")
				delete data[userName].password;

			if (userName in _protected_users) {
				delete data[userName].inactive;
			}

			function cb(result){
				if (!result) {
					//error
					Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
					return;
				}



				var ug_cube = '#_USER_GROUP';
				var ug_data = {};
				var ug_order = ['#_USER_'];

				ug_data[userName] = that.getUserGroups();

				if (userName in _protected_users){
					for (i in _protected_groups)
						delete ug_data[userName][i];
				}


				function ug_cb(result){
					if (!result) {
						//error
						Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
						return;
					}



					if (!addF && userName != that.userNameTxf.getValue()) {

						var r_db = 'System';
						var r_dim = '#_USER_';
						var r_data = {};

						var newUserName = that.userNameTxf.getValue();

						r_data[userName] = newUserName;


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
					(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [Jedox.studio.users.paloConn, db, ug_cube, ug_data, ug_order, add])).setOnSuccess([this, ug_cb]),
					(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
				)).setFlags(1).send();

			}


			(new Jedox.backend.RPCAsyncBatch(true,
				(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [Jedox.studio.users.paloConn, db, cube, data, order, add])).setOnSuccess([this, cb]),
				(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
			)).setFlags(1).send();

		}


	},


	getUserGroups: function(){

		var data = {}

		for (var i=0, agNmbr = this.memeberOfIS.fromStore.getCount(); i<agNmbr; i++)
			data[this.memeberOfIS.fromStore.getAt(i).get('groupName')] = "";
		for (var i=0, ugNmbr = this.memeberOfIS.toStore.getCount(); i<ugNmbr; i++)
			data[this.memeberOfIS.toStore.getAt(i).get('groupName')] = "1";

		return data;
	},

	isError:function(result){
		if (result[0] === "!" && result.length === 2)
			return true;
		return false;

	},


	validateForm:function(addF){
			var that = this;
			var _return=true;

			function userName(){
				var msg = 'sign_in_name_validation_err'.localize();
//				var my_regexp =	/^[^\s#$@%^&*"',+=<>!?~:;|\\\/\(\)\{\}\[\]]{2,}$/;
				var value = that.userNameTxf.getValue();
				if (!Jedox.palo.utils.checkPaloName(value, 'elem')/*!my_regexp.test(value)*/){
					that.userNameTxf.markInvalid(msg);
					_return=false;
				}
			}

			function fullName(){
				var msg = 'full_name_validation_err'.localize();
				var my_regexp = /^[^\s][^#$%^&*"+=<>!?~:;|\\\/\(\)\{\}\[\]]+\w*$/
				var value = that.fullNameTxf.getValue();
				if (!my_regexp.test(value)){
					that.fullNameTxf.markInvalid(msg);
					_return=false;
				}
			}

			function password(){

				var msg = "password_validation_err".localize();
				var cmfmsg = 'Retype same password'.localize() + '...';
				var value = that.passwordTxf.getValue();
				var cmfvalue = that.confirmPasswordTxf.getValue();

				if(!addF && value == cmfvalue && value == "")
					return;

				if (value.length < 5){
					that.passwordTxf.markInvalid(msg);
					_return=false;
					return;
				}

				if (value!=cmfvalue){
					that.confirmPasswordTxf.markInvalid(cmfmsg);
					_return=false;
					return;
				}


			}

			userName();
			fullName();
			password();

			return _return;
	},

	onSave:function(){
		if (this.addFlag === 'add')
			this.addUser(true);
		else
			this.addUser(false); // update user
	},

	onCancel:function(){
		if (this.addFlag) {
			this.ownerCt.ownerCt.refreshUserList();
			this.ownerCt.ownerCt.remove(this.ownerCt);
		}
		else
			this.initUser(this.userName);
	},

	onClose:function(){
		if (this.addFlag) {
			this.ownerCt.ownerCt.refreshUserList();
			this.ownerCt.ownerCt.remove(this.ownerCt);
			if(this.addFlag == 'add')
				Jedox.studio.app.showTopMsg('', 'User added successefully'.localize());
			else
				Jedox.studio.app.showTopMsg('', 'User updated successefully'.localize())
		}
		else {
			this.ownerCt.ownerCt.ownerCt.ownerCt.refreshUserList();
			Jedox.studio.app.showTopMsg('', 'User updated successefully'.localize());
		}
	}


});
