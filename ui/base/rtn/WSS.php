<?php

/*
 * \brief RPC routines
 *
 * \file WSS.php
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: WSS.php 5152 2011-07-28 10:02:33Z predragm $
 *
 */

class WSS
{
	const UNDEFINED = -1;

	const MAX_COL = 255;
	const MAX_ROW = 65535;

	const Q_VALUE = 1;
	const Q_FORMULA = 2;
	const Q_STYLE = 4;
	const Q_FORMULA_WE = 8;
	const Q_ATTRS = 16;
	const Q_DIMS = 32;
	const Q_FMT_VAL = 64;
	const Q_FMT = 128;
	const Q_MERGE = 256;
	const Q_FORMULA_NF = 512;
	const Q_LOCK = 1024;
	const Q_ALL = 2013; // all except FORMULA and DIMS

	const D_NONE = 0;
	const D_COLS = 1;
	const D_ROWS = 2;
	const D_BOTH = 3;

	const WB_EXTENSION = '.wss';
	const WB_TEMPLATE = 'blank_workbook_template';
	const WB_TEMPLATE_RELPATH = '../../base/templates/';
	const WB_INIT = 'Workbook#id';

	const RE_RANGE = '/^=\$([A-Z]+)\$([0-9]+)[:,]\$([A-Z]+)\$([0-9]+)(,.+)?$/';

	const MACRO_FILE_PFX = 'mmdl_';

	const SEP_DECIMAL = 0;
	const SEP_THOUSAND = 1;
	const SEP_ELEMENT = 2;

	const CCMD_STOP_ON_ERR = 1;

	private static $l10n_book = array(
	  'en_US' => 'Workbook'
	, 'de_DE' => 'Arbeitsmappe'
	, 'fr_FR' => 'Classeur'
	);

	private static $l10n_sheet = array(
	  'en_US' => 'Sheet'
	, 'de_DE' => 'Tabellenblatt'
	, 'fr_FR' => 'Feuille'
	);

	private static $cb_handles = array(
	  'hb_run' => array('$hb_catalog', 'run', false, false)
	, 'hb_ec' => array('$hb_catalog', 'ec', false, false)
	, 'mc_getFuncFromState' => array(null, 'microchart::getFuncFromState', true, true)
	, 'palo_handlerPasteView' => array(null, 'palo_view::handlerPasteView', true, true)
	, 'palo_handlerExpandCollapsePasteView' => array(null, 'palo_view::handlerExpandCollapsePasteView', true, true)
	, 'palo_handlerSelectElements' => array(null, 'palo_view::handlerSelectElements', true, true)
	, 'palo_handlerChooseElements' => array(null, 'palo_view::handlerChooseElements', true, true)
	, 'palo_handlerPasteDataFunctions' => array(null, 'palo_view::handlerPasteDataFunctions', true, true)
	, 'palo_handlerElemSelectPaloView' => array(null, 'palo_view::handlerElemSelectPaloView', true, true)
	, 'palo_handlerPutValuesOnGrid' => array(null, 'palo_misc::handlerPutValuesOnGrid', true, true)
	, 'palo_handlerImportPaloDataFunc' => array(null, 'palo_misc::handlerImportPaloDataFunc', true, true)
	, 'palo_handlerGetGeneratedSubsetFunc' => array(null, 'palo_sbst::handlerGetGeneratedSubsetFunc', true, true)
	);

	private static $framesets = array('frameset', 'rframeset');

	private $curr_appid;
	private $curr_wbid;
	private $curr_wsid;

	private $worksheet_elems;
	private $worksheet_clones;

	private $hb_catalog;

	private function _setupSess (SessWSS $session)
	{
			$this->curr_appid = &$session->curr_appid;
			$this->curr_wbid = &$session->curr_wbid;
			$this->curr_wsid = &$session->curr_wsid;

			$this->worksheet_elems = &$session->worksheet_elems;
			$this->worksheet_clones = &$session->worksheet_clones;

			$this->hb_catalog = &$session->hb_catalog;
	}

	public function __construct ($auto_login = null)
	{
		if ($auto_login != null)
		{
			if (!isset($auto_login['wb']) || !isset($auto_login['grp']) || !isset($auto_login['hrc']))
				throw new Exception('Unable to perform auto login.');

			$_SESSION['wss'] = $session = new SessWSS();
			$this->_setupSess($session);

			$res = json_decode(ccmd('[["oadd",0,"' . ('A' . mt_rand()) . '"]]'), true);

			$this->curr_appid = $res[0][1];
			ccmd('[["osel",0,"' . $this->curr_appid . '"]]');

			$ext = array('vars' => $auto_login['vars'], 'rPath' => $auto_login['rPath'], 'appmode' => $auto_login['appmode']);
			if (array_key_exists('opar', $auto_login))
				$ext['opar'] = $auto_login['opar'];

			$_SESSION['preload'] = array_merge(
				array(array($auto_login['wb'], $auto_login['grp'], $auto_login['hrc'], $ext)),
			 	$auto_login['ntype'] == W3S_NodeData::$workbook || $auto_login['ntype'] == W3S_NodeData::$template ?
			 	array(call_user_func_array(array($this, 'load_workbook'), array($auto_login['wb'], $auto_login['grp'], $auto_login['hrc'], $ext))) :
			 	array(array(false, 'errLoadFS_noNode'))
			);
		}
		else if (isset($_SESSION['wss']))
			$this->_setupSess($_SESSION['wss']);
		else
		{
			$_SESSION['wss'] = $session = new SessWSS();
			$this->_setupSess($session);

			$res = json_decode(ccmd('[["oadd",0,"' . ('A' . mt_rand()) . '"]]'), true);

			$this->curr_appid = $res[0][1];
			ccmd('[["osel",0,"' . $this->curr_appid . '"]]');

			$this->load_workbook();
		}
	}

	public function getPreload ()
	{
		$preload = $_SESSION['preload'];
		unset($_SESSION['preload']);

		return $preload;
	}


	/*
	 * #############
	 * ### PROXY ###
	 * #############
	 */

	public function wsel ($name)
	{
		$func_args = func_get_args();
		$func_args[0] = $this;

		return call_user_func_array(array($this->worksheet_elems, $name), $func_args);
	}

	private function _loadCharts(&$list) {
		if (!count($list))
			return;

		$maps_cmd = array(); $charts = array(); $idx_list = array();

		foreach ($list as $ws_id => $ws_name) {
			$maps_cmd[] = array('wget', $ws_id, array(), array('e_id', 'map'), array('e_type' => 'charts'));
			$idx_list[] = $ws_id;
		}

		$maps_res = ccmd($maps_cmd);
		$is_ng = true;

		foreach ($maps_res as $map_els)
			if ($map_els[0] && count($map_els[1])) {
				$is_ng = false;
				break;
			}

		if ($is_ng) {
			$getall_cmd = array();

			foreach ($idx_list as $ws_id)
				$getall_cmd[] = array('wget', $ws_id, array(), array('e_id', 'payload'), array('e_type' => 'chart'));

			if (count($getall_res = ccmd($getall_cmd))) {
				foreach ($getall_res as $idx => $ws_charts) {
					if (!$ws_charts[0])
						continue;

					foreach ($ws_charts[1] as $chart)
						if (isset($chart['payload']))
							$charts[$idx_list[$idx]][$chart['e_id']] = unserialize(gzuncompress(base64_decode($chart['payload'])));
				}

				if (count($charts))
					$this->worksheet_elems->set_workbook_storage($this->curr_wbid, $charts);
			}
		} else {
			$conv_cmd = array();

			foreach ($maps_res as $idx => $map_els)
				if (array_key_exists($idx, $idx_list) && count($map_els[1])) {
					$charts[$idx_list[$idx]] = unserialize(gzuncompress(base64_decode($map_els[1][0]['map'])));

					$map_ids = array();
					foreach ($map_els[1] as $map_el)
						$map_ids[] = $map_el['e_id'];

					$conv_cmd[] = array('wdel', $idx_list[$idx], $map_ids);
				}

			if (count($charts))
				$this->worksheet_elems->set_workbook_storage($this->curr_wbid, $charts);

			$charts = $this->worksheet_elems->get_workbook_storage($this->curr_wbid);

			foreach ($charts as $ws_id => $wsels)
				foreach ($wsels as $wsel_id => $chart)
					$conv_cmd[] = array('wupd', $ws_id, array($wsel_id => array('payload' => base64_encode(gzcompress(serialize($chart), 1)))));

			if (count($conv_cmd))
				$conv_res = ccmd($conv_cmd);
		}
	}

