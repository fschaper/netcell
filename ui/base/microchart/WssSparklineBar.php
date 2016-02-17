<?php

/*
 * @brief ajax
 *
 * @file WssSparklineBar.php
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
 * SVN: $Id: WssSparklineBar.php 3631 2010-08-10 14:01:04Z mladent $
 *
 */

class WssSparklineBar extends Sparkline_Bar
{
	var $_trendColor;
	var $_firstShowNum;
	var $_trendLineShow;
	var $_lastShowNum;
	var $_minmaxShowNum;

	var $_min;
	var $_max;
	var $_fistNumber;
	var $_lastNumber;

	var $_scaling;
	var $_scalingMin;
	var $_scalingMax;
	var $_numOfScales;

	var $_fontSize;
	var $_fontType;

	var $_pxPerPt;

	function WssSparklineBar($data, $posValsColor, $negValsColor, $scaling, $scalingMin =0, $scalingMax =1)
	{
		parent::Sparkline_Bar();

		$this->_minmaxShowNum = false;
		$this->_lastShowNum = false;
		$this->_firstShowNum = false;
		$this->_trendLineShow = false;

		$this->_fontSize = 10; // this is in points
		$this->_pxPerPt = 1.4;
		$this->_fontType = 'arial';
		$this->_trendColor = 'black';
		$this->_numOfScales = null;

		$this->_scaling = $scaling;
		$this->_scalingMin = $scalingMin;
		$this->_scalingMax = $scalingMax;

		// add Colors
		$this->SetColorHtml('posValsColor', $posValsColor);
		$this->SetColorHtml('negValsColor', $negValsColor);

		$this->_min = array(0, $data[0]);
		$this->_max = array(0, $data[0]);
		$this->_fistNumber = $data[0];
		$this->_lastNumber = $data[count($data) - 1];

		// scaling (this need to be checked)
		// sacling = 0 [0..max]
		// scaling = 1 [min..max]
		// scaling = 2 [userdefined]
		if ($this->_scaling == 1)
		{
			$this->_scalingMin = min($data);
			$this->_scalingMax = max($data);

			if (($this->_sgnPos($this->_scalingMin) != $this->_sgnNeg($this->_scalingMax)) || ($this->_scalingMin == $this->_scalingMax))
				$this->_scaling = 0;
		}

		foreach ($data as $key => $value)
		{
			if ($this->_min[1] > $value)
				$this->_min = array($key, $value);
			else if ($this->_max[1] < $value)
				$this->_max = array($key, $value);

			if ($this->_scaling != 0)
			{
				if ($value < $this->_scalingMin)
				{
					$data[$key] = $this->_scalingMin;
					if ($this->_min[0] == $key)
						$this->_min = array($key, $this->_scalingMin);
				}

				if ($value > $this->_scalingMax)
				{
					$data[$key] = $this->_scalingMax;
					if ($this->_max[0] == $key)
						$this->_max = array($key, $this->_scalingMax);
				}
			}
		}

		$this->_numOfScales = abs($this->_scalingMax - $this->_scalingMin);
		if (($this->_sgnPos($this->_scalingMin) != $this->_sgnNeg($this->_scalingMax)) && ($this->_sgnPos($this->_scalingMin) == -1))
		{
			$tmpNum = $this->_scalingMin;
			$this->_scalingMin = $this->_scalingMax;
			$this->_scalingMax = $tmpNum;
		}

		if ($this->_scaling == 2)
		{
			$this->SetYMin($this->_scalingMin);
			$this->SetYMax($this->_scalingMax);
		}

		foreach($data as $key => $value)
		{
			if ($this->_scaling == 1)
				$value = (($this->_numOfScales / $this->_scalingMax) * ($value - $this->_scalingMin));

			if ($value >= 0)
				$this->setData($key, $value, 'posValsColor');
			else if ($value < 0)
				$this->setData($key, $value, 'negValsColor');
		}
	}

	function _preRender()
	{
		//
	}

