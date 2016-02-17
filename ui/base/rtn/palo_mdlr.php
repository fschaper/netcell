<?php

/*
 * \brief RPC routines for handling Palo Modeller
 *
 * \file palo_mdlr.php
 *
 * Copyright (C) 2006-2010 Jedox AG
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: palo_mdlr.php 5124 2011-07-18 11:28:00Z mladent $
 *
 */

class palo_mdlr
{
	/* private methods */
	private static function _addElemRules(&$elems, $connName, $dbName, $dimName)
	{
		$perms = null;
		if (strpos($dimName, '#_') !== 0)
		{
			$aplcy = palo::getAP($connName);

			if ($aplcy != null)
			{
				$elemNames = array();
				foreach ($elems as $elem)
					$elemNames[] = $elem['name'];
				$perms = $aplcy->calcPerms($dbName, $dimName, $elemNames, false, 'dimension element', true);
			}
		}

		$numOfElems = count($elems);
		for ($i = 0; $i < $numOfElems; $i++)
			$elems[$i]['perms'] = ($perms != null) ? $perms[$elems[$i]['name']] : 7; // 7 - read, write, delete
	}

	/* public methods */
	// Element
	public static function getDimElems($connName, $dbName, $dimName, $fromId, $toId)
	{
		// TODO: Change in Future when new version of Palo Server and Palo PHP API is widely used
		$newPaloMethods = function_exists('palo_dimension_reduced_top_list_elements');

		palo::paloCheckDbName($dbName);
		// adjusting dimName for different working modes
		$conn = palo::palo_init($connName);

		if ($_SESSION['servid_' . $connName][$dbName][$dimName]['workingMode'] == 'subsets')
		{
			$listSubset = palo_dimension_list_elements($conn, $dbName, '#_SUBSET_', true);
			$listElems = array();
			foreach($listSubset as $subset)
				if (palo_data($conn, $dbName, '#_SUBSET_GLOBAL', $dimName, $subset['name']) != null)
					$listElems[] = array('name' => $subset['name'], 'type' => 'subset', 'identifier' => $subset['identifier']);

			$numOfElems = count($listElems);
		}
		else
		{
			$dimName = palo::adjustDimModeName($connName, $dbName, $dimName);

			$dimInfo = palo_dimension_info($conn, $dbName, $dimName); // index 2 - number of elements
			$numOfElems = intval($dimInfo[2]);

			if ($toId > $numOfElems)
				$toId = $numOfElems;

			if ($newPaloMethods && isset($fromId) && isset($toId))
			{
				$listElems = array();
				$listDetailedElems = palo_dimension_reduced_flat_list_elements($conn, $dbName, $dimName, $fromId, $toId - $fromId);
				foreach ($listDetailedElems as $elem)
					$listElems[] = array('name' => $elem['name'], 'type' => $elem['type'], 'identifier' => $elem['identifier']);
			}
			else
				$listElems = palo_dimension_list_elements($conn, $dbName, $dimName, true);
		}

		palo::palo_disconnect($conn);

		if (!$newPaloMethods && isset($fromId) && isset($toId))
		{
			$toId = ($toId > count($listElems)) ? count($listElems) : $toId;
			$listElems = array_slice($listElems, $fromId, $toId - $fromId);
		}

		// Add Elem Rights
		if (isset($fromId) && isset($toId))
			self::_addElemRules($listElems, $connName, $dbName, $dimName);

		return array(array($fromId, $toId, count($listElems), $numOfElems), $listElems);
	}
}

?>