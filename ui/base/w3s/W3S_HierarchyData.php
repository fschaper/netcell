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
 * SVN: $Id: W3S_HierarchyData.php 3560 2010-07-23 13:32:53Z drazenk $
 *
 */

class W3S_HierarchyData extends W3S_BaseData {

	// Constants
	private static $types = array('report', 'file');

	private $triggersOn = true;
	private $triggers = array(
		'moveHierarchy_before' => array(),
		'moveHierarchy_after' => array()
	);

	// W3S_Backend object.
	private $backend;

	/**
	 * Constructor.
	 * @param array Basic node data: array('el' => 'e0', 'type' => report | file, 'name' => 'Some name', 'desc' => 'Some description', 'backend' => array('type' => ('local' | 'SMB' | 'WebDAV' | 'FTP' | 'SVN' | 'CVS'), 'location' => ('URL' | 'Path'), 'username' => 'admin', 'password' => 'adminpass')).
	 */
	public function __construct($params = null) {
		parent::__construct($params);

		if (isset($params)) {
			$this->chkData(array('element' => $params['el'], 'type' => $params['type'], 'backend' => $params['backend']));

			$this->element = $params['el'];
			$this->type = $params['type'];

			if ($this->type == 'file')
				$this->backend = new W3S_Backend($params['backend']);
		}

	}

	public function __clone() {
		$this->backend = clone $this->backend;
	}

	/**
	 * Check data function.
	 * @access private
	 * @param array Data to check: array('element' => $el, 'type' => $type, 'name' => $name)
	 */
	protected function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {

				// Check element.
				case 'element':
					if (!preg_match('/^(h)(\\d+)$/is', $value))
						throw new WSS_Exception('W3S_HierarchyData-inv_el', array(), 'Invalid element.');
					break;

				// Check type.
				case 'type':
					if (!in_array($value, self::$types, true))
						throw new WSS_Exception('W3S_HierarchyData-inv_el_type', array(), 'Invalid element type.');
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

		// Process backend.
		if ($this->type == 'file') {
			$nl_backend = $xpath->query('backend', $root);
			$this->chkNode('backend', $nl_backend, true, false);
			$this->importBackend($nl_backend->item(0));
		}
	}

	private function importBackend(&$backend) {
		// Process backend.
		$arr_backend = array();
		foreach ($backend->attributes as $attr_name => $attr_node)
			$arr_backend[$attr_name] = $attr_node->value;

		$this->backend = new W3S_Backend($arr_backend);
	}

	/**
	 * XML export function.
	 * @access public
	 * @return string XML data.
	 */
	public function export() {
		$dom = $this->exportInit();
		$el_element = $dom->documentElement;

		if ($this->type == 'file') {
			// Create backend element.
			$el_backend = $dom->createElement('backend');

			foreach ($this->backend->getData() as $key => $value)
				$el_backend->setAttribute($key, $value);

			$el_element->appendChild($el_backend);
		}

		return $dom->saveXML();
	}

	// ########
	// Triggers
	// ########

	public function registerPlugin (W3S_Plugin $plugin) {
		foreach ($plugin->getTriggerInfo() as $event => $ident)
			if (isset($this->triggers[$event]))
				$this->triggers[$event][] = array($plugin, $ident);

		return true;
	}

	public function disableTriggers () {
		$this->triggersOn = false;
	}

	public function enableTriggers () {
		$this->triggersOn = true;
	}

	// ###################
	// Getters and setters
	// ###################

	/**
	 * Get backend.
	 *
	 * @return array Backend as W3S_Backend object.
	 */
	public function getBackend() {
		return $this->backend;
	}

	/**
	 * Set backend.
	 * @param W3S_Backend Backend object.
	 */
	public function setBackend($backend) {
		if ($this->type == 'file') {
			$this->chkData(array('backend' => $backend));

			$location_changed = strcasecmp($this->backend->getLocation(), $backend->getLocation());

			if ($location_changed != 0 && $this->triggersOn && isset($this->triggers['moveHierarchy_before']))
				foreach ($this->triggers['moveHierarchy_before'] as $trigger)
					call_user_func(array($trigger[0], 'moveHierarchy_before'), $trigger[1], $this->element, $this->name, $this->backend->getLocation(), $backend->getLocation());

			$this->backend = $backend;

			if ($location_changed != 0 && $this->triggersOn && isset($this->triggers['moveHierarchy_after']))
				foreach ($this->triggers['moveHierarchy_after'] as $trigger)
					call_user_func(array($trigger[0], 'moveHierarchy_after'), $trigger[1], $this->element, $this->name, $this->backend->getLocation(), $backend->getLocation());
		} else
			throw new WSS_Exception('W3S_HierarchyData-backend_unsupported', array(), 'Unable to set backend on hierarchy other than "file".');
	}
}

?>