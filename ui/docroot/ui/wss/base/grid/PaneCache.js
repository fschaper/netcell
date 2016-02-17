/*
 * \brief class PaneCache representing pane cell cache
 *
 * \file PaneCache.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: PaneCache.js 4798 2011-04-03 02:09:27Z predragm $
 *
 */

Jedox.wss.grid.PaneCache = function (pane)
{
	this._pane = pane;

	this._conn = Jedox.backend;

	this._raCoef = this._READAHEAD_COEF;

	this.clear();
};

Jedox.wss.grid.PaneCache.prototype =
{
	// consts
	  _READAHEAD_COEF: 2

	, clear: function ()
	{
		this._map = {};
		this._rng = [ 0, 0, 0, 0 ];
	}

	, get: function (x, y)
	{
		if (x in this._map)
			return this._map[x][y];

		return undefined;
	}

	, getPart: function (x, y, type)
	{
		if (x in this._map)
		{
			x = this._map[x];

			if (y in x)
				return x[y][type];

			return undefined;
		}

		return undefined;
	}

	, has: function (x, y)
	{
		return x in this._map && y in this._map[x];
	}

	, hasPart: function (x, y, type)
	{
		return x in this._map && y in this._map[x] && type in this._map[x][y];
	}

	, miss: function (rng)
	{
		return rng[0] < this._rng[0] || rng[2] > this._rng[2] || rng[1] < this._rng[1] || rng[3] > this._rng[3];
	}

	, load: function (cb, rng, opts)
	{
		if (typeof opts != 'object')
			opts = {};

		if (opts.sdr in rng)
		{
			var h_incr = this._pane._numCols * this._raCoef,
					v_incr = this._pane._numRows * this._raCoef,
					fuc = this._pane._sheet._farthestUsedCell;

			switch (opts.sdr)
			{
				case 0: // h back
					if ((rng[0] -= h_incr) < 1)
						rng[0] = 1;
					break;

				case 2: // h front
					if ((rng[2] += h_incr) > fuc[0])
						rng[2] = fuc[0];
					break;

				case 1: // v back
					if ((rng[1] -= v_incr) < 1)
						rng[1] = 1;
					break;

				case 3: // v front
					if ((rng[3] += v_incr) > fuc[1])
						rng[3] = fuc[1];
					break;
			}
		}

		return (new Jedox.backend.CCmdAsyncRqst('[["grar",'.concat(this._conn.Q_ALL, ',', rng[0], ',', rng[1], ',', rng[2], ',', rng[3], opts.rfr ? ',true]]' : ']]')))
					 .setOnSuccess([ this, this._fill, cb, rng, opts ]);
	}

	, _fill: function (rgns, cb, rng, opts)
	{
		var map = this._map = {},
				grid = this._pane.getVirtScroll(),
				frn = opts.frn ? this._pane.furnishCell : false;

		this._rng = rng;
		rgns = rgns[0];

		for (var rgn, i = 0; (rgn = rgns[++i]) != undefined; )
			for (var cell, x = rgn[0], y = rgn[1], w = rgn[2], j = 2; (cell = rgn[++j]) != undefined; )
			{
				if (!(x in map))
					map[x] = {};

				map[x][y] = cell;

				if (frn && x >= grid[0] && x <= grid[2] && y >= grid[1] && y <= grid[3])
					frn.call(this._pane, x, y, cell);

				if (++x - rgn[0] >= w && w > 0)
					++y, x = rgn[0];
			}

		if (cb instanceof Array && cb.length > 1)
			cb[1].apply(cb[0], cb.slice(2));
	}

};