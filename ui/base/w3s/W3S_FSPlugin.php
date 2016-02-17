<?php

/*
 * \brief W3S filesystem plugin
 *
 * \file W3S_FSPlugin.php
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: W3S_FSPlugin.php 4989 2011-05-24 13:06:46Z srdjanv $
 *
 */

class W3S_FSPlugin implements W3S_Plugin {

	const DEF_IDENT = 'default';
	const DIR_MODE = 0755;
	const FILE_MODE = 0644;
	const NODE_FOLDER = 'folder';
	const NODE_WB = 'workbook';
	const NODE_STATIC = 'static';
	const WB_EXTENSION = '.wss';
	const BLANK_WB_TPL = 'blank_workbook_template';
	const ACT_MOVE = 'move';
	const ACT_COPY = 'copy';
	const ACT_RENAME = 'rename';

	private static $nodeTypes = array('folder', 'workbook', 'static');
	private $wb_storage = '../../base/templates';

	public function __construct() {
		if (!file_exists($this->wb_storage)) {
			$wb_storage = '../' . $this->wb_storage;

			if (file_exists($wb_storage))
				$this->wb_storage = $wb_storage;
		}
	}

	public function getTriggerInfo() {
		return array(
		  'addHierarchy_before' => array(self::DEF_IDENT)
		, 'removeHierarchy_before' => array(self::DEF_IDENT)
		, 'renameHierarchy_before' => array(self::DEF_IDENT)
		, 'moveHierarchy_before' => array(self::DEF_IDENT)
		, 'getHierarchyProps' => array(self::DEF_IDENT)
		, 'addNode_before' => array(self::DEF_IDENT)
		, 'removeNode_before' => array(self::DEF_IDENT)
		, 'moveNode_before' => array(self::DEF_IDENT)
		, 'copyNode_before' => array(self::DEF_IDENT)
		, 'copyNode_after' => array(self::DEF_IDENT)
		, 'renameNode_before' => array(self::DEF_IDENT)
		, 'replaceNode_before' => array(self::DEF_IDENT)
		, 'importNode_before' => array(self::DEF_IDENT)
		, 'importNode_after' => array(self::DEF_IDENT)
		, 'importBundleNode_before' => array(self::DEF_IDENT)
		, 'importBundleNode_after' => array(self::DEF_IDENT)
		, 'iniNodeProps' => array(self::DEF_IDENT)
		, 'getNodeProps' => array(self::DEF_IDENT)
		);
	}

	// ########################
	// Interface implementation
	// ########################

	// Add Hierarchy
	public function addHierarchy_before(array $ident, W3S_Hierarchy $hierarchy) {
		$this->addFolder('hierarchy', $this->getHierarchyPath($hierarchy));
	}

	public function addHierarchy_after(array $ident, W3S_Hierarchy $hierarchy) {}

	// Remove Hierarchy
	public function removeHierarchy_before(array $ident, W3S_Hierarchy $hierarchy) {
		$this->delFolder('hierarchy', $this->getHierarchyPath($hierarchy));
	}

	public function removeHierarchy_after(array $ident, W3S_Hierarchy $hierarchy) {}

	// Rename Hierarchy
	public function renameHierarchy_before (array $ident, W3S_Hierarchy $hierarchy, $new_name) {
		if (strlen($new_name) == 0)
			throw new WSS_Exception('W3S_FSPlugin-no_newname', array('type' => 'hierarchy'), 'Unable to create or rename hierarchy because new name is not set.');

		$this->moveHierarchy(self::ACT_RENAME, $this->getHierarchyPath($hierarchy), $this->getHierarchyPath($hierarchy, true), $hierarchy->getUID() . '-' . urlencode($new_name));
	}

	public function renameHierarchy_after (array $ident, W3S_Hierarchy $hierarchy, $old_name) {}

	// Move Hierarchy
	public function moveHierarchy_before (array $ident, $uid, $name, $old_location, $new_location) {
		$fs_name = $uid . '-' . urlencode($name);

		$this->moveHierarchy(self::ACT_MOVE, $old_location . '/' . $fs_name, $new_location, $fs_name);
	}

