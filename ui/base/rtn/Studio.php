<?php

/*
 * \brief Studio RPC routines
 *
 * \file Studio.php
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 * Andrej Vrhovac <andrej.vrhovac@develabs.com>
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: Studio.php 5134 2011-07-20 13:17:32Z predragm $
 *
 */

class Studio
{
	const UNDEFINED = -1;
	const WB_EXTENSION = '.wss';

	public static $errMsg = array(
		1 => 'Exception Msg: ',

		111 => 'Connection failed!',
		122 => 'Getting  data failed!',
		123 => 'Setting data failed!',
		132 => 'Element list failed!',
		133 => 'Adding element failed!',
		134 => 'Removing element failed!',
		135 => 'Element already exists.',
		136 => 'Renaming element failed!',
		142 => 'Element already exists!'
	);

	private $currGroup;
	private $currHierarchy;

	private $plugins;

	private $accessPolicy;

	public function __construct ()
	{
		if (!isset($_SESSION['studio']))
			$_SESSION['studio'] = new SessStudio();

		$session = $_SESSION['studio'];

		$this->currGroup = &$session->currGroup;
		$this->currHierarchy = &$session->currHierarchy;

		$this->plugins = &$session->plugins;

		$this->accessPolicy = $_SESSION['accessPolicy'];
	}

	/*
	 * \brief verifies that the Core session is still alive
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function verifySess ()
	{
		$res = json_decode(ccmd('[["ilog"]]', -1, $_SESSION['WSSU_SESSID']), true);

		return $res[0][0] ? $res[0][1] : false;
	}

	/*
	 * \brief instructs Core to refresh Palo connection database
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function syncPaloConnData ()
	{
		ccmd('[["tee","palo_wss3",0.0]]', -1, $_SESSION['WSSU_SESSID']);
	}

	public function getUserCreds ()
	{
		return array(true, array('user' => $this->accessPolicy->getUser(), 'pass' => $this->accessPolicy->getPass()));
	}


	/*
	 * #############
	 * ### PREFS ###
	 * #############
	 */

	public function getPrefs ($level, $name = null, $path = null)
	{
		$prefs = $level == Prefs::LEVEL_USER && $name === null ? $_SESSION['prefs'] : new Prefs($this->accessPolicy, $level, $name);

		 return $prefs->get($path);
	}

	public function setPrefs ($level, $name, $data, $path = null) // eg. (2, 'smith', { general: { l10n: 'de_DE' }, wss: { interface: 'toolbar' } });
	{
		$prefs = new Prefs($this->accessPolicy, $level, $name);

		$prefs->set($path, $data);

		return $prefs->save($this->accessPolicy);
	}

	public function removePrefs ($level, $name, $path1) // , ..., $pathN)
	{
		$prefs = new Prefs($this->accessPolicy, $level, $name);

		$paths = func_get_args();
		array_splice($paths, 0, 2);

		foreach ($paths as $path)
			$prefs->remove($path);

		return $prefs->save($this->accessPolicy);
	}

	public function removeUserPrefGroupsFromSession(){
		$this->removeFromSessionCurrGH('prefs_file');
		$this->removeFromSessionCurrGH('prefs_report');
	}


	//================================================== Connections =================================================================

	public function getAllConnections ()
	{
		$db = 'Config';
		$cube = '#_connections';
		$order = array('connections');
		$coords = array('#_connections_' => array('name', 'type'));

		$conns = common::paloGet(null, $db, $cube, $order, $coords);

		if (!is_array($conns) || empty($conns))
			return array();

		$perms = $this->accessPolicy->calcPerms($db, $order[0], array_keys($conns), false, 'dimension element', true);

		foreach ($conns as $name => &$conn)
			$conn['perm'] = $perms[$name];

		return $conns;
	}

	public function getPaloConns ()
	{
		$all_conns = common::paloGet(null, 'Config', '#_connections', array('connections'), array('#_connections_' => array('name', 'type')));

		if (!is_array($all_conns) || empty($all_conns))
			return array();

		$conns = array();

		foreach ($all_conns as $conn)
			if ($conn['type'] == 'palo')
				$conns[] = $conn;

		return $conns;
	}

	public function isAdminConn ($name = null)
	{
		$err = array(1 => 'Studio-err_no_conn', 2 => 'no_connection_rights');

		if ($name == null)
		{
			$rules = $this->accessPolicy->getRules();

			return $rules['user'] < AccessPolicy::PERM_DELETE || $rules['password'] < AccessPolicy::PERM_DELETE || $rules['group'] < AccessPolicy::PERM_DELETE || $rules['rights'] < AccessPolicy::PERM_DELETE ? $err[2] : true;
		}

		try
		{
			$data = common::paloGet(null, 'Config', '#_connections', array('connections'), array('connections' => array($name), '#_connections_' => array('host', 'port', 'username', 'password', 'active', 'useLoginCred')));
			$data = $data[$name];

			if ($data['active'] != '1')
				return $err[1];

			if ($data['useLoginCred'] != '1')
				$apol = new AccessPolicy($data['host'], $data['port'], $data['username'], $data['password'], $data['username'], $data['password'], false);
			else
			{
				$user = $this->accessPolicy->getUser();
				$pass = $this->accessPolicy->getPass();

				$apol = new AccessPolicy($data['host'], $data['port'], $user, $pass, $user, $pass, false);
			}
		}
		catch (Exception $e)
		{
			return $err[1];
		}

		if (!is_resource($apol->getSuperConn()))
			return $err[1];

		if (!$apol->reload())
			return $err[2];

		$rules = $apol->getRules();

		return $rules['user'] < AccessPolicy::PERM_DELETE || $rules['password'] < AccessPolicy::PERM_DELETE || $rules['group'] < AccessPolicy::PERM_DELETE || $rules['rights'] < AccessPolicy::PERM_DELETE ? $err[2] : true;
	}