	function _postRender()
	{
		// adding number to start of graph
		if ($this->_firstShowNum && (($this->_rotationAngle % 360) === 0))
		{
//			$firstLen = strlen(round($this->dataSeries[1][0]['value'], 2)) * imagefontwidth($this->_font) + 3;
			$firstLen = $this->_getFontStringWidth($this->_fontSize, 0,$this->_fontType, $this->_fistNumber . ' ');
			$imgTmp = imagecreatetruecolor(imagesx($this->imageHandle) + $firstLen, imagesy($this->imageHandle));

			if ($this->transparentBgColor)
			{
				imagecolortransparent($imgTmp, imagecolorallocate($imgTmp, 0, 0, 0));
				imagealphablending($imgTmp, false);
				imagesavealpha($imgTmp, true);
			}

			imagecopy($imgTmp, $this->imageHandle, $firstLen, 0, 0, 0, imagesx($this->imageHandle), imagesy($this->imageHandle));
			imagefilledrectangle($imgTmp, 0, 0, $firstLen - 1, imagesy($imgTmp), $this->GetColorHandle($this->colorBackground));

			$fontColor = $this->GetColorHandle('firstNumberColor');
			$strHeight = $this->_getFontStringHeight($this->_fontSize, 0, $this->_fontType, $this->_fistNumber);
			imagettftext($imgTmp, $this->_fontSize, 0, 1, $strHeight + (imagesy($imgTmp)/2 - $strHeight/2), $fontColor, $GLOBALS['ttf_paths'][$this->_fontType], $this->_fistNumber);
//			imagestring($imgTmp, $this->_font, 1, imagesy($imgTmp)/2 - imagefontheight($this->_font)/2, $this->_fistNumber, $fontColor);

			$this->imageHandle = $imgTmp;
		}

		// trend line
		if ($this->_trendLineShow && (($this->_rotationAngle % 360) === 0))
		{
//			$imgTmp = imagecreatetruecolor(imagesx($this->imageHandle) + imagesy($this->imageHandle), imagesy($this->imageHandle));

//			imagecopy($imgTmp, $this->imageHandle, 0, 0, 0, 0, imagesx($this->imageHandle), imagesy($this->imageHandle));
//			imagefilledrectangle($imgTmp, imagesx($this->imageHandle), 0, imagesx($this->imageHandle) + imagesy($this->imageHandle), imagesy($imgTmp), $this->GetColorHandle($this->colorBackground));

//			$fontColor = $this->GetColorHandle('lastNumberColor');
//			imagestring  ($imgTmp, $this->_font, 2 + imagesx($this->imageHandle), imagesy($imgTmp)/2 - imagefontheight($this->_font)/2, $this->dataSeries[1][count($this->dataSeries[1]) - 1]['value'], $fontColor);

			// TODO .. draw arrow for Trend Line

//			$this->imageHandle = $imgTmp;
		}

		// last number
		if ($this->_lastShowNum && (($this->_rotationAngle % 360) === 0))
		{
//			$lastLen = strlen(round($this->dataSeries[1][count($this->dataSeries[1]) - 1]['value'], 2)) * imagefontwidth($this->_font) + 3;
			$lastLen = $this->_getFontStringWidth($this->_fontSize, 0, $this->_fontType, $this->_lastNumber . ' ');
			$imgTmp = imagecreatetruecolor(imagesx($this->imageHandle) + $lastLen, imagesy($this->imageHandle));

			if ($this->transparentBgColor)
			{
				imagecolortransparent($imgTmp, imagecolorallocate($imgTmp, 0, 0, 0));
				imagealphablending($imgTmp, false);
				imagesavealpha($imgTmp, true);
			}

			imagecopy($imgTmp, $this->imageHandle, 0, 0, 0, 0, imagesx($this->imageHandle), imagesy($this->imageHandle));
			imagefilledrectangle($imgTmp, imagesx($this->imageHandle), 0, imagesx($this->imageHandle) + $lastLen, imagesy($imgTmp), $this->GetColorHandle($this->colorBackground));

			$fontColor = $this->GetColorHandle('lastNumberColor');
			$strHeight = $this->_getFontStringHeight($this->_fontSize, 0, $this->_fontType, $this->_lastNumber);
			imagettftext($imgTmp, $this->_fontSize, 0, 2 + imagesx($this->imageHandle), $strHeight + (imagesy($imgTmp)/2 - $strHeight/2), $fontColor, $GLOBALS['ttf_paths'][$this->_fontType], $this->_lastNumber);
//			imagestring  ($imgTmp, $this->_font, 2 + imagesx($this->imageHandle), imagesy($imgTmp)/2 - imagefontheight($this->_font)/2, $this->_lastNumber, $fontColor);

			$this->imageHandle = $imgTmp;
		}

		// min and max Numbers
		if ($this->_minmaxShowNum && (($this->_rotationAngle % 360) === 0))
		{

//			$minmaxLen = (strlen(round($this->_min[1], 2)) + strlen(round($this->_max[1], 2)) + 3) * imagefontwidth($this->_font) + 2;
			$minmaxLen = $this->_getFontStringWidth($this->_fontSize, 0, $this->_fontType, '[' . $this->_min[1] . '|' . $this->_max[1] . '] ');
			$imgTmp = imagecreatetruecolor(imagesx($this->imageHandle) + $minmaxLen, imagesy($this->imageHandle));

			if ($this->transparentBgColor)
			{
				imagecolortransparent($imgTmp, imagecolorallocate($imgTmp, 0, 0, 0));
				imagealphablending($imgTmp, false);
				imagesavealpha($imgTmp, true);
			}

			imagecopy($imgTmp, $this->imageHandle, 0, 0, 0, 0, imagesx($this->imageHandle), imagesy($this->imageHandle));
			imagefilledrectangle($imgTmp, imagesx($this->imageHandle), 0, imagesx($this->imageHandle) + $minmaxLen, imagesy($imgTmp), $this->GetColorHandle($this->colorBackground));

			$helpColor = $this->GetColorHandle('black');
			$minColor = $this->GetColorHandle('minNumberColor');
			$maxColor = $this->GetColorHandle('maxNumberColor');

			// [ min_val | max_val ] .. fe: [ -20 | 30 ]
			$strPos = 1 + imagesx($this->imageHandle);
			imagettftext($imgTmp, $this->_fontSize - 1, 0, $strPos, $this->_getFontStringHeight($this->_fontSize, 0, $this->_fontType, '['), $helpColor, $GLOBALS['ttf_paths'][$this->_fontType], '[');
//			imagestring($imgTmp, $this->_font, $strPos, imagesy($imgTmp)/2 - imagefontheight($this->_font)/2, '[', $helpColor);
			$strPos += $this->_getFontStringWidth($this->_fontSize, 0, $this->_fontType, '[') + 1;
			$strHeight = $this->_getFontStringHeight($this->_fontSize, 0, $this->_fontType, $this->_min[1]);
			imagettftext($imgTmp, $this->_fontSize, 0, $strPos, $strHeight + (imagesy($imgTmp)/2 - $strHeight/2), $minColor, $GLOBALS['ttf_paths'][$this->_fontType], $this->_min[1]);
//			imagestring($imgTmp, $this->_font, $strPos, imagesy($imgTmp)/2 - imagefontheight($this->_font)/2, $this->_min[1], $minColor);
			$strPos += $this->_getFontStringWidth($this->_fontSize, 0, $this->_fontType, $this->_min[1]) + 1;
			imagettftext($imgTmp, $this->_fontSize - 1, 0, $strPos, $this->_getFontStringHeight($this->_fontSize, 0, $this->_fontType, '|'), $helpColor, $GLOBALS['ttf_paths'][$this->_fontType], '|');
//			imagestring($imgTmp, $this->_font, $strPos, imagesy($imgTmp)/2 - imagefontheight($this->_font)/2, '|', $helpColor);
			$strPos += $this->_getFontStringWidth($this->_fontSize, 0, $this->_fontType, '|') + 1;
			$strHeight = $this->_getFontStringHeight($this->_fontSize, 0, $this->_fontType, $this->_min[1]);
			imagettftext($imgTmp, $this->_fontSize, 0, $strPos, $strHeight + (imagesy($imgTmp)/2 - $strHeight/2), $maxColor, $GLOBALS['ttf_paths'][$this->_fontType], $this->_max[1]);
//			imagestring($imgTmp, $this->_font, $strPos, imagesy($imgTmp)/2 - imagefontheight($this->_font)/2, $this->_max[1], $maxColor);
			$strPos += $this->_getFontStringWidth($this->_fontSize, 0, $this->_fontType, $this->_max[1]) + 1;
			imagettftext($imgTmp, $this->_fontSize - 1, 0, $strPos, $this->_getFontStringHeight($this->_fontSize, 0, $this->_fontType, ']'), $helpColor, $GLOBALS['ttf_paths'][$this->_fontType], ']');
//			imagestring($imgTmp, $this->_font, $strPos, imagesy($imgTmp)/2 - imagefontheight($this->_font)/2, ']', $helpColor);

			$this->imageHandle = $imgTmp;
		}

		// Do rotation
		if (($this->_rotationAngle % 360) != 0)
		{
			if (abs($this->_rotationAngle % 360) == 90)
				$this->_doRotation($this->_rotationAngle % 360);
		}
	}

