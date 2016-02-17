<?php

/*
 * \brief class representing a single DynaRange
 *
 * \file Dynarange.php
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
 * SVN: $Id: Dynarange.php 5152 2011-07-28 10:02:33Z predragm $
 *
 */

class Dynarange
{
	const DIR_DOWN = 0;
	const DIR_RGHT = 1;

	const BORDER_OUT = 15;

	const RE_CELLREFS = '/\$([A-Z@]+)\$([0-9]+)/';

	private $catalog;
	private $id;
	private $uid;

	private $direction;

	private $srcCoords;
	private $effCoords;

	private $instCoords;

	private $idxBase;
	private $idxBase2;
	private $horizon;
	private $incrs = array(0, 0);

	private $insCmd;
	private $delCmd;

	private $dataCellCoords = array(0, 0);
	private $formula;
	private $dataList = null;

	private $cloneOf;

	private $showAlias = false;

	private $drillDown = true;
	private $beginLevel = 2;

	private $borderStyle = '1px #000000 solid;';
	private $colWidth = -1;
	private $dimSizes;
	private $indentData;

	private $innerOf;
	private $innerIds = array();
	private $innerPos = array();

	private $refAdjust = 0;

	private $precedents = array();
	private $dependents = array();

	private $activated = false;

	private $ecInfo;

	public static function ltrs2num ($ltrs)
	{
		$num = 0;

		for ($f = 1, $i = strlen($ltrs = strtoupper($ltrs)) - 1; $i >= 0; --$i, $f *= 26)
			$num += (ord($ltrs[$i]) - 64) * $f;

		return $num;
	}

	public static function num2ltrs ($num)
	{
		$ltrs = '';

		while (true)
		{
			$ltrs = chr((--$num % 26) + 65) . $ltrs;

			if (($num /= 26) < 1)
				break;
		}

		return $ltrs;
	}

	public function __construct (DynarangeCatalog $catalog, $wseUid, $drId, array $srcCoords, $direction, array $dataCellCoords = array(0, 0), $formula)
	{
		$this->catalog = $catalog;

		$this->id = $drId;
		$this->uid = $wseUid;

		$this->direction = $direction ? 1 : 0;

		$this->indentData = ! (bool) $this->direction;

		$this->effCoords = $this->srcCoords = $srcCoords;

		$this->idxBase = $this->direction ^ 1;
		$this->idxBase2 = $this->idxBase + 2;

		$this->incrs[$this->idxBase] = $srcCoords[$this->idxBase2] - $srcCoords[$this->idxBase] + 1;
		$this->horizon = $srcCoords[$this->idxBase2] + 1;

		$this->instCoords = array($this->srcCoords[$this->idxBase2]);

		$this->insCmd = $this->idxBase ? 'ir' : 'ic';
		$this->delCmd = $this->idxBase ? 'dr' : 'dc';

		if ($dataCellCoords[0] >= 0 && $dataCellCoords[0] <= $srcCoords[2] - $srcCoords[0] &&
				$dataCellCoords[1] >= 0 && $dataCellCoords[1] <= $srcCoords[3] - $srcCoords[1])
			$this->dataCellCoords = $dataCellCoords;

		$this->formula = $formula;
	}

	public function __sleep ()
	{
		return array('id', 'uid', 'direction', 'idxBase', 'idxBase2', 'insCmd', 'delCmd', 'dataCellCoords', 'formula', 'showAlias', 'drillDown', 'beginLevel', 'borderStyle', 'colWidth', 'dimSizes',
								 'indentData', 'cloneOf', 'innerOf', 'innerIds', 'innerPos', 'refAdjust', 'precedents', 'dependents', 'activated');
	}

	public function setCatalog (DynarangeCatalog $catalog)
	{
		$this->catalog = $catalog;
	}

	public function setDataList (array &$dataList)
	{
		$this->dataList = &$dataList;
	}

	public function setPrecedents (array $precedents)
	{
		$this->precedents = $precedents;
	}

	public function &getPrecedents ()
	{
		return $this->precedents;
	}

