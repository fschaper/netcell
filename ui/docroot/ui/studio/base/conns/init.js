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
 * SVN: $Id: init.js 5087 2011-06-29 14:22:30Z mladent $
 *
 */


Jedox.studio.app.modules.conns = Jedox.studio.conns.init = function() {

	return {
		navigation: {
			id: 'c-tree-holder',
			title: 'Connection Manager nav'.localize(),
			layout:'fit',
			collapsed:true,
			items:[new Jedox.studio.conns.CTreePanel()],
			listeners:{
				expand: function(){
					this.body.dom.style.display = 'block';
					var that = Ext.getCmp('ps-navigation-panel');
					that.setPanelActive('c-main-panel');
					Ext.getCmp('sConnections_treeHolder_pnl').init();
					Ext.getCmp('c-main-panel').init();

					Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

					var cts = Jedox.studio.app.containers;
					cts.connTB = Ext.getCmp('sConnections_treeHolder_pnl_tb');
					if (Ext.getCmp('c-main-panel').layout.activeItem.id != 'connempty'){
						cts.connPan = Ext.getCmp('c-main-panel').tabPanel.getActiveTab();
						cts.connSCbtn = Ext.getCmp('conn-saveCancel-tb');
					}
				},
				collapse:function(){
					this.body.dom.style.display = 'none';
					var that = Ext.getCmp('ps-navigation-panel');
					that.timer = setTimeout(function(){that.expandedFlag = false; that.setWelcomePanelActive();}, 0);

					var cts = Jedox.studio.app.containers;
					delete cts.connTB;
					delete cts.connPan;
					delete cts.connSCbtn;
				}
//				resize:function(panel, adjWidth, adjHeight, rawWidth, rawHeight){
//					Ext.getCmp('sConnections_treeHolder_pnl').setHeight(adjHeight-50);
//					Ext.getCmp('sConnections_treeHolder_pnl').doLayout();
//				}
			}
		},
		content:new Jedox.studio.conns.CPanel(),
		btn:new Ext.Panel({
		    layout:'absolute',
			bodyStyle: 'background-color: transparent;',
			width:370,
			height:180,
			border:false,
		    defaults: {
				bodyStyle: 'background-color: transparent;',
				baseCls:'x-plain'
		    },
			items:[
				new Ext.ux.ImageButton({
					autoEl: {tag: 'img', src: '../lib/ext/resources/images/default/s.gif'},
				    width: 104,
				    height: 144,
					x:20,
					y:10,
					cls: 'w_connections',
					imgNormal: '../lib/ext/resources/images/default/s.gif',
				    imgOver: '../lib/ext/resources/images/default/s.gif',
				    imgClicked: '../lib/ext/resources/images/default/s.gif',
				    actionFn: function(){
						Ext.getCmp('c-tree-holder').expand();
					}
				}),
				{x:150, y:114, html:'<b>' + 'Connection'.localize() + '</b><br>' + 'Database connection administration'.localize(), baseCls:'x-plain'}
			]
		}),
		order:6
	}

};