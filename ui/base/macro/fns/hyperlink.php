<?php

/*
 * \brief hyperlink spreadsheet functions
 *
 * \file hyperlink.php
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: hyperlink.php 4461 2010-12-13 19:23:03Z predragm $
 *
 */

function _split_args ($str, $delim)
{
	$len = strlen($str);
	$args = array();
	$arg = '';

	$squote = $dquote = false;
	$parens = $braces = 0;

	for ($i = 0; $i < $len; ++$i)
	{
		$c = $str[$i];

		if ($c == $delim && !$squote && !$dquote && $parens == 0 && $braces == 0)
		{
			$args[] = trim($arg);
			$arg = '';

			continue;
		}

		switch ($c)
		{
			case '\'':
				$squote = !$squote;
				break;

			case '"':
				$dquote = !$dquote;
				break;

			case '(':
				++$parens;
				break;

			case ')':
				--$parens;
				break;

			case '{':
				++$braces;
				break;

			case '}':
				--$braces;
				break;
		}

		$arg .= $c;
	}

	$args[] = trim($arg);

	return $args;
}

function HYPERLINK ($link, $text, $tip) {
	$errStr = '#ERR!';
	$separators = array('en_US' => ',', 'de_DE' => ';', 'fr_FR' => ';');
	$args = func_get_args();
	$args_count = count($args);

	if ($args_count < 3)
		return $errStr;

	$act_range = activerange();
	$locale = locale();
	$fdelimiter = $separators[array_key_exists($locale, $separators) ? $locale : 'en_US'];

	preg_match('/^=HYPERLINK\(.*\)$/i', $act_range->formula(), $fargs);
	$fargs = _split_args(substr($fargs[0], 11, -1), $fdelimiter);

	$data = array(
		'dyn' => true,
		'link' => array($args[0], $args[0]),
		'text' => array(trim($fargs[1], '"\''), $args[1]),
		'tip' => array($args[2], $args[2]),
		'trans' => array()
	);

	for ($i = 3; $i < $args_count; $i += 2) {
		if ($i + 1 >= $args_count)
			break;

		$data['trans'][] = array('src' => array(trim($fargs[$i], '"\''), $args[$i]), 'dst' => array(trim($fargs[$i + 1], '"\''), $args[$i + 1]));
	}

	$chng_flag = activeworkbook()->flag_changed();

	$act_range->attribute(new Attribute('"mousedown"', json_encode(array('hl', $data))));

	if (is_null($act_range->style[0][0]))
		$act_range->style = 'text-decoration: underline; color: #0000ff;';

	activeworkbook()->flag_changed($chng_flag);

	return '<span class="hl" onmouseover="Jedox.wss.hl.toolTip(event, true);" onmouseout="Jedox.wss.hl.toolTip(event, false);">' . $args[1] . '</span>';
}

?>