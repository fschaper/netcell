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
 * SVN: $Id: ChartPrinter.php 4961 2011-05-16 13:57:56Z mladent $
 *
 */

class ChartPrinter {

	function __construct(&$Chart) {
		$this->Chart = &$Chart;
		setLicenseCode('XXXX-XXXX-XXXX-XXXX-XXXX-XXXX');
	}

	public $Chart;

	private $format;
	private $evalstr;
	private $context;

	public function printChart($format, $asString) {
		$this->format = $format;

		$chart_types = new ReflectionClass('XlChartType');
		$const_array = array_flip($chart_types->getConstants());

		// Load chart.xml file content.
		$xmlStr = file_get_contents('../../../base/charts/chartmapper/xml/chart.xml');

		// Set base chart type.
		$xmlStr = str_replace('@base_chart_type', ChartmapperConfigs::$charttype[$const_array[$this->Chart->ChartType]][0], $xmlStr);

		// Set chart layer-s.
		$series_types = array();
		$series_types_base = null;
		for ($i = 1; $i <= $this->Chart->SeriesCollection->Count; ++$i) {
			$chart_type_str = $const_array[$this->Chart->SeriesCollection($i)->ChartType];

			if (array_key_exists($chart_type_str, $series_types))
				++$series_types[$chart_type_str];
			elseif (count($series_types) == 0 || ChartmapperConfigs::$charttype[$chart_type_str][0] == $series_types_base) {
				$series_types[$chart_type_str] = 1;
				$series_types_base = ChartmapperConfigs::$charttype[$chart_type_str][0];
			}
		}

		$chart_layers = '';
		foreach ($series_types AS $serie_type => $type_count) {
			if (ChartmapperConfigs::$charttype[$serie_type][1]) {
				for ($i = 0; $i < $type_count; $i = $i + ChartmapperConfigs::$charttype[$serie_type][2])
					$chart_layers .= "\n\n" . str_replace('@dataset_id', $i / ChartmapperConfigs::$charttype[$serie_type][2], file_get_contents('../../../base/charts/chartmapper/xml/layers/' . $serie_type . '.xml'));
			} else
				$chart_layers .= "\n\n" . file_get_contents('../../../base/charts/chartmapper/xml/layers/' . $serie_type . '.xml');
		}

		$xmlStr = str_replace('@chart_layers', $chart_layers, $xmlStr);

		// Create DOMDocument.
		$dom = new DOMDocument();
		$dom->preserveWhiteSpace = false;
		$dom->resolveExternals = true;
		$dom->substituteEntities = true;

		// Load expanded XML file.
		$dom->loadXML($xmlStr);

		// Save DOM to test generated XML.
		//echo $dom->saveXML(); exit;

		$this->evalstr = '';
		$this->context = '';
		return $this->processElement($dom->documentElement, $asString);
	}

