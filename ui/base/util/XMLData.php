<?php

/*
 * \brief utility class for manipulating data in XML
 *
 * \file XMLData.php
 *
 * Copyright (C) 2006-2011 Jedox AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (Version 2) as published
 * by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may obtain a copy of the License at
 *
 * <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *   http://www.jedox.com/license_palo_bi_suite.txt
 * </a>
 *
 * If you are developing and distributing open source applications under the
 * GPL License, then you are free to use Palo under the GPL License.  For OEMs,
 * ISVs, and VARs who distribute Palo with their products, and do not license
 * and distribute their source code under the GPL, Jedox provides a flexible
 * OEM Commercial License.
 *
 * \author
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: XMLData.php 5092 2011-07-01 12:43:31Z predragm $
 *
 */

class XMLData
{
	const ORIGIN_FILE		= 1,
				ORIGIN_PALO		= 2,
				ORIGIN_STRING	= 3,
				ORIGIN_ARRAY	= 4;

	const TYPE_XML		= 1,
				TYPE_ARRAY	= 2;

	const SCHEMA_RNG	= 1,
				SCHEMA_XSD	= 2;

	protected $schema;
	protected $schema_method;

	protected $origin;
	protected $address;

	protected $doc;
	protected $xpath;

	protected $apol;

	public static function dom2var ($dom)
	{
		$var = array();

		if ($dom instanceof DOMElement)
		{
			if ($dom->hasAttributes())
				foreach ($dom->attributes as $attr)
					$var['@'][$attr->name] = $attr->value;

			$dom = $dom->childNodes;
		}

		if (!($dom instanceof DOMNodeList))
			return $var;

		$c_var = &$var;
		$idx = 0;
		$len = $dom->length;

		if ($len < 1)
			return $var;

		$stack = array();

		while (true)
		{
			$c_dom = $dom->item($idx);

			$continue = false;

			switch ($c_dom->nodeType)
			{
				case XML_TEXT_NODE:

					$c_var['_'][] = $c_dom->nodeValue;

					break;

				case XML_ELEMENT_NODE:

					$name = $c_dom->tagName;

					if (isset($c_var[$name]))
					{
						$t_arr = &$c_var[$name];

						if (is_array($t_arr) && isset($t_arr[0]))
							$t_arr = &$t_arr[array_push($t_arr, array()) - 1];
						else
						{
							$t_arr = array($t_arr, array());
							$t_arr = &$t_arr[1];
						}
					}
					else
					{
						$c_var[$name] = array();
						$t_arr = &$c_var[$name];
					}

					if ($c_dom->hasAttributes())
						foreach ($c_dom->attributes as $attr)
							$t_arr['@'][$attr->name] = $attr->value;

					if ($c_dom->hasChildNodes())
					{
						if (++$idx < $len)
							$stack[] = array($dom, &$c_var, $idx, $len);

						$dom = $c_dom->childNodes;
						$c_var = &$t_arr;
						$idx = 0;
						$len = $dom->length;

						$continue = true;
					}

					break;
			}

			if ($continue || ++$idx < $len)
				continue;

			if (isset($c_var['_']) && count($c_var) == 1)
				$c_var = $c_var['_'][0];

			if (($pop = array_pop($stack)) === null)
				break;
			else
			{
				list ($dom, , $idx, $len) = $pop;
				$c_var = &$pop[1];
			}
		}

		return $var;
	}

