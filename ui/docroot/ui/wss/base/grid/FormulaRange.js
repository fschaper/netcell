/*
 * \brief class representing formula range
 *
 * \file FormulaRange.js
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
 * SVN: $Id: FormulaRange.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.wss.grid.FormulaRange = (function ()
{
	// private static fields
	var gpOffset = 5,
		gpOffsetEdge = [[-gpOffset, -gpOffset], [gpOffset, -gpOffset], [-gpOffset, gpOffset], [gpOffset, gpOffset]];

	// private static methods

	// class constructor
	return function (selection, startPoint, endPoint, isPassive)
	{
		Jedox.wss.grid.FormulaRange.parent.constructor.call(this, selection, startPoint, endPoint);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
		var that = this,
			panesLen = this._panes.length,
			htmlEl, htmlElCp;

		// Init presentation.

		// Cursor Fix
		var _curHotSpot;

		// Add html elements for each line in an range:
		for (var clsName = 'formularRangeBorder', i = 3; i >= 0; --i) {
			htmlEl = document.createElement('div');
			htmlEl.className = clsName;

			for (var j = panesLen - 1; j >= 0; j--) {
				htmlElCp = j > 0 ? htmlEl.cloneNode(true) : htmlEl;

				if (!isPassive) {
					Jedox.util.addEvent(htmlElCp, 'mousedown', function (ev) { that._onmousedown(ev); }, false);
					Jedox.util.addEvent(htmlElCp, 'mouseup', function (ev) { that._onmouseup(ev); }, false);
					Jedox.util.addEvent(htmlElCp, 'mousemove', function (ev) { that._onmousemove(ev); }, false);
					Jedox.util.addEvent(htmlElCp, 'mouseout', function (ev) { that._onmouseout(ev); }, false);
				}

				this._edgeElems[j][i] = htmlElCp;
				this._containers[j].appendChild(htmlElCp);
			}
		}

		// Add html elements for edge point(s):
		for (clsName = 'formularRangeEdge', i = 3; i >= 0; --i) {
			htmlEl = document.createElement('div');
			htmlEl.className = clsName;

			this._addCursor(htmlEl, i);

			for (var j = panesLen - 1; j >= 0; j--) {
				htmlElCp = j > 0 ? htmlEl.cloneNode(true) : htmlEl;
				htmlElCp.idx = i;
				htmlElCp._paneId = j;

				if (!isPassive) {
					Jedox.util.addEvent(htmlElCp, 'mousedown', function (ev) {
							if(document.all) ev = window.event;
							var elem = document.all ? ev.srcElement : ev.target;

							that._panes[elem._paneId].select();

							that._environment.shared.gridPosOffset = gpOffsetEdge[elem.idx];
							that._mouseOnEdgeDown(ev);
						}, false);
					Jedox.util.addEvent(htmlElCp, 'mouseup', function (ev) { that._environment.shared.gridPosOffset = [0, 0]; that._mouseOnEdgeUp(ev); }, false);
					Jedox.util.addEvent(htmlElCp, 'mouseover', function (ev) { that._mouseOnEdge(ev); }, false);
					Jedox.util.addEvent(htmlElCp, 'mouseout', function (ev) { that._mouseOffEdge(ev); }, false);
				}

				this._cornerElems[j][i] = htmlElCp;
				this._containers[j].appendChild(htmlElCp);
			}
		}
	}
}
)();

// FormulaRange extends Range
Jedox.util.extend(Jedox.wss.grid.FormulaRange, Jedox.wss.grid.Range);

// public static methods

// public methods
clsRef = Jedox.wss.grid.FormulaRange;

clsRef.prototype._hover = function (ev)
{
	if (document.all)
		ev = window.event;

	var elem = document.all ? ev.srcElement : ev.target;

	if (this._selection.getMode() == Jedox.wss.range.RangeMode.EDIT || this._status == Jedox.wss.range.AreaStatus.RESIZING || this._status == Jedox.wss.range.AreaStatus.DRAGGING)
		return ;

	this._setBorderBold();

	switch (elem.className)
	{
		case 'defaultRangeBorder':

			_curHotSpot = Jedox.wss.app.ctrlKeyPressed ? '7 4' : '9 9';

			if (Jedox.wss.app.browser == 'ie')
				_curHotSpot = '';

			elem.style.cursor = ''.concat('url(/ui/wss/res/img/cursors/rng_', Jedox.wss.app.ctrlKeyPressed ? 'copy' : 'move', '.cur)', _curHotSpot, ', default');

			this._environment.shared.mousePosition = 'rngBorder';

			break;


		case 'formularRangeBorder':

			elem.style.cursor = 'move';

			break;


		case 'rangeEdge':

			_curHotSpot = '9 9'

			if (Jedox.wss.app.browser == 'ie')
				_curHotSpot = '';

			elem.style.cursor = ''.concat('url(/ui/wss/res/img/cursors/md_curr', (Jedox.wss.app.ctrlKeyPressed ? '_plus' : ''), '.cur)', _curHotSpot, ', default');

			this._environment.shared.mousePosition = 'magicDot';

			break;
	}

	this._status = Jedox.wss.range.AreaStatus.HOVERING;
};

clsRef.prototype._unHover = function(ev)
{
	if (document.all)
		ev = window.event;

	var elem;

	if (this._status == Jedox.wss.range.AreaStatus.RESIZING)
		return ;

	if (ev instanceof Object)
	{
		elem = document.all ? ev.srcElement : ev.target;

		if (elem.className == 'formularRangeBorder' || elem.className == 'defaultRangeBorder')
			elem.style.cursor = 'inherit';
	}
	else
		for (var i = this._edgeElems.length - 1; i >= 0; i--)
			for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
				this._edgeElems[i][j].style.cursor = 'inherit';

	if (this._status == Jedox.wss.range.AreaStatus.RESIZING || this._status == Jedox.wss.range.AreaStatus.DRAGGING)
		return;

	this._setBorder();

	this._status = Jedox.wss.range.AreaStatus.NORMAL;
};

clsRef.prototype._refreshElement = function (scope, pane, nmcX, nmcY)
{
	if (!Jedox.wss.app.sourceSel)
		scope.formulaUpdate();

	scope.draw();
	scope._setMonitorCell(pane.getCellByCoords(nmcX, nmcY));
};

clsRef.prototype._move = function (ev)
{
	if (!this._handleElementMove)
		return;

	if (document.all)
		ev = window.event;

	if (this._doCC)
	{
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

	if (this._status == Jedox.wss.range.AreaStatus.DRAGGING)
	{
		var elemCoords = this._environment.shared.lastCellCoords;

		this._selection.moveTo(
			elemCoords[0] + this._realCoords[0].getX() - this._monitorCellCoords[0],
			elemCoords[1] + this._realCoords[0].getY() - this._monitorCellCoords[1]
		);
	}
	else if (this._status == Jedox.wss.range.AreaStatus.EXPANDING)
		this._magicDot.modifyRange(ev);
	else
		this._resizeRange(ev);

	if (!Jedox.wss.app.sourceSel)
		this.formulaUpdate();

	this.draw();
	this._setMonitorCell(this._environment.shared.lastCell);
};

clsRef.prototype.destruct = function ()
{
	Jedox.wss.app.mouseMovementObserver.unsubscribe(this._move);
	Jedox.wss.app.mouseUpObserver.unsubscribe(this._onmouseup);

	for (var i = this._edgeElems.length - 1; i >= 0; i--)
		for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
			this._edgeElems[i][j].parentNode.removeChild(this._edgeElems[i][j]);

	for (i = this._cornerElems.length - 1; i >= 0; i--)
		for (j = this._cornerElems[i].length - 1; j >= 0; j--)
			this._cornerElems[i][j].parentNode.removeChild(this._cornerElems[i][j]);
};

clsRef.prototype._drawCorners = function ()
{
	if (this.formulaToken instanceof Object && this.formulaToken.nf)
		return;

	var colors = this.getColors();
	var color = colors[(this.formulaToken instanceof Object ? this.formulaToken.id : 0) % colors.length];
	var offsets = [];

	switch (Jedox.wss.app.browser)
	{
		case 'ff':
			offsets = { ul: { x: 1, y: 1 }, lr: { x: 3, y: 4 } };
			break;

		case 'sf':
			offsets = { ul: { x: 1, y: 1 }, lr: { x: 3, y: 4 } };
			break;

		case 'ie':
			offsets = { ul: { x: 1, y: 1 }, lr: { x: 3, y: 4 } };
			break;

		case 'ch':
			offsets = { ul: { x: 1, y: 1 }, lr: { x: 3, y: 4 } };
			break;

		default:
			offsets = { ul: { x: 1, y: 1 }, lr: { x: 3, y: 4 } };
	}

	for(var xpos, ypos, i = this._cornerElems[0].length - 1, j, el; i >= 0; i--)
	{
		switch (i)
		{
			case 0: // lower right
				xpos = this._lrCorner.getX() - offsets.lr.x;
				ypos = this._lrCorner.getY() - offsets.lr.y;
				break;

			case 1: // lower left
				xpos = this._ulCorner.getX() - offsets.ul.x;
				ypos = this._lrCorner.getY() - offsets.lr.y;
				break;

			case 2: // upper right
				xpos = this._lrCorner.getX() - offsets.lr.x;
				ypos = this._ulCorner.getY() - offsets.ul.y;
				break;

			case 3: // upper left
				xpos = this._ulCorner.getX() - offsets.ul.x;
				ypos = this._ulCorner.getY() - offsets.ul.y;
				break;
		}

		for (j = this._cornerElems.length - 1; j >= 0; j--) {
			el = this._cornerElems[j][i];

			el.style.backgroundColor = color;
			el.style.left = ''.concat(xpos, 'px');
			el.style.top = ''.concat(ypos, 'px');
			el.style.display = 'block';
		}
	}
};

clsRef = null;
