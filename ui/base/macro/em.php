<?php

define('MACRO_FILE_PFX', 'mmdl_');

function em ($args)
{
	require(wss_temp_directory() . '/' . MACRO_FILE_PFX . activeworkbook()->uuid . '.php');

	$args = json_decode($args, true);
	$funcName = array_shift($args);

	if (($dot_pos = strpos($funcName, '.')) !== false)
		$funcName = substr($funcName, $dot_pos + 1);

	if (function_exists($funcName))
		return call_user_func_array($funcName, $args);
}

function gt ()
{
	return wss_temp_directory();
}

?>