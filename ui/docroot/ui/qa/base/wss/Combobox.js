/*
 * \brief combobox wrapper class
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
 * SVN: $Id: Combobox.js 5108 2011-07-11 14:03:59Z drazenk $
 *
 */

Jedox.qa.wss.Combobox = (function ()
{
	// private static fields

	// private static methods
	this.parseChild = function(val, node, pre){
		pre = pre == undefined ? '' : pre;

		val[val.length] = pre.concat('/',node.text);

		if(node.children != undefined)
			for(var i = 0; i < node.children.length; i++)
				parseChild(val, node.children[i], pre.concat('/',node.text));
	};

	// class constructor
	return function (obj, paneId)
	{
		Jedox.qa.wss.Combobox.parent.constructor.call(this, obj, paneId);

		// private fields

		// private methods

		// public fields
		this._cmp = this._obj.elem[this._pane._id];
		this._tree = this._obj.cmbTreeList[this._pane._id];

		this._qacmp = new Jedox.qa.cmp.Combobox(this._cmp.id);
		this._qatree = new Jedox.qa.cmp.Tree(this._tree.id);

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.qa.wss.Combobox, Jedox.qa.wss.Elem);

// public static fields

// public fields & methods
var _prototype = Jedox.qa.wss.Combobox.prototype;

_prototype.getNodes = function (item) {
	return this._tree.loader.getTreeNodeProvider().getData();
};

_prototype.getPlainNodes = function(item){
	var obj = this.getNodes(item);
	var val = [];

	for(var i = 0; i < obj.length; i++)
		parseChild(val, obj[i]);

	return val;
}

_prototype.forSelect = function (cb, item) {
	return this.forSelectByPath(cb, this._obj.getSelPath(this._tree.loader.getTreeNodeProvider().getData(), item));
};

_prototype.select = function (item) {
	return this.selectByPath(this._obj.getSelPath(this._tree.loader.getTreeNodeProvider().getData(), item));
};

_prototype.forSelectByPath = function (cb, path) {
	if (!this._cmp)
		return false;

	if (!this._cmp.expanded)
		this._cmp.onTriggerClick();

	this._qatree.expandByPath(cb, path);
};

_prototype.selectByPath = function (path) {
	if (!this._cmp)
		return false;

	if (!this._cmp.expanded)
		this._cmp.onTriggerClick();

	this._qatree.expandByPath(undefined, path);
	this._cmp.collapse();
};
