<?php

/*
 * @brief wss file
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: Report.php 4929 2011-05-04 13:10:07Z mladent $
 *
 */

class Report extends Report_Adapter
{
	private static $l10n_seps = array(
		'en_US' => array('.', ',', ',')
		, 'de_DE' => array(',', '.', ';')
		, 'fr_FR' => array(',', '.', ';')
	);

	private static $l10n_bool = array(
		'en_US' => array(1 => 'TRUE', 0 => 'FALSE')
		, 'de_DE' => array(1 => 'WAHR', 0 => 'FALSCH')
		, 'fr_FR' => array(1 => 'VRAI', 0 => 'FAUX')
	);

	private static function _lettersToNumber ($ltrs)
	{
		$num = 0;

		for ($f = 1, $i = strlen($ltrs = strtoupper($ltrs)) - 1; $i >= 0; --$i, $f *= 26)
			$num += (ord($ltrs[$i]) - 64) * $f;

		return $num;
	}

	private function _get_data()
	{
		if (isset($this->page_setup) && (is_array($this->page_setup['sheet']['print_area'])))
			$range = $this->page_setup['sheet']['print_area'];
		else
		{
			$res = json_decode(ccmd('[["gurn"]]'), true);
			$res = $res[0][1];

			$range = array(1, 1, $res[0], $res[1]);
		}

		// get data from core (modified pmalic's code)
		$query_what = WSS::Q_VALUE | WSS::Q_STYLE | WSS::Q_FMT_VAL | WSS::Q_MERGE;
		$ccmd = '['
					. '["gusl"]'
					. ',["gval",' . $query_what . ',' . $range[0] . ',' . $range[1] . ',' . $range[2] . ',' . $range[3] . ']'
					. ',["gdcr",2]'
					. ',["gcr",0,' . $range[0] . ',' . $range[2] . ']'
					. ',["gcr",1,' . $range[1] . ',' . $range[3] . ']'
					. ',["wget","",[],["e_id","e_type","n_location","pos_offsets","size"],{"e_type":"chart"}]'
					. ',["wget","",[],["e_id","e_type","n_location","pos_offsets","size","payload"],{"e_type":"img"}]'
				. ']';
		$res = json_decode(ccmd($ccmd), true);

		$l10n = array_shift($res);
		$l10n = $l10n[1];
		$cells = &$res[0][1];
		$rows = array();

		for ($i = -1, $r = $range[1]; $r <= $range[3]; ++$r)
		{
			$row = array();

			for ($c = $range[0]; $c <= $range[2]; ++$c)
			{
				$cell = array();

				if (($v = $cells[++$i]) !== '')
				{
					if (is_numeric($v) && !is_string($v))
					{
						$v = strval($v);

						if (($dec_sep = self::$l10n_seps[$l10n][WSS::SEP_DECIMAL]) != '.')
							$v = str_replace('.', $dec_sep, $v);

						$t = 'n';
					}
					else if (is_bool($v))
					{
						$v = self::$l10n_bool[$l10n][$v];
						$t = 'b';
					}
					else
						$t = substr($v, 0, 1) == '<' ? 'h' : 's';

					$cell['v'] = $v;
					$cell['t'] = $t;
				}

				if (($v = $cells[++$i]) !== '')
					$cell['s'] = $v;

				if (($v = $cells[++$i]) !== '')
					$cell['v'] = $v;

				if (($v = $cells[++$i]) !== '')
					$cell['m'] = $v;

				$row[] = $cell;
			}

			$rows[] = $row;
		}

		$def_dims = &$res[1][1];

		$col_widths = array_fill(0, $range[2] - $range[0] + 1, $def_dims[0]);
		$row_heights = array_fill(0, $range[3] - $range[1] + 1, $def_dims[1]);

		$col_w_sp = &$res[2][1];
		for ($cnt = count($col_w_sp), $i = 0; $i < $cnt; )
			$col_widths[$col_w_sp[$i++] - $range[0] + 1] = $col_w_sp[$i++];

		$row_h_sp = &$res[3][1];
		for ($cnt = count($row_h_sp), $i = 0; $i < $cnt; )
			$row_heights[$row_h_sp[$i++] - $range[1] + 1] = $row_h_sp[$i++];

		// generating wsel storage
		$wselSearchArr = array();
		if ($res[4][0] && $res[5][0])
		{
			for ($i=4; $i<=5; $i++)
			{
				foreach($res[$i][1] as $wsElem)
				{
					$wsElem['n_location'] = str_replace('$', '', $wsElem['n_location']);
					if (preg_match(self::RE_ND_RANGE, $wsElem['n_location'], $pos))
					{
						$pos = array(self::_lettersToNumber($pos[1]) - 1, intval($pos[2]) - 1, self::_lettersToNumber($pos[3]) - 1, intval($pos[4]) - 1);

						// Adjust pos if there is set Print Area
						if (isset($this->page_setup) && (is_array($this->page_setup['sheet']['print_area'])))
						{
							$pos[0] -= $this->page_setup['sheet']['print_area'][0] - 1;
							$pos[1] -= $this->page_setup['sheet']['print_area'][1] - 1;

							$pos[2] -= $this->page_setup['sheet']['print_area'][0] - 1;
							$pos[3] -= $this->page_setup['sheet']['print_area'][1] - 1;

							// exclude wsels out of Print Area
							if ($pos[2] < 0 || $pos[3] < 0 || $pos[0] >= $this->page_setup['sheet']['print_area'][2] || $pos[1] >= $this->page_setup['sheet']['print_area'][3])
								continue;
						}

						if (!isset($wselSearchArr[$pos[0]]))
							$wselSearchArr[$pos[0]] = array();
						if (!isset($wselSearchArr[$pos[0]][$pos[1]]))
							$wselSearchArr[$pos[0]][$pos[1]] = array();

						$wselSearchArr[$pos[0]][$pos[1]][] = array(
							'id' => $wsElem['e_id'],
							'type' => $wsElem['e_type'],
							'pos' => $pos,
							'offsets' => $wsElem['pos_offsets'],
							'width' => $wsElem['size'][0],
							'height' => $wsElem['size'][1],
							'payload' => (isset($wsElem['payload'])) ? $wsElem['payload'] : ''
						);
					}
				}
			}
		}

		return array('col_widths' => $col_widths, 'row_heights' => $row_heights, 'rows' => $rows, 'wsels' => $wselSearchArr);
	}

