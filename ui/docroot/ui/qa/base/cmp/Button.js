/*
 * \brief button component class
 *
 * \file Button.js
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
 * SVN: $Id: Button.js 4796 2011-04-01 12:23:58Z andrejv $
 *
 */

Jedox.qa.cmp.Button = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (id, data)
	{
		Jedox.qa.cmp.Button.parent.constructor.call(this, id, data);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.qa.cmp.Button, Jedox.qa.cmp.Generic);

// public static fields

// public fields & methods
var _prototype = Jedox.qa.cmp.Button.prototype;

// returns expand arrow DOM on split button, else button itself
_prototype.expandArrow = function ()
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	// FIXME: not working for some buttons....
	return (cmp.arrowSelector)? cmp.el.child(cmp.arrowSelector).dom : cmp.getEl().dom;
};

// expands button menu if it has one, and clicks on menu item
_prototype.clickMenu = function (item){

	var cmp = Ext.getCmp(this._id);
	if (!cmp || !cmp.menu) return; else cmp.showMenu();
	if (item == undefined) return;

	return (typeof(item) == 'string')? cmp.menu.find("id", item)[0].getEl().dom : cmp.menu.get(item).getEl().dom;
};

//returns button state (toggle). Only for buttons with enableToggle: true
_prototype.state = function ()
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp || !cmp.enableToggle) return;

	return cmp.pressed;
};
