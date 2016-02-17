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
 * SVN: $Id: UnConventional.php 4968 2011-05-18 08:22:46Z mladent $
 *
 */

class UnConventional {

	public static function getDefaultFontSizeForLabel($hasDataLabels)
	{
		return ($hasDataLabels) ? 8 : 0; // Default Font Size
	}

	public static function getDefault3DDepth($pie3DGroup)
	{
		return (get_class($pie3DGroup) == 'ChartGroup') ? 8 : 0;
	}

	public static function getLineAxisPos($chartType)
	{
		return ($chartType == XlChartType::xlMeterLineVertical) ? "Left" : "Top";
	}

	public static function getPlotAreaLeftX(&$Chart, $refcontext = null, $path = null)
	{
		return UnitConvertor::pointToPixel( $Chart->ChartArea->Width * 0.02 );
	}

	public static function getPlotAreaTopY(&$Chart, $refcontext = null, $path = null)
	{
		return UnitConvertor::pointToPixel($Chart->PlotArea->InsideTop);
	}

	public static function getPlotAreaRightX(&$Chart, $refcontext = null, $path = null)
	{
		return UnitConvertor::pointToPixel( ( ($Chart->HasLegend) ? $Chart->Legend->Left - $Chart->ChartArea->Width * 0.02 : $Chart->ChartArea->Width * 0.96 ) );
	}

	public static function getPlotAreaBottomY(&$Chart, $refcontext = null, $path = null)
	{
		return UnitConvertor::pointToPixel( $Chart->ChartArea->Height * 0.98 );
	}

	public static function getLegendOrder(&$Chart, $refcontext = null, $path = null)
	{
		return intval(!in_array($Chart->ChartType, array(
			XlChartType::xlRadar,
			XlChartType::xlRadarMarkers,
			XlChartType::xlRadarFilled,
			XlChartType::xlBubble,
			XlChartType::xlBubble3DEffect,
			XlChartType::xl3DAreaStacked,
			XlChartType::xl3DAreaStacked100,
			XlChartType::xl3DColumnStacked,
			XlChartType::xl3DColumnStacked100,
			XlChartType::xlAreaStacked,
			XlChartType::xlAreaStacked100,
			XlChartType::xlColumnStacked,
			XlChartType::xlColumnStacked100,
			XlChartType::xlCylinderColStacked,
			XlChartType::xlCylinderColStacked100,
			XlChartType::xlLineMarkersStacked,
			XlChartType::xlLineMarkersStacked100,
			XlChartType::xlLineStacked,
			XlChartType::xlLineStacked100,
		)));
	}

