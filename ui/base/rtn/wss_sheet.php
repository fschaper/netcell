<?php

/*
 * \brief RPC routines for handling WSS worksheets
 *
 * \file wss_sheet.php
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: wss_sheet.php 4195 2010-10-26 22:37:54Z predragm $
 *
 */

class wss_sheet
{
	public static function storePageSetup($inObj)
	{
		$payload = base64_encode(gzcompress(serialize($inObj), 1));

		$res = ccmd(array(array('wget', '', array(), array('e_id', 'payload'), array('e_type' => 'page_setup'))));
		if ($res[0][0] && $res[0][1][0]['e_id'])
			ccmd(array(array('wupd', '', array($res[0][1][0]['e_id'] => array('payload' => $payload)))));
		else
			ccmd(array(array('wadd', '', array('e_type' => 'page_setup', 'payload' => $payload))));

		return true;
	}

	public static function getPageSetup()
	{
		$res = ccmd(array(array('wget', '', array(), array('e_id', 'payload'), array('e_type' => 'page_setup'))));

		return (($res[0][0] && $res[0][1][0]['e_id']) ? unserialize(gzuncompress(base64_decode($res[0][1][0]['payload']))) : false);
	}
}

?>