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
 * SVN: $Id: W3S_ConstValue.php 4891 2011-04-26 13:29:59Z drazenk $
 *
 */

final class W3S_ConstValue extends W3S_BaseList {

	public function __construct($value, $hash = null) {
		$this->type = 'cval';
		$this->value = !isset($value) ? '' : $value;

		if (is_null($hash))
			$this->calcHash();
		else
			$this->hash = $hash;
	}

	/**
	 * Set list value.
	 * @param string List's constant value ('2002').
	 */
	public function setValue($value) {
		$this->value = !isset($value) ? '' : $value;

		$this->calcHash();
	}

	/**
	 * Get list value.
	 * @return string List's constant value ('2002').
	 */
	public function getValue() {
		return $this->value;
	}


	/**
	 *
	 * Calculate and store hash value.
	 */
	private function calcHash() {
		$this->hash = md5('cval:' . $this->value);
	}

}

?>