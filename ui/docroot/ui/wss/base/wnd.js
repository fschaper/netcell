/*
 * \brief routines handling windows
 *
 * \file wnd.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: wnd.js 4662 2011-02-27 18:44:45Z predragm $
 *
 */

Jedox.wss.wnd = new function ()
{
	var that = this;

	this.reg = {};

	this.minimized = [];

	this.active = null;

	this.arrangement = 'tiled';

	this.selectById = function (id)
	{
		if (id in that.reg)
			that.reg[id].select();
	};

	this.findByMeta = function (name, meta)
	{
		var win, node;

		for (var i in that.reg)
		{
			win = that.reg[i];
			node = win.node;

			if (!node)
				continue;

			if (
				node._name == name &&
				(meta ?
					node._meta && ((node._meta.g == meta.g && node._meta.h == meta.h && node._meta.n == meta.n) ||
						(!meta.g.search(/^f/) ? node._meta.fg == meta.g && node._meta.fh == meta.h && node._meta.fn == meta.n : false)) :
					!node._meta
				)
			)

				return win;
		}

		return false;
	};

	this.selectByMeta = function (name, meta)
	{
		var win = this.findByMeta(name, meta);

		if (win === false) {
			Jedox.wss.general.showMsg('Application Error'.localize(), 'noWBtoSwitch'.localize(), Ext.MessageBox.ERROR);
			return false;
		}

		return win.select();
	};

	this.closeByMeta = function (name, meta)
	{
		var win = this.findByMeta(name, meta);

		if (win === false) {
			try {
				for (var triggers = Jedox.wss.events.triggers.closeWorkbook_after, i = triggers.length - 1; i >= 0; --i)
					triggers[i][0]['closeWorkbook_after'].call(parent, triggers[i][1], meta, name);
			} catch (e) {
				Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
			}
		}

		win.unload();
	};

	this.findByTitle = function (title)
	{
		var win;

		for (var i in that.reg)
		{
			win = that.reg[i];

			if (win.title == title)
				return win;
		}

		return false;
	};

	this.getVisible = function ()
	{
		if (!that.active)
			return [];

		var list = [ that.active ],
				activeId = that.active._id,
				win;

		for (var i in that.reg)
		{
			win = that.reg[i];

			if (win._id != activeId && win.isVisible() && !win._minimized)
				list.push(win);
		}

		return list;
	};

	this.getHidden = function ()
	{
		if (!that.active)
			return [];

		var list = [],
				win;

		for (var i in that.reg)
		{
			win = that.reg[i];

			if (!win.isVisible())
				list.push(win);
		}

		return list;
	};

	this.hideActive = function ()
	{
		if (that.getVisible().length < 2) // hide only if there are more then 1 window
			return;

		var node = that.active.node;

		if (!node)
			return;

		try
		{
			for (var triggers = Jedox.wss.events.triggers.hideWorkbook_before, i = triggers.length - 1; i >= 0; i--)
				triggers[i][0]['hideWorkbook_before'].call(parent, triggers[i][1], node._meta, node._name);

			that.active.hide();
			Jedox.wss.action.adjustToACL();

			for (var triggers = Jedox.wss.events.triggers.hideWorkbook_after, i = triggers.length - 1; i >= 0; i--)
				triggers[i][0]['hideWorkbook_after'].call(parent, triggers[i][1], node._meta, node._name);
		}
		catch (e)
		{
			Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
		}
	};

	this.hasMinimized = function ()
	{
		for (var i = that.minimized.length - 1; i >= 0; --i)
			if (that.minimized[i])
				return true;

		return false;
	};

	this.triggerCloseEvt = function (name, meta)
	{
		try
		{
			for (var triggers = Jedox.wss.events.triggers.closeWorkbook_after, i = triggers.length - 1; i >= 0; --i)
				triggers[i][0]['closeWorkbook_after'].call(parent, triggers[i][1], meta, name);
		}
		catch (e)
		{
			Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
		}
	};

}