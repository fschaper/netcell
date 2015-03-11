<?php

/**
 * Specifies the type of gradient used in a shape's fill.
 * @package wsscharts
 * @subpackage enums
 **/
class MsoGradientColorType {

	/**
	 * Mixed gradient.
	 * @access public
	 * @var integer
	 **/
	const msoGradientColorMixed = -2;

	/**
	 * One-color gradient.
	 * @access public
	 * @var integer
	 **/
	const msoGradientOneColor = 1;

	/**
	 *  Gradient colors set according to a built-in gradient of the set defined by the  msoPresetGradientType constant.
	 * @access public
	 * @var integer
	 **/
	const msoGradientPresetColors = 3;

	/**
	 * Two-color gradient.
	 * @access public
	 * @var integer
	 **/
	const msoGradientTwoColors = 2;

}

?>