<?php

/**
 * Represents a series in a chart.
 * @package wsscharts
 **/
class Series extends XLSObject
{
	function DataLabels($Index = NULL)
	{
		if($Index == NULL)
			return $this->DataLabels;

		return $this->DataLabels->Item($Index);
	}

	function Points($Index = NULL)
	{
		if($Index == NULL)
			return $this->Points;

		return $this->Points->Item($Index);
	}
}

?>