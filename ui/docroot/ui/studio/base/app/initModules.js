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
 * SVN: $Id: initModules.js 4655 2011-02-23 11:42:47Z srdjanv $
 *
 */

Jedox.studio.app.initModules = function(){

	var navigation = new Jedox.studio.app.navigation();
	var content = new Jedox.studio.app.content();
	var modules = [], navigationItems = [], contentItems = [], btnItems = [];

	var inits = Jedox.studio.app.modules;

	//pointers to init module functions
	for (i in inits){
		modules.push(inits[i]());
	}

	//rearange array to match order
	modules.sort(function (module1, module2){
		return module1.order - module2.order
	});


	for (var i = 0; i<modules.length; i++){
		navigationItems.push(modules[i].navigation);
		btnItems.push(modules[i].btn);

		/* fixing ext bug when panels with diferent hideMode ('visible', 'display') interfare in cardlayout (necessary for fixing scrambled wss grid in Files Manager and Report Manager iframe after switching to other modules *hiding containder)
		 * panels with hideMode:'visible' (Files Manager content and Report Manager content), should be added after panels with hideMode:'display' to avoid layout messed up after show/hide modules...
		 */

		if(modules[i].visibleHideMode)
			contentItems.push(modules[i].content);
		else
			contentItems.unshift(modules[i].content);
	}

	navigation.addCmp(navigationItems);
	content.addBtn(btnItems);
	content.addCmp(contentItems);


	return [navigation, content];

}