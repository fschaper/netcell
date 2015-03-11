/*
 * \brief toolbar component class
 *
 * \file Toolbar.js
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
 * SVN: $Id: Toolbar.js 4683 2011-03-09 13:27:29Z andrejv $
 *
 */

Jedox.qa.cmp.Toolbar = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (id, data)
	{
		Jedox.qa.cmp.Toolbar.parent.constructor.call(this, id, data);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.qa.cmp.Toolbar, Jedox.qa.cmp.Generic);

// public static fields

// public fields & methods
var _prototype = Jedox.qa.cmp.Toolbar.prototype;

// Int item: number of item to be selected
_prototype.getItem = function (item)
{
	var cmp = Ext.getCmp(this._id);
	if (!cmp) return;
	if (!item) item = 0;

	return cmp.items.items[item].el.dom;
};
