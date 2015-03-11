<?php

/**
 * Specifies the type of the category axis.
 * @package wsscharts
 * @subpackage enums
 **/
class XlCategoryType {

	/**
	 * Excel controls the axis type.
	 * @access public
	 * @var integer
	 **/
	const xlAutomaticScale = -4105;

	/**
	 * Axis groups data by an arbitrary set of categories.
	 * @access public
	 * @var integer
	 **/
	const xlCategoryScale = 2;

	/**
	 * Axis groups data on a time scale.
	 * @access public
	 * @var integer
	 **/
	const xlTimeScale = 3;

}

?>