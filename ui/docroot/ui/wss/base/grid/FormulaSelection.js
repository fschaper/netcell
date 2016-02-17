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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: FormulaSelection.js 4776 2011-03-28 14:25:45Z predragm $
 *
 */

Jedox.wss.grid.FormulaSelection = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (startCoords, sheet)
	{
		Jedox.wss.grid.FormulaSelection.parent.constructor.call(this, startCoords, sheet);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
		this.setVisibility(Jedox.wss.range.DisplayStatus.HIDDEN);
	}
}
)();

// FormulaSelection extends Selection
Jedox.util.extend(Jedox.wss.grid.FormulaSelection, Jedox.wss.grid.Selection);

// public static methods

// public methods
clsRef = Jedox.wss.grid.FormulaSelection;

clsRef.prototype.addRange = function(startPoint, endPoint, isPassive)
{
	return this._ranges.push(new Jedox.wss.grid.FormulaRange(this, startPoint, endPoint, isPassive));
};

clsRef.prototype.moveTo = function(x, y, mode) {
	this._ranges[this._activeRange].moveTo(x, y);
	// TODO: mode == copy

	//Jedox.wss.general.updateFormula(this._ranges[this._activeRange]);

	this.checkForUndoneMarkers();
};

clsRef.prototype.expand = function(amount, direction) {
	this._ranges[this._activeRange].expand(amount, direction);
	//Jedox.wss.general.updateFormula(this._ranges[this._activeRange]);
};

clsRef.prototype._refreshElement = function(scope, range) {
	range.formulaUpdate();
	range.draw();
};

clsRef = null;