	public static function var2dom ($var, DOMNode $elem)
	{
		if ($elem instanceof DOMElement)
			$doc = $elem->ownerDocument;
		else if ($elem instanceof DOMDocument)
			$doc = $elem;
		else
			return false;

		if (!is_array($var))
		{
			$elem->appendChild($doc->createTextNode(strval($var)));

			return true;
		}

		reset($var);
		$curr = &$var;

		$stack = array();

		while (($key = key($curr)) !== null)
		{
			$val = &$curr[$key];
			next($curr);

			$continue = false;

			if (is_string($key))
				switch ($key)
				{
					case '@':

						foreach ($val as $name => $value)
							$elem->setAttribute($name, $value);

						break;

					case '_':

						if (is_array($val))
							foreach ($val as $text)
								$elem->appendChild($doc->createTextNode(strval($text)));
						else
							$elem->appendChild($doc->createTextNode(strval($val)));

						break;

					default:

						if (is_array($val))
						{
							if (key($curr) !== null)
								$stack[] = array(&$curr, $elem);

							reset($val);
							$curr = &$val;

							if (isset($val[0]))
								$name = $key;
							else
								$elem = $elem->appendChild($doc->createElement($key));

							$continue = true;
						}
						else
							$elem->appendChild($doc->createElement($key, $val));
				}
			else if (is_array($val))
			{
				if (key($curr) !== null)
					$stack[] = array(&$curr, $elem, $name);

				reset($val);
				$curr = &$val;

				$elem = $elem->appendChild($doc->createElement($name));

				$continue = true;
			}
			else
				$elem->appendChild($doc->createElement($name, $val));

			if ($continue || key($curr) !== null)
				continue;

			if (($pop = array_pop($stack)) === null)
				break;
			else
			{
				$curr = &$pop[0];
				list ( , $elem, $name) = $pop;
			}
		}

		return true;
	}

	public function __construct ($schema, $schema_src = self::ORIGIN_FILE, $schema_type = self::SCHEMA_RNG)
	{
		$this->schema = $schema;

		$this->schema_method = $schema_type == self::SCHEMA_XSD ? 'schemaValidate' : 'relaxNGValidate';

		if ($schema_src != self::ORIGIN_FILE)
			$this->schema_method .= 'Source';

		$this->createDocument();
		$this->xpath = new DOMXPath($this->doc);
	}

	public function createDocument ()
	{
		$this->doc = new DOMDocument('1.0', 'utf-8');
		$this->doc->preserveWhiteSpace = false;
		$this->doc->resolveExternals = false;
		$this->doc->substituteEntities = false;
		$this->doc->formatOutput = CFG_DEV_MODE;
	}

	public function getDocument ()
	{
		return $this->doc;
	}

	public function loadFile ($filename)
	{
		$this->origin = self::ORIGIN_FILE;
		$this->address = $filename;

		$this->createDocument();

		if ($this->doc->load($filename, LIBXML_NOWARNING | LIBXML_NOERROR) && (empty($this->schema) || @$this->doc->{$this->schema_method}($this->schema)))
			$success = true;
		else
		{
			$success = false;
			$this->createDocument();
		}

		$this->xpath = new DOMXPath($this->doc);

		return $success;
	}

	public function saveFile ($filename)
	{
		return (empty($this->schema) || @$this->doc->{$this->schema_method}($this->schema)) && $this->doc->save($filename);
	}

	public function loadPalo (AccessPolicy $apol, $db, $cube, array $coords, $asAdmin = true)
	{
		$this->origin = self::ORIGIN_PALO;
		$this->address = array($db, $cube, $coords, $asAdmin);
		$this->apol = $apol;

		$this->createDocument();

		$res = @palo_dataa(($asAdmin ? $apol->getSuperConn() : $apol->getConn()), $db, $cube, $coords);

		if (substr($res, 0, 1) == '<' && $this->doc->loadXML($res, LIBXML_NOWARNING | LIBXML_NOERROR) && (empty($this->schema) || @$this->doc->{$this->schema_method}($this->schema)))
			$success = true;
		else
		{
			$success = false;
			$this->createDocument();
		}

		$this->xpath = new DOMXPath($this->doc);

		return $success;
	}

	public function savePalo (AccessPolicy $apol, $db, $cube, array $coords, $asAdmin = true)
	{
		if (!(empty($this->schema) || @$this->doc->{$this->schema_method}($this->schema)))
			return false;

		$conn = $asAdmin ? $apol->getSuperConn() : $apol->getConn();

		palo_setdataa($this->doc->saveXML(), false, $conn, $db, $cube, $coords);

		return true;
	}

