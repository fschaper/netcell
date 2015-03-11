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
 * SVN: $Id: init.js 4869 2011-04-19 11:15:47Z lukap $
 *
 */


Jedox.studio.app.modules.files = Jedox.studio.files.init = function() {

	return {
		navigation: new Ext.Panel({
			title: 'File Manager'.localize(),
			id: 'sFiles_treeHolder_pnl',
			items: Jedox.studio.files.FTreePanel(),
			collapsed:true,
			listeners:{
				expand: function(p){
						this.body.dom.style.display = 'block';
						var that = Ext.getCmp('ps-navigation-panel');
						that.setPanelActive('wt-panel');
						Ext.getCmp('rt-main-panel').fireEvent('initTlb');
						Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

						var ct = Jedox.studio.app.containers;
						ct.fTreeTB = Ext.getCmp('f-tree-tlb');

						Jedox.kbd.ctxRegistry.add('Files');
				},
				collapse:function(p){
					this.body.dom.style.display = 'none';
					var that = Ext.getCmp('ps-navigation-panel');
					that.timer = setTimeout(function(){that.expandedFlag = false; that.setWelcomePanelActive();}, 0);

					var ct = Jedox.studio.app.containers;
					delete ct.fTreeTB;

					Jedox.kbd.ctxRegistry.remove('Files','General');
				},
				resize:function(panel, adjWidth, adjHeight, rawWidth, rawHeight){
					Ext.getCmp('sFiles_tree_tr').setHeight(adjHeight-50);
					Ext.getCmp('sFiles_tree_tr').doLayout();
				}
			}
		}),
		content:new Jedox.studio.files.WTPanel(),
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
					cls: 'w_resources',
					imgNormal: '../lib/ext/resources/images/default/s.gif',
				    imgOver: '../lib/ext/resources/images/default/s.gif',
				    imgClicked: '../lib/ext/resources/images/default/s.gif',
				    actionFn: function(){
						Ext.getCmp('sFiles_treeHolder_pnl').expand();
					}
				}),
				{x:150, y:114, html:'<b>' + 'File Manager'.localize() + '</b><br>' + 'Files and folders'.localize(), baseCls:'x-plain'}
			]
		}),
		order:1,
		visibleHideMode:true
	}

};