	/*
	 * \brief returns connection perms for a given user group
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function getConnPerms4UGroup ($user_group, $conn)
	{
		$apol = clone $this->accessPolicy;
		$apol->reload(array($user_group), array('dimension element'));

		$rule = $apol->getRule('dimension element');

		$perm = $apol->calcPerms('Config', 'connections', array($conn), true);
		$perm = $perm[$conn];

		return array('eff' => $perm & $rule, 'own' => $perm, 'def' => $rule, 'max' => $rule);
	}

	public function testConnection($connName, $host, $port, $user, $pass, $useLoginCred, $new){
		try {

			if($useLoginCred){
				$user = $this->accessPolicy->getUser();
				$pass = $this->accessPolicy->getPass();
			}
			else{
				if(!$new){
					$connData = common::paloGet(null, 'Config', '#_connections', array('connections'), array('connections' => array($connName), '#_connections_' => array('username', 'password')));
					$user = $user != $connData[$connName]['username']? $user:$connData[$connName]['username'];
					$pass = $pass != ""? $pass:$connData[$connName]['password'];
				}
			}

			$conn = palo_init($host, $port, $user, $pass);

			if ($conn === '#NULL!')
				throw new Exception();

			return true;
		}
		catch (Exception $e) {
			return false;
		}
	}



	//====================================================== Files ==================================================

	public function getDefaultLocalPath(){

			$db = 'Config';
			$cube = '#_config';
			$order = array('config');
			$coords = array('config'=>array('local'), '#_config_'=>array('value'));

			$local = common::paloGet(null, $db, $cube, $order, $coords);

			if(!isset($local['local']['value']))
				throw new WSS_Exception('Studio-err_read_def_loc_path', null, 'Unable to read data.');

			return $local['local']['value'];
	}

	// TODO: remove after full props migration
	public function getHierarchyPropertiesData($type, $h){
		try {
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;
			$guid = $group->getUID();
			$hierarchy = $group->getHierarchy($h);
			$hData = $hierarchy->getData();
			$name = $hData->getName();
			$description = $hData->getDescription();
			$studioType = $hData->getType();

			$relPath = "";
			$sysPath = "";
			$size = "";
			$props = null;

			if ($studioType == 'file'){
				$sysPath = $hData->getBackend()->getLocation();
				$props = $hierarchy->getProps();
			}

			$result = array("group"=>$guid, "hierarchy"=>$h, "node"=>$h, "sysPath"=>$sysPath, "relPath"=>$relPath, "name"=>$name, "description"=>$description, "type"=>ucwords($studioType) . " repository", "t"=>$type, 'props'=>$this->getFSProps($props));
			return $result;

		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}

	public function setHierarchyPropertiesData($type, $g, $h, $name, $desc, $path){
		try {
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;
			$hierarchy = $group->getHierarchy($h);

			if ($hierarchy->getData()->getName() != $name) {
				$group->renameHierarchy($hierarchy, $name);
				$hierarchy = $group->getHierarchy($h);
			}

			$hData = $hierarchy->getData();

			$old_name = $hData->getName();
			$hData->setName($name);
			$hData->setDescription($desc);
			$hData->setBackend(new W3S_Backend(array('type' => 'local', 'location' => $path)));
	//		$hData->getBackend()->setLocation($path);

			$result = $hierarchy->saveData();
			return $result;

		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}


	public function getGroupPropertiesData($type){
		try {
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;
			$guid = $group->getUID();
			$gData = $group->getData();
			$name = $gData->getName();
			$description = $gData->getDescription();
			$studioType = $gData->getType();
			$relPath = '';
			$sysPath = '';


			$result = array("group"=>$guid, "hierarchy"=>"", "node"=>"group", "sysPath"=>$sysPath, "relPath"=>$relPath, "name"=>$name, "description"=>$description, "type"=>ucwords($studioType) . " group", "t"=>$type);
			return $result;
		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}

	public function setGroupPropertiesData($type, $g, $name, $desc){

		try {
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;

			$gData = $group->getData();

			$gData->setName($name);
			if(isset($desc))
				$gData->setDescription($desc);

			$group->saveData();

			return true;
		}
		catch (Exception $e) {
			return false;
		}
	}

	public function removeFromSessionCurrGH($type){
		$this->currGroup[$type] = -1;
		$this->currHierarchy[$type] = null;
	}

	public function getElementPath ($guid, $huid, $nuid, $inc_huid = true)
	{
		try
		{
			$conn = $this->accessPolicy->getConn();

			if (!is_resource($conn))
				throw new WSS_Exception('Studio-err_no_parent', array('element_name' => $nuid), 'Unable to find parent for: ' . $nuid);

			if (!is_int(palo_eindex($conn, $guid, $huid, $nuid, true)))
				throw new WSS_Exception('Studio-err_no_parent', array('element_name' => $nuid), 'Node does not exist: ' . $nuid);

			$parent = $nuid;
			$path = array();

			while ($parent = palo_eparentname($conn, $guid, $huid, $parent, 1, true))
				array_unshift($path, ($inc_huid? $huid . '_':'') . $parent);

			return array(true, empty($path) ? $huid : $huid . '/' . join('/', $path));
		}
		catch (WSS_Exception $wsse)
		{
			return array(false, $wsse->getId(), $wsse->getParams());
		}
		catch (Exception $e)
		{
			return array(false, 'Studio-err_no_parent', array('element_name' => $nuid));
		}
	}


// ============================================= node properties data and access list ===================================

	public function getReferenceNode($g, $h, $n){
		$conn = $this->accessPolicy->getConn();
		$node = W3S_NodeData::getNodeData($conn, $g, $h, $n);
		$ref = $node->getReference();
		return array('g'=>$ref->getGroup(), 'h'=>$ref->getHierarchy(), 'n'=>$ref->getNode());
	}

	public function getHyperlinkURL($type, $g, $h, $n, $path = null){

		try {

			$conn = $this->accessPolicy->getConn();

			if($type == 'report' && substr($g, 0, 1) == 'r'){
				$r_node = W3S_NodeData::getNodeData($conn, $g, $h, $n);
				$ref = $r_node->getReference();
				$f_node = W3S_NodeData::getNodeData($conn, $ref->getGroup(), $ref->getHierarchy(), $ref->getNode());
			}
			else{
				$f_node = W3S_NodeData::getNodeData($conn, $g, $h, $n);
			}

			$url = $f_node->getHyperlink()->getLink();

			//add to recent
			$location = array('group'=>$g, 'hierarchy'=>$h, 'node'=>$n, 'path'=>$path);
			$this->addRecent($type, 'hyperlink', $location, 'hyperlink');

			return $url;

		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}

	public function setHyperlinkPropertiesData($type, $g, $h, $n, $data){

		try {
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;

			$h = $this->currHierarchy[$type];
			$hierarchy = $group->getHierarchy($h);
			$node = $hierarchy->getNode($n);
			$ndata = $node->getData();
			$ndata->setDescription($data['desc']);
			$ndata->getHyperlink()->setLink($data['url'], $data['target']);
			$node->saveData();

		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}

	public function setURLPluginPropertiesData($type, $g, $h, $n, $desc, $params){

		try {
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;

			$h = $this->currHierarchy[$type];
			$hierarchy = $group->getHierarchy($h);
			$node = $hierarchy->getNode($n);
			$ndata = $node->getData();
			$ndata->setDescription($desc);
			$ndata->setParams($params);
			$node->saveData();

		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}

	public function getURLPluginURL ($type, $g, $h, $n, $path = null)
	{
		try
		{
			$this->addRecent($type, 'hyperlink', array('group' => $g, 'hierarchy' => $h, 'node' => $n, 'path' => $path), 'ahview');

			$params = '&viewid=';

			if ($type == 'report')
			{
				$conn = $this->accessPolicy->getConn();
				$nodeData = W3S_NodeData::getNodeData($conn, $g, $h, $n);

				if (substr($g, 0, 1) != 'r')
					$params .= $viewid = $g . '-' . $h . '-' . $n;
				else
				{
					$ref = $nodeData->getReference();
					$ref_g = $ref->getGroup();
					$ref_h = $ref->getHierarchy();
					$ref_n = $ref->getNode();

					$nodeData = W3S_NodeData::getNodeData($conn, $ref_g, $ref_h, $ref_n);
					$params .= $viewid = $ref_g . '-' . $ref_h . '-' . $ref_n;
				}

				foreach ($nodeData->getParams() as $key => $val)
					$params .= '&'. $key . '=' . $val;
			}
			else
				$params .= $viewid = $g . '-' . $h . '-' . $n;


			$user = $this->accessPolicy->getUser();
			$pass = $this->accessPolicy->getPass();

			$td = mcrypt_module_open('rijndael-128', '', 'cfb', '');

			$block_size = mcrypt_enc_get_block_size($td);
			$pass_len = strlen($pass);
			$pass = str_pad($pass, $pass_len + $block_size - $pass_len % $block_size);

			mcrypt_generic_init($td, CFG_SECRET, md5($user . $viewid, true));
			$pass = urlencode(base64_encode(mcrypt_generic($td, $pass)));
			mcrypt_generic_deinit($td);

			mcrypt_module_close($td);


			$prefs = $_SESSION['prefs'];
			$params = 'user=' . urlencode($user) . '&pass=' . $pass . '&locale=' . $prefs->search('general/l10n') . '&theme=' . $prefs->search('general/theme') . $params;

			return array('type' => 'url', 'url' => CFG_AHVIEWER_PATH . '?' . $params . '&cksum=' . sha1($params . CFG_SECRET), 'target' => 'self');
		}
		catch (Exception $e)
		{
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}

	public function getNodeName($g, $h, $n){

		try {
			$conn = $this->accessPolicy->getConn();
			$nodeData = W3S_NodeData::getNodeData($conn, $g, $h, $n);
			$nodeName =  $nodeData->getName();

			return $nodeName;
			}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}


	public function getFramesetData($type, $g, $h, $n){

		try {

			$conn = $this->accessPolicy->getConn();
			$nodeData = W3S_NodeData::getNodeData($conn, $g, $h, $n);
			$frameset = $nodeData->getFrameset();
			$frames = $frameset->getFrames();
			$framesData = array();

			for ($i=0, $count=count($frames); $i<$count; $i++){
				$frame = $frames[$i]->getAssoc();
				$frame['file'] = $this->getNodeName($frame['group'], $frame['hierarchy'], $frame['node']);
				$frame['name'] = $frames[$i]->getName();
				array_push($framesData, $frame);
			}


			return array('rows'=>$frameset->getRows(), 'cols'=>$frameset->getCols(), 'frames'=>$framesData);

		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}

	}

	public function setFramesetPropertiesData($type, $g, $h, $n, $desc, $frameset=null){

		try {
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;

			$h = $this->currHierarchy[$type];
			$hierarchy = $group->getHierarchy($h);
			$node = $hierarchy->getNode($n);
			$ndata = $node->getData();

			$ndata->setDescription($desc);
			if(isset($frameset))
				$ndata->setFrameset(new W3S_Frameset($frameset));

			$node->saveData();

		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}


	public function setNodeVars($type, $n, $vars){

		$group = $this->currGroup[$type];
		$group->apol = $this->accessPolicy;

		$h = $this->currHierarchy[$type];
		$hierarchy = $group->getHierarchy($h);

		$node = $hierarchy->getNode($n);

		$node->getData()->setVars($vars);
		$node->saveData();

	}

	public function fetchTagged($context = null, $type = null, $tag = null){

		$conn = $this->accessPolicy->getConn();
		$all = common::fetchTagged($context, $type, $tag);
		$tagged = array();
		$untagged = array();

		for ($i=0, $count=count($all); $i<$count; $i++){
			try{
				$data = W3S_NodeData::getNodeData($conn, $all[$i]['location']['group'], $all[$i]['location']['hierarchy'], $all[$i]['location']['node']);

				if($data instanceof W3S_NodeData)
					array_push($tagged, $all[$i]);
				else
					array_push($untagged, $all[$i]);
			}
			catch (Exception $e) {
				array_push($untagged, $all[$i]);
			}
		}

		if(!empty($untagged))
			common::removeTagged($untagged);

		return $tagged;
	}

	// TODO: remove after full props migration
	public function getNodePropertiesData($type, $g, $h, $n){

		try {
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;

			$h = $this->currHierarchy[$type];
			$hierarchy = $group->getHierarchy($h);
			$node = $hierarchy->getNode($n);

			$name = $node->getData()->getName();
			$description = $node->getData()->getDescription();
			$studioType = $node->getType();

			$relPath = $node->getRelPath($node, false);
			$sysPath = '';
			$size = '0.00 B';
			$url = '';
			$urlPluginParams = '';
			$extension = '';
			$props = null;
			$subtype = '';
			$frameset = '';

			switch ($studioType) {
				case "template":
				case "rstatic":
					$ghn = $this->getTWorkbook($n);
					$group = new W3S_Group($this->accessPolicy, $ghn['grp']);

					if ($group->getType() == 'file' && $this->plugins['fs'] instanceof W3S_Plugin)
						$group->registerPlugin($this->plugins['fs'], true);

					$hierarchy = $group->getHierarchy($ghn['hr']);
					$node = $hierarchy->getNode($ghn['node']);

					if(isset($node)){
						$props = $node->getProps();
						$subtype = $node->getData()->getEffectiveType();
					}


					break;

				case "workbook":
					$extension = ".wss";
					$relPath = $relPath . $extension;

					$props = $node->getProps();
					break;

				case "folder":
					$sysPath = $node->getSysPath() . $extension;

					$props = $node->getProps();
					break;

				case "hyperlink":
					$url = $node->getData()->getHyperlink()->getLink();
					break;

				case 'urlplugin':
				case 'rurlplugin':
					$urlPluginParams = $node->getData()->getParams();
					break;
				case "rfolder":
					break;
				case "static":
					$props = $node->getProps();
					$subtype = $node->getData()->getEffectiveType();
					break;
				case "rhyperlink":
					break;
				case "frameset":
					$frameset = $this->getFramesetData($type, $g, $h, $n);
					break;
 			}

			$result = array("group"=>$g, "hierarchy"=>$h, "node"=>$n ,"sysPath"=>$sysPath, "relPath"=>$relPath, "type"=>ucwords($studioType), "name"=>$name, "description"=>$description, "url"=>$url, "urlPluginParams"=>$urlPluginParams, "t"=>$type, "props"=>$this->getFSProps($props), "subtype"=>$subtype, "frameset"=>$frameset);
			return $result;

		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}

	}

	// TODO: remove after full props migration
	public function getFSProps ($props)
	{
		if (!is_array($props) || empty($props))
			return null;

		$props['ctime'] = date('d.m.Y H:i:s', $props['ctime']);
		$props['mtime'] = date('d.m.Y H:i:s', $props['mtime']);
		$props['atime'] = date('d.m.Y H:i:s', $props['atime']);

		return $props;
	}

	public function getExternURI ($stndaln, $stq, array $params, array $creds = null)
	{

		$srv = &$_SERVER;
		$uri = 'http' . ($srv['HTTPS'] && $srv['HTTPS'] != 'off' ? 's' : '') . '://' . $srv['SERVER_NAME'] . (intval($srv['SERVER_PORT']) == 80 ? '' : ':' . $srv['SERVER_PORT'])
			. ($stq? ('/be/studio/static.php?' . $stq):('/ui/' . ($stndaln? 'wss':'studio') . '/?_=' . urlencode(base64_encode(gzcompress(json_encode($params))))));

		if (!is_array($creds))
			return $uri;

		if ($creds['flag'] == 1)
		{
			$creds['user'] = $this->accessPolicy->getUser();
			$creds['pass'] = $this->accessPolicy->getPass();
		}

		if (!isset($creds['user']) || !isset($creds['pass']))
			return $uri;

		$pass = $creds['pass'];

		$td = mcrypt_module_open('rijndael-128', '', 'cfb', '');

		$block_size = mcrypt_enc_get_block_size($td);
		$pass_len = strlen($pass);
		$pass = str_pad($pass, $pass_len + $block_size - $pass_len % $block_size);

		mcrypt_generic_init($td, CFG_SECRET, md5($creds['user'], true));
		$pass = mcrypt_generic($td, $pass);
		mcrypt_generic_deinit($td);

		mcrypt_module_close($td);

		return $uri . '&user=' . urlencode($creds['user']) . '&pass=' . urlencode(base64_encode($pass));
	}

	public function addRecent($context, $type, $location, $subtype){ //$context = files, $type = hyperlink, $location = array(group:group, hierarchy:hierarchy, node:node), $subtype = ahview

		if($context == 'file' || substr($location['group'], 0, 1) == 'f'){
			// Group
			if (get_class($this->currGroup[$context]) == 'W3S_Group' && $location["group"] == $this->currGroup[$context]->getUID()){
				$group = $this->currGroup[$context];
				$group->apol = $this->accessPolicy;
			}
			else {
				$group = new W3S_Group($this->accessPolicy, $location["group"]);
			}

			$hierarchy = $group->getHierarchy($location["hierarchy"]);
			$node = $hierarchy->getNode($location["node"]);

			$path = '//' . $group->getData()->getName() . '/' . $hierarchy->getData()->getName() . '/' . $node->getRelPath($node, false);
			$location["path"] = $path;
		}

		$recent = new Recent($this->accessPolicy);
		$recent->add($context . 's', $type, $location, $subtype);
		$recent->save();

	}


	/*
	 * ###########
	 * ### ACL ###
	 * ###########
	 */

