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
 * SVN: $Id: LookupValue.php 5025 2011-06-02 11:38:15Z mladent $
 *
 */

class LookupValue {

	// *** PRIVATE *** //

	private	function calc_stacked_data(&$sum_data, $data) {
	    if (count($sum_data) == 0) {
	        $sum_data = $data;
	        return;
	    }

	    for ($i = 0; $i < count($data); ++$i)
	        $sum_data[$i] = $sum_data[$i] + $data[$i];
	}

	private function calc_100per_data(&$data) {
	    for ($i = 0; $i < count($data[0]); ++$i) {
	        $pos_sum = 0;
	        for ($j = 0; $j < count($data); ++$j)
	            $pos_sum += $data[$j][$i];

	        $tmp_sum = 0;
	        for ($j = 0; $j < count($data); ++$j) {
	            $tmp_sum += $data[$j][$i] * 100 / $pos_sum;
	            $data[$j][$i] = $tmp_sum;
	        }
	    }
	}

	// *** PUBLIC *** //

	/**
	 * Retrieves current color palette from application environment.
	 * @access public
	 * @param string $palette the name of color palette. Default null.
	 * @return string returns the name of color palette variable.
	 **/
	public function getColorPalette() {
		return 'XLSConfig::$systemPalette';
	}

	public function setGridColor(&$Chart, $parent, $init = null, $args = null)
	{
		return '$' . $parent . '->' . $init . '(' . $args[0] . ', ' . $args[1] . ', $chart->dashLineColor(0x666666, DotLine), $chart->dashLineColor(0x666666, DotLine));' . "\n";
	}

	public function hasBranch(&$Chart, $path = null) {
		$hasObject = false;

		if (!is_null($path))
			eval('$hasObject = (boolean) $' . str_replace('.', '->', $path) . ';');

		if (isset(XLSConfig::$chartTypeConfig[$Chart->ChartType]['isMeter']) && ($path == 'Chart.HasLegend'))
			return false;
		// Some other processing on $Chart object that returns boolean value.

		return $hasObject;
	}

	public function hasLine(&$Chart, $path = null)
	{
		$hasLineObj = false;
		$curChartType = intval($Chart->ChartType + 0);

		switch ($curChartType)
		{
			case XlChartType::xlXYScatter:
			case XlChartType::xlBubble:
			case XlChartType::xlBubble3DEffect:
				break;

			default:
				$hasLineObj = true;
		}

		return $hasLineObj;
	}

	public function getLabelsRadar(&$Chart, $parent, $init = null, $args = null)
	{
		$catNames = 'array(';
		for ($i=0; $i<count($Chart->Axes(1)->CategoryNames); $i++)
			$catNames .= '\'' . $Chart->Axes(1)->CategoryNames[$i] . '\',';
		$catNames = substr($catNames, 0, -1) . ')';

		$retstr = '$var_' . $init . ' = $' . $parent . '->' . $init . '(' . $catNames . ');' . "\n";

		return $retstr;
	}

	public function swapXY(&$Chart, $path = null)
	{
		return isset(XLSConfig::$chartTypeConfig[$Chart->ChartType]['swapXY']);
	}

	public function getXAxisLabels(&$Chart, $parent, $init = null, $args = null)
	{
		$retstr = '';
		$chartType = intval($Chart->ChartType + 0);

		if ((!isset(XLSConfig::$chartTypeConfig[$chartType]['hasSpecAxisLbls'])) && ($parent == 'var_xAxis') && count($Chart->Axes(1)->CategoryNames) > 0)
		{
			$catNames = 'array(';
			for ($i=0; $i<count($Chart->Axes(1)->CategoryNames); $i++)
				$catNames .= '\'' . $Chart->Axes(1)->CategoryNames[$i] . '\',';
			$catNames = substr($catNames, 0, -1) . ')';

			$retstr = '$var_' . $init . ' = $' . $parent . '->' . $init . '(' . $catNames . ');' . "\n";

			if (in_array($Chart->ChartType, array(XlChartType::xlLineRotated, XlChartType::xlLineMarkersRotated)))
				$maxFreeW = $Chart->PlotArea->InsideLeft - XLSConfig::$configConst['wSpaceForAxes'];
			else
			{
				$paWidth = $Chart->ChartArea->Width * 0.90;

				// check if legend is visible
				$lOver = (isset($Chart->Legend->IncludeInLayout)) ? !$Chart->Legend->IncludeInLayout : false;
				$lPos = (isset($Chart->Legend->Position)) ? $Chart->Legend->Position : XlLegendPosition::xlLegendPositionRight;
				if ($Chart->HasLegend && !$lOver && in_array($lPos, array(XlLegendPosition::xlLegendPositionCustom, XlLegendPosition::xlLegendPositionCorner, XlLegendPosition::xlLegendPositionRight, XlLegendPosition::xlLegendPositionLeft)))
					$paWidth = $Chart->Legend->Left - $Chart->ChartArea->Width * 0.1;

				$maxFreeW = $paWidth / count($Chart->Axes(1)->CategoryNames);
			}

			$retstr .= '$var_' . $init . '->setTruncate(' . UnitConvertor::pointToPixel($maxFreeW) . ', 1);' . "\n";
		}

		return $retstr;
	}

