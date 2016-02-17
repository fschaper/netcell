<?php

/*
 * \brief front file for exporting from Studio
 *
 * \file export.php
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: export.php 4939 2011-05-11 12:42:25Z predragm $
 *
 */

require '../../../etc/config.php';

require 'autoload.php';
require 'ccmd.php';
require 'rtn/Studio.php';

$file_type_def = 'application/octet-stream';

$file_types = array(
  'pdf' => 'application/pdf'
, 'gif' => 'image/gif'
, 'png' => 'image/png'
, 'jpg' => 'image/jpg'
, 'jpeg' => 'image/jpg'
, 'txt' => 'text/plain'
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

try
{
	if (!isset($_GET['t']) || !isset($_GET['g']) || !isset($_GET['h']) || !isset($_GET['n']))
		throw new Exception($res = '"nodeExp_no_params"');

	$type = $_GET['t'];
	$guid = $_GET['g'];
	$huid = $_GET['h'];
	$nuid = $_GET['n'];

	$studio = new Studio();

	$node = $studio->getNodeInThisScope($type, $guid, $huid, $nuid);

	if (!($node instanceof W3S_Node))
		throw new Exception($res = '"nodeExp_no_node", { id: "' . $nuid . '" }');

	$file_name = $node->getData()->getName();
	$file_path = $node->getSysPath();

	switch ($node->getType())
	{
		case 'workbook':
			$file_ext = 'wss';
			break;

		case 'static':
			$file_ext = $node->getData()->getEffectiveType();
			break;

		default:
			$file_ext = 'unknown';
	}

	if ($file_ext != 'unknown')
	{
		$file_name .= '.' . $file_ext;
		$file_path .= '.' . $file_ext;
	}

	if (!is_readable($file_path) || !is_file($file_path))
		throw new Exception($res = '"nodeExp_no_file"');

	header('Content-Type: ' . (isset($file_types[$file_ext]) ? $file_types[$file_ext] : $file_type_def));
	header('Content-Length: ' . filesize($file_path));
	header('Content-Disposition: attachment; filename=' . urlencode($file_name));
	header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T'));
	header('Expires: Fri, 03 Sep 1999 01:00:00 GMT');
	header('Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
	header('Pragma: no-cache');

	ob_clean();
	flush();
	readfile($file_path);

	die();
}
catch (Exception $e)
{
	if (!isset($res))
		$res = '"nodeExp_proc_error"';
}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<script type="text/javascript">

function showErr ()
{
	parent.Jedox.studio.files.exportError(<?php print $res; ?>);
}

</script>
</head>
<body onload="showErr();"></body>
</html>