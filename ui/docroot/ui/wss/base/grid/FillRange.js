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
 * SVN: $Id: FillRange.js 4776 2011-03-28 14:25:45Z predragm $
 *
 */

Jedox.wss.grid.FillRange = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (selection, startPoint, endPoint)
	{
		Jedox.wss.grid.FillRange.parent.constructor.call(this, selection, startPoint, endPoint);

		// private fields

		// private methods

		// public fields
		//this._initUpperLeft;
		//this._initLowerRight;
		this._active = false;
		//this._latestChangedCell;
		this._direction = Jedox.wss.grid.ScrollDirection.NONE;
		//this._dmUpperLeft;
		//this._dmLowerRight;
		this._dmActive = false;
		//this._mdLRCornerPx;

		// privileged methods

		// constructor code

		var that = this,
			panesLen = this._panes.length,
			htmlEl, htmlElCp;

		// Init presentation.

		// Add html elements for each line in an range:
		for (var clsName = 'fillRangeBorder', i = 3; i >= 0; --i) {
			htmlEl = document.createElement('div');
			htmlEl.className = clsName;

			for (var j = panesLen - 1; j >= 0; j--) {
				htmlElCp = j > 0 ? htmlEl.cloneNode(true) : htmlEl;
				this._edgeElems[j][i] = htmlElCp;

				this._containers[j].appendChild(htmlElCp);
			}
		}

		// Add Delete Marker.
		this._delMarker = [];

		var delMarker = document.createElement('div'), delMarkerCp;
		delMarker.className = 'fillDelMarker';

		for (j = panesLen - 1; j >= 0; j--) {
			delMarkerCp = j > 0 ? delMarker.cloneNode(true) : delMarker;

			this._delMarker[j] = delMarkerCp;
			this._containers[j].appendChild(delMarkerCp);
		}
	}
}
)();

// FillRange extends Range
Jedox.util.extend(Jedox.wss.grid.FillRange, Jedox.wss.grid.Range);

clsRef = Jedox.wss.grid.FillRange;

// public static methods

// public methods

clsRef.prototype.getOffsetsPx = function(useragent) {
	var offsets = [];

	switch(useragent) {
		case 'ff':
			offsets = [
				{left : 0, top : 0, width : -1, height : 0},
				{left : 0, top : -2, width : 2, height : 0},
				{left : 0, top : 0, width : 0, height : 0},
				{left : -1, top : 0, width : 0, height : 0}
			];
			break;

		case 'sf':
			offsets = [
				{left : 0, top : 0, width : -1, height : 0},
				{left : 0, top : -2, width : 2, height : 0},
				{left : 0, top : 0, width : 0, height : 0},
				{left : -1, top : 0, width : 0, height : 0}
			];
			break;

		case 'ie':
			offsets = [
				{left : 0, top : 0, width : -1, height : 0},
				{left : 0, top : -2, width : 2, height : 0},
				{left : 0, top : 0, width : 0, height : 0},
				{left : -1, top : 0, width : 0, height : 0}
			];
			break;

		case 'ch':
			offsets = [
				{left : 0, top : 0, width : -1, height : 0},
				{left : 0, top : -2, width : 2, height : 0},
				{left : 0, top : 0, width : 0, height : 0},
				{left : -1, top : 0, width : 0, height : 0}
			];
			break;

		default:
			offsets = [
				{left : 0, top : 0, width : 0, height : 0},
				{left : 0, top : 0, width : 0, height : 0},
				{left : 0, top : 0, width : 0, height : 0},
				{left : 0, top : 0, width : 0, height : 0}
			];
			console.warn("Unkown user agent: ", useragent);
	}

	return offsets;
};

clsRef.prototype.draw = function() {
	if(this._status == Jedox.wss.range.AreaStatus.EXPANDING)
		return;

	var ulOffset = 1, lrOffset = 1, pxCoords;
	this._realCoords = this.getCorners();

	if((this._ulCell = this._pane.getCellByCoords(this._realCoords[0].getX(), this._realCoords[0].getY())) == undefined)
	{
		pxCoords = this._pane.getPixelsByCoords(this._realCoords[0].getX(), this._realCoords[0].getY());

		this._ulCorner.setX(pxCoords[0] - ulOffset);
		this._ulCorner.setY(pxCoords[1] - ulOffset);
	}
	else
	{
		this._ulCorner.setX(this._ulCell.offsetLeft - ulOffset);
		this._ulCorner.setY(this._ulCell.parentNode.offsetTop - ulOffset);
	}

	if((this._lrCell = this._pane.getCellByCoords(this._realCoords[1].getX(), this._realCoords[1].getY())) == undefined)
	{
		pxCoords = this._pane.getPixelsByCoords(this._realCoords[1].getX() + 1, this._realCoords[1].getY() + 1);

		this._lrCorner.setX(pxCoords[0]);
		this._lrCorner.setY(pxCoords[1] + lrOffset);
	}
	else
	{
		this._lrCorner.setX(this._lrCell.offsetLeft + this._lrCell.offsetWidth);
		this._lrCorner.setY(this._lrCell.parentNode.offsetTop + this._lrCell.offsetHeight + lrOffset);
	}

	this._drawRect(3);
	this._setBorder();
};

