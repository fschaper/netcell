<?PHP

/*
 * @brief ajax
 *
 * @file WssSpark.php
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
 * SVN: $Id: WssSpark.php 3631 2010-08-10 14:01:04Z mladent $
 *
 */

// adding path for fonts
$configVals = new WssSparkConfig();
setFontPaths($configVals->getVal('fontPath'));

// Function used to add font paths
function setFontPaths($path)
{
	if (!isset($GLOBALS['ttf_paths']))
		$GLOBALS['ttf_paths'] = array();

	$dir = opendir(realpath($path));//directory with fonts
	if ($dir)
	{
		while ($f = readdir($dir))
		{
			if(preg_match('/\.ttf$/',$f))
			{
				$font = explode('.',$f);
				$GLOBALS['ttf_paths'][$font[0]] = realpath($path . $f);
			}
		}

		closedir($dir);
	}
}

function getMcColor($color)
{
	return ((is_numeric($color)) ? WssSparkConfig::$mcColorPalette[abs((($color) ? $color : 1) - 1) % count(WssSparkConfig::$mcColorPalette)] : $color);
}

class SparkBars
{
	var $_spark;

	function SparkBars($data, $imgHeight, $fontFomatType, $color, $direction, $scaling =0, $scalingMin =0, $scalingMax =1)
	{
		$configVals = new WssSparkConfig();
		$configVals = $configVals->getAllVals();

		$this->_spark = new WssSparklineBar($data, $color, $color, $scaling, $scalingMin, $scalingMax);
		$this->_spark->SetDebugLevel(DEBUG_NONE);

		if ($configVals['bgColorTransparent'])
			$this->_spark->SetTransparentBgColor();
		else
		{
			$this->_spark->SetColorHtml('bgcolor', $configVals['bgColorRGB']);
			$this->_spark->SetColorBackground('bgcolor');
		}

		$this->_spark->setRotationAngle($direction);

		$barSize = floor(($imgHeight * ($configVals['barSazeInPersentsOfHeight'] + (($fontFomatType == 'bold') ? $configVals['boldIncrease'] : 0))) / 100);
		$barSpace = floor(($imgHeight * $configVals['barSpaceInPersentsOfHeight']) / 100);

		$barSize = ($barSize < $configVals['minBarSize']) ? $configVals['minBarSize'] : $barSize;
		$barSpace = ($barSpace < $configVals['minBarSpace']) ? $configVals['minBarSpace'] : $barSpace;

		$this->_spark->setBarWidth($barSize);
		$this->_spark->setBarSpacing($barSpace);

		$this->_spark->Render($imgHeight);
	}

	function output($file ='')
	{
//		$this->_spark->Output($file);
		$this->_spark->Output();
	}

	function OutputToHTML()
	{
		return $this->_spark->OutputToHTML();
	}
}

class SparkLine
{
	var $_spark;

	function Sparkline($data, $imgHeight, $fontFomatType, $color, $direction, $hasDots, $hasLine, $scaling =0, $scalingMin =0, $scalingMax =1)
	{
		$configVals = new WssSparkConfig();
		$configVals = $configVals->getAllVals();

		$this->_spark = new WssSparklineLine($data, $scaling, $scalingMin, $scalingMax);
		$this->_spark->SetDebugLevel(DEBUG_NONE);

		if ($configVals['bgColorTransparent'])
			$this->_spark->SetTransparentBgColor();
		else
		{
			$this->_spark->SetColorHtml('bgcolor', $configVals['bgColorRGB']);
			$this->_spark->SetColorBackground('bgcolor');
		}

		$this->_spark->setRotationAngle($direction);

		$this->_spark->SetColorHtml('lineColor', $color);
		$this->_spark->setLineColor('lineColor');

		$dotSize = floor(($imgHeight * ($configVals['dotSazeInPersentsOfHeight'] + (($fontFomatType == 'bold') ? $configVals['boldIncrease'] : 0))) / 100);
		$dotSpace = floor(($imgHeight * $configVals['dotSpaceInPersentsOfHeight']) / 100);
		$dotSize = ($dotSize < $configVals['minDotSize']) ? $configVals['minDotSize'] : $dotSize;
		$dotSpace = ($dotSpace < $configVals['minDotSpace']) ? $configVals['minDotSpace'] : $dotSpace;
		$this->_spark->setPointSize($dotSize);

		if ($hasDots)
			$this->_spark->addDots($color, $color);

		if (!$hasLine)
			$this->_spark->hideLine();

		// adjust imagesize
		$imgWidth = count($data) * ($dotSize + $dotSpace);

		if (($direction == 0) || (!($configVals['bgColorTransparent'])))
			$this->_spark->RenderFullResampled(($imgWidth - 2), $imgHeight);
		else
			$this->_spark->Render(($imgWidth - 2), $imgHeight);
	}

