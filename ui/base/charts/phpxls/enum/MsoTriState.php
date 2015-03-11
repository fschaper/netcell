<?php

/**
 * Specifies a tri-state Boolean value.
 * @package wsscharts
 * @subpackage enums
 **/
class MsoTriState {

	/**
	 * Not supported.
	 * @access public
	 * @var integer
	 **/
	const msoCTrue = 1;

	/**
	 * False.
	 * @access public
	 * @var integer
	 **/
	const msoFalse = 0;

	/**
	 * Not supported.
	 * @access public
	 * @var integer
	 **/
	const msoTriStateMixed = -2;

	/**
	 * Not supported.
	 * @access public
	 * @var integer
	 **/
	const msoTriStateToggle = -3;

	/**
	 * True.
	 * @access public
	 * @var integer
	 **/
	const msoTrue = -1;

}

?>