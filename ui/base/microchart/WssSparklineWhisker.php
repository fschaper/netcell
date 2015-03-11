<?php

/*
 * @brief ajax
 *
 * @file WssSparklineWhisker.php
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
 * SVN: $Id: WssSparklineWhisker.php 3631 2010-08-10 14:01:04Z mladent $
 *
 */

class WssSparklineWhisker extends WssSparklineBar
{
	function WssSparklineWhisker($data, $posValsColor, $negValsColor, $zeroValsColor, $scaling =0, $scalingMin =0, $scalingMax =1)
	{
		$whiskerData = array();
		foreach($data as $key => $value)
		{
			if ($value > 0)
				$whiskerData[$key] = 1;
			else if ($value < 0)
				$whiskerData[$key] = -1;
			else
				$whiskerData[$key] = 0;
		}

		parent::WssSparklineBar($whiskerData, $posValsColor, $negValsColor, 1);

		$this->SetColorHtml('zeroValsColor', $zeroValsColor);

		for($i=0; $i < count($this->dataSeries[1]); $i++)
		{
			if ($this->dataSeries[1][$i]['value'] == 0)
				$this->dataSeries[1][$i]['color'] =  'zeroValsColor';
		}

	}
}

?>