	protected function _create_xml_data_html()
	{
		// *** remove *** //
		if (!isset($this->wss_ajax))
		{
			$this->_gen_error_data('It\'s not possible to generate the report.');
			return;
		}

		// page setup
		$ps = $this->page_setup;

		// get all data needed for generating output from core
		$gridData = $this->_get_data();
		$wselSearchArr = &$gridData['wsels'];

		// Debug
//		die('<pre>' . print_r($gridData, true) . '</pre>');

		$xml_doc = new DOMDocument('1.0', 'utf-8');
		$xml_doc->preserveWhiteSpace = false;
		$xml_doc->resolveExternals = false;
		$xml_doc->substituteEntities = false;
		$xml_doc->loadXML('<?xml version="1.0" encoding="UTF-8"?><worksheet><pageproperties></pageproperties><sheetproperties></sheetproperties><grid></grid></worksheet>');

		$showErrors = true;
		if (isset($ps) && (strtoupper($ps['sheet']['cell_errors']) != 'DISPLAYED'))
		{
			$showErrors = false;
			$errorString = (strtoupper($ps['sheet']['cell_errors']) == 'BLANK') ? '' : $ps['sheet']['cell_errors'];
		}

		// Gridnlines
		$glns = (isset($ps) && $ps['sheet']['gridlines']);
		$pagepropertiesNode = $xml_doc->getElementsByTagName('pageproperties')->item(0);
		// add sheet
		$sheetElem = $xml_doc->createElement('sheet');
		$sheetElem->setAttribute('gridlines', (($glns) ? 'TRUE' : 'FALSE'));
		$pagepropertiesNode->appendChild($sheetElem);

		// generate grid data
		$heightsOfPages = array();
		$grid = $xml_doc->getElementsByTagName('grid')->item(0);

		// add charts node for HTML export
		if (count($wselSearchArr) > 0)
			$chartsNode = $grid->appendChild($xml_doc->createElement('charts'));

		if (is_array($gridData) && isset($gridData['rows']) && (count($gridData['rows']) > 0))
		{
			$additionalRows = array();
			$totalHeight = 0; $pageHeight = 0;
			$bordersStore = array(); $wselStore = array();
			for ($i=0; $i<count($gridData['rows']); $i++)
			{
				$rowElem = $xml_doc->createElement('row');
				$rowElem->setAttribute('height', $gridData['row_heights'][$i] . 'px');
				$totalHeight += $gridData['row_heights'][$i];
				$pageHeight += $gridData['row_heights'][$i];

				$cells = $rowElem->appendChild($xml_doc->createElement('cells'));

				$pageNum = 0; $pageWidth = 0; $totalWidth = 0;
				for ($j=0; $j<count($gridData['col_widths']); $j++)
				{
					$totalWidth += $gridData['col_widths'][$j];
					$pageWidth += $gridData['col_widths'][$j];

					if (!isset($gridData['rows'][$i][$j]['m']) || (isset($gridData['rows'][$i][$j]['m']) && ($gridData['rows'][$i][$j]['m'][0])))
					{
						$cellElem = $xml_doc->createElement('cell');

						// MERGE
						$lastCellSize = array($gridData['col_widths'][$j], $gridData['row_heights'][$i]);
						if (isset($gridData['rows'][$i][$j]['m']))
						{
							$lastCellSize = $this->_getMergedCellSize(
								array($i, $j),
								array($gridData['rows'][$i][$j]['m'][1], $gridData['rows'][$i][$j]['m'][2]),
								$gridData['row_heights'],
								$gridData['col_widths']
							);

							$cellElem->setAttribute('colspan', $gridData['rows'][$i][$j]['m'][2]);
							$cellElem->setAttribute('rowspan', $gridData['rows'][$i][$j]['m'][1]);

							$cellElem->setAttribute('width', $lastCellSize[0] . 'px');
							$cellElem->setAttribute('height', $lastCellSize[1] . 'px');
						}
						else
							$cellElem->setAttribute('width', self::_px2pt($lastCellSize[0]) . 'pt');

						if (count($gridData['rows'][$i][$j]) != 0)
						{
							$styles = $this->default_styles;

							if ($gridData['rows'][$i][$j]['t'] == 's')
								$styles['text-align'] = 'left';
							else if ($gridData['rows'][$i][$j]['t'] == 'n')
								$styles['text-align'] = 'right';
							else if ($gridData['rows'][$i][$j]['t'] == 'b')
								$styles['text-align'] = 'center';

							// Add grid styles to cell
							if ($glns && $gridData['col_widths'][$j] > 0 && $gridData['row_heights'][$i] > 0)
								foreach($this->gridline_style as $gl_sn => $gl_s)
									$styles[$gl_sn] = $gl_s;

							if (isset($gridData['rows'][$i][$j]['s']))
								$styles = $this->_parseStyle($gridData['rows'][$i][$j]['s'], $styles);

							// font size adjustment
							if (strpos($styles['font-size'], 'pt') === false)
								$styles['font-size'] .= 'pt';
							if (isset($fontSizeAdjuster))
								$styles['font-size'] = strval(intval(substr($styles['font-size'], 0, -2)) * $fontSizeAdjuster) . 'pt';

							$this->_storeBorderStyles($bordersStore, $pageNum, $gridData['rows'][$i][$j]['s'], $pageWidth, $pageHeight, $gridData['col_widths'][$j], $gridData['row_heights'][$i]);

							foreach($styles as $styleName => $styleValue)
							{
								$tmpStyleValue = $this->_checkStyle($styleName, $styleValue);
								$cellElem->setAttribute($styleName, $tmpStyleValue);
							}
						}
						else if ($glns && $gridData['col_widths'][$j] > 0 && $gridData['row_heights'][$i] > 0)
							foreach($this->gridline_style as $gl_sn => $gl_s)
								$cellElem->setAttribute($gl_sn, $gl_s);

						if (isset($gridData['rows'][$i][$j]['t']) && $gridData['rows'][$i][$j]['t'] == 'h' && isset($gridData['rows'][$i][$j]['v']))
							$gridData['rows'][$i][$j]['v'] = strip_tags($gridData['rows'][$i][$j]['v'], '<img>');

						if (isset($gridData['rows'][$i][$j]['t']) && $gridData['rows'][$i][$j]['t'] == 'h')
						{
							try
							{
								$tmpDomDoc = new DOMDocument();
								$tmpDomDoc->loadHTML($gridData['rows'][$i][$j]['v']);

								$valElem = $xml_doc->createElement('value');
								if ($tmpDomDoc->documentElement->firstChild->firstChild == null)
									throw new Exception();

								// If value is String 'P' tag will be added, that need to be taken in consideration
								if ($tmpDomDoc->documentElement->firstChild->firstChild->tagName == 'p')
									$valElem->appendChild($xml_doc->importNode($tmpDomDoc->documentElement->firstChild->firstChild->firstChild, true));
								else
									$valElem->appendChild($xml_doc->importNode($tmpDomDoc->documentElement->firstChild->firstChild, true));

								$cellElem->appendChild($valElem);
							}
							catch(Exception $e)
							{
								$cellElem->appendChild($xml_doc->createElement('value', ''));
							}
						}
						else
							$cellElem->appendChild($xml_doc->createElement('value', ((count($gridData['rows'][$i][$j]) == 0) ? '' :
								(($showErrors) ? $gridData['rows'][$i][$j]['v'] :
//									((in_array($gridData['rows'][$i][$j]['v'], $this->error_values)) ?
									((strpos($gridData['rows'][$i][$j]['v'], '#') === 0) ?
										$errorString :
										$gridData['rows'][$i][$j]['v']
									)
								)
							)));

						$cells->appendChild($cellElem);
					}
					else if (isset($gridData['rows'][$i][$j]['m']) && isset($gridData['rows'][$i][$j]['s']))
						$this->_storeBorderStyles($bordersStore, $pageNum, $gridData['rows'][$i][$j]['s'], $pageWidth, $pageHeight, $gridData['col_widths'][$j], $gridData['row_heights'][$i]);

					// adding charts and images
					if ((count($wselSearchArr) > 0) && isset($wselSearchArr[$j]) && isset($wselSearchArr[$j][$i]))
					{
						foreach ($wselSearchArr[$j][$i] as $wsElem)
						{
							$chartElem = $xml_doc->createElement('chart');

							$posLeft = $pageWidth - $gridData['col_widths'][$j] + $wsElem['offsets'][0] - 1;
							$posTop = $pageHeight - $gridData['row_heights'][$i] + $wsElem['offsets'][1] - 1;

							$chartElem->setAttribute('width', self::_px2pt($wsElem['width']) . 'pt');
							$chartElem->setAttribute('height', self::_px2pt($wsElem['height']) . 'pt');

							$chartElem->setAttribute('left', self::_px2pt($posLeft));
							$chartElem->setAttribute('top', self::_px2pt($posTop));

							$chartElem->setAttribute('src', $this->chart_url . 'wam=' . $_GET['wam'] . '&t=' . $wsElem['type'] . '&id=' . $wsElem['id'] . '&ts=' . (microtime(true) * 1000));
							$chartsNode->appendChild($chartElem);
						}
					}
				}

				if (!isset($additionalRows[$pageNum]))
					$additionalRows[$pageNum] = array();

				$additionalRows[$pageNum][$i] = $rowElem;
			}
			$heightsOfPages[] = $pageHeight;

			$rows = $grid->appendChild($xml_doc->createElement('rows'));
			$col_widths = $rows->appendChild($xml_doc->createElement('col_widths'));
			for ($i=0; $i<count($gridData['col_widths']); $i++)
			{
				$col_w = $xml_doc->createElement('col_w');
				$col_w->setAttribute('w', $gridData['col_widths'][$i] . 'px');
				$col_widths->appendChild($col_w);
			}

			for ($pageNum=0; $pageNum<count($additionalRows); $pageNum++)
				for ($i=0; $i<count($additionalRows[$pageNum]); $i++)
					$rows->appendChild($additionalRows[$pageNum][$i]);
		}

		// setup main table width
		$totalWidth = 0;
		for ($i=0; $i<count($gridData['col_widths']); $i++)
			$totalWidth += $gridData['col_widths'][$i];

		$grid->setAttribute('width', ($totalWidth) . 'px');

		$this->data_xml = $xml_doc;
	}

