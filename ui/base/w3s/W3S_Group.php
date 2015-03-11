<?php

/*
 * \brief W3S Group class
 *
 * \file W3S_Group.php
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
 * SVN: $Id: W3S_Group.php 5010 2011-05-28 22:30:58Z predragm $
 *
 */

class W3S_Group
{
	const MAX_HIERARCHIES = 255;

	private static $metas = array(
		'type' => 'S',
		'data' => 'S',
		'seq_node' => 'N'
	);

	private static $pfxs = array(
		'file' => 'fgrp',
		'report' => 'rgrp'
	);

	private $uid,

					$type,
					$data,
					$perm = -1,
					$perm_g,
					$perm_h,

					$hierarchylist = array(),
					$hierarchies = array(),

					$hierarchyplugins = array(),

					$triggers = array(
					  'addHierarchy_before' => array()
					, 'addHierarchy_after' => array()
					, 'removeHierarchy_before' => array()
					, 'removeHierarchy_after' => array()
					, 'renameHierarchy_before' => array()
					, 'renameHierarchy_after' => array()
					);

	public $apol;

	public static function _calcPerms (AccessPolicy $apol, $uid)
	{
		$rule_g = $apol->getRule('database');
		$rule_h = $apol->getRule('dimension');

		$perm = $apol->calcPerms($uid, 'meta', array('group'));
		$perm = $perm['group'];

		return $perm != -1 ? array($perm, $perm & $rule_g, $perm & $rule_h) : array($perm, $rule_g, $rule_h);
	}

	private static function _palo_listGroups (AccessPolicy $apol, array $types = null)
	{
		$conn = $apol->getConn();

		$list = array();

		$dbs = palo_root_list_databases($conn, true, true);

		foreach ($dbs as $db)
		{
			if (substr($db, 0, 6) == 'System')
				continue;

			$dims = palo_database_list_dimensions($conn, $db, 0);

			if (!in_array('meta', $dims))
				continue;

			list ( , $perm_g, $perm_h) = self::_calcPerms($apol, $db);

			if (!($perm_g & AccessPolicy::PERM_READ))
				continue;

			$meta = palo_datav($conn, $db, '#_meta', array(1, 2, 'type', 'data'), array(1, 1, 'group'));

			$type = $meta[2];

			if ($types !== null && !in_array($type, $types))
				continue;

			$data = new W3S_GroupData();

			try
			{
				$data->import($meta[3]);
			}
			catch (Exception $e)
			{
				continue;
			}

			$list[$db] = array('type' => $type, 'name' => $data->getName(), 'desc' => $data->getDescription(), 'perm_g' => $perm_g, 'perm_h' => $perm_h);
		}

		return $list;
	}

	private static function _palo_getGroupSeq ($conn, $pfx)
	{
		$pfx_len = strlen($pfx);
		$new_uid = 0;

		foreach (palo_root_list_databases($conn, true, true) as $db_name)
			if (substr($db_name, 0, $pfx_len) == $pfx && ($num = intval(substr($db_name, $pfx_len))) > $new_uid)
				$new_uid = $num;

		return ++$new_uid;
	}

	private static function _palo_addGroup ($conn, $uid, $type, W3S_GroupData $data)
	{
		if (in_array($uid, palo_root_list_databases($conn, true, true)))
			return false;

		palo_root_add_database($conn, $uid, 3);

		palo_setdata('Y', 'false', $conn, $uid, '#_CONFIGURATION', 'HideElements');

		palo_database_add_dimension($conn, $uid, 'meta');

		palo_ping($conn);

		foreach (self::$metas as $meta_name => $meta_type)
			palo_eadd($conn, $uid, '#_meta_', $meta_type, $meta_name, '', 1, false, true);

		palo_eadd($conn, $uid, 'meta', 'S', 'group', '', 1, false, true);

		palo_setdata($type, 'false', $conn, $uid, '#_meta', 'type', 'group');
		palo_setdata($data->export(), 'false', $conn, $uid, '#_meta', 'data', 'group');

		return true;
	}

	private static function _palo_removeGroup ($conn, $uid)
	{
		palo_root_delete_database($conn, $uid);

		return true;
	}

	private static function _palo_renameGroup ($conn, $uid, $new_name)
	{
		$data_xml = palo_data($conn, $uid, '#_meta', 'data', 'group');

		$data = new W3S_GroupData();

		try
		{
			$data->import($data_xml);
		}
		catch (Exception $e)
		{
			return false;
		}

		$data->setName($new_name);

		palo_setdata($data->export(), 'false', $conn, $uid, '#_meta', 'data', 'group');

		return true;
	}