	private function processElement($element, $asString) {
		global $officePalette, $apexPalette, $aspectPalette, $months;

		if ($element->nodeType != XML_ELEMENT_NODE)
			return;

		// Skip element processing if attribute skip is true or if element has refcontext outside of current context.
		if (($element->hasAttribute('skip') && $element->getAttribute('skip')) || ($element->hasAttribute('refcontext') && $element->getAttribute('refcontext') != $this->context))
			return;

		// Skip element processing if one of elements childs is execadapter that return boolean false.
		if (($elementChild = $element->firstChild) != null) {
			do {
				if ($elementChild->nodeName == 'execadapter') {
					eval('$exec_adapter = new ' . $elementChild->getAttribute('class') . '();');
					eval('$exec_return = $exec_adapter->' . $elementChild->getAttribute('method') . '($this->Chart' . (strlen($elementChild->getAttribute('path')) > 0 ? ', \'' . $elementChild->getAttribute('path') . '\'' : '') . ');');
					if ($exec_return)
						break;
					else
						return;
				} else
					$elementChild = $elementChild->nextSibling;
			} while ($elementChild != null);
		}

		if ($element->hasAttribute('type')) {
			switch ($element->getAttribute('type')) {
				case 'object':
					if ($element->hasAttribute('context'))
						eval('$this->context .= \'' . ((strlen($this->context) > 0) ? '.' : '') . $element->getAttribute('context') . '\';');

					// Locate "args" element.
					if (($argsChild = $element->firstChild) != null) {
						while ($argsChild != null && $argsChild->nodeName != 'args')
							$argsChild = $argsChild->nextSibling;
					}

					$this->evalstr .= 'static $' . $element->nodeName . ';' . "\n";
					$this->evalstr .= '$' . $element->nodeName . ' = new ' . $element->getAttribute('class') . '(' . (($argsChild->nodeName == 'args') ? $this->processArgs($argsChild, $this->context) : '') . ');' . "\n";
					break;

				case 'function':
					if ($element->hasAttribute('context'))
						eval('$this->context .= \'' . ((strlen($this->context) > 0) ? '.' : '') . $element->getAttribute('context') . '\';');

					$this->evalstr .= '$' . $element->nodeName . ' = $' . $element->parentNode->nodeName . '->' . $element->getAttribute('init') . '(' . (($element->firstChild->nodeName == 'args') ? $this->processArgs($element->firstChild, $this->context) : '') . ');' . "\n";
					break;

				case 'method':
					$this->evalstr .= '$' . $element->parentNode->nodeName . '->' . $element->nodeName . '(' . (($element->firstChild->nodeName == 'args') ? $this->processArgs($element->firstChild, $this->context) : '') . ');' . "\n";
					break;

				case 'eval':
					if ($element->hasAttribute('context'))
						eval('$this->context .= \'' . ((strlen($this->context) > 0) ? '.' : '') . $element->getAttribute('context') . '\';');

					$args = null;
					$adapterclass = null;
					$eval_adapter_str = '';
					if (($elementChild = $element->firstChild) != null) {
						do {
							switch ($elementChild->nodeName) {
								case 'args':
									$args = explode(', ', $this->processArgs($elementChild, $this->context));
									break;

								case 'evaladapter':
									eval('$adapterclass = new ' . $elementChild->getAttribute('class') . '();');
									$eval_adapter_str = '$adapterclass->' . $elementChild->getAttribute('method') . '($this->Chart';
									break;
							}

							$elementChild = $elementChild->nextSibling;
						} while ($elementChild != null);
					}

					eval('$this->evalstr .= ' . $eval_adapter_str . ', \'' . $element->parentNode->nodeName . '\'' . (strlen($element->getAttribute('init')) > 0 ? ', \'' . $element->getAttribute('init') . '\'' : '') . (!is_null($args) ? ', $args' : '') . ');');
					break;
			}
		}

		if ($element->hasChildNodes()) {
			$childElements = $element->childNodes;

			for ($i = 0; $i < $childElements->length; ++$i) {
				if ($childElements->item($i) != XML_ELEMENT_NODE || $childElements->item($i)->nodeName == 'args')
					continue;
				else
					$this->processElement($childElements->item($i), $asString);
			}
		}

		if ($element->hasAttribute('context'))
			$this->context = substr_replace($this->context, '', (strlen($element->getAttribute('context')) + 1) * -1);

		if ($element->nodeName == 'chart') {

			// Uncomment to print generated ChartDirector code.
//			die('<pre>' . $this->evalstr . '</pre>');

			eval($this->evalstr);

			if (isset($asString) && $asString)
				return ${$element->nodeName}->makeChart2($this->format);
			else
			{
				header('Content-Type: image/png');
				print(${$element->nodeName}->makeChart2($this->format));
			}
		}

		return '';
	}

