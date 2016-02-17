<?php

/*
 * \brief RPC routines for handling WSS workbooks
 *
 * \file wss_book.php
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
 * SVN: $Id: wss_book.php 4907 2011-04-29 10:58:01Z drazenk $
 *
 */

class wss_book
{

// private vars
	public static function getUsedVars ($group, $hierarchy, $node)
	{
		$list = array();

		// list of used vars
		$res = ccmd(array(array('gbvl')));
		$res = $res[0];

		$usedvars = $res[0] === true && is_array($res[1]) ? $res[1] : array();
		$privvars = array();

		// map of priv vars
		if (!empty($group) && !empty($hierarchy) && !empty($node))
		{
			$apol = $_SESSION['accessPolicy'];

			$vars = W3S_NodeData::getVariables($apol->getConn(), $group, $hierarchy, $node, array());

			foreach ($vars as $name => $props)
				if ($props['private'])
					$privvars[$name] = 0;
		}

		// values of used vars
		$ccmd = array();

		foreach ($usedvars as $var)
			$ccmd[] = array('gvar', $var);

		$res = ccmd($ccmd);

		// fill list
		foreach ($res as $idx => &$val)
		{
			$var = $usedvars[$idx];

			if (isset($privvars[$var]))
			{
				$priv = true;
				unset($privvars[$var]);
			}
			else
				$priv = false;

			if ($val[0] !== true)
				$val = '';
			elseif (is_string($val = $val[1]))
				$val = json_encode($val);
			elseif (is_bool($val))
				$val = $val ? 'TRUE' : 'FALSE';

			$list[] = array($var, $val, $priv);
		}

		// add remaining priv
		foreach ($privvars as $var => $idx)
			$list[] = array($var, '', true);

		return $list;
	}

	public static function setPrivVars ($group, $hierarchy, $node, array $varlist)
	{
		if (empty($group) || empty($hierarchy) || empty($node))
			return false;

		$varlist = array_flip($varlist);

		$apol = $_SESSION['accessPolicy'];

		$vars = W3S_NodeData::getVariables($apol->getConn(), $group, $hierarchy, $node, array());

		foreach ($vars as $name => &$props)
			if (isset($varlist[$name]))
			{
				$props['private'] = true;
				unset($varlist[$name]);
			}
			else if (isset($props['private']))
				unset($props['private']);

		foreach ($varlist as $var => $idx)
			$vars[$var] = array('private' => true);

		return W3S_NodeData::setVariables($apol->getConn(), $group, $hierarchy, $node, $vars);
	}

}

?>