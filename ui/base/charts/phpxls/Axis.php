<?php

/**
 * Represents a single axis in a chart.
 * @package wsscharts
 **/
class Axis extends XLSObject
{
	function __s_HasTitle($n, $v)
	{
		if ($this->HasTitle != $v)
		{
			$xAxisHasTitle = $this->Parent->Parent->Axes(1)->HasTitle;

			$this->__m[$n][self::M_VAL] = $v;

			$chart = $this->Parent->Parent;
			if (!isset(XLSConfig::$chartTypeConfig[$chart->ChartType]['swapXY']))
			{
				if ($xAxisHasTitle != $this->Parent->Parent->Axes(1)->HasTitle)
					$this->_calculateFormula('_' . $n . '_X', $v);
				else
					$this->_calculateFormula('_' . $n . '_Y', $v);
			}
			else
			{
				if ($xAxisHasTitle != $this->Parent->Parent->Axes(1)->HasTitle)
					$this->_calculateFormula('_' . $n . '_Y_swapXY', $v);
				else
					$this->_calculateFormula('_' . $n . '_X_swapXY', $v);
			}
		}
	}

	private function _calculateFormula($name, $new)
	{
		$chart = $this->Parent->Parent;

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