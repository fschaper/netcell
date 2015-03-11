/*
 * \brief WSS related QA routines
 *
 * \file wss.js
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
 * SVN: $Id: wss.js 5035 2011-06-06 14:12:12Z predragm $
 *
 */

Jedox.qa.wss = new function ()
{
	var that = this;

	this.wnd = function (title)
	{
		return new this.Window(title);
	};

	this.book = function (name)
	{
		return new this.Book(name);
	};

	this.sheet = function ()
	{
		return new this.Sheet();
	};

	this.cell = function (a1, paneId)
	{
		return new this.Cell(a1, paneId);
	};

	this.elem = function (name, paneId)
	{
		var elem = Jedox.wss.app.activeSheet.findElem(name);

		if (!elem)
			return false;

		if (elem instanceof Jedox.wss.wsel.ComboBox)
			return new this.Combobox(elem, paneId);
		else if (elem instanceof Jedox.wss.wsel.CheckBox)
			return new this.Checkbox(elem, paneId);
		else if (elem instanceof Jedox.wss.wsel.Button)
			return new this.Button(elem, paneId);
		else if (elem instanceof Jedox.wss.wsel.Chart)
			return new this.Chart(elem, paneId);
		else if (elem instanceof Jedox.wss.wsel.Picture)
			return new this.Picture(elem, paneId);

		return false;
	};

};