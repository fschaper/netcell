<?php

class ChartGroup extends XLSObject
{
	function SeriesCollection($Index = NULL)
	{
		if($Index == NULL)
			return $this->SeriesCollection;

		return $this->SeriesCollection->Item($Index);
	}
}

?>