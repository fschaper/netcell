<?php

/*
 * \brief RPC routines for handling Palo View
 *
 * \file palo_view.php
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
 * SVN: $Id: palo_view.php 5070 2011-06-21 10:04:02Z mladent $
 *
 */

class palo_view
{
	/* private methods */
	private static function _loadPasteViewData(&$sessData, $pvId)
	{
		if (!isset($sessData[$pvId]))
		{
			/* Backward Compatibility - 2010.07.09 */
			$res = json_decode(ccmd('[["wget","",[],["e_id","map"],{"e_type":"palo"}]]'), true);
			if (isset($res[0]) && $res[0][0] && isset($res[0][1]) && isset($res[0][1][0]['map']))
			{
				$wsData = unserialize(gzuncompress(base64_decode($res[0][1][0]['map'])));
				foreach ($wsData['palo_pasteview_states'] as $locPvId => $pvData)
					$wsData[$locPvId] = $pvData;
				unset($wsData['palo_pasteview_states']);

				// Stored data in Session
				$sessData = $wsData;

				// Store in Core (wsels) with new format and delete old wsel
				$pvWselIds = array();
				$resPvs = json_decode(ccmd('[["wget","",[],["e_id","pv_id"],{"e_type":"palo_pv"}]]'), true);
				if (isset($resPvs[0]) && $resPvs[0][0])
					foreach ($resPvs[0][1] as $pvWsel)
						$pvWselIds[$pvWsel['pv_id']] = $pvWsel['e_id'];

				$cmds = array();
				foreach ($sessData as $locPvId => $pvData)
				{
					if (isset($pvWselIds[$locPvId]))
						$cmds[] = array('wupd', '', array($pvWselIds[$locPvId] => array('payload' => base64_encode(gzcompress(serialize($pvData), 1)))));
					else
						$cmds[] = array('wadd', '', array(
							'e_type' => 'palo_pv',
							'pv_id' => $locPvId,
							'n_location' => // This is not best solution for n_location (But this will be used only for realy old saved workbooks)
								'=' .
								self::_cord2Excel($pvData[0][0], $pvData[0][1]) .
								':' .
								self::_cord2Excel($pvData[0][2], $pvData[0][3]),
							'payload' => base64_encode(gzcompress(serialize($pvData), 1))
						));
				}

				// Delete old Format
				$cmds[] = array('wdel', '', array($res[0][1][0]['e_id']));

				// Exec Commands for update/add paste view data and delete old storage wsel
				ccmd($cmds);
			}
			/* END - Backward Compatibility */

			// LOAD Session from Single PasteView
			else
			{
				$resPvs = json_decode(ccmd('[["wget","",[],["payload"],{"e_type":"palo_pv","pv_id":"' . $pvId . '"}]]'), true);

				if (isset($resPvs[0]) && $resPvs[0][0] && isset($resPvs[0][1]) && isset($resPvs[0][1][0]['payload']))
					$sessData[$pvId] = unserialize(gzuncompress(base64_decode($resPvs[0][1][0]['payload'])));
			}
		}
	}

	private static function _clearPvSess()
	{
		unset($_SESSION['palo_pasteview_states'][palo::getWbId()][palo::getWsId()]);

		if (empty($_SESSION['palo_pasteview_states'][palo::getWbId()]))
			unset($_SESSION['palo_pasteview_states'][palo::getWbId()]);

		if (empty($_SESSION['palo_pasteview_states']))
			unset($_SESSION['palo_pasteview_states']);
	}

	private static function _cord2Excel($x, $y, $mode =3)
	{
		if ($x > 26)
			$letters = chr(floor(($x - 1) / 26) + 64) . chr((($x - 1) % 26) + 65);
		else
			$letters = chr($x + 64);

		return (($mode & 2) ? '$' : '') . $letters . (($mode & 1) ? '$' : '') . $y;
	}

	private static function _excel2Cord($cell)
	{
		$cell = str_replace('$', '', strtoupper($cell));

		preg_match('/[0-9]+/', $cell, $res);
		$row = intval($res[0]);

		preg_match('/[a-zA-Z]+/', $cell, $res);
		$col = $res[0];

		if (strlen($col) == 2)
			$col = (ord($col[0]) - 64) * 26 + ord($col[1]) - 64;
		else
			$col = ord($col[0]) - 64;

		return array($col, $row);
	}

	private static function _doZeroSuppression($conn, $pvData, &$currDim)
	{
		$dbName = $pvData[0][3];
		$cubeName = $pvData[0][4];
		$dimName = $currDim[0];
		$listToFilter = &$currDim[1];

		// gen SubCube Element list
		$cubeDims = palo_cube_list_dimensions($conn, $dbName, $cubeName);
		$cubeDimsIndexes = array_flip($cubeDims);

		$cubeDims[$cubeDimsIndexes[$dimName]] = NULL;
		for ($stIndex = 1; $stIndex <= 3; $stIndex++)
			foreach ($pvData[$stIndex] as $dim)
				if ($dim[0] != $dimName)
				{
					if ($dim[1] == null)
						$dim[1] = self::_hpv_getElems($conn, $dbName, $dim, ($stIndex == 1) ? 1 : NULL);

					$elems = array();
					foreach ($dim[1] as $elem)
						$elems[] = $elem[0];

					$cubeDims[$cubeDimsIndexes[$dim[0]]] = (count($elems) != 1) ? $elems : $elems[0];
				}
		array_unshift($cubeDims, $cubeName);

		$subcube = call_user_func_array('palo_subcube', $cubeDims);
		$ssList = palo_subset($conn, $dbName, $dimName, NULL, NULL, palo_dfilter($subcube, array("<>", 0), NULL, NULL, NULL, 4), NULL, NULL, NULL, NULL, palo_sort(0, 0, NULL, 0, NULL, 0, 0));
		$ssList = array_merge($ssList, palo_subset($conn, $dbName, $dimName, NULL, NULL, palo_dfilter($subcube, array("<>", ""), NULL, NULL, NULL, 6), NULL, NULL, NULL, NULL, palo_sort(0, 0, NULL, 0, NULL, 0, 0)));

		$smplList = array();
		foreach ($ssList as $elem)
			$smplList[] = $elem['name'];

		for ($i = 0; $i < count($listToFilter); $i++)
			if (!in_array($listToFilter[$i][0], $smplList))
				array_splice($listToFilter, $i--, 1);
	}

	private static function _packStyle(&$inRetArr, &$cell, $currX, $currY, $type, &$stylesPacks, $style)
	{
		$currPos = ($type == 1) ? $currY : $currX;

		if (isset($stylesPacks[$style]))
		{
			$numOfPackes = count($stylesPacks[$style]);
			$packFound = false;
			for ($i = 0; $i < $numOfPackes; $i++)
			{
				$stylePack = &$stylesPacks[$style][$i];
				if ($stylePack[2 + $type] == $currPos - 1)
				{
					if (isset($stylePack[4]))
					{
						unset($inRetArr[0][$stylePack[4]][3]['s']);
						unset($stylePack[4]);
					}
					$stylePack[2 + $type] = $currPos;
					$packFound = true;
					break;
				}
			}

			if (!$packFound)
			{
				$stylesPacks[$style][] = array( $currX, $currY, $currX, $currY, count($inRetArr[0]) );
				$cell[3]['s'] = $style;
			}
		}
		else
		{
			$stylesPacks[$style] = array( array( $currX, $currY, $currX, $currY, count($inRetArr[0]) ) );
			$cell[3]['s'] = $style;
		}
	}

	private static function _addStylePacks(&$stylesPacks, &$retArr)
	{
		foreach($stylesPacks as $style => $packs)
			foreach ($packs as $rngInfo)
				if ($rngInfo[0] < $rngInfo[2] || $rngInfo[1] < $rngInfo[3])
					$retArr[] = array('cdrn', array('cm' => true), array($rngInfo[0], $rngInfo[1], $rngInfo[2], $rngInfo[3], array('s' => $style)));
	}

