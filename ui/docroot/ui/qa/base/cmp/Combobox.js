/*
 * \brief combobox component class
 *
 * \file Combobox.js
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
 * SVN: $Id: Combobox.js 4762 2011-03-25 10:50:41Z andrejv $
 *
 */

Jedox.qa.cmp.Combobox = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (id, data)
	{
		Jedox.qa.cmp.Combobox.parent.constructor.call(this, id, data);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.qa.cmp.Combobox, Jedox.qa.cmp.Generic);

// public static fields

// public fields & methods
var _prototype = Jedox.qa.cmp.Combobox.prototype;

//if onDrop true, returns combobox trigger button, else return combobox input field. If combobox isn't editable, always returns trigger btn.
_prototype.forClick = function (onDrop)
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;
	return (cmp.editable && !onDrop)?  cmp.getEl().dom : cmp.trigger.dom;
};

//send ID or Text to be selected in combobox dropdown. Returns false if no such item. This will expand combobox if not expanded already
_prototype.forSelect = function (item)
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	if (!cmp.expanded) cmp.onTriggerClick();

	return (typeof(item) == 'string')? cmp.view.getNode(cmp.view.getStore().find(cmp.displayField, item)) : cmp.view.getNode(item);

};

// returns current value of combobox
_prototype.getValue = function ()
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	return cmp.getValue();
};

//returns id of selected item in dropdown box
_prototype.getSelected = function ()
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	if (!cmp.expanded) {
		cmp.onTriggerClick();
		cmp.collapse();
	}
	return cmp.view.getSelectedIndexes()[0];
};