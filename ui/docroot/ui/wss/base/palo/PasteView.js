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
 * SVN: $Id: PasteView.js 4941 2011-05-11 13:37:06Z djordjez $
 *
 */

Jedox.wss.palo.PasteView = function(pasteViewId, x, y)
{
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.PasteView(pasteViewId, x, y));
};

Jedox.wss.dlg.PasteView = (function()
{
	return function (pasteViewId, x, y)
	{
		Jedox.wss.dlg.PasteView.parent.constructor.call(this);
		this.id = 'PaloImport';
		var that = this;

		pasteViewId = ((pasteViewId == 0) ? 0 : (pasteViewId || false));
		x = ((x == 0) ? 0 : (x || false));
		y = ((y == 0) ? 0 : (y || false));

		var paloCbSuccessHandlers =
		{
			_setServDbPreselection: function()
			{
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
					_cmbDbSelectionHandler(cmbDb, storeServDb.getAt(tmpIndex), tmpIndex);
				}
			},
			getServListWithDBs: function(result)
			{
				storeServDb.loadData(result[0]);
				if (result[1])
					preselectedServDb = result[1];

				Ext.MessageBox.hide();
				_init();

				if (editMode)
				{
					paloRpcServer.getPasteViewInitData(editPasteViewId);
					editData.length = 0;
				}
				else
				{
					_show();
					this._setServDbPreselection();
				}
			},
			getPasteViewInitData: function(result)
			{
				editData = result;
				servAcls = storeServDb.getAt(storeServDb.find('id', editData[0][2])).get('rules');
				_setDataMode(editData[0][9]);

				_show();

				if (editMode && (editData.length > 0))
					cmbDbState = storeServDb.find('name', editData[0][3]);

				this._setServDbPreselection();
			},
			getCubeNames: function(result)
			{
				storeCubes.removeAll();
				cmbCube.setValue('');
				for (var i = 0; i < result.length; i++)
					storeCubes.add(new CubeRecord({
						name: result[i]
					}));

				cmbCubeState = -1;
				if (result.length > 0)
				{
					var tmpIndex = 0;
					if (editMode && (editData.length > 0))
						tmpIndex = storeCubes.find('name', editData[0][4]);
					tmpIndex = (tmpIndex && tmpIndex != -1) ? tmpIndex : 0;

					cmbCube.setValue(storeCubes.getAt(tmpIndex).get('name'));
					_cmbCubeSelectionHandler(cmbCube, storeCubes.getAt(tmpIndex), tmpIndex);
				}
				else
				{
					storeDims.removeAll();
					_removeAllDimsFromPanel(panelPage);
					_removeAllDimsFromPanel(panelRow);
					_removeAllDimsFromPanel(panelColumn);
				}
			},
			getCubeDims: function(result)
			{
				// removing dims from state store and from panels (visual representation)
				storeDims.removeAll();
				_removeAllDimsFromPanel(panelPage);
				_removeAllDimsFromPanel(panelRow);
				_removeAllDimsFromPanel(panelColumn);

				if (editMode && (editData.length > 0) && (editData[0][4] == cmbCube.getValue()))
				{
					for (var i=1; i<editData.length; i++)
					{
						for (var j=0; j<editData[i].length; j++)
						{
							if (i==1)
								_addDdPanel(editData[i][j][0], panelPage, editData[i][j][1]);
							else if (i==2)
								_addDdPanel(editData[i][j][0], panelColumn, editData[i][j][1]);
							else if (i==3)
								_addDdPanel(editData[i][j][0], panelRow, editData[i][j][1]);
						}
					}
				}
				else if (result.length == 2)
				{
					_addDdPanel(result[0], panelColumn, null);
					_addDdPanel(result[1], panelRow, null);
				}
				else
					for (var i=0; i<result.length; i++)
						_addDdPanel(result[i], panelPage, null);
			}
		};

		var paloCbErrorHandlers =
		{
			getServListWithDBs: function() {},
			getPasteViewInitData: function() {},
			getCubeNames: function() {},
			getCubeDims: function() {}
		};

		var paloRpcServer = new Jedox.backend.rpc.Palo(paloCbSuccessHandlers, paloCbErrorHandlers),
			servId, dbName, preselectedServDb = null, servAcls, permTypes,
			panelMain, panelUpL, panelUpR, panelDownL, panelDownR, panelcmbDb, panelcmbCube, panelchbIndent, panelchbWl, panelchbFw, paneltxtFw,
			panelZeroS, panelchbZeroSupp, panelchbZeroSuppNull, panelchbShowElem, panelcmbPf, panelbtnsChooseCubeType, panelchbMorePasteViews,
			// Drag and Drop panels
			panelPage, panelColumn, panelRow,
			lblServDbCombo, lblCubeCombo, cmbDb, cmbCube, cmbPf, chbIndent, chbWl, chbFw, chbZeroSupp, chbZeroSuppNull, chbShowElem, chbMorePasteViews,
			btnClose, btnPaste, btnsChooseCubeType, txtFw,
			// state variables
			cmbDbState, cmbCubeState, cmbPfState, dataMode, editMode, editPasteViewId, editX, editY, editData = [],
			dragdropPanels = []; // Stores 3 drag and drop panels (index is ID of panel)

		// Store declarations
		// store DB + server
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

		// Cube Record
		var CubeRecord = new Ext.data.Record.create([{
			name: 'name'
		}]);

		// Cube combo store
		var storeCubes = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// store Palo Functions
		var storePf = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// store Dimensions
		var DimRecord = new Ext.data.Record.create([
			{name: 'name'},
			{name: 'parentPanel'},
			{name: 'elements'}
		]);

		// store Dimensions
		var storeDims = new Ext.data.SimpleStore({
			fields: [
				{name: 'name'},
				{name: 'parentPanel'},
				{name: 'elements'}
			]
		});

		// global Init
		this.init = function(inPasteViewId, inEditX, inEditY)
		{
			// initial states
			permTypes = (Jedox.palo.workIn == Jedox.palo.STUDIO) ? Jedox.studio.access.permType : { NONE: 0, READ: 1, WRITE: 2, DELETE: 4, SPLASH: 8 };
			cmbDbState = -1; // index of first selected item in DB combo list
			dataMode = 0; // btnsChooseCubeType.metaDataB is "CLICKED" because of this
			cmbPfState = 0;
			editMode = false;
			editPasteViewId = inPasteViewId;
			editX = inEditX; // relative position of X
			editY = inEditY; // relative position of Y

			if (arguments.length > 0)
			{
				editMode = true;
				editData = arguments;
			}

			var paloFnList = [
				['PALO.DATA'],
				['PALO.DATAC'],
				['PALO.DATAV']
			];
			storePf.loadData(paloFnList);

			Jedox.palo.utils.showLoadingMsg("Opening dialog".localize().concat(' ...'));
			paloRpcServer.getServListWithDBs(true);
		}

		// local INIT function
		var _init = function()
		{
			// *** Labels *** //
			// Server/DB Combo Lalel
			lblServDbCombo = new Ext.form.MiscField({
				value: "Choose Server/Database".localize() + ':',
				height: 22,
				bodyStyle: 'background-color: transparent;',
				hideLabel: true
			});

			// Cube Combo Lalel
			lblCubeCombo = new Ext.form.MiscField({
				value: "Choose Cube".localize() + ':',
				height: 22,
				bodyStyle: 'background-color: transparent;',
				hideLabel: true
			});
			// <--- Lables ---> //

			// *** Combo Boxes *** //
			// Server/DB combo Box
			cmbDb = new Ext.form.ComboBox({
				id: 'wPasteView_server_cmb',
				store: storeServDb,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				tabIndex: 1,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
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

			// Panel for Server/DB Combo Box
			panelcmbDb = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [cmbDb]
			});

			// Cube combo Box
			cmbCube = new Ext.form.ComboBox({
				id: 'wPasteView_cube_cmb',
				store: storeCubes,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 2,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				listeners: {
					select: _cmbCubeSelectionHandler
				},
				valueField: 'name',
				displayField: 'name'
			});

			// Panel for Cube Combo Box
			panelcmbCube = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [cmbCube]
			});

			// Palo Function combo Box
			cmbPf = new Ext.form.ComboBox({
				disabled: true,
				store: storePf,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 20,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'name',
				displayField: 'name'
			});
			cmbPf.setValue(storePf.getAt(cmbPfState).get('name'));
			// Panel for Palo Function Combo Box
			panelcmbPf = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [cmbPf]
			});
			// <--- Combo Boxes ---> //

			// *** Text Boxes *** //
			txtFw = new Ext.form.TextField({
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 12,
				value: Jedox.palo.config.fixWidth
			});

			paneltxtFw = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [txtFw]
			});
			// <--- Text Boxes ---> //

			// *** CheckBoxes *** //
			// Indent Check box
			chbIndent = new Ext.form.Checkbox({
				id:'wPasteView_indent_chk',
				checked: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 19,
				hideLabel: true,
				boxLabel: "Indent".localize()
			});

			// Panel for Indent Check Box
			panelchbIndent = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbIndent]
			});

			// Wrap Lables Check box
			chbWl = new Ext.form.Checkbox({
				id:'wPasteView_wrpl_chk',
				hideLabel: true,
				checked: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 10,
				boxLabel: "Wrap Labels".localize()
			});

			// Panel for Wrap Lables Check Box
			panelchbWl = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbWl]
			});

			// Fixed Width Check box
			chbFw = new Ext.form.Checkbox({
				id:'wPasteView_fxdw_chk',
				hideLabel: true,
				checked: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 11,
				boxLabel: "Fixed width".localize() + ":",
				listeners: {
					check: function()
					{
						if (chbFw.getValue())
							txtFw.enable();
						else
							txtFw.disable();
					}
				}
			});

			// Panel for Fixed Width Check Box
			panelchbFw = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbFw]
			});

			// ZeroSuppression
			chbZeroSupp = new Ext.form.Checkbox({
				id: 'wPasteView_zrSuppr_chk',
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 21,
				boxLabel: "Zero suppression".localize()
			});
			// Panel for ZeroSuppression
			panelchbZeroSupp = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbZeroSupp]
			});

			// ZeroSuppression NULL
			chbZeroSuppNull = new Ext.form.Checkbox({
				id: 'wPasteView_zrSupprNULL_chk',
				disabled: true,
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 22,
				boxLabel: "Suppress calculated NULL".localize()
			});
			// Panel for ZeroSuppression NULL
			panelchbZeroSuppNull = new Ext.Panel({
				hidden: true,
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbZeroSuppNull]
			});

			// Show Element Selector on dblclick .. Check box
			chbShowElem = new Ext.form.Checkbox({
				id: 'wPasteView_shwElSel_chk',
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 23,
				boxLabel: "Show element selector on doubleclick".localize()
			});
			// Panel for Show Element Selector on dblclick .. Check Box
			panelchbShowElem = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbShowElem]
			});

			// More Paste Views on Grid Check box
			chbMorePasteViews = new Ext.form.Checkbox({
				id: 'wPasteView_atSelCell_chk',
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 24,
				boxLabel: "Paste at selected cell".localize()
			});
			// Panel for More Paste Views on Grid Check Box
			panelchbMorePasteViews = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbMorePasteViews]
			});
			// <--- CheckBoxes ---> //

			// *** 3 - Drag and Drop Panels *** //
			panelPage = new Ext.Panel({
				id: 'pv_panelPage',
				layout:'accordion',
				autoScroll: true
			});
			dragdropPanels['pv_panelPage'] = panelPage;

			panelColumn = new Ext.Panel({
				id: 'pv_panelColumn',
				layout:'accordion',
				autoScroll: true
			});
			dragdropPanels['pv_panelColumn'] = panelColumn;

			panelRow = new Ext.Panel({
				id: 'pv_panelRow',
				layout:'accordion',
				autoScroll: true
			});
			dragdropPanels['pv_panelRow'] = panelRow;
			// <--- 3 - Drag and Drop Panels ---> //

			// *** 4 - Middle Panels *** //
			// Up Left Panel
			panelUpL = new Ext.Panel({
				title: "Page selector".localize(),
				bodyStyle: 'background-color: transparent;',
				layout: 'absolute',
				items: [panelPage]
			});

			// Up Right Panel
			panelUpR = new Ext.Panel({
				title: "Column titles".localize(),
				bodyStyle: 'background-color: transparent;',
				layout: 'absolute',
				items: [panelColumn, panelchbWl, panelchbFw, paneltxtFw]
			});

			// Down Left Panel
			panelDownL = new Ext.Panel({
				title: "Row titles".localize(),
				bodyStyle: 'background-color: transparent;',
				layout: 'absolute',
				items: [panelRow, panelchbIndent]
			});

			// Down Right Panel
			panelDownR = new Ext.Panel({
				title: "Data".localize(),
				bodyStyle: 'background-color: transparent;',
				layout: 'absolute',
				items:
				[
				 	panelcmbPf,
				 	panelZeroS = new Ext.Panel({
				 		border: false,
						bodyStyle: 'background-color: transparent;',
						layout: 'column',
						items:
						[
						 	panelchbZeroSupp,
						 	{
								border: false,
								bodyStyle: 'background-color:transparent;',
								html: '&nbsp;&nbsp;&nbsp;'
							},
				 			panelchbZeroSuppNull
				 		]
				 	}),
				 	panelchbShowElem,
				 	panelchbMorePasteViews
				]
			});
			// <--- 4 Middle Panels ---> //

			// *** Buttons *** //
			btnPaste = that.components.OK = new Ext.Button({
				id:'wPasteView_paste_btn',
				text: "Paste".localize(),
				tabIndex: 101,
				handler: function()
					{
						// Array (x, y, page, column, row)
						// panel IDs: page = pv_panelPage, colum = pv_panelColumn, row = pv_panelRow
						var pPage = [];
						var pColumn = [];
						var pRow = [];

						storeDims.each(function(inRec)
						{
							if (inRec.get('parentPanel').id == 'pv_panelPage')
								pPage[pPage.length] = [inRec.get('name'), inRec.get('elements')];
							else if (inRec.get('parentPanel').id == 'pv_panelColumn')
								pColumn[pColumn.length] = [inRec.get('name'), inRec.get('elements')];
							else if (inRec.get('parentPanel').id == 'pv_panelRow')
								pRow[pRow.length] = [inRec.get('name'), inRec.get('elements')];
						});

						Ext.MessageBox.show({
							title: "Please wait".localize(),
							msg: '<b><br>' + "Obtaining data!".localize() + '</b>',
							closable: false,
							icon: 'largeLoadingImage'
						});

						if (Jedox.wss.app.activeBook)
						{
							var env = Jedox.wss.app.environment;
							var activeBook = Jedox.wss.app.activeBook;
							var upperLeftCoords = env.defaultSelection.getActiveRange().getUpperLeft();

							var editSettingsData = [editPasteViewId, editX, editY];
							var settings =
							[
							 	upperLeftCoords.getX(),
							 	upperLeftCoords.getY(),
							 	servId,
							 	dbName,
							 	cmbCube.getValue(),
							 	chbWl.getValue(),
							 	((chbFw.getValue()) ? parseFloat(txtFw.getValue()) : -1),
							 	chbIndent.getValue(),
							 	chbMorePasteViews.getValue(),
							 	dataMode,
							 	editMode,
							 	editSettingsData,
							 	chbShowElem.getValue(),
							 	chbZeroSupp.getValue()
							 ];



							setTimeout(function()
								{
									Jedox.backend.rpc_cb('palo_handlerPasteView', [[settings, pPage, pColumn, pRow]]);
									Ext.MessageBox.hide();
									that.win.close();
								},
							0);
						}
					}
			});

			btnClose = that.components.Cancel = new Ext.Button({
				id:'wPasteView_close_btn',
				text: "Close".localize(),
				tabIndex: 102,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function(){
						that.win.close();
				}
			});

			// Image Buttons for choose of Cube types
			btnsChooseCubeType = {
				metaDataB: new Ext.Button({
					id:'wPasteView_palocube_btn',
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 3,
					cls: 'modellerImageButton',
					iconCls: 'icon_palo_cube',
					handler: function()
					{
						_setDataMode(0);
						paloRpcServer.getCubeNames(servId, dbName, dataMode);
					}
				}),

				attribsB: new Ext.Button({
					id:'wPasteView_palotable_btn',
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 4,
					cls: 'modellerImageButton',
					iconCls: 'icon_palo_table',
					handler: function()
					{
						_setDataMode(2);
						paloRpcServer.getCubeNames(servId, dbName, dataMode, true);
					}
				}),

				usersB: new Ext.Button({
					id:'wPasteView_palouser_btn',
					disabled: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 5,
					cls: 'modellerImageButton',
					iconCls: 'icon_palo_user',
					handler: function()
					{
						_setDataMode(1);
						paloRpcServer.getCubeNames(servId, dbName, dataMode);
					}
				})
			};

			// Panel for Image Buttons for choosing Cube Type
			panelbtnsChooseCubeType = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent; vertical-align: middle;',
				layout: 'table',
				width: 85,
				height: 40,
				autoHeight: true,
				items: [btnsChooseCubeType.metaDataB, btnsChooseCubeType.attribsB, btnsChooseCubeType.usersB]
			});
			// <--- Buttons ---> //

			// Main Panel
			panelMain = that.containers.mainPanel = new Ext.Panel({
				id: 'pv_mainPanel',
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'absolute',
				anchor: '100% 100%',
				monitorResize: true,
				listeners: {
					resize: _resizeAll
				},
				items: [lblServDbCombo, lblCubeCombo, panelcmbDb, panelcmbCube, panelUpL, panelUpR, panelDownL, panelDownR,
						panelbtnsChooseCubeType]
			});

			// Paste View Window
			that.win = new Ext.Window({
				id: 'pasteViewWindow',
				layout: 'fit',
				cls: 'default-format-window',
				width: 750,
				height: 540,
				minWidth: 750,
				minHeight: 500,
				closeAction: 'close',
				autoDestroy: true,
				onEsc: Ext.emptyFn,
				plain: true,
				modal: true,
				resizable: false, // It works as resizable to ;)
				title: "Paste View".localize(),
				buttons: [btnPaste, btnClose],
				listeners: {
					close: function()
					{
						Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.READY);
						Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
						that.close();
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.pasteView);
						// set preselected server/db
						setTimeout(function(){
							paloRpcServer.setPreselectServDb(servId, dbName);
						},0);
					},
					show: function()
					{
						setTimeout(function(){
//							that.initFocus(true, 100);
						});
					},
					activate: function(win) {that.activate();}
				},
				items: [panelMain]
			});
		}


		var _setSelectedElements = function(dim, elems)
		{
			if (elems.length >= 0)
				storeDims.getAt(storeDims.find('name', dim)).set('elements', elems);
		}

		this.setSelectedElements = function(dim, elems)
		{
			_setSelectedElements(dim, elems);
		}

		var _show = function()
		{
			// Set DIALOG work on Grid
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

			if (editMode && (editData.length > 0))
			{
				chbWl.setValue(editData[0][5]);
				if (editData[0][6] != -1)
					txtFw.setValue(editData[0][6]);
				else
					chbFw.setValue(false);

				chbIndent.setValue(editData[0][7]);
				chbMorePasteViews.setValue(editData[0][8]);
				chbShowElem.setValue(editData[0][12]);
				chbZeroSupp.setValue(editData[0][13]);
			}

			that.setContext();
			that.win.show();
			_resizeAll();
		}

		// *** Handler functions *** //
		var _onDragDrop = function(e, id)
		{
			var tmpRecDim = storeDims.getAt(storeDims.find('name', this.panel.title));
			if (tmpRecDim && tmpRecDim.get('parentPanel').id != id)
			{
				var tmpToPanel = dragdropPanels[id];
				if (tmpToPanel)
				{
					if ((tmpRecDim.get('parentPanel').id == 'pv_panelPage') || (id == 'pv_panelPage'))
						var elems = null;
					else
						var elems = tmpRecDim.get('elements');

					tmpRecDim.get('parentPanel').remove(this.panel);
					storeDims.remove(tmpRecDim);

					_addDdPanel(this.panel.title, tmpToPanel, elems);
				}
			}
			else if (tmpRecDim)
			{
				var panelFound = false, tmpPan, tmpSubP, tmpPos, parentP = tmpRecDim.get('parentPanel');
				for (i=0; i < parentP.items.length; i++)
				{
					tmpSubP = parentP.getComponent(i);
					tmpPos = tmpSubP.getPosition();

					if ((tmpPos[0] <= e.getPageX()) && (tmpPos[1] <= e.getPageY()) &&
						((tmpPos[0] + tmpSubP.getInnerWidth()) >= e.getPageX()) && ((tmpPos[1] + tmpSubP.getFrameHeight()) >= e.getPageY()))
					{
						tmpPan = new Ext.Panel({
							title: this.panel.title,
							border: false,
							collapsed: true,
							draggable: true,
							autoHeight: true
						});

						parentP.insert(i, tmpPan);
						tmpPan.add(_makeTreePanel(this.panel.title, parentP.id));
						parentP.remove(this.panel);

						// Trick for proper rendering
						var tmpItems = parentP.items.items;
						parentP.items.items = [];
						parentP.doLayout();

						var tmpT = setTimeout(function() {
							parentP.items.items = tmpItems;

							storeDims.remove(tmpRecDim);
							storeDims.insert(storeDims.find('name', tmpSubP.title), tmpRecDim);

							parentP.doLayout();
							tmpPan.dd.onDragDrop = _onDragDrop;
						}, 0);

						panelFound = true;

						break;
					}
				}

				if (!panelFound)
				{
					var elems = tmpRecDim.get('elements');
					parentP.remove(this.panel);
					storeDims.remove(tmpRecDim);

					// Trick for proper rendering
					var tmpItems = parentP.items.items;
					var tmpPanel = this.panel;
					parentP.items.items = [];
					parentP.doLayout();

					var tmpT = setTimeout(function() {
						parentP.items.items = tmpItems;

						_addDdPanel(tmpPanel.title, dragdropPanels[id], elems);
					}, 0);
				}
			}
		}

		var _cmbDbSelectionHandler = function(combo, record, index)
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

					if (dbName == 'System')
					{
						btnsChooseCubeType.metaDataB.disable();
						btnsChooseCubeType.attribsB.disable();
						btnsChooseCubeType.usersB.disable();

						paloRpcServer.getCubeNames(servId, dbName, 1, true);
					}
					else
					{
						// check if System Cubes are selected but user doesn't have rights to see them
						if (dataMode == 1 && !(permTypes.READ & servAcls.rights))
							dataMode = 0;

						_setDataMode(dataMode);
						paloRpcServer.getCubeNames(servId, dbName, dataMode, (dataMode == 2));
					}
				}
			}
		}

		var _cmbCubeSelectionHandler = function(combo, record, index)
		{
			if (cmbCubeState != index)
			{
				cmbCubeState = index;
				paloRpcServer.getCubeDims(servId, dbName, record.get('name'));
			}
		}

		// *** Other functions *** //
		var _getActionByPerm = function(basePerm, aclsPerm)
		{
			return (!(basePerm & aclsPerm)) ? 'disable' : 'enable';
		}

		var _removeAllDimsFromPanel = function(panel)
		{
			for (var i=(panel.items.length - 1); i>=0; i--)
				panel.remove(panel.getComponent(i));
		}

		var _addDdPanel = function(pName, parentP, elems)
		{
			var tmpPan = new Ext.Panel({
				title: pName,
				border: false,
				collapsed: true,
				draggable: true,
				autoHeight: true
			});
			parentP.add(tmpPan);

			elems = (elems) ? elems : null;
			storeDims.add(new DimRecord({
				name: pName,
				parentPanel: parentP,
				elements: elems
			}));

			tmpPan.add(_makeTreePanel(pName, parentP.id));

			parentP.doLayout();
			tmpPan.dd.onDragDrop = _onDragDrop;
		}

		var _makeTreePanel = function(dimName, panelId)
		{
			var tree = new Ext.tree.TreePanel({
				cls: 'x-tree-noicon',
				border: false,
				autoScroll: true,
				animate: true,
				enableDD: false,
				containerScroll: true,
				rootVisible: false
			});

			var root = new Ext.tree.TreeNode({
				text: 'Root',
				draggable: false,
				id: 'root'
			});
			tree.setRootNode(root);

			var tmpNode = new Ext.tree.TreeNode({
				text: ((panelId == 'pv_panelPage') ? "Choose Element".localize() : "Select Elements".localize()),
				draggable: false,
				id: 'title',
				listeners: {
					dblclick: function()
					{
						if (panelId == 'pv_panelPage' && Jedox.palo.workIn == Jedox.palo.GRID)
							Jedox.gen.load(Jedox.wss.app.dynJSRegistry.chooseElement, [{
								working_mode: 2,
								parent_object: {cb_fnc: _setSelectedElements},
								serv_id: servId,
								db_name: dbName,
								dim_name: dimName,
								edit_data: storeDims.getAt(storeDims.find('name', dimName)).get('elements')
							}]);
						else if (Jedox.palo.workIn == Jedox.palo.GRID)
							Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectElements, [ { 'mode': 1, 'conf': [that, servId, dbName, dimName, storeDims.getAt(storeDims.find('name', dimName)).get('elements')] } ]);
					}
				}
			});
			root.appendChild(tmpNode);

			return tree;
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
				btnsChooseCubeType.usersB[_getActionByPerm(permTypes.READ, servAcls.rights)]();
			}
			else if (newDataMode == 2)
			{
				btnsChooseCubeType.metaDataB.enable();
				btnsChooseCubeType.attribsB.disable();
				btnsChooseCubeType.usersB[_getActionByPerm(permTypes.READ, servAcls.rights)]();
			}
			else if (newDataMode == 1)
			{
				btnsChooseCubeType.metaDataB.enable();
				btnsChooseCubeType.attribsB.enable();
				btnsChooseCubeType.usersB.disable();
			}

			dataMode = newDataMode;
		}

		// *** Resize *** //
		var _resizeAll = function()
		{
			if (panelMain.rendered)
			{
				// disable Text selection on all elements inside window
//				panelMain.getEl().unselectable();

				// local constant variables
				var lineH = 25; // height of text field, comboBox field, checkBox Field (with margins included)
				var marginSize = 3; // size in pixels for spaces between
				var btnPosAdjuster = 8;
				var w = panelMain.getSize().width;
				var h = panelMain.getSize().height;

				var innerPanelW = (w - marginSize * 3) / 2;
				var innerPanelH = (h - lineH * 2 - marginSize * 3) / 2;

				// inner Panels
				panelUpL.setSize(innerPanelW, innerPanelH);
				panelUpL.setPosition(marginSize, marginSize + lineH * 2);
				panelUpR.setSize(innerPanelW, innerPanelH);
				panelUpR.setPosition(innerPanelW + marginSize * 2, marginSize + lineH * 2);
				panelDownL.setSize(innerPanelW, innerPanelH);
				panelDownL.setPosition(marginSize, innerPanelH + marginSize * 2 + lineH * 2);
				panelDownR.setSize(innerPanelW, innerPanelH - marginSize - lineH);
				panelDownR.setPosition(innerPanelW + marginSize * 2, innerPanelH + marginSize * 2 + lineH * 2);

				// Lables
				lblServDbCombo.setPosition(marginSize, marginSize);
				lblCubeCombo.setPosition(innerPanelW + marginSize * 2, marginSize);

				// Comboes in Main Panel
				panelcmbDb.setPosition(marginSize, lineH - marginSize);
				cmbDb.setWidth(innerPanelW);

				// Buttons
				if (panelbtnsChooseCubeType.rendered)
				{
					panelbtnsChooseCubeType.setPosition(w - marginSize - panelbtnsChooseCubeType.getSize().width, lineH - marginSize);

					// Cube Combo
					panelcmbCube.setPosition(innerPanelW + marginSize * 2, lineH - marginSize);
					cmbCube.setWidth(innerPanelW - panelbtnsChooseCubeType.getSize().width - marginSize);
				}

				// CheckBoxes
				panelchbIndent.setPosition(marginSize * 2, innerPanelH - lineH * 2);
				panelchbWl.setPosition(marginSize * 2, innerPanelH - lineH * 2);
				if (panelchbWl.rendered)
				{
					panelchbFw.setPosition(marginSize * 3 + panelchbWl.getSize().width + 15, innerPanelH - lineH * 2);
					if (panelchbFw.rendered)
					{
						paneltxtFw.setPosition(marginSize * 4 + panelchbWl.getSize().width + panelchbFw.getSize().width + 15, innerPanelH - lineH * 2 - marginSize);
						txtFw.setWidth(innerPanelW - (marginSize * 6 + panelchbWl.getSize().width + panelchbFw.getSize().width + 15));
					}
				}
				panelZeroS.setPosition(marginSize * 2, innerPanelH - lineH * 5 - 3 * marginSize);
				panelchbShowElem.setPosition(marginSize * 2, innerPanelH - lineH * 4 - 2 * marginSize);
				panelchbMorePasteViews.setPosition(marginSize * 2, innerPanelH - lineH * 3 - marginSize);

				// Combos (other)
				panelcmbPf.setPosition(marginSize, marginSize);

				// Drag and Drop panels
				panelPage.setSize(innerPanelW - marginSize * 3, innerPanelH - lineH * 2 - marginSize * 3);
				panelPage.setPosition(marginSize, marginSize);
				panelColumn.setSize(innerPanelW - marginSize * 3, innerPanelH - lineH * 2 - marginSize * 3);
				panelColumn.setPosition(marginSize, marginSize);
				panelRow.setSize(innerPanelW - marginSize * 3, innerPanelH - lineH * 2 - marginSize * 3);
				panelRow.setPosition(marginSize, marginSize);

				// Register DD on Drag and Drop panels
				if (panelPage.rendered && panelRow.rendered && panelColumn.rendered)
				{
					var tmpVar = new Ext.dd.DragDrop('pv_panelPage');
					tmpVar = new Ext.dd.DragDrop('pv_panelRow');
					tmpVar = new Ext.dd.DragDrop('pv_panelColumn');
				}
			}
		}

		// Q&A helpers
		this.ddDim = function(dim, to)
		{
			// to: pv_panelPage, pv_panelColumn, pv_panelRow /* this is panel ID - same values used for dim object*/
			// dim: string name or object: {panel: id, index: no}

			if (dim && dim.panel)
			{
				var fromPanel = dragdropPanels[dim.panel];
				if (fromPanel && fromPanel.items.get(dim.index))
					dim = fromPanel.items.get(dim.index).title;
				else
					return false;
			}

			var tecDim = storeDims.getAt(storeDims.find('name', dim)),
				toPanel = dragdropPanels[to];

			if (tecDim && toPanel)
			{
				var currPP = tecDim.get('parentPanel'),
					currPPItems = currPP.items,
					elems = (currPP.id == 'pv_panelPage' || to == 'pv_panelPage') ? null : tecDim.get('elements');

				for (var i=currPPItems.length-1; i>=0; i--)
				{
					if (currPPItems.get(i).title == dim)
					{
						currPP.remove(currPPItems.get(i));
						break;
					}
				}
				storeDims.remove(tecDim);

				_addDdPanel(dim, toPanel, elems);

				return true;
			}
			else
				return false;
		}

		// Start Init of Dialog
		if (pasteViewId || x || y)
			this.init(pasteViewId, x, y);
		else
			this.init();
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.PasteView, Jedox.dlg.Dialog);
