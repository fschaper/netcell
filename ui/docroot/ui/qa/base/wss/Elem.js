/*
 * \brief base element wrapper class
 *
 * \file Elem.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: Elem.js 5100 2011-07-08 13:45:16Z drazenk $
 *
 */

Jedox.qa.wss.Elem = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (obj, paneId)
	{
		// private fields

		// private methods

		// public fields
		this._obj = obj;
		this._pane = this._getPaneById(paneId);
		this._env = this._pane._env;
		this._qacmp = null;

		// privileged methods

		// constructor code
	};
}
)();

// public static fields

// public fields & methods
Jedox.qa.wss.Elem.prototype = {

	_getPaneById: function (paneId) {
		var	activeSheet = Jedox.wss.app.activeSheet;
		return isNaN(paneId = parseInt(paneId)) || paneId < 0 || paneId > activeSheet._panes.length - 1 ? activeSheet._aPane : activeSheet._panes[paneId];
	},

	getValue: function () {
		return this._qacmp.getValue();
	},

	forClick: function () {
		return this._qacmp.forClick();
	},

	forKeys: function () {
		return this._qacmp.forKeys();
	},

	forSelect: function (item) {
		return this._qacmp.forSelect(item);
	},

	forContextSelect: function (item) {
		var gsCoords = this._env.shared.gridScreenCoords[0];

		if (!gsCoords.length)
			gsCoords = [0, 0];

		var ctx = this._obj.showContextMenu(undefined, this._pane._id, [this._obj.conf.left + this._obj.conf.width / 2 + gsCoords[0], this._obj.conf.top + this._obj.conf.height / 2 + gsCoords[1]]);

		if (ctx instanceof Ext.menu.Menu)
			return (new Jedox.qa.cmp.Menu(ctx.getId())).forSelect(item);
	}

};