	public function addDependent ($drId)
	{
		$this->dependents[$drId] = true;
	}

	public function removeDependent ($drId)
	{
		unset($this->dependents[$drId]);
	}

	public function hasDependents ()
	{
		return !empty($this->dependents);
	}

	public function getId ()
	{
		return $this->id;
	}

	public function getUid ()
	{
		return $this->uid;
	}

	public function getFormula ()
	{
		return $this->formula;
	}

	public function getSrcCoords ()
	{
		return $this->srcCoords;
	}

	public function getIdxBase ()
	{
		return $this->idxBase;
	}

	public function getIncrs ()
	{
		return $this->incrs;
	}

	public function isClone ()
	{
		return isset($this->cloneOf);
	}

	public function setShowAlias ($showAlias)
	{
		$this->showAlias = (bool) $showAlias;
	}

	public function setDrillDown ($drillDown)
	{
		$this->drillDown = (bool) $drillDown;
	}

	public function setBeginLevel ($beginLevel)
	{
		$this->beginLevel = (int) $beginLevel;
	}

	public function setBorderStyle ($borderStyle)
	{
		$this->borderStyle = $borderStyle;
	}

	public function setColWidth ($colWidth)
	{
		$this->colWidth = $colWidth;
	}

	public function setDimSizes (array $dimSparse)
	{
		$cntSparse = count($dimSparse);

		$this->dimSizes = array_fill(0, $this->srcCoords[$this->idxBase2] - $this->srcCoords[$this->idxBase] + 1, $this->catalog->defSize[$this->idxBase]);

		for ($i = 0; $i < $cntSparse; )
			$this->dimSizes[$dimSparse[$i++] + 1 - $this->srcCoords[$this->idxBase]] = $dimSparse[$i++];
	}

	public function hasDimSizes ()
	{
		return !empty($this->dimSizes);
	}

	public function setIndentData ($indentData)
	{
		$this->indentData = (bool) $indentData;
	}

	public function activated ()
	{
		return $this->activated;
	}

	public function hasECInfo ()
	{
		return !empty($this->ecInfo);
	}

	public function getECInfo ()
	{
		return empty($this->ecInfo) ? null : array_splice($this->ecInfo, 0);
	}

	public function isInner ()
	{
		return isset($this->innerOf);
	}

	public function getLocation ()
	{
		$ulX = self::num2ltrs($this->srcCoords[0]);

		if ($this->direction)
		{
			$location = '=$' . $ulX . '$' . $this->srcCoords[1] . ',$' . $ulX . '$' . ($this->srcCoords[3] + 1) . ',$' .  self::num2ltrs($this->horizon) . '$' . $this->srcCoords[1];
			$sfx = '$' . $this->srcCoords[1];

			foreach ($this->instCoords as $coord)
				$location .= ',$' .  self::num2ltrs($coord + $this->refAdjust) . $sfx;
		}
		else
		{
			$location = '=$' . $ulX . '$' . $this->srcCoords[1] . ',$' . self::num2ltrs($this->srcCoords[2] + 1) . '$' . $this->srcCoords[1] . ',$' . $ulX . '$' . $this->horizon;
			$pfx = ',$' . self::num2ltrs($this->srcCoords[0]) . '$';

			foreach ($this->instCoords as $coord)
				$location .= $pfx . ($coord + $this->refAdjust);
		}

		return $location;
	}

