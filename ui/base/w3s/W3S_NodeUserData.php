<?php

/*
 * \brief W3S NodeUserData class
 *
 * \file W3S_NodeUserData.php
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
 * SVN: $Id: W3S_NodeUserData.php 3485 2010-07-08 14:08:55Z predragm $
 *
 */

class W3S_NodeUserData extends XMLData
{
	const STORAGE_NAME = 'userdata';

	private static $type2schema = array(
	  'workbook' => 'spreadsheet'
	, 'template' => 'spreadsheet'
	, 'folder' => 'folder'
	);

	public function __construct ($type, $userdata = array())
	{
		parent::__construct(isset(self::$type2schema[$type]) ? ($_SERVER['DOCUMENT_ROOT'] . '/../etc/schema/userdata/' . self::$type2schema[$type] . '.rng') : null);

		if (is_string($userdata))
			$this->loadString($userdata);
		else
			$this->loadArray(array(self::STORAGE_NAME => is_array($userdata) ? $userdata : array()));
	}

	public function save (W3S_Node $node)
	{
		$hierarchy = $node->getHierarchy();
		$group = $hierarchy->getGroup();

		if (!in_array($cube = self::STORAGE_NAME . '_' . ($h_uid = $hierarchy->getUID()), palo_database_list_cubes($conn = $group->apol->getSuperConn(), $g_uid = $group->getUID())))
			palo_database_add_cube($conn, $g_uid, $cube, array('#_USER_', $h_uid));

		return $this->savePalo($group->apol, $g_uid, $cube, array($group->apol->getUser(), $node->getUID()), true);
	}

	public function saveSA (AccessPolicy $apol, $group_uid, $hierarchy_uid, $node_uid)
	{
		if (!in_array($cube = self::STORAGE_NAME . '_' . $hierarchy_uid, palo_database_list_cubes($conn = $apol->getSuperConn(), $group_uid)))
			palo_database_add_cube($conn, $group_uid, $cube, array('#_USER_', $hierarchy_uid));

		return $this->savePalo($apol, $group_uid, $cube, array($apol->getUser(), $node_uid), true);
	}

	public function loadSA (AccessPolicy $apol, $group_uid, $hierarchy_uid, $node_uid)
	{
		return $this->loadPalo($apol, $group_uid, self::STORAGE_NAME . '_' . $hierarchy_uid, array($apol->getUser(), $node_uid), true) ? true : $this->loadArray(array(self::STORAGE_NAME => array()));
	}

}

?>