	private static function _hpv_addRow($inConn, $connName, $inDbName, $wrapText, $inRetArr, $inServDbStr, $inRowDims, $rowId, $startX, $startY, $relativeX, $relativeY, $pasteViewId, $hasIndent, $dialogOnDblClk, $stylesPacks)
	{
		$tmpArr = self::_hpv_getElems($inConn, $inDbName, $inRowDims[$rowId]);
		$currX = $startX;
		$currY = $startY;
		$totalNumOfRows = count($inRowDims);

		foreach ($tmpArr as $elem)
		{
			if (((isset($elem[3])) ? $elem[3] : true))
			{
				$indent = (($hasIndent) ? (palo_eindent($inConn, $inDbName, $inRowDims[$rowId][0], $elem[0]) - 1) : 0);
				$fncName = '=PALO.ENAME(' . $inServDbStr . palo::$conf['paloAttrsSeparator'] . '"' . $inRowDims[$rowId][0] . '"' . palo::$conf['paloAttrsSeparator'] . '"' . $elem[0] . '"' . palo::$conf['paloAttrsSeparator'] . '1' . palo::$conf['paloAttrsSeparator'] . '"' . $elem[0] . '"' . palo::$conf['paloAttrsSeparator'] . '"' . ( (!empty($elem[1])) ? $elem[1] : '' ) . '")';
				$cell = array($currX, $currY, 1,
					array(  'v' => $fncName,
							'a' => array('palo_pe' => array('type' => 'dim', 'name' => $inRowDims[$rowId][0]))
					)
				);
				if ($dialogOnDblClk)
					$cell[3]['a']['dblclick'] = array(
						palo::$conf['nofnc_openSelectElements_inJS'],
						array(
							'mode' => 2,
							'pv_id' => $pasteViewId,
							'serv_id' => $connName,
							'db_name' => $inDbName,
							'dim_name' => $inRowDims[$rowId][0],
							'orient_type' => 3,
							'cr_index' => $rowId,
							'pos' => array($currX - $relativeX, $currY - $relativeY)
						)
					);
				else if ($elem[2] == 'C')
					$cell[3]['a']['dblclick'] = array(palo::$conf['handlerExpandCollapsePasteView_inJS'], $currX - $relativeX, $currY - $relativeY, $pasteViewId, $inRowDims[$rowId][0], $elem[0]);
				else
					$cell[3]['a']['dblclick'] = "";

				// style packing
				$style = (($elem[2] == 'C') ? palo::$conf['styleConsolidated'] : palo::$conf['styleNormal']) . palo::$conf['colStyle' . (($totalNumOfRows - $rowId) % 3)];
				if ($indent > 0)
					$style .= 'text-indent:' . $indent . 'em;';
				if ($wrapText)
					$style .= palo::$conf['wrapText'];
				self::_packStyle($inRetArr, $cell, $currX, $currY, 1, $stylesPacks, $style);

				if (!empty($elem[1]))
					$cell[3]['o'] = ';;;"' .  self::_hpv_getAttrElem($inConn, $inDbName, $inRowDims[$rowId][0], $elem[1], $elem[0]) . '"';

				$inRetArr[0][] = $cell;

				// calculate for subrows
				if ($totalNumOfRows > ($rowId + 1))
				{
					$lastId = self::_hpv_addRow($inConn, $connName, $inDbName, $wrapText, &$inRetArr, $inServDbStr, $inRowDims, $rowId + 1, $currX + 1, $currY, $relativeX, $relativeY, $pasteViewId, $hasIndent, $dialogOnDblClk, &$stylesPacks);
					if (($lastId - 1) > $currY)
						$inRetArr[] = array('cdrn', array('cm' => false), array($currX, $currY+1, $currX, $lastId - 1, array('v' => '=' . self::_cord2Excel($currX, $currY, 0),
						'o' => ';;;" "'
					)));
					$currY = $lastId;
				}
				else
					$currY++;

				if ($currY >= palo::$conf['pvMaxRows'])
					return $currY;
			}
		}

		return $currY;
	}

	private static function _hpv_addCol($inConn, $connName, $inDbName, $wrapText, $inRetArr, $inServDbStr, $inColDims, $colId, $startX, $startY, $relativeX, $relativeY, $pasteViewId, $dialogOnDblClk, $stylesPacks)
	{
		$tmpArr = self::_hpv_getElems($inConn, $inDbName, $inColDims[$colId]);
		$currX = $startX;
		$currY = $startY;
		$totalNumOfCols = count($inColDims);

		foreach ($tmpArr as $elem)
		{
			if (((isset($elem[3])) ? $elem[3] : true))
			{
				$fncName = '=PALO.ENAME(' . $inServDbStr . palo::$conf['paloAttrsSeparator'] . '"' . $inColDims[$colId][0] . '"' . palo::$conf['paloAttrsSeparator'] . '"' . $elem[0] . '"' . palo::$conf['paloAttrsSeparator'] . '1' . palo::$conf['paloAttrsSeparator'] . '"' . $elem[0] . '"' . palo::$conf['paloAttrsSeparator'] . '"' . ( (!empty($elem[1])) ? $elem[1] : '' ) . '")';
				$cell = array($currX, $currY, 1,
					array(  'v' => $fncName,
							'a' => array('palo_pe' => array('type' => 'dim', 'name' => $inColDims[$colId][0]))
					)
				);
				if ($dialogOnDblClk)
					$cell[3]['a']['dblclick'] = array(
						palo::$conf['nofnc_openSelectElements_inJS'],
						array(
							'mode' => 2,
							'pv_id' => $pasteViewId,
							'serv_id' => $connName,
							'db_name' => $inDbName,
							'dim_name' => $inColDims[$colId][0],
							'orient_type' => 2,
							'cr_index' => $colId,
							'pos' => array($currX - $relativeX, $currY - $relativeY)
						)
					);
				else if ($elem[2] == 'C')
					$cell[3]['a']['dblclick'] = array(palo::$conf['handlerExpandCollapsePasteView_inJS'], $currX - $relativeX, $currY - $relativeY, $pasteViewId, $inColDims[$colId][0], $elem[0]);
				else
					$cell[3]['a']['dblclick'] = "";

				// styles packing
				$style = (($elem[2] == 'C') ? palo::$conf['styleConsolidated'] : palo::$conf['styleNormal']) . palo::$conf['rowStyle' . (($totalNumOfCols - $colId) % 3)];
				if ($wrapText)
					$style .= palo::$conf['wrapText'];
				self::_packStyle($inRetArr, $cell, $currX, $currY, 0, $stylesPacks, $style);

				if (!empty($elem[1]))
					$cell[3]['o'] = ';;;"' .  self::_hpv_getAttrElem($inConn, $inDbName, $inColDims[$colId][0], $elem[1], $elem[0]) . '"';

				if ($totalNumOfCols > ($colId + 1))
				{
					$lastId = self::_hpv_addCol($inConn, $connName, $inDbName, $wrapText, &$inRetArr, $inServDbStr, $inColDims, $colId + 1, $currX, $currY + 1, $relativeX, $relativeY, $pasteViewId, $dialogOnDblClk, &$stylesPacks);
					if (($lastId - 1) > $currX)
						$inRetArr[] = array('cdrn', array('cm' => false), array($currX+1, $currY, $lastId - 1, $currY, array('v' => '=' . self::_cord2Excel($currX, $currY, 0),
							'o' => ';;;" "'
						)));
					$currX = $lastId;
				}
				else
					$currX++;

				$inRetArr[0][] = $cell;

				if ($currX >= palo::$conf['pvMaxCols'])
					return $currX;
			}
		}

		return $currX;
	}

	private static function _hpv_getElems($inConn, $inDbName, $inDim, $inCount =null)
	{
		if (empty($inDim[1]))
		{
			// TODO: Change in Future when new version of Palo Server and Palo PHP API is widely used
			if (function_exists('palo_dimension_reduced_top_list_elements'))
			{
				$listElems = ($inCount == 1) ? palo_dimension_reduced_top_list_elements($inConn, $inDbName, $inDim[0], 0, 1) : palo_dimension_reduced_top_list_elements($inConn, $inDbName, $inDim[0]);

				$retArr = array();
				foreach ($listElems as $elem)
					$retArr[] = array($elem['name'], null, (($elem['type'] == 'consolidated') ? 'C' : ''));

				return $retArr;
			}
			else
			{
				$listElems = palo_dimension_list_elements2($inConn, $inDbName, $inDim[0], true);

				if ($inCount == 1)
				{
					foreach ($listElems as $elem)
						if (count($elem['parents']) == 0)
						{
							return array(array($elem['name'], null, (($elem['type'] == 'consolidated') ? 'C' : '')));
							break;
						}
				}
				else
				{
					$retArr = array();
					foreach ($listElems as $elem)
						if (count($elem['parents']) == 0)
							$retArr[] = array($elem['name'], null, (($elem['type'] == 'consolidated') ? 'C' : ''));

					return $retArr;
				}
			}
		}
		else
			return (($inCount == 1) ? array($inDim[1][0]) : $inDim[1]);

		return array();
	}

