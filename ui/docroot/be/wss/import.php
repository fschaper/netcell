<?php

/*
 * \brief front URL for Palo import and importing images
 *
 * \file import.php
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: import.php 4780 2011-03-29 06:42:51Z mladent $
 *
 */

require '../../../etc/config.php';

require 'autoload.php';
require 'ccmd.php';
require 'sess_start.php';

define('MAX_IMG_FILE_SIZE', 2097152); // 2MB = 2097152B

if (isset($_GET['t']))
{
	switch ($_GET['t'])
	{
		case 'palo':
			if (isset($_GET['f']))
			{
				switch ($_GET['f'])
				{
					case 'textfile':
						$op = (isset($_GET['o'])) ? $_GET['o'] : 'full';

						// config options
						switch ($_POST['radioImportSeparateType'])
						{
							case 'tab': $sep = "[\t]"; break;
							case 'comma': $sep = ','; break;
							case 'semi': $sep = ';'; break;
							case 'blank': $sep = '[ ]'; break;
							case 'user': $sep = $_POST['user_separator']; break;
						}
						$dPoint = $_POST['decimal_point'];
						$header = (isset($_POST['header']) && ($_POST['header'] == 'on'));

						if ($op == 'full')
						{
							$textFile = new TextFile();

							$textFile->setSep($sep);
							$textFile->setPoint($dPoint);
							$textFile->setHeader($header);

							$textFile->importFile($_FILES['palo_import_file']['tmp_name']);
							$textFile->execCmds();

							// check if full is trigered after step by step
							if (isset($_SESSION['palo_import']))
							{
								$wss_ajax = new WSS();

								$workbook = (($wss_ajax != null) ? $wss_ajax->getCurrWbId() : '1');
								$sheet = (($wss_ajax != null) ? $wss_ajax->getCurrWsId() : '1');

								unlink($_SESSION['palo_import'][$workbook][$sheet]['file']);
								unset($_SESSION['palo_import']);
							}

							// Hide Ext Wait msg
							print '<script type="text/javascript">parent.Jedox.wss.sheet.refresh();parent.Ext.MessageBox.hide();</script>';
						}
						else
						{
							// move file
							$newFilePath = str_replace('\\', '/', dirname($_FILES['palo_import_file']['tmp_name'])) . '/' . uniqid('wss_pi_', true);
							move_uploaded_file($_FILES['palo_import_file']['tmp_name'], $newFilePath);
							$countLines = count(file($newFilePath));

							//config obj
							$confObj = array('sep' => $sep, 'd_point' => $dPoint, 'header' => $header);
							$wss_ajax = new WSS();
							$workbook = (($wss_ajax != null) ? $wss_ajax->getCurrWbId() : '1');
							$sheet = (($wss_ajax != null) ? $wss_ajax->getCurrWsId() : '1');

							// do clean up if other file is stored
							if (isset($_SESSION['palo_import']) && isset($_SESSION['palo_import'][$workbook]) && isset($_SESSION['palo_import'][$workbook][$sheet]))
								unlink($_SESSION['palo_import'][$workbook][$sheet]['file']);

							if (!isset($_SESSION['palo_import']))
								$_SESSION['palo_import'] = array();
							if (!isset($_SESSION['palo_import'][$workbook]))
								$_SESSION['palo_import'][$workbook] = array();

							$_SESSION['palo_import'][$workbook][$sheet] = array('conf' => $confObj, 'file' => $newFilePath, 'num_of_lines' => $countLines);

							// import first line
							$textFile = new TextFile();

							$textFile->setSep($sep);
							$textFile->setPoint($dPoint);
							$textFile->setHeader($header);

							$textFile->importFileLine($_SESSION['palo_import'][$workbook][$sheet]['file'], 0);

							// exec commands
							ccmd(json_encode($textFile->genCmds()), 0);

							// Hide Ext Wait msg - and set progress bar
							print '<script type="text/javascript">parent.Jedox.wss.palo.numOfUploadedLines=' . $countLines . ';parent.Ext.getCmp("palo_imp_pbar3").updateProgress(' . floatval(1/($countLines - ($header ? 1 : 0))) . ');parent.Jedox.wss.sheet.refresh();parent.Ext.MessageBox.hide();</script>';
						}
					break;
				}
			}
		break;

		case 'palo_rule':
			$connName = $_POST['conn_name']; $dbName = $_POST['db_name']; $cubeName = $_POST['cube_name'];

			$conn = palo::palo_init($connName);
			// parse rules and check for errors
			$ruleLines = file($_FILES['palo_rules_file']['tmp_name'], FILE_SKIP_EMPTY_LINES | FILE_IGNORE_NEW_LINES);
			$msgs = ''; $lineNum = 1; $newRules = array();
			foreach ($ruleLines as $ruleLine)
			{
				if (strpos(str_replace("\xEF\xBB\xBF", '', $ruleLine), '#') !== 0) // str_replace("\xEF\xBB\xBF", '', $ruleLine) - to remove UTF-8 beginning file character
				{
					$ruleParams = split(';', $ruleLine);
					$newRules[] = $ruleParams;
					$res = palo_cube_rule_parse($conn, $dbName, $cubeName, $ruleParams[0]);

					if (!is_array($res) && strcasecmp($res, '#NULL!') === 0)
						$msgs .= '<br>Error at line ' . $lineNum . ' for Rule: \\"' . $ruleParams[0] . '\\"';
				}
				$lineNum++;
			}

			// Add new rules if everything is OK
			if (empty($msgs))
			{
				// delete old rules if required
				if (isset($_GET['del_old']) && $_GET['del_old'] == 'yes')
				{
					$rules = palo_cube_rules($conn, $dbName, $cubeName);
					foreach ($rules as $rule)
						palo_cube_rule_delete($conn, $dbName, $cubeName, $rule['identifier']);
				}

				// add rules
				foreach ($newRules as $ruleParams)
					palo_cube_rule_create($conn, $dbName, $cubeName, $ruleParams[0], $ruleParams[2], $ruleParams[1], 1);
			}
			palo::palo_disconnect($conn);

			print '<script type="text/javascript">'
					. 'activeDlg = parent.Jedox.dlg.dlgRegistry.getActive(); if (activeDlg.id == "RuleEditor" && activeDlg.refreshList) activeDlg.refreshList(); delete activeDlg;'
					. ((!empty($msgs)) ? 'parent.Ext.Msg.alert("Rules Import Error","' . $msgs . '");' : '')
				  . '</script>';
		break;

		case 'img':
			try
			{
				$fSize = filesize($_FILES['img_filename']['tmp_name']);
				if ($fSize > MAX_IMG_FILE_SIZE)
					die('<script type="text/javascript">parent.Ext.MessageBox.hide();parent.Jedox.wss.wsel.img.showAlert("Unable to import picture", "imgFile_toBig");</script>');

				$img_type = $_FILES['img_filename']['type'];
				// NOTE: IE8 compatibility MIME types: http://msdn.microsoft.com/en-us/library/ms775147(VS.85).aspx
				switch($img_type)
				{
					case 'image/pjpeg':
						$img_type = 'image/jpeg';
					case 'image/jpeg':
						$ih = imagecreatefromjpeg($_FILES['img_filename']['tmp_name']);
						break;
					case 'image/x-png':
						$img_type = 'image/png';
					case 'image/png':
						$ih = imagecreatefrompng($_FILES['img_filename']['tmp_name']);
						break;
					case 'image/gif':
						$ih = imagecreatefromgif($_FILES['img_filename']['tmp_name']);
						break;
					default:
						die('<script type="text/javascript">parent.Ext.MessageBox.hide();parent.Jedox.wss.wsel.img.showAlert("Unable to import picture", "imgFile_unsupportedType");</script>');
				}

				$w = imagesx($ih); $h = imagesy($ih);
				if ($w == 0 || $h == 0)
					throw new Exception();

				$payload = base64_encode(gzcompress(file_get_contents($_FILES['img_filename']['tmp_name'])));
				$zindex = $_GET['zindex'];
				$locked = $_GET['locked'];
				$hldata = ( !empty($_GET['hldata']) ) ? $_GET['hldata'] : 'null';

				if (!isset($_GET['img_id'])) // insert new image
				{
					$x = isset($_GET['x_pos']) ? intval($_GET['x_pos'] - $w/2) : 1;
                    $y = isset($_GET['y_pos']) ? intval($_GET['y_pos'] - $h/2) : 1;
                    $x = ($x < 1) ? 1 : $x;
                    $y = ($y < 1) ? 1 : $y;

					$cmds = json_encode(
						array(
							array('wadd', '', array('e_type' => 'img', 'img_type' => $img_type, 'size' => array($w, $h), 'payload' => $payload, 'zindex' => $zindex, 'locked' => $locked))
						)
					);
				}
				else // edit image
				{
					$x = isset($_GET['x_pos']) ? intval($_GET['x_pos']) : 1;
                    $y = isset($_GET['y_pos']) ? intval($_GET['y_pos']) : 1;

					$cmds = json_encode(
						array(
							array('wupd', '', array($_GET['img_id'] => array('img_type' => $img_type, 'size' => array($w, $h), 'payload' => $payload)))
						)
					);
				}
				$res = json_decode(ccmd($cmds, 0));

				$p_str = '<script type="text/javascript">parent.Ext.MessageBox.hide();if (parent.Jedox.dlg.dlgRegistry.dump().dialogs[0]) parent.Jedox.dlg.dlgRegistry.dump().dialogs[0].win.close();';
				if ($res[0][0])
					if (isset($_GET['img_id']))
						$p_str .= 'parent.Jedox.wss.wsel.img.remove(\'' . $_GET['img_id'] . '\');' .
							'parent.Jedox.wss.wsel.img.createImg(\'' . $_GET['img_id'] . '\', ' . $y . ', ' . $x . ', ' . $w . ', ' . $h . ', true, ' . $zindex . ', ' . $locked . ', ' . $hldata . ');';
					else
						$p_str .= 'parent.Jedox.wss.wsel.img.createImg(\'' . $res[0][1][0] . '\', ' . $y . ', ' . $x . ', ' . $w . ', ' . $h . ', true, ' . $zindex . ', ' . $locked . ', ' . $hldata . ');';
				$p_str .= '</script>';

				// output to trigger creation of image container in browser (javascript)
				print $p_str;
			}
			catch (Exception $e)
			{
				die('<script type="text/javascript">parent.Ext.MessageBox.hide();parent.Jedox.wss.wsel.img.showAlert("Unable to import picture", "imgFile_undefError");</script>');
			}
		break;
	}
}

?>