<?php

class Collection extends XLSObject
{
	protected $_members;
	protected $_keys;

	function __construct ($p)
	{
		parent::__construct($p);

		$this->_members = array();
		$this->_keys = array();
	}

	public function __g_Count ($n)
	{
		return $this->Count();
	}

	public function Item ($idx = 1)
	{
		if (is_int($idx) && isset($this->_members[--$idx]))
			return $this->_members[$idx];

		if (is_string($idx) && isset($this->_keys[$idx]))
			return $this->_members[$this->_keys[$idx]];

		return null;
	}

	public function Count ()
	{
		return count($this->_members);
	}

	public function _take_members ()
	{
		$this->_keys = array();
		return array_splice($this->_members, 0);
	}

	public function _add ($obj, $idx = null, $setparent = false)
	{
		if ($setparent && $obj instanceOf XLSObject)
		{
			$obj->__m['Parent'][XLSObject::M_VAL] = $this;
			$obj->__m['Parent'][XLSObject::M_KIND] = get_class($this);
		}

		if ($idx == null)
		{
			$this->_members[] = $obj;
			return count($this->_members);
		}

		if (is_int($idx))
		{
			if (--$idx >= 0 && $idx <= count($this->_members))
			{
				$this->_members[$idx] = $obj;
				return count($this->_members);
			}
		}
		else if (is_string($idx))
		{
			if (isset($this->_keys[$idx]))
			{
				$this->_members[$this->_keys[$idx]] = $obj;
				return count($this->_members);
			}

			$this->_members[] = $obj;
			$this->_keys[$idx] = count($this->_members) - 1;
			return count($this->_members);
		}

		return -1;
	}

	public function _delete ($idx)
	{
		if (is_int($idx))
		{
			$obj = $this->_members[--$idx];
			array_splice($this->_members, $idx, 1);

			foreach ($this->_keys as $key => $value)
				if ($value > $idx)
					$this->_keys[$key]--;
				else if ($value == $idx)
					unset($this->_keys[$key]);

			return $obj;
		}
		else if (is_string($idx))
		{
			$index = $this->_keys[$idx];
			$obj = $this->_members[$index];
			array_splice($this->_members, $index, 1);

			foreach ($this->_keys as $key => $value)
				if ($value > $index)
					$this->_keys[$key]--;
				else if ($value == $index)
					unset($this->_keys[$key]);

			return $obj;
		}

		return null;
	}

	public function _empty ()
	{
		$this->_members = array();
		$this->_keys = array();
	}
}

?>