	private static function _hpv_getAttrElem($inConn, $inDbName, $inDimName, $inAttr, $inElemName)
	{
		$cubeName = '#_' . $inDimName;
		$listAttributedElemNames = palo_datav($inConn, $inDbName, $cubeName, $inAttr, $inElemName);

		return (!empty($listAttributedElemNames[2])) ? $listAttributedElemNames[2] : $inElemName;
	}

	private static function _getChildElems($conn, $dbName, $dimName, $elemName, $attrib =null)
	{
		$listElems = palo_element_list_consolidation_elements($conn, $dbName, $dimName, $elemName);

		$retList = array();
		for ($i=0; $i<count($listElems); $i++)
			$retList[] = array($listElems[$i]['name'], $attrib, (($listElems[$i]['type'] == 'consolidated') ? 'C' : ''));

		return $retList;
	}

	private static function _generateDataFuncs($conn, $dbName, $inData, $lastX, $lastY)
	{
		$settings = $inData[0];
		$pageDims = $inData[1];
		$columnDims = $inData[2];
		$rowDims = $inData[3];

		$cubeDims = palo_cube_list_dimensions($conn, $dbName, $settings[4]);
		$tmpDims = array_flip($cubeDims);

		$fncPreName = '=PALO.DATA(';
		for ($i=0; $i<2; $i++)
			$fncPreName .= self::_cord2Excel($settings[0], $settings[1] + $i) . palo::$conf['paloAttrsSeparator'];

		for ($i=0; $i<count($pageDims); $i++)
			$tmpDims[$pageDims[$i][0]] = self::_cord2Excel($settings[0], $settings[1] + $i + 2);

		$rowColCellsX = $settings[0];
		$rowColCellsY = $settings[1] + count($pageDims) + 3;

		$dataCellsX = $rowColCellsX + count($rowDims);
		$dataCellsY = $rowColCellsY + count($columnDims);

		$data = array($dataCellsX, $dataCellsY, $lastX - 1, $lastY - 1);
		for ($i=$dataCellsY; $i<$lastY; $i++)
		{
			for ($j=$dataCellsX; $j<$lastX; $j++)
			{
				for ($k=0; $k<count($columnDims); $k++)
					$tmpDims[$columnDims[$k][0]] = self::_cord2Excel($j, $rowColCellsY + $k, 1);

				for ($k=0; $k<count($rowDims); $k++)
					$tmpDims[$rowDims[$k][0]] = self::_cord2Excel($rowColCellsX + $k, $i, 2);

				$attrs = '';
				for ($k=0; $k<count($cubeDims); $k++)
					$attrs .= $tmpDims[$cubeDims[$k]] . palo::$conf['paloAttrsSeparator'];

				$attrs = substr($attrs, 0, strlen($attrs) - 1);

				$fncName = $fncPreName . $attrs . ')';
				$data[] = array('v' => $fncName, 'a' => array('dblclick' => array(palo::$conf['openPaloTE'])));
			}
		}

		return $data;
	}

	private static function _elemInArray($inArr, $inElem)
	{
		for ($i=0; $i<count($inArr); $i++)
			if ($inArr[$i][0] == $inElem[0])
				return $i;

		return -1;
	}

	private static function _removeSubChilds($conn, $dbName, $dimName, &$listOfElems, $index)
	{
		$elemList = self::_getChildElems($conn, $dbName, $dimName, $listOfElems[$index][0]);

		for ($i=$index+1; $i<count($listOfElems); $i++)
		{
			if (self::_elemInArray($elemList, $listOfElems[$i]) != -1)
			{
				if (($listOfElems[$i][2] == 'C') && ((isset($listOfElems[$i][3])) ? ($listOfElems[$i][3]) : true))
					self::_removeSubChilds($conn, $dbName, $dimName, $listOfElems, $i);

				array_splice($listOfElems, $i--, 1);
				continue;
			}
			break;
		}
	}

	/* public methods */
	public static function unloadPvSess()
	{
		if (isset($_SESSION['palo_pasteview_states'][palo::getWbId()][palo::getWsId()]))
			self::_clearPvSess();
	}

	public static function getPasteViewInitData($inPasteViewId)
	{
		$sessData =& palo::getSessionDataWS('palo_pasteview_states');
		self::_loadPasteViewData($sessData, $inPasteViewId);

		if (!empty($sessData) && isset($sessData[$inPasteViewId]) && isset($sessData[$inPasteViewId][1]))
			return $sessData[$inPasteViewId][1];
		else if (empty($sessData))
			self::_clearPvSess();

		throw new WSS_Exception('P1_16', null, 'Unable to get Paste View config data.');
	}

