<?php

/*
 * \brief class representing a catalog of all DynaRanges on a sheet
 *
 * \file DynarangeCatalog.php
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
 * SVN: $Id: DynarangeCatalog.php 5080 2011-06-24 13:07:57Z predragm $
 *
 */

class DynarangeCatalog
{
	const RE_LOCATION = '/^=\$([A-Z]+)\$([0-9]+)[:,]\$([A-Z]+)\$([0-9]+)$/';

	const CCMD_STOP_ON_ERR = 1;

	private $l10n;

	private $storage = array();

	private $sheetUid;
	private $dataLists;
	private $dynaranges;

	public $defSize;
	public $expandLimit;

	private $cmds = array();

	public function __construct ()
	{
	}

	public function __sleep ()
	{
		return array('storage');
	}

	private function _setup ()
	{
		$this->l10n = $_SESSION['prefs']->search('general/l10n');

		if ($doUpdate = !isset($this->sheetUid))
		{
			$cmds = '[["ocurr",2],["wget","",[],["id","n_location"],{"e_type":"hb"}]]';

			$res = json_decode(ccmd($cmds), true);

			if (!isset($res[0][0]) || $res[0][0] !== true || !isset($res[1][0]) || $res[1][0] !== true || !is_array($res[1][1]) || empty($res[1][1]))
				return;

			$this->sheetUid = $res[0][1];
		}

		if (!isset($this->storage[$this->sheetUid]))
			return;

		$this->dataLists = &$this->storage[$this->sheetUid]['dl'];
		$this->dynaranges = &$this->storage[$this->sheetUid]['dr'];
		$this->defSize = &$this->storage[$this->sheetUid]['ds'];
		$this->expandLimit = &$this->storage[$this->sheetUid]['el'];

		if (!$doUpdate)
			return;

		foreach ($this->dynaranges as $drId => $dr)
		{
			$dr->setCatalog($this);

			if (is_array($this->dataLists[$drId]))
				$dr->setDataList($this->dataLists[$drId]);
		}

		foreach ($res[1][1] as $wsel)
		{
			if (!($dr = $this->dynaranges[$wsel['id']]))
				continue;

			if ($dr->isInner())
				$innerLctns[$wsel['id']] = $wsel['n_location'];
			else
				$dr->setLocation($wsel['n_location']);
		}

		if (isset($innerLctns))
			foreach ($innerLctns as $id => $lctn)
				$this->dynaranges[$id]->setLocation($lctn);

		if (!isset($this->defSize))
			return;

		$id_list = array();
		$cmds = '';

		foreach ($this->dynaranges as $dr)
			if ($dr->hasDimSizes())
			{
				$idxBase = $dr->getIdxBase();
				$srcCoords = $dr->getSrcCoords();

				$cmds .= ',["gcr",' . $idxBase . ',' . $srcCoords[$idxBase] . ',' . $srcCoords[$idxBase + 2] . ']';

				$id_list[] = $dr->getId();
			}

		if (empty($id_list))
			return;

		$cmds[0] = '[';
		$cmds .= ']';

		$res = json_decode(ccmd($cmds), true);

		foreach ($id_list as $i => $id)
			$this->dynaranges[$id]->setDimSizes($res[$i][1]);
	}