clsRef.prototype._drawRect = function(brdSize) {
	var offsets = this.getOffsetsPx(Jedox.wss.app.browser);

	if (brdSize == undefined)
		brdSize = 5;

	// draw upper line:
	for (var i = this._edgeElems.length - 1; i >= 0; i--) {
		this._edgeElems[i][0].style.left = ''.concat(this._ulCorner.getX() + offsets[0].left, 'px');
		this._edgeElems[i][0].style.top = ''.concat(this._ulCorner.getY() + offsets[0].top, 'px');
		this._edgeElems[i][0].style.width = ''.concat(this._lrCorner.getX() - this._ulCorner.getX() + offsets[0].width, 'px');
		this._edgeElems[i][0].style.height = ''.concat(brdSize + offsets[0].height, 'px');
		this._edgeElems[i][0].style.display = 'block';

		// draw lower line:
		this._edgeElems[i][1].style.left = ''.concat(this._ulCorner.getX() + offsets[1].left, 'px');
		this._edgeElems[i][1].style.top = ''.concat(this._lrCorner.getY() + offsets[1].top, 'px');
		this._edgeElems[i][1].style.width = ''.concat(this._lrCorner.getX() - this._ulCorner.getX() + offsets[1].width, 'px');
		this._edgeElems[i][1].style.height = ''.concat(brdSize + offsets[1].height, 'px');
		this._edgeElems[i][1].style.display = 'block';

		// draw left line:
		this._edgeElems[i][2].style.left = ''.concat(this._ulCorner.getX() + offsets[2].left, 'px');
		this._edgeElems[i][2].style.top = ''.concat(this._ulCorner.getY() + offsets[2].top, 'px');
		this._edgeElems[i][2].style.width = ''.concat(brdSize + offsets[2].width, 'px');
		this._edgeElems[i][2].style.height = ''.concat(this._lrCorner.getY() - this._ulCorner.getY() + offsets[2].height, 'px');
		this._edgeElems[i][2].style.display = 'block';

		// draw right line:
		this._edgeElems[i][3].style.left = ''.concat(this._lrCorner.getX() + offsets[3].left, 'px');
		this._edgeElems[i][3].style.top = ''.concat(this._ulCorner.getY() + offsets[3].top, 'px');
		this._edgeElems[i][3].style.width = ''.concat(brdSize + offsets[3].width, 'px');
		this._edgeElems[i][3].style.height = ''.concat(this._lrCorner.getY() - this._ulCorner.getY() + offsets[3].height, 'px');
		this._edgeElems[i][3].style.display = 'block';
	}
};

clsRef.prototype.activate = function(defSelCoords) {
	this._upperLeft = defSelCoords.ul;
	this._initUpperLeft = this._upperLeft.clone();
	this._lowerRight = defSelCoords.lr;
	this._initLowerRight = this._lowerRight.clone();

	this._ulCorner = defSelCoords.ulPx; this._lrCorner = defSelCoords.lrPx;
	this._mdLRCornerPx = defSelCoords.mdLRCornerPx;
	this._lrCell = this._pane.getCellByCoords(this._lowerRight.getX(), this._lowerRight.getY());
	this.setStartCoords();

	this.registerForMouseMovement(this._environment.shared.lastCell);
};

clsRef.prototype._diffRanges = function(ulA, lrA, ulB, lrB) {
	if (ulA.equals(ulB) && lrA.equals(lrB))
		return [ ulA.getX(), ulA.getY(), lrA.getX(), lrA.getY() ];

	// Down
	if (lrB.getY() > lrA.getY())
		return [ ulA.getX(), lrA.getY() + 1, lrB.getX(), lrB.getY() ];

	// Up
	if (ulB.getY() < ulA.getY())
		return [ ulB.getX(), ulB.getY(), lrB.getX(), ulA.getY() - 1 ];

	// Right
	if (lrB.getX() > lrA.getX())
		return [ lrA.getX() + 1, ulA.getY(), lrB.getX(), lrB.getY() ];

	// Left
	if (ulA.getX() > ulB.getX())
		return [ ulB.getX(), ulB.getY(), ulA.getX() - 1, lrB.getY() ];

	return [];
};

