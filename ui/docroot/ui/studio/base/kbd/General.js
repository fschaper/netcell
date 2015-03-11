/*
 * \brief Keyboard General class.
 *
 * \file General.js
 *
 * Copyright (C) 2006-2010 Jedox AG
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: General.js 4854 2011-04-15 13:53:28Z lukap $
 *
 */

Jedox.kbd.General = (function () {

	// class constructor
	return function () {
		Jedox.kbd.General.parent.constructor.call(this);
	};

}
)();

// General extends Base
Jedox.util.extend(Jedox.kbd.General, Jedox.kbd.Base);

//public methods
clsRef = Jedox.kbd.General;

// tab
clsRef.prototype._9 = function() {
	var that = this,
		conts = Jedox.studio.app.containers,
		elems = [];

	for (var cont in conts)
		elems = elems.concat(conts[cont].findBy(function(component, container) {
			return that._chkTabIdx(component);
		}));

	this._tabFocus(elems);
	this._handleEnd();
};

// o - Options
clsRef.prototype._79 = function() {
	if (this.event[this.keyModifier])
	{
		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openPreferences, [2, null]);
		this._preventBubble();
	}
	else
		this._handleDefault();

	this._handleEnd();
};


// p - Palo OLAP Manager
clsRef.prototype._80 = function() {
	if (this.event[this.keyModifier])
		{
			setTimeout(function(){if (Ext.getCmp('palo-tree-holder')) Ext.getCmp('palo-tree-holder').expand();},1);
			this._preventBubble();
		}
	else
		this._handleDefault();

	this._handleEnd();
};

// h - Home
clsRef.prototype._72 = function() {
	if (this.event[this.keyModifier])
	{
		if (Ext.getCmp('studio-accordion').layout.activeItem)
			Ext.getCmp('studio-accordion').layout.activeItem.collapse();
		this._preventBubble();
	}
	else
		this._handleDefault();

	this._handleEnd();
};

// l - Logout
clsRef.prototype._76 = function() {
	if (this.event[this.keyModifier])
	{
		Ext.getCmp('logoutBtn').fireEvent('click');
		this._preventBubble();
	}
	else
		this._handleDefault();

	this._handleEnd();
};

// r - Reports
clsRef.prototype._82 = function() {
	if (this.event[this.keyModifier])
	{
		this._preventBubble();
		setTimeout(function(){
			if (Ext.getCmp('sReports_treeHolder_pnl')){
				Ext.getCmp('sReports_treeHolder_pnl').expand();
			}},1);
	}
	else
		this._handleDefault();

	this._handleEnd();
};


//f - Files
clsRef.prototype._70 = function() {
	if (this.event[this.keyModifier])
	{
		setTimeout(function(){
			if (Ext.getCmp('sFiles_treeHolder_pnl')){
			Ext.getCmp('sFiles_treeHolder_pnl').expand();
		}},1);
		this._preventBubble();
	}
	else
		this._handleDefault();

	this._handleEnd();
};

//u - User Manager
clsRef.prototype._85 = function() {
	if (this.event[this.keyModifier])
		{
			this._preventBubble();
			setTimeout(function(){if (Ext.getCmp('ug-tree-holder')) Ext.getCmp('ug-tree-holder').expand();}, 1);
		}
	else
		this._handleDefault();

	this._handleEnd();
};

// e - ETL Manager
clsRef.prototype._69 = function() {
	if (this.event[this.keyModifier])
		{
			setTimeout(function(){if (Ext.getCmp('etl-tree-holder')) Ext.getCmp('etl-tree-holder').expand();},1);
			this._preventBubble();
		}
	else
		this._handleDefault();

	this._handleEnd();
};

//n - Connections
clsRef.prototype._78 = function() {
	if (this.event[this.keyModifier])
		{
			setTimeout(function(){if (Ext.getCmp('c-tree-holder')) Ext.getCmp('c-tree-holder').expand();},1);
			this._preventBubble();
		}
	else
		this._handleDefault();

	this._handleEnd();
};

// HOME - Homepage
clsRef.prototype._36 = function() {
	this._72();
};

// F1 - Help
clsRef.prototype._112 = function() {

	if (!Ext.getCmp('ps-help-btn').disabled)
		Ext.getCmp('ps-help-btn').fireEvent('click');
	this._preventBubble();

	this._handleEnd();
};

clsRef = null;