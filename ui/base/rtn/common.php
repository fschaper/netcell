<?php

/*
 * \brief commmon routines
 *
 * \file common.php
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
 * SVN: $Id: common.php 5092 2011-07-01 12:43:31Z predragm $
 *
 */

class common
{
	// recent
	public static function fetchRecent ($context = null, $type = null)
	{
		$recent = new Recent($_SESSION['accessPolicy']);

		return $recent->fetch($context, $type);
	}

	public static function clearRecent ($context = null, $type = null)
	{
		$recent = new Recent($_SESSION['accessPolicy']);

		$recent->clear($context, $type);

		return $recent->save();
	}


	// tagged
	public static function fetchTagged ($context = null, $type = null, $tag = null)
	{
		$tagged = new Tagged($_SESSION['accessPolicy']);

		return $tagged->fetch($context, $type, $tag);
	}

	public static function addTagged ($context, $type, $location, $tag, $subtype = null)
	{
		$tagged = new Tagged($_SESSION['accessPolicy']);

		$tagged->add($context, $type, $location, $tag, $subtype);

		return $tagged->save();
	}

	public static function clearTagged ($context = null, $type = null, $tag = null)
	{
		$tagged = new Tagged($_SESSION['accessPolicy']);

		$tagged->clear($context, $type, $tag);

		return $tagged->save();
	}

	public static function removeTagged (array $items)
	{
		$tagged = new Tagged($_SESSION['accessPolicy']);

		$tagged->remove($items);

		return $tagged->save();
	}

	public static function distinctTagged ($context = null, $type = null)
	{
		$tagged = new Tagged($_SESSION['accessPolicy']);

		return $tagged->distinct($context, $type);
	}


	// palo data
	private static function _initPaloConn ($name = null)
	{
		$apol = $_SESSION['accessPolicy'];

		if (!$name)
			return $apol->getConn();

		$data = common::paloGet(null, 'Config', '#_connections', array('connections'), array('connections' => array($name), '#_connections_' => array('host', 'port', 'username', 'password', 'active', 'useLoginCred')));
		$data = $data[$name];

		if ($data['active'] != '1')
			return null;

		@palo_use_unicode(true);

		return $data['useLoginCred'] != '1' ? @palo_init($data['host'], $data['port'], $data['username'], $data['password']) : @palo_init($data['host'], $data['port'], $apol->getUser(), $apol->getPass());
	}

	public static function paloDir ($conn, $db, $dim, $assoc = false)
	{
		if (!is_resource($conn = self::_initPaloConn($conn)))
			return array();

		$paloData = new PaloData($conn);

		return $paloData->dir($db, $dim, $assoc);
	}

	public static function paloGet ($conn, $db, $cube, array $order = array(), array $coords = array())
	{
		if (!is_resource($conn = self::_initPaloConn($conn)))
			return array();

		$paloData = new PaloData($conn);

		return $paloData->get($db, $cube, $order, $coords);
	}

	public static function paloSet ($conn, $db, $cube, array $data, array $order = array(), $add = true)
	{
		if (!is_resource($conn = self::_initPaloConn($conn)))
			return false;

		$paloData = new PaloData($conn);

		return $paloData->set($db, $cube, $data, $order, $add);
	}

	public static function paloRemove ($conn, $db, $dim, array $coords)
	{
		if (!is_resource($conn = self::_initPaloConn($conn)))
			return false;

		$paloData = new PaloData($conn);

		return $paloData->remove($db, $dim, $coords);
	}

	public static function paloRename ($conn, $db, $dim, array $names)
	{
		if (!is_resource($conn = self::_initPaloConn($conn)))
			return false;

		$paloData = new PaloData($conn);

		return $paloData->rename($db, $dim, $names);
	}


	// fopper
	public static function checkFopperLicense ()
	{
		$res = ccmd(array('cmd' => 'clic', 'base64Encoded' => false, 'doc' => '', 'err' => ''), -1, null, CFG_FOPPER_PATH);

		return array(!strlen($res['err']), $res['err']);
	}

}

?>