clsRef.prototype.deactivate = function() {
	if (this._active) {
		for (var i = this._edgeElems.length - 1; i >= 0; i--)
			for (j = this._edgeElems[i].length - 1; j >= 0; j--)
				this._edgeElems[i][j].style.display = 'none';

		this._active = false;
		this._direction = Jedox.wss.grid.ScrollDirection.NONE;

		var dmActive = this._dmActive;

		if (!dmActive && this._upperLeft.equals(this._initUpperLeft) && this._lowerRight.equals(this._initLowerRight))
			return;

		this._unsetDelMarker();

		var defSel = this._environment.shared.defaultSelection;
		if (dmActive) {
			var defSelCoords = this._diffRanges(this._dmUpperLeft, this._dmLowerRight, this._initUpperLeft, this._initLowerRight);
			defSel.set(new Jedox.gen.Point(defSelCoords[0], defSelCoords[1]), new Jedox.gen.Point(defSelCoords[2], defSelCoords[3]));
		} else
			defSel.set(this._upperLeft, this._lowerRight);

		defSel.draw();

		if (dmActive)
			this._pane.clrRange([ this._dmUpperLeft.getX(), this._dmUpperLeft.getY(), this._dmLowerRight.getX(), this._dmLowerRight.getY() ]);
		else {
			this._pane.pasteRange(null,
				this._diffRanges(this._initUpperLeft, this._initLowerRight, this._upperLeft, this._lowerRight),
				Jedox.backend.ccmd(0, [ 'cfrn', [ this._initUpperLeft.getX(), this._initUpperLeft.getY(), this._initLowerRight.getX(), this._initLowerRight.getY() ] ])[0][1][0]
			);
		}
	}
}

clsRef.prototype._move = function(ev) {
	if(document.all)
		ev = window.event;

	var gridScreenCoords = this._environment.shared.gridScreenCoords;

	if (ev.clientX <= gridScreenCoords[0][0] || ev.clientX >= gridScreenCoords[1][0] ||
		ev.clientY <= gridScreenCoords[0][1] || ev.clientY >= gridScreenCoords[1][1])
		return false;

	this._environment.shared.autoScroll.checkAndScroll(ev, this._resizeOnScroll, Jedox.wss.grid.scrollType.ALL, null, this);
	this._selection.setActiveRange(this);
	try {
		this._resizeRange(ev);

		if (this._active) {
			this.draw();
			this._setMonitorCell(this._environment.shared.lastCell);
		}
	} catch (e) {}
};

clsRef.prototype._onmouseup = function(ev) {
	Jedox.wss.app.mimicOvertracking = false;

	if (this._status == Jedox.wss.range.AreaStatus.EXPANDING)
		this.afterExpanding();

	this._status = Jedox.wss.range.AreaStatus.HOVERING;
	Jedox.wss.app.mouseMovementObserver.unsubscribe(this._move);
	Jedox.wss.app.mouseUpObserver.unsubscribe(this._onmouseup);
	this._unHover(ev);

	this._resizeDirection = Jedox.wss.range.ResizeDirection.NONE;
	this.deactivate();
};

/**
 * Returns the coordinates in pixels of the given HTML element.
 * @method
 * @param {Object} element
 * @return {Array} An Array containing two points: one for the upper left and one for the lower right corner in pixels
 */
clsRef.prototype._getPixelCoords = function(el) {
	var viewportPos = this._pane.getViewportPos(),
		gridScreenCoords = this._environment.shared.gridScreenCoords,
		elLeft = el.offsetLeft - viewportPos[0][0] + gridScreenCoords[0][0],
		elTop = el.parentNode.offsetTop - viewportPos[0][1] + gridScreenCoords[0][1];

	return [
		new Jedox.gen.Point(elLeft, elTop),
		new Jedox.gen.Point(elLeft + el.offsetWidth, elTop + el.offsetHeight)
	];
};

/**
 * Returns the given cell itself and the lower right cell.
 * @method
 * @param {Object} cellHtmlElement The cell's HTML element
 * @return {Object} An object containing the HTML elements of six neighbour cells
 */
clsRef.prototype._getNeighbourCells = function(cellHtmlEl) {
	var defMaxCoords = Jedox.wss.grid.defMaxCoords,
		cellCoords = this._pane.getCoordsByCell(cellHtmlEl);

	if (cellCoords == undefined)
		return null;

	var x = cellCoords[0], y = cellCoords[1];

//	console.log('# 1 # RefCell.X: ' + cellCoords);

	// TODO: check for hidden or merged cells!
	return {
		NW: (x == 1 || y == 1) ? null : this._pane.getCellByCoords(x - 1, y - 1),
		N: (y == 1) ? null : this._pane.getCellByCoords(x, y - 1),
		NE: (x == defMaxCoords[0] || y == 1) ? null : this._pane.getCellByCoords(x + 1, y - 1),

		W: (x == 1) ? null : this._pane.getCellByCoords(x - 1, y),
		X: cellHtmlEl,
		E: (x == defMaxCoords[0]) ? null : this._pane.getCellByCoords(x + 1, y),

		SW: (x == 1 || y == defMaxCoords[1]) ? null : this._pane.getCellByCoords(x - 1, y + 1),
		S: (y == defMaxCoords[1]) ? null : this._pane.getCellByCoords(x, y + 1),
		SE: (x == defMaxCoords[0] || y == defMaxCoords[1]) ? null : this._pane.getCellByCoords(x + 1, y + 1)
	}
};

/**
 * Builds an area of coordinates based on up to four elements.
 * @method
 * @param {Object} cellArea An array with HTML elements
 * @return {Array} An array containing coordinates for each given element
 */
