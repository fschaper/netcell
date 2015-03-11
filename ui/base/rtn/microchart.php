<?php

/*
 * \brief micro charts routines
 *
 * \file microchart.php
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
 *
 * \version
 * SVN: $Id: microchart.php 3524 2010-07-15 13:03:47Z mladent $
 *
 */

class microchart
{
	private static $_func_sep = ',';
	private static $_true_val = '1';
	private static $_false_val = '0';
	private static $_mchart_types = array(
		array('name' => 'SparkbarsColored', 'argsType' => 0),
		array('name' => 'SparklineColored', 'argsType' => 1),
		array('name' => 'SparkdotsColored', 'argsType' => 1),
		array('name' => 'SparklineDotsColored', 'argsType' => 1),
		array('name' => 'SparkwhiskerColored', 'argsType' => 2),
		array('name' => 'SparkpieColored', 'argsType' => 3)
	);

	public static function getFuncFromState($vals)
	{
		$classDef = self::$_mchart_types[$vals['type_index']];

		switch($classDef['argsType'])
		{
			case 0:
			case 1:
				$retStr = '=' . $classDef['name'] . '(' . (($vals['source']) ? $vals['source'] : '""') . self::$_func_sep . (($vals['target']) ? $vals['target'] : '""') . self::$_func_sep .
					self::_convertColor($vals['colorPos']) . self::$_func_sep . self::_convertColor($vals['colorNeg']) . self::$_func_sep .
					self::_convertColor($vals['colorFirst']) . self::$_func_sep . self::_convertColor($vals['colorLast']) . self::$_func_sep . '1' . self::$_func_sep .
					self::_convertColor($vals['colorMin']) . self::$_func_sep . self::_convertColor($vals['colorMax']) . self::$_func_sep .
					(($vals['showFirst']) ? self::$_true_val : self::$_false_val) . self::$_func_sep . self::$_false_val . self::$_func_sep .
					(($vals['showLast']) ? self::$_true_val : self::$_false_val) . self::$_func_sep . (($vals['showMinMax']) ? self::$_true_val : self::$_false_val) . self::$_func_sep .
					$vals['scaling_index'] . self::$_func_sep .
					(($vals['scaleMin']) ? $vals['scaleMin'] : '0') . self::$_func_sep .
					(($vals['scaleMax']) ? $vals['scaleMax'] : '1') . ')';
				break;

			case 2:
				$retStr = '=' . $classDef['name'] . '(' . (($vals['source']) ? $vals['source'] : '""') . self::$_func_sep . (($vals['target']) ? $vals['target'] : '""') . self::$_func_sep .
					self::_convertColor($vals['colorWin']) . self::$_func_sep .
					self::_convertColor($vals['colorTie']) . self::$_func_sep . self::_convertColor($vals['colorLose']) . ')';
				break;

			case 3:
				$retStr = '=' . $classDef['name'] . '(' . (($vals['source']) ? $vals['source'] : '""') . self::$_func_sep . (($vals['target']) ? $vals['target'] : '""') . self::$_func_sep .
					self::_convertColor($vals['colorPie']) . ')';
				break;
		}

		return array(array('cdrn', array('cm' => true), array($vals['upCellX'], $vals['upCellY'], $vals['upCellX'], $vals['upCellY'], array('v' => $retStr))));
	}

