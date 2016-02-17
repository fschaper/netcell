/*
 * \brief book wrapper class
 *
 * \file Book.js
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
 * SVN: $Id: Book.js 5035 2011-06-06 14:12:12Z predragm $
 *
 */

Jedox.qa.wss.Book = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (name)
	{
		// private fields

		// private methods

		// public fields
		this._obj = name ? Jedox.wss.book.findByName(name) : Jedox.wss.app.activeBook;

		// privileged methods

		// constructor code
	};
}
)();

// public static fields

// public fields & methods
Jedox.qa.wss.Book.prototype = {

	// returns dom id prefix
	  pfx: function ()
	{
		return this._obj._domId;
	}

	// returns sheet selector toolbar
	, shslToolbar: function ()
	{
		return new Jedox.qa.cmp.Toolbar(this._obj._sheetSelector.getToolbar().id);
	}

	// returns sheet selector tabpanel
	, shslTabPanel: function ()
	{
		return new Jedox.qa.cmp.TabPanel(this._obj._sheetSelector.getTabPanel().id);
	}

	// returns scroll left button image
	, scrollLeft: function (id)
	{
		if (id == undefined)
			id = 0;

		return document.getElementById(this._obj._domId.concat('_hs', id, '_rwd'));
	}

	// returns scroll right button image
	, scrollRight: function (id)
	{
		if (id == undefined)
			id = 0;

		return document.getElementById(this._obj._domId.concat('_hs', id, '_fwd'));
	}

	// returns scroll up button image
	, scrollUp: function (id)
	{
		if (id == undefined)
			id = 0;

		return document.getElementById(this._obj._domId.concat('_vs', id, '_rwd'));
	}

	// returns scroll up button image
	, scrollDown: function (id)
	{
		if (id == undefined)
			id = 0;

		return document.getElementById(this._obj._domId.concat('_vs', id, '_fwd'));
	}

	// returns horizontal slider
	, horizSlider: function (id)
	{
		if (id == undefined)
			id = 0;

		return this._obj._hScrolls[id]._slider;
	}

	// returns vertical slider
	, vertSlider: function (id)
	{
		if (id == undefined)
			id = 0;

		return this._obj._vScrolls[id]._slider;
	}

};