clsRef.prototype._getMonitorArea = function(ev, cellArea, cursorCellCoords) {
	var gridScreenCoords = this._environment.shared.gridScreenCoords,
		scrollDir = Jedox.wss.grid.ScrollDirection,
		refEl = cellArea.X, x, y, monArea = [];

	// Calculate upper-left corner.
	switch (this._direction) {
		case scrollDir.NONE:
			var refEl = (this._initUpperLeft.getX() == 1 || this._initUpperLeft.getX() != this._initLowerRight.getX()) ? cellArea.X : cellArea.W,
				refElPxCoords = this._getPixelCoords(refEl);

			x = this._initUpperLeft.getX() == 1 ? refElPxCoords[0].getX() : Math.floor(refElPxCoords[1].getX() - refEl.offsetWidth / 2);
			y = Math.floor(refElPxCoords[1].getY() - refEl.offsetHeight / 2);
			break;

		case scrollDir.UP:
		case scrollDir.DOWN:
			// Calc X
			if (this._dmActive) {
				// DEL Area
				var refElX = cellArea.X;

				if (this._initUpperLeft.getX() == 1) {
					var lastRefElX = this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initUpperLeft.getY()),
						lastRefElXPx = this._getPixelCoords(lastRefElX)[0].getX();
				} else {
					var lastRefElX = this._pane.getCellByCoords(this._initUpperLeft.getX() - 1, this._initUpperLeft.getY()),
						lastRefElXPx = Math.floor(this._getPixelCoords(lastRefElX)[1].getX() - lastRefElX.offsetWidth / 2);
				}

				x = Math.floor(this._getPixelCoords(refElX)[1].getX() - refElX.offsetWidth / 2);
				var delX = Math.floor(this._mdLRCornerPx.getX() - Math.abs(ev.clientY - this._mdLRCornerPx.getY()));

				x = (x < delX) ? x : (delX > lastRefElXPx ? delX : lastRefElXPx);
			} else if (cursorCellCoords[1] == this._initLowerRight.getY()) {
				// NONE Area
				var refElX = this._initUpperLeft.getX() != this._initLowerRight.getX() ? cellArea.X : cellArea.W;
				x = Math.floor(this._getPixelCoords(refElX)[1].getX() - refElX.offsetWidth / 2);
			} else if (cursorCellCoords[1] > this._initLowerRight.getY()) {
				// DOWN Area
				var refElXLLPx = this._getPixelCoords(this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initLowerRight.getY()));

				if (this._initUpperLeft.getX() == 1) {
					var incRefElX = this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initLowerRight.getY()),
						incRefElXPx = this._getPixelCoords(incRefElX)[0].getX();
				} else {
					var incRefElX = this._pane.getCellByCoords(this._initUpperLeft.getX() - 1, this._initLowerRight.getY()),
						incRefElXPx = Math.floor(this._getPixelCoords(incRefElX)[1].getX() - incRefElX.offsetWidth / 2);
				}

				x = refElXLLPx[0].getX() - Math.abs(ev.clientY - refElXLLPx[1].getY());
				x = (x < incRefElXPx) ? x : incRefElXPx;
			} else {
				// UP Area
				var refElXULPx = this._getPixelCoords(this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initUpperLeft.getY()));

				if (this._initUpperLeft.getX() == 1) {
					var incRefElX = this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initUpperLeft.getY()),
						incRefElXPx = this._getPixelCoords(incRefElX)[0].getX();
				} else {
					var incRefElX = this._pane.getCellByCoords(this._initUpperLeft.getX() - 1, this._initUpperLeft.getY()),
						incRefElXPx = Math.floor(this._getPixelCoords(incRefElX)[1].getX() - incRefElX.offsetWidth / 2);
				}

				x = refElXULPx[0].getX() - Math.abs(ev.clientY - refElXULPx[0].getY());
				x = (x < incRefElXPx) ? x : incRefElXPx;
			}

			// Calc Y
			var firstCol = this._initUpperLeft.getX() == 1,
				refElY = cursorCellCoords[1] < this._initLowerRight.getY() || (cursorCellCoords[1] == this._initLowerRight.getY() && this._dmActive) ? cellArea[firstCol ? 'N' : 'NW'] : cellArea[firstCol ? 'X' : 'W'];

			y = (refElY == null) ? gridScreenCoords[0][1] : Math.floor(this._getPixelCoords(refElY)[1].getY() - refElY.offsetHeight / 2);

			break;

		case scrollDir.RIGHT:
		case scrollDir.LEFT:
			// Calc X
			var refElX = (cursorCellCoords[0] < this._initLowerRight.getX()) || (cursorCellCoords[0] >= this._initLowerRight.getX() && this._dmActive) ? cellArea.W : cellArea.X;
			x = (refElX == null) ? gridScreenCoords[0][0] : Math.floor(this._getPixelCoords(refElX)[1].getX() - refElX.offsetWidth / 2);

			// Calc Y
			if (this._dmActive) {
				// DEL Area
				var refElY = cellArea.X;

				y = Math.floor(this._getPixelCoords(refElY)[1].getY() - refElY.offsetHeight / 2);
				var delY = Math.floor(this._mdLRCornerPx.getY() - Math.abs(ev.clientX - this._mdLRCornerPx.getX()));

				y = (y < delY) ? y : delY;
			} else if (cursorCellCoords[0] == this._initLowerRight.getX()) {
				// NONE Area
				var refElY = cellArea.X;
				y = Math.floor(this._getPixelCoords(refElY)[1].getY() - refElY.offsetHeight / 2);
			} else if (cursorCellCoords[0] > this._initLowerRight.getX()) {
				// RIGHT Area
				var refElYURPx = this._getPixelCoords(this._pane.getCellByCoords(this._initLowerRight.getX(), this._initUpperLeft.getY()));

				if (this._initUpperLeft.getY() == 1) {
					var incRefElY = this._pane.getCellByCoords(this._initLowerRight.getX(), this._initUpperLeft.getY()),
						incRefElYPx = this._getPixelCoords(incRefElY)[0].getY();
				} else {
					var incRefElY = this._pane.getCellByCoords(this._initLowerRight.getX(), this._initUpperLeft.getY() - 1),
						incRefElYPx = Math.floor(this._getPixelCoords(incRefElY)[1].getY() - incRefElY.offsetHeight / 2);
				}

				y = refElYURPx[0].getY() - Math.abs(ev.clientX - refElYURPx[1].getX());
				y = (y < incRefElYPx) ? y : incRefElYPx;
			} else {
				// LEFT Area
				var refElYULPx = this._getPixelCoords(this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initUpperLeft.getY()));

				if (this._initUpperLeft.getY() == 1) {
					var incRefElY = this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initUpperLeft.getY()),
						incRefElYPx = this._getPixelCoords(incRefElY)[0].getY();
				} else {
					var incRefElY = this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initUpperLeft.getY() - 1),
						incRefElYPx = Math.floor(this._getPixelCoords(incRefElY)[1].getY() - incRefElY.offsetHeight / 2);
				}

				y = refElYULPx[0].getY() - Math.abs(ev.clientX - refElYULPx[0].getX());
				y = (y < incRefElYPx) ? y : incRefElYPx;
			}

			break;
	}

	// Save upper-left corner.
	monArea.push(new Jedox.gen.Point(x, y));

	// Calculate lower-right corner.
	switch (this._direction) {
		case scrollDir.NONE:
			var refEl = cellArea.SE;
				refElPxCoords = this._getPixelCoords(refEl);

			x = Math.floor(refElPxCoords[1].getX() - refEl.offsetWidth / 2);
			y = Math.floor(refElPxCoords[1].getY() - refEl.offsetHeight / 2);
			break;

		case scrollDir.DOWN:
		case scrollDir.UP:
			// Calc Y
			var refElY = (cursorCellCoords[1] >= this._initLowerRight.getY() && !this._dmActive) ? cellArea.S : cellArea.X;
			y = (refElY == null) ? gridScreenCoords[1][1] : Math.floor(this._getPixelCoords(refElY)[1].getY() - refElY.offsetHeight / 2);

			// Calc X
			if (this._dmActive) {
				// DEL Area
				var refElX = this._pane.getCellByCoords(this._initLowerRight.getX() + 1, this._initLowerRight.getY()),
					refElLR = this._pane.getCellByCoords(this._initLowerRight.getX(), this._initLowerRight.getY()),
					refElLRPx = this._getPixelCoords(refElLR),
					refElYPx = this._mdLRCornerPx.getY() - Math.abs(this._mdLRCornerPx.getX() - ev.clientX);

				x = Math.floor(this._getPixelCoords(refElX)[1].getX() - refElX.offsetWidth / 2);
				y = ((Math.floor(refElLRPx[1].getX() - refElLR.offsetWidth / 2) <= ev.clientX && x >= ev.clientX) || y < refElYPx) ? y : refElYPx;
			} else if (cursorCellCoords[1] == this._initLowerRight.getY()) {
				// NONE Area
				var refElX = cellArea.E;
				x = Math.floor(this._getPixelCoords(refElX)[1].getX() - refElX.offsetWidth / 2);
			} else if (cursorCellCoords[1] > this._initLowerRight.getY()) {
				// DOWN Area
				var refElXLRPx = this._getPixelCoords(this._pane.getCellByCoords(this._initLowerRight.getX(), this._initLowerRight.getY())),
					incRefElX = this._pane.getCellByCoords(this._initLowerRight.getX() + 1, this._initLowerRight.getY()),
					incRefElXPx = Math.floor(this._getPixelCoords(incRefElX)[1].getX() - incRefElX.offsetWidth / 2);

				x = refElXLRPx[1].getX() + Math.abs(ev.clientY - refElXLRPx[1].getY());
				x = (x > incRefElXPx) ? x : incRefElXPx;
			} else {
				// UP Area
				var refElXURPx = this._getPixelCoords(this._pane.getCellByCoords(this._initLowerRight.getX(), this._initUpperLeft.getY())),
					incRefElX = this._pane.getCellByCoords(this._initLowerRight.getX() + 1, this._initUpperLeft.getY()),
					incRefElXPx = Math.floor(this._getPixelCoords(incRefElX)[1].getX() - incRefElX.offsetWidth / 2);

				x = refElXURPx[1].getX() + Math.abs(ev.clientY - refElXURPx[0].getY());
				x = (x > incRefElXPx) ? x : incRefElXPx;
			}

			break;

		case scrollDir.RIGHT:
		case scrollDir.LEFT:
			// Calc X
			var refElX = (cursorCellCoords[0] >= this._initLowerRight.getX() && !this._dmActive) ? cellArea.E : cellArea.X;
			x = (refElX == null) ? gridScreenCoords[1][0] : Math.floor(this._getPixelCoords(refElX)[1].getX() - refElX.offsetWidth / 2);

			// Calc Y
			if (this._dmActive) {
				// DEL Area
				var refElXPx = this._mdLRCornerPx.getX() - Math.abs(this._mdLRCornerPx.getY() - ev.clientY);
				var refElY = this._pane.getCellByCoords(this._initLowerRight.getX(), this._initLowerRight.getY() + 1);

				x = (cursorCellCoords[0] <= this._initLowerRight.getX()) ? (x < refElXPx ? x : refElXPx) : x;
				y = Math.floor(this._getPixelCoords(refElY)[1].getY() - refElY.offsetHeight / 2);
			} else if (cursorCellCoords[0] > this._initLowerRight.getX()) {
				// RIGHT Area
				var refElYLRPx = this._getPixelCoords(this._pane.getCellByCoords(this._initLowerRight.getX(), this._initLowerRight.getY())),
					incRefElY = this._pane.getCellByCoords(this._initLowerRight.getX(), this._initLowerRight.getY() + 1),
					incRefElYPx = Math.floor(this._getPixelCoords(incRefElY)[1].getY() - incRefElY.offsetHeight / 2);

				y = refElYLRPx[1].getY() + Math.abs(ev.clientX - refElYLRPx[1].getX());
				y = (y > incRefElYPx) ? y : incRefElYPx;
			} else {
				// LEFT Area
				var refElYLLPx = this._getPixelCoords(this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initLowerRight.getY())),
					incRefElY = this._pane.getCellByCoords(this._initUpperLeft.getX(), this._initLowerRight.getY() + 1),
					incRefElYPx = Math.floor(this._getPixelCoords(incRefElY)[1].getY() - incRefElY.offsetHeight / 2);

				y = refElYLLPx[1].getY() + Math.abs(ev.clientX - refElYLLPx[0].getX());
				y = (y > incRefElYPx) ? y : incRefElYPx;
			}

			break;
	}

	// Save lower-right corner.
	monArea.push(new Jedox.gen.Point(x, y));

	return monArea;
};

