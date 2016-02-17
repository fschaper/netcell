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
 * SVN: $Id: content.js 5022 2011-06-01 07:35:29Z lukap $
 *
 * \see
 * LICENSE.txt
 *
 */


Jedox.studio.app.content = function(){
	var that = this;

	var welcomePanel = this.getWelcomePanel();


	Jedox.studio.app.content.superclass.constructor.call(this, {
		id: 'ps-content-panel',
		region: 'center', // this is what makes this panel into a region within the containing layout
		layout: 'card',
		border:false,
		margins: '5 5 5 0',
		bodyStyle: 'background-color: transparent;',
		activeItem: 0,
		items: [welcomePanel]
	});
}


Ext.extend(Jedox.studio.app.content, Ext.Panel, {

	addCmp:function(cmp){
		for (var i=0; i<cmp.length; i++)
			this.add(cmp[i]);
	},

	addBtn:function(btn){
		for (var i=0; i<btn.length; i++)
			this.items.items[0].items.items[0].add(btn[i]);
	},

	getWelcomePanel:function(){

		var that = this;

		var btnPanel = new Ext.Panel({
		    layout:'table',
			border:false,
			width:750,
		    layoutConfig: {
		        columns: 2
		    }
		});

		var recentStore = new Ext.data.SimpleStore({
			fields: [
				{name: 'context', type: 'string'},
				{name: 'location'},
				{name: 'type', type: 'string'},
				{name: 'path', type: 'string'},
				{name: 'iconCls',type: 'string'}
			]
		});


		var recentListView = new Ext.DataView({
			id: 'recent-list-view',
			store: recentStore,
			tpl: new Ext.XTemplate('<div class="recent-list-view"><tpl for=".">', '<div class="thumb-wrap">',
				'<div class="thumb" style="padding: 0px; text-align: left;"><img class="{iconCls}" src="../lib/ext/resources/images/default/s.gif" width="16" height="16">',
				'<span>&nbsp;{path}</span></div></div><div class="br"><br></div>', '</tpl></div>'),
			autoWidth:true,
			autoHeight:true,
			multiSelect: false,
			singleSelect: true,
			overClass: 'x-view-over',
			itemSelector: 'div.thumb-wrap',
			emptyText: '',
			tooltip:null,
			listeners: {
				click: function(dataView, index, node, e){
					var data = dataView.getStore().getAt(index);
					var context = data.get('context');
					var location = data.get('location');
					var g = location.group;
					var h = location.hierarchy;
					var n = location.node;
					var t = data.get('iconCls').split('_').pop();
					var p = location.path;
					var vars = location['var'];
					var type = data.get('type');
					var name = (location && location.path && location.path.length != 0)? location.path.split('/').pop():'unknown'.localize();

					switch (context){
						case 'files':
							Jedox.studio.files.openRecentClb = function(){
								Ext.getCmp('wt-panel').openRecent({g:g, h:h, n:n, t:t, p:p}, name, type);
								Jedox.studio.files.openRecentClb = null;
							}
							Ext.getCmp('sFiles_treeHolder_pnl').expand();
							break;
						case 'reports':
							Jedox.studio.reports.cbf = function(){
							if (Jedox.studio.access.rules.ste_reports & Jedox.studio.access.permType.WRITE)
								Ext.getCmp('sReports_tree_tr').fireEvent('switchToQV', {g:g, h:h, n:n, rPath:location.path, open:false});
								Ext.getCmp('reports-content-panel').fireEvent('openRecent', {g:g, h:h, n:n, t:t, p:p, v:vars}, name, type);
							}
							Ext.getCmp('sReports_treeHolder_pnl').expand();
							break;
						default:
							break;
					}

				},
				contextmenu : function(dataView, index, node, e){
					var data = dataView.getStore().getAt(index);
					var context = data.get('context');
					var location = data.get('location');
					var g = location.group;
					var h = location.hierarchy;
					var n = location.node;
					var expToHF = (context == 'reports' && g.charAt(0) == 'f')? true:false;

			       var menu = new Ext.menu.Menu({
		                enableScrolling: false,
		        		listeners: {
		    				hide: function(menu){
		    					menu.destroy();
		    				}
		    			},
		                items: [{
		                    text:'Open'.localize(),
							iconCls: 'open-folder-icon',
							handler:function(){dataView.fireEvent('click', dataView, index, node, e);}
		                },{
		                    text:'Explore To'.localize(),
							hidden:expToHF,
							iconCls: 'view-list-icon',
							handler:function(){
								if (context == 'files')
									Ext.getCmp('sFiles_tree_tr').fireEvent('onExplore', g, h, n);
								else{
									Jedox.studio.reports.cbf = function(){
										if (Jedox.studio.access.rules.ste_reports & Jedox.studio.access.permType.WRITE)
											Ext.getCmp('sReports_tree_tr').fireEvent('switchToQV', {g:g, h:h, n:n, rPath:location.path, open:false});
									}
									Ext.getCmp('sReports_treeHolder_pnl').expand();
									// TODO: check this for more elegant solution
								}
							}
		                }]
					});

					e.stopEvent();
					menu.showAt(e.getXY());
				},
				mouseenter : function(dataView, index, node, e) {
					var data = dataView.getStore().getAt(index);
					var context = data.get('context');
					var title = context.substr(0, 1).toUpperCase() + context.substr(1);
					var location = data.get('location');
					var path = (context == 'reports' && location.group.charAt(0) == 'f')?  'location unknown (opened throught hyperlink)'.localize():location.path;


					if (!this.tooltip) {
						this.tooltip = new Ext.ToolTip({
							target: this.id,
							title:title,
							layout: 'fit',
							items:new Ext.form.Label({
        						text: path
							}),
							trackMouse: true,
							tplWriteMode:'overwrite'
						});
					}
					else {
						this.tooltip.setTitle(title);
						this.tooltip.items.items[0].setText(path);
					}

					this.tooltip.showAt(e.xy);
				},
				mouseleave : function(dataView, index, node, e){
					this.tooltip.hide();
				}
			}
		});


		var recentContainer = new Ext.Panel({
		    layout:'fit',
			x:40,
			y:40,
			width:700,
			height:200,
			autoScroll:true,
			border:true,
			items:[
				recentListView
			]
		});


		var clearBtn = {
			text:'Clear list'.localize(),
			tabIndex: 99,
			handler: function(){
				function cb(){
					Ext.getCmp('recent-list-view').getStore().removeAll();
				}
				Jedox.backend.rpc([this, cb], 'common', 'clearRecent');
			}
		}


		var clearBtnPanel = {
			layout:'form',
			border:false,
			bodyStyle:'padding:0px',
			width:700,
			height:20,
			x:40,
			y:245,
			buttons:[clearBtn]
		}


		var recentPanel = new Ext.Panel({
		    layout:'absolute',
			width:750,
			height:280,
			border:false,
			items:[
				{x:40, y:20, html:'<b><td>' + 'Recent Documents'.localize() + '</b>', baseCls:'x-plain'},
				recentContainer,
				clearBtnPanel
			]
		});



		var welcomePanel = new Ext.Panel({
				layout:'form',
				autoScroll:true,
			    defaults: {
			        bodyStyle:'padding:20px'
			    },
				items: [
					btnPanel,
					recentPanel
				],
				listeners:{
					beforeshow:function(){
						that.reloadRecent();
					}
				}
			});

		return welcomePanel;
	},

	reloadRecent:function(){

		function cb(result){
			var recentData = [];
			if (result) {
				for (var i = result.length-1; 0<=i; i--) {
					recentData.push([result[i].context, result[i].location, result[i].type, (result[i].location && result[i].location.path && result[i].location.path != 0)? result[i].location.path.split('/').pop():'unknown'.localize(), result[i].subtype? 'w3s_'.concat(result[i].subtype):'w3s_'.concat(result[i].type == 'spreadsheet'? 'workbook':result[i].type) /*result[i].iconCls*/]);
				}

				Ext.getCmp('recent-list-view').getStore().loadData(recentData);
			}

			setTimeout(function(){Jedox.studio.app.viewport.setReady(true);});

		}

		Jedox.backend.rpc([this, cb], 'common', 'fetchRecent');

	}

});

