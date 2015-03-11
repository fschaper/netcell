/*
 * \brief status bar setup
 *
 * Copyright (C) 2006-2011 Jedox AG
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: StatusBar.js 4605 2011-02-11 12:56:21Z predragm $
 *
 */

Jedox.wss.app.initStatusBar = function ()
{
	var modes = {
	  designer: 'Designer'.localize()
	, user: 'User'.localize()
	};

	var jwapp = Jedox.wss.app,
			itemInputMode = new Ext.Toolbar.TextItem({ text: 'Ready'.localize(), cls: 'statusBarStyle', style: 'width: 60px; padding: 0px 8px 0px 5px;' }),
			itemWorkingMode = new Ext.Toolbar.TextItem({ text: modes[jwapp.appMode], cls: 'statusBarStyle', style: 'width: 60px; padding: 0px 8px 0px 5px;' }),
			statusBar;

	Jedox.wss.app.statusBar = statusBar = new Ext.ux.StatusBar({
	  renderTo: 'statusBarContainer'
	, items: [
	    '<div id="activityIndctr" style="position: relative; left: -7px; top: -1px; width: 130px; height: 12px; background-image: url(/ui/wss/res/img/loading.gif); visibility: hidden;"></div>'
	  , new Ext.Toolbar.TextItem({ text: 'Status'.localize().concat(': '), cls: 'wssStatusBar' })
	  , itemInputMode
	  , ' '
	  , new Ext.Toolbar.TextItem({ text: 'Mode'.localize().concat(': '), cls: 'wssStatusBar' })
	  , itemWorkingMode
	  , ' '
	  ]
	});

	Ext.get('statusBarContainer').unselectable();

	// functions for setting new texts in statusbar parts
	statusBar.setInputMode = function (text)
	{
		Ext.fly(itemInputMode.getEl()).update(text);
	};

	statusBar.setWorkingMode = function (text)
	{
		Ext.fly(itemWorkingMode.getEl()).update(text);
	};

	// handler for call from menubar
	statusBar.hideShow = function (state)
	{
		if (state)
			jwapp.showBar('statusBarContainer');
		else
			jwapp.hideBar('statusBarContainer');
	};

	statusBar.doLayout();

	Jedox.backend.activityIndctr = document.getElementById('activityIndctr');
};