clsRef.prototype._resizeRange = function(ev) {
	var targetCell = document.all ? ev.srcElement : ev.target,
		cell = this._latestChangedCell,
		cursorCellCoords = Jedox.wss.mouse.getGridPos(ev),
		neighbourCells = this._getNeighbourCells(cell);

	if (neighbourCells == null)
		return false;

	var monitorArea = this._getMonitorArea(ev, neighbourCells, cursorCellCoords),
		gridScreenCoords = this._environment.shared.gridScreenCoords,
		scrollDir = Jedox.wss.grid.ScrollDirection,
		directionX = scrollDir.NONE, directionY = scrollDir.NONE,
		changeDirection = false,
		focusCell;

	function setRngEqInit(scope) {
		scope._upperLeft = scope._initUpperLeft.clone();
		scope._lowerRight = scope._initLowerRight.clone();
	}

//	console.log('# 2 # Direction before:' + this._direction);
//	console.log('# 3 # Monitor area: ' + monitorArea + ' ##### Curs x/y: ' + ev.clientX + ' / ' + ev.clientY);

	// Set scroll direction.
	if (ev.clientX > monitorArea[1].getX())
		directionX = scrollDir.RIGHT;
	else if (ev.clientX < monitorArea[0].getX())
		directionX = scrollDir.LEFT;

	if (ev.clientY > monitorArea[1].getY())
		directionY = scrollDir.DOWN;
	else if (ev.clientY < monitorArea[0].getY())
		directionY = scrollDir.UP;

	// Mouse movement inside monitor area - do nothing.
	if (directionX == scrollDir.NONE && directionY == scrollDir.NONE)
		return;
	else if (directionX != scrollDir.NONE && directionY != scrollDir.NONE)
		this._direction = (Math.abs(ev.clientX - this._mdLRCornerPx.getX()) > Math.abs(ev.clientY - this._mdLRCornerPx.getY())) ? directionX : directionY;
	else
		this._direction = (directionX == scrollDir.NONE) ? directionY : directionX;

//	console.log('# 4 # Direction after:' + this._direction);

	this._active = true;

	switch(this._direction) {
		case scrollDir.RIGHT:
			if (cursorCellCoords[0] > this._initLowerRight.getX()) {
				if (cursorCellCoords[0] > 0) {
					this._unsetDelMarker();

					this._lowerRight.setX(cursorCellCoords[0]);
					this._lowerRight.setY(this._initLowerRight.getY());
					this._upperLeft = this._initUpperLeft.clone();
					focusCell = this._pane.getCellByCoords(this._lowerRight.getX(), this._lowerRight.getY());
				}
			} else if (cursorCellCoords[0] + ((this._initUpperLeft.equals(this._initLowerRight)) ? 0 : 1) < this._initUpperLeft.getX()) {
				this._unsetDelMarker();

				this._upperLeft.setX(cursorCellCoords[0] + 1);
				this._upperLeft.setY(this._initUpperLeft.getY());
				this._lowerRight = this._initLowerRight.clone();
				focusCell = this._pane.getCellByCoords(this._upperLeft.getX(), this._upperLeft.getY());
			} else {
				// Delete area.
				setRngEqInit(this);

				var refCell;
				if (cursorCellCoords[0] > this._initLowerRight.getX()) {
					this._unsetDelMarker();
					refCell = new Jedox.gen.Point(cursorCellCoords[0], cursorCellCoords[1]);
					focusCell = this._pane.getCellByCoords(cursorCellCoords[0], cursorCellCoords[1]);
				} else {
					if (this._mdLRCornerPx.getX() - ev.clientX > this._mdLRCornerPx.getY() - ev.clientY) {
						refCell = new Jedox.gen.Point(cursorCellCoords[0] + 1, this._initUpperLeft.getY());
						focusCell = this._pane.getCellByCoords(cursorCellCoords[0] + 1, cursorCellCoords[1]);
					} else {
						refCell = new Jedox.gen.Point(this._initUpperLeft.getX(), cursorCellCoords[1] + 1);
						this._direction = scrollDir.DOWN;
						focusCell = this._pane.getCellByCoords(cursorCellCoords[0] + 1, cursorCellCoords[1] + 1);
					}

					this._setDelMarker(refCell, this._initLowerRight.clone());
				}
			}
			break;

		case scrollDir.LEFT:
			if (cursorCellCoords[0] - 1 > this._initLowerRight.getX()) {
				// Right area.
				this._unsetDelMarker();

				this._lowerRight.setX(cursorCellCoords[0] - 1);
				this._lowerRight.setY(this._initLowerRight.getY());
				this._upperLeft = this._initUpperLeft.clone();
				focusCell = this._pane.getCellByCoords(this._lowerRight.getX(), this._lowerRight.getY());
			} else if (cursorCellCoords[0] < this._initUpperLeft.getX()) {
				// Left area.
				if (cursorCellCoords[0] > 0) {
					this._unsetDelMarker();

					this._upperLeft.setX(cursorCellCoords[0]);
					this._upperLeft.setY(this._initUpperLeft.getY());
					this._lowerRight = this._initLowerRight.clone();
					focusCell = this._pane.getCellByCoords(this._upperLeft.getX(), this._upperLeft.getY());
				}
			} else {
				// Delete area.
				setRngEqInit(this);

				var refCell;
				if (this._mdLRCornerPx.getX() - ev.clientX > this._mdLRCornerPx.getY() - ev.clientY) {
					refCell = new Jedox.gen.Point(cursorCellCoords[0], this._initUpperLeft.getY());

					var refCellEl = this._pane.getCellByCoords(refCell.getX(), refCell.getY());
					if (ev.clientX > Math.floor(this._getPixelCoords(refCellEl)[1].getX() - refCellEl.offsetWidth / 2))
						refCell.setX(refCell.getX() + 1);

					focusCell = this._pane.getCellByCoords(refCell.getX(), cursorCellCoords[1]);
				} else {
					var refCellEl = this._pane.getCellByCoords(cursorCellCoords[0], cursorCellCoords[1]),
						yOffset = ev.clientY > Math.floor(this._getPixelCoords(refCellEl)[1].getY() - refCellEl.offsetHeight / 2) ? 1 : 0;

					refCell = new Jedox.gen.Point(this._initUpperLeft.getX(), cursorCellCoords[1] + yOffset);
					focusCell = this._pane.getCellByCoords(cursorCellCoords[0], cursorCellCoords[1] + yOffset);
					this._direction = scrollDir.DOWN;
				}

				this._setDelMarker(
					refCell,
					this._initLowerRight.clone()
				);
			}
			break;

		case scrollDir.DOWN:
			if (cursorCellCoords[1] > this._initLowerRight.getY()) {
				// Down area.
				if (cursorCellCoords[1] > 0) {
					this._unsetDelMarker();

					this._lowerRight.setX(this._initLowerRight.getX());
					this._lowerRight.setY(cursorCellCoords[1]);
					this._upperLeft = this._initUpperLeft.clone();
					focusCell = this._pane.getCellByCoords(this._lowerRight.getX(), this._lowerRight.getY());
				}
			} else if (cursorCellCoords[1] + 1 < this._initUpperLeft.getY()) {
				// Up area.
				this._unsetDelMarker();

				this._upperLeft.setX(this._initUpperLeft.getX());
				this._upperLeft.setY(cursorCellCoords[1] + 1);
				this._lowerRight = this._initLowerRight.clone();
				focusCell = this._pane.getCellByCoords(this._upperLeft.getX(), this._upperLeft.getY());
			} else {
				// Delete area.
				setRngEqInit(this);

				var refCell;
				if (cursorCellCoords[1] + 1 > this._initLowerRight.getY()) {
					this._unsetDelMarker();
					refCell = new Jedox.gen.Point(this._initUpperLeft.getX(), cursorCellCoords[1]);
				} else {
					if (this._mdLRCornerPx.getX() - (ev.clientX - gridScreenCoords[0][0]) > this._mdLRCornerPx.getY() - (ev.clientY - gridScreenCoords[0][1]))
						refCell = new Jedox.gen.Point(cursorCellCoords[0], this._initUpperLeft.getY());
					else
						refCell = new Jedox.gen.Point(this._initUpperLeft.getX(), cursorCellCoords[1] + 1);

					this._setDelMarker(refCell, this._initLowerRight.clone());
				}

				focusCell = this._pane.getCellByCoords(cursorCellCoords[0], refCell.getY());
			}
			break;

		case scrollDir.UP:
			if (cursorCellCoords[1] - 1 > this._initLowerRight.getY()) {
				// Down area.
				this._unsetDelMarker();

				this._lowerRight.setX(this._initLowerRight.getX());
				this._lowerRight.setY(cursorCellCoords[1] - 1);
				this._upperLeft = this._initUpperLeft.clone();
				focusCell = this._pane.getCellByCoords(this._lowerRight.getX(), this._lowerRight.getY());
			} else if (cursorCellCoords[1] < this._initUpperLeft.getY()) {
				// Up area.
				if (cursorCellCoords[1] > 0) {
					this._unsetDelMarker();

					this._upperLeft.setX(this._initUpperLeft.getX());
					this._upperLeft.setY(cursorCellCoords[1]);
					this._lowerRight = this._initLowerRight.clone();
					focusCell = this._pane.getCellByCoords(this._upperLeft.getX(), this._upperLeft.getY());
				}
			} else {
				// Delete area.
				setRngEqInit(this);

				var refCell;
				if (this._mdLRCornerPx.getX() - ev.clientX > this._mdLRCornerPx.getY() - ev.clientY) {
					var refCellEl = this._pane.getCellByCoords(cursorCellCoords[0], cursorCellCoords[1]),
						xOffset = ev.clientX > Math.floor(this._getPixelCoords(refCellEl)[1].getX() - refCellEl.offsetWidth / 2) ? 1 : 0;

					refCell = new Jedox.gen.Point(cursorCellCoords[0] + xOffset, this._initUpperLeft.getY());
					focusCell = this._pane.getCellByCoords(cursorCellCoords[0] + xOffset, refCell.getY());
					this._direction = scrollDir.RIGHT;
				} else {
					refCell = new Jedox.gen.Point(this._initUpperLeft.getX(), cursorCellCoords[1]);
					focusCell = this._pane.getCellByCoords(cursorCellCoords[0], refCell.getY());
				}

				this._setDelMarker(
					refCell,
					this._initLowerRight.clone()
				);
			}
	}

	this._latestChangedCell = focusCell;
	this.toggleCoords();
};

