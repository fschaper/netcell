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
 * SVN: $Id: W3S_NodeLink.php 3529 2010-07-15 16:02:11Z drazenk $
 *
 */

class W3S_NodeLink {

	// Constants
	private static $type_subset = array('workbook', 'hyperlink', 'frameset');

	private $group;
	private $hierarchy;
	private $node;
	private $type;

	/**
	 * Constructor.
	 * @param string Group name (Palo DB name).
	 * @param string Hierarchy name (hierarchy dimension name - h1, h2,..., hn).
	 * @param string Node name (node element name - n1, n2,..., nn).
	 * @param string Node type ('workbook'|'hyperlink'|'html'|'pdf'|...).
	 */
	public function __construct($group, $hierarchy, $node, $type = 'unknown') {
		$this->chkData(array('group' => $group, 'hierarchy' => $hierarchy, 'node' => $node, 'type' => $type));

		$this->group = $group;
		$this->hierarchy = $hierarchy;
		$this->node = $node;
		$this->type = $type;

	}

	private function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {
				// Check group.
				case 'group':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_NodeLink-err_group', array(), 'Invalid group name.');
					break;

				// Check hierarchy.
				case 'hierarchy':
					if (!preg_match('/^(h)(\\d+)$/is', $value))
						throw new WSS_Exception('W3S_NodeLink-err_hierarchy', array(), 'Invalid hierarchy name.');
					break;

				// Check node.
				case 'node':
					if (!preg_match('/^(n)(\\d+)$/is', $value))
						throw new WSS_Exception('W3S_NodeLink-err_node', array(), 'Invalid node name.');
					break;

				// Check type.
				case 'type':
					if (!in_array($value, self::$type_subset) && $value != W3S_NodeData::$def_subtype &&
						!in_array($value, W3S_NodeData::$subtypesStatic) && !in_array($value, W3S_NodeData::$subtypesUrlplugin))
						throw new WSS_Exception('W3S_NodeLink-err_type', array(), 'Invalid node type.');
					break;
			}
		}
	}

	// ###################
	// Getters and setters
	// ###################

	/**
	 * Get Group name.
	 * @return string Group name (Palo DB name).
	 */
	public function getGroup() {
		return $this->group;
	}

	/**
	 * Get Hierarchy name.
	 * @return string Hierarchy name (hierarchy dimension name - h1, h2,..., hn).
	 */
	public function getHierarchy() {
		return $this->hierarchy;
	}

	/**
	 * Get Node name.
	 * @return string Node name (node element name - n1, n2,..., nn).
	 */
	public function getNode() {
		return $this->node;
	}

	/**
	 * Get Node type.
	 * @return string Node type ('workbook'|'hyperlink'|'html'|'pdf'|...).
	 */
	public function getType() {
		return $this->type;
	}

	public function getAssoc() {
		return array('group' => $this->group, 'hierarchy' => $this->hierarchy, 'node' => $this->node, 'type' => $this->type);
	}

	public function getGHNAssoc() {
		return array('group' => $this->group, 'hierarchy' => $this->hierarchy, 'node' => $this->node);
	}
}

?>