	function output($file ='')
	{
//		$this->_spark->Output($file);
		$this->_spark->Output();
	}

	function OutputToHTML()
	{
		return $this->_spark->OutputToHTML();
	}
}

class SparkWhisker extends SparkWhiskerColored
{
	function SparkWhisker($data, $imgHeight, $fontFomatType, $color, $direction)
	{
		$configVals = new WssSparkConfig();
		$configVals = $configVals->getAllVals();

		parent::SparkWhiskerColored($data, $imgHeight, $fontFomatType, $direction, $color, $color, $color);
	}
}

class SparkWhiskerColored
{
	var $_spark;

	function SparkWhiskerColored($data, $imgHeight, $fontFomatType, $direction, $colorPos, $colorNeg, $colorTie)
	{
		$configVals = new WssSparkConfig();
		$configVals = $configVals->getAllVals();

//		$this->_spark = new WssSparklineWhisker($data, $configVals['posColorRGB'], $configVals['negColorRGB'], $configVals['tieColorRGB']);
		$this->_spark = new WssSparklineWhisker($data, $colorPos, $colorNeg, $colorTie);
		$this->_spark->SetDebugLevel(DEBUG_NONE);

		if ($configVals['bgColorTransparent'])
			$this->_spark->SetTransparentBgColor();
		else
		{
			$this->_spark->SetColorHtml('bgcolor', $configVals['bgColorRGB']);
			$this->_spark->SetColorBackground('bgcolor');
		}

		$this->_spark->setRotationAngle($direction);

		$barSize = floor(($imgHeight * ($configVals['barSazeInPersentsOfHeight'] + (($fontFomatType == 'bold') ? $configVals['boldIncrease'] : 0))) / 100);
		$barSpace = floor(($imgHeight * $configVals['barSpaceInPersentsOfHeight']) / 100);

		$barSize = ($barSize < $configVals['minBarSize']) ? $configVals['minBarSize'] : $barSize;
		$barSpace = ($barSpace < $configVals['minBarSpace']) ? $configVals['minBarSpace'] : $barSpace;

		$this->_spark->setBarWidth($barSize);
		$this->_spark->setBarSpacing($barSpace);

		$this->_spark->Render($imgHeight);
	}

	function output($file ='')
	{
//		$this->_spark->Output($file);
		$this->_spark->Output();
	}

	function OutputToHTML()
	{
		return $this->_spark->OutputToHTML();
	}
}

class SparkPieColored
{
	var $_outImg;

	function SparkPieColored($data, $imgHeight, $fontFomatType, $direction, $color)
	{
		$configVals = new WssSparkConfig();
		$configVals = $configVals->getAllVals();

		$imgHeight += floor(($imgHeight) * ((($fontFomatType == 'bold') ? $configVals['boldIncrease'] : 0)) / 100);

		for ($i=0; $i<count($data); $i++)
		{
			// set data percents between 0 and 100
			$data[$i] = (($data[$i] <= 1) ? ($data[$i] * 100) : $data[$i]);
			if ($data[$i] < 0)
				$data[$i] = 0;
			if ($data[$i] > 100)
				$data[$i] = 100;

			$sparkPie[$i] = new WssSparklinePie($data[$i]);
			$sparkPie[$i]->setPieColor($color);
			if ($configVals['bgColorTransparent'])
				$sparkPie[$i]->setTransparentBgColor();

			//$sparkPie[$i]->renderResampled($imgHeight);
			$sparkPie[$i]->render($imgHeight);
		}


		$singlePieWidth = $imgHeight + floor($imgHeight / $configVals['spaceBetweenPiesInPersentsOfHeight']);
		$this->_outImg = imagecreatetruecolor($singlePieWidth * count($data), $imgHeight);
		imagesavealpha($this->_outImg, true);

		// setBackground Color
		$rgbImg = trim($configVals['bgColorRGB'], '#');
		$imgBgColor = imagecolorallocate($this->_outImg, hexdec(substr($rgbImg, 0, 2)), hexdec(substr($rgbImg, 2, 2)), hexdec(substr($rgbImg, 4, 2)));

		if ($configVals['bgColorTransparent'])
			$imgBgColor = imagecolortransparent($this->_outImg);

		imagefill($this->_outImg, 0, 0, $imgBgColor);

		for ($i = 0; $i < count($data); $i++)
			imagecopyresampled($this->_outImg, $sparkPie[$i]->getImageHandle(), $i * $singlePieWidth, 0, 0, 0, $imgHeight, $imgHeight, $imgHeight, $imgHeight);

		if (($direction % 360) != 0)
		{
			if (abs($direction % 360) == 90)
				$this->_doRotation($direction % 360);
		}
	}

