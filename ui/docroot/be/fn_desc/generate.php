<?php

/*
 * \brief utility script that generates function info in JSON from XML files
 *
 * \file generate.php
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
 * SVN: $Id: generate.php 3951 2010-10-06 15:28:32Z vladislavm $
 *
 */

$locales = array(
  'en_US'
, 'de_DE'
, 'fr_FR'
);

$sources = array(
''
, '../../../base/macro/fns/doc/'
, 'C:/devel/wss3/core3/core3/server/xml/locale/'
);

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</head>
<body>
	<pre>
<?php

setlocale(LC_ALL, 'en_US.utf8');

foreach ($locales as $locale)
{
	$functions = array('cats' => array(), 'funcs' => array(), 'lookup_cat' => array(), 'lookup_func' => array());

	$cats = &$functions['cats'];
	$funcs = &$functions['funcs'];
	$lookup_cat = &$functions['lookup_cat'];
	$lookup_func = &$functions['lookup_func'];

	foreach ($sources as $source)
	{
		$xml_fname = $source . $locale . '.xml';

		print 'INFO: using source file "' . $xml_fname . '".<br>';

		if (!file_exists($xml_fname))
		{
			print 'WARNING: source file "' . $xml_fname . '" does not exist, trying different name.<br>';
			//continue;
            //core3
            $xml_fname = $source . substr($locale, 0, 2) . '/function_table.xml';
            print 'INFO: using source file "' . $xml_fname . '".<br>';
            // core2
            // $xml_fname = $source . $locale . '/functions.xml';
			if(!file_exists($xml_fname))
			{
			     print 'WARNING: source file "' . $xml_fname . '" does not exist, skipping.<br>';
			     continue;
		    }
		}

		$document = new DOMDocument('1.0', 'utf-8');
		$document->load($xml_fname);

		$stylesheet = new DOMDocument('1.0', 'utf-8');
		$stylesheet->load('transform.xslt');

		$processor = new XSLTProcessor();
		$processor->importStylesheet($stylesheet);

		$funcdata = $processor->transformToXML($document);
		eval (substr($funcdata, strpos($funcdata, '$funcdata = array(')));

		foreach ($funcdata['cats'] as &$group)
			if (!isset($lookup_cat[$group[0]]))
				$lookup_cat[$group[0]] = array_push($cats, $group) - 1;

		foreach ($funcdata['funcs'] as &$func)
		{
			if (isset($lookup_func[$func[1]]))
				print 'WARNING: function "' . $func[1] . '" already defined in "' . $xml_fname . '".<br>';

			if (isset($lookup_cat[$func[0]]))
				$lookup_func[$func[1]] = array_push($funcs, $func) - 1;
			else
				print 'WARNING: function "' . $func[1] . '" belongs to an unknown group "' . $func[0] . '", skipping.<br>';
		}
	}

	$json_fname = $locale . '.json';
	file_put_contents($json_fname, json_encode($functions));

	print 'INFO: wrote ' . $json_fname . '.<br><br>';
}

?>
	</pre>
</body>
</html>