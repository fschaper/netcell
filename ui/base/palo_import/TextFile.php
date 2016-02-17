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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: TextFile.php 2446 2009-11-24 14:53:51Z mladent $
 *
 */

class TextFile extends PaloImport
{
	private $sep = ',';
	private $header = false;
	private $point = '.';

	public function __construct()
	{
		parent::__construct();
	}

	public function setSep($newSep)
	{
		$this->sep = $newSep;
	}

	public function setHeader($hasHeader)
	{
		$this->header = $hasHeader;
	}

	public function setPoint($newPoint)
	{
		$this->point = $newPoint;
	}

	public function importFile($fileName)
	{
		$h = fopen($fileName, 'r');
		if ($this->header) // remove header line
			$line = fgets($h);
		while (($line = fgets($h)) !== false)
		{
			if ($this->point !== '.')
				$line = str_replace($this->point, '.' , $line);
			$impData = split($this->sep, rtrim($line, "\r\n"));

			$this->data[] = $impData;
		}
		fclose($h);
	}

	public function importFileLine($fileName, $lineNum)
	{
		$h = file($fileName);
		if ($this->header) // remove header line
			$lineNum++;

		$line = $h[$lineNum];
		if ($this->point !== '.')
			$line = str_replace($this->point, '.' , $line);
		$impData = split($this->sep, rtrim($line, "\r\n"));
		$this->data[] = $impData;
	}
}

?>
