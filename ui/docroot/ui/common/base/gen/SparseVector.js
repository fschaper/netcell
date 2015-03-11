/*
 * \brief sparse vector with cumulative sum implementation
 *
 * \file SparseVector.js
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
 * SVN: $Id: SparseVector.js 4163 2010-10-25 15:55:29Z predragm $
 *
 */

Jedox.gen.SparseVector = function (len, def)
{
	this._len = len;
	this._def = def;

	this._els = {};
	this._bit = {};
}

Jedox.gen.SparseVector.prototype = {

	  getLen: function ()
	{
		return this._len;
	}

	, getDef: function ()
	{
		return this._def;
	}

	, setElemAt: function (i, val)
	{
		if (i < 1 || i > this._len)
			return;

		var nod,
				len = this._len,
				els = this._els,
				bit = this._bit;

		if (i in els)
		{
			if (val == this._def)
			{
				val -= els[i];
				delete els[i];
			}
			else
				val -= els[i], els[i] += val;

			while (i <= len)
				bit[i][0] += val, i += i & -i;
		}
		else if (val != this._def)
		{
			els[i] = val;

			while (i <= len)
			{
				if (i in bit)
					(nod = bit[i])[0] += val;
				else
					nod = bit[i] = [ val, 0 ];

				++nod[1], i += i & -i;
			}
		}

		return this;
	}

	, getElemAt: function (i)
	{
		if (i < 1 || i > this._len)
			return;

		return i in this._els ? this._els[i] : this._def;
	}

	, reInit: function (def)
	{
		this._els = {};
		this._bit = {};

		if (typeof def == 'number')
			this._def = def;

		return this;
	}

	, getSumUpTo: function (i, from)
	{
		if (i < 1 || i > this._len + 1 || (typeof from == 'number' && from >= i))
			return;

		var nod,
				idx = --i,
				ndc = 0,
				nds = 0,
				bit = this._bit;

		while (i > 0)
		{
			if (i in bit)
				nds += (nod = bit[i])[0], ndc += nod[1];

			i -= i & -i;
		}

		return nds + (idx - ndc) * this._def - (typeof from == 'number' ? this.getSumUpTo(from) : 0);
	}

	, getIdxByOffset: function (i, offset)
	{
		if (i < 1 || i > this._len)
			return;

		for (var s = 0; s <= offset; s += this.getElemAt(i++)) {}

		return i - 1;
	}

	, getSparseArray: function ()
	{
		var array = [],
				idxs = [],
				idx;

		for (idx in this._els)
			idxs.push(idx | 0);

		idxs.sort(function (a, b) { return a - b; });

		for (var i = idxs.length - 1; i >= 0; --i)
			array.unshift(idx = idxs[i], this._els[idx]);

		return array;
	}

};
