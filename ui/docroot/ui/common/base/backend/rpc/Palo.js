/*
 * \brief backend Palo RPC wrapper class
 *
 * \file Palo.js
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: Palo.js 5124 2011-07-18 11:28:00Z mladent $
 *
 */

Jedox.backend.rpc.Palo = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (onSuccess, onError, onTimeout)
	{
		Jedox.backend.rpc.Palo.parent.constructor.call(this, onSuccess, onError, onTimeout);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.backend.rpc.Palo, Jedox.backend.RPCWrapper);

//public static fields

// public fields & methods
var _prototype = Jedox.backend.rpc.Palo.prototype;

// palo
_prototype.getServList = function ()
{
	return this._dispatch('getServList', 'palo', 'getServList', arguments);
};

_prototype.getServListWithDBs = function ()
{
	return this._dispatch('getServListWithDBs', 'palo', 'getServListWithDBs', arguments);
};

_prototype.getDBs = function ()
{
	return this._dispatch('getDBs', 'palo', 'getDBs', arguments);
};

_prototype.setPreselectServDb = function ()
{
	return this._dispatch('setPreselectServDb', 'palo', 'setPreselectServDb', arguments);
};

_prototype.getDims = function ()
{
	return this._dispatch('getDims', 'palo', 'getDims', arguments);
};

_prototype.getCubeNames = function ()
{
	return this._dispatch('getCubeNames', 'palo', 'getCubeNames', arguments);
};

_prototype.getCubeDims = function ()
{
	return this._dispatch('getCubeDims', 'palo', 'getCubeDims', arguments);
};

_prototype.setWorkingMode = function ()
{
	return this._dispatch('setWorkingMode', 'palo', 'setWorkingMode', arguments);
};

_prototype.getTreeNodes = function ()
{
	return this._dispatch('getTreeNodes', 'palo', 'getTreeNodes', arguments);
};

// palo_misc
_prototype.getDimStringAttrs = function ()
{
	return this._dispatch('getDimStringAttrs', 'palo_misc', 'getDimStringAttrs', arguments);
};

_prototype.searchElem = function ()
{
	return this._dispatch('searchElem', 'palo_misc', 'searchElem', arguments);
};

_prototype.searchElems = function ()
{
	return this._dispatch('searchElems', 'palo_misc', 'searchElems', arguments);
};

_prototype.getAttributedElems = function ()
{
	return this._dispatch('getAttributedElems', 'palo_misc', 'getAttributedElems', arguments);
};

_prototype.createNewDb = function ()
{
	return this._dispatch('createNewDb', 'palo_misc', 'createNewDb', arguments);
};

_prototype.deleteDb = function ()
{
	return this._dispatch('deleteDb', 'palo_misc', 'deleteDb', arguments);
};

_prototype.getRules = function ()
{
	return this._dispatch('getRules', 'palo_misc', 'getRules', arguments);
};

_prototype.createRule = function ()
{
	return this._dispatch('createRule', 'palo_misc', 'createRule', arguments);
};

_prototype.deleteRule = function ()
{
	return this._dispatch('deleteRule', 'palo_misc', 'deleteRule', arguments);
};

_prototype.modifyRule = function ()
{
	return this._dispatch('modifyRule', 'palo_misc', 'modifyRule', arguments);
};

_prototype.doImportCleanup = function ()
{
	return this._dispatch('doImportCleanup', 'palo_misc', 'doImportCleanup', arguments);
};

//palo_sbst
_prototype.getDimAttrs = function ()
{
	return this._dispatch('getDimAttrs', 'palo_sbst', 'getDimAttrs', arguments);
};

_prototype.getSubsetNames = function ()
{
	return this._dispatch('getSubsetNames', 'palo_sbst', 'getSubsetNames', arguments);
};

_prototype.handlerGetGeneratedSubsetFunc = function ()
{
	return this._dispatch('handlerGetGeneratedSubsetFunc', 'palo_sbst', 'handlerGetGeneratedSubsetFunc', arguments);
};

_prototype.getSubsetList = function ()
{
	return this._dispatch('getSubsetList', 'palo_sbst', 'getSubsetList', arguments);
};

_prototype.setDynarangeList = function ()
{
	return this._dispatch('setDynarangeList', 'palo_sbst', 'setDynarangeList', arguments);
};

_prototype.getSubsetDialogData = function ()
{
	return this._dispatch('getSubsetDialogData', 'palo_sbst', 'getSubsetDialogData', arguments);
};

_prototype.getSubsetListByXML = function ()
{
	return this._dispatch('getSubsetListByXML', 'palo_sbst', 'getSubsetListByXML', arguments);
};

_prototype.savePaloSubset = function ()
{
	return this._dispatch('savePaloSubset', 'palo_sbst', 'savePaloSubset', arguments);
};

_prototype.deletePaloSubset = function ()
{
	return this._dispatch('deletePaloSubset', 'palo_sbst', 'deletePaloSubset', arguments);
};

_prototype.renamePaloSubset = function ()
{
	return this._dispatch('renamePaloSubset', 'palo_sbst', 'renamePaloSubset', arguments);
};

_prototype.getCubesWithDims = function ()
{
	return this._dispatch('getCubesWithDims', 'palo_view', 'getCubesWithDims', arguments);
};

//palo_view
_prototype.getPasteViewInitData = function ()
{
	return this._dispatch('getPasteViewInitData', 'palo_view', 'getPasteViewInitData', arguments);
};

_prototype.getPVColRowElems = function ()
{
	return this._dispatch('getPVColRowElems', 'palo_view', 'getPVColRowElems', arguments);
};