	// Refresh source data for all charts on current sheet.
	private function _refreshCharts() {
		$res = json_decode(ccmd('[["wget","' . $this->curr_wsid . '",[],["e_id","n_get_val","n_source_dims"],{"e_type":"chart"}]]'), true);

		if ($res[0][0])
			foreach($res[0][1] as $wsel_data)
				$this->worksheet_elems->refresh_source_data($this->curr_wbid, $this->curr_wsid, $wsel_data);
	}

	/*
	 * ######################
	 * ### WORKBOOK/SHEET ###
	 * ######################
	 */

	public function getCurrWbId() {
		return $this->curr_wbid;
	}

	public function getCurrWsId() {
		return $this->curr_wsid;
	}

	public function get_worksheet_elements() {
		return $this->worksheet_elems;
	}

	public static function syncPrivVars (W3S_Node $node_f, W3S_Node $node_r)
	{
		$ud_f = &$node_f->getUserData();
		$ud_r = &$node_r->getUserData();

		if (empty($ud_f['var']))
		{
			if (empty($ud_r['var']))
				return true;

			unset($ud_r['var']);
			return $node_r->saveUserData();
		}

		$vars = &$ud_f['var'];

		if (isset($vars['name']))
			$vars = array($vars);

		foreach ($vars as &$var)
			$vars_f[$var['name']] = $var['val'];

		$vars_r = &$ud_r['var'];

		if (isset($vars_r['name']))
			$vars_r = array($vars_r);

		$cnt = count($vars_r);

		for ($i = $cnt - 1; $i >= 0; --$i)
			if (isset($vars_f[$name = $vars_r[$i]['name']]))
				unset($vars_f[$name]);
			else
				array_splice($vars_r, $i, 1);

		$removed = $cnt != count($vars_r);

		foreach ($vars_f as $name => $val)
			$vars_r[] = array('name' => $name, 'val' => $val);

		return $removed || !empty($vars_f) ? $node_r->saveUserData() : true;
	}

	public static function userData2UsedVars (array &$user_data, array &$priv_vars)
	{
		if (!count($priv_vars) || !isset($user_data['var']))
			return array();

		$vars = &$user_data['var'];
		$used_vars = array();

		if (isset($vars['name'])) {
			if (in_array($vars['name'], $priv_vars))
				$used_vars[$vars['name']] = json_decode($vars['val'], true);
		} else
			foreach ($vars as &$var)
				if (in_array($var['name'], $priv_vars))
					$used_vars[$var['name']] = json_decode($var['val'], true);

		return $used_vars;
	}

	public function loadFrameset($name = null, $group_name = null, $hierarchy_name = null, $ext = null) {
		return array(false, 'errLoadFS_noNode');
	}

