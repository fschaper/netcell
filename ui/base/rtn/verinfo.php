<?php

/*
 * \brief version info routines
 *
 * \file verinfo.php
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
 * SVN: $Id: verinfo.php 4669 2011-03-02 14:41:52Z predragm $
 *
 */

class verinfo
{
	const UPDATE_URI = 'http://up.palo.net/update/';

	private static function _inflateDate ($d)
	{
		return substr($d, 0, 4) . '-' . substr($d, 4, 2) . '-' . substr($d, 6, 2) . ' ' . substr($d, 8, 2) . ':' . substr($d, 10, 2) . ':' . substr($d, 12, 2) . ' ' . (substr($d, 14, 1) == '0' ? '+' : '-') . substr($d, 15, 4);
	}

	public static function get ()
	{
		$ver = array('rel' => CFG_VERSION, 'os' => php_uname('s') . ' ' . php_uname('r'), 'arch' => php_uname('m'));

		// frontend
		if (is_readable($v = $_SERVER['DOCUMENT_ROOT'] . '/../version'))
			$ver['ui'] = split("\t", trim(file_get_contents($v)));

		// backend
		$v = json_decode(ccmd('[["gsi"]]', -1, null), true);

		if (is_array($v[0]) && $v[0][0] == true && is_string($v[0][1]) && preg_match('/^.+version ([0-9\.]+) \(build: ([0-9]{19}), repository: ([0-9]{19})\)$/', $v[0][1], $v))
			$ver['core'] = array($v[1], self::_inflateDate($v[3]), self::_inflateDate($v[2]));

		// palo server
		$ch = curl_init('http://' . CFG_PALO_HOST . ':' . CFG_PALO_PORT . '/server/info');

		curl_setopt_array($ch, array(
		  CURLOPT_HEADER => false
		, CURLOPT_RETURNTRANSFER => true
		, CURLOPT_FAILONERROR => true
		, CURLOPT_PROXY => ''
		));

		if (($v = curl_exec($ch)) !== false && strpos($v, ';') !== false)
			$ver['palosrv'] = implode('.', array_slice(explode(';', $v), 0, 4));

		// palo libs
		$v = palo_version();

		if (isset($v['libpalo']))
			$ver['libpalo'] = $v['libpalo'];

		// etl
		$ch = curl_init('http://127.0.0.1:' . CFG_UB_PORT . '/tc/web-etl/app/service/studiologin');

		curl_setopt_array($ch, array(
		  CURLOPT_HEADER => false
		, CURLOPT_POST => true
		, CURLOPT_RETURNTRANSFER => true
		, CURLOPT_FAILONERROR => true
		, CURLOPT_PROXY => ''
		, CURLOPT_POSTFIELDS => '{"gv":"true","gsv":"true"}'
		));

		if (($v = curl_exec($ch)) !== false && is_array($v = json_decode($v, true)))
		{
			if (isset($v['server_version']))
				$ver['etlsrv'] = $v['server_version'];

			if (isset($v['client_version']))
				$ver['etlcln'] = $v['client_version'];
		}

		return $ver;
	}

	public static function updateCheck ($l10n, $notif)
	{
		session_write_close();

		$ver = self::get();

		$qstr = '?ns=pw1&flag=' . ($notif ? 1 : 0) . '&rel=' . urlencode($ver['rel']) . '&os=' . urlencode($ver['os']) . '&arch=' . urlencode($ver['arch']);

		if ($l10n)
			$qstr .= '&l10n=' . urlencode($l10n);

		if (isset($ver['ui']))
			$qstr .= '&pwfe=' . urlencode($ver['rel'] . '.' . $ver['ui'][0]);

		if (isset($ver['core']))
			$qstr .= '&pwbe=' . urlencode($ver['core'][0]);

		if (isset($ver['palosrv']))
			$qstr .= '&molap=' . urlencode($ver['palosrv']);

		if (isset($ver['libpalo']))
			$qstr .= '&api=' . urlencode($ver['libpalo']);

		if (isset($ver['etlsrv']))
			$qstr .= '&etl=' . urlencode($ver['etlsrv']);

		if (isset($ver['etlcln']))
			$qstr .= '&etlm=' . urlencode($ver['etlcln']);

		$ch = curl_init(self::UPDATE_URI . $qstr);

		curl_setopt_array($ch, array(
		  CURLOPT_HEADER => false
		, CURLOPT_RETURNTRANSFER => true
		, CURLOPT_FAILONERROR => true
		, CURLOPT_PROXY => ''
		, CURLOPT_USERAGENT => $_SERVER['HTTP_USER_AGENT']
		));

		return ($res = curl_exec($ch)) !== false ? $res : '0;';
	}

}

?>