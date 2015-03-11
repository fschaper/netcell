<?php

/**
 * Specifies the style for a gradient fill.
 * @package wsscharts
 * @subpackage enums
 **/
class MsoGradientStyle {

	/**
	 * Diagonal gradient moving from a top corner down to the opposite corner.
	 * @access public
	 * @var integer
	 **/
	const msoGradientDiagonalDown = 4;

	/**
	 * Diagonal gradient moving from a bottom corner up to the opposite corner.
	 * @access public
	 * @var integer
	 **/
	const msoGradientDiagonalUp = 3;

	/**
	 *  Gradient running from the center out to the corners.
	 * @access public
	 * @var integer
	 **/
	const msoGradientFromCenter = 7;

	/**
	 * Gradient running from a corner to the other three corners.
	 * @access public
	 * @var integer
	 **/
	const msoGradientFromCorner = 5;

	/**
	 * Gradient running from the title outward.
	 * @access public
	 * @var integer
	 **/
	const msoGradientFromTitle = 6;

	/**
	 * Gradient running horizontally across the shape.
	 * @access public
	 * @var integer
	 **/
	const msoGradientHorizontal = 1;

	/**
	 * Gradient is mixed.
	 * @access public
	 * @var integer
	 **/
	const msoGradientMixed = -2;

	/**
	 * Gradient running vertically down the shape.
	 * @access public
	 * @var integer
	 **/
	const msoGradientVertical = 2;

}

?>