	protected function _create_xml_data_pdf()
	{
		// *** remove *** //
		if (!isset($this->wss_ajax))
		{
			$this->_gen_error_data('It\'s not possible to generate the report.');
			return;
		}

		// page setup
		$ps = $this->page_setup;

		// workbook setup
		$wbs = $this->wb_page_setup;

		// get all data needed for generating output from core
		$gridData = $this->_get_data();
		$wselSearchArr = &$gridData['wsels'];

		// Debug
//		die('<pre>' . print_r($gridData, true) . '</pre>');

		$xml_doc = new DOMDocument('1.0', 'utf-8');
		$xml_doc->preserveWhiteSpace = false;
		$xml_doc->resolveExternals = false;
		$xml_doc->substituteEntities = false;
		$xml_doc->loadXML('<?xml version="1.0" encoding="UTF-8"?><worksheet><pageproperties></pageproperties><sheetproperties></sheetproperties><grid></grid></worksheet>');

		$showErrors = true;
		if (isset($ps) && (strtoupper($ps['sheet']['cell_errors']) != 'DISPLAYED'))
		{
			$showErrors = false;
			$errorString = (strtoupper($ps['sheet']['cell_errors']) == 'BLANK') ? '' : $ps['sheet']['cell_errors'];
		}

		// setup page size/margins/header-footer size
		if (isset($ps) && ($ps['page']['paper_size'] == 'A4'))
		{
			$pageW = self::PDF_A4_PAGE_PX_WIDTH * self::PX2PT / self::INCH2PT; // in inches
			$pageH = self::PDF_A4_PAGE_PX_HEIGHT * self::PX2PT / self::INCH2PT; // in inches
		}
		else
		{
			$pageW = self::PDF_LETTER_PAGE_PX_WIDTH * self::PX2PT / self::INCH2PT; // in inches
			$pageH = self::PDF_LETTER_PAGE_PX_HEIGHT * self::PX2PT / self::INCH2PT; // in inches
		}

		// landscape
		if (!isset($ps) || !$ps['page']['portrait'])
		{
			$tmp = $pageW;
			$pageW = $pageH;
			$pageH = $tmp;
		}

		// values are in inches (default values are used in case, that there is no page setup values)
		$margins = array(
			'top' => (isset($ps) ? $ps['margins']['top'] : $this->default_margins['top']),
			'bottom' => (isset($ps) ? $ps['margins']['bottom'] : $this->default_margins['bottom']),
			'left' => (isset($ps) ? $ps['margins']['left'] : $this->default_margins['left']),
			'right' => (isset($ps) ? $ps['margins']['right'] : $this->default_margins['right']),
			'header' => (isset($ps) ? $ps['margins']['header'] : $this->default_margins['header']),
			'footer' => (isset($ps) ? $ps['margins']['footer'] : $this->default_margins['footer'])
		);

		// init some "constant" variables
		$pageBodyWpx = floor(($pageW - $margins['left'] - $margins['right']) * self::INCH2PT / self::PX2PT);
		$pageBodyHpx = floor(($pageH - $margins['top'] - $margins['bottom']) * self::INCH2PT / self::PX2PT);

		// Gridnlines
		$glns = (isset($ps) && $ps['sheet']['gridlines']);

		// Adjust col/row width/height Size
		$sizeAdjuster = 1;
		if (!isset($ps) || $ps['page']['fit']['enabled'])
		{
			// cols
			$totalW = ($glns) ? (self::GRIDLINE_BORDER_SIZE * 2) / self::PX2PT : 1;
			for ($i=0; $i<count($gridData['col_widths']); $i++)
				$totalW += $gridData['col_widths'][$i] + (($glns && $gridData['col_widths'][$i] > 0) ? self::GRIDLINE_SIZE * 2 / self::PX2PT : 0);

			// rows
			$totalH = ($glns) ? (self::GRIDLINE_BORDER_SIZE * 2) / self::PX2PT : 1;
			for ($i=0; $i<count($gridData['row_heights']); $i++)
				$totalH += $gridData['row_heights'][$i] + (($glns && $gridData['row_heights'][$i] > 0) ? self::GRIDLINE_SIZE * 2 / self::PX2PT : 0);

			if (($totalW != 0) && ($totalH != 0))
			{
				$wCoeff = $pageBodyWpx * ((isset($ps)) ? $ps['page']['fit']['wide'] : 1) / $totalW;
				$hCoeff = $pageBodyHpx * ((isset($ps)) ? $ps['page']['fit']['tall'] : 1) / $totalH;

				if ((0 < $wCoeff && $wCoeff < 1) || (0 < $hCoeff && $hCoeff < 1))
				{
					$sizeAdjuster = (($wCoeff < $hCoeff) ? $wCoeff : $hCoeff);
					if ($sizeAdjuster == 0)
						$sizeAdjuster = (($wCoeff > $hCoeff) ? $wCoeff : $hCoeff);
					$fontSizeAdjuster = $sizeAdjuster;
				}
			}
		}
		else if (isset($ps) && $ps['page']['adjust']['enabled'] && ($ps['page']['adjust']['size'] != 100))
		{
			$sizeAdjuster = $ps['page']['adjust']['size'] / 100;
			$fontSizeAdjuster = $sizeAdjuster;
		}

		// adjust sizes
		if ($sizeAdjuster != 1 || $glns)
		{
			// cols
			for ($i=0; $i<count($gridData['col_widths']); $i++)
				$gridData['col_widths'][$i] *= $sizeAdjuster;

			// rows
			for ($i=0; $i<count($gridData['row_heights']); $i++)
			{
				$gridData['row_heights'][$i] *= $sizeAdjuster;
				if ($glns && $gridData['row_heights'][$i] > 0)
					$gridData['row_heights'][$i] -= self::GRIDLINE_SIZE / self::PX2PT;
			}
		}

		$pagepropertiesNode = $xml_doc->getElementsByTagName('pageproperties')->item(0);
		// add page size to XML
		$pageElem = $xml_doc->createElement('page');
		$pageElem->setAttribute('width', $pageW . 'in');
		$pageElem->setAttribute('height', $pageH . 'in');
		$pagepropertiesNode->appendChild($pageElem);
		// add margins to XML
		$marginsElem = $xml_doc->createElement('margins');
		$marginsElem->setAttribute('top', $margins['top'] . 'in');
		$marginsElem->setAttribute('bottom', $margins['bottom'] . 'in');
		$marginsElem->setAttribute('left', $margins['left'] . 'in');
		$marginsElem->setAttribute('right', $margins['right'] . 'in');
		$marginsElem->setAttribute('header', $margins['header'] . 'in');
		$marginsElem->setAttribute('footer', $margins['footer'] . 'in');

		$header_h = ($margins['top'] - $margins['header']) / (isset($wbs['wb']['header']) ? 2 : 1);
		$marginsElem->setAttribute('total_header', (($margins['top'] > $margins['header']) ? $margins['top'] : $margins['header']) . 'in');
		$marginsElem->setAttribute('header_height', (($margins['top'] > $margins['header']) ? $header_h : 0) . 'in');
		$marginsElem->setAttribute('wb_header_height', ((isset($wbs['wb']['header']) && $margins['top'] > $margins['header']) ? $header_h : 0) . 'in');

		$marginsElem->setAttribute('total_footer', (($margins['bottom'] > $margins['footer']) ? $margins['bottom'] : ($margins['footer'] + self::MAX_FOOTER_LINE_HEIGHT)) . 'in');
		$marginsElem->setAttribute('footer_height', (($margins['bottom'] > $margins['footer']) ? $margins['bottom'] - $margins['footer'] : self::MAX_FOOTER_LINE_HEIGHT) . 'in');
		$marginsElem->setAttribute('vertical_center', ((isset($ps) && $ps['margins']['vert']) ? 'TRUE' : 'FALSE'));
		$marginsElem->setAttribute('horizontal_center', ((isset($ps) && $ps['margins']['horiz']) ? 'TRUE' : 'FALSE'));

		// set start number for pages
		$pageElem->setAttribute('first_page_number', (((isset($ps) && (strtoupper($ps['page']['first_page']) === 'AUTO')) || (!isset($ps))) ? 1 : $ps['page']['first_page']));

		$pagepropertiesNode->appendChild($marginsElem);
		// add sheet
		$sheetElem = $xml_doc->createElement('sheet');
		$sheetElem->setAttribute('gridlines', (($glns) ? 'TRUE' : 'FALSE'));
		$pagepropertiesNode->appendChild($sheetElem);

		// generate grid data
		$heightsOfPages = array();
		$grid = $xml_doc->getElementsByTagName('grid')->item(0);

		if (is_array($gridData) && isset($gridData['rows']) && (count($gridData['rows']) > 0))
		{
			$additionalRows = array();
			$totalHeight = 0; $pageHeight = 0;
			$bordersStore = array(); $wselStore = array();
			for ($i=0; $i<count($gridData['rows']); $i++)
			{
				$rowElem = $xml_doc->createElement('row');
				$rowElem->setAttribute('height', self::_px2pt($gridData['row_heights'][$i]) . 'pt');
				$totalHeight += $gridData['row_heights'][$i];
				$pageHeight += $gridData['row_heights'][$i];

				// Workaround for gridlines size
				if ($glns && $gridData['row_heights'][$i] > 0)
					$pageHeight += self::GRIDLINE_SIZE / self::PX2PT;

				if ($pageHeight > $pageBodyHpx && $i > 0)
				{
					$cellSize = array($gridData['col_widths'][$j - 1], $gridData['row_heights'][$i - 1]);
					if (isset($gridData['rows'][$i - 1][$j - 1]['m']) && !$gridData['rows'][$i - 1][$j - 1]['m'][0])
					{
						$cellSize = $this->_getMergedCellSize(
							array($gridData['rows'][$i - 1][$j - 1]['m'][1], $gridData['rows'][$i - 1][$j - 1]['m'][2]),
							array($i - $gridData['rows'][$i - 1][$j - 1]['m'][1], $j - $gridData['rows'][$i - 1][$j - 1]['m'][2]),
							$gridData['row_heights'],
							$gridData['col_widths']
						);
						$cellElem = $gridData['rows'][$i - 1][$j - 1]['m']['cell_elem'];
					}

					$this->_addBorderBoxes(
						$xml_doc,
						$cellElem,
						$bordersStore[$pageNum],
						$pageWidth - $cellSize[0],
						$pageHeight - $cellSize[1] - $gridData['row_heights'][$i],
						$glns
					);
					$this->_addWsels(
						$xml_doc,
						$cellElem,
						$wselStore,
						$pageNum,
						$pageWidth - $cellSize[0],
						$pageHeight - $cellSize[1] - $gridData['row_heights'][$i],
						$cellSize[0],
						$cellSize[1],
						$sizeAdjuster
					);

					$heightsOfPages[] = $pageHeight - $gridData['row_heights'][$i];
					$pageHeight = $gridData['row_heights'][$i];
				}

				$cells = $rowElem->appendChild($xml_doc->createElement('cells'));

				$pageNum = 0; $pageWidth = 0; $totalWidth = 0;
				for ($j=0; $j<count($gridData['col_widths']); $j++)
				{
					$totalWidth += $gridData['col_widths'][$j];
					$pageWidth += $gridData['col_widths'][$j];

					if ($pageWidth > $pageBodyWpx && $j > 0)
					{
						if ((isset($gridData['row_heights'][$i + 1]) && ($pageHeight + $gridData['row_heights'][$i + 1] > $pageBodyHpx)) || !isset($gridData['row_heights'][$i + 1]))
						{
							$cellSize = array($gridData['col_widths'][$j - 1], $gridData['row_heights'][$i]);
							if (isset($gridData['rows'][$i][$j - 1]['m']) && !$gridData['rows'][$i][$j - 1]['m'][0])
							{
								$cellSize = $this->_getMergedCellSize(
									array($gridData['rows'][$i][$j - 1]['m'][1], $gridData['rows'][$i][$j - 1]['m'][2]),
									array($i - $gridData['rows'][$i][$j - 1]['m'][1] + 1, $j - $gridData['rows'][$i][$j - 1]['m'][2]),
									$gridData['row_heights'],
									$gridData['col_widths']
								);
								$cellElem = $gridData['rows'][$i][$j - 1]['m']['cell_elem'];
							}

							$this->_addBorderBoxes(
								$xml_doc,
								$cellElem,
								$bordersStore[$pageNum],
								$pageWidth - $cellSize[0] - $gridData['col_widths'][$j],
								$pageHeight - $cellSize[1],
								$glns
							);
							$this->_addWsels(
								$xml_doc,
								$cellElem,
								$wselStore,
								$pageNum,
								$pageWidth - $cellSize[0] - $gridData['col_widths'][$j],
								$pageHeight - $cellSize[1],
								$cellSize[0],
								$cellSize[1],
								$sizeAdjuster
							);
						}

						if (!isset($additionalRows[$pageNum]))
							$additionalRows[$pageNum] = array();

						$additionalRows[$pageNum][$i] = $rowElem;

						$rowElem = $xml_doc->createElement('row');
						$rowElem->setAttribute('height', self::_px2pt($gridData['row_heights'][$i]) . 'pt');

						$cells = $rowElem->appendChild($xml_doc->createElement('cells'));

						$pageNum++;
						$pageWidth = $gridData['col_widths'][$j];
					}

					if (!isset($gridData['rows'][$i][$j]['m']) || (isset($gridData['rows'][$i][$j]['m']) && ($gridData['rows'][$i][$j]['m'][0])))
					{
						$cellElem = $xml_doc->createElement('cell');

						// MERGE
						$lastCellSize = array($gridData['col_widths'][$j], $gridData['row_heights'][$i]);
						if (isset($gridData['rows'][$i][$j]['m']))
						{
							$this->_fixMergedCell($gridData, $cellElem, $i, $j, $pageWidth, $pageHeight, $pageBodyWpx, $pageBodyHpx);
							$cellElem->setAttribute('colspan', $gridData['rows'][$i][$j]['m']['colspan']);
							$cellElem->setAttribute('rowspan', $gridData['rows'][$i][$j]['m']['rowspan']);

							$lastCellSize = $this->_getMergedCellSize(
								array($i, $j),
								array($gridData['rows'][$i][$j]['m'][1], $gridData['rows'][$i][$j]['m'][2]),
								$gridData['row_heights'],
								$gridData['col_widths']
							);

							$cellElem->setAttribute('m_width', self::_px2pt($lastCellSize[0]) - 4); // - 4pt is because of left-padding and right-padding
							$cellElem->setAttribute('m_height', self::_px2pt($lastCellSize[1]));
						}
						else
							$cellElem->setAttribute('width', self::_px2pt($lastCellSize[0]) . 'pt');

						if (count($gridData['rows'][$i][$j]) != 0)
						{
							$styles = $this->default_styles;

							if ($gridData['rows'][$i][$j]['t'] == 's')
								$styles['text-align'] = 'left';
							else if ($gridData['rows'][$i][$j]['t'] == 'n')
								$styles['text-align'] = 'right';
							else if ($gridData['rows'][$i][$j]['t'] == 'b')
								$styles['text-align'] = 'center';

							if (isset($gridData['rows'][$i][$j]['s']))
							{
								$styles = $this->_parseStyle($gridData['rows'][$i][$j]['s'], $styles);

								// Remove Border Styles and Apply border styles if gridline is selected
								foreach (array('border-top', 'border-left', 'border-bottom', 'border-right') as $borderName)
									if (isset($styles[$borderName]))
										unset($styles[$borderName]);
							}

							// Add grid styles to cell
							if ($glns && $gridData['col_widths'][$j] > 0 && $gridData['row_heights'][$i] > 0)
								foreach($this->gridline_style as $gl_sn => $gl_s)
									$styles[$gl_sn] = $gl_s;

							// Adjustment for TEXT WRAP for PDF
							if (isset($styles['white-space']) && $styles['white-space'] == 'nowrap' &&
								isset($styles['text-align']) && $styles['text-align'] != 'left' &&
								strpos($gridData['rows'][$i][$j]['s'], 'white-space') !== false
							)
								$styles['text-align'] = 'left';

							// font size adjustment
							if (strpos($styles['font-size'], 'pt') === false)
								$styles['font-size'] .= 'pt';
							if (isset($fontSizeAdjuster))
								$styles['font-size'] = strval(intval(substr($styles['font-size'], 0, -2)) * $fontSizeAdjuster) . 'pt';

							$this->_storeBorderStyles($bordersStore, $pageNum, $gridData['rows'][$i][$j]['s'], $pageWidth, $pageHeight, $gridData['col_widths'][$j], $gridData['row_heights'][$i]);

							foreach($styles as $styleName => $styleValue)
							{
								$tmpStyleValue = $this->_checkStyle($styleName, $styleValue);
								$cellElem->setAttribute($styleName, $tmpStyleValue);
							}
						}
						else if ($glns && $gridData['col_widths'][$j] > 0 && $gridData['row_heights'][$i] > 0)
							foreach($this->gridline_style as $gl_sn => $gl_s)
								$cellElem->setAttribute($gl_sn, $gl_s);

						if (isset($gridData['rows'][$i][$j]['t']) && $gridData['rows'][$i][$j]['t'] == 'h' && isset($gridData['rows'][$i][$j]['v']))
							$gridData['rows'][$i][$j]['v'] = strip_tags($gridData['rows'][$i][$j]['v'], '<img>');

						if (isset($gridData['rows'][$i][$j]['t']) && $gridData['rows'][$i][$j]['t'] == 'h' && strpos($gridData['rows'][$i][$j]['v'], '<') === 0)
						{
							if (!empty($gridData['rows'][$i][$j]['v']))
							{
								try
								{
									$tmpDomDoc = new DOMDocument('1.0', 'utf-8');
									$tmpDomDoc->loadHTML($gridData['rows'][$i][$j]['v']);

									$valElem = $xml_doc->createElement('value');
									if ($tmpDomDoc->documentElement->firstChild->firstChild == null)
										throw new Exception();
									$hElem = $tmpDomDoc->documentElement->firstChild->firstChild;

									// If value is String 'P' tag will be added, that need to be taken in consideration
									if ($hElem->tagName == 'p')
										$hElem = $hElem->firstChild;

									if ($hElem->tagName == 'img')
									{
										// src path - get image and do base64 encode
										if (($imgSrc = $hElem->getAttribute('src')) != '' && stripos($imgSrc, 'data:image') === false)
										{
											$imgUrl = self::rel2abs($imgSrc, $this->home_url . '/ui/wss/');
											$imgUrl = str_ireplace($this->home_url, getenv("DOCUMENT_ROOT"), $imgUrl);
											$img = imagecreatefromstring(file_get_contents($imgUrl));

											$hElem->getAttribute('height', imagesy($img));
											$hElem->getAttribute('width', imagesx($img));

											ob_start();
											imagepng($img);
											$imgData = ob_get_contents();
											ob_end_clean();
											imagedestroy($img);

											$hElem->setAttribute('src', self::getImageB64Src($imgData));
										}

										if (($hAttr = $hElem->getAttribute('height')) != '' && ($wAttr = $hElem->getAttribute('width')) != '')
										{
											$httpImgH = intval($hAttr);
											$httpImgW = intval($wAttr);
										}
										else if (($imgSrc = $hElem->getAttribute('src')) != '' && stripos($imgSrc, 'data:image') === 0)
										{
											$spImgSrc = explode(',', $imgSrc);
											if (isset($spImgSrc[1]) && !empty($spImgSrc[1]) && ($binImg = base64_decode($spImgSrc[1])) !== false && ($gdImg = imagecreatefromstring($binImg)) !== false)
											{
												$httpImgH = imagesy($gdImg);
												$httpImgW = imagesx($gdImg);
											}
										}

										if (isset($httpImgH) && isset($httpImgW))
										{
											$cellElem->setAttribute('m_width', self::_px2pt($lastCellSize[0]) - 2);
											$cellElem->setAttribute('m_height', self::_px2pt($lastCellSize[1]));

											$hElem->setAttribute('height', (self::_px2pt($httpImgH) * $sizeAdjuster));
											$hElem->setAttribute('width', (self::_px2pt($httpImgW) * $sizeAdjuster));

											unset($httpImgH);
											unset($httpImgW);
										}
										else
											$hElem->setAttribute('content-height', round(100 * $sizeAdjuster) . '%');
									}

									$valElem->appendChild($xml_doc->importNode($hElem, true));
									$cellElem->appendChild($valElem);
								}
								catch(Exception $e)
								{
									$cellElem->appendChild($xml_doc->createElement('value', ''));
								}
							}
							else
								$cellElem->appendChild($xml_doc->createElement('value', ''));
						}
						else
							$cellElem->appendChild($xml_doc->createElement('value', ((count($gridData['rows'][$i][$j]) == 0) ? '' :
								(($showErrors) ?
									self::xmlentities($gridData['rows'][$i][$j]['v']) :
//									((in_array($gridData['rows'][$i][$j]['v'], $this->error_values)) ?
									((strpos($gridData['rows'][$i][$j]['v'], '#') === 0) ?
										$errorString :
										self::xmlentities($gridData['rows'][$i][$j]['v'])
									)
								)
							)));

						$cells->appendChild($cellElem);
					}
					else if (isset($gridData['rows'][$i][$j]['m']) && isset($gridData['rows'][$i][$j]['s']))
						$this->_storeBorderStyles($bordersStore, $pageNum, $gridData['rows'][$i][$j]['s'], $pageWidth, $pageHeight, $gridData['col_widths'][$j], $gridData['row_heights'][$i]);

					// adding charts and images
					if ((count($wselSearchArr) > 0) && isset($wselSearchArr[$j]) && isset($wselSearchArr[$j][$i]))
						$this->_storeWsel($wselStore, $pageNum, $wselSearchArr[$j][$i], $pageWidth - $gridData['col_widths'][$j], $pageHeight - $gridData['row_heights'][$i]);
				}

				if (!isset($additionalRows[$pageNum]))
					$additionalRows[$pageNum] = array();

				$additionalRows[$pageNum][$i] = $rowElem;
			}
			$heightsOfPages[] = $pageHeight;

			// Add border boxes to last cell

			$cellSize = array($gridData['col_widths'][$j - 1], $gridData['row_heights'][$i - 1]);
			if (isset($gridData['rows'][$i - 1][$j - 1]['m']) && !$gridData['rows'][$i - 1][$j - 1]['m'][0])
			{
				$cellSize = $this->_getMergedCellSize(
					array($gridData['rows'][$i - 1][$j - 1]['m'][1], $gridData['rows'][$i - 1][$j - 1]['m'][2]),
					array($i - $gridData['rows'][$i - 1][$j - 1]['m'][1], $j - $gridData['rows'][$i - 1][$j - 1]['m'][2]),
					$gridData['row_heights'],
					$gridData['col_widths']
				);
				$cellElem = $gridData['rows'][$i - 1][$j - 1]['m']['cell_elem'];
			}

			$this->_addBorderBoxes(
				$xml_doc,
				$cellElem,
				$bordersStore[$pageNum],
				$pageWidth - $cellSize[0],
				$pageHeight - $cellSize[1],
				$glns
			);
			$this->_addWsels(
				$xml_doc,
				$cellElem,
				$wselStore,
				$pageNum,
				$pageWidth - $cellSize[0],
				$pageHeight - $cellSize[1],
				$cellSize[0],
				$cellSize[1],
				$sizeAdjuster
			);

			$downThenOver = ((isset($ps)) ? $ps['sheet']['page_order'] : true);
			if ($downThenOver)
			{
				$colCount = 0;
				for ($pageNum=0; $pageNum<count($additionalRows); $pageNum++)
				{
					$col_widths = $xml_doc->createElement('col_widths');
					$pageWidth = 0;
					for (; $colCount < count($gridData['col_widths']); $colCount++)
					{
						$pageWidth += $gridData['col_widths'][$colCount];
						if (($pageWidth > $pageBodyWpx) && ($colCount > 0))
						{
							$pageWidth -= $gridData['col_widths'][$colCount];
							break;
						}
						else
						{
							$col_w = $xml_doc->createElement('col_w');
							$col_w->setAttribute('w', self::_px2pt($gridData['col_widths'][$colCount]) . 'pt');
							$col_widths->appendChild($col_w);
						}
					}

					$rows = $xml_doc->createElement('rows');
					if ($pageNum < (count($additionalRows) - 1))
						$rows->setAttribute('page_breaker', 'page');
					$rows->setAttribute('rows_width', self::_px2pt($pageWidth) . 'pt');
					$rows->setAttribute('space_width', self::_px2pt(($pageBodyWpx - $pageWidth) / 2));
					$pageHeightIndex = 0;
					$rows->setAttribute('space_height', self::_px2pt(($pageBodyHpx - $heightsOfPages[$pageHeightIndex++]) / 2));
					$rows = $grid->appendChild($rows);

					$rows->appendChild($col_widths);

					$pageHeight = 0;
					for ($i=0; $i<count($additionalRows[$pageNum]); $i++)
					{
						$pageHeight += $gridData['row_heights'][$i];
						// Workaround for gridlines size
						if ($glns && $gridData['row_heights'][$i] > 0)
							$pageHeight += self::GRIDLINE_SIZE / self::PX2PT;

						if (($pageHeight > $pageBodyHpx) && ($i > 0))
						{
							$pageHeight = $gridData['row_heights'][$i];

							$rows = $xml_doc->createElement('rows');
							if ($pageNum < (count($additionalRows) - 1))
								$rows->setAttribute('page_breaker', 'page');
							$rows->setAttribute('rows_width', self::_px2pt($pageWidth) . 'pt');
							$rows->setAttribute('space_width', self::_px2pt(($pageBodyWpx - $pageWidth) / 2));
							$rows->setAttribute('space_height', self::_px2pt(($heightsOfPages[$pageHeightIndex++]) / 2)); // set space for verticaly centered
							$rows = $grid->appendChild($rows);
							$rows->appendChild($col_widths->cloneNode(TRUE));
						}

						$rows->appendChild($additionalRows[$pageNum][$i]);
					}
				}
			}
			else
			{
				$pageNum = 0; $pageWidth = 0; $pageColWidths = array(); $pageWidths = array();
				for ($i=0; $i<count($gridData['col_widths']); $i++)
				{
					$pageWidth += $gridData['col_widths'][$i];
					if (($pageWidth > $pageBodyWpx) && ($i > 0))
					{
						$pageWidth -= $gridData['col_widths'][$i];
						$pageWidths[$pageNum] = $pageWidth;
						$pageNum++;
						$pageWidth = $gridData['col_widths'][$i];
					}

					if (!isset($pageColWidths[$pageNum]))
						$pageColWidths[$pageNum] = array();
					$pageColWidths[$pageNum][] = $gridData['col_widths'][$i];
				}
				$pageWidths[$pageNum] = $pageWidth;

				$strtRowId = 0; $pageHeight = 0; $pageHeightIndex = 0;
				for ($i=0; $i<count($gridData['row_heights']); $i++)
				{
					$pageHeight += $gridData['row_heights'][$i];
					// Workaround for gridlines size
					if ($glns && $gridData['row_heights'][$i] > 0)
						$pageHeight += self::GRIDLINE_SIZE / self::PX2PT;

					if (($pageHeight > $pageBodyHpx) || ($i == (count($gridData['row_heights']) - 1)))
					{
						for ($pageNum=0; $pageNum<count($additionalRows); $pageNum++)
						{
							$rows = $xml_doc->createElement('rows');
							if ($pageNum < (count($additionalRows) - 1))
								$rows->setAttribute('page_breaker', 'page');
							$rows->setAttribute('rows_width', self::_px2pt($pageWidths[$pageNum]) . 'pt');
							$rows->setAttribute('space_width', self::_px2pt(($pageBodyWpx - $pageWidth) / 2));
							$rows->setAttribute('space_height', self::_px2pt(($pageBodyHpx - $heightsOfPages[$pageHeightIndex++]) / 2));
							$rows = $grid->appendChild($rows);

							$col_widths = $rows->appendChild($xml_doc->createElement('col_widths'));
							$tmpCells = $pageColWidths[$pageNum];
							foreach ($tmpCells as $cellW)
							{
								$col_w = $xml_doc->createElement('col_w');
								$col_w->setAttribute('w', self::_px2pt($cellW) . 'pt');
								$col_widths->appendChild($col_w);
							}

							$lastRowId = (($i == (count($gridData['row_heights']) - 1)) ? ($i + 1) : $i);
							for ($j=$strtRowId; $j<$lastRowId; $j++)
								$rows->appendChild($additionalRows[$pageNum][$j]);
						}

						$strtRowId = $i;
						$pageHeight = $gridData['row_heights'][$i];
					}
				}
			}
		}

		// setup main table width
		$totalWidth = 0;
		for ($i=0; $i<count($gridData['col_widths']); $i++)
			$totalWidth += $gridData['col_widths'][$i];

		$grid->setAttribute('width', ($totalWidth) . 'px');

		if (isset($ps) && isset($ps['hf']))
			$hf = $ps['hf'];

		$sheetpropertiesNode = $xml_doc->getElementsByTagName('sheetproperties')->item(0);

		// Workbook Header
		$wb_header = $wbs['wb']['header'];
		$wb_headerElem = $xml_doc->createElement('wb_header');
		$wb_headerElem->setAttribute('show', (($this->show_header_footer & 0x04) ? 'TRUE' : 'FALSE'));
		$tmpElem = $xml_doc->createElement('left_field', $wb_header['left_value']);
		if (isset($wb_header))
			$this->_setHeaderFooterCellStyle($wb_header['left_style'], $tmpElem);
		$wb_headerElem->appendChild($tmpElem);
		$tmpElem = $xml_doc->createElement('right_field', $wb_header['right_value']);
		if (isset($wb_header))
			$this->_setHeaderFooterCellStyle($wb_header['right_style'], $tmpElem);
		$wb_headerElem->appendChild($tmpElem);
		$sheetpropertiesNode->appendChild($wb_headerElem);

		// Sheet Header&Footer
		$hfData = $this->_getHeaderFooterData($hf);
		// setting header
		$headerElem = $xml_doc->createElement('header');
		$headerElem->setAttribute('show', (($this->show_header_footer & 0x02) ? 'TRUE' : 'FALSE'));
		$tmpElem = $xml_doc->createElement('left_field', $hfData['header']['left']);
		if (isset($hf))
			$this->_setHeaderFooterCellStyle($hf['header']['left_style'], $tmpElem);
		$headerElem->appendChild($tmpElem);
		$tmpElem = $xml_doc->createElement('center_field', $hfData['header']['center']);
		if (isset($hf))
			$this->_setHeaderFooterCellStyle($hf['header']['center_style'], $tmpElem);
		$headerElem->appendChild($tmpElem);
		$tmpElem = $xml_doc->createElement('right_field', $hfData['header']['right']);
		if (isset($hf))
			$this->_setHeaderFooterCellStyle($hf['header']['right_style'], $tmpElem);
		$headerElem->appendChild($tmpElem);
		$sheetpropertiesNode->appendChild($headerElem);
		// setting footer
		$footerElem = $xml_doc->createElement('footer');
		$footerElem->setAttribute('show', (($this->show_header_footer & 0x01) ? 'TRUE' : 'FALSE'));
		$tmpElem = $xml_doc->createElement('left_field', $hfData['footer']['left']);
		if (isset($hf))
			$this->_setHeaderFooterCellStyle($hf['footer']['left_style'], $tmpElem);
		$footerElem->appendChild($tmpElem);
		$tmpElem = $xml_doc->createElement('center_field', $hfData['footer']['center']);
		if (isset($hf))
			$this->_setHeaderFooterCellStyle($hf['footer']['center_style'], $tmpElem);
		$footerElem->appendChild($tmpElem);
		$tmpElem = $xml_doc->createElement('right_field', $hfData['footer']['right']);
		if (isset($hf))
			$this->_setHeaderFooterCellStyle($hf['footer']['right_style'], $tmpElem);
		$footerElem->appendChild($tmpElem);
		$sheetpropertiesNode->appendChild($footerElem);

		$this->data_xml = $xml_doc;
	}

