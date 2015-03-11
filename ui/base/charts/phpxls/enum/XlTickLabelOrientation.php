<?php

/**
 * Specifies the text orientation for tick-mark labels.
 * @package wsscharts
 * @subpackage enums
 **/
class XlTickLabelOrientation {

	/**
	 * Text orientation set by Excel.
	 * @access public
	 * @var integer
	 **/
	const xlTickLabelOrientationAutomatic = -4105;

	/**
	 * Text runs down.
	 * @access public
	 * @var integer
	 **/
	const xlTickLabelOrientationDownward = -4170;

	/**
	 * Characters run horizontally.
	 * @access public
	 * @var integer
	 **/
	const xlTickLabelOrientationHorizontal = -4128;

	/**
	 * Text runs up.
	 * @access public
	 * @var integer
	 **/
	const xlTickLabelOrientationUpward = -4171;

	/**
	 * Characters run vertically.
	 * @access public
	 * @var integer
	 **/
	const xlTickLabelOrientationVertical = -4166;

}

?>