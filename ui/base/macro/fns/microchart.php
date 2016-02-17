<?PHP

/*
 * \brief microchart spreadsheet functions
 *
 * \file microchart.php
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
 * SVN: $Id: microchart.php 4125 2010-10-23 14:05:22Z predragm $
 *
 */

// +++ Auxiliary Functions +++ //
function _phpGetArrayFromRange ($range)
{
	if (!is_array($range))
		return array($range);

	if (is_array($range[0])) // Core3
		foreach ($range as &$row)
			foreach ($row as &$val)
				$res[] = is_numeric($val) ? $val : 0;
	else // Core2
		foreach ($range as &$val)
			$res[] = is_numeric($val) ? $val : 0;

	return $res;
}

function _phpGetNumValue($valueRange)
{
	if (is_string($valueRange))
	{
		$tmpArr = _phpGetArrayFromRange($valueRange);
		return $tmpArr[0];
	}
	else if (is_array($valueRange))
		return $valueRange[0];
	else
		return $valueRange;
}

function _getCellFormat()
{
	// default values are set in other functions to (in case of change it should be checked)
	$outStyles = array('color' => '#000000', 'font-size' => '11pt', 'font-weight' => 'normal');

	$stylesStr = activerange()->style();

	if (is_array($stylesStr))
		$stylesStr = $stylesStr[0][0];

	$styles = explode(';', $stylesStr);
	for ($i=0; $i<count($styles); $i++)
	{
		$styleParts = explode(':', $styles[$i]);
		if ($styleParts[0] != '')
			$outStyles[trim($styleParts[0])] = trim($styleParts[1]);
	}

	return $outStyles;
}

function _getMicroChartHeight($styles)
{
	$pt2px = 1.35;
	return ((isset($styles['font-size'])) ? $pt2px * intval(substr($styles['font-size'], 0, -2)) : $pt2px*11);
}

function _getFontWeight($styles)
{
	return ((isset($styles['font-weight'])) ? $styles['font-weight'] : 'normal');
}

function _getFontColor($styles)
{
	return ((isset($styles['color'])) ? $styles['color'] : '#000000');
}
// --- Auxiliary Functions --- //

// *** Monochrome *** //
// +++ Bars +++ //
function _reqBarFiles()
{
	// base and lib folders are added to include_path
	require('microchart/WssSparkConfig.php');

	require('sparkline/Object.php');
	require('sparkline/SparklineClass.php');
	require('sparkline/Sparkline_Bar.php');
	require('microchart/WssSparklineBar.php');
	require('microchart/WssSpark.php');
}

function Sparkbars($source)
{
	_reqBarFiles();
	$styles = _getCellFormat();
	$spark = new SparkBars(_phpGetArrayFromRange($source),	_getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0);
	return $spark->OutputToHTML();
}

function SparkbarsScaled($scalingMin, $scalingMax, $source)
{
	_reqBarFiles();
	$styles = _getCellFormat();
	$spark = new SparkBars(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 2, $scalingMin, $scalingMax);
	return $spark->OutputToHTML();
}

function SparkbarsScaledMM($source)
{
	_reqBarFiles();
	$styles = _getCellFormat();
	$spark = new SparkBars(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 1);
	return $spark->OutputToHTML();
}
// --- Bars --- //

// +++ Lines +++ //
function _reqLineFiles()
{
	// base and lib folders are added to include_path
	require('microchart/WssSparkConfig.php');

	require('sparkline/Object.php');
	require('sparkline/SparklineClass.php');
	require('sparkline/Sparkline_Line.php');
	require('microchart/WssSparklineLine.php');
	require('microchart/WssSpark.php');
}

function Sparkline($source)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLine(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 0, 1);
	return $spark->OutputToHTML();
}

function SparklineScaled($scalingMin, $scalingMax, $source)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLine(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 0, 1, 2, $scalingMin, $scalingMax);
	return $spark->OutputToHTML();
}

function SparklineScaledMM($source)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLine(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 0, 1, 1);
	return $spark->OutputToHTML();
}
// --- Lines --- //

// +++ Dots +++ //
function Sparkdots($source)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLine(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 1, 0);
	return $spark->OutputToHTML();
}

function SparkdotsScaled($scalingMin, $scalingMax, $source)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLine(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 1, 0, 2, $scalingMin, $scalingMax);
	return $spark->OutputToHTML();
}

function SparkdotsScaledMM($source)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLine(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 1, 0, 1);
	return $spark->OutputToHTML();
}
// --- Dots --- //

// +++ LineDots +++ //
function SparklineDots($source)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLine(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 1, 1);
	return $spark->OutputToHTML();
}

function SparklineDotsScaled($scalingMin, $scalingMax, $source)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLine(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 1, 1, 2, $scalingMin, $scalingMax);
	return $spark->OutputToHTML();
}

