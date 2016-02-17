<?php

/*
 * \brief WSS index page
 *
 * \file index.php
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: index.php 4942 2011-05-11 14:05:30Z drazenk $
 *
 */

header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T'));
header('Expires: Fri, 03 Sep 1999 01:00:00 GMT');
header('Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
header('Pragma: no-cache');

require '../../../etc/config.php';

require 'autoload.php';
require 'ccmd.php';

$params = array();

if (isset($_GET['_'])) {
	$enc_params = json_decode(gzuncompress(base64_decode($_GET['_'])), true);

	if (is_array($enc_params) && count($enc_params))
		$params = $enc_params;

	unset($_GET['_']);
}

foreach ($_GET as $key => $val)
	$params[$key] = $val;

$has_wam = isset($params['wam']);
$redirect_to = $has_wam && $params['wam'] == 'user' ? 'view' : 'main';

session_name('WSS' . ($redirect_to == 'view' ? 'U' : 'D') . '_SESSID');
session_start();

if (!isset($_SESSION['accessPolicy'])) {
	session_destroy();
	setcookie('app', '/ui/wss/' . ($_SERVER['QUERY_STRING'] ? 'index' : 'main') . '.php', 0, '/ui/login/');
	header('Location: /ui/login/' . ($_SERVER['QUERY_STRING'] ? '?' . $_SERVER['QUERY_STRING'] : ''));
	die();
}

if (array_key_exists('grp', $params) && array_key_exists('hrc', $params) && array_key_exists('wb', $params)) {
	$_SESSION['prefs']->set('node', $params['grp'] . '-' . $params['hrc'] . '-' . $params['wb'], 0);

	$vars = array('nodes' => array(), 'vars' => array());
	$var_params = array('n_', 'v_');
	$opars = array();

	foreach ($params as $name => $val) {
		$param_begin = substr($name, 0, 2);

		if (in_array($param_begin, $var_params)) {
			if (is_numeric($val))
				$val = floatval($val);
			else if (!strcasecmp($val, 'true'))
				$val = true;
			else if (!strcasecmp($val, 'false'))
				$val = false;

			$vars[$param_begin == 'n_' ? 'nodes' : 'vars'][substr($name, 2)] = $val;
		}

		if (substr($name, 0, 4) == 'var/')
			$opars[substr($name, 4)] = $val;
	}

	$prld_params = $params;
	$prld_params['appmode'] = $has_wam && strtoupper($prld_params['wam'][0]) == 'U' ? 'user' : 'designer';

	if (count($opars))
		$prld_params['opar'] = json_encode($opars);

	if (($is_vempty = isset($prld_params['vempty'])) || count($vars['nodes']) > 0 || count($vars['vars']) > 0)
		$prld_params['vars'] = $vars;

	try {
		$wssajax = new WSS($prld_params);
	} catch(Exception $e) {}
}

$params_str = '';
foreach ($params as $key => $val)
	$params_str .= '&' . $key . '=' . $val;

header('Location: /ui/wss/' . $redirect_to . '.php' . (strlen($params_str) ? '?' . substr($params_str, 1) : ''));
die();

?>