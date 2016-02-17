<?php

/**
 * Specifies the color type.
 * @package wsscharts
 * @subpackage enums
 **/
class MsoColorType {

	/**
	 * Color Management System color type.
	 * @access public
	 * @var integer
	 **/
	const msoColorTypeCMS = 4;

	/**
	 * Color is determined by values of cyan, magenta, yellow, and black.
	 * @access public
	 * @var integer
	 **/
	const msoColorTypeCMYK = 3;

	/**
	 * Not supported.
	 * @access public
	 * @var integer
	 **/
	const msoColorTypeInk = 5;

	/**
	 * Not supported.
	 * @access public
	 * @var integer
	 **/
	const msoColorTypeMixed = -2;

	/**
	 * Color is determined by values of red, green, and blue.
	 * @access public
	 * @var integer
	 **/
	const msoColorTypeRGB = 1;

	/**
	 * Color is defined by an application-specific scheme.
	 * @access public
	 * @var integer
	 **/
	const msoColorTypeScheme = 2;

}

?>