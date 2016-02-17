<?php

/*
 * \brief backend external RPC proxy
 *
 * \file erpc.php
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
 * SVN: $Id: erpc.php 4580 2011-02-08 15:11:21Z predragm $
 *
 */

define ('ERR_HNDLR_MASK', E_USER_ERROR | E_RECOVERABLE_ERROR);

function err_hndlr ($no, $str, $file, $line)
{
	if ($no & ERR_HNDLR_MASK)
		die ('[]');

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

	$class = $_GET['c'];

	if (!isset($class))
		die('[]');

	$method = $_GET['m'];

	if (!isset($method))
		die('[]');

	if (!preg_match('/\w/i', $class))
		die('[]');

	if (!class_exists($class, false))
		require 'rtn/' . $class . '.php';

	if (ctype_upper($class[0]))
		$class = new $class();

	if (!method_exists($class, $method))
		die('[]');

	print json_encode(call_user_func(array($class, $method)));
}
catch (Exception $e)
{
	die ('[]');
}

?>