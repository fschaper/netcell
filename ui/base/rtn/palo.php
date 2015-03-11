<?php

/*
 * @brief global RPC routines for Palo
 *
 * @file palo.php
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: palo.php 4721 2011-03-18 10:34:57Z mladent $
 *
 */

class palo
{
	// Last Palo error No. - P1_18

	/* Config Data */
	public static $conf = array(
		'filterDims' => array('#viewcolumns', '#viewrows', '#subsetrows', '#subsetcolumns', '#views', '#_USER_PROPERTIES_', '#_RIGHT_OBJECT_', '#_GROUP_PROPERTIES_', '#_ROLE_PROPERTIES_'),
		'filterCubes' => array('#views', '#_#viewcolumns', '#_#viewrows', '#_VIEW_LOCAL', '#_VIEW_GLOBAL', '#_GROUP_DIMENSION_DATA_#viewcolumns', '#_GROUP_DIMENSION_DATA_#viewrows'),
		'maxWinSize' => 200, // maximum nambers for window size
		'workingMode' => 'elements', // it's posible to be more 2 modes: attributes and subsets
		'pointToPixel' => 1.35,

		'colorHostDb' => '#A1BDDB',
		'colorPageElems' => '#DCE6F1',
		'colorData' => '#FFFFFF',
		'colorDataBorder' => '#D1D8E5',

		'pvMaxCols' => 257,
		'pvMaxRows' => 65537,

		'colStyle1' => 'background-color:#DCE6F1;',
		'colStyle2' => 'background-color:#A1BDDB;',
		'colStyle0' => 'background-color:#31659C;color:#FFFFFF;',

		'rowStyle1' => 'background-color:#E0E0E0;',
		'rowStyle2' => 'background-color:#BEBEBE;',
		'rowStyle0' => 'background-color:#808080;color:#FFFFFF;',

		'styleConsolidated' => 'font-weight:bold;',
		'styleNormal' => 'font-weight:normal;',
		'wrapText' => 'white-space:pre-wrap;',

		'handlerExpandCollapsePasteView_inJS' => 'hnd_dblCpv',
		'getPasteViewInitData_inJS' => 'hnd_dblCpvOpen',
		'nofnc_openChooseElement_inJS' => 'hnd_dblCceOpen',
		'nofnc_openSelectElements_inJS' => 'hnd_dblCseOpen',
		'openPaloTE' => 'hnd_openPaloTE',

		'paloSubesetFuncSeparator' => ',',
		'paloSubesetFuncSeparatorArr' => ';',
		'paloAttrsSeparator' => ',',

		'paloSubsetGrammarFile' => '../../base/rtn/subset_grammar.xslt',
		'paloSubsetGrammarFile2' => '../../../base/rtn/subset_grammar.xslt',
		'paloSubsetQucikPreviewSize' => 4,
		'paloSubsetQucikPreviewListSize' => 20,

		'numOfElemsForFullTreeExpand' => 200
	);

	/* private methods */
	private static function &_getSessionDataWB($key)
	{
		$wbId = self::getWbId();

		if (!isset($_SESSION[$key]))
			$_SESSION[$key] = array();

		if (!isset($_SESSION[$key]))
			$_SESSION[$key][$wbId] = array();

		return $_SESSION[$key][$wbId];
	}

	private static function _loadPaloPreselect(&$sessData)
	{
		if (empty($sessData))
		{
			$res = json_decode(ccmd('[["bget","",[],["data"],{"e_type":"palo_pres"}]]'), true);
			if (isset($res[0]) && $res[0][0] && isset($res[0][1][0]) && isset($res[0][1][0]['data']))
				$sessData = $res[0][1][0]['data'];
		}
	}

	private static function _clearPresSess($wbId)
	{
		unset($_SESSION['palo_preselection'][$wbId]);

		if (empty($_SESSION['palo_preselection']))
			unset($_SESSION['palo_preselection']);
	}

	private static function _getConnRules($connName)
	{
		$aplcy = self::getAP($connName);

		// Rules Filter
		$rules = array(
			'database' => 0,
			'cube' => 0,
			'dimension' => 0,
			'dimension element' => 0,
			'rights' => 0,
			'rule' => 0
		);
		foreach($rules as $key => $val)
		{
			$ruleVal = ($aplcy != null) ? $aplcy->getRule($key) : 7; // 7 = read, write, delete
			if ($ruleVal > 0)
				$rules[$key] = $ruleVal;
		}

		return $rules;
	}