	function output($file ='')
	{
		if ($file != '')
			imagepng($this->_outImg, $file);
		else
		{
			header('Content-type: image/png');
			imagepng($this->_outImg);
		}
	}

	function OutputToHTML()
	{
		ob_start(); // start a new output buffer
			imagepng($this->_outImg);
			$tmpImageData = ob_get_contents();
		ob_end_clean(); // stop this output buffer

		return '<img src="data:image/png;base64,' . base64_encode($tmpImageData) . '" />';
	}

	function _doRotation($rotationAngle)
	{
		$tmpImg = imagecreatetruecolor(imagesy($this->_outImg), imagesx($this->_outImg));
		imagecolortransparent($tmpImg, imagecolorallocate($tmpImg, 0, 0, 0));
		//imagealphablending($tmpImg, false);
		imagesavealpha($tmpImg);

		for ($i = 0; $i <= imagesx($this->_outImg); $i++)
		{
			for ($j = 0; $j <= imagesy($this->_outImg); $j++)
			{
				$alphaColor = imagecolorat($this->_outImg, $i, $j);
				$alpha = ($alphaColor >> 24) & 0x7F;
				$r = ($alphaColor >> 16) & 0xFF;
				$g = ($alphaColor >> 8) & 0xFF;
				$b = $alphaColor & 0xFF;

				if (($color = imagecolorexactalpha($tmpImg, $r, $g, $b, $alpha)) === -1)
					$color = imagecolorallocatealpha($tmpImg, $r, $g, $b, $alpha);

				if ($rotationAngle == -90)
					imagesetpixel($tmpImg, imagesx($tmpImg) - $j - 1, $i, $color); // angle = -90
				else if ($rotationAngle == 90)
					imagesetpixel($tmpImg, $j, imagesy($tmpImg) - $i - 1, $color); // angle = 90
			}
		}

		if (abs($rotationAngle) == 90)
			$this->_outImg = $tmpImg;
	}
}

class SparkbarsColored
{
	var $_spark;

	function SparkbarsColored($data, $imgHeight, $fontFomatType, $direction, $colorPos, $colorNeg, $colorFirst, $colorLast, $colorTrend,
$colorMin, $colorMax, $showFirst, $showTrend, $showLast, $showMinMax, $scaling, $scaleMin, $scaleMax)
	{
		$configVals = new WssSparkConfig();
		$configVals = $configVals->getAllVals();

		$this->_spark = new WssSparklineBar($data, $colorPos, $colorNeg, $scaling, $scaleMin, $scaleMax);
		$this->_spark->SetDebugLevel(DEBUG_NONE);

		if ($configVals['bgColorTransparent'])
			$this->_spark->SetTransparentBgColor();
		else
		{
			$this->_spark->SetColorHtml('bgcolor', $configVals['bgColorRGB']);
			$this->_spark->SetColorBackground('bgcolor');
		}

		$this->_spark->setRotationAngle($direction);

		$barSize = floor(($imgHeight * ($configVals['barSazeInPersentsOfHeight'] + (($fontFomatType == 'bold') ? $configVals['boldIncrease'] : 0))) / 100);
		//$barSize = floor(($imgHeight * $configVals['barSazeInPersentsOfHeight']) / 100);
		$barSpace = floor(($imgHeight * $configVals['barSpaceInPersentsOfHeight']) / 100);

		$barSize = ($barSize < $configVals['minBarSize']) ? $configVals['minBarSize'] : $barSize;
		$barSpace = ($barSpace < $configVals['minBarSpace']) ? $configVals['minBarSpace'] : $barSpace;

		$this->_spark->setBarWidth($barSize);
		$this->_spark->setBarSpacing($barSpace);

		if (!empty($colorFirst))
			$this->_spark->setFirstBarColor($colorFirst);
		if (!empty($colorLast))
			$this->_spark->setLastBarColor($colorLast);

		if (!empty($colorMin))
			$this->_spark->setMinBarColor($colorMin);
		if (!empty($colorMax))
			$this->_spark->setMaxBarColor($colorMax);

		if ($showMinMax)
			$this->_spark->addMinMaxNumber($colorMin, $colorMax);

		if ($showFirst)
			$this->_spark->addFirstNumber($colorFirst);

		if ($showLast)
			$this->_spark->addLastNumber($colorLast);

		$this->_spark->setFontPixelSize($imgHeight);
		$this->_spark->setFontType((($fontFomatType == 'bold') ? $configVals['boldFontName'] : $configVals['fontName']));
		$this->_spark->Render($imgHeight);
//		$this->_spark->Output();
	}

