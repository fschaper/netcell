/*
 * \brief dataview component class
 *
 * \file DataView.js
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
 * Andrej Vrhovac <andrej.vrhovac@develabs.com>
 *
 * \version
 * SVN: $Id: DataView.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.qa.cmp.DataView = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (id, data)
	{
		Jedox.qa.cmp.DataView.parent.constructor.call(this, id, data);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.qa.cmp.DataView, Jedox.qa.cmp.Generic);

// public static fields

// public fields & methods
var _prototype = Jedox.qa.cmp.DataView.prototype;

_prototype.forSelect = function (item)
{
	// send ID or Text to be selected. Returns false if no such item.

	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	return (typeof(item) == 'string')? cmp.getNode(cmp.getStore().find(cmp.tpl.re.exec(cmp.tpl.html)[1], item)) : cmp.getNode(item);
};

//	simulates mouse right click event on component
//	returns null if no context menu available
_prototype.rightClick = function (item)
{
	// show context menu for specified item

	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	if (item != undefined) {
		var elm = (typeof(item) == 'string')? cmp.getNode(cmp.getStore().find(cmp.tpl.re.exec(cmp.tpl.html)[1], item)) : cmp.getNode(item);

		cmp.fireEvent('contextMenu', cmp, item, elm, Ext.EventObject);
	}
	else
		cmp.fireEvent('containerContextMenu', cmp, Ext.EventObject);

	//TODO: contextMenu showAt(x,y)
};

_prototype.getSelected = function ()
{
	// send ID or Text to be selected. Returns false if no such item.

	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	return cmp.getSelectedIndexes()[0];
};