	private static function _useAttrNames(&$nodes, &$conn, $dbName, $dimName, $attr)
	{
		$reqList = array();
		for ($i = 0; $i < count($nodes); $i++)
			$reqList[$i] = $nodes[$i]['text'];

		array_unshift($reqList, count($reqList), 1);

		$listAttributedElemNames = palo_datav($conn, $dbName, '#_' . $dimName, $attr, $reqList);
		array_splice($listAttributedElemNames, 0, 2);

		for ($i = 0; $i < count($nodes); $i++)
			if (!empty($listAttributedElemNames[$i]))
				$nodes[$i]['text'] = $listAttributedElemNames[$i];
	}

	private static function _genTree(&$nodes, &$conn, $dbName, $dimName, $attr)
	{
		for($i=0; $i<count($nodes); $i++)
		{
			$node = &$nodes[$i];
			if (!$node['leaf'])
			{
				$listOfChilds = palo_element_list_consolidation_elements($conn, $dbName, $dimName, $node['text']);

				if (count($listOfChilds))
				{
					$node['children'] = array();
					foreach ($listOfChilds as $elem)
						$node['children'][] = array('text' => $elem['name'], 'id' => $node['name'] . '_' . $elem['name'], 'name' => $elem['name'], 'leaf' => ($elem['type'] != 'consolidated') , '_num_id' => $elem['identifier']);

					self::_genTree($node['children'], $conn, $dbName, $dimName, $attr);

					if ($attr != null)
						self::_useAttrNames($node['children'], $conn, $dbName, $dimName, $attr);
				}
			}
		}
	}

	/* public methods */
	public static function &getSessionDataWS($key)
	{
		$wsId = self::getWsId();
		$wbArr = &self::_getSessionDataWB($key);

		if (!isset($wbArr[$wsId]))
			$wbArr[$wsId] = array();

		return $wbArr[$wsId];
	}

	public static function unloadBookSess($wbId)
	{
		if (isset($_SESSION['palo_pasteview_states']) && isset($_SESSION['palo_pasteview_states'][$wbId]))
		{
			unset($_SESSION['palo_pasteview_states'][$wbId]);

			if (empty($_SESSION['palo_pasteview_states']))
				unset($_SESSION['palo_pasteview_states']);
		}

		if (isset($_SESSION['palo_preselection']) && isset($_SESSION['palo_preselection'][$wbId]))
			self::_clearPresSess($wbId);
	}

	public static function paloCheckDbName($dbName)
	{
		if ($dbName == null)
			throw new WSS_Exception('P1_0', null, 'Database name is not correct.');

		return true;
	}

	public static function get_config_conn()
	{
		if (!isset($_SESSION['accessPolicy']) || !is_resource($conn = $_SESSION['accessPolicy']->getConn()))
			throw new WSS_Exception('P1_11', null, 'Error at retreaving palo connection to config server.');

		return $conn;
	}

	public static function palo_init($connName)
	{
		try
		{
			$connInfo = self::getConnInfo($connName);

			$tmpErrRep = ini_get('error_reporting');
			error_reporting(0);
			palo_use_unicode(true);
			$conn = palo_init($connInfo['host'], $connInfo['port'], $connInfo['user'], $connInfo['pass']);
			error_reporting($tmpErrRep);

			if ($conn === '#NULL!')
				throw new Exception();

			palo_ping($conn);

			return $conn;
		}
		catch (WSS_Exception $wsse)
		{
			throw $wsse;
		}
		catch (Exception $e)
		{
			throw new WSS_Exception('P1_13', array('conn_name' => $connName), 'Unable to make connection for connection name: ' . $connName);
		}
	}

	public static function palo_disconnect($conn)
	{
		palo_ping($conn);
		palo_disconnect($conn);
	}

	// *** global ***
	public static function getWbId()
	{
		if (isset($_SESSION['wss']) && $_SESSION['wss']->curr_wbid != null)
			return $_SESSION['wss']->curr_wbid;

		throw new Exception('No workbook selected.');
	}

	public static function getWsId()
	{
		if (isset($_SESSION['wss']) && $_SESSION['wss']->curr_wsid != null)
			return $_SESSION['wss']->curr_wsid;

		throw new Exception('No sheet selected.');
	}

