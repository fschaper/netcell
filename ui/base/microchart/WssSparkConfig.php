<?PHP

/*
 * @brief ajax
 *
 * @file WssSparkConfig.php
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
 * SVN: $Id: WssSparkConfig.php 3631 2010-08-10 14:01:04Z mladent $
 *
 */

class WssSparkConfig
{
	public static $mcColorPalette = array(
		"#000000", "#993300", "#333300", "#003300", "#003366", "#000080", "#333399", "#333333",
		"#800000", "#FF6600", "#808000", "#008000", "#008080", "#0000FF", "#666699", "#808080",
		"#FF0000", "#FF9900", "#99CC00", "#339966", "#33CCCC", "#3366FF", "#800080", "#969696",
		"#FF00FF", "#FFCC00", "#FFFF00", "#00FF00", "#00FFFF", "#00CCFF", "#993366", "#C0C0C0",
		"#FF99CC", "#FFCC99", "#FFFF99", "#CCFFCC", "#CCFFFF", "#99CCFF", "#CC99FF", "#FFFFFF"
	);

	private $_configVals;

	public function WssSparkConfig()
	{
		$this->_configVals = array(
			'fontName' => 'arial', // font type (it's font file name without extension [fe: "times" for "Time New Roman"])
			'boldFontName' => 'arialbd', // bold representation of font
			'fontPath' => 'c:/windows/fonts/', // must has / (slash) at end

			'bgColorTransparent' => true,
			'bgColorRGB' => '#FFFFFF', // this background color for all charts
			'lineColorRGB' => '#000000', // default color for lines
			'dotsColorRGB' => '#000000', // default color for dots
			'posColorRGB' => '#000000', // color for positive values in bar, whisker and dots charts
			'negColorRGB' => '#000000', // color for negative values in bar, whisker and dots charts
			'tieColorRGB' => '#000000', // color for negative values in whisker charts
			'pieColorRGB' => '#000000', // color for drawing pie charts

			'scaling' => 0, // 0..max
			'scalingMin' => 0,
			'scalingMax' => 1,

			'width' => 100, // in pixels
			'height' => 20, // in pixels

			'minBarSize' => 2, // size in pixels
			'minBarSpace' => 1, // size in pixels
			'minDotSize' => 2, // size in pixels
			'minDotSpace' => 1, // size in pixels

			'spaceBetweenPiesInPersentsOfHeight' => 10, // space between pies for multiplay pies

			'barSazeInPersentsOfHeight' => 20,
			'barSpaceInPersentsOfHeight' => 10,
			'dotSazeInPersentsOfHeight' => 20,
			'dotSpaceInPersentsOfHeight' => 10,

			'boldIncrease' => 5 // Bold Size Increase (5% bigger then normal)
		);
	}

	public function getVal($key)
	{
		return $this->_configVals[$key];
	}

	public function getAllVals()
	{
		return $this->_configVals;
	}
}

?>