	public function genDataList ($wseId, $drId, &$vals, $externCall = false)
	{
		if ($externCall)
			$this->_setup();

		if (!isset($this->dynaranges[$drId]))
			return false;

		$dataList = array();

		if (!is_array($vals))
			$dataList[] = array('n' => strval($vals));
		else if (($len = count($vals)) == 0)
			$dataList[] = array('n' => '');
		else if (is_int($vals[2]) && $len % 3 == 0)
		{
			$name = $vals[0];
			$alias = $vals[1];
			$curr_lvl = $vals[2];
			$curr_lists = array($curr_lvl => &$dataList);

			for ($lvl_prev = $curr_lvl, $i = 3; $i < $len; ++$i)
			{
				$lvl = $vals[$i + 2];

				if ($lvl > $lvl_prev)
					$curr_lists[$lvl] = &$curr_lists[$curr_lvl][array_push($curr_lists[$curr_lvl], array('n' => $name, 'a' => $alias, 'l' => array())) - 1]['l'];
				else
					$curr_lists[$curr_lvl][] = array('n' => $name, 'a' => $alias);

				$lvl_prev = $lvl;

				if (isset($curr_lists[$lvl]))
					$curr_lvl = $lvl;

				$name = $vals[$i++];
				$alias = $vals[$i++];
			}

			$curr_lists[$curr_lvl][] = array('n' => $name, 'a' => $alias);
		}
		else
			foreach ($vals as $val)
				$dataList[] = array('n' => $val);

		$dr = $this->dynaranges[$drId];

		try
		{
			if ($dr->activated())
			{
				$dr->deactivate();
				$this->commit($dr);
			}

			$this->dataLists[$drId] = array('r' => $wseId, 'l' => &$dataList);
			$dr->setDataList($this->dataLists[$drId]);

			if (!$dr->isClone() && $dr->hasDependents())
				ccmd('[["nupd",[[' . json_encode($drId) . ',"' . $this->sheetUid . '"],1,1,{"refers_to":' . json_encode('="' . str_replace('"', '""', $dataList[0]['n']) . '"') . '}]]]');

			if ($dr->activated())
			{
				$dr->reactivate();
				$this->commit($dr);
			}
		}
		catch (DynarangeException $de)
		{
			return false;
		}

		return true;
	}

	public function getFirstElem ($drId)
	{
		return isset($this->dataLists[$drId]) ? $this->dataLists[$drId]['l'][0]['n'] : '';
	}

	public function addCmd (array $cmd)
	{
		$this->cmds[] = $cmd;
	}

	public function getCmds ()
	{
		return empty($this->cmds) ? null : array_splice($this->cmds, 0);
	}

	public function getDynaranges ()
	{
		return $this->dynaranges;
	}

	public function getDynarange ($drId)
	{
		return isset($this->dynaranges[$drId]) ? $this->dynaranges[$drId] : null;
	}

	public function regDynarange (Dynarange $dr)
	{
		$this->dynaranges[$dr->getId()] = $dr;
	}

	public function removeDynaranges (array &$drIds)
	{
		$wseUids = array();

		foreach ($drIds as $drId)
		{
			if (isset($this->dataLists[$drId]))
				$wseUids[] = $this->dataLists[$drId]['r'];

			unset($this->dataLists[$drId]);
			unset($this->dynaranges[$drId]);
		}

		$this->addCmd(array('wdel', '', $wseUids));

		return true;
	}

