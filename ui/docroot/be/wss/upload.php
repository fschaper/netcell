<?php

/*
 * \brief used for importing XLSX
 *
 * \file upload.php
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
 * SVN: $Id: upload.php 3866 2010-09-24 14:31:17Z predragm $
 *
 */

require '../../../etc/config.php';

require 'autoload.php';
require 'ccmd.php';
require 'sess_start.php';

$uplfile_path = $_FILES['workbook_file']['tmp_name'];
$origfile_name = basename($_FILES['workbook_file']['name']);
$mvfile_path = str_replace('\\', '/', dirname($uplfile_path)) . '/' . $origfile_name;

move_uploaded_file($uplfile_path, $mvfile_path);

$cmds = '[["limp","xlsx","' . $mvfile_path . '"]]';

header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T'));
header('Expires: Fri, 03 Sep 1999 01:00:00 GMT');
header('Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
header('Pragma: no-cache');

try
{
	$res = ccmd($cmds);
}
catch (Exception $e)
{
	$res = '[[false,0,' . json_encode($e->getMessage()) . ']]';
}

unlink($mvfile_path);

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<script type="text/javascript">

function init ()
{
	parent.Jedox.wss.dlg.processImport(<?php print $res . ', ' . json_encode($origfile_name); ?>);
}

</script>
</head>
<body onLoad="init();"></body>
</html>