	public static function getConnInfo($connName)
	{
		// read connection data
		$connection = self::get_config_conn();
		$coordinates = array('name', 'type', 'description', 'host', 'port', 'username', 'password', 'active', 'useLoginCred');
		array_unshift($coordinates,  1, count($coordinates));
		$connData = palo_datav($connection, 'Config', '#_connections', $coordinates, $connName);
		self::palo_disconnect($connection);

		// check connection type
		if (strtoupper($connData[3]) != 'PALO')
			throw new WSS_Exception('P1_12', array('conn_name' => $connName), 'Bad PALO connection type for connection name: ' . $connName);

		return array(
			'host' => $connData[5],
			'port' => $connData[6],
			'user' => ($connData[10] == 0) ? $connData[7] : $_SESSION['accessPolicy']->getUser(),
			'pass' => ($connData[10] == 0) ? $connData[8] : $_SESSION['accessPolicy']->getPass()
		);
	}

	public static function getAP($connName)
	{
		$connInfo = self::getConnInfo($connName);
		if (CFG_PALO_HOST == $connInfo['host'] && CFG_PALO_PORT == $connInfo['port'])
			$aplcy = new AccessPolicy($connInfo['host'], $connInfo['port'], CFG_PALO_USER, CFG_PALO_PASS, $connInfo['user'], $connInfo['pass'], false);
		else
			return null;

		if (!is_resource($aplcy->getSuperConn()) || !$aplcy->reload())
			return null;

		return $aplcy;
	}

	public static function getServList()
	{
	    $connection = self::get_config_conn();
	    $dbName = 'Config';
		$cubeName = '#_connections';
		$dimName = 'connections';
		$prop = array('name', 'active', 'type');
		$properties = array(count($prop), 1);

		for ($i=0; $i<count($prop); $i++)
			array_push($properties, $prop[$i]);
		$result = palo_dimension_list_elements($connection, $dbName, $dimName, true);

		$connectionNames = $result;
		$coordinates = array(1, count($connectionNames));
		for ($i=0; $i<count($connectionNames); $i++)
			array_push($coordinates, $connectionNames[$i]['name']);

		$result = palo_datav($connection, $dbName, $cubeName, $properties, $coordinates);
		self::palo_disconnect($connection);

		$result = array_slice($result, 2);
		$connectons = array();
		$rowNmb = count($result)/3;
		for ($i=0; $i<$rowNmb; $i++)
			if (strtoupper($result[2*$rowNmb+$i]) == 'PALO')
				array_push($connectons, array($result[$i], '', (!!$result[$i+$rowNmb]), 'server', $result[$i], self::_getConnRules($result[$i])));
		// TODO: ^^ Instead of 'name' from #_connections cube, as ID should be used element name

		try
		{
			$preSelSess =& self::_getSessionDataWB('palo_preselection');
			self::_loadPaloPreselect($preSelSess);
			if (!empty($preSelSess))
				return array($connectons, $preSelSess);
			else
				self::_clearPresSess(self::getWbId());
		}
		catch (Exception $e)
		{
			if (isset($_SESSION['palo_preselection']))
				unset($_SESSION['palo_preselection']);
		}

		return array($connectons);
	}

	public static function setPreselectServDb($connName, $db_name)
	{
		$preSelSess =& self::_getSessionDataWB('palo_preselection');
		$preSelSess = array($connName, $db_name);

		// Save Palo Preselection to Core
		$res = json_decode(ccmd('[["bget","",[],["e_id"],{"e_type":"palo_pres"}]]'), true);
		if (isset($res[0]) && $res[0][0] && isset($res[0][1]) && isset($res[0][1][0]))
			$cmds = array(array('bupd', '', array($res[0][1][0]['e_id'] => array('data' => $preSelSess))));
		else
			$cmds = array(array('badd', '', array('e_type' => 'palo_pres', 'data' => $preSelSess)));

		return ccmd($cmds);
	}

	public static function getServListWithDBs($withSystemDB =false)
	{
		$servs = self::getServList();
		for ($i = (count($servs[0]) - 1); $i >= 0; $i--)
		{
			$serv = &$servs[0][$i];
			if ($serv[2])
			{
				$listDB = null;
				try
				{
					$conn = self::palo_init($serv[0]);
					$listDB = palo_root_list_databases($conn);
					self::palo_disconnect($conn);
				}
				catch (Exception $e)
				{
					$serv[2] = false;
				}

				if (is_array($listDB))
				{
					if ($withSystemDB)
						$listDB[] = 'System';

					for ($j = (count($listDB) - 1); $j>=0; $j--)
						array_splice($servs[0], $i + 1, 0, array(array(
																'id-' . $serv[0] . '-' . $j,
																$serv[0],
																false,
																'database',
																 $listDB[$j]
															))
						);
				}
			}
		}

		return $servs;
	}

