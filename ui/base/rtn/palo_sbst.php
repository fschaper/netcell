<?php

/*
 * \brief RPC routines for handling Palo Subset
 *
 * \file palo_sbst.php
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
 * SVN: $Id: palo_sbst.php 4756 2011-03-24 14:10:36Z mladent $
 *
 */

class palo_sbst
{
	private static $_paloSubsetDesc = array(
		'_name' => 'PALO.SUBSET',
		'_objName' => 'subset',
		'_isSet' => array('type' => 'xpath', 'path' => '/subset:subset'),
		'_hb_hasDbName' => true,
		'@1' => array(
			'type' => 'variable',
			'data_type' => 'string',
			'var_name' => 'server/database',
			'_objName' => 'serv_db'
		),
		'@2' => array(
			'type' => 'variable',
			'data_type' => 'string',
			'var_name' => 'dimension',
			'_objName' => 'dim'
		),
		'@3' => array(
			'type' => 'xpath',
			'path' => '/subset:subset/subset:indent/subset:value',
			'_objName' => 'indent'
		),
		'@4' => array(
			'type' => 'xpath_palo_attribute',
			'path' => '/subset:subset/subset:alias_filter',
			'_objName' => array('alias1', 'alias2')
		),
		'@5' => array('type' => 'function', 'function_def' => array(
			'_name' => 'PALO.HFILTER',
			'_objName' => 'hier',
			'_isSet' => array('type' => 'xpath', 'path' => '/subset:subset/subset:hierarchical_filter'),
			'@1' => array(
				'type' => 'xpath',
				'data_type' => 'palo_element',
				'path' => '/subset:subset/subset:hierarchical_filter/subset:element/subset:value',
				'param' => '/subset:subset/subset:hierarchical_filter/subset:element/subset:parameter',
				'_objName' => 'element'
			),
			'@2' => array(
				'type' => 'xpath',
				'data_type' => 'bool',
				'path' => '/subset:subset/subset:hierarchical_filter/subset:above/subset:value',
				'param' => '/subset:subset/subset:hierarchical_filter/subset:above/subset:parameter',
				'_objName' => 'above'
			),
			'@3' => array(
				'type' => 'xpath',
				'data_type' => 'bool',
				'path' => '/subset:subset/subset:hierarchical_filter/subset:exclusive/subset:value',
				'param' => '/subset:subset/subset:hierarchical_filter/subset:exclusive/subset:parameter',
				'_objName' => 'exclusive'
			),
			'@4' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:hierarchical_filter/subset:hide/subset:value',
				'param' => '/subset:subset/subset:hierarchical_filter/subset:hide/subset:parameter',
				'_objName' => 'hide'
			),
			'@5' => array(
				'type' => 'xpath',
				'data_type' => 'palo_element',
				'path' => '/subset:subset/subset:hierarchical_filter/subset:revolve_element/subset:value',
				'param' => '/subset:subset/subset:hierarchical_filter/subset:revolve_element/subset:parameter',
				'_objName' => 'revolve_element'
			),
			'@6' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:hierarchical_filter/subset:revolve_count/subset:value',
				'param' => '/subset:subset/subset:hierarchical_filter/subset:revolve_count/subset:parameter',
				'_objName' => 'revolve_count'
			),
			'@7' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:hierarchical_filter/subset:revolve_add/subset:value',
				'param' => '/subset:subset/subset:hierarchical_filter/subset:revolve_add/subset:parameter',
				'_objName' => 'revolve_add'
			),
			'@8' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:hierarchical_filter/subset:level_start/subset:value',
				'param' => '/subset:subset/subset:hierarchical_filter/subset:level_start/subset:parameter',
				'_objName' => 'level_start'
			),
			'@9' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:hierarchical_filter/subset:level_end/subset:value',
				'param' => '/subset:subset/subset:hierarchical_filter/subset:level_end/subset:parameter',
				'_objName' => 'level_end'
			)
		)),
		'@6' => array('type' => 'function', 'function_def' => array(
			'_name' => 'PALO.TFILTER',
			'_objName' => 'text',
			'_isSet' => array('type' => 'xpath', 'path' => '/subset:subset/subset:text_filter'),
			'@1' => array(
				'type' => 'xpath',
				'data_type' => 'string',
				'path' => '/subset:subset/subset:text_filter/subset:regexes/subset:value/subset:expression',
				'param' => '/subset:subset/subset:text_filter/subset:regexes/subset:parameter',
				'_objName' => 'regexes'
			),
			'@2' => array(
				'type' => 'xpath',
				'data_type' => 'bool',
				'path' => '/subset:subset/subset:text_filter/subset:extended/subset:value',
				'param' => '/subset:subset/subset:text_filter/subset:extended/subset:parameter',
				'_objName' => 'extended'
			)
		)),
		'@7' => array('type' => 'function', 'function_def' => array(
			'_name' => 'PALO.PICKLIST',
			'_objName' => 'pick',
			'_isSet' => array('type' => 'xpath', 'path' => '/subset:subset/subset:picklist_filter'),
			'@1' => array(
				'type' => 'xpath',
				'data_type' => 'palo_element',
				'path' => '/subset:subset/subset:picklist_filter/subset:manual_definition/subset:value/subset:pick_elem',
				'param' => '/subset:subset/subset:picklist_filter/subset:manual_definition/subset:parameter',
				'_objName' => 'elems'
			),
			'@2' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:picklist_filter/subset:pick_type/subset:value',
				'param' => '/subset:subset/subset:picklist_filter/subset:pick_type/subset:parameter',
				'_objName' => 'pick_type'
			)
		)),
		'@8' => array('type' => 'function', 'function_def' => array(
			'_name' => 'PALO.AFILTER',
			'_objName' => 'attr',
			'_isSet' => array('type' => 'xpath', 'path' => '/subset:subset/subset:attribute_filter'),
			'@1' => array(
				'type' => 'xpath_palo_attribute_filter',
				'data_type' => 'string',
				'path' => '/subset:subset/subset:attribute_filter/subset:attribute_filters/subset:value/subset:filter_col',
				'param' => '/subset:subset/subset:attribute_filter/subset:attribute_filters/subset:parameter',
				'_objName' => 'attribute_filter'
			)
		)),
		'@9' => array('type' => 'function', 'function_def' => array(
			'_name' => 'PALO.DFILTER',
			'_objName' => 'data',
			'_isSet' => array('type' => 'xpath', 'path' => '/subset:subset/subset:data_filter'),
			'@1' => array(
				'type' => 'function',
				'function_def' => array(
					'_name' => 'PALO.SUBCUBE',
					'_objName' => 'subcube',
					'_isSet' => array('type' => 'xpath', 'path' => '/subset:subset/subset:data_filter/subset:subcube'),
					'@1' => array(
						'type' => 'xpath',
						'data_type' => 'palo_cube',
						'path' => '/subset:subset/subset:data_filter/subset:subcube/subset:source_cube/subset:value',
						'param' => '/subset:subset/subset:data_filter/subset:subcube/subset:source_cube/subset:parameter',
						'_objName' => 'source_cube'
					),
					'@2' => array(
						'type' => 'xpath_palo_cube_element',
						'path' => '/subset:subset/subset:data_filter/subset:subcube',
						'_objName' => 'subcube'
					)
				)
			),
			'@2' => array(
				'type' => 'xpath_palo_criteria',
				'path' => '/subset:subset/subset:data_filter/subset:criteria',
				'_objName' => 'criteria'
			),
			'@3' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:data_filter/subset:top/subset:value',
				'param' => '/subset:subset/subset:data_filter/subset:top/subset:parameter',
				'_objName' => 'top'
			),
			'@4' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:data_filter/subset:upper_percentage/subset:value',
				'param' => '/subset:subset/subset:data_filter/subset:upper_percentage/subset:parameter',
				'_objName' => 'upper_percentage'
			),
			'@5' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:data_filter/subset:lower_percentage/subset:value',
				'param' => '/subset:subset/subset:data_filter/subset:lower_percentage/subset:parameter',
				'_objName' => 'lower_percentage'
			),
			'@6' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:data_filter/subset:cell_operator/subset:value',
				'param' => '/subset:subset/subset:data_filter/subset:cell_operator/subset:parameter',
				'_objName' => 'cell_operator'
			)
		)),
		'@10' => array('type' => 'function', 'function_def' => array(
			'_name' => 'PALO.SORT',
			'_objName' => 'sort',
			'_isSet' => array('type' => 'xpath', 'path' => '/subset:subset/subset:sorting_filter'),
			'@1' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:sorting_filter/subset:whole/subset:value',
				'_objName' => 'whole'
			),
			'@2' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:sorting_filter/subset:sorting_criteria/subset:value',
				'param' => '/subset:subset/subset:sorting_filter/subset:sorting_criteria/subset:parameter',
				'_objName' => 'sorting_criteria'
			),
			'@3' => array(
				'type' => 'xpath',
				'data_type' => 'palo_attribute',
				'path' => '/subset:subset/subset:sorting_filter/subset:attribute/subset:value',
				'param' => '/subset:subset/subset:sorting_filter/subset:attribute/subset:parameter',
				'_objName' => 'attribute'
			),
			'@4' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:sorting_filter/subset:type_limitation/subset:value',
				'param' => '/subset:subset/subset:sorting_filter/subset:type_limitation/subset:parameter',
				'_objName' => 'type_limitation'
			),
			'@5' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:sorting_filter/subset:level/subset:value',
				'param' => '/subset:subset/subset:sorting_filter/subset:level/subset:parameter',
				'_objName' => 'level'
			),
			'@6' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:sorting_filter/subset:reverse/subset:value',
				'param' => '/subset:subset/subset:sorting_filter/subset:reverse/subset:parameter',
				'_objName' => 'reverse'
			),
			'@7' => array(
				'type' => 'xpath',
				'path' => '/subset:subset/subset:sorting_filter/subset:show_duplicates/subset:value',
				'_objName' => 'show_duplicates'
			)
		))
	);

	/* private methods */
	private static function _get_username_for_conn($connName)
	{
		try
		{
			 // read connection data
			$connection = palo::get_config_conn();
			$coordinates = array('name', 'type', 'description', 'host', 'port', 'userName', 'password', 'active', 'useLoginCred');
			array_unshift($coordinates,  1, count($coordinates));
			$connData = palo_datav($connection, 'Config', '#_connections', $coordinates, $connName);
			palo::palo_disconnect($connection);

			// test is connection type proper palo connection
			if (strtoupper($connData[3]) != 'PALO')
				throw new WSS_Exception('P1_12', array('conn_name' => $connName), 'Bad PALO connection type for connection name: ' . $connName);

			return $connData[7];
		}
		catch (WSS_Exception $wsse)
		{
			throw $wsse;
		}
		catch (Exception $e)
		{
			throw new WSS_Exception('P1_14', array('conn_name' => $connName), 'Unable to get user for connection name: ' . $connName);
		}
	}

	private static function _getPaloSubsetFunc($connName, $inConn, $inDbName, $inDimName, $descArr, $subsetDXPath)
	{
		$nodes = $subsetDXPath->query($descArr['_isSet']['path']);
		if ($nodes->length > 0)
		{
			$funcStr = $descArr['_name'] . '(';

			$loop = true;
			for ($i=1; $loop; $i++)
			{
				if (isset($descArr['@' . $i]))
				{
					$descElem = $descArr['@' . $i];
					$tmpSubExpresion = '';

					switch ($descElem['type'])
					{
						case 'function':
							$tmpSubExpresion = self::_getPaloSubsetFunc($connName, $inConn, $inDbName, $inDimName, $descElem['function_def'], $subsetDXPath);
							break;

						case 'xpath':
							$nodes = $subsetDXPath->query($descElem['path']);
							if (isset($descElem['param']))
							{
								$tmpParamNode = $subsetDXPath->query($descElem['param']);
								if ($tmpParamNode->length > 0)
									$nodes = $tmpParamNode;
							}

							if ($nodes->length == 1)
								$tmpSubExpresion = (isset($tmpParamNode) && ($tmpParamNode->length > 0)) ? $nodes->item(0)->nodeValue : self::_subsetFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item(0)->nodeValue, $descElem);
							else if ($nodes->length > 1)
							{
								$tmpSubExpresion = '{';
								for ($j=0; $j<$nodes->length; $j++)
									if (strlen($nodes->item($j)->nodeValue) > 0)
										$tmpSubExpresion .= (isset($tmpParamNode) && ($tmpParamNode->length > 0)) ? $nodes->item(0)->nodeValue : (($j < ($nodes->length - 1)) ? (self::_subsetFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->nodeValue, $descElem) . palo::$conf['paloSubesetFuncSeparator']) : self::_subsetFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->nodeValue, $descElem));

								$tmpSubExpresion .= '}';
							}
							break;

						case 'variable':
							switch ($descElem['var_name'])
							{
								case 'server/database':
									$tmpSubExpresion = $connName . '/' . $inDbName; // Only for testing
									break;

								case 'dimension':
									$tmpSubExpresion = $inDimName;
									break;
							}
							$tmpSubExpresion = self::_subsetFormatByDataType($inConn, $inDbName, $inDimName, $tmpSubExpresion, $descElem);
							break;

						case 'xpath_palo_attribute':
							$nodes = $subsetDXPath->query($descElem['path']);

							if ($nodes->length > 0)
								$nodes = $nodes->item(0)->childNodes;

							if ($nodes->length > 0)
							{
								$tmpSubExpresion = '{';
								for ($j=0; $j<$nodes->length; $j++)
								{
									if ($nodes->item($j)->childNodes->length > 1)
										$tmpSubExpresion .= ( (strtolower($nodes->item($j)->childNodes->item(0)->nodeName) == 'parameter') ? $nodes->item($j)->childNodes->item(0)->nodeValue : $nodes->item($j)->childNodes->item(1)->nodeValue ) . palo::$conf['paloSubesetFuncSeparator'];
									else if ($nodes->item($j)->childNodes->length > 0)
										$tmpSubExpresion .= self::_subsetFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->childNodes->item(0)->nodeValue, array('data_type' => 'palo_attribute')) . palo::$conf['paloSubesetFuncSeparator'];
								}

								$tmpSubExpresion = substr($tmpSubExpresion, ( ($nodes->length > 1) ? 0 : 1 ), -1) . ( ($nodes->length > 1) ? '}' : '' );
							}
							break;

						case 'xpath_palo_attribute_filter':
							$nodes = $subsetDXPath->query($descElem['path']);

							if (isset($descElem['param']))
								$tmpParamNode = $subsetDXPath->query($descElem['param']);

							if (isset($tmpParamNode) && ($tmpParamNode->length > 0))
								$tmpSubExpresion = $tmpParamNode->item(0)->nodeValue;
							else
							{
								$tmpSubExpresion = '{';
								for ($j=0; $j<$nodes->length; $j++)
									if ($nodes->item($j)->hasChildNodes() && strlen($nodes->item($j)->childNodes->item(0)->nodeValue) > 0)
										$tmpSubExpresion .= self::_subsetFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->childNodes->item(0)->nodeValue, array('data_type' => 'palo_attribute')) . palo::$conf['paloSubesetFuncSeparator'];

								if ($nodes->item(0)->childNodes->length > 1)
								{
									$tmpSubExpresion = substr($tmpSubExpresion, 0, -1);
									$tmpSubExpresion .= palo::$conf['paloSubesetFuncSeparatorArr'];
									for ($j=1; $j<$nodes->item(0)->childNodes->length; $j++)
									{
										for ($k=0; $k<$nodes->length; $k++)
										{
											$tmpSubExpresion .= ( (strlen($nodes->item($k)->childNodes->item($j)->nodeValue) > 0) ? self::_subsetFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($k)->childNodes->item($j)->nodeValue, $descElem) : '""' );
											if ($k < ($nodes->length - 1))
												$tmpSubExpresion .= palo::$conf['paloSubesetFuncSeparator'];
										}

										if ($j < ($nodes->item(0)->childNodes->length - 1))
											$tmpSubExpresion .= palo::$conf['paloSubesetFuncSeparatorArr'];
									}
								}
								else if ($nodes->length > 0)
								{
									$tmpSubExpresion = substr($tmpSubExpresion, 0, -1) . palo::$conf['paloSubesetFuncSeparatorArr'];
									for ($j=0; $j<$nodes->length; $j++)
										$tmpSubExpresion .= '""' . (($j < ($nodes->length - 1)) ? palo::$conf['paloSubesetFuncSeparator'] : '');
								}
								$tmpSubExpresion .= '}';
							}
							break;

						case 'xpath_palo_cube_element':
							$nodes = $subsetDXPath->query($descElem['path']);
							$tmpSubExpresion = '';

							$dimList = palo_cube_list_dimensions($inConn, $inDbName, palo_get_cube_name($inConn, $inDbName, $nodes->item(0)->childNodes->item(0)->childNodes->item(0)->nodeValue));
							for ($j=1; $j<=count($dimList); $j++)
							{
								// if parameter is set, then set parameter as value
								if ($nodes->item(0)->childNodes->item($j)->childNodes->length > 1)
									$tmpSubExpresion .= $nodes->item(0)->childNodes->item($j)->childNodes->item(0)->nodeValue;
								else
								{
									$numOfElementNodes = $nodes->item(0)->childNodes->item($j)->childNodes->item(0)->childNodes->length;

									if ($numOfElementNodes > 1)
										$tmpSubExpresion .= '{';

									for ($k = 0; $k < $numOfElementNodes; $k++)
									{
										if ($k > 0)
											$tmpSubExpresion .= palo::$conf['paloSubesetFuncSeparator'];

										$elemId = $nodes->item(0)->childNodes->item($j)->childNodes->item(0)->childNodes->item($k)->nodeValue;
										if ($elemId == -1)
										{
											if (strcmp($dimList[$j-1], $inDimName) != 0)
												$tmpSubExpresion .= '"*"';
										}
										else
											$tmpSubExpresion .= '"' . palo_get_element_name($inConn, $inDbName, $dimList[$j-1], $elemId) . '"';
									}

									if ($numOfElementNodes > 1)
										$tmpSubExpresion .= '}';
								}

								if ($j < count($dimList))
									$tmpSubExpresion .= palo::$conf['paloSubesetFuncSeparator'];
							}
							break;

						case 'xpath_palo_criteria':
							$nodes = $subsetDXPath->query($descElem['path']);

							if ($nodes->item(0)->childNodes->length > 0)
							{
								$tmpSubExpresion = '{';
								for ($j=0; $j<($nodes->item(0)->childNodes->length / 2); $j++)
								{
									$tmpSubExpresion .= '"' . $tmpOp = $nodes->item(0)->childNodes->item($j*2 + 1)->nodeValue . '"';
									$tmpSubExpresion .= palo::$conf['paloSubesetFuncSeparator'];

									$tmpPar = $nodes->item(0)->childNodes->item($j*2)->childNodes->item(0)->nodeValue;
									if ($tmpPar !== '0')
									{
										if ((0 + $tmpPar) === 0)
											$tmpSubExpresion .= '"' . $tmpPar . '"';
										else
											$tmpSubExpresion .= $tmpPar;
									}
									else
										$tmpSubExpresion .= $tmpPar;

									if ($j < ($nodes->item(0)->childNodes->length / 2 - 1))
										$tmpSubExpresion .= palo::$conf['paloSubesetFuncSeparator'];
								}
								$tmpSubExpresion .= '}';
							}
							break;
					}

					$funcStr .= $tmpSubExpresion . palo::$conf['paloSubesetFuncSeparator'];
				}
				else
					$loop = false;
			}

			if (strlen($funcStr) > strlen($descArr['_name'] . '('))
				$funcStr = substr($funcStr, 0, strlen($funcStr) - 1);

			$funcStr .= ')';

			// Workaround
			if (($descArr['_name'] == 'PALO.PICKLIST') && (strlen($funcStr) == 17))
				return '';

			return $funcStr;
		}
		else
			return '';
	}

	private static function _subsetFormatByDataType($inConn, $inDbName, $inDimName, $val, $descElem)
	{
		if (isset($descElem['data_type']))
		{
			switch ($descElem['data_type'])
			{
				case 'string':
					return '"' . $val . '"';

				case 'palo_attribute':
					if (is_numeric($val))
						return '"' . palo_get_element_name($inConn, $inDbName, '#_' . $inDimName . '_', $val) . '"';

					return $val;

				case 'palo_element':
					if (is_numeric($val))
						return '"' . palo_get_element_name($inConn, $inDbName, $inDimName, $val) . '"';

					return $val;

				case 'palo_cube':
					return '"' . palo_get_cube_name($inConn, $inDbName, $val) . '"';

				default:
					return $val;
			}
		}
		else
			return $val;
	}

	private static function _sortElemsInHierarchicalOrder(&$toArr, $listElems, $depth=0, $id=-1)
	{
		if (!isset($toArr))
			$toArr = array();

		foreach($listElems as $elem)
		{
			if ($elem['depth'] == $depth)
			{
				if ($elem['num_parents'] == 0)
				{
					if ($elem['num_children'] == 0)
						$toArr[] = $elem['name'];
					else
					{
						$toArr[] = array('n' => $elem['name'], 'l' => array());
						self::_sortElemsInHierarchicalOrder($toArr[count($toArr) - 1]['l'], $listElems, $depth+1, $elem['identifier']);
					}
				}
				else
				{
					foreach($elem['parents'] as $parentElem)
					{
						if ($parentElem['identifier'] == $id)
						{
							if ($elem['num_children'] == 0)
								$toArr[] = $elem['name'];
							else
							{
								$toArr[] = array('n' => $elem['name'], 'l' => array());
								self::_sortElemsInHierarchicalOrder($toArr[count($toArr) - 1]['l'], $listElems, $depth+1, $elem['identifier']);
							}
						}
					}
				}
			}
		}
	}

	private static function &_genHierarchicalOrder(&$vals, $levelSort =false, $isQuickPreview =false)
	{
		$dataList = array();

		$name = $vals[0]['name'];
		$curr_lvl = $vals[0]['ident'];
		$curr_lists = array($curr_lvl => &$dataList);

		for ($lvl_prev = $curr_lvl, $len = count($vals), $i = 1; $i < $len; $i++)
		{
			$lvl = $vals[$i]['ident'];

			if ((!$levelSort && ($lvl > $lvl_prev)) || ($levelSort && ($lvl < $lvl_prev)))
				if (!$isQuickPreview || count($curr_lists[$curr_lvl]) < palo::$conf['paloSubsetQucikPreviewSize'])
					$curr_lists[$lvl] = &$curr_lists[$curr_lvl][array_push($curr_lists[$curr_lvl], array('text' => $name, 'leaf' => false, 'children' => array())) - 1]['children'];
				else
					$curr_lists[$lvl] = &$curr_lists[$curr_lvl][count($curr_lists[$curr_lvl]) - 1]['children'];
			else
				if (!$isQuickPreview || count($curr_lists[$curr_lvl]) < palo::$conf['paloSubsetQucikPreviewSize'])
					$curr_lists[$curr_lvl][] = array('text' => $name, 'leaf' => true); //$name;

			$lvl_prev = $lvl;

			if (isset($curr_lists[$lvl]))
				$curr_lvl = $lvl;

			$name = $vals[$i]['name'];
		}

		if (!$isQuickPreview || count($curr_lists[$curr_lvl]) < palo::$conf['paloSubsetQucikPreviewSize'])
			$curr_lists[$curr_lvl][] = array('text' => $name, 'leaf' => true); //$name;

		return $dataList;
	}

	private static function _execPaloSubsetFunc($connName, $conn, $dbName, $dimName, &$subsetDXPath)
	{
		$execArr = array();

		// Check is there active Workbook - Then use Core to execute Subset Function - else use PHP Subset Execution mechanism
		$wsel_id = '';
		try
		{
			if (palo::getWsId())
				$res = json_decode(ccmd('[["ocurr",2]]'), true);

			if (isset($res) && is_array($res) && isset($res[0]) && $res[0][0])
			{
				$res = ccmd(array(
					array('wadd', '',
						array(
							'e_type' => 'sbst_exec',
							'n_refers_to' => '=' . self::_getPaloSubsetFunc($connName, $conn, $dbName, $dimName, self::$_paloSubsetDesc, $subsetDXPath)
						)
					)
				));

				if (is_array($res) && isset($res[0]) && $res[0][0] && isset($res[0][1]) && is_array($res[0][1]))
				{
					$wsel_id = $res[0][1][0];
					$res = ccmd(array(array('wget', '', array(), array('n_get_val'), array('e_id' => $wsel_id, 'e_type' => 'sbst_exec'))));

					if (is_array($res) && isset($res[0]) && $res[0][0] && isset($res[0][1]) && is_array($res[0][1]) && isset($res[0][1][0]) && is_array($res[0][1][0]))
					{
						$execArr = array();
						$sbstLst = &$res[0][1][0]['n_get_val'];

						if (!is_array($sbstLst))
						{
							ccmd(array(array('wdel', '', array($wsel_id))));
							throw new WSS_Exception('P1_18', array(), 'Unable to generate Subset List!');
						}

						$numOfRows = count($sbstLst);
						for ($i = 0; $i < $numOfRows; $i+=3)
							$execArr[] = array('name' => $sbstLst[$i], 'alias' => $sbstLst[$i + 1], 'ident' => $sbstLst[$i + 2]);
					}
					else
						$execArr = self::_execPHPPaloSubsetFunc($conn, $dbName, $dimName, self::$_paloSubsetDesc, $subsetDXPath);

					ccmd(array(array('wdel', '', array($wsel_id))));
				}
				else
					$execArr = self::_execPHPPaloSubsetFunc($conn, $dbName, $dimName, self::$_paloSubsetDesc, $subsetDXPath);
			}
			else
				$execArr = self::_execPHPPaloSubsetFunc($conn, $dbName, $dimName, self::$_paloSubsetDesc, $subsetDXPath);
		}
		catch (Exception $e)
		{
			if (!empty($wsel_id))
				ccmd(array(array('wdel', '', array($wsel_id))));

			$execArr = self::_execPHPPaloSubsetFunc($conn, $dbName, $dimName, self::$_paloSubsetDesc, $subsetDXPath);
		}

		if (!is_array($execArr))
			throw new WSS_Exception('P1_18', array(), 'Unable to generate Subset List!');

		return $execArr;
	}

	public static function cleanSubsetWsels()
	{
		$res = ccmd(array(array('wget', '', array(), array('e_id'), array('e_type' => 'sbst_exec'))));

		if (is_array($res) && isset($res[0]) && $res[0][0] && isset($res[0][1]) && is_array($res[0][1]) && count($res[0][1]) > 0)
		{
			$list = $res[0][1];

			$ccmd = array();
			foreach($list as $wsel)
				$ccmd[] = array('wdel', '', array($wsel['e_id']));

			ccmd($ccmd);
		}
	}

	private static function _execPHPPaloSubsetFunc($inConn, $inDbName, $inDimName, $descArr, $subsetDXPath)
	{
		$nodes = $subsetDXPath->query($descArr['_isSet']['path']);
		if ($nodes->length > 0)
		{
			$funcNameStr = strtolower(str_replace('.', '_', $descArr['_name']));
			$tmpFuncArgs = array();

			$loop = true;
			for ($i=1; $loop; $i++)
			{
				if (isset($descArr['@' . $i]))
				{
					$descElem = $descArr['@' . $i];

					switch ($descElem['type'])
					{
						case 'function':
							$tmpFuncArgs[] = self::_execPHPPaloSubsetFunc($inConn, $inDbName, $inDimName, $descElem['function_def'], $subsetDXPath);
							break;

						case 'xpath':
							$nodes = $subsetDXPath->query($descElem['path']);

							if ($nodes->length == 1)
								$tmpFuncArgs[] = self::_subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item(0)->nodeValue, $descElem);
							else if ($nodes->length > 1)
							{
								$tmpArr = array();
								for ($j=0; $j<$nodes->length; $j++)
									if (strlen($nodes->item($j)->nodeValue) > 0)
										$tmpArr[] = (($j < ($nodes->length - 1)) ? (self::_subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->nodeValue, $descElem)) : self::_subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->nodeValue, $descElem));

								$tmpFuncArgs[] = $tmpArr;
							}
							else
								$tmpFuncArgs[] = null;

							break;

						case 'variable':
							switch ($descElem['var_name'])
							{
								case 'server/database':
									$tmpVar = $inConn;
									break;

								case 'dimension':
									$tmpVar = $inDimName;
									break;
							}
							$tmpFuncArgs[] = self::_subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $tmpVar, $descElem);
							break;

						case 'xpath_palo_attribute':
							$nodes = $subsetDXPath->query($descElem['path']);

							if ($nodes->length > 0)
								$nodes = $nodes->item(0)->childNodes;

							if ($nodes->length > 0)
							{
								$tmpArr = array();
								for ($j=0; $j<$nodes->length; $j++)
								{
									if ($nodes->item($j)->childNodes->length > 1)
									{
										if (strtolower($nodes->item($j)->childNodes->item(0)->nodeName) == 'value')
											$tmpArr[] = self::_subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->childNodes->item(0)->nodeValue, array('data_type' => 'palo_attribute'));
										else
											$tmpArr[] = self::_subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->childNodes->item(1)->nodeValue, array('data_type' => 'palo_attribute'));
									}
									else
										$tmpArr[] = self::_subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->childNodes->item(0)->nodeValue, array('data_type' => 'palo_attribute'));
								}

								$tmpFuncArgs[] = $tmpArr;
							}
							else
								$tmpFuncArgs[] = null;

							break;

						case 'xpath_palo_attribute_filter':
							$nodes = $subsetDXPath->query($descElem['path']);

							if ($nodes->length > 0)
							{
								$tmpArr = array();
								$tmpArr[] = ($nodes->item(0)->childNodes->length == 1) ? 2 : $nodes->item(0)->childNodes->length;
								$tmpArr[] = $nodes->length;
								for ($j=0; $j<$nodes->length; $j++)
									if ($nodes->item($j)->hasChildNodes() && (strlen($nodes->item($j)->childNodes->item(0)->nodeValue) > 0))
										$tmpArr[] = self::_subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($j)->childNodes->item(0)->nodeValue, array('data_type' => 'palo_attribute'));

								if ($nodes->item(0)->childNodes->length > 1)
								{
									for ($j=1; $j<$nodes->item(0)->childNodes->length; $j++)
									{
										for ($k=0; $k < $nodes->length; $k++)
											if (strlen($nodes->item($k)->childNodes->item($j)->nodeValue) > 0)
												$tmpArr[] = self::_subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $nodes->item($k)->childNodes->item($j)->nodeValue, $descElem);
											else
												$tmpArr[] = null;
									}
								}
								else if ($nodes->item(0)->childNodes->length == 1)
								{
									for ($j=0; $j<$nodes->length; $j++)
										$tmpArr[] = null;
								}

								$tmpFuncArgs[] = $tmpArr;
							}
							break;

						case 'xpath_palo_cube_element':
							$nodes = $subsetDXPath->query($descElem['path']);

							$dimList = palo_cube_list_dimensions($inConn, $inDbName, palo_get_cube_name($inConn, $inDbName, $nodes->item(0)->childNodes->item(0)->childNodes->item(0)->nodeValue));
							for ($j=1; $j<=count($dimList); $j++)
							{
								$tmpArr = array();
								for ($k=0; $k<$nodes->item(0)->childNodes->item($j)->childNodes->item(0)->childNodes->length; $k++)
								{
									$elemId = $nodes->item(0)->childNodes->item($j)->childNodes->item(0)->childNodes->item($k)->nodeValue;
									if ($elemId == -1)
										$tmpArr = (strcmp($dimList[$j-1], $inDimName) != 0) ? ELEMENTS_ALL : NULL;
									else
									{
										if ($nodes->item(0)->childNodes->item($j)->childNodes->item(0)->childNodes->length > 1)
											$tmpArr[] = palo_get_element_name($inConn, $inDbName, $dimList[$j-1], intval($elemId));
										else
											$tmpArr = palo_get_element_name($inConn, $inDbName, $dimList[$j-1], intval($elemId));
									}
								}
								$tmpFuncArgs[] = $tmpArr;
							}
							break;

						case 'xpath_palo_criteria':
							$nodes = $subsetDXPath->query($descElem['path']);

							if ($nodes->item(0)->childNodes->length > 0)
							{
								$tmpArr = array();
								for ($j=0; $j<($nodes->item(0)->childNodes->length / 2); $j++)
								{
									$tmpArr[] = ($tmpOp = $nodes->item(0)->childNodes->item($j*2 + 1)->nodeValue);

									$tmpPar = $nodes->item(0)->childNodes->item($j*2)->childNodes->item(0)->nodeValue;
									$tmpArr[] = $tmpPar;
								}
								$tmpFuncArgs[] = $tmpArr;
							}
							else
								$tmpFuncArgs[] = null;

							break;
					}
				}
				else
					$loop = false;
			}

			if ($descArr['_hb_hasDbName'])
				array_splice($tmpFuncArgs, 1, 0, $inDbName); // Database name is on 2nd position of function

			// Workaround for AFILTER
			if ($funcNameStr == 'palo_afilter')
				$tmpRetVal = (empty($tmpFuncArgs)) ? null : call_user_func_array($funcNameStr, $tmpFuncArgs);
			else
				$tmpRetVal = call_user_func_array($funcNameStr, $tmpFuncArgs);

			return $tmpRetVal;
		}
		else
			return null;
	}

	private static function _subsetExecPHPFormatByDataType($inConn, $inDbName, $inDimName, $val, $descElem)
	{
		if (isset($descElem['data_type']))
		{
			switch ($descElem['data_type'])
			{
				case 'palo_attribute':
					$val = (is_array($val) ? $val[0] : $val);
					return palo_get_element_name($inConn, $inDbName, '#_' . $inDimName . '_', $val);

				case 'palo_element':
					return palo_get_element_name($inConn, $inDbName, $inDimName, $val);

				case 'palo_cube':
					return palo_get_cube_name($inConn, $inDbName, $val);

				case 'bool':
					return ((strtoupper($val) == 'TRUE') ? true : false);

				default:
					return $val;
			}
		}
		else
			return $val;
	}

	private static function _genPaloSubsetXML(&$dataArr, $setupArr =null)
	{
		$xmlDoc = new DOMDocument();
		$xmlDoc->preserveWhiteSpace = false;
		self::_fixPaloSubsetInObject($dataArr, $setupArr);
		self::_genXmlFromArr($xmlDoc, $xmlDoc, $dataArr);

		$docXslt = new DOMDocument();
		$xsl = new XSLTProcessor();

		if (is_file(palo::$conf['paloSubsetGrammarFile']))
			$docXslt->load(palo::$conf['paloSubsetGrammarFile']);
		else if (is_file(palo::$conf['paloSubsetGrammarFile2']))
			$docXslt->load(palo::$conf['paloSubsetGrammarFile2']);
		else
			throw new Exception('Can not find "subset_grammar.xslt" file!');
		$xsl->importStyleSheet($docXslt);

		$xmlDoc = $xsl->transformToDoc($xmlDoc);
		$xmlDoc->removeChild($xmlDoc->firstChild);
		$tmpNode = $xmlDoc->createProcessingInstruction('palosubset', 'version="1.0"');
		$xmlDoc->insertBefore($tmpNode, $xmlDoc->firstChild);

		return $xmlDoc->saveXML();
	}

	// fixing some data for Data Arrays with variables
	private static function _fixPaloSubsetInObject(&$dataArr, $setupArr)
	{
		if ($setupArr != null)
		{
			$conn = $setupArr['conn'];
			$dbName = $setupArr['db_name'];
			$dimName = $setupArr['dim_name'];

			$subset =& $dataArr['subset'];

			// general
			if (isset($subset['alias1']) && isset($subset['alias1']['param']))
				$subset['alias1']['value'] = palo_eindex($conn, $dbName, '#_' . $dimName . '_', $subset['alias1']['value']) - 1;
			if (isset($subset['alias2']) && isset($subset['alias2']['param']))
				$subset['alias2']['value'] = palo_eindex($conn, $dbName, '#_' . $dimName . '_', $subset['alias2']['value']) - 1;

			// hier
			if (isset($subset['hier']))
			{
				if (isset($subset['hier']['above']))
					$subset['hier']['above']['value'] = ($subset['hier']['above']['value']) ? 'true' : 'false';

				if (isset($subset['hier']['exclusive']))
					$subset['hier']['exclusive']['value'] = ($subset['hier']['exclusive']['value']) ? 'true' : 'false';

				// element identifier
				if (isset($subset['hier']['element']))
					$sub_name = 'element';
				else if (isset($subset['hier']['revolve_element']))
					$sub_name = 'revolve_element';
				if (isset($subset['hier']['element']) || isset($subset['hier']['revolve_element']))
					$subset['hier'][$sub_name]['value'] = palo_get_element_id($conn, $dbName, $dimName, $subset['hier'][$sub_name]['value']);
			}
			// text
			if (isset($subset['text']))
			{
				if (!is_array($subset['text']['regexes']['value']))
					$subset['text']['regexes']['value'] = array($subset['text']['regexes']['value']);
			}
			// picklist
			if (isset($subset['pick']))
			{
				$tmpList =& $subset['pick']['elems']['value'];

				if (is_array($tmpList))
					foreach($tmpList as $key => $val)
						$tmpList[$key] = palo_get_element_id($conn, $dbName, $dimName, $val);
				else
					$tmpList = palo_get_element_id($conn, $dbName, $dimName, $tmpList);
			}
			// attribute
			if (isset($subset['attr']))
			{
				if (isset($subset['attr']['attribute_filter']) && is_array($subset['attr']['attribute_filter']['value']))
				{
					$attribs = palo_dimension_list_elements($conn, $dbName, '#_' . $dimName . '_');

					$tmpArr = array(); $numOfAttrs = count($attribs); $tmpVals = $subset['attr']['attribute_filter']['value'];
					for ($i=0; $i<$numOfAttrs; $i++)
					{
						$tmpArr[$attribs[$i]['identifier']] = array();
						$numOfRows = count($tmpVals) / $numOfAttrs;
						for ($j=0; $j<$numOfRows; $j++)
							$tmpArr[$attribs[$i]['identifier']][] = $tmpVals[$i*$numOfRows+$j];
					}

					$subset['attr']['attribute_filter']['value'] = $tmpArr;
				}
			}
			// data
			if (isset($subset['data']))
			{
				if (isset($subset['data']['subcube']) && isset($subset['data']['subcube']['subcube']))
				{
					$cubeDims = palo_cube_info($conn, $dbName, $subset['data']['subcube']['source_cube']['value']);
					$cubeDims = $cubeDims['dimensions'];

					for ($i=0; $i<count($subset['data']['subcube']['subcube']); $i++)
					{
						$dimValues =& $subset['data']['subcube']['subcube'][$i]['value'];
						if ($dimValues != '*')
						{
							if (is_array($dimValues))
							{
								for ($j=0; $j<count($dimValues); $j++)
									$dimValues[$j] = palo_get_element_id($conn, $dbName, $cubeDims[$i], $dimValues[$j]);
							}
							else
								$dimValues = palo_get_element_id($conn, $dbName, $cubeDims[$i], $dimValues);
						}
						else
							$dimValues = -1;
					}
				}

				if (isset($subset['data']['subcube']) && isset($subset['data']['subcube']['source_cube']))
					$subset['data']['subcube']['source_cube']['value'] = palo_get_cube_id($conn, $dbName, $subset['data']['subcube']['source_cube']['value']);
			}
			// Sort
			if (isset($subset['sort']['attribute']) && (isset($subset['sort']['attribute']['param'])) && ($setupArr != null))
				$subset['sort']['attribute']['value'] = palo_eindex($conn, $dbName, '#_' . $dimName . '_', $subset['sort']['attribute']['value']) - 1;
		}
	}

	private static function _fixPaloSubsetOutObject(&$dataArr, $setupArr)
	{
		if (isset($dataArr['subset']) && isset($setupArr))
		{
			$conn = $setupArr['conn'];
			$dbName = $setupArr['db_name'];
			$dimName = $setupArr['dim_name'];

			$subset =& $dataArr['subset'];

			// general
			if (isset($subset['attribs']))
			{
				if (is_array($subset['attribs']['value']))
				{
					$subset['alias1'] = array('value' => $subset['attribs']['value'][0]);
					$subset['alias2'] = array('value' => $subset['attribs']['value'][1]);
				}
				else if ($subset['attribs']['value'] != null)
					$subset['alias1'] = array('value' => $subset['attribs']['value']);

				if (is_array($subset['attribs']['param']))
				{
					$subset['alias1']['param'] = $subset['attribs']['param'][0];
					$subset['alias2']['param'] = $subset['attribs']['param'][1];
				}
				else if ($subset['attribs']['param'] != null)
					$subset['alias1']['param'] = $subset['attribs']['param'];

				unset($subset['attribs']);
			}

			// hier
			if (isset($subset['hier']))
			{
				// element identifier
				if (isset($subset['hier']['element']))
					$sub_name = 'element';
				else if (isset($subset['hier']['revolve_element']))
					$sub_name = 'revolve_element';
				if (isset($subset['hier']['element']) || isset($subset['hier']['revolve_element']))
					$subset['hier'][$sub_name]['value'] = palo_get_element_name($conn, $dbName, $dimName, $subset['hier'][$sub_name]['value']);
			}

			// picklist
			if (isset($subset['pick']) && isset($subset['pick']['elems']))
			{
				if (is_array($subset['pick']['elems']['value']))
				{
					foreach ($subset['pick']['elems']['value'] as $key => $val)
						$subset['pick']['elems']['value'][$key] = palo_get_element_name($conn, $dbName, $dimName, $val);
				}
				else
					$subset['pick']['elems']['value'] = palo_get_element_name($conn, $dbName, $dimName, $subset['pick']['elems']['value']);
			}

			// Data
			if (isset($subset['data']) && isset($subset['data']['subcube']) && isset($subset['data']['subcube']['source_cube']))
				$subset['data']['subcube']['source_cube']['value'] = palo_get_cube_name($conn, $dbName, $subset['data']['subcube']['source_cube']['value']);

			// Sort
			if (isset($subset['sort']) && isset($subset['sort']['attribute']))
			{
				if (empty($subset['sort']['attribute']['value']))
					$subset['sort']['attribute']['value'] = 0;
			}
		}

		return $inArr;
	}

	private static function _getPaloSubsetObject($connName, $inConn, $inDbName, $inDimName, $descArr, $subsetDXPath)
	{
		$nodes = $subsetDXPath->query($descArr['_isSet']['path']);
		if ($nodes->length > 0)
		{
			$loop = true;
			for ($i=1; $loop; $i++)
			{
				if (isset($descArr['@' . $i]))
				{
					$descElem = $descArr['@' . $i];
					$tmpSubArr = array();

					switch ($descElem['type'])
					{
						case 'function':
							$tmpSubArr = self::_getPaloSubsetObject($connName, $inConn, $inDbName, $inDimName, $descElem['function_def'], $subsetDXPath);
							break;

						case 'xpath':
							$nodes = $subsetDXPath->query($descElem['path']);
							if (isset($descElem['param']))
							{
								$tmpParamNodes = $subsetDXPath->query($descElem['param']);
								if ($tmpParamNodes->length == 1)
									$paramVarName = $tmpParamNodes->item(0)->nodeValue;
								else if ($tmpParamNodes->length > 1)
								{
									$paramVarName = array();
									for ($j=0; $j<$tmpParamNodes->length; $j++)
										$paramVarName[] = $tmpParamNodes->item($j)->nodeValue;
								}
							}

							if ($nodes->length == 1)
								$tmpSubArr[$descElem['_objName']] = array('value' => $nodes->item(0)->nodeValue, 'param' => ((isset($paramVarName)) ? $paramVarName : null));
							else if ($nodes->length > 1)
							{
								$tmpSubArr[$descElem['_objName']] = array('value' => array(), 'param' => ((isset($paramVarName)) ? $paramVarName : null));
								for ($j=0; $j<$nodes->length; $j++)
									if (strlen($nodes->item($j)->nodeValue) > 0)
										$tmpSubArr[$descElem['_objName']]['value'][] = $nodes->item($j)->nodeValue;
							}

							if (isset($paramVarName))
								unset($paramVarName);

							break;

						case 'variable':
							switch ($descElem['var_name'])
							{
								case 'server/database':
									$tmpSubArr[$descElem['_objName']] = $connName . '/' . $inDbName;
									break;

								case 'dimension':
									$tmpSubArr[$descElem['_objName']] = $inDimName;
									break;
							}
							break;

						case 'xpath_palo_attribute':
							$nodes = $subsetDXPath->query($descElem['path']);

							if ($nodes->length > 0)
							{
								$nodes = $nodes->item($j)->childNodes;
								for ($j=0; $j<$nodes->length; $j++)
								{
									if ($nodes->item($j)->childNodes->length > 1)
									{
										if (strtolower($nodes->item($j)->childNodes->item(0)->nodeName) == 'value')
											$tmpSubArr[$nodes->item($j)->nodeName] = array(
												'value' => $nodes->item($j)->childNodes->item(0)->nodeValue,
												'param' => $nodes->item($j)->childNodes->item(1)->nodeValue
											);
										else
											$tmpSubArr[$nodes->item($j)->nodeName] = array(
												'value' => $nodes->item($j)->childNodes->item(1)->nodeValue,
												'param' => $nodes->item($j)->childNodes->item(0)->nodeValue
											);
									}
									else
										$tmpSubArr[$nodes->item($j)->nodeName] = array(
											'value' => $nodes->item($j)->childNodes->item(0)->nodeValue
										);
								}
							}
							break;

						case 'xpath_palo_attribute_filter':
							$nodes = $subsetDXPath->query($descElem['path']);

							if (isset($descElem['param']))
							{
								$tmpParamNodes = $subsetDXPath->query($descElem['param']);
								if ($tmpParamNodes->length == 1)
									$paramVarName = $tmpParamNodes->item(0)->nodeValue;
								else if ($tmpParamNodes->length > 1)
								{
									$paramVarName = array();
									for ($j=0; $j<$tmpParamNodes->length; $j++)
										$paramVarName[] = $tmpParamNodes->item($j)->nodeValue;
								}
							}

							$tmpSubArr[$descElem['_objName']] = array('value' => array(), 'param' => ((isset($paramVarName)) ? $paramVarName : null));

							for ($j=0; $j<$nodes->length; $j++)
							{
								$numOfChilds = $nodes->item($i)->childNodes->length;
								for ($k=1; $k<$numOfChilds; $k++)
								{
									if (strlen($nodes->item($j)->childNodes->item($k)->nodeValue) > 0)
										$tmpSubArr[$descElem['_objName']]['value'][] = $nodes->item($j)->childNodes->item($k)->nodeValue;
									else
										$tmpSubArr[$descElem['_objName']]['value'][] = '';
								}
							}
							break;

						case 'xpath_palo_cube_element':
							$nodes = $subsetDXPath->query($descElem['path']);
							$tmpSubArr[$descElem['_objName']] = array();

							$dimList = palo_cube_list_dimensions($inConn, $inDbName, palo_get_cube_name($inConn, $inDbName, $nodes->item(0)->childNodes->item(0)->childNodes->item(0)->nodeValue));
							for ($j=1; $j<=count($dimList); $j++)
							{
								$dimCord = $nodes->item(0)->childNodes->item($j);
								$serialNumber = count($tmpSubArr[$descElem['_objName']]);

								if ($dimCord->childNodes->length > 1)
								{
									$tmpSubArr[$descElem['_objName']][$serialNumber]['param'] = $dimCord->childNodes->item(0)->nodeValue;
									$elems = $dimCord->childNodes->item(1)->childNodes;
								}
								else
									$elems = $dimCord->childNodes->item(0)->childNodes;

								for ($k=0; $k<$elems->length; $k++)
								{
									$elemId =  $elems->item($k)->nodeValue;
									if ($elemId == -1)
										$tmpSubArr[$descElem['_objName']][$serialNumber]['value'] = '*';
									else
									{
										$elemName = palo_get_element_name($inConn, $inDbName, $dimList[$j-1], $elemId);
										if ($k > 0)
										{
											if ($k == 1)
												$tmpSubArr[$descElem['_objName']][$serialNumber]['value'] = array($tmpSubArr[$descElem['_objName']][$serialNumber]['value'], $elemName);
											else
												array_push($tmpSubArr[$descElem['_objName']][$serialNumber]['value'], $elemName);
										}
										else
											$tmpSubArr[$descElem['_objName']][$serialNumber]['value'] = $elemName;
									}
								}
							}
							break;

						case 'xpath_palo_criteria':
							$nodes = $subsetDXPath->query($descElem['path']);

							if ($nodes->item(0)->childNodes->length > 0)
							{
								$tmpSubArr[$descElem['_objName']] = array();
								for ($j=0; $j<($nodes->item(0)->childNodes->length / 2); $j++)
								{
									$tmpSubArr[$descElem['_objName']][] = $tmpOp = $nodes->item(0)->childNodes->item($j*2 + 1)->nodeValue;
									$parNodes = $nodes->item(0)->childNodes->item($j*2)->childNodes;
									if ($parNodes->length > 1)
										$tmpSubArr[$descElem['_objName']][] = array(
											'value' => $parNodes->item(1)->nodeValue,
											'param' => $parNodes->item(0)->nodeValue
										);
									else
										$tmpSubArr[$descElem['_objName']][] = array(
											'value' => $parNodes->item(0)->nodeValue,
											'param' => null
										);
								}
							}
							break;
					}

					foreach ($tmpSubArr as $key => $val)
						$funcArr[$descArr['_objName']][$key] = $val;
				}
				else
					$loop = false;
			}

			return $funcArr;
		}
		else
			return array();
	}

	private static function _genXmlFromArr($xmlDoc, $node, $arr)
	{
		foreach($arr as $key => $val)
		{
			$tagName = (is_numeric($key)) ? 'elem' : $key;

			$tmpElem = $xmlDoc->createElement($tagName);
			$newNode = $node->appendChild($tmpElem);
			$newNode->setAttribute('id', $key);

			if (is_array($val))
				self::_genXmlFromArr($xmlDoc, $newNode, $val);
			else
				$newNode->setAttribute('value', $val);
		}
	}

	/* public methods */
	public static function getDimAttrs($connName, $dbName, $dimName)
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
			$listElemsOut[] = array('id' => $listElems[$i]['identifier'], 'name' => $listElems[$i]['name']);

		return $listElemsOut;
	}

	public static function getSubsetNames($connName, $dbName, $dimName)
	{
		$conn = palo::palo_init($connName);
		$listSubset = palo_dimension_list_elements($conn, $dbName, '#_SUBSET_', true);

		$listDimGlobalSubsets = array();
		$listDimLocalSubsets = array();
		foreach($listSubset as $subset)
		{
			if (palo_data($conn, $dbName, '#_SUBSET_GLOBAL', $dimName, $subset['name']) != null)
				$listDimGlobalSubsets[] = $subset['name'];
			if (palo_data($conn, $dbName, '#_SUBSET_LOCAL', $dimName, self::_get_username_for_conn($connName), $subset['name']) != null)
				$listDimLocalSubsets[] = $subset['name'];
		}
		palo::palo_disconnect($conn);

		return array($listDimLocalSubsets, $listDimGlobalSubsets);
	}

	public static function handlerGetGeneratedSubsetFunc($arrSet, $dimName, $subsetName, $subsetType, $subsetDefArr =null)
	{
		$connName = $arrSet[4];
		$dbName = $arrSet[5];

		$conn = palo::palo_init($connName);

		$retStr = '';
		if ($subsetType == 1)
			$retStr = palo_data($conn, $dbName, '#_SUBSET_LOCAL', $dimName, self::_get_username_for_conn($connName), $subsetName);
		else if ($subsetType == 2)
			$retStr = palo_data($conn, $dbName, '#_SUBSET_GLOBAL', $dimName, $subsetName);
		else if ($subsetType == 0 && $subsetDefArr != null)
			$retStr = self::_genPaloSubsetXML($subsetDefArr, array('conn' => $conn, 'db_name' => $dbName, 'dim_name' => $dimName));

		$subsetInfo = new DOMDocument();
		$subsetInfo->preserveWhiteSpace = false;
		$subsetInfo->loadXML($retStr);

		$subsetDXPath = new DOMXPath($subsetInfo);
		$subsetDXPath->registerNameSpace('subset', 'http://www.jedox.com/palo/SubsetXML');
		$retStr = self::_getPaloSubsetFunc($connName, $conn, $dbName, $dimName, self::$_paloSubsetDesc, $subsetDXPath);
		$retStr = '=' . $retStr;
		palo::palo_disconnect($conn);

		return array(array('saf', array($arrSet[0], $arrSet[1], $arrSet[2], $arrSet[3], $retStr)));
	}

	public static function getSubsetList($genData, $forceList =0)
	{
		$connName = $genData['serv_id'];
		$dbName = $genData['db_name'];

		$conn = palo::palo_init($connName);

		$hierOrder = false;
		if ($genData['subset_type'] == 0)
		{
			$listElems = palo_dimension_list_elements2($conn, $dbName, $genData['dim_name'], true);
			palo::palo_disconnect($conn);

			if ((!$forceList) && $genData['layouthier'])
			{
				$hierOrder = true;
				self::_sortElemsInHierarchicalOrder($retArr, $listElems);
			}
			else
			{
				$retArr = array();
				for ($i=0; $i<count($listElems); $i++)
					$retArr[] = $listElems[$i]['name'];
			}
		}
		else
		{
			$retStr = '';
			if ($genData['subset_type'] == 1)
				$retStr = palo_data($conn, $dbName, '#_SUBSET_LOCAL', $genData['dim_name'], self::_get_username_for_conn($connName),  $genData['subset_name']);
			else if ($genData['subset_type'] == 2)
				$retStr = palo_data($conn, $dbName, '#_SUBSET_GLOBAL', $genData['dim_name'], $genData['subset_name']);

			$subsetInfo = new DOMDocument();
			$subsetInfo->preserveWhiteSpace = false;
			$subsetInfo->loadXML($retStr);

			$subsetDXPath = new DOMXPath($subsetInfo);
			$subsetDXPath->registerNameSpace('subset', 'http://www.jedox.com/palo/SubsetXML');
			$execArr = self::_execPaloSubsetFunc($connName, $conn, $dbName, $genData['dim_name'], $subsetDXPath);
			palo::palo_disconnect($conn);

			// Generate hierarchical array
			$nodes = $subsetDXPath->query('/subset:subset/subset:sorting_filter/subset:whole/subset:value | /subset:subset/subset:sorting_filter/subset:reverse/subset:value | /subset:subset/subset:indent/subset:value');
			$hierOrder = ((!$forceList) && ($nodes->length == 3) && ($nodes->item(1)->nodeValue == '1') && ($nodes->item(2)->nodeValue != '1'));
			if ($hierOrder)
				$retArr = self::_genHierarchicalOrder($execArr, ($nodes->item(0)->nodeValue == '2'), $genData['quick_preview']);
			else
			{
				$retArr = array();
				$upTo = ($genData['quick_preview'] && (count($execArr) > palo::$conf['paloSubsetQucikPreviewListSize'])) ? palo::$conf['paloSubsetQucikPreviewListSize'] : count($execArr);
				for ($i=0; $i<$upTo; $i++)
					$retArr[] = $execArr[$i]['name'];
			}
		}

		return array($hierOrder, $retArr);
	}

	public static function setDynarangeList($hbConf)
	{
		$genData = $hbConf['_gendata'];
		$retArr = self::handlerGetGeneratedSubsetFunc(array(0, 0, 0, 0, $genData[0][0], $genData[0][1]), $genData[0][2], '', 0, $genData[1]);

		return $retArr[0][1][4];
	}

	public static function getSubsetDialogData($inArr)
	{
		$connName = $inArr[0];
		$dbName = $inArr[1];
		$dimName = $inArr[2];
		$subsetName = $inArr[3];
		$subsetType = $inArr[4];

		$conn = palo::palo_init($connName);

		$retStr = '';
		if ($subsetType == 1)
			$retStr = palo_data($conn, $dbName, '#_SUBSET_LOCAL', $dimName, self::_get_username_for_conn($connName), $subsetName);
		else if ($subsetType == 2)
			$retStr = palo_data($conn, $dbName, '#_SUBSET_GLOBAL', $dimName, $subsetName);

		$subsetInfo = new DOMDocument();
		$subsetInfo->preserveWhiteSpace = false;
		$subsetInfo->loadXML($retStr);

		$subsetDXPath = new DOMXPath($subsetInfo);
		$subsetDXPath->registerNameSpace('subset', 'http://www.jedox.com/palo/SubsetXML');
		$ret = self::_getPaloSubsetObject($connName, $conn, $dbName, $dimName, self::$_paloSubsetDesc, $subsetDXPath);
		self::_fixPaloSubsetOutObject($ret, array('conn' => $conn, 'db_name' => $dbName, 'dim_name' => $dimName));
		palo::palo_disconnect($conn);

		return $ret;
	}

	public static function getSubsetListByXML($inArr, $forceList =false)
	{
		// +++ init vars +++ //
		$settings = $inArr[0];
		$dataArr = $inArr[1];

		$connName = $settings[0];
		$dbName = $settings[1];
		$dimName = $settings[2];
		$quickPreview = (isset($settings[3])) ? $settings[3] : false;

		$hierOrder = false;
		// --- init vars --- //

		$conn = palo::palo_init($connName);

		$xmlDoc = new DOMDocument();
		$xmlDoc->preserveWhiteSpace = false;
		$xmlStr = self::_genPaloSubsetXML($dataArr, array('conn' => $conn, 'db_name' => $dbName, 'dim_name' => $dimName));
		$xmlDoc->loadXML($xmlStr);

		$subsetDXPath = new DOMXPath($xmlDoc);
		$subsetDXPath->registerNameSpace('subset', 'http://www.jedox.com/palo/SubsetXML');
		$execArr = self::_execPaloSubsetFunc($connName, $conn, $dbName, $dimName, $subsetDXPath);
		palo::palo_disconnect($conn);

		$nodes = $subsetDXPath->query('/subset:subset/subset:sorting_filter/subset:whole/subset:value | /subset:subset/subset:sorting_filter/subset:reverse/subset:value | /subset:subset/subset:indent/subset:value');
		$hierOrder = ((!$forceList) && ($nodes->length == 3) && ($nodes->item(1)->nodeValue == '1') && ($nodes->item(2)->nodeValue != '1'));
		if ($hierOrder)
			$retArr = self::_genHierarchicalOrder($execArr, ($nodes->item(0)->nodeValue == '2'), $quickPreview);
		else
		{
			$retArr = array();
			$upTo = ($quickPreview && (count($execArr) > palo::$conf['paloSubsetQucikPreviewListSize'])) ? palo::$conf['paloSubsetQucikPreviewListSize'] : count($execArr);
			for ($i=0; $i<$upTo; $i++)
				$retArr[] = $execArr[$i]['name'];
		}

		return array($hierOrder, $retArr);
	}

	public static function savePaloSubset($inArr)
	{
		try
		{
			// +++ init vars +++ //
			$settings = $inArr[0];
			$dataArr = $inArr[1];

			$connName = $settings[0];
			$dbName = $settings[1];
			$dimName = $settings[2];
			$subsetName = $settings[3];
			$subsetType = $settings[4];
			// --- init vars --- //

			$conn = palo::palo_init($connName);
			$result = palo_eindex($conn, $dbName, '#_SUBSET_', $subsetName, true);
			if ($result == '')
				$result = palo_eadd($conn, $dbName, '#_SUBSET_', 'S', $subsetName, '', 1, FALSE, true);

			if ($result)
			{
				$dataArr['subset']['id'] = -1; // TODO: should be assinged proper ID number
				$dataArr['subset']['sourceDimensionId'] = 2;
				if ($subsetType == 2)
 					palo_dataset(self::_genPaloSubsetXML($dataArr, array('conn' => $conn, 'db_name' => $dbName, 'dim_name' => $dimName)), false, $conn, $dbName, '#_SUBSET_GLOBAL', array($dimName, $subsetName));
 				else if ($subsetType == 1)
 					palo_dataset(self::_genPaloSubsetXML($dataArr, array('conn' => $conn, 'db_name' => $dbName, 'dim_name' => $dimName)), false, $conn, $dbName, '#_SUBSET_LOCAL', array($dimName, self::_get_username_for_conn($connName), $subsetName));
			}
			else
				throw new WSS_Exception('P1_8', array('ss_name' => $subsetName), 'Subset is not saved.');
			palo::palo_disconnect($conn);

			return $subsetName;
		}
		catch (Exception $e)
		{
			throw new WSS_Exception('P1_8', array('ss_name' => $subsetName), 'Subset is not saved.');
		}
	}

	public static function deletePaloSubset($settings)
	{
		$connName = $settings[0];
		$dbName = $settings[1];
		$subsetName = $settings[2];

		$conn = palo::palo_init($connName);
		$result = palo_edelete($conn, $dbName, '#_SUBSET_', $subsetName, true);
		palo::palo_disconnect($conn);

		if (!$result)
			throw new WSS_Exception('P1_5', null, 'Subset not deleted.');

		return true;
	}

	public static function renamePaloSubset($settings)
	{
		$connName = $settings[0];
		$dbName = $settings[1];
		$subsetName = $settings[2];
		$newSubsetName = $settings[3];

		$conn = palo::palo_init($connName);
		$result = palo_erename($conn, $dbName, '#_SUBSET_', $subsetName, $newSubsetName, true);
		palo::palo_disconnect($conn);

		if (!$result)
			throw new WSS_Exception('P1_6', null, 'Subset not renamed.');

		return array($subsetName, $newSubsetName);
	}

	public static function getCubesWithDims($connName, $dbName, $cubeType, $onlyWithAttr =false)
	{
		$cubeList = palo::getCubeNames($connName, $dbName, $cubeType, $onlyWithAttr);

		if (($listSize = count($cubeList)) > 0)
		{
			$conn = palo::palo_init($connName);
			for ($i=$listSize-1; $i>=0; $i--)
			{
				$listDims = palo_cube_list_dimensions($conn, $dbName, $cubeList[$i]);
				$cubeList[$i] = array('name' => $cubeList[$i], 'list' => $listDims);
			}

			palo::palo_disconnect($conn);
		}

		return $cubeList;
	}
}

?>