	function Render($y)
	{
		$this->_preRender();
		parent::Render($y);
		$this->_postRender();
	}

	function setFontType($fontName)
	{
		$this->_fontType = $fontName;
	}

	function setFirstBarColor($color, $series=1)
	{
		$this->SetColorHtml('firstColor', $color);
		$this->dataSeries[$series][0]['color'] = 'firstColor';
	}

	function setLastBarColor($color, $series=1)
	{
		$this->SetColorHtml('lastColor', $color);
		$this->dataSeries[$series][count($this->dataSeries[$series]) - 1]['color'] = 'lastColor';
	}

	function setMinBarColor($color, $series=1)
	{
		$this->SetColorHtml('minColor', $color);
		$this->dataSeries[$series][$this->_min[0]]['color'] =  'minColor';
	}

	function setMaxBarColor($color, $series=1)
	{
		$this->SetColorHtml('maxColor', $color);
		$this->dataSeries[$series][$this->_max[0]]['color'] =  'maxColor';
	}

	function addFirstNumber($firstNumberColor)
	{
		$this->_firstShowNum = true;
		$this->SetColorHtml('firstNumberColor', $firstNumberColor);
	}

	function addLastNumber($lastNumberColor)
	{
		$this->_lastShowNum = true;
		$this->SetColorHtml('lastNumberColor', $lastNumberColor);
	}

