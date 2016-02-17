<?php

/*
 * \brief utility class for manipulating data in Palo
 *
 * \file PaloData.php
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: PaloData.php 4444 2010-12-10 14:29:34Z predragm $
 *
 */

class PaloData
{
	protected $conn;

	public function __construct ($conn)
	{
		$this->conn = $conn;
	}

	private function _hasRevOrder ($db, $cube)
	{
		return $db != 'System' && substr($cube, 0, 2) == '#_';
	}

	public function dir ($db, $dim, $assoc = false)
	{
		$res = @palo_dimension_list_elements($this->conn, $db, $dim, true);

		$list = array();

		if ($assoc)
			foreach ($res as $idx => &$e)
				$list[$e['name']] = $idx;
		else
			foreach ($res as &$e)
				$list[] = $e['name'];

		return $list;
	}

	public function get ($db, $cube, array $order = array(), array $coords = array())
	{
		$dims = @palo_cube_list_dimensions($this->conn, $db, $cube);

		if (!is_array($dims))
			return (object) array();

		$dims_num = count($dims);

		if (empty($order))
			$order = $this->_hasRevOrder($db, $cube) ? array_reverse($dims, false) : $dims;
		else
			$order = array_merge(array_intersect($order, $dims), array_diff($dims, $order));

		$datav_params = array($this->conn, $db, $cube);
		$coords_num = array();

		foreach ($dims as $idx => $dim)
		{
			$list = $this->dir($db, $dim);

			$coords[$dim] = is_array($coords[$dim]) && !empty($coords[$dim]) ? array_values(array_intersect($list, $coords[$dim])) : $list;
			$coords_num[$dim] = $curr_num = count($coords[$dim]);

			$datav_params[] = array_merge(array($curr_num, $curr_num ? 1 : 0), $coords[$dim]);
		}

		$datav = @call_user_func_array('palo_datav', $datav_params);

		if (!is_array($datav))
			return (object) array();

		array_splice($datav, 0, 2);

		if (empty($datav))
			return (object) array();

		$res = array();
		$curr = &$res;

		$off = 0;
		$oidx = 0;
		$cidx = 0;

		$stack = array();

		while (true)
		{
			$dim = $order[$oidx];
			$cmbs = 1;

			foreach ($dims as $c_dim)
			{
				if ($c_dim == $dim)
					break;

				$cmbs *= $coords_num[$c_dim];
			}

			if ($oidx < $dims_num - 1)
			{
				if ($cidx < $coords_num[$dim] - 1)
					$stack[] = array(&$curr, $oidx, $cidx + 1, $off);

				$coord = $coords[$dim][$cidx];
				$curr[$coord] = array();
				$curr = &$curr[$coord];

				$off += $cidx * $cmbs;
				++$oidx;
				$cidx = 0;

				continue;
			}

			$off += $cidx * $cmbs;

			foreach ($coords[$dim] as $cidx => $coord)
				$curr[$coord] = $datav[$off + $cidx * $cmbs];

			if (($pop = array_pop($stack)) === null)
				break;

			list (, $oidx, $cidx, $off) = $pop;
			$curr = &$pop[0];
		}

		return empty($res) ? (object) array() : $res;
	}

	public function set ($db, $cube, array $data, array $order = array(), $add = true)
	{
		if (empty($data))
			return false;

		$dims = @palo_cube_list_dimensions($this->conn, $db, $cube);

		if (!is_array($dims))
			return false;

		$dims_num = count($dims);

		if (empty($order))
			$order = $this->_hasRevOrder($db, $cube) ? array_reverse($dims, false) : $dims;
		else
			$order = array_merge(array_intersect($order, $dims), array_diff($dims, $order));

		if ($add)
		{
			foreach ($dims as $idx => $dim)
				$coords[$dim] = $this->dir($db, $dim, true);

			$coords_new = array();
		}

		$dims = array_flip($dims);

		reset($data);
		$curr = &$data;

		$coords_list = array();
		$curr_coords = array();
		$vals = array();

		$oidx = 0;

		$stack = array();

		while (true)
		{
			$dim = $order[$oidx];

			if ($oidx < $dims_num - 1)
			{
				$coord = key($curr);
				next($curr);

				if (key($curr) !== null)
					$stack[] = array(&$curr, $oidx, $curr_coords);

				$curr = &$curr[$coord];
				$curr_coords[$dims[$dim]] = $coord;
				++$oidx;

				if ($add && !isset($coords_new[$dim][$coord]) && !isset($coords[$dim][$coord]))
					$coords_new[$dim][$coord] = true;

				continue;
			}

			$didx = $dims[$dim];

			foreach ($curr as $coord => $val)
			{
				$curr_coords[$didx] = $coord;

				$pos = array_push($coords_list, $curr_coords);
				ksort($coords_list[$pos - 1]);

				$vals[] = $val;

				if ($add && !isset($coords_new[$dim][$coord]) && !isset($coords[$dim][$coord]))
					$coords_new[$dim][$coord] = true;
			}

			if (($pop = array_pop($stack)) === null)
				break;

			list (, $oidx, $curr_coords) = $pop;
			$curr = &$pop[0];
		}

		if ($add)
		{
			foreach ($coords_new as $dim => &$coords)
					@palo_element_create_bulk($this->conn, $db, $dim, array_keys($coords), 'S');

			if (!empty($coords_new))
				@palo_ping($this->conn);
		}

		return @palo_setdata_bulk($this->conn, $db, $cube, $coords_list, $vals, false) === true;
	}

	public function remove ($db, $dim, array $coords)
	{
		return @palo_edelete_bulk($this->conn, $db, $dim, $coords) === true;
	}

	public function rename ($db, $dim, array $names)
	{
		$names_map = $this->dir($db, $dim, true);

		foreach ($names as $name_old => $name_new)
		{
			if (!isset($names_map[$name_old]))
				continue;

			if (@palo_erename($this->conn, $db, $dim, $name_old, $name_new) !== true)
				return false;
		}

		return true;
	}

}

?>