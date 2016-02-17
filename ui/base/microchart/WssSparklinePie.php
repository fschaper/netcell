<?php

/*
 * @brief ajax
 *
 * @file WssSparklinePie.php
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
 * SVN: $Id: WssSparklinePie.php 3631 2010-08-10 14:01:04Z mladent $
 *
 */

class WssSparklinePie
{
	var $_data;
	var $_color;
	var $_bgColor;
	var $_bgPieColor;

	var $_transparentBgColor;

	var $_imageHandle;

	function WssSparklinePie($data)
	{
		$this->_data = $data;

		$this->_color = '#000000'; //black
		$this->_bgColor = '#FFFFFF'; //white
		$this->_bgPieColor = '#FFFFFF'; //white (this should be same as _bgColor)

		$this->_transparentBgColor = false;
	}

	function render($r)
	{
		$this->_imageHandle = imagecreatetruecolor($r, $r);
		imagesavealpha($this->_imageHandle, true);

		// addColors
		$pieColor = $this->addColorHtml($this->_color);
		$bgColor = $this->addColorHtml($this->_bgColor);
		$bgPieColor = $this->addColorHtml($this->_bgPieColor);

		if ($this->_transparentBgColor)
		{
			$bgPieColor = imagecolortransparent($this->_imageHandle);
			$bgColor = imagecolortransparent($this->_imageHandle);
		}

		imagefill($this->_imageHandle, 0, 0, $bgColor);

		$pieR = $r - 1;
		$center = floor($r/2);

		imagefilledarc($this->_imageHandle, $center, $center, $pieR, $pieR, -0, 360, $bgPieColor, IMG_ARC_PIE);
		imagefilledarc($this->_imageHandle, $center, $center, $pieR, $pieR, -90, -90 + (360 * ($this->_data / 101)), $pieColor, IMG_ARC_PIE);
		imagearc($this->_imageHandle, $center, $center, $pieR, $pieR, 0, 360, $pieColor);
	}

	function renderResampled($r)
	{
		$this->render($r * 4);

		$tmpImgHandle = imagecreatetruecolor($r, $r);

		imagecolortransparent($tmpImgHandle, imagecolorallocate($tmpImgHandle, 0, 0, 0));
		imagealphablending($tmpImgHandle, false);
		imagesavealpha($tmpImgHandle, true);

		imagecopyresampled($tmpImgHandle,  // dest handle
                           $this->_imageHandle,  // src  handle
                           0, 0,  // dest x, y
                           0, 0,  // src  x, y
                           imagesx($tmpImgHandle), imagesy($tmpImgHandle),   // dest w, h
						   imagesx($this->_imageHandle), imagesy($this->_imageHandle)); // src  w, h

		$this->_imageHandle = $tmpImgHandle;
	}

	function output($file ='')
	{
		if ($file == '')
		{
			header('Content-type: image/png');
			imagepng($this->_imageHandle);
		}
		else
		{
			imagepng($this->_imageHandle, $file);
    	}
 	}

	function outputToFile($file) {
		$this->Output($file);
	}

	function setPieColor($rgb)
	{
		$this->_color = $rgb;
	}

	function setPieBackgroundColor($rgb)
	{
		$this->_bgPieColor = $rgb;
	}

	function setBackgroundColor($rgb)
	{
		$this->_bgColor = $rgb;
	}

	function addColorHtml($rgb)
	{
    	$rgb = trim($rgb, '#');
		return imagecolorallocate($this->_imageHandle, hexdec(substr($rgb, 0, 2)), hexdec(substr($rgb, 2, 2)), hexdec(substr($rgb, 4, 2)));
 	}

 	function getImageHandle()
 	{
 		return $this->_imageHandle;
 	}

	function setTransparentBgColor()
	{
		$this->_transparentBgColor = true;
	}
}

?>