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
 * SVN: $Id: CTreePanel.js 4869 2011-04-19 11:15:47Z lukap $
 *
 */

Jedox.studio.conns.CTreePanel = function(){

	var that = this;
	this.initFlag = false;

	var newCTlbBtn = {
		text:'New Connection'.localize(),
		id: 'sConnections_newConn_btn',
		tabIndex: 10,
		tooltip:{title:'New Connection'.localize(), text:'Creates new connection'.localize()},
		iconCls:'connection-icon',
		disabled:!(Jedox.studio.access.rules['dimension element'] & Jedox.studio.access.permType.DELETE),
        handler:this.addConnection,
		scope:this
	}


	var removeCTlbBtn = {
		text:'Remove connection'.localize(),
		id: 'sConnections_remCon_btn',
		tabIndex: 11,
		tooltip:{title:'Remove'.localize(), text:'Removes connection from list'.localize()},
        iconCls:'delete-icon',
		disabled:true,
		handler:this.removeConnection,
		scope:this
	}

	this.cTlb = new Ext.Toolbar({
		items:[newCTlbBtn, removeCTlbBtn],
		id: 'sConnections_treeHolder_pnl_tb'
	});

	this.cTreePanel = new Ext.tree.TreePanel({
		border: false,
		lines: true,
		autoHeight:true,
		root: new Ext.tree.TreeNode({id:'c-root-node', text: 'Connections'.localize(), iconCls:'connection-icon', expanded:false }),
		rootVisible: false
	});


	//TODO: Rewrite onClick event handler
	this.cTreePanel.on('click', function(n){
		var sn = that.cTreePanel.selModel.getSelectedNode() || {}; // selNode is null on initial selection
		if (n.id != sn.id && n.id != 'c-root-node'){
			that.setInterfacePermission(n.attributes.perm);
			Ext.getCmp('c-main-panel').initConnection(n.text, n.attributes.perm);
		}
		else
			that.unselect();
	});


	Jedox.studio.conns.CTreePanel.superclass.constructor.call(this, {
		id: 'sConnections_treeHolder_pnl',
		border:false,
		tbar:that.cTlb,
		autoScroll: true,
		items:[that.cTreePanel]
	});
}


Ext.extend(Jedox.studio.conns.CTreePanel, Ext.Panel, {

	init:function(){
		if (this.initFlag)
			return false;
		this.initCData();
	},


	initCData:function (){

		var that = this,
			nodes = [];

		this.cTreePanel.root.eachChild(function(node){nodes.push(node);}, [this]);
		for (var i=0; i<nodes.length; i++)
			nodes[i].remove();

		function onSuccessCbHandler(result){

			if(result instanceof Array && result.length == 0)
				return;

			var CData=[];

			for (var i in result)
				if(i)CData.push({text:result[i]['name'], leaf:true, iconCls:result[i]['type'].concat('-connection-icon'), perm:result[i]['perm']});


			that.cTreePanel.root.appendChild(CData);
			that.cTreePanel.root.expand();
			that.initFlag = true;
		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'getAllConnections'))
			.setOnSuccess([this, onSuccessCbHandler]).send();

	},


	addConnection:function(){
		this.cTreePanel.root.select();
		Ext.getCmp('c-main-panel').newConnection();
	},

	refreshConnectionList:function(){
		var nodes=[];
		this.cTreePanel.root.eachChild(function(node){nodes.push(node);}, [this]);
		for (var i=0; i<nodes.length; i++)
			nodes[i].remove();

		this.initCData();
		this.cTreePanel.root.expand();
		this.cTreePanel.root.select();
	},


	removeConnection:function(){
		var that=this;
		var sn = this.cTreePanel.selModel.getSelectedNode() || {}; // selNode is null on initial selection

		var title = 'Remove Connection'.localize();
		var msg =  'remove_connection_warning_msg'.localize({'conn':sn.text});

		var fn = function(){
			var db = 'Config',
				dim = 'connections',
				cords = [sn.text],
				type = sn.attributes.iconCls.split('-').shift();


			function onSuccessCbHandler(){
				sn.remove();
				that.unselect();
			}


			(new Jedox.backend.RPCAsyncBatch(true,
				(new Jedox.backend.RPCAsyncRqst('common', 'paloRemove', [null, db, dim, cords])).setOnSuccess([that, onSuccessCbHandler]),
				(new Jedox.backend.RPCAsyncRqst('Studio', 'syncPaloConnData'))
			)).setFlags(1).send();

		}

		Jedox.studio.app.showMessageQUESTION(title, msg, fn);
	},


	unselect:function(){
		Ext.getCmp('c-main-panel').layout.setActiveItem(0);
	},

	setInterfacePermission:function(perm){

		if (perm & Jedox.studio.access.permType.DELETE)
			this.cTlb.items.items[1].enable();
		else
			this.cTlb.items.items[1].disable();
	},

	selectFirstNode:function(){
		var node = this.cTreePanel.getNodeById(this.cTreePanel.root.firstChild.attributes.id);
		this.cTreePanel.fireEvent('click', node);
	}

});
