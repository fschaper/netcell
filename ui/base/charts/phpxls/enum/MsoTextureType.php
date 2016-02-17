<?php

/**
 * Specifies the texture type for the selected fill.
 * @package wsscharts
 * @subpackage enums
 **/
class MsoTextureType {

	/**
	 * Preset texture type.
	 * @access public
	 * @var integer
	 **/
	const msoTexturePreset = 1;

	/**
	 * Return value only; indicates a combination of the other states.
	 * @access public
	 * @var integer
	 **/
	const msoTextureTypeMixed = -2;

	/**
	 * User-defined texture type.
	 * @access public
	 * @var integer
	 **/
	const msoTextureUserDefined = 2;

}

?>