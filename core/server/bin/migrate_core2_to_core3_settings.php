<?php
/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as published
 *  by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 *  Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  You may obtain a copy of the License at
 *
 *  <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *    http://www.jedox.com/license_palo_bi_suite.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 *
 *  \author
 *  Radu Racariu <radu@yalos-solutions.com>
 */

// core2 config files
$core2_config = array("config" => "config.xml",
"palo_config" => "palo_wss3_config.xml",
"macro_engine_config" => "php_macro_engine_config.xml",
"ui_backend_config" => "ui_backend_config.xml",
"font_list_config" => "font_list.xml",
"locale_dir_patern" => '(\b[a-z]{2}_[A-Z]{2}\b)');

// core3 config files
$core3_config = array("config" => "config.xml",
"palo_config" => "palo_config.xml",
"macro_engine_config" => "macro_engine_config.xml",
"ui_backend_config" => "ui_backend_config.xml",
"font_list_config" => "font_list.xml",
"locale_dir_patern" => '(\b[a-z]{2}\b)');


$help_screen = '
Conver config files from core2 to core 3
-s  specifies the sources (core2) directory default is .
-d  specifies the destination (core3) directory, default is .\conveted_core3\
-f  convert one file. default is false, all files will be converted.
-h  display this help page.
';

// main starts here
if (empty($argv))
{
	die($help_screen);
}

$run_dir = ".";
$target_dir = "converted_core3";
$file = "";
$opt_count = 0;

foreach($argv as $index => $value){
	switch($value)
	{
		case "-s":
			$run_dir = $argv[$index+1];
			$opt_count++;
			break;
		case "-d":
			$target_dir = $argv[$index+1];
			$opt_count++;
			break;
		case "-f":
			$file = $argv[$index+1];
			$opt_count++;
			break;
		case "-h":
			exit($help_screen);
	}
}
if (!$opt_count)
{
	die($help_screen);
}

echo "Configured with\n rundir: $run_dir \n target dir: $target_dir \n file: $file \n";

if (!file_exists($target_dir)) {
	mkdir($target_dir);
}
// file param was set. do one file
if ($file != "")
{
	echo ("Migrating just the file $file.\n");
	foreach ($core2_config as $k=>$v)
	{
		if (strripos($file, $v) != false)
		{
			call_user_func("migrate_$k", "$run_dir/".$core2_config[$k]);
		}
	}
	exit ("Done migrating file $file.\n");
}

// automatic dir scan and migration
if ($handle = opendir($run_dir)) {
	echo ("Migrating bulk config files from $run_dir.\n");
	while (false !== ($f = readdir($handle))) {
		foreach ($core2_config as $k=>$v)
		{
			if ($f == $v)
			{
				call_user_func("migrate_$k", "$run_dir/".$core2_config[$k]);
			}
		}
	}
}
closedir($handle);

/*
 * Testing...
 migrate_config("$run_dir/".$core2_config["config"]);
 migrate_palo_config("$run_dir/".$core2_config["palo_config"]);
 migrate_font_list_config("$run_dir/".$core2_config["font_list_config"]);
 migrate_macro_engine_config("$run_dir/".$core2_config["macro_engine_config"]);
 migrate_ui_backend_config("$run_dir/".$core2_config["ui_backend_config"]);
 */
rename_locale();

exit("Done migrating core2 files.");

// function definitions
function migrate_config($config_xml)
{
	global $core3_config, $core2_config;

	echo "Migrating $config_xml\n";

	if (file_exists($config_xml)) {
		$xml = simplexml_load_file($config_xml);
		foreach ( $xml->extensions->extension as $ext )
		{
			// strip OS specific extension
			$ext['name'] = substr($ext['name'], 0, strripos($ext['name'], '.') );
			// rename extensions
			$ext['name'] = str_replace("php_","",$ext['name']);
			$ext['name'] = str_replace("_wss3","",$ext['name']);

			if ($ext['name'] == "filter_xlsx")
			{
				$dom=dom_import_simplexml($ext);
				$dom->parentNode->removeChild($dom);
				continue;
			}

			// rename configs
			foreach ($core2_config as $key=>$value)
			{
				if ($ext['config'] == $value)
				{
					$ext['config'] = $core3_config[$key];
					break;
				}
			}
		}

		// save migrated file
		saveXML($core3_config["config"], $xml->asXML());

		echo "Saved $config_xml\n";

	} else {
		die("Failed to open $config_xml.");
	}
}

