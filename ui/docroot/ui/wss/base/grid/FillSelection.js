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
 * SVN: $Id: FillSelection.js 4776 2011-03-28 14:25:45Z predragm $
 *
 */

Jedox.wss.grid.FillSelection = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (startCoords, sheet)
	{
		Jedox.wss.grid.FillSelection.parent.constructor.call(this, startCoords, sheet);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
		this._ranges = [ new Jedox.wss.grid.FillRange(this, this._startCoords, this._startCoords) ];

		this._firstRange = this._ranges[0];
		this._activeRange = 0;
	}
}
)();

// FillSelection extends Selection
Jedox.util.extend(Jedox.wss.grid.FillSelection, Jedox.wss.grid.Selection);

// public static methods

// public methods
clsRef = Jedox.wss.grid.FillSelection;

clsRef = null;