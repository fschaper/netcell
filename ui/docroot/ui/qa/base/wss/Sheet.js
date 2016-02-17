/*
 * \brief sheet wrapper class
 *
 * \file Sheet.js
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
 * SVN: $Id: Sheet.js 4662 2011-02-27 18:44:45Z predragm $
 *
 */

Jedox.qa.wss.Sheet = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function ()
	{
		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

// public static fields

// public fields & methods
Jedox.qa.wss.Sheet.prototype = {

	// returns dom id prefix
	  pfx: function ()
	{
		return Jedox.wss.app.activeSheet._domId;
	}

	// returns column or row header dom
	, hdr: function (idx, pane)
	{
		var type;

		if (isNaN(idx))
		{
			type = 0;
			idx = Jedox.wss.formula.ltrs2num(idx);
		}
		else
		{
			type = 1;
			idx = idx | 0;
		}

		var sheet = Jedox.wss.app.activeSheet;

		return sheet._hdrArrs0[type][idx - sheet._aPane._currTopCell[type]];
	}

	// returns select all cell dom
	, selectAll: function ()
	{
		return document.getElementById(Jedox.wss.app.activeSheet._domId.concat('_gridSelectAll'));
	}

};