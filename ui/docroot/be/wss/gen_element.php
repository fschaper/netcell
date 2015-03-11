<?php

/*
 * \brief used as URL source for images and charts
 *
 * \file gen_element.php
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: gen_element.php 5134 2011-07-20 13:17:32Z predragm $
 *
 */

if (CFG_PERF_MODE)
	$_dur_php = microtime(true);

require '../../../etc/config.php';

require 'autoload.php';
require 'ccmd.php';

if (isset($_GET['sid']))
	session_id($_GET['sid']);

require 'sess_start.php';

if (!isset($_GET['id']))
	die();

$id = $_GET['id'];
$type = isset($_GET['t']) ? $_GET['t'] : 'chart';

switch ($type)
{
	case 'img':

		$res = ccmd(array(array('wget', '', array(), array('img_type', 'payload'), array('e_id' => $id))));

		session_write_close();

		if (!is_array($res[0][1][0]))
			die();

		$res = $res[0][1][0];

		ob_clean();

		$data = gzuncompress(base64_decode($res['payload']));

		header('Content-Type: ' . $res['img_type']);
		header('Content-Length: ' . strlen($data));

		print $data;

		flush();
		ob_end_flush();

		break;

	default:

		if (!isset($_SESSION['wss']))
			die();

		$wss = new WSS();
		$wsels = $wss->get_worksheet_elements();

		if (($chart = $wsels->get_element($wss->getCurrWbId(), $wss->getCurrWsId(), $id)) === false)
			die();

		if (isset($_GET['w']) && isset($_GET['h']))
		{
			$wpx = intval($_GET['w']);
			$hpx = intval($_GET['h']);

			$wpt = $wsels->pixel_to_point($wpx);
			$hpt = $wsels->pixel_to_point($hpx);

			if ($chart->ChartArea->Width != $wpt || $chart->ChartArea->Height != $hpt)
			{
				$chart->ChartArea->Width = $wpt;
				$chart->ChartArea->Height = $hpt;
				$wsels->savePayload($wss->getCurrWbId(), $wss->getCurrWsId(), $id);

				ccmd('[["wupd","",{"' . $id . '":{"size":[' . $wpx . ',' . $hpx . ']}}]]');
			}
		}

		session_write_close();

		require 'chartdir/phpchartdir.php';

		ob_clean();

		$chart->MakeChart('PNG');

		flush();
		ob_end_flush();
}

if (CFG_PERF_MODE)
{
	session_start();
	$_SESSION['_dur_php'] += round((microtime(true) - $_dur_php) * 1000);
}

?>