	public static function getStateFromFunc($funcStr, $separator)
	{
		$state = array();
		$isOneColored = false;

		$state['start_time'] = microtime();
		$time_start = microtime(true);

		$funcParts = explode('(', $funcStr);
		$funcName = substr($funcParts[0], 1); // Will be from 1 instead of 0 -- when "=" comes on beginning

		for($i=0; $i < count(self::$_mchart_types); $i++)
		{
			if (strtoupper(self::$_mchart_types[$i]['name']) == strtoupper($funcName))
			{
				$state['type_index'] = $i;
				break;
			}
			else if (strtoupper(substr(self::$_mchart_types[$i]['name'], 0, -strlen('Colored'))) == strtoupper($funcName))
			{
				// one color
				$state['type_index'] = $i;
				$isOneColored = true;
				break;
			}
		}

		$funcParts = explode(')', $funcParts[1]);
//		$funcArgs = explode(self::$_func_sep, $funcParts[0]);
		$funcArgs = explode($separator, $funcParts[0]);

		if ((count($state) > 0) && !$isOneColored)
			switch (self::$_mchart_types[$state['type_index']]['argsType'])
			{
				case 0:
				case 1:
					$state['source'] = self::_removeDoubleQuotes($funcArgs[0]);
					$state['target'] = self::_removeDoubleQuotes($funcArgs[1]);

					$state['colorPos'] = self::_removeDoubleQuotes($funcArgs[2]);
					$state['colorNeg'] = self::_removeDoubleQuotes($funcArgs[3]);
					$state['colorFirst'] = self::_removeDoubleQuotes($funcArgs[4]);
					$state['colorLast'] = self::_removeDoubleQuotes($funcArgs[5]);

					$state['colorMin'] = self::_removeDoubleQuotes($funcArgs[7]);
					$state['colorMax'] = self::_removeDoubleQuotes($funcArgs[8]);
					$state['showFirst'] = $funcArgs[9];

					$state['showLast'] = $funcArgs[11];
					$state['showMinMax'] = $funcArgs[12];
					$state['scaling_index'] = $funcArgs[13];
					$state['scaleMin'] = self::_removeDoubleQuotes($funcArgs[14]);
					$state['scaleMax'] = self::_removeDoubleQuotes($funcArgs[15]);
					break;

				case 2:
					$state['source'] = self::_removeDoubleQuotes($funcArgs[0]);
					$state['target'] = self::_removeDoubleQuotes($funcArgs[1]);

					$state['colorWin'] = self::_removeDoubleQuotes($funcArgs[2]);
					$state['colorTie'] = self::_removeDoubleQuotes($funcArgs[3]);
					$state['colorLose'] = self::_removeDoubleQuotes($funcArgs[4]);
					break;

				case 3:
					$state['source'] = self::_removeDoubleQuotes($funcArgs[0]);
					$state['target'] = self::_removeDoubleQuotes($funcArgs[1]);

					$state['colorPie'] = self::_removeDoubleQuotes($funcArgs[2]);
					break;
			}
		else
				switch (self::$_mchart_types[$state['type_index']]['argsType'])
			{
				case 0:
				case 1:
					$state['source'] = self::_removeDoubleQuotes($funcArgs[0]);
					$state['target'] = self::_removeDoubleQuotes($funcArgs[1]);

					$state['colorPos'] = $state['colorNeg'] = $state['colorFirst'] = $state['colorLast'] = '#000000';
					$state['colorMin'] = $state['colorMax'] = $state['showFirst'] = '#000000';

					$state['showLast'] = 0;
					$state['showMinMax'] = 0;
					$state['scaling_index'] = 0;
					$state['scaleMin'] = 0;
					$state['scaleMax'] = 1;
					break;

				case 2:
					$state['source'] = self::_removeDoubleQuotes($funcArgs[0]);
					$state['target'] = self::_removeDoubleQuotes($funcArgs[1]);

					$state['colorWin'] = $state['colorTie'] = $state['colorLose'] = '#000000';
					break;

				case 3:
					$state['source'] = self::_removeDoubleQuotes($funcArgs[0]);
					$state['target'] = self::_removeDoubleQuotes($funcArgs[1]);

					$state['colorPie'] = '#000000';
					break;
			}

		$state['end_time'] = microtime();
		$time_end = microtime(true);
		$state['vrijeme_trajanja'] = $time_end - $time_start;

		return $state;
	}

	private static function _convertColor($color)
	{
		return '"' . $color . '"';
	}

	private static function _removeDoubleQuotes($str)
	{
		return ((strpos($str, '"') === 0) ? substr($str, 1, -1) : $str);
	}
}

?>