	/*
	 * \brief returns max and effective perm (g, h or n level) for a given user group
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function getPerms4UGroup ($user_group, $type, $h = null, $n = null)
	{
		// create list of only needed rules
		$rules = array('database');

		if ($h)
		{
			$rules[] = 'dimension';

			if ($n)
				$rules[] = 'dimension element';
		}


		// clone access policy and reload it with given user group and list of rules
		$apol = clone $this->accessPolicy;
		$apol->reload(array($user_group), $rules);


		// find out perm_g/perm_h
		$group = $this->currGroup[$type];
		$g = $group->getUID();

		list ($perm, $perm_g, $perm_h) = W3S_Group::_calcPerms($apol, $g);

		$rule_g = $apol->getRule('database');

		// bail out if asking only for perm_g
		if (!$h)
			return array('eff' => $perm_g, 'own' => $perm, 'def' => $rule_g, 'max' => $rule_g);


		// find out perm_h/perm_n
		$perm = $apol->calcPerms($g, 'meta', array($h));
		$perm = $perm[$h];

		$def = $perm_h;

		$rule_h = $apol->getRule('dimension');
		$rule_n = $apol->getRule('dimension element');

		if ($perm != -1)
		{
			$perm_h = $perm & $rule_h;
			$perm_n = $perm & $rule_n;
		}
		else
			$perm_n = $perm_h & $rule_n;

		// bail out if asking only for perm_h
		if (!$n)
			return array('eff' => $perm_h, 'own' => $perm, 'def' => $def, 'max' => $rule_h);


		// asking for perm_n, will need to construct consolidation path of given node
		$hierarchy = $group->getHierarchy($h);
		$node = $hierarchy->getNode($n);

		$path = array($n);
		$node->getSuperUIDs($path);

		// find out perm_n's for all nodes in path
		$perms = $apol->calcPerms($g, $h, $path, true);

		// remove the node from path
		array_shift($path);

		$def = $perm_n;

		foreach ($path as $uid)
			if (($perm = $perms[$uid]) != -1)
			{
				$def = $perm & $rule_n;
				break;
			}

		$perm_n = ($perm = $perms[$n]) != -1 ? $perm & $rule_n : $def;

		return array('eff' => $perm_n, 'own' => $perm, 'def' => $def, 'max' => $rule_n);
	}


	public function getNodePermission($g, $h, $n){
		try {
			$perm = -1;
			if (($group = new W3S_Group($this->accessPolicy, $g)) instanceof W3S_Group){
				if (($hierarchy = $group->getHierarchy($h)) instanceof W3S_Hierarchy){
					if (($node = $hierarchy->getNode($n)) instanceof W3S_Node){
						$perm = $node->getPermN();
					}
				}
			}

			return $perm;
		}
		catch (Exception $e) {
			return array(false, $e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}


	public function setNodePemission($group, $hierarchy, $node, $accessGroup, $permission, $type){

		    $db = $group;
			$cube = '#_GROUP_DIMENSION_DATA_' . $hierarchy;
			$order = array($hierarchy);
			$data = array($node=>array($accessGroup=>$permission));

			$result = common::paloSet(null, $db, $cube, $data, $order, false);

			if($result != true)
				throw new WSS_Exception('Studio-err_set_node_perm', null, 'Unable to write data.');

			return array(true, $this->refreshNodes($group, $hierarchy, $node, $accessGroup, $type));
	}


	public function refreshNodes($g, $h, $n, $accessGroup, $type){

		try {

			$refresh = false;

			if (in_array($accessGroup, $this->accessPolicy->getGroups())){

				$refresh = true;
				$group = $this->currGroup[$type];
				$group->apol = $this->accessPolicy;

				if ($h == 'meta'){
					if ($n == 'group'){
						$group->calcPerms();
					}
					else {
						$h = $this->currHierarchy[$type];
						$hierarchy = $group->getHierarchy($h);
						$hierarchy->calcPerms();
					}
				}
				else {
					$h = $this->currHierarchy[$type];
					$hierarchy = $group->getHierarchy($h);
//					$hierarchy->calcPerms();
					$node = $hierarchy->getNode($n);
					$node->calcPerms();
				}
			}

			return $refresh;

		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}
	}

	// WSS onInsertHyperlink
	public function getNodeHyperlinkPropertiesData($g, $h, $n){

		try {
			$type = 'wss';
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;

			$h = $this->currHierarchy[$type];
			$hierarchy = $group->getHierarchy($h);

			$node = $hierarchy->getNode($n);

			$path =  '/' . $group->getData()->getName() . '/' . $hierarchy->getData()->getName() . $node->getRelPath($node, false, true);

			$result = array("g"=>$g, "h"=>$h, "n"=>$n ,"p"=>$path, "t"=>$relPath, "t"=>$node->getData()->getEffectiveType());

			return $result;
		}
		catch (Exception $e) {
			return array($e->getMessage(), self::$errMsg[$e->getCode()]);
		}

	}


	/*
	 * ####################################################
	 * ### GROUP, HIERARCHY & TREE MANIPULATION METHODS ###
	 * ####################################################
	 */

