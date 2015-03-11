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
 * SVN: $Id: W3S_PaloList.php 4891 2011-04-26 13:29:59Z drazenk $
 *
 */

final class W3S_PaloList extends W3S_ExternalList {

	// Constants
	const DIM = 'dimension';
	const SUBS = 'subset';

	private $subset; // Subset name (if available).

	public function __construct($conn, $db, $dim, $subs = null, $hash = null) {
		$this->chkConn(array('conn' => $conn, 'db' => $db));
		$this->chkData(array('dim' => $dim));

		$this->type = 'palo';
		$this->value = $dim;
		$this->subset = $subs;
		$this->conn = $conn;
		$this->db = $db;
		$this->valueType = isset($this->subset) ? self::SUBS : self::DIM;

		if (is_null($hash))
			$this->calcHash();
		else
			$this->hash = $hash;
	}

	private function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {
				// Check dimension.
				case 'dim':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_PaloList-no_dim_name', array(), 'Dimension name is not set.');
					break;
			}
		}
	}

	/**
	 * Get list values.
	 * @return array List values params in format: array('type' => 'dimension'|'subset', 'dimension' => 'Year', 'subset' => '3Years'|null);
	 */
	public function getList() {
		return array('type' => $this->valueType, 'dimension' => $this->value, 'subset' => $this->subset);
	}

	/**
	 * Set list values.
	 * @param array List values params in format: array('dimension' => 'Year'[, 'subset' => '3Years']);
	 */
	public function setList($dim, $subs = null) {
		$this->chkData(array('dim' => $dim));
		$this->value = $dim;
		$this->subset = $subs;
		$this->valueType = isset($this->subset) ? self::SUBS : self::DIM;

		$this->calcHash();
	}

	/**
	 *
	 * Calculate and store hash value.
	 */
	private function calcHash() {
		$key = ':' . $this->conn . ':' . $this->db . ':' . $this->value;

		switch ($this->valueType) {
			case self::DIM:
				$key = 'palo:' . self::DIM . $key;
				break;

			case self::SUBS:
				$key = 'palo:' . self::SUBS . $key . ':' . $this->subset;
				break;
		}

		$this->hash = md5($key);
	}

}

?>