	public function setLocation ($location)
	{
		preg_match_all(self::RE_CELLREFS, str_replace('#REF!', '$@$0', $location), $refs, PREG_SET_ORDER);
		$cnt = count($refs);

		if ($this->direction)
		{
			$this->srcCoords = array(self::ltrs2num($refs[0][1]), intval($refs[0][2]), 0, intval($refs[1][2]) - 1);
			$this->horizon = self::ltrs2num($refs[2][1]);

			$this->instCoords = array();

			for ($i = 3; $i < $cnt; ++$i)
				if (($coord = self::ltrs2num($refs[$i][1]) - $this->refAdjust) > 0)
					$this->instCoords[] = $coord;
		}
		else
		{
			$this->srcCoords = array(self::ltrs2num($refs[0][1]), intval($refs[0][2]), self::ltrs2num($refs[1][1]) - 1, 0);
			$this->horizon = intval($refs[2][2]);

			$this->instCoords = array();

			for ($i = 3; $i < $cnt; ++$i)
				if (($coord = intval($refs[$i][2]) - $this->refAdjust) > 0)
					$this->instCoords[] = $coord;
		}

		$lastInst = count($this->instCoords) - 1;

		if (isset($this->innerOf) && ($drOuter = $this->catalog->getDynarange($this->innerOf)))
		{
			$edge = $drOuter->instCoords[$drOuter->innerPos[$this->id]];

			if ($drOuter->direction == $this->direction)
			{
				if ($this->instCoords[$lastInst] > $edge || $this->instCoords[$lastInst] < 1)
					$this->instCoords[$lastInst] = $edge;

				if ($this->horizon > ++$edge)
					$this->horizon = $edge;
				else if ($this->horizon <= $this->instCoords[$lastInst])
					$this->horizon = $this->instCoords[$lastInst] + 1;
			}
			else if ($this->srcCoord[$drOuter->idxBase2] > $edge || $this->srcCoord[$drOuter->idxBase2] < 1)
				$this->srcCoord[$drOuter->idxBase2] = $edge;
		}

		$this->srcCoords[$this->idxBase2] = $this->instCoords[0];

		$this->effCoords = $this->srcCoords;
		$this->effCoords[$this->idxBase2] = $this->instCoords[$lastInst];

		$this->incrs[$this->idxBase] = $this->srcCoords[$this->idxBase2] - $this->srcCoords[$this->idxBase] + 1;
	}

	private function _intersectsWith (Dynarange $dr)
	{
		return !($this->effCoords[0] > $dr->effCoords[2] || $this->effCoords[1] > $dr->effCoords[3] ||
					 $this->effCoords[2] < $dr->effCoords[0] || $this->effCoords[3] < $dr->effCoords[1]);
	}

	private function _notIntersecting (Dynarange $dr)
	{
		return $this->effCoords[0] > $dr->effCoords[2] || $this->effCoords[1] > $dr->effCoords[3] ||
					 $this->effCoords[2] < $dr->effCoords[0] || $this->effCoords[3] < $dr->effCoords[1];
	}

	private function _fullyEnvelopes (Dynarange $dr)
	{
		return $this->effCoords[0] <= $dr->effCoords[0] && $this->effCoords[1] <= $dr->effCoords[1] &&
					 $this->effCoords[2] >= $dr->effCoords[2] && $this->effCoords[3] >= $dr->effCoords[3];
	}

	private function _fullyEnvelopedBy (Dynarange $dr)
	{
		return $this->effCoords[0] >= $dr->effCoords[0] && $this->effCoords[1] >= $dr->effCoords[1] &&
					 $this->effCoords[2] <= $dr->effCoords[2] && $this->effCoords[3] <= $dr->effCoords[3];
	}

	private function _postUnalignedWith (Dynarange $dr)
	{
		return $this->direction == $dr->direction && $this->_notIntersecting($dr) &&
					 $this->srcCoords[$this->idxBase2] > $dr->srcCoords[$this->idxBase2] && $this->srcCoords[$this->idxBase] <= $dr->srcCoords[$this->idxBase2];
	}

