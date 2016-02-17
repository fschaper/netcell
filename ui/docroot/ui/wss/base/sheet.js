/*
 * \brief sheet related routines
 *
 * \file sheet.js
 *
 * Copyright (C) 2006-2011 Jedox AG
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: sheet.js 5128 2011-07-18 14:31:43Z predragm $
 *
 */

Jedox.wss.sheet = new function ()
{
	var that = this,
			_json = Ext.util.JSON;

	this.insDelMode = {
	  SHIFT_VER: 1
	, SHIFT_HOR: 2
	, ENTIRE_COL: 3
	, ENTIRE_ROW: 4
	};

	this.undo = function ()
	{
		var env = Jedox.wss.app.environment;
		var gridMode = Jedox.wss.grid.GridMode;

		if (env.inputMode == gridMode.EDIT || env.inputMode == gridMode.INPUT)
		{
			env.redoValue = env.inputField.value;
			env.inputField.value = env.undoValue;
			Jedox.wss.app.currFormula.setValue(env.inputField.value);
			Jedox.wss.app.updateUndoState([ 0, 1 ], false);
			Jedox.wss.app.lastInputField.focus();
		}
		else
			Jedox.wss.app.activeBook.undo(1);
	};

	this.redo = function ()
	{
		var env = Jedox.wss.app.environment;
		var gridMode = Jedox.wss.grid.GridMode;

		if (env.inputMode == gridMode.EDIT || env.inputMode == gridMode.INPUT)
		{
			env.inputField.value = env.redoValue;
			Jedox.wss.app.currFormula.setValue(env.inputField.value);
			Jedox.wss.app.updateUndoState([ 1, 0 ], false);
			Jedox.wss.app.lastInputField.focus();
		}
		else
			Jedox.wss.app.activeBook.redo(1);
	};

	this.select = function (cb, wsId, book, selSheet)
	{
		var activeBook = Jedox.wss.app.activeBook;

		if (!book)
			book = activeBook;

		var sheetSel = book._sheetSelector;

		sheetSel.enable(false);
		sheetSel.freeze(false);
		sheetSel.selectById(wsId, !selSheet);
		sheetSel.enable(true);

		if (selSheet) {
			sheetSel.action = sheetSel.actionTypes.SELECTED;
			activeBook._actOnSheetSel(cb);
		} else
			book._showSheet(cb, wsId);
	};

	this.ins = function (mode)
	{
		var activeBook = Jedox.wss.app.activeBook,
				defRanges = Jedox.wss.app.environment.defaultSelection.getRanges(),
				ranges = [];

		for (var mi, range, i = defRanges.length - 1; i >= 0; --i)
		{
			range = defRanges[i].getCoords();

			if (range[0] == range[2] && range[1] == range[3] && (mi = activeBook._aPane.getMergeInfo(range[0], range[1])) && mi[0])
				range[2] += mi[1] - 1, range[3] += mi[2] - 1;

			range.push(mode);
			ranges.unshift(range);
		}

		Jedox.backend.ccmd(true, [ 'icel' ].concat(ranges), true);
	};

	this.del = function (mode)
	{
		var activeBook = Jedox.wss.app.activeBook,
				defRanges = Jedox.wss.app.environment.defaultSelection.getRanges(),
				ranges = [];

		for (var mi, range, i = defRanges.length - 1; i >= 0; --i)
		{
			range = defRanges[i].getCoords();

			if (range[0] == range[2] && range[1] == range[3] && (mi = activeBook._aPane.getMergeInfo(range[0], range[1])) && mi[0])
				range[2] += mi[1] - 1, range[3] += mi[2] - 1;

			range.push(mode);
			ranges.unshift(range);
		}

		Jedox.backend.ccmd(true, [ 'dcel' ].concat(ranges), true);
	};

	this.getMergeState = function ()
	{
		return Jedox.wss.app.activePane.getMergeState(Jedox.wss.app.environment.defaultSelection.getActiveRange().getCoords());
	};

	this.merge = function ()
	{
		Jedox.wss.app.activePane.merge(Jedox.wss.app.environment.defaultSelection.getActiveRange().getCoords());
	};

	this.unMerge = function ()
	{
		Jedox.wss.app.activePane.merge(Jedox.wss.app.environment.defaultSelection.getActiveRange().getCoords(), true);
	};

	this.refresh = function (cb, onlyActive)
	{
		function _post (res, cb)
		{
			Jedox.wss.ccmd.mexec(res);

			if (cb instanceof Array && cb.length > 1)
				cb[1].apply(cb[0], cb.slice(2));
		}

		Jedox.backend.rpc([ this, _post, cb ], 'WSS', 'refresh', [ Jedox.wss.book.getVirtScroll(onlyActive), Jedox.wss.app.autoCalc ]);
	};

	this.getColRowSize = function (type)
	{
		var activeSheet = Jedox.wss.app.activeSheet;

		if (!activeSheet || !activeSheet._defaultSelection)
			return;

		var crs = activeSheet._colRowDims[type],
				ranges = activeSheet._defaultSelection.getRanges(),
				size, coords, beg, end, i, j;

		if (!ranges[0])
			return;

		size = crs.getElemAt(ranges[0].getCoords()[type]);

		for (i = ranges.length - 1; i >= 0; --i)
		{
			coords = ranges[i].getCoords();
			beg = coords[type];
			end = coords[type + 2];

			if (end - beg > 256)
				return;

			for (j = end; j >= beg; --j)
				if (size != crs.getElemAt(j))
					return;
		}

		return size;
	};

};