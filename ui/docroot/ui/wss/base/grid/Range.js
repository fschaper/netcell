/*
 * @brief ajax
 *
 * @file Group.js
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
 * SVN: $Id: Range.js 5018 2011-05-30 13:45:33Z drazenk $
 *
 */

Jedox.wss.grid.Range = (function ()
{
	// private static fields
	var _colors = [
		'#0000FF',
		'#008000',
		'#9900CC',
		'#800000',
		'#00CC33',
		'#FF6600',
		'#CC0099'
	];

	// Cursor Fix
	var _curHotSpot;

	// private static methods

	// class constructor
	return function (selection, startPoint, endPoint)
	{
		// private fields
		var _prot = this.prototype;

		// private methods

		// public fields
		this._selection = selection;

		this._panes = this._selection._panes;
		this._pane = this._selection._pane;
		this._sheet = this._pane._sheet;
		this._book = this._sheet._book;

		this._containers = selection._containers;
		this._container = selection._container;

		this._environment = selection !== null ? selection._environment : null;

		// Old Area begin.
		this._startPoint = startPoint;
		this._endPoint = endPoint;

		this._upperLeft = startPoint.clone();
		this._lowerRight = endPoint != undefined ? endPoint.clone() : startPoint.clone();
		this._lastActiveCell = startPoint.clone();
		//this._activeCell;
		//this._refActiveCell;
		//this._anchorCell;
		this._scope = this;
		//this._offsets;
		//this._state;
		//this._startCoords;
		this.formulaToken = null;

		// Old Area end.

		// Old AreaPresentation begin.

		//this._activeCellEl;
		this._edgeElems = [];
		this._cornerElems = [];
		this._bgndElem = [];
		this._bgndElemParams;
		this._bgndMask = [];
		this._bgndMaskPos = [];

		for (var i = this._panes.length - 1; i >= 0; i--) {
			this._edgeElems[i] = [];
			this._cornerElems[i] = [];
			this._bgndMaskPos[i] = [ 0, 0 ];
		}

		//this._latestChangedCell;
		this._ulCorner = new Jedox.gen.Point(1, 1);
		this._lrCorner = new Jedox.gen.Point(1, 1);
		//this._ulCell; //this._lrCell;
		this._status = Jedox.wss.range.AreaStatus.NORMAL;
		this._monitorCell = {};
		this._monitorCellCoords = [];
		this._monitorCoords = {};
		this._resizeDirection = Jedox.wss.range.ResizeDirection.NONE;
		this._handleElementMove = true;

		this._realCoords = this.getCorners();
		this._borderState = Jedox.wss.range.BorderState.UNKOWN;

		//this._cursorField; // RENAMED FROM _activeCellElement
		this._visibility = Jedox.wss.range.DisplayStatus.VISIBLE;
		this._scrollElem = false;
		this._doCC = false, _doPaste = false;

		// Old AreaPresentation end.

		// privileged methods
		this.getColors = function () {
			return _colors;
		};

		this.getParent = function() {
			return selection;
		};

		// constructor code
		this._activeCell = this._anchorCell = new Jedox.gen.Point(this._startPoint.getX(), this._startPoint.getY());
		this._offsets = [ ( this._startPoint.getX() - Jedox.wss.app.firstRowNumeric), ( this._startPoint.getY() - Jedox.wss.app.firstColumn ) ];
		this._state = Jedox.wss.range.AreaState.NORMAL;
	}
}
)();

