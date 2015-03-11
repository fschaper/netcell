<?php

/*
 * @brief ajax
 *
 * @file W3S_BaseLink.php
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
 * SVN: $Id: W3S_BaseLink.php 2212 2009-09-30 13:16:31Z predragm $
 *
 */

abstract class W3S_BaseLink {

	// Constants
	private static $targets = array('self', 'blank');

	protected $type; // Link type: 'url'
	protected $target; // Link target: 'self' | 'blank'

	/**
	 * Check data function.
	 * @access private
	 * @param array Data to check: array('target' => $target)
	 */
	protected function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {

				// Check target.
				case 'target':
					if (!in_array($value, self::$targets, true))
						throw new WSS_Exception('W3S_BaseLink-inv_target', array(), 'Invalid hyperlink target.');
					break;

			}
		}
	}

	// ###################
	// Getters and setters
	// ###################

	/**
	 * Get Link type.
	 * @return string Link type ('url').
	 */
	public function getType() {
		return $this->type;
	}

	/**
	 * Get Link target.
	 * @return string Link target ('self' | 'blank').
	 */
	public function getTarget() {
		return $this->target;
	}

	/**
	 * Set Link target.
	 * @param string Link target ('self' | 'blank').
	 */
	public function setTarget($target) {
		$this->chkData(array('target' => $target));
		$this->target = $target;
	}

}

?>