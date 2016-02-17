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
 * SVN: $Id: SubsetEditor.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.palo.openSubsetEditor = function(conf)
{
	Jedox.dlg.dlgRegistry.add(new Jedox.palo.SubsetEditor(false, 0, true, conf));
}

Jedox.palo.SubsetEditor = (function(){

	return function(callBackFn, tabOffset, dlgMode, conf) {

		var that = this;

		this.cts = (callBackFn)? Jedox.studio.app.containers : {};

		// Checkbox class for Grid in Data Tab
		var DataGridCheckBox = function(config){
			Ext.apply(this, config);
			if(!this.id){
				this.id = Ext.id();
			}
			this.renderer = this.renderer.createDelegate(this);
		};

		DataGridCheckBox.prototype = {
			init : function(grid)
			{
				this.grid = grid;
				this.grid.on('render', function()
				{
					var view = this.grid.getView();
					view.mainBody.on('mousedown', this.onMouseDown, this);
				}, this);
			},
			onMouseDown : function(e, t)
			{
				if (t.className && t.className.indexOf('x-grid3-cc-'+this.id) != -1)
				{
					// Workaround for non triggering change on Variable Combobox
					var tmpExtObj = Ext.getCmp(document.activeElement.id);
					if (tmpExtObj && tmpExtObj._var_name) // check is it Variable Combobox
					{
						var newValue = tmpExtObj.getRawValue(),
							rec = storeVars.getAt(storeVars.find('name', newValue));
						if (rec)
							_setVar(tmpExtObj._var_name, rec.get('name'), rec.get('value'));
						else
							_setVar(tmpExtObj._var_name, _formulaName, newValue);
					}

					e.stopEvent();
					var index = this.grid.getView().findRowIndex(t);
					var record = this.grid.store.getAt(index);
					record.set(this.dataIndex, !record.data[this.dataIndex]);
				}
			},
			renderer : function(v, p, record)
			{
				p.css += ' x-grid3-check-col-td';
				return (record.get('name') != cmbDim.getValue()) ?
					'<div class="x-grid3-check-col' + (v?'-on':'') + ' x-grid3-cc-' + this.id + '" style="background-position:left;padding-left:20px;padding-top:2px;">' +
					"Variable".localize() + '</div>' : '<div></div>';
			}
		};

		// Spacer for Form elements
		var SseSpacer = Ext.extend(Ext.form.MiscField, {
			initComponent: function()
			{
				SseSpacer.superclass.initComponent.call(this);

				this.hidden = false;
				if (this.labelStyle)
					this.labelStyle += 'width:1px;';
				else
					this.labelStyle = 'width:1px;';
				this.labelSeparator = '&nbsp';
			}
		});

		// Local Ext JS class extensions for Edit in Text Patterns
		var _TextPatternEditor = function(cfg, field)
		{
			_TextPatternEditor.superclass.constructor.call(this,
					field || new Ext.form.TextField({
							allowBlank: true,
							growMin: 90,
							growMax: 240,
							grow: true,
							selectOnFocus: true
					}), cfg
			);
		}

		Ext.extend(_TextPatternEditor, Ext.Editor,
		{
			alignment: "tl-tl",
			hideEl : false,
			cls: "x-small-editor",
			shim: false,
			completeOnEnter: true,
			cancelOnEsc: true,

			init: function(view)
			{
				this.view = view;
				view.on('render', this.initEditor, this);
			},

			initEditor: function()
			{
				this.view.getEl().on('mousedown', this.onMouseDown, this, {delegate: this.labelSelector});
			},

			onMouseDown: function(e, target)
			{
				if(!this.disabled && !e.ctrlKey && !e.shiftKey)
				{
					var item = this.view.findItemFromChild(target);
					e.stopEvent();
					var record = this.view.store.getAt(this.view.indexOf(item));
					this.startEdit(target, record.data[this.dataIndex]);
					this.activeRecord = record;
				}
				else
					e.preventDefault();
			}
		});

		// Palo callback handlers
		var paloCbSuccessHandlers =
		{
			getServListWithDBs: function(result)
			{
				storeServDb.loadData(result[0]);
				if (result[1])
					preselectedServDb = result[1];

				Ext.MessageBox.hide();
				paloCbErrorHandlers.getServListWithDBs(result);
			},
			getDims: function(result)
			{
				storeDims.removeAll();
				cmbDim.clearValue();
				for (var i=0; i < result.length; i++)
					storeDims.add(new DimRecord({
						name: result[i]
					}));

				if (storeDims.getCount() > 0)
				{
					var tmpIndex = 0;
					if (editingConfig)
						tmpIndex = storeDims.find('name', editingConfig.dim_name);

					if (tmpIndex == -1)
						tmpIndex = 0;

					var tmpRec = storeDims.getAt(tmpIndex);
					if (tmpRec)
					{
						cmbDim.setValue(tmpRec.get('name'));
						_cmbDimSelectHandler(cmbDim, tmpRec, tmpIndex);
					}
				}
				else
				{
					var noneName = "[none]".localize();

					storeAlias.removeAll();
					storeAlias.add(new AttrRecord({
						identifier: -1,
						name: noneName,
						esc_name: noneName
					}));
					cmbFirstA.setValue(noneName);
					cmbSecondA.setValue(noneName);
				}
			},
			getCubesWithDims: function(result)
			{
				storeCubes.removeAll();
				storeCubeDimensions.removeAll();
				cmbDSCubes.setValue('');
				for (var i=0; i < result.length; i++)
					storeCubes.add(new CubeRecord({
						name: result[i].name,
						list: result[i].list
					}));

				if (result.length > 0)
				{
					cmbDSCubes.setValue(storeCubes.getAt(0).get('name'));
					_cmbDSCubesSelectionHandler(cmbDSCubes, storeCubes.getAt(0), 0);
				}

				paloRpcServer.getSubsetNames(servId, dbName, cmbDim.getValue());
			},
			getDimAttrs: function(result)
			{
				var tmpRec, columns = [], storeObj = [], emptyDataRow = [];
				var noneName = "[none]".localize();

				storeAlias.removeAll();
				storeAttrs.removeAll();
				tmpRec = new AttrRecord({
					identifier: -1,
					name: noneName,
					esc_name: noneName
				});
				storeAlias.add(tmpRec);

				cmbFirstA.setValue(noneName);
				cmbSecondA.setValue(noneName);
				for (var i=0; i < result.length; i++)
				{
					tmpRec = new AttrRecord({
						identifier: result[i].id,
						name: result[i].name,
						esc_name: Jedox.palo.utils.escHTML(result[i].name)
					});
					storeAlias.add(tmpRec);
					storeAttrs.add(tmpRec);

					storeObj[storeObj.length] = {name: result[i].name};
					columns[columns.length] = {header: Jedox.palo.utils.escHTML(result[i].name), editor: new Ext.form.TextField({allowBlank: true}), menuDisabled: true, dataIndex: result[i].name};
					emptyDataRow[emptyDataRow.length] = '';
				}

				panelgridASAttrs.items.removeAt(0);
				if (result.length == 0)
				{
					columns = [{
						header: "",
						editor: new Ext.form.TextField({
							allowBlank: false
						}),
						menuDisabled: true,
						dataIndex: 'name'
					}];
					storeASAttrs = new Ext.data.SimpleStore({
						fields: [{
							name: 'name'
						}]
					});
					ASAttrsRecord = new Ext.data.Record.create([{
						name: ''
					}]);
				}
				else
				{
					storeASAttrs = new Ext.data.SimpleStore({
						fields: storeObj
					});
					ASAttrsRecord = new Ext.data.Record.create(storeObj);
					storeASAttrs.loadData([emptyDataRow]);
				}

				gridASAttrs = new Ext.grid.EditorGridPanel({
					disabled: true,
					store: storeASAttrs,
					columns: columns,
					stripeRows: true,
					viewConfig: {
						autoFill: true
					},
					listeners: {
						validateedit: function(el)
						{
							// add
							if ((el.row == (storeASAttrs.getCount() - 1)) && (el.value != ''))
							{
								var newRecData = {};
								for (var i=0; i<storeAttrs.getCount(); i++)
									newRecData[storeAttrs.getAt(i).get('name')] = '';
								el.record.set(el.field, el.value);

								storeASAttrs.add(new ASAttrsRecord(newRecData));
							}
							else if ((el.value == '') && (el.orginalValue != '') && (el.row == (storeASAttrs.getCount() - 2)))
							{
								var allEmpty = true;
								for (var i=0; ((i<storeAttrs.getCount()) && allEmpty); i++)
									if ((el.record.get(storeAttrs.getAt(i).get('name')) != '') && (i != el.column))
										allEmpty = false;

								if (allEmpty)
									storeASAttrs.remove(el.record);
								else
									el.record.set(el.field, el.value);
							}
							else
								el.record.set(el.field, el.value);

							_reqGetSubsetList();
							return false;
						}
					}
				});
				panelgridASAttrs.add(gridASAttrs);

				if (storeAttrs.getCount() > 0)
				{
					rbSoSoAttr.enable();
					cmbSoSoAttr.setValue(storeAttrs.getAt(0).get('name'));
				}
				else
				{
					if (_getRbVal(rbSoSoAttr))
					{
						cmbSoSoAttr.disable();
						rbSoSoDef.setValue(true);
						rbSoSoAttr.setValue(false);
					}
					rbSoSoAttr.disable();
					cmbSoSoAttr.setValue('');
				}
			},
			getSubsetNames: function(result)
			{
				disableAutoPreview = true;

				storeLocalSubsets.removeAll();
				for (var i=0; i < result[0].length; i++)
					storeLocalSubsets.add(new SubsetRecord({
						name: result[0][i]
					}));

				storeGlobalSubsets.removeAll();
				for (var i=0; i < result[1].length; i++)
					storeGlobalSubsets.add(new SubsetRecord({
						name: result[1][i]
					}));

				if (editingConfig)
				{
					switch (editingConfig.subset_type)
					{
						case 0:
							_reloadSubsetObject(dynarangeConf._gendata[1]);
							panelFormulaSubset.expand();
							break;

						case 1:
							panelLocalSubset.expand();
							disableAutoPreview = true;
							viewLocalSubsets.select(storeLocalSubsets.find('name', editingConfig.subset_name));
							break;

						case 2:
							panelGlobalSubset.expand();
							disableAutoPreview = true;
							viewGlobalSubsets.select(storeGlobalSubsets.find('name', editingConfig.subset_name));
							break;

						default:
							panelFormulaSubset.expand();
					}

					// finished loading of Editing Data
					editingConfig = null;
				}
				else
					panelFormulaSubset.expand();

				disableAutoPreview = false;

				_reqGetSubsetList();
				loadingDialog = false;
			},
			setDynarangeList: function(result)
			{
				dynarangeConf.ss_func = result;
				if (Jedox.palo.workIn == Jedox.palo.GRID)
					Jedox.wss.hb.subsetDlgCB(dynarangeConf);
			},
			getSubsetList: function(result)
			{
				Ext.MessageBox.hide();
				btnPaste.enable();

				if (result[0])
				{
					var tmpRootNode = previewTree.getRootNode();
					tmpRootNode.removeAll(true);
					tmpRootNode.appendChild(result[1]);

					previewDataView.hide();
					previewTree.show();

					tmpRootNode.expandChildNodes();
				}
				else
				{
					storeElems.removeAll();
					for (var i=0; i < result[1].length; i++)
						storeElems.add(new ElemRecord({
							name: result[1][i]
						}));

					previewTree.hide();
					previewDataView.show();
				}
			},
			getSubsetListByXML: function(result)
			{
				this.getSubsetList(result);
			},
			savePaloSubset: function(result)
			{
				var tmpView, tmpStore;
				if (selectedWestPanel == 1)
				{
					tmpStore = storeLocalSubsets;
					tmpView = viewLocalSubsets;
				}
				else if (selectedWestPanel == 2)
				{
					tmpStore = storeGlobalSubsets;
					tmpView = viewGlobalSubsets;
				}

				var subsetName = null;
				if ((tmpView) && (tmpView.getSelectionCount() > 0))
					subsetName = tmpView.getSelectedRecords()[0].get('name');

				if (subsetName != result)
				{
					tmpStore.add(new SubsetRecord({name: result}));
					var lastElemIndex = tmpStore.getCount() - 1;
					var lastNode = tmpView.getNode(lastElemIndex);
					lastNode.scrollIntoView(tmpView.body, false);
					tmpView.select(lastElemIndex);
				}

				Jedox.palo.utils.hideWaitMsg();
			},
			deletePaloSubset: function(result)
			{
				var tmpView;
				if ((selectedWestPanel == 1) && (viewLocalSubsets.getSelectionCount() > 0))
				{
					storeLocalSubsets.remove(viewLocalSubsets.getSelectedRecords()[0]);
					tmpView = viewLocalSubsets;
				}
				else if ((selectedWestPanel == 2) && (viewGlobalSubsets.getSelectionCount() > 0))
				{
					storeGlobalSubsets.remove(viewGlobalSubsets.getSelectedRecords()[0]);
					tmpView = viewGlobalSubsets;
				}

				var firstNode = tmpView.getNode(0);
				if (firstNode)
				{
					firstNode.scrollIntoView(tmpView.body, false);
					tmpView.select(0);
				}

				Jedox.palo.utils.hideWaitMsg();
			},
			renamePaloSubset: function(result)
			{
				if ((selectedWestPanel == 1) && (viewLocalSubsets.getSelectionCount() > 0))
					storeLocalSubsets.getAt(storeLocalSubsets.find('name', result[0])).set('name', result[1]);
				else if ((selectedWestPanel == 2) && (viewGlobalSubsets.getSelectionCount() > 0))
					storeGlobalSubsets.getAt(storeGlobalSubsets.find('name', result[0])).set('name', result[1]);

				Jedox.palo.utils.hideWaitMsg();
			},
			getSubsetDialogData: function(result)
			{
				_reloadSubsetObject(result);
			},
			handlerGetGeneratedSubsetFunc: function(result)
			{
				if (conf && (conf.mode == 3 || conf.mode == 4))
				{
					var tmpView;
					if (selectedWestPanel == 1)
						tmpView = viewLocalSubsets;
					else if (selectedWestPanel == 2)
						tmpView = viewGlobalSubsets;

					var genData = null;
					if ((tmpView) && (tmpView.getSelectionCount() > 0))
						genData = [[servId, dbName, cmbDim.getValue(), tmpView.getSelectedRecords()[0].get('name'), selectedWestPanel], _generateSubsetObject(), _getNumOfFilledVars()];
					else if (!cmbDim.disabled && cmbDim.getValue())
						genData = [[servId, dbName, cmbDim.getValue(), '', 0], _generateSubsetObject(), _getNumOfFilledVars()];

					funcText = result[0][1][4];
					conf.fnc({ss_func: funcText, _gendata: genData, _preview_val: _getPreviewValue()});

					that.win.close();
				}
			}
		};

		var paloCbErrorHandlers =
		{
			getServListWithDBs: function(result)
			{
				if (editingConfig && result)
					cmbDbState = storeServDb.find('name', editingConfig.db_name, storeServDb.find('id', editingConfig.serv_id));

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
					cmbServDb.setValue(storeServDb.getAt(tmpIndex).get('id'));
					_cmbServDbSelectionHandler(cmbServDb, storeServDb.getAt(tmpIndex), tmpIndex);
				}
			},
			getDims: function() {},
			getCubesWithDims: function() {},
			getDimAttrs: function() {},
			getSubsetNames: function() {},
			setDynarangeList: function() {},
			getSubsetList: function()
			{
				// Clear Preview
				if (previewTree.isVisible())
					previewTree.getRootNode().removeAll(true);
				else if (previewDataView.isVisible())
					storeElems.removeAll();

				btnPaste.enable();
			},
			getSubsetListByXML: function() { this.getSubsetList(); },
			savePaloSubset: function() {},
			deletePaloSubset: function() {},
			renamePaloSubset: function() {},
			getSubsetDialogData: function() {},
			handlerGetGeneratedSubsetFunc: function() {}
		};

		var paloCbTimeoutHandlers =
		{
			getServListWithDBs: function() { paloCbErrorHandlers.getServListWithDBs(); },
			getDims: function() {},
			getCubesWithDims: function() {},
			getDimAttrs: function() {},
			getSubsetNames: function() {},
			setDynarangeList: function() {},
			getSubsetList: function()
			{
				Ext.MessageBox.hide();
				paloCbErrorHandlers.getSubsetList();
			},
			getSubsetListByXML: function() { this.getSubsetList(); },
			savePaloSubset: function() { Jedox.palo.utils.hideWaitMsg(true); },
			deletePaloSubset: function() { Jedox.palo.utils.hideWaitMsg(true); },
			renamePaloSubset: function() { Jedox.palo.utils.hideWaitMsg(true); },
			getSubsetDialogData: function() {},
			handlerGetGeneratedSubsetFunc: function() {}
		};

		var servId, dbName, preselectedServDb = null, servAcls, permTypes,
			paloRpcServerListByXML = new Jedox.backend.RPCAsyncRqst('palo_sbst', 'getSubsetListByXML'),
			paloRpcServerList = new Jedox.backend.RPCAsyncRqst('palo_sbst', 'getSubsetList'),
			paloRpcServer = new Jedox.backend.rpc.Palo(paloCbSuccessHandlers, paloCbErrorHandlers, paloCbTimeoutHandlers),
			_config =
			{
				tabOkIcon: 'palo_icon_OK',
				_tabSize: 30,
				sseWinW: 900,
				sseWinH: 550
			},
			_marginSize = 3, // size in pixels for spaces between
			_lineH = 20, // size in pixels for element line (like checkbox, textbox, etc..)
			_formulaName = '_$formula$_',
			dataMode, // 0 = normal cubes, 1 = system cubes, 2 = attribute cubes
			win, panelMain, panelWest, panelEast, panelCenter, panelCenterTab, panelCenterBottom, panelStoredSubsets,
			panelFormulaSubset, panelLocalSubset, panelGlobalSubset, panelPreviewCenter, panelPreviewSouth, panelbtnRefreshPreview, panelbtnSubsetActions,
			fsServer, fsAlias, fsLayout, fsHierarchy, fsOptional, fsSoSorting, fsSoOrder, fsSoType, fsSoLevel, fsTSettings,
			lblGenDesc, lblServDb, lblDim, lblFirstA, lblSecondA, cmbServDb, cmbDim, cmbFirstA, cmbSecondA, rbHierIndent, rbHierLevel, rbHierDepth,
			rbLayoutFlat, rbLayoutHier, chbParentsReverse, chbLayoutDouble, chbLayoutChildren, chbAutoPreview, chbQuickPreview, btnSave, btnPaste, btnClose, btnRefreshPreview, btnSubsetActions,
			chbVFirstA, chbVSecondA,
			rbSoSoDef, rbSoSoElem, rbSoSoAlias, rbSoSoVal, rbSoSoAttr, chbSoOrReverse, rbSoTyElems, rbSoTyBase, rbSoTyCons, chbSoLvSort, cmbSoSoAttr,
			chbSoSoVCriteria, chbSoSoVAttr, chbSoOrVReverse, chbSoTyVType, chbSoLvVLevel, spinSoLvIndent,
			chbHEnable, fsHHier, rbHElemH, rbHElemHCyc, cmbHHList, treecmbHHList, rbHHBelow, rbHHAbove, chbHHExclusive, panelchbHHExclusive, spinHHListLength, panelspinHHListLength,
			chbHType, rbHTCons, rbHTBase, chbHLevel, spinHLStart, spinHLEnd, elemsHL = [],
			chbHHVList, chbHHVBelowAbove, chbHHVExclusiveList, chbHVType, chbHLVStart, chbHLVEnd,
			chbTEnable, viewTextPatterns, panelviewTextPatterns, chbTSPerl, lblTSExample, viewTextPatternsEditor, chbTSVPatterns, chbTSVPerl,
			chbPEnable, fsPDimCont, fsPBehave, viewPDElems, panelviewPDElems, lblPDElems, lblPBInsertType, rbPBFront, rbPBBack, rbPBMerge, rbPBSubtract, btnPDEdit, chbPDVElems, chbPBVBehave,
			chbAEnable, fsASettings, lblASView, lblASExample, gridASAttrs, panelgridASAttrs, chbASVAttrs,
			chbDEnable, fsDSettings,fsDSlice, fsDOptional, cmbDSCubes, gridDSCubeDims, panelgridDSCubeDims, cmbDSCriteria, cmbDOFirst, cmbDOSecond, txtDOFirst, txtDOSecond,
			chbD3Topmost, chbD3Upper, chbD3Lower, spinD3Topmost, spinD3Upper, spinD3Lower,
			chbDSVCube, chbDSVCriteria, chbDOVFirst, chbDOVSecond, chbD3VTop, chbD3VUpper, chbD3VLower,
			viewFormulaSubsets, viewGlobalSubsets, viewLocalSubsets, lblHHListLength,
			tabGeneral, tabHierarchy, tabText, tabPicklist, tabAttribute, tabData, tabSort, cmbDbState,
			selectedWestPanel, // used to store is it selected Local, or Global Subset Panel .. 1=local, 2=global
			conf, dynarangeConf,
			editingConfig, previewTree, previewDataView, panelPreviewVars, disableAutoPreview, loadingDialog, dirtySubset;

		// *** Stores ***
		// variable combo boxes list
		var VarComboRecord = new Ext.data.Record.create([
			{ name: 'name' },
			{ name: 'desc' },
			{ name: 'var_name' },
			{ name: 'var_value' }
		]);
		var storeVarCombos = new Ext.data.SimpleStore({
			fields: [
				{ name: 'name' },
				{ name: 'desc' },
				{ name: 'var_name' },
				{ name: 'var_value' }
			]
		});

		// variable store
		var VarRecord = new Ext.data.Record.create([
			{ name: 'name' },
			{ name: 'value' }
		]);
		var storeVars = new Ext.data.SimpleStore({
			fields: [
				{ name: 'name' },
				{ name: 'value' }
			]
		});

		// server + database
		var storeServDb = new Ext.data.SimpleStore({
			fields: [
				{ name: 'id' },
				{ name: 'parent_id' },
				{ name: 'connected' },
				{ name: 'type' },
				{ name: 'name' },
				{ name: 'rules' }
			]
		});

		// dimensions
		var DimRecord = new Ext.data.Record.create([{
			name: 'name'
		}]);
		var storeDims = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// attributes
		var AttrRecord = new Ext.data.Record.create([{
			name: 'identifier',
			name: 'name',
			name: 'esc_name'
		}]);
		var storeAttrs = new Ext.data.SimpleStore({
			fields: [
				{ name: 'identifier' },
				{ name: 'name' },
				{ name: 'esc_name' }
			]
		});
		// first and second alias store
		var storeAlias = new Ext.data.SimpleStore({
			fields: [
				{ name: 'identifier' },
				{ name: 'name' },
				{ name: 'esc_name' }
			]
		});

		// subsets
		var SubsetRecord = new Ext.data.Record.create([{
			name: 'name'
		}]);
		var storeFormulaSubsets = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});
		var storeGlobalSubsets = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});
		var storeLocalSubsets = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// preview
		var ElemRecord = new Ext.data.Record.create([{
			name: 'name'
		}]);
		var storeElems = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// text patterns
		var TextPatternRecord = new Ext.data.Record.create([{
			name: 'text'
		}]);
		var storeTextPatterns = new Ext.data.SimpleStore({
			fields: [{
				name: 'text'
			}]
		});

		// picklist elements
		var PicklistElemRecord = new Ext.data.Record.create([
			{ name: 'index' },
			{ name: 'name' },
			{ name: 'esc_name' }
		]);
		var storePDElems = new Ext.data.SimpleStore({
			fields: [
				{ name: 'index' },
				{ name: 'name' },
				{ name: 'esc_name' }
			]
		});

		// attribute attributes
		var ASAttrsRecord = new Ext.data.Record.create([{
			name: 'name'
		}]);
		var storeASAttrs = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// cubes (data tab)
		var CubeRecord = new Ext.data.Record.create([
			{name: 'name'},
			{name: 'list'}
		]);
		var storeCubes = new Ext.data.SimpleStore({
			fields: [
				{name: 'name'},
				{name: 'list'}
			]
		});

		// cube dims (data tab)
		var CubeDimRecord = new Ext.data.Record.create([
			{ name: 'name' },
			{ name: 'elements' },
			{ name: 'variable' }
		]);
		var storeCubeDimensions = new Ext.data.SimpleStore({
			fields: [
				{ name: 'name' },
				{ name: 'elements' },
				{ name: 'variable' }
			],
			listeners:
			{
				add: function(thisStore, records, index)
				{
					var numOfRecs = records.length;
					for (var i=0; i<numOfRecs; i++)
						_handleDataGridChange(records[i]);
				},

				update: function(thisStore, record, operation)
				{
					_handleDataGridChange(record);
				}
			}
		});

		// criteria (data tab)
		var storeCriteria = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// operands (data tab)
		var storeOperands = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});
		// ***

		// Private initialization function
		var _init = function(inConf) // (inDynarangeConf, inCallDialogHandler, listWizardConf)
		{
			permTypes = (Jedox.palo.workIn == Jedox.palo.STUDIO) ? Jedox.studio.access.permType : { NONE: 0, READ: 1, WRITE: 2, DELETE: 4, SPLASH: 8 };
			cmbDbState = -1; // initial value before anything is selected
			selectedWestPanel = 0;
			disableAutoPreview = false;
			dirtySubset = true;
			dynarangeConf = null;

			// init special rpc calls - Timer is set to 2 minutes
			paloRpcServerListByXML.setOnSuccess([paloCbSuccessHandlers, paloCbSuccessHandlers.getSubsetListByXML]).setOnError([paloCbErrorHandlers, paloCbErrorHandlers.getSubsetListByXML]).setOnTimeout([paloCbTimeoutHandlers, paloCbTimeoutHandlers.getSubsetListByXML], 120000);
			paloRpcServerList.setOnSuccess([paloCbSuccessHandlers, paloCbSuccessHandlers.getSubsetList]).setOnError([paloCbErrorHandlers, paloCbErrorHandlers.getSubsetList]).setOnTimeout([paloCbTimeoutHandlers, paloCbTimeoutHandlers.getSubsetList], 120000);

			// init criteria store
			storeCriteria.loadData([
				["SUM OF THE ELEMENTS".localize()],
				["ALL ELEMENTS".localize()],
				["AVEREGE OF THE ELEMENTS".localize()],
				["MAXIMUM OF THE ELEMETNS".localize()],
				["ANY ELEMENT".localize()],
				["MINIMUM OF THE ELEMENTS".localize()],
				["STRING".localize()]
			]);

			// init operands store
			storeOperands.loadData([
			    ["[none]".localize()],
				['='],
				['>='],
				['>'],
				['<='],
				['<'],
				['<>']
			]);

			// init hb conf
			if (inConf)
			{
				conf = inConf;
				/***
				 * MODES:
				 *
				 * 1 - Dynarange,
				 * 2 - Modeller,
				 * 3 - ComboBox (Worksheet Element Dialog),
				 * 4 - Dynarange (from Properties dialog of Dynarange),
				 * 5 - used when subset is called from Variable Mapping
				 *
				 */

				// dynarange + combo + variable mapping
				if (conf.mode == 1 || conf.mode == 3 || conf.mode == 4 || conf.mode == 5)
				{
					dynarangeConf = conf.dynarange;

					if (dynarangeConf && dynarangeConf._gendata && dynarangeConf._gendata[0])
					{
						tmpGenDataSettings = dynarangeConf._gendata[0];

						editingConfig = {
							serv_id: tmpGenDataSettings[0],
							db_name: tmpGenDataSettings[1],
							dim_name: tmpGenDataSettings[2],
							subset_type: tmpGenDataSettings[4],
							subset_name: tmpGenDataSettings[3]
						};
					}
				}

				// modeller
				else if (conf.mode == 2)
				{
					editingConfig = {
						serv_id: conf.load_data[0],
						db_name: conf.load_data[1],
						dim_name: conf.load_data[2],
						subset_type: conf.load_data[4],
						subset_name: conf.load_data[3]
					};
				}
			}

			// init name range list
			if ((Jedox.palo.workIn == Jedox.palo.GRID) && Jedox.wss.app.activeBook)
			{
				var conn = Jedox.backend;
				conn.ccmdBuffer();
				conn.ccmd(null, ['nlst', [1, 1]]);
				conn.ccmd(null, ['gvls']);
				var tmpResponse = conn.ccmdFlush(null);

				if (tmpResponse[0][0])
				{
					var names = tmpResponse[0][1][0];

					for (var vals, varVals, rowNums, cellNums, i=0; i<names.length; i++)
						if ( ( (conf.mode == 1 || conf.mode == 4) && dynarangeConf && dynarangeConf.id && (dynarangeConf.id != names[i]['name']) ) || (!dynarangeConf) || (conf.mode == 3) )
						{
							if (names[i]['value'])
							{
								vals = names[i]['value'].match(/[^{},;]+/g);
								if (vals)
								{
									for (var tmpVals, j=0; j<vals.length; j++)
									{
										tmpVals = vals[j].match(/[^"]+/g);
										vals[j] = (tmpVals) ? tmpVals[0] : '';
									}

									if (vals && (vals.length > 0))
										storeVars.add(new VarRecord({
											'name': names[i]['name'],
											'value': (vals.length > 1) ? vals : vals[0]
										}));
								}
								else
									storeVars.add(new VarRecord({
										'name': names[i]['name'],
										'value': vals
									}));
							}
							else
								storeVars.add(new VarRecord({
									'name': names[i]['name'],
									'value': names[i]['value']
								}));
						}
				}

				if (tmpResponse[1][0])
				{
					var variables = tmpResponse[1][1];

					for (var i=0; i<variables.length; i++)
						storeVars.add(new VarRecord({
							'name': '@'.concat(variables[i]),
							'value': null
						}));
				}
			}

			// +++ DataViews +++ //
			// Stored Subsets (west panel)
			viewFormulaSubsets = new Ext.DataView({
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				singleSelect: true,
				store: storeFormulaSubsets,
				cls: 'modellerDataViewSelect',
				tpl: new Ext.XTemplate('<tpl for=".">', '<div class="row-modeller">', '<span>&#160;{name}</span>', '</div>', '</tpl>')
			});
			storeFormulaSubsets.loadData([
				[((conf && (conf.mode == 1 || conf.mode == 4)) ? "[_name: hb List]".localize() : "[Formula Subset]".localize())]
			]);
			viewGlobalSubsets = new Ext.DataView({
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				singleSelect: true,
				store: storeGlobalSubsets,
				cls: 'modellerDataViewSelect',
				tpl: new Ext.XTemplate('<tpl for=".">', '<div class="row-modeller">', '<span>&#160;{name}</span>', '</div>', '</tpl>'),
				listeners: {
					selectionchange: function()
					{
						if (viewGlobalSubsets.getSelectionCount() > 0)
						{
							var settings = [servId, dbName, cmbDim.getValue(), viewGlobalSubsets.getSelectedRecords()[0].get('name'), selectedWestPanel];
							paloRpcServer.getSubsetDialogData(settings);
						}

						dirtySubset = false;
						_reqGetSubsetList();
					}
				}
			});
			viewLocalSubsets = new Ext.DataView({
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				singleSelect: true,
				store: storeLocalSubsets,
				cls: 'modellerDataViewSelect',
				tpl: new Ext.XTemplate('<tpl for=".">', '<div class="row-modeller">', '<span>&#160;{name}</span>', '</div>', '</tpl>'),
				listeners: {
					selectionchange: function()
					{
						if (viewLocalSubsets.getSelectionCount() > 0)
						{
							var settings = [servId, dbName, cmbDim.getValue(), viewLocalSubsets.getSelectedRecords()[0].get('name'), selectedWestPanel];
							paloRpcServer.getSubsetDialogData(settings);
						}

						dirtySubset = false;
						_reqGetSubsetList();
					}
				}
			});

			// Preview (east panel)
			previewDataView = new Ext.DataView({
				hidden: true,
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				singleSelect: true,
				store: storeElems,
				cls: 'modellerDataViewSelect',
				tpl: new Ext.XTemplate('<tpl for=".">', '<div class="row-modeller">', '<span>&#160;{name}</span>', '</div>', '</tpl>')
			});

			// Text Tab
			viewTextPatterns = new Ext.DataView({
				disabled: true,
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				singleSelect: true,
				store: storeTextPatterns,
				cls: 'modellerDataViewSelect',
				plugins: [
					viewTextPatternsEditor = new _TextPatternEditor({
						disabled: true,
						dataIndex: 'text',
						labelSelector: 'div.row-modeller',
						listeners: {
							beforecomplete: function(thisEd, value, startValue)
							{
								if (value && (value != '') && (thisEd.activeRecord.get(thisEd.dataIndex) != value) && (startValue != "[none]".localize()))
								{
									// rename
									thisEd.activeRecord.set(thisEd.dataIndex, value);
									_reqGetSubsetList();
								}
								else if (value && (value != '') && (thisEd.activeRecord.get(thisEd.dataIndex) != value) && (startValue == "[none]".localize()))
								{
									// add
									thisEd.activeRecord.set(thisEd.dataIndex, value);
									thisEd.activeRecord.store.add(new TextPatternRecord({
										text: "[none]".localize()
									}));
									_reqGetSubsetList();
								}
								else if (value == '' && (startValue != "[none]".localize()))
								{
									// delete
									thisEd.activeRecord.store.remove(thisEd.activeRecord);
									_reqGetSubsetList();
								}
							}
						}
					})
				],
				tpl: new Ext.XTemplate('<tpl for=".">', '<div class="row-modeller">', '<span>&#160;{text}</span>', '</div>', '</tpl>')
			});
			storeTextPatterns.loadData([
				["[none]".localize()]
			]);

			// Picklist
			viewPDElems = new Ext.DataView({
				disabled: true,
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				singleSelect: true,
				store: storePDElems,
				cls: 'modellerDataViewSelect',
				tpl: new Ext.XTemplate('<tpl for=".">', '<div class="row-modeller">', '<span>&#160;{esc_name}</span>', '</div>', '</tpl>')
			});
			// --- DataViews --- //

			// +++ GRIDS +++ //
			// Attribute Tab
			gridASAttrs = new Ext.grid.EditorGridPanel({
				disabled: true,
				store: storeASAttrs,
				columns: [
					{header: "", editor: new Ext.form.TextField({allowBlank:false}), menuDisabled: true, dataIndex: 'name'}
				],
				viewConfig: {
					forceFit: true
				},
				stripeRows: true,
				autoExpandColumn: 'name'
			});

			// Data Tab -> Settings
			var cbActive = new DataGridCheckBox({
				dataIndex: 'variable',
				width: 70
			});

			gridDSCubeDims = new Ext.grid.GridPanel({
				disabled: true,
				store: storeCubeDimensions,
				plugins: cbActive,
				viewConfig: {
					forceFit: true
				},
				cm: new Ext.grid.ColumnModel([
					{width: 170, sortable: false, dataIndex: 'name'},
					{id: 'elements', width: 170, sortable: false, dataIndex: 'elements'},
					cbActive
				]),
				sm: new Ext.grid.CellSelectionModel({}),
				stripeRows: false,
				header: false,
				enableHdMenu: false,
				autoExpandColumn: 'elements',
				autoWidth: true,
				baseCls: 'x-plain',
				subDialogOpened: false,
				listeners:
				{
					cellclick: function(thisGrid, rowIndex, columnIndex, e)
					{
						if (!gridDSCubeDims.subDialogOpened)
						{
							gridDSCubeDims.subDialogOpened = true;

							if ((columnIndex == 0) && (!storeCubeDimensions.getAt(rowIndex).get('variable')))
							{
								var tmpDimName = storeCubeDimensions.getAt(rowIndex).get('name');

								if (tmpDimName != cmbDim.getValue())
								{
									var elemList = storeCubeDimensions.getAt(rowIndex).get('elements')
										, listLen = elemList.length
										, preSelList = [];

									if (typeof elemList == 'string')
										preSelList[0] = [elemList, null];
									else
										for (var i=0; i<listLen; i++)
											preSelList[preSelList.length] = [elemList[i], null];

									if (Jedox.palo.workIn == Jedox.palo.STUDIO)
										Jedox.gen.load(Jedox.studio.app.dynJSRegistry.chooseElement, [{
											working_mode: 4,
											parent_object: {cb_fnc: _setSelectedDataElements},
											serv_id: servId,
											db_name: dbName,
											dim_name: tmpDimName,
											edit_data: (listLen > 0) ? preSelList : null
										}]);
									else if (Jedox.palo.workIn == Jedox.palo.GRID)
										Jedox.gen.load(Jedox.wss.app.dynJSRegistry.chooseElement, [{
											working_mode: 4,
											parent_object: {cb_fnc: _setSelectedDataElements},
											serv_id: servId,
											db_name: dbName,
											dim_name: tmpDimName,
											edit_data: (listLen > 0) ? preSelList : null
										}]);
								}
							}

							setTimeout(function()
							{
								gridDSCubeDims.subDialogOpened = false;
							}, 1000);
						}
					}
				}
			});
			// --- GRIDS --- //

			// +++ Spinners +++ //
			// Hier Tab
			spinHLStart = new Ext.ux.form.SpinnerField({
				disabled: true,
				minValue: 1,
				tabIndex: tabOffset + 221,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				maxValue: 99,
				hideLabel: true,
				allowBlank: false,
				width: 45,
				border: false,
				value: 1,
				enableKeyEvents: true,
				setMinAndCheck: function(minVal)
				{
					this.minValue = minVal;
					if (this.getValue() < minVal)
						this.setValue(minVal);
				},
				listeners: {
					spin: function()
					{
						_reqGetSubsetList();
					},
					keyup: function()
					{
						_reqGetSubsetList();
					}
				}
			});
			spinHLEnd = new Ext.ux.form.SpinnerField({
				disabled: true,
				minValue: 1,
				maxValue: 99,
				tabIndex: tabOffset + 223,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				allowBlank: false,
				width: 45,
				border: false,
				value: 1,
				enableKeyEvents: true,
				setMinAndCheck: function(minVal)
				{
					this.minValue = minVal;
					if (this.getValue() < minVal)
						this.setValue(minVal);
				},
				listeners: {
					spin: function()
					{
						_reqGetSubsetList();
					},
					keyup: function()
					{
						_reqGetSubsetList();
					}
				}
			});
			spinHHListLength = new Ext.ux.form.SpinnerField({
				minValue: 1,
				maxValue: 99,
				hideLabel: true,
				allowBlank: false,
				width: 45,
				border: false,
				value: 1,
				enableKeyEvents: true,
				listeners: {
					spin: function()
					{
						_reqGetSubsetList();
					},
					keyup: function()
					{
						_reqGetSubsetList();
					}
				}
			});

			// Data Tab
			spinD3Topmost = new Ext.ux.form.SpinnerField({
				disabled: true,
				minValue: 1,
				maxValue: 100,
				tabIndex: tabOffset + 621,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				allowBlank: false,
				width: 45,
				border: false,
				value: 1
			});
			spinD3Upper = new Ext.ux.form.SpinnerField({
				disabled: true,
				minValue: 0,
				maxValue: 100,
				tabIndex: tabOffset + 631,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				allowBlank: false,
				width: 45,
				border: false,
				value: 0
			});
			spinD3Lower = new Ext.ux.form.SpinnerField({
				disabled: true,
				minValue: 0,
				maxValue: 100,
				tabIndex: tabOffset + 641,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				allowBlank: false,
				width: 45,
				border: false,
				value: 0
			});

			// Sort Tab
			spinSoLvIndent = new Ext.ux.form.SpinnerField({
				disabled: true,
				tabIndex: tabOffset + 731,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				minValue: 1,
				maxValue: 3,
				allowBlank: false,
				width: 60,
				border: false,
				value: 1,
				enableKeyEvents: true,
				setMinAndCheck: function(minVal)
				{
					this.minValue = minVal;
					if (this.getValue() < minVal)
						this.setValue(minVal);
				},
				listeners: {
					spin: function()
					{
						_reqGetSubsetList();
					},
					keyup: function()
					{
						_reqGetSubsetList();
					}
				}
			});
			// --- Spinners --- //

			// +++ Preview Tree +++ //
			previewTree = new Ext.tree.TreePanel({
				hidden: true,
				cls: 'x-tree-noicon',
				border: false,
				animate: false,
				enableDD: false,
				rootVisible: false,
				bodyStyle: 'background-color: transparent;',
				plugins: new Ext.ux.tree.TreeNodeMouseoverPlugin(),
				loader: new Ext.ux.tree.PagingTreeLoader( { pagingModel: 'local' } ),
				listeners: {
					append: function(thisT, parNode, node, index)
					{
						node.text = Jedox.palo.utils.escHTML(node.text);
					}
				}
			});

			previewTree.setRootNode(
				new Ext.tree.AsyncTreeNode({
					text: 'root',
					draggable: false,
					id: 'root'
				})
			);
			// --- Preview Tree --- //

			// +++ Text Labels +++ //
			// General Tab
			lblGenDescnew = new Ext.form.MiscField({
				value: "Subset General Settings".localize() + ':',
				hideLabel: true
			});
			lblServDb = new Ext.form.MiscField({
				value: "Choose Server/Database".localize() + ':',
				hideLabel: true
			});
			lblDim = new Ext.form.MiscField({
				value: "Dimension".localize() + ':',
				hideLabel: true
			});
			lblFirstA = new Ext.form.MiscField({
				value: "Select First Alias".localize() + ':',
				hideLabel: true
			});
			lblSecondA = new Ext.form.MiscField({
				value: "Select Second Alias".localize() + ':',
				hideLabel: true
			});

			// Text tab
			lblTSExample = new Ext.form.MiscField({
				disabled: true,
				value: "_subsetTextTabExamples".localize(),
				hideLabel: true
			});

			// Picklist Tab
			lblPBInsertType = new Ext.form.MiscField({
				disabled: true,
				value: "Please select how to insert choosen elements".localize() + ':',
				hideLabel: true
			});

			// Attribute Tab
			lblASView = new Ext.form.MiscField({
				disabled: true,
				value: "Please select and set attribute fields".localize(),
				hideLabel: true
			});
			lblASExample = new Ext.form.MiscField({
				disabled: true,
				value: "_subsetAttrTabExample".localize(),
				hideLabel: true
			});
			// --- Text Labels --- //

			// +++ TextFields +++ //
			txtDOFirst = new Ext.form.TextField({
				disabled: true,
				allowBlank: true,
				tabIndex: tabOffset + 611,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				width: 250,
				hideLabel: true
			});
			txtDOSecond = new Ext.form.TextField({
				disabled: true,
				tabIndex: tabOffset + 614,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				allowBlank: true,
				width: 250,
				hideLabel: true
			});
			// --- TextFields --- //

			// +++ ComboBoxes +++ //
			// General Tab
			cmbServDb = new Ext.form.ComboBox({
				store: storeServDb,
				tabIndex: tabOffset + 100,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				tpl: new Ext.XTemplate('<tpl for=".">', '<div class="x-combo-list-item">', '<tpl if="type == \'database\'">', '<span style="cursor: default;">&#160;&#160;&#160;{name}</span>', '</tpl>', '<tpl if="type == \'server\'">', '<span style="cursor: default;">{name}</span>', '</tpl>', '</div>', '</tpl>'),
				listeners: {
					select: _cmbServDbSelectionHandler
				},
				valueField: 'id',
				displayField: 'name'
			});
			cmbDim = new Ext.form.ComboBox({
				id: 'wSSE_dims_cmb',
				store: storeDims,
				tabIndex: tabOffset + 101,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				listeners: {
					select: _cmbDimSelectHandler
				},
				valueField: 'name',
				displayField: 'name'
			});
			cmbFirstA = new Ext.form.ComboBox({
				store: storeAlias,
				width: 100,
				tabIndex: tabOffset + 115,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				listeners: {
					select: function(thisCmb, record, index)
					{
						disableAutoPreview = true;
						_changeStateRbSoSoAlias();
						disableAutoPreview = false;

						_reqGetSubsetList();
					}
				},
				valueField: 'name',
				displayField: 'name',
				tpl: '<tpl for="."><div class="x-combo-list-item">{esc_name}</div></tpl>'
			});
			cmbSecondA = new Ext.form.ComboBox({
				store: storeAlias,
				tabIndex: tabOffset + 117,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				width: 100,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				listeners: {
					select: function()
					{
						disableAutoPreview = true;
						_changeStateRbSoSoAlias();
						disableAutoPreview = false;

						_reqGetSubsetList();
					}
				},
				valueField: 'name',
				displayField: 'name',
				tpl: '<tpl for="."><div class="x-combo-list-item">{esc_name}</div></tpl>'
			});

			// Sort Tab -> Sort befaviour -> By Attribute
			cmbSoSoAttr = new Ext.form.ComboBox({
				disabled: true,
				store: storeAttrs,
				tabIndex: tabOffset + 707,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'name',
				displayField: 'name',
				tpl: '<tpl for="."><div class="x-combo-list-item">{esc_name}</div></tpl>',
				listeners: {
					select: function()
					{
						_reqGetSubsetList();
					}
				}
			});

			// Hier Tab -> Hier
			cmbHHList = new Ext.ux.TreeComboBox({
				disabled: true,
				store: new Ext.data.SimpleStore({fields:[],data:[[]]}),
				hideLabel: true,
				editable: false,
				tabIndex: tabOffset + 203,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				triggerAction: 'all',
				mode: 'local',
				shadow: false,
				maxHeight: 200,
				tpl: '<tpl for="."><div style="height:200px"><div id="treecmbHHList"></div></div></tpl>',
				minListWidth: 250,
				selectedClass: '',
				onSelect: Ext.emptyFn
			});

			treecmbHHList = new Ext.tree.TreePanel({
				border: false,
				cls: 'x-tree-noicon',
				autoScroll: true,
				animate: false,
				enableDD: false,
				containerScroll: true,
				plugins: new Ext.ux.tree.TreeNodeMouseoverPlugin(),
				listeners: {
					append: function(thisT, parNode, node, index)
					{
						node.text = Jedox.palo.utils.escHTML(node.text);
					}
				},
				loader: new Ext.ux.tree.PagingTreeLoader({
					pagingModel: 'remote',
					baseParams: {name: 'root'},
					listeners: {
						beforeload: function(thisL, node, cb)
						{
							this.baseParams.name = node.attributes.name;
						}
					}
				}),
				root: new Ext.tree.AsyncTreeNode({
					text: "[All Elements]".localize(),
					draggable: false,
					id: 'root',
					name: 'root'
				})
			});

			treecmbHHList.on('click', function(node)
			{
				if (node.attributes.name == 'root' && node.text == "[All Elements]".localize())
					cmbHHList.setValue("[All Elements]".localize());
				else
					cmbHHList.setValue(node.attributes.name);
				cmbHHList.collapse();

				treecmbHHList.getSelectionModel().select(node);

				_reqGetSubsetList();
			});
			treecmbHHList.on('beforeexpandnode', function(node)
					{
						cmbHHList.doCollapse = false;
					});
			treecmbHHList.on('beforecollapsenode', function(node)
					{
						cmbHHList.doCollapse = false;
					});
			cmbHHList.on('expand',function()
			{
				if (!treecmbHHList.rendered)
				{
					treecmbHHList.render('treecmbHHList');
					treecmbHHList.getRootNode().reload();
				}
			});
			cmbHHList.setValue("[All Elements]".localize());

			// Data Tab -> Settings
			cmbDSCubes = new Ext.form.ComboBox({
				disabled: true,
				fieldLabel: "Select Cube".localize() + ':',
				labelSeparator: '',
				tabIndex: tabOffset + 601,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				store: storeCubes,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'name',
				displayField: 'name',
				listeners: {
					select: _cmbDSCubesSelectionHandler
				}
			});
			cmbDSCriteria = new Ext.form.ComboBox({
				disabled: true,
				tabIndex: tabOffset + 604,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				fieldLabel: "Criteria".localize() + ':',
				labelSeparator: '',
				store: storeCriteria,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'name',
				displayField: 'name',
				listeners: {
					select: function()
					{
	//					_reqGetSubsetList();
					}
				}
			});
			cmbDSCriteria.setValue(storeCriteria.getAt(0).get('name'));

			// Data tab -> Slice operators
			cmbDOFirst = new Ext.form.ComboBox({
				disabled: true,
				width: 70,
				tabIndex: tabOffset + 610,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				store: storeOperands,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'name',
				displayField: 'name',
				listeners: {
					select: function(thisCombo, record, index)
					{
						if (record.get('name') != "[none]".localize())
						{
							txtDOFirst.enable();
							chbDOVFirst.enable();
							cmbDOSecond.enable();
						}
						else
						{
							chbDOVFirst.setValue(false);
							chbDOVFirst.disable();
							txtDOFirst.disable();
							if (cmbDOSecond.getValue() == "[none]".localize())
								cmbDOSecond.disable();
						}

	//					_reqGetSubsetList();
					}
				}
			});
			cmbDOFirst.setValue(storeOperands.getAt(0).get('name'));
			cmbDOSecond = new Ext.form.ComboBox({
				disabled: true,
				width: 70,
				tabIndex: tabOffset + 613,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				store: storeOperands,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'name',
				displayField: 'name',
				listeners: {
					select: function(thisCombo, record, index)
					{
						if (record.get('name') != "[none]".localize())
						{
							txtDOSecond.enable();
							chbDOVSecond.enable();
						}
						else
						{
							chbDOVSecond.setValue();
							txtDOSecond.disable();
							chbDOVSecond.disable();
							if (cmbDOFirst.getValue() == "[none]".localize())
								cmbDOSecond.disable();
						}

			//			_reqGetSubsetList();
					}
				}
			});
			cmbDOSecond.setValue(storeOperands.getAt(0).get('name'));
			// --- ComboBoxes --- //

			// +++ Radio Buttons +++ //
			// General Tab
			rbHierIndent = new Ext.form.Radio({
				name: 'radioHier',
				tabIndex: tabOffset + 120,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "subset_Indent".localize(),
				hideLabel: true,
				checked: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							spinHLStart.setMinAndCheck(1);
							spinHLEnd.setMinAndCheck(1);
							spinSoLvIndent.setMinAndCheck(1);

							_reqGetSubsetList();
						}
					}
				}
			});
			rbHierLevel = new Ext.form.Radio({
				name: 'radioHier',
				tabIndex: tabOffset + 121,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Level".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							spinHLStart.setMinAndCheck(0);
							spinHLEnd.setMinAndCheck(0);
							spinSoLvIndent.setMinAndCheck(0);

							_reqGetSubsetList();
						}
					}
				}
			});
			rbHierDepth = new Ext.form.Radio({
				name: 'radioHier',
				tabIndex: tabOffset + 122,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Depth".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							spinHLStart.setMinAndCheck(0);
							spinHLEnd.setMinAndCheck(0);
							spinSoLvIndent.setMinAndCheck(0);

							_reqGetSubsetList();
						}
					}
				}
			});
			rbLayoutFlat = new Ext.form.Radio({
				name: 'radioLayer',
				tabIndex: tabOffset + 105,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Flat".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							chbSoLvSort.setValue(false);
							chbSoLvSort.disable();

							chbParentsReverse.boxLabel = "Reverse".localize();
							if (chbParentsReverse.rendered)
								chbParentsReverse.wrap.child('.x-form-cb-label').update(chbParentsReverse.boxLabel);

							_reqGetSubsetList();
						}
					}
				}
			});
			rbLayoutHier = new Ext.form.Radio({
				name: 'radioLayer',
				boxLabel: "Hierarchy".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 106,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				checked: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							chbSoLvSort.enable();

							chbParentsReverse.boxLabel = "Show parents below children".localize()
							if (chbParentsReverse.rendered)
								chbParentsReverse.wrap.child('.x-form-cb-label').update(chbParentsReverse.boxLabel);

							_reqGetSubsetList();
						}
					}
				}
			});

			// Hierarchy tab
			rbHElemH = new Ext.form.Radio({
				disabled: true,
				checked: true,
				name: 'radioHElemHorHC',
				tabIndex: tabOffset + 201,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Filter elements hierarchically".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							panelchbHHExclusive.setVisible(true);
							panelspinHHListLength.setVisible(false);

							chbHType.enable();
							chbHLevel.enable();

							if (chbHType.checked)
							{
								rbHTBase.enable();
								rbHTCons.enable();
							}

							if (chbHLevel.checked)
								for (var i=0; i<elemsHL.length; i++)
									elemsHL[i].enable();

							_reqGetSubsetList();
						}
					}
				}
			});
			rbHElemHCyc = new Ext.form.Radio({
				disabled: true,
				name: 'radioHElemHorHC',
				tabIndex: tabOffset + 202,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Cyclic list".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							panelchbHHExclusive.setVisible(false);
							panelspinHHListLength.setVisible(true);

							chbHType.disable();
							chbHLevel.disable();

							if (chbHType.checked)
							{
								rbHTBase.disable();
								rbHTCons.disable();
							}

							if (chbHLevel.checked)
								for (var i=0; i<elemsHL.length; i++)
									elemsHL[i].disable();

							_reqGetSubsetList();
						}
					}
				}
			});
			rbHHBelow = new Ext.form.Radio({
				disabled: true,
				checked: true,
				tabIndex: tabOffset + 205,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioHH',
				boxLabel: "Below".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbHHAbove = new Ext.form.Radio({
				disabled: true,
				tabIndex: tabOffset + 206,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioHH',
				boxLabel: "Above".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbHTCons = new Ext.form.Radio({
				disabled: true,
				checked: true,
				tabIndex: tabOffset + 211,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioHT',
				boxLabel: "Consolidated".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbHTBase = new Ext.form.Radio({
				disabled: true,
				tabIndex: tabOffset + 212,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioHT',
				boxLabel: "Base Elements".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});

			// Picklist Tab
			rbPBFront = new Ext.form.Radio({
				disabled: true,
				checked: true,
				tabIndex: tabOffset + 410,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioPB',
				boxLabel: '<b>' + "FRONT".localize() + '</b>',
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbPBBack = new Ext.form.Radio({
				disabled: true,
				tabIndex: tabOffset + 411,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioPB',
				boxLabel: '<b>' + "BACK".localize() + '</b>',
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbPBMerge = new Ext.form.Radio({
				disabled: true,
				name: 'radioPB',
				tabIndex: tabOffset + 412,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: '<b>' + "MERGE".localize() + '</b>',
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbPBSubtract = new Ext.form.Radio({
				disabled: true,
				name: 'radioPB',
				tabIndex: tabOffset + 413,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: '<b>' + "SUBTRACT".localize() + '</b>',
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});

			// Sort Tab
			rbSoSoDef = new Ext.form.Radio({
				checked: true,
				name: 'radioSoSo',
				tabIndex: tabOffset + 701,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "By Definition".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbSoSoElem = new Ext.form.Radio({
				name: 'radioSoSo',
				boxLabel: "By Element name".localize(),
				tabIndex: tabOffset + 702,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbSoSoAlias = new Ext.form.Radio({
				disabled: true,
				name: 'radioSoSo',
				tabIndex: tabOffset + 703,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "By Alias".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbSoSoVal = new Ext.form.Radio({
				disabled: true,
				name: 'radioSoSo',
				tabIndex: tabOffset + 704,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "By Value".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbSoSoAttr = new Ext.form.Radio({
				disabled: true,
				tabIndex: tabOffset + 706,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioSoSo',
				boxLabel: "By Attribute".localize() + '&nbsp;&nbsp;&nbsp;',
				hideLabel: true,
				listeners: {
					check: function (thisRb, isChecked)
					{
						if (isChecked)
						{
							chbSoSoVCriteria.setValue(false);
							chbSoSoVCriteria.disable();

							cmbSoSoAttr.enable();
							chbSoSoVAttr.enable();
							_reqGetSubsetList();
						}
						else
						{
							chbSoSoVCriteria.enable();

							chbSoSoVAttr.setValue(false);
							chbSoSoVAttr.disable();
							cmbSoSoAttr.disable();
						}
					}
				}
			});
			rbSoTyElems = new Ext.form.Radio({
				checked: true,
				name: 'radioSoType',
				boxLabel: "All Elements".localize(),
				tabIndex: tabOffset + 720,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbSoTyBase = new Ext.form.Radio({
				name: 'radioSoType',
				boxLabel: "Base Elements Only".localize(),
				tabIndex: tabOffset + 721,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			rbSoTyCons = new Ext.form.Radio({
				name: 'radioSoType',
				boxLabel: "Consolidated Elements Only".localize(),
				tabIndex: tabOffset + 722,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							_reqGetSubsetList();
					}
				}
			});
			// --- Radio Buttons --- //

			// +++ ChechBoxes +++ //
			// General Tab
			chbLayoutDouble = new Ext.form.Checkbox({
				boxLabel: "Show duplicates".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 111,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				checked: true,
				listeners: {
					check: function(thisChb, isChecked)
					{
						_reqGetSubsetList();
					}
				}
			});
			chbLayoutChildren = new Ext.form.Checkbox({
				boxLabel: "Show children of hidden elements".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 110,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				checked: true,
				listeners: {
					render: function(thisCmp)
					{
						Ext.get(thisCmp.id).parent().parent().setStyle('overflow', 'hidden');
					},
					check: function(thisChb, isChecked)
					{
						_reqGetSubsetList();
					}
				}
			});
			chbParentsReverse = new Ext.form.Checkbox({
				boxLabel: "Show parents below children".localize(),
				tabIndex: tabOffset + 107,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisChb, isChecked)
					{
						_reqGetSubsetList();
					}
				}
			});
			chbAutoPreview = new Ext.form.Checkbox({
				checked: true,
				tabIndex: tabOffset + 1000,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Auto".localize(),
				hideLabel: true
			});
			chbQuickPreview = new Ext.form.Checkbox({
				checked: true,
				boxLabel: "Quick".localize(),
				tabIndex: tabOffset + 1001,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisChb, isChecked)
					{
						_reqGetSubsetList();
					}
				}
			});

			// Hier Tab
			chbHEnable = new Ext.form.Checkbox({
				boxLabel: "Activate this filter".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 200,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					check: function(thisCb, isChecked)
					{
						var funcName = 'disable';
						if (isChecked)
							funcName = 'enable';
						else
						{
							chbHHVList.setValue(false);
							chbHHVBelowAbove.setValue(false);
							chbHHVExclusiveList.setValue(false);
							chbHVType.setValue(false);
							chbHLVStart.setValue(false);
							chbHLVEnd.setValue(false);
						}
						_updateHierTab(funcName);

						_reqGetSubsetList();
					}
				}
			});
			chbHHExclusive = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 208,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Exclusive".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						_reqGetSubsetList();
					}
				}
			});
			chbHType = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Filter Element by type".localize(),
				tabIndex: tabOffset + 210,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							rbHTBase.enable();
							rbHTCons.enable();

							chbHVType.enable();
						}
						else
						{
							rbHTBase.disable();
							rbHTCons.disable();

							chbHVType.setValue(false);
							chbHVType.disable();
						}

						_reqGetSubsetList();
					}
				}
			});
			chbHLevel = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Filter elements by Level".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 215,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							for (var i=0; i<elemsHL.length; i++)
								elemsHL[i].enable();

							chbHLVStart.enable();
							chbHLVEnd.enable();
						}
						else
						{
							for (var i=0; i<elemsHL.length; i++)
								elemsHL[i].disable();

							chbHLVStart.setValue(false);
							chbHLVEnd.setValue(false);
							chbHLVStart.disable();
							chbHLVEnd.disable();
						}

						_reqGetSubsetList();
					}
				}
			});

			// Text Tab
			chbTEnable = new Ext.form.Checkbox({
				boxLabel: "Activate this filter".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 300,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					check: function(thisCb, isChecked)
					{
						var funcName = 'disable';
						if (isChecked)
							funcName = 'enable';
						else
						{
							chbTSVPatterns.setValue(false);
							chbTSVPerl.setValue(false);
						}

						_updateTextTab(funcName);

						_reqGetSubsetList();
					}
				}
			});
			chbTSPerl = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 310,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "_subsetTextTabPerl".localize(),
				hideLabel: true
			});

			// Picklist Tab
			chbPEnable = new Ext.form.Checkbox({
				boxLabel: "Activate this filter".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 400,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					check: function(thisCb, isChecked)
					{
						var funcName = 'disable';
						if (isChecked)
							funcName = 'enable';
						else
						{
							chbPDVElems.setValue(false);
							chbPBVBehave.setValue(false);
						}

						_updatePicklistTab(funcName);

						_reqGetSubsetList();
					}
				}
			});

			// Attribute Tab
			chbAEnable = new Ext.form.Checkbox({
				boxLabel: "Activate this filter".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 500,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					check: function(thisCb, isChecked)
					{
						var funcName = 'disable';
						if (isChecked)
							funcName = 'enable';
						else
							chbASVAttrs.setValue(false);

						_updateAttributeTab(funcName);

						_reqGetSubsetList();
					}
				}
			});

			// Data Tab
			chbDEnable = new Ext.form.Checkbox({
				boxLabel: "Activate this filter".localize(),
				tabIndex: tabOffset + 600,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						var funcName = 'disable';
						if (isChecked)
							funcName = 'enable';
						else
						{
							chbDSVCube.setValue(false);
							chbDSVCriteria.setValue(false);
							chbDOVFirst.setValue(false);
							chbDOVSecond.setValue(false);
							chbD3VTop.setValue(false);
							chbD3VUpper.setValue(false);
							chbD3VLower.setValue(false);
						}

						_updateDataTab(funcName);
					}
				}
			});
			chbD3Topmost = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Take topmost elements".localize(),
				tabIndex: tabOffset + 620,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							spinD3Topmost.enable();
							chbD3VTop.enable();
						}
						else
						{
							chbD3VTop.setValue(false);
							spinD3Topmost.disable();
							chbD3VTop.disable();
						}
					}
				}
			});
			chbD3Upper = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Take all upper elements up to %".localize(),
				tabIndex: tabOffset + 630,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							spinD3Upper.enable();
							chbD3VUpper.enable();
						}
						else
						{
							chbD3VUpper.setValue(false);
							spinD3Upper.disable();
							chbD3VUpper.disable();
						}
					}
				}
			});
			chbD3Lower = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Take all lower elements up to %".localize(),
				tabIndex: tabOffset + 640,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							spinD3Lower.enable();
							chbD3VLower.enable();
						}
						else
						{
							chbD3VLower.setValue(false);
							spinD3Lower.disable();
							chbD3VLower.disable();
						}
					}
				}
			});

			// Sort Tab
			chbSoOrReverse = new Ext.form.Checkbox({
				boxLabel: "Reverse".localize(),
				tabIndex: tabOffset + 710,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function()
					{
						_reqGetSubsetList();
					}
				}
			});
			chbSoLvSort = new Ext.form.Checkbox({
				boxLabel: "Sort at Level".localize(),
				tabIndex: tabOffset + 730,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							spinSoLvIndent.enable();
							chbSoLvVLevel.enable();
						}
						else
						{
							chbSoLvVLevel.setValue(false);
							spinSoLvIndent.disable();
							chbSoLvVLevel.disable();
						}

						_reqGetSubsetList();
					}
				}
			});
				// variables
			chbVFirstA = new Ext.form.Checkbox({
				boxLabel: "Variable".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 116,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
							_addVarToList('_varFirstA', "Alias 1".localize());
						else
							_removeVarFromList('_varFirstA');

						cmbFirstA[_getActionByPerm(true, !isChecked)]();
						disableAutoPreview = true;
						_changeStateRbSoSoAlias();
						disableAutoPreview = false;
					}
				}
			});
			chbVSecondA = new Ext.form.Checkbox({
				boxLabel: "Variable".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 118,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
							_addVarToList('_varSecondA', "Alias 2".localize());
						else
							_removeVarFromList('_varSecondA');

						cmbSecondA[_getActionByPerm(true, !isChecked)]();
						disableAutoPreview = true;
						_changeStateRbSoSoAlias();
						disableAutoPreview = false;
					}
				}
			});
				// hier - variables
			chbHHVList = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 204,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varHHList', "Element".localize());
							cmbHHList.disable();
						}
						else
						{
							_removeVarFromList('_varHHList');
							cmbHHList.enable();
						}
					}
				}
			});
			chbHHVBelowAbove = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 207,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varHHBelowAbove', "Above".localize());
							rbHHAbove.disable();
							rbHHBelow.disable();
						}
						else
						{
							_removeVarFromList('_varHHBelowAbove');
							rbHHAbove.enable();
							rbHHBelow.enable();
						}
					}
				}
			});
			chbHHVExclusiveList = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 209,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							if (_getRbVal(rbHElemHCyc))
							{
								_addVarToList('_varHHExclusiveList', "List Length".localize());
								spinHHListLength.disable();
							}
							else
							{
								_addVarToList('_varHHExclusiveList', "Exclusive".localize());
								chbHHExclusive.disable();
							}
						}
						else
						{
							_removeVarFromList('_varHHExclusiveList');

							if (_getRbVal(rbHElemHCyc))
								spinHHListLength.enable();
							else
								chbHHExclusive.enable();
						}
					}
				}
			});
			chbHVType = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 214,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varHType', "Hide".localize());
							rbHTCons.disable();
							rbHTBase.disable();
						}
						else
						{
							_removeVarFromList('_varHType');
							rbHTCons.enable();
							rbHTBase.enable();
						}
					}
				}
			});
			chbHLVStart = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				tabIndex: tabOffset + 222,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varHLStart', "Level Start".localize());
							spinHLStart.disable();
						}
						else
						{
							_removeVarFromList('_varHLStart');
							spinHLStart.enable();
						}
					}
				}
			});
			chbHLVEnd = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 224,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varHLEnd', "Level End".localize());
							spinHLEnd.disable();
						}
						else
						{
							_removeVarFromList('_varHLEnd');
							spinHLEnd.enable();
						}
					}
				}
			});
				// - text - variables
			chbTSVPatterns = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 301,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varTSPatterns', "RegExes".localize());
							viewTextPatterns.disable();
							viewTextPatternsEditor.disable();
						}
						else
						{
							_removeVarFromList('_varTSPatterns');
							viewTextPatterns.enable();
							viewTextPatternsEditor.enable();
						}
					}
				}
			});
			chbTSVPerl = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 311,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varTSPerl', "RegEx".localize());
							chbTSPerl.disable();
						}
						else
						{
							_removeVarFromList('_varTSPerl');
							chbTSPerl.enable();
						}
					}
				}
			});
				// - picklist - variables
			chbPDVElems = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 402,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varPElems', "Picklist".localize());
							viewPDElems.disable();
							btnPDEdit.disable();
						}
						else
						{
							_removeVarFromList('_varPElems');
							viewPDElems.enable();
							btnPDEdit.enable();
						}
					}
				}
			});
			chbPBVBehave = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 420,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varPBehave', "Picklist Type".localize());
							rbPBFront.disable();
							rbPBBack.disable();
							rbPBMerge.disable();
							rbPBSubtract.disable();
						}
						else
						{
							_removeVarFromList('_varPBehave');
							rbPBFront.enable();
							rbPBBack.enable();
							rbPBMerge.enable();
							rbPBSubtract.enable();
						}
					}
				}
			});
				// - attributes - variables
			chbASVAttrs = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 501,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							// clear list of elements in attribute list
							var tmpStoreData = [];
							for (var i=0; i<storeAttrs.getCount(); i++)
								tmpStoreData[i] = '';
							storeASAttrs.loadData([tmpStoreData]);

							_addVarToList('_varASAttrs', "Attributes".localize());
							gridASAttrs.disable();
						}
						else
						{
							_removeVarFromList('_varASAttrs');
							gridASAttrs.enable();
						}
					}
				}
			});
				// - data - variables
			chbDSVCube = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 602,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varDSCube', "Cube".localize());
							cmbDSCubes.disable();
						}
						else
						{
							_removeVarFromList('_varDSCube');
							cmbDSCubes.enable();
						}
					}
				}
			});
			chbDSVCriteria = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 605,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varDSCriteria', "Criteria".localize());
							cmbDSCriteria.disable();
						}
						else
						{
							_removeVarFromList('_varDSCriteria');
							cmbDSCriteria.enable();
						}
					}
				}
			});
			chbDOVFirst = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 612,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varDOFirst', "Par1".localize());
							txtDOFirst.disable();
						}
						else
						{
							_removeVarFromList('_varDOFirst');
							txtDOFirst.enable();
						}
					}
				}
			});
			chbDOVSecond = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 615,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varDOSecond', "Par2".localize());
							txtDOSecond.disable();
						}
						else
						{
							_removeVarFromList('_varDOSecond');
							txtDOSecond.enable();
						}
					}
				}
			});
			chbD3VTop = new Ext.form.Checkbox({
				disabled: true,
				tabIndex: tabOffset + 622,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varD3Topmost', "Topmost".localize());
							spinD3Topmost.disable();
						}
						else
						{
							_removeVarFromList('_varD3Topmost');
							spinD3Topmost.enable();
						}
					}
				}
			});
			chbD3VUpper = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 632,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varD3Upper', "Upper".localize());
							spinD3Upper.disable();
						}
						else
						{
							_removeVarFromList('_varD3Upper');
							spinD3Upper.enable();
						}
					}
				}
			});
			chbD3VLower = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 642,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varD3Lower', "Lower".localize());
							spinD3Lower.disable();
						}
						else
						{
							_removeVarFromList('_varD3Lower');
							spinD3Lower.enable();
						}
					}
				}
			});
				// - sort - variables
			chbSoSoVCriteria = new Ext.form.Checkbox({
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 705,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varSoSoCriteria', "Criteria".localize());
							rbSoSoDef.disable();
							rbSoSoElem.disable();
							rbSoSoAlias.disable();
							rbSoSoVal.disable();
						}
						else
						{
							_removeVarFromList('_varSoSoCriteria');
							rbSoSoDef.enable();
							rbSoSoElem.enable();
							//rbSoSoAlias.enable(); // TODO
							if (_getRbVal(chbDEnable))
								rbSoSoVal.enable();
						}
					}
				}
			});
			chbSoSoVAttr = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 709,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							chbSoSoVCriteria.setValue(false);
							_addVarToList('_varSoSoAttr', "Sort Attribute".localize());

							cmbSoSoAttr.disable();
							rbSoSoAttr.disable();
						}
						else
						{
							_removeVarFromList('_varSoSoAttr');
							rbSoSoAttr.enable();
							cmbSoSoAttr.enable();
						}
					}
				}
			});
			chbSoOrVReverse = new Ext.form.Checkbox({
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 711,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varSoOrReverse', "Reverse".localize());
							disableAutoPreview = true;
							chbSoOrReverse.setValue(false);
							disableAutoPreview = false;
							chbSoOrReverse.disable();
						}
						else
						{
							_removeVarFromList('_varSoOrReverse');
							chbSoOrReverse.enable();
						}
					}
				}
			});
			chbSoTyVType = new Ext.form.Checkbox({
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 725,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varSoTyType', "Type Limitation".localize());
							rbSoTyElems.disable();
							rbSoTyBase.disable();
							rbSoTyCons.disable();
						}
						else
						{
							_removeVarFromList('_varSoTyType');
							rbSoTyElems.enable();
							rbSoTyBase.enable();
							rbSoTyCons.enable();
						}
					}
				}
			});
			chbSoLvVLevel = new Ext.form.Checkbox({
				disabled: true,
				boxLabel: "Variable".localize(),
				tabIndex: tabOffset + 733,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				hideLabel: true,
				listeners: {
					check: function(thisCb, isChecked)
					{
						if (isChecked)
						{
							_addVarToList('_varSoLvLevel', "Sort Level".localize());
							spinSoLvIndent.disable();
						}
						else
						{
							_removeVarFromList('_varSoLvLevel');
							spinSoLvIndent.enable();
						}
					}
				}
			});
			// --- CheckBoxes --- //

			// +++ Buttons +++ //
			// Global buttons
			btnSave = new Ext.Button({
				disabled: true,
				ctCls: 'subsetEditorBtns',
				text: "Save".localize(),
				tabIndex: tabOffset + 990,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				listeners: {
					click: function()
					{
						var tmpView;
						if (selectedWestPanel == 1)
							tmpView = viewLocalSubsets;
						else if (selectedWestPanel == 2)
							tmpView = viewGlobalSubsets;

						if ((tmpView) && (tmpView.getSelectionCount() > 0))
						{
							var subsetName = tmpView.getSelectedRecords()[0].get('name');
							var tmpObj = _generateSubsetObject();
							settings = [servId, dbName, cmbDim.getValue(), subsetName, selectedWestPanel];
							paloRpcServer.savePaloSubset([settings, tmpObj]);
							Jedox.palo.utils.showWaitMsg("_msg: update Subset".localize(), "Storing".localize().concat('...'));
						}
						else
							Ext.MessageBox.prompt("New Subset".localize(), "Enter name for Subset".localize() + ":", _newSubset);
					}
				}
			});
			btnPaste = new Ext.Button({
				id: 'wSSE_ok_btn',
				ctCls: 'subsetEditorBtns',
				tabIndex: tabOffset + 991,
				disabled: ((Jedox.palo.workIn != Jedox.palo.GRID) && !(conf && (conf.mode == 2))),
				text: ((conf && (conf.mode == 1 || conf.mode == 2 || conf.mode == 3 || conf.mode == 4)) ? "OK".localize() : "Paste".localize()),
				handler: function()
					{
						var tmpView;
						if (selectedWestPanel == 1)
							tmpView = viewLocalSubsets;
						else if (selectedWestPanel == 2)
							tmpView = viewGlobalSubsets;

						if (conf && conf.mode == 1)
						{
							dynarangeConf._preview_val = _getPreviewValue();

							if ((tmpView) && (tmpView.getSelectionCount() > 0))
								dynarangeConf._gendata = [[servId, dbName, cmbDim.getValue(), tmpView.getSelectedRecords()[0].get('name'), selectedWestPanel], _generateSubsetObject(), _getNumOfFilledVars()];
							else if (!cmbDim.disabled && cmbDim.getValue())
								dynarangeConf._gendata = [[servId, dbName, cmbDim.getValue(), '', 0], _generateSubsetObject(), _getNumOfFilledVars()];

							paloRpcServer.setDynarangeList(dynarangeConf);
						}
						else if (conf && (conf.mode == 3 || conf.mode == 4))
							paloRpcServer.handlerGetGeneratedSubsetFunc([1, 1, 2, 2, servId, dbName], cmbDim.getValue(), '', 0, _generateSubsetObject());
						else if ((!conf) || (conf.mode != 2))
						{
							if (Jedox.palo.workIn == Jedox.palo.GRID)
							{
								var env = Jedox.wss.app.environment;
								var activeBook = Jedox.wss.app.activeBook;
								var upperLeftCoords = env.defaultSelection.getActiveRange().getUpperLeft();
								var lowerRightCoords = env.defaultSelection.getActiveRange().getLowerRight();

								var settings = [upperLeftCoords.getX(), upperLeftCoords.getY(), lowerRightCoords.getX(), lowerRightCoords.getY(), servId, dbName];
								if ((tmpView) && (tmpView.getSelectionCount() > 0))
									Jedox.backend.rpc_cb('palo_handlerGetGeneratedSubsetFunc', [settings, cmbDim.getValue(), tmpView.getSelectedRecords()[0].get('name'), selectedWestPanel]);
								else if (!cmbDim.disabled && cmbDim.getValue())
									Jedox.backend.rpc_cb('palo_handlerGetGeneratedSubsetFunc', [settings, cmbDim.getValue(), '', 0, _generateSubsetObject()]);
							}
						}

						if (!(conf && (conf.mode == 3 || conf.mode == 4)))
							that.win.close();
					}
			});
			btnClose = new Ext.Button({
				id: 'wSSE_close_btn',
				text: "Close".localize(),
				tabIndex: tabOffset + 992,
				ctCls: 'subsetEditorBtns'.concat(' ',Jedox.kbd.Base.tags.NO_ENTER),
				handler: function()
					{
						that.win.close();
					}
			});
			btnRefreshPreview = new Ext.Button({
				text: "Refresh".localize(),
				ctCls: 'subsetEditorBtns',
				tabIndex: tabOffset + 1002,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				width: '70px',
				listeners: {
					click: function()
					{
						_reqGetSubsetList(true);
					}
				}
			});
			panelbtnRefreshPreview = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				autoWidth: true,
				autoHeight: true,
				items: [btnRefreshPreview]
			});
			btnSubsetActions = {
				newB: new Ext.Button({
					disabled: true,
					cls: 'modellerImageButton',
					tabIndex: tabOffset + 1,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					iconCls: 'palo_icon_cl_create',
					handler: function()
					{
						Ext.MessageBox.prompt("New Subset".localize(), "Enter name for Subset".localize() + ":", _newSubset);
					}
				}),
				deleteB: new Ext.Button({
					disabled: true,
					cls: 'modellerImageButton',
					tabIndex: tabOffset + 2,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					iconCls: 'palo_icon_cl_delete',
					handler: function()
					{
						Ext.MessageBox.show({
							title: "Delete Subset".localize(),
							msg: "_msg: Delete Subset".localize(),
							buttons: Ext.MessageBox.OKCANCEL,
							fn: _deleteSubset,
							icon: Ext.MessageBox.QUESTION
						});
					}
				}),
				editB: new Ext.Button({
					disabled: true,
					cls: 'modellerImageButton',
					tabIndex: tabOffset + 3,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					iconCls: 'palo_icon_cl_edit',
					handler: function()
					{
						var tmpView;
						if (selectedWestPanel == 1)
							tmpView = viewLocalSubsets;
						else if (selectedWestPanel == 2)
							tmpView = viewGlobalSubsets;

						if (tmpView)
						{
							var ssName = ((tmpView.getSelectedIndexes().length > 0) ? tmpView.getSelectedRecords()[0].get('name') : null);
							if (ssName)
								Ext.MessageBox.show({
									title: "Rename Subset".localize(),
									msg: "Enter new name for Subset".localize() + ":",
									buttons: Ext.MessageBox.OKCANCEL,
									fn: _renameSubset,
									prompt: true,
									value: ssName
								});
						}
					}
				})
			};
			panelbtnSubsetActions = new Ext.Panel({
				region: 'south',
				layout: 'table',
				border: false,
				bodyStyle: 'background-color: transparent;',
				height: 30,
				maxHeight: 30,
				minHeight: 30,
				autoWidth: true,
				split: true,
				items: [btnSubsetActions.newB, btnSubsetActions.deleteB, btnSubsetActions.editB]
			});

			// Picklist Tab
			btnPDEdit = new Ext.Button({
				disabled: true,
				tabIndex: tabOffset + 401,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				ctCls: 'subsetEditorBtns',
				text: "Edit".localize(),
				width: '70px',
				listeners: {
					click: function()
					{
						var preSelList = [],
							storeSize = storePDElems.getCount();
						for (var i=0; i<storeSize; i++)
							preSelList[preSelList.length] = [storePDElems.getAt(i).get('name'), null];

						if (Jedox.palo.workIn == Jedox.palo.STUDIO)
							Jedox.gen.load(Jedox.studio.app.dynJSRegistry.chooseElement, [{
								working_mode: 4,
								parent_object: {cb_fnc: _setSelectedPicklistElements},
								serv_id: servId,
								db_name: dbName,
								dim_name: cmbDim.getValue(),
								edit_data: (storeSize > 0) ? preSelList : null
							}]);
						else if (Jedox.palo.workIn == Jedox.palo.GRID)
							Jedox.gen.load(Jedox.wss.app.dynJSRegistry.chooseElement, [{
								working_mode: 4,
								parent_object: {cb_fnc: _setSelectedPicklistElements},
								serv_id: servId,
								db_name: dbName,
								dim_name: cmbDim.getValue(),
								edit_data: (storeSize > 0) ? preSelList : null
							}]);
					}
				}
			});
			// --- Buttons --- //

			// +++ FieldSets +++ //
			// General Tab
			fsServer = new Ext.form.FieldSet({
				title: "Server".localize(),
				collapsible: false,
				items: [lblServDb, cmbServDb, lblDim, cmbDim]
			});
			fsAlias = new Ext.form.FieldSet({
				title: "Alias".localize(),
				collapsible: false,
				items: [_addFSPanels([
							lblFirstA, cmbFirstA, lblSecondA, cmbSecondA
						],
						[
							new SseSpacer({labelStyle: 'height:10px;'}),
							chbVFirstA,
							new SseSpacer({labelStyle: 'height:10px;'}),
							chbVSecondA
						],
						{left_proc: 0.65, right_proc: 0.35}
				)]
			});
			fsLayout = new Ext.form.FieldSet({
				title: "Layout".localize(),
				collapsible: false,
				items: [rbLayoutFlat, rbLayoutHier, chbParentsReverse]
			});
			fsHierarchy = new Ext.form.FieldSet({
				title: "Hierarchy enumeration".localize(),
				collapsible: false,
				items: [rbHierIndent, rbHierLevel, rbHierDepth]
			});
			fsOptional = new Ext.form.FieldSet({
				title: "Optional Settings".localize(),
				collapsible: false,
				items: [chbLayoutChildren, chbLayoutDouble]
			});

			// Hier Tab
			fsHHier = new Ext.form.FieldSet({
				title: "Hierarchy".localize(),
				collapsible: false,
				items: [_addFSPanels([
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [rbHElemH]
									}),
									{
										border: false,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;&nbsp;&nbsp;'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [rbHElemHCyc]
									})
								]
							}),
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									{
										border: false,
										width: _config._tabSize,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [cmbHHList]
									})
								]
							}),
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									{
										border: false,
										width: _config._tabSize,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [rbHHBelow]
									})
								]
							}),
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									{
										border: false,
										width: _config._tabSize,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [rbHHAbove]
									})
								]
							}),
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									{
										border: false,
										width: _config._tabSize,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									panelchbHHExclusive = new Ext.Panel({
										hideMode: 'offsets',
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [chbHHExclusive]
									}),
									panelspinHHListLength = new Ext.Panel({
										border: false,
										hideMode: 'offsets',
										layout: 'column',
										bodyStyle: 'background-color:transparent;',
										width: 150,
										autoHeight: true,
										items: [
											lblHHListLength = new Ext.form.Label({
												cls: 'x-form-item',
												width: 80,
												style: 'padding-top:2px;',
												text: "List length".localize() + ':'
											}),
											new Ext.Panel({
												border: false,
												layout: 'form',
												bodyStyle: 'background-color:transparent;',
												bodyCfg: {
													cls: 'spinner-panel-scroll-hide'
												},
												autoWidth: true,
												autoHeight: true,
												items: [spinHHListLength]
											})
										]
									})
								]
							}),
							chbHType,
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									{
										border: false,
										width: _config._tabSize,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [rbHTCons]
									})
								]
							}),
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									{
										border: false,
										width: _config._tabSize,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [rbHTBase]
									})
								]
							}),
							chbHLevel,
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									{
										border: false,
										width: _config._tabSize,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									elemsHL[elemsHL.length] = new Ext.form.Label({
										disabled: true,
										cls: 'x-form-item',
										width: 80,
										style: 'padding-top:2px;',
										text: "Start level".localize()
									}),
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										bodyCfg: {
											cls: 'spinner-panel-scroll-hide'
										},
										autoWidth: true,
										autoHeight: true,
										items: [elemsHL[elemsHL.length] = spinHLStart]
									}),
									{
										border: false,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;&nbsp;&nbsp;'
									},
									elemsHL[elemsHL.length] = new Ext.form.Label({
										disabled: true,
										cls: 'x-form-item',
										style: 'padding-top:2px;',
										text: "Indent Enumeration".localize()
									})
								]
							}),
							new Ext.Panel({
								border: false,
								layout: 'column',
								bodyStyle: 'background-color:transparent;',
								autoWidth: true,
								autoHeight: true,
								items: [
									{
										border: false,
										width: _config._tabSize,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									elemsHL[elemsHL.length] = new Ext.form.Label({
										disabled: true,
										cls: 'x-form-item',
										width: 80,
										style: 'padding-top:2px;',
										text: "End level".localize()
									}),
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										bodyCfg: {
											cls: 'spinner-panel-scroll-hide'
										},
										autoWidth: true,
										autoHeight: true,
										items: [elemsHL[elemsHL.length] = spinHLEnd]
									}),
									{
										border: false,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;&nbsp;&nbsp;'
									},
									elemsHL[elemsHL.length] = new Ext.form.Label({
										disabled: true,
										cls: 'x-form-item',
										style: 'padding-top:2px;',
										text: "Indent Enumeration".localize()
									})
								]
							})
					],
					[new SseSpacer({labelStyle: 'height:16px;'}), chbHHVList, new SseSpacer({labelStyle: 'height:0px;'}), chbHHVBelowAbove, new SseSpacer({labelStyle: 'height:3px;'}), chbHHVExclusiveList, new SseSpacer({labelStyle: 'height:26px;'}), chbHVType, new SseSpacer(), new SseSpacer({labelStyle: 'height:10px;'}), chbHLVStart, chbHLVEnd],
					{left_proc: 0.7, right_proc: 0.3}
				)]
			});
			panelspinHHListLength.setVisible(false);

			// Text Tab
			fsTSettings = new Ext.form.FieldSet({
				title: "Settings".localize(),
				collapsible: false,
				items: [
					_addFSPanels([panelviewTextPatterns = new Ext.Panel({
							layout: 'fit',
							items: [viewTextPatterns]
						})],
						[new Ext.Panel({
							border: false,
							layout: 'column',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								{
									border: false,
									bodyStyle: 'background-color:transparent;',
									html: '&nbsp;&nbsp;&nbsp;'
								},
								new Ext.Panel({
									border: false,
									layout: 'form',
									bodyStyle: 'background-color:transparent;',
									autoWidth: true,
									autoHeight: true,
									items: [chbTSVPatterns]
								})
							]
						})],
						{left_proc: 0.7, right_proc: 0.3}
					),
					_addFSPanels(
						[chbTSPerl],
						[new Ext.Panel({
							border: false,
							layout: 'column',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								{
									border: false,
									bodyStyle: 'background-color:transparent;',
									html: '&nbsp;&nbsp;&nbsp;'
								},
								new Ext.Panel({
									border: false,
									layout: 'form',
									bodyStyle: 'background-color:transparent;',
									autoWidth: true,
									autoHeight: true,
									items: [chbTSVPerl]
								})
							]
						})],
						{left_proc: 0.7, right_proc: 0.3}
					),
					lblTSExample
				]
			});

			// Picklist Tab
			fsPDimCont = new Ext.form.FieldSet({
				title: "Dimension Contents".localize(),
				collapsible: false,
				items: [_addFSPanels([
						new Ext.Panel({
							layout: 'column',
							border: false,
							autoWidth: true,
							autoHeight: true,
							bodyStyle: 'background-color: transparent;',
							items: [new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [lblPDElems = new Ext.form.Label({
											disabled: true,
											cls: 'x-form-item',
											width: 80,
											style: 'padding-top:2px;',
											text: "Elements".localize() + ':'
										})]
									}),
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;padding-bottom:3px;',
										autoWidth: true,
										autoHeight: true,
										items: [btnPDEdit]
									})

							]
						})],
						[chbPDVElems],
						{left_proc: 0.7, right_proc: 0.3}
					),
					panelviewPDElems = new Ext.Panel({
						layout: 'fit',
						items: [viewPDElems]
					})
				]
			});
			fsPBehave = new Ext.form.FieldSet({
				title: "Behaviour".localize(),
				collapsible: false,
				items: [_addFSPanels(
							[lblPBInsertType, rbPBFront, rbPBBack, rbPBMerge, rbPBSubtract],
							[new SseSpacer({labelStyle: 'height:85px;'}), chbPBVBehave],
							{left_proc: 0.7, right_proc: 0.3}
				)]
			});

			// Attribute Tab
			fsASettings = new Ext.form.FieldSet({
				title: "Settings".localize(),
				collapsible: false,
				items: [
					lblASView,
					_addFSPanels(
						[
							panelgridASAttrs = new Ext.Panel({
								border: false,
								layout: 'fit',
								items: [gridASAttrs]
							})
						],
						[new Ext.Panel({
							border: false,
							layout: 'column',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								{
									border: false,
									bodyStyle: 'background-color:transparent;',
									html: '&nbsp;&nbsp;&nbsp;'
								},
								new Ext.Panel({
									border: false,
									layout: 'form',
									bodyStyle: 'background-color:transparent;',
									autoWidth: true,
									autoHeight: true,
									items: [chbASVAttrs]
								})
							]
						})],
						{left_proc: 0.8, right_proc: 0.2}
					),
					lblASExample
				]
			});

			// Data Tab
			fsDSettings = new Ext.form.FieldSet({
				title: "Settings".localize(),
				collapsible: false,
				items: [
					_addFSPanels(
						[cmbDSCubes],
						[chbDSVCube],
						{left_proc: 0.8, right_proc: 0.2}
					),
					panelgridDSCubeDims = new Ext.Panel({
						layout: 'fit',
						items: [gridDSCubeDims]
					}),
					_addFSPanels(
						[new Ext.Panel({
							border: false,
							bodyStyle: 'background-color:transparent;padding-top:3px;',
							layout: 'form',
							items: [cmbDSCriteria]
						})],
						[new Ext.Panel({
							border: false,
							bodyStyle: 'background-color:transparent;padding-top:3px;',
							layout: 'form',
							items: [chbDSVCriteria]
						})],
						{left_proc: 0.8, right_proc: 0.2}
					)
				]
			});
			fsDSlice = new Ext.form.FieldSet({
				title: "Slice operators".localize(),
				collapsible: false,
				items: [
					_addFSPanels(
						[new Ext.Panel({
							layout: 'column',
							border: false,
							autoWidth: true,
							autoHeight: true,
							bodyStyle: 'background-color: transparent;',
							items: [new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [cmbDOFirst]
									}),
									{
										border: false,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;&nbsp;&nbsp;'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [txtDOFirst]
									})
							]
						})],
						[chbDOVFirst],
						{left_proc: 0.8, right_proc: 0.2}
					),
					new Ext.form.Label({
						cls: 'x-form-item',
						text: "AND".localize()
					}),
					_addFSPanels(
						[new Ext.Panel({
							layout: 'column',
							border: false,
							autoWidth: true,
							autoHeight: true,
							bodyStyle: 'background-color: transparent;',
							items: [new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [cmbDOSecond]
									}),
									{
										border: false,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;&nbsp;&nbsp;'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [txtDOSecond]
									})
							]
						})],
						[chbDOVSecond],
						{left_proc: 0.8, right_proc: 0.2}
					)
				]
			});
			fsDOptional = new Ext.form.FieldSet({
				title: "Optional Settings".localize(),
				collapsible: false,
				items: [_addFSPanels(
					[
						new Ext.Panel({
							layout: 'column',
							border: false,
							autoWidth: true,
							autoHeight: true,
							bodyStyle: 'background-color: transparent;',
							items: [new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [chbD3Topmost, chbD3Upper, chbD3Lower]
									}),
									{
										border: false,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;&nbsp;&nbsp;'
									},
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										bodyCfg: {
											cls: 'spinner-panel-scroll-hide'
										},
										autoWidth: true,
										autoHeight: true,
										items: [spinD3Topmost, spinD3Upper, spinD3Lower]
									})
							]
						})
					],
					[chbD3VTop, chbD3VUpper, chbD3VLower],
					{left_proc: 0.8, right_proc: 0.2}
				)]
			});

			// Sort Tab
			fsSoSorting = new Ext.form.FieldSet({
				title: "Sorting behaviour".localize(),
				collapsible: false,
				items: [
						_addFSPanels([
							rbSoSoDef, rbSoSoElem, rbSoSoAlias, rbSoSoVal,
							new Ext.Panel({
								layout: 'column',
								border:false,
								autoWidth: true,
								autoHeight: true,
								bodyStyle: 'background-color: transparent;',
								items: [new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [rbSoSoAttr]
									}),
									new Ext.Panel({
										border: false,
										layout: 'form',
										bodyStyle: 'background-color:transparent;',
										autoWidth: true,
										autoHeight: true,
										items: [cmbSoSoAttr]
									})
								]
							})
							],
							[
								new SseSpacer({labelStyle: 'height:26px;'}),
								chbSoSoVCriteria,
								new SseSpacer(),
								new SseSpacer({labelStyle: 'height:10px;'}),
								chbSoSoVAttr
						],
						{left_proc: .8, right_proc: .2}
					)
				]
			});
			fsSoOrder = new Ext.form.FieldSet({
				title: "Reverse Order".localize(),
				collapsible: false,
				items: [_addFSPanels([chbSoOrReverse], [chbSoOrVReverse], {left_proc: .8, right_proc: .2})]
			});
			fsSoType = new Ext.form.FieldSet({
				title: "Type Limitation".localize(),
				collapsible: false,
				items: [_addFSPanels([rbSoTyElems, rbSoTyBase, rbSoTyCons], [new SseSpacer({labelStyle: 'height:15px;'}), chbSoTyVType], {left_proc: .8, right_proc: .2})]
			});
			fsSoLevel = new Ext.form.FieldSet({
				title: "Sort at Level".localize(),
				collapsible: false,
				items: [_addFSPanels(
					[
						new Ext.Panel({
							layout: 'column',
							border:false,
							autoWidth: true,
							autoHeight: true,
							bodyStyle: 'background-color: transparent;',
							items: [new Ext.Panel({
									border: false,
									layout: 'form',
									bodyStyle: 'background-color:transparent;',
									autoWidth: true,
									autoHeight: true,
									items: [chbSoLvSort]
								}),
								new Ext.Panel({
									border: false,
									layout: 'form',
									bodyStyle: 'background-color:transparent;',
									bodyCfg: {
										cls: 'spinner-panel-scroll-hide'
									},
									autoWidth: true,
									autoHeight: true,
									items: [spinSoLvIndent]
								})
							]
						})
					],
					[chbSoLvVLevel],
					{left_proc: .8, right_proc: .2}
				)]
			});
			// --- FieldSets --- //

			var ieOffset10 = Ext.isIE? 10:0;
			var ieOffset20 = Ext.isIE? 20:0;

			// +++ Tabs +++ //
			tabGeneral = new Ext.Panel({
				title: "General".localize(),
				layout: 'absolute',
				border: false,
				bodyStyle: 'background-color: transparent;',
				listeners: {
					resize: function(thisObj, adjWidth, adjHeight, rawWidth, rawHeight)
					{
						var fsUpSize = {
							width: adjWidth / 2 - 2 * _marginSize,
							height: adjHeight * 2 / 5 - 2 * _marginSize-ieOffset10
						};
						var fsDownSize = {
							width: adjWidth / 2 - 2 * _marginSize,
							height: adjHeight * 3 / 5 - 2 * _marginSize-ieOffset20
						};
						fsServer.setPosition(_marginSize, _marginSize);
						fsServer.setSize(fsUpSize);
						fsAlias.setPosition(adjWidth / 2 + _marginSize, _marginSize);
						fsAlias.setSize(fsUpSize);

						fsLayout.setPosition(_marginSize, fsUpSize.height + _marginSize + ieOffset10);
						fsLayout.setSize({
							width: fsDownSize.width,
							height: fsDownSize.height * 3 / 5
						});

						fsOptional.setPosition(_marginSize, fsUpSize.height + fsDownSize.height * 3 / 5 + _marginSize + ieOffset20);
						fsOptional.setSize({
							width: fsDownSize.width,
							height: fsDownSize.height * 2 / 5
						});
						fsHierarchy.setPosition(adjWidth / 2 + _marginSize, fsUpSize.height + _marginSize + ieOffset10);
						fsHierarchy.setSize({width: fsDownSize.width, height: fsDownSize.height + ieOffset10});
					}
				},
				items: [fsServer, fsAlias, fsLayout, fsHierarchy, fsOptional]
			});
			tabHierarchy = new Ext.Panel({
				title: "Hierarchy".localize(),
				layout: 'absolute',
				border: false,
				bodyStyle: 'background-color: transparent;',
				listeners: {
					resize: function(thisObj, adjWidth, adjHeight, rawWidth, rawHeight)
					{
						chbHEnable.setPosition(adjWidth - 2*_marginSize - 150, _marginSize);
						fsHHier.setPosition(_marginSize, _lineH + 2*_marginSize);
						fsHHier.setSize(adjWidth - 2 * _marginSize, adjHeight - 3 * _marginSize - _lineH - ieOffset20);
					}
				},
				items: [chbHEnable, fsHHier]
			});
			tabText = new Ext.Panel({
				title: "Text".localize(),
				layout: 'absolute',
				border: false,
				bodyStyle: 'background-color: transparent;',
				listeners: {
					resize: function(thisObj, adjWidth, adjHeight, rawWidth, rawHeight)
					{
						chbTEnable.setPosition(adjWidth - 2*_marginSize - 150, _marginSize);
						fsTSettings.setPosition(_marginSize, _lineH + 2*_marginSize);
						fsTSettings.setSize(adjWidth - 2 * _marginSize, adjHeight - 3 * _marginSize - _lineH - ieOffset20);

						panelviewTextPatterns.setHeight(adjHeight/2);
					}
				},
				items: [chbTEnable, fsTSettings]
			});
			tabPicklist = new Ext.Panel({
				title: "Picklist".localize(),
				layout: 'absolute',
				border: false,
				bodyStyle: 'background-color: transparent;',
				listeners: {
					resize: function(thisObj, adjWidth, adjHeight, rawWidth, rawHeight)
					{
						chbPEnable.setPosition(adjWidth - 2*_marginSize - 150, _marginSize);

						fsPDimCont.setPosition(_marginSize, _lineH + 2*_marginSize);
						fsPDimCont.setSize(adjWidth - 2*_marginSize, adjHeight/2);
						panelviewPDElems.setHeight(adjHeight/2 - 2*_lineH - 7*_marginSize);

						fsPBehave.setPosition(_marginSize, (adjHeight/2 + _lineH + 3*_marginSize) + ieOffset10);
						fsPBehave.setSize(adjWidth - 2 * _marginSize, adjHeight/2 - _lineH - 4*_marginSize - ieOffset20);
					}
				},
				items: [chbPEnable, fsPDimCont, fsPBehave]
			});
			tabAttribute = new Ext.Panel({
				title: "Attribute".localize(),
				layout: 'absolute',
				border: false,
				bodyStyle: 'background-color: transparent;',
				listeners: {
					resize: function(thisObj, adjWidth, adjHeight, rawWidth, rawHeight)
					{
						chbAEnable.setPosition(adjWidth - 2*_marginSize - 150, _marginSize);

						fsASettings.setPosition(_marginSize, _lineH + 2*_marginSize);
						fsASettings.setSize(adjWidth - 2 * _marginSize, adjHeight - 3 * _marginSize - _lineH - ieOffset20);
						panelgridASAttrs.setHeight(adjHeight - 9*_lineH - 4*_marginSize);
					}
				},
				items: [chbAEnable, fsASettings]
			});
			tabData = new Ext.Panel({
	//			disabled: true,
				title: "Data".localize(),
				layout: 'absolute',
				border: false,
				bodyStyle: 'background-color: transparent;',
				listeners: {
					resize: function(thisObj, adjWidth, adjHeight, rawWidth, rawHeight)
					{
						chbDEnable.setPosition(adjWidth - 2*_marginSize - 150, _marginSize);

						fsDSettings.setPosition(_marginSize, _lineH + 2*_marginSize);
						fsDSettings.setSize(adjWidth - 2*_marginSize, adjHeight/2 - 3*_marginSize - _lineH - ieOffset10);

						panelgridDSCubeDims.setHeight(adjHeight/2 - 5*_marginSize - 5*_lineH);

						fsDSlice.setPosition(_marginSize, adjHeight/2);
						fsDSlice.setSize(adjWidth - 2*_marginSize, adjHeight/4 - 2*_marginSize - (Ext.isIE?12:0));

						fsDOptional.setPosition(_marginSize, adjHeight/2 + adjHeight/4 - (Ext.isIE?5:0));
						fsDOptional.setSize(adjWidth - 2*_marginSize, adjHeight/4 - 2*_marginSize+5);
					}
				},
				items: [chbDEnable, fsDSettings, fsDSlice, fsDOptional]
			});
			tabSort = new Ext.Panel({
				title: "Sort".localize(),
				layout: 'absolute',
				border: false,
				bodyStyle: 'background-color: transparent;',
				listeners: {
					resize: function(thisObj, adjWidth, adjHeight, rawWidth, rawHeight)
					{
						var widthForFs = adjWidth - 2*_marginSize;

						fsSoSorting.setSize(widthForFs, adjHeight * 0.40 - ieOffset20);
						fsSoSorting.setPosition(_marginSize, _marginSize);

						fsSoOrder.setSize(widthForFs, adjHeight * 0.14);
						fsSoOrder.setPosition(_marginSize, adjHeight * 0.40 + 2*_marginSize - ieOffset10);

						fsSoType.setSize(widthForFs, adjHeight * 0.27 - ieOffset10);
						fsSoType.setPosition(_marginSize, adjHeight * 0.54 + 3*_marginSize);

						fsSoLevel.setSize(widthForFs, adjHeight * 0.14);
						fsSoLevel.setPosition(_marginSize, adjHeight * 0.81 + 4*_marginSize);
					}
				},
				items: [fsSoSorting, fsSoOrder, fsSoType, fsSoLevel]
			});

			panelCenterTab = new Ext.TabPanel({
				region: 'center',
				minTabWidth: 115,
				tabWidth: 135,
				enableTabScroll: true,
				bodyStyle: 'background-color: transparent;',
				layoutOnTabChange: true,
				items: [tabGeneral, tabHierarchy, tabText, tabPicklist, tabAttribute, tabData, tabSort],
				listeners: {
					tabChange: function(p, t){
						// a lot of work here :)
						that.cts.paloSE_activePanel = t;
					}
				}
			});
			panelCenterTab.setActiveTab(tabGeneral);
			panelCenterBottom = that.cts.paloSE_btnSave = new Ext.Panel({
				region: 'south',
				layout: 'absolute',
				bodyStyle: 'background-color: transparent;',
				border: false,
				height: 30,
				maxHeight: 30,
				minHeight: 30,
				split: true,
				buttons: [btnSave, btnPaste, btnClose]
			});
			// --- Tabs --- //

			// *** SubSets accordion panel with subpanels *** //
			panelFormulaSubset = new Ext.Panel({
				title: ((conf && (conf.mode == 1 || conf.mode == 4)) ? "_msg: hb Lists".localize() : "Formula Subset".localize()),
				listeners: {
					expand: function()
					{
						this.body.dom.style.display = 'block';
						_setAcctBtns('formula');

						viewFormulaSubsets.select(0);

						selectedWestPanel = 0;
						_reqGetSubsetList();
					},
					collapse: function()
					{
						this.body.dom.style.display = 'none';
					}
				},
				items: [viewFormulaSubsets]
			});
			panelLocalSubset = new Ext.Panel({
				title: "Local Subsets".localize(),
				layout: 'fit',
				listeners: {
					expand: function()
					{
						this.body.dom.style.display = 'block';
						_setAcctBtns('local');

						selectedWestPanel = 1;
						if (storeLocalSubsets.getCount() > 0)
						{
							disableAutoPreview = true;
							viewLocalSubsets.select(0);
							disableAutoPreview = false;
						}

						_reqGetSubsetList();
					},
					collapse: function()
					{
						this.body.dom.style.display = 'none';
					}
				},
				items: [viewLocalSubsets]
			});
			panelGlobalSubset = new Ext.Panel({
				title: "Global Subsets".localize(),
				layout: 'fit',
				listeners: {
					expand: function()
					{
						this.body.dom.style.display = 'block';
						_setAcctBtns('global');

						selectedWestPanel = 2;
						if (storeGlobalSubsets.getCount() > 0)
						{
							disableAutoPreview = true;
							viewGlobalSubsets.select(0);
							disableAutoPreview = false;
						}

						_reqGetSubsetList();
					},
					collapse: function()
					{
						this.body.dom.style.display = 'none';
					}
				},
				items: [viewGlobalSubsets]
			});
			panelStoredSubsets = new Ext.Panel({
				region: 'center',
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'accordion',
				autoScroll: true,
				items: [panelFormulaSubset, panelLocalSubset, panelGlobalSubset]
			});
			// --- SubSets accordion panel with subpanels --- //

			// +++ Preview Panels +++ //
			panelPreviewCenter = new Ext.Panel({
				region: 'center',
				layout: 'fit',
				bodyStyle: 'overflow: auto;',
				items: [previewDataView, previewTree]
			});
			panelPreviewSouth = new Ext.Panel({
				region: 'south',
				layout: 'absolute',
				bodyStyle: 'background-color: transparent;',
				height: 30,
				maxHeight: 30,
				minHeight: 30,
				split: true,
				items: [chbAutoPreview, chbQuickPreview, panelbtnRefreshPreview]
			});
			// --- Preview Panels --- //

			// *** West, East and Center Panels ***
			panelWest = new Ext.Panel({
				region: 'west',
				layout: 'border',
				title: "Stored Subsets".localize(),
				bodyStyle: 'background-color: transparent;',
				split: true,
				width: _config.sseWinW / 5,
				minWidth: _config.sseWinW / 5,
				collapsible: true,
				collapsed: false,
				items: [
					new Ext.Panel({
						region: 'center',
						layout: 'fit',
						items: [panelStoredSubsets]
					}),
					panelbtnSubsetActions
				],
				listeners: {
					collapse: function(p){
						delete that.cts.paloSE_PanelWest;
					},
					expand: function(p){
						that.cts.paloSE_PanelWest = p;
					},
					render: function(p){
						that.cts.paloSE_PanelWest = p;
					}
				}
			});

			panelEast = new Ext.Panel({
				region: 'east',
				layout: 'border',
				title: "Preview".localize(),
				bodyStyle: 'background-color: transparent;',
				split: true,
				width: _config.sseWinW / 4,
				minWidth: _config.sseWinW / 4,
				collapsible: true,
				collapsed: false,
				items: [
					new Ext.Panel({
						border: false,
						bodyStyle: 'background-color:transparent;',
						region: 'center',
						layout: 'border',
						items: [panelPreviewCenter, panelPreviewSouth]
					}),
					panelPreviewVars = new Ext.Panel({
						autoScroll: true,
						border: false,
						bodyStyle: 'background-color:transparent;',
						height: 1,
						region: 'south',
						layout: 'fit'
					})
				],
				listeners: {
					collapse: function(p){
						delete that.cts.paloSE_PanelEast;
					},
					expand: function(p){
						that.cts.paloSE_PanelEast = p;
					},
					render: function(p){
						that.cts.paloSE_PanelEast = p;
					}
				}
			});

			panelCenter = new Ext.Panel({
				region: 'center',
				layout: 'border',
				border: false,
				bodyStyle: 'background-color: transparent;',
				minWidth: _config.sseWinW / 5,
				items: [panelCenterTab, panelCenterBottom]
			});
			// --- West, East and Center Panels ---

			// main panel
			panelMain = new Ext.Panel({
				_getSubsetRequestObj: function()
				{
					var tmpObj = _generateSubsetObject();
					var settings = [servId, dbName, cmbDim.getValue(), chbQuickPreview.checked, selectedWestPanel];

					return [settings, tmpObj];
				},
				layout: 'border',
				border: false,
				bodyStyle: 'background-color: transparent;',
				items: [panelWest, panelCenter, panelEast]
			});


			win = new Ext.Window({
				id: 'wSSE_edit_wnd',
				layout: 'fit',
				title: ((conf && (conf.mode == 1 || conf.mode == 4)) ? "_tit: hb List Editor".localize() : "Subset Editor".localize()),
				cls: 'palo-sse-dailog default-format-window',
				width: _config.sseWinW,
				height: _config.sseWinH,
				minWidth: _config.sseWinW,
				minHeight: _config.sseWinH,
				closeAction: 'close',
				onEsc: Ext.emptyFn,
				autoDestroy: true,
				plain: true,
				modal: true,
				listeners: {
					close: function()
					{
						if (Jedox.palo.workIn == Jedox.palo.GRID)
						{
							if ((!conf) || (conf && (conf.mode != 2) && (conf.mode != 3) && (conf.mode != 4)))
							{
								Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
								Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							}
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.subsetEditor);

							// set preselected server/db
							setTimeout(function(){
								paloRpcServer.setPreselectServDb(servId, dbName);
							},0);
						}

						if (conf && (conf.mode == 2))
							conf.fnc();
					},
					show:function(){
						setTimeout(function(){
							//that.initFocus(true, 100);
						});
					}
				},
				items: [panelMain]
			});

			// Set DIALOG work on Grid
			if ((Jedox.palo.workIn == Jedox.palo.GRID) && ((!conf) || (conf && (conf.mode == 1))))
			{
				Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
				Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
			}

			loadingDialog = true;
			paloRpcServer.getServListWithDBs();
		}

		var _show = function()
		{
			_getVarsPanel();
			that.setContext();
			that.win = win;
			that.components.Cancel = btnClose;
			that.components.OK = btnPaste;
			that.win.show();
			that.activate();

			// setup initail settings
			// Stored Subsets (west panel)
			viewFormulaSubsets.select(0);

			_resizeAll();
		}

		var _setSelectedPicklistElements = function(elems)
		{
			storePDElems.loadData(elems);

			_reqGetSubsetList();
		}

		var _setSelectedDataElements = function(elems)
		{
			var tmpRec = storeCubeDimensions.getAt(gridDSCubeDims.getSelectionModel().getSelectedCell()[0]);
			var tmpRecElems = [];
			if (elems.length > 0)
			{
				if (elems.length > 1)
					for(var i=0; i<elems.length; i++)
						tmpRecElems[tmpRecElems.length] = elems[i][1];
				else
					tmpRecElems = elems[0][1];
			}
			else
				tmpRecElems = '';

			tmpRec.set('elements', tmpRecElems);
		}

		// *** HANDLERS function ***
		var _cmbServDbSelectionHandler = function(combo, record, index)
		{
			if (cmbDbState != index)
			{
				cmbDbState = index;
				if (record.get('type') == 'database')
				{
					servId = record.get('parent_id');
					var servIndex = storeServDb.findBy(function(rec, id)
					{
						return (rec.get('id') == servId && rec.get('type') == 'server')
					});
					servAcls = (servIndex != -1) ? storeServDb.getAt(servIndex).get('rules') : null;
					dbName = record.get('name');

					paloRpcServer.getDims(servId, dbName, 0); // it's for data dimensions
					cmbDim.enable();
				}
				else if (record.get('type') == 'server')
				{
					servId = record.get('id');
					servAcls = record.get('rules');
					storeDims.removeAll();
					cmbDim.disable();
				}
			}
		}

		var _cmbDimSelectHandler = function(combo, record, index)
		{
			if (conf && (conf.mode == 1 || conf.mode == 4))
				btnPaste.disable();

			loadingDialog = true;

			var dimName = record.get('name');
			(new Jedox.backend.RPCAsyncBatch(
					true,
					(new Jedox.backend.RPCAsyncRqst('palo_sbst', 'getDimAttrs', [servId, dbName, dimName])).setOnSuccess([paloCbSuccessHandlers, paloCbSuccessHandlers.getDimAttrs]).setOnError([paloCbErrorHandlers, paloCbErrorHandlers.getDimAttrs]).setOnTimeout([paloCbTimeoutHandlers, paloCbTimeoutHandlers.getDimAttrs]),
					(new Jedox.backend.RPCAsyncRqst('palo_sbst', 'getCubesWithDims', [servId, dbName, 0])).setOnSuccess([paloCbSuccessHandlers, paloCbSuccessHandlers.getCubesWithDims]).setOnError([paloCbErrorHandlers, paloCbErrorHandlers.getCubesWithDims]).setOnTimeout([paloCbTimeoutHandlers, paloCbTimeoutHandlers.getCubesWithDims])
				)).setFlags(1).send();

			if (chbHEnable.checked)
				_changeTreecmbHHListSoruce();
		}

		var _cmbDSCubesSelectionHandler = function(combo, record, index)
		{
			var dimList = record.get('list');
			if (dimList && dimList.length > 0)
			{
				storeCubeDimensions.removeAll();
				for (var i=0, listLen=dimList.length; i<listLen; i++)
					storeCubeDimensions.add(new CubeDimRecord({
						name: dimList[i],
						elements: '',
						variable: false
					}));
			}
		}

		var _handleDataGridChange = function(record)
		{
			if (record.get('variable'))
				_addVarToList('_varDS_' + record.get('name'), '[' + record.get('name') + ']');
			else
				_removeVarFromList('_varDS_' + record.get('name'));
		}
		// --- HANDLERS function ---

		// *** PRIVATE functions ***
		var _getActionByPerm = function(basePerm, aclsPerm)
		{
			return (!(basePerm & aclsPerm)) ? 'disable' : 'enable';
		}

		var _setAcctBtns = function(mode)
		{
			if (mode == 'formula')
			{
				btnSubsetActions.newB.disable();
				btnSubsetActions.deleteB.disable();
				btnSubsetActions.editB.disable();
				btnSave.disable();
			}
			else if (mode == 'local' || mode == 'global')
			{
				btnSubsetActions.newB[_getActionByPerm(permTypes.WRITE, servAcls['dimension element'])]();
				btnSave[_getActionByPerm(permTypes.WRITE, servAcls['dimension element'])]();
			}
		}

		var _changeStateRbSoSoAlias = function()
		{
			var states = ( ((cmbFirstA.getValue() != '') && (cmbFirstA.getValue() != "[none]".localize())) || chbVFirstA.checked ) ||
						 ( ((cmbSecondA.getValue() != '') && (cmbSecondA.getValue() != "[none]".localize())) || chbVSecondA.checked );

			if (!states && _getRbVal(rbSoSoAlias))
				rbSoSoDef.setValue(true);

			rbSoSoAlias[_getActionByPerm(true, states)]();
		}

		var _changeTreecmbHHListSoruce = function()
		{
			if (cmbDim.getValue() != "[All Elements]".localize())
				cmbHHList.setValue("[All Elements]".localize());

			treecmbHHList.getLoader().dataUrl = '/be/erpc.php?wam=' + ((Jedox.palo.workIn == Jedox.palo.GRID) ? Jedox.wss.app.appModeS : 'studio') +
				'&c=palo&m=getTreeNodes&servId=' +	servId + '&dbName=' + dbName + '&dimName=' + cmbDim.getValue();

			if (treecmbHHList.rendered)
				treecmbHHList.getRootNode().reload();
		}

		var _reqGetSubsetList = function(forceRefresh)
		{
			if (disableAutoPreview && (!forceRefresh))
				return;

			var tmpView;
			if (selectedWestPanel == 1)
				tmpView = viewLocalSubsets;
			else if (selectedWestPanel == 2)
				tmpView = viewGlobalSubsets;

			if (chbAutoPreview.checked || (!!forceRefresh))
			{
				if ((tmpView) && (tmpView.getSelectionCount() > 0) && (!dirtySubset))
				{
					btnSubsetActions.deleteB[_getActionByPerm(permTypes.DELETE, servAcls['dimension element'])]();
					btnSubsetActions.editB[_getActionByPerm(permTypes.WRITE, servAcls['dimension element'])]();

					_showObtainPreviewMsg();

					paloRpcServerList.send([ {
						serv_id: servId,
						db_name: dbName,
						dim_name: cmbDim.getValue(),
						subset_type: selectedWestPanel,
						subset_name: tmpView.getSelectedRecords()[0].get('name'),
						layoutflat: _getRbVal(rbLayoutFlat),
						layouthier: _getRbVal(rbLayoutHier),
						quick_preview: chbQuickPreview.checked
					} ]);

					dirtySubset = true;
				}
				else if (!cmbDim.disabled && cmbDim.getValue())
				{
					btnSubsetActions.deleteB.disable();
					btnSubsetActions.editB.disable();

					_showObtainPreviewMsg();

					var tmpObj = _generateSubsetObject();
					var settings = [servId, dbName, cmbDim.getValue(), chbQuickPreview.checked, selectedWestPanel];

					paloRpcServerListByXML.send([ [settings, tmpObj] ]);
				}
			}
			else if (btnPaste.disabled)
				btnPaste.enable();
		}

		var _showObtainPreviewMsg = function()
		{
			var addMsg = (chbDEnable.getValue()) ? '<br><br>'.concat("_msg: paloSbstDFilterEnabled".localize(), '.') : '';

			Ext.MessageBox.show({
				title: "Please wait".localize(),
				msg: '<b><br>'.concat("Obtaining preview data".localize(), '!', '</b>', addMsg),
				closable: false,
				icon: 'largeLoadingImage'
			});
			btnPaste.disable();
		}

		// generate subset object which is used to generate XML for storing subset in palo server
		var _generateSubsetObject = function()
		{
			var tmpObj;

			// General
			var obj = {};
			obj.subset = {};
			obj.subset.indent = {value: ((_getRbVal(rbHierIndent)) ? 1 : ((_getRbVal(rbHierLevel)) ? 2 : 3))};
			if (((cmbFirstA.getValue() != '') && (cmbFirstA.getValue() != "[none]".localize())) || (_getVar('_varFirstA')[0]))
				obj.subset.alias1 = _genSsObjPart('_varFirstA', storeAlias.getAt(storeAlias.find('name',  cmbFirstA.getValue())).get('identifier'));
			if (((cmbSecondA.getValue() != '') && (cmbSecondA.getValue() != "[none]".localize())) || (_getVar('_varSecondA')[0]))
				obj.subset.alias2 = _genSsObjPart('_varSecondA', storeAlias.getAt(storeAlias.find('name',  cmbSecondA.getValue())).get('identifier'));

			// Hierarchy
			if (chbHEnable.checked)
			{
				obj.subset.hier = {};
				tmpObj = obj.subset.hier;
				if (_getRbVal(rbHElemH))
				{
					tmpObj.above = _genSsObjPart('_varHHBelowAbove', _getRbVal(rbHHAbove));
					tmpObj.exclusive = _genSsObjPart('_varHHExclusiveList', chbHHExclusive.getValue());

					if (chbHHVList.checked && (_getVar('_varHHList')[0]))
						tmpObj.element = _genSsObjPart('_varHHList', null);
					else if (cmbHHList.getValue() != "[All Elements]".localize())
						tmpObj.element = _genSsObjPart('_varHHList', cmbHHList.getValue());
					if (chbHType.checked)
						tmpObj.hide = _genSsObjPart('_varHType', ((_getRbVal(rbHTCons)) ? 1 : 2));
					if (chbHLevel.checked)
					{
						tmpObj.level_start = _genSsObjPart('_varHLStart', spinHLStart.getValue());
						tmpObj.level_end = _genSsObjPart('_varHLEnd', spinHLEnd.getValue());
					}
				}
				else
				{
					if (chbHHVList.checked && (_getVar('_varHHList')[0]))
						tmpObj.revolve_element = _genSsObjPart('_varHHList', null);
					else if (cmbHHList.getValue() != "[All Elements]".localize())
						tmpObj.revolve_element = _genSsObjPart('_varHHList', cmbHHList.getValue());
					tmpObj.revolve_add = _genSsObjPart('_varHHBelowAbove', ((_getRbVal(rbHHAbove)) ? 2 : 1));
					tmpObj.revolve_count = _genSsObjPart('_varHHExclusiveList', spinHHListLength.getValue());
				}
			}

			// Text
			if (chbTEnable.checked)
			{
				obj.subset.text = {};
				tmpObj = obj.subset.text;

				tmpArr = [];
				for (var i=0; i<(storeTextPatterns.getCount() - 1); i++)
					tmpArr[tmpArr.length] = storeTextPatterns.getAt(i).get('text');

				tmpObj.regexes = _genSsObjPart('_varTSPatterns', tmpArr);
				tmpObj.extended = _genSsObjPart('_varTSPerl', ((chbTSPerl.checked) ? 'true' : 'false'));
			}

			// Picklist
			if (chbPEnable.checked)
			{
				obj.subset.pick = {};
				tmpObj = obj.subset.pick;

				var tmpArr = [];
				for (var i=0; i < storePDElems.getCount(); i++)
					tmpArr[i] = storePDElems.getAt(i).get('name');
				tmpObj.elems = _genSsObjPart('_varPElems', tmpArr);
				tmpObj.pick_type = _genSsObjPart('_varPBehave', ((_getRbVal(rbPBFront)) ? 0 : ((_getRbVal(rbPBBack)) ? 1 : ((_getRbVal(rbPBMerge)) ? 2 : 3))));
			}

			// Attribute
			if (chbAEnable.checked)
			{
				obj.subset.attr = {};
				tmpObj = obj.subset.attr;

				var tmpArr = [];
				for (var i=0; i<storeAttrs.getCount(); i++)
					for (var j=0; j<(storeASAttrs.getCount() - 1); j++)
						tmpArr[tmpArr.length] = storeASAttrs.getAt(j).get(storeAttrs.getAt(i).get('name'));

				varVal = _getVar('_varASAttrs');
				if (varVal[0])
				{
					numOfAttrs = storeAttrs.getCount();
					numOfVarVals = varVal[2].length;
					tmpVarVals = [];

					for (var i=0; i<numOfAttrs; i++)
						for (var j=(numOfAttrs+i); j<numOfVarVals; j+=numOfAttrs)
							tmpVarVals.push(varVal[2][j]);

					tmpObj.attribute_filter = {
						param: varVal[1],
						value: tmpVarVals
					};
				}
				else
					tmpObj.attribute_filter = {value: tmpArr};
			}

			// Data
			if (chbDEnable.checked)
			{
				obj.subset.data = {};
				tmpObj = obj.subset.data;

				if (cmbDSCubes.getValue())
				{
					tmpObj.subcube = {};
					tmpObj.subcube.source_cube = _genSsObjPart('_varDSCube', cmbDSCubes.getValue());

					tmpObj.subcube.subcube = [];
					var storeSize = storeCubeDimensions.getCount();
					for (var tmpElems, tmpRec, i=0; i<storeSize; i++)
					{
						tmpRec = storeCubeDimensions.getAt(i);
						tmpElems = tmpRec.get('elements');
						tmpObj.subcube.subcube[tmpObj.subcube.subcube.length] = _genSsObjPart('_varDS_' + tmpRec.get('name'), ((tmpElems) ? tmpElems : '*'));
					}
				}

				tmpObj.cell_operator = _genSsObjPart('_varDSCriteria', storeCriteria.find('name', cmbDSCriteria.getValue()));

				if (cmbDOFirst.getValue() != "[none]".localize())
				{
					tmpObj.criteria = [];
					tmpObj.criteria[0] = cmbDOFirst.getValue();
					tmpObj.criteria[1] = _genSsObjPart('_varDOFirst', txtDOFirst.getValue());

					if (cmbDOSecond.getValue() != "[none]".localize())
					{
						tmpObj.criteria[2] = cmbDOSecond.getValue();
						tmpObj.criteria[3] = _genSsObjPart('_varDOSecond', txtDOSecond.getValue());
					}
				}

				if (chbD3Topmost.checked)
					tmpObj.top = _genSsObjPart('_varD3Topmost', spinD3Topmost.getValue());

				if (chbD3Upper.checked)
					tmpObj.upper_percentage = _genSsObjPart('_varD3Upper', spinD3Upper.getValue());

				if (chbD3Lower.checked)
					tmpObj.lower_percentage = _genSsObjPart('_varD3Lower', spinD3Lower.getValue());
			}

			// Sort
			obj.subset.sort = {};
			tmpObj = obj.subset.sort;
			tmpObj.whole = {value: ((_getRbVal(rbLayoutHier) && (!_getRbVal(rbLayoutFlat))) ? 1 : 0)};
			// TODO: add option "by Value"
			if (_getRbVal(rbSoSoDef) || _getRbVal(rbSoSoElem) || _getRbVal(rbSoSoAlias) || _getRbVal(rbSoSoVal))
			{
				tmpObj.sorting_criteria = _genSsObjPart('_varSoSoCriteria',
					((_getRbVal(rbSoSoDef)) ? 0 :
						((_getRbVal(rbSoSoVal)) ? 1 :
							((_getRbVal(rbSoSoElem)) ? 2 : 3)
						)
					)
				);
			}
			else if (_getRbVal(rbSoSoAttr))
				tmpObj.attribute = _genSsObjPart('_varSoSoAttr', storeAttrs.getAt(storeAttrs.find('name',  cmbSoSoAttr.getValue())).get('identifier'));
			tmpObj.reverse = _genSsObjPart('_varSoOrReverse', ((_getRbVal(chbParentsReverse)) ? 1 : 0) + ((_getRbVal(chbSoOrReverse)) ? 2 : 0));
			tmpObj.type_limitation = _genSsObjPart('_varSoTyType',
				((_getRbVal(rbSoTyElems)) ? 0 :
					((_getRbVal(rbSoTyBase)) ? 1 : 2)
				)
			);
			if (chbSoLvSort.checked)
				tmpObj.level = _genSsObjPart('_varSoLvLevel', spinSoLvIndent.getValue());
			tmpObj.show_duplicates = {value: ((chbLayoutDouble.checked) ? 1 : 0)};

			return obj;
		}

		var _genSsObjPart = function(name, value)
		{
			var tmpVar = _getVar(name);
			var tmpObjPart;

			if (tmpVar[0])
				tmpObjPart = {
					param: tmpVar[1],
					value: (tmpVar[2]) ? tmpVar[2] : value
				};
			else
				tmpObjPart = {
					value: value
				};

			return tmpObjPart;
		}

		// reload subset data
		var _reloadSubsetObject = function(reloadData)
		{
			disableAutoPreview = true;
			var tmpObj;

			// indent
			if (reloadData.subset.indent.value == 1)
				rbHierIndent.setValue(true);
			else if (reloadData.subset.indent.value == 2)
				rbHierLevel.setValue(true);
			else
				rbHierDepth.setValue(true);

			var attribId;
			if (reloadData.subset.alias1)
			{
				var alias1 = reloadData.subset.alias1;

				attribId = storeAlias.find('identifier', alias1.value);
				chbVFirstA.setValue(false);
				if (attribId != -1)
				{
					cmbFirstA.setValue(storeAlias.getAt(attribId).get('name'));
					if (alias1.param && (alias1.param != null))
					{
						_addVarToList('_varFirstA', "Alias 1".localize(), alias1.param, storeAlias.getAt(attribId).get('name'));
						chbVFirstA.setValue(true);
					}
				}
				else
					cmbFirstA.setValue("[none]".localize());
			}
			else
			{
				chbVFirstA.setValue(false);
				cmbFirstA.setValue("[none]".localize());
			}

			if (reloadData.subset.alias2)
			{
				var alias2 = reloadData.subset.alias2;

				attribId = storeAlias.find('identifier', alias2.value);
				chbVSecondA.setValue(false);
				if (attribId != -1)
				{
					cmbSecondA.setValue(storeAlias.getAt(attribId).get('name'));
					if (alias2.param && (alias2.param != null))
					{
						_addVarToList('_varSecondA', "Alias 2".localize(), alias2.param, storeAlias.getAt(attribId).get('name'));
						chbVSecondA.setValue(true);
					}
				}
				else
					cmbSecondA.setValue("[none]".localize());
			}
			else
			{
				chbVSecondA.setValue(false);
				cmbSecondA.setValue("[none]".localize());
			}
			_changeStateRbSoSoAlias();

			// + HIER - TAB +
			if (reloadData.subset.hier)
			{
				chbHEnable.setValue(true);
				tmpObj = reloadData.subset.hier;

				if (tmpObj.revolve_add)
				{
					rbHElemH.setValue(false);
					rbHElemHCyc.setValue(true);

					panelchbHHExclusive.setVisible(false);
					panelspinHHListLength.setVisible(true);

					if (tmpObj.revolve_add.value == 2)
					{
						rbHHAbove.setValue(true);
						rbHHBelow.setValue(false);
					}
					else
					{
						rbHHAbove.setValue(false);
						rbHHBelow.setValue(true);
					}

					spinHHListLength.setValue(tmpObj.revolve_count.value);
				}
				else
				{
					rbHElemH.setValue(true);
					rbHElemHCyc.setValue(false);

					panelchbHHExclusive.setVisible(true);
					panelspinHHListLength.setVisible(false);

					if ((tmpObj.above) && (tmpObj.above.value) && (tmpObj.above.value != 'false'))
					{
						rbHHAbove.setValue(true);
						rbHHBelow.setValue(false);
					}
					else
					{
						rbHHAbove.setValue(false);
						rbHHBelow.setValue(true);
					}

					if (tmpObj.exclusive && tmpObj.exclusive.value)
						chbHHExclusive.setValue(tmpObj.exclusive.value);

					if (tmpObj.hide)
					{
						chbHType.setValue(true);
						var tmpSetHTCons = ((tmpObj.hide.value == 1) ? true : false);
						rbHTCons.setValue(tmpSetHTCons);
						rbHTBase.setValue(!tmpSetHTCons);
					}
					else
						chbHType.setValue(false);

					if (tmpObj.level_start && tmpObj.level_end)
					{
						chbHLevel.setValue(true);
						spinHLStart.setValue(tmpObj.level_start.value);
						spinHLEnd.setValue(tmpObj.level_end.value);
					}
					else
						chbHLevel.setValue(false);
				}

				_updateHierTab('enable', true);

				if (tmpObj.revolve_element)
					cmbHHList.setValue(tmpObj.revolve_element.value);
				else if (tmpObj.element)
					cmbHHList.setValue(tmpObj.element.value);

				// update variables
				if ((tmpObj.above) && (tmpObj.above.param))
				{
					_addVarToList('_varHHBelowAbove', "Above".localize(), tmpObj.above.param, tmpObj.above.value);
					chbHHVBelowAbove.setValue(true);
				}
				if ((!tmpObj.revolve_add) && (tmpObj.exclusive) && (tmpObj.exclusive.param))
				{
					_addVarToList('_varHHExclusiveList', "Exclusive".localize(), tmpObj.exclusive.param, tmpObj.exclusive.value);
					chbHHVExclusiveList.setValue(true);
				}

				if (tmpObj.element && tmpObj.element.param)
				{
					_addVarToList('_varHHList', "Element".localize(), tmpObj.element.param, tmpObj.element.value);
					chbHHVList.setValue(true);
				}

				if (tmpObj.hide && tmpObj.hide.param)
				{
					_addVarToList('_varHType', "Hide".localize(), tmpObj.hide.param, tmpObj.hide.value);
					chbHVType.setValue(true);
				}

				if (tmpObj.level_start && tmpObj.level_end)
				{
					if (tmpObj.level_start.param)
					{
						_addVarToList('_varHLStart', "Level Start".localize(), tmpObj.level_start.param, tmpObj.level_start.value);
						chbHLVStart.setValue(true);
					}
					if (tmpObj.level_end.param)
					{
						_addVarToList('_varHLEnd', "Level End".localize(), tmpObj.level_end.param, tmpObj.level_end.value);
						chbHLVEnd.setValue(true);
					}
				}
			}
			else
			{
				chbHEnable.setValue(false);
				_updateHierTab('disable', true);
			}
			// - HIER - TAB -

			// + TEXT - TAB +
			storeTextPatterns.removeAll();
			if (reloadData.subset.text)
			{
				chbTEnable.setValue(true);
				tmpObj = reloadData.subset.text;

				if (tmpObj && tmpObj.regexes && tmpObj.regexes.value.constructor.toString().indexOf("Array") != -1)
					for (var i=0; i<tmpObj.regexes.value.length; i++)
						storeTextPatterns.add(new TextPatternRecord({
							text: tmpObj.regexes.value[i]
						}));
				else if (tmpObj && tmpObj.regexes)
					storeTextPatterns.add(new TextPatternRecord({
						text: tmpObj.regexes.value
					}));
				storeTextPatterns.add(new TextPatternRecord({
					text: "[none]".localize()
				}));

				chbTSPerl.setValue(tmpObj.extended.value);

				_updateTextTab('enable');

				// variables
				if (tmpObj && tmpObj.regexes && tmpObj.regexes.param)
				{
					_addVarToList('_varTSPatterns', "RegExes".localize(), tmpObj.regexes.param, tmpObj.regexes.value);
					chbTSVPatterns.setValue(true);
				}
				else
					chbTSVPatterns.setValue(false);

				if (tmpObj.extended.param)
				{
					_addVarToList('_varTSPerl', "RegEx".localize(), tmpObj.extended.param, tmpObj.extended.value);
					chbTSVPerl.setValue(true);
				}
				else
					chbTSVPerl.setValue(false);
			}
			else
			{
				tmpRec = new TextPatternRecord({
					text: "[none]".localize()
				});
				storeTextPatterns.add(tmpRec);

				chbTEnable.setValue(false);
				_updateTextTab('disable');
			}
			// - TEXT - TAB -

			// + PICKLIST - TAB +
			if (reloadData.subset.pick)
			{
				chbPEnable.setValue(true);
				tmpObj = reloadData.subset.pick;

				if (tmpObj.elems)
				{
					var tmpLen = tmpObj.elems.value.length;
					storePDElems.removeAll();
					for (var i=0; i<tmpLen; i++)
						storePDElems.add(new PicklistElemRecord({
							index: i,
							name: tmpObj.elems.value[i],
							esc_name: Jedox.palo.utils.escHTML(tmpObj.elems.value[i])
						}));
				}
				else
					storePDElems.removeAll();

				if (tmpObj.pick_type.value == 0)
				{
					rbPBFront.setValue(true);
					rbPBBack.setValue(false);
					rbPBMerge.setValue(false);
					rbPBSubtract.setValue(false);
				}
				else if (tmpObj.pick_type.value == 1)
				{
					rbPBFront.setValue(false);
					rbPBBack.setValue(true);
					rbPBMerge.setValue(false);
					rbPBSubtract.setValue(false);
				}
				else if (tmpObj.pick_type.value == 2)
				{
					rbPBFront.setValue(false);
					rbPBBack.setValue(false);
					rbPBMerge.setValue(true);
					rbPBSubtract.setValue(false);
				}
				else
				{
					rbPBFront.setValue(false);
					rbPBBack.setValue(false);
					rbPBMerge.setValue(false);
					rbPBSubtract.setValue(true);
				}

				_updatePicklistTab('enable');

				// update variables
				if (tmpObj.elems.param)
				{
					_addVarToList('_varPElems', "Picklist".localize(), tmpObj.elems.param, tmpObj.elems.value);
					chbPDVElems.setValue(true);
				}
				else
					chbPDVElems.setValue(false);

				if (tmpObj.pick_type.param)
				{
					_addVarToList('_varPBehave', "Picklist Type".localize(), tmpObj.pick_type.param, tmpObj.pick_type.value);
					chbPBVBehave.setValue(true);
				}
				else
					chbPBVBehave.setValue(false);
			}
			else
			{
				chbPEnable.setValue(false);
				storePDElems.removeAll();
				_updatePicklistTab('disable');
			}
			// - PICKLIST - TAB -

			// + ATTRIBUTE - TAB +
			if (reloadData.subset.attr)
			{
				chbAEnable.setValue(true);
				tmpObj = reloadData.subset.attr;

				_updateAttributeTab('enable');

				if (tmpObj.attribute_filter.param)
				{
					var tmpData = tmpObj.attribute_filter.value;
					var rowLen = tmpData.length / storeAttrs.getCount();
					var numOfAttrs = storeAttrs.getCount();

					var tmpValue = ['', ''];
					for (var i=0; i<rowLen; i++)
						for (var j=0; j<numOfAttrs; j++)
							tmpValue.push(tmpData[i + j*rowLen]);

					_addVarToList('_varASAttrs', "Attributes".localize(), tmpObj.attribute_filter.param, tmpValue);
					chbASVAttrs.setValue(true);
				}
				else
				{
					if (storeAttrs.getCount() > 0)
					{
						var tmpData = tmpObj.attribute_filter.value;
						var rowLen = tmpData.length / storeAttrs.getCount();

						var tmpStoreData = [];
						for (var i=0; i<storeAttrs.getCount(); i++)
						{
							for (var j=0; j<rowLen; j++)
							{
								if (!tmpStoreData[j])
									tmpStoreData[j] = [];

								tmpStoreData[j][i] = tmpData[i*rowLen + j];
							}
						}

						// add empty row
						var tmpArrLen = tmpStoreData.length;
						tmpStoreData[tmpArrLen] = [];
						for (var i=0; i<storeAttrs.getCount(); i++)
							tmpStoreData[tmpArrLen][i] = '';

						storeASAttrs.loadData(tmpStoreData);
					}

					chbASVAttrs.setValue(false);
				}
			}
			else
			{
				chbAEnable.setValue(false);
				var tmpStoreData = [];
				for (var i=0; i<storeAttrs.getCount(); i++)
					tmpStoreData[i] = '';
				storeASAttrs.loadData([tmpStoreData]);

				_updateAttributeTab('disable');
			}
			// - ATTRIBUTE - TAB -

			// + DATA TAB +
			if (reloadData.subset.data)
			{
				chbDEnable.setValue(true);
				tmpObj = reloadData.subset.data;

				if (tmpObj.subcube.source_cube.value)
				{
					cmbDSCubes.setValue(tmpObj.subcube.source_cube.value);

					// Get Selected Record
					var recIndex = storeCubes.find('name', tmpObj.subcube.source_cube.value);
					if (recIndex < 0)
						recIndex = 0;
					_cmbDSCubesSelectionHandler(cmbDSCubes, storeCubes.getAt(recIndex), recIndex);
				}
				else
					cmbDSCubes.setValue('');

				if (tmpObj.subcube && tmpObj.subcube.subcube && (tmpObj.subcube.subcube.length > 0) && (storeCubeDimensions.getCount() > 0))
				{
					var ssubcube = tmpObj.subcube.subcube,
						curDimName = cmbDim.getValue(),
						cubeDimsLen = storeCubeDimensions.getCount();

					for (var i=0; i<ssubcube.length; i++)
					{
						var tmpRec = storeCubeDimensions.getAt(i);
						if (tmpRec.get('name') != curDimName)
						{
							if (ssubcube[i].param)
							{
								_addVarToList('_varDS_' + tmpRec.get('name'), '[' + tmpRec.get('name') + ']', ssubcube[i].param, (ssubcube[i].value != '*') ? ssubcube[i].value : '');
								tmpRec.set('variable', true);
								tmpRec.set('elements', '');
							}
							else
							{
								tmpRec.set('variable', false);
								tmpRec.set('elements', (ssubcube[i].value != '*') ? ssubcube[i].value : '');
							}
						}
					}
				}

				if (tmpObj.cell_operator.value)
					cmbDSCriteria.setValue(storeCriteria.getAt(tmpObj.cell_operator.value).get('name'));

				if (tmpObj.criteria)
				{
					if (tmpObj.criteria.length > 1)
					{
						cmbDOFirst.setValue(tmpObj.criteria[0]);
						txtDOFirst.setValue(tmpObj.criteria[1].value);
					}

					if (tmpObj.criteria.length > 3)
					{
						cmbDOSecond.setValue(tmpObj.criteria[2]);
						txtDOSecond.setValue(tmpObj.criteria[3].value);
					}
					else
						cmbDOSecond.setValue("[none]".localize());
				}
				else
				{
					cmbDOFirst.setValue("[none]".localize());
					cmbDOSecond.setValue("[none]".localize());
					txtDOFirst.setValue('');
					txtDOSecond.setValue('');
				}

				if (tmpObj.top)
				{
					chbD3Topmost.setValue(true);
					spinD3Topmost.setValue(tmpObj.top.value);
				}
				else
					chbD3Topmost.setValue(false);

				if (tmpObj.upper_percentage)
				{
					chbD3Upper.setValue(true);
					spinD3Upper.setValue(tmpObj.upper_percentage.value);
				}
				else
					chbD3Upper.setValue(false);

				if (tmpObj.lower_percentage)
				{
					chbD3Lower.setValue(true);
					spinD3Lower.setValue(tmpObj.lower_percentage.value);
				}
				else
					chbD3Lower.setValue(false);

				_updateDataTab('enable');

				if (tmpObj.subcube && tmpObj.subcube.source_cube)
					if (tmpObj.subcube.source_cube.param)
					{
						_addVarToList('_varDSCube', "Cube".localize(), tmpObj.subcube.source_cube.param, tmpObj.subcube.source_cube.value);
						chbDSVCube.setValue(true);
					}
					else
						chbDSVCube.setValue(false);

				if (tmpObj.cell_operator)
					if (tmpObj.cell_operator.param)
					{
						_addVarToList('_varDSCriteria', "Criteria".localize(), tmpObj.cell_operator.param, tmpObj.cell_operator.value);
						chbDSVCriteria.setValue(true);
					}
					else
						chbDSVCriteria.setValue(false);

				if (tmpObj.criteria)
				{
					if ((tmpObj.criteria.length > 1) && (tmpObj.criteria[1].param))
					{
						_addVarToList('_varDOFirst', "Par1".localize(), tmpObj.criteria[1].param, tmpObj.criteria[1].value);
						chbDOVFirst.setValue(true);
					}
					else
						chbDOVFirst.setValue(false);

					if ((tmpObj.criteria.length > 3) && (tmpObj.criteria[3].param))
					{
						_addVarToList('_varDOSecond', "Par2".localize(), tmpObj.criteria[3].param, tmpObj.criteria[3].value);
						chbDOVSecond.setValue(true);
					}
					else
						chbDOVSecond.setValue(false);
				}
				else
				{
					chbDOVFirst.setValue(false);
					chbDOVSecond.setValue(false);
				}

				if (tmpObj.top && tmpObj.top.param)
				{
					_addVarToList('_varD3Topmost', "Topmost".localize(), tmpObj.top.param, tmpObj.top.value);
					chbD3VTop.setValue(true);
				}
				else
					chbD3VTop.setValue(false);

				if (tmpObj.upper_percentage && tmpObj.upper_percentage.param)
				{
					_addVarToList('_varD3Upper', "Upper".localize(), tmpObj.upper_percentage.param, tmpObj.upper_percentage.value);
					chbD3VUpper.setValue(true);
				}
				else
					chbD3VUpper.setValue(false);

				if (tmpObj.lower_percentage && tmpObj.lower_percentage.param)
				{
					_addVarToList('_varD3Lower', "Lower".localize(), tmpObj.lower_percentage.param, tmpObj.lower_percentage.value);
					chbD3VLower.setValue(true);
				}
				else
					chbD3VLower.setValue(false);
			}
			else
			{
				for (var i=0; i<storeCubeDimensions.getCount(); i++)
					storeCubeDimensions.getAt(i).set('elements', '');

				chbDEnable.setValue(false);
				_updateDataTab('disable');
			}
			// - DATA TAB -

			// + SORT - TAB +
			tmpObj = reloadData.subset.sort;
			if (tmpObj.whole.value == 0)
			{
				rbLayoutFlat.setValue(true);
				rbLayoutHier.setValue(false);
			}
			else
			{
				rbLayoutFlat.setValue(false);
				rbLayoutHier.setValue(true);
			}

			if (tmpObj.reverse.param != null)
			{
				_addVarToList('_varSoOrReverse', "Reverse".localize(), tmpObj.reverse.param, tmpObj.reverse.value);
				chbSoOrVReverse.setValue(true);
			}
			else
			{
				_removeVarFromList('_varSoOrReverse');
				chbSoOrVReverse.setValue(false);

				chbParentsReverse.setValue(!!(tmpObj.reverse.value & 1));
				chbSoOrReverse.setValue(!!(tmpObj.reverse.value & 2));
			}

			chbLayoutDouble.setValue(tmpObj.show_duplicates.value == 1);

			if ((tmpObj.level) && (tmpObj.level.param != null))
			{
				chbSoLvSort.setValue(true);
				_addVarToList('_varSoLvLevel', "Sort Level".localize(), tmpObj.level.param, tmpObj.level.value);
				chbSoLvVLevel.setValue(true);
			}
			else
			{
				_removeVarFromList('_varSoLvLevel');
				chbSoLvVLevel.setValue(false);

				if ((tmpObj.level) && (tmpObj.level.value))
				{
					chbSoLvSort.setValue(true);
					spinSoLvIndent.setValue(tmpObj.level);
				}
				else
				{
					chbSoLvSort.setValue(false);
					spinSoLvIndent.setValue(1);
				}
			}

			if (tmpObj.type_limitation.param != null)
			{
				_addVarToList('_varSoTyType', "Type Limitation".localize(), tmpObj.type_limitation.param, tmpObj.type_limitation.value);
				chbSoTyVType.setValue(true);
			}
			else
			{
				_removeVarFromList('_varSoTyType');
				chbSoTyVType.setValue(false);

				if (tmpObj.type_limitation.value == 0)
				{
					rbSoTyElems.setValue(true);
					rbSoTyCons.setValue(false);
					rbSoTyBase.setValue(false);
				}
				else if (tmpObj.type_limitation.value == 1)
				{
					rbSoTyElems.setValue(false);
					rbSoTyCons.setValue(false);
					rbSoTyBase.setValue(true);
				}
				else
				{
					rbSoTyElems.setValue(false);
					rbSoTyCons.setValue(true);
					rbSoTyBase.setValue(false);
				}
			}

			if (tmpObj.sorting_criteria)
			{
				if (tmpObj.sorting_criteria.param != null)
				{
					_addVarToList('_varSoSoCriteria', "Criteria".localize(), tmpObj.sorting_criteria.param, tmpObj.sorting_criteria.value);
					chbSoSoVCriteria.setValue(true);
				}
				else
				{
					_removeVarFromList('_varSoSoCriteria');
					chbSoSoVCriteria.setValue(false);

					if (tmpObj.sorting_criteria.value == 0)
					{
						rbSoSoDef.setValue(true);
						rbSoSoElem.setValue(false);
						rbSoSoAlias.setValue(false);
						rbSoSoVal.setValue(false);
						rbSoSoAttr.setValue(false);
					}
					else if (tmpObj.sorting_criteria.value == 1)
					{
						rbSoSoDef.setValue(false);
						rbSoSoElem.setValue(false);
						rbSoSoAlias.setValue(false);
						rbSoSoVal.setValue(true);
						rbSoSoAttr.setValue(false);
					}
					else if (tmpObj.sorting_criteria.value == 2)
					{
						rbSoSoDef.setValue(false);
						rbSoSoElem.setValue(true);
						rbSoSoAlias.setValue(false);
						rbSoSoVal.setValue(false);
						rbSoSoAttr.setValue(false);
					}
					else if (tmpObj.sorting_criteria.value == 3)
					{
						rbSoSoDef.setValue(false);
						rbSoSoElem.setValue(false);
						rbSoSoAlias.setValue(true);
						rbSoSoVal.setValue(false);
						rbSoSoAttr.setValue(false);
					}
				}
			}
			else if (tmpObj.attribute)
			{
				rbSoSoDef.setValue(false);
				rbSoSoElem.setValue(false);
				rbSoSoAlias.setValue(false);
				rbSoSoVal.setValue(false);
				rbSoSoAttr.setValue(true);

				cmbSoSoAttr.setValue(storeAttrs.getAt(storeAttrs.find('identifier',  tmpObj.attribute.value)).get('name'));

				if (tmpObj.attribute.param != null)
				{
					_addVarToList('_varSoSoAttr', "Sort Attribute".localize(), tmpObj.attribute.param, tmpObj.attribute.value);
					chbSoSoVAttr.setValue(true);
				}
				else
				{
					_removeVarFromList('_varSoSoAttr');
					chbSoSoVAttr.setValue(false);
				}
			}
			// - SORT - TAB -

			disableAutoPreview = false;
		}

		// add panel in fieldset
		var _addFSPanels = function(panelItems, panelVarsItems, setup)
		{
			return new Ext.Panel({
				layout: 'column',
				border:false,
				autoWidth: true,
				autoHeight: true,
				bodyStyle: 'background-color: transparent;',
				items: [
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						columnWidth: setup.left_proc,
						autoHeight: true,
						items: panelItems
					}),
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						columnWidth: setup.right_proc,
						autoHeight: true,
						items: panelVarsItems
					})
				]
			});
		}

		// add, delete and rename
		var _newSubset = function(btn, subsetName)
		{
			if (btn == 'ok' && subsetName != '')
			{
				if (Jedox.palo.utils.checkPaloName(subsetName, 'elem'))
				{
					var tmpObj = _generateSubsetObject();
					settings = [servId, dbName, cmbDim.getValue(), subsetName, selectedWestPanel];
					paloRpcServer.savePaloSubset([settings, tmpObj]);
					Jedox.palo.utils.showWaitMsg("_msg: new Subset".localize(), "Storing".localize().concat('...'));
				}
				else
					Ext.MessageBox.show({
						title: "Information".localize(),
						msg: ("Name".localize()).concat(' "', subsetName.replace('<', '&lt;'), '" ', "is not allowed".localize()),
						buttons: Ext.Msg.OK,
						icon: Ext.MessageBox.INFO
					});
			}
		}

		var _deleteSubset = function(btn)
		{
			if (btn == 'ok')
			{
				var tmpView;
				if (selectedWestPanel == 1)
					tmpView = viewLocalSubsets;
				else if (selectedWestPanel == 2)
					tmpView = viewGlobalSubsets;

				if ((tmpView) && (tmpView.getSelectionCount() > 0))
				{
					paloRpcServer.deletePaloSubset([servId, dbName, tmpView.getSelectedRecords()[0].get('name')]);
					Jedox.palo.utils.showWaitMsg("_msg: delete Subset".localize(), "Storing".localize().concat('...'));
				}
			}
		}

		var _renameSubset = function(btn, subsetName)
		{
			if (btn == 'ok' && subsetName != '')
			{
				var tmpView;
				if (selectedWestPanel == 1)
					tmpView = viewLocalSubsets;
				else if (selectedWestPanel == 2)
					tmpView = viewGlobalSubsets;

				if ((tmpView) && (tmpView.getSelectionCount() > 0))
				{
					if (Jedox.palo.utils.checkPaloName(tmpView.getSelectedRecords()[0].get('name'), 'elem'))
					{
						paloRpcServer.renamePaloSubset([servId, dbName, tmpView.getSelectedRecords()[0].get('name'), subsetName]);
						Jedox.palo.utils.showWaitMsg("_msg: rename Subset".localize(), "Storing".localize().concat('...'));
					}
					else
						Ext.MessageBox.show({
							title: "Information".localize(),
							msg: ("Name".localize()).concat(' "', tmpView.getSelectedRecords()[0].get('name').replace('<', '&lt;'), '" ', "is not allowed".localize()),
							buttons: Ext.Msg.OK,
							icon: Ext.MessageBox.INFO
						});
				}
			}
		}

		// HIER - change look of desable/enabled tab components
		var _updateHierTab = function(funcName, subElems)
		{
			if (funcName == 'enable')
				_changeTreecmbHHListSoruce();

			tabHierarchy.setIconClass((funcName == 'enable') ? _config.tabOkIcon : '');

			cmbHHList[funcName]();
			rbHElemH[funcName]();
			rbHElemHCyc[funcName]();
			rbHHBelow[funcName]();
			rbHHAbove[funcName]();
			if (_getRbVal(rbHElemHCyc))
			{
				lblHHListLength[funcName]();
				spinHHListLength[funcName]();
			}
			else
				chbHHExclusive[funcName]();

			chbHType[funcName]();
			chbHLevel[funcName]();

			if (chbHType.checked)
			{
				rbHTBase[funcName]();
				rbHTCons[funcName]();

				chbHVType[funcName]();
			}
			else if (subElems)
			{
				rbHTBase.disable();
				rbHTCons.disable();

				chbHVType.disable();
			}

			if (chbHLevel.checked)
			{
				for (var i=0; i<elemsHL.length; i++)
					elemsHL[i][funcName]();

				chbHLVStart[funcName]();
				chbHLVEnd[funcName]();
			}
			else if (subElems)
			{
				for (var i=0; i<elemsHL.length; i++)
					elemsHL[i].disable();

				chbHLVStart.disable();
				chbHLVEnd.disable();
			}

			chbHHVList[funcName]();
			chbHHVBelowAbove[funcName]();
			chbHHVExclusiveList[funcName]();
		}

		// TEXT - change look of desable/enabled tab components
		var _updateTextTab = function(funcName)
		{
			tabText.setIconClass((funcName == 'enable') ? _config.tabOkIcon : '');

			viewTextPatterns[funcName]();
			viewTextPatternsEditor[funcName]();
			chbTSPerl[funcName]();
			lblTSExample[funcName]();

			chbTSVPatterns[funcName]();
			chbTSVPerl[funcName]();
		}

		// PICKLIST - change look of desable/enabled tab components
		var _updatePicklistTab = function(funcName)
		{
			tabPicklist.setIconClass((funcName == 'enable') ? _config.tabOkIcon : '');

			lblPDElems[funcName]();
			btnPDEdit[funcName]();
			viewPDElems[funcName]();

			lblPBInsertType[funcName]();
			rbPBFront[funcName]();
			rbPBBack[funcName]();
			rbPBMerge[funcName]();
			rbPBSubtract[funcName]();

			chbPDVElems[funcName]();
			chbPBVBehave[funcName]();
		}

		// ATTRIBUTE - change look of desable/enabled tab components
		var _updateAttributeTab = function(funcName)
		{
			tabAttribute.setIconClass((funcName == 'enable') ? _config.tabOkIcon : '');

			lblASView[funcName]();
			gridASAttrs[funcName]();
			lblASExample[funcName]();

			chbASVAttrs[funcName]();
		}

		// DATA - change look of desable/enabled tab components
		var _updateDataTab = function(funcName)
		{
			tabData.setIconClass((funcName == 'enable') ? _config.tabOkIcon : '');

			rbSoSoVal[funcName]();
			if ((funcName == 'disable') && _getRbVal(rbSoSoVal))
			{
				rbSoSoVal.setValue(false);
				rbSoSoDef.setValue(true);
			}

			cmbDSCubes[funcName]();
			gridDSCubeDims[funcName]();
			cmbDSCriteria[funcName]();

			cmbDOFirst[funcName]();
			if (cmbDOFirst.getValue() != "[none]".localize())
			{
				txtDOFirst[funcName]();
				chbDOVFirst[funcName]();
				cmbDOSecond[funcName]();
				if (cmbDOSecond.getValue() != "[none]".localize())
				{
					txtDOSecond[funcName]();
					chbDOVSecond[funcName]();
				}
				else
				{
					txtDOSecond.disable();
					chbDOVSecond.disable();
				}
			}
			else
			{
				cmbDOSecond.disable();
				txtDOFirst.disable();
				txtDOSecond.disable();
				chbDOVFirst.disable();
				chbDOVSecond.disable();
			}

			chbD3Topmost[funcName]();
			if (chbD3Topmost.checked)
			{
				spinD3Topmost[funcName]();
				chbD3VTop[funcName]();
			}
			chbD3Upper[funcName]();
			if (chbD3Upper.checked)
			{
				spinD3Upper[funcName]();
				chbD3VUpper[funcName]();
			}
			chbD3Lower[funcName]();
			if (chbD3Lower.checked)
			{
				spinD3Lower[funcName]();
				chbD3VLower[funcName]();
			}

			chbDSVCube[funcName]();
			chbDSVCriteria[funcName]();

			if (funcName == 'disable')
				chbAutoPreview.enable();
			else
			{
				chbAutoPreview.setValue(false);
				chbAutoPreview.disable();
			}
		}

		// add variable to list
		var _addVarToList = function(name, varDesc, var_name, var_value)
		{
			if (storeVarCombos.find('name', name) == -1)
			{
				storeVarCombos.add(new VarComboRecord({
					'name': name,
					'desc': varDesc,
					'var_name': ((var_name) ? var_name : null),
					'var_value': ((var_value) ? var_value : null)
				}));

				_getVarsPanel();
			}
		}

		// set variable name
		var _setVar = function(name, varName, value)
		{
			var tmpRec = storeVarCombos.getAt(storeVarCombos.find('name', name));
			tmpRec.set('var_name', varName);
			tmpRec.set('var_value', value);
		}

		// get variable name
		var _getVar = function(name)
		{
			var index = storeVarCombos.find('name', name);

			if (index != -1)
			{
				var tmpRec = storeVarCombos.getAt(index);
				if (tmpRec.get('var_name') != null)
					if (tmpRec.get('var_name') == _formulaName)
					{
						var res = _resolveFormula(tmpRec.get('var_value'));
						if (res[0])
							return [true, tmpRec.get('var_value'), res[2]];
						else
							Ext.MessageBox.show({
								title: "Error".localize(),
								msg: ''.concat("Unable to resolve value for".localize(), ': ') + tmpRec.get('var_value'),
								buttons: Ext.Msg.OK,
								icon: Ext.MessageBox.ERROR
							});
					}
					else
						return [true, tmpRec.get('var_name'), tmpRec.get('var_value')];
			}

			return [false];
		}

		// remove variable from list
		var _removeVarFromList = function(name)
		{
			var index = storeVarCombos.find('name', name);
			if (index != -1)
			{
				storeVarCombos.remove(storeVarCombos.getAt(index));

				_getVarsPanel();
			}
		}

		// get Number of filled variable combos
		var _getNumOfFilledVars = function()
		{
			var tmpCount = 0;

			for (var i=0; i<storeVarCombos.getCount(); i++)
				if (storeVarCombos.getAt(i).get('var_name') != null)
					tmpCount++;

			return tmpCount;
		}

		// generate VARIABLES panel
		var _getVarsPanel = function()
		{
			var panelShow = null;
			if (storeVarCombos.getCount() > 0)
			{
				var partW = 73,
					partLabelW = 120;

				panelShow = new Ext.Panel({
					border: false,
					layout: 'form',
					bodyStyle: 'background-color:transparent;',
					autoWidth: true,
					autoHeight: true
				});

				panelShow.add(new Ext.form.Label({
					cls: 'x-form-item',
					width: partW + partW,
					style: 'padding-top:2px;padding-left:2px;font-weight:bold;',
					text: "Named Variables".localize()
				}));

				var tmpRec, tmpCombo;
				for (var i=0; i<storeVarCombos.getCount(); i++)
				{
					tmpRec = storeVarCombos.getAt(i);
					tmpCombo = new Ext.form.ComboBox({
						store: storeVars,
						width: partW,
						tabIndex: tabOffset + 2000 + i,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						bodyStyle: 'background-color: transparent;',
						typeAhead: true,
						selectOnFocus: true,
						hideLabel: true,
						editable: true,
						triggerAction: 'all',
						mode: 'local',
						valueField: 'name',
						displayField: 'name',
						_var_name: tmpRec.get('name'),
						listeners: {
							change: function(thisCmb, newValue, oldValue)
							{
								var rec = storeVars.getAt(storeVars.find('name', newValue));
								if (rec)
									_setVar(thisCmb._var_name, rec.get('name'), rec.get('value'));
								else
									_setVar(thisCmb._var_name, _formulaName, newValue);
							}
						}
					});

					if (tmpRec.get('var_name') != null)
						tmpCombo.setValue((tmpRec.get('var_name') != _formulaName) ? tmpRec.get('var_name') : tmpRec.get('var_value'));

					panelShow.add(
						new Ext.Panel({
							border: false,
							layout: 'column',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								new Ext.Panel({
									border: false,
									layout: 'form',
									bodyStyle: 'background-color:transparent;',
									width: partLabelW + _marginSize,
									autoHeight: true,
									items: [
										new Ext.form.MiscField({
											width: partLabelW,
											value: '&nbsp;' + tmpRec.get('desc').localize() + ':',
											hideLabel: true
										})
									]
								}),
								new Ext.Panel({
									border: false,
									layout: 'form',
									bodyStyle: 'background-color:transparent;',
									width: partW + _marginSize,
									autoHeight: true,
									items: [tmpCombo]
								})
							]
						})
					);
				}

				panelPreviewVars.setHeight(150);
			}
			else
			{
				panelShow = new Ext.Panel({
					border: false,
					layout: 'form',
					bodyStyle: 'background-color:transparent;',
					autoWidth: true,
					autoHeight: true
				});

				panelPreviewVars.setHeight(1);
			}

			// remove all
			if (panelPreviewVars.items)
				for (var i = (panelPreviewVars.items.getCount() - 1); i >= 0; i--)
					panelPreviewVars.remove(panelPreviewVars.getComponent(i));

			panelPreviewVars.add(panelShow);
			panelEast.doLayout();
		}

		var _getRbVal = function(radioB)
		{
			return (radioB.rendered) ? radioB.getValue() : radioB.checked;
		}

		var _getPreviewValue = function()
		{
			if (previewDataView.isVisible())
			{
				if (storeElems.getCount() > 0)
					return storeElems.getAt(0).get('name');
			}
			else if (previewTree.isVisible())
			{
				var tmpRootNode = previewTree.getRootNode();
				if (tmpRootNode.childNodes.length > 0)
					return tmpRootNode.childNodes[0].text;
			}

			return '';
		}

		var _resolveFormula = function(frm)
		{
			var activeBook = Jedox.wss.app.activeBook,
				conn = activeBook._conn,
				actSheet = activeBook.getSheetSelector().getActiveSheetName(),
				tmpName = 'tmp_'.concat(Math.ceil(Math.random() * 10000000000));

			var res = conn.ccmd(0, ["nadd", [1, 1, {
				name: tmpName,
				refers_to: (!frm.search(/^=/) ? '' : '=').concat(frm),
				scope: actSheet,
				comment: 'Temporary Named Range'
			}]]);

			if (res[0][0])
				conn.ccmd(0, ['ndel', res[0][1][0].uuid]);

			return res[0][0] ? [res[0][0], res[0][1][0].uuid, res[0][1][0].value] : res[0];
		}
		// --- PRIVATE functions ---

		// RESIZING function. Triggered after resizing of MAIN Window
		var _resizeAll = function()
		{
			if (panelMain.rendered)
			{
				//panelMain.getEl().unselectable();

				// additional local vars
				var marginSize = 3, chbAutoPreviewSize = 70, chbQuickPreviewSize = 70;

				// Setup for South Part of Preview Panel
				panelbtnRefreshPreview.setPosition(chbAutoPreviewSize + chbQuickPreviewSize, marginSize);
				chbAutoPreview.setPosition(marginSize, marginSize);
				chbQuickPreview.setPosition(chbAutoPreviewSize, marginSize);
			}
		}

		this.startDialog = function(confT)
		{
			_init(confT);
			Jedox.palo.SubsetEditor.parent.constructor.call(that);
			that.id='paloSubsetEditor';
			that.containers = that.cts;
			_show();
			Jedox.palo.utils.showLoadingMsg("Acquiring Server List".localize().concat(' ...'));

			// Do cleanup of Not Deleted Temp Subset Worksheet Elements
			(new Jedox.backend.RPCAsyncRqst('palo_sbst', 'cleanSubsetWsels')).send();
		}

		this.getDialogPanel = function(confT)
		{
			_init(confT);
			Jedox.palo.utils.showLoadingMsg("Acquiring Server List".localize().concat(' ...'));
			var tmpT = setTimeout(function() {
				_resizeAll();
			}, 0);

			return panelMain;
		}

		this.setPanelMode = function()
		{
			btnClose.hide();
			btnPaste.hide();
		}

		/// callback function after all
		if (callBackFn) callBackFn(this);

		if (dlgMode) this.startDialog(conf);
	};
})();

Jedox.util.extend(Jedox.palo.SubsetEditor, Jedox.dlg.Dialog);