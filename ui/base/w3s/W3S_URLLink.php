<?php

/*
 * @brief ajax
 *
 * @file W3S_URLLink.php
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
 * SVN: $Id: W3S_URLLink.php 2212 2009-09-30 13:16:31Z predragm $
 *
 */

class W3S_URLLink extends W3S_BaseLink {

	// Constants
	const DEF_TARGET = 'self';

	private $url;

	public function __construct($url, $target = self::DEF_TARGET) {
		$this->chkData(array('url' => $url));

		$this->type = 'url';
		$this->setTarget($target);
		$this->url = $url;
	}

	protected function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {

				// Check URL.
				case 'url':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_URLLink-no_url', array(), 'URL is not set.');
					break;

			}
		}
	}

	/**
	 * Get link values.
	 * @return array Link values in format: array('type' => 'url', 'target' => 'self'|'blank', 'url' => 'http://host.domain.tld/');
	 */
	public function getLink() {
		return array('type' => $this->type, 'target' => $this->target, 'url' => $this->url);
	}

	/**
	 * Set link values.
	 * @param string URL ('http://host.domain.tld/').
	 * @param string Link target ('self' | 'blank').
	 */
	public function setLink($url, $target = self::DEF_TARGET) {
		$this->chkData(array('url' => $url));

		$this->setTarget($target);
		$this->url = $url;
	}

}

?>