	private function processArgs($args, $context) {
		$argarray = array();

		if (($arg = $args->firstChild) != null) {
			do {
				if ($arg->nodeType == XML_ELEMENT_NODE) {

				if (($argChild = $arg->firstChild) != null) {
					while ($argChild != null && ($argChild->nodeName != 'map' || ($argChild->hasAttribute('refcontext') && $argChild->getAttribute('refcontext') != $context)))
						$argChild = $argChild->nextSibling;

					if ($argChild->nodeName == 'map') {
						$argIsString = $arg->hasAttribute('string') && $arg->getAttribute('string');

						$mapAdapter = $argChild->firstChild;

						$adapter_args = '';
						if (($adapterArg = $mapAdapter->firstChild) != null) {
							do {
								if ($adapterArg->hasAttribute('value'))
									$adapter_args .= ', \'' . $adapterArg->getAttribute('value') . '\'';

								$adapterArg = $adapterArg->nextSibling;
							} while ($adapterArg != null);
						}

						switch ($mapAdapter->nodeName) {
							case 'adapter':
								if ($mapAdapter->hasAttribute('static') && $mapAdapter->getAttribute('static'))
									eval('$argarray[] = ' . ($argIsString ? '. \'\\\'\' . ' : '') . $mapAdapter->getAttribute('class') . '::' . $mapAdapter->getAttribute('method') . '(' . (strlen($argChild->getAttribute('path')) > 0 ? '$this->' . str_replace('.', '->', $argChild->getAttribute('path')) : 'null') . $adapter_args . ')' . ($argIsString ? ' . \'\\\'\' . ' : '') . ';');
								else {
									eval('$adapterclass = new ' . $mapAdapter->getAttribute('class') . '();');
									eval('$argarray[] = ' . ($argIsString ? '. \'\\\'\' . ' : '') . '$adapterclass->' . $mapAdapter->getAttribute('method') . '(' . (strlen($argChild->getAttribute('path')) > 0 ? '$this->' . str_replace('.', '->', $argChild->getAttribute('path')) : 'null') . $adapter_args . ')' . ($argIsString ? ' . \'\\\'\' . ' : '') . ';');
								}
								break;

							case 'superadapter':
								eval('$adapterclass = new ' . $mapAdapter->getAttribute('class') . '();');
								eval('$argarray[] = ' . ($argIsString ? '. \'\\\'\' . ' : '') . '$adapterclass->' . $mapAdapter->getAttribute('method') . '($this->Chart, ' . ($argChild->hasAttribute('refcontext') ? '\'' . $argChild->getAttribute('refcontext') . '\'' : 'null') . (strlen($argChild->getAttribute('path')) > 0 ? ', \'' . $argChild->getAttribute('path') . '\'' : ', null') . $adapter_args . ')' . ($argIsString ? ' . \'\\\'\' . ' : '') . ';');
								break;

							default:
								eval('$argarray[] = ' . ($argIsString ? '\'\\\'\' . ' : '') . '$this->' . str_replace('.', '->', $argChild->getAttribute('path')) . ($argIsString ? ' . \'\\\'\'' : '') . ';');
								break;
						}
					} else
						$this->setArgDefault($arg, $argarray);
				} else
					$this->setArgDefault($arg, $argarray);


				}
				$arg = $arg->nextSibling;
			} while ($arg != null);
		}

		$is_first = true;
		$argstring = '';
		foreach ($argarray AS $param) {
			if (!$is_first)
				$argstring .= ', ';
			else
				$is_first = false;

			$argstring .= $param;
		}

		return $argstring;
	}

	private function setArgDefault(&$arg, &$argarray) {
		if ($arg->hasAttribute('default')) {
			$default_value = $arg->getAttribute('default');

			switch ($default_value) {
				case '[Empty_Array]':
					$default_value = 'array()';
					break;

				case '[-Infinity]':
					$default_value = '\'[-Infinity]\'';
					break;
			}

			$argarray[] = ($arg->hasAttribute('string') && $arg->getAttribute('string')) ? $this->quoteString($arg->getAttribute('default')) : $arg->getAttribute('default');
		} elseif ($arg->hasAttribute('mandatory') && $arg->getAttribute('mandatory'))
			throw new Exception('Mandatory without default value', 5);
	}

	private function quoteString($str) {
		return '\'' . $str . '\'';
	}
}

?>