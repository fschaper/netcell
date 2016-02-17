<?php

/*
 * \brief class representing preferences (user, group or server level)
 *
 * \file Prefs.php
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
 * SVN: $Id: Prefs.php 4629 2011-02-15 10:22:29Z predragm $
 *
 */

class Prefs
{
	const ATTR_NAME = 'prefs';

	const LEVEL_SERVER	= 0,
				LEVEL_GROUP		= 1,
				LEVEL_USER		= 2;

	private static $locations = array(
	  self::LEVEL_SERVER => array('db' => 'Config', 'dim' => 'config', 'cube' => '#_config', 'attr' => 'value')
	, self::LEVEL_GROUP => array('db' => 'System', 'dim' => '#_GROUP_PROPERTIES_', 'cube' => '#_GROUP_GROUP_PROPERTIES')
	, self::LEVEL_USER => array('db' => 'System', 'dim' => '#_USER_PROPERTIES_', 'cube' => '#_USER_USER_PROPERTIES')
	);

	private static $default = array('general' => array('l10n' => DEF_PREFS_L10N, 'theme' => DEF_PREFS_THEME, 'updatecheck' => DEF_PREFS_UPCHK), 'studio' => array('default' => array('view' => DEF_PREFS_VIEW)), 'wss' => array('interface' => DEF_PREFS_IFACE));

	private $level,
					$name,

					$idx,
					$prefs;

	public function __construct (AccessPolicy $apol, $level, $name = null)
	{
		$this->level = $level;
		$this->name = $name;

		$this->reload($apol);
	}

	public function reload (AccessPolicy $apol)
	{
		$this->idx = 0;
		$this->prefs = array();

		$xmlData = new XMLData($_SERVER['DOCUMENT_ROOT'] . '/../etc/schema/prefs.rng');

		$loc = &self::$locations[$this->level];

		switch ($this->level)
		{
			case self::LEVEL_USER:

				if ($this->name)
				{
					$apol = clone $apol;
					$apol->setUser($this->name);
					$apol->reload();
				}
				else
				{
					$this->name = $apol->getUser();

					$this->idx = 1;
					$this->prefs[] = array();
				}

				$xmlData->loadPalo($apol, $loc['db'], $loc['cube'], array($this->name, self::ATTR_NAME));

				$prefs = $xmlData->get('.');
				$this->prefs[] = isset($prefs[self::ATTR_NAME]) ? $prefs[self::ATTR_NAME] : array();

				$loc = &self::$locations[self::LEVEL_GROUP];

				foreach ($apol->getGroups() as $group)
					if ($xmlData->loadPalo($apol, $loc['db'], $loc['cube'], array($group, self::ATTR_NAME)))
					{
						$prefs = $xmlData->get('.');

						if (isset($prefs[self::ATTR_NAME]))
							$this->prefs[] = $prefs[self::ATTR_NAME];
					}

				break;

			case self::LEVEL_GROUP:

				if (!$this->name)
					return false;

				$xmlData->loadPalo($apol, $loc['db'], $loc['cube'], array($this->name, self::ATTR_NAME));

				$prefs = $xmlData->get('.');
				$this->prefs[] = isset($prefs[self::ATTR_NAME]) ? $prefs[self::ATTR_NAME] : array();

				break;

			default:
				$this->name = self::$locations[self::LEVEL_SERVER]['attr'];
		}

		$loc = &self::$locations[self::LEVEL_SERVER];

		if ($xmlData->loadPalo($apol, $loc['db'], $loc['cube'], array($loc['attr'], self::ATTR_NAME)) || $this->level == self::LEVEL_SERVER)
		{
			$prefs = $xmlData->get('.');
			$this->prefs[] = isset($prefs[self::ATTR_NAME]) ? $prefs[self::ATTR_NAME] : array();
		}

		$this->prefs[] = self::$default;

		return true;
	}

	public function get ($path = null, $idx = -1)
	{
		if ($idx < 0)
			$idx = $this->idx;

		$prefs = &$this->prefs[$idx];

		if (!is_string($path) || !strlen($path))
			return $prefs;

		foreach (split('/', $path) as $key)
		{
			if (!isset($prefs[$key]))
				return null;

			$prefs = &$prefs[$key];
		}

		return $prefs;
	}

	public function has ($path, $idx = -1)
	{
		if ($idx < 0)
			$idx = $this->idx;

		$prefs = &$this->prefs[$idx];

		foreach (split('/', $path) as $key)
		{
			if (!isset($prefs[$key]))
				return false;

			$prefs = &$prefs[$key];
		}

		return true;
	}

	public function set ($path, $val, $idx = -1)
	{
		if ($idx < 0)
			$idx = $this->idx;

		if (!is_string($path) || !strlen($path))
		{
			$this->prefs[$idx] = $val;
			return true;
		}

		$prefs = &$this->prefs[$idx];

		$path = split('/', $path);
		$last_key = array_pop($path);

		foreach ($path as $key)
		{
			if (!isset($prefs[$key]))
				$prefs[$key] = array();

			$prefs = &$prefs[$key];
		}

		$prefs[$last_key] = $val;

		return true;
	}

	public function remove ($path, $idx = -1)
	{
		if ($idx < 0)
			$idx = $this->idx;

		$prefs = &$this->prefs[$idx];

		$path = split('/', $path);
		$last_key = array_pop($path);

		foreach ($path as $key)
		{
			if (!isset($prefs[$key]))
				return false;

			$prefs = &$prefs[$key];
		}

		unset($prefs[$last_key]);

		return true;
	}

	public function search ($path, $path_local = null)
	{
		$path = split('/', $path);
		$path_local = is_string($path_local) ? split('/', $path_local) : array();

		foreach ($this->prefs as &$prefs)
		{
			$continue = false;

			foreach ($path as $key)
			{
				if (!isset($prefs[$key]))
				{
					$continue = true;
					break;
				}

				$prefs = &$prefs[$key];
			}

			if ($continue)
				continue;

			$continue = false;

			foreach ($path_local as $key)
			{
				if (!isset($prefs[$key]))
				{
					$continue = true;
					break;
				}

				$prefs = &$prefs[$key];
			}

			if ($continue)
				continue;

			return $prefs;
		}

		return null;
	}

	public function save (AccessPolicy $apol)
	{
		$xmlData = new XMLData($_SERVER['DOCUMENT_ROOT'] . '/../etc/schema/prefs.rng');

		if (!count($this->prefs[$this->idx]) || !$xmlData->loadArray(array(self::ATTR_NAME => $this->prefs[$this->idx])))
			return false;

		$loc = &self::$locations[$this->level];

		if (!is_int(palo_eindex($conn = $apol->getSuperConn(), $loc['db'], $loc['dim'], self::ATTR_NAME, true)))
		{
			palo_eadd($conn, $loc['db'], $loc['dim'], 'S', self::ATTR_NAME, '', 1, false, true);
			palo_ping($conn);
		}

		return $xmlData->savePalo($apol, $loc['db'], $loc['cube'], array($this->name, self::ATTR_NAME));
	}

	public function dump ($idx = null)
	{
		return isset($this->prefs[$idx]) ? $this->prefs[$idx] : $this->prefs;
	}

}

?>