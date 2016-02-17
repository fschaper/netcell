/*
 * \brief class Window representing window
 *
 * \file Window.js
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: Window.js 5128 2011-07-18 14:31:43Z predragm $
 *
 */

Jedox.wss.wnd.Window = (function ()
{
	// private static fields
	var _id = 0;

	// private static methods

	// class constructor
	return function (cb, data)
	{
		var that = this,
				jwwnd = Jedox.wss.wnd,
				enaRestr = !Jedox.wss.app.UPRestrictMode;

		var conf = {
			title: data.name
			, renderTo: Jedox.wss.wspc.dom
			, width: 900
			, height: 300
			, minWidth: 350
			, minHeight: 150
			, maximizable: true
			, minimizable: enaRestr
			, bodyBorder: false
			, border: true
			, header: false
			, footer: false
			, plain: true
			, shadow: false
			, hideBorders: true
			, onEsc: Ext.emptyFn
			, closable: enaRestr
			, _minimized: false
		};

		jwwnd.Window.parent.constructor.call(this, conf);

		this._id = ++_id;
		this._data = data;
		jwwnd.reg[this._id] = this;
		jwwnd.active = this;

		this._domId = 'W'.concat(this._id);
		this._domCnts = {};

		this.on('activate', this._select);
		this.on('resize', this._fit);
		this.on('beforeclose', this._preunload);
		this.on('close', this._unload);

		this.show();
		this.maximize();

		this._spawnNode(cb, data);
	};
}
)();

Jedox.util.extend(Jedox.wss.wnd.Window, Ext.Window);

// public static fields

// public fields & methods
var _prototype = Jedox.wss.wnd.Window.prototype;

_prototype._spawnNode = function (cb, data)
{
	switch (data.type)
	{
		case 'workbook':
			this.node = new Jedox.wss.grid.Book(cb, this, data.uid, data.name, data.meta);
			break;
	}
}

_prototype._select = function (that)
{
	var node = that.node;

	if (!node) {
		if (that._data) {
			var skipProc = true;
			node = {_meta: that._data.meta, _name: that._data.name};
		} else
			return;
	}

	try
	{
		for (var triggers = Jedox.wss.events.triggers.switchWorkbook_before, i = triggers.length - 1; i >= 0; i--)
			triggers[i][0]['switchWorkbook_before'].call(parent, triggers[i][1], node._meta, node._name);
	}
	catch (e)
	{
		Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
	}

	if (!skipProc) {
		Jedox.wss.wnd.active = that;

		var status = node._select ? node._select() : true;

		if (status && node.refresh) {
			if (that.skipNodeRefresh === true)
				delete that.skipNodeRefresh;
			else
				node.refresh();
		}
	}

	try
	{
		for (var triggers = Jedox.wss.events.triggers.switchWorkbook_after, i = triggers.length - 1; i >= 0; i--)
			triggers[i][0]['switchWorkbook_after'].call(parent, triggers[i][1], node._meta, node._name);
	}
	catch (e)
	{
		Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
	}

	if (skipProc)
		delete that._data;
};

_prototype._fit = function (that)
{
	if (that._isMinimizing)
		return;

	var node = that.node;

	if (node && node._fit)
		node._fit();
};

