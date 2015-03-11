<?php

/*
 * \brief login form
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: index.php 5038 2011-06-07 15:16:03Z predragm $
 *
 */

header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T'));
header('Expires: Fri, 03 Sep 1999 01:00:00 GMT');
header('Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
header('Pragma: no-cache');

require '../../../etc/config.php';

define ('EXPIRE', time() - 604800);

if (isset($_COOKIE['app']))
{
	define ('APP', $_COOKIE['app']);
	setcookie('app', '', EXPIRE, '/ui/login/');
}
else
	define ('APP', '/ui/studio/');

// logout
if ($_SERVER['QUERY_STRING'] == 'r')
{
	require '../../../base/ccmd.php';
	require '../../../base/AccessPolicy.php';

	foreach (array('WSSU_SESSID', 'WSSD_SESSID') as $sess_name)
	{
		session_name($sess_name);
		session_start();

		ccmd('[["logo"]]');

		session_destroy();
		setcookie($sess_name, '', EXPIRE, '/');
	}

	session_name('STUDIO_SESSID');
	session_start();

	if (isset($_SESSION['accessPolicy']))
	{
		$apol = $_SESSION['accessPolicy'];
		palo_remove_connection($apol->getConn());
		palo_remove_connection($apol->getSuperConn());
	}

	session_destroy();
	setcookie('STUDIO_SESSID', '', EXPIRE, '/');

	header('Location: /ui/login/');
	die();
}

// auto-login
if (isset($_GET['user']) && isset($_GET['pass']))
{
	require '../../../base/ccmd.php';
	require '../../../base/AccessPolicy.php';
	require '../../../base/util/XMLData.php';
	require '../../../base/Prefs.php';
	require '../../../base/rtn/login.php';

	$user = $_GET['user'];
	$pass = base64_decode($_GET['pass']);

	$td = mcrypt_module_open('rijndael-128', '', 'cfb', '');

	mcrypt_generic_init($td, CFG_SECRET, md5($user, true));
	$pass = trim(mdecrypt_generic($td, $pass));
	mcrypt_generic_deinit($td);

	mcrypt_module_close($td);

	$res = login::in($user, $pass);

	if ($res[0])
	{
		header('Location: ' . APP . ($_SERVER['QUERY_STRING'] ? '?' . $_SERVER['QUERY_STRING'] : ''));
		die();
	}
	else
		$errmsg = $res[1];
}

// version
DEFINE('VERSION_FILE', '../../../version');

if (is_readable(VERSION_FILE))
	$version = file_get_contents(VERSION_FILE);

// license
if (is_resource($conn = @palo_init(CFG_PALO_HOST, CFG_PALO_PORT, CFG_PALO_USER, CFG_PALO_PASS)))
{
	$license = @palo_license_info($conn);
	@palo_disconnect($conn);
}

if (!isset($license) || !is_array($license))
	$license = array();

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>

<head>
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE8" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Palo Web | Login</title>
<style type="text/css">

*
{
	font-family: Arial, Helvetica, sans-serif;
	font-size: 12px;
	font-weight: bold;
	color: #1C3F93;
}

body
{
	margin: 0px;
	padding: 0px;
	background-image: url(/ui/studio/res/img/login/hg_top.jpg);
	background-position: top left;
	background-repeat: repeat-x;
}

#board
{
	position: relative;
	width: 340px;
	margin: 0px auto 0px auto;
	padding: 0 0 0 0;
	background-color: #3C3C3C;
	background-position: top left;
	background-repeat: repeat-y;
}

#login_box
{
	position: absolute;
	background-image: url(/ui/studio/res/img/login/box.jpg);
	background-repeat: no-repeat;
	top: 165px;
	padding: 45px;
	width: 346px;
	height: 875px;
	padding-top: 140px;
}

#login_button
{
	background-color: #448855;
	margin-top: 0px;
	clear: both;
	border: 1px #B3B9C3 solid;
	background-color: #C2C9CF;
}

#edition_box
{
	position: absolute;
	top: 265px;
	left: 5px;
	padding: 10px;
	width: 310px;
	white-space: nowrap;
	font-size: 11px;
	font-weight: bold;
	text-align: left;
}

#release_box
{
	position: absolute;
	top: 265px;
	left: 0px;
	padding: 10px;
	width: 315px;
	white-space: nowrap;
	font-size: 11px;
	font-weight: bold;
	text-align: right;
}

#info_box
{
	position: absolute;
	top: 308px;
	left: 0px;
	padding: 10px;
	width: 320px;
	font-size: 11px;
	font-weight: normal;
	text-align: center;
}

#username
{
	position: absolute;
	margin-top: 8px;
	width: 80px;
}

#userinput
{
	position: absolute;
	padding-left: 80px;
	margin-top: 8px;
	width: 150px;
}

#password
{
	position: absolute;
	margin-top: 38px;
	width: 80px;
}

#passinput
{
	position: absolute;
	padding-left: 80px;
	margin-top: 38px;
	width: 150px;
}

#nwindowcheck
{
	position: absolute;
	margin-top: 76px;
	margin-left: 140px;
	width: 150px;
	z-index: 100;
}

#login
{
	position: absolute;
	padding-left: 80px;
	margin-top: 76px;
	width: 100px;
}

</style>
</head>

<body onLoad="onLoad();">

	<div id="board">
		<div id="login_box">
			<iframe src="empty.html" id="temp" name="temp" style="display: none;"></iframe>
			<form name="loginForm" id="loginForm" rel="nofollow" target="temp" action="" onsubmit="return login();">
				<div id="username">Username:</div>
				<div id="userinput">
					<input id="user" type="text" name="username" onKeyPress="chkInput(event);">
				</div>
				<div id="password">Password:</div>
				<div id="passinput">
					<input id="pass" type="password" name="password" value="" onKeyPress="chkInput(event);">
				</div>
				<div id="nwindowcheck">
					<input id="newwin" type="checkbox" name="newwin">&nbsp;New Window
				</div>
				<div id="login">
					<input name="Submit" id="login_button" type="submit" value="Login">
				</div>
			<div id="edition_box"><?php print $license['name'] ? 'Premium' : 'Community'; ?> Edition</div>
			<div id="release_box">Release: <?php print CFG_VERSION . (isset($version) ? '.' . substr($version, 0, strpos($version, "\t")) : '-dev'); ?></div>
			<?php if ($license['name']) { ?><div id="info_box">Licensed to: <?php print $license['name']; ?></div><?php } ?>
			</form>
		</div>
	</div>

	<script type="text/javascript">

		function onLoad ()
		{
			<?php if (isset($errmsg)) print 'alert("' . $errmsg . '"); '; ?>document.getElementById('user').focus();
		}

		function chkInput (ev)
		{
			if ((document.all ? window.event.keyCode : ev.which) == 13)
				document.getElementById('loginForm').submit();
		}

		function login ()
		{
			var userField = document.getElementById('user'),
					passField = document.getElementById('pass');

			if (userField.value.length < 1)
			{
				alert('Please, input your username!');
				userField.focus();
				return;
			}

			if (passField.value.length < 1)
			{
				alert('Please, input your password!');
				passField.focus();
				return;
			}

			var post = 'user='.concat(encodeURIComponent(userField.value), '&pass=', encodeURIComponent(passField.value)),
					xhr = new XMLHttpRequest();

			xhr.open('POST', '/be/login.php', true);
			xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
			xhr.setRequestHeader('Content-Length', post.length);

			xhr.onreadystatechange = function ()
			{
				if (xhr.readyState != 4)
					return;

				if (xhr.status != 200 || xhr.responseText != 'OK')
				{
					alert(xhr.responseText);
					userField.focus();
					return;
				}

				var url = '<?php print APP; ?>'.concat(window.location.search);

				if (document.getElementById('newwin').checked)
					window.open(url, 'app_win', 'directories=no,menubar=no,toolbar=no,location=no,status=no,resizable=yes,scrollbars=no');
				else
					window.location.href = url;
			};

			xhr.send(post);
		}

	</script>

</body>

</html>