<?php

/*
 * \brief RPC routines for handling Palo Dailogs (Palo Wizard, Choose Elements, Select Elements, Paset Function, Palo Import, etc.)
 *
 * \file palo_misc.php
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: palo_misc.php 4747 2011-03-22 15:03:51Z mladent $
 *
 */

class palo_misc
{
	/* private methods */
	private static function _getElemPaths($conn, $dbName, $dimName, $elemName, $singlePath)
	{
		$retArr = array();

		// allways retrive first parent of this element if element have more then one parent
		if ($numOfParents = palo_eparentcount($conn, $dbName, $dimName, $elemName))
		{
			for ($i = 1; $i <= $numOfParents; $i++)
			{
				$parent = palo_eparentname($conn, $dbName, $dimName, $elemName, $i);
				$preParentPaths = self::_getElemPaths($conn, $dbName, $dimName, $parent, $singlePath);

				foreach($preParentPaths as $preParentPath)
					$retArr[] = $preParentPath . '/' . $parent . '_' . $elemName;

				if ($singlePath)
					break;
			}
		}
		else
			$retArr[] = 'root_' . $elemName;

		return $retArr;
	}

	/* public methods */
	public static function getAttributedElems($connName, $dbName, $dimName, $attr, $fromId, $toId)
	{
		palo::paloCheckDbName($dbName);
		$conn = palo::palo_init($connName);
		$listElems = palo_dimension_list_elements($conn, $dbName, $dimName, true);

		$numOfElems = count($listElems);
		$listElemsOut = array();
		for ($i=$fromId; $i<$toId && $i<$numOfElems; $i++)
		{
			$listElemsOut[] = $listElems[$i];
			$listElemsOut[count($listElemsOut) - 1]['id'] = $listElems[$i]['name'];
			$listElemsOut[count($listElemsOut) - 1]['attr'] = $attr;
		}

		if ($attr != null)
		{
			$cubeName = '#_' . $dimName;
			$reqList = array();
			for ($i = 0; $i < count($listElemsOut); $i++)
				$reqList[$i] = $listElemsOut[$i]['name'];

			array_unshift($reqList, count($reqList), 1);

			$listAttributedElemNames = palo_datav($conn, $dbName, $cubeName, $attr, $reqList);
			array_splice($listAttributedElemNames, 0, 2);

			for ($i = 0; $i < count($listElemsOut); $i++)
				if (!empty($listAttributedElemNames[$i]))
					$listElemsOut[$i]['name'] = $listAttributedElemNames[$i];
		}
		palo::palo_disconnect($conn);

		return array(array($fromId, $toId, count($listElemsOut), $numOfElems, $attr), $listElemsOut);
	}

	public static function searchElems($connName, $dbName, $dimName, $elemList, $attr =null, $singlePath =false)
	{
		$listSize = count($elemList);
		$pathList = array();

		for ($i=0; $i<$listSize; $i++)
		{
			$res = self::searchElem($connName, $dbName, $dimName, $elemList[$i], $attr, $singlePath);
			if ($res[0] > 0)
				array_splice($pathList, count($pathList), 0, $res[1]);
		}

		return array(count($pathList), $pathList);
	}

	public static function searchElem($connName, $dbName, $dimName, $elemName, $attr =null, $singlePath =false)
	{
		palo::paloCheckDbName($dbName);
		$dimName = palo::adjustDimModeName($connName, $dbName, $dimName);
		$cubeName = '#_' . $dimName;
		$conn = palo::palo_init($connName);
		$listElems = palo_dimension_list_elements($conn, $dbName, $dimName);

		if ($attr != null)
		{
			$reqList = array();
			for ($i = 0; $i < count($listElems); $i++)
				$reqList[$i] = $listElems[$i]['name'];

			array_unshift($reqList, count($reqList), 1);

			$searchList = palo_datav($conn, $dbName, $cubeName, $attr, $reqList);
			array_splice($searchList, 0, 2);
		}

		// Wildcard character
		$hasWcStart = (strpos($elemName, '*') === 0);
		$hasWcEnd = (strrpos($elemName, '*') === (strlen($elemName) - 1));
		if ($hasWcStart)
			$elemName = substr($elemName, 1);
		if ($hasWcEnd)
			$elemName = substr($elemName, 0, -1);

		$numOfElems = ($attr != null) ? count($searchList) : count($listElems);
		$retArr = array();
		for ($i = 0; $i < $numOfElems; $i++)
		{
			$currElemName = ($attr != null) ? $searchList[$i] : $listElems[$i]['name'];
			if (
				( !$hasWcStart && !$hasWcEnd && strcasecmp($elemName, $currElemName) == 0 ) ||
				(  $hasWcStart && !$hasWcEnd && strcasecmp($elemName, substr($currElemName, strlen($currElemName) - strlen($elemName))) == 0 ) ||
				( !$hasWcStart &&  $hasWcEnd && strcasecmp($elemName, substr($currElemName, 0, strlen($elemName))) == 0 ) ||
				(  $hasWcStart &&  $hasWcEnd && stripos($currElemName, $elemName) !== false )
			)
			{
				$elemPaths = self::_getElemPaths($conn, $dbName, $dimName, $listElems[$i]['name'], $singlePath);
				foreach($elemPaths as &$elemPath)
					$retArr[] = '/root/' . $elemPath;

				if ($singlePath)
					break;
			}
		}

		palo::palo_disconnect($conn);

		return array(count($retArr), $retArr);
	}

