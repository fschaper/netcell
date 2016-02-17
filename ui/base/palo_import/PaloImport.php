<?php

/*
 * @brief ajax
 *
 * @file Group.js
 *
 * Copyright (C) 2006-2009 Jedox AG
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
 * SVN: $Id: PaloImport.php 2960 2010-03-19 15:13:02Z mladent $
 *
 */

class PaloImport
{
	protected $data;

	public function __construct()
	{
		$this->data = array();
	}

	public function execCmds()
	{
		try
		{
			$res = json_decode(ccmd('[["gurn"]]', 0), true);
			if ($res[0])
			{
				$u_rng = array(1,1,$res[0][1][0],$res[0][1][1]);
				$gvalCmd = array("gval", 1, $u_rng[0], $u_rng[1], $u_rng[2], $u_rng[3]);

				$execCmds = array();
				foreach ($this->data as $vals)
				{
					$cmd_arr = array(1, 1, count($vals), 1);
					foreach ($vals as $val)
						$cmd_arr[] = array('v' => $val);

					$execCmds[] = array('cdrn', array('cm' => false), $cmd_arr);
					$execCmds[] = $gvalCmd;
				}
				ccmd(json_encode($execCmds));
			}
		}
		catch (Exception $e)
		{}
	}

	public function genCmds()
	{
		$cmds = array();
		foreach ($this->data as $vals)
		{
			$cmd_arr = array(1, 1, count($vals), 1);
			foreach ($vals as $val)
				$cmd_arr[] = array('v' => $val);

			$cmds[] = array('cdrn', array('cm' => false), $cmd_arr);
		}

		return $cmds;
	}
}

?>