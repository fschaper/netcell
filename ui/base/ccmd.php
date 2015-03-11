<?php

/*
 * \brief ccmd function
 *
 * \file ccmd.php
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
 *
 * \version
 * SVN: $Id: ccmd.php 5101 2011-07-08 13:46:57Z predragm $
 *
 */

function ccmd ($ccmd, $flags = -1, $sess_id = '', $path = CFG_UB_PATH)
{
	$ch = curl_init('http://127.0.0.1:' . CFG_UB_PORT . $path . ($flags == -1 ? '' : '?' . $flags));

	$hdrs = array('Content-Type: application/json; charset=utf-8; charset=UTF-8');

	if (($sess_wss = $_SESSION['wss']) && $sess_wss->curr_wbid)
		$hdrs[] = 'X-WSS-Book: ' . $sess_wss->curr_wbid . ($sess_wss->curr_wsid ? ' ' . $sess_wss->curr_wsid : '');

	curl_setopt_array($ch, array(
	  CURLOPT_HEADER => false
	, CURLOPT_FORBID_REUSE => false
	, CURLOPT_FRESH_CONNECT => false
	, CURLOPT_POST => true
	, CURLOPT_RETURNTRANSFER => true
	, CURLOPT_FAILONERROR => true
	, CURLOPT_PROXY => ''
	, CURLOPT_USERAGENT => $_SERVER['HTTP_USER_AGENT']
	, CURLOPT_HTTPHEADER => &$hdrs
	));

	curl_setopt($ch, CURLOPT_POSTFIELDS, ($un = is_array($ccmd)) ? json_encode($ccmd) : $ccmd);

	if ($sess_id !== null && ($sess_id != '' || ($sess_id = session_id()) != ''))
		curl_setopt($ch, CURLOPT_COOKIE, 'WSS_SESSID=' . $sess_id . ';');

	if (CFG_PERF_MODE)
		$_dur_ccmd = microtime(true);

	if (($res = curl_exec($ch)) === false)
		$res = '[[false,3' . curl_errno($ch) . ',' . json_encode(curl_error($ch)) . ']]';

	if (CFG_PERF_MODE)
		$_SESSION['_dur_ccmd'] += round((microtime(true) - $_dur_ccmd) * 1000);

	curl_close($ch);

	return $un ? json_decode($res, true) : $res;
}

?>