	public function commit (Dynarange $dr, $readLctns = true)
	{
		if (empty($this->cmds))
			return;

		$this->addCmd(array('wupd', '', array($dr->getUid() => array('n_location' => $dr->getLocation()))));

		if ($hasECInfo = $dr->hasECInfo())
		{
			$this->addCmd(array('hbd', $dr->getSrcCoords()));
			$this->addCmd(array('wget', '', array(), array('e_id', 'n_refers_to'), (object) array()));
		}

		if (!$readLctns)
		{
			$res = ccmd($this->getCmds(), self::CCMD_STOP_ON_ERR);
			$last = end($res);

			if (!$last[0])
				throw new DynarangeException($last);

			if ($hasECInfo)
			{
				$res = prev($res);
				DynarangeDepsRewriter::rewrite($dr, $res[1][0], $last[1], $this->l10n);
			}

			return;
		}

		$this->addCmd(array('wget', '', array(), array('id', 'n_location'), array('e_type' => 'hb')));

		$res = ccmd($this->getCmds(), self::CCMD_STOP_ON_ERR);
		$last = end($res);

		if (!$last[0])
			throw new DynarangeException($last);

		$id = $dr->getId();

		foreach ($last[1] as $lctn)
		{
			if ($lctn['id'] == $id || !($d = $this->dynaranges[$lctn['id']]))
				continue;

			if ($d->isInner())
				$innerLctns[$lctn['id']] = $lctn['n_location'];
			else
				$d->setLocation($lctn['n_location']);
		}

		if (isset($innerLctns))
			foreach ($innerLctns as $id => $lctn)
				$this->dynaranges[$id]->setLocation($lctn);

		if ($hasECInfo)
		{
			$wsels = prev($res);
			$res = prev($res);

			DynarangeDepsRewriter::rewrite($dr, $res[1][0], $wsels[1], $this->l10n);
		}

		if (!isset($this->defSize))
			return;

		$id_list = array();

		foreach ($this->dynaranges as $d)
			if ($d->hasDimSizes())
			{
				$idxBase = $d->getIdxBase();
				$srcCoords = $d->getSrcCoords();

				$this->addCmd(array('gcr', $idxBase, $srcCoords[$idxBase], $srcCoords[$idxBase + 2]));

				$id_list[] = $d->getId();
			}

		$res = ccmd($this->getCmds(), self::CCMD_STOP_ON_ERR);
		$last = end($res);

		if (!$last[0])
			throw new DynarangeException($last);

		reset($res);

		foreach ($id_list as $id)
		{
			$sizes = current($res);
			$this->dynaranges[$id]->setDimSizes($sizes[1]);
			next($res);
		}
	}

	public function activate ()
	{
		foreach ($this->dynaranges as $dr)
			$dr->scan();

		foreach ($this->dynaranges as $dr)
			$dr->activate();
	}

