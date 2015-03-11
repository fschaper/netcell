<?php

/*
 * @brief ajax
 *
 * @file Group.js
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: W3S_ODBCList.php 4891 2011-04-26 13:29:59Z drazenk $
 *
 */

final class W3S_ODBCList extends W3S_ExternalList {

	// Constants
	private static $types = array('query');

	public function __construct($conn, $db, $type, $list, $hash = null) {
		$this->chkConn(array('conn' => $conn, 'db' => $db));
		$this->chkData(array('type' => $type, 'list' => $list));

		$this->type = 'odbc';
		$this->value = $list;
		$this->conn = $conn;
		$this->db = $db;
		$this->valueType = $type;

		if (is_null($hash))
			$this->calcHash();
		else
			$this->hash = $hash;
	}

	private function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {
				// Check type.
				case 'type':
					if (!isset($value) || strlen($value) == 0 || !in_array($value, self::$types, true))
						throw new WSS_Exception('W3S_ODBCList-inv_list_type', array(), 'Invalid list type.');
					break;

				// Check list
				case 'list':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_ODBCList-no_list_name', array(), 'List name is not set.');
					break;
			}
		}
	}

	/**
	 * Get list values.
	 * @return array List values params in format: array('type' => 'query', 'list' => 'SELECT year FROM years WHERE year > 2000');
	 */
	public function getList() {
		return array('type' => $this->valueType, 'list' => $this->value);
	}

	/**
	 * Set list values.
	 * @param array List values params in format: array('type' => 'query', 'list' => 'SELECT year FROM years WHERE year > 2000');
	 */
	public function setList($type, $list) {
		$this->chkData(array('type' => $type, 'list' => $list));
		$this->value = $list;
		$this->valueType = $type;

		$this->calcHash();
	}

	/**
	 *
	 * Calculate and store hash value.
	 */
	private function calcHash() {
		$this->hash = md5($this->type . ':' . $this->valueType . ':' . $this->conn . ':' . $this->db . ':' . $this->value);
	}

}

?>