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
 * SVN: $Id: FormatConvertor.php 5025 2011-06-02 11:38:15Z mladent $
 *
 */

class FormatConvertor {
   public static $fontMapping = array('Calibri'          => 'CALIBRI.TTF',
                                      'Tahoma'           => 'tahoma.ttf',
                                      'Sans Serif'       => 'micross.ttf',
                                      'Times New Roman'  => 'times.ttf',
                                      'Arial'            => 'arial.ttf',
                                      'Arial Narrow'     => 'arialn.ttf',
                                      'Verdana'          => 'verdana.ttf',
                                      'Monotype Corsiva' => 'mtcorsva.ttf',
                                      'Georgia'          => 'georgia.ttf',
                                      'Impact'           => 'impact.ttf',
                                      'Trebuchet MS'     => 'trebuc.ttf',
                                      'Comic Sans MS'    => 'comic.ttf',
                                      'Arial Black'      => 'ariblk.ttf',
                                      'Lucida Console'   => 'lucon.ttf');

	/**
	 * FUNCTION TO BE REMOVED
	 **/
	public static function hexColor($color) {
		return $color;
	}

	public function colorObject(&$Chart, $refcontext = null, $path = null) {
		if (is_null($path))
			return 'Transparent';
		else {
			eval('$colorObj = $' . str_replace('.', '->', $path) . ';');
			return $this->RGBExcelToCD($colorObj->RGB);
		}
	}

   /**
    * Convert Excel RGB format(BGR) to CD format
    **/
	public static function RGBExcelToCD($RGB) {
		if ($RGB < 0x0 || $RGB > 0xFFFFFF)
		   return 'Transparent';
		else {
         $RGB = substr($RGB, 2);
         $RGB = str_pad($RGB, 6, '0', STR_PAD_LEFT);
		   $BGR = str_split($RGB, 2);
		   return '0x' . $BGR[2] . $BGR[1] . $BGR[0];
		}
	}

	/**
	 * FUNCTION TO BE REMOVED
	 **/
	public static function hexNumber($hex) {
		return $hex;
	}

	public function textObject(&$Chart, $refcontext = null, $path = null) {
	   if (is_null($path))
         return '';

      $CDMLString = '<*';
		eval('$textObj = $' . str_replace('.', '->', $path) . ';');
		if ( isset(FormatConvertor::$fontMapping[$textObj->Font->Name]) ) {
		   $CDMLString .= 'font=' . FormatConvertor::$fontMapping[$textObj->Font->Name];
         if ( $textObj->Font->Bold || stripos( $textObj->Font->FontStyle, 'Bold') !== false )
            $CDMLString .= ' Bold';
         if ( $textObj->Font->Italic || stripos( $textObj->Font->FontStyle, 'Italic') !== false )
            $CDMLString .= ' Italic';
		   $CDMLString .= ',';
		}

      $CDMLString .= 'size=' . $textObj->Font->Size . ',';
      if ( $textObj->Font->Subscript )
         $CDMLString .= 'sub,';
      if ( $textObj->Font->Superscript )
         $CDMLString .= 'super,';

      if ( $textObj->Font->Underline != 606358669 )
         $CDMLString .= 'underline=1,';
      $CDMLString .= 'color=' . str_replace('0x', '', $this->RGBExcelToCD($textObj->Font->Color)) . ',';
      //if ( $textObj->Interior->Color >= 0 && $textObj->Interior->Color <= 0xFFFFFF )
      //   $CDMLString .= 'bgColor=' . substr($textObj->Interior->Color,2) . '';

		return '\'' . $CDMLString . '*>' . addcslashes($textObj->Text, '\'\\') . '\'';
	}

	public static function escapedText($text)
	{
		return '\'' . addcslashes($text, '\'\\') . '\'';
	}

	public static function fontFileName($font) {
		return '\'' . (isset(FormatConvertor::$fontMapping[$font]) ? FormatConvertor::$fontMapping[$font] : 'CALIBRI.TTF') . '\'';
	}

	public static function fontSize($font)
	{
		if (isset($font) && isset($font->Size))
			return $font->Size;

		return 10;
	}

