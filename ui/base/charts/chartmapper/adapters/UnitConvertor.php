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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: UnitConvertor.php 2212 2009-09-30 13:16:31Z predragm $
 *
 */

class UnitConvertor {

	/**
	 * Converts points to pixels.
	 * @access public
	 * @param integer $points the number of the points.
	 * @return integer returns the value in pixels.
	 **/
	public static function pointToPixel($points) {
		return intval($points * 96 / 72);
	}

	/**
	 * Converts percent to decimal number.
	 * @access public
	 * @param string $percent (0x37).
	 * @return decimal float (0.55).
	 **/
	public static function percentToNumber($percent)
	{

		return floatval(ltrim($percent, '0x')) / 100.0;
	}

	/**
	 * Converts percent Bar Gap in Excel format to decimal number for Bar Gap percents in ChartDirector format.
	 * @access public
	 * @param string $percent (0x37).
	 * @return decimal float (0.35).
	 **/
	public static function percentBarGap($percent)
	{
		// MLADEN .. cd_proc = exl_proc / (1 + exl_proc)
		$exl_proc = floatval(ltrim($percent, '0x')) / 100.0;
		return floatval($exl_proc / (1 + $exl_proc));
	}

	public function pointToPixelSuperTest(&$Chart, $refcontext = null, $argvalue = null) {
		return intval(($argvalue + $Chart->ChartTitle->Left - 218) * 96 / 72);
	}

	public static function pointToPixelTweakTest($points, $operator, $tweak, $unit) {
		$pixelValue = intval($points * 96 / 72);
		$evalStr = '$result = ' . $pixelValue . ' ' . $operator;

		switch ($unit) {
			case 'pixel':
				$evalStr .= ' ' . $tweak . ';';
				break;

			case 'percent':
				$evalStr .= $pixelValue . ' * ' . $tweak . ' / 100;';
				break;

			default:
				$evalStr .= ' ' . $tweak . ';';
				break;
		}

		eval($evalStr);
		return $result;
	}

	public static function xlBarShapeToCDBarShape($chartTypeArg)
	{
		$chartType = intval($chartTypeArg + 0);

		switch ($chartType)
		{
			case XlChartType::xlCylinderBarClustered:
			case XlChartType::xlCylinderBarStacked:
			case XlChartType::xlCylinderBarStacked100:
			case XlChartType::xlCylinderColClustered:
			case XlChartType::xlCylinderColStacked:
			case XlChartType::xlCylinderColStacked100:
				return 'CircleShape';

			default:
				return 'SquareShape';
		}
	}
}

?>