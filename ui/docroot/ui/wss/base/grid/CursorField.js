/*
 * \brief class representing cursor field
 *
 * \file CursorField.js
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: CursorField.js 4837 2011-04-13 12:25:05Z predragm $
 *
 */

Jedox.wss.grid.CursorField = function(domID, sheet, selection) {

	var _cursorFld = [],
		_actCursorFld, _coords,

		_sheet = sheet,
		_selection = selection ? selection : _sheet._defaultSelection,
		_book = _sheet._book,
		_panes = _sheet._panes,
		_pane = _selection ? _selection._pane : _sheet._aPane,
		_env = _sheet._env.shared,

		_containers = [];

	for (var i = _panes.length - 1; i >= 0; i--)
		_containers[i] = _panes[i] ? _panes[i].getIC() : null;

	this.draw = function(activeCell, activeCellCoords) {
		var viewMode = Jedox.wss.grid.viewMode,
			offsets = (_env.viewMode == viewMode.DESIGNER) ? {t: 1, l: 0, w: -6, h: -6} : {t: -1, l: -1, w: -5, h: -5},
			selCelFVal = (_pane == undefined) ? _env.selectedCellValue : _pane.getCellValue(activeCellCoords.getX(), activeCellCoords.getY()),
			defDraw = true;

		_coords = activeCellCoords;

		if (selCelFVal == undefined)
			selCelFVal = '';

		if (_pane == undefined) {
			if (selCelFVal.indexOf('<') == 0)
				defDraw = false;
		} else {
			var cellType = _pane.getCellType(activeCellCoords.getX(), activeCellCoords.getY());
			defDraw = (cellType == undefined || cellType == 's' || cellType == 'n' || cellType == 'b' || cellType == 'e');
		}

		for (var i = _cursorFld.length - 1; i >= 0; i--) {
			_cursorFld[i].style.left = activeCell.ulX + offsets.l + 'px';
			_cursorFld[i].style.top = activeCell.ulY + offsets.t + 'px';

			_cursorFld[i].style.width = activeCell.lrX - activeCell.ulX + offsets.w + 'px';
			_cursorFld[i].style.height = activeCell.lrY - activeCell.ulY + offsets.h + 'px';

			if (defDraw)
				Jedox.util.setText(_cursorFld[i], selCelFVal);
			else {
				while (_cursorFld[i].childNodes.length >= 1)
					_cursorFld[i].removeChild(_cursorFld[i].firstChild);

				_cursorFld[i].appendChild(_env.selectedCell.firstChild.cloneNode(true));
			}

			Jedox.wss.style.cellTransfer(_cursorFld[i]);

			// Show only in active pane.
			_cursorFld[i].style.display = _env.viewMode == viewMode.USER ? 'block' : (_pane._id == i ? 'block' : 'none');
		}
	};

	this.hide = function() {
		for (var i = _cursorFld.length - 1; i >= 0; i--)
			_cursorFld[i].style.display = 'none';
	};

	this.show = function() {
		for (var i = _cursorFld.length - 1; i >= 0; i--)
			// Show only in active pane.
			_cursorFld[i].style.display = _pane._id == i ? 'block' : 'none';
	};

	this.adjustVisibility = function() {
		if (!_coords)
			return;

		var x = _coords.getX(), y = _coords.getY();

		if (_sheet.isCellHidden(x, y)) {
			var mrgInfoSelCell = _pane.getMergeInfo(x, y),
				actCellCoords = _pane.getPixelsByCoords(x, y),
				actCellIncCoords = _pane.getPixelsByCoords(x + (mrgInfoSelCell && mrgInfoSelCell[0] ? mrgInfoSelCell[1] : 1), y + (mrgInfoSelCell && mrgInfoSelCell[0] ? mrgInfoSelCell[2] : 1));

			this.draw(
				{
					ulX: actCellCoords[0],
					ulY: actCellCoords[1],
					lrX: actCellIncCoords[0],
					lrY: actCellIncCoords[1]
				},
				_coords
			);
		} else
			this.hide();
	};

	this.getSize = function() {
		var sWidth = _actCursorFld.style.width,
			sHeight = _actCursorFld.style.height;

		return {w: parseInt(sWidth.substr(0, sWidth.length - 2)), h: parseInt(sHeight.substr(0, sHeight.length - 2))};
	};

	this.getPosition = function() {
		var sTop = _actCursorFld.style.top,
			sLeft = _actCursorFld.style.left;

		return {t: parseInt(sTop.substr(0, sTop.length - 2)), l: parseInt(sLeft.substr(0, sLeft.length - 2))};
	};

	this.refresh = function() {
		var selCellCoords = _env.selectedCellCoords,
			cursorValue = typeof selCellCoords[0] != 'number' || typeof selCellCoords[1] != 'number' ? undefined : _pane.getCellValue(selCellCoords[0], selCellCoords[1]),
			redrawCursorField;

		if (_env.viewMode == Jedox.wss.grid.viewMode.USER && _actCursorFld.style.display != 'none' && _pane.isCellLocked(selCellCoords[0], selCellCoords[1])) {
			for (var i = _cursorFld.length - 1; i >= 0; i--)
				_cursorFld[i].style.display = 'none';

			return;
		}

		try {
			redrawCursorField = !cursorValue.search(/^<img src="/);
		} catch (e) {
			redrawCursorField = false;
		}

		if (redrawCursorField)
			_selection.getActiveRange().drawActiveCell();
		else {
			cursorValue = cursorValue == undefined ? '' : Jedox.wss.general.filterHLTags(selCellCoords[0], selCellCoords[1], cursorValue, false);

			for (var i = _cursorFld.length - 1; i >= 0; i--) {
				Jedox.util.setText(_cursorFld[i], cursorValue);
				Jedox.wss.style.cellTransfer(_cursorFld[i]);
			}
		}
	};

	this.cloneStyle = function() {
		for (var i = _cursorFld.length - 1; i >= 0; i--)
			Jedox.wss.style.cellTransfer(_cursorFld[i]);
	};

	this.setContent = function(content) {
		for (var i = _cursorFld.length - 1; i >= 0; i--)
			_cursorFld[i].innerHTML = content;
	};

	this.setBorder = function(style) {
		for (var i = _cursorFld.length - 1; i >= 0; i--)
			_cursorFld[i].style.border = style;
	};

	this.syncActivePane = function() {
		_pane = _selection ? _selection._pane : _sheet._aPane;
		_actCursorFld = _cursorFld[_pane._id];
	};

	function _init() {
		var viewMode = Jedox.wss.grid.viewMode,
		cursorFld = document.createElement('div'), cursorFldCp;
		cursorFld.id = ''.concat(domID, '_cursorField');

		if (_env.viewMode == viewMode.DESIGNER)
			cursorFld.className = 'activeCellElement cursorField default-format customCursor';
		else if (_env.viewMode == viewMode.USER)
			cursorFld.className = 'cursorFieldUM default-format';

		cursorFld.style.display = 'none';

		for (var i = _panes.length - 1; i >= 0; i--) {
			cursorFldCp = i > 0 ? cursorFld.cloneNode(true) : cursorFld;

			cursorFldCp.ondblclick = function() {
				Jedox.wss.mouse.showCursorLayer('marker_sand_clock');

				var selCellCoords = _env.selectedCellCoords;
				var cbRes = _pane.cbFire(selCellCoords[0], selCellCoords[1], 'dblclick', {
					c: selCellCoords[0],
					r: selCellCoords[1]
				});
				Jedox.wss.mouse.hideCursorLayer();

				if (!cbRes)
					return false;

				Jedox.wss.general.setInputMode(_actCursorFld.innerHTML != '' ? Jedox.wss.grid.GridMode.EDIT : Jedox.wss.grid.GridMode.INPUT);
				Jedox.wss.general.showInputField(null, false, true);
			}

			if (_env.viewMode == viewMode.DESIGNER) {
				cursorFldCp.onmousedown = function(ev) {
					if (document.all)
						ev = window.event;

					var selCellCoords = _env.selectedCellCoords;
					if (!_pane.cbFire(selCellCoords[0], selCellCoords[1], 'mousedown', ev))
						return false;

					if (ev.button == 2 || (Ext.isMac && ev.button == 0 && Jedox.wss.app.ctrlKeyPressed))
						Jedox.wss.mouse.showMainCntxMenu(ev);
					else if (_env.inputMode == Jedox.wss.grid.GridMode.DIALOG && Jedox.wss.app.sourceSel)
						Jedox.wss.mouse.initSourceRange(_pane.getCellByCoords(selCellCoords[0], selCellCoords[1]), selCellCoords);
					else {
						var singleCell = _selection.isSingleCell();
						_selection.set(
							new Jedox.gen.Point(selCellCoords[0], selCellCoords[1]),
							new Jedox.gen.Point(selCellCoords[0], selCellCoords[1])
						);

						if (!singleCell)
							_selection.draw();

						_selection.registerForMouseMovement(_env.selectedCell);
					}
				}

				cursorFldCp.onmouseover = function() {
					_env.lastCell = _env.selectedCell;
					_env.lastCellCoords = _env.selectedCellCoords;

					// cell comment
					Jedox.wss.cmnt.showComment(_env.lastCellCoords, _pane);
				}
			}

			_cursorFld[i] = cursorFldCp;
			_containers[i].appendChild(cursorFldCp);
		}

		_actCursorFld = _cursorFld[0];
	}

	_init();
}