	public function load_workbook($name = null, $group_name = null, $hierarchy_name = null, $ext = null) {
		$used_vars = array();
		$blank = !isset($name);
		$from_studio = (isset($group_name) && isset($hierarchy_name));
		$from_reports = false;
		$save_recent = isset($ext['saverec']) ? $ext['saverec'] : true;
		$apol = $_SESSION['accessPolicy'];

		// if Studio initiated load, fetch name, path and meta data.
		if ($from_studio) {
			try {
				$node = null;
				$meta = '{"group": "' . $group_name . '", "hierarchy": "' . $hierarchy_name . '", "node": "' . $name . '", "relpath": "';

				$group = new W3S_Group($apol, $group_name);
				$hierarchy = $group->getHierarchy($hierarchy_name);

				$vars = $ext['vars'];

				if (isset($vars) && is_array($vars)) {
					$from_reports = true;
					$rep_node = $hierarchy->getNode($name);
					$meta .= $rep_node->getRelPath($rep_node, false) . '"';
					$meta .= ', "ghpath": "/' . $group->getData()->getName() . '/' . $hierarchy->getData()->getName() . '"';

					if ($group_name[0] == 'f') {
						$node = $rep_node;
						$maps = array_key_exists('maps', $ext) ? $ext['maps'] : array();
					} else {
						$rep_node_data = $rep_node->getData();
						$rep_name = $rep_node_data->getName();
						$real_wb = $rep_node_data->getWorkbook();

						$group = new W3S_Group($apol, $real_wb->getGroup());
						$hierarchy = $group->getHierarchy($real_wb->getHierarchy());
						$node = $hierarchy->getNode($real_wb->getNode());

						$res_fghn = array('fgroup' => $real_wb->getGroup(), 'fhierarchy' => $real_wb->getHierarchy(), 'fnode' => $real_wb->getNode());
						$meta .= ', "fgroup": "' . $res_fghn['fgroup'] . '", "fhierarchy": "' . $res_fghn['fhierarchy'] . '", "fnode": "' . $res_fghn['fnode'] . '"';

						$maps = w3s::getMap($apol->getConn(), $rep_node_data, w3s::EXC_PRIVATE_VARS);

						self::syncPrivVars($node, $rep_node);
					}

					// Set variables from private storage.
					$used_vars = self::userData2UsedVars($rep_node->getUserData(), array_keys($node->getData()->getVars(array('private' => true))));

					// Set variables from report.
					if (array_key_exists('nodes', $vars) || array_key_exists('vars', $vars)) {
						foreach ($maps as $map_var => $map_list)

							if (get_class($map_list['list']) == 'W3S_LinkList') {
								if (is_array($vars['nodes']) && array_key_exists($map_list['list']->getElement(), $vars['nodes']))
									$used_vars[$map_var] = $vars['nodes'][$map_list['list']->getElement()];

							} elseif (is_array($vars['vars']) && array_key_exists($map_var, $vars['vars']))
								$used_vars[$map_var] = $vars['vars'][$map_var];
					}

					if (array_key_exists('opar', $ext) && is_array($opars = json_decode($ext['opar'], true))) {
						$save_recent = false;

						// Set variables from external parameters.
						foreach ($opars as $o_key => $o_val)
							$used_vars[$o_key] = $o_val;
					} else {
						$recent_vars = array();
						foreach ($vars as $type => $vlist)
							foreach ($vlist as $key => $val)
								$recent_vars[] = array('type' => $type, 'name' => $key, 'val' => $val);
					}
				} else {
					$node = $hierarchy->getNode($name);

					if (!isset($node))
						return array(false, 'follHLInvalidDoc');

					$used_vars = self::userData2UsedVars($node->getUserData(), array_keys($node->getData()->getVars(array('private' => true))));

					$meta .= $node->getRelPath($node, false) . '"';
					$meta .= ', "ghpath": "/' . $group->getData()->getName() . '/' . $hierarchy->getData()->getName() . '"';
				}

				if (!isset($node))
					return array(false, 'errLoadWB_noNode');

				$node_name = $name;
				$name = isset($rep_name) ? $rep_name : $node->getData()->getName();

				// Check Autosave files.
				if (!isset($ext) || !array_key_exists('asid', $ext)) {
					$node_dir = str_replace('\\', '/', $node->getParent()->getSysPath());
					$as_list = array('recov' => array());

					if (is_dir($node_dir) && ($dir_files = scandir($node_dir))) {
						$node_sys_name = $node->getUID() . '-' . urlencode($node->getData()->getName()) . self::WB_EXTENSION;
						$node_sys_name_len = strlen($node_sys_name) + 1;
						$node_sys_name_user = $node_sys_name . '.' . $apol->getUser() . '.';

						for ($i = array_search($node_sys_name, $dir_files), $len = count($dir_files); $i < $len; $i++)
							if (stripos($dir_files[$i], $node_sys_name) !== false) {
								$file_stat = stat($node_dir . '/' . $dir_files[$i]);

								if (!array_key_exists('orig', $as_list) && $dir_files[$i] === $node_sys_name)
									$as_list['orig'] = array(
															'meta' => array('ghn' => array('g' => $group_name, 'h' => $hierarchy_name, 'n' => $node_name), 'name' => $name),
															'date' => date('d.m.Y H:i:s', $file_stat['mtime']),
															'size' => $file_stat['size']
														);
								elseif (stripos($dir_files[$i], $node_sys_name_user) !== false)
									$as_list['recov'][] = array(substr($dir_files[$i], $node_sys_name_len), date('d.m.Y H:i:s', $file_stat['mtime']), $file_stat['size']);
							} else
								break;
					}

					if (count($as_list['recov']))
						return array(false, 'recoveryList', $as_list);
				}

				$path = str_replace('\\', '/', $node->getSysPath() . self::WB_EXTENSION);

				if (!file_exists($path))
					return array(false, 'errLoadWB_noFile');

				if (($perm = $node->getPermN()) < AccessPolicy::PERM_READ)
					return array(false, 'errLoadWB_noRights');

				$from_frameset = isset($ext) && array_key_exists('frameset', $ext);
				$meta .= ', "cnts": ["' . ($from_frameset ? $ext['frameset'] : 'so') . '"]';

				$meta .= ', "name": "' . $name . '", "perm": "' . $perm . '", "hidden": ' . ($ext['hidden'] ? 'true'  : 'false') . '}';
			} catch (Exception $e) {
				return array(false, 'errLoadWB_noNode');
			}
		}

		// get list of loaded books
		if (!isset($ext['bels'])) {
			$llist = json_decode(ccmd('[["bels"]]'), true);
			$llist = $llist[0][0] === true && is_array($llist[0][1]) ? $llist[0][1] : array();
		} else
			$llist = $ext['bels'];

		$prev_wbid = $this->curr_wbid; $prev_wsid = $this->curr_wsid;

		if (!$blank)
			// Select already loaded workbook.
			for ($i = count($llist) - 1; $i >= 0; --$i)
				if ($from_studio ? (str_replace('\\', '/', $llist[$i]['path']) == $path) : ($llist[$i]['name'] == $name)) {
					try {
						$this->curr_wbid = $llist[$i]['id'];
						$this->curr_wsid = '';

						if (!is_null($lwb_meta = json_decode($llist[$i]['meta'], true))) {
							if (!$ext['hidden'] && $lwb_meta['hidden']) {
								$lwb_meta['hidden'] = false;
								$meta_changed = true;
							}

							if (!array_key_exists('cnts', $lwb_meta))
								$lwb_meta['cnts'] = array();

							if ($from_frameset) {
								$lwb_meta['cnts'][] = $ext['frameset'];
								$meta_changed = true;
							} elseif (($first_so = !in_array('so', $lwb_meta['cnts']))) {
								$lwb_meta['cnts'][] = 'so';
								$meta_changed = true;
							}

							if (isset($meta_changed))
								ccmd('[["bcmd",' . str_replace('\\\\\\/', '/', json_encode(json_encode($lwb_meta))) . ']]');
						}

						$sel_sheet_res = isset($ext['sheet_name']) ? $this->selectSheet(null, false, !($ext['appmode'] == 'user' || $from_reports), $ext['sheet_name']) : $this->selectSheet(null, false, $ext['appmode'] == 'designer');
						if (!$sel_sheet_res[0]) {
							ccmd('[["osel",1,"' . ($this->curr_wbid = $prev_wbid) . '"]]');
							$this->selectSheet($prev_wsid);
							return array(false, 'follHLInvalidSheet');
						}

						if (isset($ext['nrange'])) {
							$nget_res = json_decode(ccmd('[["nget",[1,1,"' . $ext['nrange'] . '","' . $this->curr_wsid . '"]]]'), true);

							if (!$nget_res[0][0])
								$nget_res = json_decode(ccmd('[["nget",[1,1,"' . $ext['nrange'] . '",""]]]'), true);

							if (!$nget_res[0][0]) {
								ccmd('[["osel",1,"' . ($this->curr_wbid = $prev_wbid) . '"]]');
								$this->selectSheet($prev_wsid);
								return array(false, 'follHLInvTrgNRange');
							}
						}

						$imported = ($lastdot = strrpos($name, '.')) && in_array(strtolower(substr($name, $lastdot)), array('.xlsx', '.tmp'));

						if ($imported) {
							$name = substr_replace($name, '', $lastdot);
							ccmd('[["oren",1,' . json_encode($name) . ']]');

							$save_recent = false;
							$perm = AccessPolicy::PERM_DELETE;

							// load sheet elements into session
							$list = json_decode(ccmd('[["olst",2]]'), true);
							$list = $list[0][0] && is_array($list[0][1]) ? $list[0][1] : array();
							$this->_loadCharts($list);

							// Load Macros
							$this->exportMacros();
						} elseif ($first_so)
							$imported = true;

						$res_arr = array('wbid' => $this->curr_wbid, 'name' => $name, 'imp' => !$imported, 'perm' => $perm);

						if (isset($res_fghn))
							$res_arr = array_merge($res_arr, $res_fghn);

						if (isset($ext['sheet_name']))
							$res_arr['wsid'] = array_key_exists($this->curr_wsid, $this->worksheet_clones) ? $this->worksheet_clones[$this->curr_wsid] : $this->curr_wsid;

						if (isset($ext['cbkey'])) {
							$res_arr[$ext['cbkey']] = array('wbid' => $this->curr_wbid, 'wsid' => $this->curr_wsid);

							if (isset($nget_res))
								$res_arr[$ext['cbkey']][$nget_res[0][1][0]['name']] = $nget_res[0][1][0]['refers_to'];
						}
					} catch (Exception $e) {
						return array(false, 'errLoadWB_selErr');
					}
				}

		try {
			if (!isset($res_arr)) {
				if ($from_studio && count($resources = $node->getData()->getResources())) {
					if (!$ext['hidden'])
						$dep_ext = array('asid' => '', saverec => false, 'hidden' => true, 'lmark' => array($group_name . '-' . $hierarchy_name . '-' . $node_name)); // Temp. disabled: 'bels' => $llist
					else {
						$dep_ext = $ext;
						$dep_ext['lmark'][] = $group_name . '-' . $hierarchy_name . '-' . $node_name;
					}

					foreach ($resources as $resource) {
						if (in_array($resource['group'] . '-' . $resource['hierarchy'] . '-' . $resource['node'], $dep_ext['lmark'], true))
							return array(false, 'errLoadWB_cyclicDep');

						$load_res = $this->load_workbook($resource['node'], $resource['group'], $resource['hierarchy'], $dep_ext);

						if (!$load_res[0])
							return $load_res;
					}
				}

				$l10n = $_SESSION['prefs']->search('general/l10n');

				if ($from_studio) {
					$lpath = $path . (isset($ext) && array_key_exists('asid', $ext) && strlen($ext['asid']) > 0 ? '.' . $ext['asid'] : '');
					$ccmd = '[["load",' . json_encode($lpath) . ',' . json_encode($meta) . ',true,' . ($ext['appmode'] == 'user' || $perm < AccessPolicy::PERM_WRITE ? 'true' : 'false') . '],["oren",1,' . json_encode($name) . ']]';
				} else
					$ccmd = '[["load",' . json_encode(str_replace('\\', '/', realpath(self::WB_TEMPLATE_RELPATH . self::WB_TEMPLATE . '_' . $l10n . self::WB_EXTENSION))) . ',"",true,true]]';

				$res = json_decode(ccmd($ccmd), true);

				ccmd('[["osel",1,"' . ($this->curr_wbid = $res[0][1]) . '"]]');

				if ($from_studio)
					$llist[] = array('id' => $this->curr_wbid, 'name' => $name, 'path' => $lpath);

				if (isset($used_vars))
				{
					$set_vars_ccmd = '[';

					foreach ($used_vars as $var_name => $var_value)
						$set_vars_ccmd .= '["svar",' . json_encode($var_name) . ',' . json_encode($var_value) . '],';

					if (($ccmd_len = strlen($set_vars_ccmd)) > 1)
					{
						$set_vars_ccmd[$ccmd_len - 1] = ']';
						ccmd($set_vars_ccmd);
					}
				}

				// load sheet elements into session
				$list = json_decode(ccmd('[["olst",2]]'), true);
				$list = $list[0][0] && is_array($list[0][1]) ? $list[0][1] : array();
				$this->_loadCharts($list);

				// Load Macros
				$this->exportMacros();

				$sel_sheet_res = $this->selectSheet(null, false, !($ext['appmode'] == 'user' || $from_reports), $ext['sheet_name']);
				if (!$sel_sheet_res[0]) {
					$del_wbid = $this->curr_wbid;
					ccmd('[["osel",1,"' . ($this->curr_wbid = $prev_wbid) . '"]]');
					$this->selectSheet($prev_wsid);
					$this->removeBook($del_wbid);
					return array(false, 'follHLInvalidSheet');
				}

				if (isset($ext['nrange'])) {
					$nget_res = json_decode(ccmd('[["nget",[1,1,"' . $ext['nrange'] . '","' . $this->curr_wsid . '"]]]'), true);

					if (!$nget_res[0][0])
						$nget_res = json_decode(ccmd('[["nget",[1,1,"' . $ext['nrange'] . '",""]]]'), true);

					if (!$nget_res[0][0]) {
						$del_wbid = $this->curr_wbid;
						ccmd('[["osel",1,"' . ($this->curr_wbid = $prev_wbid) . '"]]');
						$this->selectSheet($prev_wsid);
						$this->removeBook($del_wbid);
						return array(false, 'follHLInvTrgNRange');
					}
				}

				if ($blank) {
					$id = isset($_SESSION['blwbcnum']) ? $_SESSION['blwbcnum'] + 1 : 1;
					$it = 1;

					do {
						$name = self::$l10n_book[$l10n] . $id;

						$wb_exists = false;
						for ($i = count($llist) - 1; $i >= 0; --$i)
							if ($llist[$i]['name'] == $name) {
								$wb_exists = true;
								break;
							}

						if (!$wb_exists) {
							ccmd('[["oren",1,' . json_encode($name) . ']]');
							break;
						} elseif ($id < 1000000)
							$id++;
						else {
							$id = 1;
							$it++;
						}
					} while ($it <= 2);

					$_SESSION['blwbcnum'] = $id;

					$init_sheets = $this->getSheets();
					if (($loc_sheet_name = str_replace('Sheet', self::$l10n_sheet[$l10n], $init_sheets[0][1])) != $init_sheets[0][1])
						ccmd('[["oren",2,"' . $loc_sheet_name . '"]]');
				}

				// Refresh Charts
				$this->_refreshCharts();

				// Auto-correct Workbook name if copied from blank_workbook_template.
				if ($this->getWbName($this->curr_wbid) == self::WB_TEMPLATE . '_' . $l10n)
					ccmd('[["oren",1,' . json_encode($name) . '],["save","' . $this->curr_wbid . '",""]]');

				$res_arr = array('wbid' => $this->curr_wbid, 'name' => $name, 'imp' => false, 'perm' => $perm);

				if (isset($res_fghn))
					$res_arr = array_merge($res_arr, $res_fghn);

				if (isset($ext['sheet_name']))
					$res_arr['wsid'] = $this->curr_wsid;

				if (isset($ext['cbkey'])) {
					$res_arr[$ext['cbkey']] = array('wbid' => $this->curr_wbid, 'wsid' => $this->curr_wsid);

					if (isset($nget_res))
						$res_arr[$ext['cbkey']][$nget_res[0][1][0]['name']] = $nget_res[0][1][0]['refers_to'];
				}
			}

			// Add to list of recent items.
			if ($save_recent && !$blank) {
				$meta_arr = json_decode($meta, true);
				$location = array(
					'group' => $meta_arr['group'],
					'hierarchy' => $meta_arr['hierarchy'],
					'node' => $meta_arr['node'],
					'path' => $from_reports && array_key_exists('rPath', $ext) ? $ext['rPath'] : '/' . $meta_arr['ghpath'] . $meta_arr['relpath']
				);

				if ($from_reports && count($recent_vars))
					$location['var'] = $recent_vars;

				$recent = new Recent($apol);
				$recent->add($from_reports || $ext['appmode'] == 'user' ? 'reports' : 'files', 'spreadsheet', $location);
				$recent->save();
			}

			return array(true, $res_arr);
		} catch (Exception $e) {
			return array(false, 'errLoadWB_coreErr');
		}
	}

