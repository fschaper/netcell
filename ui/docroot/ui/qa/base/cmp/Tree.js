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
 * SVN: $Id: Tree.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.qa.cmp.Tree = (function ()
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
	return function (id, data)
	{
		Jedox.qa.cmp.Tree.parent.constructor.call(this, id, data);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.qa.cmp.Tree, Jedox.qa.cmp.Generic);

// public fields & methods
var _prototype = Jedox.qa.cmp.Tree.prototype;

//send ID to be selected. Returns false if no such item.
_prototype.getNode = function (node)
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	var n = cmp.getRootNode().findChild("text", node, true);
	return (n) ? n.ui.elNode : false;
};

_prototype.expandByPath = function (cb, path)
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	var	cbSelPath = function(bSuccess, oSelNode) {
		if (cb instanceof Object)
			cb(bSuccess ? oSelNode.ui.elNode : false);
		else if (bSuccess)
			oSelNode.fireEvent('click', oSelNode, Ext.EventObject);
	}

	cmp.selectPath('/root'.concat(path), 'val', cbSelPath);
};

_prototype.expandNode = function (nodes)
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	var n;

	for (var i = 0; i < nodes.length; i++){
		n = cmp.getRootNode().findChild("text", nodes[i], true);
		if(n)
			n.expand();
	}

	return (n) ? n.ui.elNode : false;
};

_prototype.asyncExpandNode = function (cb, path)
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;
	
	if(!cmp.rootVisible)
		path = "/".concat(cmp.getRootNode().text,path);
	
	var	cbSelPath = function(bSuccess, oSelNode) {
		if (cb instanceof Object)
			cb(oSelNode != null ? oSelNode.ui.elNode : false);
	}
	
	cmp.expandPath(path, 'text', cbSelPath);
};

//simulates mouse right click event on component
//returns null if no context menu available
_prototype.rightClick = function (item)
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;

	if (item != undefined) {
		var node = (typeof(item) == 'string')? cmp.getRootNode().findChild("text", item, true) : cmp.getNodeById(item);
		if (!node) return;

		cmp.fireEvent('contextMenu', node, Ext.EventObject);
	}
	else
		cmp.fireEvent('containerContextMenu', cmp, Ext.EventObject);

	//TODO: contextMenu showAt(x,y)
};

//return plain nodes
_prototype.getPlainNodes = function(){
	var cmp = Ext.getCmp(this._id);
	cmp.expand(false);

	cmp.expandAll();
	if(cmp.loader.isLoading())
		return false;

	obj = cmp.getRootNode().attributes.children;

	var val = [];

	for(var i = 0; i < obj.length; i++)
		parseChild(val, obj[i]);

	return val;
}