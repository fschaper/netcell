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
 * SVN: $Id: DynarangeRange.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.wss.grid.DynarangeRange = (function ()
{
	// private static fields
	var constants = {
			DIRECTION: {
				VERT: 0,
				HORIZ: 1
			}
		},
		gpOffset = 7,
		gpOffsetBorder = [[0, gpOffset], [0, -gpOffset], [gpOffset, 0], [-gpOffset, 0]],
		gpOffsetEdge = [[-gpOffset, -gpOffset], [gpOffset, -gpOffset], [-gpOffset, gpOffset], [gpOffset, gpOffset]];

	// private static methods

	// class constructor
	return function (selection, startPoint, endPoint, props)
	{
		Jedox.wss.grid.DynarangeRange.parent.constructor.call(this, selection, startPoint, endPoint);

		// private fields

		// private methods

		// public fields
		this._mode = Jedox.wss.range.RangeMode.EDIT;
		this._props = props;
		this._propsPrev = (props.wselid == undefined) ? null : Ext.ux.clone(props);
		this._cntrlElems = [];

		//this._expDir = constants.DIRECTION[expDir];
		this._expDir = props.dir;

		// privileged methods
		this.getConstant = function(name) {
			return constants[name];
		};

		// constructor code

		var that = this,
			panesLen = this._panes.length,
			htmlEl, htmlElCp;

		for (var i = panesLen - 1; i >= 0; i--)
			this._cntrlElems[i] = {};

		// Init presentation.

		// Add html elements for each line in an range:
		for(var clsName = 'HBRangeBorder', i = 3; i >= 0; --i) {
			htmlEl = document.createElement('div');
			htmlEl.className = clsName;

			for (var j = panesLen - 1; j >= 0; j--) {
				htmlElCp = j > 0 ? htmlEl.cloneNode(true) : htmlEl;
				htmlElCp.idx = i;

				Jedox.util.addEvent(htmlElCp, 'mousedown', function(ev) {
						if(document.all) ev = window.event;
						var elem = document.all ? ev.srcElement : ev.target;

						if (that.chkRightClick.call(that, ev)) {
							that._environment.shared.gridPosOffset = gpOffsetBorder[elem.idx];
							that._onmousedown(ev);
						}
					}, false);

				Jedox.util.addEvent(htmlElCp, 'mouseup', function(ev) {that._environment.shared.gridPosOffset = [0, 0]; that._onmouseup(ev);}, false);
				Jedox.util.addEvent(htmlElCp, 'mousemove', function(ev) {that._onmousemove(ev);}, false);
				Jedox.util.addEvent(htmlElCp, 'mouseout', function(ev) {that._onmouseout(ev);}, false);

				this._edgeElems[j][i] = htmlElCp;
				this._containers[j].appendChild(htmlElCp);
			}
		}

		// Add html elements for edge point(s):
		for (var clsName = 'HBRangeEdge', i = 3; i >= 0; --i) {
			htmlEl = document.createElement('div');
			htmlEl.className = clsName;

			this._addCursor(htmlEl, i);

			for (var j = panesLen - 1; j >= 0; j--) {
				htmlElCp = j > 0 ? htmlEl.cloneNode(true) : htmlEl;
				htmlElCp.idx = i;

				Jedox.util.addEvent(htmlElCp, 'mousedown', function(ev) {
						if(document.all) ev = window.event;
						var elem = document.all ? ev.srcElement : ev.target;

						if (that.chkRightClick.call(that, ev)) {
							that._environment.shared.gridPosOffset = gpOffsetEdge[elem.idx];
							that._mouseOnEdgeDown(ev);
						}
					}, false);

				Jedox.util.addEvent(htmlElCp, 'mouseup', function(ev) {that._environment.shared.gridPosOffset = [0, 0]; that._mouseOnEdgeUp(ev, true);}, false);
				Jedox.util.addEvent(htmlElCp, 'mouseover', function(ev) {that._mouseOnEdge(ev);}, false);
				Jedox.util.addEvent(htmlElCp, 'mouseout', function(ev) {that._mouseOffEdge(ev);}, false);

				this._cornerElems[j][i] = htmlElCp;
				this._containers[j].appendChild(htmlElCp);
			}
		}

		// Add controls.

		// Properties button.
		var propsEl = document.createElement('div'), propsElCp;
		propsEl.className = 'HBProps';

		// Direction arrow.
		var dirArrowEl = document.createElement('div'), dirArrowElCp;
		dirArrowEl.id = 'dirArrowCont';
		dirArrowEl.className = 'HBDirArrCont';

		for (j = panesLen - 1; j >= 0; j--) {
			propsElCp = j > 0 ? propsEl.cloneNode(true) : propsEl;

			//Jedox.util.addEvent(propsElCp, 'mousedown', function(ev){that._propsMouseDown(ev);}, false);
			Jedox.util.addEvent(propsElCp, 'mousedown', function(ev){if (that.chkRightClick.call(that, ev)) that._openPropDlg(ev);}, false);
			Jedox.util.addEvent(propsElCp, 'mouseover', function(ev){that._propsBtnMouseOver(ev);}, false);

			dirArrowElCp = j > 0 ? dirArrowEl.cloneNode(true) : dirArrowEl;

			Jedox.util.addEvent(dirArrowElCp, 'dblclick', function(ev){that._dirSwitchMouseDown(true);}, false);
			Jedox.util.addEvent(dirArrowElCp, 'mousedown', function(ev){
					if (that.chkRightClick.call(that, ev)) {
						that._environment.shared.gridPosOffset = gpOffsetBorder[that._expDir == constants.DIRECTION.VERT ? 2 : 0];
						that._dirArrowMouseDown(ev);
					}
				}, false);
			Jedox.util.addEvent(dirArrowElCp, 'mouseup', function(ev) {that._environment.shared.gridPosOffset = [0, 0];}, false);
			Jedox.util.addEvent(dirArrowElCp, 'mousemove', function(ev) {that._onmousemove(ev);}, false);
			Jedox.util.addEvent(dirArrowElCp, 'mouseout', function(ev) {that._onmouseout(ev);}, false);

			this._cntrlElems[j].props = propsElCp;
			this._containers[j].appendChild(propsElCp);

			this._cntrlElems[j].dirArrow = dirArrowElCp;
			this._containers[j].appendChild(dirArrowElCp);

			this._cntrlElems[j].arrCanvas = new jsGraphics(dirArrowElCp);
		}

		// Add Subrange.
		var selCellCoords = (props.dcell == undefined) ? this._environment.shared.selectedCellCoords : [props.src[0] + props.dcell[0], props.src[1] + props.dcell[1]];
		var dataCellPos = new Jedox.gen.Point(selCellCoords[0], selCellCoords[1]);
		this._subrange = new Jedox.wss.grid.DynarangeSubSelection(dataCellPos, dataCellPos, that._sheet, that, startPoint, endPoint);

		this.draw(false);

		if (props.wselid == undefined)
			this.save();
	};
}
)();

