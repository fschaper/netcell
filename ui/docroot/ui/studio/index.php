<?php

/*
 * \brief studio app front file
 *
 * \file index.php
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: index.php 5152 2011-07-28 10:02:33Z predragm $
 *
 */

header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T'));
header('Expires: Fri, 03 Sep 1999 01:00:00 GMT');
header('Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
header('Pragma: no-cache');

require '../../../etc/config.php';

require '../../../base/AccessPolicy.php';
require '../../../base/util/XMLData.php';
require '../../../base/Prefs.php';

session_name('STUDIO_SESSID');
session_start();

if (!isset($_SESSION['accessPolicy']))
{
	session_destroy();
	setcookie('app', '/ui/studio/', 0, '/ui/login/');
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

$ui_ver = is_readable($ui_ver = '../../../version') ? current(split("\t", trim(file_get_contents($ui_ver)))) : 'dev';

$apol = $_SESSION['accessPolicy'];
$ld_conf = '';

foreach (array('files', 'users', 'etl', 'conns') as $module)
	if ($apol->getRule('ste_' . $module) != AccessPolicy::PERM_NONE)
		$ld_conf .= ',' . 'studio/' . $module;

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head id="head">
	<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE8" />
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta name="gwt:module" content="app" />
	<meta name="gwt:property" content="locale=<?php print $prefs_l10n; ?>" />
	<title>Palo Web</title>
<?php if ($ui_ver != 'dev') { ?>
	<link rel="stylesheet" type="text/css" href="/ui/ld/?studio/main.<?php print $ui_ver; ?>.css" media="screen" />
<?php } else { require('../ld/dev.php'); ld('studio/main.css'); } ?>
	<link rel="stylesheet" type="text/css" media="screen" id="theme" href="/ui/lib/ext/resources/css/xtheme-<?php print $prefs->search('general/theme'); ?>.css" />
</head>

<body onContextMenu="return false;">

	<div id="testWidth" style="position: absolute; visibility: hidden; white-space: nowrap;">Width</div>

	<div id="activityIndctr" style="position: relative; float: right; left: -15px; top: 13px; width: 100px; height: 10px; background-image: url(/ui/studio/res/img/loading.gif); z-index: 100000; visibility: hidden;"></div>

	<script type="text/javascript">

		function getCookie (name)
		{
			var re = new RegExp('(^|; ?)'.concat(name, '=([^;]+)')),
					match = document.cookie.match(re);

			return match instanceof Array ? unescape(match[2]) : '';
		}

		window.name = 'wetl-main';

		// ETL setup properties
		var etl_web_mode_options = {
		  mode: 'integrated'
		, app_path: '/tc/web-etl/app/'
		};

	</script>
<?php if ($ui_ver != 'dev') { ?>
	<script type="text/javascript" src="/ui/ld/?studio/main<?php print $ld_conf . ',studio/' . $prefs_l10n . '.' . $ui_ver; ?>.js"></script>
<?php } else ld('studio/main' . $ld_conf . ',studio/' . $prefs_l10n . ',studio/qa.js'); ?>
	<script type="text/javascript">

		Ext.BLANK_IMAGE_URL = '/ui/lib/ext/resources/images/default/s.gif';

<?php
if (is_array($license = @palo_license_info($apol->getSuperConn())) && $license['name'])
	print '		Jedox.studio.app.license = ' . json_encode($license) . ";\n";
?>

		Jedox.studio.app.params = <?php print json_encode($prefs->dump(0)); ?>;

		Jedox.studio.access.rules = <?php print json_encode($apol->getRules()); ?>;
		Jedox.studio.access.perm_g = <?php print $apol->getRule('database'); ?>;

		Jedox.studio.app.defaultFiles = <?php print ($studio_def_files = $prefs->search('studio/default/files')) ? json_encode($studio_def_files) : '\'\'' ?>;
		Jedox.studio.app.defaultView = '<?php print $prefs->search('studio/default/view'); ?>';
<?php
if ($panelVisibility = $prefs->search('studio/panel/visibility'))
	print '		Jedox.studio.app.panelVisibility = \'' . $panelVisibility . "';\n";

if ($usersLayout = $prefs->search('studio/users/layout'))
	print '		Jedox.studio.app.usersLayout = \'' . $usersLayout . "';\n";

if ($mypalo = $prefs->search('mypalo'))
	print '		Jedox.studio.app.myPalo = ' . json_encode($mypalo) . ";\n";
?>

		Jedox.backend.SyncRqst.prototype._baseHdrs = Jedox.backend.AsyncRqst.prototype._baseHdrs = { 'X-Sess-Select': 'studio' };

		Jedox.backend.ping_cmd = '[["ping","<?php print $_SESSION['WSSU_SESSID'] . '","' . $_SESSION['WSSD_SESSID']; ?>"]]';
		setTimeout(Jedox.backend.ping, Jedox.backend.ping_interval);

		Jedox.backend.php_ping_interval = <?php print intval(ini_get('session.gc_maxlifetime')) * 1000 - 120000; ?>;
		setTimeout(Jedox.backend.php_ping, Jedox.backend.php_ping_interval);

		Jedox.backend.activityIndctr = document.getElementById('activityIndctr');

<?php
if (!CFG_DEV_MODE && $prefs->search('general/updatecheck') != 'no')
	print '		Jedox.studio.app.updateCheck();' . "\n";
?>

		window.onbeforeunload = function () { return 'leaving_app_msg'.localize(); };

	</script>

	<iframe src="" id="etl_download" style="width: 0px; height: 0px; border: 0px; visibility: hidden;"></iframe>

</body>

</html>