function migrate_palo_config($file)
{
  global $core3_config;
  echo "Migrating $file\n";
  if (file_exists($file)) {
    $f = file_get_contents($file);
    $f = str_replace("palo_wss3_config","palo_configuration", $f);
    saveXML($core3_config["palo_config"],$f);
    echo "Saved ".$core3_config["palo_config"]."\n";
  }
  else {
    die("Failed to open $file.");
  }
}

function migrate_font_list_config($file)
{
	global $core3_config;

	echo "Migrating $file\n";
	copyFile($file, $core3_config["font_list_config"]);
	echo "Saved ".$core3_config["font_list_config"]."\n";
}

function migrate_macro_engine_config($file)
{
	global $core3_config;
	echo "Migrating $file\n";
	if (file_exists($file)) {
		$xml = simplexml_load_file($file);
		$xnodes = array();
		$words = array("DAYxl","MONTHxl","YEARxl");
		foreach ( $xml->functions->function as $f)
		{
			if ( in_array($f["php_function"], $words) || stristr($f["php_function"],"ODBC") != false )
			{
				array_push( $xnodes, $f );
			}
		}

		foreach($xnodes as $n )
		{
			echo "Removing function ". $n["php_function"] ."\n";
			$dom=dom_import_simplexml($n);
			$dom->parentNode->removeChild($dom);
		}
		saveXML($core3_config["macro_engine_config"],$xml->asXML());
		echo "Saved ".$core3_config["macro_engine_config"]."\n";
	}
	else {
		die("Failed to open $file.");
	}

}

function migrate_ui_backend_config($file)
{
	global $core3_config;

	echo "Migrating $file\n";
	copyFile($file, $core3_config["ui_backend_config"]);
	echo "Saved ".$core3_config["ui_backend_config"]."\n";
}

function rename_locale()
{
	global $run_dir, $target_dir, $core2_config, $core3_config;
	echo "Start rename the locale dir\n";
	$locale_dir = "$run_dir/locale";
	$target_locale_dir = $target_dir . "/locale";

	if (file_exists($locale_dir))
	{
		copyDir($locale_dir, $target_locale_dir);
		if ($handle = opendir($target_locale_dir)) {
			while (false !== ($file = readdir($handle))) {
				if(preg_match($core2_config["locale_dir_patern"], $file, $matches))
				{
					$name = preg_split("/_/",$matches[0]);
					rename($target_locale_dir. "/". $file, $target_locale_dir. "/". $name[0] );
					echo "renamed file $file to $name[0]\n";
				}
			}
			closedir($handle);
			echo "Done renamig\n";
		}
	}
	else
	{
		echo "locale dir not found in $run_dir\n";
	}
}

function saveXML($filename, $content)
{
	global $target_dir;
	$file = fopen("$target_dir/$filename", 'w');
	fwrite($file, $content);
	fclose($file);
}

function copyFile($original, $new)
{
	global $target_dir;
	if (file_exists($original)) {
		if (!copy($original, "$target_dir/".$new)) {
			echo "failed to copy $original...\n";
		}
	}
	else {
		die("Failed to open $original.");
	}
}
function copyDir($src,$dst) {
	$dir = opendir($src);
	if (!$dir)
	{
		echo "Source dir $src not found";
		return;
	}
	@mkdir($dst);
	while(false !== ( $file = readdir($dir)) ) {
		if (( $file != '.' ) && ( $file != '..' )) {
			if ( is_dir($src . '/' . $file) ) {
				copyDir($src . '/' . $file,$dst . '/' . $file);
			}
			else {
				copy($src . '/' . $file,$dst . '/' . $file);
			}
		}
	}
	closedir($dir);
}

?>