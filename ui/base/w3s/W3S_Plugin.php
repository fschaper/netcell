<?php

/*
 * \brief W3S plugin interface
 *
 * \file W3S_Plugin.php
 *
 * Copyright (C) 2006-2011 Jedox AG
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: W3S_Plugin.php 4988 2011-05-24 12:25:52Z drazenk $
 *
 */

interface W3S_Plugin
{
	public function getTriggerInfo ();

	public function addHierarchy_before (array $ident, W3S_Hierarchy $hierarchy);
	public function addHierarchy_after (array $ident, W3S_Hierarchy $hierarchy);

	public function removeHierarchy_before (array $ident, W3S_Hierarchy $hierarchy);
	public function removeHierarchy_after (array $ident, W3S_Hierarchy $hierarchy);

	public function renameHierarchy_before (array $ident, W3S_Hierarchy $hierarchy, $new_name);
	public function renameHierarchy_after (array $ident, W3S_Hierarchy $hierarchy, $old_name);

	public function moveHierarchy_before (array $ident, $uid, $name, $old_location, $new_location);
	public function moveHierarchy_after (array $ident, $uid, $name, $old_location, $new_location);

	public function getHierarchyProps (array $ident, W3S_Hierarchy $hierarchy);

	public function addNode_before (array $ident, W3S_Node $node);
	public function addNode_after (array $ident, W3S_Node $node);

	public function replaceNode_before (array $ident, W3S_Node $node, array $data);
	public function replaceNode_after (array $ident, W3S_Node $node);

	public function removeNode_before (array $ident, W3S_Node $node);
	public function removeNode_after (array $ident, W3S_Node $node);

	public function moveNode_before (array $ident, W3S_Node $node, W3S_Node $new_parent, $new_pos);
	public function moveNode_after (array $ident, W3S_Node $node, W3S_Node $old_parent, $old_pos);

	public function copyNode_before (array $ident, W3S_Node $node_orig, W3S_Node $new_parent, $new_pos, array &$data);
	public function copyNode_after (array $ident, W3S_Node $node_orig, W3S_Node $node_copy, array &$data);

	public function renameNode_before (array $ident, W3S_Node $node, $new_name);
	public function renameNode_after (array $ident, W3S_Node $node, $old_name);

	public function importNode_before (array $ident, W3S_Node $parent, $leaf, $type, array &$data, $pos);
	public function importNode_after (array $ident, $type, array &$data, W3S_Node $node);

	public function importBundleNode_before (array $ident, W3S_Node $parent, $leaf, $type, array &$data, $pos);
	public function importBundleNode_after (array $ident, $type, array &$data, W3S_Node $node);

	public function iniNodeProps (array $ident, W3S_Node $node, array $params);
	public function getNodeProps (array $ident, W3S_Node $node, array $ini = null);
}

?>