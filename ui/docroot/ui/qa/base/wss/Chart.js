/*
 * \brief chart wrapper class
 *
 * \file Button.js
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
 *
 * \version
 * SVN: $Id: Chart.js 5055 2011-06-14 13:18:51Z djordjez $
 *
 */

Jedox.qa.wss.Chart = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (obj, paneId)
	{
		Jedox.qa.wss.Chart.parent.constructor.call(this, obj, paneId);

		// private fields

		// private methods

		// public fields
		this._cmp = this._obj.resCont[this._pane._id];

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.qa.wss.Chart, Jedox.qa.wss.Elem);

// public static fields

// public fields & methods
var _prototype = Jedox.qa.wss.Chart.prototype;

_prototype.forClick = function () {
	return this._cmp;
};

_prototype.hasContent = function () {
	if(!Ext.isIE)
		return this._cmp.naturalWidth && this._cmp.naturalHeight ? true : false;
	else
		return (this._cmp.width == 28 && this._cmp.height == 30) || (this._cmp.width == 0 && this._cmp.height == 0) ? false : true;
};