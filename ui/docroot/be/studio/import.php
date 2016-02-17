<?php

/*
 * \brief form action file for Studio import dialog
 *
 * \file import.php
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
 *
 * \version
 * SVN: $Id: import.php 5130 2011-07-19 10:03:10Z srdjanv $
 *
 */

require '../../../etc/config.php';

require 'autoload.php';
require 'ccmd.php';
require 'rtn/Studio.php';

session_name('STUDIO_SESSID');
session_start();

try
{
	if (!isset($_FILES['import_file']) || !isset($_POST['importParentNode']))
		throw new Exception($res = 'false, { loc: "errFileImport", params: { name: "" } }');

	$uplfile_path = $_FILES['import_file']['tmp_name'];
	$origfile_name = $name = $_FILES['import_file']['name'];

	$convert = $_GET['convert'];

	if (strtolower(substr($origfile_name, -4)) == '.wss' || $convert)
	{
		$name = substr($origfile_name, 0, $convert? -5:-4);
		$uplfile_type = 'workbook';
	}
	else
		$uplfile_type = 'static';

	$studio = new Studio();

	$node_meta = array('name' => $name, 'desc' => $name, 'uplpath' => $uplfile_path);

	if ($uplfile_type == 'workbook')
	{
		$apol = $_SESSION['accessPolicy'];

		$res = json_decode(ccmd('[["logi",' . json_encode($apol->getUser()) . ',""],["oadd",0,"' . ('A' . mt_rand()) . '"]]', -1, null), true);
		$sess_id = $res[0][1];
		$app_uid = $res[1][1];

		//import *.xlsx
		if($convert){
			$osel_r = json_decode(ccmd('[["osel",0,"' . $app_uid . '"]]', -1, $sess_id), true);
			$limp_r = json_decode(ccmd('[["limp","xlsx",' . json_encode($uplfile_path) . ']]', -1, $sess_id), true);

			if(is_array($limp_r) && is_array($limp_r[0]) && $limp_r[0][0])
				$log = implode("\n", str_replace(basename($uplfile_path), $origfile_name, $limp_r[0][1]));
		}
		//---------------------------

		$res = json_decode(ccmd('[["osel",0,"' . $app_uid . '"],["gbvl",' . json_encode($uplfile_path) . '],["odel",0,"' . $app_uid . '"],["logo"]]', -1, $sess_id), true);
		$var_list = $res[1][1];

		if (is_array($var_list) && !empty($var_list))
			$node_meta['vars'] = $var_list;
	}

	$nuid = $studio->treeMngNode('file', $_POST['importParentNode'], 'importNode', true, $uplfile_type, $node_meta);

	$result = json_encode(array(true, array('log'=>$log, 'nodeId'=>$nuid, 'name'=>$name)));

}
catch (Exception $e)
{
	if (!isset($result))
		$result = 'false, { loc: "errFileImport", params: { name: "' . $name . '" } }';
}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<script type="text/javascript">

function init ()
{
	parent.Jedox.studio.files.processImport(<?php print $result; ?>);
}

</script>
</head>
<body onload="init();"></body>
</html>