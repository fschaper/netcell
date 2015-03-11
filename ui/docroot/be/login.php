<?php

/*
 * \brief backend login script
 *
 * \file login.php
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
 * SVN: $Id: login.php 4580 2011-02-08 15:11:21Z predragm $
 *
 */

define ('ERR_HNDLR_MASK', E_USER_ERROR | E_RECOVERABLE_ERROR);

function err_hndlr ($no, $str, $file, $line)
{
	if ($no & ERR_HNDLR_MASK)
		die ('SYSTEM ERROR: ' . $str);

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

	require '../../base/ccmd.php';
	require '../../base/AccessPolicy.php';
	require '../../base/util/XMLData.php';
	require '../../base/Prefs.php';
	require '../../base/rtn/login.php';

	$res = login::in($_POST['user'], $_POST['pass']);

	print $res[0] ? 'OK' : $res[1];
}
catch (Exception $e)
{
	die ('SYSTEM ERROR: ' . $e->getMessage());
}

?>