	public function moveHierarchy_after (array $ident, $uid, $name, $old_location, $new_location) {}

	// Add Node
	public function addNode_before(array $ident, W3S_Node $node) {
		switch ($node->getType()) {
			case self::NODE_FOLDER:
				$this->addFolder(self::NODE_FOLDER, $this->getFullNodePath($node));
				break;

			case self::NODE_WB:
				$this->addWorkbook($this->getFullNodePath($node) . self::WB_EXTENSION);
				break;
		}
	}

	public function addNode_after(array $ident, W3S_Node $node) {}

	// Remove Node
	public function removeNode_before(array $ident, W3S_Node $node) {
		switch ($node->getType()) {
			case self::NODE_FOLDER:
				$this->delFolder(self::NODE_FOLDER, $this->getFullNodePath($node));
				break;

			case self::NODE_WB:
				$this->delFile($this->getFullNodePath($node->getParent()),  $node->getUID() . '-' . urlencode($node->getData()->getName()) . self::WB_EXTENSION);
				break;

			case self::NODE_STATIC:
				$this->delFile($this->getFullNodePath($node) . (($eff_type = $node->getData()->getEffectiveType()) != 'unknown'  ? '.' . $eff_type : ''));
				break;
		}
	}

	public function removeNode_after(array $ident, W3S_Node $node) {}

	// Move Node
	public function moveNode_before(array $ident, W3S_Node $node, W3S_Node $new_parent, $new_pos) {
		$this->copyMoveRenameNode(self::ACT_MOVE, $node, $new_parent);
	}

	public function moveNode_after(array $ident, W3S_Node $node, W3S_Node $old_parent, $old_pos) {}

	// Copy Node
	public function copyNode_before(array $ident, W3S_Node $node_orig, W3S_Node $new_parent, $new_pos, array &$data) {
		$data['tmpname'] = session_id() . '-' . strval(mt_rand());

		if ($node_orig->getType() == self::NODE_FOLDER)
			$this->addFolder(self::NODE_FOLDER, $this->getFullNodePath($new_parent) . '/' . $data['tmpname']);
		else
			$this->copyMoveRenameNode(self::ACT_COPY, $node_orig, $new_parent, $data['tmpname'], true);
	}

	public function copyNode_after(array $ident, W3S_Node $node_orig, W3S_Node $node_copy, array &$data) {
		$this->copyMoveRenameNode(self::ACT_COPY, $node_copy, $node_copy->getParent(), $data['tmpname'], false);

		if ($node_orig->getType() == self::NODE_FOLDER && !$this->copyRecursive($node_orig, $node_copy)) {
			$src_path = $this->getFullNodePath($node_orig);
			$dst_path = $this->getFullNodePath($node_copy);

			$this->unlinkRecursive($dst_path, true);
			throw new WSS_Exception('W3S_FSPlugin-unable_copy', array('type' => self::NODE_FOLDER, 'src' => $src_path, 'dst' => $dst_path), 'Unable to copy ' . self::NODE_FOLDER . ' ' . $src_path . ' to ' . $dst_path . ' on file system.');
		}
	}

	// Rename Node
	public function renameNode_before (array $ident, W3S_Node $node, $new_name) {
		if (strlen($new_name) == 0)
			throw new WSS_Exception('W3S_FSPlugin-no_newname', array('type' => 'node'), 'Unable to create or rename node because new name is not set.');

		$this->copyMoveRenameNode(self::ACT_RENAME, $node, $node->getParent(), $new_name);
	}

	public function renameNode_after (array $ident, W3S_Node $node, $old_name) {}

