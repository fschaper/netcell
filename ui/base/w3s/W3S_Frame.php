<?php

/*
 * @brief W3S_
 *
 * @file W3S_Frame.php
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
 * SVN: $Id: W3S_Frame.php 3980 2010-10-11 11:14:50Z drazenk $
 *
 */

final class W3S_Frame {

	/*
	 	Frame name.
	 */
	private $name;

	/*
	 	W3S_NodeLink object.
	 */
	private $src;

	/*
	 	params:
	 	array('param1' => 'yes', 'param2' => 'no')
	 */
	private $params = array();

	/**
	 * Constructor.
	 * @param string Frame name ('frame1').
	 * @param W3S_NodeLink NodeLink object.
	 * @param array Frame parameters in format: array('param1' => 'yes', 'param2' => 'no')
	 */
	public function __construct($name, $src, $params = null) {
		$this->chkData(array('name' => $name, 'src' => $src));

		$this->name = $name;
		$this->src = $src;

		if (is_array($params))
			$this->params = $params;
	}

	private function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {
				// Check name.
				case 'name':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_Frame-err_name', array(), 'Frame name is not set.');
					break;

				// Check source.
				case 'src':
					if (!isset($value) || get_class($value) != 'W3S_NodeLink')
						throw new WSS_Exception('W3S_Frame-inv_frame_src', array(), 'Invalid frame source.');
					break;
			}
		}
	}

	/**
	 * Get frames as associative array.
	 * @return array Frames as associative array.
	 */
	public function getAssoc() {
		$arr = $this->src->getAssoc();
		$arr['name'] = $this->name;
		$arr['params'] = $this->params;

		return $arr;
	}

	/**
	 * Get name.
	 * @return string Frame name ('frame1').
	 */
	public function getName() {
		return $this->name;
	}

	/**
	 * Set name.
	 * @param string Frame name ('navigation', 'rightframe').
	 */
	public function setName($name) {
		$this->chkData(array('name' => $name));
		$this->name = $name;
	}

	/**
	 * Get source.
	 * @return W3S_NodeLink Frame source.
	 */
	public function getSource() {
		return $this->src;
	}

	/**
	 * Set source.
	 * @param W3S_NodeLink NodeLink object.
	 */
	public function setSource($src) {
		$this->chkData(array('src' => $src));

		$this->src = $src;
	}

	/**
	 * Get parameters.
	 * @return array Frame parameters in format: array('param1' => 'yes', 'param2' => 'no')
	 */
	public function getParams() {
		return $this->params;
	}

	/**
	 * Set parameters.
	 * @param array Parameters array in format: array('param1' => 'yes', 'param2' => 'no')
	 */
	public function setParams(array $params) {
		if (is_array($params))
			$this->params = $params;
	}

	/**
	 * Update parameters.
	 * @param array Parameters array in format: array('param1' => 'yes', 'param2' => 'no')
	 */
	public function updateParams(array $params) {
		foreach ($params as $key => $val)
			$this->params[$key] = $val;
	}

	/**
	 * Delete parameters named in array.
	 * @param array Parameters array in format: array('param1', 'param2', ...).
	 */
	public function deleteParams(array $params) {
		foreach ($params as $key)
			unset($this->params[$key]);
	}

	/**
	 * Delete all parameters.
	 */
	public function deleteAllParams() {
		$this->params = array();
	}

}

?>