	public function save_workbook($group, $hierarchy, $name, $parent_name = null, $repl_node = null, $active = true, $as_snapshot = false) {
		if (!$active) {
			$slist = json_decode(ccmd('[["bels"]]'), true);
			$slist = $slist[0][0] === true && is_array($slist[0][1]) ? $slist[0][1] : array();

			$node_loaded = false;
			$prev_node = null;

			foreach ($slist as &$node) {
				$meta = json_decode($node['meta'], true);

				if ($meta['group'] == $group && $meta['hierarchy'] == $hierarchy && $meta['node'] == $name) {
					$node_loaded = true;

					if ($node['id'] != $this->curr_wbid) {
						$prev_node = $this->curr_wbid;
						$this->curr_wbid = $node['id'];
						$this->curr_wsid = '';
					}

					break;
				}
			}

			if (!node_loaded)
				return array(true, array('wbid' => null));
		}

		// Get list of used variables in workbook.
		$var_list = json_decode(ccmd('[["gbvl"]]'), true);
		$var_list = $var_list[0][0] && is_array($var_list[0][1]) ? $var_list[0][1] : array();

		$apol = $_SESSION['accessPolicy'];
		$conn = $apol->getSuperConn();

		if (isset($parent_name)) {
			if (!isset($slist)) {
				$slist = json_decode(ccmd('[["bels"]]'), true);
				$slist = $slist[0][0] === true && is_array($slist[0][1]) ? $slist[0][1] : array();
			}

			for ($i = count($slist) - 1; $i >= 0; --$i)
				if (strlen($slist[$i]['meta']) && $slist[$i]['name'] == $name)
					return array(false, 'errWBSave_nameExists', array('name' => $name));

			$g = new W3S_Group($apol, $group);
			$g->registerPlugin(new W3S_FSPlugin(), true);
			$h = $g->getHierarchy($hierarchy);
			$parent_node = $h->getNode($parent_name);

			if (!isset($parent_node))
				return array(false, 'errWBSave_noParent', array('name' => $parent_name));

			if ($parent_node->getPermN() < AccessPolicy::PERM_WRITE)
				return array(false, 'errWBSave_noParentAccess');

			if (isset($repl_node)) {
				$exist_node = $h->getNode($repl_node);

				if (isset($exist_node))
					$parent_node->removeNode($exist_node);
			}

			$wb_meta = array('name' => $name, 'desc' => $name);
			if (count($var_list) > 0)
				$wb_meta['vars'] = $var_list;

			$wb_id = $parent_node->addNode(true, 'workbook', $wb_meta)->getUID();
			$path = str_replace('\\', '/', $parent_node->getSysPath()) . '/' . $wb_id . '-' . urlencode($name) . self::WB_EXTENSION;

			$node = $h->getNode($wb_id);
			$meta = isset($node) ? '{"group": "' . $group . '", "hierarchy": "' . $hierarchy . '", "node": "' . $wb_id . '", "relpath": "' . $node->getRelPath($node, false) .
					'", "ghpath": "/' . $g->getData()->getName() . '/' . $h->getData()->getName() . '", "name": "' . $name . '", "perm": "' . AccessPolicy::PERM_DELETE . '", "hidden": false, "cnts": ["so"]}' : '';

			$save_cmd = array(
				array('oren', 1, $name),
				array('bcmd', $meta),
				array('save', $this->curr_wbid, $path, true, $as_snapshot)
			);

			if ($as_snapshot) {
				$save_cmd[] = array('odel', 1, $this->curr_wbid);
				$save_cmd[] = array('load', $path, $meta, true, false);
				$save_cmd[] = array('oren', 1, $name);
			}

			$save_res = ccmd($save_cmd);

			foreach ($save_res as $cmd_res)
				if (!$cmd_res[0])
					return array(false, 'saveFileErr');

			if ($as_snapshot) {
				ccmd('[["osel",1,"' . ($this->curr_wbid = $save_res[4][1]) . '"]]');
				$this->selectSheet(null, false, true);
			}

			// Add to list of recent items.
			$recent = new Recent($apol);
			$recent->add('files', 'spreadsheet', array('group' => $group, 'hierarchy' => $hierarchy, 'node' => $wb_id, 'path' => '//' . $g->getData()->getName() . '/' . $h->getData()->getName() . $parent_node->getRelPath($parent_node, false) . '/' . $name));
			$recent->save();

			return array(true, array('wbid' => $this->curr_wbid, 'group' => $group, 'hierarchy' => $hierarchy, 'node' => $wb_id, 'perm' => AccessPolicy::PERM_DELETE));
		} else {
			$g = new W3S_Group($apol, $group);
			$h = $g->getHierarchy($hierarchy);
			$n = $h->getNode($name);
			$save_wbid = $this->curr_wbid;

			if ($n->getPermN() < AccessPolicy::PERM_WRITE)
				return array(false, 'errWBSave_noAccess');

			W3S_NodeData::setVariables($conn, $group, $hierarchy, $name, $var_list);

			if (!$active && !is_null($prev_node)) {
				$this->curr_wbid = $prev_node;
				$this->curr_wsid = '';
			}

			$save_res = ccmd(array(array('save', $save_wbid ,'')));

			return array(true, array('wbid' => $save_wbid));
		}
	}