	public function setXDataValues(&$Chart, $parent, $init = null, $args = null)
	{
		$chartType = intval($Chart->ChartType + 0);

		switch ($chartType)
		{
			case XlChartType::xlXYScatterSmooth:
			case XlChartType::xlXYScatterSmoothNoMarkers:
			case XlChartType::xlXYScatterLines:
			case XlChartType::xlXYScatterLinesNoMarkers:
				$retstr = '$var_' . $init . ' = $' . $parent . '->' . $init . '($this->Chart->SeriesCollection(1)->XValues);' . "\n";
				break;

			default:
				$retstr = '';
		}

		return $retstr;
	}

	public function setKeySize(&$Chart, $parent, $init = null, $args = null)
	{
		switch ($Chart->ChartType)
		{
			case XlChartType::xlLine:
			case XlChartType::xlLineRotated:
			case XlChartType::xlLineMarkers:
			case XlChartType::xlLineMarkersRotated:
			case XlChartType::xlLineMarkersStacked:
			case XlChartType::xlLineMarkersStacked100:
			case XlChartType::xlLineStacked:
			case XlChartType::xlLineStacked100:
			case XlChartType::xlRadar:
			case XlChartType::xlRadarMarkers:
				return $retstr = '$' . $parent . '->setKeySize(20, 4, 2);' . "\n";
				break;
			default:
				return $retstr = '$' . $parent . '->setKeySize(9, 9, 2);' . "\n";
		}
	}

	public function axis_setLinearScale(&$Chart, $parent, $init = null, $args = null)
	{
		$retstr = '';

		switch ($Chart->ChartType)
		{
			case XlChartType::xlLineMarkersStacked100:
			case XlChartType::xlLineStacked100:
				if ($parent == 'var_yAxis')
				{
					$retstr = '$' . $parent . '->' . $init . '(' . $args[0] . ', ' . $args[1] . ', ' . $args[2] . ', ' . $args[3] . ');' . "\n";
					$retstr .= '$' . $parent . '->setLabelFormat(\'{value} %\');' . "\n";
				}
				break;

			default:
				$retstr = '';
		}

		$axisId = ($parent == 'var_yAxis') ? 2 : 1;
		if (isset($Chart->Axes($axisId)->MaximumScaleIsAuto) && isset($Chart->Axes($axisId)->MinimumScaleIsAuto) && !$Chart->Axes($axisId)->MaximumScaleIsAuto && !$Chart->Axes($axisId)->MinimumScaleIsAuto)
		{
			$majorTick = ($Chart->Axes($axisId)->MajorUnitIsAuto) ? 0 : $Chart->Axes($axisId)->MajorUnit;
			$minorTick = ($Chart->Axes($axisId)->MinorUnitIsAuto) ? 0 : $Chart->Axes($axisId)->MinorUnit;
			$retstr = '$' . $parent . '->' . $init . '(' . $Chart->Axes($axisId)->MinimumScale . ', ' . $Chart->Axes($axisId)->MaximumScale . ', ' . $majorTick . ', ' . $minorTick . ');' . "\n";
		}


		return $retstr;
	}

	public function xAxisOnTop(&$Chart, $path = null) {
		if (!is_null($path))
		{
			eval('$xAxisPos = intval($' . str_replace('.', '->', $path) . ');');
			return ($xAxisPos == XlTickLabelPosition::xlTickLabelPositionHigh);
		}

		return false;
	}

