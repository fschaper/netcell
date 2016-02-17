/*
 * @brief ajax
 *
 * @file Group.js
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
 * SVN: $Id: menubar.js 2183 2009-09-24 13:32:27Z andrejv $
 *
 */


//TODO: Complete handler for all menu Items

Jedox.studio.app.initMenubar = function(){

	// Menus
	var fileMenu = new Ext.menu.Menu({
		id: 'fileMenu',
		enableScrolling: false,
		listeners: {
			hide: function(menu){
				menu.destroy();
			}
		},
		items: [{
			text: 'Options'.localize()
			//handler:
		}, '-', {
			text: 'Exit'.localize()
			//handler:onItemClick
		}]
	});


	var actionMenu = new Ext.menu.Menu({
		id: 'actionMenu',
		enableScrolling: false,
		listeners: {
			hide: function(menu){
				menu.destroy();
			}
		},
		items: [{
			text: 'New User'.localize().concat('...')
			//handler:
		}]
	});


	var helpMenu = new Ext.menu.Menu({
		id: 'helpMenu',
		enableScrolling: false,
		listeners: {
			hide: function(menu){
				menu.destroy();
			}
		},
		items: [{
			text: 'Help Topics'.localize()
			//cls:'mmenu',
			//handler:
		}]
	});


	// Main Menu
	var mainMenu = new Ext.Toolbar({
    	cls: "extmenubar"
    });
	mainMenu.render('mainMenu');


	mainMenu.add({
		text: 'File'.localize(),
		cls: "extmenubaritem",
		menu: fileMenu
		//handler:onButtonClick
	}, {
		text: 'Action'.localize(),
		menu: actionMenu,
		cls: "extmenubaritem"
		//handler:onButtonClick
	}, {
		text: 'Help'.localize(),
		menu: helpMenu,
		cls: "extmenubaritem"
		//handler:onButtonClick
	});
}