	// *** Paste Data Function *** //
	public static function handlerPasteDataFunctions($inVals)
	{
		$settings = $inVals[0];
		$connName = $settings[4];
		$dbName = $settings[5];

		$conn = palo::palo_init($connName);
		$cubeName = $inVals[1];
		$guessARgs = $settings[6];

		$cubeDims = palo_cube_list_dimensions($conn, $dbName, $cubeName);
		$tmpDims = array_flip($cubeDims);

		// gen Data Functions
		if ($guessARgs)
		{
			// Zones
			$zones[2] = array(1, 1, $settings[0] - 1, $settings[1] - 1); // Zone 1
			$zones[0] = array($settings[0], 1, $settings[2], $settings[1] - 1); // Zone 2
			$zones[1] = array(1, $settings[1], $settings[0] - 1, $settings[3]); // Zone 3

			// get cells for all zones
			$cmds = '[';
			for ($i=0; $i<count($zones); $i++)
				$cmds .= '["gval",16,' . $zones[$i][0] . ',' . $zones[$i][1] . ',' . $zones[$i][2] . ',' . $zones[$i][3] . '],';
			$cmds = substr($cmds, 0, -1) . ']';

			// execute commands on core
			$res = json_decode(ccmd($cmds), true);

			// get wsels with posible Guess Args support
			$wselRes = json_decode(ccmd('[["wget","",[],["_gendata","data","n_location","n_target_ref"],{"e_type":"formel","formel_type":"ComboBox"}]]'), true);
			if (isset($wselRes[0]) && $wselRes[0][0] && !empty($wselRes[0][1]))
			{
				foreach ($wselRes[0][1] as $wsel)
				{
					if (isset($wsel['_gendata']) && !empty($wsel['_gendata']) && isset($wsel['data']) && isset($wsel['data']['trange']) && empty($wsel['data']['trange']))
					{
						if (!isset($gsWsels))
							$gsWsels = array();

//						$spltNLoc = preg_split('/[!,=,:]/', $wsel['n_location']);
//						$cords = self::_excel2Cord( (!empty($spltNLoc[count($spltNLoc) - 2])) ? $spltNLoc[count($spltNLoc) - 2] : $spltNLoc[count($spltNLoc) - 1]);

						$spltNLoc = preg_split('/.*[!,=]/', $wsel['n_location']);
						$spltNLoc = split(':', $spltNLoc[1]);
						$cords = self::_excel2Cord($spltNLoc[0]);

						if (!isset($gsWsels[$cords[1]]))
							$gsWsels[$cords[1]] = array();

						if (!isset($gsWsels[$cords[1]][$cords[0]]))
							$gsWsels[$cords[1]][$cords[0]] = array();

						$gsWsels[$cords[1]][$cords[0]][] = array( 'name' => $wsel['_gendata'][0][2], 'target' => substr($wsel['n_target_ref'], 1) );
					}
				}
			}

			// Server/DB Guess and Cube Guess
			$guessServDb = null;
			$guessCube = null;

			// get all cells from core
			for ($i=0; $i<count($zones); $i++)
			{
				if (isset($res[$i]) && $res[$i][0])
				{
					$rngVals = $res[$i][1];
					$valsLen = count($rngVals);

					for ($j=0; $j<$valsLen; $j++)
					{
						$cords = array($zones[$i][0] + intval($j % ($zones[$i][2] - $zones[$i][0] + 1)), $zones[$i][1] + intval($j / ($zones[$i][2] - $zones[$i][0] + 1)));

						// handle wsels (they have prio over cells)
						if (isset($gsWsels) && isset($gsWsels[$cords[1]][$cords[0]]))
							foreach ($gsWsels[$cords[1]][$cords[0]] as $wsel)
								if ( !is_array($tmpDims[ $wsel['name'] ]) )
									$tmpDims[$wsel['name']] = array($wsel['target']);

						// handle cells
						if (!empty($rngVals[$j]) && (strpos($rngVals[$j], 'palo_pe') !== false))
						{
							$attrVal = json_decode($rngVals[$j], true);

							if (isset($attrVal['palo_pe']) && isset($attrVal['palo_pe']['type']))
							{
								if ($attrVal['palo_pe']['type'] == 'dim')
								{
									if (!is_array($tmpDims[$attrVal['palo_pe']['name']]))
										$tmpDims[$attrVal['palo_pe']['name']] = array($i, $cords);
								}
								else if ($attrVal['palo_pe']['type'] == 'serv_db' && $guessServDb == null)
									$guessServDb = self::_cord2Excel($cords[0], $cords[1]);
								else if ($attrVal['palo_pe']['type'] == 'cube' && $guessCube == null)
									$guessCube = self::_cord2Excel($cords[0], $cords[1]);
							}
						}
					}
				}
			}

			// gen function start name (with posible guessed serv/db and cube name)
			$fncPreName = '=PALO.DATA(' . (($guessServDb == null) ? ('"' . $connName . '/' . $dbName . '"') : $guessServDb) . palo::$conf['paloAttrsSeparator'] . (($guessCube == null) ? ('"' . $cubeName . '"') : $guessCube) . palo::$conf['paloAttrsSeparator'];

			for ($i=0; $i<count($cubeDims); $i++)
			{
				if (!is_array($tmpDims[$cubeDims[$i]]))
				{
					$tmpDim = array($cubeDims[$i], null);
					$tmpElems = self::_hpv_getElems($conn, $dbName, $tmpDim, 1);

					$tmpDims[$cubeDims[$i]] = $tmpElems[0][0];
				}
			}

			$data = array($settings[0], $settings[1], $settings[2], $settings[3]);
			for ($j=$settings[1]; $j<=$settings[3]; $j++)
			{
				for ($i=$settings[0]; $i<=$settings[2]; $i++)
				{
					$singleDataFunc = $fncPreName;
					for ($k=0; $k<count($cubeDims); $k++)
					{
						$tmpDimInfo = $tmpDims[$cubeDims[$k]];

						if (!is_array($tmpDimInfo)) // not guessed argument
							$singleDataFunc .= '"' . $tmpDimInfo . '"';
						else if (isset($tmpDimInfo[1])) // guessed cell value
						{
							if ($tmpDimInfo[0] == 2)
								$singleDataFunc .= self::_cord2Excel($tmpDimInfo[1][0], $tmpDimInfo[1][1]);
							else if ($tmpDimInfo[0] == 0)
								$singleDataFunc .= self::_cord2Excel($tmpDimInfo[1][0] + ($i - $settings[0]), $tmpDimInfo[1][1], 1);
							else
								$singleDataFunc .= self::_cord2Excel($tmpDimInfo[1][0], $tmpDimInfo[1][1] + ($j - $settings[1]), 2);
						}
						else // guessed wsel value
							$singleDataFunc .= $tmpDimInfo[0];

						if ($k < (count($cubeDims) - 1))
							$singleDataFunc .= palo::$conf['paloAttrsSeparator'];
					}
					$singleDataFunc .= ')';

					$data[] = array('v' => $singleDataFunc, 'a' => array('dblclick' => array(palo::$conf['openPaloTE'])));
				}
			}
		}
		else
		{
			// gen start of function name for non guessed function
			$fncPreName = '=PALO.DATA("' . $connName . '/' . $dbName . '"' . palo::$conf['paloAttrsSeparator'] . '"' . $cubeName . '"' . palo::$conf['paloAttrsSeparator'];

			for ($i=0; $i<count($cubeDims); $i++)
			{
				$tmpDim = array($cubeDims[$i], null);
				$tmpElems = self::_hpv_getElems($conn, $dbName, $tmpDim, 1);

				$fncPreName .= '"' . $tmpElems[0][0] . '"';
				if ($i < (count($cubeDims) - 1))
					$fncPreName .= palo::$conf['paloAttrsSeparator'];
			}
			$fncPreName .= ')';

			$data = array($settings[0], $settings[1], $settings[2], $settings[3], array('v' => $fncPreName, 'a' => array('dblclick' => array(palo::$conf['openPaloTE']))));
		}

		palo::palo_disconnect($conn);

		return array(array('cdrn', array('cm' => true), $data));
	}

	public static function handlerSelectElements($inVals)
	{
		$settings = $inVals[0];
		$connName = $settings[2];
		$dbName = $settings[3];

		$dims = array();
		foreach ($inVals[1] as $dimName => $elems)
			$dims[] = array($dimName, $elems);

		$conn = palo::palo_init($connName);

		$retArr = array('cdrg', array('cm' => true), array($settings[0], $settings[1], (($settings[4]) ? 0 : 1)));
		if (count($dims[0][1]) > 1)
		{
			foreach ($dims[0][1] as $elem)
			{
				$cellElem = array(
					'v' => $elem[0],
					's' => (($elem[2] == 'C') ? palo::$conf['styleConsolidated'] : palo::$conf['styleNormal']),
					'a' => array('palo_pe' => array('type' => 'dim', 'name' => $dims[0][0]))
				);
				if (isset($elem[1]) && !empty($elem[1]))
					$cellElem['o'] = ';;;"' . self::_hpv_getAttrElem($conn, $dbName, $dims[0][0], $elem[1], $elem[0]) . '"';
				else
					$cellElem['o'] = '';
				$retArr[2][] = $cellElem;

				if ($settings[4])
					$retArr[2][2]++;
			}
		}
		else if (count($dims[0][1]) == 1)
		{
			$elem = $dims[0][1][0];
			$cellElem = array(
				'v' => '=PALO.ENAME("' . $connName . '/' . $dbName . '"' . palo::$conf['paloAttrsSeparator'] . '"' . $dims[0][0] . '"' . palo::$conf['paloAttrsSeparator'] . '"' . $elem[0] . '"' . palo::$conf['paloAttrsSeparator'] . '1' . palo::$conf['paloAttrsSeparator'] . '"' . $elem[0] . '"' . palo::$conf['paloAttrsSeparator'] . '"' . ( (!empty($elem[1])) ? $elem[1] : '' ) . '")',
				's' => (($elem[2] == 'C') ? palo::$conf['styleConsolidated'] : palo::$conf['styleNormal']),
				'a' => array(
					'palo_pe' => array('type' => 'dim', 'name' => $dims[0][0]),
					'dblclick' => array(palo::$conf['nofnc_openChooseElement_inJS'], array(
						'working_mode' => 8,
						'serv_id' => $connName,
						'db_name' => $dbName,
						'dim_name' => $dims[0][0],
						'edit_data' => array($elem)
					))
				)
			);
			if (isset($elem[1]) && !empty($elem[1]))
				$cellElem['o'] = ';;;"' . self::_hpv_getAttrElem($conn, $dbName, $dims[0][0], $elem[1], $elem[0]) . '"';
			else
				$cellElem['o'] = '';
			$retArr[2][] = $cellElem;

			if ($settings[4])
				$retArr[2][2]++;
		}

		palo::palo_disconnect($conn);

		return array($retArr);
	}