	// *** Tree Panel ***
	public static function getTreeNodes()
	{
		// POST Attributes
		$elemName = isset($_POST['name']) ? $_POST['name'] : null;
		$elemName = stripslashes($elemName);
		$elemId = isset($_POST['_num_id']) ? $_POST['_num_id'] : null;

		// GET Attributes
		$connName = isset($_GET['servId']) ? $_GET['servId'] : null;
		$dbName = isset($_GET['dbName']) ? $_GET['dbName'] : null;
		$attr = isset($_GET['attr']) ? $_GET['attr'] : null;

		// MISC
		$dimName = isset($_POST['dimName']) ? $_POST['dimName'] : (isset($_GET['dimName']) ? $_GET['dimName'] : null);

		// POST Attributes for Server Side Paging
		$start = isset($_POST['start']) ? $_POST['start'] : null;
		$limit = isset($_POST['limit']) ? $_POST['limit'] : null;
		$total = isset($_POST['total']) ? $_POST['total'] : null;

		/*** for server side paging ***/
		// start : the start index of the children,when the node first expends,the start value is 0
		// limit : equals the jscode's pageSize,means the count of the node to show ervery time
		// total : the total count of the node's children,when the node first expends,the total parameter dosen't exist.

		$nodes = array();
		$dimName = self::adjustDimModeName($connName, $dbName, $dimName);

		if (($connName != null) && ($dbName != null) && ($dimName != null) && ($elemName != null))
		{
			$conn = self::palo_init($connName);

			// TODO: Change in Future when new version of Palo Server and Palo PHP API is widely used
			if (function_exists('palo_dimension_reduced_top_list_elements') && function_exists('palo_dimension_reduced_children_list_elements') && function_exists('palo_dimension_count_top_list_elements'))
			{
				if ($elemName == 'root')
				{
					$dimInfo = palo_dimension_info($conn, $dbName, $dimName); // index 2 - number of elements
					$getAll = intval($dimInfo[2]) < self::$conf['numOfElemsForFullTreeExpand'] || $start == null || $limit == null;

					$listElems = ($getAll) ? palo_dimension_reduced_top_list_elements($conn, $dbName, $dimName) : palo_dimension_reduced_top_list_elements($conn, $dbName, $dimName, $start, $limit);

					foreach ($listElems as $elem)
						$nodes[] = array('text' => $elem['name'], 'id' => $elemName . '_' . $elem['name'], 'name' => $elem['name'], 'leaf' => ($elem['type'] != 'consolidated'), '_num_id' => $elem['identifier']);

					if ($dimInfo[2] < self::$conf['numOfElemsForFullTreeExpand'])
						self::_genTree($nodes, $conn, $dbName, $dimName, $attr);

					if ($total == null && $start != null && $limit != null)
						$total = palo_dimension_count_top_list_elements($conn, $dbName, $dimName);
				}
				else
				{
					if ($elemId == null)
						$elemId = palo_get_element_id($conn, $dbName, $dimName, $elemName);
					$listElems = ($start != null && $limit != null) ? palo_dimension_reduced_children_list_elements($conn, $dbName, $dimName, $elemId, $start, $limit) : palo_dimension_reduced_children_list_elements($conn, $dbName, $dimName, $elemId);

					if ($total == null && $start != null && $limit != null)
						$total = palo_echildcount($conn, $dbName, $dimName, $elemName, true);

					foreach ($listElems as $elem)
						$nodes[] = array('text' => $elem['name'], 'id' => $elemName . '_' . $elem['name'], 'name' => $elem['name'], 'leaf' => ($elem['type'] != 'consolidated'), '_num_id' => $elem['identifier']);
				}
			}
			else
			{
				if ($elemName == 'root')
				{
					$listElems = palo_dimension_list_elements2($conn, $dbName, $dimName, true);

					foreach ($listElems as $elem)
						if ($elem['num_parents'] == 0)
							$nodes[] = array('text' => $elem['name'], 'id' => $elemName . '_' . $elem['name'], 'name' => $elem['name'], 'leaf' => ($elem['type'] != 'consolidated'), '_num_id' => $elem['identifier']);

					if (count($listElems) < self::$conf['numOfElemsForFullTreeExpand'] && count($nodes) < self::$conf['numOfElemsForFullTreeExpand'])
						self::_genTree($nodes, $conn, $dbName, $dimName, $attr);
					else if ($start != null && $limit != null)
					{
						$total = count($nodes);
						$nodes = array_slice($nodes, $start, $limit);
					}
				}
				else
				{
					$listElems = palo_element_list_consolidation_elements($conn, $dbName, $dimName, $elemName);

					if ($start != null && $limit != null)
					{
						$total = count($listElems);
						$listElems = array_slice($listElems, $start, $limit);
					}

					foreach ($listElems as $elem)
						$nodes[] = array('text' => $elem['name'], 'id' => $elemName . '_' . $elem['name'], 'name' => $elem['name'], 'leaf' => ($elem['type'] != 'consolidated'), '_num_id' => $elem['identifier']);
				}
			}

			if ($attr != null)
				self::_useAttrNames($nodes, $conn, $dbName, $dimName, $attr);

			self::palo_disconnect($conn);
		}

		if ($start != null && $limit != null)
			return array('total' => ( ($total != null && !empty($total)) ? $total : count($nodes) ), 'nodes' => $nodes);
		else
			return $nodes;
	}

