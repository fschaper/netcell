<?php

/*
 * \brief class for working with recent items
 *
 * \file Recent.php
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
 * SVN: $Id: Recent.php 5062 2011-06-16 10:44:31Z predragm $
 *
 */

class Recent extends XMLData
{
	const ATTR_NAME		= 'recent',
				DEFAULT_MAX	= 16;

	private static function _make_query ($context = null, $type = null)
	{
		if ($type)
		{
			if (!is_array($type))
				$type = 'type = "' . $type . '"';
			else
			{
				foreach ($type as $i => $t)
					$type[$i] = 'type = "' . $t . '"';

				$type = join(' or ', $type);
			}

			return $context ? ('item[context = "' . $context . '" and (' . $type .')]') : ('item[' . $type . ']');
		}

		if ($context)
			return 'item[context = "' . $context . '"]';

		return 'item';
	}

	public function __construct (AccessPolicy $apol)
	{
		parent::__construct($_SERVER['DOCUMENT_ROOT'] . '/../etc/schema/recent.rng');

		if ($this->loadPalo($apol, 'System', '#_USER_USER_PROPERTIES', array($apol->getUser(), self::ATTR_NAME)))
			return;

		$this->set(null, array(self::ATTR_NAME => array('@' => array('max' => self::DEFAULT_MAX))));

		if (!is_int(@palo_eindex($conn = $apol->getSuperConn(), 'System', '#_USER_PROPERTIES_', self::ATTR_NAME, true)))
		{
			@palo_eadd($conn, 'System', '#_USER_PROPERTIES_', 'S', self::ATTR_NAME, '', 1, false, true);
			@palo_ping($conn);
		}
	}

	public function fetch ($context = null, $type = null)
	{
		$res = $this->get(self::_make_query($context, $type));

		if (!isset($res['item']))
			return array();

		$res = $res['item'];

		return isset($res['context']) ? array($res) : $res;
	}

	public function add ($context, $type, $location, $subtype = null)
	{
		// remove duplicates if any
		$query = 'item[context = "' . $context . '"';

		if (is_array($location))
			foreach ($location as $key => &$val)
				$query .= ' and location/' . $key . ' = "' . $val . '"';
		else
			$query .= ' and location = "' . $location . '"';

		parent::remove($query . ']');

		// remove surplus item
		$recent = $this->doc->documentElement;

		if ($this->evaluate('count(item)') >= intval($recent->getAttribute('max')))
			$recent->removeChild($recent->firstChild);

		// add item
		$item = array('context' => $context, 'type' => $type);

		if ($subtype)
			$item['subtype'] = $subtype;

		if (isset($location['path'])) // TODO: evaluate moving to XMLData
			$location['path'] = htmlspecialchars($location['path']);

		$item['location'] = $location;

		return $this->set('.', array('item' => $item), true);
	}

	public function clear ($context = null, $type = null)
	{
		parent::remove(self::_make_query($context, $type));
	}

}

?>