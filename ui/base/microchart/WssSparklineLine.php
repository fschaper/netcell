<?php

/*
 * @brief ajax
 *
 * @file WssSparklineLine.php
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
 * SVN: $Id: WssSparklineLine.php 3631 2010-08-10 14:01:04Z mladent $
 *
 */

class WssSparklineLine extends Sparkline_Line
{
	var $_trendColor;
	var $_firstShowNum;
	var $_trendShowNum;
	var $_lastShowNum;
	var $_minmaxShowNum;
	var $_maxShowNum;

	var $_min;
	var $_max;
	var $_firstNumber;
	var $_lastNumber;

	var $_scaling;
	var $_scalingMin;
	var $_scalingMax;

	var $_fontSize;
	var $_fontType;
	var $_pointSize;
	var $_hasLine;
	var $_hasDots;
	var $_pointSpacing;

	var $_pxPerPt;

	function WssSparklineLine($data, $scaling =0, $scalingMin =0, $scalingMax =1)
	{
		parent::Sparkline_Line();

		$this->_minmaxShowNum = false;
		$this->_lastShowNum = false;
		$this->_firstShowNum = false;

		$this->_pointSize = 3;
		$this->_fontSize = 10; // this is in points
		$this->_pxPerPt = 1.4;
		$this->_fontType = 'arial';
		$this->_hasLine = true;
		$this->_hasDots = false;
		$this->_pointSpacing = 2;

		$this->_scaling = $scaling;
		$this->_scalingMin = $scalingMin;
		$this->_scalingMax = $scalingMax;

		$this->_min = array(0, $data[0]);
		$this->_max = array(0, $data[0]);
		$this->_firstNumber = $data[0];
		$this->_lastNumber = $data[count($data) - 1];

		if ((abs($this->_scalingMin) != $this->_scalingMin) && (abs($this->_scalingMax) != $this->_scalingMax))
		{
			if ($this->_scalingMin > $this->_scalingMax)
			{
				$tmpNum = $this->_scalingMin;
				$this->_scalingMin = $this->_scalingMax;
				$this->_scalingMax = $tmpNum;
			}
		}

		// scaling (this need to be checked)
		// sacling = 0 [0..max]
		// scaling = 1 [min..max]
		// scaling = 2 [userdefined]
		foreach ($data as $key => $value)
		{
			if ($this->_min[1] > $value)
				$this->_min = array($key, $value);
			else if ($this->_max[1] < $value)
				$this->_max = array($key, $value);

			if ($this->_scaling == 2)
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

		foreach($data as $key => $value)
		{
			$this->setData($key, $value);
		}

		/*
		if ($this->_scaling == 2)
		{
			$this->SetYMin($this->_scalingMin);
			$this->SetYMax($this->_scalingMax);
		}
		*/

		$this->_trendColor = $trendColor;
		$this->_trendShowNum = $trendShowNum;
	}

	function Render($x, $y, $resampling =false)
	{
		$this->_preRender();
		parent::Render($x, $y);

		if (!$resampling)
			$this->_postRender();
	}

	function RenderResampled($x, $y)
	{
		$this->_preRender();
		parent::RenderResampled($x, $y);
		$this->_postRender();
	}

	function RenderFullResampled($x, $y)
	{
		$highestDot = array($this->featurePoint[0]['ptX'], $this->featurePoint[0]['ptY'], $this->featurePoint[0]['diameter']);
		$lowestDot = array($this->featurePoint[0]['ptX'], $this->featurePoint[0]['ptY'], $this->featurePoint[0]['diameter']);

		for ($i=0; $i < count($this->featurePoint); $i++)
		{
			if ($highestDot[1] < $this->featurePoint[$i]['ptY'])
				$highestDot = array($this->featurePoint[$i]['ptX'], $this->featurePoint[$i]['ptY'], $this->featurePoint[$i]['diameter']);

			if ($lowestDot[1] > $this->featurePoint[$i]['ptY'])
				$lowestDot = array($this->featurePoint[$i]['ptX'], $this->featurePoint[$i]['ptY'], $this->featurePoint[$i]['diameter']);

			$this->featurePoint[$i]['diameter'] *= 4;
		}

		$this->SetPadding((($highestDot[2] > $lowestDot[2]) ? ($highestDot[2]/2) : ($lowestDot[2]/2)) * 4);

		$this->SetLineSize($this->GetLineSize() * 3);

		$this->Render($x * 4, $y * 4, true);
		$this->_resampleAll($x, $y);

		$this->_postRender();
	}

	function RenderDots($y)
	{
		$x = ($this->_pointSpacing + $this->_pointSize) * count($this->dataSeries[1]);
		$this->Render($x, $y);
	}

	function RenderDotsResampled($y)
	{
		$x = ($this->_pointSpacing + $this->_pointSize) * count($this->dataSeries[1]);
		$this->RenderFullResampled($x, $y);
	}

	function _resampleAll($x, $y)
	{
		$tmpImgHandle = imagecreatetruecolor($x, $y);

		imagecolortransparent($tmpImgHandle, imagecolorallocate($tmpImgHandle, 0, 0, 0));
		imagealphablending($tmpImgHandle, false);
		imagesavealpha($tmpImgHandle, true);

		imagecopyresampled($tmpImgHandle,  // dest handle
                           $this->imageHandle,  // src  handle
                           0, 0,  // dest x, y
                           0, 0,  // src  x, y
                           imagesx($tmpImgHandle), imagesy($tmpImgHandle),   // dest w, h
						   imagesx($this->imageHandle), imagesy($this->imageHandle)); // src  w, h

		$this->imageHandle = $tmpImgHandle;
	}

	function _preRender()
	{
		if (!$this->_hasLine)
			$this->lineColor = $this->_colorBackground;
	}

	function _postRender()
	{
		// adding number to start of graph
		if ($this->_firstShowNum && (($this->_rotationAngle % 360) === 0))
		{
//			$firstLen = strlen(round($this->dataSeries[1][0]['value'], 2)) * imagefontwidth($this->_font) + 3;
			$firstLen = $this->_getFontStringWidth($this->_fontSize, 0, $this->_fontType, $this->_firstNumber . ' ');
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
			$strHeight = $this->_getFontStringHeight($this->_fontSize, 0, $this->_fontType, $this->_firstNumber);
			imagettftext($imgTmp, $this->_fontSize, 0, 1, $strHeight + (imagesy($imgTmp)/2 - $strHeight/2), $fontColor, $GLOBALS['ttf_paths'][$this->_fontType], $this->_firstNumber);
//			imagestring($imgTmp, $this->_font, 1, imagesy($imgTmp)/2 - imagefontheight($this->_font)/2, $this->_firstNumber, $fontColor);

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

	function setFontType($fontName)
	{
		$this->_fontType = $fontName;
	}

	function setPointSize($val)
	{
		$this->_pointSize = $val;
	}

	function setFirstPointColor($color, $pointSize =null, $series =1)
	{
		$this->SetColorHtml('firstColor', $color);
		$this->SetFeaturePoint(0, $this->dataSeries[$series][0], 'firstColor', (($pointSize != null) ? $pointSize : $this->_pointSize));
	}

	function setLastPointColor($color, $pointSize =null, $series=1)
	{
		$this->SetColorHtml('lastColor', $color);
		$this->SetFeaturePoint(count($this->dataSeries[$series]) - 1, $this->dataSeries[$series][count($this->dataSeries[$series]) - 1], 'lastColor',  (($pointSize != null) ? $pointSize : $this->_pointSize));
	}

	function setMinPointColor($color, $pointSize =null, $series=1)
	{
		$this->SetColorHtml('minColor', $color);
		$this->SetFeaturePoint($this->_min[0], $this->dataSeries[$series][$this->_min[0]], 'minColor',  (($pointSize != null) ? $pointSize : $this->_pointSize));
	}

	function setMaxPointColor($color, $pointSize =null, $series=1)
	{
		$this->SetColorHtml('maxColor', $color);
		$this->SetFeaturePoint($this->_max[0], $this->dataSeries[$series][$this->_max[0]], 'maxColor',  (($pointSize != null) ? $pointSize : $this->_pointSize));
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

	function addDots($posValsColor, $negValsColor, $pointSize =null, $series =1)
	{
		// add Colors
		$this->SetColorHtml('posValsColor', $posValsColor);
		$this->SetColorHtml('negValsColor', $negValsColor);

		$dotSize = (($pointSize != null) ? $pointSize : $this->_pointSize);
		foreach ($this->dataSeries[$series] as $key => $value)
		{
			if ($value >= 0)
				$this->SetFeaturePoint($key, $value, 'posValsColor',  $dotSize);
			else if ($value < 0)
				$this->SetFeaturePoint($key, $value, 'negValsColor',  $dotSize);
		}

		$this->_hasDots = true;
	}

	function setPointSpacing($pixels)
	{
		$this->_pointSpacing = $pixels;
	}

	function hideLine()
	{
		$this->_hasLine = false;
	}

	function setLineColor($val)
	{
		if ($this->_hasLine)
  			$this->lineColor = $val;
	}

	function setFontPixelSize($pixels)
	{
		$this->_fontSize = $pixels / $this->_pxPerPt;
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