	private function _parseStyle($style, &$styles =null)
	{
		if (!is_array($styles))
			$styles = array();

		$dataStyles = explode(';', $style);
		for($i=0; $i<(count($dataStyles) - 1); $i++)
		{
			$styleArr = explode(':', $dataStyles[$i]);
			$styles[trim($styleArr[0])] = trim($styleArr[1]);
		}

		return $styles;
	}

	private function _gen_error_data($msg) {
		$initialXML = '<?xml version="1.0" encoding="UTF-8"?><message>' .
			'<img path="' . $this->imgs_url . 'warning.png" w="48px" h="48px"></img>' .
			'<text>' . $msg . '</text>' .
		'</message>';

		$this->data_xml = new DOMDocument();
		$this->data_xml->loadXML($initialXML);

		$this->type = self::TYPE_ERR;
	}

	private static function _px2pt($pixels)
	{
		return $pixels * self::PX2PT;
	}

	private function _getHeaderFooterData($hf)
	{
		$vars = array('&[Page]', '&[Pages]', '&[Date]', '&[Time]', '&[File]', '&[Tab]', '&[Picture]');
		$vals = array('#@|Page|@#', '#@|Pages|@#', date(self::HF_DATE), date(self::HF_TIME), '', '', '');

		// &[Tab]
		$worksheets = $this->wss_ajax->getSheets();
		$curr_wsid = $this->wss_ajax->getCurrWsId();
		for ($i=0; $i<count($worksheets[0]); $i+=2)
			if ($worksheets[0][$i] == $curr_wsid)
			{
				$vals[5] = $worksheets[0][$i + 1];
				break;
			}

		// &[File]
		$workbooks = $this->wss_ajax->getLoadedBooks();
		$curr_wbid = $this->wss_ajax->getCurrWbId();
		for ($i=0; $i<count($workbooks); $i++)
			if ($workbooks[$i][0] == $curr_wbid)
			{
				$vals[4] = $workbooks[$i][1];
				break;
			}

		// Page Setup Object
		return ( (isset($hf)) ?
			array(
				'header' => array('left' => str_replace($vars, $vals, $hf['header']['left_value']), 'center' => str_replace($vars, $vals, $hf['header']['center_value']), 'right' => str_replace($vars, $vals, $hf['header']['right_value'])),
				'footer' => array('left' => str_replace($vars, $vals, $hf['footer']['left_value']), 'center' => str_replace($vars, $vals, $hf['footer']['center_value']), 'right' => str_replace($vars, $vals, $hf['footer']['right_value']))
			) :
			array(
				'header' => array('left' => '', 'center' => '', 'right' => ''),
				'footer' => array('left' => '', 'center' => '', 'right' => '')
			)
		);
	}

