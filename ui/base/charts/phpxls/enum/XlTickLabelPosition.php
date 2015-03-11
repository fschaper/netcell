<?php

/**
 * Specifies the position of tick-mark labels on the specified axis.
 * @package wsscharts
 * @subpackage enums
 **/
class XlTickLabelPosition {

	/**
	 * Top or right side of the chart.
	 * @access public
	 * @var integer
	 **/
	const xlTickLabelPositionHigh = -4127;

	/**
	 * Bottom or left side of the chart.
	 * @access public
	 * @var integer
	 **/
	const xlTickLabelPositionLow = -4134;

	/**
	 * Next to axis (where axis is not at either side of the chart).
	 * @access public
	 * @var integer
	 **/
	const xlTickLabelPositionNextToAxis = 4;

	/**
	 * No tick marks.
	 * @access public
	 * @var integer
	 **/
	const xlTickLabelPositionNone = -4142;

}

?>