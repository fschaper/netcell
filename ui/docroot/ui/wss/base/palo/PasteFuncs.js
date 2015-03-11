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
 * SVN: $Id: PasteFuncs.js 5106 2011-07-11 13:49:48Z lukap $
 *
 */

Jedox.wss.palo.PasteDataFunctions = function(pv)
{
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.PasteFunctions(pv));
};

Jedox.wss.dlg.PasteFunctions = (function()
{
	return function (pv) {

		Jedox.wss.dlg.PasteFunctions.parent.constructor.call(this);
		this.id = 'wPasteFuncs_dlg_wnd';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
	  	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		var paloCbSuccessHandlers =
		{
			getServListWithDBs: function(result)
			{
				storeServDb.loadData(result[0]);
				if (result[1])
					preselectedServDb = result[1];

				Ext.MessageBox.hide();

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

			getCubeNames: function(result)
			{
				storeCubes.removeAll();
				for (var i = 0; i < result.length; i++)
					storeCubes.add(new CubeRecord({
						name:  result[i]
					}));

				if (result.length > 0)
					listCubes.select(0);
			}
		};

		var paloCbErrorHandlers =
		{
			getServListWithDBs: function() {},
			getCubeNames: function() {}
		};

		var paloRpcServer = new Jedox.backend.rpc.Palo(paloCbSuccessHandlers, paloCbErrorHandlers),
			servId, dbName, preselectedServDb = null, listCubes,
			panelMain, panelcmbDb, panelcmbPaloFuncs, panelchbAttrCubes, panelchbGuessArgs,
			lblcmbDb, cmbDb, cmbPaloFuncs, chbAttrCubes, chbGuessArgs, btnPaste, btnClose,
			selectedElem, cmbPaloFuncsState, cmbDbState, dataMode;

		// Store for server + database
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

		// record and store for Cubes
		var CubeRecord = new Ext.data.Record.create([{
			name: 'name'
		}]);
		var storeCubes = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		// store Palo Functions
		var storePaloFuncs = new Ext.data.SimpleStore({
			fields: [{
				name: 'name'
			}]
		});

		this.init = function()
		{
			selectedElem = null;
			cmbPaloFuncsState = 0;
			cmbDbState = -1;
			dataMode = 0;

			var paloFuncList = [
				['PALO.DATA'],
				['PALO.DATAC'],
				['PALO.DATAV']
			];
			storePaloFuncs.loadData(paloFuncList);

			paloRpcServer.getServListWithDBs();

			lbllistCubes = new Ext.form.MiscField({
				value: "Choose Cube".localize() + ':',
				height: 22,
				bodyStyle: 'background-color: transparent;',
				hideLabel: true
			});
			listCubes = new Ext.DataView({
				id: 'wPasteFuncs_cubes_dv',
				store: storeCubes,
				itemSelector: 'div.row-modeller',
				style: 'overflow:auto',
				singleSelect: true,
				cls: 'modellerDataViewSelect',
				tpl: new Ext.XTemplate(
					'<tpl for=".">',
						'<div class="row-modeller">',
							'<span>&#160;{name}</span>',
						'</div>',
					'</tpl>'
				)
			});
			panellistCubes = new Ext.Panel({
				layout:'fit',
				items: [listCubes]
			});

			// *** BUTTONS *** //
			// Paste button and panel
			btnPaste = that.components.OK = new Ext.Button({
				id: 'wPasteFuncs_paste_btn',
				text: "Paste".localize(),
				tabIndex: 101,
				ctCls: 'subsetEditorBtns',
				handler: function(){
						if (listCubes.getSelectionCount() > 0)
						{
							var cube = listCubes.getSelectedRecords()[0].get('name');
							if (Jedox.wss.app.activeBook)
							{
								var env = Jedox.wss.app.environment;
								var activeBook = Jedox.wss.app.activeBook;
								var upperLeftCoords = env.defaultSelection.getActiveRange().getUpperLeft();
								var lowerRighCoords = env.defaultSelection.getActiveRange().getLowerRight();

								var settings = [upperLeftCoords.getX(), upperLeftCoords.getY(), lowerRighCoords.getX(), lowerRighCoords.getY(), servId, dbName, chbGuessArgs.getValue()];
								Jedox.backend.rpc_cb('palo_handlerPasteDataFunctions', [[settings, cube]]);
							}
						}
						that.win.close();
					}
			});

			// Close button and panel
			btnClose = that.components.Cancel = new Ext.Button({
				id: 'wPasteFuncs_cancel_btn',
				text: "Close".localize(),
				tabIndex: 102,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function(){
						that.win.close();
					}
			});
			// <--- BUTTONS ---> //

			// *** Combo Boxes *** //
			// Dababase Combo label, ComboBox and Panel
			lblcmbDb = new Ext.form.MiscField({
				value: "Choose Server/Database".localize() + ':',
				height: 22,
				bodyStyle: 'background-color: transparent;',
				hideLabel: true
			});
			cmbDb = new Ext.form.ComboBox({
				id: 'wPasteFuncs_serverDb_cmb',
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
			panelcmbDb = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [cmbDb]
			});

			// Palo Function Combo Box and Panel
			cmbPaloFuncs = new Ext.form.ComboBox({
				id: 'wPasteFuncs_paloFunc_cmb',
				disabled: true,
				store: storePaloFuncs,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 3,
				bodyStyle: 'background-color: transparent;',
				typeAhead: true,
				selectOnFocus: true,
				hideLabel: true,
				editable: false,
				forceSelection: true,
				triggerAction: 'all',
				mode: 'local',
				valueField: 'name',
				displayField: 'name'
			});
			panelcmbPaloFuncs = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [cmbPaloFuncs]
			});
			cmbPaloFuncs.setValue(storePaloFuncs.getAt(cmbPaloFuncsState).get('name'));

			// Attribute Cubes CheckBox and Panel
			chbAttrCubes = new Ext.form.Checkbox({
				id: 'wPasteFuncs_atrCubes_chk',
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 2,
				boxLabel: "Attribute Cubes".localize(),
				listeners:
				{
					check: function()
					{
						var tmpType = storeServDb.getAt(cmbDbState).get('type');
						if (chbAttrCubes.getValue())
						{
							dataMode = 2;
							if (tmpType == 'database')
								paloRpcServer.getCubeNames(servId, dbName, dataMode);
						}
						else
						{
							dataMode = 0;
							if (tmpType == 'database')
								paloRpcServer.getCubeNames(servId, dbName, dataMode);
						}
					}
				}
			});
			panelchbAttrCubes = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbAttrCubes]
			});

			// Guess Arguments CheckBox and Panel
			chbGuessArgs = new Ext.form.Checkbox({
				id: 'wPasteFuncs_guessArgs_chk',
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 4,
				boxLabel: "Guess Arguments".localize()
			});
			panelchbGuessArgs = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'form',
				autoWidth: true,
				autoHeight: true,
				items: [chbGuessArgs]
			});
			// <--- Combo Boxes ---> //

			// *** MAIN panel and Window *** //
			panelMain = that.containers.mainPanel = new Ext.Panel({
				id: 'pdf_mainPanel',
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'absolute',
				anchor: '100% 100%',
				monitorResize: true,
				listeners: {
					resize: _resizeAll
				},
				items: [panellistCubes, lbllistCubes, panelcmbDb, lblcmbDb, panelcmbPaloFuncs,
						panelchbAttrCubes, panelchbGuessArgs]
			});

			// Wizard Window
			that.win = new Ext.Window({
				id: 'wPasteFuncs_dlg_wnd',
				layout: 'fit',
				cls: 'default-format-window',
				title: "Paste Data Functions".localize(),
				width: 350,
				height: 490,
				minWidth: 350,
				minHeight: 490,
				closeAction: 'close',
				onEsc: Ext.emptyFn,
				autoDestroy: true,
				plain: true,
				modal: true,
				resizable: true,
				buttons: [btnPaste, btnClose],
				listeners: {
					activate: _resizeAll,
					close: function()
					{
						Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
						Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;

						that.close();
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.pasteDataFunctions);

						// set preselected server/db
						setTimeout(function(){
							paloRpcServer.setPreselectServDb(servId, dbName);
						},0);
					}
				},
				items: [panelMain]
			});
			// <--- MAIN panel and Window ---> //
			that.setContext();
		}

		// *** PUBLIC functions *** //
		this.show = function()
		{
			if (that.win)
				that.win.show();
				setTimeout(function(){
					//that.initFocus(true, 100);
				});
		}
		// <--- PUBLIC functions --->//

		// *** EVENT HANLDERS *** //
		var _cmbDbSelectionHandler = function(combo, record, index)
		{
			if (cmbDbState != index)
			{
				cmbDbState = index;
				if (record.get('type') == 'database')
				{
					servId = record.get('parent_id');
					dbName = record.get('name');

					paloRpcServer.getCubeNames(servId, dbName, dataMode);
				}
				else
					storeCubes.removeAll();
			}
		}
		// <--- EVENT HANDLERS ---> //

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

				var listW = w - 2*marginSize;
				var listH = h - 7*marginSize - 5*lineH;

				// dataView
				panellistCubes.setSize(listW, listH);
				panellistCubes.setPosition(marginSize, 3*marginSize + 3*lineH);

				// Combos and Labels
				cmbDb.setWidth(listW);
				panelcmbDb.setPosition(marginSize, marginSize + lineH);
				lblcmbDb.setPosition(marginSize, 3*marginSize);
				lbllistCubes.setPosition(marginSize, 5*marginSize + 2*lineH);
				panelcmbPaloFuncs.setPosition(marginSize, 5*marginSize + 3*lineH + listH);

				// CheckBoxes
				if (chbAttrCubes.rendered && chbGuessArgs.rendered)
				{
					var widthShow = Ext.util.TextMetrics.measure(chbAttrCubes.id, "Attribute Cubes".localize());
					panelchbAttrCubes.setPosition(w - widthShow.width - 35, 4*marginSize + 2*lineH);

					var widthShow2 = Ext.util.TextMetrics.measure(chbGuessArgs.id, "Guess Arguments".localize());
					panelchbGuessArgs.setPosition(w - widthShow2.width - 35, 5*marginSize + 3*lineH + listH + 2);
				}
			}
			that.activate();
		}

		this.init();
		this.show();
		Jedox.palo.utils.showLoadingMsg("Acquiring Server List".localize().concat(' ...'));
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.PasteFunctions, Jedox.dlg.Dialog);