	// Replace Node
	public function replaceNode_before (array $ident, W3S_Node $node, array $data) {
		if (!in_array($node->getData()->getType(), self::$nodeTypes, true))
			return;

		$src = $data['uplpath'];
		$dst = $this->getFullNodePath($node) . $this->getNodeExtension($node);

		clearstatcache();
//		if (!file_exists($src))
//			throw new WSS_Exception('W3S_FSPlugin-replace_no_srcnode', array('act' => 'replace', 'type' => $type, 'node' => $node->getData()->getName()), 'Unable to replace ' . $type . ' ' . $node->getData()->getName() . ' on file system because new file doesn\'t exist.');

		if (!copy($src, $dst))
			throw new WSS_Exception('W3S_FSPlugin-unable_move', array('type' => $type, 'src' => $src, 'dst' => $dst), 'Unable to move ' . $type . ' ' . $src . ' to ' . $dst . ' on file system.');
	}

	public function replaceNode_after (array $ident, W3S_Node $node) {}

	// Import Node
	public function importNode_before (array $ident, W3S_Node $parent, $leaf, $type, array &$data, $pos) {
		if (!in_array($type, self::$nodeTypes, true))
			return;

		$data['tmpname'] = session_id() . '-' . strval(mt_rand());
		$src = $data['uplpath'];
		$dst = $this->getFullNodePath($parent) . '/' . $data['tmpname'];

		clearstatcache();
		if (!file_exists($src))
			throw new WSS_Exception('W3S_FSPlugin-no_srcnode', array('act' => 'import', 'type' => $type, 'node' => $data['name']), 'Unable to import ' . $type . ' ' . $data['name'] . ' on file system because it doesn\'t exist.');

		if (file_exists($dst))
			throw new WSS_Exception('W3S_FSPlugin-dstnode_exists', array('act' => 'import', 'type' => $type, 'node' => $dst), 'Unable to import ' . $type . ' on file system because destination ' . $dst . ' already exists.');

		if (!rename($src, $dst))
			throw new WSS_Exception('W3S_FSPlugin-unable_move', array('type' => $type, 'src' => $src, 'dst' => $dst), 'Unable to move ' . $type . ' ' . $src . ' to ' . $dst . ' on file system.');
	}

	public function importNode_after (array $ident, $type, array &$data, W3S_Node $node) {
		if (!in_array($type, self::$nodeTypes, true))
			return;

		$node_ext = $this->getNodeExtension($node);
		$node_name = $node->getUID() . '-' . urlencode($node->getData()->getName());

		$dst = $this->getFullNodePath($node) . $node_ext;
		$src = str_replace($node_name . $node_ext, $data['tmpname'], $dst);

		clearstatcache();
		if (!file_exists($src))
			throw new WSS_Exception('W3S_FSPlugin-no_srcnode', array('act' => 'import', 'type' => $type, 'node' => $data['name'] . $node_ext), 'Unable to import ' . $type . ' ' . $data['name'] . $node_ext . ' on file system because it doesn\'t exist.');

		if (file_exists($dst))
			throw new WSS_Exception('W3S_FSPlugin-dstnode_exists', array('act' => 'import', 'type' => $type , 'node' => $dst), 'Unable to import ' . $type . ' on file system because destination ' . $dst . ' already exists.');

		if (!rename($src, $dst))
			throw new WSS_Exception('W3S_FSPlugin-unable_move', array('type' => $type, 'src' => $src, 'dst' => $dst), 'Unable to move ' . $type . ' ' . $src . ' to ' . $dst . ' on file system.');
	}

	// Import BundleNode
	public function importBundleNode_before (array $ident, W3S_Node $parent, $leaf, $type, array &$data, $pos) {
		if (!in_array($type, self::$nodeTypes, true))
			return;

		$data['tmpname'] = session_id() . '-' . strval(mt_rand());
		$src = $data['uplpath'];
		$dst = $this->getFullNodePath($parent) . '/' . $data['tmpname'];

		clearstatcache();
//		if (!file_exists($src))
//			throw new WSS_Exception('W3S_FSPlugin-no_srcnode', array('act' => 'import', 'type' => $type, 'node' => $data['name']), 'Unable to import ' . $type . ' ' . $data['name'] . ' on file system because it doesn\'t exist.');

		if (file_exists($dst))
			throw new WSS_Exception('W3S_FSPlugin-dstnode_exists', array('act' => 'import', 'type' => $type, 'node' => $dst), 'Unable to import ' . $type . ' on file system because destination ' . $dst . ' already exists.');

		if (!copy($src, $dst))
			throw new WSS_Exception('W3S_FSPlugin-unable_move', array('type' => $type, 'src' => $src, 'dst' => $dst), 'Unable to move ' . $type . ' ' . $src . ' to ' . $dst . ' on file system.');
	}

