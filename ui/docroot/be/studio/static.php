<?php

/*
 * \brief front file for downloading files from Studio
 *
 * \file static.php
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: static.php 5129 2011-07-19 09:24:21Z srdjanv $
 *
 */

require '../../../etc/config.php';

require 'autoload.php';
require 'ccmd.php';
require 'rtn/Studio.php';

$file_type_def = 'application/octet-stream';

$file_types = array(
  'pdf' => array('mime' => 'application/pdf', 'inline' => true)
, 'gif' => array('mime' => 'image/gif', 'inline' => true)
, 'png' => array('mime' => 'image/png', 'inline' => true)
, 'jpg' => array('mime' => 'image/jpeg', 'inline' => true)
, 'jpeg' => array('mime' => 'image/jpeg', 'inline' => true, 'subtype' => 'jpg')
, 'txt' => array('mime' => 'text/plain', 'inline' => true)
, 'htm' => array('mime' => 'text/html', 'inline' => true)
, 'html' => array('mime' => 'text/html', 'inline' => true)
, 'csv' => 'text/csv'
, 'zip' => 'application/zip'
, 'rar' => 'application/x-rar-compressed'
, 'doc' => 'application/msword'
, 'docx' => 'application/vnd.openxmlformats-officedocument.wordprocessingml.document'
, 'xls' => 'application/vnd.ms-excel'
, 'xlsx' => 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet'
, 'ppt' => 'application/vnd.ms-powerpoint'
, 'pps' => 'application/vnd.ms-powerpoint'
, 'pptx' => 'application/vnd.openxmlformats-officedocument.presentationml.presentation'
, 'ppsx' => 'application/vnd.openxmlformats-officedocument.presentationml.slideshow'
);

session_name('STUDIO_SESSID');
session_start();


if (!isset($_SESSION['accessPolicy']))
{
	session_destroy();
	setcookie('app', '/be/studio/static.php', 0, '/ui/login/');
	header('Location: /ui/login/' . ($_SERVER['QUERY_STRING'] ? '?' . $_SERVER['QUERY_STRING'] : ''));
	die();
}

if (!isset($_GET['t']) || !isset($_GET['g']) || !isset($_GET['h']) || !isset($_GET['n']))
	die('ERROR: mandatory parameter missing.');

$type = $_GET['t'];
$guid = $_GET['g'];
$huid = $_GET['h'];
$nuid = $_GET['n'];
$path = $_GET['p'];
$skip_recent = isset($_GET['sr'])? ($_GET['sr'] == 'yes'):false;

try
{
	$studio = new Studio();

	if ($type == 'report' && substr($guid, 0, 1) == 'r')
	{
		$ref = $studio->getReferenceNode($guid, $huid, $nuid);
		$node = $studio->getNodeInThisScope('file', $ref['g'], $ref['h'], $ref['n']);
	}
	else
		$node = $studio->getNodeInThisScope('file', $guid, $huid, $nuid);

	if (!($node instanceof W3S_Node))
		throw new Exception('node not found');

	$file_name = $node->getData()->getName();
	$file_ext = $node->getData()->getEffectiveType();
	$file_path = $node->getSysPath();

	if ($file_ext != 'unknown')
	{
		$file_name .= '.' . $file_ext;
		$file_path .= '.' . $file_ext;
	}

	if (!is_readable($file_path) || !is_file($file_path))
		throw new Exception('file not found');

	$file_type = isset($file_types[$file_ext]) ? $file_types[$file_ext] : $file_type_def;

	if (is_array($file_type) && $file_type['inline'])
	{
		$disp_type = 'inline';

		if(!$skip_recent)
			$studio->addRecent($type, 'static', array('group' => $guid, 'hierarchy' => $huid, 'node' => $nuid, 'path' => str_replace("\\", "/", $path)), $file_type['subtype'] ? $file_type['subtype'] : $file_ext);
	}
	else
		$disp_type = 'attachment';
}
catch (Exception $e)
{
	die('ERROR: ' . $e->getMessage() . '.');
}

header('Content-Type: ' . (is_array($file_type) ? $file_type['mime'] : $file_type));
header('Content-Length: ' . filesize($file_path));
header('Content-Disposition: ' . $disp_type . '; filename=' . urlencode($file_name));
header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T'));
header('Expires: Fri, 03 Sep 1999 01:00:00 GMT');
header('Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
header('Pragma: no-cache');

ob_clean();
flush();
readfile($file_path);

?>