	public static function removeNodes (AccessPolicy $apol, array $list)
	{
		$conn = $apol->getConn();

		foreach ($list as $g_uid => $h_list)
			foreach ($h_list as $h_uid => $n_list)
				palo_edelete_bulk($conn, $g_uid, $h_uid, $n_list);
	}

	public static function listGroups (AccessPolicy $apol, array $types = null)
	{
		return self::_palo_listGroups($apol, $types);
	}

	public static function addGroup (AccessPolicy $apol, $type, array $params)
	{
		$conn = $apol->getConn();

		$pfx = isset(self::$pfxs[$type]) ? self::$pfxs[$type] : '_grp';

		$uid = $pfx . self::_palo_getGroupSeq($conn, $pfx);
		$type = (string) $type;

		$params['el'] = $uid;
		$params['type'] = $type;

		$data = new W3S_GroupData($params);

		$group = new W3S_Group($apol, $uid, $type, $data, true);

		return self::_palo_addGroup($conn, $uid, $type, $data) ? $group : null;
	}

	public static function removeGroup (AccessPolicy $apol, W3S_Group $group)
	{
		foreach (array_keys($group->hierarchylist) as $uid)
			$group->removeHierarchy($group->getHierarchy($uid));

		return self::_palo_removeGroup($apol->getConn(), $group->getUID());
	}

	public static function renameGroup (AccessPolicy $apol, $uid, $new_name)
	{
		return self::_palo_renameGroup($apol->getConn(), $uid, $new_name);
	}

	public function __construct (AccessPolicy $apol, $uid, $type = '', W3S_GroupData $data = null, $isNew = false)
	{
		$this->uid = (string) $uid;

		$this->apol = $apol;

		$this->type = (string) $type;
		$this->data = $data;

		if ($isNew)
		{
			$this->perm_g = $apol->getRule('database');
			$this->perm_h = $apol->getRule('dimension');
		}
		else
			$this->_palo_load();
	}

	public function __sleep ()
	{
		return array('uid', 'type', 'data', 'perm', 'perm_g', 'perm_h', 'hierarchylist', 'hierarchies', 'hierarchyplugins', 'triggers');
	}

	public function __wakeup ()
	{
		foreach ($this->hierarchies as $hierarchy)
			$hierarchy->_sess_setGroup($this);
	}

	public function calcPerms ()
	{
		list ($this->perm, $this->perm_g, $this->perm_h) = self::_calcPerms($this->apol, $this->uid);

		foreach ($this->hierarchies as $hierarchy)
			$hierarchy->refreshPerms();
	}

	private function _palo_load ()
	{
		$conn = $this->apol->getConn();

		$data = palo_datav($conn, $this->uid, '#_meta', array(1, 2, 'type', 'data'), array(1, 1, 'group'));

		$this->type = $data[2];

		$this->data = new W3S_GroupData();

		try
		{
			$this->data->import($data[3]);
		}
		catch (Exception $e)
		{
			return false;
		}

		$dims = array_flip(palo_database_list_dimensions($conn, $this->uid, 0));
		$metas = palo_dimension_list_elements($conn, $this->uid, 'meta', true);

		foreach ($metas as &$meta)
			if (preg_match('/^h[0-9]+$/', $uid = $meta['name']) && isset($dims[$uid]))
				$this->hierarchylist[$uid] = $uid;

		$this->calcPerms();

		return true;
	}

	private function _palo_saveData ()
	{
		palo_setdata($this->data->export(), 'false', $this->apol->getConn(), $this->uid, '#_meta', 'data', 'group');

		return true;
	}

	private function _palo_addHierarchy ($uid, $type, W3S_HierarchyData $data)
	{
		$conn = $this->apol->getConn();

		palo_database_add_dimension($conn, $this->uid, $uid);

		palo_ping($conn);

		palo_eadd($conn, $this->uid, 'meta', 'S', $uid, '', 1, false, true);

		palo_setdata($type, 'false', $conn, $this->uid, '#_meta', 'type', $uid);
		palo_setdata($data->export(), 'false', $conn, $this->uid, '#_meta', 'data', $uid);

		palo_eadd($conn, $this->uid, '#_' . $uid . '_', 'S', 'type', '', 1, false, true);
		palo_eadd($conn, $this->uid, '#_' . $uid . '_', 'S', 'data', '', 1, false, true);

		return true;
	}

	private function _palo_removeHierarchy ($uid)
	{
		$conn = $this->apol->getConn();

		palo_database_delete_dimension($conn, $this->uid, $uid);

		palo_edelete($conn, $this->uid, 'meta', $uid);

		return true;
	}

