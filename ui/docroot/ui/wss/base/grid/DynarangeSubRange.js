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
 * SVN: $Id: DynarangeSubRange.js 4938 2011-05-11 12:09:12Z drazenk $
 *
 */

Jedox.wss.grid.DynarangeSubRange = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (parent, selection, startPoint, endPoint, parentStartPoint, parentEndPoint)
	{
		Jedox.wss.grid.DynarangeSubRange.parent.constructor.call(this, selection, startPoint, endPoint);

		// private fields

		// private methods

		// public fields
		this._parent = parent;
		this._parentStartPoint = parentStartPoint.clone();
		this._parentEndPoint = parentEndPoint.clone();
		this._cntrlElems = [];
		this._dataCell = [];
		this._mode = Jedox.wss.range.RangeMode.EDIT;

		// privileged methods

		// constructor code
		this.parentOffset = {top: this._upperLeft.getY() - parentStartPoint.getY(), left: this._upperLeft.getX() - parentStartPoint.getX()};

		var that = this,
			panesLen = this._panes.length,
			htmlEl, htmlElCp;

		for (var i = panesLen - 1; i >= 0; i--)
			this._cntrlElems[i] = {};

		// Init presentation.

		// Add html elements for each line in an range:
		for(var clsName = 'HBSubRangeBorder', i = 3; i >= 0; --i) {
			htmlEl = document.createElement('div');
			htmlEl.className = clsName;

			for (var j = panesLen - 1; j >= 0; j--) {
				htmlElCp = j > 0 ? htmlEl.cloneNode(true) : htmlEl;

				Jedox.util.addEvent(htmlElCp, 'mousedown', function(ev){if (parent.chkRightClick.call(parent, ev)) that._onmousedown(ev);}, false);
				Jedox.util.addEvent(htmlElCp, 'mouseup', function(ev){that._onmouseup(ev); parent.save(false);}, false);
				Jedox.util.addEvent(htmlElCp, 'mousemove', function(ev){that._onmousemove(ev);}, false);
				Jedox.util.addEvent(htmlElCp, 'mouseout', function(ev){that._onmouseout(ev);}, false);

				this._edgeElems[j][i] = htmlElCp;
				this._containers[j].appendChild(htmlElCp);
			}
		}

		// Add controls.

		// Edit List button.
		var listEl = document.createElement('div'), listElCp;
		listEl.className = 'HBSubList';

		// Data cell.
		var dataCellEl = document.createElement('div'), dataCellElCp;
		dataCellEl.className = 'HBSubDataCell';

		for (j = panesLen - 1; j >= 0; j--) {
			listElCp = j > 0 ? listEl.cloneNode(true) : listEl;
			Jedox.util.addEvent(listElCp, 'mousedown', function(ev){if (parent.chkRightClick.call(parent, ev)) that._openListDlg(ev);}, false);
			Jedox.util.addEvent(listElCp, 'mouseover', function(ev){that._listBtnMouseOver(ev);}, false);

			dataCellElCp = j > 0 ? dataCellEl.cloneNode(true) : dataCellEl;

			Jedox.util.addEvent(dataCellElCp, 'mousedown', function(ev){if (parent.chkRightClick.call(parent, ev)) that._dataCellMouseDown(ev);}, false);
			Jedox.util.addEvent(dataCellElCp, 'mouseover', function(ev){that._dataCellMouseOver(ev);}, false);

			this._cntrlElems[j].list = listElCp;
			this._containers[j].appendChild(listElCp);

			this._dataCell[j] = dataCellElCp;
			this._containers[j].appendChild(dataCellElCp);
		}

		this.draw();
	}
}
)();

// DynarangeSubRange extends Range
Jedox.util.extend(Jedox.wss.grid.DynarangeSubRange, Jedox.wss.grid.Range);

// public static methods

// public methods
clsRef = Jedox.wss.grid.DynarangeSubRange;

