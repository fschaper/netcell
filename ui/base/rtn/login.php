<?php

/*
 * \brief class for login ops
 *
 * \file login.php
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: login.php 5134 2011-07-20 13:17:32Z predragm $
 *
 */

class login
{
	public static function in ($user, $pass)
	{
		// access policy
		$apol = new AccessPolicy(CFG_PALO_HOST, CFG_PALO_PORT, CFG_PALO_USER, CFG_PALO_PASS, $user, $pass, false);

		if (!is_resource($apol->getConn(true)))
			return array(false, 'ERROR: Username or password invalid!');

		$apol->reload();

		$groups = $apol->getGroups();

		if (!count($groups))
				return array(false, 'ERROR: Unable to fetch user group!');


		// check Config db
		$superconn = $apol->getSuperConn();

		if (!is_int(palo_get_dimension_id($superconn, 'Config', 'config')) || !is_int(palo_get_dimension_id($superconn, 'Config', 'connections')))
				return array(false, 'ERROR: Config database missing or invalid!');


		// prefs + login ccmd
		$prefs = new Prefs($apol, Prefs::LEVEL_USER);

		$ccmd = '[["logi",' . json_encode($user) . ',' . json_encode($pass) . ',' . json_encode($groups) . '],["susl","' . $prefs->search('general/l10n') . '"]]';


		// wss user sess
		$res = json_decode(ccmd($ccmd, -1, null), true);

		if ($res[0][0] !== true || $res[1][0] !== true)
			return array(false, 'ERROR: Backend is unavailable!');

		session_id($wssu_sessid = $res[0][1]);
		session_name('WSSU_SESSID');
		session_start();

		$_SESSION['accessPolicy'] = $apol;
		$_SESSION['prefs'] = $prefs;

		session_write_close();


		// wss designer sess
		$res = json_decode(ccmd($ccmd, -1, null), true);

		if ($res[0][0] !== true || $res[1][0] !== true)
			return array(false, 'ERROR: Backend is unavailable!');

		session_id($wssd_sessid = $res[0][1]);
		session_name('WSSD_SESSID');
		session_start();

		$_SESSION['accessPolicy'] = $apol;
		$_SESSION['prefs'] = $prefs;

		session_write_close();


		// studio sess
		session_name('STUDIO_SESSID');
		session_start();
		session_regenerate_id(false);

		$_SESSION['accessPolicy'] = $apol;
		$_SESSION['prefs'] = $prefs;
		$_SESSION['WSSU_SESSID'] = $wssu_sessid;
		$_SESSION['WSSD_SESSID'] = $wssd_sessid;

		session_write_close();

		return array(true);
	}
}

?>