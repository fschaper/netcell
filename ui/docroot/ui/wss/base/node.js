/*
 * \brief generic node handling routines
 *
 * \file node.js
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
 *
 * \version
 * SVN: $Id: node.js 5128 2011-07-18 14:31:43Z predragm $
 *
 */

Jedox.wss.node = new function ()
{
	var that = this;

	this.spawn = function (cb, type, meta, ext)
	{
		switch (type)
		{
			case 'workbook':
			case 'template':
				Jedox.wss.book.spawn(cb, ext.uid, ext.name, meta);
				break;
		}
	};

	this.load = function (cb, type, node, group, hierarchy, extra, pc)
	{
		switch (type)
		{
			case 'workbook':
			case 'template':
				Jedox.wss.book.load(cb, node, group, hierarchy, extra, pc);
				break;

			case 'frameset':
			case 'rframeset':
				Jedox.wss.frameset.load(cb, node, group, hierarchy, extra, pc);
				break;
		}
	};

	this.unload = function (cb, node)
	{
		if (node instanceof Jedox.wss.grid.Book)
			Jedox.wss.book.unload(cb, node.uid);
	};

	this.save = function (cb, node, showMsg)
	{
		if (!node || (!(node instanceof Jedox.wss.grid.Book)))
			node = Jedox.wss.wnd.active.node;

		if (showMsg == undefined)
			showMsg = true;

		if (node instanceof Jedox.wss.grid.Book)
			Jedox.wss.book.save(cb, node);
	};

	this.recover = function (cb, win, args)
	{
		if (cb)
			Jedox.wss.frameset.recover(cb, win);
		else
			Jedox.wss.book.recover(win, args);
	};

	this.chkSaved = function (cb, node)
	{
		if (node instanceof Jedox.wss.grid.Book)
			Jedox.wss.book.chkSaved(cb, node);
	};

	this.getPerm = function (node)
	{
		if (node instanceof Jedox.wss.grid.Book)
			return Jedox.wss.book.getPerm(node);
	};

}