	public function registerPlugin (W3S_Plugin $plugin, $hierarchiesToo = false)
	{
		foreach ($plugin->getTriggerInfo() as $event => $ident)
			if (isset($this->triggers[$event]))
				$this->triggers[$event][] = array($plugin, $ident);

		if ($hierarchiesToo)
		{
			$this->hierarchyplugins[] = $plugin;

			foreach ($this->hierarchies as $hierarchy)
				$hierarchy->registerPlugin($plugin);
		}

		return true;
	}

	public function getUID ()
	{
		return $this->uid;
	}

	public function bundle($doc, $zip, $path=''){
		$xmlNode = $doc->createElement($this->uid);

		$nameAttr =  $doc->createAttribute('name');
		$nameAttr->appendChild($doc->createTextNode( $this->data->getName()));
		$xmlNode->appendChild($nameAttr);

		$typeAttr = $doc->createAttribute('type');
		$typeAttr->appendChild($doc->createTextNode('group'));
		$xmlNode->appendChild($typeAttr);

		$zip->addFromString($path . "item.xml", $this->data->export());

		//permission node (permissions for all user groups)
		$permsNode = $doc->createElement('perms');
		$xmlNode->appendChild($permsNode);

		$zip->addFromString($path . "perms.xml", $this->getUGsNodePerms());

		return $xmlNode;
	}

	private function getUGsNodePerms()
	{
		$db = $this->uid;
		$cube = '#_GROUP_DIMENSION_DATA_meta';
		$order = array('meta');
		$coords = array('meta'=>array('group'));

		$paloData = new PaloData($this->apol->getSuperConn());
		$result = $paloData->get($db, $cube, $order, $coords);

		$xmlData = new XMLData(null);
		$xmlData->loadArray(array('perms' => $result['group']));

  		return $xmlData->saveString();
	}

	public function getType ()
	{
		return $this->type;
	}

	public function getData ()
	{
		return $this->data;
	}

	public function getPermG ()
	{
		return $this->perm_g;
	}

	public function getPermH ()
	{
		return $this->perm_h;
	}

	public function saveData ()
	{
		return $this->data instanceof W3S_GroupData ? $this->_palo_saveData() : false;
	}

	public function getHierarchy ($uid, $load = true)
	{
		if (isset($this->hierarchies[$uid]))
			return $this->hierarchies[$uid];

		if (isset($this->hierarchylist[$uid]) && $load)
			try
			{
				$this->hierarchies[$uid] = $hierarchy = new W3S_Hierarchy($uid, $this);

				foreach ($this->hierarchyplugins as $plugin)
					$hierarchy->registerPlugin($plugin);

				return $hierarchy;
			}
			catch (Exception $e)
			{
			}

		return null;
	}

	public function getFirstHierarchy ()
	{
		foreach ($this->hierarchylist as $uid)
			return $this->getHierarchy($uid);

		return null;
	}

	private function _palo_listHierarchies ()
	{
		$conn = $this->apol->getConn();

		$dims = array_flip(palo_database_list_dimensions($conn, $this->uid, 0));
		$metas = palo_dimension_list_elements($conn, $this->uid, 'meta', true);

		$uids_seen = array();

		foreach ($metas as &$meta)
			if (preg_match('/^h[0-9]+$/', $uid = $meta['name']) && isset($dims[$uid]))
				$uids_seen[] = $uid;

		$uids = array_keys($this->hierarchylist);

		foreach (array_diff($uids, $uids_seen) as $uid)
		{
			unset($this->hierarchylist[$uid]);
			unset($this->hierarchies[$uid]);
		}

		foreach (array_diff($uids_seen, $uids) as $uid)
			$this->hierarchylist[$uid] = $uid;

		$uids = array_keys($this->hierarchylist);

		if (($num = count($uids)) < 1)
			return null;

		$res = palo_datav($conn, $this->uid, '#_meta', array(1, 2, 'type', 'data'), array_merge(array($num, 1), $uids));
		array_splice($res, 0, 2);

		$perms = $this->apol->calcPerms($this->uid, 'meta', $uids);

		$rule_h = $this->apol->getRule('dimension');
		$rule_n = $this->apol->getRule('dimension element');

		$list = array();
		$idx = -1;

		foreach ($uids as $uid)
		{
			$type = $res[++$idx];

			$data = new W3S_HierarchyData();

			try
			{
				$data->import($res[++$idx]);
			}
			catch (Exception $e)
			{
				continue;
			}

			$perm = $perms[$uid];

			if ($perm != -1)
			{
				$perm_h = $perm & $rule_h;
				$perm_n = $perm & $rule_n;
			}
			else
			{
				$perm_h = $this->perm_h;
				$perm_n = $perm_h & $rule_n;
			}

			$list[$uid] = array('type' => $type, 'name' => $data->getName(), 'desc' => $data->getDescription(), 'perm_h' => $perm_h, 'perm_n' => $perm_n);

			$userdata = new W3S_HierarchyUserData();
			$userdata->loadSA($this->apol, $this->uid, $uid);

			$userdata = $userdata->get('view');

			if (isset($userdata['view']))
				$list[$uid]['view'] = $userdata['view'];
		}

		return $list;
	}