	public function importBundleNode_after (array $ident, $type, array &$data, W3S_Node $node) {
		if (!in_array($type, self::$nodeTypes, true))
			return;

		$node_ext = $this->getNodeExtension($node);
		$node_name = $node->getUID() . '-' . urlencode($node->getData()->getName());

		$dst = $this->getFullNodePath($node) . $node_ext;
		$src = str_replace($node_name . $node_ext, $data['tmpname'], $dst);

		clearstatcache();
		if (!file_exists($src))
			throw new WSS_Exception('W3S_FSPlugin-no_srcnode', array('act' => 'import', 'type' => $type, 'node' => $data['name'] . $node_ext), 'Unable to import ' . $type . ' ' . $data['name'] . $node_ext . ' on file system because it doesn\'t exist.');

		if (file_exists($dst))
			throw new WSS_Exception('W3S_FSPlugin-dstnode_exists', array('act' => 'import', 'type' => $type , 'node' => $dst), 'Unable to import ' . $type . ' on file system because destination ' . $dst . ' already exists.');

		if (!rename($src, $dst))
			throw new WSS_Exception('W3S_FSPlugin-unable_move', array('type' => $type, 'src' => $src, 'dst' => $dst), 'Unable to move ' . $type . ' ' . $src . ' to ' . $dst . ' on file system.');
	}

	public function getHierarchyProps(array $ident, W3S_Hierarchy $hierarchy) {
		return $this->getPropsSingle($this->getHierarchyPath($hierarchy));
	}

	public function iniNodeProps(array $ident, W3S_Node $node, array $params) {
		$ini = array('path' => $this->getFullNodePath($node), 'proplist' => $params['proplist']);

		if (is_dir($ini['path']))
			$ini['scandir'] = scandir($ini['path']);

		return $ini;
	}

	public function getNodeProps(array $ident, W3S_Node $node, array $ini = null) {
		$node_name = $node->getUID() . '-' . urlencode($node->getData()->getName()) . $this->getNodeExtension($node);

		if ($ini && isset($ini['path'])) {
			$props = $this->getProps4List($ini['path'] . '/' . $node_name, $ini['proplist']);
			$props['hasAs'] = isset($ini['scandir']) ? $this->hasAs($node_name, null, $ini['scandir']) : $this->hasAs($node_name, $ini['path']);
		} else {
			$props = $this->getPropsSingle($this->getFullNodePath($node) . $this->getNodeExtension($node));
			$props['hasAs'] = $this->hasAs($node_name, $this->getFullNodePath($node->getParent()));
		}

		return $props;
	}


	// ################
	// Helper functions
	// ################

	private function getHierarchyPath(W3S_Hierarchy $hierarchy, $location_only = false) {
		return str_replace('\\', '/', $hierarchy->getData()->getBackend()->getLocation()) . ($location_only ? '' : '/' . $hierarchy->getUID() . '-' . urlencode($hierarchy->getData()->getName()));
	}

	private function getRelNodePath(W3S_Node $node) {
		if ($node->getType() == 'root')
			return '';

		return $this->getRelNodePath($node->getParent()) . '/' . $node->getUID() . '-' . urlencode($node->getData()->getName());
	}

	private function getFullNodePath(W3S_Node $node) {
		return $this->getHierarchyPath($node->getHierarchy()) . $this->getRelNodePath($node);
	}

	private function unlinkRecursive($dir, $del_root) {
		if (!$dh = opendir($dir))
			return false;

		while (($obj = readdir($dh)) !== false) {
			if ($obj == '.' || $obj == '..')
				continue;

			$path = $dir . '/' . $obj;
			if (is_dir($path) || !unlink($path))
				$this->unlinkRecursive($path, true);
		}

		closedir($dh);

		if ($del_root)
			return rmdir($dir);

	    return true;
	}