	// Choose Element
	public static function handlerChooseElements($inVals)
	{
		$retArr = array();
		$settings = $inVals[0];
		$dim = $inVals[1];

		$connName = $settings[2];
		$dbName = $settings[3];
		$pasteViewId = $settings[4];

		$firstCellX = $settings[0];
		$firstCellY = $settings[1] - $settings[5];

		$sessData =& palo::getSessionDataWS('palo_pasteview_states');
		self::_loadPasteViewData($sessData, $pasteViewId);
		$state = $sessData[$pasteViewId];

		if ((($firstCellX != $state[0][0]) || ($firstCellY != $state[0][1])) && ($firstCellX > 0) && ($firstCellY > 0))
		{
			$diffX = $state[0][2] - $state[0][0];
			$diffY = $state[0][3] - $state[0][1];
			// X
			$sessData[$pasteViewId][1][0][0] = $firstCellX;
			$sessData[$pasteViewId][0][0] = $firstCellX;
			$sessData[$pasteViewId][0][2] = $firstCellX + $diffX;
			// Y
			$sessData[$pasteViewId][1][0][1] = $firstCellY;
			$sessData[$pasteViewId][0][1] = $firstCellY;
			$sessData[$pasteViewId][0][3] = $firstCellY + $diffY;
		}

		$res = ccmd(array(array('wget', '', array(), array('e_id','n_location'), array('pv_id' => $pasteViewId, 'e_type' => 'palo_pv'))));
		if ($res[0][0])
		{
			$pv_fields = explode(',', $res[0][1][0]['n_location']);
			$servDbCell = $pv_fields[1];
		}

		$cmdModCell = array('cdrg', array('cm' => false), array($settings[0], $settings[1], 1, array(
			'v' => '=PALO.ENAME(' . ( isset($servDbCell) ? $servDbCell : self::_cord2Excel($firstCellX, $firstCellY) ) . palo::$conf['paloAttrsSeparator'] . '"' . $dim[0] . '"' . palo::$conf['paloAttrsSeparator'] . '"' . $dim[1][0][0] . '"' . palo::$conf['paloAttrsSeparator'] . '1' . palo::$conf['paloAttrsSeparator'] . '""' . palo::$conf['paloAttrsSeparator'] . '"' . ( (!empty($dim[1][0][1])) ? $dim[1][0][1] : '' ) . '")',
			's' => (($dim[1][0][2] == 'C') ? (palo::$conf['styleConsolidated']) : (palo::$conf['styleNormal'])) . 'background-color:' . palo::$conf['colorPageElems'] . ';',
			'a' => array('dblclick' => array(palo::$conf['nofnc_openChooseElement_inJS'], array(
						'working_mode' => 1,
						'serv_id' => $connName,
						'db_name' => $dbName,
						'dim_name' => $dim[0],
						'edit_data' => array($dim[1][0]),
						'pasteview_id' => $pasteViewId,
						'edit_y' => $settings[5]
					)
			))
		)));
		if (!empty($dim[1][0][1]))
		{
			$conn = palo::palo_init($connName);
			$cmdModCell[2][3]['o'] = ';;;"' .  self::_hpv_getAttrElem($conn, $dbName, $dim[0], $dim[1][0][1], $dim[1][0][0]) . '"';
			palo::palo_disconnect($conn);
		}
		else
			$cmdModCell[2][3]['o'] = '';

		// Saving change
		foreach ($sessData[$pasteViewId][1][1] as $dimKey => $storedDim)
		{
			if ($storedDim[0] == $dim[0])
			{
				$sessData[$pasteViewId][1][1][$dimKey] = $dim;
				break;
			}
		}

		$retArr[] = $cmdModCell;

		// Store changes to Core
		if ($res[0][0])
			ccmd(array(array('wupd', '', array($res[0][1][0]['e_id'] => array('payload' => base64_encode(gzcompress(serialize($sessData[$pasteViewId]), 1)))))));

		return $retArr;
	}

