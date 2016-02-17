<?php

/*
 * \brief Helper class used for formula rewriting when dynaranges expand or collapse.
 *
 * \file DynarangeDepsRewriter.php
 *
 * Copyright (C) 2006-2010 Jedox AG
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: DynarangeDepsRewriter.php 4320 2010-11-21 23:27:38Z predragm $
 *
 */

class DynarangeDepsRewriter
{
	const MAX_COL = 256;
	const MAX_ROW = 65536;

	const RE_DQUOTED = '/"[^"]*"/';
	const RE_SQUOTED = '/\'[^\']*\'(?!!)/';
	const RE_TOKENIZE = '/(?:[^\wŠšŸ§:\$!])((?:[a-zŠšŸ§][\wŠšŸ§]+!)|(?:\'[^\']+\'!))?(\$?[A-Z]+\$?[0-9]+)(:\$?[A-Z]+\$?[0-9]+)?(?![\wŠšŸ§:\$!])/i';
	const RE_SEPARATE = '/^(\$?)([A-Z]+)(\$?)([0-9]+)$/';

	private static $SEP = array(
	  'en_US' => ','
	, 'de_DE' => ';'
	, 'fr_FR' => ';'
	);

	private static $REF = array(
	  'en_US' => 'REF'
	, 'de_DE' => 'BEZUG'
	, 'fr_FR' => 'REF'
	);

	private static function _parseCellRef ($refstr)
	{
		if (!preg_match(self::RE_SEPARATE, $refstr, $refstr))
			return null;

		$col = Dynarange::ltrs2num($refstr[2]);
		$row = intval($refstr[4]);

		if ($col < 1 || $col > self::MAX_COL || $row < 1 || $row > self::MAX_ROW)
			return null;

		return array($col, $row, $refstr[1], $refstr[3]);
	}

	private static function _genPadding ($match)
	{
		return str_pad('', strlen($match[0]), ' ');
	}

	private static function _rewriteFormula ($sep, $fstr, array $srcCoords, $idxBase, array $incrs, $distance, $count)
	{
		for ($i = (int) preg_match_all(self::RE_TOKENIZE, preg_replace_callback(self::RE_SQUOTED, 'DynarangeDepsRewriter::_genPadding', preg_replace_callback(self::RE_DQUOTED, 'DynarangeDepsRewriter::_genPadding', $fstr)), $matches, PREG_SET_ORDER | PREG_OFFSET_CAPTURE) - 1;
				 $i >= 0; --$i)
		{
			$res = $matches[$i];

			if (($ul = $lr = self::_parseCellRef($res[2][0])) === null)
				continue;

			if (isset($res[3]))
			{
				if (($lr = self::_parseCellRef(ltrim($res[3][0], ':'))) === null)
					continue;

				if ($lr[0] < $ul[0] || $lr[1] < $ul[1])
				{
					$tmp = $ul;
					$ul = $lr;
					$lr = $tmp;
				}

				$isRange = true;
			}
			else
				$isRange = false;

			if ($ul[0] > $srcCoords[2] || $ul[1] > $srcCoords[3] || $lr[0] < $srcCoords[0] || $lr[1] < $srcCoords[1])
				continue;

			if ($ul[0] < $srcCoords[0])
				$ul[0] = $srcCoords[0];

			if ($ul[1] < $srcCoords[1])
				$ul[1] = $srcCoords[1];

			if ($lr[0] > $srcCoords[2])
				$lr[0] = $srcCoords[2];

			if ($lr[1] > $srcCoords[3])
				$lr[1] = $srcCoords[3];

			$ul[$idxBase] += $distance;
			$lr[$idxBase] += $distance;

			$csep = isset($res[1]) ? $sep . $res[1][0] : $sep;
			$refs = '';

			for ($c = 0; $c < $count; $ul[$idxBase] += $incrs[$idxBase], $lr[$idxBase] += $incrs[$idxBase], ++$c)
				$refs .= $csep . $ul[2] . Dynarange::num2ltrs($ul[0]) . $ul[3] . $ul[1] . ($isRange ? (':' . $lr[2] . Dynarange::num2ltrs($lr[0]) . $lr[3] . $lr[1]) : '');

			$fstr = substr_replace($fstr, $refs, $res[0][1] + strlen($res[0][0]), 0);
		}

		return $fstr;
	}

	public static function rewrite (Dynarange $dr, $deps, $wsels, $l10n)
	{
		$srcCoords = $dr->getSrcCoords();
		$idxBase = $dr->getIdxBase();
		$incrs = $dr->getIncrs();

		list ($distance, $count) = $dr->getECInfo();

		$sep = self::$SEP[$l10n];
		$hashref = '/' . $sep . '(([a-zŠšŸ§][\wŠšŸ§]+!)|(\'[^\']+\'!))?#' . self::$REF[$l10n] . '!/i';
		$cmds = array();


		$regs = array('cdrg', array('cm' => true));
		$reg = $ox = $oy = false;

		$c_prev = array(0, 0);

		foreach ($deps as $dep)
		{
			list ($c, $f) = $dep;

			if ($c == $c_prev)
				continue;

			$c_prev = $c;

			$x = $c[0];
			$y = $c[1];

			if (($x >= $srcCoords[0] && $x <= $srcCoords[2] && $y >= $srcCoords[1] && $y <= $srcCoords[3])
				 || ($v = $count > 0 ? self::_rewriteFormula($sep, $f, $srcCoords, $idxBase, $incrs, $distance, $count) : preg_replace($hashref, '', $f)) == $f)
				continue;

			$cell = array('v' => $v);

			if ($reg !== false)
			{
				if ($y == $oy && $x == $ox + 1 && ($reg[2] == 0 || $reg[2] > $x - $reg[0]))
					$reg[] = $cell;
				else if ($y == $oy + 1 && $x == $reg[0] && $reg[2] == 0)
				{
					$reg[2] = $ox - $x + 1;
					$reg[] = $cell;
				}
				else
				{
					$regs[] = $reg;
					$reg = array($x, $y, 0, $cell);
				}
			}
			else
				$reg = array($x, $y, 0, $cell);

			$ox = $x;

			if ($y != $oy)
				$oy = $y;
		}

		if ($reg != false)
			$regs[] = $reg;

		if (count($regs) > 2)
			$cmds[] = $regs;


		$wupd = array();

		foreach ($wsels as $wsel)
		{
			if (!isset($wsel['n_refers_to']) || ($f = $wsel['n_refers_to']) == '')
				continue;

			if (($v = $count > 0 ? self::_rewriteFormula($sep, $f, $srcCoords, $idxBase, $incrs, $distance, $count) : preg_replace($hashref, '', $f)) == $f)
				continue;

			$wupd[$wsel['e_id']] = array('n_refers_to' => $v);
		}

		if (!empty($wupd))
			$cmds[] = array('wupd', '', $wupd);

		if (!empty($cmds))
			ccmd(json_encode($cmds));
	}

}

?>
