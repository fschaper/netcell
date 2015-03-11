<?php

/*
 * Copyright (C) 2006-2009 Jedox AG, Freiburg, Germany
 * http://www.jedox.com/
 *
 * \author
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: Chart.php 4961 2011-05-16 13:57:56Z mladent $
 *
 * \see
 * LICENSE.txt
 *
 */

/**
 * Represents a chart in a workbook.
 * @package wsscharts
 **/
class Chart extends XLSObject
{
	private $_ChartInit;
	private $_sourcedata;
	private $_layout;

	public $_has_ser_lbls;
	public $_has_cat_lbls;

	public function _get_set_chartgroup($chartgroup = NULL, $index = 1)
	{
		switch ($this->ChartType)
		{
			case XlChartType::xl3DAreaStacked100:
			case XlChartType::xl3DAreaStacked:
			case XlChartType::xl3DArea:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->__add('Area3DGroup', $chartgroup, 'Object');
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->Area3DGroup;
				break;

			case XlChartType::xl3DBarClustered:
			case XlChartType::xl3DBarStacked100:
			case XlChartType::xl3DBarStacked:
			case XlChartType::xlCylinderBarClustered:
			case XlChartType::xlCylinderBarStacked100:
			case XlChartType::xlCylinderBarStacked:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->__add('Bar3DGroup', $chartgroup, 'Object');
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->Bar3DGroup;
				break;

			case XlChartType::xl3DColumnClustered:
			case XlChartType::xl3DColumnStacked100:
			case XlChartType::xl3DColumnStacked:
			case XlChartType::xlCylinderColClustered:
			case XlChartType::xlCylinderColStacked100:
			case XlChartType::xlCylinderColStacked:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->__add('Column3DGroup', $chartgroup, 'Object');
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->Column3DGroup;
				break;

			case XlChartType::xl3DLine:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->__add('Line3DGroup', $chartgroup, 'Object');
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->Line3DGroup;
				break;

			case XlChartType::xl3DPieExploded:
			case XlChartType::xl3DPie:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->__add('Pie3DGroup', $chartgroup, 'Object');
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->Pie3DGroup;
				break;

			case XlChartType::xlAreaStacked100:
			case XlChartType::xlAreaStacked:
			case XlChartType::xlArea:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->AreaGroups->_add($chartgroup, NULL, TRUE);
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->AreaGroups->Item($index);
				break;

			case XlChartType::xlBarClustered:
			case XlChartType::xlBarStacked100:
			case XlChartType::xlBarStacked:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->BarGroups->_add($chartgroup, NULL, TRUE);
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->BarGroups->Item($index);
				break;

			case XlChartType::xlBubble3DEffect:
			case XlChartType::xlBubble:
			case XlChartType::xlXYScatterLinesNoMarkers:
			case XlChartType::xlXYScatterLines:
			case XlChartType::xlXYScatterSmoothNoMarkers:
			case XlChartType::xlXYScatterSmooth:
			case XlChartType::xlXYScatter:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->XYGroups->_add($chartgroup, NULL, TRUE);
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->XYGroups->Item($index);
				break;

			case XlChartType::xlColumnClustered:
			case XlChartType::xlColumnStacked100:
			case XlChartType::xlColumnStacked:
			case XlChartType::xlStockHLC:
			case XlChartType::xlStockOHLC:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->ColumnGroups->_add($chartgroup, NULL, TRUE);
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->ColumnGroups->Item($index);
				break;

			case XlChartType::xlDoughnut:
			case XlChartType::xlDoughnutExploded:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->DoughnutGroups->_add($chartgroup, NULL, TRUE);
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->DoughnutGroups->Item($index);
				break;

			case XlChartType::xlLineMarkersStacked100:
			case XlChartType::xlLineMarkersStacked:
			case XlChartType::xlLineMarkers:
			case XlChartType::xlLineStacked100:
			case XlChartType::xlLineStacked:
			case XlChartType::xlLine:
			case XlChartType::xlLineRotated:
			case XlChartType::xlLineMarkersRotated:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->LineGroups->_add($chartgroup, NULL, TRUE);
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->LineGroups->Item($index);
				break;

			case XlChartType::xlPieExploded:
			case XlChartType::xlPie:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->PieGroups->_add($chartgroup, NULL, TRUE);
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->PieGroups->Item($index);
				break;

			case XlChartType::xlRadarFilled:
			case XlChartType::xlRadarMarkers:
			case XlChartType::xlRadar:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->RadarGroups->_add($chartgroup, NULL, TRUE);
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->RadarGroups->Item($index);
				break;

			case XlChartType::xlMeterOdoFull:
			case XlChartType::xlMeterOdoFull100:
			case XlChartType::xlMeterOdoHalf:
			case XlChartType::xlMeterOdoHalf100:
			case XlChartType::xlMeterAngularWide:
			case XlChartType::xlMeterLineHorizontal:
			case XlChartType::xlMeterLineVertical:
				if ($chartgroup instanceof ChartGroup)
				{
					$this->__add('MeterGroup', $chartgroup, 'Object');
					$this->ChartGroups->_add($chartgroup);
				}
				else
					$chartgroup = $this->MeterGroup;
				break;
		}

		return $chartgroup;
	}