	private function _traverseExpandList (array &$list, array $path, $pathLen, $upToLevel, &$col, &$row, array &$dataCells, array &$listElems, $limit = null)
	{
		$idx = 0;

		$root = &$this->dataList['l'][0];

		foreach ($list['l'] as &$entry)
		{
			if ($limit !== null && (isset($list['r']) ? count($listElems) >= $limit + 1 : $idx >= $limit))
				break;

			$cell = array();

			// 'o' needs to be set first
			if ($this->showAlias)
			{
				if ($entry['a'] != '')
				{
					$a = '"' . str_replace('"', '"\""', $entry['a']) . '"';
					$cell['o'] = $a . ';' . $a . ';' . $a . ';' . $a;
				}
				else
					$cell['o'] = '';
			}

			$cell['v'] = '\'' . $entry['n'];

			$path_new = array_merge($path, (array) $idx);

			if ($this->drillDown)
			{
				if (isset($entry['l']))
				{
					$cell['s'] = 'font-weight:bold;';
					$cell['a'] = array('dblclick' => array('hb_ec', $this->id, $path_new));
				}
				else if (isset($root['l']))
				{
					$cell['s'] = 'font-weight:;';
					$cell['a'] = array('dblclick' => 0);
				}
			}

			if ($this->indentData && $pathLen)
			{
				if (isset($cell['s']))
					$cell['s'] .= 'text-indent:' . $pathLen . 'em;';
				else
					$cell['s'] = 'text-indent:' . $pathLen . 'em;';
			}

			$dataCells[] = array($col, $row, 0, $cell);
			$col += $this->incrs[0];
			$row += $this->incrs[1];

			$listElems[] = array($entry['n'], &$list);

			++$idx;

			if (!isset($entry['l']))
				continue;

			if ($upToLevel > $pathLen + 1)
				$entry['e'] = true;

			if (isset($entry['e']))
				$this->_traverseExpandList($entry, $path_new, $pathLen + 1, $upToLevel, $col, $row, $dataCells, $listElems, $limit);
		}

		$list['c'] = $idx;
	}