	public function getWbName ($uid = null)
	{
		if ($uid == null)
			$uid = $this->curr_wbid;

		$list = json_decode(ccmd('[["olst",1]]'), true);

		if ($list[0][0] !== true)
			return false;

		$list = &$list[0][1];

		return isset($list[$uid]) ? $list[$uid] : false;
	}

	// add a sheet if it doesn't already exist and also select it
	public function addSheet($nextSheetId = '') {
		$sheets = $this->getSheets();

		$i = 0;
		$name_found = false;
		$l10n = $_SESSION['prefs']->search('general/l10n');

		do {
			$name = self::$l10n_sheet[$l10n] . ++$i;
			if (!in_array($name, $sheets[0])) {
				$name_found = true;
				break;
			}
		} while ($id < 1000);

		$name = ($name_found) ? $name : 'SheetA';

		try
		{
			$res = json_decode(ccmd('[["oadd",2,' . json_encode($name) . ',' . json_encode($nextSheetId) . ']]'), true);
			$this->curr_wsid = $res[0][1];

			ccmd('[["osel",2,"' . $this->curr_wsid . '"]]');
		}
		catch (Exception $e)
		{
			return array('errcode' => 1);
		}

		return array('errcode' => 0, 'wsid' => $this->curr_wsid, 'name' => $name);
	}

	public function copySheet ($sheetUid, $nextSheetUid = '', $bookUid = '')
	{
		$res = json_decode(ccmd('[["scp","' . $sheetUid . '","' . $nextSheetUid . '","' . $bookUid . '"]]'), true);

		if ($res[0][0] === false)
			return array('errcode' => $res[0][1], 'errdesc' => $res[0][2]);

		$res = json_decode(ccmd('[' . ($bookUid == '' ? '' : '["osel",1,"' . ($this->curr_wbid = $bookUid) . '"],') . '["osel",2,"' . ($this->curr_wsid = $res[0][1]) . '"],["olst",2]]'), true);

		return array('errcode' => 0, 'wsid' => $this->curr_wsid, 'name' => $res[$bookUid == '' ? 1 : 2][1][$this->curr_wsid]);
	}

	public function moveSheet ($sheetUid, $nextSheetUid = '', $bookUid = '')
	{
		$res = json_decode(ccmd('[["smv","' . $sheetUid . '","' . $nextSheetUid . '","' . $bookUid . '"]' . ($bookUid == '' ? ',["olst",2]' : '') . ']'), true);

		if ($res[0][0] === false)
			return array('errcode' => $res[0][1], 'errdesc' => $res[0][2]);

		if ($bookUid == '')
			$sheetName = $res[1][1][$this->curr_wsid];
		else
		{
			$res = json_decode(ccmd('[["osel",1,"' . ($this->curr_wbid = $bookUid) . '"],["osel",2,"' . ($this->curr_wsid = $res[0][1]) . '"],["olst",2]]'), true);
			$sheetName = $res[2][1][$this->curr_wsid];
		}

		return array('errcode' => 0, 'wsid' => $this->curr_wsid, 'name' => $sheetName);
	}

	public function addCloneWorksheet() {
		$curr_wsid = $this->curr_wsid;

		try {
			$new_wsid = json_decode(ccmd('[["sclo","' . ('S' . mt_rand()) . '"]]'), true);

			if ($new_wsid[0][0] !== true)
				return false;

			$new_wsid = $new_wsid[0][1];

			$this->worksheet_elems->copy_worksheet_storage($this->curr_wbid, $curr_wsid, $new_wsid);
			$this->worksheet_clones[$new_wsid] = $curr_wsid;
			ccmd('[["osel",2,"' . ($this->curr_wsid = $new_wsid) . '"]]');

			return $new_wsid;
		} catch(Exception $e) {
			ccmd('[["osel",2,"' . ($this->curr_wsid = $curr_wsid) . '"]]');
			return false;
		}
	}

	public function removeCloneWorksheet() {
		try {
			$cloned_wsid = $this->curr_wsid;
			ccmd('[["osel",2,"' . ($this->curr_wsid = $this->worksheet_clones[$cloned_wsid]) . '"]]');
			unset($this->worksheet_clones[$cloned_wsid]);
			ccmd('[["srcl","' . $cloned_wsid . '"]]');
			$this->worksheet_elems->remove_worksheet_storage($this->curr_wbid, $cloned_wsid);

			return $this->curr_wsid;
		} catch(Exception $e) {
			return false;
		}
	}

	public function getSheets ($bookUid = null, $cloned = false)
	{
		$res = json_decode(ccmd('[["olst",2' . ($bookUid === null ? '' : ',"' . $bookUid . '"') . ']]'), true);

		if ($res[0][0] !== true || !is_array($res[0][1]))
			return array();

		$list = array();

		if (is_array($this->worksheet_clones))
			$wsclones_flip = array_flip($this->worksheet_clones);

		foreach ($res[0][1] as $uid => $name)
			array_push($list, $cloned && in_array($uid, $this->worksheet_clones) ? $wsclones_flip[$uid] : $uid, $name);

		return array($list, $this->curr_wsid);
	}

	public function getLoadedBooks ()
	{
		$res = json_decode(ccmd('[["bels"]]'), true);

		if ($res[0][0] !== true || !is_array($res[0][1]))
			return array();

		$list = array();

		foreach ($res[0][1] as &$book)
			$list[] = array($book['id'], $book['name'], $book['meta']);

		return $list;
	}

