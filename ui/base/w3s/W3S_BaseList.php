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
 * SVN: $Id: W3S_BaseList.php 4891 2011-04-26 13:29:59Z drazenk $
 *
 */

abstract class W3S_BaseList {

	protected $type; // List type: link, palo, palosubset, odbc, clist, cval
	protected $value; // Single value or list values - array('val1', 'val2', ..., 'valn')
	protected $hash; // Hash value.

	/**
	 * Get List type.
	 * @return string List type (link, palo, odbc, clist, cval).
	 */
	public function getType() {
		return $this->type;
	}

	/**
	 * Get Hash value.
	 * @return string Hash value ("66ab2683836462263884f7642f2315e7").
	 */
	public function getHash() {
		return is_null($this->hash) ? '' : $this->hash;
	}

	/**
	 * Set Hash value.
	 * @param string Hash value ("66ab2683836462263884f7642f2315e7").
	 */
	public function setHash($hash) {
		$this->hash = $hash;
	}

}

?>