clsRef.prototype.getOffsetsPx = function(useragent) {
	var offsets = [];



	switch(useragent) {
		case 'ff':
			offsets = [
				{left : -5, top : -6, width : 6, height : 0, listTop: 2, listLeftWhenRight: 0, listLeftWhenLeft: 1},
				{left : -5, top : 0, width : 6, height : 0},
				{left : -5, top : 0, width : 0, height : 0},
				{left : 1, top : -6, width : 0, height : 12}
			];
			break;

		case 'sf':
			offsets = [
				{left : -5, top : -6, width : 6, height : 0, listTop: 2, listLeftWhenRight: 0, listLeftWhenLeft: 1},
				{left : -5, top : 0, width : 6, height : 0},
				{left : -5, top : 0, width : 0, height : 0},
				{left : 1, top : -6, width : 0, height : 12}
			];
			break;

		case 'ie':
			offsets = [
				{left : -5, top : -6, width : 6, height : 0, listTop: 2, listLeftWhenRight: 0, listLeftWhenLeft: 1},
				{left : -5, top : 0, width : 6, height : 0},
				{left : -5, top : 0, width : 0, height : 0},
				{left : 1, top : -6, width : 0, height : 12}
			];
			break;

		case 'ch':
			offsets = [
				{left : -5, top : -6, width : 6, height : 0, listTop: 2, listLeftWhenRight: 0, listLeftWhenLeft: 1},
				{left : -5, top : 0, width : 6, height : 0},
				{left : -5, top : 0, width : 0, height : 0},
				{left : 1, top : -6, width : 0, height : 12}
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

	this._drawRect(6);
	this._setBorder();
	this._drawControls();
	this._drawDataCell();
};

clsRef.prototype._drawRect = function(brdSize) {
	var offsets = this.getOffsetsPx(Jedox.wss.app.browser);

	if (brdSize == undefined)
		brdSize = 5;

	for (var i = this._edgeElems.length - 1; i >= 0; i--) {
		// draw upper line:
		this._edgeElems[i][0].style.left = ''.concat(this._ulCorner.getX() + offsets[0].left, 'px');
		this._edgeElems[i][0].style.top = ''.concat(this._ulCorner.getY() + offsets[0].top, 'px');
		this._edgeElems[i][0].style.width = ''.concat(this._lrCorner.getX() - this._ulCorner.getX() + offsets[0].width, 'px');
		this._edgeElems[i][0].style.height = ''.concat(brdSize + offsets[0].height, 'px');
	//	this._edgeElems[i][0].style.borderBottom = '1px solid #000000';
		this._edgeElems[i][0].style.display = 'block';

		// draw lower line:
		this._edgeElems[i][1].style.left = ''.concat(this._ulCorner.getX() + offsets[1].left, 'px');
		this._edgeElems[i][1].style.top = ''.concat(this._lrCorner.getY() + offsets[1].top, 'px');
		this._edgeElems[i][1].style.width = ''.concat(this._lrCorner.getX() - this._ulCorner.getX() + offsets[1].width, 'px');
		this._edgeElems[i][1].style.height = ''.concat(brdSize + offsets[1].height, 'px');
	//	this._edgeElems[i][1].style.borderTop = '1px solid #000000';
		this._edgeElems[i][1].style.display = 'block';

		// draw left line:
		this._edgeElems[i][2].style.left = ''.concat(this._ulCorner.getX() + offsets[2].left, 'px');
		this._edgeElems[i][2].style.top = ''.concat(this._ulCorner.getY() + offsets[2].top, 'px');
		this._edgeElems[i][2].style.width = ''.concat(brdSize + offsets[2].width, 'px');
		this._edgeElems[i][2].style.height = ''.concat(this._lrCorner.getY() - this._ulCorner.getY() + offsets[2].height, 'px');
	//	this._edgeElems[i][2].style.borderRight = '1px solid #000000';
		this._edgeElems[i][2].style.display = 'block';

		// draw right line:
		this._edgeElems[i][3].style.left = ''.concat(this._lrCorner.getX() + offsets[3].left, 'px');
		this._edgeElems[i][3].style.top = ''.concat(this._ulCorner.getY() + offsets[3].top, 'px');
		this._edgeElems[i][3].style.width = ''.concat(brdSize + offsets[3].width, 'px');
		this._edgeElems[i][3].style.height = ''.concat(this._lrCorner.getY() - this._ulCorner.getY() + offsets[3].height, 'px');
	//	this._edgeElems[i][3].style.borderLeft = '1px solid #000000';
		this._edgeElems[i][3].style.display = 'block';
	}
};

clsRef.prototype.updateParentCoords = function(startPoint, endPoint) {
	this._parentStartPoint = startPoint.clone();
	this._parentEndPoint = endPoint.clone();

	if (this._parentStartPoint.getX() + this.parentOffset.left > this._parentEndPoint.getX()) {
		this._upperLeft.setX(this._parentEndPoint.getX());
		this.parentOffset.left = this._parentEndPoint.getX() - this._parentStartPoint.getX();
	} else
		this._upperLeft.setX(this._parentStartPoint.getX() + this.parentOffset.left);

	if (this._parentStartPoint.getY() + this.parentOffset.top > this._parentEndPoint.getY()) {
		this._upperLeft.setY(this._parentEndPoint.getY());
		this.parentOffset.top = this._parentEndPoint.getY() - this._parentStartPoint.getY();
	} else
		this._upperLeft.setY(this._parentStartPoint.getY() + this.parentOffset.top);

	this._lowerRight = this._upperLeft.clone();
	this.draw();
}

clsRef.prototype._drawControls = function() {
	var offsets = this.getOffsetsPx(Jedox.wss.app.browser), cntrlWidth = 19;

	for (var i = this._cntrlElems.length - 1, cntrlStyle; i >= 0; i--) {
		cntrlStyle = this._cntrlElems[i].list.style;

		if (this._parentStartPoint.getX() == this._parentEndPoint.getX())
			cntrlStyle.left = ''.concat(this._lrCorner.getX() - cntrlWidth + offsets[0].listLeftWhenRight, 'px');
		else if (this._parentEndPoint.getX() == this._lowerRight.getX())
			cntrlStyle.left = ''.concat(this._ulCorner.getX() - cntrlWidth + offsets[0].listLeftWhenLeft, 'px');
		else
			cntrlStyle.left = ''.concat(this._lrCorner.getX() + offsets[0].listLeftWhenRight, 'px');

		cntrlStyle.top = ''.concat(this._ulCorner.getY() + offsets[0].listTop, 'px');
		cntrlStyle.display = 'block';
	}
}

clsRef.prototype._drawDataCell = function() {
	var viewMode = Jedox.wss.grid.viewMode,
		offsets = (this._environment.shared.viewMode == viewMode.DESIGNER) ? {t: 0, l: 0, w: -2, h: -4} : {t: -1, l: -1, w: -7, h: -6},
		refCell = this._pane.getCellByCoords(this._upperLeft.getX(), this._upperLeft.getY());

	if (!refCell) {
		var refCellUL = this._pane.getPixelsByCoords(this._upperLeft.getX(), this._upperLeft.getY()),
			refCellWH = this._pane.getCellDims(this._upperLeft.getX(), this._upperLeft.getY());
	}

	var sLeft = (refCell ? refCell.offsetLeft : refCellUL[0]) + offsets.l + 'px',
		sTop = (refCell ? refCell.parentNode.offsetTop : refCellUL[1]) + offsets.t + 'px',

		_width = (refCell ? refCell.offsetWidth : refCellWH[0] + 1) + offsets.w,
		_height = (refCell ? refCell.offsetHeight : refCellWH[1] + 1) + offsets.h,

		// negative dimension values are not supported by all browsers - it must either be positive or empty string
		sWidth = (_width>=0)? _width + 'px' : '',
		sHeight = (_height>=0)? _height + 'px' : '',

		dataCellContent = '{'.concat(this._parent._props._gendata[0][2], '}');

	for (var i = this._dataCell.length - 1, stl; i >= 0; i--) {
		stl = this._dataCell[i].style;

		stl.left = sLeft;
		stl.top = sTop;
		stl.width = sWidth;
		stl.height = sHeight;

		Jedox.util.setText(this._dataCell[i], dataCellContent);

		if (refCell)
			Jedox.wss.style.cellTransfer(this._dataCell[i], refCell);

		stl.fontSize = '8pt';
		stl.textAlign = 'center';

		if (!stl.backgroundColor || stl.backgroundColor == '')
			stl.backgroundColor = '#FFFFFF';

		stl.display = 'block';
	}
}

clsRef.prototype.switchMode = function(mode) {

};

clsRef.prototype.setNormalMode = function() {
	var i, j;

	for (i = this._edgeElems.length - 1; i >= 0; i--)
		for (j = this._edgeElems[i].length - 1; j >= 0; j--) {
			this._edgeElems[i][j].style.zIndex = '37';
			this._edgeElems[i][j].style.display = 'none';
		}

	for (i = this._cntrlElems.length - 1; i >= 0; i--) {
		this._cntrlElems[i].list.style.zIndex = '40';
		this._cntrlElems[i].list.style.display = 'none';
	}

	for (i = this._dataCell.length - 1; i >= 0; i--) {
		this._dataCell[i].style.zIndex = '39';
		this._dataCell[i].style.display = 'block';
	}
};

clsRef.prototype.setEditMode = function() {
	var i, j;

	for (i = this._edgeElems.length - 1; i >= 0; i--)
		for (j = this._edgeElems[i].length - 1; j >= 0; j--) {
			this._edgeElems[i][j].style.zIndex = '41';
			this._edgeElems[i][j].style.display = 'block';
		}

	for (i = this._cntrlElems.length - 1; i >= 0; i--) {
		this._cntrlElems[i].list.style.zIndex = '44';
		this._cntrlElems[i].list.style.display = 'block';
	}

	for (i = this._dataCell.length - 1; i >= 0; i--)
		this._dataCell[i].style.zIndex = '43';
};

clsRef.prototype.setHiddenMode = function() {
	var i, j;

	for (i = this._edgeElems.length - 1; i >= 0; i--)
		for (j = this._edgeElems[i].length - 1; j >= 0; j--)
			this._edgeElems[i][j].style.display = 'none';

	for (i = this._cntrlElems.length - 1; i >= 0; i--)
		this._cntrlElems[i].list.style.display = 'none';

	for (i = this._dataCell.length - 1; i >= 0; i--)
		this._dataCell[i].style.display = 'none';
};


clsRef.prototype._getColorNumber = function() {
	return 'hbsub';
};

clsRef.prototype.getPosInParent = function() {
	return [this.parentOffset.left, this.parentOffset.top];
}

clsRef.prototype._openListDlg = function(ev) {
	var props = this._parent.getProps();

	if (props._gendata[0][0] == -1)
		Jedox.gen.load(Jedox.wss.app.dynJSRegistry.manageDynarange, [props]);
	else
		Jedox.palo.utils.openSubsetEditor({mode: 1, dynarange: props});

	if (document.all) {
		window.event.returnValue = false;
		window.event.cancelBubble = true;
	}else{
		ev.preventDefault();
		ev.stopPropagation();
	}
}

clsRef.prototype.setMode = function(mode){
	this._mode = mode;
}

clsRef.prototype._dataCellMouseDown = function(ev) {
	var env = this._environment.shared, gridMode = Jedox.wss.grid.GridMode, value = env.inputField.value;

	if ((env.inputMode == gridMode.EDIT || env.inputMode == gridMode.INPUT) && (value.length > 0) && (value.substr(0, 1) == '=')) {
		Jedox.wss.mouse.mimicCellMouseEvent(this._upperLeft.getX(), this._upperLeft.getY(), 'mousedown');
		return;
	}

	var rngMode = Jedox.wss.range.RangeMode;

	if (this._mode == rngMode.NONE)
		this._parent._selection.setMode(rngMode.EDIT);
}

clsRef.prototype._dataCellMouseOver = function() {
	var env = this._environment.shared,
	x = this._upperLeft.getX(), y = this._upperLeft.getY();

	env.lastCell = this._pane.getCellByCoords(x, y);
	env.lastCellCoords = [x, y];
}

clsRef.prototype._onmousedown = function(ev) {
	var that = this;

	if (document.all)
		ev = window.event;

	this._status = Jedox.wss.range.AreaStatus.DRAGGING;
	Jedox.wss.app.mimicOvertracking = (Ext.isGecko && ev.button == 0);
	this._setMonitorCell(this._environment.shared.lastCell, (document.all) ? ev.srcElement : ev.target);

	Jedox.wss.app.mouseMovementObserver.subscribe(this._move, this);
	Jedox.wss.app.mouseUpObserver.subscribe(this._onmouseup, this);

	this._selection.activeToken = this.formulaToken;
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
	this._legacyMouseUp();
	this._parent.save(false);
};

clsRef.prototype._move = function(ev) {
	if (!this._handleElementMove)
		return;

	if(document.all)
		ev = window.event;

	if (this.chkPaneSwitch(ev))
		return;

	this._environment.shared.autoScroll.checkAndScroll(ev, this._resizeOnScroll, Jedox.wss.grid.scrollType.ALL, null, this);
	this._selection.setActiveRange(this);

	if(this._status == Jedox.wss.range.AreaStatus.DRAGGING)
	{
		var elemCoords = this._environment.shared.lastCellCoords,
		newX = elemCoords[0] + this._realCoords[0].getX() - this._monitorCellCoords[0],
		newY = elemCoords[1] + this._realCoords[0].getY() - this._monitorCellCoords[1];

		if (newX >= this._parentStartPoint.getX() && newX <= this._parentEndPoint.getX() && newY >= this._parentStartPoint.getY() && newY <= this._parentEndPoint.getY()) {
			this._selection.moveTo(newX, newY);
			this.parentOffset.left = newX - this._parentStartPoint.getX();
			this.parentOffset.top = newY - this._parentStartPoint.getY();
		}
	}

	this.draw();
	this._setMonitorCell(this._environment.shared.lastCell);
};

clsRef.prototype._listBtnMouseOver = function(ev) {
	var coords = Jedox.wss.mouse.getGridPos((document.all) ? window.event : ev);

	Jedox.wss.mouse.mimicCellMouseEvent(coords[0], coords[1], "mouseover");
}

clsRef.prototype.remove = function() {
	// Remove html elements for each line in an range:
	for (var i = this._edgeElems.length - 1; i >= 0; i--)
		for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
			this._edgeElems[i][j].parentNode.removeChild(this._edgeElems[i][j]);

	// Remove Edit List button.
	for (i = this._cntrlElems.length - 1; i >= 0; i--)
		this._cntrlElems[i].list.parentNode.removeChild(this._cntrlElems[i].list);

	// Remove Data cell.
	for (i = this._dataCell.length - 1; i >= 0; i--)
		this._dataCell[i].parentNode.removeChild(this._dataCell[i]);
}

clsRef = null;