	private function copyRecursive($src_node, $dst_node) {
		$dst_path = $this->getFullNodePath($dst_node);

		if (!is_dir($dst_path) && !mkdir($dst_path, self::DIR_MODE, true))
			return false;

		for ($i = 0; $i < $src_node->numOfChildren(); $i++) {
			$src_child_node = $src_node->getChildAtPos($i);
			$dst_child_node = $dst_node->getChildAtPos($i);

			if ($src_child_node->getType() == self::NODE_FOLDER) {
				if (!$this->copyRecursive($src_child_node, $dst_child_node))
					return false;
			} elseif (!copy($this->getFullNodePath($src_child_node) . $this->getNodeExtension($src_child_node), $this->getFullNodePath($dst_child_node) . $this->getNodeExtension($dst_child_node)))
				return false;
		}

		// For testing:
//		if (!is_dir($dst_path))
//			error_log('mkdir(' . $dst_path . ');' . "\n");
//
//		for ($i = 0; $i < $src_node->numOfChildren(); $i++) {
//			$src_child_node = $src_node->getChildAtPos($i);
//			$dst_child_node = $dst_node->getChildAtPos($i);
//
//			if ($src_child_node->getType() == self::NODE_FOLDER) {
//				if (!$this->copyRecursive($src_child_node, $dst_child_node))
//					return false;
//			} else
//				error_log('copy(' . $this->getFullNodePath($src_child_node) . $this->getNodeExtension($src_child_node) . ', ' . $this->getFullNodePath($dst_child_node) . $this->getNodeExtension($dst_child_node) . '))' . "\n");
//		}

	    return true;
	}

	private function addFolder($type, $path) {
		clearstatcache();
		if (file_exists($path))
			throw new WSS_Exception('W3S_FSPlugin-dir_exists', array('type' => $type, 'dir' => $path), 'Unable to create ' . $type . ' folder ' . $path . ' on file system because it already exists.');

		if (!mkdir($path, self::DIR_MODE, true))
			throw new WSS_Exception('W3S_FSPlugin-unable_mkdir', array('type' => $type, 'dir' => $path), 'Unable to create ' . $type . ' folder ' . $path . ' on file system.');
	}

	private function delFolder($type, $path) {
		clearstatcache();
		if (!file_exists($path))
			return;

		if (!$this->unlinkRecursive($path, true))
			throw new WSS_Exception('W3S_FSPlugin-unable_rmdir', array('type' => $type, 'dir' => $path), 'Unable to remove ' . $type . ' folder ' . $path . ' from file system.');
	}

	private function addWorkbook($path) {
		clearstatcache();
		if (file_exists($path))
			throw new WSS_Exception('W3S_FSPlugin-file_exists', array('wb' => $path), 'Unable to create workbook ' . $path . ' on file system because it already exists.');

		if (!copy($this->wb_storage . '/' . self::BLANK_WB_TPL . '_' . $_SESSION['prefs']->search('general/l10n') . self::WB_EXTENSION, $path))
			throw new WSS_Exception('W3S_FSPlugin-unable_add_wb', array('wb' => $path), 'Unable to create workbook ' . $path . ' on file system.');
	}

	private function delFile($path, $file = null) {
		$full_path = isset($file) ? $path . '/' . $file : $path;

		clearstatcache();
		if (!file_exists($full_path))
			return;

		// Autosave files handling.
		if (isset($file))
			$this->asDelete($path, $file);

		if (!unlink($full_path))
			throw new WSS_Exception('W3S_FSPlugin-unable_rm_file', array('file' => $full_path), 'Unable to remove file ' . $full_path . ' from file system.');
	}