	public function InitChart($mode = 0, $SeriesLabels = NULL, $CategoryLabels = NULL)
	{
		if (!is_int($this->ChartType) || !is_int($this->ChartStyle) || !isset($this->_layout) || !is_int($mode))
			return false;

		$this->_ChartInit->setMode($mode);

		$plotby = $this->PlotBy;

		$this->_ChartInit->init(ChartInit::INIT_BASE);

		if ($mode & ChartInit::MODE_DYNEXMPL)
			return true;

		$this->PlotBy = $plotby;

		$obj = new ChartGroups($this);
		$this->__add('ChartGroups', $obj, 'Object');

		$chartgroup = $this->_ChartInit->init(ChartInit::INIT_CHARTGROUP, $this);
		$this->_get_set_chartgroup($chartgroup);

		$obj = new SeriesCollection($this);
		$this->__add('SeriesCollection', $obj, 'Object');

		$chartgroup->SeriesCollection->Add($this->_sourcedata, $this->PlotBy, $SeriesLabels, $CategoryLabels);

		if (isset($chartgroup->HasHiLoLines) && $chartgroup->HasHiLoLines == true && $this->_ChartInit->has_part(ChartInit::INIT_HILOLINES))
			$chartgroup->__add('HiLoLines', $this->_ChartInit->init(ChartInit::INIT_HILOLINES, $chartgroup), 'Object');

		return true;
	}

	public function RefreshSourceData ($SeriesLabels = null, $CategoryLabels = null)
	{
		if (($chartgroup = $this->_get_set_chartgroup()) == null || !isset($chartgroup->SeriesCollection))
			return false;

		$chartgroup->SeriesCollection->Add($this->_sourcedata, $this->PlotBy, ($SeriesLabels != null ? $SeriesLabels : $this->_has_ser_lbls), ($CategoryLabels != null ? $CategoryLabels : $this->_has_cat_lbls), true);

		return true;
	}

	public function _init_part($init_part, $obj_parent, $obj_num = 1)
	{
		return $this->_ChartInit->init($init_part, $obj_parent, $obj_num);
	}

	public function _has_part($init_part)
	{
		return $this->_ChartInit->has_part($init_part);
	}

	public function MakeChart($format)
	{
		$chartPrinter = new ChartPrinter($this);
		$chartPrinter->printChart($format, false);
	}

	public function GetLayout()
	{
		return $this->_layout;
	}

	function __construct()
	{
		parent::__construct();

		$this->__add('ChartType', NULL, 'XlChartType');
		$this->__add('ChartStyle', NULL, 'Integer');
		$this->__add('PlotBy', NULL, 'XlRowCol');

		$this->_ChartInit = new ChartInit($this);
	}

	function AreaGroups($Index = NULL)
	{
		if ($Index == NULL)
			return $this->AreaGroups;

		return $this->AreaGroups->Item($Index);
	}

	function Axes($Type = NULL)
	{
		if ($Type == NULL)
			return $this->Axes;

		return $this->Axes->Item($Type);
	}

	function BarGroups($Index = NULL)
	{
		if ($Index == NULL)
			return $this->BarGroups;

		return $this->BarGroups->Item($Index);
	}

	function ChartGroups($Index = NULL)
	{
		if ($Index == NULL)
			return $this->ChartGroups;

		return $this->ChartGroups->Item($Index);
	}

	function ColumnGroups($Index = NULL)
	{
		if ($Index == NULL)
			return $this->ColumnGroups;

		return $this->ColumnGroups->Item($Index);
	}

	function DoughnutGroups($Index = NULL)
	{
		if ($Index == NULL)
			return $this->DoughnutGroups;

		return $this->DoughnutGroups->Item($Index);
	}

	function LineGroups($Index = NULL)
	{
		if ($Index == NULL)
			return $this->LineGroups;

		return $this->LineGroups->Item($Index);
	}

	function PieGroups($Index = NULL)
	{
		if ($Index == NULL)
			return $this->PieGroups;

		return $this->PieGroups->Item($Index);
	}

	function RadarGroups($Index = NULL)
	{
		if ($Index == NULL)
			return $this->RadarGroups;

		return $this->RadarGroups->Item($Index);
	}

	function SeriesCollection($Index = NULL)
	{
		if ($Index == NULL)
			return $this->SeriesCollection;

		return $this->SeriesCollection->Item($Index);
	}

	function XYGroups($Index = NULL)
	{
		if ($Index == NULL)
			return $this->XYGroups;

		return $this->XYGroups->Item($Index);
	}

	function SetSourceData(array $Source, $PlotBy = NULL)
	{
		$this->_sourcedata = $Source;

		if ($PlotBy != NULL)
			$this->PlotBy = $PlotBy;
	}

	function ApplyLayout($Layout)
	{
		$this->_layout = intval($Layout);
	}

	function __s_HasLegend($n, $v)
	{
		if (($this->HasLegend != $v) && (!isset(XLSConfig::$chartTypeConfig[$this->ChartType]['isMeter'])))
		{
			$this->__m[$n][self::M_VAL] = $v;
			$this->_calculateFormula($n, $v);
		}
	}

	function __s_HasTitle($n, $v)
	{
		if ($this->HasTitle != $v)
		{
			$this->__m[$n][self::M_VAL] = $v;
			$this->_calculateFormula($n, $v);
		}
	}

	private function _calculateFormula($name, $new)
	{
		$chart = $this;

		foreach (XLSConfig::$convFormula[get_class($this)] as $formula)
		{
			if ($formula[0] == $name)
			{
				$valueName = str_replace('Chart', '$chart', str_replace('.', '->', $formula[1]));

				$execFormula = $valueName . ' = (' . $formula[2] . ');';
				$execFormula = str_replace('Chart', '$chart', str_replace('.', '->', $execFormula));

				$execFormula = str_replace('_$NEW', $new, $execFormula);
				$execFormula = str_replace('_$OLD', ('$this->' . $name), $execFormula);
				$execFormula = str_replace('_$VALUE', $valueName, $execFormula);

				eval($execFormula);
			}
		}
	}
}

?>