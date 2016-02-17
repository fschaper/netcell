/*
 * \brief class representing default selection
 *
 * \file DefaultSelection.js
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: DefaultSelection.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.wss.grid.DefaultSelection = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (startCoords, sheet)
	{
		Jedox.wss.grid.DefaultSelection.parent.constructor.call(this, startCoords, sheet);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
		this._ranges = [ new Jedox.wss.grid.DefaultRange(this, this._startCoords, this._startCoords) ];

		this._firstRange = this._ranges[0];
		this._activeRange = 0;

		this._ranges[this._activeRange].activate();
		this._setLegacyVars();

/*
		this.draw();

		this._sheet.activateHdr(Jedox.wss.grid.headerType.COLUMN, this._environment.shared.selectedCellCoords[0], 'col_active');
		this._sheet.activateHdr(Jedox.wss.grid.headerType.ROW, this._environment.shared.selectedCellCoords[1], 'row_active');
*/
	}
}
)();

// DefaultSelection extends Selection
Jedox.util.extend(Jedox.wss.grid.DefaultSelection, Jedox.wss.grid.Selection);

// public static methods

// public methods
clsRef = Jedox.wss.grid.DefaultSelection;

clsRef.prototype._isRect = function() {
	return (this._ranges.length === 1);
};

clsRef.prototype.addRange = function(startPoint, endPoint) {
	return this._ranges.push(new Jedox.wss.grid.DefaultRange(this, startPoint, endPoint));
};

clsRef.prototype.expandToCell = function(cell) {
	this._selectionChanged = true;
	this._ranges[this._activeRange].expandToCell(cell);
};

clsRef.prototype.moveTo = function(x, y, mode) {
	this._selectionChanged = true;
	this._ranges[this._activeRange].moveTo(x, y);
	// TODO: mode == copy
	this.checkForUndoneMarkers();
};

clsRef.prototype.expand = function(amount, direction, defExpand) {
	this._selectionChanged = true;
	this._ranges[this._activeRange].expand(amount, direction, defExpand);
};

clsRef.prototype.show = function() {
	for (var i = this._ranges.length - 1; i >= 0; i--) {
		if (this._ranges[i].isVisible())
			return;

		this._ranges[i].show();
	}

	this._selectionChanged = true;
	this.checkForUndoneMarkers();
};

clsRef.prototype.jumpTo = function(rng) {
	this.set(new Jedox.gen.Point(rng[0], rng[1]), new Jedox.gen.Point(rng[2], rng[3]));
	this.draw();
};

clsRef.prototype.getCursorField = function() {
	return this._ranges[this._activeRange].getCursorField();
};

clsRef = null;