	public function loadString ($string)
	{
		$this->origin = self::ORIGIN_STRING;
		$this->address = null;

		$this->createDocument();

		if ($this->doc->loadXML($string, LIBXML_NOWARNING | LIBXML_NOERROR) && (empty($this->schema) || @$this->doc->{$this->schema_method}($this->schema)))
			$success = true;
		else
		{
			$success = false;
			$this->createDocument();
		}

		$this->xpath = new DOMXPath($this->doc);

		return $success;
	}

	public function saveString ()
	{
		if (!(empty($this->schema) || @$this->doc->{$this->schema_method}($this->schema)))
			return false;

		return $this->doc->saveXML();
	}

	public function loadArray ($array)
	{
		$this->origin = self::ORIGIN_ARRAY;
		$this->address = null;

		$this->createDocument();

		if (is_array($array) && count($array) == 1 && !isset($array[0]) && self::var2dom($array, $this->doc) && (empty($this->schema) || @$this->doc->{$this->schema_method}($this->schema)))
			$success = true;
		else
		{
			$success = false;
			$this->createDocument();
		}

		$this->xpath = new DOMXPath($this->doc);

		return $success;
	}

	public function saveArray ($woRoot = false)
	{
		if (!(empty($this->schema) || @$this->doc->{$this->schema_method}($this->schema)))
			return false;

		return self::dom2var($woRoot ? $this->doc->documentElement : $this->doc->childNodes);
	}

	public function save ()
	{
		switch ($this->origin)
		{
			case self::ORIGIN_FILE:
				return $this->saveFile($this->address);

			case self::ORIGIN_PALO:
				return $this->savePalo($this->apol, $this->address[0], $this->address[1], $this->address[2], $this->address[3]);

			case self::ORIGIN_STRING:
				return $this->saveString();

			case self::ORIGIN_ARRAY:
				return $this->saveArray();
		}

		return false;
	}

	protected function _getContext ($context)
	{
		if (is_string($context) && strlen($context))
		{
			$context = $this->xpath->query($context);
			return $context->length == 1 ? $context->item(0) : null;
		}

		if ($context instanceof DOMNode)
			return $context->ownerDocument->isSameNode($this->doc) ? $context : null;

		return $this->doc->documentElement ? $this->doc->documentElement : $this->doc;
	}

	public function query ($query, $context = null)
	{
		return ($context = $this->_getContext($context)) instanceof DOMNode ? $this->xpath->query($query, $context) : null;
	}

	public function evaluate ($expression, $context = null)
	{
		return ($context = $this->_getContext($context)) instanceof DOMNode ? $this->xpath->evaluate($expression, $context) : null;
	}

	public function get ($query, $context = null)
	{
		return ($context = $this->_getContext($context)) instanceof DOMNode ? self::dom2var($this->xpath->query($query, $context)) : null;
	}

	public function set ($context, $var, $append = false)
	{
		$context = $this->_getContext($context);

		if (!($context instanceof DOMNode))
			return false;

		if ($context->isSameNode($this->doc))
		{
			if (!is_array($var) || count($var) != 1 || isset($var[0]))
				return false;

			if (!$append && $this->doc->documentElement)
				$this->doc->removeChild($this->doc->documentElement);

			$elem = $context;
		}
		else if (!$append)
			$context->parentNode->replaceChild($elem = $this->doc->createElement($context->tagName), $context);
		else
			$elem = $context;

		return self::var2dom($var, $elem);
	}

	public function remove ($query, $context = null)
	{
		$context = $this->_getContext($context);

		if (!($context instanceof DOMNode))
			return false;

		foreach ($this->xpath->query($query, $context) as $item)
			$item->parentNode->removeChild($item);

		return true;
	}

}

?>