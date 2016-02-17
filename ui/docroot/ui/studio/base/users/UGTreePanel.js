/*
 * @brief ajax
 *
 * @file UGTreePanel.js
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
 * SVN: $Id: UGTreePanel.js 4854 2011-04-15 13:53:28Z lukap $
 *
 * \see
 * LICENSE.txt
 *
 */

Jedox.studio.users.UGTreePanel = function(){

	var _int = false;

	var connToolbar = new Ext.Toolbar({
		id: 'connToolbar',
		items: [
		        {xtype: 'tbtext', text: 'Connection_users'.localize().concat(':')}
		        ]
	});

	var connData = [];

	var connStore = new Ext.data.ArrayStore({
		fields: ['desc', 'name'],
		data: connData
	});

	var _internalConn = '<'.concat('internal_conn'.localize(),'>');
	var _internalConnHTM = '&lt;'.concat('internal_conn'.localize(),'&gt;');

	var initUsers = false;
	var initGroups = false;
	var initRoles = false;

	var _stopAll = false;

	var connCombo = new Ext.form.ComboBox({
		id: 'sUsers_conn_cmb',
        store: connStore,
        displayField: 'desc',
        tabIndex: 10,
        editable: false,
		lazyRender: true,
        typeAhead: true,
        mode: 'local',
        triggerAction: 'all',
        value: '',
        selectOnFocus: true,
        listWidth: 200,
        width: 200,
		listeners: {
			select: function(cmb, rec, index) {

				function onSuccessCbHandler(res){
					if (res !== true) {
						Jedox.studio.app.showMessageERROR('Connection error'.localize(), res.localize({conn_name: connData[index][1] || 'internal'}));
						this.setValue(cmb.startValue)
						_stopAll = true;
						Ext.getCmp('ug-grid-panel').layout.activeItem.topToolbar.disable();
						return false;
						}

					Jedox.studio.users.paloConn = connData[index][1];
					_stopAll = false;
					Ext.getCmp('ug-grid-panel').layout.activeItem.topToolbar.enable();
					if (this.value == _internalConnHTM)
						{
							this.setValue(_internalConn);
							_int = Jedox.studio.users.internalConnection = true;
						}
						else {
							_int = Jedox.studio.users.internalConnection = false;
						}

					initUsers = false;
					initGroups = false;
					initRoles = false;

					cmb.startValue = this.value;
					var ai = Ext.getCmp('ug-grid-panel').layout.activeItem.id.split('-')[1];
					switch (ai){
					case 'user':
						if (!initUsers) Ext.getCmp('ug-panel').refreshUserList();
						initUsers = true;
						break;
					case 'group':
						if (!initGroups) Ext.getCmp('ug-panel').refreshGroupList();
						initGroups = true;
						break;
					case 'role':
						if (!initRoles) Ext.getCmp('ug-panel').refreshRoleList();
						initRoles = true;
						break;
					}

				}

				function onErrorCbHandler(result){

				}

				(new Jedox.backend.RPCAsyncRqst('Studio', 'isAdminConn', [connData[index][1]])).setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();

			}
		}
	});

	connToolbar.add(connCombo);

	var usersAndGroupsTP = new Ext.tree.TreePanel({
		id: 'ps-ug-tree',
		rootVisible: false,
		border: false,
		lines: true,
		autoScroll: true,
		root: new Ext.tree.TreeNode('Users and Groups'),
		collapseFirst: false,
		tbar: connToolbar,
		listeners: {
			refreshToolbarCombo: function(){
				connData = [];

				function onSuccessCbHandler(conns){
					connData.push([_internalConnHTM, null]);

					for (i = 0; i < conns.length; i++)
						connData.push([conns[i]['name'], conns[i]['name']]);

					connStore.loadData(connData);
					var _isValid = connStore.find('name', Jedox.studio.users.paloConn);
					if (_isValid>0) {
						connCombo.setValue(Jedox.studio.users.paloConn);
					} else {
						if (!_int) connCombo.fireEvent('select', connCombo, null, 0);
						connCombo.setValue(_internalConn);
						_int = Jedox.studio.users.internalConnection = true;
					}
				}

				function onErrorCbHandler(result){

				}

				(new Jedox.backend.RPCAsyncRqst('Studio', 'getPaloConns'))
					.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();
			}
		}
	});

	initUserAndGroupsTP();

	function initUserAndGroupsTP(){

		var userN = new Ext.tree.TreeNode({
			id: 'ug-user-node',
			text: 'Users'.localize(),
			iconCls: 'user-icon',
			expanded: true
		});

		var groupN = new Ext.tree.TreeNode({
			id: 'ug-group-node',
			text: 'Groups'.localize(),
			iconCls: 'group-icon',
			expanded: true
		});

		var roleN = new Ext.tree.TreeNode({
			id: 'ug-role-node',
			text: 'Roles'.localize(),
			iconCls: 'role-icon',
			expanded: true
		});

		usersAndGroupsTP.root.appendChild([userN, groupN, roleN]);
	}

	//TODO: Rewrite onClick event handler
	usersAndGroupsTP.on('click', function(n){
		if (_stopAll) {
			Ext.getCmp('ug-grid-panel').layout.activeItem.topToolbar.disable();
			return false;
		};
		var sn = this.selModel.selNode || {}; // selNode is null on initial selection
		if (n.id != sn.id) {
			//console.log(sn.id);
			//Ext.getCmp('ps-content-panel').layout.setActiveItem(n.id + '-panel');
			var title = n.id.split('-')[1];

			Ext.getCmp('ug-grid-panel').layout.setActiveItem(n.id + '-panel');
			Jedox.studio.app.containers.ugrGrid = Ext.getCmp('ug-grid-panel').layout.activeItem.topToolbar; // setting toolbar tabbing
			Jedox.studio.app.containers.ugrGrid.enable();
			Ext.getCmp('ug-main-panel').setTitle(('All ' + title.charAt(0).toUpperCase() + title.slice(-(title.length - 1)) + 's').localize());
			if (title === 'user')
				{
					Ext.getCmp('ug-panel').openSelectedUser();
					if (initUsers) return;
					Ext.getCmp('ug-panel').refreshUserList();
					initUsers = true;
				}
			else
				if (title === 'group')
					{
					Ext.getCmp('ug-panel').openSelectedGroup();
					if (initGroups) return;
					Ext.getCmp('ug-panel').refreshGroupList();
					initGroups = true;
					}
			else
				if (title === 'role')
					{
					Ext.getCmp('ug-panel').openSelectedRole();
					if (initRoles) return;
					Ext.getCmp('ug-panel').refreshRoleList();
					initRoles = true;
					}
					//Ext.getCmp('ug-panel').closeAllTabs();
			//Ext.getCmp('ug-preview-panel').layout.setActiveItem(n.id.replace('node', 'panel'));
		}

	});

	return usersAndGroupsTP;
}