	public static function getDBs($connName)
	{
		try
		{
			$conn = self::palo_init($connName);
			$listDB = palo_root_list_databases($conn);
			self::palo_disconnect($conn);

			if (!is_array($listDB))
				throw new WSS_Exception('P1_7', array('conn_name' => $connName), 'Unable to get list of Databases.');

			array_unshift($listDB, $connName);

			return $listDB;
		}
		catch (Exception $e)
		{
			throw new WSS_Exception('P1_7', array('conn_name' => $connName), 'Unable to get list of Databases.');
		}
	}

	public static function getDims($connName, $dbName, $dimType)
	{
		$retList = array();
		$srvRules = self::_getConnRules($connName);
		if ($srvRules['dimension'] & 1)
		{
			self::paloCheckDbName($dbName);

			// $dimType .. data, user, att
			$dimType = ($dimType == 2) ? 0 : $dimType;
			if ($dbName == 'System')
				$dimType = 1;

			$conn = self::palo_init($connName);
			$listDims = palo_database_list_dimensions($conn, $dbName, $dimType);
			self::palo_disconnect($conn);

			foreach ($listDims as $dim)
				if (!in_array($dim, self::$conf['filterDims']))
					 $retList[] = $dim;

			$_SESSION['servid_' . $connName][$dbName] = null;
		}

		return $retList;
	}

	public static function getCubeNames($connName, $dbName, $cubeType, $onlyWithAttr =false)
	{
		self::paloCheckDbName($dbName);
		$conn = self::palo_init($connName);

		$listCubes = palo_database_list_cubes($conn, $dbName, $cubeType);

		if ($cubeType == 0 && is_array($listCubes))
		{
			// GPU cubes into list
			$listCubesGPU = palo_database_list_cubes($conn, $dbName, 4);
			$listCubes = array_merge($listCubes, $listCubesGPU);
		}

		if ($onlyWithAttr && (($cubeType == 2) || ($cubeType == 1)))
		{
			$newCubeList = array();
			for ($i=0; $i<count($listCubes); $i++)
			{
				$cInfo =  palo_cube_info($conn, $dbName, $listCubes[$i]);
				if ($cInfo['number_cells'] > 0)
					$newCubeList[] = $listCubes[$i];
			}

			$listCubes = $newCubeList;
		}
		self::palo_disconnect($conn);

		$newCubeList = array();
		for ($i=0; $i<count($listCubes); $i++)
			if (!in_array($listCubes[$i], self::$conf['filterCubes']))
				$newCubeList[] = $listCubes[$i];

		return $newCubeList;
	}

	public static function getCubeDims($connName, $dbName, $cubeName)
	{
		self::paloCheckDbName($dbName);
		$conn = self::palo_init($connName);
		$listDims = palo_cube_list_dimensions($conn, $dbName, $cubeName);
		self::palo_disconnect($conn);

		return $listDims;
	}

	public static function setWorkingMode($connName, $dbName, $dimName, $newMode)
	{
		$_SESSION['servid_' . $connName][$dbName][$dimName]['workingMode'] = $newMode;

		return $newMode;
	}

	public static function adjustDimModeName($connName, $dbName, $dimName)
	{
		if (!isset($_SESSION['servid_' . $connName][$dbName][$dimName]['workingMode']))
			$_SESSION['servid_' . $connName][$dbName][$dimName]['workingMode'] = self::$conf['workingMode'];

		if ($_SESSION['servid_' . $connName][$dbName][$dimName]['workingMode'] == 'attributes') //attributes
			return '#_' . $dimName . '_';

		return $dimName;
	}
}

?>