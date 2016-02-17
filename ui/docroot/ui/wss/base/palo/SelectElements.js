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
 * SVN: $Id: SelectElements.js 5113 2011-07-14 13:55:46Z mladent $
 *
 */

Jedox.wss.palo.SelectElements = function(conf)
{
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.SelectElements(conf));
};

Jedox.wss.dlg.SelectElements = (function() {

	return function (conf)
	{
		Jedox.wss.dlg.SelectElements.parent.constructor.call(this);
		this.id = 'SelectElements';
		var that = this;

		var paloCbSuccessHandlers =
		{
			getServListWithDBs: function(result)
			{
				storeServDb.loadData(result[0]);

				Ext.MessageBox.hide();

				if (cmbDbState == -1 && editMode)
					cmbDbState = storeServDb.findBy(function(rec, id)
					{
						return (rec.get('name') == dbName && rec.get('parent_id') == servId && rec.get('type') == 'database')
					});

				if (result[1] && editMode == 0)
					preselectedServDb = result[1];

				if (cmbDbState == -1 && preselectedServDb)
					cmbDbState = storeServDb.findBy(function(rec, id)
					{
						return (rec.get('name') == preselectedServDb[1] && rec.get('parent_id') == preselectedServDb[0] && rec.get('type') == 'database')
					});

				if (cmbDbState == -1 || storeServDb.getCount() <= cmbDbState)
					cmbDbState = storeServDb.find('type', 'database');

				if (cmbDbState != -1)
				{
					var tmpIndex = cmbDbState;
					cmbDbState = -1;
					cmbDb.setValue(storeServDb.getAt(tmpIndex).get('id'));
					cmbDb2.setValue(storeServDb.getAt(tmpIndex).get('id'));
					_cmbDbSelectionHandler(cmbDb, storeServDb.getAt(tmpIndex), tmpIndex);
				}
			},
			getDims: function(result)
			{
				_removeAllDimsFromPanel(panelDims);
				for (var i = 0; i < result.length; i++)
					_addDimPanel(result[i], ((i == 0) ? true : false), i);

				storeDimNames.removeAll();
				for (var i = 0; i < result.length; i++)
					storeDimNames.add(new DimNameRecord({
						name: result[i]
					}));
			},
			getCubeNames: function(result)
			{
				storeCubes.removeAll();
				cmbCube.setValue('');
				for (var i = 0; i < result.length; i++)
					storeCubes.add(new CubeRecord({
						name: result[i]
					}));

				cmbCube.setValue( ( (storeCubes.getCount() > 0) ? storeCubes.getAt(0).get('name') : '' ) );
			},
			getDimStringAttrs: function(result)
			{
					storeAttrs.removeAll();
					storeAttrs.add(new AttrRecord({
						name: "[none]".localize(),
						esc_name: "[none]".localize()
					}));

					for (var i = 0; i < result.length; i++)
						storeAttrs.add(new AttrRecord({
							name: result[i].name,
							esc_name: Jedox.palo.utils.escHTML(result[i].name)
						}));

					var tmpAttrId = storeDims.getAt(storeDims.find('name', dimName)).get('selectedAttr');
					cmbAttr.setValue(storeAttrs.getAt(tmpAttrId).get('name'));
			},
			searchElem: function(result)
			{
				if (result[0])
					treeMain.selectPaths(result[1]);
				else
					Ext.MessageBox.show({
						title: "Information".localize(),
						msg: "Element not found!".localize(),
						buttons: Ext.Msg.OK,
						icon: Ext.MessageBox.INFO
					});
			},
			getAttributedElems: function(result)
			{
				storeListView.removeAll();
				if (result[1].length > 0)
				{
					for (var i = 0; i < result[1].length; i++)
						storeListView.add(new ElemListRecord({
							id: result[1][i].id,
							name: result[1][i].name,
							type: result[1][i].type,
							attr: result[1][i].attr,
							dim: dimName,
							esc_name: Jedox.palo.utils.escHTML(result[1][i].name)
						}));

					_notEmptyTreeList();
				}
			},
			getPVColRowElems: function(result)
			{
				storeElemList.removeAll();
				for (i = 0; i < result.length; i++)
					storeElemList.add(new ElemListRecord({
						id: result[i][0],
						name: result[i][0],
						type: ((result[i][2] != 'C') ? '' : 'consolidated'),
						attr: result[i][1],
						dim: dimName,
						esc_name: Jedox.palo.utils.escHTML(result[i][0])
					}));
			}
		};

		var paloCbErrorHandlers =
		{
			getServListWithDBs: function() {},
			getDims: function() {},
			getCubeNames: function() {},
			getDimStringAttrs: function() {},
			searchElem: function() {},
			getAttributedElems: function() {},
			getPVColRowElems: function() {}
		};

		var parentPasteView,
			_config = Jedox.palo.config,
			paloRpcServer = new Jedox.backend.rpc.Palo(paloCbSuccessHandlers, paloCbErrorHandlers),
			servId, dbName, preselectedServDb = null, dimName, listView, displayMode, // 0 = tree, 1 = list
			panelMain, panelTopBtns, panelBottomTreeBtns, panelbtnSearch, paneltxtSearch, panelcmbAttr, panelbtnMids, panellistView,
			panelcmbDb, cmbDb2, lblcmbDb2, panelcmbDb2, panelDims, panelbtnSelectBranch, panelbtnSelectAll, panelbtnInvertSelect, panelbtnClearList, panelbtnAsc, panelbtnDesc,
			panelbtnTreeList, panelchbShowHideB, panelcmbCube, panellistOfDims, panelbtnsChooseCubeType,
			dvMain, treeMain, expandMoreLevels, expandAllLevels, treeLevel, syncCounter, treeMaxLevelReached, hasOnlyLeaves, treeMode,
			txtSearch, lblcmbDb, lblList, lblBottomInfo, cmbAttr, cmbDb, btnTreeList, chbShowHideB, chbInsertOtherElems, chbInsertOtherElems2,
			btnTreeControls, btnSearch, btnMids, btnSelectBranch, btnSelectAll, btnInvertSelect, btnPasteVert, btnAsc, btnDesc, btnClearList,
			rbServerDb, rbCubeName, rbDimName, cmbCube, listOfDims, btnsChooseCubeType,
			cmbDbState, showAsTree, editData, editMode, dataMode;

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

		var DimNameRecord = new Ext.data.Record.create([{
			name: 'name'
		}]);
		var storeDimNames = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// Dim store
		var DimRecord = new Ext.data.Record.create([
			{ name: 'name' },
			{ name: 'type' },
			{ name: 'selectedAttr'}
		]);
		var storeDims = new Ext.data.SimpleStore({
			fields: [
				{ name: 'name' },
				{ name: 'type' },
				{ name: 'selectedAttr'}
			]
		});

		var storeListView = new Ext.data.SimpleStore({
			fields: [
				{ name: 'id' },
				{ name: 'name' },
				{ name: 'type' },
				{ name: 'attr' },
				{ name: 'dim' },
				{ name: 'esc_name' }
			]
		});

		// store for Right Element List
		var ElemListRecord = new Ext.data.Record.create([
			{ name: 'id' },
			{ name: 'name' },
			{ name: 'type' },
			{ name: 'attr' },
			{ name: 'dim' },
			{ name: 'esc_name' }
		]);
		var storeElemList = new Ext.data.SimpleStore({
			fields: [
				{ name: 'id' },
				{ name: 'name' },
				{ name: 'type' },
				{ name: 'attr' },
				{ name: 'dim' },
				{ name: 'esc_name' }
			],

			listeners: {
				add: function()
				{
					if (storeElemList.getCount() > 0)
						_showhidePasteButtons(storeElemList.getCount());
					else if (treeMain)
						_showhidePasteButtons(treeMain.getSelectionModel().getSelectedNodes().length);
					else
						_showhidePasteButtons(storeElemList.getCount());
				},

				remove: function()
				{
					if (storeElemList.getCount() > 0)
						_showhidePasteButtons(storeElemList.getCount());
					else if (treeMain)
						_showhidePasteButtons(treeMain.getSelectionModel().getSelectedNodes().length);
					else
						_showhidePasteButtons(storeElemList.getCount());
				},

				clear: function()
				{
					if (!chbInsertOtherElems.getValue())
					{
						if (treeMain)
							_showhidePasteButtons(treeMain.getSelectionModel().getSelectedNodes().length);
						else
							_showhidePasteButtons(storeElemList.getCount());
					}
				}
			}
		});

		// server + database
		var storeServDb = new Ext.data.SimpleStore({
			fields: [
				{ name: 'id' },
				{ name: 'parent_id'	},
				{ name: 'connected'	},
				{ name: 'type' },
				{ name: 'name' },
				{ name: 'rules' }
			]
		});

		// Cube Record & Cube combo store
		var CubeRecord = new Ext.data.Record.create([{
			name: 'name'
		}]);
		var storeCubes = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		this.init = function(conf)
		{
			cmbDbState = -1;
			treeLevel = 0;
			syncCounter = 0;
			showAsTree = true;
			displayMode = 0;
			expandAllLevels = false;
			hasOnlyLeaves = false;
			treeMode = true;
			dataMode = 0;

			editMode = ((conf) ? conf.mode : 0);
			if (editMode == 1) // call from Paste View
			{
				parentPasteView = conf.conf[0];
				servId = conf.conf[1];
				dbName = conf.conf[2];
				dimName = conf.conf[3];
				editData = ((conf.conf[4]) ? conf.conf[4] : []);
			}
			else if (editMode == 2)
			{
				servId = conf.serv_id;
				dbName = conf.db_name;
				dimName = conf.dim_name;

				// Call to get Elements list
				paloRpcServer.getPVColRowElems({
					pv_id: conf.pv_id,
					orient_type: conf.orient_type,
					cr_index: conf.cr_index
				});
			}

			paloRpcServer.getServListWithDBs();

			// *** DATA VIEW *** //
			listView = new Ext.DataView({
				id:'wSelEl_modeller_dv',
				store: storeElemList,
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				multiSelect: true,
				cls: 'modellerDataViewSelect',

				tpl: new Ext.XTemplate(
					'<tpl for=".">',
						'<div class="row-modeller">',
							'<span>&#160;{esc_name}</span>',
						'</div>',
					'</tpl>'
				),

				listeners: {
					click: _singleClickListView,
					dblclick: function(dataView, index, node, e)
					{
						btnMids.up.disable();
						btnMids.left.disable();
						btnMids.down.disable();

						_dblClickListView(dataView, index, node, e);
					}
				}
			});
			panellistView = new Ext.Panel({
				layout:'fit',
				items: [listView]
			});
			// <--- DATA VIEW ---> //

			// *** BUTTONS *** //
			// Tree controling buttons
			btnTreeControls = {
				plusB: new Ext.Button({
					id:'wSelEl_treePlus_btn',
					cls: 'modellerImageButton',
					style: 'vertical-align:bottom;',
					iconCls: 'palo_icon_plus',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 2,
					handler: function()
						{
							treeLevel++;
							_expandTreeToLevel(treeMain.getRootNode(), false);
						}
				}),
				minusB: new Ext.Button({
					id:'wSelEl_treeMinus_btn',
					cls: 'modellerImageButton',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 3,
					style: 'vertical-align:bottom;',
					iconCls: 'palo_icon_minus',
					handler: function()
						{
							if (treeLevel > 0)
							{
								treeLevel--;
								_expandTreeToLevel(treeMain.getRootNode(), false);
							}
						}
				}),
				expandAllB: new Ext.Button({
					id:'wSelEl_treeExp_btn',
					cls: 'modellerImageButton',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 4,
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
					id:'wSelEl_treeCol_btn',
					cls: 'modellerImageButton',
					style: 'vertical-align:bottom;',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 5,
					iconCls: 'palo_icon_colapseall',
					handler: function()
						{
							treeMain.collapseAll();
							treeLevel = 0;
						}
				}),
				oneB: new Ext.Button({
					id:'wSelEl_one_btn',
					text: '1',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 30,
					ctCls: 'modellerButtonWithMargin',
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 0;
							if (treeMain)
								treeMain.getSelectionModel().clearSelections();

							_expandTreeToLevel(treeMain.getRootNode());
						}
					}
				}),
				twoB: new Ext.Button({
					id:'wSelEl_two_btn',
					text: '2',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 31,
					ctCls: 'modellerButtonWithMargin',
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 1;
							if (treeMain)
								treeMain.getSelectionModel().clearSelections();

							_expandTreeToLevel(treeMain.getRootNode());
						}
					}
				}),
				threeB: new Ext.Button({
					id:'wSelEl_three_btn',
					text: '3',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 32,
					ctCls: 'modellerButtonWithMargin',
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 2;
							if (treeMain)
								treeMain.getSelectionModel().clearSelections();

							_expandTreeToLevel(treeMain.getRootNode());
						}
					}
				}),
				fourB: new Ext.Button({
					id:'wSelEl_four_btn',
					text: '4',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 33,
					ctCls: 'modellerButtonWithMargin',
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 3;
							if (treeMain)
								treeMain.getSelectionModel().clearSelections();

							_expandTreeToLevel(treeMain.getRootNode());
						}
					}
				}),
				fiveB: new Ext.Button({
					id:'wSelEl_five_btn',
					text: '5',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 34,
					ctCls: 'modellerButtonWithMargin',
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							treeLevel = 4;
							if (treeMain)
								treeMain.getSelectionModel().clearSelections();

							_expandTreeToLevel(treeMain.getRootNode());
						}
					}
				}),
				branchB: new Ext.Button({
					id:'wSelEl_branchB_btn',
					text: "B".localize(),
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 35,
					ctCls: 'modellerButtonWithMargin',
					cls: 'modellerButtonWithMargin',
					listeners: {
						click: function()
						{
							if (displayMode == 0)
							{
								treeMain.getRootNode().cascade(function(node)
								{
									if (node.parentNode)
									{
										if (node.isLeaf() && node.parentNode.isExpanded())
										{
											if (!node.isSelected())
												treeMain.getSelectionModel().select(node, null, true);
										}
										else if (node.isSelected())
											treeMain.getSelectionModel().unselect(node);
									}
								});
							}
							else if (displayMode == 1)
							{
								dvMain.clearSelections(true);

								for (var i=0; i<storeListView.getCount(); i++)
									if (storeListView.getAt(i).get('type') != 'consolidated')
										dvMain.select(i, true, true);

								if (storeElemList.getCount() == 0)
									_showhidePasteButtons(dvMain.getSelectionCount());
							}
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
						btnTreeControls.threeB, btnTreeControls.fourB, btnTreeControls.fiveB, btnTreeControls.branchB]
			});

			btnSearch = new Ext.Button({
				id:'wSelEl_SearchSelect_btn',
				text: "Search & Select".localize(),
				cls: "seButton1",
				hidden: true,

				listeners: {
					click: function()
					{
						if (txtSearch.getValue() != '')
						{
							if (displayMode == 0)
							{
								var tmpAttrId = storeDims.getAt(storeDims.find('name', dimName)).get('selectedAttr');
								paloRpcServer.searchElem(servId, dbName, dimName, txtSearch.getValue(), ((tmpAttrId == 0) ? null : storeAttrs.getAt(tmpAttrId).get('name')), false);
							}
							else if (displayMode == 1)
							{
								var valToSearch = txtSearch.getValue().replace(/[*]/g, '.*');

								if (valToSearch != txtSearch.getValue())
									valToSearch = new RegExp(valToSearch);

								var tmpIndex = storeListView.find('name', valToSearch);
								if (tmpIndex >= 0)
								{
									dvMain.clearSelections(true);
									do
										dvMain.select(tmpIndex, true, false);
									while( ( tmpIndex = storeListView.find('name', valToSearch, tmpIndex + 1) ) >= 0 )

									var dvSelectedIndexes = dvMain.getSelectedIndexes()
									if (dvSelectedIndexes.length > 0)
										dvMain.getNode(dvSelectedIndexes[dvSelectedIndexes.length - 1]).scrollIntoView(dvMain.body, false);
								}
								else
									Ext.MessageBox.show({
										title: "Error".localize(),
										msg: "Element not found!".localize(),
										buttons: Ext.Msg.OK,
										icon: Ext.MessageBox.ERROR
									});
							}
						}
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

			btnOk = that.components.OK = new Ext.Button({
				id:'wSelEl_sbDlg_btn',
				text: ((editMode) ? "OK".localize() : "Paste".localize()),
				cls: "seButton1",
				tabIndex: 101,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function(){
						if (editMode == 1 || editMode == 2)
						{
							var elems = [];
							if (storeElemList.getCount() > 0)
							{
								// return form storeElemList
								for (var i = 0; i < storeElemList.getCount(); i++)
									elems[i] = [storeElemList.getAt(i).get('id'),
													storeElemList.getAt(i).get('attr'),
													((storeElemList.getAt(i).get('type') == 'consolidated') ? 'C' : '')];
							}
							else if ((displayMode == 0) && (treeMain))
							{
								// return from current selected tree
								var tmpNodes = treeMain.getSelectionModel().getSelectedNodes();
								for (var i = 0; i < tmpNodes.length; i++)
									elems[i] = [tmpNodes[i].attributes.name,
													((cmbAttr.getValue() == "[none]".localize()) ? null : cmbAttr.getValue()),
													((tmpNodes[i].isLeaf()) ? '' : 'C')];
							}
							else if (displayMode == 1)
							{
								// return from current selected data view
								var tmpRecs = dvMain.getSelectedRecords();
								for (var i = 0; i < tmpRecs.length; i++)
									elems[i] = [tmpRecs[i].get('id'), tmpRecs[i].get('attr'), ((tmpRecs[i].get('type') == 'consolidated') ? 'C' : '')];
							}
						}

						if (editMode == 1)
							parentPasteView.setSelectedElements(dimName, elems);
						else if (editMode == 2)
						{
							if (Jedox.wss.app.activePane)
							{
								$confObj = {
									pv_id: conf.pv_id,
									orient_type: conf.orient_type,
									cr_index: conf.cr_index,

									clk_pos: conf.dblclick_data,
									pos: conf.pos,
									elems: elems
								};

								setTimeout(function()
									{
										Jedox.backend.rpc_cb('palo_handlerElemSelectPaloView', [ $confObj ]);
									},
								0);
							}
						}
						else
							_doPasteOnGrid(true);

						that.win.close();
					}
			});

			btnClose = that.components.Cancel = new Ext.Button({
				id:'wSelEl_cancel_btn',
				text: "Cancel".localize(),
				cls: "seButton1",
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 102,
				handler: function(){
						that.win.close();
				}
			});

			// mid Buttons
			btnMids = {
				up: new Ext.Button({
					id:'wSelEl_up_btn',
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 10,
					cls: 'modellerImageButton',
					style: 'margin-top: 2px; margin-bottom: 2px;',
					iconCls: 'palo_icon_up',
					handler: _upBtnHandler
				}),
				right: new Ext.Button({
					id:'wSelEl_right_btn',
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 11,
					cls: 'modellerImageButton',
					style: 'margin-top: 2px; margin-bottom: 2px;',
					iconCls: 'palo_icon_right',
					handler: _rightBtnHandler
				}),
				left: new Ext.Button({
					id:'wSelEl_left_btn',
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 12,
					cls: 'modellerImageButton',
					style: 'margin-top: 2px; margin-bottom: 2px;',
					iconCls: 'palo_icon_left',
					handler: _leftBtnHandler
				}),
				down: new Ext.Button({
					id:'wSelEl_down_btn',
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 13,
					cls: 'modellerImageButton',
					style: 'margin-top: 2px; margin-bottom: 2px;',
					iconCls: 'palo_icon_down',
					handler: _downBtnHandler
				})
			};
			// mid Panel
			panelbtnMids = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent; vertical-align: middle;',
				layout: 'form',
				width: 31,
				autoHeight: true,
				items: [btnMids.up,
						btnMids.right,
						btnMids.left,
						btnMids.down]
			});

			// Select Branch
			btnSelectBranch = new Ext.Button({
				id:'wSelEl_selectBranch_btn',
				text: "Select Branch".localize(),
				cls: "seButton1",
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 27,
				listeners: {
					click: function()
					{
						var tmpNodes = treeMain.getSelectionModel().getSelectedNodes();
						for (var i=0; i<tmpNodes.length; i++)
							_selectSubNodes(tmpNodes[i]);
					}
				}
			});
			panelbtnSelectBranch = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [btnSelectBranch]
			});

			// Select All button
			btnSelectAll = new Ext.Button({
				id:'wSelEl_selectAll_btn',
				text: "Select All".localize(),
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 26,
				cls: "seButton1",
				listeners: {
					click: function() {
						if (displayMode == 0)
						{
							var treeSellModel = treeMain.getSelectionModel(),
								tmp_onSelectedChange;

							treeSellModel.suspendEvents();

							treeSellModel.clearSelections();
							treeMain.getRootNode().cascade(function(node)
							{
								if (node.parentNode && !node.isSelected())
								{
									if (node.parentNode.isExpanded())
									{
										tmp_onSelectedChange = node.ui.onSelectedChange;
										node.ui.onSelectedChange = _tree_onSelectedChange_WithoutFocus;
										treeSellModel.select(node, null, true);
										node.ui.onSelectedChange = tmp_onSelectedChange;
									}
									else
										return false;
								}
							});

							treeSellModel.suspendEvents();

							// Need to trigger
							_treeOnSelectionChange(treeSellModel, treeSellModel.getSelectedNodes());
						}
						else if (displayMode == 1)
							dvMain.selectRange(0, storeListView.getCount() - 1);
					}
				}
			});
			panelbtnSelectAll = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [btnSelectAll]
			});

			// Invert Select button
			btnInvertSelect = new Ext.Button({
				id:'wSelEl_invertSel_btn',
				text: "Invert Select".localize(),
				cls: "seButton1",
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 28,
				hidden: true,
				listeners: {
					click: function()
					{
						if (displayMode == 0)
						{
							treeMain.getRootNode().cascade(function(node)
							{
								if (node.parentNode)
								{
									if (!node.isSelected() && node.parentNode.isExpanded())
										treeMain.getSelectionModel().select(node, null, true);
									else if (node.isSelected())
										treeMain.getSelectionModel().unselect(node);
								}
							});
						}
						else if (displayMode == 1)
						{
							for (var i=0; i<storeListView.getCount(); i++)
							{
								if (!dvMain.isSelected(i))
									dvMain.select(i, true, true);
								else
									dvMain.deselect(i);
							}

							if (storeElemList.getCount() == 0)
								_showhidePasteButtons(dvMain.getSelectionCount());
						}
					}
				}
			});
			panelbtnInvertSelect = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [btnInvertSelect]
			});

			// Paste Verticaly button
			btnPasteVert = that.components.Apply = new Ext.Button({
				id:'wSelEl_pasteV_btn',
				text: "Paste Vertically".localize(),
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 100,
				cls: "seButton1",
				hidden: true,
				listeners: {
					click: function()
					{
						_doPasteOnGrid(false);
						that.win.close();
					}
				}
			});

			// Ascending button
			btnAsc = new Ext.Button({
				id:'wSelEl_Ascending_btn',
				text: "Ascending".localize(),
				cls: "seButton1",
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 20,
				listeners: {
					click: function()
					{
						storeElemList.sort('name');
					}
				}
			});
			panelbtnAsc = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [btnAsc]
			});

			// Descending button
			btnDesc = new Ext.Button({
				id:'wSelEl_descending_btn',
				text: "Descending".localize(),
				cls: "seButton1",
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 21,
				listeners: {
					click: function()
					{
						storeElemList.sort('name', 'DESC');
					}
				}
			});
			panelbtnDesc = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [btnDesc]
			});

			// Clear List button
			btnClearList = new Ext.Button({
				id:'wSelEl_clearList_btn',
				text: "Clear list".localize(),
				cls: "seButton1",
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 22,
				listeners: {
					click: function()
					{
						storeElemList.removeAll();
					}
				}
			});
			panelbtnClearList = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [btnClearList]
			});
			// <--- BUTTONS ---> //

			// *** ComboBoxes, Text fields, label and check boxes *** //
			lblcmbDb = new Ext.form.MiscField({
				value: "Choose Server/Database".localize() + ':',
				height: 22,
				bodyStyle: 'background-color: transparent;',
				hideLabel: true
			});
			cmbDb = new Ext.form.ComboBox({
				id:'wSelEl_server_cmb',
				disabled: editMode,
				store: storeServDb,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 1,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				tpl: new Ext.XTemplate('<tpl for=".">', '<div class="x-combo-list-item">', '<tpl if="type == \'database\'">', '<span style="cursor: default;">&#160;&#160;&#160;{name}</span>', '</tpl>', '<tpl if="type == \'server\'">', '<span style="cursor: default;">{name}</span>', '</tpl>', '</div>', '</tpl>'),
				listeners: {
					select: _cmbDbSelectionHandler
				},
				valueField: 'id',
				displayField: 'name'
			});
			// panel for Combo Box
			panelcmbDb = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [cmbDb]
			});

			/* *** */

			lblcmbDb2 = new Ext.form.MiscField({
				value: "Choose Server/Database".localize() + ':',
				height: 22,
				bodyStyle: 'background-color: transparent;',
				hideLabel: true
			});
			cmbDb2 = new Ext.form.ComboBox({
				id:'wSelEl_server2_cmb',
				store: storeServDb,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 1,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				width: 164,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				tpl: new Ext.XTemplate('<tpl for=".">', '<div class="x-combo-list-item">', '<tpl if="type == \'database\'">', '<span style="cursor: default;">&#160;&#160;&#160;{name}</span>', '</tpl>', '<tpl if="type == \'server\'">', '<span style="cursor: default;">{name}</span>', '</tpl>', '</div>', '</tpl>'),
				listeners: {
					select: _cmbDbSelectionHandler
				},
				valueField: 'id',
				displayField: 'name'
			});
			// panel for Combo Box
			panelcmbDb2 = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				width: 164,
				autoHeight: true,
				items: [cmbDb2]
			});

			/**********************************/

			cmbAttr = new Ext.form.ComboBox({
				id:'wSelEl_attr_cmb',
				store: storeAttrs,
				bodyStyle: 'background-color: transparent;',
				width: 150,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 9,
				typeAhead: false,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				listeners: {
					select: function(combo, record, index)
					{
						var tmpAttrId = storeDims.getAt(storeDims.find('name', dimName)).get('selectedAttr');
						if (index != tmpAttrId)
						{
							if (displayMode == 0)
							{
								treeMain.getLoader().dataUrl = '/be/erpc.php?wam=' + Jedox.wss.app.appModeS +
									'&c=palo&m=getTreeNodes&servId=' + servId + '&dbName=' + dbName + ( (index != 0) ? '&attr=' + record.get('name') : '' );

								treeMain.getRootNode().reload();
								storeDims.getAt(storeDims.find('name', dimName)).set('selectedAttr', index);
							}
							else if (displayMode == 1)
							{
								paloRpcServer.getAttributedElems(servId, dbName, dimName, ((cmbAttr.getValue() == "[none]".localize()) ? null : cmbAttr.getValue()), 0, _config.numberOfElements * 5);
								storeDims.getAt(storeDims.find('name', dimName)).set('selectedAttr', index);
							}
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
				autoHeight: true,
				items: [cmbAttr]
			});

			txtSearch = new Ext.form.TextField({
				id:'wSelEl_searchFld_fld',
				hideLabel: true,
				hidden: true,
				width: 250
			});
			paneltxtSearch = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				width: 250,
				autoHeight: true,
				items: [txtSearch]
			});

			lblList = new Ext.form.MiscField({
				value: "Pick list".localize() + ':',
				height: 22,
				bodyStyle: 'background-color: transparent;',
				hideLabel: true
			});

			btnTreeList = new Ext.Button({
				id:'wSelEl_showHR_btn',
				cls: 'modellerImageButton',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 6,
				style: 'vertical-align:bottom;',
				iconCls: 'palo_icon_showHR',
				handler: function()
					{
						treeMode = (treeMode) ? false : true;
						if (treeMode)
						{
							this.setIconClass('palo_icon_showHR');
							displayMode = 0;

							var tmpNum = panelDims.items.length;
							for (var i=0; i<tmpNum; i++)
							{
								var tmpTreeP = _makeTreePanel(panelDims.getComponent(i).title, i);
								var tmpRec = storeDims.getAt(storeDims.find('name', panelDims.getComponent(i).title));
								var tmpCount = storeListView.getCount();
								tmpRec.set('type', 'tree');

								panelDims.getComponent(i).add(tmpTreeP);
								panelDims.getComponent(i).remove(panelDims.getComponent(i).getComponent(0));

								if (dimName == panelDims.getComponent(i).title)
								{
									treeMain = tmpTreeP;
									if (tmpCount > 0)
										_notEmptyTreeList();
								}
							}

							if (storeElemList.getCount() == 0)
								_showhidePasteButtons(0);

							panelDims.doLayout();
						}
						else
						{
							this.setIconClass('palo_icon_showHRflat');
							displayMode = 1;

							var tmpNum = panelDims.items.length;
							for (var i=0; i<tmpNum; i++)
							{
								var tmpDv = _makeDataView();

								var tmpRec = storeDims.getAt(storeDims.find('name', panelDims.getComponent(i).title));
								tmpRec.set('type', 'list');

								panelDims.getComponent(i).add(tmpDv);
								panelDims.getComponent(i).remove(panelDims.getComponent(i).getComponent(0));

								if (dimName == panelDims.getComponent(i).title)
									dvMain = tmpDv;
							}

							paloRpcServer.getAttributedElems(servId, dbName, dimName, ((cmbAttr.getValue() == "[none]".localize()) ? null : cmbAttr.getValue()), 0, _config.numberOfElements * 5);
							_emptyTreeList();
							panelDims.doLayout();
						}
					}
			});

			// panel for Check box
			panelbtnTreeList = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,

				items: [btnTreeList]
			});

			// label at bottom window
			lblBottomInfo = new Ext.form.MiscField({
				value: "_msg: se_Tip".localize(),
				height: 22,
				bodyStyle: 'background-color: transparent;',
				hideLabel: true,
				hidden: true
			});

			// Show/Hide Selection tools .. Check Box
			chbShowHideB = new Ext.form.Checkbox({
				id:'wSelEl_showAllSel_chk',
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 25,
				boxLabel: "Show all selection tools".localize(),
				listeners: {
					check: function(checkBox, checked)
					{
						if (checked)
						{
							btnInvertSelect.show();
							txtSearch.show();
							btnSearch.show();
							lblBottomInfo.show();
						}
						else
						{
							btnInvertSelect.hide();
							txtSearch.hide();
							btnSearch.hide();
							lblBottomInfo.hide();
						}

						_resizeAll();
					}
				}
			});
			// panel for Show/Hide Selection tools .. Check Box
			panelchbShowHideB = new Ext.Panel(
			{
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbShowHideB]
			});
			// <--- ComboBoxes, Lables, Text fields and check boxes  ---> //

			// +++ PASTE OTHER ELEMENTS +++ //
			chbInsertOtherElems = new Ext.form.Checkbox({
				id:'wSelEl_insertDBEl_chk',
				hidden: editMode,
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 19,
				boxLabel: "insert database elements".localize(),
				listeners: {
					check: function(checkBox, checked)
					{
						if (checked)
						{
							panelMain.layout.setActiveItem(1);
							that.containers.activePanel = panelMain.layout.activeItem;
							chbInsertOtherElems2.setValue(true);

							if (rbDimName.getValue())
								_showhidePasteButtons(listOfDims.getSelectedIndexes().length);
							else
								_showhidePasteButtons(1);
						}
						else
						{
							panelMain.layout.setActiveItem(0);
							that.containers.activePanel = panelMain.layout.activeItem;

							if ((displayMode == 0) && treeMain)
								_showhidePasteButtons(treeMain.getSelectionModel().getSelectedNodes().length);
							else if (displayMode == 1)
								_showhidePasteButtons(dvMain.getSelectedIndexes().length);
						}
					}
				}
			});

			chbInsertOtherElems2 = new Ext.form.Checkbox({
				id:'wSelEl_insertDBEl2_chk',
				hidden: editMode,
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 19,
				checked: true,
				boxLabel: "insert database elements".localize(),
				listeners: {
					check: function(checkBox, checked)
					{
						if (checked)
						{
							panelMain.layout.setActiveItem(1);
							that.containers.activePanel = panelMain.layout.activeItem;

							if (rbDimName.getValue())
								_showhidePasteButtons(listOfDims.getSelectedIndexes().length);
							else
								_showhidePasteButtons(1);
						}
						else
						{
							panelMain.layout.setActiveItem(0);
							that.containers.activePanel = panelMain.layout.activeItem;
							chbInsertOtherElems.setValue(false);

							if ((displayMode == 0) && treeMain)
								_showhidePasteButtons(treeMain.getSelectionModel().getSelectedNodes().length);
							else if (displayMode == 1)
								_showhidePasteButtons(dvMain.getSelectedIndexes().length);
						}
					}
				}
			});

			// Radio Buttons for Paste Other Elements
			rbServerDb = new Ext.form.Radio({
				id:'wSelEl_insServer_rd',
				name: 'pasteOtherElems',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 50,
				boxLabel: "insert server/database (connection)".localize(),
				hideLabel: true,
				checked: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_showhidePasteButtons(1);
					}
				}
			});
			rbCubeName = new Ext.form.Radio({
				id:'wSelEl_insCube_rd',
				name: 'pasteOtherElems',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 51,
				boxLabel: "insert cube name".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_showhidePasteButtons((cmbCube.getValue() ? 1 : 0));
					}
				}
			});
			rbDimName = new Ext.form.Radio({
				id:'wSelEl_insDim_rd',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 56,
				name: 'pasteOtherElems',
				boxLabel: "insert dimension names".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_showhidePasteButtons(listOfDims.getSelectedIndexes().length);
					}
				}
			});

			// Cube combobox
			cmbCube = new Ext.form.ComboBox({
				store: storeCubes,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 52,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'name',
				displayField: 'name',
				listeners: {
					select: function()
					{
						_setOtherElemsRadios(2);
						_showhidePasteButtons(1);
					}
				}
			});
			panelcmbCube = new Ext.Panel({
				border: false,
				hideMode: 'offsets',
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoHeight: true,
				items: [cmbCube]
			});

			// Image Buttons for Choose of Cube types
			btnsChooseCubeType = {
				metaDataB: new Ext.Button({
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 53,
					iconCls: 'icon_palo_cube',
					cls: 'modellerImageButton',
					handler: function()
					{
						_setDataMode(0);
						paloRpcServer.getCubeNames(servId, dbName, dataMode);
					}
				}),

				attribsB: new Ext.Button({
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 54,
					iconCls: 'icon_palo_table',
					cls: 'modellerImageButton',
					handler: function()
					{
						_setDataMode(2);
						paloRpcServer.getCubeNames(servId, dbName, dataMode);
					}
				}),

				usersB: new Ext.Button({
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 55,
					iconCls: 'icon_palo_user',
					cls: 'modellerImageButton',
					handler: function()
					{
						_setDataMode(1);
						paloRpcServer.getCubeNames(servId, dbName, dataMode);
					}
				})
			};
			panelbtnsChooseCubeType = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent; vertical-align: middle;',
				layout: 'table',
				width: 85,
				height: 40,
				autoHeight: true,
				items: [btnsChooseCubeType.metaDataB, btnsChooseCubeType.attribsB, btnsChooseCubeType.usersB]
			});


			// List of Dimensions
			listOfDims = new Ext.DataView({
				id:'wSelEl_modellerL_dv',
				store: storeDimNames,
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				multiSelect: true,
				cls: 'modellerDataViewSelect',
				tpl: new Ext.XTemplate(
					'<tpl for=".">',
						'<div class="row-modeller">',
							'<span>&#160;{name}</span>',
						'</div>',
					'</tpl>'
				),
				listeners: {
					selectionchange: function(thisDv, selections) {
						rbDimName.setValue(true);
						_setOtherElemsRadios(3);
						_showhidePasteButtons(selections.length);
					}
				}
			});
			panellistOfDims = new Ext.Panel({
				layout:'fit',
				items: [listOfDims]
			});
			// --- PASTE OTHER ELEMENTS --- //

			// *** Panel for Dims *** //
			panelDims = new Ext.Panel({
				id: 'se_panelDims',
				layout:'accordion',
				autoScroll: true
			});
			// <--- Panel for Dims ---> //

			// *** MAIN panel and Window *** //
			panelMain = new Ext.Panel({
				id: 'se_mainPanel',
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'card',
				activeItem: 0,
				monitorResize: true,
				listeners: {
					resize: _resizeAll
				},
				items: [
			        new Ext.Panel({
						layout: 'absolute',
						anchor: '100% 100%',
						monitorResize: true,
						baseCls: 'x-plain',
						items: [
							panelTopBtns, panelDims, panelBottomTreeBtns, panelbtnSearch,
							panelcmbAttr, paneltxtSearch, panelbtnMids, panellistView, lblcmbDb, panelcmbDb, lblList,
							panelbtnSelectBranch, panelbtnInvertSelect, panelbtnSelectAll,
							panelbtnClearList, panelbtnAsc, panelbtnDesc, panelbtnTreeList, lblBottomInfo, panelchbShowHideB, chbInsertOtherElems
						]
					}),
					new Ext.Panel({
						layout: 'absolute',
						anchor: '100% 100%',
						monitorResize: true,
						baseCls: 'x-plain',
						items: [
							lblcmbDb2, panelcmbDb2, rbServerDb, rbCubeName, rbDimName, panelcmbCube, panellistOfDims, panelbtnsChooseCubeType, chbInsertOtherElems2
						]
					})
				]
			});

			// Wizard Window
			that.win = new Ext.Window({
				id: 'selectelementsWizardWindow',
				layout: 'fit',
				title: ((editMode) ? "Select Elements".localize() : "Paste Elements".localize()),
				width: 750,
				height: 540,
				minWidth: 750,
				minHeight: 540,
				closeAction: 'close',
				cls: 'default-format-window',
				autoDestroy: true,
				plain: true,
				modal: true,
				onEsc: Ext.emptyFn,
				resizable: true,
				buttons: [btnPasteVert, btnOk, btnClose],
				listeners: {
					activate: function() {_resizeAll(); that.activate();},
					close: function()
					{
						if (displayMode == 0)
							treeMain.getSelectionModel().un('selectionchange', _treeOnSelectionChange);

						if (!parentPasteView)
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							setTimeout(function(){
								paloRpcServer.setPreselectServDb(servId, dbName); // set preselected server/db
							},0);
						}
						that.close();
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.selectElements);
					},
					show: function()
					{
						setTimeout(function(){
//							that.initFocus(true, 100);
						});
					}
				},
				items: [panelMain]
			});
			// <--- MAIN panel and Window ---> //
			that.containers.activePanel = panelMain.items.items[0];
			that.setContext();
		}

		// *** PUBLIC functions *** //
		this.show = function()
		{
			if (that.win)
			{
				btnOk.disable();

				if (!parentPasteView)
				{
					Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
					Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
				}

				that.win.show();

				storeAttrs.add(new AttrRecord({
					name: "[none]".localize(),
					esc_name: "[none]".localize()
				}));
				cmbAttr.setValue("[none]".localize());

				if (editMode == 1)
				{
					// TODO: For attributed names (Names should be updated for elements if they have attribute)
					for (i=0; i<editData.length; i++)
						storeElemList.add(new ElemListRecord({
							id: editData[i][0],
							name: editData[i][0],
							type: ((editData[i][2] != 'C') ? '' : 'consolidated'),
							attr: editData[i][1],
							dim: dimName,
							esc_name: Jedox.palo.utils.escHTML(editData[i][0])
						}));
				}
			}
		}
		// <--- PUBLIC functions ---> //

		// *** EVENT HANLDERS *** //
		var _tree_onSelectedChange_WithoutFocus = function(state)
		{
			this.addClass("x-tree-selected");
		}

		var _cmbDbSelectionHandler = function(combo, record, index)
		{
			if (chbInsertOtherElems.getValue())
			{
				listOfDims.clearSelections();
				_setOtherElemsRadios(1);
				_showhidePasteButtons(1);
			}

			if (cmbDbState != index)
			{
				cmbDbState = index;
				storeAttrs.removeAll();
				storeAttrs.add(new AttrRecord({
					name: "[none]".localize(),
					esc_name: "[none]".localize()
				}));
				cmbAttr.setValue("[none]".localize());
				if (record.get('type') == 'database')
				{
					servId = record.get('parent_id');
					dbName = record.get('name');

					if (editMode)
						_addDimPanel(dimName, true, 0);
					else
					{
						_setDataMode(dataMode);

						// Batch call
						(new Jedox.backend.RPCAsyncBatch(
								true,
								(new Jedox.backend.RPCAsyncRqst('palo', 'getDims', [servId, dbName, 0])).setOnSuccess([paloCbSuccessHandlers, paloCbSuccessHandlers.getDims]).setOnError([paloCbErrorHandlers, paloCbErrorHandlers.getDims]),
								(new Jedox.backend.RPCAsyncRqst('palo', 'getCubeNames', [servId, dbName, dataMode])).setOnSuccess([paloCbSuccessHandlers, paloCbSuccessHandlers.getCubeNames]).setOnError([paloCbErrorHandlers, paloCbErrorHandlers.getCubeNames])
							)).setFlags(1).send();
					}

				}
				else if (record.get('type') == 'server')
					for (var i=(panelDims.items.length-1); i>=0; i--)
						panelDims.remove(panelDims.getComponent(i));

				if (storeElemList.getCount() > 0 && editMode == 1 && editData.length == 0)
					storeElemList.removeAll();

				_emptyTreeList();
			}
			cmbDb.setValue(record.data.name);
			cmbDb2.setValue(record.data.name);
		}

		var _upBtnHandler = function()
		{
			var tmpElem;
			var tmpSelectedIds = listView.getSelectedIndexes();
			for (var i=1; i<storeElemList.getCount(); i++)
			{
				if (listView.isSelected(listView.getNode(i)))
				{
					if (!listView.isSelected(listView.getNode(i - 1)))
					{
						tmpElem = storeElemList.getAt(i);
						storeElemList.remove(tmpElem);
						storeElemList.insert(i-1, tmpElem);

						for (var j=0; j<tmpSelectedIds.length; j++)
							if (tmpSelectedIds[j] == i)
							{
								tmpSelectedIds[j] = i-1;
								break;
							}

						listView.select(tmpSelectedIds);
					}
				}
			}
		}

		var _rightBtnHandler = function()
		{
			if (displayMode == 0)
			{
				var nodeList = treeMain.getSelectionModel().getSelectedNodes();
				_sortSelectedNodesNodes(nodeList);

				for (var i=0, nodesLen=nodeList.length; i<nodesLen; i++)
					storeElemList.add(new ElemListRecord({
						id: nodeList[i].attributes.name,
						name: nodeList[i].text,
						type: ((nodeList[i].isLeaf()) ? '' : 'consolidated'),
						attr: ((cmbAttr.getValue() == "[none]".localize()) ? null : cmbAttr.getValue()),
						dim: dimName,
						esc_name: nodeList[i].text
					}));
			}
			else if (displayMode == 1)
			{
				var tmpIndexes = dvMain.getSelectedIndexes()
					, indexesLen = tmpIndexes.length
					, tmpIndex
					, i
					, j;

				for (i=0; i<indexesLen-1; i++)
					for (j=indexesLen-1; j>i; j--)
						if (tmpIndexes[j-1] > tmpIndexes[j])
						{
							tmpIndex = tmpIndexes[j-1];
							tmpIndexes[j-1] = tmpIndexes[j];
							tmpIndexes[j] = tmpIndex;
						}

				for (i=0; i<indexesLen; i++)
					_dblClickListViewHandler(dvMain, tmpIndexes[i], dvMain.getNode(tmpIndexes[i]), null);
			}
		}

		var _leftBtnHandler = function()
		{
			btnMids.up.disable();
			btnMids.left.disable();
			btnMids.down.disable();

			var tmpElems = listView.getSelectedRecords();
			for (var i=0; i<tmpElems.length; i++)
				storeElemList.remove(tmpElems[i]);
		}

		var _downBtnHandler = function()
		{
			var tmpElem;
			var tmpSelectedIds = listView.getSelectedIndexes();
			for (var i=(storeElemList.getCount() - 2); i>=0; i--)
			{
				if (listView.isSelected(listView.getNode(i)))
				{
					if (!listView.isSelected(listView.getNode(i + 1)))
					{
						tmpElem = storeElemList.getAt(i);
						storeElemList.remove(tmpElem);
						storeElemList.insert(i+1, tmpElem);

						for (var j=0; j<tmpSelectedIds.length; j++)
							if (tmpSelectedIds[j] == i)
							{
								tmpSelectedIds[j] = i+1;
								break;
							}

						listView.select(tmpSelectedIds);
					}
				}
			}
		}

		var _singleClickListView = function(dataView, index, record, e)
		{
			// set Mid buttons
			btnMids.up.enable();
			btnMids.left.enable();
			btnMids.down.enable();
		}

		var _dblClickListView = function(dataView, index, node, e)
		{
			storeElemList.remove(storeElemList.getAt(index));
		}

		var _dblClickListViewHandler = function(dataView, index, node, evnt)
		{
			var tmpRec = storeListView.getAt(index);
			storeElemList.add(new ElemListRecord({
				id: tmpRec.get('id'),
				name: tmpRec.get('name'),
				type: tmpRec.get('type'),
				attr: tmpRec.get('attr'),
				dim: dimName,
				esc_name: tmpRec.get('esc_name')
			}));
		}
		// <--- EVENT HANDLERS ---> //

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
		var _expandTreeToLevel = function(node, withSelecting)
		{
			withSelecting = (withSelecting == undefined) ? true : withSelecting;

			expandMoreLevels = true;
			_doExpandigTreeToLevel(node, withSelecting);
			if ((treeLevel > (treeMaxLevelReached)) && (syncCounter == 0))
				treeLevel = treeMaxLevelReached;

			if (syncCounter == 0)
				expandMoreLevels = false;
		}

		var _doExpandigTreeToLevel = function(node, withSelecting)
		{
			if (node.getDepth() > treeMaxLevelReached)
			{
				if ((node.childNodes.length == 0) && ((node.getDepth() - 1) >= treeMaxLevelReached))
					treeMaxLevelReached = node.getDepth() - 1;
				else
					treeMaxLevelReached = node.getDepth();
			}

			if (node.getDepth() == treeLevel)
			{
				node.collapseChildNodes(true);

				if (withSelecting && treeMain)
					for (var i=(node.childNodes.length - 1); i>=0; i--)
						treeMain.getSelectionModel().select(node.childNodes[i], null, true);
			}
			else if (node.childNodes.length > 0)
			{
				for (var i=(node.childNodes.length - 1); i>=0; i--)
					if (node.childNodes[i].getDepth() <= treeLevel)
					{
						node.childNodes[i].expand();
						_doExpandigTreeToLevel(node.childNodes[i], withSelecting);
					}
			}
		}

		var _removeAllDimsFromPanel = function(panel)
		{
			storeDims.removeAll();
			for (var i=(panel.items.length - 1); i>=0; i--)
				panel.remove(panel.getComponent(i));
		}

		var _addDimPanel = function(pName, inExpand, index)
		{
			var tmpPan = new Ext.Panel({
				title: pName,
				border: false,
				collapsed: true,
				draggable: false,
				autoHeight: true,
				animCollapse: false,
				listeners: {
					expand: function(p)
					{
						if (dimName != p.title)
							storeElemList.removeAll();

						dimName = p.title;

						if (displayMode == 0)
						{
							treeLevel = 0;
							syncCounter = 0;
							treeMaxLevelReached = 0;

							if (treeMain)
								treeMain.getSelectionModel().clearSelections();

							treeMain = p.getComponent(0);
							if (treeMain.getRootNode().childNodes.length > 0)
							{
								_notEmptyTreeList();
								paloRpcServer.getDimStringAttrs(servId, dbName, dimName); // fill Attr combo box
							}
							else
								p.collapse();
						}
						else if (displayMode == 1)
						{
							storeListView.removeAll();
							(new Jedox.backend.RPCAsyncBatch(
								true,
								(new Jedox.backend.RPCAsyncRqst('palo_misc', 'getDimStringAttrs', [servId, dbName, dimName])).setOnSuccess([paloCbSuccessHandlers, paloCbSuccessHandlers.getDimStringAttrs]).setOnError([paloCbErrorHandlers, paloCbErrorHandlers.getDimStringAttrs]),
								(new Jedox.backend.RPCAsyncRqst('palo_misc', 'getAttributedElems', [servId, dbName, dimName, null, 0, _config.numberOfElements * 5])).setOnSuccess([paloCbSuccessHandlers, paloCbSuccessHandlers.getAttributedElems]).setOnError([paloCbErrorHandlers, paloCbErrorHandlers.getAttributedElems])
							)).setFlags(1).send();
							dvMain = p.getComponent(0);
						}
						btnMids.right.disable();
					},

					collapse: function(p)
					{
						_emptyTreeList();
						btnMids.right.disable();
					}
				}
			});

			if (displayMode == 0)
			{
				tmpPan.add(_makeTreePanel(pName, index, tmpPan));
				panelDims.add(tmpPan);
				storeDims.add(new DimRecord({
					name: pName,
					type: 'tree',
					selectedAttr: 0
				}));
			}
			else
			{
				var tmpDv = _makeDataView();
				tmpPan.add(tmpDv);
				panelDims.add(tmpPan);
				storeDims.add(new DimRecord({
					name: pName,
					type: 'list',
					selectedAttr: 0
				}));
			}

			panelDims.doLayout();
			if (inExpand)
				tmpPan.expand();
		}

		var _makeDataView = function()
		{
			var tmpDv = new Ext.DataView({
				id:'wSelEl_modellerX_dv',
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				multiSelect: true,
				store: storeListView,
				cls: 'modellerDataViewSelect',

				tpl: new Ext.XTemplate(
						'<tpl for=".">',
						'<div class="row-modeller">',
						'<tpl if="type == \'string\'">',
							'<img class="palo_selelem_string" src="../lib/ext/resources/images/default/s.gif" width="16" height="16"/>',
						'</tpl>',
						'<tpl if="type == \'numeric\'">',
							'<img class="palo_selelem_numeric" src="../lib/ext/resources/images/default/s.gif"/ width="16" height="16">',
						'</tpl>',
						'<tpl if="type == \'consolidated\'">',
							'<img class="palo_selelem_consolidated" src="../lib/ext/resources/images/default/s.gif"/ width="16" height="16">',
						'</tpl>',
						'<span>&#160;{esc_name}</span>',
						'</div>',
					'</tpl>'
				),

				listeners: {
					dblclick: function(dataView, index, node, e)
					{
						_dblClickListViewHandler(dataView, index, node, e);
					},
					contextmenu: function(dataView, index, node, e)
					{
						e.stopEvent();
					},

					selectionchange: function(dataView, indexes)
					{
						if (indexes.length > 0)
							btnMids.right.enable();
						else
							btnMids.right.disable();

						if (storeElemList.getCount() == 0)
							_showhidePasteButtons(indexes.length);
					}
				}
			});

			return tmpDv;
		}

		var _makeTreePanel = function(dimensionName, index, inPanel)
		{
			var tree = new Ext.tree.TreePanel({
				id:'wSelEl_tree_'.concat(index, '_tr'),
				cls: 'x-tree-noicon',
				border: false,
				autoScroll: false,
				animate: false,
				enableDD: false,
				containerScroll: true,
				rootVisible: false,
				selModel: new Ext.tree.MultiSelectionModel(),
				plugins: new Ext.ux.tree.TreeNodeMouseoverPlugin(),
				loader: new Ext.ux.tree.PagingTreeLoader({
					pagingModel: 'local',
					baseParams: {name: 'root'},
					dataUrl: '/be/erpc.php?wam=' + Jedox.wss.app.appModeS + '&c=palo&m=getTreeNodes&servId=' + servId +
							'&dbName=' + dbName + ((cmbAttr.getValue() == "[none]".localize()) ? '' : '&attr=' + cmbAttr.getValue()),
					listeners: {
						beforeload: function(thisL, node, cb)
						{
							this.baseParams.name = node.attributes.name;
							this.baseParams.dimName = dimensionName;

							if (expandMoreLevels || expandAllLevels)
							{
								if (!hasOnlyLeaves)
									hasOnlyLeaves = true;

								syncCounter++;
							}
						},
						load: function(thisS, node, response)
						{
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
						}
					}
				}),
				listeners: {
					dblclick: function(node)
					{
						storeElemList.add(new ElemListRecord({
							id: node.attributes.name,
							name: node.text,
							type: ((node.isLeaf()) ? '' : 'consolidated'),
							attr: ((cmbAttr.getValue() == "[none]".localize()) ? null : cmbAttr.getValue()),
							dim: dimName,
							esc_name: node.text
						}));
					},
					expandnode: function(node)
					{
						treeLevel = node.getDepth();
					},
					collapsenode: function(node)
					{
						node.eachChild(function(chNode)
						{
							if (chNode.isSelected())
								chNode.unselect();
						});
					},
					append: function(thisT, parNode, node, index)
					{
						node.text = Jedox.palo.utils.escHTML(node.text);
					}
				},
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

			var root = new Ext.tree.AsyncTreeNode({
				text: 'Root',
				draggable: false,
				id: 'root',
				name: 'root',
				listeners: {
					load: function(tmp)
					{
						if (inPanel)
							inPanel.expand();
					}
				}
			});
			tree.setRootNode(root);
			tree.getSelectionModel().on('selectionchange', _treeOnSelectionChange);

			return tree;
		}

		var _treeOnSelectionChange = function(thisM, nodes)
		{
			if (nodes.length > 0)
				btnMids.right.enable();
			else
				btnMids.right.disable();

			if (storeElemList.getCount() == 0)
				_showhidePasteButtons(nodes.length);
		}

		var _showhidePasteButtons = function(num)
		{
			if ((num > 1) && (!editMode))
			{
				btnOk.enable();
				btnOk.setText("Paste horizontaly".localize());
				btnPasteVert.show();
			}
			else if ((num == 1) || ((num > 1) && (editMode)))
			{
				btnOk.enable();
				btnOk.setText((editMode) ? "OK".localize() : "Paste".localize());
				btnPasteVert.hide();
			}
			else
			{
				btnOk.disable();
				btnOk.setText((editMode) ? "OK".localize() : "Paste".localize());
				btnPasteVert.hide();
			}
		}

		var _emptyTreeList = function()
		{
			btnTreeControls.minusB.disable();
			btnTreeControls.plusB.disable();
			btnTreeControls.expandAllB.disable();
			btnTreeControls.collapseAllB.disable();

			btnTreeControls.oneB.disable();
			btnTreeControls.twoB.disable();
			btnTreeControls.threeB.disable();
			btnTreeControls.fourB.disable();
			btnTreeControls.fiveB.disable();
			btnTreeControls.branchB.disable();

			btnSearch.disable();
			btnSelectAll.disable();
			btnSelectBranch.disable();
			btnInvertSelect.disable();

			txtSearch.disable();
			cmbAttr.disable();
			btnTreeList.disable();
		}

		var _notEmptyTreeList = function()
		{
			if (displayMode == 0)
			{
				btnTreeControls.minusB.enable();
				btnTreeControls.plusB.enable();
				btnTreeControls.expandAllB.enable();
				btnTreeControls.collapseAllB.enable();

				btnTreeControls.oneB.enable();
				btnTreeControls.twoB.enable();
				btnTreeControls.threeB.enable();
				btnTreeControls.fourB.enable();
				btnTreeControls.fiveB.enable();

				btnSelectBranch.enable();
			}

			btnTreeControls.branchB.enable();

			btnSearch.enable();
			btnSelectAll.enable();

			btnInvertSelect.enable();

			txtSearch.enable();
			cmbAttr.enable();
			btnTreeList.enable();
		}

		var _selectSubNodes = function(node)
		{
			if (node.parentNode)
			{
				if (!node.isSelected() && node.parentNode.isExpanded())
					treeMain.getSelectionModel().select(node, null, true);
				else if (node.isSelected() && (!node.parentNode.isExpanded()))
					treeMain.getSelectionModel().unselect(node);

				for (var i = 0; i < node.childNodes.length; i++)
					_selectSubNodes(node.childNodes[i]);
			}
		}

		var _doPasteOnGrid = function(horizVert)
		{
			// horizVert - true = Horizontal; false = Vertical
			var tmpRec, dims = {};
			if (chbInsertOtherElems.getValue())
			{
				var type = '', values = [];
				if (rbServerDb.getValue())
				{
					type = 'serv_db';
					values[values.length] = storeServDb.getAt(storeServDb.find('id', servId)).get('name') + '/' + dbName;
				}
				else if (rbCubeName.getValue())
				{
					type = 'cube';
					values[values.length] = cmbCube.getValue();
				}
				else if (rbDimName.getValue())
				{
					type = 'dim_name';
					var listOfRecs = listOfDims.getSelectedRecords();
					for (var i=0; i<listOfRecs.length; i++)
						values[values.length] = listOfRecs[i].get('name');
				}

				if (Jedox.wss.app.activePane)
				{
					var env = Jedox.wss.app.environment;
					var activePane = Jedox.wss.app.activePane;
					var upperLeftCoords = env.defaultSelection.getActiveRange().getUpperLeft();

					var settings = [upperLeftCoords.getX(), upperLeftCoords.getY(), servId, dbName, horizVert, type];
					Jedox.backend.rpc_cb('palo_handlerPutValuesOnGrid', [settings, values]);
				}
			}
			else
			{
				if (storeElemList.getCount() > 0)
				{
					// return form storeElemList
					for (var i = 0; i < storeElemList.getCount(); i++)
					{
						tmpRec = storeElemList.getAt(i);
						if (!(dims[tmpRec.get('dim')]))
							dims[tmpRec.get('dim')] = [];

						dims[tmpRec.get('dim')][dims[tmpRec.get('dim')].length] = [tmpRec.get('id'), tmpRec.get('attr'), ((tmpRec.get('type') == 'consolidated') ? 'C' : '')];
					}
				}
				else if ((displayMode == 0) && (treeMain))
				{
					// return from current selected tree
					var tmpNodes = treeMain.getSelectionModel().getSelectedNodes();
					_sortSelectedNodesNodes(tmpNodes);
					dims[dimName] = [];
					for (var i=0, nodesLen=tmpNodes.length; i<nodesLen; i++)
						dims[dimName][i] = [tmpNodes[i].attributes.name, ((cmbAttr.getValue() == "[none]".localize()) ? null : cmbAttr.getValue()), ((tmpNodes[i].isLeaf()) ? '' : 'C')];
				}
				else if (displayMode == 1)
				{
					// return from current selected data view
					var tmpIndexes = dvMain.getSelectedIndexes()
						, dvStore = dvMain.getStore()
						, indexesLen = tmpIndexes.length
						, tmpIndex
						, i
						, j;
					dims[dimName] = [];

					for (i=0; i<indexesLen-1; i++)
						for (j=indexesLen-1; j>i; j--)
							if (tmpIndexes[j-1] > tmpIndexes[j])
							{
								tmpIndex = tmpIndexes[j-1];
								tmpIndexes[j-1] = tmpIndexes[j];
								tmpIndexes[j] = tmpIndex;
							}

					for (i=0; i<indexesLen; i++)
					{
						tmpRec = dvStore.getAt(tmpIndexes[i]);
						dims[dimName][i] = [tmpRec.get('id'), tmpRec.get('attr'), ((tmpRec.get('type') == 'consolidated') ? 'C' : '')];
					}
				}

				if (Jedox.wss.app.activePane)
				{
					var env = Jedox.wss.app.environment;
					var activePane = Jedox.wss.app.activePane;
					var upperLeftCoords = env.defaultSelection.getActiveRange().getUpperLeft();

					var settings = [upperLeftCoords.getX(), upperLeftCoords.getY(), servId, dbName, horizVert];
					Jedox.backend.rpc_cb('palo_handlerSelectElements', [[settings, dims]]);

					// Refresh cursor field.
					var cursorValue = activePane.getCellValue(upperLeftCoords.getX(), upperLeftCoords.getY()),
						cursorField = Jedox.wss.app.activeSheet._defaultSelection.getCursorField();

					cursorField.setContent(cursorValue == undefined ? '' : cursorValue);
					cursorField.cloneStyle();
				}
			}
		}

		var _setDataMode = function(newDataMode)
		{
			if (newDataMode == -1)
			{
				btnsChooseCubeType.metaDataB.disable();
				btnsChooseCubeType.attribsB.disable();
				btnsChooseCubeType.usersB.disable();

				return;
			}

			if (newDataMode == 0)
			{
				btnsChooseCubeType.metaDataB.disable();
				btnsChooseCubeType.attribsB.enable();
				btnsChooseCubeType.usersB.enable();
			}
			else if (newDataMode == 2)
			{
				btnsChooseCubeType.metaDataB.enable();
				btnsChooseCubeType.attribsB.disable();
				btnsChooseCubeType.usersB.enable();
			}
			else if (newDataMode == 1)
			{
				btnsChooseCubeType.metaDataB.enable();
				btnsChooseCubeType.attribsB.enable();
				btnsChooseCubeType.usersB.disable();
			}

			dataMode = newDataMode;
		}

		var _setOtherElemsRadios = function(radioId)
		{
			if (radioId == 2)
			{
				rbServerDb.setValue(false);
				rbCubeName.setValue(true);
				rbDimName.setValue(false);
			}
			else if (radioId == 3)
			{
				rbServerDb.setValue(false);
				rbCubeName.setValue(false);
				rbDimName.setValue(true);
			}
			else
			{
				rbServerDb.setValue(true);
				rbCubeName.setValue(false);
				rbDimName.setValue(false);
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

				var listW = 750 * (13/21);
				var listH = h - 9*marginSize - 7*lineH;

				var treeW = w - 2*marginSize - listW - _config.widthMidButtons;
				var treeH = h - 6*marginSize - 4*lineH;

				// tree
				panelDims.setSize(treeW, treeH);
				panelDims.setPosition(marginSize, 4*marginSize + 3*lineH);

				// data view
				panellistView.setSize(listW, listH);
				panellistView.setPosition(marginSize + treeW + _config.widthMidButtons, 3*marginSize + 2*lineH);

				// Buttons
				panelTopBtns.setPosition(marginSize, 3*marginSize + 2*lineH);
				panelBottomTreeBtns.setPosition(marginSize + treeW + _config.widthMidButtons, listH + 6*marginSize + 4*lineH);
				if (
					panelbtnSelectBranch.rendered && btnSelectBranch.rendered
					&& panelbtnSearch.rendered && btnSearch.rendered
					&& panelbtnSelectAll.rendered && btnSelectAll.rendered
					&& panelbtnInvertSelect.rendered && btnInvertSelect.rendered
					&& btnPasteVert.rendered)
				{
					panelbtnSelectAll.setPosition(marginSize + treeW + _config.widthMidButtons, listH + 5*marginSize + 3*lineH);
					panelbtnSelectBranch.setPosition(w - btnOk.getEl().getBox().width - btnSelectBranch.getEl().getBox().width - 2*marginSize, listH + 5*marginSize + 3*lineH);

					// width of btnOk is used because btnPasteVert is hiden sometimes
					panelbtnInvertSelect.setPosition(w - btnOk.getEl().getBox().width - btnInvertSelect.getEl().getBox().width - 2*marginSize, listH + 6*marginSize + 4*lineH);

					panelbtnSearch.setPosition(w - btnClose.getEl().getBox().width - btnSearch.getEl().getBox().width - 2*marginSize, treeH + 4*marginSize + 2*lineH);
				}
				panelbtnTreeList.setPosition(treeW - lineH, 3*marginSize + 2*lineH);

				if (panelbtnClearList.rendered && btnClearList.rendered
					&& panelbtnAsc.rendered && btnAsc.rendered
					&& panelbtnDesc.rendered && btnDesc.rendered)
				{
					panelbtnClearList.setPosition(w - btnClearList.getEl().getBox().width - marginSize, 2*marginSize + 1*lineH);
					panelbtnDesc.setPosition(w - btnClearList.getEl().getBox().width - btnDesc.getEl().getBox().width - 2*marginSize, 2*marginSize + 1*lineH);
					panelbtnAsc.setPosition(w - btnClearList.getEl().getBox().width - btnDesc.getEl().getBox().width - btnAsc.getEl().getBox().width - 3*marginSize, 2*marginSize + 1*lineH);
				}

				if (panelbtnMids.rendered)
					panelbtnMids.setPosition(treeW + 2*marginSize + 1, 2*marginSize + lineH + (listH/2 - panelbtnMids.getSize().height/2));

				// Combo and Text field
				panelcmbAttr.setPosition(marginSize, treeH + 5*marginSize + 3*lineH);
				panelcmbDb.setPosition(marginSize, 2*marginSize + lineH);
				panelcmbDb2.setPosition(marginSize, 2*marginSize + lineH);
				lblcmbDb.setPosition(marginSize, 4*marginSize);
				lblcmbDb2.setPosition(marginSize, 4*marginSize);
				lblList.setPosition(marginSize + treeW + _config.widthMidButtons, 5*marginSize + lineH);
				lblBottomInfo.setPosition(marginSize + treeW + _config.widthMidButtons, treeH + 5*marginSize + 3*lineH);

				// Input text field
				paneltxtSearch.setPosition(marginSize + treeW + _config.widthMidButtons, treeH + 4*marginSize + 2*lineH);

				// Check boxes
				panelchbShowHideB.setPosition(marginSize + treeW + _config.widthMidButtons, listH + 4*marginSize + 2*lineH);
				chbInsertOtherElems.setPosition(marginSize + treeW + _config.widthMidButtons, marginSize);
				chbInsertOtherElems2.setPosition(marginSize + treeW + _config.widthMidButtons, marginSize);

				// **** Paste Other Elems *** //
				rbServerDb.setPosition(marginSize, 3*marginSize + 2*lineH);
				rbCubeName.setPosition(marginSize, 4*marginSize + 3*lineH);
				rbDimName.setPosition(marginSize, 6*marginSize + 5*lineH);
				panelcmbCube.setPosition(marginSize, 5*marginSize + 4*lineH);
				panellistOfDims.setPosition(marginSize, 7*marginSize + 6*lineH);

					cmbCube.setWidth(w - btnClose.getEl().getBox().width - 8*marginSize);
					panelcmbCube.setWidth(w - btnClose.getEl().getBox().width - 6*marginSize);
					panellistOfDims.setSize(w - btnClose.getEl().getBox().width - 8*marginSize, h - 9*marginSize - 7*lineH);
					panelbtnsChooseCubeType.setPosition(w - btnClose.getEl().getBox().width - marginSize, 5*marginSize + 4*lineH);
			}
			that.activate();
		}

		this.init(conf);
		this.show();
		Jedox.palo.utils.showLoadingMsg("Acquiring Server List".localize().concat(' ...'));
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.SelectElements, Jedox.dlg.Dialog);
