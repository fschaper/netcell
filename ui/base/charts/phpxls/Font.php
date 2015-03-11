<?php

class Font extends XLSObject
{
	function __s_Size($n, $v)
	{
		if ((get_class($this->Parent) == 'ChartTitle') && ($this->Parent->Parent->HasTitle))
			$this->_calculateFormula($n, $v);

		$this->__m[$n][self::M_VAL] = $v;
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