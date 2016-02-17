<?php

/*
 * \brief class representing access control policy
 *
 * \file AccessPolicy.php
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: AccessPolicy.php 4521 2011-01-14 11:06:20Z predragm $
 *
 */

class AccessPolicy
{
	const PERM_NONE		= 0,
				PERM_READ		= 1,
				PERM_WRITE	= 3,
				PERM_DELETE	= 7,
				PERM_SPLASH	= 15,

				HIGHEST_RULE_PERM = self::PERM_SPLASH,
				HIGHEST_ELEM_PERM = self::PERM_DELETE;

	private static $perm_conv_map = array(
	  'N' => self::PERM_NONE
	, 'R' => self::PERM_READ
	, 'W' => self::PERM_WRITE
	, 'D' => self::PERM_DELETE
	, 'S' => self::PERM_SPLASH
	);

	private	$host,
					$port,

					$superuser,
					$superpass,

					$user,
					$pass,
					$groups,

					$licensed,

					$superconn,
					$conn,
					$last_conn_type,

					$rules;

	public function __construct ($host, $port, $superuser, $superpass, $user, $pass, $load = true)
	{
		$this->host = $host;
		$this->port = $port;

		$this->superuser = $superuser;
		$this->superpass = $superpass;

		$this->user = $user;
		$this->pass = $pass;

		$this->getSuperConn();
		$this->licensed = is_array($lic = @palo_license_info($this->superconn)) && $lic['expiredate'] > gmmktime();

		if ($load)
			$this->reload();
	}

	public function __sleep ()
	{
//		if (is_resource($this->superconn))
//			@palo_disconnect($this->superconn);
//
//		if (is_resource($this->conn))
//			@palo_disconnect($this->conn);

		return array('host', 'port', 'superuser', 'superpass', 'user', 'pass', 'groups', 'licensed', 'rules');
	}

	public function getSuperConn ()
	{
		if (!is_resource($this->superconn))
		{
			@palo_use_unicode(true);
			$this->superconn = @palo_init($this->host, $this->port, $this->superuser, $this->superpass);
		}

		if (!$this->last_conn_type)
		{
			@palo_ping($this->superconn);
			$this->last_conn_type = true;
		}

		return $this->superconn;
	}

	public function getConn ($check = false)
	{
		if (!is_resource($this->conn))
		{
			@palo_use_unicode(true);
			$this->conn = @palo_init($this->host, $this->port, $this->user, $this->pass, $check);
		}

		if ($this->last_conn_type)
		{
			@palo_ping($this->conn);
			$this->last_conn_type = false;
		}

		return $this->conn;
	}

	public function setUser ($user)
	{
		$this->user = (string) $user;
	}

	public function getUser ()
	{
		return $this->user;
	}

	public function getPass ()
	{
		return $this->pass;
	}

	public function getGroups ()
	{
		return $this->groups;
	}

	public function getRule ($name)
	{
		return isset($this->rules[$name]) ? $this->rules[$name] : -1;
	}

	public function getRules ()
	{
		return $this->rules;
	}

