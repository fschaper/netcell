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
 * SVN: $Id: W3S_GroupData.php 3560 2010-07-23 13:32:53Z drazenk $
 *
 */

class W3S_GroupData extends W3S_BaseData {

	// Constants
	private static $types = array('file', 'report');

	/**
	 * Constructor.
	 * @param array Group data: array('el' => 'group', 'type' => 'group', 'name' => 'Some name', 'desc' => 'Some description').
	 */
	public function __construct($params = null) {
		parent::__construct($params);

		if (isset($params)) {
			$this->chkData(array('element' => $params['el'], 'type' => $params['type']));

			$this->element = $params['el'];
			$this->type = $params['type'];
		}

	}

	/**
	 * Check data function.
	 * @access private
	 * @param array Data to check: array('element' => $el, 'type' => $type, 'name' => $name).
	 */
	protected function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {

				// Check element.
				case 'element':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_GroupData-inv_el', array(), 'Invalid element.');
					break;

				// Check type.
				case 'type':
					if (!in_array($value, self::$types, true))
						throw new WSS_Exception('W3S_GroupData-inv_el_type', array(), 'Invalid element type.');
					break;
			}
		}
	}

	/**
	 * XML import function.
	 * @access public
	 * @param string XML data to import.
	 */
	public function import($data) {
		$root = null; $xpath = null;
		$this->importInit($data, $root, $xpath);
		$this->chkData(array('element' => $this->element, 'type' => $this->type));
	}

	/**
	 * XML export function.
	 * @access public
	 * @return string XML data.
	 */
	public function export() {
		$dom = $this->exportInit();
		$el_element = $dom->documentElement;
		return $dom->saveXML();
	}

}

?>