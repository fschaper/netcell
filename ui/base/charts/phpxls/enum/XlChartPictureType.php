<?php

/**
 * Specifies how pictures are displayed on a column, bar picture chart, or legend key.
 * @package wsscharts
 * @subpackage enums
 **/
class XlChartPictureType {

	/**
	 * Picture is sized to repeat a maximum of 15 times in the longest stacked bar.
	 * @access public
	 * @var integer
	 **/
	const xlStack = 2;

	/**
	 * Picture is sized to a specified number of units and repeated the length of the bar.
	 * @access public
	 * @var integer
	 **/
	const xlStackScale = 3;

	/**
	 * Picture is stretched the full length of the stacked bar.
	 * @access public
	 * @var integer
	 **/
	const xlStretch = 1;

}

?>