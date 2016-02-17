<?php

/*
 * \brief class for w3s ops
 *
 * \file w3s.php
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: w3s.php 4994 2011-05-25 10:52:00Z drazenk $
 *
 */

class w3s {

	const UNMODIFIED = 0;				// Return unmodified map list.
	const INC_VAR_PARAMS = 1;		 	// Include variable parameters.
	const EXC_PRIVATE_VARS = 2;			// Exclude maps to private variables.
	const INC_UNMAPPED_VARS = 4;		// Include unmapped variables.

	public static function getMap($conn, W3S_NodeData $node_data, $format = self::UNMODIFIED, array $vars = array()) {
		$maps = $node_data->getMap();

		if ($node_data->getType() == 'rfolder' || (!count($maps) && !($format & self::INC_UNMAPPED_VARS)) || $format == self::UNMODIFIED)
			return self::_filterMap($maps, $vars);

		if ($format & (self::INC_VAR_PARAMS | self::EXC_PRIVATE_VARS | self::INC_UNMAPPED_VARS)) {
			$ref = $node_data->getReference()->getGHNAssoc();
			$ref_node_data = W3S_NodeData::getNodeData($conn, $ref['group'], $ref['hierarchy'], $ref['node']);

			if (is_null($ref_node_data))
				return self::_filterMap($maps, $vars);

			// Fill map variables with additional info.
			switch ($ref_node_data->getType()) {
				case 'workbook':
					$ref_node_data->fillVarInfo($maps, $format & self::INC_UNMAPPED_VARS);
					break;

				case 'frameset':
					foreach ($ref_node_data->getFrameset()->getFrames() as $frame) {
						$frame_src = $frame->getSource();
						$frame_node_data = W3S_NodeData::getNodeData($conn, $frame_src->getGroup(), $frame_src->getHierarchy(), $frame_src->getNode());

						if (is_null($frame_node_data))
							continue;

						if ($frame_node_data->getType() == 'workbook')
							$frame_node_data->fillVarInfo($maps, $format & self::INC_UNMAPPED_VARS);
					}

					break;
			}
		}

		if (!($format & self::EXC_PRIVATE_VARS))
			return self::_filterMap($maps, $vars);

		// Filter maps.
		$fltr_maps = array();

		foreach($maps as $mkey => $mval)
			if ($mval['force'] || !$mval['private'])
				$fltr_maps[$mkey] = !($format & self::INC_VAR_PARAMS) ? array('defval' => $mval['defval'], 'list' => $mval['list'], 'ordnum' => $mval['ordnum'], 'force' => $mval['force']) : $mval;

		return self::_filterMap($fltr_maps, $vars);
	}

	private static function _filterMap(&$map, &$vars) {
		if (!count($vars))
			return $map;

		$fltrd = array();

		foreach ($vars as $var)
			if (array_key_exists($var, $map))
				$fltrd[$var] = $map[$var];

		return $fltrd;
	}

}

?>