	public function addAreaLayer(&$Chart, $parent, $init = null, $args = null)
	{
		$firstTime = true;
		$retstr = '';

		for ($i = 1; ($i <= $Chart->SeriesCollection->Count()) && $firstTime; $i++)
		{
			if ($Chart->SeriesCollection($i)->ChartType == XlChartType::xl3DArea)
			{
				$firstTime = false;
				$dataSetName = $Chart->SeriesCollection($i)->Name;

				$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Interior->Color);
				$retstr .= '$xl3DArea = $' . $parent . '->' . $init . '($this->Chart->SeriesCollection(' . $i . ')->Values, ' . $dataSetColor . ', "' . $dataSetName . '", ' . $args[3] . ');' . "\n";
				if ($Chart->SeriesCollection($i)->Border->LineStyle == Constants::xlSolid)
						$retstr .= '$xl3DArea->setBorderColor(' . FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color) . ');' . "\n";
			}
			else if ($Chart->SeriesCollection($i)->ChartType == XlChartType::xlArea)
			{
				$firstTime = false;
				$dataSetName = $Chart->SeriesCollection($i)->Name;

				$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Interior->Color);
				$retstr .= '$xlArea = $' . $parent . '->' . $init . '($this->Chart->SeriesCollection(' . $i . ')->Values, ' . $dataSetColor . ', "' . $dataSetName . '", ' . $args[3] . ');' . "\n";
				if ($Chart->SeriesCollection($i)->Border->LineStyle == Constants::xlSolid)
						$retstr .= '$xlArea->setBorderColor(' . FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color) . ');' . "\n";
			}
		}

		return $retstr;
	}

	public function addScatterLayer(&$Chart, $parent, $init = null, $args = null)
	{
		$firstTime = true;
		$retstr = '';

		for ($i = 1; ($i <= $Chart->SeriesCollection->Count()) && $firstTime; $i++)
		{
			if ($Chart->SeriesCollection($i)->ChartType == XlChartType::xlXYScatter)
			{
				$firstTime = false;
				$series = $Chart->SeriesCollection($i);
				$dataSetName = $series->Name;
				$markerSize = UnitConvertor::pointToPixel($series->MarkerSize);

				$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Interior->Color);
				$retstr .= '$xlXYScatter = $' . $parent . '->addScatterLayer($this->Chart->SeriesCollection(1)->XValues, $this->Chart->SeriesCollection(' . $i . ')->Values, "' . $dataSetName . '", 1, ' . $markerSize . ', ' . $dataSetColor . ', -1);' . "\n";
				if ($Chart->SeriesCollection($i)->Border->LineStyle == Constants::xlSolid)
					$retstr .= '$xlXYScatter->setBorderColor(' . FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color) . ');' . "\n";
			}
		}

		return $retstr;
	}

	public function addBubbleLayer(&$Chart, $parent, $init = null, $args = null)
	{
		$layer_type = (split('_', $args[0]));
		eval('$chartType = XlChartType::' . $layer_type[0] . ';');
		$layerID = $layer_type[1];

		$is3D = false;
		$retstr = '';
		$countLayers = 0;
		$addingDone = false;

		for ($i = 1; ($i <= $Chart->SeriesCollection->Count()) && (!$addingDone); $i++)
		{
			switch ($Chart->SeriesCollection($i)->ChartType)
			{
				case XlChartType::xlBubble3DEffect:
					$is3D = true;
				case XlChartType::xlBubble:
					if ($countLayers == $layerID)
					{
						$dataSetName = $Chart->SeriesCollection($i)->Name;

						$symbole_size_array = 'array(';
						for ($k = 0; $k < count($Chart->SeriesCollection($i+2)->Values); $k++)
						{
							$symbole_size_array .= (($Chart->SeriesCollection($i+2)->Values[$k] + 12) * 2.2);
							// this function is taken from prototype example -> (size+12)*2.2

							if ($k < count($Chart->SeriesCollection($i+2)->Values))
								$symbole_size_array .= ', ';
						}
						$symbole_size_array .= ')';

						$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Interior->Color);
						$retstr .= '$' . $args[0] . ' = $' . $parent . '->addScatterLayer($this->Chart->SeriesCollection(' . $i . ')->Values, $this->Chart->SeriesCollection(' . ($i + 1) . ')->Values, "' . $dataSetName . '", ' . $args[4] . ', 9, ' . $dataSetColor . ', ' .
							(($Chart->SeriesCollection($i)->Border->LineStyle == Constants::xlSolid) ? FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color) : $dataSetColor) . ');' . "\n";
						$retstr .= '$' . $args[0] . '->setSymbolScale(' . $symbole_size_array . ');' . "\n"; // $layer->setSymbolScale($values3);

						if ($is3D)
							$retstr .= '$' . $args[0] . '->getDataSet(0)->setDataSymbol(SolidSphereShape);' . "\n";

						$addingDone = true;
					}

					$countLayers++;
					$i += 2;
					break;
			}
		}

		return $retstr;
	}

	public function addOHLCLayer(&$Chart, $parent, $init = null, $args = null)
	{
		$firstTime = true;
		$retstr = '';

		for ($i = 1; ($i <= $Chart->SeriesCollection->Count()) && $firstTime; $i++)
		{
			switch ($Chart->SeriesCollection($i)->ChartType)
			{
				case XlChartType::xlStockOHLC:
					$retstr .= '$xlStockOHLC = $' . $parent . '->addCandleStickLayer($this->Chart->SeriesCollection(' . ($i+1) . ')->Values, $this->Chart->SeriesCollection(' . ($i+2) . ')->Values,  $this->Chart->SeriesCollection(' . $i . ')->Values,  $this->Chart->SeriesCollection(' . ($i+3) . ')->Values, 0xFFFFFF, 0x505050, LineColor);' . "\n";
					$firstTime = false;
					break;

				case XlChartType::xlStockHLC:
					$retstr .= '$xlStockHLC = $' . $parent . '->addHLOCLayer($this->Chart->SeriesCollection(' . $i . ')->Values, $this->Chart->SeriesCollection(' . ($i+1) . ')->Values, array(), $this->Chart->SeriesCollection(' . ($i+2) . ')->Values, -1);' . "\n";
					$firstTime = false;
					break;
			}
		}

		return $retstr;
	}

	public function addRadarLayer(&$Chart, $parent, $init = null, $args = null)
	{
		$layer_type = (split('_', $args[0]));
		eval('$chartType = XlChartType::' . $layer_type[0] . ';');
		$layerID = $layer_type[1];

		$retstr = '';
		$countLayers = 0;
		$addingDone = false;

		for ($i = 1; ($i <= $Chart->SeriesCollection->Count()) && (!$addingDone); $i++)
		{
			if ($Chart->SeriesCollection($i)->ChartType == $chartType)
			{
				if ($countLayers == $layerID)
				{
					$addingDone = true;
					$dataSetName = $Chart->SeriesCollection($i)->Name;
					$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Interior->Color);
					$retstr .= '$' . $args[0] . ' = $' . $parent . '->' . $init . '($this->Chart->SeriesCollection(' . $i . ')->Values, ' . $dataSetColor . ', \'' . $dataSetName . '\');' . "\n";
					if ($Chart->SeriesCollection($i)->Border->LineStyle == Constants::xlSolid)
						$retstr .= '$' . $args[0] . '->setBorderColor(' . FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color) . ');' . "\n";
					if ($chartType == XlChartType::xlRadarMarkers)
					{
						$markerSize = UnitConvertor::pointToPixel($Chart->SeriesCollection($i)->MarkerSize);
						$retstr .= '$' . $args[0] . '->setDataSymbol(' . ($layerID + 1) . ', ' . $markerSize . ', -1, 0xFF000000);' . "\n";
					}
				}
				else
					$countLayers++;
			}
		}

		return $retstr;
	}

	public function addPieDataSet(&$Chart, $parent, $init = null, $args = null)
	{
		$retstr = '';
		$i = 1;

		switch ($Chart->SeriesCollection($i)->ChartType)
		{
			case XlChartType::xl3DPieExploded:
			case XlChartType::xl3DPie:
			case XlChartType::xlDoughnut:
			case XlChartType::xlDoughnutExploded:
			case XlChartType::xlPieExploded:
			case XlChartType::xlPie:
				$retstr .= '$setData_' . $i . ' = $' . $parent . '->setData($this->Chart->SeriesCollection(' . $i . ')->Values, $this->Chart->SeriesCollection(' . $i . ')->XValues);' . "\n";
				// This part do explosion, color and label style for pie parts
				$partColors = 'array(';
				for ($k = 0, $numOfPoints = $Chart->SeriesCollection($i)->Points->Count(), $pieRadius = FormatConvertor::getPieRadius($Chart); $k < $numOfPoints; $k++)
				{
					$point = $Chart->SeriesCollection($i)->Points($k+1);

					// Explode
					$retstr .= '$' . $parent . '->setExplode(' . $k . ', ' . ( $pieRadius * ($point->Explosion / 100) ) . ');' . "\n";

					// Style for Labels
					$dataLabel = $point->DataLabel;
					$retstr .= '$sector_tb_' . $i . '_' . $k . ' = $' .$parent . '->sector(' . $k . ')->setLabelStyle(' . FormatConvertor::fontFileName($dataLabel->Font->Name) . ', ' . FormatConvertor::fontSize($dataLabel->Font) . ', ' . strval(FormatConvertor::RGBExcelToCD($dataLabel->Font->Color)) . ');' . "\n";
					$retstr .= '$sector_tb_' . $i . '_' . $k . '->setFontAngle(' . FormatConvertor::getTickLabelAngle($dataLabel->Orientation) . ');' . "\n";

					// generates DataColor palette
					if (isset($Chart->SeriesCollection($i)->Points($k+1)->Interior))
						$partColors .= strval(FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Points($k+1)->Interior->Color)) . ',';
				}
				$partColors = substr($partColors, 0, -1) . ')';
				$retstr .= '$' . $parent . '->setColors2(DataColor, ' . $partColors . ');' . "\n";
		}

		return $retstr;
	}

	public function addDataSets(&$Chart, $parent, $init = null, $args = null)
	{
		$layer_type = (split('_', $parent));
		eval('$chartType = XlChartType::' . $layer_type[0] . ';');

		switch ($chartType) {
			//case XlChartType:::
			case XlChartType::xlColumnClustered:
			case XlChartType::xlColumnStacked:
			case XlChartType::xlColumnStacked100:
			case XlChartType::xl3DColumnClustered:
			case XlChartType::xl3DColumnStacked:
			case XlChartType::xl3DColumnStacked100:

			case XlChartType::xlCylinderColClustered:
			case XlChartType::xlCylinderColStacked:
			case XlChartType::xlCylinderColStacked100:
			case XlChartType::xlCylinderBarClustered:
			case XlChartType::xlCylinderBarStacked:
			case XlChartType::xlCylinderBarStacked100:

			case XlChartType::xlBarClustered:
			case XlChartType::xlBarStacked:
			case XlChartType::xlBarStacked100:
			case XlChartType::xl3DBarClustered:
			case XlChartType::xl3DBarStacked:
			case XlChartType::xl3DBarStacked100:

			case XlChartType::xlAreaStacked:
			case XlChartType::xlAreaStacked100:
			case XlChartType::xl3DAreaStacked:
			case XlChartType::xl3DAreaStacked100:
			//case XlChartType:::
				return $this->addDataSet1($Chart, $parent, $chartType, $init, $args);
				break;

			case XlChartType::xlLine:
			case XlChartType::xlLineRotated:
			case XlChartType::xlLineMarkers:
			case XlChartType::xlLineMarkersRotated:
			case XlChartType::xl3DLine:

			case XlChartType::xlXYScatterLines:
			case XlChartType::xlXYScatterLinesNoMarkers:
			case XlChartType::xlXYScatterSmooth:
			case XlChartType::xlXYScatterSmoothNoMarkers:
				return $this->addDataSet2($Chart, $parent, $chartType, $init, $args);
				break;

			case XlChartType::xlLineStacked:
			case XlChartType::xlLineMarkersStacked:
				return $this->addDataSet3($Chart, $parent, $chartType, $init, $args);
				break;

			case XlChartType::xlLineStacked100:
			case XlChartType::xlLineMarkersStacked100:
				return $this->addDataSet4($Chart, $parent, $chartType, $init, $args);
				break;

			case XlChartType::xlArea:
			case XlChartType::xl3DArea:
				return $this->addDataSet5($Chart, $parent, $chartType, $init, $args);
				break;

			case XlChartType::xlXYScatter:
				return $this->addDataSet6($Chart, $parent, $chartType, $init, $args);
				break;

			default:
				return '';
				break;
		}
	}

	// xlColumn, xlBar, xlCylinder (2D nad 3D) types + xlAreaStacked (2D and 3D) types
	private function addDataSet1(&$Chart, $parent, $chartType, $init = null, $args = null)
	{
		$retstr = '';
		for ($i = 1; $i <= $Chart->SeriesCollection->Count(); $i++)
		{
			if ($Chart->SeriesCollection($i)->ChartType == $chartType)
			{
				$dataSetName = $Chart->SeriesCollection($i)->Name;

				$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Interior->Color);
				$retstr .= '$dataSet_' . $i . ' = $' . $parent . '->addDataSet($this->Chart->SeriesCollection(' . $i . ')->Values, ' . $dataSetColor . ', \'' . $dataSetName . '\');' . "\n";
				if ($Chart->SeriesCollection($i)->Border->LineStyle == Constants::xlSolid)
					$retstr .= '$dataSet_' . $i . '->setDataColor(' . $dataSetColor . ', ' . FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color) . ');' . "\n";
			}
		}

		return $retstr;
	}

	// xlLine, xlLineMarkers, xl3DLine, xlXYScatterLines, xlXYScatterLinesNoMarkers, xlXYScatterSmooth, xlXYScatterSmoothNoMarkers
	private function addDataSet2(&$Chart, $parent, $chartType, $init = null, $args = null)
	{
		$retstr = '';
		$markCounter = 1;

		for ($i = 1; $i <= $Chart->SeriesCollection->Count(); $i++)
		{
			if ($Chart->SeriesCollection($i)->ChartType == $chartType)
			{
				$dataSetName = $Chart->SeriesCollection($i)->Name;
				$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color);
				$retstr .= '$dataSet_' . $i . ' = $' . $parent . '->addDataSet($this->Chart->SeriesCollection(' . $i . ')->Values, ' . $dataSetColor . ', \'' . $dataSetName . '\');' . "\n";
				if (in_array($chartType, array(XlChartType::xlLineMarkers, XlChartType::xlLineMarkersRotated, XlChartType::xlXYScatterLines, XlChartType::xlXYScatterSmooth)))
				{
					$markerSize = UnitConvertor::pointToPixel($Chart->SeriesCollection($i)->MarkerSize);
					$retstr .= '$dataSet_' . $i . '->setDataSymbol(' . $markCounter++ . ', ' . $markerSize . ', -1, 0xFF000000);' . "\n";
				}
			}
		}

		return $retstr;
	}

	// xlLineMarkersStacked and xlLineStacked
	private function addDataSet3(&$Chart, $parent, $chartType, $init = null, $args = null)
	{
		$retstr = '';
		$markCounter = 1;
		$firstTime = true;

		for ($i = 1; $i <= $Chart->SeriesCollection->Count(); $i++)
		{
			if ($Chart->SeriesCollection($i)->ChartType == $chartType)
			{
				$series = $Chart->SeriesCollection($i);
				if ($firstTime)
				{
					$firstTime = false;
					$sum_data = array();
					for ($k=0; $k < count($series->Values); $k++)
						$sum_data[$k] = 0;
				}

				$dataSetName = $series->Name;
				$this->calc_stacked_data($sum_data, $series->Values);

				$arrayStr = 'array(';
				for ($k = 0; $k < count($series->Values); $k++)
				{
					$arrayStr .= $sum_data[$k];
					if ($k < (count($series->Values) - 1))
						$arrayStr .= ',';
				}
				$arrayStr .= ')';

				$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color);
				$retstr .= '$dataSet_' . $i . ' = $' . $parent . '->addDataSet(' . $arrayStr . ', ' . $dataSetColor . ', \'' . $dataSetName . '\');' . "\n";
				if ($chartType == XlChartType::xlLineMarkersStacked)
				{
					$markerSize = UnitConvertor::pointToPixel($Chart->SeriesCollection($i)->MarkerSize);
					$retstr .= '$dataSet_' . $i . '->setDataSymbol(' . $markCounter++ . ', ' . $markerSize . ', -1, 0xFF000000);' . "\n";
				}
			}
		}

		return $retstr;
	}

	// xlLineMarkersStacked100 and xlLineStacked100
	private function addDataSet4(&$Chart, $parent, $chartType, $init = null, $args = null)
	{
		$retstr = '';
		$markCounter = 1;
		$all_data = array();

		for ($i = 1, $j = 0; $i <= $Chart->SeriesCollection->Count(); $i++)
			if ($Chart->SeriesCollection($i)->ChartType == $chartType)
				$all_data[$j++] = $Chart->SeriesCollection($i)->Values;

		$this->calc_100per_data($all_data);

		for ($i = 1, $j = 0; $i <= $Chart->SeriesCollection->Count(); $i++)
		{
			if ($Chart->SeriesCollection($i)->ChartType == $chartType)
			{
				$series = $Chart->SeriesCollection($i);
				$dataSetName = $series->Name;

				$arrayStr = 'array(';
				for ($k = 0; $k < count($series->Values); $k++)
				{
					$arrayStr .= $all_data[$j][$k];
					if ($k < (count($series->Values) - 1))
						$arrayStr .= ',';
				}
				$arrayStr .= ')';
				$j++;

				$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color);
				$retstr .= '$dataSet_' . $i . ' = $' . $parent . '->addDataSet(' . $arrayStr . ', ' . $dataSetColor . ', \'' . $dataSetName . '\');' . "\n";
				if ($chartType == XlChartType::xlLineMarkersStacked100)
				{
					$markerSize = UnitConvertor::pointToPixel($Chart->SeriesCollection($i)->MarkerSize);
					$retstr .= '$dataSet_' . $i . '->setDataSymbol(' . $markCounter++ . ', ' . $markerSize . ', -1, 0xFF000000);' . "\n";
				}
			}
		}

		return $retstr;
	}

	// xlArea and xl3DArea
	private function addDataSet5(&$Chart, $parent, $chartType, $init = null, $args = null)
	{
		$retstr = '';
		$firstTime = true;

		for ($i = 1; $i <= $Chart->SeriesCollection->Count(); $i++)
		{
			if ($Chart->SeriesCollection($i)->ChartType == $chartType)
			{
				if (!$firstTime)
				{
					$dataSetName = $Chart->SeriesCollection($i)->Name;
					$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Interior->Color);
					$retstr .= '$dataSet_' . $i . ' = $' . $parent . '->addDataSet($this->Chart->SeriesCollection(' . $i . ')->Values, ' . $dataSetColor . ', \'' . $dataSetName . '\');' . "\n";
					if ($Chart->SeriesCollection($i)->Border->LineStyle == Constants::xlSolid)
						$retstr .= '$dataSet_' . $i . '->setDataColor(' . $dataSetColor . ', ' . FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Border->Color) . ');' . "\n";
				}
				else
					$firstTime = false;
			}
		}

		return $retstr;
	}

	// xlXYScatter
	private function addDataSet6(&$Chart, $parent, $chartType, $init = null, $args = null)
	{
		$retstr = '';
		$firstTime = true;
		$markCounter = 2; // this is because marker 1 is added when layer is added to chart

		for ($i = 1; $i <= $Chart->SeriesCollection->Count(); $i++)
		{
			if ($Chart->SeriesCollection($i)->ChartType == $chartType)
			{
				if (!$firstTime)
				{
					$dataSetName = $Chart->SeriesCollection($i)->Name;
					$dataSetColor = FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Interior->Color);
					$retstr .= '$dataSet_' . $i . ' = $' . $parent . '->addDataSet($this->Chart->SeriesCollection(' . $i . ')->Values, ' . $dataSetColor . ', \'' . $dataSetName . '\');' . "\n";
					$markerSize = UnitConvertor::pointToPixel($Chart->SeriesCollection($i)->MarkerSize);
					$retstr .= '$dataSet_' . $i . '->setDataSymbol(' . $markCounter++ . ', ' . $markerSize . ', -1, 0xFF000000);' . "\n";
				}
				else
					$firstTime = false;
			}
		}

		return $retstr;
	}

	// xlOdoMeter
	public function addZones(&$Chart, $parent, $init = null, $args = null)
	{
		$retstr = '';

		if ($Chart->SeriesCollection->Count() > 1)
		{
			$numOfSeries = $Chart->SeriesCollection->Count();
			$openedZone = false;
			for ($i = 2; $i <= $numOfSeries; $i++)
			{
				if (count($Chart->SeriesCollection($i)->Values) == 1 || $Chart->SeriesCollection($i)->Values[1] == XLSConfig::NOVALUE)
				{
					if ($openedZone)
						$retstr .= '$' . $parent . '->' . $init . '(' .
										'$this->Chart->SeriesCollection(' . ($i - 1) . ')->Values[0], ' .
										'$this->Chart->SeriesCollection(' . $i . ')->Values[0], ' .
										FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i - 1)->Interior->Color) .
										');' . "\n";

					$openedZone = true;
				}
				else if (count($Chart->SeriesCollection($i)->Values) >= 2)
				{
					if ($openedZone)
						$retstr .= '$' . $parent . '->' . $init . '(' .
										'$this->Chart->SeriesCollection(' . ($i - 1) . ')->Values[0], ' .
										'$this->Chart->SeriesCollection(' . $i . ')->Values[0], ' .
										FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i - 1)->Interior->Color) .
										');' . "\n";

					$retstr .= '$' . $parent . '->' . $init . '(' .
										'$this->Chart->SeriesCollection(' . $i . ')->Values[0], ' .
										'$this->Chart->SeriesCollection(' . $i . ')->Values[1], ' .
										FormatConvertor::RGBExcelToCD($Chart->SeriesCollection($i)->Interior->Color) .
										');' . "\n";

					$openedZone = false;
				}
			}
		}

		return $retstr;
	}

	public function addPointers(&$Chart, $parent, $init = null, $args = null)
	{
		$retstr = '';
		if (strpos($Chart->SeriesCollection(1)->Name, 'Series') !== 0)
		{
			if (in_array($Chart->ChartType, array(XlChartType::xlMeterLineHorizontal, XlChartType::xlMeterLineVertical)))
			{
				$retstr .='$' . $parent . '->addText(' . FormatConvertor::getOdometerCenterX($Chart) .
							', ' . (UnitConvertor::pointToPixel($Chart->ChartArea->Height)) . ', ' .
							'\'' . $Chart->SeriesCollection(1)->Name . '\', ' .
							'"CALIBRI.TTF", 15 , '.
							'TextColor, BottomCenter);' . "\n";
			}
			else
			{
				if (in_array($Chart->ChartType, array(XlChartType::xlMeterOdoFull100, XlChartType::xlMeterOdoFull)))
					$posAdjuster = FormatConvertor::getOdometerRadius($Chart) / 4;
				else if (in_array($Chart->ChartType, array(XlChartType::xlMeterOdoHalf, XlChartType::xlMeterOdoHalf100)))
					$posAdjuster = -FormatConvertor::getOdometerRadius($Chart) / 3;
				else
					$posAdjuster = -FormatConvertor::getOdometerRadius($Chart) + 40;

				$retstr .='$' . $parent . '->addText(' . FormatConvertor::getOdometerCenterX($Chart) .
							', ' . (FormatConvertor::getOdometerCenterY($Chart) + $posAdjuster) . ', ' .
							'\'' . $Chart->SeriesCollection(1)->Name . '\', ' .
							'"CALIBRI.TTF", 15 , '.
							'TextColor, Center);' . "\n";
			}
		}

		$numOfPoints = count($Chart->SeriesCollection(1)->Values);
		for ($i = 0; $i < $numOfPoints; $i++)
		{
			if ($Chart->SeriesCollection(1)->Values[$i] == XLSConfig::NOVALUE)
				break;

			$tmpPoint = $Chart->SeriesCollection(1)->Points($i+1);
			$pointColor = (isset($tmpPoint)) ? FormatConvertor::RGBExcelToCD($tmpPoint->Interior->Color) : $args[1];
			$pointBorderColor = (isset($tmpPoint)) ? FormatConvertor::RGBExcelToCD($tmpPoint->Border->Color) : $args[2];
			$retstr .= '$' . $parent . '->' . $init . '($this->Chart->SeriesCollection(1)->Values[' . $i . '], ' . $pointColor . ', ' . $pointBorderColor . ');' . "\n";
		}

		return $retstr;
	}

	public function addRings(&$Chart, $parent, $init = null, $args = null)
	{
		$retstr = '';

		if (($Chart->ChartType == XlChartType::xlMeterOdoFull) || ($Chart->ChartType == XlChartType::xlMeterOdoFull100))
		{
			$tmpR = FormatConvertor::getOdometerRadius($Chart);
			$retstr .= '$' . $parent . '->' . $init . '(' . ($tmpR + 2) . ', ' . ($tmpR + 3) . ', ' . $args[2] . ', ' . $args[3] . ');' . "\n";
		}

		return $retstr;
	}

	public function addRingSectors(&$Chart, $parent, $init = null, $args = null)
	{
		$retstr = '';

		if (($Chart->ChartType == XlChartType::xlMeterOdoHalf) || ($Chart->ChartType == XlChartType::xlMeterOdoHalf100))
		{
			$tmpR = FormatConvertor::getOdometerRadius($Chart);
			$retstr .= '$' . $parent . '->' . $init . '(' . ($tmpR + 2) . ', ' . ($tmpR + 3) . ', ' . $args[2] . ', ' . $args[3] . ', ' . $args[4] . ', ' . $args[5] . ');' . "\n";
		}

		return $retstr;
	}

	public function addLabels(&$Chart, $parent, $init = null, $args = null)
	{
		$retstr = '';

		if (in_array($Chart->ChartType, array(XlChartType::xlMeterOdoFull100, XlChartType::xlMeterOdoHalf100)) && ($majorTick = FormatConvertor::getOdometerMajorTick($Chart)) > 0)
		{
			for ($i=FormatConvertor::getOdometerStart($Chart); $i<=FormatConvertor::getOdometerEnd($Chart); $i+=$majorTick)
				$retstr .= '$' . $parent . '->' . $init . '(' . $i . ', \'' . $i . '%\');' . "\n";

			$retstr .= '$' . $parent . '->setLabelPos(true, 8);' . "\n";
		}

		return $retstr;
	}
}

?>