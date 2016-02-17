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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: ChartmapperConfigs.php 2355 2009-10-28 15:53:50Z predragm $
 *
 */

class ChartmapperConfigs {

	// ChartType related configurations.
	// chartType => array(baseChart, multilayer (true/false), number of Series in dataset or 0 if multilayer = false)
    public static $charttype = array(
        'xl3DArea' => array('XYChart', false, 0),
    	'xl3DAreaStacked' => array('XYChart', false, 0),
    	'xl3DAreaStacked100' => array('XYChart', false, 0),
    	'xl3DBarClustered' => array('XYChart', false, 0),
    	'xl3DBarStacked' => array('XYChart', false, 0),
    	'xl3DBarStacked100' => array('XYChart', false, 0),
    	'xl3DColumnClustered' => array('XYChart', false, 0),
    	'xl3DColumnStacked' => array('XYChart', false, 0),
    	'xl3DColumnStacked100' => array('XYChart', false, 0),
    	'xl3DLine' => array('XYChart', false, 0),
    	'xl3DPie' => array('PieChart', false, 0),
    	'xl3DPieExploded' => array('PieChart', false, 0),
    	'xlArea' => array('XYChart', false, 0),
    	'xlAreaStacked' => array('XYChart', false, 0),
    	'xlAreaStacked100' => array('XYChart', false, 0),
    	'xlBarClustered' => array('XYChart', false, 0),
    	'xlBarStacked' => array('XYChart', false, 0),
    	'xlBarStacked100' => array('XYChart', false, 0),
    	'xlBubble' => array('XYChart', true, 3),
    	'xlBubble3DEffect' => array('XYChart', true, 3),
    	'xlColumnClustered' => array('XYChart', false, 0),
    	'xlColumnStacked' => array('XYChart', false, 0),
    	'xlColumnStacked100' => array('XYChart', false, 0),
    	'xlCylinderBarClustered' => array('XYChart', false, 0),
    	'xlCylinderBarStacked' => array('XYChart', false, 0),
    	'xlCylinderBarStacked100' => array('XYChart', false, 0),
    	'xlCylinderColClustered' => array('XYChart', false, 0),
    	'xlCylinderColStacked' => array('XYChart', false, 0),
    	'xlCylinderColStacked100' => array('XYChart', false, 0),
    	'xlDoughnut' => array('PieChart', false, 0),
    	'xlDoughnutExploded' => array('PieChart', false, 0),
    	'xlLine' => array('XYChart', false, 0),
    	'xlLineMarkers' => array('XYChart', false, 0),
    	'xlLineMarkersStacked' => array('XYChart', false, 0),
    	'xlLineMarkersStacked100' => array('XYChart', false, 0),
    	'xlLineStacked' => array('XYChart', false, 0),
    	'xlLineStacked100' => array('XYChart', false, 0),
    	'xlPie' => array('PieChart', false, 0),
    	'xlPieExploded' => array('PieChart', false, 0),
    	'xlRadar' => array('PolarChart', true, 1),
    	'xlRadarFilled' => array('PolarChart', true, 1),
    	'xlRadarMarkers' => array('PolarChart', true, 1),
    	'xlStockHLC' => array('XYChart', false, 0),
    	'xlStockOHLC' => array('XYChart', false, 0),
    	'xlXYScatter' => array('XYChart', false, 0),
    	'xlXYScatterLines' => array('XYChart', false, 0),
    	'xlXYScatterLinesNoMarkers' => array('XYChart', false, 0),
    	'xlXYScatterSmooth' => array('XYChart', false, 0),
    	'xlXYScatterSmoothNoMarkers' => array('XYChart', false, 0),
    	'xlMeterOdoFull' => array('AngularMeter', false, 0),
    	'xlMeterOdoFull100' => array('AngularMeter', false, 0),
    	'xlMeterOdoHalf' => array('AngularMeter', false, 0),
    	'xlMeterOdoHalf100' => array('AngularMeter', false, 0),
    	'xlMeterAngularWide' => array('AngularMeter', false, 0),
    	'xlMeterLineHorizontal' => array('LinearMeter', false, 0),
    	'xlMeterLineVertical' => array('LinearMeter', false, 0),
    	'xlLineRotated' => array('XYChart', false, 0),
    	'xlLineMarkersRotated' => array('XYChart', false, 0)
    );

}
?>