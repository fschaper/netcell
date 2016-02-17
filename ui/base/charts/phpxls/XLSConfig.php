<?php

class XLSConfig
{
	const PALETTE_OFFICE	= 0;
	const PALETTE_APEX		= 1;
	const PALETTE_ASPECT	= 2;
	const PALETTE_METER		= 3;

	const PALETTE_DEFAULT = self::PALETTE_OFFICE;

	const NOVALUE					= 1.7e308;

	public static $paletteInfo = array(
	  self::PALETTE_OFFICE => array('Office', true) // name, user-selectable
	, self::PALETTE_APEX => array('Apex', true)
	, self::PALETTE_ASPECT => array('Aspect', true)
	, self::PALETTE_METER => array('Meter', false)
	);

	public static $paletteData = array(

	  self::PALETTE_OFFICE => array(
		'0xbd814f', '0x4d50c0', '0x59bb9b', '0xa26480',
		'0xc6ac4b', '0x4696f7', '0x33ccff', '0xcccccc',
		'0x9999cc', '0x669933', '0x009999', '0x0033cc',
		'0x999966', '0x333399', '0x006600', '0x990099',
		'0x6699ff', '0x99ff99', '0xff9999', '0x0066cc',
		'0x33cc33', '0xff99cc', '0x6666ff', '0x66cc99',
		'0x999900', '0x3333cc', '0xff3399', '0x0000ff',
		'0xff0000', '0x00ff00', '0x99ccff', '0x999999',
	null)

	, self::PALETTE_APEX => array(
		'0x66b9ce', '0x84b09c', '0xc9b16b', '0xcf8565',
		'0xc96b7f', '0xbb79a3', '0x33ccff', '0xcccccc',
		'0x9999cc', '0x669933', '0x009999', '0x0033cc',
		'0x999966', '0x333399', '0x006600', '0x990099',
		'0x6699ff', '0x99ff99', '0xff9999', '0x0066cc',
		'0x33cc33', '0xff99cc', '0x6666ff', '0x66cc99',
		'0x999900', '0x3333cc', '0xff3399', '0x0000ff',
		'0xff0000', '0x00ff00', '0x99ccff', '0x999999',
	null)

	, self::PALETTE_ASPECT => array(
		'0x097ff0', '0x36299f', '0x7c581b', '0x42854e',
		'0x784860', '0x5998c1', '0x33ccff', '0xcccccc',
		'0x9999cc', '0x669933', '0x009999', '0x0033cc',
		'0x999966', '0x333399', '0x006600', '0x990099',
		'0x6699ff', '0x99ff99', '0xff9999', '0x0066cc',
		'0x33cc33', '0xff99cc', '0x6666ff', '0x66cc99',
		'0x999900', '0x3333cc', '0xff3399', '0x0000ff',
		'0xff0000', '0x00ff00', '0x99ccff', '0x999999',
	null)

	, self::PALETTE_METER => array(
		'0x000000', '0x339933', '0x33ccff', '0x4d50c0',
		'0x808080', '0xbd814f', '0x4d50c0', '0x59bb9b',
		'0xa26480', '0xc6ac4b', '0x4696f7', '0x33ccff',
	null)

	);

	public static $systemPalette = array(
		0xffffff, 0x000000, 0x000000, 0x808080,
		0x808080, 0x808080, 0x808080, 0x808080,
		0x4f81bd, 0xc0504d, 0x9bbb59, 0x8064a2,
		0x4bacc6, 0xf79646, 0xffcc33, 0xcccccc,
		0xcc9999, 0x339966, 0x999900, 0xcc3300,
		0x669999, 0x993333, 0x006600, 0x990099,
		0xff9966, 0x99ff99, 0x9999ff, 0xcc6600,
		0x33cc33, 0xcc99ff, 0xff6666, 0x99cc66,
		0x009999, 0xcc3333, 0x9933ff, 0xff0000,
		0x0000ff, 0x00ff00, 0xffcc99, 0x999999,
	-1);