clsRef.prototype._getColorNumber = function() {
	return 'fill';
};

clsRef.prototype._setDelMarker = function(ul, lr) {
	var offsets = {t: 0, l: 0, w: -1, h: -1},
		refUL = this._pane.getCellByCoords(ul.getX(), ul.getY()),
		refLR = this._pane.getCellByCoords(lr.getX(), lr.getY());

	for (var i = this._delMarker.length - 1; i >= 0; i--) {
		this._delMarker[i].style.left = refUL.offsetLeft + offsets.l + 'px';
		this._delMarker[i].style.top = refUL.parentNode.offsetTop + offsets.t + 'px';
		this._delMarker[i].style.width = refLR.offsetLeft + refLR.offsetWidth - refUL.offsetLeft + offsets.w + 'px';
		this._delMarker[i].style.height = refLR.parentNode.offsetTop + refLR.offsetHeight - refUL.parentNode.offsetTop + offsets.h + 'px';
		this._delMarker[i].style.display = 'block';
	}

	this._dmUpperLeft = ul; this._dmLowerRight = lr; this._dmActive = true;
}

clsRef.prototype._unsetDelMarker = function() {
	if (this._dmActive) {
		for (var i = this._delMarker.length - 1; i >= 0; i--)
			this._delMarker[i].style.display = 'none';

		this._dmActive = false;
	}
}

clsRef = null;