	private function copyMoveRenameNode($act, $node, $parent, $new_name = '', $is_before = true) {
		$type = $node->getType();

		if (!in_array($type, self::$nodeTypes, true))
			return;

		$node_ext = $this->getNodeExtension($node);

		$src = ($act == self::ACT_COPY && !$is_before) ? $this->getFullNodePath($parent) . '/' . $new_name : $this->getFullNodePath($node) . $node_ext;
		$dst = $this->getFullNodePath($parent) . '/' . ($act == self::ACT_COPY && $is_before ? $new_name : $node->getUID() . '-' . urlencode($act == self::ACT_RENAME ? $new_name : $node->getData()->getName()) . $node_ext);

		clearstatcache();
		if (!file_exists($src))
			throw new WSS_Exception('W3S_FSPlugin-no_srcnode', array('act' => $act, 'type' => $type, 'node' => $src), 'Unable to ' . $act . ' ' . $type . ' ' . $src . ' on file system because it doesn\'t exist.');

		if (file_exists($dst) && !($act == self::ACT_RENAME && strtolower($src) == strtolower($dst)))
			throw new WSS_Exception('W3S_FSPlugin-dstnode_exists', array('act' => $act, 'type' => $type, 'node' => $dst), 'Unable to ' . $act . ' ' . $type . ' ' . ' on file system because destination ' . $dst . ' already exists.');

		$exec_copy = $act == self::ACT_COPY && $is_before;

		// Autosave files handling.
		$this->asCopyRename($exec_copy ? self::ACT_COPY : self::ACT_RENAME, $type, $src, $dst);

		if (!($exec_copy ? copy($src, $dst) : rename($src, $dst)))
			throw new WSS_Exception('W3S_FSPlugin-unable_' . $act, array('act' => $act, 'type' => $type, 'src' => $src, 'dst' => $dst), 'Unable to ' . $act . ' ' . $type . ' ' . $src . ' to ' . $dst . ' on file system.');
	}

	private function moveHierarchy($act, $src, $dst_location, $dst_name) {
		$src = str_replace('\\', '/', $src);
		$dst_loc_fixed = str_replace('\\', '/', $dst_location);
		$dst = $dst_loc_fixed . '/' . $dst_name;

		if ($act == self::ACT_MOVE && !is_dir($dst_loc_fixed) && !mkdir($dst_loc_fixed, self::DIR_MODE, true))
			throw new WSS_Exception('W3S_FSPlugin-unable_mkdir', array('type' => 'hierarchy', 'dir' => $dst_location), 'Unable to create hierarchy folder ' . $dst_location . ' on file system.');

		clearstatcache();
		if (!file_exists($src))
			throw new WSS_Exception('W3S_FSPlugin-no_srchierarchy', array('act' => $act, 'hierarchy' => $src), 'Unable to ' . $act . ' ' . $src . ' on file system because it doesn\'t exist.');

		if (file_exists($dst))
			throw new WSS_Exception('W3S_FSPlugin-dsthierarchy_exists', array('act' => $act, 'hierarchy' => $dst), 'Unable to ' . $act . ' hierarchy on file system because destination ' . $dst . ' already exists.');

		if (!rename($src, $dst))
			throw new WSS_Exception('W3S_FSPlugin-unable_' . $act, array('type' => 'hierarchy', 'src' => $src, 'dst' => $dst), 'Unable to ' . $act . ' hierarchy ' . $src . ' to ' . $dst . ' on file system.');
	}

	private function getNodeExtension($node) {
		$type = $node->getType();
		return $type == self::NODE_WB ? '.wss' : ($type == self::NODE_STATIC && ($eff_type = $node->getData()->getEffectiveType()) != 'unknown'  ? '.' . $eff_type : '');
	}

	private function getProps4List ($path, array $proplist)
	{
		clearstatcache();

		if (!file_exists($path) || !($stat = lstat($path)))
			return array();

		$props = array();

		foreach ($proplist as $prop)
			$props[$prop] = $stat[$prop];

		if (isset($props['size']) && is_dir($path))
			unset($props['size']);

		return $props;
	}