_prototype._preunload = function (that)
{
	Jedox.wss.general.chkState();

	var node = that.node;

	if (!node)
		return true;

	try {
		for (var triggers = Jedox.wss.events.triggers.closeWorkbook_before, i = triggers.length - 1; i >= 0; --i)
			triggers[i][0]['closeWorkbook_before'].call(parent, triggers[i][1], node._meta, node._name);
	} catch (e) {
		Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
	}

	var that = this,
		jwgrid = Jedox.wss.grid;

	if (this._unloadRqst === true || Jedox.wss.app.environment.viewMode != jwgrid.viewMode.DESIGNER || (this.node._meta && this.node._meta.p < jwgrid.permission.PERM_WRITE))
		return true;

	if (this._unloadRqst)
		return false;

	function reUnload () {
		that._unloadRqst = true;
		that.unload();
	}

	function dywtsc(isSaved) {
		if (isSaved)
			return reUnload();

		var wasAct = Jedox.wss.wnd.active == that;

		if (!wasAct) {
			that.skipNodeRefresh = true;
			that.select();
		}

		Ext.MessageBox.show({
			title: 'File not saved'.localize(),
			msg: 'autosave_msg'.localize(),
			icon: Ext.MessageBox.WARNING,
			modal: true,
			buttons: Ext.MessageBox.YESNOCANCEL,
			buttonText: { yes: 'Yes'.localize(), no: 'No'.localize(), Cancel: 'Cancel'.localize() },

			fn: function (btn) {
				switch (btn) {
					case 'yes':
						Jedox.wss.node.save([ that, reUnload ], undefined, false);
						break;

					case 'no':
						reUnload();
						break;

					case 'Cancel':
						if (!wasAct)
							that.node.refresh();

						delete that._unloadRqst;
						break;
				}
			}
		});
	}

	Jedox.wss.node.chkSaved([this, dywtsc], node);

	return false;
};

_prototype._unload = function (that)
{
	var node = that.node;

	if (node._unload)
		node._unload();

	var jwwnd = Jedox.wss.wnd;

	if (jwwnd.active == that)
		jwwnd.active = undefined;

	delete jwwnd.reg[that._id];

	function cbRemove (res)
	{
		try
		{
			for (var triggers = Jedox.wss.events.triggers.closeWorkbook_after, i = triggers.length - 1; i >= 0; --i)
				triggers[i][0]['closeWorkbook_after'].call(parent, triggers[i][1], node._meta, node._name);
		}
		catch (e)
		{
			Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
		}
	}

	Jedox.wss.node.unload([ that, cbRemove ], node);
};

_prototype.show = function (animateTarget, callback, scope)
{
	Jedox.wss.wnd.Window.parent.show.call(this, animateTarget, callback, scope);

	if (this._minimized)
		this.collapse();
};

_prototype.select = function ()
{
	Jedox.wss.app.switchContextObserver.notify(this);
	this.toFront();
};

_prototype.unload = function ()
{
	this.close();
};

_prototype.minimize = function ()
{
	if (!this._minimized)
	{
		this._isMinimizing = true;
		if (this.id == Jedox.wss.wnd.active.id)
		{
			var arrWins = Jedox.wss.wnd.getVisible();
			if (arrWins.length > 1)
				Jedox.wss.wnd.active = arrWins[1];
		}

		this._restoreData = {
			h: ((this.maximized) ? this.restoreSize.height : this.getSize().height),
			w: ((this.maximized) ? this.restoreSize.width : this.getSize().width),
			x: ((this.maximized) ? this.restorePos[0] : this.x),
			y: ((this.maximized) ? this.restorePos[1] : this.y)
		};

		var titleSize = Ext.util.TextMetrics.measure(this.header.id, this.title);
		if (titleSize.width > 70)
		{
			var headerId = this.header.id;
			var getNewName = function(inName, inWidth)
			{
				if (Ext.util.TextMetrics.measure(headerId, inName + '...').width > inWidth)
					return getNewName(inName.substring(0, inName.length - 1), inWidth);
				else
					return inName + '...';
			}

			this._restoreData.title = this.title;
			this.setTitle(getNewName(this.title.substring(0, this.title.length - 1), 70));
		}

		this.restore();
		this._minimized = true;
		this.toBack();
		this.collapse();

		this.tools.restore.show();
		this.tools.maximize.show();
		this.tools.minimize.hide();

		this.setWidth(150); // width of minimized Window
		var wsH = Jedox.wss.wspc.getHeight();

		var minimizedWins = Jedox.wss.wnd.minimized;

		var i=0;
		for (; i<minimizedWins.length; i++)
		{
			if (!minimizedWins[i])
			{
				minimizedWins[i] = true;
				this.setPosition(2*(i + 1) + (150*i), wsH - this.header.getSize().height - 2);
				this._restoreData.position = i;
				break;
			}
		}
		if (i == minimizedWins.length)
		{
			minimizedWins[i] = true;
			this.setPosition(2*(i + 1) + (150*i), wsH - this.header.getSize().height - 2);
			this._restoreData.position = i;
		}
		delete this._isMinimizing;
	}
};

