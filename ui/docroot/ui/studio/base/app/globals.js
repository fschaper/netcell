/*
 * \brief studio js globals
 *
 * \file globals.js
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
 * SVN: $Id: globals.js 5152 2011-07-28 10:02:33Z predragm $
 *
 */

Jedox.studio.access.permType =
{
  NONE: 0
, READ: 1
, WRITE: 2
, DELETE: 4
, SPLASH: 8
};

// Flag indicating global view mode (DESIGNER or USER).
//Jedox.studio.app.appMode;
//
//Jedox.studio.app.linkRequest;

//input modes
Jedox.studio.app.inputMode_studio_DEFAULT = 0;
Jedox.studio.app.inputMode_navigation_FILES = 1;
Jedox.studio.app.inputMode_navigation_REPORTS = 2;
Jedox.studio.app.inputMode_navigation_qREPORTS = 3;
Jedox.studio.app.inputMode_content_FILES = 4;

Jedox.studio.app.reportsRefreshFlag = false;
Jedox.studio.app.resourcesRefreshFlag = false; //after save as from wss, = TRUE, and trigger refresh on activate...

//obj = {group:"", hierarchy:""}
//Jedox.studio.app.defaultFiles;

Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;
//Jedox.studio.app.lastInputMode;

Jedox.studio.app.modules = {};
Jedox.studio.app.markers = {};
//Jedox.studio.users.internalConnection;

Jedox.studio.app.containers = {};

Jedox.studio.app.updateCheck = function ()
{
	var jsaccess = Jedox.studio.access;

	var cb = jsaccess.rules['system operations'] & jsaccess.permType.DELETE ?
		[ this, function (res)
		{
			if (res.charAt(0) != '1' || res.substr(2, 4) != 'http')
				return;

			Jedox.studio.app.showMsg('updateCheckTitle'.localize(), 'updateCheckText'.localize(), Ext.MessageBox.QUESTION, Ext.Msg.YESNO, [ this, function () { window.open(res.substr(2), '_blank'); } ], [ this, function () {} ]);
		} ]
		: null;

	Jedox.backend.rpc(cb, 'verinfo', 'updateCheck', [ Jedox.studio.i18n.L10n, cb != null ]);
};
