<?php

/*
 * \brief front file for saving preferences across all sessions
 *
 * \file prefs.php
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: prefs.php 4977 2011-05-20 14:32:03Z predragm $
 *
 */

require '../../../etc/config.php';

require 'autoload.php';
require 'ccmd.php';


// studio sess
session_name('STUDIO_SESSID');
session_start();

if (!isset($_SESSION['accessPolicy']))
	die();

$apol = $_SESSION['accessPolicy'];
$prefs = $_SESSION['prefs'];

$l10n_curr = $prefs->search('general/l10n');

$data = json_decode(file_get_contents('php://input', FILE_BINARY), true);

$prefs->set('', $data);

$res = $prefs->save($apol);

$wssu_sessid = $_SESSION['WSSU_SESSID'];
$wssd_sessid = $_SESSION['WSSD_SESSID'];

session_write_close();


// check if l10n has changed
$l10n_new = $prefs->search('general/l10n');

if ($l10n_new != $l10n_curr)
	$ccmd_susl = '[["susl","' . $l10n_new . '"]]';


// wss user sess
session_id($wssu_sessid);
session_name('WSSU_SESSID');
session_start();

$_SESSION['prefs']= $prefs;

if (isset($ccmd_susl))
	ccmd($ccmd_susl, -1, $wssu_sessid);

session_write_close();


// wss designer sess
session_id($wssd_sessid);
session_name('WSSD_SESSID');
session_start();

$_SESSION['prefs']= $prefs;

if (isset($ccmd_susl))
	ccmd($ccmd_susl, -1, $wssd_sessid);

session_write_close();

print $res ? 'OK' : 'ERR';

?>