	private function _setHeaderFooterCellStyle($style, $elem)
	{
		$styles = $this->_parseStyle($style);

		foreach($styles as $styleName => $styleValue)
		{
			$tmpStyleValue = $this->_checkStyle($styleName, $styleValue);
			$elem->setAttribute($styleName, $tmpStyleValue);
		}
	}

	private function _checkStyle($styleName, $styleValue)
	{
		switch ($styleName)
		{
			case 'background-image':
				if ($styleValue != 'none')
					return $this->home_url . substr($styleValue, 4, -1);
				break;

			case 'border-top':
			case 'border-left':
			case 'border-bottom':
			case 'border-right':
					$styleValue = str_replace('2px', '1.5pt', $styleValue);
					$styleValue = str_replace('1px', '0.75pt', $styleValue);
				break;
		}

		return $styleValue;
	}

	private function _getMergedCellSize($start, $size, $row_heights, $col_widths)
	{
		$h = 0;
		for ($i=$start[0]; $i<($start[0] + $size[0]); $i++)
			$h += $row_heights[$i];

		$w = 0;
		for ($i=$start[1]; $i<($start[1] + $size[1]); $i++)
			$w += $col_widths[$i];

		return array($w, $h);
	}

	private function _fixMergedCell(&$data, &$cellElement, $i, $j, $currPageW, $currPageH, $pageW, $pageH)
	{
		$numRows = $data['rows'][$i][$j]['m'][1];
		$numCols = $data['rows'][$i][$j]['m'][2];

		for ($ii=1; $ii<$numRows; $ii++)
		{
			$currPageH += $data['row_heights'][$i + $ii];
			if ($currPageH > $pageH)
			{
				$data['rows'][$i][$j]['m']['rowspan'] = $ii;
				$data['rows'][$i+$ii][$j]['m'][0] = 1;
				$data['rows'][$i+$ii][$j]['m'][1] = $data['rows'][$i][$j]['m'][1] - $ii;
				$data['rows'][$i+$ii][$j]['m'][2] = $data['rows'][$i][$j]['m'][2];
				break;
			}
		}

		if (!isset($data['rows'][$i][$j]['m']['rowspan']))
			$data['rows'][$i][$j]['m']['rowspan'] = $data['rows'][$i][$j]['m'][1];

		for ($jj=1; $jj<$numCols; $jj++)
		{
			$currPageW += $data['col_widths'][$j + $jj];
			if ($currPageW > $pageW)
			{
				$data['rows'][$i][$j]['m']['colspan'] = $jj;
				$data['rows'][$i][$j+$jj]['m'][0] = 1;
				$data['rows'][$i][$j+$jj]['m'][1] = $data['rows'][$i][$j]['m'][1];
				$data['rows'][$i][$j+$jj]['m'][2] = $data['rows'][$i][$j]['m'][2] - $jj;
				break;
			}
		}

		if (!isset($data['rows'][$i][$j]['m']['colspan']))
			$data['rows'][$i][$j]['m']['colspan'] = $data['rows'][$i][$j]['m'][2];

		// adjust cell pointers in child cells
		$numRows = $data['rows'][$i][$j]['m'][1];
		$numCols = $data['rows'][$i][$j]['m'][2];
		for ($ii=0; $ii<$numRows; $ii++)
			for ($jj=0; $jj<$numCols; $jj++)
				if (!$data['rows'][$i+$ii][$j+$jj]['m'][0])
				{
					$data['rows'][$i+$ii][$j+$jj]['m'][1] = $i;
					$data['rows'][$i+$ii][$j+$jj]['m'][2] = $j;
					$data['rows'][$i+$ii][$j+$jj]['m']['cell_elem'] = $cellElement;
				}
	}