	function output($file ='')
	{
//		$this->_spark->Output($file);
		$this->_spark->Output();
	}

	function OutputToHTML()
	{
		return $this->_spark->OutputToHTML();
	}
}

class SparkLineColored
{
	var $_spark;

	function SparkLineColored($data, $imgHeight, $fontFomatType, $direction, $hasDots, $hasLine, $colorPos, $colorNeg, $colorFirst, $colorLast, $colorTrend,
$colorMin, $colorMax, $showFirst, $showTrend, $showLast, $showMinMax, $scaling, $scaleMin, $scaleMax)
	{
		$configVals = new WssSparkConfig();
		$configVals = $configVals->getAllVals();

		$this->_spark = new WssSparklineLine($data, $scaling, $scaleMin, $scaleMax);
		$this->_spark->SetDebugLevel(DEBUG_NONE);

		if ($configVals['bgColorTransparent'])
			$this->_spark->SetTransparentBgColor();
		else
		{
			$this->_spark->SetColorHtml('bgcolor', $configVals['bgColorRGB']);
			$this->_spark->SetColorBackground('bgcolor');
		}

		$this->_spark->setRotationAngle($direction);

		$this->_spark->SetColorHtml('lineColor', $configVals['lineColorRGB']);
		$this->_spark->setLineColor('lineColor');

		$dotSize = floor(($imgHeight * ($configVals['dotSazeInPersentsOfHeight'] + (($fontFomatType == 'bold') ? $configVals['boldIncrease'] : 0))) / 100);
		$dotSpace = floor(($imgHeight * $configVals['dotSpaceInPersentsOfHeight']) / 100);
		$dotSize = ($dotSize < $configVals['minDotSize']) ? $configVals['minDotSize'] : $dotSize;
		$dotSpace = ($dotSpace < $configVals['minDotSpace']) ? $configVals['minDotSpace'] : $dotSpace;
		$this->_spark->setPointSize($dotSize);

		if ($hasDots)
			$this->_spark->addDots($colorPos, $colorNeg);

		if (!$hasLine)
			$this->_spark->hideLine();

		if (!empty($colorFirst))
			$this->_spark->setFirstPointColor($colorFirst);
		if (!empty($colorLast))
			$this->_spark->setLastPointColor($colorLast);

		if (!empty($colorMin))
			$this->_spark->setMinPointColor($colorMin);
		if (!empty($colorMax))
			$this->_spark->setMaxPointColor($colorMax);

		if ($showMinMax)
			$this->_spark->addMinMaxNumber($colorMin, $colorMax);

		if ($showFirst)
			$this->_spark->addFirstNumber($colorFirst);

		if ($showLast)
			$this->_spark->addLastNumber($colorLast);

		$this->_spark->setFontPixelSize($imgHeight);
		$this->_spark->setFontType((($fontFomatType == 'bold') ? $configVals['boldFontName'] : $configVals['fontName']));
//		$this->_spark->setFontType($configVals['fontName']);
		//$sparkline->Render(($imgWidth - 2), $imgHeight);
		//$sparkline->RenderResampled(($imgWidth - 2), $imgHeight);
		//$sparkline->RenderDots($imgHeight);
		//$sparkline->RenderDotsResampled(($imgWidth - 2));
		$imgWidth = count($data) * ($dotSize + $dotSpace);

		if (($direction == 0) || (!($configVals['bgColorTransparent'])))
			$this->_spark->RenderFullResampled(($imgWidth - 2), $imgHeight);
		else
			$this->_spark->Render(($imgWidth - 2), $imgHeight);
	}

	function output($file ='')
	{
//		$this->_spark->Output($file);
		$this->_spark->Output();
	}

	function OutputToHTML()
	{
		return $this->_spark->OutputToHTML();
	}
}

?>