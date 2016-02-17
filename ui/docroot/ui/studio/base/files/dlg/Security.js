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
 * SVN: $Id: Security.js 5113 2011-07-14 13:55:46Z mladent $
 *
 */


Jedox.studio.files.dlg.Security = function(dlgFlag, callBackFn, tabOffset) {

	var that = this;
	if (!tabOffset) tabOffset = 0;

	this._dlgFlag = dlgFlag;

    var chbLOCK = false;
    //this.accessGroup;
    this.permission = '';
    this.permissionChanged = false;
	//this.connectionName;

    this.defaultPermission = false;
    var groupSelectedIndex;
    var referrersDataTypeFlag = false;

	var _tmpPermission;
	this._refreshFlag = false;
	this._resetFlag = false;

	// data from properties Dlg
	//this._type;
	//this._data;

    var groupListStore = new Ext.data.SimpleStore({
        fields: [{
            name: 'name',
            type: 'string'
        }, {
            name: 'description',
            type: 'string'
        }]
    });


    var groupListLbl = new Ext.form.Label({
        text: 'Groups'.localize().concat(':'),
        baseCls: 'x-plain'
    });


    var space = {
        html: '<br>',
        baseCls: 'x-plain'
    }

    var permissionListLbl = new Ext.form.Label({
        text: 'Permissions'.localize().concat(':')
    });

    var allowLbl = new Ext.form.Label({
        text: 'Allow'.localize()
    });

    var denyLbl = new Ext.form.Label({
        text: 'Deny'.localize()
    });

    var fullControlLbl = new Ext.form.Label({
        text: 'Full Control'.localize().concat(':'),
        baseCls: 'x-plain'
    });

    var fullControlAllowChb = new Ext.ux.form.TriCheckbox({
        hideLabel: true,
        //tabIndex: tabOffset + 1,
		value:false,
        labelStyle: 'font-size:11px;',
		listeners: {
   			check: function(cmp, state){
    			if (!chbLOCK && that.accessGroup && !that._resetFlag)
	                setPermission(7, false, true);
			}
  		}
    });

    var fullControlDenyChb = new Ext.ux.form.TriCheckbox({
        hideLabel: true,
        //tabIndex: tabOffset + 2,
		value:false,
        labelStyle: 'font-size:11px;',
		listeners: {
   			check: function(cmp, state){
	            if (!chbLOCK && that.accessGroup && !that._resetFlag)
	                setPermission(3, false, true);
			}
  		}
    });

    var writeLbl = new Ext.form.Label({
        text: 'Write'.localize().concat(':'),
        baseCls: 'x-plain'
    });

    var writeAllowChb = new Ext.ux.form.TriCheckbox({
        hideLabel: true,
		value:false,
		//tabIndex: tabOffset + 3,
        labelStyle: 'font-size:11px;',
		listeners: {
   			check: function(cmp, state){
	            if (!chbLOCK && that.accessGroup && !that._resetFlag)
	                setPermission(3, false, true);
			}
  		}
    });

    var writeDenyChb = new Ext.ux.form.TriCheckbox({
        hideLabel: true,
        //tabIndex: tabOffset + 4,
		value:false,
        labelStyle: 'font-size:11px;',
		listeners: {
   			check: function(cmp, state){
	            if (!chbLOCK && that.accessGroup && !that._resetFlag)
	                setPermission(1, false, true);
			}
  		}
    });


    var readLbl = new Ext.form.Label({
        text: 'Read'.localize().concat(':'),
        baseCls: 'x-plain'
    });

    var readAllowChb = new Ext.ux.form.TriCheckbox({
        hideLabel: true,
		value:false,
        labelStyle: 'font-size:11px;',
        //tabIndex: tabOffset + 5,
		listeners: {
   			check: function(cmp, state){
	            if (!chbLOCK && that.accessGroup && !that._resetFlag)
	                setPermission(1, false, true);
			}
  		}
    });

    var readDenyChb = new Ext.ux.form.TriCheckbox({
        hideLabel: true,
		value:false,
		//tabIndex: tabOffset + 6,
        labelStyle: 'font-size:11px;',
		listeners: {
   			check: function(cmp, state){
	            if (!chbLOCK && that.accessGroup && !that._resetFlag)
	                setPermission(0, false, true);
			}
  		}
    });


    var groupListView = new Ext.DataView({
        id: 'group-list-view',
		style: 'overflow:auto;',
        store: groupListStore,
        tpl: new Ext.XTemplate('<div class="group-list-view"><tpl for=".">', '<div class="thumb-wrap">', '<div class="thumb" style="padding: 0px; text-align: left;  ">', '<img class="group-icon" src="../lib/ext/resources/images/default/s.gif"/>&nbsp;{name}&nbsp;({description})</div></div>', '</tpl></div>'),
        multiSelect: false,
        singleSelect: true,
        overClass: 'x-view-over',
        itemSelector: 'div.thumb-wrap',
        emptyText: 'No groups'.localize(),
        listeners: {
            click: function(dataView, index, node, e)
            {
                that.permissionPanel.enable();
				that.permissionPanel.buttons[0].enable();
                that.accessGroup = dataView.store.getAt(index).get('name');
                that.permissionChanged = false;
                that.defaultPermission = false;
                groupSelectedIndex = index;
				var tmpPermission;
				var args;

				function onSuccessCbHandler(result)
				{
					tmpPermission = _tmpPermission = result;

					var defaultFlag = tmpPermission.own < 0;
					var permission = defaultFlag? tmpPermission.eff:tmpPermission.own
					setPermission(permission, defaultFlag);
	                setAccessGroupInterfacePermission(_tmpPermission.max);
				}

				function onErrorCbHandler(result) {}

				if (that._dlgFlag == 2) {

					switch(that._type){
						case 'group':
							args = [that.accessGroup, that._data.t];
							break;
						case 'hierarchy':
						case 'rhierarchy':
							args = [that.accessGroup, that._data.t, that._data.hierarchy];
							break;
						default:
							args = [that.accessGroup, that._data.t, that._data.hierarchy, that._data.node];
							break;
					}

					(new Jedox.backend.RPCAsyncRqst('Studio', 'getPerms4UGroup', args))
						.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

				}
				else if (that._dlgFlag == 1) {
					args = [that.accessGroup, that.connectionName];

					(new Jedox.backend.RPCAsyncRqst('Studio', 'getConnPerms4UGroup', args))
						.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();
				}
				else if (that._dlgFlag == 3)
				{
					args = [that.accessGroup, that._data.task_id, that._data.prvt];
					(new Jedox.backend.RPCAsyncRqst('scheduler', 'getPerms', args)).setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();
				}
            }
        }
    });


    var groupListPanel = {
        layout: 'fit',
        height: 240,
        width: 360,
		autoScroll:true,
        items: groupListView
    }

    var permissionLabelPanel = {
        layout: 'absolute',
        border: false,
        bodyStyle: 'background-color: transparent;',
        width: 360,
        height: 15,
        defaults: {
            baseCls: 'x-plain'
        },
        items: [{
            x: 0,
            y: 0,
            items: permissionListLbl
        }, {
            x: 280,
            y: 0,
            items: allowLbl
        }, {
            x: 320,
            y: 0,
            items: denyLbl
        }]
    }


    this.permissionPanel = new Ext.Panel({
        layout: 'table',
        width: 360,
        //		height: 110,
        bodyStyle: 'padding-left:7px; padding-bottom: 3px;',
        disabled: true,
        defaults: {
            baseCls: 'x-plain'
        },
        layoutConfig: {
            columns: 4
        },
        items: [{
            colspan: 2,
            width: 280,
            items: fullControlLbl
        }, {
            colspan: 1,
            width: 40,
            items: fullControlAllowChb
        }, {
            colspan: 1,

            items: fullControlDenyChb
        }, {
            colspan: 2,
            items: writeLbl
        }, {
            colspan: 1,
            items: writeAllowChb
        }, {
            colspan: 1,
            items: writeDenyChb
        }, {
            colspan: 2,
            items: readLbl
        }, {
            colspan: 1,
            items: readAllowChb
        }, {
            colspan: 1,
            items: readDenyChb
        }],
        buttons: [{
            text: 'Default'.localize(),
			disabled:true,
			//tabIndex: tabOffset + 10,
            handler: onGetDefaultPermission
        }]
    });

    var securityPanel = Ext.extend(Ext.Panel, {
    	getPanel:function(){
			return this;
		},

		reset:function(){
			Ext.getCmp('group-list-view').clearSelections();
			this.getEl().unselectable();
			that.resetChbs();
			that.permissionPanel.buttons[0].disable();
		},

		setInterfacePermission:function(perm){
			if (perm & Jedox.studio.access.permType.WRITE)
				this.enable();
			else
				this.disable();
		},

		setName:function(connectionName){
			that.connectionName = connectionName;
		},

		setData:function(type, data){
			that._type = type;
			that._data = data;
		},

		getRefreshFlag:function(){
			return that._refreshFlag;
		},

		getPermission:function(){
			return that.permission;
		},

		refreshGroupList: function(){
			initGroupListData();
		},

		savePermission:function(){
			if (!that.permissionPanel.disabled && that.permissionChanged) {

	            var tmpPermission = that.defaultPermission ? '' : that.permission;


				if (that._dlgFlag == 2){

					function onSuccessCbHandler(result){
						if (result && result[0])
							that._refreshFlag = result[1];

						that.permissionChanged = false;
						that.defaultPermission = false;
					}

					function onErrorCbHandler(result){

					}

					var args;

					switch(that._type){
						case 'group':
						case 'hierarchy':
						case 'rhierarchy':
							args = [that._data.group, "meta", that._data.node, that.accessGroup, tmpPermission, that._data.t];
							break;
						default:
							args = [that._data.group, that._data.hierarchy, that._data.node, that.accessGroup, tmpPermission, that._data.t];
							break;
					}

					(new Jedox.backend.RPCAsyncRqst('Studio', 'setNodePemission', args))
						.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

				}

	        }
		},

		saveConnectionPermission:function()
		{
			var connectionName = that.connectionName,
				accessGroup = that.accessGroup,
				tmpPermission = that.defaultPermission ? '' : that.permission;

			var db = 'Config';
			var cube = '#_GROUP_DIMENSION_DATA_connections';
			var order = ['connections'];
			var data = {};
			var connPermData = {};
			var add = false;

			connPermData[accessGroup] = tmpPermission;
			data[connectionName] = connPermData;

			function onSuccessCbHandler(result){

				that._refreshFlag = result;

				that.permissionChanged = false;
				that.defaultPermission = false;
			}

			function onErrorCbHandler(result){}

			(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [null, db, cube, data, order, add]))
				.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();
		},

		saveTaskPerms: function()
		{
			var tmpPermission = that.defaultPermission ? '' : that.permission,
				db = 'Config',
				cube = '#_GROUP_DIMENSION_DATA_jobs', // TODO: Change to task when it's renamed in database
				order = ['jobs'],
				data = {},
				taskPermData = {};

			taskPermData[that.accessGroup] = tmpPermission;
			data[that._data.task_id] = taskPermData;

			var onSuccessCbHandler = function(result)
			{
				that._refreshFlag = result;

				that.permissionChanged = false;
				that.defaultPermission = false;
			};

			(new Jedox.backend.RPCAsyncRqst('common', 'paloSet', [null, db, cube, data, order, false])).setOnSuccess([this, onSuccessCbHandler]).setOnError([this, function(){}]).send();
		},

		reloadTaskPerms: function()
		{
			if (that._dlgFlag == 3)
			{
				var tmpPermission;

				var onSuccessCbHandler = function(result)
				{
					tmpPermission = _tmpPermission = result;

					var defaultFlag = tmpPermission.own < 0;
					var permission = defaultFlag ? tmpPermission.eff:tmpPermission.own
					setPermission(permission, defaultFlag);
	                setAccessGroupInterfacePermission(_tmpPermission.max);
				}

				args = [that.accessGroup, that._data.task_id, that._data.prvt];
				(new Jedox.backend.RPCAsyncRqst('scheduler', 'getPerms', args)).setOnSuccess([this, onSuccessCbHandler]).setOnError([this, function() {}]).send();
			}
		}
    });

    var mainSecurityPanel = new securityPanel({ //=that ?check
    	layout: 'form',
        border: false,
		autoWidth: true,
        bodyStyle: 'background-color: transparent;',
        items: [groupListLbl, groupListPanel, space, permissionLabelPanel, that.permissionPanel]
    });

	this.resetChbs = function(){
		that._resetFlag = true;
		fullControlAllowChb.reset();
		fullControlDenyChb.reset();
		writeAllowChb.reset();
		writeDenyChb.reset();
		readAllowChb.reset();
		readDenyChb.reset();
		that._resetFlag = false;
	}

	// functions

    function setPermission(p, defaultFlag, changeFlag){
//		console.log(p);
		var permissionMap = {0:'N', 1:'R', 3:'W', 7:'D'}

		if (p in permissionMap)
    		that.permission = permissionMap[p];

        if (changeFlag)
            that.permissionChanged = true;
        that.defaultPermission = false;

		var value = defaultFlag? null:true;

        switch (p) {
            case 7:
                setDPermission();
                break;
            case 3:
                setWPermission();
                break;
            case 1:
                setRPermission();
                break;
            case 0:
                setNPermission();
                break;
            default:
                setDPermission();
                break;
        }


        function setDPermission(){
            chbLOCK = true;
            fullControlAllowChb.setValue(value);
            fullControlDenyChb.setValue(false);
            writeAllowChb.setValue(value);
            writeDenyChb.setValue(false);
            readAllowChb.setValue(value);
            readDenyChb.setValue(false);
            chbLOCK = false;
        }

        function setWPermission(){
            chbLOCK = true;
            fullControlAllowChb.setValue(false);
            fullControlDenyChb.setValue(value);
            writeAllowChb.setValue(value);
            writeDenyChb.setValue(false);
            readAllowChb.setValue(value);
            readDenyChb.setValue(false);
            chbLOCK = false;
        }

        function setRPermission(){
            chbLOCK = true;
            fullControlAllowChb.setValue(false);
            fullControlDenyChb.setValue(value);
            writeAllowChb.setValue(false);
            writeDenyChb.setValue(value);
            readAllowChb.setValue(value);
            readDenyChb.setValue(false);
            chbLOCK = false;
        }

        function setNPermission(){
            chbLOCK = true;
            fullControlAllowChb.setValue(false);
            fullControlDenyChb.setValue(value);
            writeAllowChb.setValue(false);
            writeDenyChb.setValue(value);
            readAllowChb.setValue(false);
            readDenyChb.setValue(value);
            chbLOCK = false;
        }
    }


	function setMaxPermissionInterface(maxAllowedInterfacePermission){

		var permType = Jedox.studio.access.permType;

		if (maxAllowedInterfacePermission & permType.DELETE){
            fullControlAllowChb.enable();
            fullControlDenyChb.enable();
            writeAllowChb.enable();
            writeDenyChb.enable();
            readAllowChb.enable();
            readDenyChb.enable();
		}
		else if ((maxAllowedInterfacePermission & permType.WRITE)){
            fullControlAllowChb.disable();
            fullControlDenyChb.disable();
            writeAllowChb.enable();
            writeDenyChb.enable();
            readAllowChb.enable();
            readDenyChb.enable();
		}
		else {
            fullControlAllowChb.disable();
            fullControlDenyChb.disable();
            writeAllowChb.disable();
            writeDenyChb.disable();
            readAllowChb.enable();
            readDenyChb.enable();
		}

	}

    function onGetDefaultPermission(){

        that.permissionChanged = true;

        setPermission(_tmpPermission.def, true);

        that.permissionChanged = true;
        that.defaultPermission = true;
    }


    function setAccessGroupInterfacePermission(maxAllowedInterfacePermission){

		var permType = Jedox.studio.access.permType;

		if (maxAllowedInterfacePermission & permType.DELETE){
            fullControlAllowChb.enable();
            fullControlDenyChb.enable();
            writeAllowChb.enable();
            writeDenyChb.enable();
            readAllowChb.enable();
            readDenyChb.enable();
		}
		else if ((maxAllowedInterfacePermission & permType.WRITE)){
            fullControlAllowChb.disable();
            fullControlDenyChb.disable();
            writeAllowChb.enable();
            writeDenyChb.enable();
            readAllowChb.enable();
            readDenyChb.enable();
		}
		else {
            fullControlAllowChb.disable();
            fullControlDenyChb.disable();
            writeAllowChb.disable();
            writeDenyChb.disable();
            readAllowChb.enable();
            readDenyChb.enable();
		}

    }

		function initGroupListData ()
		{
			var res = (new Jedox.backend.RPCSyncRqst('common', 'paloGet', [ null, 'System', '#_GROUP_GROUP_PROPERTIES', [ '#_GROUP_' ], { '#_GROUP_PROPERTIES_': [ 'description' ] } ])).send();

			if (res instanceof Array)
			{
				Jedox.studio.app.showMessageERROR('Database error'.localize(), 'Can not read groups data from database'.localize());
				return false;
			}

			var data = [];

			for (var group in res)
				data.push([ group, res[group].description ]);

			groupListStore.loadData(data);
		}

    function formatTitle(value, p, record){
        return String.format('<div class="topic"><img src="{0}"/>&nbsp;&nbsp;{1}</div>', 'res/img/fam/group.png', value);
    }


	this.refreshGroupList = function(){
		initGroupListData();
	}


	initGroupListData();

	callBackFn(mainSecurityPanel);

}