	private function _storeBorderStyles(&$bordersStore, $pageNum, &$stylesString, $pageW, $pageH, $cellW, $cellH)
	{
		if ($cellW <= 0 || $cellH <= 0)
			return;

		$styles = array();
		$styles = $this->_parseStyle($stylesString, $styles);

		if (isset($styles['border-top']) || isset($styles['border-left']))
		{
			$broderRecord = array(
				'pos_x' => $pageW - $cellW,
				'pos_y' => $pageH - $cellH,
				'w' => self::_px2pt($cellW),
				'h' => self::_px2pt($cellH)
			);

			if (isset($styles['border-top']))
			{
				$broderRecord['border-top'] = $styles['border-top'];
				$broderRecord['pos_y'] += $this->_getBorderSize($styles['border-top']) / 2;
			}

			if (isset($styles['border-left']))
			{
				$broderRecord['border-left'] = $styles['border-left'];
				$broderRecord['pos_x'] += $this->_getBorderSize($styles['border-left']) / 2;
			}

			if (!isset($bordersStore[$pageNum]))
				$bordersStore[$pageNum] = array();
			$bordersStore[$pageNum][] = $broderRecord;
		}
	}

	private function _getBorderSize($borderStyle)
	{
		if (strpos($borderStyle, '1px') !== false)
			return 1;
		else if (strpos($borderStyle, '2px') !== false)
			return 2;

		return 0;
	}