	public function run ($expandLimit = null)
	{
		$cmds = '[["bcc",false],["wget","",[],["n_location","e_id","id","hbdata"],{"e_type":"hb"}],["ocurr",2]]';

		$res = json_decode(ccmd($cmds), true);
		array_shift($res);

		if (!isset($res[0][0]) || $res[0][0] !== true || !is_array($res[0][1]) || empty($res[0][1]) || !isset($res[1][0]) || $res[1][0] !== true)
		{
			ccmd('[["ecc"]]');

			return array(array(false, 100, 'Cannot retrieve initialization data!'));
		}

		$wsElems = $res[0][1];
		$this->sheetUid = $res[1][1];

		$this->storage[$this->sheetUid] = array('dl' => array(), 'dr' => array(), 'ds' => null, 'el' => $expandLimit);
		$this->_setup();

		$tile_dims_ids = array();
		$get_dims_ccmd = array(array('gdcr', 2));

		$srcs = array();

		foreach ($wsElems as $drData)
		{
			if (!preg_match(self::RE_LOCATION, $drData['n_location'], $src))
				continue;

			if (isset($srcs[$src[0]]))
				continue;

			$srcs[$src[0]] = true;

			$src = array(Dynarange::ltrs2num($src[1]), intval($src[2]), Dynarange::ltrs2num($src[3]), intval($src[4]));

			$uid = $drData['e_id'];
			$id = $drData['id'];

			$drData = $drData['hbdata'];

			$dr = $this->dynaranges[$id] = new Dynarange($this, $uid, $id, $src, $drData['dir'], $drData['dcell'], $drData['ss_func']);

			if ($dr === null)
				continue;

			if (isset($drData['alias']))
				$dr->setShowAlias($drData['alias']);

			if (isset($drData['drill']))
				$dr->setDrillDown($drData['drill']);

			if (isset($drData['level']))
				$dr->setBeginLevel($drData['level']);

			if (isset($drData['border']))
				$dr->setBorderStyle($drData['border']);

			if (isset($drData['cwidth']))
				$dr->setColWidth(round(intval($drData['cwidth']) * 7.407));
			else if ($drData['dir'])
			{
				$tile_dims_ids[] = $id;
				$get_dims_ccmd[] = array('gcr', 0, $src[0], $src[2]);
			}

			if (!$drData['dir'])
			{
				$tile_dims_ids[] = $id;
				$get_dims_ccmd[] = array('gcr', 1, $src[1], $src[3]);
			}

			if (isset($drData['indent']))
				$dr->setIndentData($drData['indent']);
		}

		if (!empty($tile_dims_ids))
		{
			$res = ccmd($get_dims_ccmd);
			$this->defSize = array_pop(array_shift($res));

			foreach ($tile_dims_ids as $i => $id)
				$this->dynaranges[$id]->setDimSizes($res[$i][1]);
		}

		$reFindDeps = '/(?<=,|;|\() *(' . join('|', array_keys($this->dynaranges)) . ') *(?=,|;|\))(?=(?:[^"]*$)|(?:[^"]*"[^"]*"[^"]*)*$)/';

		foreach ($this->dynaranges as $dr)
		{
			preg_match_all($reFindDeps, $dr->getFormula(), $matches, PREG_PATTERN_ORDER | PREG_OFFSET_CAPTURE);

			if (!empty($matches[1]))
			{
				$precedents = array();

				foreach ($matches[1] as $match)
				{
					$drId = $match[0];

					$precedents[$drId] = array('val' => $drId, 'offset' => $match[1]);

					$this->dynaranges[$drId]->addDependent($dr->getId());
				}

				$dr->setPrecedents($precedents);
			}
		}

		$drs = $this->dynaranges;

		while (true)
		{
			$wseUpdate = array();
			$wseUids = array();

			foreach ($drs as $drId => $dr)
			{
				$prcds = $dr->getPrecedents();

				if (!empty($prcds))
				{
					$prcds = array_intersect_key($prcds, $drs);

					if (!empty($prcds))
						continue;
				}

				$uid = $dr->getUid();

				$wseUpdate[$uid] = array('n_refers_to' => $dr->getFormula(), 'n_location' => $dr->getLocation());
				$wseUids[] = $uid;
			}

			if (empty($wseUids))
				break;

			$cmds = array(array('wupd', '', $wseUpdate), array('wget', '', $wseUids, array('e_id', 'id', 'n_get_val'), (object) array()));

			$res = ccmd($cmds);

			if (!isset($res[0][0]) || $res[0][0] !== true || !isset($res[1][0]) || $res[1][0] !== true || !is_array($res[1][1]) || empty($res[1][1]))
			{
				ccmd('[["ecc"]]');

				return array(array(false, 100, 'Cannot retrieve data lists!'));
			}

			$wsElems = $res[1][1];

			foreach ($wsElems as $wsElem)
			{
				$this->genDataList($wsElem['e_id'], $drId = $wsElem['id'], $wsElem['n_get_val']);
				unset($drs[$drId]);
			}

			if (empty($drs))
				break;
		}

		try
		{
			$this->activate();
		}
		catch (DynarangeException $de)
		{
			ccmd('[["ecc"]]');

			return array($de->err);
		}

		ccmd('[["ecc"]]');

		return array(array(true));
	}

	public function ec ($drId, array $elemCoords, array $idxPath)
	{
		ccmd('[["bcc",false]]');

		try
		{
			$this->_setup();

			if (!isset($this->dynaranges[$drId]))
				throw new DynarangeException(array(false, 100, ''));

			$dr = $this->dynaranges[$drId];

			if (!$dr->expandCollapse($elemCoords, $idxPath))
				throw new DynarangeException(array(false, 100, ''));
		}
		catch (DynarangeException $de)
		{
			ccmd('[["ecc"]]');

			return array($de->err);
		}

		ccmd('[["ecc"]]');

		return array(array(true));
	}

}

class DynarangeException extends Exception
{
	public $err;

	public function __construct (array $err)
	{
		$this->err = $err;
	}
}

?>