// public methods
Jedox.wss.grid.Range.prototype =
{
	// Old Area begin.

	_updateOffsets: function() {
		this._offsets = [ ( this._upperLeft.getX() - Jedox.wss.app.firstRowNumeric), ( this._upperLeft.getY() - Jedox.wss.app.firstColumn ) ];
	},

	setToActiveCell: function() {
		this._scope.set(this._activeCell, this._activeCell);
		this._scope.draw();
	},

	getStartCoords: function() {
		return this._startCoords;
	},

	setStartCoords: function() {
		this._startCoords = [ this._upperLeft.clone(), this._lowerRight.clone() ];
	},

	afterExpanding: function() {
		// if range is unchanged, do nothing:
		if(!
			( (this._upperLeft.equals(this._startCoords[0])) &&
			(this._lowerRight.equals(this._startCoords[1])) )
		){
			Jedox.backend.wss.CopyFill(
				this._startCoords[0].getX(),
				this._startCoords[0].getY(),
				this._startCoords[1].getX(),
				this._startCoords[1].getY(),
				this._lowerRight.getX(),
				this._lowerRight.getY(),
				this._upperLeft.getX(),
				this._upperLeft.getY(),
				0
			);
		}
	},

	toggleCoords: function() {
		this.toggleCorners(this._upperLeft, this._lowerRight);
	},

	toggleCorners: function(ul, lr) {
		var tmp;

		if (ul.getX() > lr.getX()) {
			tmp = ul.getX();
			ul.setX(lr.getX());
			lr.setX(tmp);
		}

		if (ul.getY() > lr.getY()) {
			tmp = ul.getY();
			ul.setY(lr.getY());
			lr.setY(tmp);
		}
	},

	getValue: function (makeAbs)
	{
		var ntl = Jedox.wss.app.numberToLetter,
				ul = this._upperLeft,
				lr = this._lowerRight,
				pfx = makeAbs ? '$' : '';

		return pfx.concat(ntl[ul.getX()], pfx, ul.getY(), ul.equals(lr) ? '' : ':'.concat(pfx, ntl[lr.getX()], pfx, lr.getY()));
	},

	getCoords: function ()
	{
		return [ this._upperLeft.getX(), this._upperLeft.getY(), this._lowerRight.getX(), this._lowerRight.getY() ];
	},

	getLastActiveCell: function() {
		return this._lastActiveCell;
	},

	expandToCell: function(cell, setLastActiveCell) {
		var diff = new Jedox.gen.Point(
			(cell.getX() - this._lastActiveCell.getX()),
			(cell.getY() - this._lastActiveCell.getY())
		);

		if(diff.getX() > 0){
			var direction = Jedox.wss.grid.ScrollDirection.RIGHT;
			this._selection.expand(diff.getX(), direction);
		}else if(diff.getX() < 0){
			var direction = Jedox.wss.grid.ScrollDirection.LEFT;
			this._selection.expand(Math.abs(diff.getX()), direction);
		}

		if(diff.getY() > 0){
			var direction = Jedox.wss.grid.ScrollDirection.DOWN;
			this._selection.expand(diff.getY(), direction);
		}else if(diff.getY() < 0){
			var direction = Jedox.wss.grid.ScrollDirection.UP;
			this._selection.expand(Math.abs(diff.getY()), direction);
		}

		this._selection.draw();
		this.reposBgndMask(true);

		if (setLastActiveCell)
			this._lastActiveCell = cell.clone();
	},

	setActiveCell: function(cell) {
		this._activeCell = cell.clone();
		this.selectPane();
	},

	selectPane: function() {
		var vPanes = this._sheet.getPanesByCoords(this._activeCell.getX(), this._activeCell.getY());

		if (vPanes.length == 1 && vPanes[0] != this._pane)
			vPanes[0].select();
	},

	setRefActiveCell: function(cell) {
		this._refActiveCell = cell.clone();
	},

	getRefActiveCell: function() {
		return this._refActiveCell;
	},

	getCorners: function() {
		return [this._upperLeft, this._lowerRight];
	},

	getActiveCell: function() {
		return this._activeCell;
	},

	getState: function() {
		return this._state;
	},

	getOffsets: function() {
		return this._offsets;
	},

	getUpperLeft: function() {
		return this._upperLeft;
	},

	getLowerRight: function() {
		return this._lowerRight;
	},

	activate: function() {
		// TODO
	},

	deactivate: function() {
		// TODO
	},

	set: function(startPoint, endPoint) {
		this._upperLeft = new Jedox.gen.Point( parseInt(startPoint.getX(), 10), parseInt(startPoint.getY(), 10) );
		this._lowerRight = new Jedox.gen.Point( parseInt(endPoint.getX(), 10), parseInt(endPoint.getY(), 10) );
		this._lastActiveCell = new Jedox.gen.Point( parseInt(endPoint.getX(), 10), parseInt(endPoint.getY(), 10) );

		this.setActiveCell(startPoint.clone());
	},

	moveTo: function(x, y) { // Overridden only in DefaultRange.
		x = parseInt(x, 10);
		y = parseInt(y, 10);

		if (x < 1 || y < 1)
			return;

		var width = this._lowerRight.getX() - this._upperLeft.getX();
		var height = this._lowerRight.getY() - this._upperLeft.getY();

		this._upperLeft.setX(x);
		this._upperLeft.setY(y);

		this._lowerRight.setX(x + width);
		this._lowerRight.setY(y + height);

		this._environment.shared.lastRangeStartCoord = [this._upperLeft.getX(), this._upperLeft.getY()];
		this._environment.shared.lastRangeEndCoord = [this._lowerRight.getX(), this._lowerRight.getY()];

		this._updateOffsets();
	},

	setLowerRight: function(point) {
		this._lowerRight = point;
	},

	setUpperLeft: function(point) {
		this._upperLeft = point;
	},

	isFirst: function() {
		return (this._upperLeft.equals(this._activeCell));
	},

	isLast: function() {
		return (this._lowerRight.equals(this._activeCell));
	},

	next: function() {
		var actCell = this._activeCell;

		// check y border
		if (actCell.equalsX(this._lowerRight)) {
			if (actCell.equalsY(this._lowerRight)) {
				// last cell is active, select first cell
				actCell.setX(this._upperLeft.getX());
				actCell.setY(this._upperLeft.getY());
			} else {
				// last cell in row is active, select first cell in row and next in column
				actCell.setX(this._upperLeft.getX());
				actCell.setY(Jedox.wss.general.chkHiddenColRow(true, actCell.getY(), 1, true));
			}
		} else
			// select next cell in row
			actCell.setX(Jedox.wss.general.chkHiddenColRow(false, actCell.getX(), 1, true));

		var mrgInfoT = this._pane.getMergeInfo(actCell.getX(), actCell.getY());

		if (mrgInfoT)
			if (mrgInfoT[0]) {
				if (
					actCell.getX() < this._upperLeft.getX() || actCell.getY() < this._upperLeft.getY() ||
					actCell.getX() + (mrgInfoT[1] - 1) > this._lowerRight.getX() || actCell.getY() + (mrgInfoT[2] - 1) > this._lowerRight.getY()
				) {
					var newX = actCell.getX() + (mrgInfoT[1] - 1);

					actCell.setX(newX > this._lowerRight.getX() ? this._lowerRight.getX() : newX);
					this.next();
				}
			} else {
				var mrgInfoTM = this._pane.getMergeInfo(mrgInfoT[1], mrgInfoT[2]),
					newX = mrgInfoT[1] + (mrgInfoTM[1] - 1);

				actCell.setX(newX > this._lowerRight.getX() ? this._lowerRight.getX() : newX);
				this.next();
			}

		this.selectPane();
	},

	prev: function() {
		var actCell = this._activeCell;

		// check y border
		if (actCell.equalsX(this._upperLeft)) {
			if (actCell.equalsY(this._upperLeft)) {
				// last cell is active, select last cell
				actCell.setX(this._lowerRight.getX());
				actCell.setY(this._lowerRight.getY());
			} else {
				// last cell in row is active, select first cell in row and next in column
				actCell.setX(this._lowerRight.getX());
				actCell.setY(Jedox.wss.general.chkHiddenColRow(true, actCell.getY(), 1, false));
			}
		} else
			// select next cell in row
			actCell.setX(Jedox.wss.general.chkHiddenColRow(false, actCell.getX(), 1, false));

		var mrgInfoT = this._pane.getMergeInfo(actCell.getX(), actCell.getY());

		if (mrgInfoT)
			if (mrgInfoT[0]) {
				if (
					actCell.getX() < this._upperLeft.getX() || actCell.getY() < this._upperLeft.getY() ||
					actCell.getX() + (mrgInfoT[1] - 1) > this._lowerRight.getX() || actCell.getY() + (mrgInfoT[2] - 1) > this._lowerRight.getY()
				) {
					var newX = actCell.getX() - (mrgInfoT[1] - 1);

					actCell.setX(newX < this._upperLeft.getX() ? this._upperLeft.getX() : newX);
					this.prev();
				}
			} else {
				var mrgInfoTM = this._pane.getMergeInfo(mrgInfoT[1], mrgInfoT[2]),
					newX = actCell.getX() - (mrgInfoTM[1] - 1);

				actCell.setX(newX < this._upperLeft.getX() ? this._upperLeft.getX() : newX);

				if (!(actCell.getX() == mrgInfoT[1] && actCell.getY() == mrgInfoT[2] &&
						mrgInfoT[1] + (mrgInfoTM[1] - 1) <= this._lowerRight.getX() &&
						mrgInfoT[2] + (mrgInfoTM[2] - 1) <= this._lowerRight.getY()
					))
						this.prev();
			}

		this.selectPane();
	},

	nextY: function() {
		var actCell = this._activeCell;

		// check y border
		if (actCell.equalsY(this._lowerRight)) {
			if (actCell.equalsX(this._lowerRight)) {
				// last cell is active, select first cell
				actCell.setX(this._upperLeft.getX());
				actCell.setY(this._upperLeft.getY());
			} else {
				// last cell in row is active, select first cell in row and next in column
				actCell.setY(this._upperLeft.getY());
				actCell.setX(Jedox.wss.general.chkHiddenColRow(false, actCell.getX(), 1, true));
			}
		} else
			// select next cell in row
			actCell.setY(Jedox.wss.general.chkHiddenColRow(true, actCell.getY(), 1, true));

		var mrgInfoT = this._pane.getMergeInfo(actCell.getX(), actCell.getY());

		if (mrgInfoT)
			if (mrgInfoT[0]) {
				if (
					actCell.getX() < this._upperLeft.getX() || actCell.getY() < this._upperLeft.getY() ||
					actCell.getX() + (mrgInfoT[1] - 1) > this._lowerRight.getX() || actCell.getY() + (mrgInfoT[2] - 1) > this._lowerRight.getY()
				) {
					var newY = actCell.getY() + (mrgInfoT[2] - 1);

					actCell.setY(newY > this._lowerRight.getY() ? this._lowerRight.getY() : newY);
					this.nextY();
				}
			} else {
				var mrgInfoTM = this._pane.getMergeInfo(mrgInfoT[1], mrgInfoT[2]),
					newY = mrgInfoT[2] + (mrgInfoTM[2] - 1);

				actCell.setY(newY > this._lowerRight.getY() ? this._lowerRight.getY() : newY);
				this.nextY();
			}

		this.selectPane();
	},

	prevY: function() {
		var actCell = this._activeCell;

		// check y border
		if (actCell.equalsY(this._upperLeft)) {
			if (actCell.equalsX(this._upperLeft)) {
				// last cell is active, select last cell
				actCell.setX(this._lowerRight.getX());
				actCell.setY(this._lowerRight.getY());
			} else {
				// last cell in row is active, select first cell in row and next in column
				actCell.setX(Jedox.wss.general.chkHiddenColRow(false, actCell.getX(), 1, false));
				actCell.setY(this._lowerRight.getY());
			}
		} else
			// select next cell in row
			actCell.setY(Jedox.wss.general.chkHiddenColRow(true, actCell.getY(), 1, false));

		var mrgInfoT = this._pane.getMergeInfo(actCell.getX(), actCell.getY());

		if (mrgInfoT)
			if (mrgInfoT[0]) {
				if (
					actCell.getX() < this._upperLeft.getX() || actCell.getY() < this._upperLeft.getY() ||
					actCell.getX() + (mrgInfoT[1] - 1) > this._lowerRight.getX() || actCell.getY() + (mrgInfoT[2] - 1) > this._lowerRight.getY()
				) {
					var newY = actCell.getY() - (mrgInfoT[2] - 1);

					actCell.setX(newY < this._upperLeft.getY() ? this._upperLeft.getY() : newY);
					this.prevY();
				}
			} else {
				var mrgInfoTM = this._pane.getMergeInfo(mrgInfoT[1], mrgInfoT[2]),
					newY = actCell.getY() - (mrgInfoTM[2] - 1);

				actCell.setY(newY < this._upperLeft.getY() ? this._upperLeft.getY() : newY);

				if (!(actCell.getX() == mrgInfoT[1] && actCell.getY() == mrgInfoT[2] &&
					mrgInfoT[1] + (mrgInfoTM[1] - 1) <= this._lowerRight.getX() &&
					mrgInfoT[2] + (mrgInfoTM[2] - 1) <= this._lowerRight.getY()
				))
					this.prevY();
			}

		this.selectPane();
	},

	toString: function() {
		var s = '';

		s += ' active cell: ' + this._activeCell;
		s += ' upper left corner: ' + this._upperLeft.toString();
		s += ' lower right corner: ' + this._lowerRight.toString();

		return s;
	},

	formulaUpdate: function()
	{
		var env = this._environment.shared,
				currFormula = Jedox.wss.app.currFormula,
				tok, rangeVal;

		if ((tok = this.formulaToken).key == (rangeVal = this.getValue()))
			return;

		env.inputField.value = currFormula.getValue().substring(0, tok.start).concat(rangeVal, currFormula.getValue().substring(tok.end));
		currFormula.setValue(env.inputField.value);
		this._selection.lastParseRes = Jedox.wss.formula.parse(currFormula.getValue(), this._pane.getCellNFs(env.selectedCellCoords[0], env.selectedCellCoords[1]));

		Jedox.util.setSelection(Jedox.wss.app.fromFormulaField ? currFormula.el.dom : env.inputField, tok.start + rangeVal.length);

		for (var range, ranges = this._selection.getRanges(), i = ranges.length - 1; i >= 0; --i)
			(range = ranges[i]).formulaToken = this._selection.lastParseRes[range.formulaToken.idx];

		this._selection.activeToken = this.formulaToken;

		Jedox.wss.keyboard.setFieldSize();
	},

	_updateRangeSelector: function() { // Overridden only in DefaultRange.
		return;
	},

	expand: function(amount, direction, defExpand) {
		var that = this, offset,
			lastCellCoords = this._environment.shared.lastCellCoords,
			srcUl = this._upperLeft.clone(),
			srcLr = this._lowerRight.clone(),
			dstUl = this._upperLeft.clone(),
			dstLr = this._lowerRight.clone(),
			mrgInfoActCell = this._pane.getMergeInfo(this._activeCell.getX(), this._activeCell.getY());

//		console.log('expand: upperLeft=' + this._upperLeft + ' # lowerRight=' + this._lowerRight + ' # lastCellCoords=' + lastCellCoords + ' # direction=' + direction + ' # amount=' + amount + ' # defExpand=' + defExpand);

		function locMergedAreas(area, expand, ul, lr) {
			var mrgAreas = {ulX: 0, ulY: 0, lrX: 0, lrY: 0},
				updLastCell = false,
				adjDone = false;

			if (!ul || !lr) {
				ul = that._upperLeft;
				lr = that._lowerRight;
				updLastCell = true;
			}

//			console.log('================== Adjust ====================');
//			console.log('locMergedAreas: area=' + area + ' # expand=' + expand);
//			console.log('area:' + Ext.util.JSON.encode(area));

			for (var i = area.ulY; i <= area.lrY; i++)
				for (var j = area.ulX, mrgInfo, mrgInfoMa; j <= area.lrX; j++) {
					mrgInfo = that._pane.getMergeInfo(j, i);

					if (mrgInfo) {
						if (mrgInfo[0]) {
							// Master cell.
							if (expand) {
								// Expand action.
								mrgAreas.ulX = (mrgAreas.ulX == 0 || mrgAreas.ulX > j) ? j : mrgAreas.ulX;
								mrgAreas.ulY = (mrgAreas.ulY == 0 || mrgAreas.ulY > i) ? i : mrgAreas.ulY;
								mrgAreas.lrX = (mrgAreas.lrX == 0 || mrgAreas.lrX < j + mrgInfo[1] - 1) ? j + mrgInfo[1] - 1 : mrgAreas.lrX;
								mrgAreas.lrY = (mrgAreas.lrY == 0 || mrgAreas.lrY < i + mrgInfo[2] - 1) ? i + mrgInfo[2] - 1 : mrgAreas.lrY;
							} else {
								// Collapse action.
								if (j + mrgInfo[1] - 1 > area.lrX)
									mrgAreas.lrX = j - 1;

								if (i + mrgInfo[2] - 1 > area.lrY)
									mrgAreas.lrY = i - 1;
							}
						} else {
							// Slave cell.
							mrgInfoMa = that._pane.getMergeInfo(mrgInfo[1], mrgInfo[2]);

							if (expand) {
								// Expand action.
								mrgAreas.ulX = (mrgAreas.ulX == 0 || mrgAreas.ulX > mrgInfo[1]) ? mrgInfo[1] : mrgAreas.ulX;
								mrgAreas.ulY = (mrgAreas.ulY == 0 || mrgAreas.ulY > mrgInfo[2]) ? mrgInfo[2] : mrgAreas.ulY;
								mrgAreas.lrX = (mrgAreas.lrX == 0 || mrgAreas.lrX < mrgInfo[1] + mrgInfoMa[1] - 1) ? mrgInfo[1] + mrgInfoMa[1] - 1 : mrgAreas.lrX;
								mrgAreas.lrY = (mrgAreas.lrY == 0 || mrgAreas.lrY < mrgInfo[2] + mrgInfoMa[2] - 1) ? mrgInfo[2] + mrgInfoMa[2] - 1 : mrgAreas.lrY;
							} else {
								// Collapse action.
								if (mrgInfo[1] < area.ulX)
									mrgAreas.ulX = mrgInfo[1] + mrgInfoMa[1];

								if (mrgInfo[2] < area.ulY)
									mrgAreas.ulY = mrgInfo[2] + mrgInfoMa[2];
							}
						}
					}
				}

//			console.log('merg:' + Ext.util.JSON.encode(mrgAreas));

			if (mrgAreas.ulX > 0 && ((expand && mrgAreas.ulX < ul.getX()) || (!expand && mrgAreas.ulX > ul.getX()))) {
				ul.setX(mrgAreas.ulX);
				adjDone = true;
			}

			if (mrgAreas.ulY > 0 && ((expand && mrgAreas.ulY < ul.getY()) || (!expand && mrgAreas.ulY > ul.getY()))) {
				ul.setY(mrgAreas.ulY);
				adjDone = true;
			}

			if (mrgAreas.lrX > 0 && ((expand && mrgAreas.lrX > lr.getX()) || (!expand && mrgAreas.lrX < lr.getX()))) {
				lr.setX(mrgAreas.lrX);
				adjDone = true;
			}

			if (mrgAreas.lrY > 0 && ((expand && mrgAreas.lrY > lr.getY()) || (!expand && mrgAreas.lrY < lr.getY()))) {
				lr.setY(mrgAreas.lrY);
				adjDone = true;
			}

//			console.log('nrng:' + Ext.util.JSON.encode({ulX: ul.getX(), ulY: ul.getY(), lrX: lr.getX(), lrY: lr.getY()}));
//			console.log('=============================================');

			if (updLastCell)
				that._lastActiveCell = new Jedox.gen.Point(
						lr.getX() > that._activeCell.getX() ? lr.getX() : ul.getX(),
						lr.getY() > that._activeCell.getY() ? lr.getY() : ul.getY());

			if (adjDone)
				locMergedAreas({ulX: ul.getX(), ulY: ul.getY(), lrX: lr.getX(), lrY: lr.getY()}, expand, ul, lr);
		}

		function isInsideRng(cell, ul, lr) {
			return cell.getX() >= ul.getX() && cell.getY() >= ul.getY() && cell.getX() <= lr.getX() && cell.getY() <= lr.getY();
		}

		function chkRng(ul, lr, expand) {
			locMergedAreas({ulX: ul.getX(), ulY: ul.getY(), lrX: lr.getX(), lrY: lr.getY()}, expand, ul, lr);

			return isInsideRng(that._activeCell, ul, lr);
		}

		function calcDefExpand() {
			switch(direction){
				case Jedox.wss.grid.ScrollDirection.UP:

					if (that._activeCell.getY() + (mrgInfoActCell && mrgInfoActCell[0] ? mrgInfoActCell[2] - 1 : 0) < dstLr.getY())
						dstLr.setY(dstLr.getY() - ((dstLr.getY() - lastCellCoords[1] > 1) ? dstLr.getY() - lastCellCoords[1] : amount));
					else {
						if (dstLr.getY() < dstUl.getY())
							dstLr.setY(dstLr.getY() - amount);
						else
							dstUl.setY(dstUl.getY() - amount);
					}

					break;

				case Jedox.wss.grid.ScrollDirection.DOWN:

					if (that._activeCell.getY() + (mrgInfoActCell && mrgInfoActCell[0] ? mrgInfoActCell[2] - 1 : 0) < dstLr.getY()) {
						if (dstLr.getY() > dstUl.getY())
							dstLr.setY(dstLr.getY() + amount);
						else
							dstUl.setY(dstUl.getY() - amount);
					} else {
						if (dstLr.getY() < dstUl.getY())
							dstLr.setY(dstLr.getY() + amount);
						else
							dstUl.setY(dstUl.getY() + ((lastCellCoords[1] - dstUl.getY() > 1) ? lastCellCoords[1] - dstUl.getY() : amount));
					}

					break;

				case Jedox.wss.grid.ScrollDirection.LEFT:

					if (that._activeCell.getX() + (mrgInfoActCell && mrgInfoActCell[0] ? mrgInfoActCell[1] - 1 : 0) < dstLr.getX())
						dstLr.setX(dstLr.getX() - ((dstLr.getX() - lastCellCoords[0] > 1) ? dstLr.getX() - lastCellCoords[0] : amount));
					else {
						if (dstLr.getX() < dstUl.getX())
							dstLr.setX(dstLr.getX() - amount);
						else
							dstUl.setX(dstUl.getX() - amount);
					}

					break;

				case Jedox.wss.grid.ScrollDirection.RIGHT:

					if (that._activeCell.getX() + (mrgInfoActCell && mrgInfoActCell[0] ? mrgInfoActCell[1] - 1 : 0) < dstLr.getX()) {
						if (dstUl.getX() < dstLr.getX())
							dstLr.setX(dstLr.getX() + amount);
					} else {
						if (dstUl.getX() > dstLr.getX())
							dstLr.setX(dstLr.getX() - amount);
						else
							dstUl.setX(dstUl.getX() + ((lastCellCoords[0] - dstUl.getX() > 1) ? lastCellCoords[0] - dstUl.getX() : amount));
					}

					break;

				default:
					throw new Error('Invalid direction: ' + direction);
			}
		}

		function calcKeyExpand() {
			switch(direction){
				case Jedox.wss.grid.ScrollDirection.UP:

					if (dstLr.getY() > that._activeCell.getY() + (mrgInfoActCell && mrgInfoActCell[0] ? mrgInfoActCell[2] - 1 : 0)) {
						var dstCopyUl = dstUl.clone(), dstCopyLr = dstLr.clone();
						dstCopyLr.setY(dstCopyLr.getY() - amount);

						if (!chkRng(dstCopyUl, dstCopyLr, false))
							dstUl.setY(dstUl.getY() - amount);
						else
							dstLr.setY(dstLr.getY() - amount);
					} else
						dstUl.setY(dstUl.getY() - amount);

					break;

				case Jedox.wss.grid.ScrollDirection.DOWN:

					if (dstUl.getY() < that._activeCell.getY()) {
						var dstCopyUl = dstUl.clone(), dstCopyLr = dstLr.clone();
						dstCopyUl.setY(dstCopyUl.getY() + amount);

						if (!chkRng(dstCopyUl, dstCopyLr, false))
							dstLr.setY(dstLr.getY() + amount);
						else
							dstUl.setY(dstUl.getY() + amount);
					} else
						dstLr.setY(dstLr.getY() + amount);

					break;

				case Jedox.wss.grid.ScrollDirection.LEFT:

					if (dstLr.getX() > that._activeCell.getX() + (mrgInfoActCell && mrgInfoActCell[0] ? mrgInfoActCell[1] - 1 : 0)) {
						var dstCopyUl = dstUl.clone(), dstCopyLr = dstLr.clone();
						dstCopyLr.setX(dstCopyLr.getX() - amount);

						if (!chkRng(dstCopyUl, dstCopyLr, false))
							dstUl.setX(dstUl.getX() - amount);
						else
							dstLr.setX(dstLr.getX() - amount);
					} else
						dstUl.setX(dstUl.getX() - amount);

					break;

				case Jedox.wss.grid.ScrollDirection.RIGHT:

					if (dstUl.getX() < that._activeCell.getX()) {
						var dstCopyUl = dstUl.clone(), dstCopyLr = dstLr.clone();
						dstCopyUl.setX(dstCopyUl.getX() + amount);

						if (!chkRng(dstCopyUl, dstCopyLr, false))
							dstLr.setX(dstLr.getX() + amount);
						else
							dstUl.setX(dstUl.getX() + amount);
					} else
						dstLr.setX(dstLr.getX() + amount);

					break;

				default:
					throw new Error('Invalid direction: ' + direction);
			}
		}

		function calcPlainRng() {
			dstUl.setX(lastCellCoords[0] < that._activeCell.getX() ? lastCellCoords[0] : that._activeCell.getX());
			dstUl.setY(lastCellCoords[1] < that._activeCell.getY() ? lastCellCoords[1] : that._activeCell.getY());
			dstLr.setX(lastCellCoords[0] > that._activeCell.getX() ? lastCellCoords[0] : that._activeCell.getX());
			dstLr.setY(lastCellCoords[1] > that._activeCell.getY() ? lastCellCoords[1] : that._activeCell.getY());
		}

		function constrainToGrid(ul, lr) {
			var defMaxCoords = Jedox.wss.grid.defMaxCoords;

			if (ul.getX() < 1) ul.setX(1);
			if (ul.getY() < 1) ul.setY(1);

			if (lr.getX() > defMaxCoords[0]) lr.setX(defMaxCoords[0]);
			if (lr.getY() > defMaxCoords[1]) lr.setY(defMaxCoords[1]);
		}

		if (defExpand)
			calcDefExpand();
		else
			calcKeyExpand();

		this.toggleCorners(dstUl, dstLr);

		if (defExpand)
			calcPlainRng();

//		console.log('expand: dstUl=' + dstUl + ' # dstLr=' + dstLr);

		var expanded = dstLr.getX() - dstUl.getX() > srcLr.getX() - srcUl.getX() || dstLr.getY() - dstUl.getY() > srcLr.getY() - srcUl.getY();

		if (defExpand && expanded && isInsideRng(new Jedox.gen.Point(lastCellCoords[0], lastCellCoords[1]), this._upperLeft, this._lowerRight))
			return;

		constrainToGrid(dstUl, dstLr);
		this._upperLeft = dstUl.clone();
		this._lowerRight = dstLr.clone();

		locMergedAreas({ulX: this._upperLeft.getX(), ulY: this._upperLeft.getY(), lrX: this._lowerRight.getX(), lrY: this._lowerRight.getY()}, expanded || defExpand);

		this._environment.shared.lastRangeStartCoord = [this._upperLeft.getX(), this._upperLeft.getY()];
		this._environment.shared.lastRangeEndCoord = [this._lowerRight.getX(), this._lowerRight.getY()];

		this._updateOffsets();
		this._updateRangeSelector();
	},

	setAnchorCell: function(cell) {
		this._anchorCell = cell;
	},

	getAnchorCell: function() {
		return this._anchorCell;
	},

	// Old Area end.

	// Old AreaPresentation begin.

	getLastChangedCell: function() {
		return this._latestChangedCell;
	},

	setLastChangedCell: function(cell) {
		this._latestChangedCell = cell;
	},

	setVisibility: function(visibility) {
		this._visibility = visibility;
	},

	getStatus: function() {
		return this._status;
	},

	getCornersPx: function() {
		return [this._ulCorner, this._lrCorner];
	},

	hideBorders: function() {
		for (var i = this._edgeElems.length - 1; i >= 0; i--)
			for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
				this._edgeElems[i][j].style.display = 'none';

		for (i = this._cornerElems.length - 1; i >= 0; i--)
			for (j = this._cornerElems[i].length - 1; j >= 0; j--)
				this._cornerElems[i][j].style.display = 'none';
	},

	_addCursor: function(el, id)
	{
		switch(id)
		{
			case 0:
				el.style.cursor = 'se-resize';
				break;

			case 1:
				el.style.cursor = 'sw-resize';
				break;

			case 2:
				el.style.cursor = 'ne-resize';
				break;

			case 3:
				el.style.cursor = 'nw-resize';
				break;
		}
	},

	_mouseOnEdge: function(ev) {
		this._hover(ev);
	},

	_legacyDraw: function() {
		this._environment.shared.lastRangeStartCoord = [(this._realCoords[0]).getX(), (this._realCoords[0]).getY()];
		this._environment.shared.lastRangeEndCoord = [(this._realCoords[1]).getX(), (this._realCoords[1]).getY()];

		this._selection.checkForUndoneMarkers();
	},

	_mouseOffEdge: function(ev) {
		if(this._status != Jedox.wss.range.AreaStatus.RESIZING){
			this._unHover(ev);
		}
	},

	_mouseOnEdgeDown: function(ev) { // Overridden only in DefaultRange.

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

		Jedox.wss.app.mimicOvertracking = (Ext.isGecko && ev.button == 0);
		this._selection.activeToken = this.formulaToken;

		this.registerForMouseMovement(this._environment.shared.lastCell);
	},

	registerForMouseMovement: function(cell) {
		this._realCoords = this.getCorners();

		this._status = Jedox.wss.range.AreaStatus.RESIZING;
		this._setMonitorCell(cell);

		// set opposite corner cell to active cell:
		var tmp = this._pane.getCoordsByCell(this._monitorCell);

		if (tmp == undefined)
			for (var i = this._panes.length - 1; i >= 0; i--) {
				tmp = this._panes[i].getCoordsByCell(this._monitorCell);

				if (tmp instanceof Array)
					break;
			}

		var x = (tmp[0] == this._realCoords[0].getX()) ? this._realCoords[1].getX() : this._realCoords[0].getX();
		var y = (tmp[1] == this._realCoords[0].getY()) ? this._realCoords[1].getY() : this._realCoords[0].getY();

		this.setActiveCell(new Jedox.gen.Point(x, y));
		this._latestChangedCell = this._lrCell;

		this._selection.setMode(Jedox.wss.range.RangeMode.EDIT);

		Jedox.wss.app.mouseMovementObserver.subscribe(this._move, this);
		Jedox.wss.app.mouseUpObserver.subscribe(this._onmouseup, this);
	},

	_mouseOnEdgeUp: function(ev) {
		Jedox.wss.app.mimicOvertracking = false;
		this._legacyMouseUp();

		this._status = Jedox.wss.range.AreaStatus.HOVERING;
		Jedox.wss.app.mouseMovementObserver.unsubscribe(this._move);
		Jedox.wss.app.mouseUpObserver.unsubscribe(this._onmouseup);
		this._unHover(ev);
		this._selection.setMode(Jedox.wss.range.RangeMode.NONE);
	},

	_onmouseout: function(ev) {
		this._unHover(ev);
	},

	_onmousemove: function (ev) {
		this._hover(ev);
	},

	_hover: function(ev) { // Overridden only in FormulaRange.
		if(document.all){
			ev = window.event;
		}

		var elem = document.all ? ev.srcElement : ev.target;
		if( (this._selection.getMode() == Jedox.wss.range.RangeMode.EDIT) || (this._status == Jedox.wss.range.AreaStatus.RESIZING) || (this._status == Jedox.wss.range.AreaStatus.DRAGGING) ){
			return ;
		}

		switch(elem.className) {
			case 'defaultRangeBorder':
				if (Jedox.wss.app.ctrlKeyPressed) _curHotSpot = '7 4'; else _curHotSpot = '9 9';
				if (Jedox.wss.app.browser=='ie') _curHotSpot = '';
				elem.style.cursor = ''.concat('url(/ui/wss/res/img/cursors/rng_', Jedox.wss.app.ctrlKeyPressed ? 'copy' : 'move', '.cur)',_curHotSpot,', default');
				this._environment.shared.mousePosition = 'rngBorder';
				break;
			case 'formularRangeBorder':
				elem.style.cursor = 'move';
				break;
			case 'rangeEdge':
			_curHotSpot = '9 9'
			if (Jedox.wss.app.browser=='ie') _curHotSpot = '';
				elem.style.cursor = ''.concat('url(/ui/wss/res/img/cursors/md_curr', (Jedox.wss.app.ctrlKeyPressed ? '_plus' : ''), '.cur)',_curHotSpot,', default');
				this._environment.shared.mousePosition = 'magicDot';
		}

		this._status = Jedox.wss.range.AreaStatus.HOVERING;
	},

	_unHover: function(ev) { // Overridden only in FormulaRange.
		if (document.all)
			ev = window.event;

		var elem;

		if (this._status == Jedox.wss.range.AreaStatus.RESIZING)
			return ;

		if (typeof(ev) === 'object') {
			elem = document.all ? ev.srcElement : ev.target;

			if (elem.className == 'formularRangeBorder' || elem.className == 'defaultRangeBorder')
				elem.style.cursor = 'inherit';
		} else
			for (var i = this._edgeElems.length - 1; i >= 0; i--)
				for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
					this._edgeElems[i][j].style.cursor = 'inherit';

		if (this._status == Jedox.wss.range.AreaStatus.RESIZING || this._status == Jedox.wss.range.AreaStatus.DRAGGING)
			return ;

		this._status = Jedox.wss.range.AreaStatus.NORMAL;
	},

	_legacyMouseUp: function() { // Overridden only in DefaultRange.
		var gridMode = Jedox.wss.grid.GridMode,
			sourceSel = Jedox.wss.app.sourceSel;

		if (!sourceSel) {
			switch (this._environment.shared.inputMode) {
				case gridMode.INPUT:
					Jedox.wss.general.setInputMode(gridMode.EDIT);
					break;

				case gridMode.POINT:
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputMode);
					break;
			}
		} else {
			var selRange = Ext.getCmp('selRange'),
				sheetName = this._book.getSheetSelector().getActiveSheetName(true),
				rng = sheetName.concat('!', this.getValue(true));

			sourceSel.rng = rng;
			selRange.setValue(rng);
			selRange.selectText();
			selRange.focus();

			Jedox.wss.general.setInputMode(gridMode.DIALOG);
		}
	},

	_onmouseup: function(ev) // Overridden only in DefaultRange.
	{
		Jedox.wss.app.mimicOvertracking = false;

		if (this._status == Jedox.wss.range.AreaStatus.EXPANDING)
			this.afterExpanding();

		this._status = Jedox.wss.range.AreaStatus.HOVERING;
		Jedox.wss.app.mouseMovementObserver.unsubscribe(this._move);
		Jedox.wss.app.mouseUpObserver.unsubscribe(this._onmouseup);
		this._unHover(ev);

		this._resizeDirection = Jedox.wss.range.ResizeDirection.NONE;
		this._selection.setMode(Jedox.wss.range.RangeMode.NONE);
		this._legacyMouseUp();

/*
		if (!Jedox.wss.app.sourceSel) // Comment to change point border after mouse is up.
		{
			if(this._state == Jedox.wss.range.AreaState.NEW)
			{
				this._state = Jedox.wss.range.AreaState.NORMAL;
				this._borderState = Jedox.wss.range.BorderState.UNKOWN;
				this._setBorder();
			}
			else
				this._selection.setState(Jedox.wss.range.AreaState.NORMAL);
		}
*/

		this.reposBgndMask(true);

		if (this._doPaste && Jedox.wss.app.clipboard != null) {
			this._selection.paste();
			this._doPaste = false;
			this._environment.shared.copySelection.removeAll();
			Jedox.wss.app.clipboard = null;
			Jedox.wss.action.togglePaste(false);
		}
	},

	_onmousedown: function(ev) // Overridden only in DefaultRange.
	{
		var that = this;

		if (document.all)
			ev = window.event;

		this._status = Jedox.wss.range.AreaStatus.DRAGGING;
		Jedox.wss.app.mimicOvertracking = (Ext.isGecko && ev.button == 0);
		this._setMonitorCell(this._environment.shared.lastCell);

		Jedox.wss.app.mouseMovementObserver.subscribe(this._move, this);
		Jedox.wss.app.mouseUpObserver.subscribe(this._onmouseup, this);

		this._selection.activeToken = this.formulaToken;

		this._selection.setMode(Jedox.wss.range.RangeMode.EDIT);

		this.reposBgndMask(false);
	},

	_setMonitorCell: function(cell, el) {
		if (!cell) return;

		var pane = this._pane,
			monitorCoords = [], monitorCell, xOffset = 0, yOffset = 0,
			pxOffset = (el == undefined || el.className != 'HBSubRangeBorder') ? 0 : 2,
			cellCoords = pane.getCoordsByCell(cell);

		if (!cellCoords) {
			for (var i = this._panes.length - 1; i >= 0; i--) {
				if (i == this._pane._id)
					continue;

				if ((cellCoords = this._panes[i].getCoordsByCell(cell))) {
					this._panes[i].select();
					pane = this._panes[i];
					break;
				}
			}
		}

		if (!cellCoords) return;

		try {
			if (Jedox.util.offsetTop(cell.parentNode) < Jedox.util.offsetTop(this._edgeElems[pane._id][0]))
				yOffset = 1;
			else if (Jedox.util.offsetTop(cell.parentNode) >= Jedox.util.offsetTop(this._edgeElems[pane._id][1]) - pxOffset)
				yOffset = -1;

			if (Jedox.util.offsetLeft(cell) < Jedox.util.offsetLeft(this._edgeElems[pane._id][2]))
				xOffset = 1;
			else if(Jedox.util.offsetLeft(cell) >= Jedox.util.offsetLeft(this._edgeElems[pane._id][3]) - pxOffset)
				xOffset = -1;


			if (this._status != Jedox.wss.range.AreaStatus.DRAGGING && this._realCoords[0].equals(this._realCoords[1])) {
				// single cell selected
				this._monitorCell = cell;
				this._monitorCellCoords = [cellCoords[0], cellCoords[1]];
			} else {
				var xIncOffset = cellCoords[0] + xOffset < 1 ? 1 : cellCoords[0] + xOffset,
					yIncOffset = cellCoords[1] + yOffset < 1 ? 1 : cellCoords[1] + yOffset;

				this._monitorCell = this._selection.getCell(xIncOffset, yIncOffset);
				this._monitorCellCoords = [xIncOffset, yIncOffset];

				this._environment.shared.lastCell = this._monitorCell;
				this._environment.shared.lastCellCoords = this._monitorCellCoords;
			}

			this._monitorCoords[0] = new Jedox.gen.Point(Jedox.util.offsetLeft(this._monitorCell), Jedox.util.offsetTop(this._monitorCell.parentNode));
			this._monitorCoords[1] = new Jedox.gen.Point(Jedox.util.offsetLeft(this._monitorCell) + this._monitorCell.offsetWidth, Jedox.util.offsetTop(this._monitorCell.parentNode) + this._monitorCell.offsetHeight);
		} catch(e) {}
	},

	_refreshElement: function(scope, pane, nmcX, nmcY) { // Overridden only in FormulaRange.
		scope.draw();
		scope._setMonitorCell(pane.getCellByCoords(nmcX, nmcY));
	},

	_resizeOnScroll: function(pane, type, direction, firstVisCoord, lastVisCoord, scrollTimeout) {
		if (direction == undefined)
			return;

		var scope = this;
		var lastCellCoords = this._environment.shared.lastCellCoords;
		var rangeStatus = Jedox.wss.range.AreaStatus;
		var scrollType = Jedox.wss.grid.scrollType;
		var scrollDir = Jedox.wss.grid.ScrollDirection;
		var defMaxCoords = Jedox.wss.grid.defMaxCoords;
		var rangeCoords = this.getCorners();
		var nmcX = lastCellCoords[0];
		var nmcY = lastCellCoords[1];

		function scrollLeft() {
			if (scope._status == rangeStatus.RESIZING) {
				var nmcXDelta = Math.abs(nmcX - firstVisCoord - ((firstVisCoord == 1) ? 0 : 1));
				nmcX = nmcX - nmcXDelta;

				if (nmcX > rangeCoords[0].getX()) {
					scope._selection.expand(nmcXDelta * -1, scrollDir.RIGHT);
				} else {
					scope._selection.expand(nmcXDelta, scrollDir.LEFT);
				}
			} else if (scope._status == rangeStatus.DRAGGING) {
				nmcX = (firstVisCoord > 1) ? firstVisCoord + 1 : firstVisCoord;
				scope._selection.moveTo(nmcX, scope._realCoords[0].getY());
			}

			scope._refreshElement(scope, pane, nmcX, nmcY);
		}

		function scrollRight() {
			if (scope._status == rangeStatus.RESIZING) {
				var nmcXDelta = Math.abs(lastVisCoord - nmcX - ((lastVisCoord == defMaxCoords[0]) ? 0 : 1));
				nmcX = nmcX + nmcXDelta;

				if (nmcX < rangeCoords[1].getX()) {
					scope._selection.expand(nmcXDelta * -1, scrollDir.LEFT);
				} else {
					scope._selection.expand(nmcXDelta, scrollDir.RIGHT);
				}
			} else if (scope._status == rangeStatus.DRAGGING) {
				nmcX = (lastVisCoord < defMaxCoords[0]) ? lastVisCoord - 1 : lastVisCoord;
				scope._selection.moveTo(nmcX - (scope._realCoords[1].getX() - scope._realCoords[0].getX()), scope._realCoords[0].getY());
			}

			scope._refreshElement(scope, pane, nmcX, nmcY);
		}

		function scrollUp() {
			if (scope._status == rangeStatus.RESIZING) {
				var nmcYDelta = Math.abs(nmcY - firstVisCoord - ((firstVisCoord == 1) ? 0 : 1));
				nmcY = nmcY - nmcYDelta;

				if (nmcY > rangeCoords[0].getY()) {
					scope._selection.expand(nmcYDelta * -1, scrollDir.DOWN);
				} else {
					scope._selection.expand(nmcYDelta, scrollDir.UP);
				}
			} else if (scope._status == rangeStatus.DRAGGING) {
				nmcY = (firstVisCoord > 1) ? firstVisCoord + 1 : firstVisCoord;
				scope._selection.moveTo(scope._realCoords[0].getX(), nmcY);
			}

			scope._refreshElement(scope, pane, nmcX, nmcY);
		}

		function scrollDown() {
			if (scope._status == rangeStatus.RESIZING) {
				var nmcYDelta = Math.abs(lastVisCoord - nmcY - ((lastVisCoord == defMaxCoords[1]) ? 0 : 1));
				nmcY = nmcY + nmcYDelta;

				if (nmcY < rangeCoords[1].getY()) {
					scope._selection.expand(nmcYDelta * -1, scrollDir.UP);
				} else {
					scope._selection.expand(nmcYDelta, scrollDir.DOWN);
				}
			} else if (scope._status == rangeStatus.DRAGGING) {
				nmcY = (lastVisCoord < defMaxCoords[1]) ? lastVisCoord - 1 : lastVisCoord;
				scope._selection.moveTo(scope._realCoords[0].getX(), nmcY - (scope._realCoords[1].getY() - scope._realCoords[0].getY()));
			}

			scope._refreshElement(scope, pane, nmcX, nmcY);
		}

		if (type == scrollType.HORIZ) {
			if (direction == Jedox.wss.grid.horScrollDir.RIGHT) {
				if (nmcX < lastVisCoord - 1)
					scrollRight();

				if (lastVisCoord == defMaxCoords[0])
					this._environment.shared.autoScroll.scrollElem = setTimeout(scrollRight, scrollTimeout);
			} else {
				if (nmcX > firstVisCoord + 1)
					scrollLeft();

				if (firstVisCoord == 1)
					this._environment.shared.autoScroll.scrollElem = setTimeout(scrollLeft, scrollTimeout);
			}
		} else {
			if (direction == Jedox.wss.grid.vertScrollDir.DOWN) {
				if (nmcY < lastVisCoord - 1)
					scrollDown();

				if (lastVisCoord == defMaxCoords[1])
					this._environment.shared.autoScroll.scrollElem = setTimeout(scrollDown, scrollTimeout);
			} else {
				if (nmcY > firstVisCoord + 1)
					scrollUp();

				if (firstVisCoord == 1)
					this._environment.shared.autoScroll.scrollElem = setTimeout(scrollUp, scrollTimeout);
			}
		}
	},

	_move: function(ev) // Overridden in DefaultRange and FormulaRange.
	{
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

		if(this._status == Jedox.wss.range.AreaStatus.DRAGGING)
		{
			var elemCoords = this._environment.shared.lastCellCoords;

			this._selection.moveTo(
				elemCoords[0] + this._realCoords[0].getX() - this._monitorCellCoords[0],
				elemCoords[1] + this._realCoords[0].getY() - this._monitorCellCoords[1]
			);
		} else
			this._resizeRange(ev);

		this.draw();
		this._setMonitorCell(this._environment.shared.lastCell);
	},

	_resizeRange: function(ev) {
		var row = this._environment.shared.lastCellCoords[0] - this._monitorCellCoords[0],
			column = this._environment.shared.lastCellCoords[1] - this._monitorCellCoords[1];

		var diff = new Jedox.gen.Point(row, column);

		if(diff.getX() > 0){
			this._selection.expand(diff.getX(), Jedox.wss.grid.ScrollDirection.RIGHT, true);
		}else if(diff.getX() < 0){
			this._selection.expand(Math.abs(diff.getX()), Jedox.wss.grid.ScrollDirection.LEFT, true);
		}

		if(diff.getY() > 0){
			this._selection.expand(diff.getY(), Jedox.wss.grid.ScrollDirection.DOWN, true);
		}else if(diff.getY() < 0){
			this._selection.expand(Math.abs(diff.getY()), Jedox.wss.grid.ScrollDirection.UP, true);
		}
	},

	setState: function(state) {
		this._state = state;
	},

	hide: function() { // Overridden only in DefaultRange.
		for (var i = this._edgeElems.length - 1; i >= 0; i--)
			for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
				this._edgeElems[i][j].style.display = 'none';

		for (i = this._cornerElems.length - 1; i >= 0; i--)
			for (j = this._cornerElems[i].length - 1; j >= 0; j--)
				this._cornerElems[i][j].style.display = 'none';
	},

	hideElement: function(elementNumber) {
		for (var i = this._edgeElems.length - 1; i >= 0; i--)
			this._edgeElems[i][elementNumber].style.display = 'none';
	},

	showElement: function(elementNumber) {
		for (var i = this._edgeElems.length - 1; i >= 0; i--)
			this._edgeElems[i][elementNumber].style.display = 'block';
	},

	getOffsetsPx: function(useragent) { // Overridden only in DefaultRange.
		var offsets = [];

		switch(useragent){
			case 'ff':
				offsets = [
					{left : 1, top : -1, width : -1, height : 2},
					{left : 1, top : -4, width : -1, height : 0},
					{left : -1, top : 1, width : 0, height : -2},
					{left : -3, top : 1, width : 0, height : -2}
				];
				break;

			case 'sf':
				offsets = [
					{left : 1, top : -1, width : -1, height : 2},
					{left : 1, top : -4, width : -1, height : 0},
					{left : -1, top : 1, width : 0, height : -2},
					{left : -3, top : 1, width : 0, height : -2}
				];
				break;

			case 'ie':
				offsets = [
					{left : 1, top : -1, width : -1, height : 2},
					{left : 1, top : -4, width : -1, height : 0},
					{left : -1, top : 1, width : 0, height : -2},
					{left : -3, top : 1, width : 0, height : -2}
				];
				break;

			case 'ch':
				offsets = [
					{left : 1, top : -1, width : -1, height : 2},
					{left : 1, top : -4, width : -1, height : 0},
					{left : -1, top : 1, width : 0, height : -2},
					{left : -3, top : 1, width : 0, height : -2}
				];
				break;

			default:
				offsets = [
					{left : 1, top : -1, width : -1, height : 2},
					{left : 1, top : -4, width : -1, height : 0},
					{left : -1, top : 1, width : 0, height : -2},
					{left : -3, top : 1, width : 0, height : -2}
				];
				console.warn("Unkown user agent: ", useragent);
		}

		return offsets;
	},

	drawActiveCell: function() {
		this._cursorField.draw(this._activeCellEl, this.getActiveCell());
	},

	draw: function() { // Overridden only in DefaultRange.
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

		this._drawRect();

		if(this._state == Jedox.wss.range.AreaState.NORMAL && (this._status == Jedox.wss.range.AreaStatus.RESIZING || this._status == Jedox.wss.range.AreaStatus.DRAGGING))
			this._setBorderBold();
		else
			this._setBorder();

		this._drawCorners();
	},

	_drawRect: function(brdSize) // TODO: Check this line: Jedox.wss.app.mouseUpObserver.subscribe(this._legacyDraw);
	{
		var offsets = this.getOffsetsPx(Jedox.wss.app.browser);

		if (brdSize == undefined)
			brdSize = 5;

		for (var i = this._edgeElems.length - 1; i >= 0; i--) {
			// draw upper line:
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
	},

	_drawBgnd: function()
	{
		this._bgndElemParams = {
			 l: this._ulCorner.getX() + 4,
			 t: this._ulCorner.getY() + 4,
			 w: this._lrCorner.getX() - this._ulCorner.getX() - 6,
			 h: this._lrCorner.getY() - this._ulCorner.getY()  - 6
		};

		for (var i = this._bgndElem.length - 1; i >= 0; i--) {
			this._bgndElem[i].style.left =  this._bgndElemParams.l +  'px';
			this._bgndElem[i].style.width = this._bgndElemParams.w + 'px';
			this._bgndElem[i].style.top = this._bgndElemParams.t + 'px';
			this._bgndElem[i].style.height = this._bgndElemParams.h + 'px';
			this._bgndElem[i].style.display = 'block';
		}

		if(this._status != Jedox.wss.range.AreaStatus.DRAGGING)
			this._legacyDraw();
		else
			Jedox.wss.app.mouseUpObserver.subscribe(this._legacyDraw, this);

		for (var i = this._bgndMask.length - 1; i >= 0; i--) {
			this._reposBgndMask(this._panes[i], 0);
			this._reposBgndMask(this._panes[i], 1);
		}
	},

	reposBgndMask: function(whether) { // Overridden only in DefaultRange.
		return;
	},

	// Special handling for range masks to avoid very large layers with transparency
	_reposBgndMask: function(pane, type)
	{
		if (type == 0)
			var attr = 'left', range_beg = this._bgndElemParams.l, range_end = range_beg + this._bgndElemParams.w;
		else if (type == 1)
			var attr = 'top', range_beg = this._bgndElemParams.t, range_end = range_beg + this._bgndElemParams.h;
		else
			return;

		var vport_size = pane.getViewportSize()[type], vport_beg = pane.getViewportPos()[0][type], vport_end = vport_beg + vport_size;

		//console.log('t:', type, ';v1:', vport_beg, ';v2:', vport_end);

		// are range and viewport intersecting
		if (range_beg > vport_end || vport_beg > range_end)
			return;

		var isect_beg = range_beg < vport_beg ? vport_beg : range_beg, isect_end = range_end < vport_end ? range_end : vport_end;
		var mask_beg = range_beg + this._bgndMaskPos[pane._id][type], mask_end = mask_beg + vport_size * 2, vport_half = parseInt(vport_size / 2);

		//console.log('t:', type, ';r1:', range_beg, ';r2:', range_end, ';i1:', isect_beg, ';i2:', isect_end, ';m1:', mask_beg, ';m2:', mask_end);

		// is the mask covering the whole intersection
		if (isect_beg >= mask_beg + vport_half && isect_end <= mask_end - vport_half)
			return;

		if (isect_beg == range_beg)
			this._bgndMaskPos[pane._id][type] = -vport_half;
		else if (isect_end == range_end)
			this._bgndMaskPos[pane._id][type] = parseInt(range_end - range_beg - vport_size - vport_half);
		else
			this._bgndMaskPos[pane._id][type] = isect_beg - range_beg - vport_half;

		var attrVal = ''.concat(this._bgndMaskPos[pane._id][type], 'px');

		this._bgndMask[pane._id].style[attr] = attrVal;
	},

	destruct: function() { // Overridden in DefaultRange.
		Jedox.wss.app.mouseMovementObserver.unsubscribe(this._move);
		Jedox.wss.app.mouseUpObserver.unsubscribe(this._onmouseup);

		for (var i = this._edgeElems.length - 1; i >= 0; i--)
			for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
				this._edgeElems[i][j].parentNode.removeChild(this._edgeElems[i][j]);
	},

	_getColorNumber: function () // overridden in DefaultRange
	{
		return (this.formulaToken instanceof Object ? this.formulaToken.id : 0) % this.getColors().length;
	},

	_setBorder: function()
	{
		if(this._borderState == Jedox.wss.range.BorderState.NORMAL)
			return;

		if(this._state == Jedox.wss.range.AreaState.NEW)
		{
			for (var i = this._edgeElems.length - 1; i >= 0; i--) {
				this._edgeElems[i][0].style.backgroundImage = 'url(/ui/wss/res/img/borders/new_horizontal_up.gif)';
				this._edgeElems[i][0].style.backgroundRepeat = 'repeat-x';
				this._edgeElems[i][0].style.backgroundPosition = '0px 2px';

				this._edgeElems[i][1].style.backgroundImage = 'url(/ui/wss/res/img/borders/new_horizontal_up.gif)';
				this._edgeElems[i][1].style.backgroundRepeat = 'repeat-x';
				this._edgeElems[i][1].style.backgroundPosition = '0px 1px';

				this._edgeElems[i][2].style.backgroundImage = 'url(/ui/wss/res/img/borders/new_vertical_left.gif)';
				this._edgeElems[i][2].style.backgroundRepeat = 'repeat-y';
				this._edgeElems[i][2].style.backgroundPosition = '2px 0px';

				this._edgeElems[i][3].style.backgroundImage = 'url(/ui/wss/res/img/borders/new_vertical_left.gif)';
				this._edgeElems[i][3].style.backgroundRepeat = 'repeat-y';
				this._edgeElems[i][3].style.backgroundPosition = '1px 0px';
			}
		}
		else
		{
			var colorNumber = this._getColorNumber();

			for (var i = this._edgeElems.length - 1; i >= 0; i--) {
				this._edgeElems[i][0].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_horizontal_normal.gif)');
				this._edgeElems[i][0].style.backgroundPosition = '0px 0px';

				this._edgeElems[i][1].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_horizontal_normal.gif)');
				this._edgeElems[i][1].style.backgroundPosition = '0px 0px';

				this._edgeElems[i][2].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_vertical_normal.gif)');
				this._edgeElems[i][2].style.backgroundPosition = '0px 0px';

				this._edgeElems[i][3].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_vertical_normal.gif)');
				this._edgeElems[i][3].style.backgroundPosition = '0px 0px';
			}
		}

		this._borderState = Jedox.wss.range.BorderState.NORMAL;
	},

	_setBorderBold: function()
	{
		if(this._borderState == Jedox.wss.range.BorderState.BOLD || this._state == Jedox.wss.range.AreaState.NEW)
			return;

		var colorNumber = this._getColorNumber();

		for (var i = this._edgeElems.length - 1; i >= 0; i--) {
			this._edgeElems[i][0].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_horizontal_down.gif)');
			this._edgeElems[i][0].style.backgroundPosition = '0px 0px';

			this._edgeElems[i][1].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_horizontal_up.gif)');
			this._edgeElems[i][1].style.backgroundPosition = '0px 0px';

			this._edgeElems[i][2].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_vertical_right.gif)');
			this._edgeElems[i][2].style.backgroundPosition = '0px 0px';

			this._edgeElems[i][3].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_vertical_left.gif)');
			this._edgeElems[i][3].style.backgroundPosition = '0px 0px';
		}

		this._borderState = Jedox.wss.range.BorderState.BOLD;
	},

	_drawCorners: function() { // Overridden in DefaultRange and FormulaRange.
		return;
	},

	setCursor: function(el, cur) {
		if (cur=='rng_copy') _curHotSpot = '7 4';
		else if (cur=='rng_move') _curHotSpot = '9 9';
		else if (cur=='sand_clock') _curHotSpot = '10 10';
		else if (cur=='arrow_sclock') _curHotSpot = '10 10';
		else if (cur=='hand') _curHotSpot = '5 0';
		else if (cur=='md_curr') _curHotSpot = '8 8';
		else if (cur=='md_curr_plus') _curHotSpot = '8 8';
		else if (cur=='move') _curHotSpot = '9 9';
		else _curHotSpot = '';
		if (Jedox.wss.app.browser=='ie') _curHotSpot = '';
		switch(el) {
			case 'rngBorder':
				for (var i = this._edgeElems.length - 1; i >= 0; i--)
					for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
						this._edgeElems[i][j].style.cursor = ''.concat('url(/ui/wss/res/img/cursors/', cur, '.cur)',_curHotSpot,', default');
				break;

			case 'magicDot':
				for (var i = this._cornerElems.length - 1; i >= 0; i--)
					this._cornerElems[i][0].style.cursor = ''.concat('url(/ui/wss/res/img/cursors/', cur, '.cur)',_curHotSpot,', default');
		}
	},

	repaint: function()
	{
		var colorNumber = this._getColorNumber(),
			color = (this.getColors())[colorNumber], i;

		if (this._state == Jedox.wss.range.AreaState.NEW) {
			for (i = this._edgeElems.length - 1; i >= 0; i--) {
				this._edgeElems[i][0].style.backgroundImage = 'url(/ui/wss/res/img/borders/new_horizontal_up.gif)';
				this._edgeElems[i][0].style.backgroundRepeat = 'repeat-x';
				this._edgeElems[i][0].style.backgroundPosition = '0px 2px';

				this._edgeElems[i][1].style.backgroundImage = 'url(/ui/wss/res/img/borders/new_horizontal_up.gif)';
				this._edgeElems[i][1].style.backgroundRepeat = 'repeat-x';
				this._edgeElems[i][1].style.backgroundPosition = '0px 1px';

				this._edgeElems[i][2].style.backgroundImage = 'url(/ui/wss/res/img/borders/new_vertical_left.gif)';
				this._edgeElems[i][2].style.backgroundRepeat = 'repeat-y';
				this._edgeElems[i][2].style.backgroundPosition = '2px 0px';

				this._edgeElems[i][3].style.backgroundImage = 'url(/ui/wss/res/img/borders/new_vertical_left.gif)';
				this._edgeElems[i][3].style.backgroundRepeat = 'repeat-y';
				this._edgeElems[i][3].style.backgroundPosition = '1px 0px';
			}
		} else {
			for (i = this._edgeElems.length - 1; i >= 0; i--) {
				this._edgeElems[i][0].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_horizontal_normal.gif)');
				this._edgeElems[i][0].style.backgroundPosition = '0px 0px';

				this._edgeElems[i][1].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_horizontal_normal.gif)');
				this._edgeElems[i][1].style.backgroundPosition = '0px 0px';

				this._edgeElems[i][2].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_vertical_normal.gif)');
				this._edgeElems[i][3].style.backgroundPosition = '0px 0px';

				this._edgeElems[i][3].style.backgroundImage = 'url(/ui/wss/res/img/borders/'.concat(colorNumber, '_vertical_normal.gif)');
				this._edgeElems[i][3].style.backgroundPosition = '0px 0px';
			}
		}

		for (i = this._cornerElems.length - 1; i >= 0; i--)
			for (j = this._cornerElems[i].length - 1; j >= 0; j--)
				this._cornerElems[i][j].style.backgroundColor = color;
	},

	getContainer: function()
	{
		return this._container;
	},

	getEnvironment: function()
	{
		return this._environment;
	},

	// Old AreaPresentation end.

	syncActivePane: function() {
		this._pane = this._selection._pane;
	},

	chkPaneSwitch: function(ev) {
		var lC = this._environment.shared.lastCell,
			lCCrds = this._environment.shared.lastCellCoords;

//			console.log('-------');
//			console.log('lastcell = ' + lCCrds);
//			console.log('monitor  = ' + this._monitorCellCoords);

		if (!this._sheet._autoScroll.getActivePane().getCellByCoords(lCCrds[0], lCCrds[1])) {
//			debugger;

			for (var i = 0, rPanes = this._sheet.getPanesByCoords(lCCrds[0], lCCrds[1]), rPLen = rPanes.length; i < rPLen; i++)
				if (!rPanes[i].hasFullSize() && (lC = rPanes[i].getCellByCoords(lCCrds[0], lCCrds[1]))) {
//					console.log('================ SWITCH ==============');

					this._sheet._autoScroll.setActivePane(rPanes[i]);
					Jedox.wss.mouse.calcGridScreenCoords(ev, document.all ? ev.srcElement : ev.target, null, rPanes[i]);

					var diff = {x: lCCrds[0] - this._monitorCellCoords[0], y: lCCrds[1] - this._monitorCellCoords[1]}, scrollTo;

					if (diff.x > 1)
						scrollTo = {x: this._monitorCellCoords[0] + 1, y: this._monitorCellCoords[1]};
					else if (diff.y > 1)
						scrollTo = {x: this._monitorCellCoords[0], y: this._monitorCellCoords[1] + 1};

					if (scrollTo) {
						this._handleElementMove = false;
						rPanes[i].scrollTo([this, function() {this._handleElementMove = true;}], scrollTo.x, scrollTo.y, true, false);
					}

					return true
				}
		}

		return false;
	}
}