	// Paste View Handler
	public static function handlerPasteView($inVal)
	{
		// Make paste view to be always at position A1
		if (!$inVal[0][8] && !$inVal[0][10])
		{
			$inVal[0][0] = 1;
			$inVal[0][1] = 1;
		}
		// ***

		$retArr = array();

		// settings Def: [tlCell_X, tlCell_Y, connName, dbName, cubeName, boolWrap_Labels, fixedWidth, indent, pasteAtSelectedCell, dataMode, editMode, editSettingsData, showElemOnDblClick, zeroSupp]
		$settings = $inVal[0];
		$connName = $settings[2];
		$dbName = $settings[3];

		// init session data
		$sessData =& palo::getSessionDataWS('palo_pasteview_states');
		if (isset($settings[11]) && isset($settings[11][0]))
		{
			$pasteViewId = $settings[11][0];
			self::_loadPasteViewData($sessData, $pasteViewId);
		}

		// in case that Paste View is pasted at A1 current paste view at that position will be deleted
		$res = ccmd(array(array('wget', '', array(), array('e_id','n_location'), array('e_type' => 'palo_pv'))));
		if ($res[0][0] && (!$settings[10]))
		{
			$wbPasteViews = $res[0][1];
			for ($i=0; $i<count($wbPasteViews); $i++)
			{
				$pv_fields = explode(',', $wbPasteViews[$i]['n_location']);
				if ($pv_fields[1] == '$A$1')
				{
					$delFnc = array('clr');
					for ($pvf_n=0; $pvf_n < count($pv_fields); $pvf_n++)
					{
						if (strpos($pv_fields[$pvf_n], ':') === false)
						{
							$cell_pos = self::_excel2Cord($pv_fields[$pvf_n]);
							$delFnc[] = array(15, $cell_pos[0], $cell_pos[1], $cell_pos[0], $cell_pos[1]);
						}
						else
						{
							$cells = explode(':', $pv_fields[$pvf_n]);
							$start_cell = self::_excel2Cord($cells[0]);
							$end_cell = self::_excel2Cord($cells[1]);

							$delFnc[] = array(15, $start_cell[0], $start_cell[1], $end_cell[0], $end_cell[1]);
						}
					}

					// delete Paste View data
					$wdelFnc = array('wdel', '', array($wbPasteViews[$i]['e_id']));
					unset($sessData[$pasteViewId]);
				}
			}
		}

		// Edit
		if ($settings[10])
		{
			$settings[0] -= $settings[11][1];
			$settings[1] -= $settings[11][2];

			$diffX = $settings[0] - $sessData[$pasteViewId][0][0];
			$diffY = $settings[1] - $sessData[$pasteViewId][0][1];

			// Delete Old Paste View
			$delFnc = array('clr');
			$res = ccmd(array(array('wget', '', array(), array('e_id','n_location'), array('pv_id' => $pasteViewId, 'e_type' => 'palo_pv'))));
			if ($res[0][0])
			{
				$pv_fields = explode(',', $res[0][1][0]['n_location']);

				for ($pvf_n=0; $pvf_n < count($pv_fields); $pvf_n++)
				{
					if (strpos($pv_fields[$pvf_n], ':') === false)
					{
						$cell_pos = self::_excel2Cord($pv_fields[$pvf_n]);
						$delFnc[] = array(15, $cell_pos[0], $cell_pos[1], $cell_pos[0], $cell_pos[1]);
					}
					else
					{
						$cells = explode(':', $pv_fields[$pvf_n]);
						$start_cell = self::_excel2Cord($cells[0]);
						$end_cell = self::_excel2Cord($cells[1]);

						$delFnc[] = array(15, $start_cell[0], $start_cell[1], $end_cell[0], $end_cell[1]);
					}
				}
			}
		}
		else
		{
			$pasteViewId = uniqid('pv_');
			while(isset($sessData[$pasteViewId]))
				$pasteViewId = uniqid('pv_');
		}

		$conn = palo::palo_init($connName);
		$pageDims = $inVal[1];
		$columnDims = &$inVal[2];
		$rowDims = &$inVal[3];
		$n_loc = '';

		$header = array(
			'cdrg',
			array('cm' => false),
			array($settings[0], $settings[1], 1,
				array(
					'v' => $connName . '/' . $dbName,
					's' => palo::$conf['styleConsolidated'] . 'background-color:' . palo::$conf['colorHostDb'] . ';',
					'a' => array('palo_pe' => array('type' => 'serv_db'))
				),
				array(
					'v' => $settings[4],
					's' => palo::$conf['styleConsolidated'] . 'background-color:' . palo::$conf['colorHostDb'] . ';',
					'a' => array('palo_pe' => array('type' => 'cube'))
				)
			)
		);
		$n_loc .= self::_cord2Excel($settings[0], $settings[1]) . ',' . self::_cord2Excel($settings[0], $settings[1] + 1);

		$relativeY = 2;
		foreach ($pageDims as $dim)
		{
			$elem = self::_hpv_getElems($conn, $dbName, $dim, 1);
			$fncName = '=PALO.ENAME(' . self::_cord2Excel($settings[0], $settings[1]) . palo::$conf['paloAttrsSeparator'] . '"' . $dim[0] . '"' . palo::$conf['paloAttrsSeparator'] . '"' . $elem[0][0] . '"' . palo::$conf['paloAttrsSeparator'] . '1' . palo::$conf['paloAttrsSeparator'] . '""' . palo::$conf['paloAttrsSeparator'] . '"' . ( (!empty($elem[0][1])) ? $elem[0][1] : '' ) . '")';

			$headerCell = array(
				'v' => $fncName,
				's' => (($elem[0][2] == 'C') ? (palo::$conf['styleConsolidated']) : '') . 'background-color:' . palo::$conf['colorPageElems'] . ';' .
				(($settings[5]) ? palo::$conf['wrapText'] : ''),
				'a' => array(
					'dblclick' => array(
						palo::$conf['nofnc_openChooseElement_inJS'],
						array(
							'working_mode' => 1,
							'serv_id' => $connName,
							'db_name' => $dbName,
							'dim_name' => $dim[0],
							'edit_data' => array($elem[0]),
							'pasteview_id' => $pasteViewId,
							'edit_y' => $relativeY++
						)
					),
					'palo_pe' => array('type' => 'dim', 'name' => $dim[0])
				)
			);
			if (!empty($elem[0][1]))
				$headerCell['o'] = ';;;"' .  self::_hpv_getAttrElem($conn, $dbName, $dim[0], $elem[0][1], $elem[0][0]) . '"';
			$header[2][] = $headerCell;

			$n_loc .= ',' . self::_cord2Excel($settings[0], $settings[1] + $relativeY - 1);
		}
		$retArr[] = $header;

		// set X and Y minus factors
		$xFactor = (count($columnDims) > 0) ? 1 : 0;
		$yFactor = (count($rowDims) > 0) ? 1 : 0;

		// calculate starting cell for data (including empty space for dbclick->paste view edit dialog
		$rowColCellsX = $settings[0];
		$rowColCellsY = $settings[1] + count($header[2]) - 2;

		// Add dbl click to open filled Paste View
		if (count($columnDims) > 0 && count($rowDims) > 0)
		{
			$caArr = array('cdrn', array('cm' => false), array($rowColCellsX, $rowColCellsY, $rowColCellsX + count($rowDims) - 1, $rowColCellsY + count($columnDims) - 1));
			for ($i=$rowColCellsY; $i<($rowColCellsY + count($columnDims)); $i++)
				for ($j=$rowColCellsX; $j<($rowColCellsX + count($rowDims)); $j++)
					$caArr[2][] = array('a' => array('dblclick' => array(palo::$conf['getPasteViewInitData_inJS'], $pasteViewId, $j - $settings[0], $i - $settings[1])));
		}
		else
		{
			$caArr = array('cdrn', array('cm' => false), array($rowColCellsX, $rowColCellsY - 1, $rowColCellsX, $rowColCellsY - 1));
			$caArr[2][] = array('a' => array('dblclick' => array(palo::$conf['getPasteViewInitData_inJS'], $pasteViewId, $rowColCellsX - $settings[0], $rowColCellsY - $settings[1] - 1)));
		}

		// start generating output array
		$retArr[] = $caArr;

		// filter Elements if ZeroSupperssion is enabled
		if (isset($inVal[0][13]) && $inVal[0][13])
		{
			foreach ($rowDims as &$rowDim)
			{
				$rowDim[1] = self::_hpv_getElems($conn, $dbName, $rowDim);
				self::_doZeroSuppression($conn, $inVal, $rowDim);
			}

			foreach ($columnDims as &$colDim)
			{
				$colDim[1] = self::_hpv_getElems($conn, $dbName, $colDim);
				self::_doZeroSuppression($conn, $inVal, $colDim);
			}
		}

		// rows
		$stylesPacks = array();
		$lastY = self::_hpv_addRow($conn, $connName, $dbName, $settings[5], &$retArr, self::_cord2Excel($settings[0], $settings[1]), $rowDims, 0, $rowColCellsX, $rowColCellsY + count($columnDims), $settings[0], $settings[1], $pasteViewId, $settings[7], $settings[12], &$stylesPacks);
		// cols
		$lastX = self::_hpv_addCol($conn, $connName, $dbName, $settings[5], &$retArr, self::_cord2Excel($settings[0], $settings[1]), $columnDims, 0, $rowColCellsX + count($rowDims), $rowColCellsY, $settings[0], $settings[1], $pasteViewId, $settings[12], &$stylesPacks);
		if ($settings[6] != -1)
			$retArr[] = array('scr', 0, array($settings[0], $lastX - (($xFactor) ? 1 : 0), round($settings[6] * 10 / palo::$conf['pointToPixel'])));

		// add style packs
		self::_addStylePacks($stylesPacks, $retArr);

		// data
		$cubeDims = palo_cube_list_dimensions($conn, $dbName, $settings[4]);
		$tmpDims = array_flip($cubeDims);

		$fncPreName = '=PALO.DATA(';
		for ($i=0; $i<2; $i++)
			$fncPreName .= self::_cord2Excel($settings[0], $settings[1] + $i)  . palo::$conf['paloAttrsSeparator'];

		for ($i=0; $i<count($pageDims); $i++)
			$tmpDims[$pageDims[$i][0]] = self::_cord2Excel($settings[0], $settings[1] + $i + 2);

		$dataCellsX = $settings[0] + count($rowDims);
		$dataCellsY = $settings[1] + count($header[2]) - 2 + count($columnDims);

		$data = array($dataCellsX, $dataCellsY, $lastX - $xFactor, $lastY - $yFactor);
		if (count($columnDims) > 0 && count($rowDims) > 0)
		{
			for ($i=$dataCellsY; $i<$lastY; $i++)
			{
				for ($j=$dataCellsX; $j<$lastX; $j++)
				{
					for ($k=0; $k<count($columnDims); $k++)
						$tmpDims[$columnDims[$k][0]] = self::_cord2Excel($j, $rowColCellsY + $k, 1);

					for ($k=0; $k<count($rowDims); $k++)
						$tmpDims[$rowDims[$k][0]] = self::_cord2Excel($rowColCellsX + $k, $i, 2);

					$attrs = '';
					for ($k=0; $k<count($cubeDims); $k++)
						$attrs .= $tmpDims[$cubeDims[$k]] . palo::$conf['paloAttrsSeparator'];
					$attrs = substr($attrs, 0, strlen($attrs) - 1);

					$fncName = $fncPreName . $attrs . ')';
					$data[] = array('v' => $fncName);
				}
			}
		}
		else if (count($rowDims) > 0)
		{
			for ($i=$dataCellsY; $i<$lastY; $i++)
			{
				for ($k=0; $k<count($rowDims); $k++)
					$tmpDims[$rowDims[$k][0]] = self::_cord2Excel($rowColCellsX + $k, $i, 2);

				$attrs = '';
				for ($k=0; $k<count($cubeDims); $k++)
					$attrs .= $tmpDims[$cubeDims[$k]] . palo::$conf['paloAttrsSeparator'];
				$attrs = substr($attrs, 0, strlen($attrs) - 1);

				$fncName = $fncPreName . $attrs . ')';
				$data[] = array('v' => $fncName);
			}
		}
		else if (count($columnDims) > 0)
		{
			for ($i=$dataCellsX; $i<$lastX; $i++)
			{
				for ($k=0; $k<count($columnDims); $k++)
					$tmpDims[$columnDims[$k][0]] = self::_cord2Excel($i, $rowColCellsY + $k, 1);

				$attrs = '';
				for ($k=0; $k<count($cubeDims); $k++)
					$attrs .= $tmpDims[$cubeDims[$k]] . palo::$conf['paloAttrsSeparator'];
				$attrs = substr($attrs, 0, strlen($attrs) - 1);

				$fncName = $fncPreName . $attrs . ')';
				$data[] = array('v' => $fncName);
			}
		}
		else
		{
			$attrs = '';
			for ($k=0; $k<count($cubeDims); $k++)
				$attrs .= $tmpDims[$cubeDims[$k]] . palo::$conf['paloAttrsSeparator'];
			$attrs = substr($attrs, 0, strlen($attrs) - 1);

			$fncName = $fncPreName . $attrs . ')';
			$data[] = array('v' => $fncName);
		}

		$retArr[] = array('cdrn', array('cm' => false), $data);
		$retArr[] = array('cdrn', array('cm' => true), array($dataCellsX, $dataCellsY, $lastX - $xFactor, $lastY - $yFactor,
			array(
				's' => 'background-color:' . palo::$conf['colorData'] . ';',
				'a' => array('dblclick' => array(palo::$conf['openPaloTE']))
			)));
		$retArr[] = array('sbrd', array($dataCellsX, $dataCellsY, $lastX - $xFactor, $lastY - $yFactor), 63, '1px ' . palo::$conf['colorDataBorder'] . ' dotted');

		// Close Palo connection
		palo::palo_disconnect($conn);

		// Storing status for current Paste View
		$settingsToStore = array($settings[0], $settings[1], $lastX + ((!$xFactor)? 1 : 0), $lastY + ((!$yFactor)? 1 : 0));
		$sessData[$pasteViewId] = array($settingsToStore, $inVal);

		// Edit Mode
		if ($settings[10] && isset($delFnc))
		{
			// TODO: change when new WUPD is made with "WHERE property = value" option
			if ($res[0][0])
			{
				$updPaloPv_wsel = array('wupd', '', array(
					$res[0][1][0]['e_id'] => array(
						'n_location' => '=' . self::_cord2Excel($rowColCellsX, $rowColCellsY) . ':' . self::_cord2Excel($lastX - $xFactor, $lastY - $yFactor) . ',' . $n_loc,
						'payload' => base64_encode(gzcompress(serialize($sessData[$pasteViewId]), 1))
					)
				));

				$retArr[] = $updPaloPv_wsel;
			}

			array_unshift($retArr, $delFnc);
		}
		else
		{
			if (isset($delFnc) && isset($wdelFnc))
			{
				array_unshift($retArr, $delFnc);
				array_unshift($retArr, $wdelFnc);
			}

			// add wsel
			$addPaloPv_wsel = array('wadd', '', array(
				'e_type' => 'palo_pv',
				'pv_id' => $pasteViewId,
				'n_location' => '=' . self::_cord2Excel($rowColCellsX, $rowColCellsY) . ':' . self::_cord2Excel($lastX - $xFactor, $lastY - $yFactor) . ',' . $n_loc,
				'payload' => base64_encode(gzcompress(serialize($sessData[$pasteViewId]), 1))
			));

			$retArr[] = $addPaloPv_wsel;
		}

		return $retArr;
	}

