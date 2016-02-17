/*
 * \brief backend Studio RPC wrapper class
 *
 * \file Studio.js
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
 * SVN: $Id: Studio.js 4905 2011-04-28 14:18:53Z andrejv $
 *
 */

Jedox.backend.rpc.Studio = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (onSuccess, onError, onTimeout)
	{
		Jedox.backend.rpc.Studio.parent.constructor.call(this, onSuccess, onError, onTimeout);

		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.backend.rpc.Studio, Jedox.backend.RPCWrapper);

//public static fields

// public fields & methods
var _prototype = Jedox.backend.rpc.Studio.prototype;

_prototype.verifySess = function ()
{
	return this._dispatch('verifySess', 'Studio', 'verifySess', arguments);
};

_prototype.syncPaloConnData = function ()
{
	return this._dispatch('syncPaloConnData', 'Studio', 'syncPaloConnData', arguments);
};

_prototype.getUserCreds = function ()
{
	return this._dispatch('getUserCreds', 'Studio', 'getUserCreds', arguments);
};

_prototype.getPrefs = function ()
{
	return this._dispatch('getPrefs', 'Studio', 'getPrefs', arguments);
};

_prototype.setPrefs = function ()
{
	return this._dispatch('setPrefs', 'Studio', 'setPrefs', arguments);
};

_prototype.removePrefs = function ()
{
	return this._dispatch('removePrefs', 'Studio', 'removePrefs', arguments);
};

_prototype.removeUserPrefGroupsFromSession = function ()
{
	return this._dispatch('removeUserPrefGroupsFromSession', 'Studio', 'removeUserPrefGroupsFromSession', arguments);
};

_prototype.getAllConnections = function ()
{
	return this._dispatch('getAllConnections', 'Studio', 'getAllConnections', arguments);
};

_prototype.getPaloConns = function ()
{
	return this._dispatch('getPaloConns', 'Studio', 'getPaloConns', arguments);
};

_prototype.isAdminConn = function ()
{
	return this._dispatch('isAdminConn', 'Studio', 'isAdminConn', arguments);
};

_prototype.getConnection = function ()
{
	return this._dispatch('getConnection', 'Studio', 'getConnection', arguments);
};

_prototype.getConnPerms4UGroup = function ()
{
	return this._dispatch('getConnPerms4UGroup', 'Studio', 'getConnPerms4UGroup', arguments);
};

_prototype.testConnection = function ()
{
	return this._dispatch('testConnection', 'Studio', 'testConnection', arguments);
};

_prototype.getDefaultLocalPath = function ()
{
	return this._dispatch('getDefaultLocalPath', 'Studio', 'getDefaultLocalPath', arguments);
};

_prototype.getHierarchyPropertiesData = function ()
{
	return this._dispatch('getHierarchyPropertiesData', 'Studio', 'getHierarchyPropertiesData', arguments);
};

_prototype.setHierarchyPropertiesData = function ()
{
	return this._dispatch('setHierarchyPropertiesData', 'Studio', 'setHierarchyPropertiesData', arguments);
};

_prototype.getGroupPropertiesData = function ()
{
	return this._dispatch('getGroupPropertiesData', 'Studio', 'getGroupPropertiesData', arguments);
};

_prototype.setGroupPropertiesData = function ()
{
	return this._dispatch('setGroupPropertiesData', 'Studio', 'setGroupPropertiesData', arguments);
};

_prototype.removeFromSessionCurrGH = function ()
{
	return this._dispatch('removeFromSessionCurrGH', 'Studio', 'removeFromSessionCurrGH', arguments);
};

_prototype.getElementPath = function ()
{
	return this._dispatch('getElementPath', 'Studio', 'getElementPath', arguments);
};

_prototype.getReferenceNode = function ()
{
	return this._dispatch('getReferenceNode', 'Studio', 'getReferenceNode', arguments);
};

_prototype.getHyperlinkURL = function ()
{
	return this._dispatch('getHyperlinkURL', 'Studio', 'getHyperlinkURL', arguments);
};

_prototype.setHyperlinkPropertiesData = function ()
{
	return this._dispatch('setHyperlinkPropertiesData', 'Studio', 'setHyperlinkPropertiesData', arguments);
};

_prototype.setURLPluginPropertiesData = function ()
{
	return this._dispatch('setURLPluginPropertiesData', 'Studio', 'setURLPluginPropertiesData', arguments);
};

_prototype.getURLPluginURL = function ()
{
	return this._dispatch('getURLPluginURL', 'Studio', 'getURLPluginURL', arguments);
};

_prototype.getNodeName = function ()
{
	return this._dispatch('getNodeName', 'Studio', 'getNodeName', arguments);
};

_prototype.getFramesetData = function ()
{
	return this._dispatch('getFramesetData', 'Studio', 'getFramesetData', arguments);
};

_prototype.setFramesetPropertiesData = function ()
{
	return this._dispatch('setFramesetPropertiesData', 'Studio', 'setFramesetPropertiesData', arguments);
};

_prototype.getNodePropertiesData = function ()
{
	return this._dispatch('getNodePropertiesData', 'Studio', 'getNodePropertiesData', arguments);
};

_prototype.fetchTagged = function ()
{
	return this._dispatch('fetchTagged', 'Studio', 'fetchTagged', arguments);
};

