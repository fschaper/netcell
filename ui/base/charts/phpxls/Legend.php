<?php

class Legend extends XLSObject
{
	function LegendEntries($Index = NULL)
	{
		if($Index == NULL)
			return $this->LegendEntries;

		return $this->LegendEntries->Item($Index);
	}
}

?>