	private function _expand (array &$list, $upToLevel, $pos = -1, array $path = array(), $pathLen = 0)
	{
		$dataCellsCmd = array('cdrg', array('cm' => true));
		$expandElems = array();

		$offset = $pos == -1 ? 0 : $this->instCoords[$pos] + 1 - $this->srcCoords[$this->idxBase];

		$dataStartCoords = array($this->srcCoords[0] + $this->dataCellCoords[0], $this->srcCoords[1] + $this->dataCellCoords[1]);
		$dataStartCoords[$this->idxBase] += $offset;

		$this->_traverseExpandList($list, $path, $pathLen, $upToLevel, $dataStartCoords[0], $dataStartCoords[1], $dataCellsCmd, $expandElems, $this->catalog->expandLimit);

		if (!($expandCnt = count($expandElems)))
			return false;

		$isRoot = isset($list['r']);

		if ($isRoot)
		{
			$this->catalog->addCmd(array('sbrd', $this->srcCoords, self::BORDER_OUT, $this->borderStyle));

			if ($expandCnt == 1)
			{
				$this->catalog->addCmd($dataCellsCmd);
				return true;
			}

			--$expandCnt;
			$offset = $this->incrs[$this->idxBase];
		}

		$expandSize = $expandCnt * $this->incrs[$this->idxBase];

		$dstCoords = $this->srcCoords;
		$dstCoords[$this->idxBase] += $offset;
		$dstCoords[$this->idxBase2] = $dstCoords[$this->idxBase] + $expandSize - 1 ;

		$insAmount = $this->effCoords[$this->idxBase2] + $expandSize - $this->horizon + 1;

		if ($insAmount < 0)
			$insAmount = 0;

		$direction2 = $this->direction + 2;

		if ($insAmount > 0)
			$this->catalog->addCmd(array($this->insCmd, array($this->horizon, $insAmount)));

		if ($dstCoords[$this->idxBase] <= $this->effCoords[$this->idxBase2])
		{
			$fromCoords = $this->effCoords;
			$fromCoords[$this->idxBase] = $dstCoords[$this->idxBase];

			$toCoords = $fromCoords;
			$toCoords[$this->idxBase] += $expandSize;
			$toCoords[$this->idxBase2] += $expandSize;

			$this->catalog->addCmd(array('cu', array_merge($fromCoords, $toCoords)));

			if ($this->colWidth > 0)
				$this->catalog->addCmd(array('scr', 0, array($toCoords[0], $toCoords[2], $this->colWidth)));
			else if ($this->colWidth == 0)
				$this->catalog->addCmd(array('afit', 0, array($toCoords[0], $toCoords[2])));

			if (!empty($this->dimSizes))
				$this->catalog->addCmd(array('scr', $this->idxBase, array_merge(array($toCoords[$this->idxBase], $toCoords[$this->idxBase2]), $this->dimSizes)));
		}

		$this->effCoords[$this->idxBase2] += $expandSize;

		if ($insAmount)
			foreach ($this->catalog->getDynaranges() as $dr)
			{
				if ($dr === $this || $this->_intersectsWith($dr))
					continue;

				if ($this->horizon <= $dr->effCoords[$this->idxBase] || $this->horizon > $dr->effCoords[$this->idxBase2])
					continue;

				$fromCoords = $toCoords = $dr->effCoords;

				$fromCoords[$this->idxBase] = $this->horizon + $insAmount;
				$fromCoords[$this->idxBase2] += $insAmount;

				$toCoords[$this->idxBase] = $this->horizon;

				if ($this->direction != $dr->direction)
				{
					++$fromCoords[$this->idxBase2];
					++$toCoords[$this->idxBase2];

					$clrCoords = $dr->effCoords;

					$clrCoords[$this->idxBase] = $toCoords[$this->idxBase2] + 1;
					$clrCoords[$this->idxBase2] = $fromCoords[$this->idxBase] - 1;

					array_unshift($clrCoords, 31);
				}

				$this->catalog->addCmd(array('cu', array_merge($fromCoords, $toCoords)));

				if (isset($clrCoords))
				{
					$this->catalog->addCmd(array('clr', $clrCoords));
					unset($clrCoords);
				}
			}

		$this->horizon += $insAmount;

		$this->catalog->addCmd(array('cm', array_merge($this->srcCoords, $dstCoords)));

		$this->catalog->addCmd($dataCellsCmd);

		if ($this->colWidth > 0)
			$this->catalog->addCmd(array('scr', 0, array(($isRoot ? $this->srcCoords[0] : $dstCoords[0]), $dstCoords[2], $this->colWidth)));
		else if ($this->colWidth == 0)
			$this->catalog->addCmd(array('afit', 0, array(($isRoot ? $this->srcCoords[0] : $dstCoords[0]), $dstCoords[2])));

		if (!empty($this->dimSizes))
			$this->catalog->addCmd(array('scr', $this->idxBase, array_merge(array(($isRoot ? $this->srcCoords[$this->idxBase] : $dstCoords[$this->idxBase]), $dstCoords[$this->idxBase2]), $this->dimSizes)));

		if (!$expandCnt)
			return true;

		$from = $isRoot ? $pos + 1 : $pos;

		foreach ($this->innerPos as &$iPos)
			if ($iPos > $from)
				$iPos += $expandCnt;

		for ($cnt = count($this->instCoords), $i = $from + 1; $i < $cnt; ++$i)
			$this->instCoords[$i] += $expandSize;

		array_splice($this->instCoords, $from + 1, 0, range($this->instCoords[$from] + $this->incrs[$this->idxBase], $this->instCoords[$from] + $expandSize, $this->incrs[$this->idxBase]));

		$this->ecInfo = array($offset, $expandCnt);

		if (empty($this->innerIds))
			return true;

		$this->catalog->commit($this);

		$addClonesCmd = array('wadd', '');

		foreach ($this->innerIds as $drId)
		{
			if (!(($dr = $this->catalog->getDynarange($drId)) instanceof Dynarange))
				continue;

			$incr = $offset;
			$sameDir = $dr->direction == $this->direction;

			$clnCnt = -1;
			$elemIdx = $isRoot ? 0 : -1;

			while (++$clnCnt < $expandCnt)
			{
				$currElem = $expandElems[++$elemIdx][0];
				$currList = &$expandElems[$elemIdx][1];

				$drClone = clone $dr;

				$drClone->cloneOf = $drClone->id;
				$drClone->id .= '#' . $currElem;

				$drClone->innerOf = $this->id;
				$this->innerPos[$drClone->id] = $pos + 1 + $elemIdx;

				$drClone->srcCoords[$this->idxBase] += $incr;
				$drClone->srcCoords[$this->idxBase2] += $incr;
				$drClone->effCoords[$this->idxBase] += $incr;
				$drClone->effCoords[$this->idxBase2] += $incr;

				if ($sameDir)
				{
					$drClone->horizon += $incr;

					foreach ($drClone->instCoords as &$coord)
						$coord += $incr;
				}

				$incr += $this->incrs[$this->idxBase];

				$currList['cl'][] = $drClone->id;

				$this->catalog->regDynarange($drClone);

				$formula = $drClone->formula;

				if (!empty($drClone->precedents))
				{
					$offsetCorr = 0;

					foreach ($drClone->precedents as $prcdId => &$prcdData)
					{
						if ($prcdId == $this->id)
							$val = $currElem;
						else if (isset($this->precedents[$prcdId]))
							$val = $this->precedents[$prcdId]['val'];
						else
							$val = $this->getFirstElem($prcdId);

						$prcdData['val'] = $val;

						if ($val != '')
							$val = '"' . str_replace('"', '""', $val) . '"';

						$prcdIdLen = strlen($prcdId);
						$formula = substr_replace($formula, $val, $prcdData['offset'] + $offsetCorr, $prcdIdLen);

						$offsetCorr += strlen($val) - $prcdIdLen;
					}
				}

				$addClonesCmd[] = array('e_type' => 'hb', 'id' => $drClone->id, 'n_refers_to' => $formula, 'n_location' => $drClone->getLocation());
			}
		}

		$wsels = ccmd(array($addClonesCmd));
		$wsels = $wsels[0][1];

		$wsels = ccmd(array(array('wget', '', $wsels, array('e_id', 'id', 'n_get_val'), (object) array())));
		$wsels = $wsels[0][1];

		foreach ($wsels as $wsel)
		{
			$dr = $this->catalog->getDynarange($wsel['id']);
			$dr->uid = $wsel['e_id'];

			$this->catalog->genDataList($dr->uid, $dr->id, $wsel['n_get_val']);

			$dr->activate();
		}

		return true;
	}