	public function getPieCenterX(&$Chart, $refcontext = null, $path = null)
	{
		return UnitConvertor::pointToPixel($Chart->ChartArea->Width / 2);
	}

	public function getPieCenterY(&$Chart, $refcontext = null, $path = null)
	{
		$topPart = ($Chart->HasTitle) ? $Chart->PlotArea->InsideTop : 0;
		return UnitConvertor::pointToPixel(($Chart->ChartArea->Height - $topPart) / 2 + $topPart);
	}

	public function getPieRadius(&$Chart, $refcontext = null, $path = null)
	{
		$factorFor3D = ( in_array($Chart->ChartType, array(XlChartType::xl3DPie, XlChartType::xl3DPieExploded)) ) ? sin( pi() / 3.9 ) : 1;
		$topPart = ($Chart->HasTitle) ? $Chart->PlotArea->InsideTop : 0;
		$numOfVals = count($Chart->SeriesCollection(1)->Values);
		$totalVal = 0;
		for ($i=0; $i<$numOfVals;)
			$totalVal += abs($Chart->SeriesCollection(1)->Values[$i++]);
		$curAngle = pi()/2;
		$xSize = 33; $ySize = 23; // ? - probably for labels size
		$maxW = $Chart->ChartArea->Width / 2 - XLSConfig::$configConst['pieChartsRadiusReduction']; $maxH = ($Chart->ChartArea->Height - $topPart) / 2 - XLSConfig::$configConst['pieChartsRadiusReduction'];
		$inPoints = min($maxW, $maxH);

		// calculate where labels will be
		for ($i=0; $i<$numOfVals; $i++)
		{
			$val = $Chart->SeriesCollection(1)->Values[$i];
			$piePart = ($totalVal > 0) ? abs($val / $totalVal) * pi() : 2 * pi() / $numOfVals;
			$alpha = $curAngle - $piePart;
			$explosionDist = (in_array($Chart->ChartType, array(XlChartType::xlPieExploded, XlChartType::xlDoughnutExploded, XlChartType::xl3DPieExploded))) ? ( $Chart->SeriesCollection(1)->Points($i+1)->Explosion / 100 ) : 0;

			// calc total size of X/Y need for chart (related to Labels)
			$xt = $inPoints * abs(cos($alpha)) * ( 1 + $explosionDist ) + $xSize;
			$yt = $inPoints * abs(sin($alpha)) * ( 1 + $explosionDist ) * $factorFor3D + $ySize; // number 3.9 comes from angle of PI/4 with some modifications (that's angle in 3D)
			if ($xt > $maxW && cos($alpha) != 0)
				$inPoints = min( ($maxW - $xSize) / abs(cos($alpha)) / ( 1 + $explosionDist ), $inPoints);
			if ($yt > $maxH && sin($alpha) != 0)
				$inPoints = min( ($maxH - $ySize) / abs(sin($alpha)) / $factorFor3D / ( 1 + $explosionDist ), $inPoints);

			// calc total size of X/Y need for chart (related to Edges of exploded parts)
			if ($explosionDist != 0)
			{
				$xTFact = max( abs( cos($alpha) * $explosionDist + cos($alpha - $piePart) ), abs( cos($alpha) * $explosionDist + cos($alpha + $piePart) ) );
				$yTFact = max( abs( sin($alpha) * $explosionDist + sin($alpha - $piePart) ), abs( sin($alpha) * $explosionDist + sin($alpha + $piePart) ) );

				$xt = $inPoints * $xTFact;
				$yt = $inPoints * $yTFact * $factorFor3D;

				if ( $xt > $maxW && $xTFact != 0 )
					$inPoints = $maxW / abs( cos($alpha) * $explosionDist + cos($alpha - $piePart) );
				if ( $yt > $maxH && $yTFact != 0 )
					$inPoints = $maxH / $yTFact / $factorFor3D;
			}

			$curAngle -= 2*$piePart;
		}

		return UnitConvertor::pointToPixel($inPoints);
	}