	public static $configConst = array(
	  'pointsPerCharForAxis' => 4
	, 'leftSpaceWithAxisTitle' => 35
	, 'leftSpaceWithoutAxisTitle' => 20
	, 'leftNumOfCharsFor100' => 4
	, 'legendNameH' => 9
	, 'dump_numOfSeries' => 2
	, 'hSpaceForAxes' => 10
	, 'wSpaceForAxes' => 10
	, 'spacePlotAreaLegend' => 16
	, 'topSpace' => 15
	, 'chartTitleSpace' => 20
	, 'pointPerCharForLegendNames' => 9
	, 'maxLegendWofChartW' => 0.25
	, 'pieChartsRadiusReduction' => 5 // space between edge of chart and pie inside (in points)
	);

	public static $chartTypeConfig = array(
	  XlChartType::xl3DArea => array('fixAxisLeft' => true)
	, XlChartType::xl3DAreaStacked => array('fixAxisLeft' => true)
	, XlChartType::xl3DAreaStacked100 => array('is100' => true, 'fixAxisLeft' => true)
	, XlChartType::xl3DBarClustered => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xl3DBarStacked => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xl3DBarStacked100 => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xl3DColumn => array('fixAxisLeft' => true)
	, XlChartType::xl3DColumnClustered => array('fixAxisLeft' => true)
	, XlChartType::xl3DColumnStacked => array('fixAxisLeft' => true)
	, XlChartType::xl3DColumnStacked100 => array('is100' => true, 'fixAxisLeft' => true)
	, XlChartType::xl3DLine => array('fixAxisLeft' => true)
	, XlChartType::xl3DPie => array()
	, XlChartType::xl3DPieExploded => array()
	, XlChartType::xlArea => array('fixAxisLeft' => true)
	, XlChartType::xlAreaStacked => array('fixAxisLeft' => true)
	, XlChartType::xlAreaStacked100 => array('is100' => true, 'fixAxisLeft' => true)
	, XlChartType::xlBarClustered => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xlBarStacked => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xlBarStacked100 => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xlBubble => array('hasSpecAxisLbls' => true, 'fixAxisLeft' => true)
	, XlChartType::xlBubble3DEffect => array('hasSpecAxisLbls' => true, 'fixAxisLeft' => true)
	, XlChartType::xlColumnClustered => array('fixAxisLeft' => true)
	, XlChartType::xlColumnStacked => array('fixAxisLeft' => true)
	, XlChartType::xlColumnStacked100 => array('is100' => true, 'fixAxisLeft' => true)
	, XlChartType::xlCylinderBarClustered => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xlCylinderBarStacked => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xlCylinderBarStacked100 => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xlCylinderCol => array('fixAxisLeft' => true)
	, XlChartType::xlCylinderColClustered => array('fixAxisLeft' => true)
	, XlChartType::xlCylinderColStacked => array('fixAxisLeft' => true)
	, XlChartType::xlCylinderColStacked100 => array('is100' => true, 'fixAxisLeft' => true)
	, XlChartType::xlDoughnut => array()
	, XlChartType::xlDoughnutExploded => array()
	, XlChartType::xlLine => array('fixAxisLeft' => true)
	, XlChartType::xlLineMarkers => array('fixAxisLeft' => true)
	, XlChartType::xlLineMarkersStacked => array('fixAxisLeft' => true)
	, XlChartType::xlLineMarkersStacked100 => array('is100' => true, 'fixAxisLeft' => true)
	, XlChartType::xlLineStacked => array('fixAxisLeft' => true)
	, XlChartType::xlLineStacked100 => array('is100' => true, 'fixAxisLeft' => true)
	, XlChartType::xlPie => array()
	, XlChartType::xlPieExploded => array()
	, XlChartType::xlRadar => array()
	, XlChartType::xlRadarFilled => array()
	, XlChartType::xlRadarMarkers => array()
	, XlChartType::xlStockHLC => array('fixAxisLeft' => true)
	, XlChartType::xlStockOHLC => array('fixAxisLeft' => true)
	, XlChartType::xlXYScatter => array('hasSpecAxisLbls' => true, 'fixAxisLeft' => true, 'forceCatLbls' => true)
	, XlChartType::xlXYScatterLines => array('hasSpecAxisLbls' => true, 'fixAxisLeft' => true, 'forceCatLbls' => true)
	, XlChartType::xlXYScatterLinesNoMarkers => array('hasSpecAxisLbls' => true, 'fixAxisLeft' => true, 'forceCatLbls' => true)
	, XlChartType::xlXYScatterSmooth => array('hasSpecAxisLbls' => true, 'fixAxisLeft' => true, 'forceCatLbls' => true)
	, XlChartType::xlXYScatterSmoothNoMarkers => array('hasSpecAxisLbls' => true, 'fixAxisLeft' => true, 'forceCatLbls' => true)
	, XlChartType::xlMeterOdoFull => array('isMeter' => true, 'defPalette' => self::PALETTE_METER)
	, XlChartType::xlMeterOdoFull100 => array('isMeter' => true, 'defPalette' => self::PALETTE_METER)
	, XlChartType::xlMeterOdoHalf => array('isMeter' => true, 'defPalette' => self::PALETTE_METER)
	, XlChartType::xlMeterOdoHalf100 => array('isMeter' => true, 'defPalette' => self::PALETTE_METER)
	, XlChartType::xlMeterAngularWide => array('isMeter' => true, 'defPalette' => self::PALETTE_METER)
	, XlChartType::xlMeterLineHorizontal => array('isMeter' => true, 'defPalette' => self::PALETTE_METER)
	, XlChartType::xlMeterLineVertical => array('isMeter' => true, 'defPalette' => self::PALETTE_METER)
	, XlChartType::xlLineRotated => array('swapXY' => true, 'fixAxisLeft' => true)
	, XlChartType::xlLineMarkersRotated => array('swapXY' => true, 'fixAxisLeft' => true)
	/* unsupported chart types
	, XlChartType::xlBarOfPie => array()
	, XlChartType::xlPieOfPie => array()
	, XlChartType::xlPyramidBarClustered => array()
	, XlChartType::xlPyramidBarStacked => array()
	, XlChartType::xlPyramidBarStacked100 => array()
	, XlChartType::xlPyramidCol => array()
	, XlChartType::xlPyramidColClustered => array()
	, XlChartType::xlPyramidColStacked => array()
	, XlChartType::xlPyramidColStacked100 => array()
	, XlChartType::xlStockVHLC => array()
	, XlChartType::xlStockVOHLC => array()
	, XlChartType::xlSurface => array()
	, XlChartType::xlSurfaceTopView => array()
	, XlChartType::xlSurfaceTopViewWireframe => array()
	, XlChartType::xlSurfaceWireframe => array()
	, XlChartType::xlConeBarClustered => array()
	, XlChartType::xlConeBarStacked => array()
	, XlChartType::xlConeBarStacked100 => array()
	, XlChartType::xlConeCol => array()
	, XlChartType::xlConeColClustered => array()
	, XlChartType::xlConeColStacked => array()
	, XlChartType::xlConeColStacked100 => array()
	*/
	);

