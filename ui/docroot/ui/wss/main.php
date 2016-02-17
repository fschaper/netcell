<?php

/*
 * \brief wss app designer mode front file
 *
 * \file main.php
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: main.php 5117 2011-07-15 12:37:01Z drazenk $
 *
 */

header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T'));
header('Expires: Fri, 03 Sep 1999 01:00:00 GMT');
header('Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
header('Pragma: no-cache');

require '../../../etc/config.php';

require '../../../base/util/XMLData.php';
require '../../../base/Prefs.php';

define ('APP_MODE', 'DESIGNER');
define ('WAM', 'DESIGNER');

session_name('WSSD_SESSID');
session_start();

if (!isset($_SESSION['accessPolicy']))
{
	session_destroy();
	setcookie('app', '/ui/wss/main.php', 0, '/ui/login/');
	header('Location: /ui/login/' . ($_SERVER['QUERY_STRING'] ? '?' . $_SERVER['QUERY_STRING'] : ''));
	die();
}

$prefs = $_SESSION['prefs'];

if (isset($_GET['_']))
{
	$params = json_decode(gzuncompress(base64_decode($_GET['_'])), true);

	if (is_array($params))
		$prefs->set('', $params, 0);

	unset($_GET['_']);
}

foreach ($_GET as $key => $val)
	$prefs->set($key, $val, 0);

$prefs_l10n = $prefs->search('general/l10n');
$prefs_iface = $prefs->search('wss/interface');
$hide_toolbar = $prefs->search('wss/designer/toolbar') == 'no';
$hide_formulabar = $prefs->search('wss/designer/formulabar') == 'no';
$hide_statusbar = $prefs->search('wss/designer/status') == 'no';

$ui_ver = is_readable($ui_ver = '../../../version') ? current(split("\t", trim(file_get_contents($ui_ver)))) : 'dev';

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
	<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE8" />
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>Palo Web</title>
<?php if ($ui_ver != 'dev') { ?>
 	<link rel="stylesheet" type="text/css" media="screen" href="/ui/ld/?wss/dznr/main,wss/dznr/<?php print $prefs_iface; ?>.<?php print $ui_ver; ?>.css" />
<?php } else { require('../ld/dev.php'); ld('wss/dznr/main,wss/dznr/' . $prefs_iface . '.css'); } ?>
 	<link rel="stylesheet" type="text/css" media="screen" id="theme" href="/ui/lib/ext/resources/css/xtheme-<?php print $prefs->search('general/theme'); ?>.css" />
</head>

<body id="mainBody" style="overflow: hidden;" onunload="document.getElementById('mainBody').style.display = 'none';" onload="Jedox.wss.general.startUp();" onContextMenu="if (!Jedox.wss.app.showBrowserCtx) return false;" scroll="no">

	<!-- menubar, toolbars and formulabar container -->
	<div id="barsContainer">

		<?php switch ($prefs_iface) { case 'toolbar': ?>

		<!-- menubar -->
		<div id="MenuPlaceholder" style="height: 25px;"></div>

		<!-- toolbars -->
		<div id="Toolbar" class="wsstoolbar" style="height: 26px; overflow: hidden;<?php if ($hide_toolbar) print ' display: none;'; ?>">
			<!-- standard toolbar -->
			<div id="wssStandardBar" class="bar" style="position: absolute;">
				<div id="wssStandardToolbar" class="bar-end"></div>
			</div>
			<!-- format toolbar -->
			<div id="wssFormatBar" class="bar" style="position: absolute; left: 168px;"><!-- with undo/redo left=200px -->
				<div id="wssFormatToolbar" class="bar-end"></div>
			</div>
			<!-- dynarange toolbar -->
			<div id="wssDynarangeBar" class="bar" style="position: absolute; left: 712px;"><!-- with undo/redo left=740px -->
				<div id="wssDynarangeToolbar" class="bar-end"></div>
			</div>
		</div>

		<?php break; case 'ribbon': ?>

		<!--ribbon -->
		<div id="ribbon" style="height: 118px;"></div>

		<?php } ?>

		<!-- formulabar -->
		<div id="formulaBar"<?php if ($hide_formulabar) print ' style="display: none;"'; ?>>
			<table class="formula-bar-table">
				<tbody>
					<tr>
						<td valign="top"> <div id="currCoord"></div></td>
						<td valign="top"> <div id="formulaTlb"></div></td>
						<td style="width: 100%; height: 22px; padding-right: 1px;"><div id="formulaInfo"></div></td>
						<td valign="top"><div id="expandBtn"></div></td>
					</tr>
				</tbody>
			</table>
		</div>

	</div>
	<!-- end of bars container -->

	<!-- workspace -->
	<div id="workspace" class="workspace"></div>

	<!-- statusbar -->
	<div id="statusBarContainer" style="width: 100%;<?php if ($hide_statusbar) print ' display: none;'; ?>"></div>

	<div id="CursorMarker"></div>
	<div id="marker" onmouseup="stopTracking();"></div>

	<div id="hideRows" style="background-color: white; z-index: 100; position: absolute; display: none;"></div>
	<div id="hideCols" style="background-color: white; z-index: 100; position: absolute; display: none;"></div>

<?php if ($ui_ver != 'dev') { ?>
	<script type="text/javascript" src="/ui/ld/?wss/dznr/main,wss/dznr/<?php print $prefs_iface; ?>,wss/<?php print $prefs_l10n . '.' . $ui_ver; ?>.js"></script>
<?php } else ld('wss/dznr/main,wss/dznr/' . $prefs_iface . ',wss/' . $prefs_l10n . ',wss/qa.js'); ?>
	<script type="text/javascript">

		Ext.BLANK_IMAGE_URL = '/ui/lib/ext/resources/images/default/s.gif';

		Jedox.wss.app.params = <?php print json_encode($prefs->dump(0)); ?>;

		Jedox.wss.app.defaultFiles = <?php print ($studio_def_files = $prefs->search('studio/default/files')) ? json_encode($studio_def_files) : '\'\'' ?>;

		Jedox.wss.app.appModeS = Jedox.wss.app.appMode = Jedox.wss.grid.viewMode.<?php print APP_MODE; ?>;
		Jedox.wss.app.toolbarLayout = '<?php print $prefs_iface; ?>';
		Jedox.wss.app.fopper = <?php print(strlen(CFG_FOPPER_PATH) ? 'true' : 'false'); ?>;

<?php
if ($hide_toolbar)
	print '		Jedox.wss.app.initHideToolbar = true;' . "\n";

if ($hide_formulabar)
	print '		Jedox.wss.app.initHideFormulaBar = true;' . "\n";

if ($hide_statusbar)
	print '		Jedox.wss.app.initHideStatusBar = true;' . "\n";
?>

		Jedox.backend.SyncRqst.prototype._baseHdrs = Jedox.backend.AsyncRqst.prototype._baseHdrs = { 'X-Sess-Select': Jedox.wss.app.appModeS, 'X-WSS-Book': Jedox.wss.book.autoSwitch };

		if (window == window.parent)
			window.onbeforeunload = function () { return ''; };

	</script>

</body>

</html>