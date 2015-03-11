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
 * SVN: $Id: CPanel.js 5095 2011-07-06 12:08:18Z mladent $
 *
 */

Jedox.studio.conns.CPanel = function(){

	var that = this;
	this.addFlag=false;
	this.connectionName='';
	this.initFlag = false;
	this._passMask = '*****';

	//this._perm;

	//this.s; //securityObj

	this.connectionTypesStore= new Ext.data.SimpleStore({
		fields: [
			{name:'value'},
			{name:'connectionName'},
			{name:'icon'}
		]
	});


	this.connectionTypeCmb = new Ext.form.ComboBox({
		fieldLabel: 'Type'.localize(),
		labelStyle: 'font-size:11px;',
		//cls: 'preview-properties-panel',
		store:this.connectionTypesStore,
		valueField: 'value',
		tabIndex: 203,
		displayField: 'connectionName',
		value:'palo',
		width: 200,
		triggerAction: 'all',
		editable: false,
		mode: 'local'
	});


	this.connectionNameTxf = new Ext.form.TextField({
		fieldLabel: 'Connection Name'.localize(),
		labelStyle: 'font-size:11px;',
		tabIndex: 201,
		cls: 'preview-properties-panel',
		name: 'connectionName',
		allowBlank: false,
		width: 200
	});


	this.descriptionTxa = new Ext.form.TextArea({
		fieldLabel: 'Description'.localize(),
		labelStyle: 'font-size:11px;',
		tabIndex: 202,
		cls: 'preview-properties-panel',
		name: 'description',
		width: 200
	});

	this.hostTxf = new Ext.form.TextField({
		fieldLabel: 'Host'.localize(),
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		tabIndex: 204,
		name: 'host',
		width: 200
	});

	this.splitLine = {
		html: '<br><br>',
		baseCls: 'split-line',
		width: 315
	};

	this.portTxf = new Ext.form.TextField({
		fieldLabel: 'Port'.localize(),
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		name: 'port',
		width: 200,
		tabIndex: 205,
		baseCls: 'x-plain'
	});

	this.userNameTxf = new Ext.form.TextField({
		fieldLabel: 'User Name'.localize(),
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		tabIndex: 210,
		name: 'userName',
		width: 200
	});


	this.passwordTxf = new Ext.form.TextField({
		fieldLabel: 'Set password'.localize(),
		inputType:'password',
		enableKeyEvents:true,
		tabIndex: 211,
		labelStyle: 'font-size:11px;',
		cls: 'preview-properties-panel',
		width: 200
	});


	this.useLoginCredChb = new Ext.form.Checkbox({
		fieldLabel: 'Use login credentials'.localize(),
		tabIndex: 212,
		labelStyle: 'font-size:11px;',
		handler:function(){
			if (this.getValue()){
				that.userNameTxf.disable();
				that.passwordTxf.disable();
			}
			else{
				that.userNameTxf.enable();
				that.passwordTxf.enable();
			}
		}
	});

	this.connectionActiveChb = new Ext.form.Checkbox({
		fieldLabel: 'Connection active'.localize(),
		tabIndex: 213,
		labelStyle: 'font-size:11px;'
	});

	var generalPanel = new Ext.Panel({
		//title:'Connections',
		layout:'form',
		autoWidth: true,
		bodyStyle: 'padding:10px',
		border:false,
		items:[
			this.connectionNameTxf, this.descriptionTxa, this.connectionTypeCmb, this.splitLine,
			this.hostTxf, this.portTxf, this.splitLine, this.userNameTxf, this.passwordTxf, this.useLoginCredChb, this.splitLine, this.connectionActiveChb
		]
	});

	this.tabPanel = new Ext.TabPanel({
        activeTab: 0,
		border:false,
		bodyStyle: 'border-width: 0 0 1px 0;',
        enableTabScroll: true,
        defaults:{
			autoScroll: true,
			layout: 'form'
		},
        items:[{
            title: 'General'.localize(),
			items:[generalPanel]
		},
		{
            title: 'Security'.localize(),
			bodyStyle: 'padding:10px',
			listeners:{
				render:function(){
					makeSecurityPanel(this);
				}
			}
        }],
		listeners: {
			beforetabchange: function(tabPanel, newTab, currentTab){
				return !that.addFlag;
			},
			tabchange: function(p, at){
				if (that.initFlag) Jedox.studio.app.containers.connPan = at;
			}
		}
    });

	function makeSecurityPanel(container){

		var callBackFnSec = function(sPanel){
			container.add(sPanel);

			that.s = sPanel;
			that.s.setName(that.connectionName);
			that.s.setInterfacePermission(that._perm);
			container.doLayout();
        }

		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.fileSecurity, [1, callBackFnSec, 650]);
	}

	var mpfbar = new Ext.Toolbar({
		id: 'conn-saveCancel-tb',
		items: [{
			text: 'Test connection'.localize(),
			handler:this.onTestConnection,
			tabIndex: 301,
			scope:this
		},{
			text: 'Save'.localize(),
			handler:this.onSave,
			tabIndex: 302,
			scope:this
		},
		{
    		text: 'Cancel'.localize(),
			handler:this.onCancel,
			tabIndex: 303,
			scope:this
		}]
	});

	var mainPanel = {
		layout:'fit',
		autoWidth: true,
		border:false,
		items:[this.tabPanel],
		fbar: mpfbar
	}


	Jedox.studio.conns.CPanel.superclass.constructor.call(this, {
		id:'c-main-panel',
		title:'Connection Manager'.localize(),
		labelAlign: 'right',
		cls:'preview-properties-panel',
		layout:'card',
		items:[{html:'', baseCls:'x-plain', id: 'connempty'},mainPanel],
		activeItem:0,
		listeners:{
			show:function(){
				if(that.s)
					that.s.refreshGroupList();
			}
		}
	});

}