	// *** Expand/Collapse Paste View ***
	public static function handlerExpandCollapsePasteView($inVal)
	{
		$pasteViewId = $inVal[3];

		$sessData =& palo::getSessionDataWS('palo_pasteview_states');
		self::_loadPasteViewData($sessData, $pasteViewId);

		if (!empty($sessData) && isset($sessData[$pasteViewId]))
		{
			$pasteViewData =& $sessData[$pasteViewId];
			$data =& $pasteViewData[1];
			$connName = $data[0][2];
			$dbName = $data[0][3];

			$res = ccmd(array(array('wget', '', array(), array('e_id', 'n_location'), array('pv_id' => $pasteViewId, 'e_type' => 'palo_pv'))));
			if ($res[0][0])
			{
				$pv_fields = explode(',', $res[0][1][0]['n_location']);
				$servDbCell = $pv_fields[1];
			}

			$newX = $inVal[0]['c'] - $inVal[1];
			$newY = $inVal[0]['r'] - $inVal[2];

			// Adjusting starting cordinates
			if ((($newX != $pasteViewData[0][0]) || ($newY != $pasteViewData[0][1])) && ($newX > 0) && ($newY > 0))
			{
				$diffX = $pasteViewData[0][2] - $pasteViewData[0][0];
				$diffY = $pasteViewData[0][3] - $pasteViewData[0][1];
				// X
				$data[0][0] = $newX;
				$pasteViewData[0][0] = $newX;
				$pasteViewData[0][2] = $newX + $diffX;
				// Y
				$data[0][1] = $newY;
				$pasteViewData[0][1] = $newY;
				$pasteViewData[0][3] = $newY + $diffY;
			}

			$conn = palo::palo_init($connName);

			// Definine X and Y minus Factor
			$xFactor = (count($data[3]) > 0) ? 1 : 0;
			$yFactor = (count($data[2]) > 0) ? 1 : 0;

			// Data Range TopLeft position
			$startDataRangeX = $pasteViewData[0][0] + count($data[3]);
			$startDataRangeY = $pasteViewData[0][1] + count($data[1]) + 3 + count($data[2]);

			// $cr - 2 = column; 3 = row
			if (($startDataRangeX - $inVal[0]['c']) < 1)
			{
				$cr = 2;
				$colRowIndex = count($data[$cr]) - ($startDataRangeY - $inVal[0]['r']);
				$elemIndex = $inVal[0]['c'] - $startDataRangeX;
			}
			else
			{
				$cr = 3;
				$colRowIndex = count($data[$cr]) - ($startDataRangeX - $inVal[0]['c']);
				$elemIndex = $inVal[0]['r'] - $startDataRangeY;
			}

			$dim =& $data[$cr][$colRowIndex];
			$collapsed = true;

			// Empty dim (Initialize)
			if ($dim[1] == null)
				$dim[1] = self::_hpv_getElems($conn, $dbName, $dim);

			for ($i=(count($data[$cr]) - 1); $i>$colRowIndex; $i--)
			{
				if ($data[$cr][$i][1] == null)
					$data[$cr][$i][1] = self::_hpv_getElems($conn, $dbName, $data[$cr][$i]); // Empty dim (Initialize)
				$elemIndex /= count($data[$cr][$i][1]);
			}
			$elemIndex %= count($dim[1]);
			$elemList = self::_getChildElems($conn, $dbName, $inVal[4], $inVal[5], $dim[1][$elemIndex][1]);

			// Do Collapse
			for ($i=$elemIndex+1; $i<count($dim[1]); $i++)
			{
				if (self::_elemInArray($elemList, $dim[1][$i]) != -1)
				{
					if ($collapsed)
						$collapsed = false;

					if (((isset($dim[1][$i][3])) ? ($dim[$i][3]) : true))
						self::_removeSubChilds($conn, $dbName, $inVal[4], $dim[1], $i);

					array_splice($dim[1], $i--, 1);
					continue;
				}
				break;
			}

			// Do Expand
			if ($collapsed)
			{
				array_splice($dim[1], $elemIndex + 1, 0, $elemList);

				// if zeroSuppression is enabled - filter list first
				if (isset($data[0][13]) && $data[0][13])
					self::_doZeroSuppression($conn, $data, $dim);
			}
			else
			{
				$lastX = $pasteViewData[0][2];
				$lastY = $pasteViewData[0][3];
			}

			$stylesPacks = array();
			$retArr = array(array('cdrg', array('cm' => false)));
			if ($cr == 2)
			{
				$pasteViewData[0][2] = self::_hpv_addCol($conn, $connName, $dbName,
					$data[0][5],
					&$retArr,
					(isset($servDbCell) ? $servDbCell : self::_cord2Excel($pasteViewData[0][0], $pasteViewData[0][1])),
					$data[$cr],
					0,
					$pasteViewData[0][0] + count($data[3]),
					$pasteViewData[0][1] + count($data[1]) + 3,
					$pasteViewData[0][0],
					$pasteViewData[0][1],
					$pasteViewId,
					$data[0][12],
					&$stylesPacks
				);
			}
			else if ($cr == 3)
			{
				$pasteViewData[0][3] = self::_hpv_addRow($conn, $connName, $dbName,
					$data[0][5],
					&$retArr,
					(isset($servDbCell) ? $servDbCell : self::_cord2Excel($pasteViewData[0][0], $pasteViewData[0][1])),
					$data[$cr],
					0,
					$pasteViewData[0][0],
					$pasteViewData[0][1] + count($data[1]) + 3 + count($data[2]),
					$pasteViewData[0][0],
					$pasteViewData[0][1],
					$pasteViewId,
					$data[0][7],
					$data[0][12],
					&$stylesPacks
				);
			}

			// Close palo connection
			palo::palo_disconnect($conn);

			// add style packs
			self::_addStylePacks($stylesPacks, $retArr);

			if (!$collapsed)
			{
				$clrStartX = (($cr==2) ? $pasteViewData[0][2] : $pasteViewData[0][0]);
				$clrStartY = (($cr==3) ? $pasteViewData[0][3] : $pasteViewData[0][1] + (count($data[1]) + 3));

				if ($clrStartX <= ($lastX - $xFactor) && $clrStartY <= ($lastY - $yFactor))
				{
					$delFnc = array('clr', array(15,
						$clrStartX,
						$clrStartY,
						$lastX - $xFactor,
						$lastY - $yFactor));
					$retArr[] = $delFnc;
				}
			}
			else
			{
				 if ($cr == 2)
				 {
				 	$retArr[] = array('co', array($startDataRangeX, $startDataRangeY, $startDataRangeX, $pasteViewData[0][3] - 1, $startDataRangeX + 1, $startDataRangeY, $pasteViewData[0][2] - 1, $pasteViewData[0][3] - 1));
				 	if ($data[0][6] != -1)
						$retArr[] = array('scr', 0, array($startDataRangeX, $pasteViewData[0][2] - 1, round($data[0][6] * 10 / palo::$conf['pointToPixel'])));
				 }
				 else if ($cr == 3)
				 	$retArr[] = array('co', array($startDataRangeX, $startDataRangeY, $pasteViewData[0][2] - 1, $startDataRangeY, $startDataRangeX, $startDataRangeY + 1, $pasteViewData[0][2] - 1, $pasteViewData[0][3] - 1));
			}

			// TODO: change when new WUPD is made with "WHERE property = value" option
			if ($res[0][0])
			{
				$n_loc = self::_cord2Excel($pasteViewData[0][0], $pasteViewData[0][1] + count($data[1]) + 3) . ':' . self::_cord2Excel($pasteViewData[0][2] - 1, $pasteViewData[0][3] - 1);
				for ($pvf_n = 1; $pvf_n < count($pv_fields); $pvf_n++)
					$n_loc .= ',' . $pv_fields[$pvf_n];

				array_unshift($retArr, array('wupd', '', array(
					$res[0][1][0]['e_id'] => array(
						'n_location' => '=' . $n_loc,
						'payload' => base64_encode(gzcompress(serialize($sessData[$pasteViewId]), 1))
					)
				)));
			}

			return $retArr;
		}
	}

