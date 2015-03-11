<?php

/*
 * Copyright (C) 2006-2009 Jedox AG, Freiburg, Germany
 * http://www.jedox.com/
 *
 * \author
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: XLSObject.php 2212 2009-09-30 13:16:31Z predragm $
 *
 * \see
 * LICENSE.txt
 *
 */

class XLSObject
{
	const M_VAL  = 0;
	const M_CONV = 1;
	const M_RO   = 2;
	const M_TYPE = 3;
	const M_KIND = 4;

	protected static $__p;
	protected $__m;

	function __construct($p = null)
	{
		$this->__add('Parent', $p, 'Object', true);
	}

	public function __get($n)
	{
		$m = '__g_' . $n;

		if (method_exists($this, $m))
			return $this->$m($n);

		if (isset($this->__m[$n]))
		{
			if (isset(XLSObject::$__p))
				XLSObject::$__p->log($n, $this);

			return $this->__m[$n][self::M_VAL];
		}
	}

	public function __set($n, $v)
	{
		if (isset($this->__m[$n]))
		{
			if ($this->__m[$n][self::M_RO] == false)
			{
				if (isset($this->__m[$n][self::M_CONV]))
					$v = call_user_func($this->__m[$n][self::M_CONV], $v);

				$m = '__s_' . $n;

				if (method_exists($this, $m))
					$this->$m($n, $v);
				else
					$this->__m[$n][self::M_VAL] = $v;
			}
		}
		else
		{
			$m = '__s_' . $n;

			if (method_exists($this, $m))
				$this->$m($n, $v);
		}
	}

	public function __isset($n)
	{
		return isset($this->__m[$n]);
	}

	public static function longval($v)
	{
		if (!strncmp($v, '0x', 2))
			return $v;
		else
			return '0x' . rtrim(ltrim($v, '&H'), '&');
	}

	public static function boolval($v)
	{
		if (is_bool($v))
			return $v;

		if (is_string($v))
			return strcasecmp($v, 'True') == 0 ? true : false;

		if (is_int($v))
			return $v == 1 ? true : false;

		return false;
	}

	public function __add($n, $v = null, $t, $ro = false)
	{
		if (isset($this->__m[$n]))
			return false;
		else
			$this->__m[$n] = array();

		if (!strncmp($t, 'Xl', 2))
		{
			$enum = $t;
			$t = 'Enum';
		}

		switch ($t)
		{
			case 'Long':
				$func = 'XLSObject::longval';
				break;

			case 'Single':
			case 'Double':
				$func = 'floatval';
				break;

			case 'Object':
				if (is_object($v))
					$kind = get_class($v);
				break;

			case 'Enum':
				$func = 'intval';
				$kind = isset($enum) ? $enum : 'Constants';
				break;

			case 'Boolean':
				$func = 'XLSObject::boolval';
				break;

			case 'Integer':
				$func = 'intval';
				break;
		}

		if (isset($func))
		{
			if ($v != null)
				$this->__m[$n][self::M_VAL] = call_user_func($func, $v);
			else
				$this->__m[$n][self::M_VAL] = $v;

			$this->__m[$n][self::M_CONV] = $func;
		}
		else
			$this->__m[$n][self::M_VAL] = $v;

		$this->__m[$n][self::M_RO] = $ro == false ? $ro : true;

		$this->__m[$n][self::M_TYPE] = $t;

		if (isset($kind))
			$this->__m[$n][self::M_KIND] = $kind;

		return true;
	}

	public static function __setprof($p)
	{
		if ($p instanceOf XLSProfiler)
			XLSObject::$__p = $p;
	}

	public static function __getprof()
	{
		return XLSObject::$__p;
	}
}

?>