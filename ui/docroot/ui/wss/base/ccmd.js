/*
 * \brief ccmd routines
 *
 * \file ccmd.js
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
 *
 * \version
 * SVN: $Id: ccmd.js 5117 2011-07-15 12:37:01Z drazenk $
 *
 */

Jedox.wss.ccmd = new function ()
{
	var _book;

	function _crgn (args)
	{
		var pane = 'p' in args[0] ? _book._aSheet._panes[args[0].p] : _book._aPane;

		pane._cache.clear();

		for (var rgn, frn = pane.furnishCell, comb = args[0].cm, i = 0; (rgn = args[++i]) != undefined; )
			for (var cell, x = rgn[0], y = rgn[1], w = rgn[2], j = 2; (cell = rgn[++j]) != undefined; )
			{
				frn.call(pane, x, y, cell, comb);

				if (++x - rgn[0] >= w && w > 0)
					++y, x = rgn[0];
			}
	}

	function _ccr (args)
	{
		_book._aSheet.setColRowSize(args.shift(), args);
	}

	function _wmv (args)
	{
		for (var wsel, i = args.length - 1; i >= 0; --i)
		{
			wsel = args[i];

			switch (wsel.type)
			{
				case 'img':
					Jedox.wss.wsel.img.moveTo(wsel.id, wsel.pos, wsel.offsets);
					break;

				case 'sccmnt':
					Jedox.wss.cmnt.moveTo(wsel.id, wsel.pos, wsel.offsets);
					break;

				case 'formel':
					Jedox.wss.wsel.formelRemovize(wsel, _book);
					break;

				case 'chart':
					Jedox.wss.wsel.chart.reMovize(wsel.id, wsel.pos, wsel.offsets);
					break;

				case 'hb':
					Jedox.wss.hb.move(wsel.id, wsel.pos);
					break;
			}
		}
	}

	function _rw (args)
	{
		var num = args.length;

		if (!num)
			return;

		var aps = Jedox.wss.app.appModeS,
				buid = _book.uid,
				suid = _book._aSheet.getUid(),
				ts = (new Date()).getTime(),
				numPanes = _book._aSheet._numPanes,
				panes = _book._aSheet._panes,
				uid;

		for (var j, i = num - 1; i >= 0; --i)
			for (j = numPanes - 1; j >= 0; --j)
				document.getElementById(panes[j]._domId.concat('_wsel_cont_', (uid = args[i]))).src = '/be/wss/gen_element.php?wam='.concat(aps, '&buid=', buid, '&suid=', suid, '&id=', uid, '&ts=', ts);
	}

	function _rf (args)
	{
		if (args.length)
			Jedox.wss.wsel.refreshAll(args, _book);
	}

	function _wtrd (args)
	{
		if (args.length)
			Jedox.wss.wsel.updateTarget(args, _book);
	}

	function _curn (args)
	{
		var aSheet = _book._aSheet,
				fuc = aSheet._farthestUsedCell,
				col = args[0],
				row = args[1],
				colChg = false,
				rowChg = false;

		if (col != fuc[0])
			fuc[0] = col, colChg = true;

		if (row != fuc[1])
			fuc[1] = row, rowChg = true;

		if (!(colChg || rowChg))
			return;

		var recalcH = false,
				recalcV = false,
				pane;

		for (var i = aSheet._numPanes - 1; i >= 0; --i)
		{
			pane = aSheet._panes[i];

			if (colChg && pane._conf.hscroll)
			{
				if (col > pane._farthestSeenCell[0])
					pane._farthestSeenCell[0] = col;

				recalcH = true;
			}

			if (rowChg && pane._conf.vscroll)
			{
				if (row > pane._farthestSeenCell[1])
					pane._farthestSeenCell[1] = row;

				recalcV = true;
			}
		}

		if (recalcH)
			for (var i in _book._hScrolls)
				_book._hScrolls[i].check();

		if (recalcV)
			for (var i in _book._vScrolls)
				_book._vScrolls[i].check();
	}

	function _ncr (args)
	{
		_book._aSheet.newDims(0, args[0]);
		_book._aSheet.newDims(1, args[1]);
	}

	var _map = {
	  crgn:	_crgn
	, ccr:	_ccr
	, wmv:	_wmv
	, rw:	_rw
	, rf:	_rf
	, wtrd:	_wtrd
	, curn:	_curn
	, ncr:	_ncr
	};

	this.exec = function (ccmd, book)
	{
		if (!(ccmd instanceof Array) || !(ccmd.length))
			return false;

		_book = book ? book : Jedox.wss.app.activeBook;

		for (var cmd, name, c = -1; (cmd = ccmd[++c]) != undefined; )
			if ((name = cmd.shift()) in _map)
				_map[name](cmd);

		if (_book._gmode_edit)
		{
			_book._aSheet._defaultSelection.getCursorField().refresh();
			Jedox.wss.general.setCurrentCoord(_book);
		}
		else
			_book._aSheet._cursorField.refresh();
	};

	this.mexec = function (data)
	{
		var reg = Jedox.wss.book.reg;

		for (var id in data)
			this.exec(data[id], reg[id]);
	};

};