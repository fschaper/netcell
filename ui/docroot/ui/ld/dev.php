<?php

/*
 * \brief source loader
 *
 * \file dev.php
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: dev.php 2666 2010-01-20 13:05:22Z predragm $
 *
 */

function ld ($req)
{
	list ($f_names, $f_ext) = explode('.', $req);

	if ($f_ext == 'js')
		$html = array('	<script type="text/javascript" src="/ui/', '"></script>' . "\n");
	else if ($f_ext == 'css')
		$html = array('	<link rel="stylesheet" type="text/css" media="screen" href="/ui/', '" />' . "\n");
	else
		return;

	$f_names = explode(',', $f_names);

	$ocwd = getcwd();
	$root = substr($ocwd, 0, strrpos($ocwd, DIRECTORY_SEPARATOR) + 1);
	$sources = array();

	foreach ($f_names as $i => $f_name)
	{
		if (preg_match('/\./', $f_name))
			continue;

		chdir($root);
		$rcwd = '';

		$f_conf = 'ld/' . $f_name . '.' . $f_ext . '.conf';

		if (!is_file($f_conf) || !is_readable($f_conf))
			continue;

		$f_conf = file($f_conf, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

		foreach ($f_conf as $j => $f_name)
		{
			if ($f_name[0] == '#')
				continue;

			if ($f_name[0] == '.')
			{
				chdir($root . ($rcwd = $f_name[1] == ' ' ? substr($f_name, 2) . '/' : ''));
				continue;
			}

			if (is_file($f_name) && is_readable($f_name))
				$sources[] = $rcwd . $f_name . '?' . filemtime($f_name);
		}
	}

	chdir($ocwd);

	foreach ($sources as $i => $f_name)
		print $html[0] . $f_name . $html[1];
}

?>