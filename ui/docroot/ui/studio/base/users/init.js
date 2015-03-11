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


Jedox.studio.app.modules.users = Jedox.studio.users.init = function() {

	return {
		navigation: {
			id: 'ug-tree-holder',
			title: 'User Manager'.localize(),
			autoScroll:true,
			collapsed:true,
			items: [Jedox.studio.users.UGTreePanel()],
			listeners:{
				expand: function(){
					Jedox.studio.users.paloConn = Jedox.studio.users.paloConn || null;

					this.body.dom.style.display = 'block';
					var that = Ext.getCmp('ps-navigation-panel');
					var ugTreePanel = this.items.items[0];
					ugTreePanel.fireEvent('refreshToolbarCombo');
					if (!that.isSelected(ugTreePanel))
						ugTreePanel.root.firstChild.select();

					that.setPanelActive('ug-content');
					that.setPanelActive('ug-panel');

					Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

					// set active containers:
					var cts = Jedox.studio.app.containers;
					cts.ugrTb = Ext.getCmp('connToolbar');
					cts.ugrGrid = Ext.getCmp('ug-grid-panel').layout.activeItem.topToolbar;
				},
				collapse:function(){
					// stop editing if row editor is active
					if (Ext.getCmp('gridRowEditorUsers')) Ext.getCmp('gridRowEditorUsers').stopEditing(false);
					//
					this.body.dom.style.display = 'none';
					var that = Ext.getCmp('ps-navigation-panel');
					that.timer = setTimeout(function(){that.expandedFlag = false; that.setWelcomePanelActive();}, 0);

					var cts = Jedox.studio.app.containers;
					delete cts.ugrTb;
					delete cts.ugrGrid;

					delete cts.ugrDetPan;
					delete cts.ugrOpenInNT;
					delete cts.ugrSaveCancelBtn;
				}
			}
		},
		content:new Ext.Panel({
			id:'ug-content',
			layout:'fit',
			title:'User Manager'.localize(),
			items:new Jedox.studio.users.UGPanel()
		}),
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
					cls: 'w_users',
					imgNormal: '../lib/ext/resources/images/default/s.gif',
				    imgOver: '../lib/ext/resources/images/default/s.gif',
				    imgClicked: '../lib/ext/resources/images/default/s.gif',
				    actionFn: function(){
						Ext.getCmp('ug-tree-holder').expand();
					}
				}),
				{x:150, y:114, html:'<b>' + 'Users and Groups'.localize() + '</b><br>' + 'Users and Groups administration'.localize(), baseCls:'x-plain'}
			]
		}),
		order:4
	}

};