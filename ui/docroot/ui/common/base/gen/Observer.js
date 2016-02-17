/*
 * \brief class implementing Observer pattern
 *
 * \file Observer.js
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
 *
 * \version
 * SVN: $Id: Observer.js 2045 2009-08-25 08:57:21Z predragm $
 *
 */

Jedox.gen.Observer = function ()
{
	this._fns = [];
	this._ths = [];
}

Jedox.gen.Observer.prototype = {

	notify: function (that)
	{
		var idx, fns = this._fns.slice(), ths = this._ths.slice(),
				args = Array.prototype.slice.call(arguments, 1);

		for (var len = fns.length, i = 0; i < len; ++i)
			fns[i].apply(ths[i] ? ths[i] : that, args);

		return this;
	},

	subscribe: function (fn, th)
	{
		if (this._fns.indexOf(fn) < 0)
			this._fns.push(fn), this._ths.push(th);

		return this;
	},

	unsubscribe: function (fn)
	{
		var idx;

		if ((idx = this._fns.indexOf(fn)) >= 0)
			this._fns.splice(idx, 1), this._ths.splice(idx, 1);

		return this;
	}
};