	/* array of calculation formulas
	 _$NEW - new value of property that will be changed
	 _$OLD - old value of property that will be changed
	 _$VALUE - old value of property that is triggered but changed property
	 (fe: ChartArea that has - array('Width', 'Chart.Legend.Left', '(_$NEW - _$OLD) + _$VALUE'))
	 formula will be: $chart->Legend->Left = ((<new value> - $this->Width) + $chart->Legend->Left)
	*/
	public static $convFormula = array(
	  'ChartArea' => array(
		// Legend
		  array('Width', 'Chart.Legend.Left', '(_$NEW - _$OLD) + _$VALUE')
		, array('Height', 'Chart.Legend.Top', '((_$NEW - _$OLD) / 2) + _$VALUE')

		// PlotArea
		, array('Width', 'Chart.PlotArea.InsideWidth', '(_$NEW - _$OLD) + _$VALUE')
		, array('Height', 'Chart.PlotArea.InsideHeight', '(_$NEW - _$OLD) + _$VALUE')
		)

	, 'Chart' => array(
		// PlotArea
		  array('HasLegend', 'Chart.PlotArea.InsideWidth', '(Chart.HasLegned) ? (Chart.Legend.Left - Chart.PlotArea.InsideLeft - XLSConfig::$configConst[\'spacePlotAreaLegend\']) : (Chart.Legend.Left + Chart.Legend.Width - Chart.PlotArea.InsideLeft - XLSConfig::$configConst[\'spacePlotAreaLegend\'])')

		, array('HasTitle', 'Chart.Legend.Top', '(Chart.HasTitle) ? (Chart.Legend.Top + (Chart.ChartTitle.Font.Size / 2)) : (Chart.Legend.Top - ((Chart.PlotArea.InsideTop - XLSConfig::$configConst[\'topSpace\']) / 2))')
		, array('HasTitle', 'Chart.PlotArea.InsideHeight', '(Chart.HasTitle) ? (Chart.PlotArea.InsideHeight - Chart.ChartTitle.Font.Size) : (Chart.PlotArea.InsideHeight + Chart.PlotArea.InsideTop - XLSConfig::$configConst[\'topSpace\'])')
		, array('HasTitle', 'Chart.PlotArea.InsideTop', '(Chart.HasTitle) ? (Chart.ChartTitle.Font.Size + XLSConfig::$configConst[\'topSpace\']) : (XLSConfig::$configConst[\'topSpace\'])')
		)

	, 'Font' => array(
		  array('Size', 'Chart.Legend.Top', 'Chart.Legend.Top + ((_$NEW - XLSConfig::$configConst[\'chartTitleSpace\']) / 2)')
		, array('Size', 'Chart.PlotArea.InsideHeight', 'Chart.PlotArea.InsideHeight + Chart.PlotArea.InsideTop - (XLSConfig::$configConst[\'chartTitleSpace\'] + _$NEW)')
		, array('Size', 'Chart.PlotArea.InsideTop', '(XLSConfig::$configConst[\'chartTitleSpace\'] + _$NEW)')
		)

	, 'Axis' => array(
		// This formulas should not have _$NEW variable
		  array('_HasTitle_X', 'Chart.PlotArea.InsideHeight', '(Chart.Axes(1).HasTitle) ? (Chart.PlotArea.InsideHeight - XLSConfig::$configConst[\'hSpaceForAxes\']) : (Chart.PlotArea.InsideHeight + XLSConfig::$configConst[\'hSpaceForAxes\'])')
		, array('_HasTitle_Y', 'Chart.PlotArea.InsideLeft', '(Chart.Axes(2).HasTitle) ? (Chart.PlotArea.InsideLeft + XLSConfig::$configConst[\'wSpaceForAxes\']) : (Chart.PlotArea.InsideLeft - XLSConfig::$configConst[\'wSpaceForAxes\'])')
		, array('_HasTitle_Y', 'Chart.PlotArea.InsideWidth', '(Chart.Axes(2).HasTitle) ? (Chart.PlotArea.InsideWidth - XLSConfig::$configConst[\'wSpaceForAxes\']) : (Chart.PlotArea.InsideWidth + XLSConfig::$configConst[\'wSpaceForAxes\'])')

		, array('_HasTitle_X_swapXY', 'Chart.PlotArea.InsideHeight', '(Chart.Axes(2).HasTitle) ? (Chart.PlotArea.InsideHeight - XLSConfig::$configConst[\'hSpaceForAxes\']) : (Chart.PlotArea.InsideHeight + XLSConfig::$configConst[\'hSpaceForAxes\'])')
		, array('_HasTitle_Y_swapXY', 'Chart.PlotArea.InsideLeft', '(Chart.Axes(1).HasTitle) ? (Chart.PlotArea.InsideLeft + XLSConfig::$configConst[\'wSpaceForAxes\']) : (Chart.PlotArea.InsideLeft - XLSConfig::$configConst[\'wSpaceForAxes\'])')
		, array('_HasTitle_Y_swapXY', 'Chart.PlotArea.InsideWidth', '(Chart.Axes(1).HasTitle) ? (Chart.PlotArea.InsideWidth - XLSConfig::$configConst[\'wSpaceForAxes\']) : (Chart.PlotArea.InsideWidth + XLSConfig::$configConst[\'wSpaceForAxes\'])')
		)
	);

}

?>