<?php

/*
 * @brief W3S_
 *
 * @file W3S_Frameset.php
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
 * SVN: $Id: W3S_Frameset.php 3931 2010-10-04 22:31:06Z drazenk $
 *
 */

final class W3S_Frameset {

	private $rows; // Single value - '30%,400,*,2*'
	private $cols; // Single value - '33%,34%,33%'
	private $frames; // Array of W3S_Frame objects

	public function __construct($frames, $rows = null, $cols = null) {
		if (func_num_args() > 1) {
			$this->chkData(array('rows' => $rows, 'cols' => $cols));

			$this->rows = $rows;
			$this->cols = $cols;

			$this->chkData(array('frames' => $frames));

			$this->frames = $frames;
		} else {
			$frameset = $frames;

			if (!array_key_exists('rows', $frameset) && !array_key_exists('cols', $frameset))
				throw new WSS_Exception('W3S_Frameset-inv_frameset_rowcol', array('type' => 'rows/cols'), 'Invalid rows/cols information for frameset.');

			if (array_key_exists('rows', $frameset)) {
			 	if (strlen($frameset['rows']) > 0)
			 		$this->rows = $frameset['rows'];
			 	else
					throw new WSS_Exception('W3S_Frameset-inv_frameset_rowcol', array('type' => 'rows'), 'Invalid rows information for frameset.');
			}

			if (array_key_exists('cols', $frameset)) {
			 	if (strlen($frameset['cols']) > 0)
			 		$this->cols = $frameset['cols'];
			 	else
					throw new WSS_Exception('W3S_Frameset-inv_frameset_rowcol', array('type' => 'cols'), 'Invalid cols information for frameset.');
			}

			if (!array_key_exists('frames', $frameset) || count($frameset['frames']) == 0)
				throw new WSS_Exception('W3S_Frameset-no_frames', array(), 'No frames in frameset.');

			if (count($frameset['frames']) != (isset($this->rows) ? count(explode(',', $this->rows)) : 1) * (isset($this->cols) ? count(explode(',', $this->cols)) : 1))
				throw new WSS_Exception('W3S_Frameset-inv_frame_count', array(), 'Invalid frame count in frameset.');

			$this->frames = array();
			foreach ($frameset['frames'] as $frame)
				$this->frames[] = new W3S_Frame($frame['name'], new W3S_NodeLink($frame['group'], $frame['hierarchy'], $frame['node'], $frame['type']), $frame['params']);
		}

		$this->chkFrameNames();
	}

	private function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {
				// Check rows.
				case 'rows':
					if (isset($value) && strlen($value) == 0)
						throw new WSS_Exception('W3S_Frameset-inv_frameset_rowcol', array('type' => 'rows'), 'Invalid rows information for frameset.');
					break;

				// Check cols.
				case 'cols':
					if (isset($value) && strlen($value) == 0)
						throw new WSS_Exception('W3S_Frameset-inv_frameset_rowcol', array('type' => 'cols'), 'Invalid cols information for frameset.');
					break;

				// Check frames.
				case 'frames':
					if (!is_array($value) || count($value) == 0)
						throw new WSS_Exception('W3S_Frameset-no_frames', array(), 'No frames in frameset.');

					if (count($value) != (isset($this->rows) ? count(explode(',', $this->rows)) : 1) * (isset($this->cols) ? count(explode(',', $this->cols)) : 1))
						throw new WSS_Exception('W3S_Frameset-inv_frame_count', array(), 'Invalid frame count in frameset.');

					foreach ($value as $frame)
						if (get_class($frame) != 'W3S_Frame')
							throw new WSS_Exception('W3S_Frameset-inv_frame', array(), 'Invalid frame in frameset.');

					break;

				// Check frame.
				case 'frame':
					if (get_class($value) != 'W3S_Frame')
						throw new WSS_Exception('W3S_Frameset-inv_frame', array(), 'Invalid frame in frameset.');
			}
		}
	}

	private function chkFrameNames() {
		$names = array();

		foreach ($this->frames as $frame) {
			$frame_name = $frame->getName();

			if (in_array($frame_name, $names, true))
				throw new WSS_Exception('W3S_Frameset-duplicate_frame_name', array('name' => $frame_name), 'Duplicate frame name "' . $frame_name . '".');
			else
				$names[] = $frame_name;
		}
	}

	/**
	 * Get frameset as associative array.
	 * @return array Frameset as associative array.
	 */
	public function getAssoc() {
		$frameset = array(); $frames = array();

		foreach($this->frames as $frame)
			$frames[] = $frame->getAssoc();

		if (count($frames) > 0)
			$frameset['frames'] = $frames;

		if (isset($this->rows))
			$frameset['rows'] = $this->rows;

		if (isset($this->cols))
			$frameset['cols'] = $this->cols;

		return $frameset;
	}

	/**
	 * Get rows.
	 * @return string Rows dimensions or null if rows not set.
	 */
	public function getRows() {
		return $this->rows;
	}

	/**
	 * Set rows.
	 * @param string Rows dimensions or null if rows not set.
	 */
	public function setRows($rows) {
		$this->chkData(array('rows' => $rows));

		$this->rows = $rows;
	}

	/**
	 * Get cols.
	 * @return string Cols dimensions or null if cols not set.
	 */
	public function getCols() {
		return $this->cols;
	}

	/**
	 * Set cols.
	 * @param string Cols dimensions or null if cols not set.
	 */
	public function setCols($cols) {
		$this->chkData(array('cols' => $cols));

		$this->cols = $cols;
	}

	/**
	 * Get frames.
	 * @return array Array of W3S_Frame objects.
	 */
	public function getFrames() {
		return $this->frames;
	}

	/**
	 * Get frame.
	 * @return W3S_Frame Frame objects.
	 */
	public function getFrame($id) {
		return array_key_exists($id, $this->frames) ? $this->frames[$id] : null;
	}

	/**
	 * Set frames.
	 * @param array Array of W3S_Frame objects.
	 */
	public function setFrames($frames) {
		$this->chkData(array('frames' => $frames));

		$this->frames = $frames;
	}

	/**
	 * Set frame.
	 * @param W3S_Frame Frame objects.
	 */
	public function setFrame($id, $frame) {
		$this->chkData(array('frame' => $frame));

		if (array_key_exists($id, $this->frames))
			$this->frames[$id] = $frame;
	}

}

?>