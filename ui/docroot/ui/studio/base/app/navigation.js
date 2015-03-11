/*
 * @brief wss file
 *
 * Copyright (C) 2006-2010 Jedox AG
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
 * SVN: $Id: navigation.js 4482 2010-12-23 14:51:33Z andrejv $
 *
 */

Jedox.studio.app.navigation = function(){

	this._isReport = false;
	this.expandedFlag = false;
	//this.timer;


	var navigation = new Ext.Panel({
		layout: 'accordion',
		id: 'studio-accordion',
		bodyBorder: false, // useful for accordion containers since the inner panels have borders already
		bodyStyle: 'background-color: transparent;', // if all accordion panels are collapsed, this looks better in this layout --- hardcoded color moved to css class, see next line
		cls: 'studio-navigation-accordion'
	});

	// add to containers - nav - always on --Jedox.studio.app.containers.navBB =
	var navBottomBar = Jedox.studio.app.containers.navBB = new Ext.Toolbar({
		items:[
				{
					   iconCls: 'home-icon',
					   tooltip: 'Home Page'.localize(),
					   tabIndex: 90,
					   handler: function(){
					   	   	if (Ext.getCmp('studio-accordion').layout.activeItem)
					   		Ext.getCmp('studio-accordion').layout.activeItem.collapse();
				    }
				},
				'-',
				{
						text: 'Options'.localize(),
						iconCls: 'user-preferences-icon',
						tooltip: 'Options_tt'.localize(),
						tabIndex: 91,
						disabled: false,
						handler: function(){
							var prefs_level = {
								SERVER: 0,
								GROUP: 1,
								USER: 2
							};
							Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openPreferences, [prefs_level.USER, null]);
						}
					},
					{
						id: 'ps-help-btn',
						text: 'Help'.localize(),
						iconCls: 'help-icon',
						tabIndex: 92,
						tooltip: Jedox.studio.app.myPalo && Jedox.studio.app.myPalo.username && Jedox.studio.app.myPalo.password ? 'Help'.localize() : 'nregmsg'.localize(),
						disabled: !(Jedox.studio.app.myPalo && Jedox.studio.app.myPalo.username && Jedox.studio.app.myPalo.password),
						listeners: {
							click: function ()
							{
								var myPaloWin = window.open('' , '_blank'),
								myPaloDoc = myPaloWin.document;

								myPaloDoc.open();
								myPaloDoc.write('<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"><html xmlns="http://www.w3.org/1999/xhtml">');
								myPaloDoc.write('<head><title>Palo Web</title></head><body><form id="mypalo" action="https://www.jedox.com/login.php?lang='.concat(Jedox.studio.i18n.L10n, '" method="post">'));
								myPaloDoc.write('<input type="hidden" name="username" value="'.concat(Jedox.studio.app.myPalo.username, '" />'));
								myPaloDoc.write('<input type="hidden" name="password" value="'.concat(Jedox.studio.app.myPalo.password, '" />'));
								myPaloDoc.write('</form></body></html>');
								myPaloDoc.close();

								myPaloDoc.getElementById('mypalo').submit();
							}}
					},
					'-',
					{
						iconCls: 'logout-icon',
						text: 'Logout'.localize(),
						id: 'logoutBtn',
						tabIndex: 93,
						tooltip: 'Logout_tt'.localize(),
					   	listeners: {
							click: function() {
						   		Ext.Msg.show({
						   			title: 'Logout'.localize(),
						   			msg: 'logout_prompt'.localize(),
						   			buttons: Ext.Msg.OKCANCEL,
						   			buttonText: {OK: 'OK'.localize(), Cancel: 'Cancel'.localize()},
						   			closable: false,
						   			icon: Ext.MessageBox.QUESTION,
						   			fn: function(btn) {
						   					if (btn != 'ok')
						   						return;

						   					window.onbeforeunload = function () { };

						   					window.location.href = '/ui/login/?r';
						   				}
						   		});
						}},
					   scope: this
					}
		       ]
	});


	Jedox.studio.app.navigation.superclass.constructor.call(this, {
		id: 'ps-navigation-panel',
		title: 'Admin mode'.localize(),
		collapsible: true,
		collapsed:Jedox.studio.app.panelVisibility == "closed",
		region: 'west',
		split: true,
		width: 275,
		//minSize: 275,
		margins: '5 0 5 5',
		cmargins: '5 5 5 5',
		border: false,
		layout: 'fit',
		collapseMode:'mini',
		items: [navigation],
		listeners: {
			collapse: function(p){
				Ext.DomQuery.selectNode('*[id*=ps-navigation-panel]').style.display = "none";
			},
			expand: function(p){
				p.doLayout();
			}
		},
		bbar: navBottomBar
	});
}

Ext.extend(Jedox.studio.app.navigation, Ext.Panel, {

	addCmp:function(cmp){
		for (var i=0; i<cmp.length; i++)
			this.items.items[0].add(cmp[i]);
	},

	setWelcomePanelActive:function () {
		if (!this.expandedFlag){
			Ext.getCmp('ps-content-panel').layout.setActiveItem(0);
		}
	},

	setPanelActive:function (n){
		clearTimeout(this.timer);
		this.expandedFlag = true;
		Ext.getCmp('ps-content-panel').layout.setActiveItem(n);

	},

	isSelected:function (treePanel){
		var br = treePanel.root.childNodes.length;
		for (var i=0; i<br; i++)
			if (treePanel.root.childNodes[i].isSelected())
				return true;

			return false;
	}

});

