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
 * SVN: $Id: W3S_ConstList.php 4891 2011-04-26 13:29:59Z drazenk $
 *
 */

final class W3S_ConstList extends W3S_BaseList {

	public function __construct($values, $hash = null) {
		$this->type = 'clist';
		$this->value = $this->formatValues($values);

		if (is_null($hash))
			$this->calcHash();
		else
			$this->hash = $hash;
	}

	private function formatValues($values) {
		if (!isset($values))
			return array();
		elseif (!is_array($values))
			return array($values);
		else
			return $values;
	}

	/**
	 * Set list values.
	 * @param array List's constant values: array('2002', '2003', '2004', '2005');
	 */
	public function setValues($values) {
		$this->value = $this->formatValues($values);

		$this->calcHash();
	}

	/**
	 * Get list values.
	 * @return array List's constant values: array('2002', '2003', '2004', '2005');
	 */
	public function getValues() {
		return $this->value;
	}

	/**
	 *
	 * Calculate and store hash value.
	 */
	private function calcHash() {
		$key = 'clist';

		foreach ($this->value as $val)
			$key .= ':' . $val;

		$this->hash = md5($key);
	}

}

?>