	public function reload (array $groups = null, array $rules = null)
	{
		$conn = $this->getSuperConn();

		if (!is_resource($conn))
			return false;



		// groups
		if (is_array($groups) && count($groups))
			$this->groups = $groups;
		else
		{
			// all groups
			$res = @palo_dimension_list_elements($conn, 'System', '#_GROUP_');

			if (!is_array($res) || !count($res))
				return false;

			foreach ($res as &$entry)
				$all_groups[] = $entry['name'];

			// user's groups
			$res = @palo_datav($conn, 'System', '#_USER_GROUP', $this->user, array_merge(array(count($all_groups), 1), $all_groups));

			if (!is_array($res))
				return false;

			array_splice($res, 0, 2);

			foreach ($res as $idx => $entry)
				if ($entry == '1')
					$all_user_groups[] = $all_groups[$idx];

			if (!count($all_user_groups))
				return false;

			// active user's groups
			$res = @palo_datav($conn, 'System', '#_GROUP_GROUP_PROPERTIES', array_merge(array(1, count($all_user_groups)), $all_user_groups), 'inactive');

			if (is_array($res))
			{
				array_splice($res, 0, 2);

				$this->groups = array();

				foreach ($res as $idx => $entry)
					if ($entry != '1')
						$this->groups[] = $all_user_groups[$idx];
			}
			else
				$this->groups = $all_user_groups;
		}

		$groups_num = count($this->groups);

		if ($groups_num < 1)
			return false;



		// roles

		// all roles
		$res = @palo_dimension_list_elements($conn, 'System', '#_ROLE_');

		if (!is_array($res))
			return false;

		foreach ($res as &$entry)
			$all_roles[] = $entry['name'];

		$all_roles_num = count($all_roles);

		if ($all_roles_num < 1)
			return false;

		// groups' roles
		$res = @palo_datav($conn, 'System', '#_GROUP_ROLE', array_merge(array(1, $groups_num), $this->groups), array_merge(array($all_roles_num, 1), $all_roles));

		if (!is_array($res))
			return false;

		array_splice($res, 0, 2);

		for ($r = 0; $r < $all_roles_num; ++$r)
			for ($g = 0; $g < $groups_num; ++$g)
				if ($res[$r * $groups_num + $g] == '1')
				{
					$roles[] = $all_roles[$r];
					break;
				}

		$roles_num = count($roles);

		if ($roles_num < 1)
			return false;



		// rules
		if (!is_array($rules) || !count($rules))
		{
			$res = @palo_dimension_list_elements($conn, 'System', '#_RIGHT_OBJECT_');

			if (!is_array($res))
				return false;

			foreach ($res as &$entry)
				$rules[] = $entry['name'];
		}

		$rules_num = count($rules);

		if ($rules_num < 1)
			return false;



		// rules effective perms
		$res = @palo_datav($conn, 'System', '#_ROLE_RIGHT_OBJECT', array_merge(array(1, $roles_num), $roles), array_merge(array($rules_num, 1), $rules));

		if (!is_array($res))
			return false;

		array_splice($res, 0, 2);

		$highest_perm = self::HIGHEST_RULE_PERM;
		$this->rules = array();

		for ($u = 0; $u < $rules_num; ++$u)
		{
			for ($perm = $o = 0; $o < $roles_num && $perm < $highest_perm; ++$o)
				$perm |= intval(self::$perm_conv_map[$res[$u * $roles_num + $o]]);

			$this->rules[$rules[$u]] = $this->licensed ? $perm : ($perm <= self::PERM_READ ? $perm : self::PERM_READ);
		}

		return true;
	}

	public function calcPerms ($db, $dim, array $elems, $elems_chk = false, $rule = '', $rule_as_def = false)
	{
		$conn = $this->getSuperConn();

		if ($elems_chk)
		{
			$res = @palo_dimension_list_elements($conn, $db, $dim, true);

			if (is_array($res) && count($res))
				foreach ($res as &$elem)
					$elems_seen[] = $elem['name'];
			else
				$elems_seen = array();

			$miss = array_diff($elems, $elems_seen);
			$miss_num = count($miss);

			$perms = $miss_num ? array_combine($miss, array_fill(0, $miss_num, self::PERM_NONE)) : array();
			$elems = array_intersect($elems, $elems_seen);
		}
		else
			$perms = array();

		if (!($elems_num = count($elems)))
			return $perms;

		$groups_num = count($this->groups);

		$res = @palo_datav($conn, $db, '#_GROUP_DIMENSION_DATA_' . $dim, array_merge(array(1, $groups_num), $this->groups), array_merge(array($elems_num, 1), $elems));

		if (!is_array($res))
			return array_combine($elems, array_fill(0, $elems_num, self::PERM_NONE));

		array_splice($res, 0, 2);

		$rule = $this->getRule($rule);
		$highest_perm = self::HIGHEST_ELEM_PERM;

		for ($e = 0; $e < $elems_num; ++$e)
		{
			for ($perm = -1, $g = 0; $g < $groups_num && $perm < $highest_perm; ++$g)
				if (isset(self::$perm_conv_map[$entry = $res[$e * $groups_num + $g]]))
					$perm = $perm == -1 ? self::$perm_conv_map[$entry] : $perm | self::$perm_conv_map[$entry];

			$perms[$elems[$e]] = $rule != -1 && ($perm > $rule || ($rule_as_def && $perm == -1)) ? $rule : $perm;
		}

		return $perms;
	}

}

?>