// DynarangeRange extends Range
Jedox.util.extend(Jedox.wss.grid.DynarangeRange, Jedox.wss.grid.Range);

clsRef = Jedox.wss.grid.DynarangeRange;

// public static methods

// public methods

clsRef.prototype.chkRightClick = function(ev) {
	// Uncomment to enable dragging with right mouse button pressed in Firefox 3.
	//return true;

	if (document.all)
		ev = window.event;

	if (ev.button == 2 || (Ext.isMac && ev.button == 0 && Jedox.wss.app.ctrlKeyPressed)) {
		this._selection.setMode(Jedox.wss.range.RangeMode.EDIT);
		this.showCntxMenu(ev);
		return false;
	} else
		return true;
};

clsRef.prototype.showCntxMenu = function(ev) {
	var that = this, cntxMenu = new Ext.menu.Menu({
		id: 'HBContextMenu',
		cls: 'default-format-window',
		enableScrolling: false,
		listeners: {
			hide: function(menu){
				menu.destroy();
			}
		},
		items: [
			{
				text: 'Switch Direction'.localize(), iconCls: 'hb_switch_dir',
				handler: function(item, ev) {
					that._dirSwitchMouseDown.call(that, true);
				}
			},
			{text: 'Delete'.localize(), iconCls: 'icon_delete', handler: function() {Jedox.wss.hb.delDynarange(that._props.id);}},
			'-',
			{
				text: "Properties".localize().concat('...'), iconCls: 'hb_properties',
				handler: function(item, ev) {
					that._openPropDlg.call(that, ev.browserEvent);
				}
			}
		]
	});

	cntxMenu.showAt([ev.clientX, ev.clientY]);
};