	public function getPieInnerRadius(&$Chart, $refcontext = null, $path = null)
	{
		$chartType = intval($Chart->ChartType + 0);

		switch ($chartType)
		{
			case XlChartType::xlDoughnut:
			case XlChartType::xlDoughnutExploded:

				if (isset($Chart->ChartGroups(1)->DoughnutHoleSize))
					return UnitConvertor::pointToPixel($this->getPieRadius($Chart, $refcontext, $path) * UnitConvertor::percentToNumber($Chart->ChartGroups(1)->DoughnutHoleSize));
				else
					// if empty -> return 45%
					return UnitConvertor::pointToPixel($this->getPieRadius($Chart, $refcontext, $path) * 0.45);

			default:
				return 0;
		}
	}

	// TODO: move to UnConventional
	public function getRadarCenterX(&$Chart, $refcontext = null, $path = null)
	{
		$lX = UnConventional::getPlotAreaLeftX($Chart);
		$rX = UnConventional::getPlotAreaRightX($Chart);

		return ($rX - $lX) / 2 + $lX;
	}

	// TODO: move to UnConventional
	public function getRadarCenterY(&$Chart, $refcontext = null, $path = null)
	{
		$tY = UnConventional::getPlotAreaTopY($Chart);
		$bY = UnConventional::getPlotAreaBottomY($Chart);

		return ($bY - $tY) / 2 + $tY;
	}

	// TODO: move to UnConventional
	public function getRadarRadius(&$Chart, $refcontext = null, $path = null)
	{
		$w = UnConventional::getPlotAreaRightX($Chart) - UnConventional::getPlotAreaLeftX($Chart);
		$h = UnConventional::getPlotAreaBottomY($Chart) - UnConventional::getPlotAreaTopY($Chart);

		$inPoints = min($h, $w)  / 2;
		$inPoints -= 20; // space for labels - pixels
		return $inPoints;
	}

	public function getBorderColor(&$Chart, $refcontext = null, $path = null)
	{
		if (is_null($path))
			return 'Transparent';
		else
		{
			eval('$borderObj = $' . str_replace('.', '->', $path) . ';');
			if ((intval($borderObj->ColorIndex + 0) == XlColorIndex::xlColorIndexAutomatic ) || (intval($borderObj->ColorIndex + 0) == XlColorIndex::xlColorIndexNone))
			{
				if ($path == 'Chart.Axes(2).MajorGridlines.Border')
					return $borderObj->Color;
				else
					return 'Transparent';
			}
			else
				return $borderObj->Color;
		}
	}

	public static function getOdometerCenterX(&$Chart, $refcontext = null, $path = null)
	{
		return UnitConvertor::pointToPixel($Chart->ChartArea->Width / 2);
	}

	public static function getOdometerCenterY(&$Chart, $refcontext = null, $path = null)
	{
		if (in_array($Chart->ChartType, array(XlChartType::xlMeterOdoFull100, XlChartType::xlMeterOdoFull)))
			return UnitConvertor::pointToPixel(($Chart->ChartArea->Height + $Chart->PlotArea->InsideTop) / 2);
		else if (in_array($Chart->ChartType, array(XlChartType::xlMeterOdoHalf, XlChartType::xlMeterOdoHalf100)))
			return UnitConvertor::pointToPixel($Chart->ChartArea->Height - 15);
		else
			return UnitConvertor::pointToPixel($Chart->PlotArea->InsideTop) + FormatConvertor::getOdometerRadius($Chart);
	}

