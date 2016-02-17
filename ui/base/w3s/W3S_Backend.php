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
 * SVN: $Id: W3S_Backend.php 2212 2009-09-30 13:16:31Z predragm $
 *
 */

class W3S_Backend {

	// Constants
	private static $types = array('local', 'SMB', 'WebDAV', 'FTP', 'SVN', 'CVS');

	private $type; // Backend type.
	private $location; // Location - URL.
	private $username; // Connection credential - username.
	private $password; // Connection credential - password.

	/**
	 * Constructor.
	 * @param array Basic backend data: array('type' => ('local' | 'SMB' | 'WebDAV' | 'FTP' | 'SVN' | 'CVS'), 'location' => ('URL' | 'Path'), 'username' => 'admin', 'password' => 'adminpass').
	 */
	public function __construct($params) {
		$this->setData($params);
	}

	private function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {

				// Check type.
				case 'type':
					if (!in_array($value, self::$types, true))
						throw new WSS_Exception('W3S_Backend-err_type', array(), 'Invalid backend type.');
					break;

				// Check location.
				case 'location':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_Backend-err_location', array(), 'Backend location is not set.');
					break;
			}
		}
	}

	// ###################
	// Getters and setters
	// ###################

	/**
	 * Set all backend data.
	 * @param array Basic backend data: array('type' => ('local' | 'SMB' | 'WebDAV' | 'FTP' | 'SVN' | 'CVS'), 'location' => ('URL' | 'Path'), 'username' => 'admin', 'password' => 'adminpass').
	 */
	public function setData($params) {
		if (!isset($params) || count($params) == 0)
			throw new WSS_Exception('W3S_Backend-empty_paramlist', array(), 'The list of parameters is empty.');

		$this->chkData(array('type' => $params['type'], 'location' => $params['location']));

		$this->type = $params['type'];
		$this->location = $params['location'];

		if (array_key_exists('username', $params))
			$this->username = $params['username'];

		if (array_key_exists('password', $params))
			$this->password = $params['password'];
	}

	/**
	 * Get all backend data.
	 * @param array Basic backend data: array('type' => ('local' | 'SMB' | 'WebDAV' | 'FTP' | 'SVN' | 'CVS'), 'location' => ('URL' | 'Path'), 'username' => 'admin', 'password' => 'adminpass').
	 */
	public function getData() {
		return array('type' => $this->type, 'location' => $this->location, 'username' => $this->username, 'password' => $this->password);
	}

	/**
	 * Get backend type.
	 * @return string Backend type (local, SMB, WebDAV, FTP, SVN, CVS).
	 */
	public function getType() {
		return $this->type;
	}

	/**
	 * Set backend type.
	 * @param string Backend type (local, SMB, WebDAV, FTP, SVN, CVS).
	 */
	public function setType($type) {
		$this->chkData(array('type' => $type));
		$this->type = $type;
	}

	/**
	 * Get backend location.
	 * @return string Backend location (URL).
	 */
	public function getLocation() {
		return $this->location;
	}

	/**
	 * Set backend location.
	 * @param string Backend location (URL).
	 */
	public function setLocation($location) {
		$this->chkData(array('location' => $location));
		$this->location = $location;
	}

	/**
	 * Get backend username.
	 * @return string Backend username.
	 */
	public function getUsername() {
		return $this->username;
	}

	/**
	 * Set backend username.
	 * @param string Backend username.
	 */
	public function setUsername($username) {
		$this->username = $username;
	}

	/**
	 * Get backend password.
	 * @return string Backend password.
	 */
	public function getPassword() {
		return $this->password;
	}

	/**
	 * Set backend password.
	 * @param string Backend password.
	 */
	public function setPassword($password) {
		$this->password = $password;
	}

}

?>