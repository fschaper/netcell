/*
 * \brief cell wrapper class
 *
 * \file Cell.js
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
 * SVN: $Id: Cell.js 5036 2011-06-07 09:12:44Z drazenk $
 *
 */

Jedox.qa.wss.Cell = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (a1, paneId)
	{
		// private fields

		// private methods

		// public fields
		var ref = Jedox.wss.formula.parseCell(a1);

		this._col = ref[1];
		this._row = ref[2];

		var activeSheet = Jedox.wss.app.activeSheet;

		this._pane = paneId in activeSheet._panes ? activeSheet._panes[paneId] : activeSheet._aPane;

		// privileged methods

		// constructor code
	};
}
)();

// public static fields

// public fields & methods
Jedox.qa.wss.Cell.prototype = {

	// returns cell's div
	  dom: function ()
	{
		return this._pane.getCellByCoords(this._col, this._row);
	}

	, hyperlink: function ()
	{
		var cell = this.dom();
		return cell.childNodes.length && cell.childNodes[0].tagName == 'SPAN' ? cell.childNodes[0] : false;
	}

	// returns specific property from cell storage
	, prop: function (type)
	{
		var cell = this._pane.getCell(this._col, this._row);

		return cell[type];
	}

	, dblClick: function()
	{
		this._pane.cbFire(this._col, this._row, 'dblclick', {c: this._col, r: this._row});
	}

	, contextMenu: function(pos)
	{
		var elem = Ext.get(this.dom()),
			cmPos = {clientX: elem.getX() + elem.getWidth()/2, clientY: elem.getY() + elem.getHeight()/2};
		if (pos)
		{
			cmPos.clientX = pos[0];
			cmPos.clientY = pos[1];
		}

		Jedox.wss.mouse.mimicCellMouseEvent(this._col, this._row, 'mousedown', this._pane);
		Jedox.wss.mouse.mimicCellMouseEvent(this._col, this._row, 'mouseup', this._pane);
		Jedox.wss.mouse.showMainCntxMenu(cmPos);
	}
};