	public static function getOdometerRadius(&$Chart, $refcontext = null, $path = null)
	{
		if (in_array($Chart->ChartType, array(XlChartType::xlMeterOdoFull100, XlChartType::xlMeterOdoFull)))
			$inPoints = (($Chart->ChartArea->Height - $Chart->PlotArea->InsideTop) < $Chart->ChartArea->Width) ?
						($Chart->ChartArea->Height - $Chart->PlotArea->InsideTop) / 2 - 10 :
						$Chart->ChartArea->Width / 2 - 10;
		else if (in_array($Chart->ChartType, array(XlChartType::xlMeterOdoHalf, XlChartType::xlMeterOdoHalf100)))
			$inPoints = (($Chart->ChartArea->Height - $Chart->PlotArea->InsideTop) < ($Chart->ChartArea->Width/2)) ?
						($Chart->ChartArea->Height - $Chart->PlotArea->InsideTop) - 10 :
						$Chart->ChartArea->Width / 2 - 10;
		else
		{
			$alfa = 1.1345; // in rads

			$wSpace = $Chart->ChartArea->Width / (2*cos($alfa)) - 10;
			$hSpace = ($Chart->ChartArea->Height - $Chart->PlotArea->InsideTop - 25) / (1 - sin($alfa)) - 10;

			$inPoints = ($wSpace < $hSpace) ? $wSpace : $hSpace;
		}

		// abs is used because of problems with negative radius values
		return UnitConvertor::pointToPixel(abs($inPoints));
	}

	public static function getOdometerStart(&$Chart, $refcontext = null, $path = null)
	{
		if (isset($Chart->Axes) && $Chart->Axes(1)->MinimumScaleIsAuto === false && !empty($Chart->Axes(1)->MinimumScale))
			return $Chart->Axes(1)->MinimumScale;
		else
		{
			if (!in_array($Chart->ChartType, array(XlChartType::xlMeterOdoFull100, XlChartType::xlMeterOdoHalf100)))
			{
				$numOfSeries = $Chart->SeriesCollection->Count();
				if ($numOfSeries > 1)
				{
					if (count($Chart->SeriesCollection(2)->Values) > 0)
					{
						$minVal = $Chart->SeriesCollection(2)->Values[0];
						for ($i = 2; $i < ($numOfSeries + 1); $i++)
						{
							$seriesLen = count($Chart->SeriesCollection($i)->Values);
							for ($j = 0; $j < $seriesLen; $j++)
								if ($Chart->SeriesCollection($i)->Values[$j] != XLSConfig::NOVALUE)
									$minVal = min($minVal, $Chart->SeriesCollection($i)->Values[$j]);
						}

						return $minVal;
					}
				}
				else if (count($Chart->SeriesCollection(1)->Values) > 0)
				{
					$val = $Chart->SeriesCollection(1)->Values[0];
					$val = ($val) ? $val : (-9);
					$absVal = abs($val);
					$sign = $val / $absVal;
					$startExp = floor(log10(abs($val)));

					$numOfVals = count($Chart->SeriesCollection(1)->Values);
					for ($i = 1; $i < $numOfVals; $i++)
					{
						$val = $Chart->SeriesCollection(1)->Values[$i];
						$val = ($val) ? $val : (-10);
						$absVal = abs($val);
						$sign = min($val / $absVal, $sign);
						$startExp = max(floor(log10($absVal)), $startExp);
					}

					return (($sign == -1) ? $sign * pow(10, $startExp + 1) : 0);
				}
			}
		}

		return 0;
	}

	public static function getOdometerEnd(&$Chart, $refcontext = null, $path = null)
	{
		if (isset($Chart->Axes) && $Chart->Axes(1)->MaximumScaleIsAuto === false && !empty($Chart->Axes(1)->MaximumScale))
			return $Chart->Axes(1)->MaximumScale;
		else
		{
			if (!in_array($Chart->ChartType, array(XlChartType::xlMeterOdoFull100, XlChartType::xlMeterOdoHalf100)))
			{
				$numOfSeries = $Chart->SeriesCollection->Count();
				if ($numOfSeries > 1)
				{
					if (count($Chart->SeriesCollection(2)->Values) > 0)
					{
						$maxVal = $Chart->SeriesCollection(2)->Values[0];
						for ($i = 2; $i < ($numOfSeries + 1); $i++)
						{
							$seriesLen = count($Chart->SeriesCollection($i)->Values);
							for ($j = 0; $j < $seriesLen; $j++)
								if ($Chart->SeriesCollection($i)->Values[$j] != XLSConfig::NOVALUE)
									$maxVal = max($maxVal, $Chart->SeriesCollection($i)->Values[$j]);
						}

						return $maxVal;
					}
				}
				else if (count($Chart->SeriesCollection(1)->Values) > 0)
				{
					$val = $Chart->SeriesCollection(1)->Values[0];
					$val = ($val) ? $val : 9;

					$absVal = abs($val);
					$sign = $val / $absVal;
					$startExp = floor(log10(abs($val)));

					$numOfVals = count($Chart->SeriesCollection(1)->Values);
					for ($i = 1; $i < $numOfVals; $i++)
					{
						$val = $Chart->SeriesCollection(1)->Values[$i];
						$val = ($val) ? $val : 10;
						$absVal = abs($val);
						$sign = max($val / $absVal, $sign);
						$startExp = max(floor(log10($absVal)), $startExp);
					}

					return (($sign == -1) ? 0 : $sign * pow(10, $startExp+1));
				}
			}
		}

		return 100;
	}

