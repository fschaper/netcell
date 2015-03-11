<?php

/*
 * \brief backend RPC proxy
 *
 * \file rpc.php
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
 * SVN: $Id: rpc.php 5101 2011-07-08 13:46:57Z predragm $
 *
 */

if (CFG_PERF_MODE)
	$_dur_php = microtime(true);

define ('ERR_HNDLR_MASK', E_USER_ERROR | E_RECOVERABLE_ERROR);
define ('ERR_CODE_EXC', 'R1');
define ('ERR_CODE_ERR', 'R2');
define ('FLAG_CONT_ON_EXC', 1);

function err_hndlr ($no, $str, $file, $line)
{
	global $res;

	if ($no & ERR_HNDLR_MASK)
	{
		$res[] = array(false, ERR_CODE_ERR, $str, array('FILE' => $file, 'LINE' => $line));
		die (json_encode($res));
	}

	return false;
}

set_error_handler('err_hndlr');

header('Content-Type: application/json; charset=utf-8; charset=UTF-8');
header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T'));
header('Expires: Fri, 03 Sep 1999 01:00:00 GMT');
header('Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
header('Pragma: no-cache');

try
{
	require '../../etc/config.php';

	require 'autoload.php';
	require 'ccmd.php';
	require 'sess_start.php';

	$flags = intval($_SERVER['QUERY_STRING']);

	if (!is_array($data = json_decode(file_get_contents('php://input', FILE_BINARY), true)))
		throw new Exception('invalid data');

	$res = array();

	foreach ($data as &$rpc)
	{
		try
		{
			unset($class, $method);

			list ($class, $method) = $rpc;

			if (!isset($class))
				throw new Exception('missing class name');

			if (!isset($method))
				throw new Exception('missing method name');

			if (!preg_match('/\w/i', $class))
				throw new Exception('invalid class name');

			if (!class_exists($class, false))
				require 'rtn/' . $class . '.php';

			if (ctype_upper($class[0]))
				$class = new $class();

			if (!method_exists($class, $method))
				throw new Exception('unknown method');

			$cb = array($class, $method);

			$res[] = array(true, is_array($rpc[2]) ? call_user_func_array($cb, $rpc[2]) : call_user_func($cb));
		}
		catch (Exception $e)
		{
			$res[] = $e instanceof WSS_Exception ? $e->getCombined() : array(false, ERR_CODE_EXC, $e->getMessage());

			if (!($flags & FLAG_CONT_ON_EXC))
				break;
		}
	}

	print json_encode($res);
}
catch (Exception $e)
{
	die ('[' . json_encode($e instanceof WSS_Exception ? $e->getCombined() : array(false, ERR_CODE_EXC, $e->getMessage())) . ']');
}

if (CFG_PERF_MODE)
	$_SESSION['_dur_php'] += round((microtime(true) - $_dur_php) * 1000);

?>