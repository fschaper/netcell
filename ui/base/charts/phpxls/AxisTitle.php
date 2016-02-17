<?php

/**
 * Represents a chart axis title.
 * @package wsscharts
 **/
class AxisTitle extends XLSObject
{
	function __s_Caption($n, $v)
	{
		if (!isset(XLSConfig::$chartTypeConfig[$this->Parent->Parent->Parent->ChartType]['swapXY']))
			$tmpAT = $this;
		else
		{
			if ($this->Parent->Type == 1)
				$tmpAT = $this->Parent->Parent->Parent->Axes(2)->AxisTitle;
			else if ($this->Parent->Type == 2)
				$tmpAT = $this->Parent->Parent->Parent->Axes(1)->AxisTitle;
		}

		$tmpAT->__m[$n][self::M_VAL] = $v;

		if ($v == '')
			$tmpAT->Parent->HasTitle = false;
		else
			$tmpAT->Parent->HasTitle = true;
	}
}

?>