	private function _traverseCollapseList (array &$list, &$cnt, array &$clnIds)
	{
		$cnt += $list['c'];

		if (isset($list['cl']))
		{
			array_splice($clnIds, 0, 0, $list['cl']);
			unset($list['cl']);
		}

		foreach ($list['l'] as &$entry)
			if (isset($entry['l']) && isset($entry['e']))
				$this->_traverseCollapseList($entry, $cnt, $clnIds);
	}

	private function _collapse (array &$list, $pos = 0)
	{
		$cnt = isset($list['r']) ? -1 : 0;
		$clnIds = array();

		$this->_traverseCollapseList($list, $cnt, $clnIds);

		if (!$cnt)
			return true;

		$end = $pos + $cnt;
		$size = $this->instCoords[$end] - $this->instCoords[$pos];

		$last = count($this->instCoords) - 1;

		if ($end < $last)
		{
			$fromCoords = $this->srcCoords;
			$fromCoords[$this->idxBase] = $this->instCoords[$end] + 1;
			$fromCoords[$this->idxBase2] = $this->instCoords[$last];

			$toCoords = $fromCoords;
			$toCoords[$this->idxBase] -= $size;
			$toCoords[$this->idxBase2] -= $size;

			$this->catalog->addCmd(array('cu', array_merge($fromCoords, $toCoords)));
		}

		$delFrom = $this->horizon - $size;

		foreach ($this->catalog->getDynaranges() as $dr)
		{
			if ($this === $dr || $this->_intersectsWith($dr))
				continue;

			if ($delFrom > $dr->effCoords[$this->idxBase2] || $this->horizon <= $dr->srcCoords[$this->idxBase])
				continue;
			else if ($dr->effCoords[$this->idxBase2] >= $delFrom)
				$delFrom = $dr->effCoords[$this->idxBase2] + ($this->direction == $dr->direction ? 1 : 2);
		}

		if (($delAmount = $this->horizon - $delFrom) > 0)
		{
			$this->catalog->addCmd(array($this->delCmd, array($delFrom, $delAmount)));
			$this->horizon -= $delAmount;
		}
		else
			$delAmount = 0;

		if ($size > $delAmount)
		{
			$delCoords = $this->effCoords;

			$delCoords[$this->idxBase2] -= $delAmount;
			$delCoords[$this->idxBase] = $delCoords[$this->idxBase2] - ($size - $delAmount) + 1;

			array_unshift($delCoords, 31);
			$this->catalog->addCmd(array('clr', $delCoords));
		}

		$this->effCoords[$this->idxBase2] -= $size;

		array_splice($this->instCoords, $pos + 1, $cnt);

		for ($c = count($this->instCoords), $i = $pos + 1; $i < $c; ++$i)
			$this->instCoords[$i] -= $size;

		if (!$this->direction && $this->colWidth == 0)
			$this->catalog->addCmd(array('afit', 0, array($this->srcCoords[0], $this->srcCoords[2])));

		$this->ecInfo = array($offset, -$cnt);

		if (!empty($clnIds))
		{
			$this->innerPos = array_diff_key($this->innerPos, array_flip($clnIds));

			foreach ($this->innerPos as &$iPos)
				if ($iPos > $pos)
					$iPos -= $cnt;

			$this->catalog->removeDynaranges($clnIds);
		}

		return true;
	}