	/*
	 * \brief sets the currently selected group for a given type (file, report, ...)
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function treeSetGroup ($type, $uid)
	{
		if (!isset($this->currGroup[$type]))
			return false;

		$group = new W3S_Group($this->accessPolicy, $uid);

		$this->currGroup[$type] = $group;

		if ($group->getType() == 'file' && $this->plugins['fs'] instanceof W3S_Plugin)
			$group->registerPlugin($this->plugins['fs'], true);

		$this->currHierarchy[$type] = ($hierarchy = $group->getFirstHierarchy()) instanceof W3S_Hierarchy ? $hierarchy->getUID() : '';

		return true;
	}

	/*
	 * \brief gets the currently selected group for a given type (file, report, ...)
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function treeGetGroup ($type)
	{
		if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group))
			return false;

		return $group->getUID();
	}

	/*
	 * \brief sets the currently selected hierarchy for a given type (file, report, ...)
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function treeSetHierarchy ($type, $uid)
	{
		if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group))
			return false;

		$group->apol = $this->accessPolicy;

		if (!(($hierarchy = $group->getHierarchy($uid)) instanceof W3S_Hierarchy))
			return false;

		$this->currHierarchy[$type] = $uid;

		return true;
	}

	/*
	 * \brief gets the currently selected hierarchy for a given type (file, report, ...)
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function treeGetHierarchy ($type)
	{
		if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group) || !(($hierarchy = $group->getHierarchy($uid = $this->currHierarchy[$type])) instanceof W3S_Hierarchy))
			return '';

		return $uid;
	}

	/*
	 * \brief proxies calls to W3S_Group static methods
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function treeMngGroup ($type, $method)
	{
		if (!is_callable($callback = 'W3S_Group::' . $method))
			return false;

		$args = func_get_args();
		array_shift($args);

		$args[0] = $this->accessPolicy;

		$refl_method = new ReflectionMethod('W3S_Group', $method);

		foreach ($refl_method->getParameters() as $i => $param)
			if (($refl_class = $param->getClass()) instanceof ReflectionClass && $refl_class->getName() == 'W3S_Group')
			{
				if (!(($group = $this->currGroup[$type]) instanceof W3S_Group) || $args[$i] != $group->getUID())
					return false;

				$group->apol = $this->accessPolicy;
				$args[$i] = $group;
			}

		$res = call_user_func_array($callback, $args);

		return ($res instanceof W3S_Group) ? $res->getUID() : $res;
	}

	/*
	 * \brief proxies calls to currently selected group (of a given type)
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function treeMngHierarchy ($type)
	{
		if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group))
			return false;

		$group->apol = $this->accessPolicy;

		$args = func_get_args();

		return call_user_func_array(array($group, 'hierarchy'), array_slice($args, 1));
	}

	/*
	 * \brief proxies calls to currently selected hierarchy (of a given type)
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function treeMngNode ($type)
	{
		if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group) || !(($hierarchy = $group->getHierarchy($this->currHierarchy[$type])) instanceof W3S_Hierarchy))
			return false;

		$group->apol = $this->accessPolicy;

		$args = func_get_args();
		array_splice($args, 0, 1);

		if (count($args) > 1)
			return call_user_func_array(array($hierarchy, 'node'), $args);

		if (!is_array($args[0]))
			return false;

		$res = array();

		foreach ($args[0] as &$c_args)
		{
			try
			{
				$res[] = $res_tmp = call_user_func_array(array($hierarchy, 'node'), $c_args);
			}
			catch (Exception $e)
			{
				$res[] = false;
				break;
			}

			if ($res_tmp === false)
				break;
		}

		return $res;
	}

	public function treeNodeDelMap ($node, $tvar) {

		 $type = 'report';

	    if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group) || !(($hierarchy = $group->getHierarchy($this->currHierarchy[$type])) instanceof W3S_Hierarchy)
	        || !(($node = $hierarchy->getNode($node)) instanceof W3S_Node))
	      return false;

	    $group->apol = $this->accessPolicy;
	    $node->getData()->deleteMap($tvar);

	    $node->saveData();

	    return true;

	}

	public function treeNodeMap ($m_type, $node, array $map, $defVal, $tplVar, $force = false)
	  {
	    $type = 'report';

	    if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group) || !(($hierarchy = $group->getHierarchy($this->currHierarchy[$type])) instanceof W3S_Hierarchy)
	        || !(($node = $hierarchy->getNode($node)) instanceof W3S_Node))
	      return false;

	    $group->apol = $this->accessPolicy;

	    //	choose Palo List / Const List / Const

	    if ($m_type==0) {
	      $node->getData()->setMap(new W3S_PaloList($map[0]['conn'], $map[0]['db'], $map[0]['dim'], $map[0]['subs']), $defVal, $tplVar, null, $force);
	    } else if ($m_type==1) {
	      $node->getData()->setMap(new W3S_ConstList($map), $defVal, $tplVar, null, $force);
	    } else if ($m_type==2) {
	      $node->getData()->setMap(new W3S_ConstValue($map[0]), $defVal, $tplVar, null, $force);
	    } else if ($m_type==3) {
	      $node->getData()->setMap(new W3S_LinkList($map[0]), $defVal, $tplVar, null, $force);
	    } else if ($m_type==4) {
	      $node->getData()->setMap(new W3S_PaloSubsetList(json_encode($map)), $defVal, $tplVar, null, $force);
	      // here link! --> see how to implement
	    } else if ($m_type == 'none')
	    	$node->getData()->deleteMap($tplVar);

	    $node->saveData();

	    return true;
	  }

	  //for report node when importing from bundle
	  public function setNodeMap($n, $maps){

		$type = 'report';
		if (!$tvar) $tvar = null;

		if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group) || !(($hierarchy = $group->getHierarchy($this->currHierarchy[$type])) instanceof W3S_Hierarchy) || !(($node = $hierarchy->getNode($n)) instanceof W3S_Node))
			return false;

		$group->apol = $this->accessPolicy;

		foreach ($maps as $key => $map){
			$tvar = ($key == 'rfolder'? null:$key);
			$node->getData()->setMap($map['list'], $map['defval'], $tvar, $map['ordnum']);
		}

		$node->saveData();

	  }


	/*
	 * \brief dumps the structure of a given hierarchy (used directly by Ext's TreeLoader)
	 *
	 * \author
	 * Predrag Malicevic <predrag.malicevic@develabs.com>
	 *
	 */

