<?php

/*
 * \brief class for working with tagged items
 *
 * \file Tagged.php
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
 * SVN: $Id: Tagged.php 3276 2010-05-28 08:40:23Z predragm $
 *
 */

class Tagged extends XMLData
{
	const ATTR_NAME	= 'tagged';

	private static function _make_query ($context = null, $type = null, $location = null, $tag = null)
	{
		$query = array();

		if ($context)
			$query[] = 'context = "' . $context . '"';

		if ($type)
			$query[] = 'type = "' . $type . '"';

		if ($location)
		{
			if (is_array($location))
				foreach ($location as $key => &$val)
					$query[] = 'location/' . $key . ' = "' . $val . '"';
			else
				$query[] = 'location = "' . $location . '"';
		}

		if ($tag)
			$query[] = 'tag = "' . $tag . '"';

		return empty($query) ? 'item' : 'item[' . implode(' and ', $query) . ']';
	}

	public function __construct (AccessPolicy $apol)
	{
		parent::__construct($_SERVER['DOCUMENT_ROOT'] . '/../etc/schema/tagged.rng');

		if ($this->loadPalo($apol, 'System', '#_USER_USER_PROPERTIES', array($apol->getUser(), self::ATTR_NAME)))
			return;

		$this->set(null, array(self::ATTR_NAME => array()));

		if (!is_int(@palo_eindex($conn = $apol->getSuperConn(), 'System', '#_USER_PROPERTIES_', self::ATTR_NAME, true)))
		{
			@palo_eadd($conn, 'System', '#_USER_PROPERTIES_', 'S', self::ATTR_NAME, '', 1, false, true);
			@palo_ping($conn);
		}
	}

	public function fetch ($context = null, $type = null, $tag = null)
	{
		$res = $this->get(self::_make_query($context, $type, null, $tag));

		if (!isset($res['item']))
			return array();

		$res = $res['item'];

		return isset($res['context']) ? array($res) : $res;
	}

	public function add ($context, $type, $location, $tag, $subtype = null)
	{
		// remove duplicates if any
		parent::remove(self::_make_query($context, null, $location, $tag));

		// add item
		$item = array('context' => $context, 'type' => $type);

		if ($subtype)
			$item['subtype'] = $subtype;

		$item['location'] = $location;
		$item['tag'] = $tag;

		return $this->set('.', array('item' => $item), true);
	}

	public function clear ($context = null, $type = null, $tag = null)
	{
		parent::remove(self::_make_query($context, $type, null, $tag));
	}

	public function remove (array $items)
	{
		foreach ($items as &$elem)
			parent::remove(self::_make_query($elem['context'], null, $elem['location'], $elem['tag']));
	}

	public function distinct ($context = null, $type = null)
	{
		$query = array();

		if ($context)
			$query[] = 'context = "' . $context . '"';

		if ($type)
			$query[] = 'type = "' . $type . '"';

		$query[] = 'not (tag = preceding-sibling::item/tag)';

		$query = 'item[' . implode(' and ', $query) . ']/tag';

		$res = $this->get($query);

		if (!isset($res['tag']))
			return array();

		return is_array($res['tag']) ? $res['tag'] : array($res['tag']);
	}

}

?>