	private function getPropsSingle ($path)
	{
		clearstatcache();

		if (!file_exists($path) || !($stat = lstat($path)))
			return array();

		$props = array('atime' => $stat['atime'], 'mtime' => $stat['mtime'], 'ctime' => $stat['ctime']);

		// isn't directory
		if (!is_dir($path))
		{
			$props['size'] = $stat['size'];

			if ($stat['blocks'] >= 0)
				$props['dsize'] = $stat['blocks'] * 512;

			return $props;
		}

		// is directory
		$props['size'] = 0;

		if ($stat['blocks'] >= 0)
			$props['dsize'] = 0;

		$stack = array();
		$list = scandir($path);
		$len = count($list);
		$idx = 0;

		while (true)
		{
			$continue = false;

			for ( ; $idx < $len; ++$idx)
			{
				$item = $list[$idx];

				if ($item == '.' || $item == '..')
					continue;

				$cpath = $path . '/' . $item;

				if (is_dir($cpath))
				{
					$stack[] = array($path, $list, $len, ++$idx);

					$path = $cpath;
					$list = scandir($path);
					$len = count($list);
					$idx = 0;

					$continue = true;
					break;
				}

				$stat = lstat($cpath);

				$props['size'] += $stat['size'];

				if (isset($props['dsize']) && $stat['blocks'] > 0)
					$props['dsize'] += $stat['blocks'] * 512;
			}

			if ($continue)
				continue;

			if (empty($stack))
				break;

			list ($path, $list, $len, $idx) = array_pop($stack);
  	}

		return $props;
	}

	// Autosave Functions

	private function fullPath2DirFile($path) {
		if (($lslash = strrpos($path, '/')) === false)
			return array();

		$lslash++;
		return array('dir' => substr($path, 0, $lslash), 'file' => substr($path, $lslash));
	}

	private function hasAs($file, $node_dir = null, $scan_dir = null) {
		$dir_files = is_null($scan_dir) ? scandir($node_dir) : $scan_dir;

		if (($i = array_search($file, $dir_files)) !== false)
			for ($i++, $as_file = $file . '.', $len = count($dir_files); $i < $len; $i++) {
				if (stripos($dir_files[$i], $as_file) === false)
					return false;

				if (!preg_match('/.~[0-9]$/', $dir_files[$i]))
					continue;

				return true;
			}

		return false;
	}

	private function asDelete($node_dir, $file) {
		if (is_dir($node_dir) && ($dir_files = scandir($node_dir)) && (($i = array_search($file, $dir_files)) !== false))
			for ($i++, $as_file = $file . '.', $len = count($dir_files); $i < $len; $i++) {
				if (stripos($dir_files[$i], $as_file) === false)
					break;

				if (!preg_match('/.~[0-9]$/', $dir_files[$i]))
					continue;

				$del_file = $node_dir . '/' . $dir_files[$i];
				if (!unlink($del_file))
					throw new WSS_Exception('W3S_FSPlugin-unable_rm_recov_file', array('file' => $del_file), 'Unable to remove workbook recovery file ' . $del_file . ' from file system.');
			}
	}

	private function asCopyRename($act, $type, $src, $dst) {
		if (!count($df_src = $this->fullPath2DirFile($src))) return;
		if (!count($df_dst = $this->fullPath2DirFile($dst))) return;

		if (is_dir($df_src['dir']) && ($dir_files = scandir($df_src['dir'])) && (($i = array_search($df_src['file'], $dir_files)) !== false))
			for ($i++, $as_file = $df_src['file'] . '.', $len = count($dir_files); $i < $len; $i++) {
				if (stripos($dir_files[$i], $as_file) === false)
					break;

				if (!preg_match('/.~[0-9]$/', $dir_files[$i]))
					continue;

				$fsrc = $df_src['dir'] . '/' . $dir_files[$i];
				$fdst = $df_dst['dir'] . '/' . $df_dst['file'] . substr($dir_files[$i], strlen($as_file) - 1);

				if (!($act == self::ACT_COPY ? copy($fsrc, $fdst) : rename($fsrc, $fdst)))
					throw new WSS_Exception('W3S_FSPlugin-unable_' . $act, array('act' => $act, 'type' => $type, 'src' => $fsrc, 'dst' => $fdst), 'Unable to ' . $act . ' ' . $type . ' ' . $fsrc . ' to ' . $fdst . ' on file system.');
			}
	}
}

?>