Ext.extend(Jedox.studio.conns.CPanel, Ext.Panel, {

	init:function(){
		if (this.initFlag)
			return false;
		this.initConnectionTypes();
	},


	initConnectionTypes:function(){

		var connectionTypesData = [['palo', 'Palo', 'palo-connection-icon']]; //['odbc', 'ODBC', 'odbc-connection-icon'];
		this.connectionTypesStore.loadData(connectionTypesData);
		this.initFlag = true;

	},


	initConnection: function(connectionName, perm) {
		this._perm = perm;
		this.addFlag=false;
		this.connectionName = connectionName;
		this.layout.setActiveItem(1);

		var db = 'Config';
		var cube = '#_connections';
		var order = ['connections'];
		var props = ['name', 'type', 'description', 'host', 'port', 'username', 'active', 'useLoginCred']; //properties from store needed for interface
		var cords = {'connections':[connectionName], '#_connections_':props};

		function cb(result){
			if(!result){
				//error
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read data'.localize());
				return;
			}

			var connection = result[connectionName]

			this.connectionNameTxf.setValue(connection['name']);
			this.connectionTypeCmb.setValue(connection['type']);
			this.descriptionTxa.setValue(connection['description']);
			this.hostTxf.setValue(connection['host']);
			this.portTxf.setValue(connection['port']);
			this.userNameTxf.setValue(connection['username']);
			this.passwordTxf.setValue("");
			this.useLoginCredChb.setValue(connection['useLoginCred']);

			if(/*connection['useLoginCred'] == "0" && */connection['username'])
				this.passwordTxf.setValue(this._passMask);

			this.connectionActiveChb.setValue(connection['active']);
			this.setInterfacePermission(perm);

			if (this.s){
				this.s.reset(this.connectionName);
				this.s.setInterfacePermission(perm);
				this.s.setName(this.connectionName);
			}

		}

		Jedox.backend.rpc([this, cb], 'common', 'paloGet', [null, db, cube, order, cords]);
		Jedox.studio.app.containers.connPan = this.tabPanel.getActiveTab();
		Jedox.studio.app.containers.connSCbtn = Ext.getCmp('conn-saveCancel-tb');
	},

	testConnection:function(addF){
		var newConnectionName = this.connectionNameTxf.getValue();
		var connectionName = addF? newConnectionName:this.connectionName;
		var connectionType = this.connectionTypeCmb.getValue();
		var description = this.descriptionTxa.getValue();
		var host = this.hostTxf.getValue();
		var port = this.portTxf.getValue();
		var userName = this.userNameTxf.getValue();
		var password = this.passwordTxf.getValue();
		password = (password == this._passMask)? '':password;
		var useLoginCred = this.useLoginCredChb.getValue()? "1":"0";
		var connectionActive = this.connectionActiveChb.getValue()? "1":"0";

		if (this.validateForm(addF)) {

			function onSuccessCbHandler(result){
				//show msg
				if(result)
					Jedox.studio.app.showMsg('Test connection'.localize(), 'Connection successful!'.localize(), Ext.MessageBox.INFO, Ext.Msg.OK, null, null);
				else
					Jedox.studio.app.showMsg('Test connection'.localize(), 'Error connecting to server!'.localize(), Ext.MessageBox.ERROR, Ext.Msg.OK, null, null);
			}

			(new Jedox.backend.RPCAsyncRqst('Studio', 'testConnection', [connectionName, host, port, userName, password, useLoginCred, addF]))
				.setOnSuccess([this, onSuccessCbHandler]).send();

		}

	},


	addConnection:function(addF){

		var that = this;

		var newConnectionName = this.connectionNameTxf.getValue();
		var connectionName = addF? newConnectionName:this.connectionName;
		var connectionType = this.connectionTypeCmb.getValue();
		var description = this.descriptionTxa.getValue();
		var host = this.hostTxf.getValue();
		var port = this.portTxf.getValue();
		var userName = this.userNameTxf.getValue();
		var password = this.passwordTxf.getValue();
		password = (password == this._passMask)? '':password;
		var useLoginCred = this.useLoginCredChb.getValue()? "1":"0";
		var connectionActive = this.connectionActiveChb.getValue()? "1":"0";

		//TODO: validation

		if (this.validateForm(addF)) {

			var db = 'Config';
			var cube = '#_connections';
			var order = ['connections'];
			var data = {};
			var add = addF;


			data[connectionName] = {
				'name': newConnectionName,
				'type': connectionType,
				'description': description,
				'host':host,
				'port':port,
				'username':userName,
				'password': password,
				'useLoginCred':useLoginCred,
				'active': connectionActive
			}


			if(useLoginCred == "1"){
				delete data[connectionName].username;
				delete data[connectionName].password;
			}
			else {
				if(!addF && this.passwordTxf.getValue() == that._passMask /*password == ""*/){
					delete data[connectionName].password;
				}
			}


			function cb(result){

				if (this.s)
					this.s.saveConnectionPermission();


				if (!addF && connectionName != newConnectionName) {

					var r_db = 'Config';
					var r_dim = 'connections';
					var r_data = {};

					r_data[connectionName] = newConnectionName;

					function onSucccessCbHandler(){
						that.showFeedback('', 'Connection'.localize() +' <b>' + connectionName + ' </b> ' +'updated'.localize());
						that.onCancel();
					}


					(new Jedox.backend.RPCAsyncBatch(true,
						(new Jedox.backend.RPCAsyncRqst('common', 'paloRename', [null, r_db, r_dim, r_data])).setOnSuccess([that, onSucccessCbHandler]).setOnError([that, onErrorCbHandler]),
						(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
					)).setFlags(1).send();

				}
				else {
					that.showFeedback('', 'Connection'.localize() +' <b>' + connectionName + ' </b> ' + ((addF)? 'added'.localize():'updated'.localize()));
					that.onCancel();
				}

			}

			function onErrorCbHandler(){
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not write data'.localize());
			}


			(new Jedox.backend.RPCAsyncBatch(true,
				(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [null, db, cube, data, order, add])).setOnSuccess([that, cb]).setOnError([that, onErrorCbHandler]),
				(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
			)).setFlags(1).send();

		}
	},

	newConnection:function(){
		this.layout.setActiveItem(1);
		this.clear();
		this.setInterfacePermission(Jedox.studio.access.permType.WRITE);
		this.tabPanel.setActiveTab(0);
		this.addFlag=true;
		Jedox.studio.app.containers.connSCbtn = Ext.getCmp('conn-saveCancel-tb');
		Jedox.studio.app.containers.connPan = this.tabPanel.getActiveTab();
	},

	setInterfacePermission:function(perm){

		var that = this;

		if (perm & Jedox.studio.access.permType.WRITE)
			setWRITEPermission();
		else
			setREADPermision();


		function setREADPermision(){
			that.connectionNameTxf.disable();
			that.connectionTypeCmb.disable();
			that.descriptionTxa.disable();
			that.hostTxf.disable();
			that.portTxf.disable();
			that.userNameTxf.disable();
			that.passwordTxf.disable();
			that.useLoginCredChb.disable();
			that.connectionActiveChb.disable();
			var btns = that.items.items[1].buttons;
			btns[0].disable();
			btns[1].disable();
			btns[2].disable();
		}

		function setWRITEPermission(){
			that.connectionNameTxf.enable();
			that.connectionTypeCmb.enable();
			that.descriptionTxa.enable();
			that.hostTxf.enable();
			that.portTxf.enable();
			that.useLoginCredChb.enable();
			that.connectionActiveChb.enable();
			var btns = that.items.items[1].buttons;
			btns[0].enable();
			btns[1].enable();
			btns[2].enable();
		}

	},

	clear:function(){
		this.connectionNameTxf.reset();
		this.connectionTypeCmb.reset();
		this.descriptionTxa.reset();
		this.hostTxf.reset();
		this.portTxf.reset();
		this.userNameTxf.reset();
		this.passwordTxf.reset();
		this.useLoginCredChb.reset();
		this.connectionActiveChb.reset();
	},


	showFeedback:function (title, message){
		Jedox.studio.app.showTopMsg(title, message);
	},

	validateForm:function(addF){
		var that = this;
		var _return=true;

		function connectionName(){
			var msg = 'Connection name must start with a-z/A-Z/0-9 character and cannot contain...'.localize();
//			var my_regexp = /^[a-zA-Z0-9]+[a-zA-Z0-9_\-@\.\s]*$/; ///^[a-zA-Z][a-zA-Z0-9_\-@\.\s]+$/;
			var value = that.connectionNameTxf.getValue();
			if (!Jedox.palo.utils.checkPaloName(value, 'elem')/*!my_regexp.test(value)*/){
				that.connectionNameTxf.markInvalid(msg);
				_return=false;
			}
		}

		function host(){
			var msg = 'Host name must start with a-z/A-Z/0-9 character'.localize();
			var my_regexp = /^[a-zA-Z0-9_\-@\.:]+$/;
			var value = that.hostTxf.getValue();
			if (!my_regexp.test(value)){
				that.hostTxf.markInvalid(msg);
				_return=false;
			}
		}

		function port(){
			var msg = 'Port name must be a number...'.localize();
			var my_regexp = /^[0-9]+$/;
			var value = that.portTxf.getValue();
			if (!my_regexp.test(value)){
				that.portTxf.markInvalid(msg);
				_return=false;
			}
		}

		function userName(){
			var msg = 'User name must start with a-z/A-Z character and cannot contain...'.localize();
			var my_regexp = /^[a-zA-Z][a-zA-Z0-9_\-@\.]+$/;
			var value = that.userNameTxf.getValue();
			if (!my_regexp.test(value)){
				that.userNameTxf.markInvalid(msg);
				_return=false;
			}
		}

		function password(){

			var msg = 'Password must start with a-z/A-Z character and must contain 5 char min'.localize() + '...';
			var cmfmsg = 'Retype same password'.localize() + '...';
			var my_regexp = /^[a-zA-Z_]([a-zA-Z0-9#_-]{4,})$/;
			var value = that.passwordTxf.getValue();
			value = /*(value == that._passMask)? '':*/value;

			if(!addF && value == that._passMask)
				return;

			if (!my_regexp.test(value)){
				that.passwordTxf.markInvalid(msg);
				_return=false;
				return;
			}

		}

		connectionName();
		host();
		port();
		if (!this.useLoginCredChb.getValue()){
			userName();
			password();
		}


		return _return;
	},



	isError:function(result){
		if (result[0] === "!" && result.length === 2)
			return true;
		return false;

	},

	onTestConnection:function(){
		this.testConnection(!!(this.addFlag));
	},

	onSave:function(){
		if (this.addFlag)
			this.addConnection(true);
		else
			this.addConnection(false);
	},

	onCancel:function(){
		Ext.getCmp('sConnections_treeHolder_pnl').refreshConnectionList();
		this.layout.setActiveItem(0);
		delete Jedox.studio.app.containers.connPan;
		delete Jedox.studio.app.containers.connSCbtn;
	}

});