	public static function positionLegend(&$Chart, $parent, $init = null, $args = null)
	{
		$retEvel = '';
		if ($Chart->HasLegend)
		{
			$lOver = (isset($Chart->Legend->IncludeInLayout)) ? !$Chart->Legend->IncludeInLayout : false; // backward compatibility
			$lPos = (isset($Chart->Legend->Position)) ? $Chart->Legend->Position : XlLegendPosition::xlLegendPositionRight; // backward compatibility
			$paPos = array(self::getPlotAreaLeftX($Chart), self::getPlotAreaTopY($Chart), self::getPlotAreaRightX($Chart), self::getPlotAreaBottomY($Chart));

			if (in_array($Chart->ChartType, array(XlChartType::xlRadar, XlChartType::xlRadarMarkers, XlChartType::xlRadarFilled)))
				$adjRbyW = ($paPos[2] - $paPos[0] < $paPos[3] - $paPos[1]);

			switch ($lPos)
			{
				case XlLegendPosition::xlLegendPositionCustom: // Custom will work as Right - until custom position is implemented
					$Chart->Legend->Position = XlLegendPosition::xlLegendPositionRight;
				case XlLegendPosition::xlLegendPositionCorner: // right-top (corner)
				case XlLegendPosition::xlLegendPositionRight: // right
				default:
				{
					$halfPaH = ($lPos == XlLegendPosition::xlLegendPositionCorner) ? (-1) : ( ( self::getPlotAreaBottomY($Chart) - self::getPlotAreaTopY($Chart) ) / 2 );

					$retEvel .= '$var_' . $init . ' = $' . $parent . '->layoutLegend();' . "\n";
					$retEvel .= '$var_' . $init . '->setPos(' . UnitConvertor::pointToPixel($Chart->Legend->Left) . ', (' . $halfPaH . ' <= ($var_' . $init . '->getHeight()/2)) ? ' . self::getPlotAreaTopY($Chart) . ' : ' . ( self::getPlotAreaTopY($Chart) + $halfPaH ) . ' - ($var_' . $init . '->getHeight()/2));' . "\n";
					if (!in_array($Chart->ChartType, array(XlChartType::xlRadar, XlChartType::xlRadarMarkers, XlChartType::xlRadarFilled)))
						$retEvel .= '$' . $parent . '->packPlotArea(' . $paPos[0] . ',' . $paPos[1] . ',' . ( ($lOver) ? UnitConvertor::pointToPixel($Chart->ChartArea->Width * 0.96) : $paPos[2] ) . ',' . $paPos[3] . ',0,0);' . "\n";
					else
					{
						$xPos = $paPos[0] + (UnitConvertor::pointToPixel($Chart->ChartArea->Width * 0.96) - $paPos[0])/2;
						$chStr = '($var_' . $init . '->getWidth()+' . UnitConvertor::pointToPixel($Chart->ChartArea->Width * 0.02) . ')/2';
						$retEvel .= '$' . $parent . '->setPlotArea(' . $xPos . ( ($lOver) ? '' : ( '-' . $chStr ) ) . ',' . FormatConvertor::getRadarCenterY($Chart) . ',' . FormatConvertor::getRadarRadius($Chart) . ( $adjRbyW ? ( ($lOver) ? ('+' . $chStr) : '') : '' ) . ', Transparent, Transparent, 1);' . "\n";
					}
					break;
				}

				case XlLegendPosition::xlLegendPositionLeft: // left
				{
					$halfPaH = ( self::getPlotAreaBottomY($Chart) - self::getPlotAreaTopY($Chart) ) / 2;
					$paLgndGap = UnitConvertor::pointToPixel($Chart->ChartArea->Width * 0.02);

					$retEvel .= '$var_' . $init . ' = $' . $parent . '->layoutLegend();' . "\n";
					$retEvel .= '$var_' . $init . '->setPos(' . $paPos[0] . ', (' . $halfPaH . ' <= ($var_' . $init . '->getHeight()/2)) ? ' . self::getPlotAreaTopY($Chart) . ' : ' . ( self::getPlotAreaTopY($Chart) + $halfPaH ) . ' - ($var_' . $init . '->getHeight()/2));' . "\n";
					if (!in_array($Chart->ChartType, array(XlChartType::xlRadar, XlChartType::xlRadarMarkers, XlChartType::xlRadarFilled)))
						$retEvel .= '$' . $parent . '->packPlotArea(' . $paPos[0] . ( ($lOver) ? '' : ( '+$var_' . $init . '->getWidth()+' . $paLgndGap )) . ',' . $paPos[1] . ',' . UnitConvertor::pointToPixel($Chart->ChartArea->Width * 0.96) . ',' . $paPos[3] . ',0,0);' . "\n";
					else
					{
						$xPos = $paPos[0] + (UnitConvertor::pointToPixel($Chart->ChartArea->Width * 0.96) - $paPos[0])/2;
						$chStr = '+($var_' . $init . '->getWidth()+' . $paLgndGap . ')/2';
						$retEvel .= '$' . $parent . '->setPlotArea(' . $xPos . ( ($lOver) ? '' : $chStr ) . ',' . FormatConvertor::getRadarCenterY($Chart) . ',' . FormatConvertor::getRadarRadius($Chart) . ( $adjRbyW ? ( ($lOver) ? $chStr : '') : '' ) . ', Transparent, Transparent, 1);' . "\n";
					}

					break;
				}

				case XlLegendPosition::xlLegendPositionTop: // top
				case XlLegendPosition::xlLegendPositionBottom: // bottom
				{
					$paPos[2] = UnitConvertor::pointToPixel($Chart->ChartArea->Width * 0.96);
					$paWidth = $paPos[2] - $paPos[0];
					$paLgndGap = UnitConvertor::pointToPixel($Chart->ChartArea->Height * 0.03);

					$retEvel .= '$var_' . $init . ' = $' . $parent . '->getLegend();' . "\n";
					$retEvel .= '$var_' . $init . '->setCols(-2);' . "\n";
					$retEvel .= '$var_' . $init . '->setTruncate(' . $paWidth . ',1);' . "\n";
					$retEvel .= '$var_' . $init . ' = $' . $parent . '->layoutLegend();' . "\n";

					if ($lPos==XlLegendPosition::xlLegendPositionBottom)
					{
						$retEvel .= '$var_' . $init . '->setPos(' . ($paPos[0] + $paWidth/2) . '-$var_' . $init . '->getWidth()/2,' . $paPos[3] . '-$var_' . $init . '->getHeight());' . "\n";
						if (!in_array($Chart->ChartType, array(XlChartType::xlRadar, XlChartType::xlRadarMarkers, XlChartType::xlRadarFilled)))
							$retEvel .= '$' . $parent . '->packPlotArea(' . $paPos[0] . ',' . $paPos[1] . ',' . $paPos[2] . ',' . $paPos[3] . ( ($lOver) ? '' : ( '-$var_' . $init . '->getHeight()-' . $paLgndGap ) ) . ',0,0);' . "\n";
						else
						{
							$chStr = ( ($lOver) ? '' : ( '-($var_' . $init . '->getHeight()+' . $paLgndGap . ')/2' ) );
							$retEvel .= '$' . $parent . '->setPlotArea(' . ($paPos[0] + $paWidth/2) . ',' . FormatConvertor::getRadarCenterY($Chart) . $chStr . ',' . FormatConvertor::getRadarRadius($Chart) . ( (!$adjRbyW) ? $chStr : '' ) . ', Transparent, Transparent, 1);' . "\n";
						}
					}
					else
					{
						$retEvel .= '$var_' . $init . '->setPos(' . ($paPos[0] + $paWidth/2) . '-$var_' . $init . '->getWidth()/2,' . $paPos[1] . ');' . "\n";
						if (!in_array($Chart->ChartType, array(XlChartType::xlRadar, XlChartType::xlRadarMarkers, XlChartType::xlRadarFilled)))
							$retEvel .= '$' . $parent . '->packPlotArea(' . $paPos[0] . ',' . $paPos[1] . ( ($lOver) ? '' : ( '+$var_' . $init . '->getHeight()+' . $paLgndGap ) ) . ',' . $paPos[2] . ',' . $paPos[3] . ',0,0);' . "\n";
						else
						{
							$chStr = ( ($lOver) ? '0' : ( '($var_' . $init . '->getHeight()+' . $paLgndGap . ')/2' ) );
							$retEvel .= '$' . $parent . '->setPlotArea(' . ($paPos[0] + $paWidth/2) . ',' . FormatConvertor::getRadarCenterY($Chart) . '+' . $chStr . ',' . FormatConvertor::getRadarRadius($Chart) . ( (!$adjRbyW) ? ('-' . $chStr) : '' ) . ', Transparent, Transparent, 1);' . "\n";
						}
					}

					break;
				}
			}
		}

		return $retEvel;
	}

	public static function axis_getLabelGap(&$Chart, $refcontext = null, $path = null)
	{
		if ($path == 'Chart.XAxis')
			return UnitConvertor::pointToPixel($Chart->ChartArea->Height * 0.02);
		else if ($path == 'Chart.YAxis')
			return UnitConvertor::pointToPixel($Chart->ChartArea->Width * 0.02);
		else
			return 10;
	}
}

?>