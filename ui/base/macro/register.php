<?php

define('MACRO_FILE_PFX', 'mmdl_');

function _ ()
{
	activeworkbook()->unregister_function();

	$macro_file = wss_temp_directory() . '/' . MACRO_FILE_PFX . activeworkbook()->uuid . '.php';

	require($macro_file);

	$fns = get_defined_functions();

	foreach ($fns['user'] as $fn)
		if ($fn != '_')
			activeworkbook()->register_function($fn, $fn, $macro_file, true);
}

?>