_prototype.restore = function ()
{
	if (this._minimized)
	{
		this.expand(false);

		this.setPosition(this._restoreData.x, this._restoreData.y);
		this.setSize(this._restoreData.w, this._restoreData.h);
		delete this.restorePos;
		delete this.restoreSize;

		if (this._restoreData.title)
			this.setTitle(this._restoreData.title);
		this._minimized = false;

		this.tools.minimize.show();
		this.tools.restore.hide();

		Jedox.wss.wnd.minimized[this._restoreData.position] = false;
		delete this._restoreData;
	}
	else
		Jedox.wss.wnd.Window.parent.restore.call(this);
};

_prototype.maximize = function ()
{
	Jedox.wss.wnd.Window.parent.maximize.call(this);

	if (this._minimized)
	{
		this._minimized = false;

		if (this.maximized)
		{
			this.restoreSize.width = this._restoreData.w;
			this.restorePos = [this._restoreData.x, this._restoreData.y];
			if (this._restoreData.title)
				this.setTitle(this._restoreData.title);
		}

		this.tools.minimize.show();

		Jedox.wss.wnd.minimized[this._restoreData.position] = false
		delete this._restoreData;
	}
};

_prototype.getName = function ()
{
	return this.title;
};

_prototype.setName = function (name)
{
	this.setTitle(name);
};

_prototype.getDom = function ()
{
	return this.body.dom;
};

_prototype.getDomCnt = function (id)
{
	if (id in this._domCnts)
		return ++this._domCnts[id];

	return this._domCnts[id] = 0;
};

_prototype.replaceNode = function (cb, data)
{
	var that = this,
		oldNode = this.node,
		saveOld = false;

	try {
		for (var triggers = Jedox.wss.events.triggers.replaceNode_before, i = triggers.length - 1; i >= 0; --i)
			triggers[i][0]['replaceNode_before'].call(parent, triggers[i][1], oldNode._meta, this.node._name);
	} catch (e) {
		Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
	}

	function cbSave() {
		Jedox.wss.node.unload(cb, oldNode);
	}

	function cbSpawn() {
		if (saveOld)
			Jedox.wss.node.save([that, cbSave], oldNode);
		else
			cbSave();
	}

	function unload() {
		try {
			that.node._unload();

			that.setTitle(data.name);
			that._spawnNode([that, cbSpawn], data);

			for (var triggers = Jedox.wss.events.triggers.replaceNode_after, i = triggers.length - 1; i >= 0; --i)
				triggers[i][0]['replaceNode_after'].call(parent, triggers[i][1], oldNode._meta, that.node._meta, that.node._name);
		} catch (e) {
			Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
		}
	}

	function dywtsc(isSaved) {
		if (isSaved) {
			unload();
			return;
		}

		Ext.MessageBox.show({
			title: 'File not saved'.localize(),
			msg: 'autosave_msg'.localize(),
			icon: Ext.MessageBox.WARNING,
			modal: true,
			buttons: Ext.MessageBox.YESNO,
			buttonText: { yes: 'Yes'.localize(), no: 'No'.localize()},

			fn: function (btn) {
				switch (btn) {
					case 'yes':
						saveOld = true;
						unload();
						break;

					case 'no':
						unload();
						break;
				}
			}
		});
	}

	if (Jedox.wss.app.environment.viewMode != Jedox.wss.grid.viewMode.DESIGNER)
		unload();
	else
		Jedox.wss.node.chkSaved([this, dywtsc], this.node);
};
