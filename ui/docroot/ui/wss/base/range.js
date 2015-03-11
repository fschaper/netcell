/*
 * \brief routines for handling ranges
 *
 * \file range.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: range.js 4276 2010-11-09 13:01:22Z predragm $
 *
 */

Jedox.wss.range = new function() {

	/**
	 * Stores available range stati
	 * @type Number
	 */
	this.RangeMode = {
		NONE   : 0, // range has been set
		EDIT   : 1, // range is being resized
		HIDDEN : 2  // range is hidden
	};

	/**
	 * Stores available types of range
	 * @type Number
	 */
	this.RangeType = {
		NORMAL  : 0, // default range
		FORMULA : 1, // formula range
		MARK	: 2	 // mark range
	};

	/**
	 * Stores available types of area
	 * @type Number
	 */
	this.AreaStatus = {
		NORMAL    : 0, // area is visible
		HOVERING  : 1, // like visible, but mouse is on area border
		DRAGGING  : 2, // like hovering, but mouse is down
		RESIZING  : 3, // one of the border dots were clicked and mouse is still hold down
		EXPANDING : 4, // like resizing, but mouse is being moved
		MOVING    : 5  // like dragging, but mouse is being moved
	};

	/**
	 * Stores available area stati
	 * @type Number
	 */
	this.AreaState = {
		NORMAL : 0,
		NEW    : 1 // area has just been created. Important for formula ranges to put the range coordinates into formula
	};

	/**
	 * Stores available border stati Jedox.wss.range.BorderState
	 * @type Number
	 */
	this.BorderState = {
		NORMAL : 0,
		BOLD   : 1,
		UNKOWN : 2,
		DOTTED : 3
	};

	/**
	 * Stores available stati of display
	 * @type Number
	 */
	this.DisplayStatus = {
		VISIBLE : 0,
		HIDDEN  : 1
	};

	/**
	 * Stores available resize directions
	 * @type Number
	 */
	this.ResizeDirection = {
		NONE : 0,
		SOUTH_EAST : 1,
		SOUTH_WEST : 2,
		NORTH_EAST : 3,
		NORTH_WEST : 4
	};

	/**
	 * Stores available content types
	 * @type Number
	 */
	this.ContentType = {
	  FORMULA: 1
	, STYLE: 2
	, FORMAT: 4
	, ATTRS: 8
	, CNDFMT: 16
	, ALL_CLEAR: 1 | 2 | 4 | 8
	, ALL_PASTE: 1 | 2 | 4 | 8 | 16
	, VALUE: 32
	};

	this.drawDependingCells = function (formulastr)
	{
		var env = Jedox.wss.app.environment,
				refs = Jedox.wss.formula.parse(formulastr, Jedox.wss.app.activePane.getCellNFs(env.selectedCellCoords[0], env.selectedCellCoords[1]));

		if (refs.sgn == env.formulaSelection.lastParseRes.sgn)
			return;

		env.formulaSelection.lastParseRes = refs;

		var refs_tbl = refs.tbl,
				toks = {},
				tok, key;

		for (key in refs_tbl)
			toks[key] = refs_tbl[key].slice();

		for (var area, area_tok, states = Jedox.wss.range.AreaState, areas = env.formulaSelection.getRanges().slice(), i = areas.length - 1; i >= 0; --i)
		{
			area = areas[i];
			area_tok = area.formulaToken;
			key = area_tok.key;

			if (!(key in toks))
			{
				env.formulaSelection.removeRange(i);
				continue;
			}

			tok = toks[key].shift();

			if (area_tok.id != tok.id || area.getState() == states.NEW)
				area_tok.id = tok.id, area.setState(states.NORMAL), area.repaint();

			area.formulaToken = tok;

			if (!toks[key].length)
				delete toks[key];
		}

		var activeSheet = Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName(),
				Point = Jedox.gen.Point;

		for (key in toks)
			for (var i = toks[key].length - 1; i >= 0; --i)
			{
				tok = toks[key][i];

				if (tok.sheet.length && tok.sheet != activeSheet)
					continue;

				var area = env.formulaSelection.getRange(env.formulaSelection.addRange(new Point(tok.rng[0], tok.rng[1]), new Point(tok.rng[2], tok.rng[3]), tok.nf) - 1);

				area.formulaToken = tok;
				area.draw();
			}
	};

	this.getCellCoord = function (cell)
	{
		return [ [ Jedox.util.offsetLeft(cell), Jedox.util.offsetLeft(cell) + cell.offsetWidth ], [ Jedox.util.offsetTop(cell), Jedox.util.offsetTop(cell) + cell.offsetHeight ] ];
	};

	this.unsetArrayFormula = function ()
	{
		var rngs = Jedox.wss.app.environment.defaultSelection.getRanges(),
				backend = Jedox.backend,
				ccmd = [ 'uaf' ],
				i = -1, rng;

		while ((rng = rngs[++i]) !== undefined)
			ccmd.push(rng.getCoords());

		backend.ccmd(true, ccmd, true, backend.Q_VALUE | backend.Q_STYLE | backend.Q_FORMULA_WE | backend.Q_FMT_VAL | backend.Q_FMT | backend.Q_FORMULA_NF);
	};

}