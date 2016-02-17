/*
 * \brief backend WSS RPC wrapper class
 *
 * \file WSS.js
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
 * SVN: $Id: WSS.js 4961 2011-05-16 13:57:56Z mladent $
 *
 */

Jedox.backend.rpc.WSS = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (onSuccess, onError, onTimeout)
	{
		Jedox.backend.rpc.WSS.parent.constructor.call(this, onSuccess, onError, onTimeout);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.backend.rpc.WSS, Jedox.backend.RPCWrapper);

//public static fields

// public fields & methods
var _prototype = Jedox.backend.rpc.WSS.prototype;

_prototype.getPreload = function ()
{
	return this._dispatch('getPreload', 'WSS', 'getPreload', arguments);
};

_prototype.wsel = function ()
{
	return this._dispatch('wsel', 'WSS', 'wsel', arguments);
};

_prototype.getCurrWbId = function ()
{
	return this._dispatch('getCurrWbId', 'WSS', 'getCurrWbId', arguments);
};

_prototype.getCurrWsId = function ()
{
	return this._dispatch('getCurrWsId', 'WSS', 'getCurrWsId', arguments);
};

_prototype.get_worksheet_elements = function ()
{
	return this._dispatch('get_worksheet_elements', 'WSS', 'get_worksheet_elements', arguments);
};

_prototype.loadFrameset = function ()
{
	return this._dispatch('loadFrameset', 'WSS', 'loadFrameset', arguments);
};

_prototype.load_workbook = function ()
{
	return this._dispatch('load_workbook', 'WSS', 'load_workbook', arguments);
};

_prototype.save_workbook = function ()
{
	return this._dispatch('save_workbook', 'WSS', 'save_workbook', arguments);
};

_prototype.getWbName = function ()
{
	return this._dispatch('getWbName', 'WSS', 'getWbName', arguments);
};

_prototype.addSheet = function ()
{
	return this._dispatch('addSheet', 'WSS', 'addSheet', arguments);
};

_prototype.copySheet = function ()
{
	return this._dispatch('copySheet', 'WSS', 'copySheet', arguments);
};

_prototype.moveSheet = function ()
{
	return this._dispatch('moveSheet', 'WSS', 'moveSheet', arguments);
};

_prototype.addCloneWorksheet = function ()
{
	return this._dispatch('addCloneWorksheet', 'WSS', 'addCloneWorksheet', arguments);
};

_prototype.removeCloneWorksheet = function ()
{
	return this._dispatch('removeCloneWorksheet', 'WSS', 'removeCloneWorksheet', arguments);
};

_prototype.getSheets = function ()
{
	return this._dispatch('getSheets', 'WSS', 'getSheets', arguments);
};

_prototype.getLoadedBooks = function ()
{
	return this._dispatch('getLoadedBooks', 'WSS', 'getLoadedBooks', arguments);
};

_prototype.getLoadedNodes = function ()
{
	return this._dispatch('getLoadedNodes', 'WSS', 'getLoadedNodes', arguments);
};

_prototype.removeFrameset = function ()
{
	return this._dispatch('removeFrameset', 'WSS', 'removeFrameset', arguments);
};

_prototype.removeBook = function ()
{
	return this._dispatch('removeBook', 'WSS', 'removeBook', arguments);
};

_prototype.selectSheet = function ()
{
	return this._dispatch('selectSheet', 'WSS', 'selectSheet', arguments);
};

_prototype.selectBook = function ()
{
	return this._dispatch('selectBook', 'WSS', 'selectBook', arguments);
};

_prototype.resolveNodePath = function ()
{
	return this._dispatch('resolveNodePath', 'WSS', 'resolveNodePath', arguments);
};

_prototype.exportMacros = function ()
{
	return this._dispatch('exportMacros', 'WSS', 'exportMacros', arguments);
};

_prototype.refresh = function ()
{
	return this._dispatch('refresh', 'WSS', 'refresh', arguments);
};

_prototype.cb = function ()
{
	return this._dispatch('cb', 'WSS', 'cb', arguments);
};

_prototype.ccmd = function ()
{
	return this._dispatch('ccmd', 'WSS', 'ccmd', arguments);
};

_prototype.ccmd = function ()
{
	return this._dispatch('ccmd', 'WSS', 'ccmd', arguments);
};
