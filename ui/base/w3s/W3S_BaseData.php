<?php

/*
 * @brief ajax
 *
 * @file Group.js
 *
 * Copyright (C) 2006-2009 Jedox AG
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: W3S_BaseData.php 4120 2010-10-23 10:53:41Z drazenk $
 *
 */

abstract class W3S_BaseData {

	// Fields
	//protected $activeUser; // TODO: IMPLEMENT

	protected $element; // 'e0'
	protected $type; // ('folder' | 'rforlder' | 'template' | 'workbook' | 'hyperlink' | 'rhyperlink' | 'static' | 'rstatic' | 'urlplugin' | 'rurlplugin' | 'frameset' | 'rframeset') || ('report' || 'file') || 'group'
	protected $subtype; // if $type == 'static' then $subtype = 'html'|'pdf'|'doc'|... elseif $type == 'urlplugin | rurlplugin' then $subtype = 'ahview'|... else $subtype = $type
	protected $name; // 'Some name'
	protected $desc; // 'Some description'
	protected $comment; // 'Some comment'
	//protected $createdBy; // TODO: IMPLEMENT
	//protected $createdDate; // TODO: IMPLEMENT
	//protected $modifiedBy; // TODO: IMPLEMENT
	//protected $modifiedDate; // TODO: IMPLEMENT

	/*
	 * i18n:
	 * array(
	 * 		'en_US' => array(
	 * 			'name' => 'Some name',
	 * 			'desc' => 'Some desc'
	 * 		),
	 * 		'de_DE' => array(
	 * 			'name' => 'Some name',
	 * 			'desc' => 'Some desc'
	 * 		)
	 * );
	 */
	protected $i18n = array();

	/**
	 * Constructor.
	 * @param array Basic node data: array('el' => 'e0', 'name' => 'Some name', 'desc' => 'Some desciption').
	 */
	public function __construct($params = null) {

		if (isset($params)) {
			$this->chkData(array('name' => $params['name']));

			$this->name = $params['name'];
			$this->desc = (isset($params['desc']) && strlen($params['desc']) > 0) ? $params['desc'] : $params['name'];
		}

	}

	/**
	 * Check data function.
	 * @access private
	 * @param array Data to check: array('element' => $el, 'type' => $type, 'name' => $name)
	 */
	protected function chkData($data) {
		foreach ($data as $key => $value) {
			switch ($key) {

				// Check name.
				case 'name':
					if (!isset($value) || strlen($value) == 0)
						throw new WSS_Exception('W3S_BaseData-err_sysname', array(), 'Element real name is not set.');
					break;

			}
		}
	}

	// ###############
	// Import / Export
	// ###############

	protected function chkNode($name, &$node_list, $mandatory = false, $allow_multiple = false) {
		if ($mandatory && $node_list->length == 0)
			throw new WSS_Exception('W3S_BaseData-no_mandatory_el', array('name' => $name), 'Unable to find a mandatory element "' . $name . '".');
		elseif (!$allow_multiple && $node_list->length > 1)
			throw new WSS_Exception('W3S_BaseData-too_many_el', array('name' => $name), 'More than one "' . $name . '" element exists.');
	}

	/**
	 * XML import init function.
	 * @access protected
	 * @param string XML data to import.
	 */
	protected function importInit($data, &$root, &$xpath) {
		if (!isset($data) || strlen($data) == 0)
			throw new WSS_Exception('W3S_BaseData-import_no_data', array(), 'No data to import.');

		$dom = new DOMDocument('1.0', 'utf-8');
		$dom->preserveWhiteSpace = false;
		$dom->resolveExternals = false;
		$dom->substituteEntities = false;

		if (!$dom->loadXML($data, LIBXML_NOWARNING | LIBXML_NOERROR))
			throw new WSS_Exception('W3S_BaseData-inv_el_data', array(), 'Invalid element data.');

		$root = $dom->documentElement;

		$this->element = $root->getAttribute('name');
		$this->type = $this->subtype = $root->getAttribute('type');

		if (!$root->hasChildNodes())
			throw new WSS_Exception('W3S_BaseData-no_el_data', array(), 'No element data.');

		$xpath = new domXPath($dom);

		// Process info.
		$nl_info = $xpath->query('info', $root);
		$this->chkNode('info', $nl_info, true, false);
		$this->importInfo($xpath, $nl_info->item(0));
	}

