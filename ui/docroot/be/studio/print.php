<?php

/*
 * \brief front file for printing
 *
 * \file print.php
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: print.php 4963 2011-05-17 08:51:09Z predragm $
 *
 */

require '../../../etc/config.php';

require 'autoload.php';
require 'ccmd.php';
require 'AccessPolicy.php';
require 'util/XMLData.php';
require 'Prefs.php';
require 'rtn/WSS.php';

// Files required for Printing
require 'export/Report_Adapter.php';
require 'export/Report.php';
require 'print/WBExportPDF.php';
require 'print/RepExportPDF.php';

// fetch accessPolicy/prefs objs and wssu sessid from studio sess
session_name('STUDIO_SESSID');
session_start();

$apol = $_SESSION['accessPolicy'];
$prefs = $_SESSION['prefs'];
$wssu_sessid = $_SESSION['WSSU_SESSID'];

session_write_close();

// fetch list of used vars from wssu sess
$res = json_decode(ccmd('[["gvls"]]', -1, $wssu_sessid), true);

if ($res[0][0] !== true || !is_array($res[0][1]))
	die ('ERROR: Backend is unavailable!');

// fetch vals of all used vars if any
if (!empty($res[0][1]))
{
	$vars = array();
	$ccmd = '';

	foreach ($res[0][1] as $var)
	{
		$vars[] = $var;
		$ccmd .= ',["gvar","' . $var . '"]';
	}

	$ccmd[0] = '[';
	$ccmd .= ']';

	$vals = json_decode(ccmd($ccmd, -1, $wssu_sessid), true);
}

// login to core & create print sess
$ccmd = '[["logi",' . json_encode($apol->getUser()) . ',' . json_encode($apol->getPass()) . ',' . json_encode($apol->getGroups()) . '],["susl","' . $prefs->search('general/l10n') . '"],["oadd",0,"A' . mt_rand() . '"]]';

$res = json_decode(ccmd($ccmd, -1, null), true);

if ($res[0][0] !== true || $res[1][0] !== true || $res[2][0] !== true)
	die ('ERROR: Backend is unavailable!');

session_id($res[0][1]);
session_name('PRINT_SESSID');
session_start();

$_SESSION['accessPolicy'] = $apol;
$_SESSION['prefs'] = $prefs;
$_SESSION['wss'] = $sessWSS = new SessWSS();

ccmd('[["osel",0,"' . ($sessWSS->curr_appid = $res[2][1]) . '"]]');

// set vars from wssu sess if any
if (isset($vars))
{
	$ccmd = '';

	foreach ($vals as $idx => $val)
		if ($val[0] === true)
			$ccmd .= ',["svar","' . $vars[$idx] . '",' . json_encode($val[1]) . ']';

	$ccmd[0] = '[';
	$ccmd .= ']';

	ccmd($ccmd, -1, session_id());
}

// now generate pdf
switch ($_GET['t'])
{
	case 'report':
		$params = json_decode(gzuncompress(base64_decode($_GET['params'])), true);

		$rep = new RepExportPDF();
		$rep->setGroup($params['gr']);
		$rep->setHierarchy($params['hr']);
		$rep->setWbList($params['wbs']);
		$rep->setVsList($params['vss']);
		$rep->setWbVSOrder($params['wbvs']);
		$rep->setWbPageSetup($params['ps']);

		$rep->gen_pdf();
	break;

	case 'workbook':
		$params = json_decode(gzuncompress(base64_decode($_GET['params'])), true);

		// Single WB and Single VS
		$wbIndex = 0;
		$vsIndex = 0;

		$wbParams = $params['wb'][$wbIndex];
		$vsParams = $params['vs'][$vsIndex];

		$wb_exp = new WBExportPDF();
		if ($wb_exp->loadWbWithVs($wbParams['name'], $wbParams['group'], $wbParams['hier'], $vsParams, array($wbIndex, $vsIndex)))
			$wb_exp->gen_pdf();
		else
			die('Error: Unable to load Workbook!');
	break;
}

// logout from core & destroy print sess
ccmd('[["logo"]]');

session_destroy();
setcookie('PRINT_SESSID', '', time() - 604800, '/');

?>