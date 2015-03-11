/*
 * \brief window component class
 *
 * \file Window.js
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
 * SVN: $Id: Window.js 4737 2011-03-21 13:26:18Z andrejv $
 *
 */

Jedox.qa.cmp.Window = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (id, data)
	{
		Jedox.qa.cmp.Window.parent.constructor.call(this, id, data);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.qa.cmp.Window, Jedox.qa.cmp.Generic);

// public static fields

// public fields & methods
var _prototype = Jedox.qa.cmp.Window.prototype;

// gets window tool: (common ids: 'close', 'minimize', 'maximize') buttons
_prototype.getTool = function (id)
{
	var cmp = Ext.getCmp(this._id) || Jedox.dlg.dlgRegistry.getActive().win;

	return cmp.getTool(id).dom;
};

//returns window's title
_prototype.getTitle = function(id)
{
	var cmp = Ext.getCmp(this._id);

	return cmp.title;
}

// returns buttons
_prototype.getBtn = function(btnId)
{
	var cmp = Jedox.dlg.dlgRegistry.getActive().components[btnId].getEl();
	if (cmp) return cmp.dom;
}

// returns dimensions
_prototype.getDims = function()
{
	var cmp = Ext.getCmp(this._id);

	return [cmp.getWidth(), cmp.getHeight()];
}