	private function importInfo(&$xpath, $info) {
		// Process name.
		$nl_name = $xpath->query('name', $info);
		$this->chkNode('name', $nl_name, true, false);
		$this->name = $nl_name->item(0)->nodeValue;

		// Process description.
		$nl_desc = $xpath->query('desc', $info);
		$this->chkNode('desc', $nl_desc, false, false);

		if ($nl_desc->length == 0)
			$this->desc = $this->name;
		else
			$this->desc = $nl_desc->item(0)->nodeValue;

		// Process comment.
		$nl_comment = $xpath->query('comment', $info);
		$this->comment = $nl_comment->item(0)->nodeValue;

		// Process i18n.
		$nl_i18n = $xpath->query('i18n', $info);
		$this->chkNode('i18n', $nl_i18n, false, false);

		if ($nl_i18n->length > 0) {
			$el_i18n = $nl_i18n->item(0);

			if ($el_i18n->hasChildNodes()) {
				$childElements = $el_i18n->childNodes;

				for ($i = 0; $i < $childElements->length; $i++) {
					if ($childElements->item($i) != XML_ELEMENT_NODE)
						continue;
					else {
						$el_lang = $childElements->item($i);

						// Process name.
						$nl_name = $xpath->query('name', $el_lang);
						$this->chkNode('info/i18n/<lang>/name', $nl_name, true, false);

						// Process description.
						$nl_desc = $xpath->query('desc', $el_lang);
						$this->chkNode('info/i18n/<lang>/desc', $nl_desc, false, false);

						$this->i18n[$el_lang->nodeName] = array('name' => $nl_name->item(0)->nodeValue, 'desc' => ($nl_desc->length == 0) ? $nl_name->item(0)->nodeValue : $nl_desc->item(0)->nodeValue);
					}
				}
			}
		}
	}

	protected function exportInit() {
		$dom = new DOMDocument('1.0', 'utf-8');
		$dom->preserveWhiteSpace = false;
		$dom->resolveExternals = false;
		$dom->substituteEntities = false;
		$dom->formatOutput = CFG_DEV_MODE;

		$dom->formatOutput = true;

		// Create root element.
		$el_element = $dom->createElement('element');
		$el_element->setAttribute('name', $this->element);
		$el_element->setAttribute('type', $this->type);
		$dom->appendChild($el_element);

		// Create info element.
		$el_info = $dom->createElement('info');

		$el_name = $dom->createElement('name', htmlspecialchars($this->name));
		$el_info->appendChild($el_name);
		$el_desc = $dom->createElement('desc', htmlspecialchars($this->desc));
		$el_info->appendChild($el_desc);
		$el_comment = $dom->createElement('comment', htmlspecialchars($this->comment));
		$el_info->appendChild($el_comment);

		$el_i18n = $dom->createElement('i18n');

		foreach ($this->i18n as $key => $value) {
			$el_lang = $dom->createElement($key);

			$el_lang_name = $dom->createElement('name', $value['name']);
			$el_lang->appendChild($el_lang_name);
			$el_lang_desc = $dom->createElement('desc', $value['desc']);
			$el_lang->appendChild($el_lang_desc);

			$el_i18n->appendChild($el_lang);
		}

		$el_info->appendChild($el_i18n);
		$el_element->appendChild($el_info);

		return $dom;
	}

	// ###################
	// Getters and setters
	// ###################

	/**
	 * Get element's system name.
	 * @return string Palo element name (e0, e1, ...., en).
	 */
	public function getSystemName() {
		return $this->element;
	}

	/**
	 * Set element's system name.
	 * @param string Palo element name (e0, e1, ...., en).
	 */
	public function setSystemName($name) {
		$this->element = $name;
	}

	/**
	 * Get element's type.
	 * @return string Node type (folder, rfolder, template or workbook).
	 */
	public function getType() {
		return $this->type;
	}

	/**
	 * Get element's real name.
	 * @return string Node real name ('Some name').
	 */
	public function getName() {
		return $this->name;
	}

	/**
	 * Set element's real name.
	 * @param string Node real name ('Years', 'Products', ...).
	 */
	public function setName($name) {
		$this->chkData(array('name' => $name));
		$this->name = $name;
	}

	/**
	 * Get element's description.
	 * @return string Node description (for example Tooltip).
	 */
	public function getDescription() {
		return $this->desc;
	}

	/**
	 * Set element's description.
	 * @param string Node description (for example Tooltip).
	 */
	public function setDescription($desc = null) {
		$this->desc = (isset($desc) && strlen($desc) > 0) ? $desc : $this->name;
	}

	/**
	 * Get element's comment.
	 * @return string Node comment.
	 */
	public function getComment() {
		return $this->comment;
	}

	/**
	 * Set element's comment.
	 * @param string Node comment.
	 */
	public function setComment($comment) {
		$this->comment = $comment;
	}

	/**
	 * Get i18n data.
	 * @return array Internationalization data in format: array('en_US' => array('name' => 'Some name', 'desc' => 'Some desc'), 'de_DE' => array('name' => 'Some name', 'desc' => 'Some desc'));
	 */
	public function getI18n($lang = null) {
		return isset($lang) ? $this->i18n[$lang] : $this->i18n;
	}

	/**
	 * Set i18n data.
	 * @param array Internationalization data in format: array('en_US' => array('name' => 'Some name', 'desc' => 'Some desc'), 'de_DE' => array('name' => 'Some name', 'desc' => 'Some desc'));
	 */
	public function setI18n($i18n_data) {
		$this->i18n = $i18n_data;
	}

}

?>