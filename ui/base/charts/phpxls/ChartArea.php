<?php

class ChartArea extends XLSObject
{

	function __s_Width($n, $v)
	{
		$this->_calculateFormula($n, $v);
		$this->__m[$n][self::M_VAL] = $v;
	}

	function __s_Height($n, $v)
	{
		$this->_calculateFormula($n, $v);
		$this->__m[$n][self::M_VAL] = $v;
	}

	private function _calculateFormula($name, $new)
	{
		$chart = $this->Parent;

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