	// *** Palo View show Element selector on DblClick handler***
	public static function handlerElemSelectPaloView($conf)
	{
		$pvId = $conf['pv_id'];

		$sessData =& palo::getSessionDataWS('palo_pasteview_states');
		self::_loadPasteViewData($sessData, $pvId);

		if (!empty($sessData) && isset($sessData[$pvId]))
		{
			// init - some vars
			// - $crType - 2 = column; 3 = row -
			$crType = $conf['orient_type'];
			$crIndex = $conf['cr_index'];

			$pvData =& $sessData[$pvId];
			$data =& $pvData[1];
			$dim =& $data[$crType][$crIndex];

			$connName = $data[0][2];
			$dbName = $data[0][3];

			// position calculations
			$res = ccmd(array(array('wget', '', array(), array('e_id', 'n_location'), array('pv_id' => $pvId, 'e_type' => 'palo_pv'))));
			if ($res[0][0])
			{
				$pv_fields = explode(',', $res[0][1][0]['n_location']);
				$servDbCell = $pv_fields[1];
			}

			// adjusting starting cordinates of palo view
			$newX = $conf['clk_pos']['c'] - $conf['pos'][0];
			$newY = $conf['clk_pos']['r'] - $conf['pos'][1];
			if ((($newX != $pvData[0][0]) || ($newY != $pvData[0][1])) && ($newX > 0) && ($newY > 0))
			{
				$diffX = $pvData[0][2] - $pvData[0][0];
				$diffY = $pvData[0][3] - $pvData[0][1];
				// X
				$data[0][0] = $newX;
				$pvData[0][0] = $newX;
				$pvData[0][2] = $newX + $diffX;
				// Y
				$data[0][1] = $newY;
				$pvData[0][1] = $newY;
				$pvData[0][3] = $newY + $diffY;
			}

			// make palo connection
			$conn = palo::palo_init($connName);

			// Definine X and Y minus Factor
			$xFactor = (count($data[3]) > 0) ? 1 : 0;
			$yFactor = (count($data[2]) > 0) ? 1 : 0;

			// Data Range TopLeft position
			$startDataRangeX = $pvData[0][0] + count($data[3]);
			$startDataRangeY = $pvData[0][1] + count($data[1]) + 3 + count($data[2]);

			// fill Dim elems
			$dim[1] = (empty($conf['elems'])) ? self::_hpv_getElems($conn, $dbName, $dim) : $conf['elems'];
			for ($i = (count($data[$crType]) - 1); $i > $crIndex; $i--)
				if ($data[$crType][$i][1] == null)
					$data[$crType][$i][1] = self::_hpv_getElems($conn, $dbName, $data[$crType][$i]); // Empty dim (Initialize)

			// filter if Zero Suppression is enabled
			if (isset($data[0][13]) && $data[0][13])
				self::_doZeroSuppression($conn, $data, $dim);

			// In case of clearing some cells this will be last cell or clr range
			$clrEndX = $pvData[0][2] - $xFactor;
			$clrEndY = $pvData[0][3] - $yFactor;

			$stylesPacks = array();
			$retArr = array(array('cdrg', array('cm' => false)));
			if ($crType == 2)
				$pvData[0][2] = self::_hpv_addCol(
					$conn,
					$connName,
					$dbName,
					$data[0][5],
					&$retArr,
					(isset($servDbCell) ? $servDbCell : self::_cord2Excel($pvData[0][0], $pvData[0][1])),
					$data[$crType],
					0,
					$pvData[0][0] + count($data[3]),
					$pvData[0][1] + count($data[1]) + 3,
					$pvData[0][0],
					$pvData[0][1],
					$pvId,
					$data[0][12],
					&$stylesPacks
				);
			else if ($crType == 3)
				$pvData[0][3] = self::_hpv_addRow(
					$conn,
					$connName,
					$dbName,
					$data[0][5],
					&$retArr,
					(isset($servDbCell) ? $servDbCell : self::_cord2Excel($pvData[0][0], $pvData[0][1])),
					$data[$crType],
					0,
					$pvData[0][0],
					$pvData[0][1] + count($data[1]) + 3 + count($data[2]),
					$pvData[0][0],
					$pvData[0][1],
					$pvId,
					$data[0][7],
					$data[0][12],
					&$stylesPacks
				);

			// Close palo connection
			palo::palo_disconnect($conn);

			// add style packs
			self::_addStylePacks($stylesPacks, $retArr);

			// calc first cell of clear range
			$clrStartX = (($crType == 2) ? $pvData[0][2] : $pvData[0][0]);
			$clrStartY = (($crType == 3) ? $pvData[0][3] : $pvData[0][1] + (count($data[1]) + 3));

			if ($clrStartX <= $clrEndX && $clrStartY <= $clrEndY)
				$retArr[] = array(
					'clr',
					array(
						15,
						$clrStartX,
						$clrStartY,
						$clrEndX,
						$clrEndY
					)
				);
			else
			{
				 if ($crType == 2 && $startDataRangeX != $pvData[0][2] - 1)
				 {
				 	$retArr[] = array('co', array($startDataRangeX, $startDataRangeY, $startDataRangeX, $pvData[0][3] - 1, $startDataRangeX + 1, $startDataRangeY, $pvData[0][2] - 1, $pvData[0][3] - 1));
				 	if ($data[0][6] != -1)
						$retArr[] = array('scr', 0, array($startDataRangeX, $pvData[0][2] - 1, round($data[0][6] * 10 / palo::$conf['pointToPixel'])));
				 }
				 else if ($crType == 3 && $startDataRangeY != $pvData[0][3] - 1)
				 	$retArr[] = array('co', array($startDataRangeX, $startDataRangeY, $pvData[0][2] - 1, $startDataRangeY, $startDataRangeX, $startDataRangeY + 1, $pvData[0][2] - 1, $pvData[0][3] - 1));
			}

			// TODO: change when new WUPD is made with "WHERE property = value" option
			if ($res[0][0])
			{
				$n_loc = self::_cord2Excel($pvData[0][0], $pvData[0][1] + count($data[1]) + 3) . ':' . self::_cord2Excel($pvData[0][2] - 1, $pvData[0][3] - 1);
				for ($pvf_n = 1; $pvf_n < count($pv_fields); $pvf_n++)
					$n_loc .= ',' . $pv_fields[$pvf_n];

				array_unshift($retArr, array('wupd', '', array(
					$res[0][1][0]['e_id'] => array(
						'n_location' => '=' . $n_loc,
						'payload' => base64_encode(gzcompress(serialize($sessData[$pvId]), 1))
					)
				)));
			}

			return $retArr;
		}
	}

	// get Elements for expanded Col/Row in Palo View
	public static function getPVColRowElems($conf)
	{
		$pvId = $conf['pv_id'];

		$sessData =& palo::getSessionDataWS('palo_pasteview_states');
		self::_loadPasteViewData($sessData, $pvId);

		if (!empty($sessData) && isset($sessData[$pvId]))
		{
			$dim =& $sessData[$pvId][1][$conf['orient_type']][$conf['cr_index']];
			$elems =& $dim[1];

			// Empty dim (Initialize)
			if ($elems == null)
			{
				$conn = palo::palo_init($sessData[$pvId][1][0][2]);
				$elems = self::_hpv_getElems($conn, $sessData[$pvId][1][0][3], $dim);
				palo::palo_disconnect($conn);
			}

			return (($elems != null) ? $elems : array());
		}

		return array();
	}
}

?>