function SparklineDotsScaledMM($source)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLine(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0, 1, 1, 1);
	return $spark->OutputToHTML();
}
// --- LineDots --- //

// +++ Pie +++ //
function _reqPieFiles()
{
	require('microchart/WssSparkConfig.php');

	require('microchart/WssSparklinePie.php');
	require('microchart/WssSpark.php');
}

function Sparkpie($source)
{
	_reqPieFiles();
	$styles = _getCellFormat();
	$spark = new SparkPieColored(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), 0, _getFontColor($styles));
	return $spark->OutputToHTML();
}
// --- Pie --- //

// +++ Whisker +++ //
function _reqWhiskerFiles()
{
	require('microchart/WssSparkConfig.php');

	require('sparkline/Object.php');
	require('sparkline/SparklineClass.php');
	require('sparkline/Sparkline_Bar.php');
	require('microchart/WssSparklineBar.php');
	require('microchart/WssSparklineWhisker.php');
	require('microchart/WssSpark.php');
}

function Sparkwhisker($source)
{
	_reqWhiskerFiles();
	$styles = _getCellFormat();
	$spark = new SparkWhisker(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), _getFontColor($styles), 0);
	return $spark->OutputToHTML();
}
// --- Whisker --- //

// *** COLORED *** //
function SparkbarsColored($source, $target, $colorPos, $colorNeg, $colorFirst, $colorLast, $colorTrend, $colorMin, $colorMax, $showFirst, $showTrend, $showLast, $showMinMax, $scaling, $scalingMin, $scalingMax)
{
	_reqBarFiles();
	$styles = _getCellFormat();
	$spark = new SparkBarsColored(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), 0,
			getMcColor($colorPos), getMcColor($colorNeg), getMcColor($colorFirst), getMcColor($colorLast), getMcColor($colorTrend), getMcColor($colorMin), getMcColor($colorMax),
			$showFirst, $showTrend, $showLast, $showMinMax, $scaling, _phpGetNumValue($scalingMin), _phpGetNumValue($scalingMax));
	return $spark->OutputToHTML();
}

function SparklineColored($source, $target, $colorPos, $colorNeg, $colorFirst, $colorLast, $colorTrend, $colorMin, $colorMax, $showFirst, $showTrend, $showLast, $showMinMax, $scaling, $scalingMin, $scalingMax)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLineColored(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), 0, 0, 1,
			getMcColor($colorPos), getMcColor($colorNeg), getMcColor($colorFirst), getMcColor($colorLast), getMcColor($colorTrend), getMcColor($colorMin), getMcColor($colorMax),
			$showFirst, $showTrend, $showLast, $showMinMax, $scaling, _phpGetNumValue($scalingMin), _phpGetNumValue($scalingMax));
	return $spark->OutputToHTML();
}

function SparkdotsColored($source, $target, $colorPos, $colorNeg, $colorFirst, $colorLast, $colorTrend, $colorMin, $colorMax, $showFirst, $showTrend, $showLast, $showMinMax, $scaling, $scalingMin, $scalingMax)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLineColored(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), 0, 1, 0,
			getMcColor($colorPos), getMcColor($colorNeg), getMcColor($colorFirst), getMcColor($colorLast), getMcColor($colorTrend), getMcColor($colorMin), getMcColor($colorMax),
			$showFirst, $showTrend, $showLast, $showMinMax, $scaling, _phpGetNumValue($scalingMin), _phpGetNumValue($scalingMax));
	return $spark->OutputToHTML();
}

function SparklinedotsColored($source, $target, $colorPos, $colorNeg, $colorFirst, $colorLast, $colorTrend, $colorMin, $colorMax, $showFirst, $showTrend, $showLast, $showMinMax, $scaling, $scalingMin, $scalingMax)
{
	_reqLineFiles();
	$styles = _getCellFormat();
	$spark = new SparkLineColored(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), 0, 1, 1,
			getMcColor($colorPos), getMcColor($colorNeg), getMcColor($colorFirst), getMcColor($colorLast), getMcColor($colorTrend), getMcColor($colorMin), getMcColor($colorMax),
			$showFirst, $showTrend, $showLast, $showMinMax, $scaling, _phpGetNumValue($scalingMin), _phpGetNumValue($scalingMax));
	return $spark->OutputToHTML();
}

function SparkpieColored($source, $target, $colorPie)
{
	_reqPieFiles();
	$styles = _getCellFormat();
	$spark = new SparkPieColored(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), 0, $colorPie);
	return $spark->OutputToHTML();
}

function SparkwhiskerColored($source, $target, $colorWin, $colorTie, $colorLose)
{
	_reqWhiskerFiles();
	$styles = _getCellFormat();
	$spark = new SparkWhiskerColored(_phpGetArrayFromRange($source), _getMicroChartHeight($styles), _getFontWeight($styles), 0, $colorWin, $colorLose, $colorTie);
	return $spark->OutputToHTML();
}

?>