	public function listHierarchies ()
	{
		return self::_palo_listHierarchies();
	}

	private function _palo_getSequence ($name)
	{
		$conn = $this->apol->getConn();

		$uid = intval(palo_data($conn, $this->uid, '#_meta', 'seq_node', $name));
		palo_setdata(++$uid, 'false', $conn, $this->uid, '#_meta', 'seq_node', $name);

		return $uid;
	}

	public function getSequence ($name, $pfx)
	{
		return ($uid = $this->_palo_getSequence($name)) < 1 ? '' : $pfx . $uid;
	}

	private function _palo_getHierarchyCnt ()
	{
		return count(palo_database_list_dimensions($this->apol->getSuperConn(), $this->uid));
	}

	public function addHierarchy ($type, array $params)
	{
		if ($this->_palo_getHierarchyCnt() >= self::MAX_HIERARCHIES)
			return null;

		do
		{
			$new_uid = $this->getSequence('group', 'h');
		}
		while (isset($this->hierarchylist[$new_uid]));

		$params['el'] = $new_uid;
		$params['type'] = $type;

		$data = new W3S_HierarchyData($params);

		$hierarchy = new W3S_Hierarchy($new_uid, $this, $type, $data, true);

		foreach ($this->hierarchyplugins as $plugin)
			$hierarchy->registerPlugin($plugin);

		foreach ($this->triggers['addHierarchy_before'] as $trigger)
			call_user_func(array($trigger[0], 'addHierarchy_before'), $trigger[1], $hierarchy);

		$this->_palo_addHierarchy($new_uid, $type, $data);

		$this->hierarchylist[$new_uid] = $new_uid;
		$this->hierarchies[$new_uid] = $hierarchy;

		foreach ($this->triggers['addHierarchy_after'] as $trigger)
			call_user_func(array($trigger[0], 'addHierarchy_after'), $trigger[1], $hierarchy);

		return $hierarchy;
	}

	public function removeHierarchy (W3S_Hierarchy $hierarchy)
	{
		$uid = $hierarchy->getUID();

		if (!isset($this->hierarchies[$uid]))
			return false;

		$hierarchy = $this->hierarchies[$uid];

		foreach ($this->triggers['removeHierarchy_before'] as $trigger)
			call_user_func(array($trigger[0], 'removeHierarchy_before'), $trigger[1], $hierarchy);

		$hierarchy->unlinkNodes($hierarchy->getRoot()->getChildren());

		$this->_palo_removeHierarchy($uid);

		unset($this->hierarchylist[$uid]);
		unset($this->hierarchies[$uid]);

		foreach ($this->triggers['removeHierarchy_after'] as $trigger)
			call_user_func(array($trigger[0], 'removeHierarchy_after'), $trigger[1], $hierarchy);

		return true;
	}

	public function renameHierarchy (W3S_Hierarchy $hierarchy, $new_name)
	{
		$h_data = $hierarchy->getData();

		if (!($h_data instanceof W3S_HierarchyData))
			return false;

		$new_name = strval($new_name);

		foreach ($this->triggers['renameHierarchy_before'] as $trigger)
			call_user_func(array($trigger[0], 'renameHierarchy_before'), $trigger[1], $hierarchy, $new_name);

		$old_name = $h_data->getName();

		$h_data->setName($new_name);
		$hierarchy->saveData();

		foreach ($this->triggers['renameHierarchy_after'] as $trigger)
			call_user_func(array($trigger[0], 'renameHierarchy_after'), $trigger[1], $hierarchy, $old_name);

		return true;
	}

	public function hierarchy ($method)
	{
		if (!is_callable($callback = array($this, $method)))
			return false;

		$args = func_get_args();
		array_splice($args, 0, 1);

		$refl_method = new ReflectionMethod('W3S_Group', $method);

		foreach ($refl_method->getParameters() as $i => $param)
			if (($refl_class = $param->getClass()) instanceof ReflectionClass && $refl_class->getName() == 'W3S_Hierarchy')
				if (!($args[$i] = $this->getHierarchy($args[$i])))
					return false;

		$res = call_user_func_array($callback, $args);

		return ($res instanceof W3S_Hierarchy) ? $res->getUID() : $res;
	}

}

?>