	function addMinMaxNumber($minNumColor, $maxNumColor)
	{
		$this->_minmaxShowNum = true;
		$this->SetColorHtml('minNumberColor', $minNumColor);
		$this->SetColorHtml('maxNumberColor', $maxNumColor);
	}

	function _linearRegression($series =1)
	{
		$xSum = $ySum = $xxSum = $xySum = 0;
		$n = count($this->dataSeries[$series]);

		for ($i=0; $i<$n; $i++)
		{
			$xSum += $i;
			$ySum += $this->dataSeries[$series][$i]['value'];
			$xxSum += ($i * $i);
			$xySum += ($i * $this->dataSeries[$series][$i]['value']);
		}

		// slope
		$a = (($n * $xySum) - ($xSum * $ySum)) / (($n * $xxSum) - ($xSum * $xSum));

		// y intercept
		$b = ($ySum - ($a * $xSum)) / $n;

		return array('a' => $a, 'b' => $b);
	}

	function addTrendLine($trendLineColor)
	{
		$this->_trendLineShow = true;
		$this->SetColorHtml('trendLineColor', $trendLineColor);
	}

	function setFontPixelSize($pixels)
	{
		$this->_fontSize = $pixels / $this->_pxPerPt;
	}

	function _sgnPos($val)
	{
		if ($val >= 0)
			return 1;
		else
			return -1;
	}

	function _sgnNeg($val)
	{
		if ($val > 0)
			return 1;
		else
			return -1;
	}

	function _getFontStringWidth($fontSize, $angle, $fontType, $string)
	{
			$strCordSize = imagettfbbox($fontSize, $angle, $GLOBALS['ttf_paths'][$fontType], $string);
			return abs($strCordSize[2]) + abs($strCordSize[0]);
	}

	function _getFontStringHeight($fontSize, $angle, $fontType, $string)
	{
			$strCordSize = imagettfbbox($fontSize, $angle, $GLOBALS['ttf_paths'][$fontType], $string);
			return abs($strCordSize[5]);
	}
}

?>