	public static function getOdometerMajorTick(&$Chart, $refcontext = null, $path = null)
	{
		if (isset($Chart->Axes) && $Chart->Axes(1)->MajorUnitIsAuto === false && !empty($Chart->Axes(1)->MajorUnit))
			return $Chart->Axes(1)->MajorUnit;

		return ((in_array($Chart->ChartType, array(XlChartType::xlMeterOdoHalf, XlChartType::xlMeterOdoHalf100, XlChartType::xlMeterAngularWide)))
					? round((FormatConvertor::getOdometerEnd($Chart) - FormatConvertor::getOdometerStart($Chart)) / 5)
					: round((FormatConvertor::getOdometerEnd($Chart) - FormatConvertor::getOdometerStart($Chart)) / 10));
	}

	public static function getOdometerMinorTick(&$Chart, $refcontext = null, $path = null)
	{
		return ((isset($Chart->Axes) && $Chart->Axes(1)->MinorUnitIsAuto === false && !empty($Chart->Axes(1)->MinorUnit))
				? $Chart->Axes(1)->MinorUnit
				: round((FormatConvertor::getOdometerEnd($Chart) - FormatConvertor::getOdometerStart($Chart)) / 50));
	}

	public static function getOdometerMicroTick(&$Chart, $refcontext = null, $path = null)
	{
		// Micro ticks are hidden
		return 0;

//		return ($Chart->Axes(1)->MinorUnitIsAuto === false)
//				? round($Chart->Axes(1)->MinorUnit / 2)
//				: round((FormatConvertor::getOdometerEnd($Chart) - FormatConvertor::getOdometerStart($Chart)) / 100);
	}

	public static function getOdometerStartAngle(&$Chart, $refcontext = null, $path = null)
	{
		if (in_array($Chart->ChartType, array(XlChartType::xlMeterOdoFull100, XlChartType::xlMeterOdoFull)))
			return -135;
		else if (in_array($Chart->ChartType, array(XlChartType::xlMeterOdoHalf, XlChartType::xlMeterOdoHalf100)))
			return -90;
		else
			return -25;
	}

	public static function getOdometerEndAngle(&$Chart, $refcontext = null, $path = null)
	{
		return abs(FormatConvertor::getOdometerStartAngle($Chart));
	}

	public static function getLinearMeterTopY(&$Chart, $refcontext = null, $path = null)
	{
		return UnitConvertor::pointToPixel($Chart->PlotArea->InsideTop) + 10;
	}

	public static function getTickLabelAngle($angle)
	{
		if (abs($angle) <= 360)
			return (-$angle);

		switch ($angle)
		{
			case XlTickLabelOrientation::xlTickLabelOrientationAutomatic:
				return 0;
			case XlTickLabelOrientation::xlTickLabelOrientationDownward:
				return -90;
			case XlTickLabelOrientation::xlTickLabelOrientationHorizontal:
				return 0;
			case XlTickLabelOrientation::xlTickLabelOrientationUpward:
				return 90;
			case XlTickLabelOrientation::xlTickLabelOrientationVertical: // orientation where letters are one above other (not implemented yet)
				return 0;
			default:
				return 0;
		}
	}
}

?>