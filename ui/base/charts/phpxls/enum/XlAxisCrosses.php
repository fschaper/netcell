<?php

/**
 * Specifies the point on the specified axis where the other axis crosses.
 * @package wsscharts
 * @subpackage enums
 **/
class XlAxisCrosses {

	/**
	 * Microsoft Excel sets the axis crossing point.
	 * @access public
	 * @var integer
	 **/
	const xlAxisCrossesAutomatic = -4105;

	/**
	 * The CrossesAt property specifies the axis crossing point.
	 * @access public
	 * @var integer
	 **/
	const xlAxisCrossesCustom = -4114;

	/**
	 * The axis crosses at the maximum value.
	 * @access public
	 * @var integer
	 **/
	const xlAxisCrossesMaximum = 2;

	/**
	 * The axis crosses at the minimum value.
	 * @access public
	 * @var integer
	 **/
	const xlAxisCrossesMinimum = 4;

}

?>