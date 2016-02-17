<?php

/*
 * \brief source loader
 *
 * \file index.php
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
 * SVN: $Id: index.php 2666 2010-01-20 13:05:22Z predragm $
 *
 */

$e_tag = md5($_SERVER['QUERY_STRING']);

header('ETag: ' . $e_tag);

if (isset($_SERVER['HTTP_IF_NONE_MATCH']) && $_SERVER['HTTP_IF_NONE_MATCH'] == $e_tag)
{
	header('HTTP/1.1 304 Not Modified', false, 304);
	exit(0);
}

list ($f_names, $f_rev, $f_ext) = explode('.', $_SERVER['QUERY_STRING']);
$f_names = explode(',', $f_names);

$types = array('js' => 'text/javascript', 'css' => 'text/css');
$f_type = isset($types[$f_ext]) ? $types[$f_ext] : 'text/plain';

$ocwd = getcwd();
$root = substr($ocwd, 0, strrpos($ocwd, DIRECTORY_SEPARATOR) + 1);
$sources = array();
$c_length = 0;

foreach ($f_names as $i => $f_name)
{
	if (preg_match('/\./', $f_name))
		continue;

	chdir($ocwd);

	$f_name .= '.' . $f_ext;

	if (is_file($f_name) && is_readable($f_name))
	{
		$sources[] = $f_name;
		$c_length += filesize($f_name);
		continue;
	}

	$f_conf = $f_name . '.conf';

	if (!is_file($f_conf) || !is_readable($f_conf))
		continue;

	$f_conf = file($f_conf, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

	chdir($cwd = $root);

	foreach ($f_conf as $j => $f_name)
	{
		if ($f_name[0] == '#')
			continue;

		if ($f_name[0] == '.')
		{
			chdir($cwd = $root . ($f_name[1] == ' ' ? substr($f_name, 2) . '/' : ''));
			continue;
		}

		if (is_file($f_name) && is_readable($f_name))
		{
			$sources[] = $cwd . $f_name;
			$c_length += filesize($f_name);
		}
	}
}

$c_length += count($sources);

header('Content-Type: ' . $f_type);
header('Content-Length: ' . $c_length);

foreach ($sources as $i => $f_name)
{
	readfile($f_name, false);
	print "\n";
}

?>