clsRef.prototype.getOffsetsPx = function(useragent) {
	var offsets = [];

	switch(useragent) {
		case 'ff':
			offsets = [
				{left : 0, top : -6, width : 0, height : 0, propsTop: 2, propsLeft: 3, dirArrTop: -6, dirArrHeight: 8},
				{left : 1, top : -2, width : 0, height : 0},
				{left : -6, top : 0, width : 0, height : 0, dirArrLeft: -6, dirArrWidth: 8},
				{left : -1, top : 0, width : 0, height : 0}
			];
			break;

		case 'sf':
			offsets = [
				{left : 0, top : -6, width : 0, height : 0, propsTop: 2, propsLeft: 3, dirArrTop: -6, dirArrHeight: 8},
				{left : 1, top : -2, width : 0, height : 0},
				{left : -6, top : 0, width : 0, height : 0, dirArrLeft: -6, dirArrWidth: 8},
				{left : -1, top : 0, width : 0, height : 0}
			];
			break;

		case 'ie':
			offsets = [
				{left : 0, top : -6, width : 0, height : 0, propsTop: 2, propsLeft: 3, dirArrTop: -6, dirArrHeight: 8},
				{left : 1, top : -2, width : 0, height : 0},
				{left : -6, top : 0, width : 0, height : 0, dirArrLeft: -6, dirArrWidth: 8},
				{left : -1, top : 0, width : 0, height : 0}
			];
			break;

		case 'ch':
			offsets = [
				{left : 0, top : -6, width : 0, height : 0, propsTop: 2, propsLeft: 3, dirArrTop: -6, dirArrHeight: 8},
				{left : 1, top : -2, width : 0, height : 0},
				{left : -6, top : 0, width : 0, height : 0, dirArrLeft: -6, dirArrWidth: 8},
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

clsRef.prototype.draw = function(setHdr) {
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
	this._drawCorners();
	this._drawControls();
	this._subrange.getActiveRange().updateParentCoords(this._upperLeft, this._lowerRight);

	if (setHdr == undefined) {
		this._selection._selectionChanged = true;
		this._selection.checkForUndoneMarkers();
	}
};

clsRef.prototype._drawCorners = function() {
	// Note: r4609 contains commented version of this functions. Not sure if it'll be used in future.

	var offsets = [];

	switch(Jedox.wss.app.browser) {
		case 'ff':
			offsets = [{xpos : 0, ypos : -1},{xpos : 6, ypos : -1},{xpos : 0, ypos : 6},{xpos : 6, ypos : 6}];
			break;
		case 'sf':
			offsets = [{xpos : 0, ypos : -1},{xpos : 6, ypos : -1},{xpos : 0, ypos : 6},{xpos : 6, ypos : 6}];
			break;
		case 'ie':
			offsets = [{xpos : 0, ypos : -1},{xpos : 6, ypos : -1},{xpos : 0, ypos : 6},{xpos : 6, ypos : 6}];
			break;
		case 'ch':
			offsets = [{xpos : 0, ypos : -1},{xpos : 6, ypos : -1},{xpos : 0, ypos : 6},{xpos : 6, ypos : 6}];
			break;
		default:
			offsets = [{xpos : 0, ypos : -1},{xpos : 6, ypos : -1},{xpos : 0, ypos : 6},{xpos : 6, ypos : 6}];
			console.warn("Unkown user agent: ", useragent);
	}

	for(var xpos, ypos, i = this._cornerElems[0].length - 1; i >= 0; i--) {
		switch(i) {
			case 0: // bottom right
				xpos = this._lrCorner.getX() + offsets[0].xpos;
				ypos = this._lrCorner.getY() + offsets[0].ypos;
				break;

			case 1: // bottom left
				xpos = this._ulCorner.getX() - offsets[1].xpos;
				ypos = this._lrCorner.getY() + offsets[1].ypos;
				break;

			case 2: // top right
				xpos = this._lrCorner.getX() + offsets[2].xpos;
				ypos = this._ulCorner.getY() - offsets[2].ypos;
				break;

			case 3: // top left
				xpos = this._ulCorner.getX() - offsets[3].xpos;
				ypos = this._ulCorner.getY() - offsets[3].ypos;
				break;
		}

		for (var j = this._cornerElems.length - 1; j >= 0; j--) {
			this._cornerElems[j][i].style.left = ''.concat(xpos, 'px');
			this._cornerElems[j][i].style.top = ''.concat(ypos, 'px');
			this._cornerElems[j][i].style.display = 'block';
		}
	}
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
		this._edgeElems[i][0].style.borderBottom = '2px solid #000000';
		this._edgeElems[i][0].style.display = 'block';

		// draw lower line:
		this._edgeElems[i][1].style.left = ''.concat(this._ulCorner.getX() + offsets[1].left, 'px');
		this._edgeElems[i][1].style.top = ''.concat(this._lrCorner.getY() + offsets[1].top, 'px');
		this._edgeElems[i][1].style.width = ''.concat(this._lrCorner.getX() - this._ulCorner.getX() + offsets[1].width, 'px');
		this._edgeElems[i][1].style.height = ''.concat(brdSize + offsets[1].height, 'px');
		this._edgeElems[i][1].style.borderTop = '2px solid #000000';
		this._edgeElems[i][1].style.display = 'block';

		// draw left line:
		this._edgeElems[i][2].style.left = ''.concat(this._ulCorner.getX() + offsets[2].left, 'px');
		this._edgeElems[i][2].style.top = ''.concat(this._ulCorner.getY() + offsets[2].top, 'px');
		this._edgeElems[i][2].style.width = ''.concat(brdSize + offsets[2].width, 'px');
		this._edgeElems[i][2].style.height = ''.concat(this._lrCorner.getY() - this._ulCorner.getY() + offsets[2].height, 'px');
		this._edgeElems[i][2].style.borderRight = '2px solid #000000';
		this._edgeElems[i][2].style.display = 'block';

		// draw right line:
		this._edgeElems[i][3].style.left = ''.concat(this._lrCorner.getX() + offsets[3].left, 'px');
		this._edgeElems[i][3].style.top = ''.concat(this._ulCorner.getY() + offsets[3].top, 'px');
		this._edgeElems[i][3].style.width = ''.concat(brdSize + offsets[3].width, 'px');
		this._edgeElems[i][3].style.height = ''.concat(this._lrCorner.getY() - this._ulCorner.getY() + offsets[3].height, 'px');
		this._edgeElems[i][3].style.borderLeft = '2px solid #000000';
		this._edgeElems[i][3].style.display = 'block';
	}
};

clsRef.prototype._drawControls = function() {
	var offsets = this.getOffsetsPx(Jedox.wss.app.browser);

	for (var i = this._cntrlElems.length - 1; i >= 0; i--) {
		this._cntrlElems[i].props.style.left = ''.concat(this._ulCorner.getX() + offsets[0].propsLeft, 'px');
		this._cntrlElems[i].props.style.top = ''.concat(this._ulCorner.getY() + offsets[0].propsTop, 'px');
		this._cntrlElems[i].props.style.display = 'block';
	}

	this._drawDirArrow(offsets);
};

clsRef.prototype._drawDirArrow = function(offsets) {
	if (offsets == undefined)
		offsets = this.getOffsetsPx(Jedox.wss.app.browser);

	if (this._expDir == this.getConstant('DIRECTION').VERT) {
		var dirArrHeight = this._lrCorner.getY() - this._ulCorner.getY() + offsets[2].height;

		for (var i = this._cntrlElems.length - 1; i >= 0; i--) {
			this._cntrlElems[i].dirArrow.style.left = ''.concat(this._ulCorner.getX() + offsets[2].dirArrLeft, 'px');
			this._cntrlElems[i].dirArrow.style.top = ''.concat(this._ulCorner.getY() + offsets[2].top, 'px');
			this._cntrlElems[i].dirArrow.style.width = ''.concat(6 + offsets[2].dirArrWidth, 'px');
			this._cntrlElems[i].dirArrow.style.height = ''.concat(dirArrHeight, 'px');
			this._cntrlElems[i].dirArrow.style.display = 'block';

			this._cntrlElems[i].arrCanvas.clear();
			this._cntrlElems[i].arrCanvas.setColor("#455B87"); // Prev = #800000
			this._cntrlElems[i].arrCanvas.fillRect(4, 0, 5, dirArrHeight - 15);
			this._cntrlElems[i].arrCanvas.fillPolygon(new Array(0, 12, 6), new Array(dirArrHeight - 15, dirArrHeight - 15, dirArrHeight));
			this._cntrlElems[i].arrCanvas.paint();
		}
	} else {
		var dirArrWidth = this._lrCorner.getX() - this._ulCorner.getX() + offsets[0].width;

		for (var i = this._cntrlElems.length - 1; i >= 0; i--) {
			this._cntrlElems[i].dirArrow.style.left = ''.concat(this._ulCorner.getX() + offsets[0].left, 'px');
			this._cntrlElems[i].dirArrow.style.top = ''.concat(this._ulCorner.getY() + offsets[0].dirArrTop, 'px');
			this._cntrlElems[i].dirArrow.style.width = ''.concat(dirArrWidth, 'px');
			this._cntrlElems[i].dirArrow.style.height = ''.concat(6 + offsets[0].dirArrHeight, 'px');
			this._cntrlElems[i].dirArrow.style.display = 'block';

			this._cntrlElems[i].arrCanvas.clear();
			this._cntrlElems[i].arrCanvas.setColor("#455B87"); // Prev = #800000
			this._cntrlElems[i].arrCanvas.fillRect(0, 4, dirArrWidth - 15, 5);
			this._cntrlElems[i].arrCanvas.fillPolygon(new Array(dirArrWidth - 15, dirArrWidth - 15, dirArrWidth), new Array(0, 12, 6));
			this._cntrlElems[i].arrCanvas.paint();
		}
	}
};

clsRef.prototype._dirSwitchMouseDown = function(doSave) {
	this._expDir = (this._expDir == this.getConstant('DIRECTION').VERT ? this.getConstant('DIRECTION').HORIZ : this.getConstant('DIRECTION').VERT);
	this._drawDirArrow();

	if (doSave)
		this.save(false);
};

clsRef.prototype._dirArrowMouseDown = function(ev) {
	if (document.all)
		ev = window.event;

	var mouseEl = (document.all) ? ev.srcElement : ev.target,
		rngMode = Jedox.wss.range.RangeMode,
		offsets = [0, 0];

	if (mouseEl.id != 'dirArrowCont') {
		offsets = [mouseEl.offsetLeft, mouseEl.offsetTop];

		while (mouseEl.id != 'dirArrowCont')
			mouseEl = mouseEl.parentNode;
	}

	if (this._mode == rngMode.NONE)
		this._selection.setMode(rngMode.EDIT);

	Jedox.wss.mouse.calcGridScreenCoords(ev, mouseEl, offsets);

	this._onmousedown(ev);
};

clsRef.prototype.switchMode = function(mode) {
	var rngMode = Jedox.wss.range.RangeMode;
	this._mode = mode;
	this._subrange.getActiveRange().setMode(mode);

	switch(mode) {
		case rngMode.NONE:
			this.setNormalMode();
			break;
		case rngMode.EDIT:
			this.setEditMode();
			break;
		case rngMode.HIDDEN:
			this.setHiddenMode();
	}
};


clsRef.prototype.setNormalMode = function() {
	var i, j;

	for (i = this._cornerElems.length - 1; i >= 0; i--)
		for (j = this._cornerElems[i].length - 1; j >= 0; j--) {
			this._cornerElems[i][j].style.zIndex = '38';
			this._cornerElems[i][j].style.display = 'none';
		}

	for (i = this._edgeElems.length - 1; i >= 0; i--)
		for (j = this._edgeElems[i].length - 1; j >= 0; j--) {
			this._edgeElems[i][j].style.zIndex = '38';
			this._edgeElems[i][j].style.backgroundImage = 'none';
			this._edgeElems[i][j].style.backgroundColor = 'transparent';
			this._edgeElems[i][j].style.display = 'block';
		}

	for (i = this._cntrlElems.length - 1; i >= 0; i--) {
		this._cntrlElems[i].dirArrow.style.zIndex = '40';
		this._cntrlElems[i].props.style.zIndex = '41';

		this._cntrlElems[i].props.style.display = 'none';
		this._cntrlElems[i].dirArrow.style.display = 'block';
	}

	this._subrange.getActiveRange().setNormalMode();
};

clsRef.prototype.setEditMode = function() {
	var i, j;

	for (i = this._cornerElems.length - 1; i >= 0; i--)
		for (j = this._cornerElems[i].length - 1; j >= 0; j--) {
			this._cornerElems[i][j].style.zIndex = '42';
			this._cornerElems[i][j].style.display = 'block';
		}

	for (i = this._edgeElems.length - 1; i >= 0; i--)
		for (j = this._edgeElems[i].length - 1; j >= 0; j--) {
			this._edgeElems[i][j].style.zIndex = '42';
			this._edgeElems[i][j].style.backgroundImage = 'url(/ui/wss/res/img/borders/hb_horizontal_normal.gif)';
			this._edgeElems[i][j].style.backgroundColor = '#FFFFFF';
		}

	for (i = this._cntrlElems.length - 1; i >= 0; i--) {
		this._cntrlElems[i].dirArrow.style.zIndex = '44';
		this._cntrlElems[i].props.style.zIndex = '45';

		this._cntrlElems[i].props.style.display = 'block';
	}

	this._subrange.getActiveRange().setEditMode();
};

clsRef.prototype.setHiddenMode = function() {
	var i, j;

	for (i = this._cornerElems.length - 1; i >= 0; i--)
		for (j = this._cornerElems[i].length - 1; j >= 0; j--)
			this._cornerElems[i][j].style.display = 'none';

	for (i = this._edgeElems.length - 1; i >= 0; i--)
		for (j = this._edgeElems[i].length - 1; j >= 0; j--)
			this._edgeElems[i][j].style.display = 'none';

	for (i = this._cntrlElems.length - 1; i >= 0; i--) {
		this._cntrlElems[i].props.style.display = 'none';
		this._cntrlElems[i].dirArrow.style.display = 'none';
	}

	this._subrange.getActiveRange().setHiddenMode();
};

clsRef.prototype._getColorNumber = function() {
	return 'hb';
};

clsRef.prototype.getProps = function() {
	this._props.src = [this._upperLeft.getX(), this._upperLeft.getY(), this._lowerRight.getX(), this._lowerRight.getY()];
	this._props.dir = this._expDir;
	this._props.dcell = this._subrange.getActiveRange().getPosInParent();

	return this._props;
};

clsRef.prototype.setProps = function(props) {
	if (props.dir != this._expDir)
		this._dirSwitchMouseDown(false);

	this._props = props;
	this._subrange.getActiveRange()._drawDataCell();
	this.save(true);
};

clsRef.prototype.getId = function(){
	return this._props.id;
};

clsRef.prototype._mouseOnEdgeUp = function(ev) {
	Jedox.wss.app.mimicOvertracking = false;
	this._legacyMouseUp();

	this._status = Jedox.wss.range.AreaStatus.HOVERING;
	Jedox.wss.app.mouseMovementObserver.unsubscribe(this._move);
	Jedox.wss.app.mouseUpObserver.unsubscribe(this._onmouseup);
	this._unHover(ev);
	this.save(false);
};

clsRef.prototype._onmouseup = function(ev) {
	if (this._status == Jedox.wss.range.AreaStatus.EXPANDING)
		this.afterExpanding();

	this._status = Jedox.wss.range.AreaStatus.HOVERING;
	Jedox.wss.app.mouseMovementObserver.unsubscribe(this._move);
	Jedox.wss.app.mouseUpObserver.unsubscribe(this._onmouseup);
	this._unHover(ev);

	this._resizeDirection = Jedox.wss.range.ResizeDirection.NONE;
	this._legacyMouseUp();
	this.save(false);
};

clsRef.prototype._openPropDlg = function(ev) {
	Jedox.gen.load(Jedox.wss.app.dynJSRegistry.manageDynarange, [this.getProps()]);

	if (document.all) {
		window.event.returnValue = false;
		window.event.cancelBubble = true;
	}else{
		ev.preventDefault();
		ev.stopPropagation();
	}
};

clsRef.prototype._propsBtnMouseOver = function(ev) {
	var coords = Jedox.wss.mouse.getGridPos((document.all) ? window.event : ev);

	Jedox.wss.mouse.mimicCellMouseEvent(coords[0], coords[1], "mouseover");
};

clsRef.prototype.remove = function(perm) {
	// Remove subrange.
	this._subrange.remove();

	// Remove html elements for each line in an range.
	for (var i = this._edgeElems.length - 1; i >= 0; i--)
		for (var j = this._edgeElems[i].length - 1; j >= 0; j--)
			this._edgeElems[i][j].parentNode.removeChild(this._edgeElems[i][j]);

	// Remove html elements for edge point.
	for (i = this._cornerElems.length - 1; i >= 0; i--)
		for (j = this._cornerElems[i].length - 1; j >= 0; j--)
			this._cornerElems[i][j].parentNode.removeChild(this._cornerElems[i][j]);

	for (i = this._cntrlElems.length - 1; i >= 0; i--) {
		// Remove Properties button.
		this._cntrlElems[i].props.parentNode.removeChild(this._cntrlElems[i].props);

		// Remove Direction arrow.
		this._cntrlElems[i].dirArrow.parentNode.removeChild(this._cntrlElems[i].dirArrow);
	}

	if (perm) {
		var conn = Jedox.backend,
			rngClearType = Jedox.wss.range.ContentType,
			dcellX = this._props.src[0] + this._props.dcell[0],
			dcellY = this._props.src[1] + this._props.dcell[1],
			ngetRes = conn.ccmd(0, ['nget', [1, 1, this._props.id, this._book._sheetSelector.getActiveSheetId()]])[0];

		conn.ccmdBuffer();

		// Delete Worksheet Element.
		conn.ccmd(0, ['wdel', '', [this._props.wselid]]);

		if (ngetRes[0])
			// Delete associated Named Range
			conn.ccmd(0, ['ndel', ngetRes[1][0].uuid]);

		// Clear value and attribute from previous DataCell underlying cell.
		this._pane.clrRange([dcellX, dcellY, dcellX, dcellY], rngClearType.FORMULA | rngClearType.ATTRS);

		conn.ccmdFlush(true, true, conn.Q_ALL, conn.D_NONE);
	}
};

clsRef.prototype.save = function(force) {
	var props = this.getProps(),
		prevVal = this._props._preview_val;

	function propsChanged(prev, curr) {
		return (!prev.src.compare(curr.src) || prev.dir != curr.dir || !prev.dcell.compare(curr.dcell));
	}

	var propsClone = Ext.ux.clone(props),
			id = propsClone.id,
			_gendata = propsClone._gendata,
			conn = Jedox.backend,
			that = this,
			dcellX = props.src[0] + props.dcell[0],
			dcellY = props.src[1] + props.dcell[1],
			numToLet = Jedox.wss.app.numberToLetter,
			nLoc = '=$'.concat(numToLet[this._upperLeft.getX()], '$', this._upperLeft.getY(), ':$', numToLet[this._lowerRight.getX()], '$', this._lowerRight.getY());

	delete propsClone.id;
	delete propsClone._gendata;

	if (!('wselid' in props)) {
		var	updWSElId = function(res) {
				if (res[0][0] && res[0][1].length)
					that._props.wselid = res[0][1][0];
			};

		conn.ccmdBuffer();

		// Add Worksheet Element.
		conn.ccmd(0, [ 'wadd', '', { e_type: 'hb', id: id, hbdata: propsClone, _gendata: _gendata, n_location: nLoc, pos_offsets: [0, 0, 0, 0]} ]);

		// Add named range.
		conn.ccmd(0, [ 'nadd', [ 1, 1, {
			name: this._props.id,
			refers_to: '="'.concat(prevVal, '"'),
			scope: this._book._sheetSelector.getActiveSheetName(),
			comment: 'Managed by DynaRange '.concat(this._props.id)
		} ] ]);

		// Set value and attribute to DataCell underlying cell.
		conn.ccmd(0, ['cdrn', {cm: true}, [dcellX, dcellY, dcellX, dcellY, {v: prevVal, a: {'palo_pe': {'type': 'dim', 'name': props._gendata[0][2]}}}]]);

		conn.ccmdFlush([ this, updWSElId ], true, conn.Q_ALL, conn.D_NONE);
	} else if (force == undefined || force || propsChanged(this._propsPrev, props)) {
		var updObj = {},
			prevDcellX = this._propsPrev.src[0] + this._propsPrev.dcell[0],
			prevDcellY = this._propsPrev.src[1] + this._propsPrev.dcell[1];

		delete propsClone.wselid;
		updObj[props.wselid] = { id: id, hbdata: propsClone, _gendata: _gendata, n_location: nLoc, pos_offsets: [0, 0, 0, 0] };

		conn.ccmdBuffer();

		// Update Worksheet Element.
		conn.ccmd(0, [ 'wupd', '', updObj ]);

		if (dcellX != prevDcellX || dcellY != prevDcellY || prevVal != this._propsPrev._preview_val || props._gendata[0][2] != this._propsPrev._gendata[0][2]) {
			// Clear value and attribute from previous DataCell underlying cell.
			var rngClearType = Jedox.wss.range.ContentType;
			this._pane.clrRange([prevDcellX, prevDcellY, prevDcellX, prevDcellY], rngClearType.FORMULA | rngClearType.ATTRS);

			// Set value and attribute to DataCell underlying cell.
			conn.ccmd(0, ['cdrn', {cm: true}, [dcellX, dcellY, dcellX, dcellY, {v: prevVal, a: {'palo_pe': {'type': 'dim', 'name': props._gendata[0][2]}}}]]);
		}

		conn.ccmdFlush(true, true, conn.Q_ALL, conn.D_NONE);
	}

	this._propsPrev = Ext.ux.clone(props);
};

clsRef.prototype.move = function(pos) {
	this._upperLeft.setX(pos[0]); this._upperLeft.setY(pos[1]);
	this._lowerRight.setX(pos[2]); this._lowerRight.setY(pos[3]);

	this.save(false);
};

clsRef.prototype.syncActivePane = function() {
	this._pane = this._selection._pane;

	this._subrange.syncActivePane();
};

clsRef = null;