	public static function getDimStringAttrs($connName, $dbName, $dimName)
	{
		palo::paloCheckDbName($dbName);

		if (!(strpos($dimName, '#_') === 0))
			$dimName = '#_' . $dimName . '_'; // settings for dimension attributes
		else
			return array();

		$conn = palo::palo_init($connName);
		$listElems = palo_dimension_list_elements($conn, $dbName, $dimName);
		palo::palo_disconnect($conn);

		$listElemsOut = array();
		for ($i=0; $i<count($listElems); $i++)
			if ($listElems[$i]['type'] == 'string')
				$listElemsOut[] = array('id' => $listElems[$i]['identifier'], 'name' => $listElems[$i]['name']);

		return $listElemsOut;
	}

	// *** SelectElements Dialog - Other Elements paste function *** //
	public static function handlerPutValuesOnGrid($settings, $data)
	{
		$retArr = array('cdrg', array('cm' => false), array($settings[0], $settings[1], (($settings[4]) ? 0 : 1)));
		foreach ($data as $dim)
		{
			$retArr[2][] = array(
				'v' => $dim,
				'a' => array('palo_pe' => array('type' => $settings[5]))
			);

			if ($settings[4])
				$retArr[2][2]++;
		}

		return array($retArr);
	}

	// *** PALO WIZARD *** //
	public static function createNewDb($inArr)
	{
		$connName = $inArr[0];
		$dbName = $inArr[1];

		$conn = palo::palo_init($connName);
		$listDB = palo_root_list_databases($conn);

		if (in_array($dbName, $listDB))
			throw new WSS_Exception('P1_15', array('db_name' => $dbName), 'Unabe to create new database.');

		try
		{
			if (!palo_root_add_database($conn, $dbName))
				throw new Exception();

			palo::palo_disconnect($conn);

			return true;
		}
		catch (Exception $e)
		{
			palo::palo_disconnect($conn);
			throw new WSS_Exception('P1_15', array('db_name' => $dbName), 'Unabe to create new database.');
		}
	}

	public static function deleteDb($inArr)
	{
		$connName = $inArr[0];
		$dbName = $inArr[1];

		$conn = palo::palo_init($connName);
		$listDB = palo_root_list_databases($conn);

		if (in_array($dbName, $listDB) && palo_root_delete_database($conn, $dbName))
		{
			palo::palo_disconnect($conn);
			return true;
		}
		palo::palo_disconnect($conn);

		throw new WSS_Exception('P1_17', array('db_name' => $dbName), 'Unabe to delete database.');
	}

	// *** PALO Rules functions *** //
	public static function getRules($settings)
	{
		$connName = $settings[0];
		$dbName = $settings[1];
		$cubeName = $settings[2];

		$conn = palo::palo_init($connName);
		$result = palo_cube_rules($conn, $dbName, $cubeName);
		palo::palo_disconnect($conn);

		return $result;
	}

	public static function createRule($inArr)
	{
		$settings = $inArr[0];
		$data = $inArr[1];

		$connName = $settings[0];
		$dbName = $settings[1];
		$cubeName = $settings[2];

		$conn = palo::palo_init($connName);
		$result = palo_cube_rule_create($conn, $dbName, $cubeName, $data['definition'], $data['extern_id'], $data['comment'], $data['activate']);
		palo::palo_disconnect($conn);

		return $result;
	}

	public static function deleteRule($inArr)
	{
		$settings = $inArr[0];
		$ruleId = $inArr[1];

		$connName = $settings[0];
		$dbName = $settings[1];
		$cubeName = $settings[2];

		$conn = palo::palo_init($connName);
		$result = palo_cube_rule_delete($conn, $dbName, $cubeName, $ruleId);
		palo::palo_disconnect($conn);

		return $result;
	}

	public static function modifyRule($inArr)
	{
		$settings = $inArr[0];
		$dataArr = $inArr[1]; // 0 = old rule, 1 = new rule

		$connName = $settings[0];
		$dbName = $settings[1];
		$cubeName = $settings[2];

		$conn = palo::palo_init($connName);
		$result = palo_cube_rule_modify($conn, $dbName, $cubeName, $dataArr[0]['identifier'], $dataArr[1]['def'], $dataArr[0]['extern_id'], $dataArr[1]['comment'], $dataArr[1]['active']);
		palo::palo_disconnect($conn);

		return $result;
	}

	// palo import methods
	public static function handlerImportPaloDataFunc($negativeLineNum)
	{
		$sessData =& palo::getSessionDataWS('palo_import');
		if (!empty($sessData))
		{
			$textFile = new TextFile();

			$conf = $sessData['conf'];

			$textFile->setSep($conf['sep']);
			$textFile->setPoint($conf['d_point']);
			$textFile->setHeader($conf['header']);

			// num_of_lines <- number of lines in file
			$textFile->importFileLine($sessData['file'], $sessData['num_of_lines'] - $negativeLineNum);

			// delete file in case of last import
			$lineNum = $negativeLineNum - (($conf['header']) ? 2 : 1);
			if ($lineNum == 0)
			{
				unlink($sessData['file']);
				unset($_SESSION['palo_import']);
			}

			return $textFile->genCmds();
		}
		else
			unset($_SESSION['palo_import']);
	}

	public static function doImportCleanup()
	{
		$sessData =& palo::getSessionDataWS('palo_import');

		if (!empty($sessData))
			unlink($sessData['file']);

		unset($_SESSION['palo_import']);

		return true;
	}
}

?>