	public function treeDump ()
	{
		if (!isset($_POST['type']))
			return array();

		$type = $_POST['type'];

		if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group))
			return array();

		if (isset($_POST['hierarchy']))
		{
			if (!$this->treeSetHierarchy($type, $_POST['hierarchy']))
				return array();

			$hierarchy = $group->getHierarchy($this->currHierarchy[$type]);
		}
		else if (!(($hierarchy = $group->getHierarchy($this->currHierarchy[$type])) instanceof W3S_Hierarchy))
			return array();

		if (isset($_POST['reload']))
			$hierarchy->reloadNodes();

		if (!isset($_POST['node']) || !(($node = $hierarchy->getNode($_POST['node'])) instanceof W3S_Node))
			$node = $hierarchy->getRoot();

		$level = isset($_POST['level']) ? intval($_POST['level']) : -1;
		$filter = isset($_POST['filter']) ? split(',', $_POST['filter']) : null;
		$multi_h = isset($_POST['multi_h']) ? ($_POST['multi_h'] == 'true') : false;

		return $node->dump($level, $filter, $multi_h);
	}

	private function getLinks($link_type, $nodes) {
		// Refresh group stored in session
		$type = 'file';
		$g = $this->currGroup[$type]->getUID();
		$h = $this->currHierarchy[$type];
		$this->treeSetGroup($type, $g);
		$this->treeSetHierarchy($type, $h);

		$group = $this->currGroup[$type];
		$group->apol = $this->accessPolicy;
		$h = $this->currHierarchy[$type];
		$hierarchy = $group->getHierarchy($h);

	    $nodes_cnt = count($nodes);
	    $all_links = array();

	    foreach ($nodes as $n) {
		    $node = $hierarchy->getNode($n);

		    if (!($node instanceof W3S_Node))
		    	continue;

		    $links = array();
		    $node->getLinks($link_type, $links, $nodes_cnt > 1 ? $node : null);

		    if (!count($links))
		    	continue;

			foreach ($links as $link)
				foreach ($link['links'] as $node_link)
					$link_struct[$node_link['group']][$node_link['hierarchy']][$node_link['node']] = 'unknown';

			$all_links = array_merge($all_links, $links);
	    }

	    if (!count($all_links))
		    return $all_links;

		foreach ($link_struct as $grp => $hrcs) {
			if (!(($group = new W3S_Group($this->accessPolicy, $grp)) instanceof W3S_Group))
				continue;

			foreach ($hrcs as $hrc => $nds) {
				if (!(($hierarchy = $group->getHierarchy($hrc)) instanceof W3S_Hierarchy))
					continue;

				foreach ($nds as $nd => $path) {
					if (!(($node = $hierarchy->getNode($nd)) instanceof W3S_Node))
						continue;

					$link_struct[$grp][$hrc][$nd] = '//' . $group->getData()->getName() . '/' . $hierarchy->getData()->getName() . $node->getRelPath($node, false);

					unset($node);
				}

				unset($hierarchy);
			}

			unset($group);
		}

		$is_resource = $link_type == W3S_NodeData::$resource;

		if (count($all_links) == 1 && !strlen($all_links[0]['path'])) {
			foreach ($all_links[0]['links'] as $node_link) {
				$larr = array($link_struct[$node_link['group']][$node_link['hierarchy']][$node_link['node']]);

				if ($is_resource) {
					$larr[] = $node_link['group']; $larr[] = $node_link['hierarchy']; $larr[] = $node_link['node'];
				}

				$res_arr[] = $larr;
			}
		} else {
			foreach ($all_links as $link)
				foreach ($link['links'] as $node_link) {
					$larr = array($link['path'], $link_struct[$node_link['group']][$node_link['hierarchy']][$node_link['node']]);

					if ($is_resource) {
						$larr[] = $node_link['group']; $larr[] = $node_link['hierarchy']; $larr[] = $node_link['node'];
					}

					$res_arr[] = $larr;
				}
		}

	    return $res_arr;
	}

	public function getReferrers($nodes) {
		return $this->getLinks(W3S_NodeData::$referrer, $nodes);
	}

	public function getResources($nodes) {
		return $this->getLinks(W3S_NodeData::$resource, $nodes);
	}

	public function getDependents($nodes) {
		return $this->getLinks(W3S_NodeData::$dependent, $nodes);
	}

	public function setResources($n, $old_r, $new_r){
		$type = 'file';
		$g = $this->currGroup[$type]->getUID();
		$group = $this->currGroup[$type];
		$group->apol = $this->accessPolicy;

		$h = $this->currHierarchy[$type];
		$hierarchy = $group->getHierarchy($h);
		$node = $hierarchy->getNode($n);

		$d_res = array_diff_key($old_r, $new_r);
		$a_res = array_diff_key($new_r, $old_r);


		//remove resource - dependent link
		foreach ($d_res as $k => $v){
			$result = $this->removeDependent($group, $hierarchy, $v, array($g, $h, $n));
			if ($result)
				$node->removeResource($v[0], $v[1], $v[2]);
		}

		//add new resource - dependent link
		foreach ($a_res as $k => $v){
			$result = $this->addDependent($group, $hierarchy, $v, array($g, $h, $n));
			if ($result)
				$node->addResource($v[0], $v[1], $v[2]);
		}

		$node->saveData();

	}

	function removeDependent($group, $hierarchy, $d, $r){

		if($group->getUID() != $d[0] || $hierarchy->getUID() != $d[1]){

			if (!(($group = new W3S_Group($this->accessPolicy, $d[0])) instanceof W3S_Group))
				return false;

			if (!(($hierarchy = $group->getHierarchy($d[1])) instanceof W3S_Hierarchy))
				return false;

		}

		if (!(($node = $hierarchy->getNode($d[2])) instanceof W3S_Node)){
			return false;
		}

		$node->removeDependent($r[0], $r[1], $r[2]);
		$node->saveData();

		return true;

	}


	function addDependent($group, $hierarchy, $d, $r){

		if($group->getUID() != $d[0] || $hierarchy->getUID() != $d[1]){

			if (!(($group = new W3S_Group($this->accessPolicy, $d[0])) instanceof W3S_Group))
				return false;

			if (!(($hierarchy = $group->getHierarchy($d[1])) instanceof W3S_Hierarchy))
				return false;

		}

		if (!(($node = $hierarchy->getNode($d[2])) instanceof W3S_Node))
			return false;

		$node->addDependent($r[0], $r[1], $r[2]);
		$node->saveData();

		return true;

	}

	//updates referrers, resources, dependents node data after import bundle and node replace operation to remain old nodes connections
	function updateData($type, $n, $rnreferrers = null, $rnresources = null, $rndependents = null){

		if(empty($rnreferrers) && empty($rnresources) && empty($rndependents))
			return;

		$g = $this->currGroup[$type]->getUID();
		$group = $this->currGroup[$type];
		$group->apol = $this->accessPolicy;

		$h = $this->currHierarchy[$type];
		$hierarchy = $group->getHierarchy($h);
		$node = $hierarchy->getNode($n);

		if($node instanceof W3S_Node){
			$ndata = $node->getData();

			$fnc = array();
			if(!empty($rnreferrers))$fnc['Referrer']= $rnreferrers;
			if(!empty($rnresources))$fnc['Resource']=  $rnresources;
			if(!empty($rndependents))$fnc['Dependent']= $rndependents;

			foreach($fnc as $f => $rnvalues){
				$g = 'get' . $f . 's';
				$s = 'add' .$f;
				$values = $ndata->$g(); // indirectly call correct function
				foreach($rnvalues as $rnv){
					$addF = true;
					foreach($values as $v){
						if($rnv['group'] == $v['group'] && $rnv['hierarchy'] == $v['hierarchy'] && $rnv['node'] == $v['node']){
							$addF = false;
							break;
						}
					}
					if($addF){
						$ndata->$s($rnv['group'], $rnv['hierarchy'], $rnv['node']); // indirectly call correct function
					}
				}
			}

			$node->saveData();

		}

	}


	//===================================================================================================================================================
	// get Database/Dimension/Subsets Nodes
	public function getDDSTreeNodes()
	{
		$elemID = isset($_POST['node']) ? stripslashes($_POST['node']) : null;
		$paloPath = isset($_POST['_palo_path']) ? json_decode(stripslashes($_POST['_palo_path']), true) : null;
		$connName = isset($_GET['connName']) ? $_GET['connName'] : null;
		$connName = isset($_POST['_conn_name']) ? $_POST['_conn_name'] : $connName;

		$nodes = array();
		if (($elemID != null) && ($connName != null))
		{
			try
			{
				if (strtoupper($elemID) == strtoupper('root'))
				{
					$rootData = palo::getDBs($connName);
					for ($i=1; $i<count($rootData); $i++)
						$nodes[] = array('text' => $rootData[$i], 'iconCls' => 'w3s_database', 'leaf' => false, '_palo_path' => array('db' => $rootData[$i]));
				}
				else if (count($paloPath) == 1)
				{
					$dbData = palo::getDims($connName, $paloPath['db'], 0);
					for ($i=0; $i<count($dbData); $i++)
						$nodes[] = array('text' => $dbData[$i], 'iconCls' => 'w3s_dimension', 'leaf' => false, '_palo_path' => array('db' => $paloPath['db'], 'dim' => $dbData[$i]));
				}
				else if (count($paloPath) == 2)
				{
					$dimData = palo_sbst::getSubsetNames($connName, $paloPath['db'], $paloPath['dim']);
					for ($i=0; $i<count($dimData[1]); $i++)
						$nodes[] = array('text' => $dimData[1][$i], 'iconCls' => 'w3s_subset', 'leaf' => true, '_palo_path' => array('db' => $paloPath['db'], 'dim' => $paloPath['dim'], 'ss' => $dimData[1][$i]));
				}
			}
			catch (WSS_Exception $wsse)
			{
				$nodes[] = array('text' => '', 'iconCls' => 'w3s_error', 'leaf' => true, '_error' => array('id' => $wsse->getId(), 'params' => $wsse->getParams()));
			}
			catch (Exception $e)
			{
				$nodes = array();
			}
		}

		return $nodes;
	}

	public function getListByPaloPath($connName, $paloPath)
	{
		try
		{
			if (count($paloPath) == 2)
			{
				$res = palo_mdlr::getDimElems($connName, $paloPath['db'], $paloPath['dim']);
				$retElems = array();
					foreach ($res[1] as $elem)
						$retElems[] = $elem['name'];
				return array(true, $retElems);
			}
			else if (count($paloPath) == 3)
			{
				$res = palo_sbst::getSubsetList(array(
					'serv_id' => $connName,
					'db_name' => $paloPath['db'],
					'dim_name' => $paloPath['dim'],
					'subset_name' => $paloPath['ss'],
					'subset_type' => 0,
					'layouthier' => false
				));
				return array(true, $res[1]);
			}
		}
		catch (Exception $e) {}

		return array(false);
	}

	private static function _getTreeIconCls($type)
	{
		if (strpos($type, 'rfolder') === 0)
			return 'w3s_rfolder_s';
		else if (strpos($type, 'template') === 0)
			return 'w3s_template_s';

		return 'w3s_' . $type;
	}

	public function getMappedTreeNodes()
	{
		try
		{
			$elemID = isset($_POST['node']) ? stripslashes($_POST['node']) : null;
			$connName = isset($_POST['cn']) ? stripslashes($_POST['cn']) : null;
			$dbName = isset($_POST['g']) ? stripslashes($_POST['g']) : null;
			$dimName = isset($_POST['h']) ? stripslashes($_POST['h']) : null;
			$nodeInfo = isset($_POST['_ni']) ? json_decode(stripslashes($_POST['_ni']), true) : null;

			if ($connName !== null)
				$conn = palo::palo_init($connName);
			else
				$conn = $this->accessPolicy->getConn();

			$retList = array();
			if (strtoupper($elemID) == strtoupper('root'))
			{
				// ROOT
				$listElems = palo_dimension_list_elements2($conn, $dbName, $dimName, true);
				$cubeName = '#_' . $dimName;

				foreach($listElems as $elem)
					if ($elem['num_parents'] == 0)
					{
						$nodeData = W3S_NodeData::getNodeData($conn, $dbName, $dimName, $elem['name']);
						$isDynamic = false;
						if (!in_array($nodeData->getType(), array('rstatic', 'rhyperlink', 'rurlplugin')))
						{
							$tmpMap = w3s::getMap($conn, $nodeData, w3s::EXC_PRIVATE_VARS);
							$isDynamic = (!empty($tmpMap) && in_array($nodeData->getType(), array('template', 'rframeset')));
							if ($isDynamic)
							{
								$allLinks = true;
								foreach($tmpMap as $map)
									if ($map['list']->getType() != 'link')
									{
										$allLinks = false;
										break;
									}

								if ($allLinks)
									$isDynamic = false;
							}
						}

						$nodeArr = array(
							'text' => $nodeData->getName(),
							//'qtip' => $nodeData->getDescription(), --- until complete implementation of quick tips, only name of item will be used
							'qtip' => $nodeData->getName(),
							'iconCls' => self::_getTreeIconCls($nodeData->getEffectiveType()),
							'leaf' => (($isDynamic || (!in_array($nodeData->getType(), array('rstatic', 'rhyperlink', 'rurlplugin', 'template', 'rframeset')))) ? false : true),
							'_ni' => array('n' => $elem['name'])
						);

						if (in_array($nodeData->getType(), array('rstatic', 'rhyperlink', 'rurlplugin', 'template', 'rframeset')))
						{
							$nodeLink = $nodeData->getReference();
							$nodeArr['_wb'] = array('g' => $nodeLink->getGroup(), 'h' => $nodeLink->getHierarchy(), 'n' => $nodeLink->getNode());
						}

						$retList[] = $nodeArr;
					}
			}
			else if (isset($nodeInfo['n']) && isset($nodeInfo['elem_n']))
			{
				// dim nodes
				$listElems =  palo_element_list_consolidation_elements($conn, $dbName, $dimName, $nodeInfo['n']);
				$cubeName = '#_' . $dimName;

				foreach ($listElems as $elem)
				{
					$nodeData = W3S_NodeData::getNodeData($conn, $dbName, $dimName, $elem['name']);
					$isDynamic = false;
					if (!in_array($nodeData->getType(), array('rstatic', 'rhyperlink', 'rurlplugin')))
					{
						$tmpMap = w3s::getMap($conn, $nodeData, w3s::EXC_PRIVATE_VARS);
						$isDynamic = (!empty($tmpMap) && in_array($nodeData->getType(), array('template', 'rframeset')));
						if ($isDynamic)
						{
							$allLinks = true;
							foreach($tmpMap as $map)
								if ($map['list']->getType() != 'link')
								{
									$allLinks = false;
									break;
								}

							if ($allLinks)
								$isDynamic = false;
						}
					}

					$nodeArr = array(
						'text' => $nodeData->getName(),
						//'qtip' => $nodeData->getDescription(), --- until complete implementation of quick tips, only name of item will be used
						'qtip' => $nodeData->getName(),
						'iconCls' => self::_getTreeIconCls($nodeData->getEffectiveType()),
						'leaf' => (($isDynamic || (!in_array($nodeData->getType(), array('rstatic', 'rhyperlink', 'rurlplugin', 'template', 'rframeset')))) ? false : true),
						'_ni' => array('n' => $elem['name'])
					);

					if (in_array($nodeData->getType(),array('rstatic', 'rhyperlink', 'rurlplugin', 'template', 'rframeset')))
					{
						$nodeLink = $nodeData->getReference();
						$nodeArr['_wb'] = array('g' => $nodeLink->getGroup(), 'h' => $nodeLink->getHierarchy(), 'n' => $nodeLink->getNode());
					}

					$retList[] = $nodeArr;
				}

				// getting map
				$nodeData = W3S_NodeData::getNodeData($conn, $dbName, $dimName, $nodeInfo['n']);
				$mappedData = w3s::getMap($conn, $nodeData, w3s::EXC_PRIVATE_VARS);

				// generate nodes for map
				$isWbContainer = in_array($nodeData->getType(), array('template', 'rframeset'));
				if (!empty($mappedData))
				{
					$map = $mappedData;
					$addVar = false;
					if ($isWbContainer)
					{
						$addVar = true;
						$map = $map[$nodeInfo['v_n']];
						$varName = $nodeInfo['v_n'];

						$mappedData = $this->_getOrderedVariables($mappedData);
						$varNames = array_keys($mappedData);
						$keyIndex = array_search($nodeInfo['v_n'], $varNames);

						if ($keyIndex == (count($varNames) - 1))
						{
							$nodeData = W3S_NodeData::getNodeData($conn, $dbName, $dimName, $nodeInfo['n']);
							$nodeLink = $nodeData->getReference();
							$retList[] = array(
								'text' => $nodeData->getName(),
								//'qtip' => $nodeData->getDescription(), --- until complete implementation of quick tips, only name of item will be used
								'qtip' => $nodeData->getName(),
								'iconCls' => self::_getTreeIconCls($nodeData->getEffectiveType()),
								'leaf' => true,
								'_ni' => array('n' => $nodeInfo['n']),
								'_wb' => array('g' => $nodeLink->getGroup(), 'h' => $nodeLink->getHierarchy(), 'n' => $nodeLink->getNode())
							);
						}
					}

					$map = $map['list'];
					if ($map->getType() == 'palo')
					{
						$dimMapList = $map->getList();
						if ($dimMapList['type'] == 'dimension')
						{
							if ($map->getConnection() === $connName)
								$dim_conn = $conn;
							else
								$dim_conn = palo::palo_init($map->getConnection());
							$dim_dbName = $map->getDb();

							$listElems = palo_element_list_consolidation_elements($dim_conn, $dim_dbName, $dimMapList['dimension'], $nodeInfo['elem_n']);
							if (count($listElems) > 0)
							{
//								$addVar = false;

								foreach($listElems as $elem)
								{
									$ni = array('n' => $nodeInfo['n'], 'elem_n' => $elem['name']);
									if ($isWbContainer)
										$ni['v_n'] = $varName;

									$retList[] = array(
										'text' => $elem['name'],
										'iconCls' => 'w3s_rfolder_s',
										'leaf' => false,
										'_ni' => $ni
									);
								}
							}
						}
					}

					if ($addVar)
					{
						$mappedData = $this->_getOrderedVariables($mappedData);
						$varNames = array_keys($mappedData);
						$keyIndex = array_search($nodeInfo['v_n'], $varNames);

						while ($keyIndex < (count($varNames) - 1))
						{
							$varName = $varNames[++$keyIndex];
							$map = $mappedData[$varName]['list'];

							if ($map->getType() != 'link')
							{
								// next templated mapped variable
								$retList[] = array(
									'text' => $varName,
									'iconCls' => 'w3s_var_folder',
									'leaf' => false,
									'_ni' => array('n' => $nodeInfo['n'], 'v_n' => $varName)
								);
								break;
							}
							else if ($keyIndex == (count($varNames) - 1))
							{
								$nodeData = W3S_NodeData::getNodeData($conn, $dbName, $dimName, $nodeInfo['n']);
								$nodeLink = $nodeData->getReference();
								$retList[] = array(
									'text' => $nodeData->getName(),
									//'qtip' => $nodeData->getDescription(), --- until complete implementation of quick tips, only name of item will be used
									'qtip' => $nodeData->getName(),
									'iconCls' => self::_getTreeIconCls($nodeData->getEffectiveType()),
									'leaf' => true,
									'_ni' => array('n' => $nodeInfo['n']),
									'_wb' => array('g' => $nodeLink->getGroup(), 'h' => $nodeLink->getHierarchy(), 'n' => $nodeLink->getNode())
								);
								break;
							}
						}
					}
				}
			}
			else if (isset($nodeInfo['n']))
			{
				// hier nodes
				$listElems =  palo_element_list_consolidation_elements($conn, $dbName, $dimName, $nodeInfo['n']);
				$cubeName = '#_' . $dimName;

				// getting map
				$nodeData = W3S_NodeData::getNodeData($conn, $dbName, $dimName, $nodeInfo['n']);
				$map = w3s::getMap($conn, $nodeData, w3s::EXC_PRIVATE_VARS);

				// generate nodes for map
				$isWbContainer = in_array($nodeData->getType(), array('template', 'rframeset'));
				if ($isWbContainer && !empty($map) && !isset($nodeInfo['v_n']))
				{
					$mappedData = $map;
					$mappedData = $this->_getOrderedVariables($mappedData);
					$varNames = array_keys($mappedData);
					$keyIndex = -1;

					while ($keyIndex < (count($varNames) - 1))
					{
						$varName = $varNames[++$keyIndex];
						$map = $mappedData[$varName]['list'];

						if ($map->getType() != 'link')
						{
							// next templated mapped variable
							$retList[] = array(
								'text' => $varName,
								'iconCls' => 'w3s_var_folder',
								'leaf' => false,
								'_ni' => array('n' => $nodeInfo['n'], 'v_n' => $varName)
							);
							break;
						}
						else if ($keyIndex == (count($varNames) - 1))
						{
							$nodeData = W3S_NodeData::getNodeData($conn, $dbName, $dimName, $nodeInfo['n']);
							$nodeLink = $nodeData->getReference();
							$retList[] = array(
								'text' => $nodeData->getName(),
								//'qtip' => $nodeData->getDescription(), --- until complete implementation of quick tips, only name of item will be used
								'qtip' => $nodeData->getName(),
								'iconCls' => self::_getTreeIconCls($nodeData->getEffectiveType()),
								'leaf' => true,
								'_ni' => array('n' => $elem['name']),
								'_wb' => array('g' => $nodeLink->getGroup(), 'h' => $nodeLink->getHierarchy(), 'n' => $nodeLink->getNode())
							);
							break;
						}
					}
				}
				else if (!empty($map))
				{
					if ($isWbContainer)
					{
						$map = $map[$nodeInfo['v_n']];
						$varName = $nodeInfo['v_n'];
					}

					$map = $map['list'];
					$listType = strtolower($map->getType());

					if ($listType == 'palo')
					{
						$dimMapList = $map->getList();
						if ($dimMapList['type'] == 'dimension')
						{
							if ($map->getConnection() === $connName)
								$dim_conn = $conn;
							else
								$dim_conn = palo::palo_init($map->getConnection());
							$dim_dbName = $map->getDb();

							$listElems = palo_dimension_list_elements2($dim_conn, $dim_dbName, $dimMapList['dimension'], true);

							foreach($listElems as $elem)
							{
								// if element has no parents then it's root element
								if($elem['num_parents'] > 0)
									continue;
								else
								{
									$ni = array('n' => $nodeInfo['n'], 'elem_n' => $elem['name']);
									if ($isWbContainer)
										$ni['v_n'] = $varName;

									$retList[] = array(
										'text' => $elem['name'],
										'iconCls' => 'w3s_rfolder_s',
										'leaf' => false,
										'_ni' => $ni
									);
								}
							}
						}
						else if ($dimMapList['type'] == 'subset')
						{
							$ssList = palo_sbst::getSubsetList(array(
								'serv_id' => $map->getConnection(),
								'db_name' => $map->getDb(),
								'dim_name' => $dimMapList['dimension'],
								'subset_name' => $dimMapList['subset'],
								'subset_type' => 0,
								'layouthier' => false
							));
							$ssList = $ssList[1];

							foreach($ssList as $ssName)
							{
								$ni = array('n' => $nodeInfo['n'], 'elem_n' => $ssName);
								if ($isWbContainer)
									$ni['v_n'] = $varName;

								$retList[] = array(
									'text' => $ssName,
									'iconCls' => 'w3s_rfolder_s',
									'leaf' => false,
									'_ni' => $ni
								);
							}
						}
					}
					else if ($listType == 'clist')
					{
						$constList = $map->getValues();

						foreach($constList as $constName)
						{
							$ni = array('n' => $nodeInfo['n'], 'elem_n' => $constName);
							if ($isWbContainer)
								$ni['v_n'] = $varName;

							$retList[] = array(
								'text' => $constName,
								'iconCls' => 'w3s_rfolder_s',
								'leaf' => false,
								'_ni' => $ni
							);
						}
					}
					else if ($listType == 'cval')
					{
						$constVal = $map->getValue();

						$ni = array('n' => $nodeInfo['n'], 'elem_n' => $constVal);
						if ($isWbContainer)
							$ni['v_n'] = $varName;

						$retList[] = array(
							'text' => $constVal,
							'iconCls' => 'w3s_rfolder_s',
							'leaf' => false,
							'_ni' => $ni
						);
					}
					else if ($listType == 'palosubset')
					{
						$ssList = palo_sbst::getSubsetListByXML(json_decode($map->getData(), true), true);

						foreach($ssList[1] as $elemName)
						{
							$ni = array('n' => $nodeInfo['n'], 'elem_n' => $elemName);
							if ($isWbContainer)
								$ni['v_n'] = $varName;

							$retList[] = array(
								'text' => $elemName,
								'iconCls' => 'w3s_rfolder_s',
								'leaf' => false,
								'_ni' => $ni
							);
						}
					}
				}
				else
				{
					// not mapped node
					$listElems =  palo_element_list_consolidation_elements($conn, $dbName, $dimName, $nodeInfo['n']);
					$cubeName = '#_' . $dimName;

					foreach ($listElems as $elem)
					{
						$nodeData = W3S_NodeData::getNodeData($conn, $dbName, $dimName, $elem['name']);
						$isDynamic = false;
						if (!in_array($nodeData->getType(), array('rstatic', 'rhyperlink', 'rurlplugin')))
						{
							$tmpMap = w3s::getMap($conn, $nodeData, w3s::EXC_PRIVATE_VARS);
							$isDynamic = (!empty($tmpMap) && in_array($nodeData->getType(), array('template', 'rframeset')));
							if ($isDynamic)
							{
								$allLinks = true;
								foreach($tmpMap as $map)
									if ($map['list']->getType() != 'link')
									{
										$allLinks = false;
										break;
									}

								if ($allLinks)
									$isDynamic = false;
							}
						}

						$nodeArr = array(
							'text' => $nodeData->getName(),
							//'qtip' => $nodeData->getDescription(), --- until complete implementation of quick tips, only name of item will be used
							'qtip' => $nodeData->getName(),
							'iconCls' => self::_getTreeIconCls($nodeData->getEffectiveType()),
							'leaf' => (($isDynamic || (!in_array($nodeData->getType(), array('rstatic', 'rhyperlink', 'rurlplugin', 'template', 'rframeset')))) ? false : true),
							'_ni' => array('n' => $elem['name'])
						);

						if (in_array($nodeData->getType(), array('rstatic', 'rhyperlink', 'rurlplugin', 'template', 'rframeset')))
						{
							$nodeLink = $nodeData->getReference();
							$nodeArr['_wb'] = array('g' => $nodeLink->getGroup(), 'h' => $nodeLink->getHierarchy(), 'n' => $nodeLink->getNode());
						}

						$retList[] = $nodeArr;
					}
				}
			}
		}
		catch (Exception $e)
		{
			return array();
		}

		return  $retList;
	}

	private function _getOrderedVariables($vars)
	{
		$indexesArr = array();
		$keysArr = array();
		foreach ($vars as $key => $val)
		{
			array_push($indexesArr, $val['ordnum']);
			if (isset($keysArr[$val['ordnum']]))
				array_push($keysArr[$val['ordnum']], $key);
			else
				$keysArr[$val['ordnum']] = array($key);
		}

		$orderedVars = array();
		if (count($indexesArr) > 0)
		{
			sort($indexesArr, SORT_STRING);
			if (intval($indexesArr[0]) == 0)
			{
				$zeroIndex = array_shift($indexesArr);
				array_push($indexesArr, $zeroIndex);
			}

			foreach($indexesArr as $iVal)
			{
				sort($keysArr[$iVal], SORT_STRING);
				foreach($keysArr[$iVal] as $kVal)
					$orderedVars[$kVal] = $vars[$kVal];
			}
		}

		return ((count($orderedVars) > 0) ? $orderedVars : $vars);
	}

	/*
	 * Function for parsing raw maps object
	 * author: andrejv
	 */
	public function parseMaps ($map)
	{
	    $defval = $map['defval'];
	    $private = $map['private'];
	    $force = $map['force'];
	    $type = 'none';

	    if ($map['list']) $type = $map['list']->getType();

	    switch($type){
	    	case 'palo':
	    		return array('type'=>$type, 'conn' => $map['list']->getConnection(), 'db' => $map['list']->getDb(), 'list' => $map['list']->getList(), 'defval' => $defval, 'ordnum' => $map['ordnum'], 'private' => $private, 'force' => $force);
	    	case 'clist':
				return array('type'=>$type, 'values' => $map['list']->getValues(), 'defval' => $defval, 'ordnum' => $map['ordnum'], 'private' => $private, 'force' => $force);
	    	case 'cval':
				return array('type'=>$type, 'value' => $map['list']->getValue(), 'defval' => $defval, 'ordnum' => $map['ordnum'], 'private' => $private, 'force' => $force);
	    	case 'link':
				return array('type'=>$type, 'value' => $map['list']->getElement(), 'defval' => $defval, 'ordnum' => $map['ordnum'], 'private' => $private, 'force' => $force);
	    	case 'palosubset':
				return array('type'=>$type, 'value' => $map['list']->getData(), 'defval' => $defval, 'ordnum' => $map['ordnum'], 'private' => $private, 'force' => $force);
	    	default:
	    		return array('private' => $private);
		}
	}

	public function getUsedVariables ($nuid, $type = false)
	{
		$group = $this->currGroup['report'];
		$hierarchy = $group->getHierarchy($this->currHierarchy['report']);
		$conn = $this->accessPolicy->getConn();

		$data = W3S_NodeData::getNodeData($conn, $group->getUID(), $hierarchy->getUID(), $nuid);

		if (!($data instanceof W3S_NodeData))
			return null;

		$maps = w3s::getMap($conn, $data, ($type)? w3s::UNMODIFIED : w3s::INC_UNMAPPED_VARS);

		if ($type)
			$result = $this->parseMaps($maps);
		else
			foreach ($maps as $var => $map)
				$result[$var] = $this->parseMaps($map);

		return $result;
	}

	public function getSNodeInScope($g, $h, $n) {
		$group = new W3S_Group($this->accessPolicy, $g);
		$hierarchy = $group->getHierarchy($h);
		$node = $hierarchy->getNode($n);
		return $node;
	}

	public function getNodeInThisScope($type, $g, $h, $n) {

		// Group
		if (get_class($this->currGroup[$type]) == 'W3S_Group' && $g == $this->currGroup[$type]->getUID()){
			$group = $this->currGroup[$type];
			$group->apol = $this->accessPolicy;
		}
		else {
			$group = new W3S_Group($this->accessPolicy, $g);
		}

		$hierarchy = $group->getHierarchy($h);
		$node = $hierarchy->getNode($n);


		if ($type == 'report') {
			$ref = $node->getData()->getReference();
			$node = $this->getSNodeInScope($ref->getGroup(), $ref->getHierarchy(), $ref->getNode());
		}

		return (get_class($node) == 'W3S_Node') ? $node : null;
	}

	public function getTWorkbook ($template) {
	    $group = $this->currGroup['report'];
	    $hierarchy = $group->getHierarchy($this->currHierarchy['report']);

	    $node = $hierarchy->getNode($template);
	    $workbook = $node->getData()->getReference();

	    if (!isset($workbook))
	      return array();

	    $wb_gr = $workbook->getGroup();
	    $wb_hr = $workbook->getHierarchy();
	    $wb_nd = $workbook->getNode();

	    return array('grp' => $wb_gr, 'hr' => $wb_hr, 'node' => $wb_nd);
	}

	public function getChildTempVars ($folder) {
	    $group = $this->currGroup['report'];
	    $hierarchy = $group->getHierarchy($this->currHierarchy['report']);
	    $conn = $this->accessPolicy->getConn();

	    $node = $hierarchy->getNode($folder);

	    $allCh = array();
	    $toReturn = array();
	    $node->getSubUIDs($allCh);

	    foreach ($allCh as $nod) {
	    	$tnode = $hierarchy->getNode($nod);
	    	if ($tnode->getType() == 'template') {

		    	$path = $tnode -> getRelPath($tnode, false);
		    	$path = split('[/-]', $path);

		    	$rpath = '/';

		    	for ($i=1; $i < count($path); $i+=1) {
		    		if ($i!=1)$rpath .= '/'; $rpath .= str_replace('+', ' ', $path[$i]);
		    	}

		    	$ndata = W3S_NodeData::getNodeData($conn, $group->getUID(), $hierarchy->getUID(), $nod);
		    	if (!($ndata instanceof W3S_NodeData))
					return null;

				$maps = w3s::getMap($conn, $ndata, w3s::INC_UNMAPPED_VARS);

		    	$tname = $tnode -> getData() -> getName();
		    	$mapsArray = array();
		    	$vars = array();

		    	//print_r($maps);
		    	foreach ($maps as $mp => $val) {
		    		//print_r($val);
		    		//$mtype = $val['list']->getType();
		    		$private = $val['private'];
	    			$force = $val['force'];
		    		$mtype = false;
		    		if ($val['list']) $mtype = $val['list']->getType();

		    		if ($mtype == 'link') {
		    			$mlist = $val['list']->getElement();
		    		}

		    		$mapsArray[$mp] = array('type' => $mtype, 'list' => $mlist, 'private' => $private, 'force' => $force);
		    		array_push($vars, $mp);
		    	}


		    	$toReturn[$nod] = array('name' => $tname, 'path' => $rpath, 'vars' => $vars, 'maps' => $mapsArray, 'node' => $nod);
	    	}
	    }
	    return($toReturn);
	}

	public function sortVariables($node, array $ord) {

	    $type = 'report';

	    if (!isset($this->currGroup[$type]) || !(($group = $this->currGroup[$type]) instanceof W3S_Group) || !(($hierarchy = $group->getHierarchy($this->currHierarchy[$type])) instanceof W3S_Hierarchy)
	        || !(($node = $hierarchy->getNode($node)) instanceof W3S_Node))
	      return false;

	    $group->apol = $this->accessPolicy;

	    $node->getData()->rearrangeMaps($ord);
	    $node->saveData();
		return true;
	}


	/*
	 * #####################
	 * ### HOMEPAGE MGMT ###
	 * #####################
	 */

	public function getDefRepsByGroup ()
	{
		$list = palo_dimension_list_elements($this->accessPolicy->getSuperConn(), 'System', '#_GROUP_', true);
		$res = array();

		foreach ($list as &$entry)
		{
			$prefs = new Prefs($this->accessPolicy, Prefs::LEVEL_GROUP, $group = $entry['name']);
			$defRep = $prefs->get('studio/default/reports');

			if (!$defRep || !isset($defRep['node']) || !isset($defRep['path']))
			{
				$res[$group] = false;
				continue;
			}

			$vars = array();

			if (isset($defRep['var']))
			{
				if (isset($defRep['var']['name']))
				{
					$var = &$defRep['var'];
					$vars[$var['type']][$var['name']] = $var['val'];
				}
				else
					foreach ($defRep['var'] as &$var)
						$vars[$var['type']][$var['name']] = $var['val'];
			}

			$res[$group] = array('g' => $defRep['group'], 'h' => $defRep['hierarchy'], 'n' => $defRep['node'], 'p' => $defRep['path'], 'v' => $vars);
		}

		return $res;
	}

	public function setDefRepsByGroup ($defRep, $list = null)
	{
		if (isset($defRep['v']))
		{
			if (is_array($defRep['v']['nodes']))
				foreach ($defRep['v']['nodes'] as $name => $val)
					$defRep['var'][] = array('type' => 'nodes', 'name' => $name, 'val' => $val);

			if (is_array($defRep['v']['vars']))
				foreach ($defRep['v']['vars'] as $name => $val)
					$defRep['var'][] = array('type' => 'vars', 'name' => $name, 'val' => $val);

			unset($defRep['v']);
		}

		if ($list)
			foreach ($list as $group => $set)
			{
				$prefs = new Prefs($this->accessPolicy, Prefs::LEVEL_GROUP, $group);

				if ($set)
					$prefs->set('studio/default/reports', $defRep);
				else
				{
					$prefs->remove('studio/default/reports/node');
					$prefs->remove('studio/default/reports/path');
					$prefs->remove('studio/default/reports/var');
				}

				$prefs->save($this->accessPolicy);
			}
		else
		{
			$prefs = new Prefs($this->accessPolicy, Prefs::LEVEL_SERVER);
			$prefs->set('studio/default/reports', $defRep);
			$prefs->save($this->accessPolicy);
		}
	}

	/*
	 * ########################
	 * ### FOLDER VIEW MODE ###
	 * ########################
	 */

	public function setFilesUserView ($type, $n, $view)
	{
		$group = $this->currGroup[$type];

		if (!($group instanceof W3S_Group))
			return false;

		$group->apol = $this->accessPolicy;


		$obj = $group->getHierarchy($this->currHierarchy[$type]);

		if (!($obj instanceof W3S_Hierarchy))
			return false;

		if ($n != 'root')
		{
			$obj = $obj->getNode($n);

			if (!($obj instanceof W3S_Node))
				return false;
		}

		$userdata = &$obj->getUserData();

		if ($view)
			$userdata['view'] = $view;
		else
			unset($userdata['view']);

		return $obj->saveUserData();
	}

	// mtodorovic - used for Batch PDF priting - to send data over URL
	public static function encodeUrlParams (array $params)
	{
		return urlencode(base64_encode(gzcompress(json_encode($params))));
	}
}

?>