	private function _addBorderBoxes(&$xmlDoc, &$cellElem, &$bordersStore, $pageW, $pageH, $glns)
	{
		if (count($bordersStore) > 0)
		{
			foreach($bordersStore as $borderRecord)
			{
				$borderBox = $xmlDoc->createElement('border_box');

				// Fix offsets
				$borderRecord['pos_x'] = self::_px2pt($borderRecord['pos_x'] - $pageW) - 2; // 2pt - are beacuse of left/right padding inside of cell (padding is 2pt)
				$borderRecord['pos_y'] = self::_px2pt($borderRecord['pos_y'] - $pageH) + (($glns) ? self::GRIDLINE_SIZE : 0);

				foreach($borderRecord as $attName => $attValue)
				{
					if ($attName == 'border-top' || $attName == 'border-left')
						$attValue = $this->_checkStyle($attName, $attValue);
					$borderBox->setAttribute($attName, $attValue);
				}
				$cellElem->appendChild($borderBox);
			}

			// clear store
			$bordersStore = array();
		}
	}

	private function _storeWsel(&$wselStore, $pageNum, &$wsels, $pageW, $pageH)
	{
		if (!isset($wselStore[$pageNum]))
			$wselStore[$pageNum] = array();

		$wselStore[$pageNum][] = array('wsels' => $wsels, 'pos_x' => $pageW, 'pos_y' => $pageH);
	}