_prototype.getFSProps = function ()
{
	return this._dispatch('getFSProps', 'Studio', 'getFSProps', arguments);
};

_prototype.getExternURI = function ()
{
	return this._dispatch('getExternURI', 'Studio', 'getExternURI', arguments);
};

_prototype.addRecent = function ()
{
	return this._dispatch('addRecent', 'Studio', 'addRecent', arguments);
};

_prototype.getPerms4UGroup = function ()
{
	return this._dispatch('getPerms4UGroup', 'Studio', 'getPerms4UGroup', arguments);
};

_prototype.getNodePermission = function ()
{
	return this._dispatch('getNodePermission', 'Studio', 'getNodePermission', arguments);
};

_prototype.setNodePemission = function ()
{
	return this._dispatch('setNodePemission', 'Studio', 'setNodePemission', arguments);
};

_prototype.refreshNodes = function ()
{
	return this._dispatch('refreshNodes', 'Studio', 'refreshNodes', arguments);
};

_prototype.getNodeHyperlinkPropertiesData = function ()
{
	return this._dispatch('getNodeHyperlinkPropertiesData', 'Studio', 'getNodeHyperlinkPropertiesData', arguments);
};

_prototype.treeSetGroup = function ()
{
	return this._dispatch('treeSetGroup', 'Studio', 'treeSetGroup', arguments);
};

_prototype.treeGetGroup = function ()
{
	return this._dispatch('treeGetGroup', 'Studio', 'treeGetGroup', arguments);
};

_prototype.treeSetHierarchy = function ()
{
	return this._dispatch('treeSetHierarchy', 'Studio', 'treeSetHierarchy', arguments);
};

_prototype.treeGetHierarchy = function ()
{
	return this._dispatch('treeGetHierarchy', 'Studio', 'treeGetHierarchy', arguments);
};

_prototype.treeMngGroup = function ()
{
	return this._dispatch('treeMngGroup', 'Studio', 'treeMngGroup', arguments);
};

_prototype.treeMngHierarchy = function ()
{
	return this._dispatch('treeMngHierarchy', 'Studio', 'treeMngHierarchy', arguments);
};

_prototype.treeMngNode = function ()
{
	return this._dispatch('treeMngNode', 'Studio', 'treeMngNode', arguments);
};

_prototype.treeNodeDelMap = function ()
{
	return this._dispatch('treeNodeDelMap', 'Studio', 'treeNodeDelMap', arguments);
};

_prototype.treeNodeMap = function ()
{
	return this._dispatch('treeNodeMap', 'Studio', 'treeNodeMap', arguments);
};

_prototype.treeDump = function ()
{
	return this._dispatch('treeDump', 'Studio', 'treeDump', arguments);
};

_prototype.getReferrers = function ()
{
	return this._dispatch('getReferrers', 'Studio', 'getReferrers', arguments);
};

_prototype.getResources = function ()
{
	return this._dispatch('getResources', 'Studio', 'getResources', arguments);
};

_prototype.getDependents = function ()
{
	return this._dispatch('getDependents', 'Studio', 'getDependents', arguments);
};

_prototype.setResources = function ()
{
	return this._dispatch('setResources', 'Studio', 'setResources', arguments);
};

_prototype.removeDependent = function ()
{
	return this._dispatch('removeDependent', 'Studio', 'removeDependent', arguments);
};

_prototype.addDependent = function ()
{
	return this._dispatch('addDependent', 'Studio', 'addDependent', arguments);
};

_prototype.getDDSTreeNodes = function ()
{
	return this._dispatch('getDDSTreeNodes', 'Studio', 'getDDSTreeNodes', arguments);
};

_prototype.getListByPaloPath = function ()
{
	return this._dispatch('getListByPaloPath', 'Studio', 'getListByPaloPath', arguments);
};

_prototype.getMappedTreeNodes = function ()
{
	return this._dispatch('getMappedTreeNodes', 'Studio', 'getMappedTreeNodes', arguments);
};

_prototype.getUsedVariables = function ()
{
	return this._dispatch('getUsedVariables', 'Studio', 'getUsedVariables', arguments);
};

_prototype.getSNodeInScope = function ()
{
	return this._dispatch('getSNodeInScope', 'Studio', 'getSNodeInScope', arguments);
};

_prototype.getNodeInThisScope = function ()
{
	return this._dispatch('getNodeInThisScope', 'Studio', 'getNodeInThisScope', arguments);
};

_prototype.getTWorkbook = function ()
{
	return this._dispatch('getTWorkbook', 'Studio', 'getTWorkbook', arguments);
};

_prototype.getChildTempVars = function ()
{
	return this._dispatch('getChildTempVars', 'Studio', 'getChildTempVars', arguments);
};

_prototype.sortVariables = function ()
{
	return this._dispatch('sortVariables', 'Studio', 'sortVariables', arguments);
};

_prototype.getDefRepsByGroup = function ()
{
	return this._dispatch('getDefRepsByGroup', 'Studio', 'getDefRepsByGroup', arguments);
};

_prototype.setDefRepsByGroup = function ()
{
	return this._dispatch('setDefRepsByGroup', 'Studio', 'setDefRepsByGroup', arguments);
};

_prototype.setFilesUserView = function ()
{
	return this._dispatch('setFilesUserView', 'Studio', 'setFilesUserView', arguments);
};