	public function scan ()
	{
		foreach ($this->catalog->getDynaranges() as $dr)
		{
			if ($dr === $this)
				continue;

			if ($this->_fullyEnvelopes($dr))
			{
				$this->innerIds[] = $dr->id;

				$dr->innerOf = $this->id;
				$this->innerPos[$dr->id] = 0;

				if ($this->direction == $dr->direction)
					$this->refAdjust = 1;
			}
		}
	}

	public function activate ()
	{
		if ($this->activated)
			return false;

		foreach ($this->catalog->getDynaranges() as $dr)
		{
			if ($dr === $this || $dr->activated)
				continue;

			if ($dr->innerPos[$this->id] === 0 || $this->_postUnalignedWith($dr))
				$dr->activate();
		}

		$this->_expand($this->dataList, $this->beginLevel);

		$this->catalog->commit($this);

		$this->activated = true;
	}

	public function expandCollapse (array $cellCoords, array $path)
	{
		if (($pathLen = count($path)) < 1)
			return false;

		if (($ecPos = array_search($cellCoords[$this->idxBase] - $this->dataCellCoords[$this->idxBase] - 1, $this->instCoords)) === false)
			$ecPos = -1;

		++$ecPos;

		$list = &$this->dataList;

		for ($i = 0; $i < $pathLen; ++$i)
		{
			$idx = $path[$i];
			$entry = &$list['l'];

			if (!isset($entry[$idx]['l']))
				return false;

			$list = &$list['l'][$idx];
		}

		if (isset($list['e']))
		{
			unset($list['e']);
			$res = $this->_collapse($list, $ecPos);
		}
		else
		{
			$list['e'] = true;
			$res = $this->_expand($list, $pathLen + 1, $ecPos, $path, $pathLen);
		}

		if ($res)
		{
			$this->catalog->commit($this, false);
			return true;
		}
		else
			return false;
	}

	public function deactivate ()
	{
		if (isset($this->dataList['l'][0]['l']))
			$this->catalog->addCmd(array('cdrg', array('cm' => true), array($this->srcCoords[0] + $this->dataCellCoords[0], $this->srcCoords[1] + $this->dataCellCoords[1], 0, array('s' => 'font-weight:', 'a' => array('dblclick' => 0)))));

		return $this->_collapse($this->dataList);
	}

	public function reactivate ()
	{
		return $this->_expand($this->dataList, $this->beginLevel);
	}

}

?>