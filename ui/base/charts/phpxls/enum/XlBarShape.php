<?php

/**
 * Specifies the shape used with the 3-D bar or column chart.
 * @package wsscharts
 * @subpackage enums
 **/
class XlBarShape {

	/**
	 * Box.
	 * @access public
	 * @var integer
	 **/
	const xlBox = 0;

	/**
	 * Cone, truncated at value.
	 * @access public
	 * @var integer
	 **/
	const xlConeToMax = 5;

	/**
	 * Cone, coming to point at value.
	 * @access public
	 * @var integer
	 **/
	const xlConeToPoint = 4;

	/**
	 * Cylinder.
	 * @access public
	 * @var integer
	 **/
	const xlCylinder = 3;

	/**
	 * Pyramid, truncated at value.
	 * @access public
	 * @var integer
	 **/
	const xlPyramidToMax = 2;

	/**
	 * Pyramid, coming to point at value.
	 * @access public
	 * @var integer
	 **/
	const xlPyramidToPoint = 1;

}

?>