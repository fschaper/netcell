/*
 * \brief class representing abstract point
 *
 * \file Point.js
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
 * SVN: $Id: Point.js 4135 2010-10-24 19:37:01Z predragm $
 *
 */

Jedox.gen.Point = function (x, y)
{
	this._x = x;
	this._y = y;
}

Jedox.gen.Point.prototype = {

	getX: function ()
	{
		return this._x;
	},

	getY: function ()
	{
		return this._y;
	},

	setX: function (x)
	{
		this._x = x;
	},

	setY: function (y)
	{
		this._y = y;
	},

	getCoords: function ()
	{
		return [ this._x, this._y ];
	},

	toString: function ()
	{
		return this._x + ' / ' + this._y;
	},

	equals: function (point)
	{
		return this._x == point._x && this._y == point._y;
	},

	equalsX: function (point)
	{
		return this._x == point._x;
	},

	equalsY: function (point)
	{
		return this._y == point._y;
	},

	clone: function ()
	{
		return new Jedox.gen.Point(this._x, this._y);
	}

};