	public function getLoadedNodes ($designer_mode = true, $act_only = false) {
		$res = json_decode(ccmd('[["bels"]]'), true);

		if ($res[0][0] !== true || !is_array($res[0][1]))
			return array();

		$list = array();

		foreach ($res[0][1] as &$book) {
			$meta = json_decode($book['meta'], true);
			$is_report = $meta['group'][0] == 'r';

			if (!is_null($meta)) {
				foreach ($meta['cnts'] as $cnt) {

					if ($cnt == 'so') {
						$nidx = $meta['group'] . '-' . $meta['hierarchy'] . '-' . $meta['node'];

						$list[$nidx] = array(
							'type' => $is_report ? 'template' : 'workbook',
							'meta' => array(
								'g' => $meta['group'],
								'h' => $meta['hierarchy'],
								'n' => $meta['node'],
								'p' => $meta['perm'],
								'v' => $meta['hidden']
							),
							'ext' => array(
								'uid' => $book['id'],
								'name' => $book['name']
							)
						);

						if (array_key_exists('fgroup', $meta)) {
							$list[$nidx]['meta']['fg'] = $meta['fgroup'];
							$list[$nidx]['meta']['fh'] = $meta['fhierarchy'];
							$list[$nidx]['meta']['fn'] = $meta['fnode'];
						}
					} else {
						$cnt = explode('#', $cnt, 2);
						$frame_name = $cnt[1];
						$cnt = $cnt[0];

						if (!array_key_exists($cnt, $list)) {
							$conn = $_SESSION['accessPolicy']->getConn();

							$ghn = explode('-', $cnt, 3);
							$group = $ghn[0];
							$hierarchy = $ghn[1];
							$node = $ghn[2];
							$is_fs_report = $ghn[0][0] == 'r';

							if ($is_fs_report) {
								$rep_node_data = W3S_NodeData::getNodeData($conn, $group, $hierarchy, $node);
								$real_node = $rep_node_data->getReference();

								$group = $real_node->getGroup();
								$hierarchy = $real_node->getHierarchy();
								$node = $real_node->getNode();

								$fghn = array('fg' => $group, 'fh' => $hierarchy, 'fn' => $node);
							}

							$node_data = W3S_NodeData::getNodeData($conn, $group, $hierarchy, $node);

							$frameset = $node_data->getFrameset()->getAssoc();
							$frameset['name'] = $node_data->getName();

							foreach ($frameset['frames'] as &$frame) {
								$frame['uid'] = '';
								$frame['ldres'] = array(false, array());
							}

							$list[$cnt] = array(
								'type' => $is_fs_report ? 'rframeset' : 'frameset',
								'meta' => is_null($meta) ? null : array(
									'g' => $ghn[0],
									'h' => $ghn[1],
									'n' => $ghn[2],
									'p' => $meta['perm'],
									'v' => false
								),
								'ext' => $frameset
							);

							if (isset($fghn))
								$list[$cnt]['meta'] = array_merge($list[$cnt]['meta'], $fghn);
						}

						foreach ($list[$cnt]['ext']['frames'] as &$frame) {
							if ($frame['name'] == $frame_name) {
								$frame['group'] = $meta['group'];
								$frame['hierarchy'] = $meta['hierarchy'];
								$frame['node'] = $meta['node'];
								$frame['uid'] = $book['id'];

								$frame['ldres'] = array(true, array(
										'wbid' => $book['id'],
										'name' => $book['name'],
										'perm' => $meta['perm'],
										'imp' => false
									)
								);

								break;
							}
						}

						if ($meta['perm'] < $list[$cnt]['meta']['p'])
							$list[$cnt]['meta']['p'] = $meta['perm'];
					}
				}

			} else {
				$nidx = $book['id'];

				$list[$nidx] = array(
					'type' => 'workbook',
					'meta' => null,
					'ext' => array(
						'uid' => $book['id'],
						'name' => $book['name']
					)
				);
			}

			$this->selectBook($book['id'], $designer_mode, false);
		}

		$clist = array();

		foreach ($list as $nidx => $node) {
			if (in_array($node['type'], self::$framesets)) {
				foreach ($node['ext']['frames'] as &$frame) {
					if (!strlen($frame['uid'])) {
						continue 2;
					}
				}
			}

			$clist[$nidx] = $node;
		}

		if ($act_only && !is_null($act_node = $_SESSION['prefs']->search('node')))
			$curr_nidx = $act_node;

		return !count($clist) ? $clist : ($act_only ? array($clist[$curr_nidx]) : array_values($clist));
	}

	public function removeBook ($uid, $bels = null)
	{
		$bels_set = isset($bels);
		$direct_rm = !$bels_set;

		// Get the list of loaded workbooks.
		if (!$bels_set) {
			$bels = json_decode(ccmd('[["bels"]]'), true);

			if ($bels[0][0] !== true)
				return false;

			if (!is_array($bels = $bels[0][1]) || !count($bels))
				return true;
		}

		$bels_metas = array();

		foreach($bels as $wb)
			if ($wb['id'] == $uid)
				$wb_meta = !strlen($wb['meta']) ? array() : json_decode($wb['meta'], true);
			elseif (strlen($wb['meta'])) {
				$ometa = json_decode($wb['meta'], true);
				$ometa['id'] = $wb['id'];

				$bels_metas[] = $ometa;
			}

		if (!isset($wb_meta))
			return true;

		if (count($wb_meta)) {
			$apol = $_SESSION['accessPolicy'];
			$g_idx = $wb_meta['group'][0] == 'r' ? 'f' : '';

			if (count($bels_metas)) {
				try {
					$node_data = W3S_NodeData::getNodeData($apol->getSuperConn(), $wb_meta[$g_idx . 'group'], $wb_meta[$g_idx . 'hierarchy'], $wb_meta[$g_idx . 'node']);

					if (count($deps = $node_data->getDependents()))
						foreach ($bels_metas as $bels_meta) {
							$dep_g_idx = $bels_meta['group'][0] == 'r' ? 'f' : '';

							foreach ($deps as $dep)
								if ($dep['group'] == $bels_meta[$dep_g_idx . 'group'] && $dep['hierarchy'] == $bels_meta[$dep_g_idx . 'hierarchy'] && $dep['node'] == $bels_meta[$dep_g_idx . 'node']) {
									if (!$wb_meta['hidden']) {
										$wb_meta['hidden'] = true;
										ccmd('[["bcmd",' . json_encode(str_replace('\\', '', json_encode($wb_meta))) . ',"' . $uid . '"]]');
									}

									return true;
								}
						}
				} catch (Exception $e) {
					return false;
				}
			}

			$pvars = W3S_NodeData::getVariables($apol->getSuperConn(), $wb_meta[$g_idx . 'group'], $wb_meta[$g_idx . 'hierarchy'], $wb_meta[$g_idx . 'node'], array('private' => true));
			$gvar_cmd = array();

			foreach ($pvars as $name => $params)
				$gvar_cmd[] = array('gvar', $name);

			if (count($gvar_cmd)) {
				$gvar_res = ccmd($gvar_cmd);
				$data = array();

				foreach ($gvar_res as $idx => &$val)
					$data[] = array('name' => $gvar_cmd[$idx][1], 'val' => $val[0] === true ? json_encode($val[1]) : '');

				$usr_data = new W3S_NodeUserData(!strlen($g_idx) ? 'workbook' : 'template');
				$usr_data->loadSA($apol, $wb_meta['group'], $wb_meta['hierarchy'], $wb_meta['node']);
				$usr_data->set('.', array('var' => $data));

				$save_res = $usr_data->saveSA($apol, $wb_meta['group'], $wb_meta['hierarchy'], $wb_meta['node']);
			}
		}

		$cnts_len = count($wb_meta['cnts']);

		if ($direct_rm && $cnts_len > 1) {
			for ($i = 0; $i < $cnts_len; $i++)
				if ($wb_meta['cnts'][$i] == 'so') {
					array_splice($wb_meta['cnts'], $i, 1);
					ccmd('[["bcmd",' . str_replace('\\\\\\/', '/', json_encode(json_encode($wb_meta))) . ',"' . $uid . '"]]');
				}
		} else {
			$this->worksheet_elems->remove_workbook_storage($uid);
			palo::unloadBookSess($uid);

			$del_res = json_decode(ccmd('[["odel",1,"' . $uid . '"]]'), true);

			if ($del_res[0][0] !== true)
				return false;


			if (isset($node_data) && count($ress = $node_data->getResources())) {
					foreach ($bels_metas as $bels_meta) {
						$g_idx = $bels_meta['group'][0] == 'r' ? 'f' : '';

						foreach ($ress as $res)
							if ($bels_meta['hidden'] && $res['group'] == $bels_meta[$g_idx . 'group'] && $res['hierarchy'] == $bels_meta[$g_idx . 'hierarchy'] && $res['node'] == $bels_meta[$g_idx . 'node'])
								$this->removeBook($bels_meta['id']);
					}
			}
		}

		$list = json_decode(ccmd('[["olst",1]]'), true);

		if (!count($list[0][1]))
			$this->curr_wsid = $this->curr_wbid = '';

		return true;
	}

	public function selectSheet ($uid = null, $cloned = false, $designer_mode = true, $name = null, $tmp = false, $refresh = false)
	{
		// Unload Palo Session data for current Sheet
		if ($this->curr_wsid != null)
			palo_view::unloadPvSess();

		if ($uid !== null && $cloned)
		{
			ccmd('[["osel",2,"' . ($this->curr_wsid = $uid) . '"]]');
			return array(true, false, $this->curr_wsid);
		}

		$list = json_decode(ccmd('[["olst",2]]'), true);

		if ($list[0][0] !== true || !is_array($list = $list[0][1]) || !count($list))
			return array(false);

		if ($name !== null)
		{
			if (($uid = array_search($name, $list)) === false)
				return array(false);
		}
		else if ($uid !== null && !isset($list[$uid]))
				return array(false);

		reset($list);

		$wsid = $uid !== null ? $uid : key($list);

		if (is_array($this->worksheet_clones) && in_array($wsid, $this->worksheet_clones)) {
			$wsclones_copy = $this->worksheet_clones;
			$wsclones_copy = array_flip($wsclones_copy);
			ccmd('[["osel",2,"' . ($this->curr_wsid = $wsclones_copy[$wsid]) . '"]]');
		} else {
			if (!$tmp)
				$this->curr_wsid = $wsid;

			ccmd('[["osel",2,"' . $wsid . '"]]');

			if ($refresh)
				$this->_refreshCharts();

			// clone if necessary
			if (!$cloned && !$designer_mode) {
				$res = json_decode(ccmd('[["wget","",[],["e_id"],{"e_type":"hb"}]]'), true);

				if ($res[0][0] && count($res[0][1]) && $this->addCloneWorksheet() !== false) {
					$this->cb('hb_run', array());
					$this->_refreshCharts();

					return array(true, true, $this->curr_wsid);
				}
			}
		}

		return array(true, false, $this->curr_wsid);;
	}

