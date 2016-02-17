/*
 * @brief wss file
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
 * SVN: $Id: ChooseElement.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */
Jedox.palo.openChooseElement = function(confDataT){
	Jedox.dlg.dlgRegistry.add(new Jedox.palo.ChooseElement(confDataT));
};

Jedox.palo.ChooseElement = (function(){

	// class constructor
	return function (confDataT) {

		Jedox.palo.ChooseElement.parent.constructor.call(this);

		this.id = 'chooseElement';
		var that = this;

		var paloCbSuccessHandlers =
		{
			getDimStringAttrs: function(result)
			{
				var tmpRec;
				tmpRec = new AttrRecord({
					name: "[none]".localize(),
					esc_name: "[none]".localize()
				});
				storeAttrs.add(tmpRec);

				for (var i = 0; i < result.length; i++)
				{
					tmpRec = new AttrRecord({
						name: result[i].name,
						esc_name: Jedox.palo.utils.escHTML(result[i].name)
					});
					storeAttrs.add(tmpRec);
				}

				if (editMode && editData.length > 0 && editData[0][1] != null)
					selectedAttr = storeAttrs.find('name', editData[0][1]);

				cmbAttr.setValue(storeAttrs.getAt(selectedAttr).get('name'));
			},
			searchElem: function(result)
			{
				if (result[0])
				{
					if (workingMode == 4)
						treeMain.selectPaths(result[1]);
					else
						treeMain.selectPath(result[1][0]);
				}
				else
					Ext.MessageBox.show({
						title: "Information".localize(),
						msg: "Element not found!".localize(),
						buttons: Ext.Msg.OK,
						icon: Ext.MessageBox.INFO
					});
			},
			searchElems: function(result)
			{
				paloCbSuccessHandlers.searchElem(result);
			}
		};

		var paloCbErrorHandlers =
		{
			getDimStringAttrs: function() {},
			searchElem: function() {},
			searchElems: function() {}
		};

		var paloCbTimeoutHandlers =
		{
			getDimStringAttrs: function() {},
			searchElem: function() {},
			searchElems: function() {}
		};

		var paloRpcServer = new Jedox.backend.rpc.Palo(paloCbSuccessHandlers, paloCbErrorHandlers, paloCbTimeoutHandlers),
			servId, dbName, dimName, parentObject,
			panelMain, panelTopBtns, panelBottomTreeBtns, panelbtnSearch, paneltxtSearch, panelcmbAttr,
			treeMain, treeRoot, expandMoreLevels, treeLevel, syncCounter, treeMaxLevelReached, expandAllLevels, hasOnlyLeaves,
			txtSearch, cmbAttr, btnTreeControls, btnSearch,
			selectedAttr, editMode, editData, editY, editPasteViewId, dblClickData;

		// record and store for Attribute combo box
		var AttrRecord = new Ext.data.Record.create([
			{ name: 'name' },
			{ name: 'esc_name' }
		]);
		var storeAttrs = new Ext.data.SimpleStore({
			fields: [
				{ name: 'name' },
				{ name: 'esc_name' }
			]
		});

		this.init = function(confData)
		{
			workingMode = confData.working_mode; // 1 - grid PasteView, 2 - dialog PasteView, 4 - Subset Dialog, 8 - grid PasteElements (single element)

			// get confData properties (+ editData property few rows below)
			parentObject = confData.parent_object;
			servId = confData.serv_id;
			dbName = confData.db_name;
			dimName = confData.dim_name;
			editPasteViewId = confData.pasteview_id;
			editY = confData.edit_y;
			dblClickData = confData.dblclick_data;

			treeLevel = 0;
			syncCounter = 0;
			treeMaxLevelReached = 0;
			selectedAttr = 0;
			expandAllLevels = false;
			hasOnlyLeaves = false;

			editMode = ((confData.edit_data) ? true : false);
			editData = ((editMode) ? confData.edit_data : []);

			// *** BUTTONS *** //
			// Tree controling buttons
			btnTreeControls = {
				plusB: new Ext.Button({
					id:'wChooseEl_plus_btn',
					cls: 'modellerImageButton',
					style: 'vertical-align:bottom;',
					tabIndex: 1,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					iconCls: 'palo_icon_plus',
					handler: function()
						{
							treeLevel++;
							_expandTreeToLevel(treeRoot);
						}
				}),
				minusB: new Ext.Button({
					id:'wChooseEl_minus_btn',
					cls: 'modellerImageButton',
					iconCls: 'palo_icon_minus',
					tabIndex: 2,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					style: 'vertical-align:bottom;',
					handler: function()
						{
							if (treeLevel > 0)
							{
								treeLevel--;
								_expandTreeToLevel(treeRoot);
							}
						}
				}),
				expandAllB: new Ext.Button({
					id:'wChooseEl_expandall_btn',
					cls: 'modellerImageButton',
					tabIndex: 3,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					style: 'vertical-align:bottom;',
					iconCls: 'palo_icon_expandall',
					handler: function()
						{
							expandAllLevels = true;
							treeMain.expandAll();
							treeLevel = (treeMaxLevelReached >= 0) ? treeMaxLevelReached : 0;
						}
				}),
				collapseAllB: new Ext.Button({
					id:'wChooseEl_collapseall_btn',
					cls: 'modellerImageButton',
					tabIndex: 4,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					style: 'vertical-align:bottom;',
					iconCls: 'palo_icon_colapseall',
					handler: function()
						{
							treeMain.collapseAll();
							treeLevel = 0;
						}
				}),
				oneB: new Ext.Button({
					id:'wChooseEl_one_btn',
					text: '1',
					tabIndex: 20,
					ctCls: 'modellerButtonWithMargin'.concat(' ',Jedox.kbd.Base.tags.NO_ENTER),
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 0;
							_expandTreeToLevel(treeRoot);
						}
					}
				}),
				twoB: new Ext.Button({
					id:'wChooseEl_two_btn',
					text: '2',
					tabIndex: 21,
					ctCls: 'modellerButtonWithMargin'.concat(' ',Jedox.kbd.Base.tags.NO_ENTER),
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 1;
							_expandTreeToLevel(treeRoot);
						}
					}
				}),
				threeB: new Ext.Button({
					id:'wChooseEl_three_btn',
					text: '3',
					tabIndex: 22,
					ctCls: 'modellerButtonWithMargin'.concat(' ',Jedox.kbd.Base.tags.NO_ENTER),
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 2;
							_expandTreeToLevel(treeRoot);
						}
					}
				}),
				fourB: new Ext.Button({
					id:'wChooseEl_four_btn',
					text: '4',
					tabIndex: 23,
					ctCls: 'modellerButtonWithMargin'.concat(' ',Jedox.kbd.Base.tags.NO_ENTER),
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 3;
							_expandTreeToLevel(treeRoot);
						}
					}
				}),
				fiveB: new Ext.Button({
					id:'wChooseEl_five_btn',
					text: '5',
					tabIndex: 24,
					ctCls: 'modellerButtonWithMargin'.concat(' ',Jedox.kbd.Base.tags.NO_ENTER),
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 4;
							_expandTreeToLevel(treeRoot);
						}
					}
				})
			};

			// panel with buttons (+, -, Expand All and Collapse All)
			panelTopBtns = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'table',
				items: [btnTreeControls.plusB, btnTreeControls.minusB,
						btnTreeControls.expandAllB, btnTreeControls.collapseAllB]
			});

			// panel with buttons (1, 2, 3, 4, 5 and B)
			panelBottomTreeBtns = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'table',
				items: [btnTreeControls.oneB, btnTreeControls.twoB,
						btnTreeControls.threeB, btnTreeControls.fourB, btnTreeControls.fiveB]
			});

			btnSearch = new Ext.Button({
				id:'wChooseEl_search_btn',
				text: "Search & Select".localize(),
				tabIndex: 13,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				cls: 'modellerButtonWithMargin',
				listeners: {
					click: function()
					{
						if (txtSearch.getValue() != '')
							paloRpcServer.searchElem(servId, dbName, dimName, txtSearch.getValue(), ((selectedAttr == 0) ? null : storeAttrs.getAt(selectedAttr).get('name')), (workingMode != 4));
					}
				}
			});
			panelbtnSearch = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [btnSearch]
			});

			// *** Buttons *** //
			btnOk = that.components.OK = new Ext.Button({
				id:'wChooseEl_OK_btn',
				text: "OK".localize(),
				tabIndex: 100,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				ctCls: 'stdButtons'.concat(' ',Jedox.kbd.Base.tags.NO_ENTER),
				handler: function(){_btnOkHandler();}
			});

			btnClose = that.components.Cancel = new Ext.Button({
				id:'wChooseEl_close_btn',
				text: "Close".localize(),
				tabIndex: 101,
				ctCls: 'stdButtons'.concat(' ',Jedox.kbd.Base.tags.NO_ENTER),
				handler: function()
					{
						that.win.close();
					}
			});
			// <--- BUTTONS ---> //

			// *** ComboBoxes and Text fields *** //
			cmbAttr = new Ext.form.ComboBox({
				id:'wChooseEl_attr_cmb',
				store: storeAttrs,
				bodyStyle: 'background-color: transparent;',
				typeAhead: false,
				tabIndex: 10,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				listeners: {
					select: function(combo, record, index)
					{
						if (index != selectedAttr)
						{
							treeMain.getLoader().dataUrl = '/be/erpc.php?wam=' + Jedox.wss.app.appModeS + '&c=palo&m=getTreeNodes&servId=' + servId +
								'&dbName=' + dbName + ( (index != 0) ? '&attr=' + record.get('name') : '' );

							treeRoot.reload();
							selectedAttr = index;
						}
					}
				},
				valueField: 'name',
				displayField: 'name',
				tpl: '<tpl for="."><div class="x-combo-list-item">{esc_name}</div></tpl>'
			});
			panelcmbAttr = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [cmbAttr]
			});

			txtSearch = new Ext.form.TextField({
				id:'wChooseEl_search_fld',
				hideLabel: true,
				tabIndex: 11,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER
			});

			paneltxtSearch = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [txtSearch]
			});
			// <--- ComboBoxes and Text fields ---> //

			// *** TREE PANEL and ROOT *** //
			treeMain = new Ext.tree.TreePanel({
				id:'wChooseEl_tree_tr',
				cls: 'x-tree-noicon',
				selModel: ( ( workingMode == 4 ) ? new Ext.tree.MultiSelectionModel() : new Ext.tree.DefaultSelectionModel() ),
				border: false,
				autoScroll: true,
				animate: false,
				enableDD: false,
				containerScroll: true,
				rootVisible: false,
				plugins: new Ext.ux.tree.TreeNodeMouseoverPlugin(),
				listeners: {
					contextmenu: function(node, e)
					{
						e.stopEvent();
					},
					dblclick: function(node, e)
					{
						_btnOkHandler();
					},
					append: function(thisT, parNode, node, index)
					{
						node.text = Jedox.palo.utils.escHTML(node.text);
					},
					expandnode: function(sNode)
					{
						if (sNode.attributes.ptb)
							sNode.attributes.ptb.show();this.body.unmask();
					},
					collapsenode: function(sNode)
					{
						if (sNode.attributes.ptb)
							sNode.attributes.ptb.hide();
					}
				},
				loader: new Ext.ux.tree.PagingTreeLoader({
					pagingModel: 'local',
					baseParams: {name: 'root'},
					dataUrl: '/be/erpc.php?wam=' + Jedox.wss.app.appModeS + '&c=palo&m=getTreeNodes&servId=' + servId +
							'&dbName=' + dbName + ((editMode && ((editData.length > 0) && (editData[0][1] != null))) ? '&attr=' + editData[0][1] : ''),
					listeners: {
						beforeload: function(thisL, node, cb)
						{
							this.baseParams.name = node.attributes.name;
							this.baseParams.dimName = dimName;

							if (expandMoreLevels || expandAllLevels)
							{
								if (!hasOnlyLeaves)
									hasOnlyLeaves = true;

								syncCounter++;
							}
						},
						load: function(thisS, node, response)
						{
							for (var i=0; i<node.childNodes.length; i++)
								node.childNodes[i].ui.onDblClick = function(e)
								{
									e.preventDefault();
									if (this.disabled)
										return;
									this.fireEvent("dblclick", this.node, e);
								};

							if (node.getDepth() > treeMaxLevelReached)
								treeMaxLevelReached = node.getDepth();

							if (syncCounter > 0)
							{
								if (hasOnlyLeaves)
									node.eachChild(
										function(chNode) {
											if (!chNode.isLeaf())
											{
												hasOnlyLeaves = false;
												return false;
											}
										}
									);

								syncCounter--;
								if (expandMoreLevels)
									_expandTreeToLevel(node);
								else if ((expandAllLevels) && (syncCounter == 0) && (hasOnlyLeaves))
								{
									hasOnlyLeaves = false;
									expandAllLevels = false;
									if (treeMaxLevelReached > treeLevel)
										treeLevel = treeMaxLevelReached;
								}
							}
							else if (singleRunFncPreSelect)
							{
								singleRunFncPreSelect();
								singleRunFncPreSelect = null;
							}
						}
					}
				}),
				selectPaths: function(paths, attr)
				{
					attr = attr || 'id';
					var keys, selectionModel = this.getSelectionModel();

					selectionModel.clearSelections();
					for (var i=0, numOfPaths=paths.length; i < paths.length; i++)
					{
						keys = paths[i].split(this.pathSeparator);
						if (keys.length > 1)
						{
							var selNode = function(scope, lastNodeName)
							{
								var f = function(success, node)
								{
									if (success && node)
									{
										node = node.findChild(attr, lastNodeName);
										if (node && !selectionModel.isSelected(node))
										{
											selectionModel.selNodes.push(node);
											selectionModel.selMap[node.id] = node;
											node.ui.addClass("x-tree-selected");
										}

										if (node)
											selectionModel.lastSelNode = node;
									}

									if (--numOfPaths == 0 && selectionModel.lastSelNode)
									{
										selectionModel.fireEvent('selectionchange', selectionModel, selectionModel.selNodes);
										selectionModel.lastSelNode.ui.focus();
									}
								};
								scope.expandPath(keys.join(scope.pathSeparator), attr, f);
							}(this, keys.pop());
						}
					}
				}
			});

			// set the root node
			treeRoot = new Ext.tree.AsyncTreeNode({
				text: 'Test',
				draggable: false,
				id: 'root',
				name: 'root'
			});
			treeMain.setRootNode(treeRoot);
			// <--- TREE PANEL and ROOT ---> //

			// *** MAIN panel and Window *** //
			panelMain = that.containers.mainPanel = new Ext.Panel({
				id: 'ce_mainPanel',
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'absolute',
				anchor: '100% 100%',
				monitorResize: true,
				listeners: {
					resize: _resizeAll
				},
				items: [panelTopBtns, treeMain, panelBottomTreeBtns, panelbtnSearch,
						panelcmbAttr, paneltxtSearch]
			});

			// Wizard Window
			that.win = new Ext.Window({
				id: 'chooseelementWizardWindow',
				layout: 'fit',
				cls: 'default-format-window',
				title: "Choose Element".localize(),
				width: 350,
				height: 450,
				minWidth: 350,
				minHeight: 450,
				closeAction: 'close',
				autoDestroy: true,
				plain: true,
				onEsc: Ext.emptyFn,
				modal: true,
				resizable: true,
				listeners: {
					activate: _resizeAll,
					close: function()
					{
						if (Jedox.palo.workIn == Jedox.palo.GRID && !parentObject)
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
						}
						that.close();
						if (Jedox.palo.workIn == Jedox.palo.STUDIO){
							Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
							Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.chooseElement);
						}
						if (Jedox.palo.workIn == Jedox.palo.GRID)
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.chooseElement);
					},
					show:function(){
						setTimeout(function(){
							//that.initFocus(true, 300);
						});
					},
					activate: function(win) {that.activate();}
				},
				items: [panelMain],
				buttons: [
					btnOk,
					btnClose
				]
			});

			var singleRunFncPreSelect = function()
			{
				if (editMode && (editData.length > 0))
				{
					if (workingMode == 4 && editData.length > 1)
					{
						var elemList = []
							, dataLen = editData.length;

						for (var i=0; i<dataLen; i++)
							elemList[elemList.length] = editData[i][0];
						paloRpcServer.searchElems(servId, dbName, dimName, elemList, null, (workingMode != 4));
					}
					else
						paloRpcServer.searchElem(servId, dbName, dimName, editData[0][0], null, (workingMode != 4));
				}
			};
			// <--- MAIN panel and Window ---> //
		}

		// *** PUBLIC functions *** //
		this.show = function()
		{
			if (that.win)
			{
				paloRpcServer.getDimStringAttrs(servId, dbName, dimName);

				if (Jedox.palo.workIn == Jedox.palo.GRID && !parentObject)
				{
					Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
					Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
				}
				if (Jedox.palo.workIn == Jedox.palo.STUDIO){
					Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
					Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;
				}

				that.win.show();
			}
		}
		// <--- PUBLIC functions --->//

		// +++ Handler Functions +++ //
		var _btnOkHandler =	function()
		{
			if (workingMode == 1)
			{
				// used for "on grid" Paste View change
				var tmpNode = treeMain.getSelectionModel().getSelectedNode();
				if (tmpNode && tmpNode.attributes.name != editData[0][0])
				{
					var tmpDim = [
						dimName,
						[[
							tmpNode.attributes.name,
							((cmbAttr.getValue() == "[none]".localize()) ? null : cmbAttr.getValue()),
							((tmpNode.isLeaf()) ? '' : 'C')
						]]
					];

					var settings = [dblClickData.c, dblClickData.r, servId, dbName, editPasteViewId, editY];
					if (Jedox.palo.workIn == Jedox.palo.GRID)
						Jedox.backend.rpc_cb('palo_handlerChooseElements', [[settings, tmpDim]]);
				}
			}
			else if (workingMode == 2)
			{
				// used for Paste View
				var tmpNode = treeMain.getSelectionModel().getSelectedNode(), elemDef = [];
				if (tmpNode)
					elemDef = [[
						tmpNode.attributes.name,
						((cmbAttr.getValue() == "[none]".localize()) ? null : cmbAttr.getValue()),
						((tmpNode.isLeaf()) ? '' : 'C')
					]];
				parentObject.cb_fnc(dimName, elemDef);
			}
			else if (workingMode == 4)
			{
				// used for Subset Editor
				var tmpElems = [],
					tmpNodes = treeMain.getSelectionModel().getSelectedNodes(),
					nodeListLen = tmpNodes.length;

				_sortSelectedNodesNodes(tmpNodes);
				for (var i=0; i<nodeListLen; i++)
					tmpElems[tmpElems.length] = [i, tmpNodes[i].attributes.name, Jedox.palo.utils.escHTML(tmpNodes[i].attributes.name)];

				parentObject.cb_fnc(tmpElems);
			}
			else if (workingMode == 8)
			{
				// used from grid for Paste Elements (single cell)
				var tmpNode = treeMain.getSelectionModel().getSelectedNode();
				if (tmpNode && tmpNode.attributes.name != editData[0][0])
				{
					var tmpDim = {};
					tmpDim[dimName] =
						[
							[
								tmpNode.attributes.name,
								((cmbAttr.getValue() == "[none]".localize()) ? null : cmbAttr.getValue()),
								((tmpNode.isLeaf()) ? '' : 'C')
							]
						];

					var settings = [dblClickData.c, dblClickData.r, servId, dbName, 0];
					if (Jedox.palo.workIn == Jedox.palo.GRID)
						Jedox.backend.rpc_cb('palo_handlerSelectElements', [[settings, tmpDim]]);
				}
			}

			that.win.close();
		}
		// --- Hanlder Functions --- //

		// *** Other Functions *** //
		// Tree->List sorting
		var _sortSelectedNodesNodes = function(nodeList)
		{
			var nodesLen = nodeList.length
				, tmpNode
				, i
				, j;

			var genKey = function(node)
			{
				if (!node.attributes._sort && node.getDepth() > 0)
				{
					var pathList = genKey(node.parentNode);
					pathList[pathList.length] = node.attributes._num_id + 1;
					node.attributes._sort = pathList;

					return pathList.slice(0);
				}

				if (node.attributes._sort)
					return node.attributes._sort.slice(0);
				else
					return [];
			};

			for (i=0; i<nodesLen; i++)
				genKey(nodeList[i]);

			var gtNode = function(node1, node2)
			{
				var sArr1 = node1.attributes._sort
					, sArr2 = node2.attributes._sort
					, i=0;

				while(sArr1[i] && sArr2[i])
				{
					if (sArr1[i] > sArr2[i])
						return true;
					else if (sArr1[i] < sArr2[i])
						return false;

					i++;
				}

				return (!!sArr1[i]);
			};

			for (i=0; i<nodesLen-1; i++)
				for (j=nodesLen-1; j>i; j--)
					if (gtNode(nodeList[j-1], nodeList[j]))
					{
						tmpNode = nodeList[j-1];
						nodeList[j-1] = nodeList[j];
						nodeList[j] = tmpNode;
					}
		}

		// Expand/Collapse tree nodes by level
		var _expandTreeToLevel = function(node)
		{
			expandMoreLevels = true;
			_doExpandigTreeToLevel(node);
			if ((treeLevel > (treeMaxLevelReached)) && (syncCounter == 0))
				treeLevel = treeMaxLevelReached;

			if (syncCounter == 0)
				expandMoreLevels = false;
		}

		var _doExpandigTreeToLevel = function(node)
		{
			if (node.getDepth() > treeMaxLevelReached)
				treeMaxLevelReached = ( ((node.childNodes.length == 0) && ((node.getDepth() - 1) >= treeMaxLevelReached)) ? node.getDepth() - 1 : node.getDepth());

			if (node.getDepth() == treeLevel)
				node.collapseChildNodes(true);
			else if (node.childNodes.length > 0)
				for (var i=(node.childNodes.length - 1); i>=0; i--)
					if (node.childNodes[i].getDepth() <= treeLevel)
					{
						node.childNodes[i].expand();
						_doExpandigTreeToLevel(node.childNodes[i]);
					}
		}
		// <--- Other Functions ---> //

		// *** RESIZE function *** //
		var _resizeAll = function()
		{
			if (panelMain.rendered)
			{
				// disable Text selection on all elements inside window
				//panelMain.getEl().unselectable();

				var lineH = 23; // in pixels (height of lines [buttons, text fields, combo boxes, etc])
				var marginSize = 3; // size in pixels for spacing

				var w = panelMain.getSize().width;
				var h = panelMain.getSize().height;

				var treeW = w - 2*marginSize;
				var treeH = h - 7*marginSize - 5*lineH;

				// tree
				treeMain.setSize(treeW, treeH);
				treeMain.setPosition(marginSize, 2*marginSize + lineH);

				// Buttons
				panelTopBtns.setPosition(marginSize, marginSize);
				panelBottomTreeBtns.setPosition(marginSize, treeH + 5*marginSize + 3*lineH);
				if (panelbtnSearch.rendered && btnSearch.rendered)
					panelbtnSearch.setPosition(w - marginSize - btnSearch.getEl().getBox().width, treeH + 4*marginSize + 2*lineH);

				// Combo and Text field
				panelcmbAttr.setPosition(marginSize, treeH + 3*marginSize + lineH);
				paneltxtSearch.setPosition(marginSize, treeH + 4*marginSize + 2*lineH);
				if (cmbAttr.rendered && btnSearch.rendered)
				{
					cmbAttr.setWidth(w - 3*marginSize - panelbtnSearch.getEl().getBox().width);
					txtSearch.setWidth(w - 3*marginSize - panelbtnSearch.getEl().getBox().width);
				}
			}
		}

		this.init(confDataT);
		this.setContext();
		this.show();
	};
}
)();

Jedox.util.extend(Jedox.palo.ChooseElement, Jedox.dlg.Dialog);