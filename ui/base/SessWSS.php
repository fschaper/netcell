<?php

/*
 * \brief WSS session class
 *
 * \file SessWSS.php
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: SessWSS.php 4218 2010-10-29 07:12:20Z predragm $
 *
 */

class SessWSS
{
	public $curr_appid;
	public $curr_wbid;
	public $curr_wsid;

	public $worksheet_elems;
	public $worksheet_clones;

	public $hb_catalog;

	public function __construct ()
	{
		$this->__wakeup();

		$this->worksheet_elems = new WorksheetElementsCollection();

		$this->hb_catalog = new DynarangeCatalog();
	}

	public function __wakeup ()
	{
		if (isset($_SERVER['HTTP_X_WSS_BOOK']))
			list ($this->curr_wbid, $this->curr_wsid) = split(' ', $_SERVER['HTTP_X_WSS_BOOK']);
		else if (isset($_GET['buid']))
		{
			$this->curr_wbid = $_GET['buid'];
			$this->curr_wsid = isset($_GET['suid']) ? $_GET['suid'] : '';
		}
	}
}

?>