	public function selectBook ($uid, $designer_mode = true, $sel_first_sheet = true)
	{
		$res = json_decode(ccmd('[["osel",1,"' . $uid . '"]]'), true);

		if ($res[0][0] !== true)
			return array(false);

		$this->curr_wbid = $uid;

		// make the first sheet in the book active, otherwise return false
		$res = $this->selectSheet($sel_first_sheet ? null : $this->curr_wsid, false, $designer_mode);

		return array(true, $res[1], $res[2]);
	}

	public function resolveNodePath($path, $type = 'file') {
		$path_elems = explode('/', $path[0] == '/' ? substr($path, 1) : $path, 3);

		if (count($path_elems) < 3)
			return null;

		$ghnt = array();
		$apol = $_SESSION['accessPolicy'];

		// Resolve Group.
		$groups = W3S_Group::listGroups($apol, array($type));

		foreach ($groups as $group => $meta)
			if ($meta['name'] == $path_elems[0]) {
				$ghnt['g'] = $group;
				break;
			}

		if (!isset($ghnt['g']))
			return null;

		$group = new W3S_Group($apol, $ghnt['g']);

		// Resolve Hierarchy.
		$hierarchies = $group->listHierarchies();

		foreach ($hierarchies as $hierarchy => $meta)
			if ($meta['name'] == $path_elems[1]) {
				$ghnt['h'] = $hierarchy;
				break;
			}

		if (!isset($ghnt['h']))
			return null;

		$hierarchy = $group->getHierarchy($ghnt['h']);

		// Resolve Node.
		$node = $hierarchy->getNodeByPath($path_elems[2]);

		if (!isset($node))
			return null;

		$ghnt['n'] = $node->getUID();
		$ghnt['t'] = $node->getData()->getEffectiveType();

		return $ghnt;
	}


	/*
	 * ##############
	 * ### MACROS ###
	 * ##############
	 */

  public function exportMacros ()
  {
		$ccmd = '[["bget","",[],["e_id","name","src"],{"e_type":"macromdl"}],["em","php","base/macro/em.php","gt",[]]]';

		$res = json_decode(ccmd($ccmd), true);

		$mdls = $res[0][1];

		if (!count($mdls))
			return true;


		$tmppath = $res[1][1];

		if (!is_writable($tmppath))
			return false;

		$tmppath = $tmppath . DIRECTORY_SEPARATOR . self::MACRO_FILE_PFX . $this->curr_wbid . '.php';

		if (file_exists($tmppath))
		{
			if (is_dir($tmppath))
				return false;

			unlink($tmppath);
		}


		$fp = fopen($tmppath, 'a');
		fwrite($fp, "<?php\n\n");


		foreach ($mdls as $idx => &$mdl)
		{
			fwrite($fp, '// ' . $mdl['name'] . ' (' . $mdl['e_id'] . ")\n\n");
			fwrite($fp, $mdl['src']);
			fwrite($fp, "\n\n\n");
		}

		fwrite($fp, '?>');
		fclose($fp);

		ccmd('[["em","php","base/macro/register.php","_",[]]]');

		return true;
  }


	/*
	 * ################
	 * ### GRID OPS ###
	 * ################
	 */

	private static function _lettersToNumber ($ltrs)
	{
		$num = 0;

		for ($f = 1, $i = strlen($ltrs = strtoupper($ltrs)) - 1; $i >= 0; --$i, $f *= 26)
			$num += (ord($ltrs[$i]) - 64) * $f;

		return $num;
	}

	private function _handle_changed_wsels (array &$res)
	{
		if (array_shift($res) !== true)
			return $res = array();

		$l10n = $_SESSION['prefs']->search('general/l10n');

		$ui_ccmd = array();

		foreach ($res as $idx => &$cmd)
			switch ($cmd[0])
			{
				case 'wmvd':

					$wmv_cmd = array('wmv');

					foreach ($cmd[1] as &$wsel)
					{
						$pos = preg_match(self::RE_RANGE, $wsel['n_location'], $pos) ? array(self::_lettersToNumber($pos[1]), intval($pos[2]), self::_lettersToNumber($pos[3]), intval($pos[4])) : array(0, 0, 0, 0);

						$elem = array('id' => $wsel['e_id'], 'type' => $wsel['e_type'], 'loc' => $wsel['n_location'], 'pos' => $pos, 'offsets' => $wsel['pos_offsets']);

						if ($wsel['e_type'] == 'formel')
							$elem['formel_type'] = $wsel['formel_type'];

						$wmv_cmd[] = $elem;
					}

					if (count($wmv_cmd) > 1)
						$ui_ccmd[] = $wmv_cmd;

					unset($res[$idx]);

					break;

				case 'wdrt':

					$rw_cmd = array('rw');
					$rf_cmd = array('rf');

					foreach ($cmd[1] as &$wsel)
						switch ($wsel['e_type'])
						{
							case 'chart':
								if ($this->worksheet_elems->refresh_source_data($this->curr_wbid, $this->curr_wsid, $wsel))
									$rw_cmd[] = $wsel['e_id'];
								break;

							case 'hb':
								$this->hb_catalog->genDataList($wsel['e_id'], $wsel['id'], $wsel['n_get_val'], true);
								break;

							case 'formel':
								$rf_cmd[] = array('id' => $wsel['e_id'], 'val' => $wsel['n_get_val'], 'ref' => $wsel['n_refers_to']);
								break;
						}

					if (count($rw_cmd) > 1)
						$ui_ccmd[] = $rw_cmd;

					if (count($rf_cmd) > 1)
						$ui_ccmd[] = $rf_cmd;

					unset($res[$idx]);

					break;

				case 'wtrd':

					if (count($cmd[1]))
					{
						array_unshift($cmd[1], 'wtrd');
						$ui_ccmd[] = $cmd[1];
					}

					unset($res[$idx]);

					break;
			}

		return $ui_ccmd;
	}

