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
 * SVN: $Id: DynarangeSelection.js 4776 2011-03-28 14:25:45Z predragm $
 *
 */

Jedox.wss.grid.DynarangeSelection = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (sheet, props) {
		var startCoords = new Jedox.gen.Point(props.src[0], props.src[1]);
		Jedox.wss.grid.DynarangeSelection.parent.constructor.call(this, startCoords, sheet);

		// private fields

		// private methods

		// public fields
		this.dynarange = true;
		this._endCoords = new Jedox.gen.Point(props.src[2], props.src[3]);

		// privileged methods

		// constructor code
		this._ranges = [ new Jedox.wss.grid.DynarangeRange(this, this._startCoords, this._endCoords, props) ];

		this._firstRange = this._ranges[0];
		this._activeRange = 0;
	}
}
)();

// DynarangeSelection extends Selection
Jedox.util.extend(Jedox.wss.grid.DynarangeSelection, Jedox.wss.grid.Selection);

// public static methods

// public methods
clsRef = Jedox.wss.grid.DynarangeSelection;

clsRef.prototype._isRect = function() {
	return (this._ranges.length === 1);
};

clsRef.prototype.setMode = function(mode) {
	this._mode = mode;

	if (this._mode == Jedox.wss.range.RangeMode.EDIT) {
		Jedox.wss.hb.setAllNormal(this.getActiveRange().getId());
		this._environment.shared.defaultSelection.hide();
		this._selectionChanged = true;
		this.checkForUndoneMarkers();
	}

	this.getActiveRange().switchMode(mode);
};

clsRef.prototype.getProps = function() {
	return this.getActiveRange().getProps();
};

clsRef.prototype.setProps = function(props) {
	this.getActiveRange().setProps(props);
};

clsRef.prototype.hide = function() {
	this.setMode(Jedox.wss.range.RangeMode.HIDDEN);
};

clsRef.prototype.show = function() {
	this.setMode(Jedox.wss.range.RangeMode.NONE);
};

clsRef.prototype.redraw = function() {
	var actRng = this.getActiveRange();
	actRng.draw(false);
	actRng.setNormalMode();
};

clsRef.prototype.remove = function(perm) {
	this.getActiveRange().remove(perm);
};

clsRef.prototype.move = function(pos) {
	this.getActiveRange().move(pos);
};

clsRef = null;