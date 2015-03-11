/*
 * \brief class representing default range
 *
 * \file DefaultRange.js
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
 * SVN: $Id: DefaultRange.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.wss.grid.DefaultRange = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (selection, startPoint, endPoint)
	{
		Jedox.wss.grid.DefaultRange.parent.constructor.call(this, selection, startPoint, endPoint);

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
		for (var clsName = 'defaultRangeBorder', i = 3; i >= 0; --i) {
			htmlEl = document.createElement('div');
			htmlEl.className = clsName;

			for (var j = panesLen - 1; j >= 0; j--) {
				htmlElCp = j > 0 ? htmlEl.cloneNode(true) : htmlEl;

				Jedox.util.addEvent(htmlElCp, 'mousedown', function(ev){that._onmousedown(ev);}, false);
				Jedox.util.addEvent(htmlElCp, 'mouseup', function(ev){that._onmouseup(ev);}, false);
				Jedox.util.addEvent(htmlElCp, 'mousemove', function(ev){that._onmousemove(ev);}, false);
				Jedox.util.addEvent(htmlElCp, 'mouseout', function(ev){that._onmouseout(ev);}, false);

				this._edgeElems[j][i] = htmlElCp;
				this._containers[j].appendChild(htmlElCp);
			}
		}

		this._cursorField = new Jedox.wss.grid.CursorField(this._selection.getDomId(), this._sheet, this._selection);
		this._fillRange = new Jedox.wss.grid.FillSelection(this._upperLeft, this._sheet);

		// Add html elements for edge point (MagicDot).
		htmlEl = document.createElement('div');
		htmlEl.className = 'rangeEdge';

		this._addCursor(htmlEl, 0);

		var bgndElem = document.createElement('div'), bgndElemCp;
		bgndElem.className = 'rangeBackground';

		var bgndMask = document.createElement('div'), bgndMaskCp, vportSize;
		bgndMask.className = 'rangeMask customCursor';

		for (j = panesLen - 1; j >= 0; j--) {
			htmlElCp = j > 0 ? htmlEl.cloneNode(true) : htmlEl;

			Jedox.util.addEvent(htmlElCp, 'mousedown', function(ev) {
					var env = that._environment.shared, gridMode = Jedox.wss.grid.GridMode;
					if (
						(env.inputMode == Jedox.wss.grid.GridMode.INPUT || env.inputMode == Jedox.wss.grid.GridMode.EDIT) &&
						Jedox.wss.keyboard.sendInput(env.inputField, false)
					) {
						Jedox.wss.keyboard.cancelInput(true);

						try {
							Jedox.wss.app.currFormula.getEl().blur();
						} catch (e) {}
					}

					var viewportPos = that._pane.getViewportPos();

					that._fillRange.getActiveRange().activate({
						ul: that._upperLeft.clone(),
						lr: that._lowerRight.clone(),
						ulPx: that._ulCorner.clone(),
						lrPx: that._lrCorner.clone(),
						mdLRCornerPx: new Jedox.gen.Point(
	                        that._cornerElems[that._pane._id][0].offsetLeft + that._cornerElems[that._pane._id][0].offsetWidth + env.gridScreenCoords[0][0] - viewportPos[0][0],
							that._cornerElems[that._pane._id][0].offsetTop + that._cornerElems[that._pane._id][0].offsetHeight + env.gridScreenCoords[0][1] - viewportPos[0][1]
						)
					});
				}, false
			);
			Jedox.util.addEvent(htmlElCp, 'mouseover', function(ev){that._mouseOnEdge(ev);}, false);
			Jedox.util.addEvent(htmlElCp, 'mouseout', function(ev){that._mouseOffEdge(ev);}, false);

			bgndElemCp = j > 0 ? bgndElem.cloneNode(true) : bgndElem;
			bgndElemCp._paneId = j;
			Jedox.util.addEvent(bgndElemCp, 'mousemove', function(ev){Jedox.wss.mouse.rangeOverTracking(ev, that._sheet);}, false);
			Jedox.util.addEvent(bgndElemCp, 'mousedown', function(ev){Jedox.wss.mouse.mouseOnRangeDown(ev, that._sheet);}, false);

			bgndMaskCp = j > 0 ? bgndMask.cloneNode(true) : bgndMask;
			vportSize = this._panes[j].getViewportSize();
			bgndMaskCp.style.cssText = ''.concat('width:', vportSize[0] * 2, 'px;height:', vportSize[1] * 2, 'px;left:0px;top:0px;');

			this._cornerElems[j][0] = htmlElCp;
			this._containers[j].appendChild(htmlElCp);

			this._bgndElem[j] = bgndElemCp;
			this._bgndMask[j] = bgndMaskCp;
			bgndElemCp.appendChild(bgndMaskCp);
			this._containers[j].appendChild(bgndElemCp);
		}
	}
}
)();

// DefaultRange extends Range
Jedox.util.extend(Jedox.wss.grid.DefaultRange, Jedox.wss.grid.Range);

// public static methods

// public methods
clsRef = Jedox.wss.grid.DefaultRange;

clsRef.prototype.moveTo = function(x, y) {
	x = parseInt(x, 10);
	y = parseInt(y, 10);

	var width = this._lowerRight.getX() - this._upperLeft.getX(),
		height = this._lowerRight.getY() - this._upperLeft.getY(),
		defMaxCoords = Jedox.wss.grid.defMaxCoords;

	if (x < 1 || y < 1 || x + width > defMaxCoords[0] || y + height > defMaxCoords[1])
		return;

	this._upperLeft.setX(x);
	this._upperLeft.setY(y);

	this._lowerRight.setX(x + width);
	this._lowerRight.setY(y + height);

	this._environment.shared.lastRangeStartCoord = [this._upperLeft.getX(), this._upperLeft.getY()];
	this._environment.shared.lastRangeEndCoord = [this._lowerRight.getX(), this._lowerRight.getY()];

	this._activeCell.setX(x);
	this._activeCell.setY(y);

	this._selection.setActiveCell(
		null,
		x - Jedox.wss.app.firstRowNumeric + 1,
		y - Jedox.wss.app.firstColumn + 1,
		false
	);

	this._updateOffsets();
};

clsRef.prototype._updateRangeSelector = function() {
	this._selection.updateRangeSelector();
};

clsRef.prototype._mouseOnEdgeDown = function(ev) {
	if(document.all){
		ev = window.event;
	}
	var elem = document.all ? ev.srcElement : ev.target;

	switch(elem.style.cursor){

		case 'se-resize':
			this._resizeDirection = Jedox.wss.range.ResizeDirection.SOUTH_EAST;
		break;

		case 'sw-resize':
			this._resizeDirection = Jedox.wss.range.ResizeDirection.SOUTH_WEST;
		break;

		case 'ne-resize':
			this._resizeDirection = Jedox.wss.range.ResizeDirection.NORTH_EAST;
		break;

		case 'nw-resize':
			this._resizeDirection = Jedox.wss.range.ResizeDirection.NORTH_WEST;
		break;

		default:
			this._resizeDirection = Jedox.wss.range.ResizeDirection.SOUTH_EAST;

	}

	this._selection.activeToken = this.formulaToken;

	this.registerForMouseMovement(this._environment.shared.lastCell);

	this._latestChangedCell = this._lrCell;

	this.setStartCoords();
};

clsRef.prototype._legacyMouseUp = function() {
	if(this._environment.shared.inputMode == Jedox.wss.grid.GridMode.EDIT){
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.READY);
	}else if(this._environment.shared.inputMode == Jedox.wss.grid.GridMode.INPUT){
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.EDIT);
	}

	Jedox.wss.general.setCoords();
	this._selection.checkForUndoneMarkers();
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
	this._selection.setMode(Jedox.wss.range.RangeMode.NONE);

	Jedox.wss.app.mouseUpObserver.unsubscribe(this._legacyDraw);

	this._legacyMouseUp();
	this.reposBgndMask(true);

	if (this._doPaste && Jedox.wss.app.clipboard != null) {
		this._selection.paste();
		this._doPaste = false;
		this._environment.shared.copySelection.removeAll();
		Jedox.wss.app.clipboard = null;
		Jedox.wss.action.togglePaste(false);
	}

	if (Jedox.wss.app.formatPainter && this._environment.shared.inputMode == Jedox.wss.grid.GridMode.READY)
		this._selection.pasteFormat();
};

clsRef.prototype._onmousedown = function(ev) {
	var that = this;

	if (document.all)
		ev = window.event;

	this._doCC = true;
	this._status = Jedox.wss.range.AreaStatus.DRAGGING;

	Jedox.wss.app.mimicOvertracking = (Ext.isGecko && ev.button == 0);
	this._setMonitorCell(this._environment.shared.lastCell);

	Jedox.wss.app.mouseMovementObserver.subscribe(this._move, this);
	Jedox.wss.app.mouseUpObserver.subscribe(this._onmouseup, this);

	this._selection.activeToken = this.formulaToken;

	this._selection.setMode(Jedox.wss.range.RangeMode.EDIT);

	this.reposBgndMask(false);
};

clsRef.prototype._move = function(ev) {
	if (!this._handleElementMove)
		return;

	if(document.all)
		ev = window.event;

	if (this._doCC) {
		this._doCC = false;
		this._doPaste = true;
		if (ev.ctrlKey)
			this._selection.copy();
		else
			this._selection.cut();
	}

	if (this.chkPaneSwitch(ev))
		return;

	this._environment.shared.autoScroll.checkAndScroll(ev, this._resizeOnScroll, Jedox.wss.grid.scrollType.ALL, null, this);
	this._selection.setActiveRange(this);

	if(this._status == Jedox.wss.range.AreaStatus.DRAGGING) {
		var lCCrds = this._environment.shared.lastCellCoords;

		this._selection.moveTo(
			lCCrds[0] + this._realCoords[0].getX() - this._monitorCellCoords[0],
			lCCrds[1] + this._realCoords[0].getY() - this._monitorCellCoords[1]
		);

		this.selectPane();
	} else
		this._resizeRange(ev);

	this.draw();
	this._setMonitorCell(this._environment.shared.lastCell);
};

clsRef.prototype.hide = function() {
	this._switchVisibility(false);
};

clsRef.prototype.show = function() {
	this._switchVisibility(true);
};

clsRef.prototype._switchVisibility = function(rngVis) {
	var dspl = rngVis ? 'block' : 'none', i, j;

	for (i = this._edgeElems.length - 1; i >= 0; i--)
		for (j = this._edgeElems[i].length - 1; j >= 0; j--)
			this._edgeElems[i][j].style.display = dspl;

	for (i = this._cornerElems.length - 1; i >= 0; i--)
		for (j = this._cornerElems[i].length - 1; j >= 0; j--)
			this._cornerElems[i][j].style.display = dspl;

	for (i = this._bgndElem.length - 1; i >= 0; i--)
		this._bgndElem[i].style.display = dspl;

	if (rngVis)
		this._cursorField.show();
	else
		this._cursorField.hide();
}

clsRef.prototype.isVisible = function() {
	return this._edgeElems[this._pane._id][0].style.display == 'block' && this._cornerElems[this._pane._id][0].style.display == 'block';
};

clsRef.prototype.getOffsetsPx = function(useragent) {
	var offsets = [];

	switch(useragent) {
		case 'ff':
			offsets = [
				{left : 0, top : -1, width : 1, height : 0},
				{left : 0, top : -2, width : 0, height : 0},
				{left : -1, top : 0, width : 0, height : 1},
				{left : -2, top : 0, width : 0, height : 0}
			];
			break;

		case 'sf':
			offsets = [
				{left : 0, top : -1, width : 1, height : 0},
				{left : 0, top : -2, width : 0, height : 0},
				{left : -1, top : 0, width : 0, height : 1},
				{left : -2, top : 0, width : 0, height : 0}
			];
			break;

		case 'ie':
			offsets = [
				{left : 0, top : -1, width : 1, height : 0},
				{left : 0, top : -2, width : 0, height : 0},
				{left : -1, top : 0, width : 0, height : 1},
				{left : -2, top : 0, width : 0, height : 0}
			];
			break;

		case 'ch':
			offsets = [
				{left : 0, top : -1, width : 1, height : 0},
				{left : 0, top : -2, width : 0, height : 0},
				{left : -1, top : 0, width : 0, height : 1},
				{left : -2, top : 0, width : 0, height : 0}
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

	var ulOffset, lrOffset, pxCoords,
		acell = this.getActiveCell(),
		actX = this._sheet._colWidths.getElemAt(acell.getX()),
		actY = this._sheet._rowHeights.getElemAt(acell.getY());

	if (!actX || !actY) {
		actX = acell.getX() + (!actX ? 1 : 0);
		actY = acell.getY() + (!actY ? 1 : 0);

		this._selection.set(new Jedox.gen.Point(actX, actY), new Jedox.gen.Point(actX, actY));
		this._selection.draw();
		return;
	}

	var	acellEl = this._pane.getCellByCoords(acell.getX(), acell.getY());

	if (acellEl) {
		var acellCoords = this._pane.getPixelsByCoords(acell.getX(), acell.getY());

		this._activeCellEl = {
			ulX: acellCoords[0],
			ulY: acellCoords[1],
			lrX: acellCoords[0] + acellEl.offsetWidth,
			lrY: acellCoords[1] + acellEl.offsetHeight
		};
	}

	ulOffset = 1;
	lrOffset = 0;

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

	var vPanes = this._sheet.getPanesByCoords(this._realCoords[1].getX(), this._realCoords[1].getY()),
		lrPane = (vPanes.length == 1 && vPanes[0] != this._pane) ? vPanes[0] : this._pane;

	if((this._lrCell = lrPane.getCellByCoords(this._realCoords[1].getX(), this._realCoords[1].getY())) == undefined)
	{
		pxCoords = lrPane.getPixelsByCoords(this._realCoords[1].getX() + 1, this._realCoords[1].getY() + 1);

		this._lrCorner.setX(pxCoords[0]);
		this._lrCorner.setY(pxCoords[1] + lrOffset);
	}
	else
	{
		this._lrCorner.setX(this._lrCell.offsetLeft + this._lrCell.offsetWidth);
		this._lrCorner.setY(this._lrCell.parentNode.offsetTop + this._lrCell.offsetHeight + lrOffset);
	}

	this._drawRect();
	this._drawBgnd();
	this.drawActiveCell();
	this._setBorder();
	this._drawCorners();
	Jedox.wss.hb.setAllNormal();
};

clsRef.prototype.reposBgndMask = function(whether) {
	if (whether) {
		if (this._bgndElemParams && (this._bgndElemParams.w > this._pane.getViewportSize()[0] || this._bgndElemParams.h > this._pane.getViewportSize()[1]))
			this._pane.scrollObserver.subscribe(this._reposBgndMask, this);
	} else
		this._pane.scrollObserver.unsubscribe(this._reposBgndMask);
};

clsRef.prototype.destruct = function() {
	Jedox.wss.app.mouseMovementObserver.unsubscribe(this._move);
	Jedox.wss.app.mouseUpObserver.unsubscribe(this._onmouseup);

	for (var i = this._edgeElems.length - 1; i >= 0; i--)
		for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
			this._edgeElems[i][j].parentNode.removeChild(this._edgeElems[i][j]);

	for (i = this._cornerElems.length - 1; i >= 0; i--)
		for (j = this._cornerElems[i].length - 1; j >= 0; j--)
			this._cornerElems[i][j].parentNode.removeChild(this._cornerElems[i][j]);
};

clsRef.prototype._getColorNumber = function() {
	return 'default';
};

clsRef.prototype._drawCorners = function() {
	for (var i = this._cornerElems.length - 1; i >= 0; i--) {
		this._cornerElems[i][0].style.left = ''.concat(this._lrCorner.getX() - 3, 'px');
		this._cornerElems[i][0].style.top = ''.concat(this._lrCorner.getY() - 3, 'px');
		this._cornerElems[i][0].style.display = 'block';
	}
};

clsRef.prototype.getCursorField = function() {
	return this._cursorField;
};

clsRef.prototype.syncActivePane = function() {
	this._pane = this._selection._pane;

	this._cursorField.syncActivePane();
	this._fillRange.syncActivePane();
};

clsRef = null;