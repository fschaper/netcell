/*
 * @brief ajax
 *
 * @file Group.js
 *
 * Copyright (C) 2006-2009 Jedox AG
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
 * SVN: $Id: CopyRange.js 4776 2011-03-28 14:25:45Z predragm $
 *
 */

Jedox.wss.grid.CopyRange = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (selection, startPoint, endPoint)
	{
		Jedox.wss.grid.CopyRange.parent.constructor.call(this, selection, startPoint, endPoint);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
		var that = this,
			panesLen = this._panes.length,
			htmlEl, htmlElCp;

		// Init presentation.

		// Add html elements for each line in an range:
		for(var clsName = 'formularRangeBorder', i = 3; i >= 0; --i) {
			htmlEl = document.createElement('div');
			htmlEl.className = clsName;

			for (var j = panesLen - 1; j >= 0; j--) {
				htmlElCp = j > 0 ? htmlEl.cloneNode(true) : htmlEl;

				this._edgeElems[j][i] = htmlElCp;
				this._containers[j].appendChild(htmlElCp);
			}
		}
	}
}
)();

// CopyRange extends Range
Jedox.util.extend(Jedox.wss.grid.CopyRange, Jedox.wss.grid.Range);

// public static methods

// public methods
clsRef = Jedox.wss.grid.CopyRange;


clsRef = null;