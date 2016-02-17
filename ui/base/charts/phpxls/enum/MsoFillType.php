<?php

/**
 * Specifies a shape's fill type.
 * @package wsscharts
 * @subpackage enums
 **/
class MsoFillType {

	/**
	 * Fill is the same as the background.
	 * @access public
	 * @var integer
	 **/
	const msoFillBackground = 5;

	/**
	 * Gradient fill.
	 * @access public
	 * @var integer
	 **/
	const msoFillGradient = 3;

	/**
	 * Mixed fill.
	 * @access public
	 * @var integer
	 **/
	const msoFillMixed = -2;

	/**
	 * Patterned fill.
	 * @access public
	 * @var integer
	 **/
	const msoFillPatterned = 2;

	/**
	 * Picture fill.
	 * @access public
	 * @var integer
	 **/
	const msoFillPicture = 6;

	/**
	 * Solid fill.
	 * @access public
	 * @var integer
	 **/
	const msoFillSolid = 1;

	/**
	 * Textured fill.
	 * @access public
	 * @var integer
	 **/
	const msoFillTextured = 4;

}

?>