  public function refresh (array $vscroll, $auto_calc = true)
	{
		ccmd('[' . ($auto_calc ? '' : '["sac",1],') . '["bcc"]]');

		ksort($vscroll);

		$data = array();

		$curr_buid = $this->curr_wbid;
		$curr_suid = $this->curr_wsid;
		$suidmap = array();
		$ccmd = '[';
		$uid_old = '';

		foreach ($vscroll as $key => $ranges)
		{
			list ($uid, $id) = explode('.', $key);

			if ($uid)
			{
				$this->curr_wbid = $uid;
				$this->curr_wsid = '';

				$res = json_decode(ccmd('[["gcwe"],["ocurr",2]]'), true);

				$this->curr_wsid = $suidmap[$uid] = $res[1][1];
			}
			else
			{
				$this->curr_wbid = $curr_buid;
				$this->curr_wsid = $curr_suid;

				$res = json_decode(ccmd('[["gcwe"]]'), true);
			}

			$gcwe = $this->_handle_changed_wsels($res[0]);

			if (!empty($gcwe))
			{
				$data[$id] = $gcwe;

				$res = json_decode(ccmd('[["gcwe"]]'), true);
				$gcwe = $this->_handle_changed_wsels($res[0]);

				if (!empty($gcwe))
					array_splice($data[$id], -1, 0, $gcwe);
			}

			if ($uid_old != $uid)
				$ccmd .= '["osel",1,"' . ($uid ? $uid : $this->curr_wbid) . '"],';

			if (!is_array($ranges[0]))
				$ccmd .= '["grar",' . self::Q_ALL . ',' . implode(',', $ranges) . ',true],';
			else
				foreach ($ranges as $range)
					$ccmd .= '["grar",' . self::Q_ALL . ',' . implode(',', $range) . ',true],';

			$ccmd .= '["gcwe"],["gcr",0,1,' . self::MAX_COL . '],["gcr",1,1,' . self::MAX_ROW . '],["gurn"],';

			$uid_old = $uid;
		}

		$this->curr_wbid = $curr_buid;
		$this->curr_wsid = $curr_suid;

		$ccmd .= '["ecc"]' . ($auto_calc ? ']' : ',["sac",0]]');

		$res = json_decode(ccmd($ccmd), true);

		$uid_old = '';
		$cnt = -1;

		foreach ($vscroll as $key => $ranges)
		{
			list ($uid, $id) = explode('.', $key);

			if ($uid)
			{
				$this->curr_wbid = $uid;
				$this->curr_wsid = $suidmap[$uid];
			}
			else
			{
				$this->curr_wbid = $curr_buid;
				$this->curr_wsid = $curr_suid;
			}

			if (!isset($data[$id]))
				$data[$id] = array();

			if ($uid_old != $uid)
				++$cnt;

			if (!is_array($ranges[0]))
			{
				array_splice($res[++$cnt], 0, 1, array('crgn', (object) array()));
				array_unshift($data[$id], $res[$cnt]);
			}
			else
				foreach ($ranges as $idx => $range)
				{
					array_splice($res[++$cnt], 0, 1, array('crgn', array('p' => $idx)));
					array_unshift($data[$id], $res[$cnt]);
				}

			$gcwe = $this->_handle_changed_wsels($res[++$cnt]);

			if (!empty($gcwe))
				array_splice($data[$id], -1, 0, $gcwe);

			$data[$id][] = array('ncr', $res[++$cnt][1], $res[++$cnt][1]);

			$data[$id][] = array('curn', $res[++$cnt][1][0], $res[$cnt][1][1]);

			$uid_old = $uid;
		}

		$this->curr_wbid = $curr_buid;
		$this->curr_wsid = $curr_suid;

		return $data;
	}

	public function cb ($handle, $params, $vscroll = null, $property_set = self::Q_ALL, $dimension_set = self::D_BOTH)
	{
		if (!isset(self::$cb_handles[$handle]))
			return '[]';

		$hndl = &self::$cb_handles[$handle];

		if ($hndl[0] == null)
			$cb = $hndl[1];
		else if ($hndl[0][0] == '$')
			$cb = array($this->{substr($hndl[0], 1)}, $hndl[1]);
		else
			$cb = array(new $hndl[0], $hndl[1]);

		if (!is_callable($cb))
			return '[]';

		$l10n = $_SESSION['prefs']->search('general/l10n');

		if ($hndl[2])
		{
			if (!is_array($ccmd = call_user_func_array($cb, $params)))
				return '[]';

			if ($hndl[3] && $l10n != 'en_US')
			{
				array_unshift($ccmd, array('susl', 'en_US'));
				$ccmd[] = array('susl', $l10n);
			}

			return $vscroll ? $this->ccmd(json_encode($ccmd), $vscroll, $property_set, $dimension_set, self::CCMD_STOP_ON_ERR) : ccmd($ccmd);
		}

		if ($vscroll)
		 $this->_diff_start($vscroll, $property_set, $dimension_set);

		if ($hndl[3] && $l10n != 'en_US')
			ccmd('[["susl","en_US"]]');

		$res = call_user_func_array($cb, $params);

		if ($hndl[3] && $l10n != 'en_US')
			ccmd('[["susl","' . $l10n . '"]]');

		$ui_ccmd = $vscroll ? $this->_diff_stop($vscroll) : array();

		return array($ui_ccmd, $res);
	}

	public function _diff_start (array &$vscroll, $property_set, $dimension_set)
	{
		krsort($vscroll);

		$ccmd = '[';
		$uid_old = '';

		foreach ($vscroll as $key => $ranges)
		{
			list ($uid, ) = explode('.', $key);

			if ($uid_old != $uid)
				$ccmd .= '["osel",1,"' . ($uid ? $uid : $this->curr_wbid) . '"],';

			if (!is_array($ranges[0]))
				$ccmd .= '["snpc",' . join(',', $ranges) . ',' . $property_set . ',' . $dimension_set . '],';
			else
			{
				$ccmd .= '["snpc",' . join(',', $ranges[$p = count($ranges) - 1]) . ',' . $property_set . ',' . $dimension_set . '],';

				for (--$p; $p >= 0; --$p)
					$ccmd .= '["snpc",' . join(',', $ranges[$p]) . ',' . $property_set . ',0],';
			}

			$uid_old = $uid;
		}

		$ccmd[strlen($ccmd) - 1] = ']';

		ccmd($ccmd);
	}

	public function _diff_stop (array &$vscroll)
	{
		ksort($vscroll);

		$diff = array();

		$curr_buid = $this->curr_wbid;
		$curr_suid = $this->curr_wsid;
		$suidmap = array();
		$ccmd = '[';
		$uid_old = '';

		foreach ($vscroll as $key => $ranges)
		{
			list ($uid, $id) = explode('.', $key);

			if ($uid)
			{
				$this->curr_wbid = $uid;
				$this->curr_wsid = '';

				$res = json_decode(ccmd('[["gcwe"],["ocurr",2]]'), true);

				$this->curr_wsid = $suidmap[$uid] = $res[1][1];
			}
			else
			{
				$this->curr_wbid = $curr_buid;
				$this->curr_wsid = $curr_suid;

				$res = json_decode(ccmd('[["gcwe"]]'), true);
			}

			$gcwe = $this->_handle_changed_wsels($res[0]);

			if (empty($gcwe))
				$diff[$id] = array();
			else
			{
				$diff[$id] = $gcwe;

				$res = json_decode(ccmd('[["gcwe"]]'), true);
				$gcwe = $this->_handle_changed_wsels($res[0]);

				if (!empty($gcwe))
					array_splice($diff[$id], -1, 0, $gcwe);
			}

			if ($uid_old != $uid)
				$ccmd .= '["osel",1,"' . ($uid ? $uid : $this->curr_wbid) . '"],';

			if (!is_array($ranges[0]))
				$ccmd .= '["snpd"],';
			else
			{
				for ($p = count($ranges); $p > 1; --$p)
					$ccmd .= '["snpd",false],';

				$ccmd .= '["snpd"],';
			}

			$uid_old = $uid;
		}

		$this->curr_wbid = $curr_buid;
		$this->curr_wsid = $curr_suid;

		$ccmd[strlen($ccmd) - 1] = ']';

		$res = json_decode(ccmd($ccmd), true);

		$uid_old = '';
		$cnt = -1;

		foreach ($vscroll as $key => $ranges)
		{
			list ($uid, $id) = explode('.', $key);

			if ($uid)
			{
				$this->curr_wbid = $uid;
				$this->curr_wsid = $suidmap[$uid];
			}
			else
			{
				$this->curr_wbid = $curr_buid;
				$this->curr_wsid = $curr_suid;
			}

			if ($uid_old != $uid)
				++$cnt;

			if (!is_array($ranges[0]))
				$p = 0;
			else
				for ($c = count($ranges) - 1, $p = 0; $p < $c; ++$p)
				{
					$res_c = &$res[++$cnt];
					array_shift($res_c);

					if (empty($res_c))
						continue;

					$res_c[0][1]['p'] = $p;
					array_splice($diff[$id], 0, 0, $res_c);
				}

			$res_c = &$res[++$cnt];
			$res_c[1][1]['p'] = $p;

			array_splice($diff[$id], -1, 0, $this->_handle_changed_wsels($res_c));
			array_splice($diff[$id], 0, 0, $res_c);

			$uid_old = $uid;
		}

		$this->curr_wbid = $curr_buid;
		$this->curr_wsid = $curr_suid;

		return $diff;
	}

	public function ccmd ($ccmd, array $vscroll, $property_set = self::Q_ALL, $dimension_set = self::D_BOTH, $flags = -1)
	{
		$this->_diff_start($vscroll, $property_set, $dimension_set);

		$res = json_decode(ccmd($ccmd, $flags), true);

		$ui_ccmd = $this->_diff_stop($vscroll);

		return array($ui_ccmd, $res);
	}
}

?>