	private function _addWsels(&$xmlDoc, &$cellElem, &$wselStore, $pageNum, $pageW, $pageH, $cellW, $cellH, $sizeAdjuster)
	{
		$currWselStore = &$wselStore[$pageNum];
		$currWbId = $this->wss_ajax->getCurrWbId();
		$currWsId = $this->wss_ajax->getCurrWsId();

		if (count($currWselStore) > 0)
		{
			foreach($currWselStore as $wselsRecord)
			{
				foreach($wselsRecord['wsels'] as $wselRec)
				{
					$wselElem = $xmlDoc->createElement('wsel');

					// Catting sizes
					$cat_w = (isset($wselsRecord['cat_w']) ? $wselsRecord['cat_w'] : 0);
					$cat_h = (isset($wselsRecord['cat_h']) ? $wselsRecord['cat_h'] : 0);

					// Offsets
					$offest_w = ($cat_w != 0) ? 0 : ($wselRec['offsets'][0] * $sizeAdjuster);
					$offest_h = ($cat_h != 0) ? 0 : ($wselRec['offsets'][1] * $sizeAdjuster);

					// Set Offset Positions
					$wselElem->setAttribute('pos_x', self::_px2pt($wselsRecord['pos_x'] - $pageW + $offest_w) - 2); // 2pt - are beacuse of left/right padding inside of cell (padding is 2pt)
					$wselElem->setAttribute('pos_y', self::_px2pt($wselsRecord['pos_y'] - $pageH + $offest_h));

					// Define size of showing parts + add next parts to following pages
					$partW = $pageW + $cellW - $wselsRecord['pos_x'] - $offest_w;
					$partH = $pageH + $cellH - $wselsRecord['pos_y'] - $offest_h;

					// Total Wsel Size
					$wselW = $wselRec['width'] * $sizeAdjuster;
					$wselH = $wselRec['height'] * $sizeAdjuster;

					if ($partH >= $wselH)
						$partH = $wselH;
					else
					{
						if (!isset($addToSamePage))
							$addToSamePage = array();
						$addToSamePage[] = array(
							'wsels' => array($wselRec),
							'pos_x' => (($cat_w == 0) ? $wselsRecord['pos_x'] : 0),
							'pos_y' => 0,
							'cat_w' => $cat_w,
							'cat_h' => $partH + $cat_h
						);
					}

					if ($partW >= $wselW)
						$partW = $wselW;
					else if ($cat_h == 0) // $cat_h == 0 - makes no duplicates for bottom/right chank of Image
						$wselStore[$pageNum + 1][] = array('wsels' => array($wselRec), 'pos_x' => 0, 'pos_y' => $wselsRecord['pos_y'], 'cat_w' => $partW + $cat_w);

					// Size of Visible part of Image
					$wselElem->setAttribute('part_width', self::_px2pt($partW));
					$wselElem->setAttribute('part_height', self::_px2pt($partH));

					// Inner Box image positioning (for showing parts of image)
					$wselElem->setAttribute('inner_left', -self::_px2pt($cat_w));
					$wselElem->setAttribute('inner_top', -self::_px2pt($cat_h) - 1);

					$wselElem->setAttribute('width', self::_px2pt($wselW));
					$wselElem->setAttribute('height', self::_px2pt($wselH));

					if (strcasecmp($wselRec['type'], 'chart') == 0)
						$wselElem->setAttribute('src', self::getChartB64Src($wselRec['id']));
					else
						$wselElem->setAttribute('src', self::getImageB64Src(gzuncompress(base64_decode($wselRec['payload']))));

//					$wselElem->setAttribute('src', '\'' . $this->chart_url . 'wam=' . $_GET['wam'] . '&wbid=' . $currWbId . '&wsid=' . $currWsId . '&sid=' . session_id() . '&t=' . $wselRec['type'] . '&id=' . $wselRec['id'] . '&ts=' . (microtime(true) * 1000) . '\'');
					$cellElem->appendChild($wselElem);
				}
			}

			// clear store
			$currWselStore = array();

			// Add parts for Pages bellow
			if (isset($addToSamePage))
				$wselStore[$pageNum] = $addToSamePage;
		}
	}

	private static function xmlentities ($str)
	{
		return str_replace(array( '&', '"', '\'', '<', '>'), array( '&amp;', '&quot;', '&apos;', '&lt;', '&gt;'), $str);
	}

	private static function rel2abs($rel, $base)
	{
		if (parse_url($rel, PHP_URL_SCHEME) != '')
			return $rel;
		if ($rel[0]=='#' || $rel[0]=='?')
			return $base.$rel;

		/* parse base URL and convert to local variables: $scheme, $host, $path */
		extract(parse_url($base));

		$path = preg_replace('#/[^/]*$#', '', $path);
		if ($rel[0] == '/')
			$path = '';

		$abs = "$host$path/$rel";

		/* replace '//' or '/./' or '/foo/../' with '/' */
		$re = array('#(/\.?/)#', '#/(?!\.\.)[^/]+/\.\./#');
		for ($n=1; $n>0; $abs=preg_replace($re, '/', $abs, -1, $n)) {}

		return $scheme.'://'.$abs;
	}

	private function getChartB64Src($id)
	{
		$wsels = $this->wss_ajax->get_worksheet_elements();
		if (($chart = $wsels->get_element($this->wss_ajax->getCurrWbId(), $this->wss_ajax->getCurrWsId(), $id)) === false)
			return '';

		if (!function_exists('cdErrorHandler'))
			require 'chartdir/phpchartdir.php';

		$chartPrinter = new ChartPrinter($chart);
		$img = $chartPrinter->printChart('PNG', true);
		if (!empty($img))
			return 'data:image/png;base64,' . base64_encode($img);

		return '';
	}

	private static function getImageB64Src($img)
	{
		if (!empty($img))
			return 'data:image/png;base64,' . base64_encode($img);

		return '';
	}
}

?>
