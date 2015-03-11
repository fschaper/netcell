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
 * SVN: $Id: W3S_ExternalList.php 4891 2011-04-26 13:29:59Z drazenk $
 *
 */

abstract class W3S_ExternalList extends W3S_BaseList {

	protected $conn; // Connection name
	protected $db; // DB name
	protected $valueType; // Source type

	protected function chkConn($data) {
		foreach ($data as $key => $value) {
			switch ($key) {

				// Check connection.
				case 'conn':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_ExternalList-no_conn', array(), 'Connection is not set.');
					break;

				// Check db.
				case 'db':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_ExternalList-no_db', array(), 'DB is not set.');
					break;
			}
		}
	}

	/**
	 * Get list's connection name.
	 * @return string The name of connection.
	 */
	public function getConnection() {
		return $this->conn;
	}

	/**
	 * Set list's connection name.
	 * @param string The name of connection.
	 */
	public function setConnection($conn) {
		$this->chkConn(array('conn' => $conn));
		$this->conn = $conn;

		$this->calcHash();
	}

	/**
	 * Get list's database name.
	 * @return string The name of database.
	 */
	public function getDb() {
		return $this->db;
	}

	/**
	 * Set list's database name.
	 * @param string The name of database.
	 */
	public function setDb($db) {
		$this->chkConn(array('db' => $db));
		$this->db = $db;

		$this->calcHash();
	}

}

?>